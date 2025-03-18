/* 2.4.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Vehicle Driving Support Configuration/Calibration Interface                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define VDS_CI_CFG_C_MAJOR                     (2)
#define VDS_CI_CFG_C_MINOR                     (4)
#define VDS_CI_CFG_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "vds_ci_cfg_private.h"
#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif


#include "veh_opemd.h"
#if 0   /* BEV BSW provisionally */
#else
#include "veh_opemd_xmode_STUB.h"
#endif
#include "iohw_diflt.h"
#if 0   /* BEV BSW provisionally */
#else
#include "iohw_adc_channel_STUB.h"
#include "iohw_diflt_sgnl_STUB.h"
#endif
#include "odo_km.h"
#include "vardef.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((VDS_CI_CFG_C_MAJOR != VDS_CI_H_MAJOR) || \
     (VDS_CI_CFG_C_MINOR != VDS_CI_H_MINOR) || \
     (VDS_CI_CFG_C_PATCH != VDS_CI_H_PATCH))
#error "vds_ci_cfg.c and vds_ci.h : source and header files are inconsistent!"
#endif

#if ((VDS_CI_CFG_C_MAJOR != VDS_CI_CFG_H_MAJOR) || \
     (VDS_CI_CFG_C_MINOR != VDS_CI_CFG_H_MINOR) || \
     (VDS_CI_CFG_C_PATCH != VDS_CI_CFG_H_PATCH))
#error "vds_ci_cfg.c and vds_ci_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
ST_VDS_CI_CH           st_gp_vds_ci_ch[VDS_CI_NUM_CH];

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_VdsCISelRx_Unk(void);

