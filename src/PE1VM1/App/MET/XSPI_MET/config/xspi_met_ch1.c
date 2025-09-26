/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Local Communication SPI                                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_CH1_C_MAJOR                     (0U)
#define XSPI_CH1_C_MINOR                     (0U)
#define XSPI_CH1_C_PATCH                     (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "xspi_met.h"
#include "xspi_met_ch1.h"
#if 0   /* BEV BSW provisionally */
#include "xspi_met_can_cfg.h"
#endif
#include "xspi_met_ch_private.h"

#if 0   /* BEV Rebase provisionally */
/* Platform */
/* #include "oxcan.h" */ /* @@@ Provisional for 310D PreCV @@@ */

#include "mulmed_color.h"
#include "locale.h"
#include "vardef.h"

#include "gateway_mm.h"

/* Hmi */
#include "hmimm2c100n.h"
#include "hmimm2c107n.h"
#include "hmimm2c118n.h"
#include "hmimm2c112n.h"
#include "hmimm2c124n.h"
#include "evschg.h"
#endif   /* BEV Rebase provisionally */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((XSPI_CH1_C_MAJOR != XSPI_CFG_H_MAJOR) || \
     (XSPI_CH1_C_MINOR != XSPI_CFG_H_MINOR) || \
     (XSPI_CH1_C_PATCH != XSPI_CFG_H_PATCH))
#error "xspi_ch1.c and xspi_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((XSPI_CH1_C_MAJOR != XSPI_CH_H_MAJOR) || \
     (XSPI_CH1_C_MINOR != XSPI_CH_H_MINOR) || \
     (XSPI_CH1_C_PATCH != XSPI_CH_H_PATCH))
#error "xspi_ch1.c and xspi_ch_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_XSPI_MET_READ__BIT(u4_buf , u1_pos , u1_len) ((U1)((U1)((u4_buf)  >> (u1_pos)) & (U1)((1U << (u1_len)) - 1U)))
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if 0   /* BEV Rebase provisionally */
typedef struct{
    U1                          u1_xspiid;
    U1                          u1_bitpos;
    U1                          u1_datalen;
    U1                          u1_maxvalue;
    U1                          u1_vdsci_id;
}ST_XSPI_TXSIG;
#endif   /* BEV Rebase provisionally */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/  

#if 0   /* BEV Rebase provisionally */
static U1             u1_s_xspi_ethercomsts;
static U1             u1_s_xspi_mm2c100n_rxcnt;
static U1             u1_s_xspi_mm2c107n_rxcnt;
static U1             u1_s_xspi_mm2c112n_rxcnt;
static U1             u1_s_xspi_mm2c118n_rxcnt;
static U1             u1_s_xspi_mm2c124n_rxcnt;

