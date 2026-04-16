/* 1.3.2 */
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
#define XSPI_DSAL_C_MINOR                    (3)
#define XSPI_DSAL_C_PATCH                    (2)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "xspi_met.h"
#include "xspi_met_dsal.h"

#include "memfill_u1.h"
#include "memcpy_u1.h"
#include "vardef.h"
#include "product.h"

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

#define XSPI_SPN_RX_NWORD                    (25U)
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
#define XSPI_SPN_RX_W18_HUD_SERI_N           (18U)
#define XSPI_SPN_RX_W19_HUD_SERI_N           (19U)
#define XSPI_SPN_RX_W20_HUD_SERI_N           (20U)
#define XSPI_SPN_RX_W21_HUD_SERI_N           (21U)
#define XSPI_SPN_RX_W22_HUD_SERI_N           (22U)
#define XSPI_SPN_RX_W23_VER                  (23U)
#define XSPI_SPN_RX_W24_VER                  (24U)

#define XSPI_SPN_RX_TOC_INI                  (0xffU)
#define XSPI_SPN_RX_TOC_MAX                  (0xfeU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* For ds22 1027 */
#define XSPI_DS22_RX_CHK                     (0x00000003U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_DSR_INA                         (0xffffffffU)

#define XSPI_DSR_TOC_INI                     (0xffffU)
#define XSPI_DSR_TOC_MAX                     (0xfffeU)

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
#define XSPI_NUM_DISP_RST                    (2U)
#define XSPI_EXT_DISP_CRT                    (0U)
#define XSPI_EXT_DISP_LAS                    (1U)

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

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_XSPI_DSR_TRX     st_sp_xspi_dsr_trx[XSPI_DSR_NUM_CH];
static U4                      u4_s_xspi_dsr_unlock;

static U4                      u4_s_xspi_hud_ds22;
static U4                      u4_s_xspi_dsp_ds22;
static U1                      u1_s_xspi_hud_rst_cnt[XSPI_NUM_HUD_RST];
static U1                      u1_s_xspi_dsp_rst_cnt[XSPI_NUM_DISP_RST];

static ST_XSPI_DTC_RX      st_sp_xspi_dtc_rx[XSPI_DTC_NUM_RX];

static U4                      u4_sp_xspi_spn_rx[XSPI_SPN_RX_NWORD];
static U1                      u1_s_xspi_spn_rx_tocnt;
static U1                      u1_s_xspi_spn_rx_chk;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_XSpiDsalDtcRxTOchk(void);
static void    vd_s_XSpiDsalDsrTxTOchk(void);
static void    vd_s_XSpiDsalSpnRxTOchk(void);

static void    vd_s_XSpiDsalRx_Dtc(const U4 * u4_ap_PDU_RX);
static void    vd_s_XSpiDsalRx_Spn(const U4 * u4_ap_PDU_RX);
static void    vd_s_XSpiDsalRx_Gvif(const U4 * u4_ap_PDU_RX);

