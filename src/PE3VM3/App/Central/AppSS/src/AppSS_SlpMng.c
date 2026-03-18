/****************************************************************************/
/*  Copyright DENSO Corporation                                             */
/****************************************************************************/
/****************************************************************************/
/*  AppSS.c                                                                 */
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "oxcan.h"
#include "ChipCom.h"
#include "ChipCom_Cfg.h"
#include "AppSS_SlpMng.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define APPSS_SLPMNG_SLEEPNG_ID_BIT1	(1U)	/* for bitmap calculation */
#define APPSS_SLPMNG_RESULT_SLEEPOK		(1U)	/* Sleep OK */
#define APPSS_SLPMNG_RESULT_SLEEPNG	    (0U)	/* Sleep NG */

#define APPSS_SLPMNG_TRANSREQ_LENGTH	(1U)	/* chipcom：data length(1byte) */

/* Debug Code */
static U1 AppSS_SlpMng_TestTimer = 0U;
static U1 AppSS_SlpMng_Flag = 0U;
/* Debug Code */

/*--------------------------------------------------------------------------*/
/* External Functions                                                       */
/*--------------------------------------------------------------------------*/
void AppSS_SlpMng_Init(void)
{

	return;
}

void AppSS_SlpMng_Main(void)
{
    U1 u1_t_sht_ok = (U1)TRUE;
    U1 u1_t_slp_req_data = (U1)APPSS_SLPMNG_RESULT_SLEEPOK;

    /*  CAN Bus SleepOK/NG Check*/
    //u1_t_sht_ok = u1_g_oXCANShtdwnOk();
    /* Debug Code */
    if(AppSS_SlpMng_TestTimer >= 20U){
		if (AppSS_SlpMng_Flag == 0U) {
			u1_t_sht_ok = (U1)TRUE;
		} else {
			u1_t_sht_ok = (U1)FALSE;
		}
		AppSS_SlpMng_TestTimer = 0U;
		AppSS_SlpMng_Flag = ~AppSS_SlpMng_Flag;
	}
    /* Debug Code */

    /* Send Sleep state */
    switch (u1_t_sht_ok) {
        case (U1)TRUE:
            /* Send SleepOK state */
            u1_t_slp_req_data = (U1)APPSS_SLPMNG_RESULT_SLEEPOK;
            (void)ChipCom_SendSignal((Com_SignalIdType)SIGNAL_CHIPCOM_BUS_CSS1M01_CANWKUPSLP, &u1_t_slp_req_data);
            break;
        case (U1)FALSE:
            /* Send SleepNG state */
            u1_t_slp_req_data = (U1)APPSS_SLPMNG_RESULT_SLEEPNG;
            (void)ChipCom_SendSignal((Com_SignalIdType)SIGNAL_CHIPCOM_BUS_CSS1M01_CANWKUPSLP, &u1_t_slp_req_data);
            break;
        default:
            /* Send SleepOK state */
            u1_t_slp_req_data = (U1)APPSS_SLPMNG_RESULT_SLEEPOK;
            (void)ChipCom_SendSignal((Com_SignalIdType)SIGNAL_CHIPCOM_BUS_CSS1M01_CANWKUPSLP, &u1_t_slp_req_data);
            break;
    }

    return;
}

/**** End of File ***********************************************************/
