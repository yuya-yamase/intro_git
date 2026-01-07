/* 0.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Date clock Synchronization Interface                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DATESI_TIM_CFG_C_MAJOR                  (0)
#define DATESI_TIM_CFG_C_MINOR                  (0)
#define DATESI_TIM_CFG_C_PATCH                  (1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "datesi_tim_cfg_private.h"
#include "datesi_cfg_private.h"
#include "datesi_com.h"
#include "oxcan.h"
#include "rim_ctl.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DATESI_TIM_CFG_C_MAJOR != DATESI_TIM_H_MAJOR) || \
     (DATESI_TIM_CFG_C_MINOR != DATESI_TIM_H_MINOR) || \
     (DATESI_TIM_CFG_C_PATCH != DATESI_TIM_H_PATCH))
#error "datesi_tim_cfg.c and datesi_tim.h : source and header files are inconsistent!"
#endif

#if ((DATESI_TIM_CFG_C_MAJOR != DATESI_TIM_CFG_H_MAJOR) || \
     (DATESI_TIM_CFG_C_MINOR != DATESI_TIM_CFG_H_MINOR) || \
     (DATESI_TIM_CFG_C_PATCH != DATESI_TIM_CFG_H_PATCH))
#error "datesi_tim_cfg.c and datesi_tim_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define DATESI_TIM_SET_12H                      (1U)
#define DATESI_TIM_SET_24H                      (2U)
#define DATESI_TIM_12H_BIT_TO_AMPM              (18U)

#define DATESI_TIM_OFFSET_SIGN_P                (1U)
#define DATESI_TIM_OFFSET_SIGN_M                (2U)

#define DATESI_TIM_SHIFT_HRUP                   (7U)
#define DATESI_TIM_SHIFT_HRDW                   (6U)
#define DATESI_TIM_SHIFT_MIUP                   (5U)
#define DATESI_TIM_SHIFT_MIDW                   (4U)
#define DATESI_TIM_SHIFT_SET                    (3U)
#define DATESI_TIM_SHIFT_12_24                  (2U)
#define DATESI_TIM_SHIFT_OFFSETUP               (1U)
#define DATESI_TIM_SHIFT_OFFSETDW               (0U)

#define DATESI_TIM_OFST_INIT                    (0)

#define DATESI_TIM_OFST_CNT_INIT                (0U)
#define DATESI_TIM_OFST_CNT_END                 (3000U / DATESI_TIM_MAIN_TICK)
#define DATESI_TIM_OFST_STS_NON                 (0U)
#define DATESI_TIM_OFST_STS_ADJ                 (1U)

#define DATESI_TIM_HALF_HOUR                    (HHMMSS_HR_TO_SE / 2U)

#define DATESI_TIM_FMT_NUM_VAL                  (2U)
#define DATESI_TIM_FMT_VAL_24H                  (0U)
#define DATESI_TIM_FMT_VAL_12H                  (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  U1                                      u1_s_datesi_tim_tmchg_tx_cnt;
static  U2                                      u2_s_datesi_tim_bus_sts_old;
static  U2                                      u2_s_datesi_tim_ofstcnt;
static  U1                                      u1_s_datesi_tim_ofststs;
static  S4                                      s4_s_datesi_tim_ofsttime;
static  U1                                      u1_s_datesi_tim_fmt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static  void    vd_s_DateSITimCfgCxpiTx(const U1 u1_a_CXPI_TRIG, const U1 * u1_ap_TIME, const U1 u1_a_EVENT_EI);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const   S4                                      s4_g_DATESI_TIM_OFFSET_MIN        = ((S4)HHMMSS_HR_TO_SE * (S4)(-6));
const   S4                                      s4_g_DATESI_TIM_OFFSET_MAX        = ((S4)HHMMSS_HR_TO_SE * (S4)6);
const   S4                                      s4_g_DATESI_TIM_TIMZN_MIN         = (((S4)HHMMSS_HR_TO_SE * (S4)(-15)) - (S4)DATESI_TIM_HALF_HOUR);
const   S4                                      s4_g_DATESI_TIM_TIMZN_MAX         = (((S4)HHMMSS_HR_TO_SE * (S4)16) + (S4)DATESI_TIM_HALF_HOUR);

const   U2                                      u2_gp_TIMEZONE_RIMID[TIMEZONE_NUM_RX] = {
    (U2)RIMID_U1_TIMEZONE_TZ,                   /* TIMEZONE_RX_TZ                    (0U) */
    (U2)RIMID_U1_TIMEZONE_TZ_SIGN,              /* TIMEZONE_RX_TZ_SIGN               (1U) */
    (U2)RIMID_U1_TIMEZONE_DST_S30               /* TIMEZONE_RX_DST_S30               (2U) */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((DATESI_TIM_STSBIT_UNKNOWN != COM_NO_RX  ) || \
     (DATESI_TIM_STSBIT_INVALID != COM_TIMEOUT))