static void    vd_s_XSpiDsalTx_2E(U4 * u4_ap_pdu_tx);
static void    vd_s_XSpiDsalTx_Dsr(U4 * u4_ap_pdu_tx);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_XSPI_DSR_CH   st_sp_XSPI_DSR_CH[XSPI_DSR_NUM_CH] = {
    /* XSPI_DSR_31_ESO (0U) */
    {
        (U2)200U   / (U2)DSAL_MAIN_TICK_CFG,    /* u2_tout */
        (U2)245U                                /* u2_woff */
    },
    /* XSPI_DSR_14_DTC (1U) */
    {
        (U2)1000U  / (U2)DSAL_MAIN_TICK_CFG,    /* u2_tout */
        (U2)239U                                /* u2_woff */
    }
};

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
        st_sp_xspi_dsr_trx[u4_t_lpcnt].u4_reqtx = (U4)XSPI_DSR_INA;
        st_sp_xspi_dsr_trx[u4_t_lpcnt].u2_tocnt = (U2)XSPI_DSR_TOC_MAX;
        st_sp_xspi_dsr_trx[u4_t_lpcnt].u2_rslt  = (U2)XSPI_DSR_TRX_UNK;
    }
    u4_s_xspi_dsr_unlock   = (U4)0U;

    u4_s_xspi_hud_ds22     = (U4)0U;
    u4_s_xspi_dsp_ds22     = (U4)0U;
    u1_s_xspi_hud_rst_cnt[XSPI_HUD_CRT]      = (U1)0U;
    u1_s_xspi_hud_rst_cnt[XSPI_HUD_LAS]      = (U1)0U;
    u1_s_xspi_dsp_rst_cnt[XSPI_EXT_DISP_CRT] = (U1)0U;
    u1_s_xspi_dsp_rst_cnt[XSPI_EXT_DISP_LAS] = (U1)0U;

    st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1510].u1_tocnt = (U1)XSPI_DTC_RX_TOC_MAX;
    st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1510].u1_rx    = (U1)XSPI_DTC_RX_INI;
    st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1511].u1_tocnt = (U1)XSPI_DTC_RX_TOC_MAX;
    st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1511].u1_rx    = (U1)XSPI_DTC_RX_INI;
    st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1518].u1_tocnt = (U1)XSPI_DTC_RX_TOC_MAX;
    st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1518].u1_rx    = (U1)XSPI_DTC_RX_INI;
    st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1519].u1_tocnt = (U1)XSPI_DTC_RX_TOC_MAX;
    st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1519].u1_rx    = (U1)XSPI_DTC_RX_INI;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)XSPI_SPN_RX_NWORD; u4_t_lpcnt++){
        u4_sp_xspi_spn_rx[u4_t_lpcnt] = (U4)0U;
    }
    u1_s_xspi_spn_rx_tocnt = (U1)XSPI_SPN_RX_TOC_MAX;
    u1_s_xspi_spn_rx_chk   = (U1)0U;

}
/*===================================================================================================================================*/
/*  void    vd_g_XSpiDsalMainTask(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiDsalMainTask(void)
{
    vd_s_XSpiDsalDtcRxTOchk();    /* DTC Rx time out check       */

    vd_s_XSpiDsalDsrTxTOchk();    /* DSR Tx time out check       */

    vd_s_XSpiDsalSpnRxTOchk();    /* SPN Rx time out check       */
}
/*===================================================================================================================================*/
/*  void    vd_g_XSpiDsalRx(const U4 * u4_ap_PDU_RX)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiDsalRx(const U4 * u4_ap_PDU_RX)
{
#if 0     /* BEV Diag provisionally */
    vd_s_XSpiDsalRx_Gvif(u4_ap_PDU_RX);    /* GVIF                    */

    vd_s_XSpiDsalRx_Dtc(u4_ap_PDU_RX);     /* Diag Trouble Code       */
#endif    /* BEV Diag provisionally */
    vd_s_XSpiDsalRx_Spn(u4_ap_PDU_RX);     /* Soft Product Number     */
}
/*===================================================================================================================================*/
/*  void    vd_g_XSpiDsalTx(U4 * u4_ap_pdu_tx)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiDsalTx(U4 * u4_ap_pdu_tx)
{
    vd_s_XSpiDsalTx_Dsr(u4_ap_pdu_tx);    /* Diag Service Request     */

#if 0     /* BEV Diag provisionally */
    vd_s_XSpiDsalTx_2E(u4_ap_pdu_tx);     /* TyDoCAN Customize        */
