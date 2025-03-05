/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for Toyota MET/HUD based on AUBIST/DEM, DCM                                                                     */
/*  NM Diag / ECU Sleep Diag  (Detection of excessive wakeup and sleep ng continuation)                                              */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_DTC_NMSLP_CFG_C_MAJOR           (1U)
#define TYDOCAN_DTC_NMSLP_CFG_C_MINOR           (0U)
#define TYDOCAN_DTC_NMSLP_CFG_C_PATCH           (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"

/* #include "oxcan.h"                oxcan.h is included in oxdocan_cfg_private.h                 */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Application Headers */
#include "tydocan_dtc_nmwk_cfg_private.h"
#include "tydocan_dtc_ecuslp_cfg_private.h"
#include "tydocan_dtc_nmgbl_cfg_private.h"
#include "veh_opemd.h"
#if 0   /* BEV BSW provisionally */
#else
#include "veh_opemd_xmode_STUB.h"
#endif
/*#include "ecu_m.h"*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (TYDOCAN_DTC_NMSLP_CFG_C_MAJOR != OXDOCAN_CFG_H_MAJOR)
#error "tydocan_dtc_nmslp_cfg.c and oxdocan_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#ifdef TYDOCAN_DTC_NMWK_CFG_H
#define TYDC_DTC_NMWK_NUM_LOG                   (10U)
#define TYDC_DTC_NMWK_LOG_NWORD                 ((TYDC_DTC_NMWK_NUM_LOG + 3U) >> 2U)
#define TYDC_NMWK_WKF_DTC_DTCT                  (0x01U)
#define TYDC_NMWK_WKF_TAI_EVTX                  (0x02U)
#define TYDC_NMWK_WKF_RHE_EVTX                  (0x04U)
#define TYDC_NMWK_WKF_CAN_EVTX                  (0x08U)
#define TYDC_NMWK_WKF_OTHER                     (0x10U)
#endif /* #ifdef TYDOCAN_DTC_NMWK_CFG_H */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#ifdef TYDOCAN_DTC_ECUSLP_CFG_H
#define TYDC_DTC_ECUSLP_NUM_LOG                 (10U)
#define TYDC_DTC_ECUSLP_LOG_NWORD               ((TYDC_DTC_ECUSLP_NUM_LOG + 3U) >> 2U)
#define TYDC_ECUSLP_WKF_LSTM_EDG                (0x00000001U)
#define TYDC_ECUSLP_WKF_CXPI_SLNG               (0x00000002U)
#define TYDC_ECUSLP_WKF_CAN_EDG                 (0x00000004U)
#define TYDC_ECUSLP_WKF_LST1_EDG                (0x00000008U)
#define TYDC_ECUSLP_WKF_CAN_SLNG                (0x00000010U)
#define TYDC_ECUSLP_WKF_FUE_SLNG                (0x00000020U)
#define TYDC_ECUSLP_WKF_NVM_SLNG                (0x00000040U)
#define TYDC_ECUSLP_WKF_CXPI_EVTX               (0x00000080U)
#define TYDC_ECUSLP_WKF_OTHR_NG                 (0x00000100U)
#define TYDC_ECUSLP_WKF_EPB_EDG                 (0x00000200U)
#endif /* #ifdef TYDOCAN_DTC_ECUSLP_CFG_H */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_TYDC_NMWK_WKF_TX_IDX(w)              (((U1)(w) >> 3U) << 1U)
#define u1_TYDC_NMWK_WKF_TX_BIT(w)              ((U1)0x80U >> ((U1)(w) & (U1)0x07U))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U4      u4_chk;
    U1      u1_idx;
    U1      u1_bit;
}ST_TYDC_NMWK_TX;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#ifdef TYDOCAN_DTC_NMWK_CFG_H
U4                  u4_gp_tydc_dtc_nmwk_log_wk[TYDC_DTC_NMWK_LOG_NWORD] __attribute__((section(".bss_BACK")));
#endif /* #ifdef TYDOCAN_DTC_NMWK_CFG_H */

#ifdef TYDOCAN_DTC_ECUSLP_CFG_H
U4                  u4_gp_tydc_dtc_ecuslp_log_wk[TYDC_DTC_ECUSLP_NUM_LOG] __attribute__((section(".bss_BACK")));
static U4           u4_s_tydc_ecuslp_wkf;
#endif /* #ifdef TYDOCAN_DTC_ECUSLP_CFG_H */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#ifdef TYDOCAN_DTC_NMWK_CFG_H  /* tydocan_dtc_nmwk_cfg_private.h */
const U1            u1_g_TYDC_NMWK_COM_CH          = (U1)OXCAN_CH_0_VCAN;                /* NM channel in OXCAN_RX       */