#error "datesi_tim status bit and com status bit are inconsistent!"
#endif
/*===================================================================================================================================*/
/* void            vd_g_DateSITimCfgBonInit(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSITimCfgBonInit(void)
{
    u1_s_datesi_tim_tmchg_tx_cnt = (U1)DATESI_TIM_MIN_TX_NUM;
    u2_s_datesi_tim_bus_sts_old  = (U2)DATESI_TIM_NM_STS_UNINIT;
    u2_s_datesi_tim_ofstcnt      = (U2)DATESI_TIM_OFST_CNT_INIT;
    u1_s_datesi_tim_ofststs      = (U1)DATESI_TIM_OFST_STS_NON;
    u1_s_datesi_tim_fmt          = (U1)DATESI_TIM_FMT_VAL_12H;

    vd_g_Rim_WriteU1((U2)RIMID_U1_TIME_FORMAT, u1_s_datesi_tim_fmt);
}

/*===================================================================================================================================*/
/* S4              s4_g_DateSITimCfgBonOfstTime(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
S4              s4_g_DateSITimCfgBonOfstTime(void)
{
    U2  u2_t_ofsttime;
    S2  s2_t_ofsttime;

    u2_t_ofsttime = (U2)DATESI_TIM_OFST_INIT;
    
    vd_g_Rim_WriteU2((U2)RIMID_U2_OFFSET_TIME, u2_t_ofsttime);
    s2_t_ofsttime            = (S2)u2_t_ofsttime;
    s4_s_datesi_tim_ofsttime = (S4)s2_t_ofsttime;

    return(s4_s_datesi_tim_ofsttime);
}

/*===================================================================================================================================*/
/* void            vd_g_DateSITimCfgRstWkupInit(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSITimCfgRstWkupInit(void)
{
    U1  u1_t_rim_sts;
    U1  u1_t_rim_data;

    u1_s_datesi_tim_tmchg_tx_cnt = (U1)DATESI_TIM_MIN_TX_NUM;
    u2_s_datesi_tim_bus_sts_old  = (U2)DATESI_TIM_NM_STS_UNINIT;
    u2_s_datesi_tim_ofstcnt      = (U2)DATESI_TIM_OFST_CNT_INIT;
    u1_s_datesi_tim_ofststs      = (U1)DATESI_TIM_OFST_STS_NON;
    u1_s_datesi_tim_fmt          = (U1)DATESI_TIM_FMT_VAL_12H;

    u1_t_rim_data = (U1)0U;
    u1_t_rim_sts  = u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_TIME_FORMAT, &u1_t_rim_data);
    if(((u1_t_rim_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK) && (u1_t_rim_data < (U1)DATESI_TIM_FMT_NUM_VAL)){
        u1_s_datesi_tim_fmt = u1_t_rim_data;
    }

}

/*===================================================================================================================================*/
/* S4              s4_g_DateSITimCfgWkupOfstTime(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
S4              s4_g_DateSITimCfgWkupOfstTime(void)
{
    U1  u1_t_rim_sts;
    U2  u2_t_rim_data;
    S2  s2_t_ofsttime;
    S4  s4_t_ofsttime;

    s4_t_ofsttime = (S4)DATESI_TIM_OFST_INIT;

    u2_t_rim_data = (U2)0U;
    u1_t_rim_sts  = u1_g_Rim_ReadU2withStatus((U2)RIMID_U2_OFFSET_TIME, &u2_t_rim_data);
    if((u1_t_rim_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        s2_t_ofsttime = (S2)u2_t_rim_data;
        s4_t_ofsttime = (S4)s2_t_ofsttime;
    }
    s4_s_datesi_tim_ofsttime = s4_t_ofsttime;

    return(s4_s_datesi_tim_ofsttime);
}

/*===================================================================================================================================*/
/* U1              U1_g_DateSITimCfgInitOfstTime(S4 * s4p_a_offset_time)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_DateSITimCfgInitOfstTime(S4 * s4p_a_offset_time)
{
    U4  u4_t_read;
    U2  u2_t_ofsttime;
    S2  s2_t_offset_time;
    U1  u1_t_read_sts;

    u4_t_read        = (U4)0U;
    u1_t_read_sts    = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_VM1TO2_TIMOFST, &u4_t_read, (U2)DATESI_TIME_VM_1WORD);
    if((u1_t_read_sts != (U1)IVDSH_NO_REA) && (u4_t_read <= (U4)U2_MAX)){
        u2_t_ofsttime            = (U2)u4_t_read;
        s2_t_offset_time         = (S2)u2_t_ofsttime;
        (*s4p_a_offset_time)     = (S4)s2_t_offset_time;
        s4_s_datesi_tim_ofsttime = (S4)s2_t_offset_time;
        vd_g_Rim_WriteU2((U2)RIMID_U2_OFFSET_TIME, u2_t_ofsttime);
    }

    return(u1_t_read_sts);
}

/*===================================================================================================================================*/
/* U1              u1_g_DateSITimCfgEcuExst(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_DateSITimCfgEcuExst(void)
{
    return((U1)TRUE);
}

/*===================================================================================================================================*/
/* U1              u1_g_DateSITimCfgRxMsgSts(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_DateSITimCfgRxMsgSts(void)
{
    U1  u1_t_status;

    u1_t_status = (U1)DATESI_TIM_STSBIT_VALID;

    return(u1_t_status);
}

/*===================================================================================================================================*/
/* U1              u1_g_DateSITimCfgCanRx(ST_DATESI_TIM_RX * stp_a_rx)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_DateSITimCfgCanRx(ST_DATESI_TIM_RX * stp_a_rx)
{
    ST_DATESI_COMMAND_DATA  st_t_command_data;
    U1                      u1_t_status;

    u1_t_status = (U1)DATESI_TIM_STSBIT_VALID;

    st_t_command_data = st_g_DateSIComRx();
    stp_a_rx->u1p_time[HHMMSS_24H_TIME_SE] = st_t_command_data.u1_clk_sec;
    stp_a_rx->u1p_time[HHMMSS_24H_TIME_MI] = st_t_command_data.u1_clk_min;
    stp_a_rx->u1p_time[HHMMSS_24H_TIME_HR] = st_t_command_data.u1_clk_hour;
    stp_a_rx->u1_valid                     = st_t_command_data.u1_gps_st;
    stp_a_rx->u1_act                       = st_t_command_data.u1_gps_crct;

    return(u1_t_status);
}

/*===================================================================================================================================*/
/* void            vd_g_DateSITimCfgCanTx(const U4 u4_a_HHMMSS_24H, const U1 u1_a_EVENT_EI)                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSITimCfgCanTx(const U4 u4_a_HHMMSS_24H, const U1 u1_a_EVENT_EI)
{
    U4  u4_t_hhmmss;
    U4  u4_t_fmt_is12h;
    U1  u1_t_read_sts;
    U1  u1_t_ampm;
    U1  u1_t_timeset;
    U1  u1_t_pretx;
    U1  u1_t_can_trig;
    U1  u1_t_cxpi_trig;
    U1  u1_tp_time[HHMMSS_24H_TIME_SIZE];
    U1  u1_t_nmchk;
    U1  u1_t_nmmod;
    U2  u2_t_bus_sts;
    U1  u1_t_ba_is_on;
    U1  u1_t_acc_is_on;
    U1  u1_t_ig_is_on;

    u4_t_fmt_is12h = (U4)0U;
    u1_t_read_sts  = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_VM1TO2_TIMFMT, &u4_t_fmt_is12h, (U2)DATESI_TIME_VM_1WORD);
    if((u1_t_read_sts != IVDSH_NO_REA) && (u4_t_fmt_is12h < (U4)DATESI_TIM_FMT_NUM_VAL)){
        if(u1_s_datesi_tim_fmt != (U1)u4_t_fmt_is12h){
            u1_s_datesi_tim_fmt = (U1)u4_t_fmt_is12h;
            vd_g_Rim_WriteU1((U2)RIMID_U1_TIME_FORMAT, (U1)u4_t_fmt_is12h);
        }
    }
    u4_t_hhmmss    = u4_a_HHMMSS_24H;
    u1_t_timeset   = (U1)DATESI_TIM_SET_24H;

    if(u1_s_datesi_tim_fmt == (U1)DATESI_TIM_FMT_VAL_12H){
        u4_t_hhmmss  = u4_g_Hhmmss24hTo12h(u4_a_HHMMSS_24H);
        u1_t_timeset = (U1)DATESI_TIM_SET_12H;
    }
    u1_t_ampm    = (U1)((u4_t_hhmmss & (U4)HHMMSS_12H_BIT_AMPM) >> DATESI_TIM_12H_BIT_TO_AMPM);
    u4_t_hhmmss &= (~(U4)HHMMSS_12H_BIT_AMPM);

    u1_tp_time[HHMMSS_24H_TIME_SE] = (U1)((u4_t_hhmmss & (U4)HHMMSS_BIT_SE)                 );/* >> HHMMSS_LSB_SE(=0) */
    u1_tp_time[HHMMSS_24H_TIME_MI] = (U1)((u4_t_hhmmss & (U4)HHMMSS_BIT_MI) >> HHMMSS_LSB_MI);
    u1_tp_time[HHMMSS_24H_TIME_HR] = (U1)((u4_t_hhmmss & (U4)HHMMSS_BIT_HR) >> HHMMSS_LSB_HR);

    u1_t_pretx       = (U1)0U;
    u1_t_can_trig    = (U1)FALSE;
    u1_t_cxpi_trig   = (U1)FALSE;
    u1_t_ba_is_on    = u1_g_DateSI_Baon();
    u1_t_acc_is_on   = u1_g_DateSI_AccOn();
    u1_t_ig_is_on    = u1_g_DateSI_IgOn();
    u1_t_nmchk       = Nm_GetState((U1)DATESI_TIM_CAN_CH,  &u2_t_bus_sts, &u1_t_nmmod);

    if((u1_t_nmchk                  == (U1)DATESI_TIM_NM_RET_OK     ) &&
       (u2_s_datesi_tim_bus_sts_old != (U2)DATESI_TIM_NM_STS_RPT_MSG) &&
       (u2_t_bus_sts                == (U2)DATESI_TIM_NM_STS_RPT_MSG)){
        u1_s_datesi_tim_tmchg_tx_cnt = (U1)0U;
    }
    u2_s_datesi_tim_bus_sts_old = u2_t_bus_sts;

    (void)Com_ReceiveSignal(ComConf_ComSignal_CL_AMPM, &u1_t_pretx);
    if(u1_t_pretx != u1_t_ampm){
        vd_g_DateSIComClockDispUpdate(u1_t_ampm, DATESI_COM_CL_AMPM, u1_a_EVENT_EI);
        (void)Com_SendSignal(ComConf_ComSignal_CL_AMPM, &u1_t_ampm);
        u1_t_can_trig = (U1)TRUE;
    }
    (void)Com_ReceiveSignal(ComConf_ComSignal_TIME_SET, &u1_t_pretx);
    if(u1_t_pretx != u1_t_timeset){
        vd_g_DateSIComClockDispUpdate(u1_t_timeset, DATESI_COM_TIME_SET, u1_a_EVENT_EI);
        (void)Com_SendSignal(ComConf_ComSignal_TIME_SET, &u1_t_timeset);
        u1_t_can_trig = (U1)TRUE;
    }
    (void)Com_ReceiveSignal(ComConf_ComSignal_CL_MIN, &u1_t_pretx);
    if(u1_t_pretx != u1_tp_time[HHMMSS_24H_TIME_MI]){
        vd_g_DateSIComClockDispUpdate(u1_tp_time[HHMMSS_24H_TIME_MI], DATESI_COM_CL_MIN, u1_a_EVENT_EI);
        (void)Com_SendSignal(ComConf_ComSignal_CL_MIN, &u1_tp_time[HHMMSS_24H_TIME_MI]);
        u1_t_cxpi_trig = (U1)TRUE; /* Minute Update Event */
        u1_t_can_trig  = (U1)TRUE;
    }
    (void)Com_ReceiveSignal(ComConf_ComSignal_CL_HOUR, &u1_t_pretx);
    if(u1_t_pretx != u1_tp_time[HHMMSS_24H_TIME_HR]){
        vd_g_DateSIComClockDispUpdate(u1_tp_time[HHMMSS_24H_TIME_HR], DATESI_COM_CL_HOUR, u1_a_EVENT_EI);
        (void)Com_SendSignal(ComConf_ComSignal_CL_HOUR, &u1_tp_time[HHMMSS_24H_TIME_HR]);
        u1_t_cxpi_trig = (U1)TRUE; /* Hour Update Event */
        u1_t_can_trig  = (U1)TRUE;
    }
    (void)Com_ReceiveSignal(ComConf_ComSignal_CL_SEC, &u1_t_pretx);
    if(u1_t_pretx != u1_tp_time[HHMMSS_24H_TIME_SE]){
        vd_g_DateSIComClockDispUpdate(u1_tp_time[HHMMSS_24H_TIME_SE], DATESI_COM_CL_SEC, u1_a_EVENT_EI);
        (void)Com_SendSignal(ComConf_ComSignal_CL_SEC, &u1_tp_time[HHMMSS_24H_TIME_SE]);
        if(((u1_t_ba_is_on                == (U1)FALSE                )  &&
            (u1_t_acc_is_on               == (U1)FALSE                )  &&
            (u1_t_ig_is_on                == (U1)FALSE                )) &&
            (u1_s_datesi_tim_tmchg_tx_cnt >= (U1)DATESI_TIM_MIN_TX_NUM)){
            u1_t_can_trig = (U1)FALSE;
        }
        else{
            u1_t_can_trig = (U1)TRUE;
        }
    }
    if((u1_t_can_trig == (U1)TRUE) &&
       (u1_a_EVENT_EI == (U1)TRUE)){
        (void)Com_TriggerIPDUSend(MSG_MET1S33_TXCH0);
    }

    vd_s_DateSITimCfgCxpiTx(u1_t_cxpi_trig, &u1_tp_time[HHMMSS_24H_TIME_SE], u1_a_EVENT_EI);
}

