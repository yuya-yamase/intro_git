/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Can Tx Application                                                                                                               */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define CANTXAPPDUM_CFG_C_MAJOR                     (0)
#define CANTXAPPDUM_CFG_C_MINOR                     (0)
#define CANTXAPPDUM_CFG_C_PATCH                     (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "cantxappdum_cfg.h"
#include "cantxappdum_cfg_private.h"
#include "oxcan.h"
#include "ivdsh.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((CANTXAPPDUM_CFG_C_MAJOR != CANTXAPPDUM_CFG_H_MAJOR) || \
     (CANTXAPPDUM_CFG_C_MINOR != CANTXAPPDUM_CFG_H_MINOR) || \
     (CANTXAPPDUM_CFG_C_PATCH != CANTXAPPDUM_CFG_H_PATCH))
#error "cantxappdum_cfg.c and cantxappdum_cfg.h : source and header files are inconsistent!"
#endif

#if ((CANTXAPPDUM_CFG_C_MAJOR != CANTXAPPDUM_CFG_PRIVATE_H_MAJOR) || \
     (CANTXAPPDUM_CFG_C_MINOR != CANTXAPPDUM_CFG_PRIVATE_H_MINOR) || \
     (CANTXAPPDUM_CFG_C_PATCH != CANTXAPPDUM_CFG_PRIVATE_H_PATCH))
#error "cantxappdum_cfg.c and cantxappdum_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_CANTXAPPDUM_READ_BIT(u1_buf , u1_pos , u1_len) (((u1_buf)  >> (u1_pos)) & ((1U << (u1_len)) - 1U))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void vd_s_CanTxAppDumDMS1S02(void);
static void vd_s_CanTxAppDumMET1S27(void);
static void vd_s_CanTxAppDumMET1S28(void);
static void vd_s_CanTxAppDumMET1S29(void);
static void vd_s_CanTxAppDumMET1S30(void);
static void vd_s_CanTxAppDumMET1S43(void);
static void vd_s_CanTxAppDumMET1S62(void);
static void vd_s_CanTxAppDumMET1S70(void);