static void vd_s_VdsCIReqTx_ASD_CONT(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_ASD_CANC(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_METSPDIS(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_FCMUSER (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_LCASGAPR(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_ST_TDEF (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_ST_TAUTO(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_ST_ACOFF(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_VRESTPSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_M_SETSTS(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_M_SETNXT(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_PSRSP1  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_PSRSP2  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_PSRSP3  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_PLUSSW  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_M_COP_S (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_M_OP_SUP(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_PWSPSWAC(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_BSMMSW  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_CSRMSW  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_FCMMSW  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_ICSMSW  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_LDA_SFB (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_LDAMCUS (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_PCSMSW  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_RCTAMSW (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_SW_DEA01(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_SW_LTC01(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_SW_RCD01(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_TSR_OSL (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_TSR_SNM (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_RSCSW_OP(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_TPINSEL (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_TPINSELF(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_TPINSELR(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_TPUNTSET(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_MINTRSOF(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_PBDBZMVL(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_PBDKSW  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_PBDMCUS (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_PBDMSW  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_RSRMSW  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_PSR_EN  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_PSR_PSSR(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_SR_BACK (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_SR_COM  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_SR_DRV  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_SR_ST   (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_SR_TOP  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_CLOCK_SU(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_M_CUR200(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_M_DPWREQ(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_M_LMTREQ(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_M_SLMREQ(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_MRMRQBK (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_MRMRQSW (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_PWSPL_BK(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_PWSPL_OK(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_PWSPL_SU(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_TBCSW   (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_BSMM_ILV(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_IDAMSW  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_IDASESW (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_LCASGMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_LDASW   (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_PKSSVOL (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_RSR_TIM (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_RTAN_TIM(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_ACCACLSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_ACCRACSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_ACCROSSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_ACCSSOSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_CTAMSW  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_RTAN_MSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_TSR_MAIN(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_M_WEEK  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_M_SETID (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_M_SETTYP(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_M_SETWKD(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_CSR_MUTE(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_HOFCUS  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_SW_ITS04(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_ACCADPSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_LPSDKSW (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_LPSDBZVL(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_RPSDBZVL(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_RPSDKSW (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_SSMMODE (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_GPFGENSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_GPFINDSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_ACINV_SW(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_SR_NUM  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_SDGMSW  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_USMMAIN (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_PDAMSW  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_DRECSW  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_ADDS_MSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_SPBZ_OPE(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_RSRCANSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_VRAPRMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_VRAPMSWS(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_VRAPRDIS(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_RTWMSW  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_BSD_SMSB(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_BSD_SMSS(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_SETDCLVI(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_SETDCLVM(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_METMDREJ(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_TRLC_YN (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_M_SLMDRQ(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_TBWSW   (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_ULKMSW  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_LKMSW   (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_M_PNCSW (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_LMTDAANS(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_M_OCOFOK(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_SRPMSW  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_RG_MD_SW(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_RNGMSW  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_LDAAMSW (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_RSA_NEM (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_RSA_LSM (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_TRA_SW  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_ERMSW   (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_ACCSPMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_ACCGCRSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_CCSMDMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_SLSSOSW (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_PMARSW  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_DOAM_SW (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_DOAM_TIM(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_TMNVSW  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_TMNSSW  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_ITSSETSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_DISSUISW(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_DM_SW_A2(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_AHSSWVSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_AHSSDESW(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_M_BB    (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_MLR_BB  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_RLM_BB  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_MRT_BB  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_ART_BB  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_PWLSW   (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_WVRD_BB (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_WVRU_BB (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_WROF_BB (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_WRLO_BB (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_WRIN_BB (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_WRSW_BB (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_WSVS_BB (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_TRNBBSW (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_LSW_BB  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_FOG_BB  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_RFG_BB  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_WDI_BB  (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_TITE_BB (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_MW_BB   (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_AECOSWBB(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_METMDSEL(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_ACCDSTSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_HCSUPEN (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_HCSDWEN (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_HCSMNSW (const U1 u1_a_OPT, const U2 u2_a_ELPSD);
static void vd_s_VdsCIReqTx_HCSSTPOP(const U1 u1_a_OPT, const U2 u2_a_ELPSD);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_VDS_CI_TRX    st_gp_VDS_CI_TRX[VDS_CI_NUM_CH] = {
    /* -------------------------------------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                                                */
    /* -------------------------------------------------------------------------------------------------------------------------- */
    /* st_gp_VDS_CI_TRX[].fp_u1_RX and st_gp_VDS_CI_TRX[].fp_vd_TX shall be valid function pointer.                               */
    /* -------------------------------------------------------------------------------------------------------------------------- */
    /*1234567890123456789012345678901  1234567890123456789012345678901                                                            */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_ASD_CONT,    (U2)0xFFFFU, (U2)0x0001U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /*  0 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_ASD_CANC,    (U2)0xFFFFU, (U2)0x0002U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /*  1 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_METSPDIS,    (U2)0xFFFFU, (U2)0x0004U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /*  2 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_FCMUSER,     (U2)0xFFFFU, (U2)0x0008U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /*  3 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_LCASGAPR,    (U2)0xFFFFU, (U2)0x0010U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /*  4 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_ST_TDEF,     (U2)0xFFFFU, (U2)0x0020U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /*  5 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_ST_TAUTO,    (U2)0xFFFFU, (U2)0x0040U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /*  6 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_ST_ACOFF,    (U2)0xFFFFU, (U2)0x0080U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /*  7 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_VRESTPSW,    (U2)0xFFFFU, (U2)0x0100U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /*  8 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_M_SETSTS,    (U2)0xFFFFU, (U2)0x0200U, (U2)VDS_CI_DELAY_HOLD,   (U1)VDS_CI_TX_MASK_NON       }, /*  9 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_M_SETNXT,    (U2)0xFFFFU, (U2)0x0001U, (U2)VDS_CI_DELAY_HOLD,   (U1)VDS_CI_TX_MASK_NON       }, /* 10 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_PSRSP1,      (U2)0xFFFFU, (U2)0x0002U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 11 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_PSRSP2,      (U2)0xFFFFU, (U2)0x0004U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 12 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_PSRSP3,      (U2)0xFFFFU, (U2)0x0008U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 13 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_PLUSSW,      (U2)0xFFFFU, (U2)0x0010U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 14 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_M_COP_S,     (U2)0xFFFFU, (U2)0x0020U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 15 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_M_OP_SUP,    (U2)0xFFFFU, (U2)0x0040U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 16 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_PWSPSWAC,    (U2)0xFFFFU, (U2)0x0080U, (U2)VDS_CI_DELAY_HOLD,   (U1)VDS_CI_TX_MASK_NON       }, /* 17 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_BSMMSW,      (U2)0xFFFFU, (U2)0x0100U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 18 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_CSRMSW,      (U2)0xFFFFU, (U2)0x0200U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 19 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_FCMMSW,      (U2)0xFFFFU, (U2)0x0001U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 20 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_ICSMSW,      (U2)0xFFFFU, (U2)0x0002U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 21 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_LDA_SFB,     (U2)0xFFFFU, (U2)0x0004U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 22 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_LDAMCUS,     (U2)0xFFFFU, (U2)0x0008U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 23 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_PCSMSW,      (U2)0xFFFFU, (U2)0x0010U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 24 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_RCTAMSW,     (U2)0xFFFFU, (U2)0x0020U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 25 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_SW_DEA01,    (U2)0xFFFFU, (U2)0x0040U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 26 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_SW_LTC01,    (U2)0xFFFFU, (U2)0x0080U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 27 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_SW_RCD01,    (U2)0xFFFFU, (U2)0x0100U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 28 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_TSR_OSL,     (U2)0xFFFFU, (U2)0x0200U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 29 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_TSR_SNM,     (U2)0xFFFFU, (U2)0x0001U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 30 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_RSCSW_OP,    (U2)0xFFFFU, (U2)0x0002U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 31 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_TPINSEL,     (U2)0xFFFFU, (U2)0x0004U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 32 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_TPINSELF,    (U2)0xFFFFU, (U2)0x0008U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 33 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_TPINSELR,    (U2)0xFFFFU, (U2)0x0010U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 34 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_TPUNTSET,    (U2)0xFFFFU, (U2)0x0020U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 35 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_MINTRSOF,    (U2)0xFFFFU, (U2)0x0040U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 36 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_PBDBZMVL,    (U2)0xFFFFU, (U2)0x0080U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 37 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_PBDKSW,      (U2)0xFFFFU, (U2)0x0100U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 38 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_PBDMCUS,     (U2)0xFFFFU, (U2)0x0200U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 39 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_PBDMSW,      (U2)0xFFFFU, (U2)0x0001U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 40 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_RSRMSW,      (U2)0xFFFFU, (U2)0x0002U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 41 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_PSR_EN,      (U2)0xFFFFU, (U2)0x0004U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 42 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_PSR_PSSR,    (U2)0xFFFFU, (U2)0x0008U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 43 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_SR_BACK,     (U2)0xFFFFU, (U2)0x0010U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 44 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_SR_COM,      (U2)0xFFFFU, (U2)0x0020U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 45 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_SR_DRV,      (U2)0xFFFFU, (U2)0x0040U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 46 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_SR_ST,       (U2)0xFFFFU, (U2)0x0080U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 47 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_SR_TOP,      (U2)0xFFFFU, (U2)0x0100U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 48 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_CLOCK_SU,    (U2)0xFFFFU, (U2)0x0200U, (U2)VDS_CI_DELAY_HOLD,   (U1)VDS_CI_TX_MASK_NON       }, /* 49 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_M_CUR200,    (U2)0xFFFFU, (U2)0x0001U, (U2)VDS_CI_DELAY_HOLD,   (U1)VDS_CI_TX_MASK_NON       }, /* 50 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_M_DPWREQ,    (U2)0xFFFFU, (U2)0x0002U, (U2)VDS_CI_DELAY_HOLD,   (U1)VDS_CI_TX_MASK_NON       }, /* 51 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_M_LMTREQ,    (U2)0xFFFFU, (U2)0x0004U, (U2)VDS_CI_DELAY_HOLD,   (U1)VDS_CI_TX_MASK_NON       }, /* 52 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_M_SLMREQ,    (U2)0xFFFFU, (U2)0x0008U, (U2)VDS_CI_DELAY_HOLD,   (U1)VDS_CI_TX_MASK_NON       }, /* 53 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_MRMRQBK,     (U2)0xFFFFU, (U2)0x0010U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 54 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_MRMRQSW,     (U2)0xFFFFU, (U2)0x0020U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 55 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_PWSPL_BK,    (U2)0xFFFFU, (U2)0x0040U, (U2)VDS_CI_DELAY_HOLD,   (U1)VDS_CI_TX_MASK_NON       }, /* 56 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_PWSPL_OK,    (U2)0xFFFFU, (U2)0x0080U, (U2)VDS_CI_DELAY_HOLD,   (U1)VDS_CI_TX_MASK_NON       }, /* 57 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_PWSPL_SU,    (U2)0xFFFFU, (U2)0x0100U, (U2)VDS_CI_DELAY_HOLD,   (U1)VDS_CI_TX_MASK_NON       }, /* 58 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_TBCSW,       (U2)0xFFFFU, (U2)0x0200U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 59 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_BSMM_ILV,    (U2)0xFFFFU, (U2)0x0001U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 60 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_IDAMSW,      (U2)0xFFFFU, (U2)0x0002U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 61 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_IDASESW,     (U2)0xFFFFU, (U2)0x0004U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 62 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_LCASGMSW,    (U2)0xFFFFU, (U2)0x0008U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 63 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_LDASW,       (U2)0xFFFFU, (U2)0x0010U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 64 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_PKSSVOL,     (U2)0xFFFFU, (U2)0x0020U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 65 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_RSR_TIM,     (U2)0xFFFFU, (U2)0x0040U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 66 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_RTAN_TIM,    (U2)0xFFFFU, (U2)0x0080U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 67 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_ACCACLSW,    (U2)0xFFFFU, (U2)0x0100U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 68 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_ACCRACSW,    (U2)0xFFFFU, (U2)0x0200U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 69 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_ACCROSSW,    (U2)0xFFFFU, (U2)0x0001U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 70 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_ACCSSOSW,    (U2)0xFFFFU, (U2)0x0002U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 71 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_CTAMSW,      (U2)0xFFFFU, (U2)0x0004U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 72 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_RTAN_MSW,    (U2)0xFFFFU, (U2)0x0008U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 73 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_TSR_MAIN,    (U2)0xFFFFU, (U2)0x0010U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 74 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_M_WEEK,      (U2)0xFFFFU, (U2)0x0020U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 75 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_M_SETID,     (U2)0xFFFFU, (U2)0x0040U, (U2)VDS_CI_DELAY_HOLD,   (U1)VDS_CI_TX_MASK_NON       }, /* 76 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_M_SETTYP,    (U2)0xFFFFU, (U2)0x0080U, (U2)VDS_CI_DELAY_HOLD,   (U1)VDS_CI_TX_MASK_NON       }, /* 77 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_M_SETWKD,    (U2)0xFFFFU, (U2)0x0100U, (U2)VDS_CI_DELAY_HOLD,   (U1)VDS_CI_TX_MASK_NON       }, /* 78 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_CSR_MUTE,    (U2)0xFFFFU, (U2)0x0200U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 79 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_HOFCUS,      (U2)0xFFFFU, (U2)0x0001U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 80 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_SW_ITS04,    (U2)0xFFFFU, (U2)0x0002U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 81 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_ACCADPSW,    (U2)0xFFFFU, (U2)0x0004U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 82 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_LPSDKSW,     (U2)0xFFFFU, (U2)0x0008U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 83 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_LPSDBZVL,    (U2)0xFFFFU, (U2)0x0010U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 84 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_RPSDBZVL,    (U2)0xFFFFU, (U2)0x0020U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 85 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_RPSDKSW,     (U2)0xFFFFU, (U2)0x0040U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 86 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_SSMMODE,     (U2)0xFFFFU, (U2)0x0080U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 87 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_GPFGENSW,    (U2)0xFFFFU, (U2)0x0100U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 88 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_GPFINDSW,    (U2)0xFFFFU, (U2)0x0200U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 89 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_ACINV_SW,    (U2)0xFFFFU, (U2)0x0001U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 90 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_SR_NUM,      (U2)0xFFFFU, (U2)0x0002U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 91 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_SDGMSW,      (U2)0xFFFFU, (U2)0x0004U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 92 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_USMMAIN,     (U2)0xFFFFU, (U2)0x0008U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 93 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_PDAMSW,      (U2)0xFFFFU, (U2)0x0010U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 94 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_DRECSW,      (U2)0xFFFFU, (U2)0x0020U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 95 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_ADDS_MSW,    (U2)0xFFFFU, (U2)0x0040U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 96 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_SPBZ_OPE,    (U2)0xFFFFU, (U2)0x0080U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 97 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_RSRCANSW,    (U2)0xFFFFU, (U2)0x0100U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 98 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_VRAPRMSW,    (U2)0xFFFFU, (U2)0x0200U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 99 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_VRAPMSWS,    (U2)0xFFFFU, (U2)0x0001U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 100 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_VRAPRDIS,    (U2)0xFFFFU, (U2)0x0002U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 101 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_RTWMSW,      (U2)0xFFFFU, (U2)0x0004U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 102 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_BSD_SMSB,    (U2)0xFFFFU, (U2)0x0008U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 103 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_BSD_SMSS,    (U2)0xFFFFU, (U2)0x0010U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 104 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_SETDCLVI,    (U2)0xFFFFU, (U2)0x0020U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 105 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_SETDCLVM,    (U2)0xFFFFU, (U2)0x0040U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 106 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_METMDREJ,    (U2)0xFFFFU, (U2)0x0080U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 107 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_TRLC_YN,     (U2)0xFFFFU, (U2)0x0100U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 108 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_M_SLMDRQ,    (U2)0xFFFFU, (U2)0x0200U, (U2)VDS_CI_DELAY_HOLD,   (U1)VDS_CI_TX_MASK_NON       }, /* 109 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_TBWSW,       (U2)0xFFFFU, (U2)0x0001U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 110 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_ULKMSW,      (U2)0xFFFFU, (U2)0x0002U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 111 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_LKMSW,       (U2)0xFFFFU, (U2)0x0004U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 112 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_M_PNCSW,     (U2)0xFFFFU, (U2)0x0008U, (U2)VDS_CI_DELAY_HOLD,   (U1)VDS_CI_TX_MASK_NON       }, /* 113 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_LMTDAANS,    (U2)0xFFFFU, (U2)0x0010U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 114 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_M_OCOFOK,    (U2)0xFFFFU, (U2)0x0020U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 115 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_SRPMSW,      (U2)0xFFFFU, (U2)0x0040U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 116 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_RG_MD_SW,    (U2)0xFFFFU, (U2)0x0080U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 117 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_RNGMSW,      (U2)0xFFFFU, (U2)0x0100U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 118 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_LDAAMSW,     (U2)0xFFFFU, (U2)0x0200U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 119 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_RSA_NEM,     (U2)0xFFFFU, (U2)0x0001U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 120 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_RSA_LSM,     (U2)0xFFFFU, (U2)0x0002U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 121 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_TRA_SW,      (U2)0xFFFFU, (U2)0x0004U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 122 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_ERMSW,       (U2)0xFFFFU, (U2)0x0008U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 123 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_ACCSPMSW,    (U2)0xFFFFU, (U2)0x0010U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 124 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_ACCGCRSW,    (U2)0xFFFFU, (U2)0x0020U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 125 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_CCSMDMSW,    (U2)0xFFFFU, (U2)0x0040U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 126 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_SLSSOSW,     (U2)0xFFFFU, (U2)0x0080U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 127 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_PMARSW,      (U2)0xFFFFU, (U2)0x0100U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 128 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_DOAM_SW,     (U2)0xFFFFU, (U2)0x0200U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 129 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_DOAM_TIM,    (U2)0xFFFFU, (U2)0x0001U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 130 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_TMNVSW,      (U2)0xFFFFU, (U2)0x0002U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 131 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_TMNSSW,      (U2)0xFFFFU, (U2)0x0004U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 132 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_ITSSETSW,    (U2)0xFFFFU, (U2)0x0008U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 133 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_DISSUISW,    (U2)0xFFFFU, (U2)0x0010U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 134 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_DM_SW_A2,    (U2)0xFFFFU, (U2)0x0020U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 135 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_AHSSWVSW,    (U2)0xFFFFU, (U2)0x0040U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 136 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_AHSSDESW,    (U2)0xFFFFU, (U2)0x0080U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_MM_ESOPT  }, /* 137 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_M_BB,        (U2)0xFFFFU, (U2)0x0100U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 138 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_MLR_BB,      (U2)0xFFFFU, (U2)0x0200U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 139 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_RLM_BB,      (U2)0xFFFFU, (U2)0x0001U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 140 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_MRT_BB,      (U2)0xFFFFU, (U2)0x0002U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 141 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_ART_BB,      (U2)0xFFFFU, (U2)0x0004U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 142 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_PWLSW,       (U2)0xFFFFU, (U2)0x0008U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 143 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_WVRD_BB,     (U2)0xFFFFU, (U2)0x0010U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 144 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_WVRU_BB,     (U2)0xFFFFU, (U2)0x0020U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 145 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_WROF_BB,     (U2)0xFFFFU, (U2)0x0040U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 146 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_WRLO_BB,     (U2)0xFFFFU, (U2)0x0080U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 147 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_WRIN_BB,     (U2)0xFFFFU, (U2)0x0100U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 148 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_WRSW_BB,     (U2)0xFFFFU, (U2)0x0200U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 149 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_WSVS_BB,     (U2)0xFFFFU, (U2)0x0001U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 150 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_TRNBBSW,     (U2)0xFFFFU, (U2)0x0002U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 151 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_LSW_BB,      (U2)0xFFFFU, (U2)0x0004U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 152 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_FOG_BB,      (U2)0xFFFFU, (U2)0x0008U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 153 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_RFG_BB,      (U2)0xFFFFU, (U2)0x0010U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 154 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_WDI_BB,      (U2)0xFFFFU, (U2)0x0020U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 155 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_TITE_BB,     (U2)0xFFFFU, (U2)0x0040U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 156 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_MW_BB,       (U2)0xFFFFU, (U2)0x0080U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 157 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_AECOSWBB,    (U2)0xFFFFU, (U2)0x0100U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 158 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_METMDSEL,    (U2)0xFFFFU, (U2)0x0200U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 159 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_ACCDSTSW,    (U2)0xFFFFU, (U2)0x0001U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 160 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_HCSUPEN,     (U2)0xFFFFU, (U2)0x0002U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 161 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_HCSDWEN,     (U2)0xFFFFU, (U2)0x0004U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 162 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_HCSMNSW,     (U2)0xFFFFU, (U2)0x0008U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }, /* 163 */
    {&u1_s_VdsCISelRx_Unk,    &vd_s_VdsCIReqTx_HCSSTPOP,    (U2)0xFFFFU, (U2)0x0010U, (U2)VDS_CI_HOLD_TIME,    (U1)VDS_CI_TX_MASK_NON       }  /* 164 */
};
const U1               u1_g_VDS_CI_NUM_CH = (U1)VDS_CI_NUM_CH;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_VdsCICfgInit(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VdsCICfgInit(void)
{
    st_gp_vds_ci_ch[VDS_CI_SW_M_SLMREQ].u1_req_tx = (U1)VDS_CI_M_SLMREQ_INIT;

    /* MET-H_TIMCHG Send Init Value   */
    st_gp_vds_ci_ch[VDS_CI_SW_M_SETID].u1_req_tx  = (U1)VDS_CI_M_SETID_INIT;

    /* MET-H_SWQUICHA Send Init Value */
    st_gp_vds_ci_ch[VDS_CI_SW_M_CUR200].u1_req_tx = (U1)VDS_CI_M_CUR200_INIT;
    st_gp_vds_ci_ch[VDS_CI_SW_M_DPWREQ].u1_req_tx = (U1)VDS_CI_M_DPWREQ_INIT;
    st_gp_vds_ci_ch[VDS_CI_SW_M_LMTREQ].u1_req_tx = (U1)VDS_CI_M_LMTREQ_INIT;
}
/*===================================================================================================================================*/
/*  void    vd_g_VdsCICfgMainStart(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VdsCICfgMainStart(void)
{
}
/*===================================================================================================================================*/
/*  void    vd_g_VdsCICfgMainFinish(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_VdsCICfgMainFinish(void)
{
}
/*===================================================================================================================================*/
/*  U1      u1_g_VdsCICfgGetMMEsopt(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_VdsCICfgGetMMEsopt(void)
{
    U1 u1_t_ret;

#if 0   /* BEV provisionally */
    u1_t_ret = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_MOP);
#else
    u1_t_ret = (U1)FALSE;
#endif
    return(u1_t_ret);
}
/*===================================================================================================================================*/
/* static U1      u1_s_VdsCISelRx_Unk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_VdsCISelRx_Unk(void)
{
    return((U1)VDS_CI_OPT_UNK);
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_ASD_CONT(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_ASD_CONT(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_ASD_CONT
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_ASD_CONT, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_ASD_CONT, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_ASD_CONT */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_ASD_CANC(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_ASD_CANC(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_ASD_CANC
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_ASD_CANC, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_ASD_CANC, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_ASD_CANC */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_METSPDIS(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_METSPDIS(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_METSPDIS
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_METSPDIS, &u1_t_tx);
#endif /* #ifdef ComConf_ComSignal_METSPDIS */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_FCMUSER(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_FCMUSER(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_FCMUSER
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_FCMUSER, &u1_t_tx);
#endif /* #ifdef ComConf_ComSignal_FCMUSER */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_LCASGAPR(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_LCASGAPR(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_LCASGAPR
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_LCASGAPR_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_LCASGAPR, &u1_t_tx);
#endif /* #ifdef ComConf_ComSignal_LCASGAPR */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_ST_TDEF(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_ST_TDEF(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_ST_TDEF
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_ST_TDEF, &u1_t_tx);

#endif /* ComConf_ComSignal_ST_TDEF */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_ST_TAUTO(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_ST_TAUTO(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_ST_TAUTO
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_ST_TAUTO, &u1_t_tx);

#endif /* ComConf_ComSignal_ST_TAUTO */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_ST_ACOFF(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_ST_ACOFF(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_ST_ACOFF
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_ST_ACOFF, &u1_t_tx);

#endif /* ComConf_ComSignal_ST_ACOFF */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_VRESTPSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_VRESTPSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_VRESTPSW
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_VRESTPSW, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_VRESTPSW, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_VRESTPSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_M_SETSTS(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_M_SETSTS(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_M_SETSTS
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_M_SETSTS_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_M_SETSTS_INIT;
    }
    u1_t_pre_tx = (U1)VDS_CI_M_SETSTS_INIT;

    (void)Com_ReceiveSignal(ComConf_ComSignal_M_SETSTS, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_M_SETSTS, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S61_TXCH0);
    }
#endif /* ComConf_ComSignal_M_SETSTS */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_M_SETNXT(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_M_SETNXT(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_M_SETNXT
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_M_SETNXT_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_M_SETNXT_INIT;
    }
    u1_t_pre_tx = (U1)VDS_CI_M_SETNXT_INIT;

    (void)Com_ReceiveSignal(ComConf_ComSignal_M_SETNXT, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_M_SETNXT, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S61_TXCH0);
    }
#endif /* ComConf_ComSignal_M_SETNXT */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_PSRSP1(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_PSRSP1(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
    /* Not Applicable */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_PSRSP2(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_PSRSP2(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
    /* Not Applicable */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_PSRSP3(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_PSRSP3(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
    /* Not Applicable */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_PLUSSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_PLUSSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_PLUSSW
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_PLUSSW, &u1_t_tx);
#endif /* ComConf_ComSignal_PLUSSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_M_COP_S(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_M_COP_S(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_M_COP_S
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_M_COP_S_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_M_COP_S, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_M_COP_S, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S47_TXCH0);
    }
#endif /* ComConf_ComSignal_M_COP_S */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_M_OP_SUP(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_M_OP_SUP(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_M_OP_SUP
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_M_OP_SUP_OK){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_M_OP_SUP_NG;
    }
    u1_t_pre_tx = (U1)VDS_CI_M_OP_SUP_NG;

    (void)Com_ReceiveSignal(ComConf_ComSignal_M_OP_SUP, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_M_OP_SUP, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S47_TXCH0);
    }
#endif /* ComConf_ComSignal_M_OP_SUP */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_PWSPSWAC(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_PWSPSWAC(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_PWSPSWAC
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_PWSPSWAC_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_PWSPSWAC, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_PWSPSWAC, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S62_TXCH0);
    }
#endif /* ComConf_ComSignal_PWSPSWAC */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_BSMMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_BSMMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_BSMMSW
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_BSMMSW, &u1_t_tx);
#endif /* ComConf_ComSignal_BSMMSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_CSRMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_CSRMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_CSRMSW
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_CSRMSW, &u1_t_tx);
#endif /* ComConf_ComSignal_CSRMSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_FCMMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_FCMMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_FCMMSW, &u1_t_tx);
#endif /* ComConf_ComSignal_FCMMSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_ICSMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_ICSMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_ICSMSW
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_ICSMSW, &u1_t_tx);
#endif /* ComConf_ComSignal_ICSMSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_LDA_SFB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_LDA_SFB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_LDA_SFB
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_LDA_SFB_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_LDA_SFB, &u1_t_tx);
#endif /* ComConf_ComSignal_LDA_SFB */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_LDAMCUS(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_LDAMCUS(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_LDAMCUS
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_LDAMCUS_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_LDAMCUS, &u1_t_tx);
#endif /* ComConf_ComSignal_LDAMCUS */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_PCSMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_PCSMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_PCSMSW
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_PCSMSW, &u1_t_tx);
#endif /* ComConf_ComSignal_PCSMSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_RCTAMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_RCTAMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_RCTAMSW
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_RCTAMSW, &u1_t_tx);
#endif /* ComConf_ComSignal_RCTAMSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_SW_DEA01(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_SW_DEA01(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_SW_DEA01
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_SW_DEA01, &u1_t_tx);
#endif /* ComConf_ComSignal_SW_DEA01 */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_SW_LTC01(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_SW_LTC01(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_SW_LTC01
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_SW_LTC01, &u1_t_tx);
#endif /* ComConf_ComSignal_SW_LTC01 */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_SW_RCD01(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_SW_RCD01(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_SW_RCD01
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_SW_RCD01, &u1_t_tx);
#endif /* ComConf_ComSignal_SW_RCD01 */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_TSR_OSL(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_TSR_OSL(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_TSR_OSL
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_TSR_OSL_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_TSR_OSL, &u1_t_tx);
#endif /* ComConf_ComSignal_TSR_OSL */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_TSR_SNM(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_TSR_SNM(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_TSR_SNM
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_TSR_SNM_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_TSR_SNM, &u1_t_tx);
#endif /* ComConf_ComSignal_TSR_SNM */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_RSCSW_OP(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_RSCSW_OP(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_RSCSW_OP, &u1_t_tx);
#endif /* ComConf_ComSignal_RSCSW_OP */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_TPINSEL(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_TPINSEL(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_TPINSEL
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_TPINSEL_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_TPINSEL, &u1_t_tx);
#endif /* ComConf_ComSignal_TPINSEL */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_TPINSELF(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_TPINSELF(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_TPINSELF
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_TPINSELF_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_TPINSELF, &u1_t_tx);
#endif /* ComConf_ComSignal_TPINSELF */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_TPINSELR(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_TPINSELR(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_TPINSELR
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_TPINSELR_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_TPINSELR, &u1_t_tx);
#endif /* ComConf_ComSignal_TPINSELR */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_TPUNTSET(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_TPUNTSET(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_TPUNTSET
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_TPUNTSET_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_TPUNTSET, &u1_t_tx);
#endif /* ComConf_ComSignal_TPUNTSET */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_MINTRSOF(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_MINTRSOF(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_MINTRSOF, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_MINTRSOF, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_MINTRSOF */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_PBDBZMVL(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_PBDBZMVL(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_PBDBZMVL
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_PBDBZMVL_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_PBDBZMVL, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_PBDBZMVL, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_PBDBZMVL */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_PBDKSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_PBDKSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_PBDKSW
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_PBDKSW, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_PBDKSW, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_PBDKSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_PBDMCUS(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_PBDMCUS(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_PBDMCUS
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_PBDMCUS_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_PBDMCUS, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_PBDMCUS, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_PBDMCUS */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_PBDMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_PBDMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_PBDMSW
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_PBDMSW, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_PBDMSW, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_PBDMSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_RSRMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_RSRMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_RSRMSW, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_RSRMSW, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_RSRMSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_PSR_EN(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_PSR_EN(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_PSR_EN
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_PSR_EN, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_PSR_EN, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S50_TXCH0);
    }
#endif /* ComConf_ComSignal_PSR_EN */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_PSR_PSSR(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_PSR_PSSR(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_PSR_PSSR
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_PSR_PSSR, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_PSR_PSSR, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S50_TXCH0);
    }
#endif /* ComConf_ComSignal_PSR_PSSR */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_SR_BACK(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_SR_BACK(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_SR_BACK
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_SR_BACK, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_SR_BACK, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S50_TXCH0);
    }
#endif /* ComConf_ComSignal_SR_BACK */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_SR_COM(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_SR_COM(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_SR_COM
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_SR_COM_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_SR_COM, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_SR_COM, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S50_TXCH0);
    }
#endif /* ComConf_ComSignal_SR_COM */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_SR_DRV(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_SR_DRV(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_SR_DRV
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_SR_DRV_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_SR_DRV, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_SR_DRV, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S50_TXCH0);
    }
#endif /* ComConf_ComSignal_SR_DRV */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_SR_ST(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_SR_ST(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_SR_ST
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_SR_ST, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_SR_ST, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S50_TXCH0);
    }
#endif /* ComConf_ComSignal_SR_ST */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_SR_TOP(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_SR_TOP(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_SR_TOP
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_SR_TOP, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_SR_TOP, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S50_TXCH0);
    }
#endif /* ComConf_ComSignal_SR_TOP */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_CLOCK_SU(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_CLOCK_SU(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_CLOCK_SU
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if((u1_a_OPT <= (U1)VDS_CI_CLOCK_SU_LOCK_UNLOCK)||
       (u1_a_OPT == (U1)VDS_CI_CLOCK_SU_OFF)){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_CLOCK_SU_INIT;
    }

    u1_t_pre_tx = (U1)VDS_CI_CLOCK_SU_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_CLOCK_SU, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_CLOCK_SU, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S62_TXCH0);
    }
#endif /* ComConf_ComSignal_CLOCK_SU */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_M_CUR200(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_M_CUR200(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_M_CUR200
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if((u1_a_OPT <= (U1)VDS_CI_M_CUR200_32A)||
       (u1_a_OPT == (U1)VDS_CI_M_CUR200_MAX)){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_M_CUR200_INIT;
    }

    u1_t_pre_tx = (U1)VDS_CI_M_CUR200_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_M_CUR200, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_M_CUR200, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S62_TXCH0);
    }
#endif /* ComConf_ComSignal_M_CUR200 */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_M_DPWREQ(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_M_DPWREQ(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_M_DPWREQ
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if((u1_a_OPT <= (U1)VDS_CI_M_DPWREQ_350kW)||
       (u1_a_OPT == (U1)VDS_CI_M_DPWREQ_INIT)){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_M_DPWREQ_INIT;
    }

    u1_t_pre_tx = (U1)VDS_CI_M_DPWREQ_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_M_DPWREQ, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_M_DPWREQ, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S62_TXCH0);
    }
#endif /* ComConf_ComSignal_M_DPWREQ */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_M_LMTREQ(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_M_LMTREQ(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_M_LMTREQ
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_M_LMTREQ_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_M_LMTREQ_INIT;
    }

    u1_t_pre_tx = (U1)VDS_CI_M_LMTREQ_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_M_LMTREQ, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_M_LMTREQ, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S62_TXCH0);
    }
#endif /* ComConf_ComSignal_M_LMTREQ */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_M_SLMREQ(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_M_SLMREQ(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_M_SLMREQ
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_M_SLMREQ_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_M_SLMREQ_INIT;
    }
    u1_t_pre_tx = (U1)VDS_CI_M_SLMREQ_INIT;

    (void)Com_ReceiveSignal(ComConf_ComSignal_M_SLMREQ, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_M_SLMREQ, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S62_TXCH0);
    }
#endif /* ComConf_ComSignal_M_SLMREQ */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_MRMRQBK(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_MRMRQBK(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_MRMRQBK
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_MRMRQBK, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_MRMRQBK, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S62_TXCH0);
    }
#endif /* ComConf_ComSignal_MRMRQBK */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_MRMRQSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_MRMRQSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_MRMRQSW
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_MRMRQSW, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_MRMRQSW, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S62_TXCH0);
    }
#endif /* ComConf_ComSignal_MRMRQSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_PWSPL_BK(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_PWSPL_BK(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_PWSPL_BK
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_PWSPL_BK, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_PWSPL_BK, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S62_TXCH0);
    }
#endif /* ComConf_ComSignal_PWSPL_BK */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_PWSPL_OK(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_PWSPL_OK(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_PWSPL_OK
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_PWSPL_OK, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_PWSPL_OK, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S62_TXCH0);
    }
#endif /* ComConf_ComSignal_PWSPL_OK */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_PWSPL_SU(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_PWSPL_SU(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_PWSPL_SU
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_PWSPL_SU_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_PWSPL_SU, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_PWSPL_SU, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S62_TXCH0);
    }
#endif /* ComConf_ComSignal_PWSPL_SU */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_TBCSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_TBCSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_TBCSW
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_TBCSW, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_TBCSW, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S62_TXCH0);
    }
#endif /* ComConf_ComSignal_TBCSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_BSMM_ILV(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_BSMM_ILV(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_BSMM_ILV_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_BSMM_ILV, &u1_t_tx);
#endif /* ComConf_ComSignal_BSMM_ILV */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_IDAMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_IDAMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_IDAMSW
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_IDAMSW, &u1_t_tx);
#endif /* ComConf_ComSignal_IDAMSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_IDASESW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_IDASESW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_IDASESW_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_IDASESW, &u1_t_tx);
#endif /* ComConf_ComSignal_IDASESW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_LCASGMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_LCASGMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_LCASGMSW , &u1_t_tx);
#endif /* ComConf_ComSignal_LCASGMSW  */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_LDASW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_LDASW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_LDASW, &u1_t_tx);
#endif /* ComConf_ComSignal_LDASW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_PKSSVOL(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_PKSSVOL(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_PKSSVOL_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_PKSSVOL, &u1_t_tx);
#endif /* ComConf_ComSignal_PKSSVOL */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_RSR_TIM(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_RSR_TIM(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_RSR_TIM_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_RSR_TIM, &u1_t_tx);
#endif /* ComConf_ComSignal_RSR_TIM */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_RTAN_TIM(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_RTAN_TIM(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_RTAN_TIM_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_RTAN_TIM, &u1_t_tx);
#endif /* ComConf_ComSignal_RTAN_TIM */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_ACCACLSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_ACCACLSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_ACCACLSW_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_ACCACLSW, &u1_t_tx);
#endif /* ComConf_ComSignal_ACCACLSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_ACCRACSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_ACCRACSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_ACCRACSW, &u1_t_tx);
#endif /* ComConf_ComSignal_ACCRACSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_ACCROSSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_ACCROSSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_ACCROSSW, &u1_t_tx);
#endif /* ComConf_ComSignal_ACCROSSW */
}
/*===================================================================================================================================*/
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_ACCSSOSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_ACCSSOSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_ACCSSOSW_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_ACCSSOSW, &u1_t_tx);
#endif /* ComConf_ComSignal_ACCSSOSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_CTAMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_CTAMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_CTAMSW, &u1_t_tx);
#endif /* ComConf_ComSignal_CTAMSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_RTAN_MSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_RTAN_MSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_RTAN_MSW, &u1_t_tx);
#endif /* ComConf_ComSignal_RTAN_MSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_TSR_MAIN(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_TSR_MAIN(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_TSR_MAIN
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_TSR_MAIN, &u1_t_tx);
#endif /* ComConf_ComSignal_TSR_MAIN */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_M_WEEK(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_M_WEEK(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
    /* Not Applicable */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_M_SETID(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_M_SETID(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_M_SETID
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if((u1_a_OPT  <= (U1)VDS_CI_M_SETID_ID_NUM) ||
       ((u1_a_OPT >= (U1)VDS_CI_M_SETID_ADD) && (u1_a_OPT <= (U1)VDS_CI_M_SETID_MAX))){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_M_SETID_INIT;
    }
    u1_t_pre_tx = (U1)VDS_CI_M_SETID_INIT;

    (void)Com_ReceiveSignal(ComConf_ComSignal_M_SETID, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_M_SETID, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S61_TXCH0);
    }
#endif /* ComConf_ComSignal_M_SETID */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_M_SETTYP(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_M_SETTYP(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_M_SETTYP
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if((u1_a_OPT <= (U1)VDS_CI_M_SETTYP_START) ||
       (u1_a_OPT == (U1)VDS_CI_M_SETTYP_MAX)){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_M_SETTYP_INIT;
    }
    u1_t_pre_tx = (U1)VDS_CI_M_SETTYP_INIT;

    (void)Com_ReceiveSignal(ComConf_ComSignal_M_SETTYP, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_M_SETTYP, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S61_TXCH0);
    }
#endif /* ComConf_ComSignal_M_SETTYP */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_M_SETWKD(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_M_SETWKD(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_M_SETWKD
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_M_SETWKD_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_M_SETWKD_INIT;
    }
    u1_t_pre_tx = (U1)VDS_CI_M_SETWKD_INIT;

    (void)Com_ReceiveSignal(ComConf_ComSignal_M_SETWKD, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_M_SETWKD, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S61_TXCH0);
    }
#endif /* ComConf_ComSignal_M_SETWKD */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_CSR_MUTE(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_CSR_MUTE(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_CSR_MUTE
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_CSR_MUTE, &u1_t_tx);
#endif /* ComConf_ComSignal_CSR_MUTE */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_HOFCUS(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_HOFCUS(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_HOFCUS
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_HOFCUS, &u1_t_tx);    /* COM Tx STUB delete */
#endif
#endif /* ComConf_ComSignal_HOFCUS */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_SW_ITS04(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_SW_ITS04(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_SW_ITS04
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_SW_ITS04, &u1_t_tx);
#endif /* ComConf_ComSignal_SW_ITS04 */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_ACCADPSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_ACCADPSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_ACCADPSW
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_ACCADPSW, &u1_t_tx);
#endif /* ComConf_ComSignal_ACCADPSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_LPSDKSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_LPSDKSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_LPSDKSW
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_LPSDKSW, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_LPSDKSW, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_LPSDKSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_LPSDBZVL(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_LPSDBZVL(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_LPSDBZVL
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_LPSDBZVL_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_LPSDBZVL, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_LPSDBZVL, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_LPSDBZVL */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_RPSDBZVL(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_RPSDBZVL(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_RPSDBZVL
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_RPSDBZVL_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_RPSDBZVL, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_RPSDBZVL, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_RPSDBZVL */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_RPSDKSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_RPSDKSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_RPSDKSW
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_RPSDKSW, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_RPSDKSW, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_RPSDKSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_SSMMODE(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_SSMMODE(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_SSMMODE
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_SSMMODE_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_SSMMODE, &u1_t_tx);    /* COM Tx STUB delete */
#endif
#endif /* ComConf_ComSignal_SSMMODE */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_GPFGENSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_GPFGENSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_GPFGENSW
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_GPFGENSW, &u1_t_tx);    /* COM Tx STUB delete */
#endif
#endif /* ComConf_ComSignal_GPFGENSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_GPFINDSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_GPFINDSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_GPFINDSW
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_GPFINDSW, &u1_t_tx);    /* COM Tx STUB delete */
#endif
#endif /* ComConf_ComSignal_GPFINDSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_ACINV_SW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_ACINV_SW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_ACINV_SW, &u1_t_tx);
#endif /* ComConf_ComSignal_ACINV_SW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_SR_NUM(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_SR_NUM(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_SR_NUM
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_SR_NUM_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_SR_NUM, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_SR_NUM, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S50_TXCH0);
    }
#endif /* ComConf_ComSignal_SR_NUM */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_SDGMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_SDGMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_SDGMSW, &u1_t_tx);

#endif /* ComConf_ComSignal_SDGMSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_USMMAIN(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_USMMAIN(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_USMMAIN, &u1_t_tx);

#endif /* ComConf_ComSignal_USMMAIN */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_PDAMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_PDAMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_PDAMSW, &u1_t_tx);

#endif /* ComConf_ComSignal_PDAMSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_DRECSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_DRECSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_DRECSW
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_DRECSW, &u1_t_tx);    /* COM Tx STUB delete */
#endif

#endif /* ComConf_ComSignal_DRECSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_ADDS_MSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_VdsCIReqTx_ADDS_MSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_ADDS_MSW, &u1_t_tx);

#endif /* ComConf_ComSignal_ADDS_MSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_SPBZ_OPE(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_VdsCIReqTx_SPBZ_OPE(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_SPBZ_OPE
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_SPBZ_OPE, &u1_t_tx);

#endif /* ComConf_ComSignal_SPBZ_OPE */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_RSRCANSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_VdsCIReqTx_RSRCANSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_RSRCANSW
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_ReceiveSignal(ComConf_ComSignal_RSRCANSW, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_RSRCANSW, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_RSRCANSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_VRAPRMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_VdsCIReqTx_VRAPRMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_VRAPRMSW
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_VRAPRMSW_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_ReceiveSignal(ComConf_ComSignal_VRAPRMSW, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_VRAPRMSW, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_VRAPRMSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_VRAPMSWS(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_VdsCIReqTx_VRAPMSWS(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_VRAPMSWS
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_VRAPMSWS_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_VRAPMSWS, &u1_t_tx);

#endif /* ComConf_ComSignal_VRAPMSWS */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_VRAPRDIS(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_VdsCIReqTx_VRAPRDIS(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_VRAPRDIS
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_ReceiveSignal(ComConf_ComSignal_VRAPRDIS, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_VRAPRDIS, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_VRAPRDIS */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_RTWMSW  (const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_VdsCIReqTx_RTWMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_RTWMSW, &u1_t_tx);

#endif /* ComConf_ComSignal_RTWMSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_BSD_SMSB  (const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_VdsCIReqTx_BSD_SMSB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_BSD_SMSB, &u1_t_tx);

#endif /* ComConf_ComSignal_BSD_SMSB */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_BSD_SMSS  (const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_VdsCIReqTx_BSD_SMSS(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_BSD_SMSS_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_BSD_SMSS, &u1_t_tx);

#endif /* ComConf_ComSignal_BSD_SMSS */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_SETDCLVI(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_SETDCLVI(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_SETDCLVI
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_SETDCLVI_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_SETDCLVI_INIT;
    }

    u1_t_pre_tx = (U1)VDS_CI_SETDCLVI_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_SETDCLVI, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_SETDCLVI, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S62_TXCH0);
    }
#endif /* ComConf_ComSignal_SETDCLVI */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_SETDCLVM(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_SETDCLVM(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_SETDCLVM
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_SETDCLVM_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_SETDCLVM_INIT;
    }

    u1_t_pre_tx = (U1)VDS_CI_SETDCLVM_INIT;
    (void)Com_ReceiveSignal(ComConf_ComSignal_SETDCLVM, &u1_t_pre_tx);
    (void)Com_SendSignal(ComConf_ComSignal_SETDCLVM, &u1_t_tx);

    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S62_TXCH0);
    }
#endif /* ComConf_ComSignal_SETDCLVM */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_METMDREJ(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_METMDREJ(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_METMDREJ
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_METMDREJ, &u1_t_tx);
#endif /* ComConf_ComSignal_METMDREJ */
}

/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_TRLC_YN(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_TRLC_YN(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_TRLC_YN
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDSCI_TRLC_YN_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_TRLC_YN, &u1_t_tx);

#endif /* ComConf_ComSignal_TRLC_YN */
}

/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_M_SLMDRQ(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_M_SLMDRQ(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_M_SLMDRQ
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDSCI_M_SLMDRQ_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_M_SLMDRQ, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_M_SLMDRQ, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S61_TXCH0);
    }
#endif /* ComConf_ComSignal_M_SLMDRQ */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_TBWSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_VdsCIReqTx_TBWSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_TBWSW
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;
    (void)Com_ReceiveSignal(ComConf_ComSignal_TBWSW, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_TBWSW, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S62_TXCH0);
    }
#endif /* ComConf_ComSignal_TBWSW */
}

/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_ULKMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_ULKMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_ULKMSW
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_ULKMSW, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_ULKMSW, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_ULKMSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_LKMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_LKMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_LKMSW
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_LKMSW, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_LKMSW, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_LKMSW */
}

/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_M_PNCSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_M_PNCSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_M_PNCSW
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_M_PNCSW, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_M_PNCSW, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S62_TXCH0);
    }
#endif /* ComConf_ComSignal_M_PNCSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_LMTDAANS(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_LMTDAANS(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_LMTDAANS
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_LMTDAANS_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_LMTDAANS, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_LMTDAANS, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S62_TXCH0);
    }
#endif /* ComConf_ComSignal_LMTDAANS */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_M_OCOFOK(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_M_OCOFOK(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_M_OCOFOK
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_M_OCOFOK, &u1_t_pre_tx);

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_M_OCOFOK, &u1_t_tx);    /* COM Tx STUB delete */
#endif
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S61_TXCH0);
    }
#endif /* ComConf_ComSignal_M_OCOFOK */
}

/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_SRPMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_SRPMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_SRPMSW, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_SRPMSW, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_SRPMSW */
}

/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_RG_MD_SW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_RG_MD_SW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_RG_MD_SW
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_RG_MD_SW, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_RG_MD_SW, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
    }
#endif /* ComConf_ComSignal_RG_MD_SW */
}

/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_RNGMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_RNGMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_RNGMSW
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_RNGMSW, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_RNGMSW, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S62_TXCH0);
    }
#endif /* ComConf_ComSignal_RNGMSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_LDAAMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_LDAAMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_LDAAMSW_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_LDAAMSW, &u1_t_tx);

#endif /* ComConf_ComSignal_LDAAMSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_RSA_NEM(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_RSA_NEM(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_RSA_NEM_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_RSA_NEM, &u1_t_tx);

#endif /* ComConf_ComSignal_RSA_NEM */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_RSA_LSM(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_RSA_LSM(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_RSA_LSM_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_RSA_LSM, &u1_t_tx);

#endif /* ComConf_ComSignal_RSA_LSM */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_TRA_SW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_TRA_SW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_TRA_SW_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_TRA_SW, &u1_t_tx);

#endif /* ComConf_ComSignal_TRA_SW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_ERMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_ERMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_ERMSW_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_ERMSW, &u1_t_tx);

#endif /* ComConf_ComSignal_ERMSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_ACCSPMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_ACCSPMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_ACCSPMSW_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_ACCSPMSW, &u1_t_tx);

#endif /* ComConf_ComSignal_ACCSPMSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_ACCGCRSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_ACCGCRSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_ACCGCRSW_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_ACCGCRSW, &u1_t_tx);

#endif /* ComConf_ComSignal_ACCGCRSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_CCSMDMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_CCSMDMSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_CCSMDMSW_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_CCSMDMSW, &u1_t_tx);

#endif /* ComConf_ComSignal_CCSMDMSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_SLSSOSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_SLSSOSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_SLSSOSW_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_SLSSOSW, &u1_t_tx);

#endif /* ComConf_ComSignal_SLSSOSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_PMARSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_PMARSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_PMARSW_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_PMARSW, &u1_t_tx);

#endif /* ComConf_ComSignal_PMARSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_DOAM_SW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_DOAM_SW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_DOAM_SW_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_DOAM_SW, &u1_t_tx);

#endif /* ComConf_ComSignal_DOAM_SW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_DOAM_TIM(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_DOAM_TIM(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_DOAM_TIM_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_DOAM_TIM, &u1_t_tx);

#endif /* ComConf_ComSignal_DOAM_TIM */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_TMNVSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_TMNVSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_TMNVSW_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_TMNVSW, &u1_t_tx);

#endif /* ComConf_ComSignal_TMNVSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_TMNSSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_TMNSSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_TMNSSW_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_TMNSSW, &u1_t_tx);

#endif /* ComConf_ComSignal_TMNSSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_ITSSETSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_ITSSETSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_ITSSETSW
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_ITSSETSW_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_ITSSETSW, &u1_t_tx);

#endif /* ComConf_ComSignal_ITSSETSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_DISSUISW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_DISSUISW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_DISSUISW_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_DISSUISW, &u1_t_tx);

#endif /* ComConf_ComSignal_DISSUISW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_DM_SW_A2(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_DM_SW_A2(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_DM_SW_A2_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_DM_SW_A2, &u1_t_tx);

#endif /* ComConf_ComSignal_DM_SW_A2 */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_AHSSWVSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_AHSSWVSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_AHSSWVSW_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_AHSSWVSW, &u1_t_tx);

#endif /* ComConf_ComSignal_AHSSWVSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_AHSSDESW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_AHSSDESW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#if 0  /* BEV provisionally */
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_AHSSDESW_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    (void)Com_SendSignal(ComConf_ComSignal_AHSSDESW, &u1_t_tx);

#endif /* ComConf_ComSignal_AHSSDESW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_M_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_M_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_M_BB
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_M_BB_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_M_BB, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_M_BB, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_M_BB */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_MLR_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_MLR_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_MLR_BB
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_MLR_BB_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_MLR_BB, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_MLR_BB, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_MLR_BB */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_RLM_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_RLM_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_RLM_BB
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_RLM_BB_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_RLM_BB, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_RLM_BB, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_RLM_BB */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_MRT_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_MRT_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_MRT_BB
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_MRT_BB_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_MRT_BB, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_MRT_BB, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_MRT_BB */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_ART_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_ART_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_ART_BB
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_ART_BB_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_ART_BB, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_ART_BB, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_ART_BB */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_PWLSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_PWLSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_PWLSW
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_PWLSW, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_PWLSW, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_PWLSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_WVRD_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_WVRD_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_WVRD_BB
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_WVRD_BB, &u1_t_tx);

#endif /* ComConf_ComSignal_WVRD_BB */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_WVRU_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_WVRU_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_WVRU_BB
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_WVRU_BB, &u1_t_tx);

#endif /* ComConf_ComSignal_WVRU_BB */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_WROF_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_WROF_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_WROF_BB
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_WROF_BB, &u1_t_tx);

#endif /* ComConf_ComSignal_WROF_BB */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_WRLO_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_WRLO_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_WRLO_BB
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_WRLO_BB, &u1_t_tx);

#endif /* ComConf_ComSignal_WRLO_BB */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_WRIN_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_WRIN_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_WRIN_BB
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_WRIN_BB, &u1_t_tx);

#endif /* ComConf_ComSignal_WRIN_BB */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_WRSW_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_WRSW_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_WRSW_BB
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_WRSW_BB, &u1_t_tx);

#endif /* ComConf_ComSignal_WRSW_BB */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_WSVS_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_WSVS_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_WSVS_BB
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_WSVS_BB, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_WSVS_BB, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_WSVS_BB */
}

/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_TRNBBSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_TRNBBSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_TRNBBSW
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_TRNBBSW_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_TRNBBSW, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_TRNBBSW, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S47_TXCH0);
    }
#endif /* ComConf_ComSignal_TRNBBSW */
}

/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_LSW_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_LSW_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_LSW_BB
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_LSW_BB_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_LSW_BB, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_LSW_BB, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_LSW_BB */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_FOG_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_FOG_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_FOG_BB
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_FOG_BB, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_FOG_BB, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_FOG_BB */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_RFG_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_RFG_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_RFG_BB
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_RFG_BB, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_RFG_BB, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_RFG_BB */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_WDI_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_WDI_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_WDI_BB
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_WDI_BB_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_WDI_BB, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_WDI_BB, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_WDI_BB */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_TITE_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_TITE_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_TITE_BB
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_TITE_BB_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_TITE_BB, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_TITE_BB, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_TITE_BB */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_MW_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_MW_BB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_MW_BB
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_MW_BB, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_MW_BB, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
#endif /* ComConf_ComSignal_MW_BB */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_AECOSWBB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_AECOSWBB(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_AECOSWBB
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_AECOSWBB, &u1_t_tx);

#endif /* ComConf_ComSignal_AECOSWBB */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_METMDSEL(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_METMDSEL(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_METMDSEL
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_METMDSEL_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_METMDSEL, &u1_t_tx);

#endif /* ComConf_ComSignal_METMDSEL */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_ACCDSTSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_ACCDSTSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_ACCDSTSW
    U1                 u1_t_tx;

    if(u1_a_OPT <= (U1)VDS_CI_ACCDSTSW_MAX){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_ACCDSTSW, &u1_t_tx);

#endif /* ComConf_ComSignal_ACCDSTSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_HCSUPEN(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_HCSUPEN(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_HCSUPEN
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_HCSUPEN, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_HCSUPEN, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S11_TXCH0);
    }
#endif /* ComConf_ComSignal_HCSUPEN */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_HCSDWEN(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_HCSDWEN(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_HCSDWEN
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_HCSDWEN, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_HCSDWEN, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S11_TXCH0);
    }