/*===================================================================================================================================*/
/* static void     vd_s_DateSITimCfgCxpiTx(const U1 u1_a_CXPI_TRIG, const U1 * u1_ap_TIME, const U1 u1_a_EVENT_EI)                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_DateSITimCfgCxpiTx(const U1 u1_a_CXPI_TRIG, const U1 * u1_ap_TIME, const U1 u1_a_EVENT_EI)
{
#if 0
/* ifdef CXPICDD_H */
    U1  u1_t_ba_is_on;
    U1  u1_t_acc_is_on;
    U1  u1_t_ig_is_on;
    
    u1_t_ba_is_on    = u1_g_DateSI_Baon();
    u1_t_acc_is_on   = u1_g_DateSI_AccOn();
    u1_t_ig_is_on    = u1_g_DateSI_IgOn();
    
    if((u1_t_ba_is_on  == (U1)TRUE) ||
       (u1_t_acc_is_on == (U1)TRUE) ||
       (u1_t_ig_is_on  == (U1)TRUE)){
        if((u1_a_CXPI_TRIG   == (U1)TRUE) &&
           (u1_a_EVENT_EI    == (U1)TRUE)){
            CxpiCdd_TsWr0Cxmet1s01DT_HR(u1_ap_TIME[HHMMSS_24H_TIME_HR]);
            CxpiCdd_TsWr0Cxmet1s01DT_MIN(u1_ap_TIME[HHMMSS_24H_TIME_MI]);
            vd_g_oXCANCxptxTrgrTx((U1)CXPICDD_FRM_0_CH0_CXMET1S01_INDEX);
        }
    }