/* DMS1S02 */
static void    vd_s_CanTxAppDum_R1_MD_SW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_TW_MD_SW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_CH_MD_SW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_P1_MD_SW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_RG_MD_SW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_PW_MD_SW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_EC_MD_SW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_NR_MD_SW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_CS_MD_SW(U1 * u1p_a_flame);
/* MET1S27 */
static void    vd_s_CanTxAppDum_SW_LTC01(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_SW_RCD01(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_TSR_OSL(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_TSR_SNM(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_ITSSETSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_RCTAMSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_ICSMSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_BSMMSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_CSRMSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_SW_ITS04(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_TSR_MAIN(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_LDAMCUS(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_PCSMSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_FCMMSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_LDA_SFB(U1 * u1p_a_flame);
/* MET1S28 */
static void    vd_s_CanTxAppDum_ACINV_SW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_RSCSW_OP(U1 * u1p_a_flame);
/* MET1S29 */
static void    vd_s_CanTxAppDum_SW_AS01(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_SW_AS02(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_TPUNTSET(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_TPINSEL(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_TPINSELR(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_TPINSELF(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_SW_AS05(U1 * u1p_a_flame);
/* MET1S30 */
static void    vd_s_CanTxAppDum_SRPMSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_MINTRSOF(U1 * u1p_a_flame);
/* MET1S43 */
static void    vd_s_CanTxAppDum_SPBZ_OPE(U1 * u1p_a_flame);
/* MET1S62 */
static void    vd_s_CanTxAppDum_TBCSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_TBWSW(U1 * u1p_a_flame);
/* MET1S70 */
static void    vd_s_CanTxAppDum_LCASGMSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_IDAMSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_IDASESW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_BSD_SMSB(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_BSD_SMSS(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_RSR_TIM(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_DOAM_SW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_LDASW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_DOAM_TIM(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_BSMM_ILV(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_RTAN_TIM(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_RTAN_MSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_SDGMSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_PDAMSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_RSA_NEM(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_RSA_LSM(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_PMARSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_ADDS_MSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_LDAAMSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_TMNVSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_TMNSSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_DM_SW_A2(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_DISSUISW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_SLDMSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_SLSSSSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_ADADDRSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_ADOTASSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_ADDMCRSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_ADSVSSSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_ADCVVSSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_ACCSSOSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_ACCRACSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_ACCROSSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_AHSACTSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_AHBACTSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_ACCACLSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_ACCSPMSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_USMMAIN(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_SLSSOSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_CTAMSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_ACCGCRSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_RTWMSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_AHSSDESW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_AHSSWVSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_CCSMDMSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_ERMSW(U1 * u1p_a_flame);
static void    vd_s_CanTxAppDum_TRA_SW(U1 * u1p_a_flame);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_CanTxAppDumCfgInit(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
#if 0
void    vd_g_CanTxAppDumCfgInit(void)
{
    vd_g_CanTxAppDumMET1S29_Init();
}
#endif
/*===================================================================================================================================*/
/*  void    vd_g_CanTxAppDumCfgMainTask(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_CanTxAppDumCfgMainTask(void)
{
    vd_s_CanTxAppDumDMS1S02();
    vd_s_CanTxAppDumMET1S27();
    vd_s_CanTxAppDumMET1S28();
    vd_s_CanTxAppDumMET1S29();
    vd_s_CanTxAppDumMET1S30();
    vd_s_CanTxAppDumMET1S43();
    vd_s_CanTxAppDumMET1S62();
    vd_s_CanTxAppDumMET1S70();
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumDMS1S02(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDumDMS1S02(void)
{
    U1    u1_t_sts;
    U1  * u1p_t_dms1s02;
    U4    u4_t_dms1s02_addr;

    u1_t_sts     = u1_g_iVDshReabyDid((U1)IVDSH_DID_REA_VM2TO1_DMS1S02, &u4_t_dms1s02_addr, (U1)1U);

    if((u1_t_sts          != (U1)IVDSH_NO_REA) && 
       (u4_t_dms1s02_addr != vdp_PTR_NA)){
        u1p_t_dms1s02 = (U1 *)u4_t_dms1s02_addr;
        vd_s_CanTxAppDum_R1_MD_SW(u1p_t_dms1s02);
        vd_s_CanTxAppDum_TW_MD_SW(u1p_t_dms1s02);
        vd_s_CanTxAppDum_CH_MD_SW(u1p_t_dms1s02);
        vd_s_CanTxAppDum_P1_MD_SW(u1p_t_dms1s02);
        vd_s_CanTxAppDum_RG_MD_SW(u1p_t_dms1s02);
        vd_s_CanTxAppDum_PW_MD_SW(u1p_t_dms1s02);
        vd_s_CanTxAppDum_EC_MD_SW(u1p_t_dms1s02);
        vd_s_CanTxAppDum_NR_MD_SW(u1p_t_dms1s02);
        vd_s_CanTxAppDum_CS_MD_SW(u1p_t_dms1s02);
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumMET1S27(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDumMET1S27(void)
{
    U1    u1_t_sts;
    U1  * u1p_t_met1s27;
    U4    u4_t_met1s27_addr;

    u1_t_sts     = u1_g_iVDshReabyDid((U1)IVDSH_DID_REA_VM2TO1_MET1S27, &u4_t_met1s27_addr, (U1)1U);

    if((u1_t_sts          != (U1)IVDSH_NO_REA) && 
       (u4_t_met1s27_addr != vdp_PTR_NA)){
        u1p_t_met1s27 = (U1 *)u4_t_met1s27_addr;
        vd_s_CanTxAppDum_SW_LTC01(u1p_t_met1s27);
        vd_s_CanTxAppDum_SW_RCD01(u1p_t_met1s27);
        vd_s_CanTxAppDum_TSR_OSL(u1p_t_met1s27);
        vd_s_CanTxAppDum_TSR_SNM(u1p_t_met1s27);
        vd_s_CanTxAppDum_ITSSETSW(u1p_t_met1s27);
        vd_s_CanTxAppDum_RCTAMSW(u1p_t_met1s27);
        vd_s_CanTxAppDum_ICSMSW(u1p_t_met1s27);
        vd_s_CanTxAppDum_BSMMSW(u1p_t_met1s27);
        vd_s_CanTxAppDum_CSRMSW(u1p_t_met1s27);
        vd_s_CanTxAppDum_SW_ITS04(u1p_t_met1s27);
        vd_s_CanTxAppDum_TSR_MAIN(u1p_t_met1s27);
        vd_s_CanTxAppDum_LDAMCUS(u1p_t_met1s27);
        vd_s_CanTxAppDum_PCSMSW(u1p_t_met1s27);
        vd_s_CanTxAppDum_FCMMSW(u1p_t_met1s27);
        vd_s_CanTxAppDum_LDA_SFB(u1p_t_met1s27);
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumMET1S28(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDumMET1S28(void)
{
    U1    u1_t_sts;
    U1  * u1p_t_met1s28;
    U4    u4_t_met1s28_addr;

    u1_t_sts     = u1_g_iVDshReabyDid((U1)IVDSH_DID_REA_VM2TO1_MET1S28, &u4_t_met1s28_addr, (U1)1U);

    if((u1_t_sts          != (U1)IVDSH_NO_REA) && 
       (u4_t_met1s28_addr != vdp_PTR_NA)){
        u1p_t_met1s28 = (U1 *)u4_t_met1s28_addr;
        vd_s_CanTxAppDum_ACINV_SW(u1p_t_met1s28);
        vd_s_CanTxAppDum_RSCSW_OP(u1p_t_met1s28);
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumMET1S29(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDumMET1S29(void)
{
    U1    u1_t_sts;
    U1  * u1p_t_met1s29;
    U4    u4_t_met1s29_addr;

    u1_t_sts     = u1_g_iVDshReabyDid((U1)IVDSH_DID_REA_VM2TO1_MET1S29, &u4_t_met1s29_addr, (U1)1U);

    if((u1_t_sts          != (U1)IVDSH_NO_REA) && 
       (u4_t_met1s29_addr != vdp_PTR_NA)){
        u1p_t_met1s29 = (U1 *)u4_t_met1s29_addr;
        vd_s_CanTxAppDum_SW_AS01(u1p_t_met1s29);
        vd_s_CanTxAppDum_SW_AS02(u1p_t_met1s29);
        vd_s_CanTxAppDum_TPUNTSET(u1p_t_met1s29);
        vd_s_CanTxAppDum_TPINSEL(u1p_t_met1s29);
        vd_s_CanTxAppDum_TPINSELR(u1p_t_met1s29);
        vd_s_CanTxAppDum_TPINSELF(u1p_t_met1s29);
        vd_s_CanTxAppDum_SW_AS05(u1p_t_met1s29);
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumMET1S30(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDumMET1S30(void)
{
    U1    u1_t_sts;
    U1  * u1p_t_met1s30;
    U4    u4_t_met1s30_addr;

    u1_t_sts     = u1_g_iVDshReabyDid((U1)IVDSH_DID_REA_VM2TO1_MET1S30, &u4_t_met1s30_addr, (U1)1U);

    if((u1_t_sts          != (U1)IVDSH_NO_REA) && 
       (u4_t_met1s30_addr != vdp_PTR_NA)){
        u1p_t_met1s30 = (U1 *)u4_t_met1s30_addr;
        vd_s_CanTxAppDum_SRPMSW(u1p_t_met1s30);
        vd_s_CanTxAppDum_MINTRSOF(u1p_t_met1s30);
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumMET1S43(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDumMET1S43(void)
{
    U1    u1_t_sts;
    U1  * u1p_t_met1s43;
    U4    u4_t_met1s43_addr;

    u1_t_sts     = u1_g_iVDshReabyDid((U1)IVDSH_DID_REA_VM2TO1_MET1S43, &u4_t_met1s43_addr, (U1)1U);

    if((u1_t_sts          != (U1)IVDSH_NO_REA) && 
       (u4_t_met1s43_addr != vdp_PTR_NA)){
        u1p_t_met1s43 = (U1 *)u4_t_met1s43_addr;
        vd_s_CanTxAppDum_SPBZ_OPE(u1p_t_met1s43);
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumMET1S62(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDumMET1S62(void)
{
    U1    u1_t_sts;
    U1  * u1p_t_met1s62;
    U4    u4_t_met1s62_addr;

    u1_t_sts     = u1_g_iVDshReabyDid((U1)IVDSH_DID_REA_VM2TO1_MET1S62, &u4_t_met1s62_addr, (U1)1U);

    if((u1_t_sts          != (U1)IVDSH_NO_REA) && 
       (u4_t_met1s62_addr != vdp_PTR_NA)){
        u1p_t_met1s62 = (U1 *)u4_t_met1s62_addr;
        vd_s_CanTxAppDum_TBCSW(u1p_t_met1s62);
        vd_s_CanTxAppDum_TBWSW(u1p_t_met1s62);
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumMET1S70(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDumMET1S70(void)
{
    U1    u1_t_sts;
    U1  * u1p_t_met1s70;
    U4    u4_t_met1s70_addr;

    u1_t_sts     = u1_g_iVDshReabyDid((U1)IVDSH_DID_REA_VM2TO1_MET1S70, &u4_t_met1s70_addr, (U1)1U);

    if((u1_t_sts          != (U1)IVDSH_NO_REA) && 
       (u4_t_met1s70_addr != vdp_PTR_NA)){
        u1p_t_met1s70 = (U1 *)u4_t_met1s70_addr;
        vd_s_CanTxAppDum_LCASGMSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_IDAMSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_IDASESW(u1p_t_met1s70);
        vd_s_CanTxAppDum_BSD_SMSB(u1p_t_met1s70);
        vd_s_CanTxAppDum_BSD_SMSS(u1p_t_met1s70);
        vd_s_CanTxAppDum_RSR_TIM(u1p_t_met1s70);
        vd_s_CanTxAppDum_DOAM_SW(u1p_t_met1s70);
        vd_s_CanTxAppDum_LDASW(u1p_t_met1s70);
        vd_s_CanTxAppDum_DOAM_TIM(u1p_t_met1s70);
        vd_s_CanTxAppDum_BSMM_ILV(u1p_t_met1s70);
        vd_s_CanTxAppDum_RTAN_TIM(u1p_t_met1s70);
        vd_s_CanTxAppDum_RTAN_MSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_SDGMSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_PDAMSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_RSA_NEM(u1p_t_met1s70);
        vd_s_CanTxAppDum_RSA_LSM(u1p_t_met1s70);
        vd_s_CanTxAppDum_PMARSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_ADDS_MSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_LDAAMSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_TMNVSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_TMNSSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_DM_SW_A2(u1p_t_met1s70);
        vd_s_CanTxAppDum_DISSUISW(u1p_t_met1s70);
        vd_s_CanTxAppDum_SLDMSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_SLSSSSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_ADADDRSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_ADOTASSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_ADDMCRSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_ADSVSSSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_ADCVVSSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_ACCSSOSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_ACCRACSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_ACCROSSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_AHSACTSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_AHBACTSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_ACCACLSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_ACCSPMSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_USMMAIN(u1p_t_met1s70);
        vd_s_CanTxAppDum_SLSSOSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_CTAMSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_ACCGCRSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_RTWMSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_AHSSDESW(u1p_t_met1s70);
        vd_s_CanTxAppDum_AHSSWVSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_CCSMDMSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_ERMSW(u1p_t_met1s70);
        vd_s_CanTxAppDum_TRA_SW(u1p_t_met1s70);
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumR1_MD_SW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_R1_MD_SW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;
    U1    u1_t_tx_pre;

    u1_t_tx     = (U1)0U;
    u1_t_tx_pre = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[0], (U1)7U, (U1)1U);
    (void)Com_ReceiveSignal(ComConf_ComSignal_R1_MD_SW, &u1_t_tx_pre);
    (void)Com_SendSignal(ComConf_ComSignal_R1_MD_SW,    &u1_t_tx);

    if(u1_t_tx_pre != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumTW_MD_SW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_TW_MD_SW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;
    U1    u1_t_tx_pre;

    u1_t_tx     = (U1)0U;
    u1_t_tx_pre = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[3], (U1)7U, (U1)1U);
    (void)Com_ReceiveSignal(ComConf_ComSignal_TW_MD_SW, &u1_t_tx_pre);
    (void)Com_SendSignal(ComConf_ComSignal_TW_MD_SW,    &u1_t_tx);

    if(u1_t_tx_pre != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumCH_MD_SW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_CH_MD_SW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;
    U1    u1_t_tx_pre;

    u1_t_tx     = (U1)0U;
    u1_t_tx_pre = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[3], (U1)4U, (U1)1U);
    (void)Com_ReceiveSignal(ComConf_ComSignal_CH_MD_SW, &u1_t_tx_pre);
    (void)Com_SendSignal(ComConf_ComSignal_CH_MD_SW,    &u1_t_tx);

    if(u1_t_tx_pre != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumP1_MD_SW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_P1_MD_SW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;
    U1    u1_t_tx_pre;

    u1_t_tx     = (U1)0U;
    u1_t_tx_pre = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[3], (U1)3U, (U1)1U);
    (void)Com_ReceiveSignal(ComConf_ComSignal_P1_MD_SW, &u1_t_tx_pre);
    (void)Com_SendSignal(ComConf_ComSignal_P1_MD_SW,    &u1_t_tx);

    if(u1_t_tx_pre != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumRG_MD_SW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_RG_MD_SW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;
    U1    u1_t_tx_pre;

    u1_t_tx     = (U1)0U;
    u1_t_tx_pre = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[3], (U1)2U, (U1)1U);
    (void)Com_ReceiveSignal(ComConf_ComSignal_RG_MD_SW, &u1_t_tx_pre);
    (void)Com_SendSignal(ComConf_ComSignal_RG_MD_SW,    &u1_t_tx);

    if(u1_t_tx_pre != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumPW_MD_SW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_PW_MD_SW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;
    U1    u1_t_tx_pre;

    u1_t_tx     = (U1)0U;
    u1_t_tx_pre = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[4], (U1)6U, (U1)1U);
    (void)Com_ReceiveSignal(ComConf_ComSignal_PW_MD_SW, &u1_t_tx_pre);
    (void)Com_SendSignal(ComConf_ComSignal_PW_MD_SW,    &u1_t_tx);

    if(u1_t_tx_pre != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumEC_MD_SW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_EC_MD_SW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;
    U1    u1_t_tx_pre;

    u1_t_tx     = (U1)0U;
    u1_t_tx_pre = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[4], (U1)3U, (U1)1U);
    (void)Com_ReceiveSignal(ComConf_ComSignal_EC_MD_SW, &u1_t_tx_pre);
    (void)Com_SendSignal(ComConf_ComSignal_EC_MD_SW,    &u1_t_tx);

    if(u1_t_tx_pre != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumNR_MD_SW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_NR_MD_SW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;
    U1    u1_t_tx_pre;

    u1_t_tx     = (U1)0U;
    u1_t_tx_pre = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[4], (U1)2U, (U1)1U);
    (void)Com_ReceiveSignal(ComConf_ComSignal_NR_MD_SW, &u1_t_tx_pre);
    (void)Com_SendSignal(ComConf_ComSignal_NR_MD_SW,    &u1_t_tx);

    if(u1_t_tx_pre != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumCS_MD_SW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_CS_MD_SW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;
    U1    u1_t_tx_pre;

    u1_t_tx     = (U1)0U;
    u1_t_tx_pre = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[4], (U1)1U, (U1)1U);
    (void)Com_ReceiveSignal(ComConf_ComSignal_CS_MD_SW, &u1_t_tx_pre);
    (void)Com_SendSignal(ComConf_ComSignal_CS_MD_SW,    &u1_t_tx);

    if(u1_t_tx_pre != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_DMS1S02_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumSW_LTC01(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_SW_LTC01(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[0], (U1)2U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_SW_LTC01,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumSW_RCD01(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_SW_RCD01(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[0], (U1)0U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_SW_RCD01,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumTSR_OSL(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_TSR_OSL(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[1], (U1)3U, (U1)2U);

    (void)Com_SendSignal(ComConf_ComSignal_TSR_OSL,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumTSR_SNM(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_TSR_SNM(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[2], (U1)1U, (U1)2U);

    (void)Com_SendSignal(ComConf_ComSignal_TSR_SNM,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumITSSETSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_ITSSETSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[3], (U1)2U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_ITSSETSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumRCTAMSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_RCTAMSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[4], (U1)7U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_RCTAMSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumICSMSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_ICSMSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[4], (U1)6U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_ICSMSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumBSMMSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_BSMMSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[4], (U1)5U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_BSMMSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumCSRMSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_CSRMSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[4], (U1)2U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_CSRMSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumSW_ITS04(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_SW_ITS04(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[4], (U1)1U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_SW_ITS04,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumTSR_MAIN(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_TSR_MAIN(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[4], (U1)0U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_TSR_MAIN,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumLDAMCUS(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_LDAMCUS(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[5], (U1)6U, (U1)2U);

    (void)Com_SendSignal(ComConf_ComSignal_LDAMCUS,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumPCSMSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_PCSMSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[5], (U1)0U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_PCSMSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumFCMMSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_FCMMSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[6], (U1)4U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_FCMMSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumLDA_SFB(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_LDA_SFB(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[6], (U1)0U, (U1)3U);

    (void)Com_SendSignal(ComConf_ComSignal_LDA_SFB,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumACINV_SW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_ACINV_SW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[0], (U1)7U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_ACINV_SW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumRSCSW_OP(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_RSCSW_OP(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[1], (U1)0U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_RSCSW_OP,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumSW_AS01(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_SW_AS01(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[0], (U1)7U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_SW_AS01,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumSW_AS02(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_SW_AS02(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[0], (U1)6U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_SW_AS02,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumTPUNTSET(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_TPUNTSET(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[1], (U1)5U, (U1)3U);

    (void)Com_SendSignal(ComConf_ComSignal_TPUNTSET,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumTPINSEL(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_TPINSEL(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[1], (U1)0U, (U1)4U);

    (void)Com_SendSignal(ComConf_ComSignal_TPINSEL,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumTPINSELR(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_TPINSELR(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[2], (U1)4U, (U1)3U);

    (void)Com_SendSignal(ComConf_ComSignal_TPINSELR,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumTPINSELF(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_TPINSELF(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[2], (U1)0U, (U1)3U);

    (void)Com_SendSignal(ComConf_ComSignal_TPINSELF,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumSW_AS05(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_SW_AS05(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[3], (U1)6U, (U1)2U);

    (void)Com_SendSignal(ComConf_ComSignal_SW_AS05,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumSRPMSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_SRPMSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;
    U1    u1_t_tx_pre;

    u1_t_tx     = (U1)0U;
    u1_t_tx_pre = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[1], (U1)6U, (U1)1U);
    (void)Com_ReceiveSignal(ComConf_ComSignal_SRPMSW, &u1_t_tx_pre);
    (void)Com_SendSignal(ComConf_ComSignal_SRPMSW,    &u1_t_tx);

    if(u1_t_tx_pre != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumMINTRSOF(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_MINTRSOF(U1 * u1p_a_flame)
{
    U1    u1_t_tx;
    U1    u1_t_tx_pre;

    u1_t_tx     = (U1)0U;
    u1_t_tx_pre = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[4], (U1)7U, (U1)1U);
    (void)Com_ReceiveSignal(ComConf_ComSignal_MINTRSOF, &u1_t_tx_pre);
    (void)Com_SendSignal(ComConf_ComSignal_MINTRSOF,    &u1_t_tx);

    if(u1_t_tx_pre != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S30_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumSPBZ_OPE(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_SPBZ_OPE(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[7], (U1)7U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_SPBZ_OPE,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumTBCSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_TBCSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;
    U1    u1_t_tx_pre;

    u1_t_tx     = (U1)0U;
    u1_t_tx_pre = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[5], (U1)1U, (U1)1U);
    (void)Com_ReceiveSignal(ComConf_ComSignal_TBCSW, &u1_t_tx_pre);
    (void)Com_SendSignal(ComConf_ComSignal_TBCSW,    &u1_t_tx);

    if(u1_t_tx_pre != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S62_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumTBWSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_TBWSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;
    U1    u1_t_tx_pre;

    u1_t_tx     = (U1)0U;
    u1_t_tx_pre = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[5], (U1)0U, (U1)1U);
    (void)Com_ReceiveSignal(ComConf_ComSignal_TBWSW, &u1_t_tx_pre);
    (void)Com_SendSignal(ComConf_ComSignal_TBWSW,    &u1_t_tx);

    if(u1_t_tx_pre != u1_t_tx){
        (void)Com_TriggerIPDUSend(MSG_MET1S62_TXCH0);
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumLCASGMSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_LCASGMSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[0], (U1)5U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_LCASGMSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumIDAMSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_IDAMSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[1], (U1)6U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_IDAMSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumIDASESW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_IDASESW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[1], (U1)4U, (U1)2U);

    (void)Com_SendSignal(ComConf_ComSignal_IDASESW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumBSD_SMSB(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_BSD_SMSB(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[1], (U1)2U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_BSD_SMSB,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumBSD_SMSS(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_BSD_SMSS(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[1], (U1)0U, (U1)2U);

    (void)Com_SendSignal(ComConf_ComSignal_BSD_SMSS,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumRSR_TIM(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_RSR_TIM(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[2], (U1)5U, (U1)3U);

    (void)Com_SendSignal(ComConf_ComSignal_RSR_TIM,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumDOAM_SW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_DOAM_SW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[2], (U1)4U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_DOAM_SW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumLDASW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_LDASW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[2], (U1)0U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_LDASW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumDOAM_TIM(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_DOAM_TIM(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[3], (U1)6U, (U1)2U);

    (void)Com_SendSignal(ComConf_ComSignal_DOAM_TIM,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumBSMM_ILV(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_BSMM_ILV(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[3], (U1)4U, (U1)2U);

    (void)Com_SendSignal(ComConf_ComSignal_BSMM_ILV,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumRTAN_TIM(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_RTAN_TIM(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[3], (U1)2U, (U1)2U);

    (void)Com_SendSignal(ComConf_ComSignal_RTAN_TIM,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumRTAN_MSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_RTAN_MSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[3], (U1)1U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_RTAN_MSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumSDGMSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_SDGMSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[4], (U1)1U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_SDGMSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumPDAMSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_PDAMSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[4], (U1)0U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_PDAMSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumRSA_NEM(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_RSA_NEM(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[5], (U1)5U, (U1)3U);

    (void)Com_SendSignal(ComConf_ComSignal_RSA_NEM,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumRSA_LSM(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_RSA_LSM(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[5], (U1)2U, (U1)3U);

    (void)Com_SendSignal(ComConf_ComSignal_RSA_LSM,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumPMARSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_PMARSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[5], (U1)1U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_PMARSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumADDS_MSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_ADDS_MSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[5], (U1)0U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_ADDS_MSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumLDAAMSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_LDAAMSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[6], (U1)5U, (U1)3U);

    (void)Com_SendSignal(ComConf_ComSignal_LDAAMSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumTMNVSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_TMNVSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[6], (U1)2U, (U1)3U);

    (void)Com_SendSignal(ComConf_ComSignal_TMNVSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumTMNSSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_TMNSSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx    = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[7], (U1)7U, (U1)1U);
    u1_t_tx   |= u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[6], (U1)0U, (U1)2U) << 1;


    (void)Com_SendSignal(ComConf_ComSignal_TMNSSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumDM_SW_A2(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_DM_SW_A2(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[7], (U1)4U, (U1)3U);

    (void)Com_SendSignal(ComConf_ComSignal_DM_SW_A2,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumDISSUISW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_DISSUISW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[7], (U1)3U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_DISSUISW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumSLDMSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_SLDMSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[8], (U1)7U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_SLDMSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumSLSSSSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_SLSSSSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[8], (U1)5U, (U1)2U);

    (void)Com_SendSignal(ComConf_ComSignal_SLSSSSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumADADDRSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_ADADDRSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[13], (U1)6U, (U1)2U);

    (void)Com_SendSignal(ComConf_ComSignal_ADADDRSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumADOTASSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_ADOTASSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[13], (U1)4U, (U1)2U);

    (void)Com_SendSignal(ComConf_ComSignal_ADOTASSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumADDMCRSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_ADDMCRSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[15], (U1)6U, (U1)2U);

    (void)Com_SendSignal(ComConf_ComSignal_ADDMCRSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumADSVSSSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_ADSVSSSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[16], (U1)6U, (U1)2U);

    (void)Com_SendSignal(ComConf_ComSignal_ADSVSSSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumADCVVSSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_ADCVVSSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[16], (U1)2U, (U1)2U);

    (void)Com_SendSignal(ComConf_ComSignal_ADCVVSSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumACCSSOSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_ACCSSOSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[17], (U1)6U, (U1)2U);

    (void)Com_SendSignal(ComConf_ComSignal_ACCSSOSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumACCRACSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_ACCRACSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[17], (U1)5U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_ACCRACSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumACCROSSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_ACCROSSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[17], (U1)3U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_ACCROSSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumAHSACTSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_AHSACTSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[17], (U1)2U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_AHSACTSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumAHBACTSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_AHBACTSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[17], (U1)1U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_AHBACTSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumACCACLSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_ACCACLSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[18], (U1)5U, (U1)3U);

    (void)Com_SendSignal(ComConf_ComSignal_ACCACLSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumACCSPMSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_ACCSPMSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[18], (U1)2U, (U1)3U);

    (void)Com_SendSignal(ComConf_ComSignal_ACCSPMSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumUSMMAIN(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_USMMAIN(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[19], (U1)4U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_USMMAIN,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumSLSSOSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_SLSSOSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[19], (U1)2U, (U1)2U);

    (void)Com_SendSignal(ComConf_ComSignal_SLSSOSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumCTAMSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_CTAMSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[21], (U1)5U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_CTAMSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumACCGCRSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_ACCGCRSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[21], (U1)4U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_ACCGCRSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumRTWMSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_RTWMSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[21], (U1)2U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_RTWMSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumAHSSDESW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_AHSSDESW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[22], (U1)5U, (U1)3U);

    (void)Com_SendSignal(ComConf_ComSignal_AHSSDESW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumAHSSWVSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_AHSSWVSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[22], (U1)4U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_AHSSWVSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumCCSMDMSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_CCSMDMSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[22], (U1)2U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_CCSMDMSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumERMSW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_ERMSW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[22], (U1)0U, (U1)2U);

    (void)Com_SendSignal(ComConf_ComSignal_ERMSW,    &u1_t_tx);
}
/*===================================================================================================================================*/
/*  void    vd_s_CanTxAppDumTRA_SW(U1 * u1p_a_flame) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_s_CanTxAppDum_TRA_SW(U1 * u1p_a_flame)
{
    U1    u1_t_tx;

    u1_t_tx     = (U1)0U;

    u1_t_tx   = u1_CANTXAPPDUM_READ_BIT(u1p_a_flame[23], (U1)7U, (U1)1U);

    (void)Com_SendSignal(ComConf_ComSignal_TRA_SW,    &u1_t_tx);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  0.0.0    11/11/2025  TN       New.                                                                                               */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TN   = Tetsushi Nakano, Denso Techno                                                                                           */
/*                                                                                                                                   */
/*===================================================================================================================================*/
