/* 2.5.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Throughput Measure                                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                                   */
/*                                                                                                                                   */
#if ((defined(__AIP_THROUGHPUT__)) && (__AIP_THROUGHPUT__ == 1))
/*                                                                                                                                   */
/*                                                                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define THROUGHPUT_CFG_C_MAJOR                   (2)
#define THROUGHPUT_CFG_C_MINOR                   (5)
#define THROUGHPUT_CFG_C_PATCH                   (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "throughput_cfg_private.h"

#define __THROUGHPUT_CFG_BOOT_MEAS__             (0)
#if (__THROUGHPUT_CFG_BOOT_MEAS__ == 1)
#include "mcu_drv.h"
#include "dio_drv.h"
#include "veh_opemd.h"
#endif /* #if (__THROUGHPUT_CFG_BOOT_MEAS__ == 1) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((THROUGHPUT_CFG_C_MAJOR != THROUGHPUT_CFG_H_MAJOR) || \
     (THROUGHPUT_CFG_C_MINOR != THROUGHPUT_CFG_H_MINOR) || \
     (THROUGHPUT_CFG_C_PATCH != THROUGHPUT_CFG_H_PATCH))
#error "throughput_cfg.c and throughput_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define THROUGHPUT_AVG_WEIGHT_MAX                (200U)              /* 100 %  4byte, 0xffffffff/20,000,000(20ms) = 214 */
#define THROUGHPUT_AVG_WEIGHT_MIN                (20U)               /* 10  %                                           */
#define THROUGHPUT_AVG_WEIGHT_DELTA              (2U)                /* 1   %                                           */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u4_THROUGHPIT_FRT_TO_0P1US(frt)          ((U4)(((frt) + (U4)4U) >> 3U))     /* Frt:80MHz -> 10MHz */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U2      u2_irq_ch;
    U2      u2_task_id;
}ST_THROUGHPUT_IRQ;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
volatile U4               u4_gp_throughput_errlog[THROUGHPUT_ERR_NUM_INFO]; /* Error Checker */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4                 u4_sp_throughput_task_max[THRPTM_NUM_TASK];
static U4                 u4_sp_throughput_task_avg[THRPTM_NUM_TASK];
static U2                 u2_sp_throughput_task_weight[THRPTM_NUM_TASK];

static volatile U4        u4_s_throughput_0p1us_capt;
static volatile U2        u2_s_throughput_task_id;

static U4                 u4_sp_throughput_csc_max[THRPTM_NUM_CSC];

#define THROUGHPIT_NUM_VD_FVD                    (128U)
U4                        u4_sp_throughput_vd_fvd[THROUGHPIT_NUM_VD_FVD];
static volatile U2        u2_s_throughput_vd_fvd_id;

#if (__THROUGHPUT_CFG_BOOT_MEAS__ == 1)
static U1                 u1_s_throughput_igon_cnt;
static U1                 u1_s_throughput_igon_bak;
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_ThroughputCfgInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ThroughputCfgInit(void)
{
    U4                 u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)THRPTM_NUM_CSC; u4_t_lpcnt++){
        u4_sp_throughput_csc_max[u4_t_lpcnt] = (U4)0U;
    }

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)THRPTM_NUM_TASK; u4_t_lpcnt++){
        u4_sp_throughput_task_max[u4_t_lpcnt] = (U4)0U;
        u4_sp_throughput_task_avg[u4_t_lpcnt] = (U4)0U;
        u2_sp_throughput_task_weight[u4_t_lpcnt] = (U2)THROUGHPUT_AVG_WEIGHT_MAX;
    }

    u4_s_throughput_0p1us_capt = (U4)0U;
    u2_s_throughput_task_id    = (U2)U2_MAX;

    /*---------------------------------------------------------------------------------------------------------------*/
    /* Note :                                                                                                        */
    /*                                                                                                               */
    /* DO NOT INITIALIZE u4_gp_throughput_vd_fvd[] because vd_g_ThroughputCfgInit is being called right before ECU   */
    /* transits to RUN.                                                                                              */
    /*---------------------------------------------------------------------------------------------------------------*/

#if (__THROUGHPUT_CFG_BOOT_MEAS__ == 1)
    u1_s_throughput_igon_cnt = (U1)0U;
    u1_s_throughput_igon_bak = (U1)FALSE;