#endif /* #ifdef CXPICDD_H */
}

/*===================================================================================================================================*/
/* void            vd_g_DateSITimCfgCanTxOffst(const S4 s4_a_SEC, const U1 u1_a_EVENT_EI)                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSITimCfgCanTxOffst(const S4 s4_a_SEC, const U1 u1_a_EVENT_EI)
{
    S4  s4_t_sec;
    U4  u4_t_sec_abs;
    U1  u1_t_pretx;
    U1  u1_t_trig;
    U1  u1_t_sign;
    U1  u1_t_mi;
    U1  u1_t_hr;
    U1  u1_t_ba_is_on;
    U1  u1_t_acc_is_on;
    U1  u1_t_ig_is_on;

    if(s4_a_SEC < (S4)0){
        s4_t_sec     = s4_a_SEC * (S4)DATESI_TIM_SIGN_CHG;
        u4_t_sec_abs = (U4)s4_t_sec;
        u1_t_sign    = (U1)DATESI_TIM_OFFSET_SIGN_M;
    }
    else{
        u4_t_sec_abs = (U4)s4_a_SEC;
        u1_t_sign    = (U1)DATESI_TIM_OFFSET_SIGN_P;
    }
    u1_t_mi = (U1)((u4_t_sec_abs % (U4)HHMMSS_HR_TO_SE) / (U4)HHMMSS_MI_TO_SE);
    u1_t_hr = (U1)(u4_t_sec_abs  / (U4)HHMMSS_HR_TO_SE);

    u1_t_pretx = (U1)0U;
    u1_t_trig  = (U1)FALSE;
    (void)Com_ReceiveSignal(ComConf_ComSignal_OFST_M, &u1_t_pretx);
    if(u1_t_pretx != u1_t_mi){
        vd_g_DateSIComClockDispUpdate(u1_t_mi, DATESI_COM_OFST_M, u1_a_EVENT_EI);
        (void)Com_SendSignal(ComConf_ComSignal_OFST_M, &u1_t_mi);
        u1_t_trig = (U1)TRUE;
    }
    (void)Com_ReceiveSignal(ComConf_ComSignal_OFST_H, &u1_t_pretx);
    if(u1_t_pretx != u1_t_hr){
        vd_g_DateSIComClockDispUpdate(u1_t_hr, DATESI_COM_OFST_H, u1_a_EVENT_EI);
        (void)Com_SendSignal(ComConf_ComSignal_OFST_H, &u1_t_hr);
        u1_t_trig = (U1)TRUE;
    }
    (void)Com_ReceiveSignal(ComConf_ComSignal_OFSTSIGN, &u1_t_pretx);
    if(u1_t_pretx != u1_t_sign){
        vd_g_DateSIComClockDispUpdate(u1_t_sign, DATESI_COM_OFSTSIGN, u1_a_EVENT_EI);
        (void)Com_SendSignal(ComConf_ComSignal_OFSTSIGN, &u1_t_sign);
        u1_t_trig = (U1)TRUE;
    }
    
    u1_t_ba_is_on    = u1_g_DateSI_Baon();
    u1_t_acc_is_on   = u1_g_DateSI_AccOn();
    u1_t_ig_is_on    = u1_g_DateSI_IgOn();
    if((u1_t_ba_is_on  == (U1)TRUE) ||
       (u1_t_acc_is_on == (U1)TRUE) ||
       (u1_t_ig_is_on  == (U1)TRUE)){
        if((u1_t_trig     == (U1)TRUE) &&
           (u1_a_EVENT_EI == (U1)TRUE)){
            (void)Com_TriggerIPDUSend(MSG_MET1S33_TXCH0);
        }
   }
}

/*===================================================================================================================================*/
/* void            vd_g_DateSITimCfgCanTxHk(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSITimCfgCanTxHk(void)
{
    if(u1_s_datesi_tim_tmchg_tx_cnt < (U1)U1_MAX){
        u1_s_datesi_tim_tmchg_tx_cnt++;
    }
}

/*===================================================================================================================================*/
/* U1              u1_g_DateSITimCfgBusSlpOk(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments :  -                                                                                                                   */
/*  Return    :  U1 u1_t_slp_ok : BusSleepEnable(FALSE:Awake,TRUE:Sleep)                                                             */
/*===================================================================================================================================*/
U1              u1_g_DateSITimCfgBusSlpOk(void)
{
    U1  u1_t_slp_ok;
    U1  u1_t_nmchk;
    U1  u1_t_nmmod;
    U2  u2_t_bus_sts;

    u1_t_slp_ok = (U1)TRUE;

    u1_t_nmchk  = Nm_GetState((U1)DATESI_TIM_CAN_CH, &u2_t_bus_sts, &u1_t_nmmod);

    if((u1_s_datesi_tim_tmchg_tx_cnt < (U1)DATESI_TIM_MIN_TX_NUM    ) &&
      ((u1_t_nmchk                  == (U1)DATESI_TIM_NM_RET_OK     ) &&
      ((u2_t_bus_sts                == (U2)DATESI_TIM_NM_STS_RDY_SLP) ||
       (u2_t_bus_sts                == (U2)DATESI_TIM_NM_STS_NML_OPE) ||
       (u2_t_bus_sts                == (U2)DATESI_TIM_NM_STS_RPT_MSG)))){
        u1_t_slp_ok = (U1)FALSE;
    }

    return(u1_t_slp_ok);
}

