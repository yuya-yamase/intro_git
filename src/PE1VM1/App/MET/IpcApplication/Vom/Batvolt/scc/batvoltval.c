/* 2.0.3 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Toyota IPC/MET : Battery (+B) Voltage Value                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define BATVOLTVAL_C_MAJOR                  (2)
#define BATVOLTVAL_C_MINOR                  (0)
#define BATVOLTVAL_C_PATCH                  (3)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "batvoltval.h"
#include "batvoltval_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((BATVOLTVAL_C_MAJOR != BATVOLTVAL_H_MAJOR) || \
     (BATVOLTVAL_C_MINOR != BATVOLTVAL_H_MINOR) || \
     (BATVOLTVAL_C_PATCH != BATVOLTVAL_H_PATCH))
#error "batvoltval.c and batvoltval.h : source and header files are inconsistent!"
#endif

#if ((BATVOLTVAL_C_MAJOR != BATVOLTVAL_CFG_H_MAJOR) || \
     (BATVOLTVAL_C_MINOR != BATVOLTVAL_CFG_H_MINOR) || \
     (BATVOLTVAL_C_PATCH != BATVOLTVAL_CFG_H_PATCH))
#error "batvoltval.c and batvoltval_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* VEHVLT_ANA_STS SPI bit Assign */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1  u1_s_batvoltval_smpcnt;                        /* To store the Sample counter                                             */
static U2  u2_s_battvotval_avgvalue;                      /* To store the previous ADC average value                                 */
static U2  u2_s_batvoltval_smp[BATVOLTVAL_AVGSIZE];       /* Array to store the sample data                                          */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2 u2_s_BatVoltValADCConvScaled(U2 u2_a_adcval);
static U2 u2_s_BatVoltValAvg(U2 u2_a_batvoltval);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_BatVoltValInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*  Summary: Battery Voltage Value Initilization.                                                                                    */
/*===================================================================================================================================*/
void    vd_g_BatVoltValInit(void)
{
    U1 u1_t_cnt;

    /* Intialize the variables to default */
    u1_s_batvoltval_smpcnt   = (U1)0U;
    u2_s_battvotval_avgvalue  = (U2)BATVOLTVAL_INIT_VAL;

    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)BATVOLTVAL_AVGSIZE; u1_t_cnt++)
    {
        u2_s_batvoltval_smp[u1_t_cnt] = (U2)0U;
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_BatVoltValMainTask(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*  Summary: Battery Voltage Value Main Task - Gets ADC value (+B) and converts it into format for lcom_spi transmission.            */
/*===================================================================================================================================*/
void    vd_g_BatVoltValMainTask(void)
{   
    U1 u1_t_igon;
    U1 u1_t_cnt;
    U1 u1_t_adcsts;
    U2 u2_t_adcval;
    U2 u2_t_batvoltscale;
    U2 u2_t_batvolavg;

    /* Initialize voltage value & scale to minimum */
    u2_t_batvolavg = (U2)BATVOLTVAL_INIT_VAL;

    u1_t_igon = u1_g_BatVoltValCfgIgOn();

    if (u1_t_igon == (U1)TRUE)
    {
        /* Get ADC value for IG_MON (+B) */
        u1_t_adcsts = u1_g_BatVoltValCfgAdcRead(ADC_CH_IG_MON, &u2_t_adcval);
        
        if (u1_t_adcsts == (U1)TRUE) 
        {
            /* perform adc raw data to original Voltage */
            u2_t_batvoltscale  = u2_s_BatVoltValADCConvScaled(u2_t_adcval);
        }
        else
        {
            /* Adc status is False, so set the scale to default */
            u2_t_batvoltscale = (U2)BATVOLTVAL_VOLT_MIN;
        }

        u2_t_batvolavg  = u2_s_BatVoltValAvg(u2_t_batvoltscale);

    }
    else /* Ignition is off */
    {
        u1_s_batvoltval_smpcnt   = (U1)0U;

        for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)BATVOLTVAL_AVGSIZE; u1_t_cnt++)
        {
            u2_s_batvoltval_smp[u1_t_cnt] = (U2)0U;
        }
    }

    u2_s_battvotval_avgvalue = u2_t_batvolavg;
}