#endif
}
/*===================================================================================================================================*/
/*  U2    u2_g_ThroughputCfgMeasOvrhd(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2    u2_g_ThroughputCfgMeasOvrhd(void)
{
    volatile U4      u4_t_plm;
    volatile U4      u4_t_gli;
    volatile U4      u4_t_start;
    U4               u4_t_ovrhd;

    u4_t_plm = u4_g_PLM_DI((U4)0U);

#if (__THROUGHPUT_INTRPT_DI_BY_CALLER__ == 1)
    vd_g_IRQ_EI((U4)INT_DRV_IRQ_PRI_EI);
#else
    vd_g_IRQ_EI((U4)INT_DRV_IRQ_USR_EI);
#endif

    u4_t_start = u4_g_ThroughputCfgFrt();

    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);          /* 10 */

    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);          /* 20 */

    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);          /* 30 */

    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);          /* 40 */

    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);          /* 50 */

    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);          /* 60 */

    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);
    u4_t_gli = u4_g_IRQ_DI();
    vd_g_IRQ_EI(u4_t_gli);          /* 64 */

    u4_t_ovrhd = u4_g_ThroughputCfgFrt() - u4_t_start;

    (void)u4_g_IRQ_DI();
    vd_g_PLM_EI(u4_t_plm);

    if(u4_t_ovrhd > (U4)U2_MAX){
        u4_t_ovrhd = (U4)U2_MAX;
    }

    return((U2)u4_t_ovrhd);
}
/*===================================================================================================================================*/
/*  U2      u2_g_ThroughputCfgIrqOvrhd(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_ThroughputCfgIrqOvrhd(void)
{
    /*----------------------------------------------------------*/
    /* Warning :                                                */
    /*                                                          */
    /* IRQ overhead of RTOS is unknown, so not considered.      */
    /* Task execution time may be overestimated.                */
    /* Interrupt handling time may be under- or overestimated.  */
    /*----------------------------------------------------------*/
    return((U2)0U);
}
/*===================================================================================================================================*/
/*  void    vd_g_ThroughputCfgIsrCapt(const U2 u2_a_IRQ_CH, const U4 u4_a_THROUGHPUT)                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ThroughputCfgIsrCapt(const U2 u2_a_IRQ_CH, const U4 u4_a_THROUGHPUT)
{
    if(u2_a_IRQ_CH < (U2)THRPTM_NUM_IRQ_CH){
        vd_g_ThroughputCfgTaskCapt(u2_a_IRQ_CH, u4_a_THROUGHPUT);
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_ThroughputCfgTaskCapt(const U2 u2_a_TASK_ID, const U4 u4_a_THROUGHPUT)                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ThroughputCfgTaskCapt(const U2 u2_a_TASK_ID, const U4 u4_a_THROUGHPUT)
{
    static const U4                   u4_s_THROUGHPUT_AVG_MAX = (U4)U4_MAX / (U4)THROUGHPUT_AVG_WEIGHT_MAX;

    U4                                u4_t_avg;
    U4                                u4_t_0p1us_capt;

    if(u2_a_TASK_ID < (U2)THRPTM_NUM_TASK){

        u4_t_0p1us_capt = u4_THROUGHPIT_FRT_TO_0P1US(u4_a_THROUGHPUT);
        if(u4_sp_throughput_task_max[u2_a_TASK_ID] < u4_t_0p1us_capt){
            u4_sp_throughput_task_max[u2_a_TASK_ID] = u4_t_0p1us_capt;
        }

        if(u2_sp_throughput_task_weight[u2_a_TASK_ID] >= (U2)THROUGHPUT_AVG_WEIGHT_MAX){
            u2_sp_throughput_task_weight[u2_a_TASK_ID] = (U2)THROUGHPUT_AVG_WEIGHT_MAX;
        }
        else if(u2_sp_throughput_task_weight[u2_a_TASK_ID] <= (U2)THROUGHPUT_AVG_WEIGHT_MIN){
            u2_sp_throughput_task_weight[u2_a_TASK_ID] = (U2)THROUGHPUT_AVG_WEIGHT_MIN;
        }
        else{
            /* do nothing */
        }

        if((u4_t_0p1us_capt                         <= u4_s_THROUGHPUT_AVG_MAX) &&
           (u4_sp_throughput_task_avg[u2_a_TASK_ID] <= u4_s_THROUGHPUT_AVG_MAX)){

            u4_t_avg  = (U4)THROUGHPUT_AVG_WEIGHT_MAX - (U4)u2_sp_throughput_task_weight[u2_a_TASK_ID];
            u4_t_avg *=  u4_sp_throughput_task_avg[u2_a_TASK_ID];
            u4_t_avg += (u4_t_0p1us_capt * (U4)u2_sp_throughput_task_weight[u2_a_TASK_ID]);
            u4_sp_throughput_task_avg[u2_a_TASK_ID] = u4_t_avg / (U4)THROUGHPUT_AVG_WEIGHT_MAX;

            if(u2_sp_throughput_task_weight[u2_a_TASK_ID] >= (U2)THROUGHPUT_AVG_WEIGHT_DELTA){
                u2_sp_throughput_task_weight[u2_a_TASK_ID] -= (U2)THROUGHPUT_AVG_WEIGHT_DELTA;
            }
        }
        else{
            u4_sp_throughput_task_avg[u2_a_TASK_ID] = (U4)U4_MAX;
        }

        if(u2_a_TASK_ID == u2_s_throughput_task_id){
            u4_s_throughput_0p1us_capt = u4_t_0p1us_capt; /* Set OCD break at here */
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_ThroughputCfgCscCapt(const U2 u2_a_CSC_ID, const U4 u4_a_THROUGHPUT)                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ThroughputCfgCscCapt(const U2 u2_a_CSC_ID, const U4 u4_a_THROUGHPUT)
{
    U4                                u4_t_0p1us_capt;

    if(u2_a_CSC_ID < (U2)THRPTM_NUM_CSC){

        u4_t_0p1us_capt = u4_THROUGHPIT_FRT_TO_0P1US(u4_a_THROUGHPUT);
        if(u4_sp_throughput_csc_max[u2_a_CSC_ID] < u4_t_0p1us_capt){
            u4_sp_throughput_csc_max[u2_a_CSC_ID] = u4_t_0p1us_capt;
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_ThroughputCfgToRun(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ThroughputCfgToRun(void)
{
#if (__THROUGHPUT_CFG_BOOT_MEAS__ == 1)
    /* ---------------------------------------------------------------------------- */
    /* Attention :                                                                  */
    /* ---------------------------------------------------------------------------- */
    /* MCU/ECU start/shutdown time shall be re-measured by using digital I/O and    */
    /* oscilloscope if following configuraitons are modified.                       */
    /*                                                                              */
    /* 1. Size of the ".XXX_STACK"                                                  */
    /* 2. Size of the ".data" section.                                              */
    /* 3. Size of the ".bss_BSW" section.                                           */
    /* 4. Size of the ".bss_BACK_BSW" section.                                      */
    /* 5. Implementation of ecu_m_usrhk                                             */
    /* ---------------------------------------------------------------------------- */

    /* ---------------------------------------------------------------------------- */
    /* HOW TO USE :                                                                 */
    /* ---------------------------------------------------------------------------- */
    /* If a level of test pin is low when ECU is in low power mode, set high in     */
    /* this function. If high, set low.                                             */
    /* ---------------------------------------------------------------------------- */
    vd_g_Dio_WriteChannel((U2)DIO_CH_ID_P42_12, (U1)DIO_LVL_HIGH); /* 153pin */
#endif
}
/*===================================================================================================================================*/
/*  void    vd_g_ThroughputCfgMainTask(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ThroughputCfgMainTask(void)
{
#if (__THROUGHPUT_CFG_BOOT_MEAS__ == 1)
    static const U1                   u1_s_THROUGHPUT_IGON_CNT_TO_RST = (U1)5U;
    volatile U4                       u4_t_gli;
    U1                                u1_t_igon;

    u1_t_igon = u1_g_VehopemdIgnOn();
    if((u1_t_igon                == (U1)TRUE  ) &&
       (u1_s_throughput_igon_bak == (U1)FALSE ) &&
       (u1_s_throughput_igon_cnt  < (U1)U1_MAX)){

        u1_s_throughput_igon_cnt++;
    }
    u1_s_throughput_igon_bak = u1_t_igon;

    if(u1_s_throughput_igon_cnt >= u1_s_THROUGHPUT_IGON_CNT_TO_RST){

        u4_t_gli = u4_g_IRQ_DI();

        vd_g_Dio_WriteChannel((U2)DIO_CH_ID_P42_12, (U1)DIO_LVL_LOW); /* 153pin */
/*        vd_g_TYCanUsrhkTrcvToInact((U1)0); */
        vd_g_Mcu_PerformReset((U1)MCU_RESET_TYPE_HARD);

        vd_g_IRQ_EI(u4_t_gli);
    }
#endif /* #if (__THROUGHPUT_CFG_BOOT_MEAS__ == 1) */
}
/*===================================================================================================================================*/
/*  void    vd_g_ThroughputCfgToShtdwn(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ThroughputCfgToShtdwn(void)
{
#if (__THROUGHPUT_CFG_BOOT_MEAS__ == 1)
    static const U4                   u4_s_THROUGHPUT_WUF_CHBIT_CAN = (U4)0x00000200U;   /* WUF0.WUF11    */
    static volatile U1 * const        u1_sp_THROUGHPUT_RADDR_ELVL   = (volatile U1 *)0xFFC34104U;
                                             /* set address for CAN assinged to external interrupt.      */
                                             /* 1. WUF0[7]  INTP6/CAN0RX           : 0xFFC3401C          */
                                             /* 2. WUF0[9]  INTP8/CAN1RX/RLIN30RX  : 0xFFC34104          */
                                             /* 3. WUF0[11] INTP10/CAN2RX/RLIN30RX : 0xFFC3410C          */

    static const U1                   u1_s_THROUGHPUT_IGON_CNT_JMP_STA = (U1)2U;

    static const U1                   u1_s_THROUGHPUT_ELVL_CH_HI    = (U1)0x05U;
    volatile U4 *                     u4_tp_word;
    volatile U1 *                     u1_tp_byte;
    U4                                u4_t_irqbit;
    volatile U4                       u4_t_gli;
    volatile U4                       u4_t_dummyrd;
    U1                                u1_t_elvl_bak;

    if(u1_s_throughput_igon_cnt >= u1_s_THROUGHPUT_IGON_CNT_JMP_STA){

        u4_t_gli = u4_g_IRQ_DI();

        u1_tp_byte = u1_sp_THROUGHPUT_RADDR_ELVL;

        u1_t_elvl_bak = u1_REG_READ(*u1_tp_byte);
        vd_REG_U1_WRITE(*u1_tp_byte, u1_s_THROUGHPUT_ELVL_CH_HI);
        u4_t_dummyrd  = (U4)u1_REG_READ(*u1_tp_byte);

        u4_tp_word = (volatile U4 *)0xFFF80400U;     /* WUF0     */
        do{
            u4_t_irqbit = u4_REG_READ(*u4_tp_word) & u4_s_THROUGHPUT_WUF_CHBIT_CAN;
        }while(u4_t_irqbit == (U4)0);

        vd_REG_U1_WRITE(*u1_tp_byte, u1_t_elvl_bak);
        u4_t_dummyrd  = (U4)u1_REG_READ(*u1_tp_byte);

        vd_g_IRQ_EI(u4_t_gli);
    }

    /* ---------------------------------------------------------------------------- */
    /* Attention :                                                                  */
    /* ---------------------------------------------------------------------------- */
    /* MCU/ECU start/shutdown time shall be re-measured by using digital I/O and    */
    /* oscilloscope if following configuraitons are modified.                       */
    /*                                                                              */
    /* 1. Size of the ".XXX_STACK"                                                  */
    /* 2. Size of the ".data" section.                                              */
    /* 3. Size of the ".bss_BSW" section.                                           */
    /* 4. Size of the ".bss_BACK_BSW" section.                                      */
    /* 5. Implementation of ecu_m_usrhk                                             */
    /* ---------------------------------------------------------------------------- */

    /* ---------------------------------------------------------------------------- */
    /* HOW TO USE :                                                                 */
    /* ---------------------------------------------------------------------------- */
    /* If a level of test pin is low when ECU is in low power mode, set high in     */
    /* this function. If high, set low.                                             */
    /* ---------------------------------------------------------------------------- */
    vd_g_Dio_WriteChannel((U2)DIO_CH_ID_P42_12, (U1)DIO_LVL_LOW); /* 153pin */
#endif /* #if (__THROUGHPUT_CFG_BOOT_MEAS__ == 1) */
}
/*===================================================================================================================================*/
/*  void    vd_g_ThroughputCfg_vd_Fvd_Start(const U2 u2_a_vd_FVD_ID)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ThroughputCfg_vd_Fvd_Start(const U2 u2_a_vd_FVD_ID)
{
    /* ---------------------------------------------------------------------------- */
    /* Warning :                                                                    */
    /* ---------------------------------------------------------------------------- */
    /* Initialize static variables in this function if vd_g_Throughput_vd_Fvd is    */
    /* called before ECU transits to RUN.                                           */
    /* Otherwise RAM ECC error might be detected and Data Abort Exception is        */
    /* invoked.                                                                     */
    /* ---------------------------------------------------------------------------- */
}
/*===================================================================================================================================*/
/*  void    vd_g_ThroughputCfg_vd_Fvd_Capt(const U2 u2_a_LP_IDX, const U4 u4_a_THROUGHPUT)                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ThroughputCfg_vd_Fvd_Capt(const U2 u2_a_LP_IDX, const U4 u4_a_THROUGHPUT)
{
    if(u2_a_LP_IDX < (U2)THROUGHPIT_NUM_VD_FVD){
        u4_sp_throughput_vd_fvd[u2_a_LP_IDX] = u4_THROUGHPIT_FRT_TO_0P1US(u4_a_THROUGHPUT);
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_ThroughputCfg_vd_Fvd_Finish(const U2 u2_a_vd_FVD_ID)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_ThroughputCfg_vd_Fvd_Finish(const U2 u2_a_vd_FVD_ID)
{
    u2_s_throughput_vd_fvd_id = u2_a_vd_FVD_ID;  /* Set OCD break at here */
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                                   */
/*                                                                                                                                   */
#endif /* #if ((defined(__AIP_THROUGHPUT__)) && (__AIP_THROUGHPUT__ == 1)) */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     5/29/2015  TN       New.                                                                                               */
/*  1.1.0     6/12/2015  TN       u2_g_ThroughputCfgCalcOvrhd() -> u2_g_ThroughputCfgMeasOvrhd()                                     */
/*                                u2_g_ThroughputCfgIrqOvrhd() was implemented instead of u4_g_THROUGHPUT_OVRHD_FRT_INTRPT.          */
/*  1.2.0     6/25/2015  TN       throughput.c v1.1.0 -> v1.2.0.                                                                     */
/*  2.0.0    10/12/2015  TN       throughput.c v1.2.0 -> v2.0.0.                                                                     */
/*  2.1.0     1/15/2016  TN       throughput.c v2.0.0 -> v2.1.0.                                                                     */
/*  2.2.0     1/20/2016  TN       vd_g_ThroughputCfg_vd_Fvd_Start, vd_g_ThroughputCfg_vd_Fvd_Capt and                                */
/*                                vd_g_ThroughputCfg_vd_Fvd_Finish were implemented.                                                 */
/*                                vd_g_ThroughputCfgIsrUpdt  -> vd_g_ThroughputCfgIsrCapt                                            */
/*                                vd_g_ThroughputCfgTaskUpdt -> vd_g_ThroughputCfgTaskCapt                                           */
/*                                Throughput resolution was changed from 1[us] to 0.1[us].                                           */
/*            2/ 3/2016  TN       vd_g_ThroughputCfghkToXXXXX -> vd_g_ThroughputCfgToXXXXX.                                          */
/*  2.3.0     2/ 4/2016  TN       vd_g_ThroughputMainTask was implemented.                                                           */
/*  2.4.0     2/19/2016  TN       throughput.c v2.3.0 -> v2.4.0.                                                                     */
/*            6/17/2016  TN       Bug Fix : Round calculation was incorrect in u4_s_ThroughputCfgResConvervt.                        */
/*  2.4.1     9/ 7/2021  TN       throughput.c v2.4.0 -> v2.4.1.                                                                     */
/*  2.5.0     9/15/2021  TN       throughput.c v2.4.1 -> v2.5.0.                                                                     */
/*  2.5.1    11/22/2023  KM       throughput.c v2.5.0 -> v2.5.1.                                                                     */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * KM   = Kazuyuki Makino, DENSO.                                                                                                 */
/*                                                                                                                                   */
/*===================================================================================================================================*/