/*===================================================================================================================================*/
/* void            u1_g_DateSITimCfgCanRxHk(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1              u1_g_DateSITimCfgCanRxHk(void)
{
    ST_DATESI_COMMAND_DATA  st_t_command_data;
    U1                      u1_t_swinf;

    u1_t_swinf = (U1)0U;

    /* SW Input Infomation */
    st_t_command_data = st_g_DateSIComRx();
    u1_t_swinf  = (U1)(st_t_command_data.u1_hour_usw << DATESI_TIM_SHIFT_HRUP);
    u1_t_swinf |= (U1)(st_t_command_data.u1_hour_dsw << DATESI_TIM_SHIFT_HRDW);
    u1_t_swinf |= (U1)(st_t_command_data.u1_min_usw << DATESI_TIM_SHIFT_MIUP);
    u1_t_swinf |= (U1)(st_t_command_data.u1_min_dsw << DATESI_TIM_SHIFT_MIDW);
    u1_t_swinf |= (U1)(st_t_command_data.u1_m_rst_sw << DATESI_TIM_SHIFT_SET);
    u1_t_swinf |= (U1)(st_t_command_data.u1_clkfmtsw << DATESI_TIM_SHIFT_12_24);
    u1_t_swinf |= (U1)(st_t_command_data.u1_oset_usw << DATESI_TIM_SHIFT_OFFSETUP);
    u1_t_swinf |= (U1)(st_t_command_data.u1_oset_dsw << DATESI_TIM_SHIFT_OFFSETDW);

    return(u1_t_swinf);
}