const U4            u4_g_TYDC_DTC_NMWK_WKM_TOUT    = (U4)3600000U;                      /* 60[min] -> [millisecond]     */
const U4            u4_g_TYDC_DTC_NMWK_SLM_TOUT    = (U4)3600000U;                      /* 60[min] -> [millisecond]     */

const U2            u2_g_TYDC_DTC_NMWK_INA_TOUT    = (U2)1000U / (U2)OXDC_MAIN_TICK;    /* 1[sec] -> [/10 milliseconds] */
const U2            u2_g_TYDC_DTC_NMWK_WKC_THRSH   = (U2)25U;                           /* 25[times]                    */

const U1            u1_g_TYDC_DTC_NMWK_NUM_LOG     = (U1)TYDC_DTC_NMWK_NUM_LOG;         /* G_WKP_SAVE_MAX_NUM */

const U1            u1_g_TYDC_DTC_NMWK_DCT_CH      = (U1)DATE_CLK_ETM_CH_DTC_NMWK;      /* Dateclk ETM Channel    */
#endif /* #ifdef TYDOCAN_DTC_NMWK_CFG_H */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#ifdef TYDOCAN_DTC_ECUSLP_CFG_H  /* tydocan_dtc_ecuslp_cfg_private.h */
const U4            u4_g_TYDC_DTC_ECUSLP_WKM_TOUT  = (U4)4200000U;                      /* 70[min] -> [millisecond]     */
const U4            u4_g_TYDC_DTC_ECUSLP_SLM_TOUT  = (U4)4200000U;                      /* 70[min] -> [millisecond]     */

const U2            u2_g_TYDC_DTC_ECUSLP_INA_TOUT  = (U2)1000U / (U2)OXDC_MAIN_TICK;    /* 1[sec] -> [/10 milliseconds] */
const U2            u2_g_TYDC_DTC_ECUSLP_WKC_THRSH = (U2)30U;                           /* 30[times]                    */

const U1            u1_g_TYDC_DTC_ECUSLP_NUM_LOG   = (U1)TYDC_DTC_ECUSLP_NUM_LOG;       /* E_WKP_SAVE_MAX_NUM */

const U1            u1_g_TYDC_DTC_ECUSLP_DCT_CH    = (U1)DATE_CLK_ETM_CH_DTC_NMGBL;     /* Dateclk ETM Channel  */
#endif /* #ifdef TYDOCAN_DTC_ECUSLP_CFG_H */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#ifdef TYDOCAN_DTC_NMGBL_CFG_H
const U1            u1_g_TYDC_DTC_NMGBL_COM_CH     = (U1)OXCAN_CH_0_VCAN;                /* NM channel in OXCAN_RX */
const U1            u1_g_TYDC_DTC_NMGBL_CANIF_CH   = (U1)BSW_CANIF_CH0;                 /* NM channel in CANIF    */
const U1            u1_g_TYDC_DTC_NMGBL_REC_CH_BIT = (U1)0x01U;                         /* NM channel bit written to snapshot record */
                                                                                        /*  ch1=bit0, ch2=bit1, ... ch8=bit7         */
const U4            u4_g_TYDC_DTC_NMGBL_WKM_TOUT   = (U4)3300000U;                      /* 55[min] -> [millisecond] */
const U2            u2_g_TYDC_DTC_NMGBL_WKC_THRSH  = (U2)27U;                           /* 27[times]                */
const U4            u4_g_TYDC_DTC_NMGBL_TERM_LMT   = (U4)240000U;                       /* 4[min] -> [millisecond]  */

const U4            u4_g_TYDC_DTC_NMGBL_SLM_TOUT   = (U4)3300000U;                      /* 55[min] -> [millisecond] */

const U1            u1_g_TYDC_DTC_NMGBL_DCT_CH     = (U1)DATE_CLK_ETM_CH_DTC_ECUSLP;    /* Dateclk ETM Channel  */