#endif    /* BEV Diag provisionally */
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


        if((u1_a_CH     == (U1)XSPI_DSR_14_DTC ) &&
           (u4_a_REQ_TX == (U4)XSPI_DTC_CLR_FIN)){

            st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1510].u1_rx = (U1)XSPI_DTC_RX_INI;
            st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1511].u1_rx = (U1)XSPI_DTC_RX_INI;

            st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1518].u1_rx = (U1)XSPI_DTC_RX_INI;
            st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1519].u1_rx = (U1)XSPI_DTC_RX_INI;
        }
    }
    u4_s_xspi_dsr_unlock = (U4)0U;
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
        (U1)XSPI_SPN_NB_HUD_SERI_N,
        (U1)XSPI_SPN_NB_VER
    };

    static const U1                   u1_sp_XSPI_SPN_RX_OFFSET[] = {
        (U1)XSPI_SPN_RX_W0_LB3,
        (U1)XSPI_SPN_RX_W3_LB4,
        (U1)XSPI_SPN_RX_W6_LB5,
        (U1)XSPI_SPN_RX_W9_LB6,
        (U1)XSPI_SPN_RX_W12_HUD,
        (U1)XSPI_SPN_RX_W15_DISP,
        (U1)XSPI_SPN_RX_W18_HUD_SERI_N,
        (U1)XSPI_SPN_RX_W23_VER
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

            u1_t_woff = u1_sp_XSPI_SPN_RX_OFFSET[u1_a_SPN];
            vd_g_MemcpyU1(u1_ap_spn_rx, (U1 *)&u4_sp_xspi_spn_rx[u1_t_woff], (U4)u1_t_nb_min);
        }
    }

    return(u1_t_rx_chk);
}
/*===================================================================================================================================*/
/*  U1      u1_g_XSpiDsHudEvCapt(const U1 u1_a_ODO_UPDT, U4 * u4_ap_ss)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if 0     /* BEV Diag provisionally */
U1      u1_g_XSpiDsHudEvCapt(const U1 u1_a_ODO_UPDT, U4 * u4_ap_ss)
{
    U1                                u1_t_capt;

    U1                                u1_t_mrc_fact;

    u1_t_mrc_fact = (U1)((u4_s_xspi_hud_ds22 >> 16) & (U4)U1_MAX);

    if((u1_t_mrc_fact                               != (U1)0U                                          ) &&
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
#endif    /* BEV Diag provisionally */
/*===================================================================================================================================*/
/*  U1      u1_g_XSpiDsDispEvCapt(const U1 u1_a_ODO_UPDT, U4 * u4_ap_ss)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if 0     /* BEV Diag provisionally */
U1      u1_g_XSpiDsDispEvCapt(const U1 u1_a_ODO_UPDT, U4 * u4_ap_ss)
{
    U1                                u1_t_capt;

    U1                                u1_t_mrc_fact;

    u1_t_mrc_fact = (U1)((u4_s_xspi_dsp_ds22 >> 16) & (U4)U1_MAX);

    if((u1_t_mrc_fact                                != (U1)0U                                      ) &&
       (u1_s_xspi_dsp_rst_cnt[XSPI_EXT_DISP_CRT] != u1_s_xspi_dsp_rst_cnt[XSPI_EXT_DISP_LAS])){

        u4_ap_ss[0] = (U4)u1_t_mrc_fact;
        u1_t_capt   = (U1)TRUE;
    }
    else{
        u1_t_capt   = (U1)FALSE;
    }

    u1_s_xspi_dsp_rst_cnt[XSPI_EXT_DISP_LAS] = u1_s_xspi_dsp_rst_cnt[XSPI_EXT_DISP_CRT];


    return(u1_t_capt);
}
#endif    /* BEV Diag provisionally */
/*===================================================================================================================================*/
/*  void      vd_g_XSpiDs22Read(const U1 u1_a_DS22_DID, U1 * u1_ap_ans)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void      vd_g_XSpiDs22Read(const U1 u1_a_DS22_DID, U1 * u1_ap_ans)
{
    if(u1_a_DS22_DID == (U1)XSPI_DS22_1025){
        u1_ap_ans[XSPI_DS22_TX_W4] = (U1)(u4_s_xspi_hud_ds22 & (U4)0xFFU);
    }

    else if(u1_a_DS22_DID == (U1)XSPI_DS22_10AC){
        u1_ap_ans[XSPI_DS22_TX_W4] = (U1)((u4_s_xspi_hud_ds22 >> 8) & (U4)0xFFU);
    }
    else if(u1_a_DS22_DID == (U1)XSPI_DS22_1027){
        u1_ap_ans[XSPI_DS22_TX_W4] = (U1)(u4_s_xspi_dsp_ds22 & (U4)0xFFU);
    }
    else{
        /* Do Nothing */
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_XSpiDsalDtcRxTOchk(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XSpiDsalDtcRxTOchk(void)
{
    static const U1                   u1_s_XSPI_DTC_RX_TOUT = (U1)200U / (U1)DSAL_MAIN_TICK_CFG;

    U4                                u4_t_lpcnt;

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

}
/*===================================================================================================================================*/
/*  static void    vd_s_XSpiDsalDsrTxTOchk(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XSpiDsalDsrTxTOchk(void)
{
    U4                                u4_t_lpcnt;
    U4                                u4_t_tocnt;

    
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
            
            st_sp_xspi_dsr_trx[u4_t_lpcnt].u4_reqtx = (U4)XSPI_DSR_INA;

        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_XSpiDsalSpnRxTOchk(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XSpiDsalSpnRxTOchk(void)
{
    static const U1                   u1_s_XSPI_SPN_RX_TOUT = (U1)200U  / (U1)DSAL_MAIN_TICK_CFG;

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
}
/*===================================================================================================================================*/
/*  static void    vd_s_XSpiDsalRx_Gvif(const U4 * u4_ap_PDU_RX)                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XSpiDsalRx_Gvif(const U4 * u4_ap_PDU_RX)
{
#if 0     /* BEV Diag provisionally */
    U4                                u4_t_gvif;

    u4_t_gvif = (U4)(u4_ap_PDU_RX[102] >> 24) & (U4)U1_MAX;
    if(u4_t_gvif == (U4)0U){
        u4_s_xspi_hud_ds22                      = u4_ap_PDU_RX[119];
        u1_s_xspi_hud_rst_cnt[XSPI_HUD_CRT] = (U1)u4_ap_PDU_RX[120] & (U1)U1_MAX;
    }
    else{
        u4_s_xspi_hud_ds22 = (U4)0xffffU; /* VIPOS_DEG & VOLT_BA is undef (0xff) */ 
    }

    u4_t_gvif = (U4)(u4_ap_PDU_RX[124] >> 24) & (U4)XSPI_DS22_RX_CHK;
    if(u4_t_gvif == (U4)0x01U){
        u4_s_xspi_dsp_ds22                           = u4_ap_PDU_RX[124];
        u1_s_xspi_dsp_rst_cnt[XSPI_EXT_DISP_CRT] = (U1)((u4_ap_PDU_RX[124] >> 8) & (U4)U1_MAX);
    }
    else{
        u4_s_xspi_dsp_ds22 = (U4)0xffU; /* DISP_VOLT_B is undef (0xff) */
    }
#endif    /* BEV Diag provisionally */
}
/*===================================================================================================================================*/
/*  static void    vd_s_XSpiDsalRx_Dtc(const U4 * u4_ap_PDU_RX)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XSpiDsalRx_Dtc(const U4 * u4_ap_PDU_RX)
{
#if 0    /* BEV Diag provisionally */
    U1                                u1_t_dtc_rx;
    U2                                u2_t_clr_chk;

    u2_t_clr_chk = st_sp_xspi_dsr_trx[XSPI_DSR_14_DTC].u2_rslt;

    /* B1510 */
    u1_t_dtc_rx = (U1)(u4_ap_PDU_RX[368] & (U4)U1_MAX);
    if((u1_t_dtc_rx  <  (U1)XSPI_DTC_RX_UNK_GVIF ) &&
       (u2_t_clr_chk != (U2)XSPI_DSR_TRX_RUN     )){
        st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1510].u1_tocnt  = (U1)XSPI_DTC_RX_TOC_INI;
        st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1510].u1_rx     = u1_t_dtc_rx;
    }

    /* B1511 */
    u1_t_dtc_rx = (U1)(u4_ap_PDU_RX[370] & (U4)U1_MAX);
    if((u1_t_dtc_rx  <  (U1)XSPI_DTC_RX_UNK_GVIF ) &&
       (u2_t_clr_chk != (U2)XSPI_DSR_TRX_RUN     )){
        st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1511].u1_tocnt  = (U1)XSPI_DTC_RX_TOC_INI;
        st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1511].u1_rx     = u1_t_dtc_rx;
    }
    /* B1518 */
    u1_t_dtc_rx = (U1)((u4_ap_PDU_RX[368] >> 8) & (U4)U1_MAX);
    if((u1_t_dtc_rx  <  (U1)XSPI_DTC_RX_UNK_GVIF ) &&
       (u2_t_clr_chk != (U2)XSPI_DSR_TRX_RUN     )){
        st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1518].u1_tocnt  = (U1)XSPI_DTC_RX_TOC_INI;
        st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1518].u1_rx     = u1_t_dtc_rx;
    }
    /* B1519 */
    u1_t_dtc_rx = (U1)((u4_ap_PDU_RX[370] >> 8)& (U4)U1_MAX);
    if((u1_t_dtc_rx  <  (U1)XSPI_DTC_RX_UNK_GVIF ) &&
       (u2_t_clr_chk != (U2)XSPI_DSR_TRX_RUN     )){
        st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1519].u1_tocnt  = (U1)XSPI_DTC_RX_TOC_INI;
        st_sp_xspi_dtc_rx[XSPI_DTC_RX_B1519].u1_rx     = u1_t_dtc_rx;
    }