#endif /* ComConf_ComSignal_HCSDWEN */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_HCSMNSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_HCSMNSW(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_HCSMNSW
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_HCSMNSW, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_HCSMNSW, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S11_TXCH0);
    }
#endif /* ComConf_ComSignal_HCSMNSW */
}
/*===================================================================================================================================*/
/*  static void    vd_s_VdsCIReqTx_HCSSTPOP(const U1 u1_a_OPT, const U2 u2_a_ELPSD)                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_OPT: send signal value                                                                                      */
/*                  u2_a_ELPSD: elapsed time                                                                                         */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_VdsCIReqTx_HCSSTPOP(const U1 u1_a_OPT, const U2 u2_a_ELPSD)
{
#ifdef ComConf_ComSignal_HCSSTPOP
    U1                 u1_t_tx;
    U1                 u1_t_pre_tx;

    if(u1_a_OPT <= (U1)VDS_CI_OPT_ON){
        u1_t_tx = u1_a_OPT;
    }
    else{
        u1_t_tx = (U1)VDS_CI_OPT_OFF;
    }
    u1_t_pre_tx = (U1)VDS_CI_OPT_OFF;

    (void)Com_ReceiveSignal(ComConf_ComSignal_HCSSTPOP, &u1_t_pre_tx);

    (void)Com_SendSignal(ComConf_ComSignal_HCSSTPOP, &u1_t_tx);
    if(u1_t_pre_tx != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S11_TXCH0);
    }
