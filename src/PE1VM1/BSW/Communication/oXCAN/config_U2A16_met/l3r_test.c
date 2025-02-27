/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  L3R Test                                                                                                                         */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define L3R_TEST_C_MAJOR                         (1)
#define L3R_TEST_C_MINOR                         (0)
#define L3R_TEST_C_PATCH                         (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "l3r_test.h"
#include "gpt_drv_frt.h"
#include "veh_opemd.h"

#include "oxcan.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((L3R_TEST_C_MAJOR != L3R_TEST_H_MAJOR) || \
     (L3R_TEST_C_MINOR != L3R_TEST_H_MINOR) || \
     (L3R_TEST_C_PATCH != L3R_TEST_H_PATCH))
#error "l3r_test.c and l3r_test.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define L3R_TEST_FRT_MAX                         (0x7fffffffU)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define L3R_TEST_PDU_LOG_TX                      (MSG_MET1S55_TXCH0)  /* CAN-ID 0x1F7                       */
#define L3R_TEST_LOG_DLC_MAX                     (32U)                /* data length of L3R_TEST_PDU_LOG_TX */
#define L3R_TEST_LOG_RXC_MAX                     (15U)                /* (32 byte - 2 byte) / 2 byte        */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define L3R_TEST_PDU_CYC_TX                      (MSG_CDC1S01_TXCH0)  /* CAN-ID 0x333                       */
#define L3R_TEST_CYC_DLC_MAX                     (32U)                /* data length of L3R_TEST_PDU_CYC_TX */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Transmission Source */
#define L3R_TEST_TXS_VM_0                        (0x10U)
#define L3R_TEST_TXS_VM_1                        (0x20U)
#define L3R_TEST_TXS_VM_2                        (0x40U)
#define L3R_TEST_TXS_VM_3                        (0x80U)

#define L3R_TEST_TXS_VM_X                        (L3R_TEST_TXS_VM_1)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define L3R_TEST_NUM_PDU_RX                      (BSW_COM_CFG_CH00_RX_NUM)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u2_L3R_TEST_LTX_MAX(npdu, nrxc)          (((U2)(npdu) + ((U2)(nrxc) - (U2)1U)) / (U2)(nrxc))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U4   u4_min;
    U4   u4_max;
    U4   u4_frt;
}ST_L3R_TEST_CYC;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static ST_L3R_TEST_CYC    st_s_l3r_test_mid;
static ST_L3R_TEST_CYC    st_s_l3r_test_high;

static U4   u4_s_l3r_test_nrx_frt;
static U4   u4_s_l3r_test_cyc_frt;
static U4   u4_s_l3r_test_ev_frt;
static U1   u1_s_l3r_test_ev_cnt;

static U2   u2_s_l3r_test_ltxrun; /* ltx = log tx */
static U2   u2_s_l3r_test_ltxfin;