/*===================================================================================================================================*/
/* void            vd_g_DateSITimCfgExec24(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSITimCfgExec24(void)
{
    U4  u4_t_24h_fmt;    /* 24H Format           */
    U4  u4_t_24h_ind;    /* Indicator 24H Format */
    U1  u1_t_read_sts;

    u4_t_24h_ind  = (U4)0U;
    u1_t_read_sts = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_VM1TO2_TIMFMT, &u4_t_24h_ind, (U2)DATESI_TIME_VM_1WORD);
    if((u1_t_read_sts == (U1)IVDSH_NO_REA) || (u4_t_24h_ind >= (U4)DATESI_TIM_FMT_NUM_VAL)){
        u4_t_24h_ind = (U4)u1_s_datesi_tim_fmt;
    }

    if(u4_t_24h_ind == (U4)DATESI_TIM_FMT_VAL_24H){
        u4_t_24h_fmt = (U4)DATESI_TIM_FMT_VAL_12H;
    }
    else{
        u4_t_24h_fmt = (U4)DATESI_TIM_FMT_VAL_24H;
    }
    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO1_TIMFMT, &u4_t_24h_fmt, (U2)DATESI_TIME_VM_1WORD);
}

/*===================================================================================================================================*/
/* void            vd_g_DateSITimCfgOfstRoutine(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSITimCfgOfstRoutine(void)
{
    U4  u4_t_ofsttime;

    u4_t_ofsttime = (U4)0U;


    if(u2_s_datesi_tim_ofstcnt < (U2)U2_MAX) {
        u2_s_datesi_tim_ofstcnt++;
    }
    else{
        u2_s_datesi_tim_ofstcnt = (U2)U2_MAX;
    }
    if(u2_s_datesi_tim_ofstcnt > (U2)DATESI_TIM_OFST_CNT_END){
        if(u1_s_datesi_tim_ofststs == (U1)DATESI_TIM_OFST_STS_ADJ){
            u4_t_ofsttime = (U4)s4_s_datesi_tim_ofsttime;
            u4_t_ofsttime = (u4_t_ofsttime & (U4)U2_MAX);
            vd_g_Rim_WriteU2((U2)RIMID_U2_OFFSET_TIME, (U2)u4_t_ofsttime);
            vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO1_TIMOFST, &u4_t_ofsttime, (U2)DATESI_TIME_VM_1WORD);
            u1_s_datesi_tim_ofststs = (U1)DATESI_TIM_OFST_STS_NON;
        }
    }
}

/*===================================================================================================================================*/
/* void            vd_g_DateSITimCfgOfstAdjStart(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSITimCfgOfstAdjStart(void)
{
    if(u1_s_datesi_tim_ofststs != (U1)DATESI_TIM_OFST_STS_ADJ){
        u1_s_datesi_tim_ofststs = (U1)DATESI_TIM_OFST_STS_ADJ;
    }
}

/*===================================================================================================================================*/
/* S4              s4_g_DateSITimCfgGetOfstTime(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
S4              s4_g_DateSITimCfgGetOfstTime(void)
{
    S4  s4_t_offset_time;

    s4_t_offset_time = s4_s_datesi_tim_ofsttime;

    return(s4_t_offset_time);
}

/*===================================================================================================================================*/
/* void            vd_g_DateSITimCfgSetOfstTime(const S4 s4_a_OFST)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSITimCfgSetOfstTime(const S4 s4_a_OFST)
{
    if(u1_s_datesi_tim_ofststs == (U1)DATESI_TIM_OFST_STS_ADJ){
        s4_s_datesi_tim_ofsttime = s4_a_OFST;
        u2_s_datesi_tim_ofstcnt  = (U2)DATESI_TIM_OFST_CNT_INIT;
    }
}

/*===================================================================================================================================*/
/* void            vd_g_DateSITimCfgOfstReadHook(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSITimCfgOfstReadHook(void)
{
#if 0   /* B_PERMEM Not applicable */
    U2  u2_t_read;
    S2  s2_t_readtime;
    U4  u4_t_ofsttime;

    if(u1_s_DATESI_TIM_OFST_DEST == (U1)DATESI_TIM_OFST_MCST){
        u4_t_ofsttime = (U4)s4_s_datesi_tim_ofsttime;
        u4_t_ofsttime = (u4_t_ofsttime & (U4)U2_MAX);
        vd_g_McstBfPutPreUser((U1)MCST_BFI_OFFSET_TIME, u4_t_ofsttime);
        u2_t_read                = (U2)u4_g_McstBfU4((U1)MCST_BFI_OFFSET_TIME);
        s2_t_readtime            = (S2)u2_t_read;
        s4_s_datesi_tim_ofsttime = (S4)s2_t_readtime;
    }