#endif /* ComConf_ComSignal_HCSSTPOP */
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     2/25/2020  TN       New.                                                                                               */
/*  1.1.0     7/20/2020  TH       Config for 800B CV-R                                                                               */
/*  2.1.1    10/18/2021  TA(M)    vds_ci.c v1.1.0 -> v2.1.1                                                                          */
/*  2.2.0    10/06/2022  TA(M)    vds_ci.c v2.1.1 -> v2.2.0                                                                          */
/*  2.3.0     3/22/2024  SW       vds_ci.c v2.2.0 -> v2.3.0 (add member for transmission mask to ST_VDS_CI_TRX)                      */
/*  2.4.0     1/30/2025  KO       vds_ci.c v2.3.0 -> v2.4.0                                                                          */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/* 19PFv3-1  09/15/2023  SN       Merge Config                                                                                       */
/* 19PFv3-2  11/10/2023  TH(K)    Change config for 19PFv3 CV                                                                        */
/* 19PFv3-3  12/28/2023  AA       Added config for TCHAR                                                                             */
/* 19PFv3-4  01/16/2024  SN       Change vd_s_VdsCIReqTx_PLUSSW                                                                      */
/* 19PFv3-5  01/29/2024  AA       Change config for TPACP                                                                            */
/* 19PFv3-6  02/06/2024  AA       Added config for ACDCSUP                                                                           */
/* 19PFv3-7  02/14/2024  DR       Change config for TIMCHG                                                                           */
/* 19PFv3-8  02/20/2024  GM       Change config for 19PFv3 CV                                                                        */
/* 19PFv3-9  02/20/2024  HF       Change config for SWQUICHA                                                                         */
/* 19PFv3-9  03/22/2024  SW       Set new config for M_GTW                                                                           */
/* 19PFv3-10 04/08/2024  SN       Change config for ADASCS                                                                           */
/* 19PFv3-11 05/07/2024  TR       Change config for 19PFv3 CV                                                                        */
/* 19PFv3-12 07/10/2024  YR       Added config for HCS                                                                               */
/* BEV-1     10/10/2024  KT       Change config for BEV System_Consideration_1.(MET-B_OMRBB-CSTD-0-)                                 */
/* BEV-2     01/30/2025  KO       Change config for BEV System_Consideration_1.(MET-C_HCS-CSTD-0-)                                   */
/* BEV-3     01/31/2025  HY       Change config for BEV System_Consideration_1.(MET-B_PWLBB-CSTD-0-)                                 */
/* BEV-4     01/31/2025  HY       Change config for BEV System_Consideration_1.(MET-B_WPBB-CSTD-0-)                                  */
/* BEV-5     02/10/2025  RO       Change config for BEV System_Consideration_1.(MET-S_ADMID-CSTD-0-)                                 */
/* BEV-6     02/10/2025  RO       Change config for BEV System_Consideration_1.(MET-S_ADVMID-CSTD-0-)                                */
/* BEV-7     02/10/2025  HF       Change config for BEV System_Consideration_1.(MET-B_LMPBB-CSTD-0-)                                 */
/* BEV-8     02/10/2025  SF       Change for BEV System_Consideration_1.(MET-M_ONOFF-CSTD-1-02-A-C0)                                 */
/* BEV-9     03/06/2025  HT       Change for BEV System_Consideration_1.(MET-B_WDICBB-CSTD-0-01-A-C0)                                */
/* BEV-10    03/06/2025  HT       Change for BEV System_Consideration_1.(MET-B_TITEBB-CSTD-0-00-A-C0)                                */
/* BEV-11    03/06/2025  HT       Change for BEV System_Consideration_1.(MET-B_MWBB-CSTD-0-00-A-C0)                                  */
/* BEV-12    03/06/2025  HT       Change for BEV System_Consideration_1.(MET-S_ADBB-CSTD-0-01-A-C0)                                  */
/* BEV-13    03/06/2025  HT       Change for BEV System_Consideration_1.(MET-C_HCSBSW-CSTD-0-01-A-C0)                                */
/* BEV-14    03/14/2025  KT       Change for BEV System_Consideration_1.(Delete Signal for BitAssign6.5)                             */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * TH   = Takahiro Hirano, Denso Techno                                                                                           */
/*  * TA(M)= Teruyuki Anjima, NTT Data MSE                                                                                           */
/*  * SN   = Shimon Nambu, Denso Techno                                                                                              */
/*  * TH(K)= Taisuke Hirakawa, KSE                                                                                                   */
/*  * AA   = Anna Asuncion, Denso Techno                                                                                             */
/*  * DR   = Dyan Reyes, DTPH                                                                                                        */
/*  * GM   = Glen Monteposo, DTPH                                                                                                    */
/*  * HF   = Hinari Fukamachi, KSE                                                                                                   */
/*  * SW   = Shun Watanabe, Denso Techno                                                                                             */
/*  * SN   = Shimon Nambu, Denso Techno                                                                                              */
/*  * TR   = Tebs Ramos,   DTPH                                                                                                      */
/*  * YR   = Yhana Regalario, DTPH                                                                                                   */
/*  * KO   = Kazuto Oishi,  Denso Techno                                                                                             */
/*  * HY   = Haruki Yagi, KSE                                                                                                        */
/*  * RO   = Ryo Oohashi, KSE                                                                                                        */
/*  * HF   = Hinari Fukamachi, KSE                                                                                                   */
/*  * SF   = Shiro Furui, Denso Techno                                                                                               */
/*  * HT   = Hibiki Tanii, KSE                                                                                                       */
/*  * KT   = Kenta Takaji, Denso Techno                                                                                              */
/*                                                                                                                                   */
/*===================================================================================================================================*/