static U2   u2_sp_l3r_test_rxcnt[L3R_TEST_NUM_PDU_RX];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_L3rTestCycCapt(ST_L3R_TEST_CYC * st_ap_cyc);
static void    vd_s_L3rTestCycTx(void);
static void    vd_s_L3rTestLogTx(const U4 u4_a_RUN, const U1 u1_a_RXC_STA);
static void    vd_s_L3rTestEvTx(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4             u4_s_L3R_TEST_CYC_TX     = (U4)1000000U * (U4)GPT_FRT_1US;

static const U2             u2_s_L3R_TEST_LTX_MAX    = u2_L3R_TEST_LTX_MAX(L3R_TEST_NUM_PDU_RX, L3R_TEST_LOG_RXC_MAX);
static const U2             u2_s_L3R_TEST_PDU_RX_MIN = (U2)MSG_ABG1D50_RXCH0;
static const U2             u2_s_L3R_TEST_PDU_RX_MAX = (U2)MSG_ZN21S72_RXCH0;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_L3rTestInit(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_L3rTestInit(void)
{
    U4                          u4_t_lpcnt;

    st_s_l3r_test_mid.u4_min  = (U4)U4_MAX;
    st_s_l3r_test_mid.u4_max  = (U4)0U;
    st_s_l3r_test_mid.u4_frt  = (U4)U4_MAX;

    st_s_l3r_test_high.u4_min = (U4)U4_MAX;
    st_s_l3r_test_high.u4_max = (U4)0U;
    st_s_l3r_test_high.u4_frt = (U4)U4_MAX;

    u4_s_l3r_test_cyc_frt     = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA) - u4_s_L3R_TEST_CYC_TX;
    u4_s_l3r_test_nrx_frt     = (U4)U4_MAX;
    u4_s_l3r_test_ev_frt      = (U4)U4_MAX;
    u1_s_l3r_test_ev_cnt      = (U1)U1_MAX;

    u2_s_l3r_test_ltxrun      = (U2)U2_MAX;
    u2_s_l3r_test_ltxfin      = (U2)U2_MAX;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)L3R_TEST_NUM_PDU_RX; u4_t_lpcnt++){
        u2_sp_l3r_test_rxcnt[u4_t_lpcnt] = (U2)0U;
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_L3rTestMainTask(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_L3rTestMainTask(void)
{
    static const U4             u4_s_L3R_TEST_FRT_TX_STA = (U4)2000000U * (U4)GPT_FRT_1US; /* 2 seconds */
    U4                          u4_t_elpsd;

    vd_s_L3rTestCycCapt(&st_s_l3r_test_mid);
    vd_s_L3rTestCycTx();
    vd_s_L3rTestEvTx();

    if(u4_s_l3r_test_nrx_frt <= (U4)L3R_TEST_FRT_MAX){
        u4_t_elpsd = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA) - u4_s_l3r_test_nrx_frt;
        u4_t_elpsd = u4_t_elpsd & (U4)L3R_TEST_FRT_MAX;
    }
    else{
        u4_t_elpsd = (U4)0U;
    }

    if((u4_t_elpsd           >= u4_s_L3R_TEST_FRT_TX_STA) &&
       (u2_s_l3r_test_ltxfin >= (U2)U2_MAX              )){

        u2_s_l3r_test_ltxrun = (U2)0U;
        u2_s_l3r_test_ltxfin = (U2)0U;
    }

    if((u2_s_l3r_test_ltxrun <  u2_s_L3R_TEST_LTX_MAX) &&
       (u2_s_l3r_test_ltxrun == u2_s_l3r_test_ltxfin )){

        vd_s_L3rTestLogTx((U4)u2_s_l3r_test_ltxrun, (U1)FALSE);
        u2_s_l3r_test_ltxrun++;
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_L3rTestCycleHigh(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_L3rTestCycleHigh(void)
{
    vd_s_L3rTestCycCapt(&st_s_l3r_test_high);
}
/*===================================================================================================================================*/
/*  void    vd_g_L3rTestStart(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_L3rTestStart(void)
{
    U4                          u4_t_lpcnt;

    u4_s_l3r_test_nrx_frt = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA) & (U4)L3R_TEST_FRT_MAX;
    u2_s_l3r_test_ltxrun  = (U2)U2_MAX;
    u2_s_l3r_test_ltxfin  = (U2)U2_MAX;

    for(u4_t_lpcnt = (U4)0U; u4_t_lpcnt < (U4)L3R_TEST_NUM_PDU_RX; u4_t_lpcnt++){
        u2_sp_l3r_test_rxcnt[u4_t_lpcnt] = (U2)0U;
    }

    vd_s_L3rTestLogTx((U4)0U, (U1)TRUE);
}
/*===================================================================================================================================*/
/*  void    vd_g_L3rTestTxAck(const U2 u2_a_PDU_TX)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_L3rTestTxAck(const U2 u2_a_PDU_TX)
{
    if((u2_a_PDU_TX          == (U2)L3R_TEST_PDU_LOG_TX) &&
       (u2_s_l3r_test_ltxfin <  u2_s_l3r_test_ltxrun   )){

        u2_s_l3r_test_ltxfin++;
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_L3rTestRxAck(const U2 u2_a_PDU_RX)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_L3rTestRxAck(const U2 u2_a_PDU_RX)
{
    U2                          u2_t_pdu_rx;

    if((u2_a_PDU_RX >= u2_s_L3R_TEST_PDU_RX_MIN) &&
       (u2_a_PDU_RX <= u2_s_L3R_TEST_PDU_RX_MAX)){

        u2_t_pdu_rx = u2_a_PDU_RX - u2_s_L3R_TEST_PDU_RX_MIN;

        if(u2_s_l3r_test_ltxrun == (U2)U2_MAX){
            u2_sp_l3r_test_rxcnt[u2_t_pdu_rx]++;
        }

        if((u2_a_PDU_RX           != (U2)MSG_BDC1S81_RXCH0) &&
           (u4_s_l3r_test_nrx_frt <= (U4)L3R_TEST_FRT_MAX )){

            u4_s_l3r_test_nrx_frt = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA) & (U4)L3R_TEST_FRT_MAX;
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_L3rTestCycCapt(ST_L3R_TEST_CYC * st_ap_cyc)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_L3rTestCycCapt(ST_L3R_TEST_CYC * st_ap_cyc)
{
    U4                          u4_t_frt;
    U4                          u4_t_elpsd;

    u4_t_frt = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA) & (U4)L3R_TEST_FRT_MAX;

    if(st_ap_cyc->u4_frt < (U4)U4_MAX){

        u4_t_elpsd = (u4_t_frt - st_ap_cyc->u4_frt) & (U4)L3R_TEST_FRT_MAX;
        if(u4_t_elpsd < st_ap_cyc->u4_min){
            st_ap_cyc->u4_min = u4_t_elpsd;
        }

        if(u4_t_elpsd > st_ap_cyc->u4_max){
            st_ap_cyc->u4_max = u4_t_elpsd;
        }
    }
    st_ap_cyc->u4_frt = u4_t_frt;
}
/*===================================================================================================================================*/
/*  static void    vd_s_L3rTestCycTx(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_L3rTestCycTx(void)
{
    U1 *                        u1_tp_byte_ctx;
    U4                          u4_tp_word_ctx[L3R_TEST_CYC_DLC_MAX >> 2U];
    U4                          u4_t_elpsd;
    U4                          u4_t_offset;
    U4                          u4_t_min;
    U4                          u4_t_max;

    u4_t_elpsd = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA) - u4_s_l3r_test_cyc_frt;
    if(u4_t_elpsd >= u4_s_L3R_TEST_CYC_TX){

        u4_s_l3r_test_cyc_frt += u4_s_L3R_TEST_CYC_TX;

        for(u4_t_offset = (U4)0U; u4_t_offset < (U4)(L3R_TEST_CYC_DLC_MAX >> 2U); u4_t_offset++){
            u4_tp_word_ctx[u4_t_offset] = (U4)0U;
        }
        u1_tp_byte_ctx     = (U1 *)&u4_tp_word_ctx[0U];

        u4_t_min = st_s_l3r_test_mid.u4_min >> 3U;  /* 80MHz -> 10MHz */
        u4_t_max = st_s_l3r_test_mid.u4_max >> 3U;  /* 80MHz -> 10MHz */

        u1_tp_byte_ctx[0U]  = (U1)(u4_t_min >> 24U);
        u1_tp_byte_ctx[1U]  = (U1)(u4_t_min >> 16U);
        u1_tp_byte_ctx[2U]  = (U1)(u4_t_min >> 8U);
        u1_tp_byte_ctx[3U]  = (U1)u4_t_min;

        u1_tp_byte_ctx[4U]  = (U1)(u4_t_max >> 24U);
        u1_tp_byte_ctx[5U]  = (U1)(u4_t_max >> 16U);
        u1_tp_byte_ctx[6U]  = (U1)(u4_t_max >> 8U);
        u1_tp_byte_ctx[7U]  = (U1)u4_t_max;

        u4_t_min = st_s_l3r_test_high.u4_min >> 3U;  /* 80MHz -> 10MHz */
        u4_t_max = st_s_l3r_test_high.u4_max >> 3U;  /* 80MHz -> 10MHz */

        u1_tp_byte_ctx[8U]  = (U1)(u4_t_min >> 24U);
        u1_tp_byte_ctx[9U]  = (U1)(u4_t_min >> 16U);
        u1_tp_byte_ctx[10U] = (U1)(u4_t_min >> 8U);
        u1_tp_byte_ctx[11U] = (U1)u4_t_min;

        u1_tp_byte_ctx[12U] = (U1)(u4_t_max >> 24U);
        u1_tp_byte_ctx[13U] = (U1)(u4_t_max >> 16U);
        u1_tp_byte_ctx[14U] = (U1)(u4_t_max >> 8U);
        u1_tp_byte_ctx[15U] = (U1)u4_t_max;

        Com_SendIPDU((PduIdType)L3R_TEST_PDU_CYC_TX, &u1_tp_byte_ctx[0]);
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_L3rTestEvTx(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_L3rTestEvTx(void)
{
    static const U4             u4_s_L3R_TEST_EV_TX     = (U4)500000U * (U4)GPT_FRT_1US;

    U1 *                        u1_tp_byte_etx;
    U4                          u4_tp_word_etx[2U];
    U4                          u4_t_elpsd;
    U4                          u4_t_offset;
    U4                          u4_t_vom;

    u4_t_vom = u4_g_VehopemdMdfield() & (U4)VEH_OPEMD_MDBIT_IG_P;
    if(u4_t_vom == (U4)0U){

        u4_s_l3r_test_ev_frt = (U4)U4_MAX;
        u1_s_l3r_test_ev_cnt = (U1)0U;
    }
    else if(u4_s_l3r_test_ev_frt >= (U4)U4_MAX){

        u4_s_l3r_test_ev_frt = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA) & (U4)L3R_TEST_FRT_MAX;
        u1_s_l3r_test_ev_cnt = (U1)0U;
    }
    else{

        u4_t_elpsd  = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA) - u4_s_l3r_test_ev_frt;
        u4_t_elpsd &= (U4)L3R_TEST_FRT_MAX;
        if(u4_t_elpsd >= u4_s_L3R_TEST_EV_TX){

            u4_s_l3r_test_ev_frt = (u4_s_l3r_test_ev_frt + u4_s_L3R_TEST_EV_TX) & (U4)L3R_TEST_FRT_MAX;

            for(u4_t_offset = (U4)0U; u4_t_offset < (U4)2U; u4_t_offset++){
                u4_tp_word_etx[u4_t_offset] = (U4)0U;
            }
            u1_tp_byte_etx     = (U1 *)&u4_tp_word_etx[0U];
            u1_tp_byte_etx[0U] = u1_s_l3r_test_ev_cnt;
            u1_s_l3r_test_ev_cnt++;

            Com_SendIPDU((PduIdType)MSG_MET1S25_TXCH0, &u1_tp_byte_etx[0]);
            Com_SendIPDU((PduIdType)MSG_MET1S33_TXCH0, &u1_tp_byte_etx[0]);
        }
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_L3rTestLogTx(const U4 u4_a_RUN, const U1 u1_a_RXC_STA)                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_L3rTestLogTx(const U4 u4_a_RUN, const U1 u1_a_RXC_STA)
{
    U1 *                        u1_tp_byte_ltx;

    U4                          u4_tp_word_ltx[L3R_TEST_LOG_DLC_MAX >> 2U];
    U4                          u4_t_rxc_sta;
    U4                          u4_t_rxc_end;
    U4                          u4_t_ipdu_rx;
    U4                          u4_t_offset;

    u4_t_rxc_sta = u4_a_RUN * (U4)L3R_TEST_LOG_RXC_MAX;
    u4_t_rxc_end = u4_t_rxc_sta + (U4)L3R_TEST_LOG_RXC_MAX;
    if(u4_t_rxc_end >= (U4)L3R_TEST_NUM_PDU_RX){
        u4_t_rxc_end = (U4)L3R_TEST_NUM_PDU_RX;
    }

    if(u1_a_RXC_STA == (U1)TRUE){
        u4_t_ipdu_rx = (U4)0x00000fffU;
    }
    else{
        u4_t_ipdu_rx = u4_t_rxc_sta + (U4)u2_s_L3R_TEST_PDU_RX_MIN;
    }

    for(u4_t_offset = (U4)0U; u4_t_offset < (U4)(L3R_TEST_LOG_DLC_MAX >> 2U); u4_t_offset++){
        u4_tp_word_ltx[u4_t_offset] = (U4)0U;
    }
    u1_tp_byte_ltx     = (U1 *)&u4_tp_word_ltx[0U];
    u1_tp_byte_ltx[0U] = (U1)L3R_TEST_TXS_VM_X | (U1)(u4_t_ipdu_rx >> 8U);
    u1_tp_byte_ltx[1U] = (U1)u4_t_ipdu_rx;

    u4_t_offset = (U4)2U;
    while((u4_t_rxc_sta < u4_t_rxc_end            ) &&
          (u4_t_offset  < (U4)L3R_TEST_LOG_DLC_MAX)){

        u1_tp_byte_ltx[u4_t_offset] = (U1)(u2_sp_l3r_test_rxcnt[u4_t_rxc_sta] >> 8U);
        u4_t_offset++;

        u1_tp_byte_ltx[u4_t_offset] = (U1)u2_sp_l3r_test_rxcnt[u4_t_rxc_sta];
        u4_t_offset++;

        u4_t_rxc_sta++;
    }

    /* Com_WriteIPDU((PduIdType)L3R_TEST_PDU_LOG_TX, &u1_tp_byte_ltx[0]); */
    Com_SendIPDU((PduIdType)L3R_TEST_PDU_LOG_TX, &u1_tp_byte_ltx[0]);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     1/ 9/2025  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