#endif /* #ifdef TYDOCAN_DTC_NMGBL_CFG_H */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#ifdef TYDOCAN_DTC_NMWK_CFG_H  /* tydocan_dtc_nmwk_cfg_private.h */
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANDtcNmwkCfgWkmAct(const U1 u1_a_RUN)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANDtcNmwkCfgWkmAct(const U1 u1_a_RUN)
{
    U4      u4_t_mdbit;
    U1      u1_t_act;
    U1      u1_t_scene;
    U1      u1_t_rx_stat;

    u4_t_mdbit = u4_g_VehopemdMdfield() & ((U4)VEH_OPEMD_MDBIT_ACC | (U4)VEH_OPEMD_MDBIT_IGN);
    u1_t_scene = (U1)0U;
    u1_t_rx_stat = Com_GetIPDUStatus((U2)MSG_PMN1G03_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    if(u1_t_rx_stat == (U1)0U){
        (void)Com_ReceiveSignal(ComConf_ComSignal_IGB_EIG, &u1_t_scene);
    }

    if((u4_t_mdbit != (U4)0U) || (u1_t_scene != (U1)0U)){
        u1_t_act = (U1)FALSE;
    }
    else{
        u1_t_act = (U1)TRUE;
    }
    /**************************************************************************/
    /* Note: +B/+BA Voltage condition if u1_a_RUN == FALSE is not implemented */
    /**************************************************************************/

    return(u1_t_act);
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANDtcNmwkCfgWkfchk(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANDtcNmwkCfgWkfchk(void)
{
    return((U1)0x00U);
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcNmwkCfgWkfTx(const U1 u1_a_WKF, U1 * u1_ap_tx)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcNmwkCfgWkfTx(const U1 u1_a_WKF, U1 * u1_ap_tx)
{
    static const ST_TYDC_NMWK_TX  st_sp_TYDC_NMWK_TX[] = {
        {(U4)TYDC_NMWK_WKF_DTC_DTCT, u1_TYDC_NMWK_WKF_TX_IDX(0x00U), u1_TYDC_NMWK_WKF_TX_BIT(0x00U)},
        {(U4)TYDC_NMWK_WKF_TAI_EVTX, u1_TYDC_NMWK_WKF_TX_IDX(0x01U), u1_TYDC_NMWK_WKF_TX_BIT(0x01U)},
        {(U4)TYDC_NMWK_WKF_RHE_EVTX, u1_TYDC_NMWK_WKF_TX_IDX(0x02U), u1_TYDC_NMWK_WKF_TX_BIT(0x02U)},
        {(U4)TYDC_NMWK_WKF_CAN_EVTX, u1_TYDC_NMWK_WKF_TX_IDX(0x03U), u1_TYDC_NMWK_WKF_TX_BIT(0x03U)},
        {(U4)TYDC_NMWK_WKF_OTHER,    u1_TYDC_NMWK_WKF_TX_IDX(0x04U), u1_TYDC_NMWK_WKF_TX_BIT(0x04U)}
    };
    static const U1               u1_s_TYDC_NMWK_NUM_TX = (U1)(sizeof(st_sp_TYDC_NMWK_TX) / sizeof(ST_TYDC_NMWK_TX));

    U4      u4_t_lpcnt;
    U4      u4_t_chk;
    U1      u1_t_idx;
    U1      u1_t_bit;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TYDC_DTC_NMWK_WKF_NBYTE; u4_t_lpcnt++){
        u1_ap_tx[u4_t_lpcnt] = (U1)0U;
    }

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_s_TYDC_NMWK_NUM_TX; u4_t_lpcnt++){

        u1_t_idx = st_sp_TYDC_NMWK_TX[u4_t_lpcnt].u1_idx;
        u1_t_bit = st_sp_TYDC_NMWK_TX[u4_t_lpcnt].u1_bit;

        if(u1_t_idx < ((U1)TYDC_DTC_NMWK_WKF_NBYTE - (U1)1U)){
            u1_ap_tx[u1_t_idx] |= u1_t_bit;  /* support bit */

            u4_t_chk = st_sp_TYDC_NMWK_TX[u4_t_lpcnt].u4_chk & (U4)u1_a_WKF;
            if(u4_t_chk != (U4)0U){
                u1_t_idx++;
                u1_ap_tx[u1_t_idx] |= u1_t_bit;
            }
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcNmwkRcvryEvhk(const U2 u2_a_ELPSD)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcNmwkRcvryEvhk(const U2 u2_a_ELPSD)
{
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif /* #ifdef TYDOCAN_DTC_NMWK_CFG_H */

/*-----------------------------------------------------------------------------------------------------------------------------------*/

#ifdef TYDOCAN_DTC_ECUSLP_CFG_H  /* tydocan_dtc_ecuslp_cfg_private.h */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void      vd_g_TyDoCANDtcEcuSlpCfgWake(const U1 u1_a_WAKE)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void      vd_g_TyDoCANDtcEcuSlpCfgWake(const U1 u1_a_WAKE)
{
    u4_s_tydc_ecuslp_wkf = (U4)0x00000000U;
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANDtcEcuSlpCfgWkmAct(const U1 u1_a_RUN)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANDtcEcuSlpCfgWkmAct(const U1 u1_a_RUN)
{
    U4      u4_t_mdbit;
    U1      u1_t_act;
    U1      u1_t_scene;
    U1      u1_t_rx_stat;

    u4_t_mdbit = u4_g_VehopemdMdfield() & ((U4)VEH_OPEMD_MDBIT_ACC | (U4)VEH_OPEMD_MDBIT_IGN);
    u1_t_scene = (U1)0U;
    u1_t_rx_stat = Com_GetIPDUStatus((U2)MSG_PMN1G03_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    if(u1_t_rx_stat == (U1)0U){
        (void)Com_ReceiveSignal(ComConf_ComSignal_IGB_EIG, &u1_t_scene);
    }

    if((u4_t_mdbit != (U4)0U) || (u1_t_scene != (U1)0U)){
        u1_t_act = (U1)FALSE;
    }
    else{
        u1_t_act = (U1)TRUE;
    }
    /**************************************************************************/
    /* Note: +B/+BA Voltage condition if u1_a_RUN == FALSE is not implemented */
    /**************************************************************************/

    return(u1_t_act);
}
/*===================================================================================================================================*/
/*  U4      u4_g_TyDoCANDtcEcuSlpCfgWkfChk(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_TyDoCANDtcEcuSlpCfgWkfChk(void)
{
    return(u4_s_tydc_ecuslp_wkf);
}
/*===================================================================================================================================*/
/*  U4      u4_g_TyDoCANDtcEcuSlpCfgSngfChk(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_TyDoCANDtcEcuSlpCfgSngfChk(void)
{
    return((U4)0x00000000U);
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcEcuSlpCfgWkfTx(const U1 u1_a_WKF, U1 * u1_ap_tx)                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcEcuSlpCfgWkfTx(const U4 u4_a_WKF, U1 * u1_ap_tx)
{
    static const ST_TYDC_NMWK_TX  st_sp_TYDC_ECUSLP_TX[] = {
        {(U4)TYDC_ECUSLP_WKF_LSTM_EDG,  u1_TYDC_NMWK_WKF_TX_IDX(0x01U), u1_TYDC_NMWK_WKF_TX_BIT(0x01U)},
        {(U4)TYDC_ECUSLP_WKF_CXPI_SLNG, u1_TYDC_NMWK_WKF_TX_IDX(0x02U), u1_TYDC_NMWK_WKF_TX_BIT(0x02U)},
        {(U4)TYDC_ECUSLP_WKF_CAN_EDG ,  u1_TYDC_NMWK_WKF_TX_IDX(0x04U), u1_TYDC_NMWK_WKF_TX_BIT(0x04U)},
        {(U4)TYDC_ECUSLP_WKF_LST1_EDG,  u1_TYDC_NMWK_WKF_TX_IDX(0x05U), u1_TYDC_NMWK_WKF_TX_BIT(0x05U)},
        {(U4)TYDC_ECUSLP_WKF_CAN_SLNG,  u1_TYDC_NMWK_WKF_TX_IDX(0x09U), u1_TYDC_NMWK_WKF_TX_BIT(0x09U)},
        {(U4)TYDC_ECUSLP_WKF_FUE_SLNG,  u1_TYDC_NMWK_WKF_TX_IDX(0x0AU), u1_TYDC_NMWK_WKF_TX_BIT(0x0AU)},
        {(U4)TYDC_ECUSLP_WKF_NVM_SLNG,  u1_TYDC_NMWK_WKF_TX_IDX(0x0CU), u1_TYDC_NMWK_WKF_TX_BIT(0x0CU)},
        {(U4)TYDC_ECUSLP_WKF_CXPI_EVTX, u1_TYDC_NMWK_WKF_TX_IDX(0x0DU), u1_TYDC_NMWK_WKF_TX_BIT(0x0DU)},
        {(U4)TYDC_ECUSLP_WKF_OTHR_NG ,  u1_TYDC_NMWK_WKF_TX_IDX(0x0EU), u1_TYDC_NMWK_WKF_TX_BIT(0x0EU)},
        {(U4)TYDC_ECUSLP_WKF_EPB_EDG ,  u1_TYDC_NMWK_WKF_TX_IDX(0x30U), u1_TYDC_NMWK_WKF_TX_BIT(0x30U)}
    };
    static const U1     u1_s_TYDC_ECUSLP_NUM_TX = (U1)(sizeof(st_sp_TYDC_ECUSLP_TX) / sizeof(ST_TYDC_NMWK_TX));

    U4                  u4_t_lpcnt;
    U4                  u4_t_chk;
    U1                  u1_t_idx;
    U1                  u1_t_bit;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)TYDC_DTC_ECUSLP_WKF_NBYTE; u4_t_lpcnt++){
        u1_ap_tx[u4_t_lpcnt] = (U1)0U;
    }

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)u1_s_TYDC_ECUSLP_NUM_TX; u4_t_lpcnt++){

        u1_t_idx = st_sp_TYDC_ECUSLP_TX[u4_t_lpcnt].u1_idx;
        u1_t_bit = st_sp_TYDC_ECUSLP_TX[u4_t_lpcnt].u1_bit;

        u1_ap_tx[u1_t_idx] |= u1_t_bit;  /* support bit */

        u4_t_chk = st_sp_TYDC_ECUSLP_TX[u4_t_lpcnt].u4_chk & u4_a_WKF;
        if(u4_t_chk != (U4)0U){
            u1_t_idx++;
            u1_ap_tx[u1_t_idx] |= u1_t_bit;
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_TyDoCANDtcEcuSlpRcvryEvhk(const U2 u2_a_ELPSD)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_TyDoCANDtcEcuSlpRcvryEvhk(const U2 u2_a_ELPSD)
{
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#endif /* #ifdef TYDOCAN_DTC_ECUSLP_CFG_H */

/*-----------------------------------------------------------------------------------------------------------------------------------*/

#ifdef TYDOCAN_DTC_NMGBL_CFG_H  /* tydocan_dtc_nmgbl_cfg_private.h */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANDtcNmGblCfgWkmAct(const U1 u1_a_RUN)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANDtcNmGblCfgWkmAct(const U1 u1_a_RUN)
{
    U4      u4_t_mdbit;
    U1      u1_t_act;
    U1      u1_t_scene;
    U1      u1_t_rx_stat;

    u4_t_mdbit = u4_g_VehopemdMdfield() & ((U4)VEH_OPEMD_MDBIT_ACC | (U4)VEH_OPEMD_MDBIT_IGN);
    u1_t_scene = (U1)0U;
    u1_t_rx_stat = Com_GetIPDUStatus((U2)MSG_PMN1G03_RXCH0) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    if(u1_t_rx_stat == (U1)0U){
        (void)Com_ReceiveSignal(ComConf_ComSignal_IGB_EIG, &u1_t_scene);
    }

    if((u4_t_mdbit != (U4)0U) || (u1_t_scene != (U1)0U)){
        u1_t_act = (U1)FALSE;
    }
    else{
        u1_t_act = (U1)TRUE;
    }
    /**************************************************************************/
    /* Note: +B/+BA Voltage condition if u1_a_RUN == FALSE is not implemented */
    /**************************************************************************/

    return(u1_t_act);
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANDtcNmGblCfgWkmReAct(void)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANDtcNmGblCfgWkmReAct(void)
{
    U4      u4_t_mdbit;
    U1      u1_t_react;

    u4_t_mdbit = u4_g_VehopemdMdfield() & ((U4)VEH_OPEMD_MDBIT_ACC | (U4)VEH_OPEMD_MDBIT_IGN);

    if(u4_t_mdbit != (U4)0U){
        u1_t_react = (U1)TRUE;
    }
    else{
        u1_t_react = (U1)FALSE;
    }

    return(u1_t_react);
}
/*===================================================================================================================================*/
/*  U1      u1_g_TyDoCANDtcNmGblCfgStopWkfRec(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_TyDoCANDtcNmGblCfgStopWkfRec(void)
{
    U4      u4_t_mdbit;
    U1      u1_t_stop;

    u4_t_mdbit = u4_g_VehopemdMdfield() & (U4)VEH_OPEMD_MDBIT_IGN;

    if(u4_t_mdbit != (U4)0U){
        u1_t_stop = (U1)TRUE;
    }
    else{
        u1_t_stop = (U1)FALSE;
    }

    return(u1_t_stop);
}
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#endif /* #ifdef TYDOCAN_DTC_NMGBL_CFG_H */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     1/17/2024  TI       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TI = Tomoko Inuzuka, DENSO                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