static U1             u1_s_prem_bb;               /*  M_BB Previous RxValue    */
static U1             u1_s_premlr_bb;             /*  MLR_BB Previous RxValue  */
static U1             u1_s_prerlm_bb;             /*  RLM_BB Previous RxValue  */
static U1             u1_s_premrt_bb;             /*  MRT_BB Previous RxValue  */
static U1             u1_s_preart_bb;             /*  ART_BB Previous RxValue  */
static U1             u1_s_prepwlsw;              /*  PWLSW Previous RxValue   */
static U1             u1_s_prewvrd_bb;            /*  WVRD_BB Previous RxValue */
static U1             u1_s_prewvru_bb;            /*  WVRU_BB Previous RxValue */
static U1             u1_s_prewrof_bb;            /*  WROF_BB Previous RxValue */
static U1             u1_s_prewrlo_bb;            /*  WRLO_BB Previous RxValue */
static U1             u1_s_prewrin_bb;            /*  WRIN_BB Previous RxValue */
static U1             u1_s_prewrsw_bb;            /*  WRSW_BB Previous RxValue */
static U1             u1_s_prewsvs_bb;            /*  WSVS_BB Previous RxValue */
static U1             u1_s_pretrnbbsw;            /*  TRNBBSW Previous RxValue */
static U1             u1_s_prelswbb;              /*  LSW_BB Previous RxValue  */
static U1             u1_s_prefogbb;              /*  FOG_BB Previous RxValue  */
static U1             u1_s_prerfgbb;              /*  LSW_BB Previous RxValue  */
static U1             u1_s_premetmdsel;           /*  METMDSEL Previous RxValue*/
static U1             u1_s_preaecoswbb;           /*  AECOSWBB Previous RxValue*/
static U1             u1_s_premw_bb;              /*  MW_BB Previous RxValue   */
static U1             u1_s_prewdi_bb;             /*  WDI_BB Previous RxValue  */
static U1             u1_s_prehcsupen;            /*  HCSUPEN Previous RxValue */
static U1             u1_s_prehcsdwen;            /*  HCSDWEN Previous RxValue */
static U1             u1_s_prehcsmnsw;            /*  HCSMNSW Previous RxValue */
static U1             u1_s_prehcsstpop;           /*  HCSSTPOP Previous RxValue*/
static U1             u1_s_pretite_bb;            /*  TITE_BB Previous RxValue */
static U1             u1_s_preadsegdsw;           /*  ADSEGDSW Previous RxValue*/
static U1             u1_s_predpms_bb;            /*  DPMS_BB Previous RxValue */
static U1             u1_s_prepos_call;           /*  POS_CALL Previous RxValue*/
static U1             u1_s_prepos_reg;            /*  POS_REG Previous RxValue */
static U1             u1_s_preflynop;             /*  FLYNOP Previous RxValue  */
#endif   /* BEV Rebase provisionally */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if 0   /* BEV Rebase provisionally */
static inline void    vd_s_XSpiCfgRxEther(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_M_BB(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_MLR_BB(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_RLM_BB(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_MRT_BB(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_ART_BB(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_PWLSW(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_WVRD_BB(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_WVRU_BB(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_WROF_BB(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_WRLO_BB(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_WRIN_BB(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_WRSW_BB(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_WSVS_BB(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_TRNBBSW(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_LSW_BB(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_FOG_BB(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_RFG_BB(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_METMDSEL(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_AECOSWBB(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_MW_BB(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_WDI_BB(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_HCSUPEN(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_HCSDWEN(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_HCSMNSW(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_HCSSTPOP(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_TITE_BB(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_ADSEGDSW(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_DPMS_BB(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_POS_CALL(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_POS_REG(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_FLYNOP(const U4* u4_ap_pck_rx);
#endif   /* BEV Rebase provisionally */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_XSpiCfgInitCh1(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiCfgInitCh1(void)
{
#if 0   /* BEV Rebase provisionally */
    U1  u1_t_loop;

    u1_s_xspi_ethercomsts = (U1)XSPI_ETHER_UNDEF2;
    u1_s_xspi_mm2c100n_rxcnt = (U1)0U;
    u1_s_xspi_mm2c107n_rxcnt = (U1)0U;
    u1_s_xspi_mm2c112n_rxcnt = (U1)0U;
    u1_s_xspi_mm2c118n_rxcnt = (U1)0U;
    u1_s_xspi_mm2c124n_rxcnt = (U1)0U;
    u1_s_prem_bb     = (U1)0U;
    u1_s_premlr_bb   = (U1)0U;
    u1_s_prerlm_bb   = (U1)0U;
    u1_s_premrt_bb   = (U1)0U;
    u1_s_preart_bb   = (U1)0U;
    u1_s_prepwlsw    = (U1)0U;
    u1_s_prewvrd_bb  = (U1)0U;
    u1_s_prewvru_bb  = (U1)0U;
    u1_s_prewrof_bb  = (U1)0U;
    u1_s_prewrlo_bb  = (U1)0U;
    u1_s_prewrin_bb  = (U1)0U;
    u1_s_prewrsw_bb  = (U1)0U;
    u1_s_prewsvs_bb  = (U1)0U;
    u1_s_pretrnbbsw  = (U1)0U;
    u1_s_prelswbb = (U1)0U;
    u1_s_prefogbb = (U1)0U;
    u1_s_prerfgbb = (U1)0U;
    u1_s_premetmdsel = (U1)0U;
    u1_s_preaecoswbb = (U1)0U;
    u1_s_premw_bb    = (U1)0U;
    u1_s_prewdi_bb   = (U1)0U;
    u1_s_prehcsupen  = (U1)0U;
    u1_s_prehcsdwen  = (U1)0U;
    u1_s_prehcsmnsw  = (U1)0U;
    u1_s_prehcsstpop = (U1)0U;
    u1_s_pretite_bb  = (U1)0U;
    u1_s_preadsegdsw = (U1)0U;
    u1_s_predpms_bb  = (U1)0U;
    u1_s_prepos_call = (U1)0U;
    u1_s_prepos_reg  = (U1)0U;
    u1_s_preflynop   = (U1)0U;

#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  void    vd_g_XSpiCfgPduRxCh1(const U4 * u4_ap_PDU_RX)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiCfgPduRxCh1(const U4 * u4_ap_PDU_RX)
{
#if 0   /* BEV Rebase provisionally */
    vd_s_XSpiCfgRxEther(&u4_ap_PDU_RX[100]);

    vd_s_XSpiCanTx_M_BB(&u4_ap_PDU_RX[91]);
    vd_s_XSpiCanTx_MLR_BB(&u4_ap_PDU_RX[91]);
    vd_s_XSpiCanTx_RLM_BB(&u4_ap_PDU_RX[91]);
    vd_s_XSpiCanTx_MRT_BB(&u4_ap_PDU_RX[91]);
    vd_s_XSpiCanTx_ART_BB(&u4_ap_PDU_RX[91]);
    vd_s_XSpiCanTx_PWLSW(&u4_ap_PDU_RX[91]);
    vd_s_XSpiCanTx_WVRD_BB(&u4_ap_PDU_RX[23]);
    vd_s_XSpiCanTx_WVRU_BB(&u4_ap_PDU_RX[23]);
    vd_s_XSpiCanTx_WROF_BB(&u4_ap_PDU_RX[23]);
    vd_s_XSpiCanTx_WRLO_BB(&u4_ap_PDU_RX[23]);
    vd_s_XSpiCanTx_WRIN_BB(&u4_ap_PDU_RX[23]);
    vd_s_XSpiCanTx_WRSW_BB(&u4_ap_PDU_RX[23]);
    vd_s_XSpiCanTx_WSVS_BB(&u4_ap_PDU_RX[91]);
    vd_s_XSpiCanTx_TRNBBSW(&u4_ap_PDU_RX[35]);
    vd_s_XSpiCanTx_LSW_BB(&u4_ap_PDU_RX[91]);
    vd_s_XSpiCanTx_FOG_BB(&u4_ap_PDU_RX[91]);
    vd_s_XSpiCanTx_RFG_BB(&u4_ap_PDU_RX[91]);
    vd_s_XSpiCanTx_METMDSEL(&u4_ap_PDU_RX[39]);
    vd_s_XSpiCanTx_AECOSWBB(&u4_ap_PDU_RX[39]);
    vd_s_XSpiCanTx_MW_BB(&u4_ap_PDU_RX[91]);
    vd_s_XSpiCanTx_WDI_BB(&u4_ap_PDU_RX[91]);
    vd_s_XSpiCanTx_HCSUPEN(&u4_ap_PDU_RX[69]);
    vd_s_XSpiCanTx_HCSDWEN(&u4_ap_PDU_RX[69]);
    vd_s_XSpiCanTx_HCSMNSW(&u4_ap_PDU_RX[69]);
    vd_s_XSpiCanTx_HCSSTPOP(&u4_ap_PDU_RX[69]);
    vd_s_XSpiCanTx_TITE_BB(&u4_ap_PDU_RX[91]);
    vd_s_XSpiCanTx_ADSEGDSW(&u4_ap_PDU_RX[39]);
    vd_s_XSpiCanTx_DPMS_BB(&u4_ap_PDU_RX[91]);
    vd_s_XSpiCanTx_POS_CALL(&u4_ap_PDU_RX[91]);
    vd_s_XSpiCanTx_POS_REG(&u4_ap_PDU_RX[91]);
    vd_s_XSpiCanTx_FLYNOP(&u4_ap_PDU_RX[47]);

#endif   /* BEV Rebase provisionally */
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Rx Functions                                                                                                                     */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if 0   /* BEV Rebase provisionally */
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCfgRxEther(  const U4 * u4_ap_pck_rx)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgRxEther(const U4 * u4_ap_pck_rx)
{
    u1_s_xspi_ethercomsts = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[5], (U1)0U, (U1)2U);
    u1_s_xspi_mm2c100n_rxcnt = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)0U, (U1)8U);
    u1_s_xspi_mm2c107n_rxcnt = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)8U, (U1)8U);
    u1_s_xspi_mm2c118n_rxcnt = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)16U, (U1)8U);
    u1_s_xspi_mm2c112n_rxcnt = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)24U, (U1)8U);
    u1_s_xspi_mm2c124n_rxcnt = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)0U, (U1)8U);
    vd_g_HmiMM2C100NDataPut(&u4_ap_pck_rx[6]);
    vd_g_HmiMM2C107NDataPut(&u4_ap_pck_rx[31]);
    vd_g_HmiMM2C112NDataPut(&u4_ap_pck_rx[38]);
    vd_g_HmiMM2C118NDataPut(&u4_ap_pck_rx[58]);
    vd_g_HmiMM2C124NDataPut(&u4_ap_pck_rx[93]);

}
#endif   /* BEV Rebase provisionally */
/*===================================================================================================================================*/
/*  U1    u1_g_XSpiEtherComSts(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_s_xspi_ethercomsts                                                                                            */
/*===================================================================================================================================*/
U1    u1_g_XSpiEtherComSts(void){
#if 0   /* BEV Rebase provisionally */
    return(u1_s_xspi_ethercomsts);
#else   /* BEV Rebase provisionally */
    return(0U);
#endif   /* BEV Rebase provisionally */
}
/*===================================================================================================================================*/
/*  U1    u1_g_XSpiMm2c100n_rxcnt(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_s_xspi_mm2c100n_rxcnt                                                                                         */
/*===================================================================================================================================*/
U1    u1_g_XSpiMm2c100n_rxcnt(void){
#if 0   /* BEV Rebase provisionally */
    return(u1_s_xspi_mm2c100n_rxcnt);
#else   /* BEV Rebase provisionally */
    return(0U);
#endif   /* BEV Rebase provisionally */
}
/*===================================================================================================================================*/
/*  U1    u1_g_XSpiMm2c107n_rxcnt(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_s_xspi_mm2c107n_rxcnt                                                                                         */
/*===================================================================================================================================*/
U1    u1_g_XSpiMm2c107n_rxcnt(void){
#if 0   /* BEV Rebase provisionally */
    return(u1_s_xspi_mm2c107n_rxcnt);
#else   /* BEV Rebase provisionally */
    return(0U);
#endif   /* BEV Rebase provisionally */
}
/*===================================================================================================================================*/
/*  U1    u1_g_XSpiMm2c112n_rxcnt(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_s_xspi_mm2c112n_rxcnt                                                                                         */
/*===================================================================================================================================*/
U1    u1_g_XSpiMm2c112n_rxcnt(void){
#if 0   /* BEV Rebase provisionally */
    return(u1_s_xspi_mm2c112n_rxcnt);
#else   /* BEV Rebase provisionally */
    return(0U);
#endif   /* BEV Rebase provisionally */
}
/*===================================================================================================================================*/
/*  U1    u1_g_XSpiMm2c118n_rxcnt(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_s_xspi_mm2c118n_rxcnt                                                                                         */
/*===================================================================================================================================*/
U1    u1_g_XSpiMm2c118n_rxcnt(void){
#if 0   /* BEV Rebase provisionally */
    return(u1_s_xspi_mm2c118n_rxcnt);
#else   /* BEV Rebase provisionally */
    return(0U);
#endif   /* BEV Rebase provisionally */
}

#if 0   /* BEV Rebase provisionally */

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_M_BB(const U4* u4_ap_pck_rx)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_M_BB(const U4* u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_M_BB_MAX = (U1)0x04U;
    U1  u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)9U, (U1)3U);

    if (u1_t_rxdata != u1_s_prem_bb) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_M_BB_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_M_BB, u1_t_rxdata);
        }
    }
    u1_s_prem_bb = u1_t_rxdata;  
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_MLR_BB(const U4* u4_ap_pck_rx)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_MLR_BB(const U4* u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_MLR_BB_MAX = (U1)0x02U;
    U1  u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)17U, (U1)2U);

    if (u1_t_rxdata != u1_s_premlr_bb) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_MLR_BB_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_MLR_BB, u1_t_rxdata);
        }
    }
    u1_s_premlr_bb = u1_t_rxdata; 
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_RLM_BB(const U4* u4_ap_pck_rx)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_RLM_BB(const U4* u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_RLM_BB_MAX = (U1)0x03U;
    U1  u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)3U, (U1)2U);

    if (u1_t_rxdata != u1_s_prerlm_bb) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_RLM_BB_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_RLM_BB, u1_t_rxdata);
        }
    }
    u1_s_prerlm_bb = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_MRT_BB(const U4* u4_ap_pck_rx)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_MRT_BB(const U4* u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_MRT_BB_MAX = (U1)0x03U;
    U1  u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)5U, (U1)2U);

    if (u1_t_rxdata != u1_s_premrt_bb) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_MRT_BB_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_MRT_BB, u1_t_rxdata);
        }
    }
    u1_s_premrt_bb = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_ART_BB(const U4* u4_ap_pck_rx)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_ART_BB(const U4* u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_ART_BB_MAX = (U1)0x03U;
    U1  u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)27U, (U1)2U);

    if (u1_t_rxdata != u1_s_preart_bb) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_ART_BB_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_ART_BB, u1_t_rxdata);
        }
    }
    u1_s_preart_bb = u1_t_rxdata;
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_PWLSW(const U4* u4_ap_pck_rx)                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_PWLSW(const U4* u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_PWLSW_MAX = (U1)0x01U;
    U1  u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)19U, (U1)1U);

    if (u1_t_rxdata != u1_s_prepwlsw) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_PWLSW_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_PWLSW, u1_t_rxdata);
        }
    }
    u1_s_prepwlsw = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_WVRD_BB(const U4* u4_ap_pck_rx)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_WVRD_BB(const U4* u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_WVRD_BB_MAX = (U1)0x01U;
    U1  u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)4U, (U1)1U);

    if (u1_t_rxdata != u1_s_prewvrd_bb) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_WVRD_BB_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_WVRD_BB, u1_t_rxdata);
        }
    }
    u1_s_prewvrd_bb = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_WVRU_BB(const U4* u4_ap_pck_rx)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_WVRU_BB(const U4* u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_WVRU_BB_MAX = (U1)0x01U;
    U1  u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)5U, (U1)1U);

    if (u1_t_rxdata != u1_s_prewvru_bb) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_WVRU_BB_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_WVRU_BB, u1_t_rxdata);
        }
    }
    u1_s_prewvru_bb = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_WROF_BB(const U4* u4_ap_pck_rx)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_WROF_BB(const U4* u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_WROF_BB_MAX = (U1)0x01U;
    U1  u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)2U, (U1)1U);

    if (u1_t_rxdata != u1_s_prewrof_bb) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_WROF_BB_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_WROF_BB, u1_t_rxdata);
        }
    }
    u1_s_prewrof_bb = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_WRLO_BB(const U4* u4_ap_pck_rx)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_WRLO_BB(const U4* u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_WRLO_BB_MAX = (U1)0x01U;
    U1  u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)0U, (U1)1U);

    if (u1_t_rxdata != u1_s_prewrlo_bb) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_WRLO_BB_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_WRLO_BB, u1_t_rxdata);
        }
    }
    u1_s_prewrlo_bb = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_WRIN_BB(const U4* u4_ap_pck_rx)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_WRIN_BB(const U4* u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_WRIN_BB_MAX = (U1)0x01U;
    U1  u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)1U, (U1)1U);

    if (u1_t_rxdata != u1_s_prewrin_bb) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_WRIN_BB_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_WRIN_BB, u1_t_rxdata);
        }
    }
    u1_s_prewrin_bb = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_WRSW_BB(const U4* u4_ap_pck_rx)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_WRSW_BB(const U4* u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_WRSW_BB_MAX = (U1)0x01U;
    U1  u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)3U, (U1)1U);

    if (u1_t_rxdata != u1_s_prewrsw_bb) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_WRSW_BB_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_WRSW_BB, u1_t_rxdata);
        }
    }
    u1_s_prewrsw_bb = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_WSVS_BB(const U4* u4_ap_pck_rx)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_WSVS_BB(const U4* u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_WSVS_BB_MAX = (U1)0x01U;
    U1  u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)12U, (U1)1U);

    if (u1_t_rxdata != u1_s_prewsvs_bb) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_WSVS_BB_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_WSVS_BB, u1_t_rxdata);
        }
    }
    u1_s_prewsvs_bb = u1_t_rxdata;
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_TRNBBSW(const U4* u4_ap_pck_rx)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_TRNBBSW(const U4* u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_TRNBBSW_MAX = (U1)0x02U;
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)3U, (U1)3U);

    if(u1_t_rxdata != u1_s_pretrnbbsw){
        if(u1_t_rxdata <= u1_s_XSPI_MET_TRNBBSW_MAX){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_TRNBBSW, u1_t_rxdata);
        }
    }
    u1_s_pretrnbbsw = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_LSW_BB(const U4* u4_ap_pck_rx)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_LSW_BB(const U4* u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_LSW_BB_MAX = (U1)0x07U;
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)13U, (U1)3U);

    if (u1_t_rxdata != u1_s_prelswbb) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_LSW_BB_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_LSW_BB, u1_t_rxdata);
        }
    }
    u1_s_prelswbb = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_FOG_BB(U4 * u4_ap_pdu_tx)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_FOG_BB(const U4 * u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_FOG_BB_MAX = (U1)0x01U;
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)1U, (U1)2U);

    if (u1_t_rxdata != u1_s_prefogbb) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_FOG_BB_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_FOG_BB, u1_t_rxdata);
        }
    }
    u1_s_prefogbb = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_RFG_BB(U4 * u4_ap_pdu_tx)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_RFG_BB(const U4 * u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_RFG_BB_MAX = (U1)0x01U;
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)29U, (U1)2U);

    if (u1_t_rxdata != u1_s_prerfgbb) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_RFG_BB_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_RFG_BB, u1_t_rxdata);
        }
    }
    u1_s_prerfgbb = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_METMDSEL(U4 * u4_ap_pdu_tx)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_METMDSEL(const U4 * u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_METMDSEL_MAX = (U1)0x03U;
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[5], (U1)29U, (U1)3U);

    if (u1_t_rxdata != u1_s_premetmdsel) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_METMDSEL_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_METMDSEL, u1_t_rxdata);
        }
    }
    u1_s_premetmdsel = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_AECOSWBB(U4 * u4_ap_pdu_tx)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_AECOSWBB(const U4 * u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_AECOSWBB_MAX = (U1)0x01U;
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[4], (U1)25U, (U1)1U);

    if (u1_t_rxdata != u1_s_preaecoswbb) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_AECOSWBB_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_AECOSWBB, u1_t_rxdata);
        }
    }
    u1_s_preaecoswbb = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_MW_BB(U4 * u4_ap_pdu_tx)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_MW_BB(const U4 * u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_MW_BB_MAX = (U1)0x01U;
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)16U, (U1)2U);

    if (u1_t_rxdata != u1_s_premw_bb) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_MW_BB_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_MW_BB, u1_t_rxdata);
        }
    }
    u1_s_premw_bb = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_WDI_BB(U4 * u4_ap_pdu_tx)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_WDI_BB(const U4 * u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_WDI_BB_MAX = (U1)0x03U;
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)8U, (U1)2U);

    if (u1_t_rxdata != u1_s_prewdi_bb) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_WDI_BB_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_WDI_BB, u1_t_rxdata);
        }
    }
    u1_s_prewdi_bb = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_HCSUPEN(U4 * u4_ap_pdu_tx)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_HCSUPEN(const U4 * u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_HCSUPEN_MAX = (U1)0x01U;
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)28U, (U1)1U);

    if (u1_t_rxdata != u1_s_prehcsupen) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_HCSUPEN_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_HCSUPEN, u1_t_rxdata);
        }
    }
    u1_s_prehcsupen = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_HCSDWEN(U4 * u4_ap_pdu_tx)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_HCSDWEN(const U4 * u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_HCSDWEN_MAX = (U1)0x01U;
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)27U, (U1)1U);

    if (u1_t_rxdata != u1_s_prehcsdwen) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_HCSDWEN_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_HCSDWEN, u1_t_rxdata);
        }
    }
    u1_s_prehcsdwen = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_HCSMNSW(U4 * u4_ap_pdu_tx)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_HCSMNSW(const U4 * u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_HCSMNSW_MAX = (U1)0x01U;
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)26U, (U1)1U);

    if (u1_t_rxdata != u1_s_prehcsmnsw) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_HCSMNSW_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_HCSMNSW, u1_t_rxdata);
        }
    }
    u1_s_prehcsmnsw = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_HCSSTPOP(U4 * u4_ap_pdu_tx)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_HCSSTPOP(const U4 * u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_HCSSTPOP_MAX = (U1)0x01U;
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)24U, (U1)1U);

    if (u1_t_rxdata != u1_s_prehcsstpop) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_HCSSTPOP_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_HCSSTPOP, u1_t_rxdata);
        }
    }
    u1_s_prehcsstpop = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_TITE_BB(U4 * u4_ap_pdu_tx)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_TITE_BB(const U4 * u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_TITE_BB_MAX = (U1)0x0FU;
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)26U, (U1)4U);

    if (u1_t_rxdata != u1_s_pretite_bb) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_TITE_BB_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_TITE_BB, u1_t_rxdata);
        }
    }
    u1_s_pretite_bb = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_ADSEGDSW(U4 * u4_ap_pdu_tx)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_ADSEGDSW(const U4 * u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_ADSEGDSW_MAX = (U1)0x03U;
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[3], (U1)4U, (U1)2U);

    if (u1_t_rxdata != u1_s_preadsegdsw) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_ADSEGDSW_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_ADSEGDSW, u1_t_rxdata);
        }
    }
    u1_s_preadsegdsw = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_DPMS_BB(U4 * u4_ap_pdu_tx)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_DPMS_BB(const U4 * u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_DPMS_BB_MAX = (U1)0x01U;
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)16U, (U1)1U);

    if (u1_t_rxdata != u1_s_predpms_bb) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_DPMS_BB_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_DPMS_BB, u1_t_rxdata);
        }
    }
    u1_s_predpms_bb = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_POS_CALL(U4 * u4_ap_pdu_tx)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_POS_CALL(const U4 * u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_POS_CALL_MAX = (U1)0x03U;
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)18U, (U1)2U);

    if (u1_t_rxdata != u1_s_prepos_call) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_POS_CALL_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_POS_CALL, u1_t_rxdata);
        }
    }
    u1_s_prepos_call = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_POS_REG(U4 * u4_ap_pdu_tx)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_POS_REG(const U4 * u4_ap_pck_rx)
{
    static const U1 u1_s_XSPI_MET_POS_REG_MAX = (U1)0x03U;
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)22U, (U1)2U);

    if (u1_t_rxdata != u1_s_prepos_reg) {
        if (u1_t_rxdata <= u1_s_XSPI_MET_POS_REG_MAX) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_POS_REG, u1_t_rxdata);
        }
    }
    u1_s_prepos_reg = u1_t_rxdata;
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_FLYNOP(U4 * u4_ap_pdu_tx)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_FLYNOP(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)29U, (U1)2U);

    if (u1_t_rxdata != u1_s_preflynop) {
        vd_g_VdsCIReqTx((U1)VDS_CI_SW_FLYNOP, u1_t_rxdata);
    }
    u1_s_preflynop = u1_t_rxdata;
}
#endif   /* BEV Rebase provisionally */

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     8/22/2018  TA       New.                                                                                               */
/*  1.3.0    10/05/2020  KM       Change for 800B CV-R.                                                                              */
/*  1.4.0    12/21/2020  TN       Change for 800B 1A                                                                                 */
/*  1.5.0    05/17/2021  TN       Change for 300D/178D/893B CV.                                                                      */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  970B/200D/220D                                                                                                                   */
/*           07/18/2022  TN       New for 970B/200D/220D Pre1A base on 178D.                                                         */
/*  115D/117D/200D                                                                                                                   */
/*           08/30/2022  TN       Change for 115D/117D/200D 1A                                                                       */
/*  970B/850B                                                                                                                        */
/*           08/30/2022  TN       Change for 970B/850B 1A. HOFDIOPE Gateway Add.                                                     */
/*  130D HEV                                                                                                                         */
/*           04/04/2023  TN       DCLV Add. Change for 130D HEV MPT.                                                                 */
/*  19PFv3                                                                                                                           */
/*           02/19/2024  DR       Change for 19PFv3 TIMCHG                                                                           */
/*           02/20/2024  GM       Change config for 19PFv3 CV                                                                        */
/*           03/13/2024  PG       Delete vd_s_LcomSpiCfgTxSCL                                                                        */
/*           04/15/2024  SN       Change for 19PFv3 ADASCS                                                                           */
/*           04/23/2024  TR       Delete LCOM config functions of DK_DLSCT, SW_ITS01,                                                */
/*                                SW_ITS02, EMGONSW, CACONSW, SW_RSA01 and TSR_OSM                                                   */
/*           05/07/2024  TR       Delete LCOM config functions of DK_METDL and DK_DLCNL                                              */
/*           07/10/2024  YR       Added config for 19PFv3 HCS                                                                        */
/*  BEV                                                                                                                              */
/*           10/10/2024  KT       Change for BEV System_Consideration_1.(MET-B_OMRBB-CSTD-0-)                                        */
/*           01/30/2025  KO       Change for BEV System_Consideration_1.(MET-C_HCS-CSTD-0-)                                          */
/*           01/31/2025  MN       Change for BEV System_Consideration_1.(MET-B_PWLBB-CSTD-0-)                                        */
/*           01/31/2025  HY       Change for BEV System_Consideration_1.(MET-B_WPBB-CSTD-0-)                                         */
/*           02/10/2024  RO       Change for BEV System_Consideration_1.(MET-S_ADMID-CSTD-0-)                                        */
/*           02/10/2024  RO       Change for BEV System_Consideration_1.(MET-S_ADVMID-CSTD-0-)                                       */
/*           02/10/2025  HF       Change for BEV System_Consideration_1.(MET-B_LMPBB-CSTD-0-)                                        */
/*           02/10/2025  SF       Change for BEV System_Consideration_1.(MET-M_ONOFF-CSTD-1-02-A-C0)                                 */
/*           03/06/2025  HT       Change for BEV System_Consideration_1.(MET-B_WDICBB-CSTD-0-01-A-C0)                                */
/*           03/06/2025  HT       Change for BEV System_Consideration_1.(MET-B_TITEBB-CSTD-0-00-A-C0)                                */
/*           03/06/2025  HT       Change for BEV System_Consideration_1.(MET-B_MWBB-CSTD-0-00-A-C0)                                  */
/*           03/06/2025  HT       Change for BEV System_Consideration_1.(MET-S_ADBB-CSTD-0-01-A-C0)                                  */
/*           03/06/2025  HT       Change for BEV System_Consideration_1.(MET-C_HCSBSW-CSTD-0-01-A-C0)                                */
/*           05/14/2025  RO       Change for BEV EMC R.(MET-S_ADMID-CSTD-0-02-A-C0)                                                  */
/*           05/30/2025  SN(K)    Change for BEV System_Consideration_2.(MET-S_ADBB-CSTD-0-01-A-C0)                                  */
/*           06/13/2025  KO       Change for BEV System_Consideration_2.(MET-B_DRPBB-CSTD-0-01-A-C0)                                 */
/*           06/30/2025  KT       Change for BEV System_Consideration_2.(BEV3CDCMET-547/BEV3CDCMET-549)                              */
/*           07/07/2025  KT       Change for BEV System_Consideration_2.(CAN V7.3)                                                   */
/*           07/08/2025  TH       Change for BEV System_Consideration_2.(MET-C_HCSBSW-CSTD-0-02-A-C0)                                */
/*                                                                                                                                   */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*  * KM   = Keisuke Mashita, Denso Techno                                                                                           */
/*  * TN   = Tetsushi Nakano, Denso Techno                                                                                           */
/*  * DR   = Dyan Reyes, DTPH                                                                                                        */
/*  * GM   = Glen Monteposo, DTPH                                                                                                    */
/*  * PG   = Patrick Garcia, DTPH                                                                                                    */
/*  * SN   = Shimon Nambu, Denso Techno                                                                                              */
/*  * TR   = Tebs Ramos,     DTPH                                                                                                    */
/*  * YR   = Yhana Regalario, DTPH                                                                                                   */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*  * KO   = Kazuto Oishi,  Denso Techno                                                                                             */
/*  * MN   = Mikiya Negishi, KSE                                                                                                     */
/*  * HY   = Haruki Yagi, KSE                                                                                                        */
/*  * RO   = Ryo Oohashi, KSE                                                                                                        */
/*  * HF   = Hinari Fukamachi, KSE                                                                                                   */
/*  * SF   = Shiro Furui, Denso Techno                                                                                               */
/*  * HT   = Hibiki Tanii, KSE                                                                                                       */
/*  * SN(K)= Shizuka Nakajima, KSE                                                                                                   */
/*  * TH   = Taisuke Hirakawa, KSE                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