/*===================================================================================================================================*/
/*  void u2_s_BatVoltValAvg(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*  Summary: To calculate average of battery voltage values                                                                          */
/*===================================================================================================================================*/
static U2 u2_s_BatVoltValAvg(U2 u2_a_batvoltval)
{
    U2 u2_t_avg;
    U1 u1_t_cnt;
    U2 u2_t_sum;
    U2 u2_t_calcavg;

    u2_t_sum = (U2)0U;

    /* Boundary check for the sample counter */
    if (u1_s_batvoltval_smpcnt >= (U1)BATVOLTVAL_AVGSIZE)  
    {
         u1_s_batvoltval_smpcnt = (U1)0U; 
    }

    u2_s_batvoltval_smp[u1_s_batvoltval_smpcnt] = u2_a_batvoltval;

    /* Add the total data */
    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)BATVOLTVAL_AVGSIZE; u1_t_cnt++) 
    {
        u2_t_sum += u2_s_batvoltval_smp[u1_t_cnt];
    }

    /* Avegage data based on the Max sample */
    u2_t_avg = u2_t_sum / (U2)BATVOLTVAL_AVGSIZE;

    u1_s_batvoltval_smpcnt++;


    /* validate the Hystersis logic to adjust the output value */
    if (u2_t_avg > u2_s_battvotval_avgvalue) 
    {
        u2_t_calcavg = u2_t_avg - u2_s_battvotval_avgvalue;
    }
    else
    {
        u2_t_calcavg = u2_s_battvotval_avgvalue - u2_t_avg;
    }

    if (u2_t_calcavg <= (U2)BATVOLTVAL_VOLT_HYSTERESIS) 
    {
        u2_t_avg = u2_s_battvotval_avgvalue;
    }

    /* check the boundary condition before output the voltage value  */
    if (u2_t_avg >= (U2)BATVOLTVAL_VOLT_MAX)
    {
        u2_t_avg = (U2)BATVOLTVAL_VOLT_MAX;
    }
    else if (u2_t_avg <= (U2)BATVOLTVAL_VOLT_MIN)
    {
        u2_t_avg = (U2)BATVOLTVAL_VOLT_MIN;
    }
    else
    {
        /* do nothing */
    }

    return(u2_t_avg);
}

/*===================================================================================================================================*/
/*  U2 u2_s_BatVoltValADCConvScaled(U2 u2_a_adcval)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*  Summary: Battery Voltage Value ADC Conversion - Converts input ADC value based on Voltage Divider and ADC offset Scaled.         */
/*===================================================================================================================================*/
static U2 u2_s_BatVoltValADCConvScaled(U2 u2_a_adcval)
{
             U4 u4_t_batvolval;

    /* Voltage divider calculation */
	u4_t_batvolval = (((U4)u2_a_adcval * (U4)BATVOLTVAL_VOLT_LSB ) * (U4)IG_MON1_VOLTDIV_RVAL) / (U4)BATVOLTVAL_ADC_OFFSET;

    return ((U2)u4_t_batvolval);
}

/*===================================================================================================================================*/
/*  U2 vd_g_BatVoltValGetTx(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*  Summary: Battery Voltage Value Get Transmission - Return the Battery Voltage Gauge Percentage                                    */
/*===================================================================================================================================*/
U1 u1_g_BatVoltValGetDispVal(void)
{
    return ((U1)((u2_s_battvotval_avgvalue /u2_BATVOLTVAL_VOLT_OUT_LSB) - (U2)BATVOLTVAL_VOLT_OFFSET));
}


/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    04/16/2019  MP       New.                                                                                               */
/*  2.0.0    3/16/2021   KS       Redesign the Boost Pressure Gauge                                                                  */
/*  2.0.1    05/11/2021  KS       QAC Fixes                                                                                          */
/*  2.0.2    06/15/2021  KS       Implemented hysteresis logic based on MET-M_VOLT-CSTD-1-00-A-C1_en-787W-e (002).docx               */
/*  2.0.3    08/19/2021  KS       Defect Fix #4043799/4001118                                                                        */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * MP   = Martin Peltz Denso                                                                                                      */
/*  * KS   = Kannan Selvaraj Denso                                                                                                   */
/*===================================================================================================================================*/
