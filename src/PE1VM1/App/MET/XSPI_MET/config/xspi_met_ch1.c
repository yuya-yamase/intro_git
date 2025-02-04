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

/* Platform */
/* #include "oxcan.h" */ /* @@@ Provisional for 310D PreCV @@@ */

#include "vds_ci.h"
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
#define XSPI_MMCUS_NUM_TXSIGNAL     (4U)
#define XSPI_METCUS_NUM_TXSIGNAL    (16U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_XSPI_MET_READ__BIT(u4_buf , u1_pos , u1_len) ((U1)((U1)((u4_buf)  >> (u1_pos)) & (U1)((1U << (u1_len)) - 1U)))
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U1                          u1_xspiid;
    U1                          u1_bitpos;
    U1                          u1_datalen;
    U1                          u1_maxvalue;
    U1                          u1_vdsci_id;
}ST_XSPI_TXSIG;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/  

static U1             u1_s_xspi_ethercomsts;
static U1             u1_s_xspi_mm2c100n_rxcnt;
static U1             u1_s_xspi_mm2c107n_rxcnt;
static U1             u1_s_xspi_mm2c112n_rxcnt;
static U1             u1_s_xspi_mm2c118n_rxcnt;
static U1             u1_s_xspi_mm2c124n_rxcnt;
static U1             u1_s_prebsmope;
static U1             u1_s_precsrmope;
static U1             u1_s_preacinvope;
static U1             u1_s_prekmmileope;
static U1             u1_s_prepfmautoope;
static U1             u1_s_prekpvclope;
static U1             u1_s_pretsmodedspope;
static U1             u1_s_prefcmusrbkope;
static U1             u1_s_prelcaprope;
static U1             u1_s_prevrctrlcanope;
static U1             u1_s_preplusswope;
static U1             u1_s_premetmdrej;           /* METMDREJ Previous RxValue */
static U1             u1_s_preldasw;              /* LDASW Previous RxValue    */
static U1             u1_s_prelda_sfb;            /* LDA_SFB Previous RxValue  */
static U1             u1_s_preldamcus;            /* LDAMCUS Previous RxValue  */
static U1             u1_s_prefcmmsw;             /* FCMMSW Previous RxValue   */
static U1             u1_s_prersr_tim;            /* RSR_TIM Previous RxValue  */
static U1             u1_s_prebsmm_ilv;           /* BSMM_ILV Previous RxValue */
static U1             u1_s_prepcsmsw;             /* PCSMSW Previous RxValue   */
static U1             u1_s_preidasesw;            /* IDASESW Previous RxValue  */
static U1             u1_s_preidamsw;             /* IDAMSW Previous RxValue   */
static U1             u1_s_prepkssvol;            /* PKSSVOL Previous RxValue  */
static U1             u1_s_prerctamsw;            /* RCTAMSW Previous RxValue  */
static U1             u1_s_presw_rcd01;           /* SW_RCD01 Previous RxValue */
static U1             u1_s_preicsmsw;             /* ICSMSW Previous RxValue   */
static U1             u1_s_pretrlc_yn;            /* TRLC_YN Previous RxValue  */
static U1             u1_s_prertan_tim;           /* RTAN_TIM Previous RxValue */
static U1             u1_s_prertan_msw;           /* RTAN_MSW Previous RxValue */
static U1             u1_s_presw_ltc01;           /* SW_LTC01 Previous RxValue */
static U1             u1_s_prelcasgmsw;           /* LCASGMSW Previous RxValue */
static U1             u1_s_presw_its04;           /* SW_ITS04 Previous RxValue */
static U1             u1_s_preaccracsw;           /* ACCRACSW Previous RxValue */
static U1             u1_s_preaccssosw;           /* ACCSSOSW Previous RxValue */
static U1             u1_s_preaccrossw;           /* ACCROSSW Previous RxValue */
static U1             u1_s_preaccaclsw;           /* ACCACLSW Previous RxValue */
static U1             u1_s_prectamsw;             /* CTAMSW Previous RxValue   */
static U1             u1_s_prepbdbzmvl;           /* PBDBZMVL Previous RxValue */
static U1             u1_s_prepbdmsw;             /* PBDMSW Previous RxValue   */
static U1             u1_s_prepbdksw;             /* PBDKSW Previous RxValue   */
static U1             u1_s_prepbdmcus;            /* PBDMCUS Previous RxValue  */
static U1             u1_s_pretpuntset;           /* TPUNTSET Previous RxValue */
static U1             u1_s_pretpinsel;            /* TPINSEL Previous RxValue  */
static U1             u1_s_pretpinself;           /* TPINSELF Previous RxValue */
static U1             u1_s_pretpinselr;           /* TPINSELR Previous RxValue */
static U1             u1_s_prersrmsw;             /* RSRMSW Previous RxValue   */
static U1             u1_s_prerscsw_op;           /* RSCSW_OP Previous RxValue */
static U1             u1_s_premintrsof;           /* MINTRSOF Previous RxValue */
static U1             u1_s_precsr_mute;           /* CSR_MUTE Previous RxValue */
static U1             u1_s_pretbwsw;              /* TBWSW Previous RxValue    */
static U1             u1_s_premetmspdi;           /* METMSPDI Previous RxValue */
static U1             u1_s_presrpmsw;             /* SRPMSW Previous RxValue   */
static U1             u1_s_preulkmsw;             /* ULKMSW Previous RxValue   */
static U1             u1_s_prelkmsw;              /* LKMSW Previous RxValue    */
static U1             u1_s_prergmdsw;             /* RG_MD_SW Previous RxValue */
static U1             u1_s_prerngmsw;             /* RNGMSW Previous RxValue   */
static U1             u1_sp_xspi_mmcus_pretxsig[XSPI_MMCUS_NUM_TXSIGNAL];
static U1             u1_sp_xspi_metcus_pretxsig[XSPI_METCUS_NUM_TXSIGNAL];

static U1             u1_s_prelddamsw;            /*  LDDAMSW Previous RxValue */
static U1             u1_s_prersa_nem;            /*  RSA_NEM Previous RxValue */
static U1             u1_s_prersa_lsm;            /*  RSA_LSM Previous RxValue */
static U1             u1_s_pretra_sw;             /*  TRA_SW Previous RxValue  */
static U1             u1_s_preermsw;              /*  ERMSW Previous RxValue   */
static U1             u1_s_preaccspmsw;           /*  ACCSPMSW Previous RxValue*/
static U1             u1_s_preaccgcrsw;           /*  ACCGCRSW Previous RxValue*/
static U1             u1_s_preccsmdmsw;           /*  CCSMDMSW Previous RxValue*/
static U1             u1_s_preslssosw;            /*  SLSSOSW Previous RxValue */
static U1             u1_s_prepmarsw;             /*  PMARSW Previous RxValue  */
static U1             u1_s_predoam_sw;            /*  DOAM_SW Previous RxValue */
static U1             u1_s_predoam_tim;           /*  DOAM_TIM Previous RxValue*/
static U1             u1_s_pretmnvsw;             /*  TMNVSW Previous RxValue  */
static U1             u1_s_pretmnssw;             /*  TMNSSW Previous RxValue  */
static U1             u1_s_preitssetsw;           /*  ITSSETSW Previous RxValue*/
static U1             u1_s_predissuisw;           /*  DISSUISW Previous RxValue*/
static U1             u1_s_predm_sw_a2;           /*  DM_SW_A2 Previous RxValue*/
static U1             u1_s_preahsswvsw;           /*  AHSSWVSW Previous RxValue*/
static U1             u1_s_preahssdesw;           /*  AHSSDESW Previous RxValue*/
static U1             u1_s_presw_as02;            /*  SW_AS02 Previous RxValue */
static U1             u1_s_presw_as01;            /*  SW_AS01 Previous RxValue */
static U1             u1_s_prem_bb;               /*  M_BB Previous RxValue    */
static U1             u1_s_premlr_bb;             /*  MLR_BB Previous RxValue  */
static U1             u1_s_prerlm_bb;             /*  RLM_BB Previous RxValue  */
static U1             u1_s_premrt_bb;             /*  MRT_BB Previous RxValue  */
static U1             u1_s_preart_bb;             /*  ART_BB Previous RxValue  */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static inline void    vd_s_XSpiCfgRxEther(const U4 * u4_ap_pck_rx);