#endif
}

/*===================================================================================================================================*/
/* void            vd_g_DateSITimCfgOfstDelHook(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void            vd_g_DateSITimCfgOfstDelHook(void)
{
#if 0   /* B_PERMEM Not applicable */
    U2  u2_t_read;
    S2  s2_t_readtime;

    if(u1_s_DATESI_TIM_OFST_DEST == (U1)DATESI_TIM_OFST_MCST){
        u2_t_read                = (U2)u4_g_McstBfU4((U1)MCST_BFI_OFFSET_TIME);
        s2_t_readtime            = (S2)u2_t_read;
        s4_s_datesi_tim_ofsttime = (S4)s2_t_readtime;
    }
#endif
}
/*===================================================================================================================================*/
/*  U1      u1_g_TimeZoneCfgRxTZ(U1 * u1p_a_rx)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TimeZoneCfgRxTZ(U1 * u1p_a_rx)
{
    ST_DATESI_COMMAND_DATA st_t_command_data;

    st_t_command_data = st_g_DateSIComRx();
    (*u1p_a_rx) = st_t_command_data.u1_tz;

    return((U1)DATESI_TIM_STSBIT_VALID);
}
/*===================================================================================================================================*/
/*  U1      u1_g_TimeZoneCfgRxTZ_SIGN(U1 * u1p_a_rx)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TimeZoneCfgRxTZ_SIGN(U1 * u1p_a_rx)
{
    ST_DATESI_COMMAND_DATA st_t_command_data;

    st_t_command_data = st_g_DateSIComRx();
    (*u1p_a_rx) = st_t_command_data.u1_tz_sign;

    return((U1)DATESI_TIM_STSBIT_VALID);
}
/*===================================================================================================================================*/
/*  U1      u1_g_TimeZoneCfgRxDST_S30(U1 * u1p_a_rx)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TimeZoneCfgRxDST_S30(U1 * u1p_a_rx)
{
    ST_DATESI_COMMAND_DATA st_t_command_data;

    st_t_command_data = st_g_DateSIComRx();
    (*u1p_a_rx) = st_t_command_data.u1_dst_s30;

    return((U1)DATESI_TIM_STSBIT_VALID);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  0.0.0    04/23/2025  MN       New.                                                                                               */
/*  0.0.1    12/18/2025  MN       Change for BEV Pre_CV                                                                              */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  BEV-1    12/18/2025  MN       Addressing issues.                                                                                 */
/*                                                                                                                                   */
/*  * MN   = Mikiya Negishi, KSE                                                                                                     */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
