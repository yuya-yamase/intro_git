/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Local Communication SPI / Diag Service Application Layer                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_DSAL_C_MAJOR                    (1)
#define XSPI_DSAL_C_MINOR                    (1)
#define XSPI_DSAL_C_PATCH                    (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "xspi_met_dsal.h"

#include "memfill_u1.h"
#include "memfill_u4.h"

#include "memcpy_u4.h"
#include "memcpy_u1.h"

#include "nvmc_mgr.h"
#if 0   /* BEV BSW provisionally */
#else
#include "nvmc_mgr_cfg_STUB.h"
#endif

#if 0   /* BEV BSW provisionally */
#include "es_inspect.h"
#endif
#include "veh_opemd.h"

#include "vehspd_kmph.h"
#include "hud_ca.h"
#include "vardef.h"
#if 0   /* BEV BSW provisionally */
#include "product.h"
#endif

#include "rim_ctl.h"
#if 0   /* BEV BSW provisionally */
#else
#include "rim_ctl_cfg_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((XSPI_DSAL_C_MAJOR != XSPI_DSAL_H_MAJOR) || \
     (XSPI_DSAL_C_MINOR != XSPI_DSAL_H_MINOR) || \
     (XSPI_DSAL_C_PATCH != XSPI_DSAL_H_PATCH))
#error "xspi_dsal.c and xspi_dsal.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_DTC_RX_TOC_INI                  (0xffU)
#define XSPI_DTC_RX_TOC_MAX                  (0xfeU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_SPN_RX_CHK                      (0x00000003U)
#define XSPI_SOCSPN_RX_CHK                   (0x0000000FU)

#define XSPI_SPN_RX_NWORD                    (20U)
#define XSPI_SPN_RX_NW_3                     (3U)

#define XSPI_SPN_RX_W0_LB3                   (0U)
#define XSPI_SPN_RX_W1_LB3                   (1U)
#define XSPI_SPN_RX_W2_LB3                   (2U)
#define XSPI_SPN_RX_W3_LB4                   (3U)
#define XSPI_SPN_RX_W4_LB4                   (4U)
#define XSPI_SPN_RX_W5_LB4                   (5U)
#define XSPI_SPN_RX_W6_LB5                   (6U)
#define XSPI_SPN_RX_W7_LB5                   (7U)
#define XSPI_SPN_RX_W8_LB5                   (8U)
#define XSPI_SPN_RX_W9_LB6                   (9U)
#define XSPI_SPN_RX_W10_LB6                  (10U)
#define XSPI_SPN_RX_W11_LB6                  (11U)
#define XSPI_SPN_RX_W12_HUD                  (12U)
#define XSPI_SPN_RX_W13_HUD                  (13U)
#define XSPI_SPN_RX_W14_HUD                  (14U)
#define XSPI_SPN_RX_W15_DISP                 (15U)
#define XSPI_SPN_RX_W16_DISP                 (16U)
#define XSPI_SPN_RX_W17_DISP                 (17U)
#define XSPI_SPN_RX_W18_VER                  (18U)
#define XSPI_SPN_RX_W19_VER                  (19U)

#define XSPI_SPN_RX_TOC_INI                  (0xffU)
#define XSPI_SPN_RX_TOC_MAX                  (0xfeU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* For ds22 10A7 */
#define XSPI_NUM_ODOSW                       (2U)
#define XSPI_ODO_SHORT                       (0U)
#define XSPI_ODO_LONG                        (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* For ds22 10A9 */
#define XSPI_NUM_STSW                        (46U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* For ds22 10A8 */
#define XSPI_CURSOR_POS                      (16U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_DSR_INA                         (0xffffffffU)

#define XSPI_DSR_TOC_INI                     (0xffffU)
#define XSPI_DSR_TOC_MAX                     (0xfffeU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/

#define XSPI_ROB_TX_NWORD                    (5U)
#define XSPI_ROB_TX_W0                       (0U)
#define XSPI_ROB_TX_W1                       (1U)
#define XSPI_ROB_TX_W2                       (2U)
#define XSPI_ROB_TX_W3                       (3U)
#define XSPI_ROB_TX_W4                       (4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_DS22_TX_W4                      (0U)
#define XSPI_DS22_TX_W5                      (1U)
#define XSPI_DS22_TX_W6                      (2U)
#define XSPI_DS22_TX_W7                      (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_NUM_HUD_RST                     (2U)
#define XSPI_HUD_CRT                         (0U)
#define XSPI_HUD_LAS                         (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_XPN_TX_UNDEF                    (0x3fU)
#define XSPI_XPN_TX_ESN_INI                  (0x3f3f3f3fU)
#define XSPI_XPN_TX_NWORD                    (5U)
#define XSPI_XPN_TX_ECU_N                    (10U)
#define XSPI_XPN_TX_SOFT_N                   (9U)
#define XSPI_XPN_TX_NW_SOFT                  (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U2          u2_tout;
    U2          u2_woff;
}ST_XSPI_DSR_CH;

typedef struct{
    U4          u4_reqtx;
    U2          u2_tocnt;
    U2          u2_rslt;
}ST_XSPI_DSR_TRX;

typedef struct{
    U1          u1_tocnt;
    U1          u1_rx;
}ST_XSPI_DTC_RX;

typedef struct{
    U2          u2_cnt;
    U1          u1_sts;
    U1          u1_edge;
}ST_XSPI_TESMD;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_XSPI_DSR_TRX         st_sp_xspi_dsr_trx[XSPI_DSR_NUM_CH];
static U4                      u4_s_xspi_dsr_unlock;

static ST_XSPI_TESMD           st_sp_xspi_tesmd_rx;
static U1                      u1_s_xspi_tesmd_dsp;

static U1                      u1_sp_xspi_odosw[XSPI_NUM_ODOSW];
static U1                      u1_sp_xspi_stsw_cnt[XSPI_NUM_STSW];

static U4                      u4_sp_xspi_rob_tx[XSPI_ROB_TX_NWORD];
static U4                      u4_s_xspi_eth_rwrslt;

static U4                      u4_s_xspi_hw_mal_rx;
static U2                      u2_s_xspi_hw_mal_ca;

static U4                      u4_s_xspi_hud_ds22;
static U1                      u1_s_xspi_hud_rst_cnt[XSPI_NUM_HUD_RST];

static ST_XSPI_DTC_RX          st_sp_xspi_dtc_rx[XSPI_DTC_NUM_RX];
static U2                      u2_s_xspi_thtemp_rx;

static U1                      u1_s_xspi_nvm_res_rx;

static U4                      u4_sp_xspi_spn_rx[XSPI_SPN_RX_NWORD];
static U1                      u1_s_xspi_spn_rx_tocnt;
static U1                      u1_s_xspi_spn_rx_chk;
static U1                      u1_s_xspi_cursor_chk;
static U2                      u2_s_xspi_cursor_cnt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_XSpiEthrRx(const U1 u1_a_NEXT);
static void    vd_s_XSpiDtcRxTOchk(void);

static void    vd_s_XSpiDsalRx_Dtc(const U4 * u4_ap_PDU_RX);
static void    vd_s_XSpiDsalRx_Mal(const U4 * u4_ap_PDU_RX);
static void    vd_s_XSpiDsalRx_Spn(const U4 * u4_ap_PDU_RX);

static void    vd_s_XSpiOdoswChk(const U4 * u4_ap_PDU_RX);
static void    vd_s_XSpiStswCntChk(const U4 * u4_ap_PDU_RX);
static void    vd_s_XSpiDsalRx_Cursor(const U4 * u4_ap_PDU_RX);