static inline void    vd_s_XSpiCanTx_ASD_CONT(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_ASD_CANC(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_METSPDIS(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_FCMUSER(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_LCASGAPR(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_BSMMSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_CSRMSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_VRESTPSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_ACINVSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_PLUSSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_METMDREJ(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_LDASW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_LDA_SFB(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_LDAMCUS(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_FCMMSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_RSR_TIM(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_BSMM_ILV(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_PCSMSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_IDASESW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_IDAMSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_PKSSVOL(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_RCTAMSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_SW_RCD01(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_ICSMSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_TRLC_YN(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_RTAN_TIM(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_RTAN_MSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_SW_LTC01(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_LCASGMSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_SW_ITS04(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_ACCRACSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_ACCSSOSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_ACCROSSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_ACCACLSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_CTAMSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_PBDBZMVL(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_PBDMSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_PBDKSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_PBDMCUS(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_TPUNTSET(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_TPINSEL(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_TPINSELF(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_TPINSELR(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_RSRMSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_RSCSW_OP(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_MINTRSOF(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_CSR_MUTE(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_TBWSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_METMSPDI(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_SRPMSW(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_ULKMSW(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_LKMSW(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_RG_MD_SW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_RNGMSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_CANSignal(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_DOAM_TIM(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_DOAM_SW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_LDAAMSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_RSA_NEM(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_RSA_LSM(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_TRA_SW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_ERMSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_ACCSPMSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_ACCGCRSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_CCSMDMSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_SLSSOSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_PMARSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_TMNVSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_TMNSSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_ITSSETSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_DISSUISW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_DM_SW_A2(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_AHSSWVSW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_AHSSDESW(const U4 * u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_SW_AS02(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_SW_AS01(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_M_BB(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_MLR_BB(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_RLM_BB(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_MRT_BB(const U4* u4_ap_pck_rx);
static inline void    vd_s_XSpiCanTx_ART_BB(const U4* u4_ap_pck_rx);
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
    U1  u1_t_loop;

    u1_s_xspi_ethercomsts = (U1)XSPI_ETHER_UNDEF2;
    u1_s_xspi_mm2c100n_rxcnt = (U1)0U;
    u1_s_xspi_mm2c107n_rxcnt = (U1)0U;
    u1_s_xspi_mm2c112n_rxcnt = (U1)0U;
    u1_s_xspi_mm2c118n_rxcnt = (U1)0U;
    u1_s_xspi_mm2c124n_rxcnt = (U1)0U;
    u1_s_prebsmope = (U1)0U;
    u1_s_precsrmope = (U1)0U;
    u1_s_preacinvope = (U1)0U;
    u1_s_prekmmileope = (U1)0U;
    u1_s_prepfmautoope = (U1)0U;
    u1_s_prekpvclope = (U1)0U;
    u1_s_pretsmodedspope = (U1)0U;
    u1_s_prefcmusrbkope = (U1)0U;
    u1_s_prelcaprope = (U1)0U;
    u1_s_prevrctrlcanope = (U1)0U;
    u1_s_preplusswope = (U1)0U;
    u1_s_premetmdrej = (U1)0U;
    u1_s_preldasw = (U1)0U;
    u1_s_prelda_sfb = (U1)0U;
    u1_s_preldamcus = (U1)0U;
    u1_s_prefcmmsw = (U1)0U;
    u1_s_prersr_tim = (U1)0U;
    u1_s_prebsmm_ilv = (U1)0U;
    u1_s_prepcsmsw = (U1)0U;
    u1_s_preidasesw = (U1)0U;
    u1_s_preidamsw = (U1)0U;
    u1_s_prepkssvol = (U1)0U;
    u1_s_prerctamsw = (U1)0U;
    u1_s_presw_rcd01 = (U1)0U;
    u1_s_preicsmsw = (U1)0U;
    u1_s_pretrlc_yn = (U1)0U;
    u1_s_prertan_tim = (U1)0U;
    u1_s_prertan_msw = (U1)0U;
    u1_s_presw_ltc01 = (U1)0U;
    u1_s_prelcasgmsw = (U1)0U;
    u1_s_presw_its04 = (U1)0U;
    u1_s_preaccracsw = (U1)0U;
    u1_s_preaccssosw = (U1)0U;
    u1_s_preaccrossw = (U1)0U;
    u1_s_preaccaclsw = (U1)0U;
    u1_s_prectamsw = (U1)0U;
    u1_s_prepbdbzmvl = (U1)0U;
    u1_s_prepbdmsw = (U1)0U;
    u1_s_prepbdksw = (U1)0U;
    u1_s_prepbdmcus = (U1)0U;
    u1_s_pretpuntset = (U1)0U;
    u1_s_pretpinsel = (U1)0U;
    u1_s_pretpinself = (U1)0U;
    u1_s_pretpinselr = (U1)0U;
    u1_s_prersrmsw = (U1)0U;
    u1_s_prerscsw_op = (U1)0U;
    u1_s_premintrsof = (U1)0U;
    u1_s_precsr_mute = (U1)0U;
    u1_s_pretbwsw = (U1)0U;
    u1_s_premetmspdi = (U1)0U;
    u1_s_presrpmsw   = (U1)0U;
    u1_s_preulkmsw = (U1)0U;
    u1_s_prelkmsw = (U1)0U;
    u1_s_prergmdsw = (U1)0U;
    u1_s_prerngmsw = (U1)0U;
    u1_s_prersa_nem = (U1)0U;
    u1_s_prersa_lsm = (U1)0U;
    u1_s_pretra_sw = (U1)0U;
    u1_s_preermsw = (U1)0U;
    u1_s_preaccspmsw = (U1)0U;
    u1_s_preaccgcrsw = (U1)0U;
    u1_s_preccsmdmsw = (U1)0U;
    u1_s_preslssosw = (U1)0U;
    u1_s_prepmarsw = (U1)0U;
    u1_s_predoam_sw = (U1)0U;
    u1_s_predoam_tim = (U1)0U;
    u1_s_pretmnvsw = (U1)0U;
    u1_s_pretmnssw = (U1)0U;
    u1_s_preitssetsw = (U1)0U;
    u1_s_predissuisw = (U1)0U;
    u1_s_predm_sw_a2 = (U1)0U;
    u1_s_preahsswvsw = (U1)0U;
    u1_s_preahssdesw = (U1)0U;
    u1_s_prelddamsw  = (U1)0U;
    u1_s_presw_as02  = (U1)0U;
    u1_s_presw_as01  = (U1)0U;
    u1_s_prem_bb     = (U1)0U;
    u1_s_premlr_bb   = (U1)0U;
    u1_s_prerlm_bb   = (U1)0U;
    u1_s_premrt_bb   = (U1)0U;
    u1_s_preart_bb   = (U1)0U;

    for (u1_t_loop = (U1)0U; u1_t_loop < (U1)XSPI_MMCUS_NUM_TXSIGNAL; u1_t_loop++) {
        u1_sp_xspi_mmcus_pretxsig[u1_t_loop] = (U1)0U;
    }
    for (u1_t_loop = (U1)0U; u1_t_loop < (U1)XSPI_METCUS_NUM_TXSIGNAL; u1_t_loop++) {
        u1_sp_xspi_metcus_pretxsig[u1_t_loop] = (U1)0U;
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_XSpiCfgPduRxCh1(const U4 * u4_ap_PDU_RX)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiCfgPduRxCh1(const U4 * u4_ap_PDU_RX)
{
    vd_s_XSpiCfgRxEther(&u4_ap_PDU_RX[100]);

    vd_s_XSpiCanTx_CANSignal(&u4_ap_PDU_RX[15]);
    vd_s_XSpiCanTx_ASD_CONT(&u4_ap_PDU_RX[35]);
    vd_s_XSpiCanTx_ASD_CANC(&u4_ap_PDU_RX[35]);
    vd_s_XSpiCanTx_METSPDIS(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_FCMUSER(&u4_ap_PDU_RX[29]);
    vd_s_XSpiCanTx_LCASGAPR(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_BSMMSW(&u4_ap_PDU_RX[29]);
    vd_s_XSpiCanTx_CSRMSW(&u4_ap_PDU_RX[29]);
    vd_s_XSpiCanTx_VRESTPSW(&u4_ap_PDU_RX[35]);
    vd_s_XSpiCanTx_ACINVSW(&u4_ap_PDU_RX[31]);
    vd_s_XSpiCanTx_PLUSSW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_METMDREJ(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_LDASW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_LDA_SFB(&u4_ap_PDU_RX[29]);
    vd_s_XSpiCanTx_LDAMCUS(&u4_ap_PDU_RX[29]);
    vd_s_XSpiCanTx_FCMMSW(&u4_ap_PDU_RX[29]);
    vd_s_XSpiCanTx_RSR_TIM(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_BSMM_ILV(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_PCSMSW(&u4_ap_PDU_RX[29]);
    vd_s_XSpiCanTx_IDASESW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_IDAMSW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_PKSSVOL(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_RCTAMSW(&u4_ap_PDU_RX[29]);
    vd_s_XSpiCanTx_SW_RCD01(&u4_ap_PDU_RX[29]);
    vd_s_XSpiCanTx_ICSMSW(&u4_ap_PDU_RX[29]);
    vd_s_XSpiCanTx_DOAM_TIM(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_DOAM_SW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_TRLC_YN(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_RTAN_TIM(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_RTAN_MSW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_SW_LTC01(&u4_ap_PDU_RX[29]);
    vd_s_XSpiCanTx_LCASGMSW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_SW_ITS04(&u4_ap_PDU_RX[29]);
    vd_s_XSpiCanTx_ACCRACSW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_ACCSSOSW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_ACCROSSW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_ACCACLSW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_CTAMSW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_PBDBZMVL(&u4_ap_PDU_RX[35]);
    vd_s_XSpiCanTx_PBDMSW(&u4_ap_PDU_RX[35]);
    vd_s_XSpiCanTx_PBDKSW(&u4_ap_PDU_RX[35]);
    vd_s_XSpiCanTx_PBDMCUS(&u4_ap_PDU_RX[35]);
    vd_s_XSpiCanTx_TPUNTSET(&u4_ap_PDU_RX[33]);
    vd_s_XSpiCanTx_TPINSEL(&u4_ap_PDU_RX[33]);
    vd_s_XSpiCanTx_TPINSELF(&u4_ap_PDU_RX[33]);
    vd_s_XSpiCanTx_TPINSELR(&u4_ap_PDU_RX[33]);
    vd_s_XSpiCanTx_RG_MD_SW(&u4_ap_PDU_RX[23]);
    vd_s_XSpiCanTx_RNGMSW(&u4_ap_PDU_RX[49]);
    vd_s_XSpiCanTx_RSRMSW(&u4_ap_PDU_RX[35]);
    vd_s_XSpiCanTx_MINTRSOF(&u4_ap_PDU_RX[35]);
    vd_s_XSpiCanTx_CSR_MUTE(&u4_ap_PDU_RX[29]);
    vd_s_XSpiCanTx_TBWSW(&u4_ap_PDU_RX[49]);
    vd_s_XSpiCanTx_METMSPDI(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_SRPMSW(&u4_ap_PDU_RX[35]);	
    vd_s_XSpiCanTx_ULKMSW(&u4_ap_PDU_RX[35]);
    vd_s_XSpiCanTx_LKMSW(&u4_ap_PDU_RX[35]);
    vd_s_XSpiCanTx_LDAAMSW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_RSA_NEM(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_RSA_LSM(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_TRA_SW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_ERMSW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_ACCSPMSW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_ACCGCRSW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_CCSMDMSW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_SLSSOSW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_PMARSW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_TMNVSW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_TMNSSW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_ITSSETSW(&u4_ap_PDU_RX[29]);
    vd_s_XSpiCanTx_DISSUISW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_DM_SW_A2(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_AHSSWVSW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_AHSSDESW(&u4_ap_PDU_RX[51]);
    vd_s_XSpiCanTx_RSCSW_OP(&u4_ap_PDU_RX[31]);
    vd_s_XSpiCanTx_SW_AS02(&u4_ap_PDU_RX[33]);
    vd_s_XSpiCanTx_SW_AS01(&u4_ap_PDU_RX[33]);
    vd_s_XSpiCanTx_M_BB(&u4_ap_PDU_RX[35]);
    vd_s_XSpiCanTx_MLR_BB(&u4_ap_PDU_RX[35]);
    vd_s_XSpiCanTx_RLM_BB(&u4_ap_PDU_RX[35]);
    vd_s_XSpiCanTx_MRT_BB(&u4_ap_PDU_RX[35]);
    vd_s_XSpiCanTx_ART_BB(&u4_ap_PDU_RX[35]);

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
/*===================================================================================================================================*/
/*  U1    u1_g_XSpiEtherComSts(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_s_xspi_ethercomsts                                                                                            */
/*===================================================================================================================================*/
U1    u1_g_XSpiEtherComSts(void){
    return(u1_s_xspi_ethercomsts);
}
/*===================================================================================================================================*/
/*  U1    u1_g_XSpiMm2c100n_rxcnt(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_s_xspi_mm2c100n_rxcnt                                                                                         */
/*===================================================================================================================================*/
U1    u1_g_XSpiMm2c100n_rxcnt(void){
    return(u1_s_xspi_mm2c100n_rxcnt);
}
/*===================================================================================================================================*/
/*  U1    u1_g_XSpiMm2c107n_rxcnt(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_s_xspi_mm2c107n_rxcnt                                                                                         */
/*===================================================================================================================================*/
U1    u1_g_XSpiMm2c107n_rxcnt(void){
    return(u1_s_xspi_mm2c107n_rxcnt);
}
/*===================================================================================================================================*/
/*  U1    u1_g_XSpiMm2c112n_rxcnt(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_s_xspi_mm2c112n_rxcnt                                                                                         */
/*===================================================================================================================================*/
U1    u1_g_XSpiMm2c112n_rxcnt(void){
    return(u1_s_xspi_mm2c112n_rxcnt);
}
/*===================================================================================================================================*/
/*  U1    u1_g_XSpiMm2c118n_rxcnt(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_s_xspi_mm2c118n_rxcnt                                                                                         */
/*===================================================================================================================================*/
U1    u1_g_XSpiMm2c118n_rxcnt(void){
    return(u1_s_xspi_mm2c118n_rxcnt);
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_ASD_CONT(U4 * u4_ap_pdu_tx)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_ASD_CONT(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_rxdata;
    U1 u1_t_asdcont;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)24U, (U1)1U);

    if((u1_t_rxdata == (U1)1U) && (u1_t_rxdata != u1_s_prepfmautoope)){
        u1_t_asdcont = (U1)1U;
        vd_g_VdsCIReqTx((U1)VDS_CI_SW_ASD_CONT, u1_t_asdcont);
    } else if ((u1_t_rxdata == (U1)0U) && (u1_t_rxdata != u1_s_prepfmautoope)) {
        u1_t_asdcont = (U1)0U;
        vd_g_VdsCIReqTx((U1)VDS_CI_SW_ASD_CONT, u1_t_asdcont);
    } else {
        /* Do Nothing */
    }
    u1_s_prepfmautoope = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_ASD_CANC(U4 * u4_ap_pdu_tx)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_ASD_CANC(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_rxdata;
    U1 u1_t_asdcanc;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)25U, (U1)1U);

    if((u1_t_rxdata == (U1)1U) && (u1_t_rxdata != u1_s_prekpvclope)){
        u1_t_asdcanc = (U1)1U;
        vd_g_VdsCIReqTx((U1)VDS_CI_SW_ASD_CANC, u1_t_asdcanc);
    } else if ((u1_t_rxdata == (U1)0U) && (u1_t_rxdata != u1_s_prekpvclope)) {
        u1_t_asdcanc = (U1)0U;
        vd_g_VdsCIReqTx((U1)VDS_CI_SW_ASD_CANC, u1_t_asdcanc);
    } else {
        /* Do Nothing */
    }
    u1_s_prekpvclope = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_METSPDIS(U4 * u4_ap_pdu_tx)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_METSPDIS(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_rxdata;
    U1 u1_t_metspdis;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)31U, (U1)1U);

    if((u1_t_rxdata == (U1)1U) && (u1_t_rxdata != u1_s_pretsmodedspope)){
        u1_t_metspdis = (U1)1U;
        vd_g_VdsCIReqTx((U1)VDS_CI_SW_METSPDIS, u1_t_metspdis);
    } else if ((u1_t_rxdata == (U1)0U) && (u1_t_rxdata != u1_s_pretsmodedspope)) {
        u1_t_metspdis = (U1)0U;
        vd_g_VdsCIReqTx((U1)VDS_CI_SW_METSPDIS, u1_t_metspdis);
    } else {
        /* Do Nothing */
    }
    u1_s_pretsmodedspope = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_FCMUSER(U4 * u4_ap_pdu_tx)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_FCMUSER(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_rxdata;
    U1 u1_t_fcmusr;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)3U, (U1)1U);

    if((u1_t_rxdata == (U1)1U) && (u1_t_rxdata != u1_s_prefcmusrbkope)){
        u1_t_fcmusr = (U1)1U;
        vd_g_VdsCIReqTx((U1)VDS_CI_SW_FCMUSER, u1_t_fcmusr);
    } else if ((u1_t_rxdata == (U1)0U) && (u1_t_rxdata != u1_s_prefcmusrbkope)) {
        u1_t_fcmusr = (U1)0U;
        vd_g_VdsCIReqTx((U1)VDS_CI_SW_FCMUSER, u1_t_fcmusr);
    } else {
        /* Do Nothing */
    }
    u1_s_prefcmusrbkope = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_LCASGAPR(U4 * u4_ap_pdu_tx)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_LCASGAPR(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_rxdata;
    U1 u1_t_lcasgapr;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)26U, (U1)2U);

    if((u1_t_rxdata == (U1)1U) && (u1_t_rxdata != u1_s_prelcaprope)){
        u1_t_lcasgapr = (U1)1U;
        vd_g_VdsCIReqTx((U1)VDS_CI_SW_LCASGAPR, u1_t_lcasgapr);
    } else if ((u1_t_rxdata == (U1)2U) && (u1_t_rxdata != u1_s_prelcaprope)) {
        u1_t_lcasgapr = (U1)2U;
        vd_g_VdsCIReqTx((U1)VDS_CI_SW_LCASGAPR, u1_t_lcasgapr);
    } else if ((u1_t_rxdata == (U1)0U) && (u1_t_rxdata != u1_s_prelcaprope)) {
        u1_t_lcasgapr = (U1)0U;
        vd_g_VdsCIReqTx((U1)VDS_CI_SW_LCASGAPR, u1_t_lcasgapr);
    } else {
        /* Do Nothing */
    }
    u1_s_prelcaprope = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_BSMMSW(U4 * u4_ap_pdu_tx)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_BSMMSW(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_rxdata;
    U1 u1_t_mmsup;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)29U, (U1)1U);
    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);

    if(u1_t_mmsup == (U1)TRUE){
        if((u1_t_rxdata == (U1)1U) && (u1_t_rxdata != u1_s_prebsmope)){
            vd_g_GatewaymmDrvmdPut((U1)GATEWAY_MM_BSMM_SW, (U1)1U);
        } else if ((u1_t_rxdata == (U1)0U) && (u1_t_rxdata != u1_s_prebsmope)) {
            vd_g_GatewaymmDrvmdPut((U1)GATEWAY_MM_BSMM_SW, (U1)0U);
        } else {
            /* Do Nothing */
        }
    }
    else{
        if(u1_t_rxdata != u1_s_prebsmope){
            if(u1_t_rxdata <= (U1)1U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_BSMMSW, u1_t_rxdata);
            }
        }
    }
    u1_s_prebsmope = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_CSRMSW(U4 * u4_ap_pdu_tx)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_CSRMSW(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_rxdata;
    U1 u1_t_mmsup;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)26U, (U1)1U);
    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);

    if(u1_t_mmsup == (U1)TRUE){
        if((u1_t_rxdata == (U1)1U) && (u1_t_rxdata != u1_s_precsrmope)){
            vd_g_GatewaymmDrvmdPut((U1)GATEWAY_MM_CSRM_SW, (U1)1U);
        } else if ((u1_t_rxdata == (U1)0U) && (u1_t_rxdata != u1_s_precsrmope)) {
            vd_g_GatewaymmDrvmdPut((U1)GATEWAY_MM_CSRM_SW, (U1)0U);
        } else {
            /* Do Nothing */
        }
    }
    else{
        if(u1_t_rxdata != u1_s_precsrmope){
            if(u1_t_rxdata <= (U1)1U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_CSRMSW, u1_t_rxdata);
            }
        }
    }
    u1_s_precsrmope = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_VRESTPSW(U4 * u4_ap_pdu_tx)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_VRESTPSW(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_rxdata;
    U1 u1_t_vrestp;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)7U, (U1)1U);

    if((u1_t_rxdata == (U1)1U) && (u1_t_rxdata != u1_s_prevrctrlcanope)){
        u1_t_vrestp = (U1)1U;
        vd_g_VdsCIReqTx((U1)VDS_CI_SW_VRESTPSW, u1_t_vrestp);
    } else if ((u1_t_rxdata == (U1)0U) && (u1_t_rxdata != u1_s_prevrctrlcanope)) {
        u1_t_vrestp = (U1)0U;
        vd_g_VdsCIReqTx((U1)VDS_CI_SW_VRESTPSW, u1_t_vrestp);
    } else {
        /* Do Nothing */
    }
    u1_s_prevrctrlcanope = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_ACINVSW(U4 * u4_ap_pdu_tx)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_ACINVSW(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_rxdata;
    U1 u1_t_mmsup;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)31U, (U1)1U);
    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);

    if(u1_t_mmsup == (U1)TRUE){
        if((u1_t_rxdata == (U1)1U) && (u1_t_rxdata != u1_s_preacinvope)){
            vd_g_GatewaymmDrvmdPut((U1)GATEWAY_MM_ACINV_SW, (U1)1U);
        } else if ((u1_t_rxdata == (U1)0U) && (u1_t_rxdata != u1_s_preacinvope)) {
            vd_g_GatewaymmDrvmdPut((U1)GATEWAY_MM_ACINV_SW, (U1)0U);
        } else {
            /* Do Nothing */
        }
    }
    else{
        if(u1_t_rxdata != u1_s_preacinvope){
            if(u1_t_rxdata <= (U1)1U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_ACINV_SW, u1_t_rxdata);
            }
        }
    }
    u1_s_preacinvope = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_PLUSSW(U4 * u4_ap_pdu_tx)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_PLUSSW(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_rxdata;
    U1 u1_t_plussw;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)0U, (U1)1U);

    if((u1_t_rxdata == (U1)1U) && (u1_t_rxdata != u1_s_preplusswope)){
        u1_t_plussw = (U1)1U;
        vd_g_VdsCIReqTx((U1)VDS_CI_SW_PLUSSW, u1_t_plussw);
    } else if ((u1_t_rxdata == (U1)0U) && (u1_t_rxdata != u1_s_preplusswope)) {
        u1_t_plussw = (U1)0U;
        vd_g_VdsCIReqTx((U1)VDS_CI_SW_PLUSSW, u1_t_plussw);
    } else {
        /* Do Nothing */
    }
    u1_s_preplusswope = u1_t_rxdata;

}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_METMDREJ(U4 * u4_ap_pdu_tx)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_METMDREJ(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[5], (U1)11U, (U1)1U);

    if(u1_t_rxdata != u1_s_premetmdrej){
        if(u1_t_rxdata <= (U1)1U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_METMDREJ, u1_t_rxdata);
        }
    }
    u1_s_premetmdrej = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_LDASW(const U4 * u4_ap_pdu_rx)                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_LDASW(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)8U, (U1)1U);

        if(u1_t_rxdata != u1_s_preldasw){
            if(u1_t_rxdata <= (U1)1U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_LDASW, u1_t_rxdata);
            }
        }
        u1_s_preldasw = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_LDA_SFB(const U4 * u4_ap_pdu_rx)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_LDA_SFB(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)8U, (U1)3U);

        if(u1_t_rxdata != u1_s_prelda_sfb){
            if((u1_t_rxdata <= (U1)7U) && (u1_t_rxdata != (U1)2U) && (u1_t_rxdata != (U1)3U)
            && (u1_t_rxdata != (U1)5U) && (u1_t_rxdata != (U1)6U)){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_LDA_SFB, u1_t_rxdata);
            }
        }
        u1_s_prelda_sfb = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_LDAMCUS(const U4 * u4_ap_pdu_rx)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_LDAMCUS(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)22U, (U1)2U);

        if(u1_t_rxdata != u1_s_preldamcus){
            if(u1_t_rxdata <= (U1)3U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_LDAMCUS, u1_t_rxdata);
            }
        }
        u1_s_preldamcus = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_FCMMSW(const U4 * u4_ap_pdu_rx)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_FCMMSW(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)12U, (U1)1U);

        if(u1_t_rxdata != u1_s_prefcmmsw){
            if(u1_t_rxdata <= (U1)1U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_FCMMSW, u1_t_rxdata);
            }
        }
        u1_s_prefcmmsw = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_RSR_TIM(const U4 * u4_ap_pdu_rx)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_RSR_TIM(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)13U, (U1)3U);

        if(u1_t_rxdata != u1_s_prersr_tim){
            if(u1_t_rxdata <= (U1)3U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_RSR_TIM, u1_t_rxdata);
            }
        }
        u1_s_prersr_tim = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_BSMM_ILV(const U4 * u4_ap_pdu_rx)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_BSMM_ILV(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)4U, (U1)2U);

        if(u1_t_rxdata != u1_s_prebsmm_ilv){
            if(u1_t_rxdata <= (U1)2U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_BSMM_ILV, u1_t_rxdata);
            }
        }
        u1_s_prebsmm_ilv = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_PCSMSW(const U4 * u4_ap_pdu_rx)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_PCSMSW(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)16U, (U1)1U);

        if(u1_t_rxdata != u1_s_prepcsmsw){
            if(u1_t_rxdata <= (U1)1U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_PCSMSW, u1_t_rxdata);
            }
        }
        u1_s_prepcsmsw = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_IDASESW(const U4 * u4_ap_pdu_rx)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_IDASESW(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)20U, (U1)2U);

        if(u1_t_rxdata != u1_s_preidasesw){
            if(u1_t_rxdata <= (U1)3U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_IDASESW, u1_t_rxdata);
            }
        }
        u1_s_preidasesw = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_IDAMSW(const U4 * u4_ap_pdu_rx)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_IDAMSW(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)22U, (U1)1U);

        if(u1_t_rxdata != u1_s_preidamsw){
            if(u1_t_rxdata <= (U1)1U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_IDAMSW, u1_t_rxdata);
            }
        }
        u1_s_preidamsw = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_PKSSVOL(const U4 * u4_ap_pdu_rx)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_PKSSVOL(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)9U, (U1)2U);

    if(u1_t_rxdata != u1_s_prepkssvol){
        if(u1_t_rxdata <= (U1)3U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_PKSSVOL, u1_t_rxdata);
        }
    }
    u1_s_prepkssvol = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_RCTAMSW(const U4 * u4_ap_pdu_rx)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_RCTAMSW(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)31U, (U1)1U);

        if(u1_t_rxdata != u1_s_prerctamsw){
            if(u1_t_rxdata <= (U1)1U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_RCTAMSW, u1_t_rxdata);
            }
        }
        u1_s_prerctamsw = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_SW_RCD01(const U4 * u4_ap_pdu_rx)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_SW_RCD01(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)24U, (U1)1U);

        if(u1_t_rxdata != u1_s_presw_rcd01){
            if(u1_t_rxdata <= (U1)1U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_SW_RCD01, u1_t_rxdata);
            }
        }
        u1_s_presw_rcd01 = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_ICSMSW(const U4 * u4_ap_pdu_rx)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_ICSMSW(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)30U, (U1)1U);

        if(u1_t_rxdata != u1_s_preicsmsw){
            if(u1_t_rxdata <= (U1)1U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_ICSMSW, u1_t_rxdata);
            }
        }
        u1_s_preicsmsw = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_TRLC_YN(const U4 * u4_ap_pdu_rx)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_TRLC_YN(const U4* u4_ap_pck_rx)
{
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[5], (U1)4U, (U1)3U);

    if (u1_t_rxdata != u1_s_pretrlc_yn) {
        if (u1_t_rxdata <= (U1)2U) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_TRLC_YN, u1_t_rxdata);
        }
    }
    u1_s_pretrlc_yn = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_RTAN_TIM(const U4 * u4_ap_pdu_rx)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_RTAN_TIM(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)2U, (U1)2U);

        if(u1_t_rxdata != u1_s_prertan_tim){
            if(u1_t_rxdata <= (U1)3U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_RTAN_TIM, u1_t_rxdata);
            }
        }
        u1_s_prertan_tim = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_RTAN_MSW(const U4 * u4_ap_pdu_rx)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_RTAN_MSW(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)1U, (U1)1U);

        if(u1_t_rxdata != u1_s_prertan_msw){
            if(u1_t_rxdata <= (U1)1U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_RTAN_MSW, u1_t_rxdata);
            }
        }
        u1_s_prertan_msw = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_SW_LTC01(const U4 * u4_ap_pdu_rx)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_SW_LTC01(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)26U, (U1)1U);

        if(u1_t_rxdata != u1_s_presw_ltc01){
            if(u1_t_rxdata <= (U1)1U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_SW_LTC01, u1_t_rxdata);
            }
        }
        u1_s_presw_ltc01 = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_LCASGMSW(const U4 * u4_ap_pdu_rx)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_LCASGMSW(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)29U, (U1)1U);

        if(u1_t_rxdata != u1_s_prelcasgmsw){
            if(u1_t_rxdata <= (U1)1U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_LCASGMSW, u1_t_rxdata);
            }
        }
        u1_s_prelcasgmsw = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_SW_ITS04(const U4 * u4_ap_pdu_rx)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_SW_ITS04(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)25U, (U1)1U);

        if(u1_t_rxdata != u1_s_presw_its04){
            if(u1_t_rxdata <= (U1)1U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_SW_ITS04, u1_t_rxdata);
            }
        }
        u1_s_presw_its04 = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_ACCRACSW(const U4 * u4_ap_pdu_rx)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_ACCRACSW(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[4], (U1)21U, (U1)1U);

        if(u1_t_rxdata != u1_s_preaccracsw){
            if(u1_t_rxdata <= (U1)1U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_ACCRACSW, u1_t_rxdata);
            }
        }
        u1_s_preaccracsw = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_ACCSSOSW(const U4 * u4_ap_pdu_rx)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_ACCSSOSW(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[4], (U1)22U, (U1)2U);

        if(u1_t_rxdata != u1_s_preaccssosw){
            if(u1_t_rxdata <= (U1)2U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_ACCSSOSW, u1_t_rxdata);
            }
        }
        u1_s_preaccssosw = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_ACCROSSW(const U4 * u4_ap_pdu_rx)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_ACCROSSW(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[4], (U1)19U, (U1)1U);

        if(u1_t_rxdata != u1_s_preaccrossw){
            if(u1_t_rxdata <= (U1)1U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_ACCROSSW, u1_t_rxdata);
            }
        }
        u1_s_preaccrossw = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_ACCACLSW(const U4 * u4_ap_pdu_rx)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_ACCACLSW(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[4], (U1)13U, (U1)3U);

        if(u1_t_rxdata != u1_s_preaccaclsw){
            if((u1_t_rxdata <= (U1)4U) && (u1_t_rxdata != (U1)1U)){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_ACCACLSW, u1_t_rxdata);
            }
        }
        u1_s_preaccaclsw = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_CTAMSW(const U4 * u4_ap_pdu_rx)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_CTAMSW(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[5], (U1)21U, (U1)1U);

        if(u1_t_rxdata != u1_s_prectamsw){
            if(u1_t_rxdata <= (U1)1U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_CTAMSW, u1_t_rxdata);
            }
        }
        u1_s_prectamsw = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_PBDBZMVL(const U4 * u4_ap_pdu_rx)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_PBDBZMVL(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)20U, (U1)2U);

    if(u1_t_rxdata != u1_s_prepbdbzmvl){
        if(u1_t_rxdata <= (U1)3U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_PBDBZMVL, u1_t_rxdata);
        }
    }
    u1_s_prepbdbzmvl = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_PBDMSW(const U4 * u4_ap_pdu_rx)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_PBDMSW(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)15U, (U1)1U);

    if(u1_t_rxdata != u1_s_prepbdmsw){
        if(u1_t_rxdata <= (U1)1U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_PBDMSW, u1_t_rxdata);
        }
    }
    u1_s_prepbdmsw = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_PBDKSW(const U4 * u4_ap_pdu_rx)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_PBDKSW(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)30U, (U1)1U);

    if(u1_t_rxdata != u1_s_prepbdksw){
        if(u1_t_rxdata <= (U1)1U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_PBDKSW, u1_t_rxdata);
        }
    }
    u1_s_prepbdksw = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_PBDMCUS(const U4 * u4_ap_pdu_rx)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_PBDMCUS(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)12U, (U1)3U);

    if(u1_t_rxdata != u1_s_prepbdmcus){
        if((u1_t_rxdata <= (U1)7U) && (u1_t_rxdata != (U1)6U)){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_PBDMCUS, u1_t_rxdata);
        }
    }
    u1_s_prepbdmcus = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_TPUNTSET(const U4 * u4_ap_pdu_rx)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_TPUNTSET(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)21U, (U1)3U);

        if(u1_t_rxdata != u1_s_pretpuntset){
            if(u1_t_rxdata <= (U1)3U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_TPUNTSET, u1_t_rxdata);
            }
        }
        u1_s_pretpuntset = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_TPINSEL(const U4 * u4_ap_pdu_rx)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_TPINSEL(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)16U, (U1)4U);

        if(u1_t_rxdata != u1_s_pretpinsel){
            if((u1_t_rxdata <= (U1)7U) && (u1_t_rxdata != (U1)2U)){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_TPINSEL, u1_t_rxdata);
            }
        }
        u1_s_pretpinsel = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_TPINSELF(const U4 * u4_ap_pdu_rx)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_TPINSELF(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)8U, (U1)3U);

        if(u1_t_rxdata != u1_s_pretpinself){
            if(u1_t_rxdata <= (U1)6U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_TPINSELF, u1_t_rxdata);
            }
        }
        u1_s_pretpinself = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_TPINSELR(const U4 * u4_ap_pdu_rx)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_TPINSELR(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)12U, (U1)3U);

        if(u1_t_rxdata != u1_s_pretpinselr){
            if(u1_t_rxdata <= (U1)6U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_TPINSELR, u1_t_rxdata);
            }
        }
        u1_s_pretpinselr = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_RSRMSW(const U4 * u4_ap_pdu_rx)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_RSRMSW(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)23U, (U1)1U);

    if(u1_t_rxdata != u1_s_prersrmsw){
        if(u1_t_rxdata <= (U1)1U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_RSRMSW, u1_t_rxdata);
        }
    }
    u1_s_prersrmsw = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_RSCSW_OP(const U4 * u4_ap_pdu_rx)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_RSCSW_OP(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)16U, (U1)1U);

        if(u1_t_rxdata != u1_s_prerscsw_op){
            if(u1_t_rxdata <= (U1)1U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_RSCSW_OP, u1_t_rxdata);
            }
        }
        u1_s_prerscsw_op = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_MINTRSOF(const U4 * u4_ap_pdu_rx)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_MINTRSOF(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_mmsup;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)31U, (U1)1U);

        if(u1_t_rxdata != u1_s_premintrsof){
            if(u1_t_rxdata <= (U1)1U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_MINTRSOF, u1_t_rxdata);
            }
        }
        u1_s_premintrsof = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_CSR_MUTE(const U4 * u4_ap_pdu_rx)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_CSR_MUTE(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)31U, (U1)1U);

    if(u1_t_rxdata != u1_s_precsr_mute){
        if(u1_t_rxdata <= (U1)1U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_CSR_MUTE, u1_t_rxdata);
        }
    }
    u1_s_precsr_mute = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_TBWSW(U4 * u4_ap_pdu_tx)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_TBWSW(const U4 * u4_ap_pck_rx)
{
    U1  u1_t_mmsup;
    U1  u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)16U, (U1)1U);

        if(u1_t_rxdata != u1_s_pretbwsw){
            if(u1_t_rxdata <= (U1)1U){
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_TBWSW, u1_t_rxdata);
            }
        }
        u1_s_pretbwsw = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_METMSPDI(U4 * u4_ap_pdu_tx)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_METMSPDI(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[5], (U1)19U, (U1)1U);

    if(u1_t_rxdata != u1_s_premetmspdi){
        if(u1_t_rxdata <= (U1)1U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_METMSPDI, u1_t_rxdata);
        }
    }
    u1_s_premetmspdi = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_SRPMSW(U4 * u4_ap_pdu_tx)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_SRPMSW(const U4 * u4_ap_pck_rx)
{
    U1  u1_t_mmsup;
    U1  u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)22U, (U1)1U);

        if(u1_t_rxdata != u1_s_presrpmsw){
            if(u1_t_rxdata <= (U1)1U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_SRPMSW, u1_t_rxdata);
            }
        }
        u1_s_presrpmsw = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_ULKMSW(U4 * u4_ap_pdu_tx)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_ULKMSW(const U4* u4_ap_pck_rx)
{
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)11U, (U1)1U);

    if (u1_t_rxdata != u1_s_preulkmsw) {
        if (u1_t_rxdata <= (U1)1U) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_ULKMSW, u1_t_rxdata);
        }
    }
    u1_s_preulkmsw = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_LKMSW(U4 * u4_ap_pdu_tx)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_LKMSW(const U4* u4_ap_pck_rx)
{
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)10U, (U1)1U);

    if (u1_t_rxdata != u1_s_prelkmsw) {
        if (u1_t_rxdata <= (U1)1U) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_LKMSW, u1_t_rxdata);
        }
    }
    u1_s_prelkmsw = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_RG_MD_SW(U4 * u4_ap_pdu_tx)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_RG_MD_SW(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_rxdata;
    U1 u1_t_mmsup;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)2U, (U1)1U);
    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);

    if(u1_t_mmsup == (U1)TRUE){
        if((u1_t_rxdata == (U1)1U) && (u1_t_rxdata != u1_s_prergmdsw)){
            vd_g_GatewaymmDrvmdPut((U1)GATEWAY_MM_RG_MD_SW, (U1)1U);
        } else if ((u1_t_rxdata == (U1)0U) && (u1_t_rxdata != u1_s_prergmdsw)) {
            vd_g_GatewaymmDrvmdPut((U1)GATEWAY_MM_RG_MD_SW, (U1)0U);
        } else {
            /* Do Nothing */
        }
    }
    else{
        if (u1_t_rxdata != u1_s_prergmdsw) {
            if (u1_t_rxdata <= (U1)1U) {
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_RG_MD_SW, u1_t_rxdata);
            }
        }
    }
    u1_s_prergmdsw = u1_t_rxdata;
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_RNGMSW(U4 * u4_ap_pdu_tx)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_RNGMSW(const U4 * u4_ap_pck_rx)
{
    U1 u1_t_rxdata;

    u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)27U, (U1)1U);

    if (u1_t_rxdata != u1_s_prerngmsw) {
        if (u1_t_rxdata <= (U1)1U) {
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_RNGMSW, u1_t_rxdata);
        }
    }
    u1_s_prerngmsw = u1_t_rxdata;
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_LDAAMSW(U4 * u4_ap_pdu_tx)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_LDAAMSW(const U4 * u4_ap_pck_rx)
{
    U1  u1_t_mmsup;
    U1  u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)13U, (U1)3U);

        if(u1_t_rxdata != u1_s_prelddamsw){
            if(u1_t_rxdata <= (U1)4U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_LDAAMSW, u1_t_rxdata);
            }
        }
        u1_s_prelddamsw = u1_t_rxdata;
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_RSA_NEM(U4 * u4_ap_pdu_tx)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_RSA_NEM(const U4 * u4_ap_pck_rx)
{
    U1  u1_t_mmsup;
    U1  u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)21U, (U1)3U);

        if(u1_t_rxdata != u1_s_prersa_nem){
            if(u1_t_rxdata <= (U1)3U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_RSA_NEM, u1_t_rxdata);
            }
        }
        u1_s_prersa_nem = u1_t_rxdata;
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_RSA_LSM(U4 * u4_ap_pdu_tx)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_RSA_LSM(const U4 * u4_ap_pck_rx)
{
    U1  u1_t_mmsup;
    U1  u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)18U, (U1)3U);

        if(u1_t_rxdata != u1_s_prersa_lsm){
            if(u1_t_rxdata <= (U1)3U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_RSA_LSM, u1_t_rxdata);
            }
        }
        u1_s_prersa_lsm = u1_t_rxdata;
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_TRA_SW(U4 * u4_ap_pdu_tx)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_TRA_SW(const U4 * u4_ap_pck_rx)
{
    U1  u1_t_mmsup;
    U1  u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[5], (U1)7U, (U1)1U);

        if(u1_t_rxdata != u1_s_pretra_sw){
            if(u1_t_rxdata <= (U1)1U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_TRA_SW, u1_t_rxdata);
            }
        }
        u1_s_pretra_sw = u1_t_rxdata;
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_ERMSW(U4 * u4_ap_pdu_tx)                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_ERMSW(const U4 * u4_ap_pck_rx)
{
    U1  u1_t_mmsup;
    U1  u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[5], (U1)8U, (U1)2U);

        if(u1_t_rxdata != u1_s_preermsw){
            if(u1_t_rxdata <= (U1)3U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_ERMSW, u1_t_rxdata);
            }
        }
        u1_s_preermsw = u1_t_rxdata;
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_ACCSPMSW(U4 * u4_ap_pdu_tx)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_ACCSPMSW(const U4 * u4_ap_pck_rx)
{
    U1  u1_t_mmsup;
    U1  u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[4], (U1)10U, (U1)3U);

        if(u1_t_rxdata != u1_s_preaccspmsw){
            if(u1_t_rxdata <= (U1)4U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_ACCSPMSW, u1_t_rxdata);
            }
        }
        u1_s_preaccspmsw = u1_t_rxdata;
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_ACCGCRSW(U4 * u4_ap_pdu_tx)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_ACCGCRSW(const U4 * u4_ap_pck_rx)
{
    U1  u1_t_mmsup;
    U1  u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[5], (U1)20U, (U1)1U);

        if(u1_t_rxdata != u1_s_preaccgcrsw){
            if(u1_t_rxdata <= (U1)1U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_ACCGCRSW, u1_t_rxdata);
            }
        }
        u1_s_preaccgcrsw = u1_t_rxdata;
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_CCSMDMSW(U4 * u4_ap_pdu_tx)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_CCSMDMSW(const U4 * u4_ap_pck_rx)
{
    U1  u1_t_mmsup;
    U1  u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[5], (U1)10U, (U1)1U);

        if(u1_t_rxdata != u1_s_preccsmdmsw){
            if(u1_t_rxdata <= (U1)1U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_CCSMDMSW, u1_t_rxdata);
            }
        }
        u1_s_preccsmdmsw = u1_t_rxdata;
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_SLSSOSW(U4 * u4_ap_pdu_tx)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_SLSSOSW(const U4 * u4_ap_pck_rx)
{
    U1  u1_t_mmsup;
    U1  u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[4], (U1)2U, (U1)2U);

        if(u1_t_rxdata != u1_s_preslssosw){
            if(u1_t_rxdata <= (U1)2U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_SLSSOSW, u1_t_rxdata);
            }
        }
        u1_s_preslssosw = u1_t_rxdata;
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_PMARSW(U4 * u4_ap_pdu_tx)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_PMARSW(const U4 * u4_ap_pck_rx)
{
    U1  u1_t_mmsup;
    U1  u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)17U, (U1)1U);

        if(u1_t_rxdata != u1_s_prepmarsw){
            if(u1_t_rxdata <= (U1)1U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_PMARSW, u1_t_rxdata);
            }
        }
        u1_s_prepmarsw = u1_t_rxdata;
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_DOAM_SW(U4 * u4_ap_pdu_tx)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_DOAM_SW(const U4 * u4_ap_pck_rx)
{
    U1  u1_t_mmsup;
    U1  u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)12U, (U1)1U);

        if(u1_t_rxdata != u1_s_predoam_sw){
            if(u1_t_rxdata <= (U1)1U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_DOAM_SW, u1_t_rxdata);
            }
        }
        u1_s_predoam_sw = u1_t_rxdata;
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_DOAM_TIM(U4 * u4_ap_pdu_tx)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_DOAM_TIM(const U4 * u4_ap_pck_rx)
{
    U1  u1_t_mmsup;
    U1  u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)6U, (U1)2U);

        if(u1_t_rxdata != u1_s_predoam_tim){
            if(u1_t_rxdata <= (U1)3U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_DOAM_TIM, u1_t_rxdata);
            }
        }
        u1_s_predoam_tim = u1_t_rxdata;
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_TMNVSW(U4 * u4_ap_pdu_tx)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_TMNVSW(const U4 * u4_ap_pck_rx)
{
    U1  u1_t_mmsup;
    U1  u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)10U, (U1)3U);

        if(u1_t_rxdata != u1_s_pretmnvsw){
            if(u1_t_rxdata <= (U1)4U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_TMNVSW, u1_t_rxdata);
            }
        }
        u1_s_pretmnvsw = u1_t_rxdata;
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_TMNSSW(U4 * u4_ap_pdu_tx)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_TMNSSW(const U4 * u4_ap_pck_rx)
{
    U1  u1_t_mmsup;
    U1  u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)7U, (U1)3U);

        if(u1_t_rxdata != u1_s_pretmnssw){
            if(u1_t_rxdata <= (U1)4U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_TMNSSW, u1_t_rxdata);
            }
        }
        u1_s_pretmnssw = u1_t_rxdata;
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_ITSSETSW(U4 * u4_ap_pdu_tx)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_ITSSETSW(const U4 * u4_ap_pck_rx)
{
    U1  u1_t_mmsup;
    U1  u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)2U, (U1)1U);

        if(u1_t_rxdata != u1_s_preitssetsw){
            if(u1_t_rxdata <= (U1)1U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_ITSSETSW, u1_t_rxdata);
            }
        }
        u1_s_preitssetsw = u1_t_rxdata;
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_DISSUISW(U4 * u4_ap_pdu_tx)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_DISSUISW(const U4 * u4_ap_pck_rx)
{
    U1  u1_t_mmsup;
    U1  u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)3U, (U1)1U);

        if(u1_t_rxdata != u1_s_predissuisw){
            if(u1_t_rxdata <= (U1)1U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_DISSUISW, u1_t_rxdata);
            }
        }
        u1_s_predissuisw = u1_t_rxdata;
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_DM_SW_A2(U4 * u4_ap_pdu_tx)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_DM_SW_A2(const U4 * u4_ap_pck_rx)
{
    U1  u1_t_mmsup;
    U1  u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[1], (U1)4U, (U1)3U);

        if(u1_t_rxdata != u1_s_predm_sw_a2){
            if(u1_t_rxdata <= (U1)3U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_DM_SW_A2, u1_t_rxdata);
            }
        }
        u1_s_predm_sw_a2 = u1_t_rxdata;
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_AHSSWVSW(U4 * u4_ap_pdu_tx)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_AHSSWVSW(const U4 * u4_ap_pck_rx)
{
    U1  u1_t_mmsup;
    U1  u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[5], (U1)12U, (U1)1U);

        if(u1_t_rxdata != u1_s_preahsswvsw){
            if(u1_t_rxdata <= (U1)1U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_AHSSWVSW, u1_t_rxdata);
            }
        }
        u1_s_preahsswvsw = u1_t_rxdata;
    }
}
/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_AHSSDESW(U4 * u4_ap_pdu_tx)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_AHSSDESW(const U4 * u4_ap_pck_rx)
{
    U1  u1_t_mmsup;
    U1  u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if(u1_t_mmsup == (U1)FALSE){
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[5], (U1)13U, (U1)3U);

        if(u1_t_rxdata != u1_s_preahssdesw){
            if(u1_t_rxdata <= (U1)5U){
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_AHSSDESW, u1_t_rxdata);
            }
        }
        u1_s_preahssdesw = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_CANSignal(const U4 * u4_ap_pck_rx)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void vd_s_XSpiCanTx_CANSignal(const U4 * u4_ap_pck_rx){
    static const ST_XSPI_TXSIG st_sp_XSPI_MMCUS_TXSIG[XSPI_MMCUS_NUM_TXSIGNAL] = {
    /* u1_xspiid,  u1_bitpos,  u1_datalen, u1_maxvalue, u1_vdsci_id */
        {(U1)20U,   (U1)21U,   (U1)1U,    (U1)1U,    (U1)VDS_CI_SW_RSRCANSW   },    /* MET1S30->RSRCANSW */
        {(U1)21U,   (U1)6U,    (U1)2U,    (U1)3U,    (U1)VDS_CI_SW_VRAPRMSW   },    /* MET1S30->VRAPRMSW */
        {(U1)24U,   (U1)12U,   (U1)2U,    (U1)3U,    (U1)VDS_CI_SW_VRAPMSWS   },    /* MET1S44->VRAPMSWS */
        {(U1)20U,   (U1)20U,   (U1)1U,    (U1)1U,    (U1)VDS_CI_SW_VRAPRDIS   }     /* MET1S30->VRAPRDIS */
    };
    static const ST_XSPI_TXSIG st_sp_XSPI_METCUS_TXSIG[XSPI_METCUS_NUM_TXSIGNAL] = {
    /* u1_xspiid,  u1_bitpos,  u1_datalen, u1_maxvalue, u1_vdsci_id */
        {(U1)14U,   (U1)9U,    (U1)2U,    (U1)3U,    (U1)VDS_CI_SW_TSR_SNM    },    /* MET1S27->TSR_SNM  */
        {(U1)15U,   (U1)24U,   (U1)1U,    (U1)1U,    (U1)VDS_CI_SW_TSR_MAIN   },    /* MET1S27->TSR_MAIN */
        {(U1)14U,   (U1)19U,   (U1)3U,    (U1)7U,    (U1)VDS_CI_SW_TSR_OSL    },    /* MET1S27->TSR_OSL  */
        {(U1)37U,   (U1)25U,   (U1)1U,    (U1)1U,    (U1)VDS_CI_SW_SDGMSW     },    /* MET1S70->SDGMSW   */
        {(U1)40U,   (U1)4U,    (U1)1U,    (U1)1U,    (U1)VDS_CI_SW_USMMAIN    },    /* MET1S70->USMMAIN  */
        {(U1)37U,   (U1)24U,   (U1)1U,    (U1)1U,    (U1)VDS_CI_SW_PDAMSW     },    /* MET1S70->PDAMSW   */
        {(U1)36U,   (U1)16U,   (U1)2U,    (U1)3U,    (U1)VDS_CI_SW_BSD_SMSS   },    /* MET1S70->BSD_SMSS */
        {(U1)36U,   (U1)18U,   (U1)1U,    (U1)1U,    (U1)VDS_CI_SW_BSD_SMSB   },    /* MET1S70->BSD_SMSB */
        {(U1)37U,   (U1)16U,   (U1)1U,    (U1)1U,    (U1)VDS_CI_SW_ADDS_MSW   },    /* MET1S70->ADDS_MSW */
        {(U1)22U,   (U1)7U,    (U1)1U,    (U1)1U,    (U1)VDS_CI_SW_SPBZ_OPE   },    /* MET1S43->SPBZ_OPE */
        {(U1)20U,   (U1)21U,   (U1)1U,    (U1)1U,    (U1)VDS_CI_SW_RSRCANSW   },    /* MET1S30->RSRCANSW */
        {(U1)21U,   (U1)6U,    (U1)2U,    (U1)3U,    (U1)VDS_CI_SW_VRAPRMSW   },    /* MET1S30->VRAPRMSW */
        {(U1)24U,   (U1)12U,   (U1)2U,    (U1)3U,    (U1)VDS_CI_SW_VRAPMSWS   },    /* MET1S44->VRAPMSWS */
        {(U1)20U,   (U1)20U,   (U1)1U,    (U1)1U,    (U1)VDS_CI_SW_VRAPRDIS   },    /* MET1S30->VRAPRDIS */
        {(U1)41U,   (U1)18U,   (U1)1U,    (U1)1U,    (U1)VDS_CI_SW_RTWMSW     },    /* MET1S71->RTWMSW   */
        {(U1)35U,   (U1)17U,   (U1)1U,    (U1)1U,    (U1)VDS_CI_SW_TBCSW      }     /* MET1S62->TBCSW    */
    };

    U1 u1_t_mmsup;
    U1 u1_t_loop;
    U1 u1_t_rxdata;

    u1_t_mmsup  = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
        if(u1_t_mmsup == (U1)TRUE){
        for (u1_t_loop = (U1)0U; u1_t_loop < (U1)XSPI_MMCUS_NUM_TXSIGNAL; u1_t_loop++) {
            u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[st_sp_XSPI_MMCUS_TXSIG[u1_t_loop].u1_xspiid],
                                            st_sp_XSPI_MMCUS_TXSIG[u1_t_loop].u1_bitpos, st_sp_XSPI_MMCUS_TXSIG[u1_t_loop].u1_datalen);

            if(u1_t_rxdata != u1_sp_xspi_mmcus_pretxsig[u1_t_loop]) {
                if(u1_t_rxdata != (U1)st_sp_XSPI_MMCUS_TXSIG[u1_t_loop].u1_maxvalue) {
                    vd_g_VdsCIReqTx((U1)st_sp_XSPI_MMCUS_TXSIG[u1_t_loop].u1_vdsci_id, u1_t_rxdata);
                }
            }
            u1_sp_xspi_mmcus_pretxsig[u1_t_loop] = u1_t_rxdata;
        }
    }
    else{
        for (u1_t_loop = (U1)0U; u1_t_loop < (U1)XSPI_METCUS_NUM_TXSIGNAL; u1_t_loop++) {
            u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[st_sp_XSPI_METCUS_TXSIG[u1_t_loop].u1_xspiid],
                                            st_sp_XSPI_METCUS_TXSIG[u1_t_loop].u1_bitpos, st_sp_XSPI_METCUS_TXSIG[u1_t_loop].u1_datalen);

            if(u1_t_rxdata != u1_sp_xspi_metcus_pretxsig[u1_t_loop]) {
                if(u1_t_rxdata != (U1)st_sp_XSPI_METCUS_TXSIG[u1_t_loop].u1_maxvalue) {
                    vd_g_VdsCIReqTx((U1)st_sp_XSPI_METCUS_TXSIG[u1_t_loop].u1_vdsci_id, u1_t_rxdata);
                }
            }
            u1_sp_xspi_metcus_pretxsig[u1_t_loop] = u1_t_rxdata;
        }
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_SW_AS02(const U4* u4_ap_pck_rx)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_SW_AS02(const U4* u4_ap_pck_rx)
{
    static const U1 u1_s_xSPI_ACS_MODE_ON = (U1)0x01U;
    U1  u1_t_mmsup;
    U1  u1_t_rxdata;

    u1_t_mmsup = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if (u1_t_mmsup == (U1)FALSE) {
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)30U, (U1)1U);

        if (u1_t_rxdata != u1_s_presw_as02) {
            if (u1_t_rxdata <= u1_s_xSPI_ACS_MODE_ON) {
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_SW_AS02, u1_t_rxdata);
            }
        }
        u1_s_presw_as02 = u1_t_rxdata;
    }
}