#endif    /* BEV Diag provisionally */
}
/*===================================================================================================================================*/
/*  static void    vd_s_XSpiDsalRx_Spn(const U4 * u4_ap_PDU_RX)                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XSpiDsalRx_Spn(const U4 * u4_ap_PDU_RX)
{
    U1                                u1_t_ok;
    U1                                u1_t_rx_chk;

    u1_t_rx_chk = (U1)0U;

#if 0   /* BEV Diag provisionally *//* Temporary implementation for the ECV phase; will be fixed in a later phase. */
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
#endif  /* BEV Diag provisionally *//* Temporary implementation for the ECV phase; will be fixed in a later phase. */

    /* HUD  */
    u1_t_ok = u1_g_XSpiMETRxRdAccessSts((U1)XSPI_MET_XSPI_RX_HUDGVIFCTL);   /* HUDGVIFCTL_UP_STS(2,3-2)         */
    if(u1_t_ok == (U1)XSPI_MET_XSPI_RX_READ_VALID){
        /* HUD Product Number */
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W12_HUD]  = u4_ap_PDU_RX[65];         /* HUD_DG_22_F191_SPN_11-14         */
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W13_HUD]  = u4_ap_PDU_RX[66];         /* HUD_DG_22_F191_SPN_15,21-23      */
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W14_HUD]  = u4_ap_PDU_RX[67];         /* HUD_DG_22_F191_SPN_24-25,M1-M2   */
        u1_t_rx_chk                                    |= (U1)((U1)0x01U << XSPI_SPN_RX_HUD);

        /* HUD Serial number */
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W18_HUD_SERI_N]  = u4_ap_PDU_RX[73];  /* HUD_GV_DG_HUDSN_1-4              */
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W19_HUD_SERI_N]  = u4_ap_PDU_RX[74];  /* HUD_GV_DG_HUDSN_5-8              */
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W20_HUD_SERI_N]  = u4_ap_PDU_RX[75];  /* HUD_GV_DG_HUDSN_9-12             */
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W21_HUD_SERI_N]  = u4_ap_PDU_RX[76];  /* HUD_GV_DG_HUDSN_13-16            */
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W22_HUD_SERI_N]  = u4_ap_PDU_RX[77];  /* HUD_GV_DG_HUDSN_17-20            */
        u1_t_rx_chk                                    |= (U1)((U1)0x01U << XSPI_SPN_RX_HUD_SERI_N);
    }
    /* EXT DISP  */
    u1_t_ok = u1_g_XSpiMETRxRdAccessSts((U1)XSPI_MET_XSPI_RX_METGVIFCTL);   /* METGVIFCTL_UP_STS(2,1-0)         */
    if(u1_t_ok == (U1)XSPI_MET_XSPI_RX_READ_VALID){
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W15_DISP]  = u4_ap_PDU_RX[121];       /* DISP_DG_22_F191_SPN_11-14        */
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W16_DISP]  = u4_ap_PDU_RX[122];       /* DISP_DG_22_F191_SPN_15,21-23     */
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W17_DISP]  = u4_ap_PDU_RX[123];       /* DISP_DG_22_F191_SPN_24-25,M1-M2  */
        u1_t_rx_chk                                     |= (U1)((U1)0x01U << XSPI_SPN_RX_DISP);
    }