static void    vd_s_XSpiDsalTx_Tesmd(U4 * u4_ap_pdu_tx);
static void    vd_s_XSpiDsalTx_2E(U4 * u4_ap_pdu_tx);
static void    vd_s_XSpiDsalTx_Xpn(U4 * u4_ap_pdu_tx);
static void    vd_s_XSpiDsalTx_BA_DA(U4 * u4_ap_pdu_tx);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_XSpiDsalInit(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiDsalInit(void)
{
    U4                                u4_t_lpcnt;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)XSPI_DSR_NUM_CH; u4_t_lpcnt++){

        if(u4_t_lpcnt <= (U4)XSPI_DSR_BA_TFT){
            st_sp_xspi_dsr_trx[u4_t_lpcnt].u4_reqtx = (U4)0U;
        }
        else{
            st_sp_xspi_dsr_trx[u4_t_lpcnt].u4_reqtx = (U4)XSPI_DSR_INA;
        }

        st_sp_xspi_dsr_trx[u4_t_lpcnt].u2_tocnt = (U2)XSPI_DSR_TOC_MAX;
        st_sp_xspi_dsr_trx[u4_t_lpcnt].u2_rslt  = (U2)XSPI_DSR_TRX_UNK;
    }
    u4_s_xspi_dsr_unlock   = (U4)0U;

    st_sp_xspi_tesmd_rx.u1_edge  = (U1)FALSE;
    st_sp_xspi_tesmd_rx.u2_cnt   = (U1)0U;
    st_sp_xspi_tesmd_rx.u1_sts   = (U1)XSPI_TESMD_SW_INACT;
    
    u1_s_xspi_tesmd_dsp                                 = (U1)0U;

    u1_sp_xspi_odosw[XSPI_ODO_SHORT] = (U1)0U;
    u1_sp_xspi_odosw[XSPI_ODO_LONG]  = (U1)0U;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)XSPI_NUM_STSW; u4_t_lpcnt++){
        u1_sp_xspi_stsw_cnt[u4_t_lpcnt] = (U1)0U;
    }

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)XSPI_ROB_TX_NWORD; u4_t_lpcnt++){
        u4_sp_xspi_rob_tx[u4_t_lpcnt] = (U4)XSPI_DSR_INA;
    }

    u4_s_xspi_eth_rwrslt   = (U4)XSPI_DSR_INA;

    u4_s_xspi_hw_mal_rx    = (U4)XSPI_BA_SS_UNK;
    u2_s_xspi_hw_mal_ca    = (U2)0U;

    u2_s_xspi_thtemp_rx    = (U2)U2_MAX;
    u4_s_xspi_hud_ds22     = (U4)0U;
    u1_s_xspi_hud_rst_cnt[XSPI_HUD_CRT]  = (U1)0U;
    u1_s_xspi_hud_rst_cnt[XSPI_HUD_LAS]  = (U1)0U;

    st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1510].u1_tocnt = (U1)XSPI_DTC_RX_TOC_MAX;
    st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1510].u1_rx    = (U1)0U;
    st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1328].u1_tocnt = (U1)XSPI_DTC_RX_TOC_MAX;
    st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1328].u1_rx    = u1_s_XSpiEthrRx((U1)XSPI_DTC_RX_UNK);
    st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1511].u1_tocnt = (U1)XSPI_DTC_RX_TOC_MAX;
    st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1511].u1_rx    = (U1)0U;

    u1_s_xspi_nvm_res_rx   = (U1)XSPI_NVM_RES_UNK;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)XSPI_SPN_RX_NWORD; u4_t_lpcnt++){
        u4_sp_xspi_spn_rx[u4_t_lpcnt] = (U4)0U;
    }
    u1_s_xspi_spn_rx_tocnt = (U1)XSPI_SPN_RX_TOC_MAX;
    u1_s_xspi_spn_rx_chk   = (U1)0U;
    u1_s_xspi_cursor_chk   = (U1)0U;
    u2_s_xspi_cursor_cnt   = (U2)0U;
}
/*===================================================================================================================================*/
/*  void    vd_g_XSpiDsalMainTask(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiDsalMainTask(void)
{
    static const U1                   u1_s_XSPI_SPN_RX_TOUT = (U1)200U  / (U1)10U;

    vd_s_XSpiDtcRxTOchk();

    /* Spn */
    if(u1_s_xspi_spn_rx_tocnt >= (U1)XSPI_SPN_RX_TOC_INI){
        u1_s_xspi_spn_rx_tocnt = (U1)0U;
    }
    else if(u1_s_xspi_spn_rx_tocnt < (U1)XSPI_SPN_RX_TOC_MAX){
        u1_s_xspi_spn_rx_tocnt++;
    }
    else{
        /* Do nothing */
    }

    if(u1_s_xspi_spn_rx_tocnt >= u1_s_XSPI_SPN_RX_TOUT){
        u1_s_xspi_spn_rx_chk = (U1)0U;
    }

    /* Test Mode */
    if(st_sp_xspi_tesmd_rx.u1_sts == (U1)XSPI_TESMD_SW_ACT){
        if(st_sp_xspi_tesmd_rx.u2_cnt < (U2)U2_MAX){

            st_sp_xspi_tesmd_rx.u2_cnt++;
        }
    }
    else{
        st_sp_xspi_tesmd_rx.u2_cnt  = (U1)0U;
        st_sp_xspi_tesmd_rx.u1_edge = (U1)FALSE;
    }

}
/*===================================================================================================================================*/
/*  void    vd_g_XSpiDsalRx(const U4 * u4_ap_PDU_RX)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiDsalRx(const U4 * u4_ap_PDU_RX)
{
    static const U2                   u2_s_XSPI_DSA_TOC_NRX = (U2)200U / (U2)10U;

    U4                                u4_t_pdu_rx;

    U2                                u2_t_tocnt;
    U2                                u2_t_trx;
    U4                                u4_t_gvif;

    u2_s_xspi_thtemp_rx = (U2)u4_ap_PDU_RX[347];

    /* Ether Register */
    u4_t_pdu_rx = u4_ap_PDU_RX[344];
    u2_t_tocnt  = st_sp_xspi_dsr_trx[XSPI_DSR_BA_ETH].u2_tocnt;
    u2_t_trx    = st_sp_xspi_dsr_trx[XSPI_DSR_BA_ETH].u2_rslt;
    if((u4_t_pdu_rx <  (U4)XSPI_DSR_INA     ) &&
       (u2_t_tocnt  <= (U2)XSPI_DSR_TOC_MAX ) &&
       (u2_t_tocnt  >= u2_s_XSPI_DSA_TOC_NRX) &&
       (u2_t_trx    == (U2)XSPI_DSR_TRX_RUN )){

        st_sp_xspi_dsr_trx[XSPI_DSR_BA_ETH].u4_reqtx = (U4)XSPI_DSR_INA;
        st_sp_xspi_dsr_trx[XSPI_DSR_BA_ETH].u2_tocnt = (U2)XSPI_DSR_TOC_MAX;
        st_sp_xspi_dsr_trx[XSPI_DSR_BA_ETH].u2_rslt  = (U2)XSPI_DSR_TRX_SUC;

        u4_s_xspi_eth_rwrslt                             = u4_t_pdu_rx;
    }

    /* R-Car EEPROM Erase */
    u4_t_pdu_rx = (u4_ap_PDU_RX[346] & (U4)U1_MAX);
    u2_t_tocnt  = st_sp_xspi_dsr_trx[XSPI_DSR_BA_NVM].u2_tocnt;
    u2_t_trx    = st_sp_xspi_dsr_trx[XSPI_DSR_BA_NVM].u2_rslt;
    if((u4_t_pdu_rx != (U4)XSPI_NVM_RES_RUN ) &&
       (u2_t_tocnt  <= (U2)XSPI_DSR_TOC_MAX ) &&
       (u2_t_tocnt  >= u2_s_XSPI_DSA_TOC_NRX) &&
       (u2_t_trx    == (U2)XSPI_DSR_TRX_RUN )){

        st_sp_xspi_dsr_trx[XSPI_DSR_BA_NVM].u4_reqtx = (U4)XSPI_DSR_INA;
        st_sp_xspi_dsr_trx[XSPI_DSR_BA_NVM].u2_tocnt = (U2)XSPI_DSR_TOC_MAX;
        st_sp_xspi_dsr_trx[XSPI_DSR_BA_NVM].u2_rslt  = (U2)XSPI_DSR_TRX_SUC;

        u1_s_xspi_nvm_res_rx                             = (U1)u4_t_pdu_rx & (U1)XSPI_DSR_TRX_UNK;
    }

    u4_t_gvif = (U4)(u4_ap_PDU_RX[102] >> 24) & (U4)U1_MAX;
    if(u4_t_gvif == (U4)0U){
        u4_s_xspi_hud_ds22                      = u4_ap_PDU_RX[119];
        u1_s_xspi_hud_rst_cnt[XSPI_HUD_CRT] = (U1)u4_ap_PDU_RX[120] & (U1)U1_MAX;
    }
    else{
        u4_s_xspi_hud_ds22 = (U4)0xffffU; /* VIPOS_DEG & VOLT_BA is undef (0xff) */ 
    }

    vd_s_XSpiDsalRx_Dtc(u4_ap_PDU_RX);

    vd_s_XSpiDsalRx_Mal(u4_ap_PDU_RX);
    vd_s_XSpiDsalRx_Spn(u4_ap_PDU_RX);

    vd_s_XSpiOdoswChk(u4_ap_PDU_RX);
    vd_s_XSpiStswCntChk(u4_ap_PDU_RX);
    vd_s_XSpiDsalRx_Cursor(u4_ap_PDU_RX);
}
/*===================================================================================================================================*/
/*  void    vd_g_XSpiDsalTx(U4 * u4_ap_pdu_tx)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiDsalTx(U4 * u4_ap_pdu_tx)
{
    static const ST_XSPI_DSR_CH   st_sp_XSPI_DSR_CH[XSPI_DSR_NUM_CH] = {
        /* XSPI_DSR_2F_MID (0U) */
        {
            (U2)5000U  / (U2)10U,            /* u2_tout */
            (U2)452U                         /* u2_woff */
        },
        /* XSPI_DSR_2F_HUD (1U) */
        {
            (U2)5000U  / (U2)10U,            /* u2_tout */
            (U2)453U                         /* u2_woff */
        },
        /* XSPI_DSR_BA_TFT (2U) */
        {
            (U2)5000U  / (U2)10U,            /* u2_tout */
            (U2)420U                         /* u2_woff */
        },
        /* XSPI_DSR_31_ROB (3U) */
        {
            (U2)200U  / (U2)10U,             /* u2_tout */
            (U2)463U                         /* u2_woff */
        },
        /* XSPI_DSR_31_ESO (4U) */
        {
            (U2)200U  / (U2)10U,             /* u2_tout */
            (U2)464U                         /* u2_woff */
        },

        /* XSPI_DSR_BA_LED (5U) */
        {
            (U2)5000U  / (U2)10U,            /* u2_tout */
            (U2)421U                         /* u2_woff */
        },
        /* XSPI_DSR_BA_ETH (6U) */
        {
            (U2)5000U  / (U2)10U,            /* u2_tout */
            (U2)423U                         /* u2_woff */
        },
        /* XSPI_DSR_BA_NVM (7U) */
        {
            (U2)5000U  / (U2)10U,            /* u2_tout */
            (U2)425U                         /* u2_woff */
        },
        /* XSPI_DSR_14_DTC (8U) */
        {
            (U2)1000U  / (U2)10U,            /* u2_tout */
            (U2)426U                         /* u2_woff */
        },
        /* XSPI_DSR_85_MSK (9U) */
        {
            (U2)1000U  / (U2)10U,            /* u2_tout */
            (U2)473U                         /* u2_woff */
        },
        /* XSPI_DSR_BA_STB (10U) */
        {
            (U2)5000U  / (U2)10U,            /* u2_tout */
            (U2)424U                         /* u2_woff */
        }
    };

    U4 *                              u4_tp_rob_tx;

    U4                                u4_t_lpcnt;
    U4                                u4_t_tocnt;
    U2                                u2_t_woff;

    u4_s_xspi_dsr_unlock = (U4)0U;
    
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)XSPI_DSR_NUM_CH; u4_t_lpcnt++){

        u4_t_tocnt = (U4)st_sp_xspi_dsr_trx[u4_t_lpcnt].u2_tocnt;
        if(u4_t_tocnt >= (U4)XSPI_DSR_TOC_INI){
            u4_t_tocnt = (U4)0U;
        }
        else if(u4_t_tocnt < (U4)XSPI_DSR_TOC_MAX){
            u4_t_tocnt++;
        }
        else{
            /* Do nothing */
        }
        st_sp_xspi_dsr_trx[u4_t_lpcnt].u2_tocnt = (U2)u4_t_tocnt;


        if(u4_t_tocnt >= (U4)st_sp_XSPI_DSR_CH[u4_t_lpcnt].u2_tout){

            if(st_sp_xspi_dsr_trx[u4_t_lpcnt].u2_rslt == (U2)XSPI_DSR_TRX_RUN){
                st_sp_xspi_dsr_trx[u4_t_lpcnt].u2_rslt = (U2)XSPI_DSR_TRX_FAI;
            }
            if(u4_t_lpcnt <= (U4)XSPI_DSR_BA_TFT){
                st_sp_xspi_dsr_trx[u4_t_lpcnt].u4_reqtx = (U4)0U;
            }
            else{
                st_sp_xspi_dsr_trx[u4_t_lpcnt].u4_reqtx = (U4)XSPI_DSR_INA;
            }

        }

        u2_t_woff  = st_sp_XSPI_DSR_CH[u4_t_lpcnt].u2_woff;
        u4_ap_pdu_tx[u2_t_woff] = st_sp_xspi_dsr_trx[u4_t_lpcnt].u4_reqtx;
    }

    /* Ether Log Tx */
    u4_ap_pdu_tx[429] = (U4)u1_s_XSpiEthrRx((U1)XSPI_DTC_RX_UNK) & (U4)XSPI_DTC_RX_ENA;

    /* Rob Stamp Tx */
    u4_tp_rob_tx = &u4_ap_pdu_tx[431];
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)XSPI_ROB_TX_NWORD; u4_t_lpcnt++){
        u4_tp_rob_tx[u4_t_lpcnt] = u4_sp_xspi_rob_tx[u4_t_lpcnt];
    }

    /* ECU Shipping Inspectoin Mode */
    #if 0   /* BEV BSW provisionally */
    u4_ap_pdu_tx[419] = u1_g_ESInspectMdchk();
    #endif

    vd_s_XSpiDsalTx_Tesmd(u4_ap_pdu_tx);  /* OEM Shipping Inspection  */
    vd_s_XSpiDsalTx_2E(u4_ap_pdu_tx);     /* TyDoCAN Customize        */

    vd_s_XSpiDsalTx_Xpn(u4_ap_pdu_tx);    /* Product Number           */

    vd_s_XSpiDsalTx_BA_DA(u4_ap_pdu_tx);  /* Display Adjustment       */
}
/*===================================================================================================================================*/
/*  U1      u1_g_XSpiDtcRx(const U1 u1_a_DTC_RX)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_XSpiDtcRx(const U1 u1_a_DTC_RX)
{
    U1                                u1_t_rx;

    if(u1_a_DTC_RX < (U1)XSPI_DTC_NUM_RX){
        u1_t_rx = st_sp_xspi_dtc_rx[u1_a_DTC_RX].u1_rx;
    }
    else{
        u1_t_rx = (U1)0U;
    }

    return(u1_t_rx);
}
/*===================================================================================================================================*/
/*  void    vd_g_XSpiDsrUnlock(const U4 u4_a_KEY)                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiDsrUnlock(const U4 u4_a_KEY)
{
    u4_s_xspi_dsr_unlock = u4_a_KEY;
}
/*===================================================================================================================================*/
/*  void      vd_g_XSpiDsrTesmdOw(const U1 u1_a_DATA)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void      vd_g_XSpiDsrTesmdOw(const U1 u1_a_DATA)
{
    if(u4_s_xspi_dsr_unlock == (U4)XSPI_DSR_UNLOCK  ){

        st_sp_xspi_tesmd_rx.u1_sts = u1_a_DATA;
    }

    u4_s_xspi_dsr_unlock = (U4)0U;
}
/*===================================================================================================================================*/
/*  void    vd_g_XSpiDsrTx(const U1 u1_a_CH, const U4 u4_a_REQ_TX)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiDsrTx(const U1 u1_a_CH, const U4 u4_a_REQ_TX)
{
    if((u4_s_xspi_dsr_unlock == (U4)XSPI_DSR_UNLOCK) &&
       (u1_a_CH                  <  (U1)XSPI_DSR_NUM_CH)){

        st_sp_xspi_dsr_trx[u1_a_CH].u4_reqtx = u4_a_REQ_TX;
        st_sp_xspi_dsr_trx[u1_a_CH].u2_tocnt = (U2)XSPI_DSR_TOC_INI;
        st_sp_xspi_dsr_trx[u1_a_CH].u2_rslt  = (U2)XSPI_DSR_TRX_RUN;

        if((u1_a_CH     == (U1)XSPI_DSR_31_ESO ) &&
           (u4_a_REQ_TX == (U4)XSPI_ESO_RES_RUN)){

            st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1328].u1_rx = u1_s_XSpiEthrRx((U1)0U);
        }

        if((u1_a_CH     == (U1)XSPI_DSR_14_DTC ) &&
           (u4_a_REQ_TX == (U4)XSPI_DTC_CLR_FIN)){

            st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1510].u1_rx = (U1)0x00U;
            st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1328].u1_rx = u1_s_XSpiEthrRx((U1)XSPI_DTC_RX_UNK);
            st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1511].u1_rx = (U1)0x00U;
        }

        if((u1_a_CH     == (U1)XSPI_DSR_85_MSK ) &&
           (u4_a_REQ_TX == (U4)XSPI_DTC_MSK_FIN)){

            st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1510].u1_rx = (U1)0x00U;
            st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1328].u1_rx = u1_s_XSpiEthrRx((U1)XSPI_DTC_RX_UNK);
            st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1511].u1_rx = (U1)0x00U;
        }
    }
    u4_s_xspi_dsr_unlock = (U4)0U;
}
/*===================================================================================================================================*/
/*  U1      u1_g_XSpiDsBA_NvmResRslt(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_XSpiDsBA_NvmResRslt(void)
{
    U2                                u2_t_trx;
    U1                                u1_t_rslt;

    u2_t_trx = st_sp_xspi_dsr_trx[XSPI_DSR_BA_NVM].u2_rslt;
    if(u2_t_trx == (U2)XSPI_DSR_TRX_RUN){
        u1_t_rslt = (U1)XSPI_NVM_RES_RUN;
    }
    else if(u2_t_trx == (U2)XSPI_DSR_TRX_SUC){
        u1_t_rslt = u1_s_xspi_nvm_res_rx;
    }
    else if(u2_t_trx == (U2)XSPI_DSR_TRX_FAI){
        u1_t_rslt = (U1)XSPI_NVM_RES_FAI;
    }
    else{
        u1_t_rslt = (U1)XSPI_NVM_RES_UNK;
    }

    return(u1_t_rslt);
}
/*===================================================================================================================================*/
/*  U4      u4_g_XSpiDsBA_EthrRWRslt(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U4      u4_g_XSpiDsBA_EthrRWRslt(void)
{
    U4                                u4_t_rslt;
    U2                                u2_t_trx;

    u2_t_trx = st_sp_xspi_dsr_trx[XSPI_DSR_BA_ETH].u2_rslt;
    if((u2_t_trx == (U2)XSPI_DSR_TRX_RUN) ||
       (u2_t_trx >= (U2)XSPI_DSR_TRX_UNK)){
        u4_t_rslt = (U4)XSPI_ETHR_RW_UNK;
    }
    else if(u2_t_trx == (U2)XSPI_DSR_TRX_SUC){
        u4_t_rslt = u4_s_xspi_eth_rwrslt;
    }
    else{
        u4_t_rslt = (U4)XSPI_ETHR_RW_RSL_FA;
    }

    return(u4_t_rslt);
}
/*===================================================================================================================================*/
/*  U2      u2_g_XSpiDsBA_ThermTemp(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2      u2_g_XSpiDsBA_ThermTemp(void)
{
    return(u2_s_xspi_thtemp_rx);
}
/*===================================================================================================================================*/
/*  void    vd_g_XSpiRobStampTx(const U1 * u1_ap_TX, const U2 u2_a_NBYTE)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiRobStampTx(const U1 * u1_ap_TX, const U2 u2_a_NBYTE)
{
    U1 *                              u1_tp_rob_tx;
    U4                                u4_t_lpcnt;

    if((u1_ap_TX   != vdp_PTR_NA               ) &&
       (u2_a_NBYTE >= (U2)XSPI_ROB_TX_NBYTE)){

        u1_tp_rob_tx = (U1 *)&u4_sp_xspi_rob_tx[0];
        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)XSPI_ROB_TX_NBYTE; u4_t_lpcnt++){
            u1_tp_rob_tx[u4_t_lpcnt] = u1_ap_TX[u4_t_lpcnt];
        }
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_XSpiSpnRx(const U1 u1_a_SPN, U1 * u1_ap_spn_rx, const U1 u1_a_NBYTE)                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_XSpiSpnRx(const U1 u1_a_SPN, U1 * u1_ap_spn_rx, const U1 u1_a_NBYTE)
{
    static const U1                   u1_sp_XSPI_SPN_RX_NB_MIN[] = {
        (U1)XSPI_SPN_NB_LB3,
        (U1)XSPI_SPN_NB_LB4,
        (U1)XSPI_SPN_NB_LB5,
        (U1)XSPI_SPN_NB_LB6,
        (U1)XSPI_SPN_NB_HUD,
        (U1)XSPI_SPN_NB_DISP,
        (U1)XSPI_SPN_NB_VER
    };

    U1                                u1_t_rx_chk;
    U1                                u1_t_nb_min;
    U1                                u1_t_woff;

    if((u1_a_SPN     >  (U1)XSPI_SPN_RX_VER) ||
       (u1_ap_spn_rx == vdp_PTR_NA             )){

        u1_t_rx_chk = (U1)FALSE;
    }
    else{

        u1_t_rx_chk = (u1_s_xspi_spn_rx_chk >> u1_a_SPN) & (U1)TRUE;

        u1_t_nb_min = u1_sp_XSPI_SPN_RX_NB_MIN[u1_a_SPN];
        if((u1_a_NBYTE  >= u1_t_nb_min) &&
           (u1_t_rx_chk == (U1)TRUE   )){

            u1_t_woff = u1_a_SPN * (U1)XSPI_SPN_RX_NW_3;
            vd_g_MemcpyU1(u1_ap_spn_rx, (U1 *)&u4_sp_xspi_spn_rx[u1_t_woff], (U4)u1_t_nb_min);
        }
    }

    return(u1_t_rx_chk);
}
/*===================================================================================================================================*/
/*  U1      u1_g_XSpiDsBAEvCapt(const U1 u1_a_ODO_UPDT, U4 * u4_ap_ss)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_XSpiDsBAEvCapt(const U1 u1_a_ODO_UPDT, U4 * u4_ap_ss)
{
    U4                                u4_t_mal_rx;
    U1                                u1_t_capt;

    u4_t_mal_rx             = u4_s_xspi_hw_mal_rx;
    u4_s_xspi_hw_mal_rx = (U4)XSPI_BA_SS_UNK;

    if((u1_a_ODO_UPDT == (U1)TRUE              ) &&
       (u4_t_mal_rx   != (U4)XSPI_BA_SS_UNK)){

        (*u4_ap_ss) = u4_t_mal_rx;
        u1_t_capt   = (U1)TRUE;
    }
    else{
        u1_t_capt   = (U1)FALSE;
    }

    return(u1_t_capt);
}
/*===================================================================================================================================*/
/*  U1      u1_g_XSpiDsHudEvCapt(const U1 u1_a_ODO_UPDT, U4 * u4_ap_ss)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_XSpiDsHudEvCapt(const U1 u1_a_ODO_UPDT, U4 * u4_ap_ss)
{
    U1                                u1_t_capt;

    U1                                u1_t_mrc_fact;

    u1_t_mrc_fact = (U1)(u4_s_xspi_hud_ds22 >> 16) & (U1)0xFFU;

    if((u1_t_mrc_fact                               != (U4)0U                                          ) &&
       (u1_s_xspi_hud_rst_cnt[XSPI_HUD_CRT] != u1_s_xspi_hud_rst_cnt[XSPI_HUD_LAS])){

        u4_ap_ss[0] = (U4)u1_t_mrc_fact;
        u1_t_capt   = (U1)TRUE;
    }
    else{
        u1_t_capt   = (U1)FALSE;
    }

    u1_s_xspi_hud_rst_cnt[XSPI_HUD_LAS] = u1_s_xspi_hud_rst_cnt[XSPI_HUD_CRT];


    return(u1_t_capt);
}
/*===================================================================================================================================*/
/*  void      vd_g_XSpiDsHudRead(const U1 u1_a_DS22_DID, U1 * u1_ap_ans)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void      vd_g_XSpiDsHudRead(const U1 u1_a_DS22_DID, U1 * u1_ap_ans)
{
    if(u1_a_DS22_DID == (U1)XSPI_DS22_1025){
        u1_ap_ans[XSPI_DS22_TX_W4] = (U1)(u4_s_xspi_hud_ds22 & (U4)0xFFU);
    }

    else if(u1_a_DS22_DID == (U1)XSPI_DS22_10AC){
        u1_ap_ans[XSPI_DS22_TX_W4] = (U1)((u4_s_xspi_hud_ds22 >> 8) & (U4)0xFFU);
    }
    else{
        /* Do Nothing */
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_XSpiEthrRx(const U1 u1_a_NEXT)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_XSpiEthrRx(const U1 u1_a_NEXT)
{
    U4                                u4_t_nvm_las;
    U1                                u1_t_nvm_chk;
    U1                                u1_t_ethr_rx;
    U1                                u1_t_esi_chk;

    u4_t_nvm_las = (U4)0U;
    u1_t_nvm_chk = u1_g_Nvmc_ReadU4withSts((U2)NVMCID_U4_RCAR_ETHR_RX, &u4_t_nvm_las);
    if((u1_t_nvm_chk >= (U1)NVMC_STATUS_KIND_NG ) ||
       (u1_t_nvm_chk == (U1)NVMC_STATUS_ERRCOMP ) ||
       (u1_t_nvm_chk == (U1)NVMC_STATUS_CACHE_NG)){

        u1_t_ethr_rx = (U1)0U;
    }
    else{
        u1_t_ethr_rx = (U1)u4_t_nvm_las & (U1)XSPI_DTC_RX_ENA;
    }

    if((u1_a_NEXT    <  (U1)XSPI_DTC_RX_UNK) &&
       (u1_t_ethr_rx != u1_a_NEXT              )){ 

        u1_t_ethr_rx = u1_a_NEXT;

#if 0   /* BEV BSW provisionally */
        u1_t_esi_chk = u1_g_ESInspectMdBfield();
#else
        u1_t_esi_chk = (U1)TRUE;
#endif
        if(u1_t_esi_chk == (U1)0U){
            vd_g_Nvmc_WriteU4((U2)NVMCID_U4_RCAR_ETHR_RX, (U4)u1_t_ethr_rx);
        }
    }

    return(u1_t_ethr_rx);
}
/*===================================================================================================================================*/
/*  static void    vd_s_XSpiDtcRxTOchk(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XSpiDtcRxTOchk(void)
{
    static const U1                   u1_s_XSPI_DTC_RX_TOUT = (U1)200U / (U1)10U;

    U4                                u4_t_lpcnt;
    U2                                u2_t_dsr_chk;
    U1                                u1_t_tout;
    U1                                u1_t_ethr_rx;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)XSPI_DTC_NUM_RX; u4_t_lpcnt++){

        if(st_sp_xspi_dtc_rx[u4_t_lpcnt].u1_tocnt >= (U1)XSPI_DTC_RX_TOC_INI){
            st_sp_xspi_dtc_rx[u4_t_lpcnt].u1_tocnt = (U1)0U;
        }
        else if(st_sp_xspi_dtc_rx[u4_t_lpcnt].u1_tocnt < (U1)XSPI_DTC_RX_TOC_MAX){
            st_sp_xspi_dtc_rx[u4_t_lpcnt].u1_tocnt++;
        }
        else{
            /* Do nothing */
        }

        if(st_sp_xspi_dtc_rx[u4_t_lpcnt].u1_tocnt >= u1_s_XSPI_DTC_RX_TOUT){
            st_sp_xspi_dtc_rx[u4_t_lpcnt].u1_rx &= (U1)XSPI_DTC_RX_ENA;
        }
    }

    u2_t_dsr_chk = st_sp_xspi_dsr_trx[XSPI_DSR_31_ESO].u2_rslt;
    u1_t_tout    = st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1328].u1_tocnt;
    if((u2_t_dsr_chk != (U2)XSPI_DSR_TRX_RUN) &&
       (u1_t_tout    == (U1)0U                  )){

        u1_t_ethr_rx = st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1328].u1_rx & (U1)XSPI_DTC_RX_ENA;
        if(u1_t_ethr_rx == (U1)0U){
            st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1328].u1_rx |= u1_s_XSpiEthrRx((U1)XSPI_DTC_RX_UNK);
        }
        else{
            (void)u1_s_XSpiEthrRx((U1)XSPI_DTC_RX_ENA);
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_XSpiDsalRx_Dtc(const U4 * u4_ap_PDU_RX)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XSpiDsalRx_Dtc(const U4 * u4_ap_PDU_RX)
{
    U1                                u1_t_dtc_rx;
    U2                                u2_t_eso_chk;
    U2                                u2_t_clr_chk;
    U2                                u2_t_msk_chk;

    u2_t_eso_chk = st_sp_xspi_dsr_trx[XSPI_DSR_31_ESO].u2_rslt;
    u2_t_clr_chk = st_sp_xspi_dsr_trx[XSPI_DSR_14_DTC].u2_rslt;
    u2_t_msk_chk = st_sp_xspi_dsr_trx[XSPI_DSR_85_MSK].u2_rslt;

    /* B1510 */
    u1_t_dtc_rx = (U1)(u4_ap_PDU_RX[368] & (U4)U1_MAX);
    if((u1_t_dtc_rx  <  (U1)XSPI_DTC_RX_UNK ) &&
       (u2_t_clr_chk != (U2)XSPI_DSR_TRX_RUN) &&
       (u2_t_msk_chk != (U2)XSPI_DSR_TRX_RUN)){
        st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1510].u1_tocnt  = (U1)XSPI_DTC_RX_TOC_INI;
        st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1510].u1_rx    &= (U1)XSPI_DTC_RX_ENA;
        st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1510].u1_rx    |= u1_t_dtc_rx;
    }

    /* B1328 */
    u1_t_dtc_rx  = (U1)(u4_ap_PDU_RX[369] & (U4)U1_MAX);
    if((u1_t_dtc_rx  <  (U1)XSPI_DTC_RX_UNK ) &&
       (u2_t_clr_chk != (U2)XSPI_DSR_TRX_RUN) &&
       (u2_t_msk_chk != (U2)XSPI_DSR_TRX_RUN) &&
       (u2_t_eso_chk != (U2)XSPI_DSR_TRX_RUN)){
        st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1328].u1_tocnt  = (U1)XSPI_DTC_RX_TOC_INI;
        st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1328].u1_rx    &= (U1)XSPI_DTC_RX_ENA;
        st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1328].u1_rx    |= u1_t_dtc_rx;
    }

    /* B1511 */
    u1_t_dtc_rx = (U1)(u4_ap_PDU_RX[370] & (U4)U1_MAX);
    if((u1_t_dtc_rx  <  (U1)XSPI_DTC_RX_UNK ) &&
       (u2_t_clr_chk != (U2)XSPI_DSR_TRX_RUN) &&
       (u2_t_msk_chk != (U2)XSPI_DSR_TRX_RUN)){
        st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1511].u1_tocnt  = (U1)XSPI_DTC_RX_TOC_INI;
        st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1511].u1_rx    &= (U1)XSPI_DTC_RX_ENA;
        st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1511].u1_rx    |= u1_t_dtc_rx;
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_XSpiDsalRx_Mal(const U4 * u4_ap_PDU_RX)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XSpiDsalRx_Mal(const U4 * u4_ap_PDU_RX)
{
    U2                                u2_t_mal_rx;
    U2                                u2_t_mal_ca;
    U2                                u2_t_kmph;

    U1                                u1_t_ign_on;
    U1                                u1_t_vs_chk;

    u1_t_ign_on = u1_g_VehopemdIgnOn();
    if(u1_t_ign_on == (U1)TRUE){

        u2_t_mal_rx = (U2)((U4)U4_MAX ^ u4_ap_PDU_RX[350]);
        u2_t_mal_ca = (u2_s_xspi_hw_mal_ca ^ u2_t_mal_rx) & u2_t_mal_rx;
        if(u2_t_mal_ca != (U2)0U){

            u2_t_kmph   = (U2)U2_MAX;
            u1_t_vs_chk = u1_g_VehspdKmphInst(&u2_t_kmph, (U1)FALSE);
            if(u1_t_vs_chk != (U1)VEHSPD_STSBIT_VALID){
                u2_t_kmph = (U2)U2_MAX;
            }

            u4_s_xspi_hw_mal_rx = ((U4)u2_t_kmph << XSPI_BA_SS_LSB_KMPH) | (U4)u2_t_mal_rx;
        }
        u2_s_xspi_hw_mal_ca |= u2_t_mal_ca;
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_XSpiDsalRx_Spn(const U4 * u4_ap_PDU_RX)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XSpiDsalRx_Spn(const U4 * u4_ap_PDU_RX)
{
    U4                                u4_t_ok;
    U1                                u1_t_rx_chk;

    u1_t_rx_chk = (U1)0U;

    /* LB3      */
    u4_t_ok = u4_ap_PDU_RX[423] & (U4)XSPI_SOCSPN_RX_CHK;
    if(u4_t_ok == (U4)0U){
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W0_LB3]  = u4_ap_PDU_RX[424];
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W1_LB3]  = u4_ap_PDU_RX[425];
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W2_LB3]  = u4_ap_PDU_RX[426];
        u1_t_rx_chk                                   |= (U1)((U1)0x01U << XSPI_SPN_RX_LB3);
    }
    /* LB4      */
    u4_t_ok = u4_ap_PDU_RX[427] & (U4)XSPI_SOCSPN_RX_CHK;
    if(u4_t_ok == (U4)0U){
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W3_LB4]  = u4_ap_PDU_RX[428];
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W4_LB4]  = u4_ap_PDU_RX[429];
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W5_LB4]  = u4_ap_PDU_RX[430];
        u1_t_rx_chk                                   |= (U1)((U1)0x01U << XSPI_SPN_RX_LB4);
    }
    /* LB5      */
    u4_t_ok = u4_ap_PDU_RX[431] & (U4)XSPI_SOCSPN_RX_CHK;
    if(u4_t_ok == (U4)0U){
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W6_LB5]  = u4_ap_PDU_RX[432];
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W7_LB5]  = u4_ap_PDU_RX[433];
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W8_LB5]  = u4_ap_PDU_RX[434];
        u1_t_rx_chk                                   |= (U1)((U1)0x01U << XSPI_SPN_RX_LB5);
    }
    /* LB6      */
    u4_t_ok = u4_ap_PDU_RX[435] & (U4)XSPI_SOCSPN_RX_CHK;
    if(u4_t_ok == (U4)0U){
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W9_LB6]   = u4_ap_PDU_RX[436];
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W10_LB6]  = u4_ap_PDU_RX[437];
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W11_LB6]  = u4_ap_PDU_RX[438];
        u1_t_rx_chk                                    |= (U1)((U1)0x01U << XSPI_SPN_RX_LB6);
    }
    /* HUD  */
    u4_t_ok = (U4)(u4_ap_PDU_RX[102] >> 24) & (U4)U1_MAX;
    if(u4_t_ok == (U4)0U){
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W12_HUD]  = u4_ap_PDU_RX[116];
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W13_HUD]  = u4_ap_PDU_RX[117];
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W14_HUD]  = u4_ap_PDU_RX[118];
        u1_t_rx_chk                                    |= (U1)((U1)0x01U << XSPI_SPN_RX_HUD);
    }
    /* EXT DISP  */
    u4_t_ok = (U4)(u4_ap_PDU_RX[124] >> 24) & (U4)XSPI_SPN_RX_CHK;
    if(u4_t_ok == (U4)0x01U){
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W15_DISP]  = u4_ap_PDU_RX[121];
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W16_DISP]  = u4_ap_PDU_RX[122];
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W17_DISP]  = u4_ap_PDU_RX[123];
        u1_t_rx_chk                                     |= (U1)((U1)0x01U << XSPI_SPN_RX_DISP);
    }
    /* Software Version */
    u4_t_ok = u4_ap_PDU_RX[509] & (U4)XSPI_SPN_RX_CHK;
    if(u4_t_ok == (U4)0U){
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W18_VER] = u4_ap_PDU_RX[507];
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W19_VER] = u4_ap_PDU_RX[508];
        u1_t_rx_chk                                   |= (U1)((U1)0x01U << XSPI_SPN_RX_VER);
    }

    u1_s_xspi_spn_rx_tocnt = (U1)XSPI_SPN_RX_TOC_INI;
    u1_s_xspi_spn_rx_chk   = u1_t_rx_chk;
}
/*===================================================================================================================================*/
/*  static void    vd_s_XSpiDsalRx_Cursor(const U4 * u4_ap_PDU_RX)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XSpiDsalRx_Cursor(const U4 * u4_ap_PDU_RX)
{
    U1      u1_t_buf;

    u1_t_buf = (U1)(u4_ap_PDU_RX[215] >> (U1)XSPI_CURSOR_POS);

    if(u1_s_xspi_cursor_chk != u1_t_buf){
        u1_s_xspi_cursor_chk = u1_t_buf;
        if(u2_s_xspi_cursor_cnt < (U2)U2_MAX){
            u2_s_xspi_cursor_cnt++;
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_XSpiOdoswChk(const U4 * u4_ap_PDU_RX)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XSpiOdoswChk(const U4 * u4_ap_PDU_RX)
{
    static const U2 u2_sp_XSPI_ODOSW_RIMID[XSPI_NUM_ODOSW] ={
        (U2)RIMID_U2_DS_22_10A7_MET_ODO_SHORT,
        (U2)RIMID_U2_DS_22_10A7_MET_ODO_LONG
    };

    U1      u1_tp_crnt[XSPI_NUM_ODOSW];
    U2      u2_t_rm;
    U4      u4_t_lpcnt;

    u1_tp_crnt[XSPI_ODO_SHORT] = (U1)(u4_ap_PDU_RX[200]  & (U4)0x03U);
    u1_tp_crnt[XSPI_ODO_LONG]  = (U1)((u4_ap_PDU_RX[200] & (U4)0x0CU) >> 2);
    u2_t_rm                        = (U2)0U;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)XSPI_NUM_ODOSW; u4_t_lpcnt++){

        if((u1_tp_crnt[u4_t_lpcnt]           == (U1)0x01U) &&
           (u1_sp_xspi_odosw[u4_t_lpcnt] == (U1)0x00U)){

            (void)u1_g_Rim_ReadU2withStatus(u2_sp_XSPI_ODOSW_RIMID[u4_t_lpcnt], &u2_t_rm);
            if(u2_t_rm < (U2)U2_MAX){
                u2_t_rm++;
                vd_g_Rim_WriteU2(u2_sp_XSPI_ODOSW_RIMID[u4_t_lpcnt], u2_t_rm);
            }
        }

        u1_sp_xspi_odosw[u4_t_lpcnt] = u1_tp_crnt[u4_t_lpcnt];
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_XSpiStswCntChk(const U4 * u4_ap_PDU_RX)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XSpiStswCntChk(const U4 * u4_ap_PDU_RX)
{
    static const U2 u2_sp_XSPI_STSW_RIMID[XSPI_NUM_STSW] = {
        (U2)RIMID_U2_DS_22_10A9_00,    (U2)RIMID_U2_DS_22_10A9_01,    (U2)RIMID_U2_DS_22_10A9_02,
        (U2)RIMID_U2_DS_22_10A9_03,    (U2)RIMID_U2_DS_22_10A9_04,    (U2)RIMID_U2_DS_22_10A9_05,
        (U2)RIMID_U2_DS_22_10A9_06,    (U2)RIMID_U2_DS_22_10A9_07,    (U2)RIMID_U2_DS_22_10A9_08,
        (U2)RIMID_U2_DS_22_10A9_09,    (U2)RIMID_U2_DS_22_10A9_10,    (U2)RIMID_U2_DS_22_10A9_11,
        (U2)RIMID_U2_DS_22_10A9_12,    (U2)RIMID_U2_DS_22_10A9_13,    (U2)RIMID_U2_DS_22_10A9_14,
        (U2)RIMID_U2_DS_22_10A9_15,    (U2)RIMID_U2_DS_22_10A9_16,    (U2)RIMID_U2_DS_22_10A9_17,
        (U2)RIMID_U2_DS_22_10A9_18,    (U2)RIMID_U2_DS_22_10A9_19,    (U2)RIMID_U2_DS_22_10A9_20,
        (U2)RIMID_U2_DS_22_10A9_21,    (U2)RIMID_U2_DS_22_10A9_22,    (U2)RIMID_U2_DS_22_10A9_23,
        (U2)RIMID_U2_DS_22_10A9_24,    (U2)RIMID_U2_DS_22_10A9_25,    (U2)RIMID_U2_DS_22_10A9_26,
        (U2)RIMID_U2_DS_22_10A9_27,    (U2)RIMID_U2_DS_22_10A9_28,    (U2)RIMID_U2_DS_22_10A9_29,
        (U2)RIMID_U2_DS_22_10A9_30,    (U2)RIMID_U2_DS_22_10A9_31,    (U2)RIMID_U2_DS_22_10A9_32,
        (U2)RIMID_U2_DS_22_10A9_33,    (U2)RIMID_U2_DS_22_10A9_34,    (U2)RIMID_U2_DS_22_10A9_35,
        (U2)RIMID_U2_DS_22_10A9_36,    (U2)RIMID_U2_DS_22_10A9_37,    (U2)RIMID_U2_DS_22_10A9_38,
        (U2)RIMID_U2_DS_22_10A9_39,    (U2)RIMID_U2_DS_22_10A9_40,    (U2)RIMID_U2_DS_22_10A9_41,
        (U2)RIMID_U2_DS_22_10A9_42,    (U2)RIMID_U2_DS_22_10A9_43,    (U2)RIMID_U2_DS_22_10A9_44,
        (U2)RIMID_U2_DS_22_10A9_45
    };
    U1         u1_t_sts;
    U1 const * u1_tp_buf;
    U4         u4_t_lpcnt;

    U2         u2_t_rm;

    u1_t_sts = (U1)(u4_ap_PDU_RX[203] & (U4)0x03U);
    u2_t_rm  = (U2)0U;

    if(u1_t_sts == (U1)0U){
        u1_tp_buf = (U1 const *)&u4_ap_PDU_RX[204];

        for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)XSPI_NUM_STSW; u4_t_lpcnt++){

            if(u1_sp_xspi_stsw_cnt[u4_t_lpcnt] != u1_tp_buf[u4_t_lpcnt]){
                (void)u1_g_Rim_ReadU2withStatus(u2_sp_XSPI_STSW_RIMID[u4_t_lpcnt], &u2_t_rm);

                if(u2_t_rm < (U2)U2_MAX){
                    u2_t_rm++;
                    vd_g_Rim_WriteU2(u2_sp_XSPI_STSW_RIMID[u4_t_lpcnt], u2_t_rm);
                }
            }

            u1_sp_xspi_stsw_cnt[u4_t_lpcnt] = u1_tp_buf[u4_t_lpcnt];
        }
    }
}
/*===================================================================================================================================*/
/*  U2    u2_g_XSpiCursorCntRead(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U2    u2_g_XSpiCursorCntRead(void)
{
    return(u2_s_xspi_cursor_cnt);
}
/*===================================================================================================================================*/
/*  static void    vd_s_XSpiDsalTx_Tesmd(U4 * u4_ap_pdu_tx)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XSpiDsalTx_Tesmd(U4 * u4_ap_pdu_tx)
{
    static const U2                   u2_s_XSPI_DSR_BACK_ON = (U2)1000U / (U2)10U;
    U2                                u2_t_tesmd;
    U1                                u1_t_rimsts;
    U1                                u1_t_ign_on;

    u2_t_tesmd            = (U1)0U;

    u1_t_rimsts = u1_g_Rim_ReadU2withStatus(RIMID_U2_TYDC_WRBYID_AA00 , &u2_t_tesmd) & (U1)RIM_RESULT_KIND_MASK;

    u4_ap_pdu_tx[440]     = (U4)(((U4)u2_t_tesmd & (U4)0xFFU) << 8);                /* #5 */

    if((u2_t_tesmd  == (U2)0U) || 
       (u1_t_rimsts != (U1)0U)) {
        u1_s_xspi_tesmd_dsp = (U1)0U;
    }
    else{
        u1_t_ign_on = u1_g_VehopemdIgnOn();
        if((  u1_t_ign_on                     == (U1)TRUE                   ) &&
           (((st_sp_xspi_tesmd_rx.u1_edge == (U1)FALSE                )   &&
             (st_sp_xspi_tesmd_rx.u2_cnt  >= u2_s_XSPI_DSR_BACK_ON)))) {

            st_sp_xspi_tesmd_rx.u1_edge = (U1)TRUE;

            u1_s_xspi_tesmd_dsp ^= (U1)0x01U;
        }
    }
    
    u4_ap_pdu_tx[439] = (U4)u1_s_xspi_tesmd_dsp;
}
/*===================================================================================================================================*/
/*  static void    vd_s_XSpiDsalTx_2E(U4 * u4_ap_pdu_tx)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XSpiDsalTx_2E(U4 * u4_ap_pdu_tx)
{
    U4                                u4_t_hud_ca;
    U4                                u4_t_stsw;

    u4_ap_pdu_tx[441]  = u4_g_VardefDs2E_Las32((U2)VDF_DS_2E_2002);                 /* DG_2E_2002_4_MET_IGOFF_ODO_TIME      */ 
    u4_ap_pdu_tx[442]  = u4_g_VardefDs2E_Las32((U2)VDF_DS_2E_2021);                 /* DG_2E_2021_5_B5_XM_CERTMODE          */ 
    u4_ap_pdu_tx[443]  = (U4)U4_MAX;                                                /* DG_2E_2081_5_B7_MET_ECOZONE          */ 
    u4_ap_pdu_tx[444]  = (U4)U4_MAX;                                                /* DG_2E_2201_4_HUD_CORR_ROTATE         */ 

    u4_t_hud_ca        = (U4)((U1)s1_g_HudCaLastByUser((U1)HUD_CA_PRM_TRA));
    u4_t_hud_ca       |= ((U4)u1_g_HudCaDsrRxcnt((U1)HUD_CA_PRM_TRA) << 24U);
    u4_ap_pdu_tx[445]  = u4_t_hud_ca;                                               /* DG_2E_2202_4_HUD_CORR_KEYSTN         */ 
    u4_t_hud_ca        = (U4)((U1)s1_g_HudCaLastByUser((U1)HUD_CA_PRM_DIS));
    u4_t_hud_ca       |= ((U4)u1_g_HudCaDsrRxcnt((U1)HUD_CA_PRM_DIS) << 24U);
    u4_ap_pdu_tx[446]  = u4_t_hud_ca;                                               /* DG_2E_2203_4_HUD_CORR_ARCH           */ 
    u4_ap_pdu_tx[447]  = u4_g_VardefDs2E_Las32((U2)VDF_DS_2E_2204);                 /* DG_2E_2204_5_B7_HUD_AUDIO_FB         */
                                                                                    /* DG_2E_2204_5_B6_HUD_MASTER_CO        */
                                                                                    /* DG_2E_2204_5_B5_HUD_NAVI_SPLIM       */ 
    u4_ap_pdu_tx[448]  = (U4)U4_MAX;                                                /* DG_2E_2205_5_B7_HUD_TBT_ANIM         */
                                                                                    /* DG_2E_2205_5_B6_HUD_TSRNAVI_ANIM     */ 
    u4_ap_pdu_tx[449]  = (U4)U4_MAX;                                                /* DG_2E_2207_4_HUD_CORR_ROTATE2        */ 
    u4_ap_pdu_tx[450]  = (U4)U4_MAX;                                                /* DG_2E_2208_5_B7_HUD_ECOZONE          */ 

    u4_t_stsw          = (U4)((u4_g_VardefDs2E_Las32((U2)VDF_DS_2E_2209) & (U4)VDF_DS_2E_TDSS_MSK) >> 8U); 
    u4_t_stsw         |= (U4)((u4_g_VardefDs2E_Las32((U2)VDF_DS_2E_2209) & (U4)VDF_DS_2E_TO_MSK  ) << 8U);
    u4_ap_pdu_tx[451]  = u4_t_stsw;                                                 /* DG_2E_2209_5_STSW_TIMEOUT            */ 
                                                                                    /* DG_2E_2209_4_STSW_TOUCH_SENSE        */
}
/*===================================================================================================================================*/
/*  static void    vd_s_XSpiDsalTx_Xpn(U4 * u4_ap_pdu_tx)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XSpiDsalTx_Xpn(U4 * u4_ap_pdu_tx)
{
#if 0   /* BEV BSW provisionally */
    U1 *                              u1_tp_xpn_tx;

    U1                                u1_tp_sn[PRDCT_SERI_N_NBYTE + PRDCT_ECU_PN_NBYTE];
    U1                                u1_t_ok;

    u1_t_ok = u1_g_Product((U1)PRDCT_PN_ECU_PN,
                           &u1_tp_sn[0],
                           (U1)PRDCT_ECU_PN_NBYTE);                                        /* ECU Product Number        */
    u1_t_ok &= u1_g_Product((U1)PRDCT_PN_SERI_N, 
                            &u1_tp_sn[PRDCT_ECU_PN_NBYTE], 
                            (U1)PRDCT_SERI_N_NBYTE);                                       /* Serial Number             */

    u1_tp_xpn_tx = (U1 *)&u4_ap_pdu_tx[458];
    if(u1_t_ok == (U1)TRUE){
        vd_g_MemcpyU1(&u1_tp_xpn_tx[3], &u1_tp_sn[0], (U4)XSPI_XPN_TX_ECU_N);
    }
    else{
        vd_g_MemfillU1(&u1_tp_xpn_tx[3], (U1)XSPI_XPN_TX_UNDEF, (U4)XSPI_XPN_TX_ECU_N);
    }

    u1_tp_xpn_tx = (U1 *)&u4_ap_pdu_tx[2];
    if(u1_t_ok == (U1)TRUE){
        vd_g_MemcpyU1(u1_tp_xpn_tx, &u1_tp_sn[0], (U4)PRDCT_SERI_N_NBYTE + (U4)PRDCT_ECU_PN_NBYTE);
    }
    else{
        vd_g_MemfillU1(u1_tp_xpn_tx, (U1)XSPI_XPN_TX_UNDEF, (U4)PRDCT_SERI_N_NBYTE + (U4)PRDCT_ECU_PN_NBYTE);
    }

    (void)u1_g_Product((U1)PRDCT_PN_REL_VN,
                       (U1 *)&u4_ap_pdu_tx[478],
                       (U1)PRDCT_REL_VN_NBYTE);                                            /* D1L1/MET Software Versoin */