/*===================================================================================================================================*/
/*  static inline void    vd_s_XSpiCanTx_SW_AS01(const U4* u4_ap_pck_rx)                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:     u4_ap_pck_rx                                                                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCanTx_SW_AS01(const U4* u4_ap_pck_rx)
{
    static const U1 u1_s_xSPI_VHC_ON = (U1)0x01U;
    U1  u1_t_mmsup;
    U1  u1_t_rxdata;

    u1_t_mmsup = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
    if (u1_t_mmsup == (U1)FALSE) {
        u1_t_rxdata = u1_XSPI_MET_READ__BIT(u4_ap_pck_rx[0], (U1)31U, (U1)1U);

        if (u1_t_rxdata != u1_s_presw_as01) {
            if (u1_t_rxdata <= u1_s_xSPI_VHC_ON) {
                vd_g_VdsCIReqTx((U1)VDS_CI_SW_SW_AS01, u1_t_rxdata);
            }
        }
        u1_s_presw_as01 = u1_t_rxdata;
    }
}

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
#if 0   /* BEV BSW provisionally */
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_M_BB, u1_t_rxdata);
#endif
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
#if 0   /* BEV BSW provisionally */
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_MLR_BB, u1_t_rxdata);
#endif
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
#if 0   /* BEV BSW provisionally */
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_RLM_BB, u1_t_rxdata);
#endif
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
#if 0   /* BEV BSW provisionally */
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_MRT_BB, u1_t_rxdata);
#endif
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
#if 0   /* BEV BSW provisionally */
            vd_g_VdsCIReqTx((U1)VDS_CI_SW_ART_BB, u1_t_rxdata);
#endif
        }
    }
    u1_s_preart_bb = u1_t_rxdata;
}
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
/*           10/10/2024  KT       Change for BEV B_OMRBB                                                                             */
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
/*                                                                                                                                   */
/*===================================================================================================================================*/