#if 0   /* BEV Diag provisionally *//* Temporary implementation for the ECV phase; will be fixed in a later phase. */
    /* Software Version */
    u4_t_ok = u4_ap_PDU_RX[509] & (U4)XSPI_SPN_RX_CHK;
    if(u4_t_ok == (U4)0U){
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W18_VER] = u4_ap_PDU_RX[507];
        u4_sp_xspi_spn_rx[XSPI_SPN_RX_W19_VER] = u4_ap_PDU_RX[508];
        u1_t_rx_chk                                   |= (U1)((U1)0x01U << XSPI_SPN_RX_VER);
    }
#endif  /* BEV Diag provisionally *//* Temporary implementation for the ECV phase; will be fixed in a later phase. */

    u1_s_xspi_spn_rx_tocnt = (U1)XSPI_SPN_RX_TOC_INI;
    u1_s_xspi_spn_rx_chk   = u1_t_rx_chk;
}
/*===================================================================================================================================*/
/*  static void    vd_s_XSpiDsalTx_2E(U4 * u4_ap_pdu_tx)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XSpiDsalTx_2E(U4 * u4_ap_pdu_tx)
{
#if 0      /* BEV Diag provisionally */
    u4_ap_pdu_tx[441]  = u4_g_VardefDs2E_Las32((U2)VDF_DS_2E_2002);                 /* DG_2E_2002_4_MET_IGOFF_ODO_TIME      */