#endif
}
/*===================================================================================================================================*/
/*  static void    vd_s_XSpiDsalTx_BA_DA(U4 * u4_ap_pdu_tx)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XSpiDsalTx_BA_DA(U4 * u4_ap_pdu_tx)
{
    U1      u1_t_dir;
    U1      u1_t_amo;

    U4      u4_t_adj_x;
    U4      u4_t_adj_y;

    U1      u1_t_nvmcsts;
    U2      u2_t_nvm_data;

    u2_t_nvm_data = (U2)0U;
    u1_t_nvmcsts   = u1_g_Nvmc_ReadU2withSts((U2)U2_MAX , &u2_t_nvm_data) & (U1)NVMC_STATUS_KIND_MASK;
    if (u1_t_nvmcsts != (U1)NVMC_STATUS_KIND_OK) {
        /* Do nothing */
    }

    u1_t_dir   = (U1)(u2_t_nvm_data >> 5) & (U1)0x07U;
    u1_t_amo   = (U1)(u2_t_nvm_data       & (U2)0x1fU);

    u4_t_adj_x = ((U4)u1_t_dir << 5) | (U4)u1_t_amo;

    u2_t_nvm_data = (U2)0U;
    u1_t_nvmcsts   = u1_g_Nvmc_ReadU2withSts((U2)U2_MAX , &u2_t_nvm_data) & (U1)NVMC_STATUS_KIND_MASK;
    if (u1_t_nvmcsts != (U1)NVMC_STATUS_KIND_OK) {
        /* Do nothing */
    }

    u1_t_dir   = (U1)(u2_t_nvm_data >> 5) & (U1)0x07U;
    u1_t_amo   = (U1)(u2_t_nvm_data       & (U2)0x1fU);

    u4_t_adj_y = ((U4)u1_t_dir << 5) | (U4)u1_t_amo;

    u4_ap_pdu_tx[438] = (U4)(u4_t_adj_x << 8) | u4_t_adj_y;
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     4/14/2020  TN       New.                                                                                               */
/*  1.1.0    10/06/2020  AS       Add several functions and processes for 800B.                                                      */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*  * AS   = Atsunori Sugita, DENSO-TECHNO                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