#endif     /* BEV Diag provisionally */
}
/*===================================================================================================================================*/
/*  static void    vd_s_XSpiDsalTx_Dsr(U4 * u4_ap_pdu_tx)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XSpiDsalTx_Dsr(U4 * u4_ap_pdu_tx)
{
    U4                                u4_t_lpcnt;
    U2                                u2_t_woff;

    u4_s_xspi_dsr_unlock = (U4)0U;
    
    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)XSPI_DSR_NUM_CH; u4_t_lpcnt++){
        u2_t_woff  = st_sp_XSPI_DSR_CH[u4_t_lpcnt].u2_woff;
        u4_ap_pdu_tx[u2_t_woff] = st_sp_xspi_dsr_trx[u4_t_lpcnt].u4_reqtx;
    }
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
/*  1.2.0     8/05/2024  SM       Rename to vd_g_LComSpiDs22Read and add process for Diag SID 0x22.                                  */
/*  1.2.1     8/27/2024  TK       Add DID 10AF proccess for 19PFv3.                                                                  */
/*  1.3.0     9/24/2024  SI       Add DID 10B2 Logic.                                                                                */
/*                                Remove unnecessary logic for DID 10A7/10A8/10A9.                                                   */
/*  1.3.1    12/23/2024  SI       Remove vd_s_LComSpiDsalTx_BA_DA.                                                                   */
/*  1.3.2    12/23/2024  SI       Add DID F082-F085 Logic.                                                                           */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  BEV-1    12/17/2025  SI       Remove unnecessary functions in BEV.                                                               */
/*  BEV-2     3/04/2026  TKa      Change vd_g_XSpiDsalMainTask execution period from 10ms to 5ms.                                    */
/*                                Replace the magic number for the execution period with a defined constant.                         */
/*  BEV-3     3/27/2026  NY       Change DID F188/F1A0 logic.                                                                        */
/*                                Change woff setting value for XSPI_DSR_31_ESO.                                                     */
/*  BEV-4     4/14/2026  TKa      Remove DID 2831/2B01 transmission logic.                                                           */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*  * AS   = Atsunori Sugita, DENSO-TECHNO                                                                                           */
/*  * SM   = Shota Maegawa, DENSO-TECHNO                                                                                             */
/*  * TK   = Toru Kamishina, DENSO-TECHNO                                                                                            */
/*  * SI   = Shugo Ichinose, DENSO-TECHNO                                                                                            */
/*  * TKa  = Tamao Kamiya, DENSO-TECHNO                                                                                              */
/*  * NY   = Nobuhiro Yoshiyasu, DENSO-TECHNO                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/
