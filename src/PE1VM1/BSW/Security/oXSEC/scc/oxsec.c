/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  OEM eXtention of Security                                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

#warning "oxsec.c : vd_g_oXSECBonKeyInit is tentative implementation for v100r10-Sep-25-2025. It shall be deleted at next release."

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define OXSEC_C_MAJOR                            (1U)
#define OXSEC_C_MINOR                            (0U)
#define OXSEC_C_PATCH                            (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxsec_cfg_private.h"

#if (OXSEC_AUB_EN_CSM == 1U)
#include "Csm.h"
#include "CryIf.h"
#include "SchM_Csm.h"
#endif /* #if (OXSEC_AUB_EN_CSM == 1U) */

#if (OXSEC_AUB_EN_CRY_SW == 1U)
#include "Crypto_83_sw.h"
#include "SchM_Crypto_83_sw.h"
#endif /* #if (OXSEC_AUB_EN_CRY_SW == 1U) */

#if (OXSEC_AUB_EN_CRY_HA == 1U)
#include "oxsec_rh850u2a.h"
#endif /* #if (OXSEC_AUB_EN_CRY_HA == 1U) */

#if (OXSEC_AUB_EN_SECOC == 1U)
#include "SecOC.h"
#endif /* #if (OXSEC_AUB_EN_SECOC == 1U) */

#if (OXSEC_AUB_EN_IDSM == 1U)
#include "IdsM.h"
#include "SchM_IdsM.h"
#endif /* #if (OXSEC_AUB_EN_IDSM == 1U) */

#if (OXSEC_AUB_EN_IED == 1U)
#include "oxsec_ied.h"
#endif /* (OXSEC_AUB_EN_IED == 1U) */

#if ((OXSEC_FV_EN_SET == 1U) || (OXSEC_FV_EN_RW == 1U))
#include "oxsec_fv.h"
#endif /* ((OXSEC_FV_EN_SET == 1U) || (OXSEC_FV_EN_RW == 1U)) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((OXSEC_C_MAJOR != OXSEC_H_MAJOR) || \
     (OXSEC_C_MINOR != OXSEC_H_MINOR) || \
     (OXSEC_C_PATCH != OXSEC_H_PATCH))
#error "oxsec.c and oxsec.h : source and header files are inconsistent!"
#endif

#if ((OXSEC_C_MAJOR != OXSEC_CFG_H_MAJOR) || \
     (OXSEC_C_MINOR != OXSEC_CFG_H_MINOR) || \
     (OXSEC_C_PATCH != OXSEC_CFG_H_PATCH))
#error "oxsec.c and oxsec_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXSEC_AUB_EN_SECOC == 1U)
/* Trip counter    */
#define OXSEC_TRIPCNT_SET_LOW       (0x000000FFU)       /* Trip counter ptFV[2] setting definition */
#define OXSEC_TRIPCNT_SET_MID       (0x0000FF00U)       /* Trip counter ptFV[1] setting definition */
#define OXSEC_TRIPCNT_SET_HI        (0x00FF0000U)       /* Trip counter ptFV[0] setting definition */
#define OXSEC_TRIPCNT_MAX           (0x00FFFFFFU)       /* Trip counter Maximum                    */
#endif /* #if (OXSEC_AUB_EN_SECOC == 1U) */

#define OXSEC_KEY_DATASIZE          (64U)  /* The concatenated data size of M1, M2, and M3 */
#define OXSEC_KEY_SET_M1M2M3        (1U)   /* KeyElementId: Key Material */
#define OXSEC_KEY_NUM               (2U)   /* Number of keys. The total number on the Crypto side is defined by CRYPTO_82_HSM_NUMBER_OF_KEYS */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXSEC_AUB_EN_SEV_HB == 1U)
#define OXSEC_MAIN_TICK_MID         (5U)     /* Unit: ms */
#define OXSEC_HEARTBEAT_CYCLIC_TIME (10000U) /* Heartbeat Cyclic Transmission Time. Unit:ms.                                         */
                                             /* Set in multiples of OXSEC_MAIN_TICK_MID. If set to 0, transmission is disabled.      */
#define OXSEC_HEARTBEAT_FIRST_DELAY (10000U) /* Heartbeat first transmission time. Unit:ms. Set in multiples of OXSEC_MAIN_TICK_MID */
#endif /* #if (OXSEC_AUB_EN_SEV_HB == 1U) */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U4                      u4_Crypto_keyId;
    U4                      u4_KeyId;
    U4                      u4_KeyElementId;
    const U1 *              u1_ap_KeyPtr;
    U4                      u4_KeyLength;
}ST_OXSEC_KEY_IF;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1               u1_s_oxsec_shtdwn_ok;

#if (OXSEC_AUB_EN_SECOC == 1U)
static U1               u1_s_oxsec_fv_rx_ok;
#endif /* #if (OXSEC_AUB_EN_SECOC == 1U) */

#if (OXSEC_AUB_EN_SEV_HB == 1U)
static U4               u4_s_oxsec_tim_elpsd;
static U4               u4_s_oxsec_hb_intvl;
#endif /* #if (OXSEC_AUB_EN_SEV_HB == 1U) */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void    vd_s_oXSECReset(void);
#if (OXSEC_AUB_EN_CSM == 1U)
static U4      u4_s_oXSECCsmMaEchk(void);
#endif /* #if (OXSEC_AUB_EN_CSM == 1U) */

#if (OXSEC_AUB_EN_CRY_SO == 1U)
static U4      u4_s_oXSECCrySoMaEchk(void);
#endif /* #if (OXSEC_AUB_EN_CRY_SO == 1U) */

#if (OXSEC_AUB_EN_SECOC == 1U)
static U4      u4_s_oXSECSecOCMaEchk(void);
#endif /* #if (OXSEC_AUB_EN_SECOC == 1U) */

#if (OXSEC_AUB_EN_SEV_HB == 1U)
static void    vd_s_oXCEC_Idsm_Heartbeat(void);
#endif /* #if (OXSEC_AUB_EN_SEV_HB == 1U) */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (OXSEC_AUB_EN_CSM == 1U)
/* Key data(Concatenation of M1, M2, and M3) */
/* Authentication key: MASTER_ECU_KEY(1)：00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 */
/* Registration key:   MASTER_ECU_KEY(1)：11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 */
/* FID(Flag)：- */
/* UID：00000000:00000000:00000000:000000 */
/* Cid：1 */
const U1  u1_g_MasterEcuKey[OXSEC_KEY_DATASIZE] = {
(U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x11,
(U1)0xff, (U1)0x8b, (U1)0x75, (U1)0xf7, (U1)0x3e, (U1)0x6a, (U1)0xd5, (U1)0xa1, (U1)0x72, (U1)0x94, (U1)0x23, (U1)0xc6, (U1)0xe9, (U1)0x31, (U1)0x1f, (U1)0x1a,
(U1)0x81, (U1)0xb9, (U1)0xf9, (U1)0x69, (U1)0xd4, (U1)0x03, (U1)0x6a, (U1)0x5b, (U1)0x22, (U1)0x1e, (U1)0x76, (U1)0xfa, (U1)0x91, (U1)0x38, (U1)0xae, (U1)0x21,
(U1)0xa2, (U1)0xc2, (U1)0xe0, (U1)0x11, (U1)0xdd, (U1)0xc4, (U1)0x27, (U1)0x8f, (U1)0x61, (U1)0xaa, (U1)0xea, (U1)0xcf, (U1)0xb9, (U1)0x6e, (U1)0xaa, (U1)0xd9
};
/* Authentication key:  MASTER_ECU_KEY(1)：11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 */
/* Registration key:    KEY_1(4)         ：11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 11 */
/* FID(Flag)：KEY_USAGE */
/* UID：00000000:00000000:00000000:000000 */
/* Cid：1 */
const U1  u1_g_SafetyMACkey[OXSEC_KEY_DATASIZE] = {
(U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x00, (U1)0x41,
(U1)0xb7, (U1)0x93, (U1)0x65, (U1)0xde, (U1)0x83, (U1)0xb9, (U1)0xb4, (U1)0x78, (U1)0xbd, (U1)0xf5, (U1)0x28, (U1)0xb0, (U1)0x19, (U1)0x6a, (U1)0x88, (U1)0x71,
(U1)0x03, (U1)0x91, (U1)0xcb, (U1)0x95, (U1)0xa1, (U1)0xb9, (U1)0x13, (U1)0x12, (U1)0xe9, (U1)0x9a, (U1)0x03, (U1)0x1a, (U1)0x61, (U1)0x45, (U1)0xb0, (U1)0x04,
(U1)0x86, (U1)0xcf, (U1)0x0d, (U1)0x0c, (U1)0x00, (U1)0x53, (U1)0x25, (U1)0x6c, (U1)0x16, (U1)0x25, (U1)0xb3, (U1)0x04, (U1)0x61, (U1)0x03, (U1)0x55, (U1)0x00
};

const ST_OXSEC_KEY_IF            st_gp_OXSEC_KEY_IF_CFG[] = {
/*   u4_Crypto_keyId                                           u4_KeyId                          u4_KeyElementId           u1_ap_KeyPtr              u4_KeyLength           */
    {(U4)CryptoConf_CryptoKey_CryptoKey_MASTER_ECU_KEY,        (U4)CsmConf_CsmKey_MasterEcuKey,  (U4)CRYPTO_KE_MAC_KEY,    &u1_g_MasterEcuKey[0],    (U4)OXSEC_KEY_DATASIZE},
    {(U4)CryptoConf_CryptoKey_CryptoKey_KeyVerify_SecOC_Mac,   (U4)CsmConf_CsmKey_MacKey,        (U4)CRYPTO_KE_MAC_KEY,    &u1_g_SafetyMACkey[0],    (U4)OXSEC_KEY_DATASIZE}
};
#endif /* #if (OXSEC_AUB_EN_CSM == 1U) */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_oXSECInit(void)                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXSECInit(void)
{
    u1_s_oxsec_shtdwn_ok = (U1)TRUE;

#if (OXSEC_AUB_EN_CRY_SO == 1U)
    Crypto_83_sw_Init(NULL_PTR);
#endif /* #if (OXSEC_AUB_EN_CRY_SO == 1U) */

#if (OXSEC_AUB_EN_CRY_HA == 1U)
    vd_g_oXSECCryHaInit();
#endif /* #if (OXSEC_AUB_EN_CRY_HA == 1U) */

#if (OXSEC_AUB_EN_CSM == 1U)
    CryIf_Init(NULL_PTR);
    Csm_Init(NULL_PTR);
#endif /* #if (OXSEC_AUB_EN_CSM == 1U) */

#if (OXSEC_AUB_EN_SECOC == 1U)
    SecOC_Init(NULL_PTR);         /* ./inc/Compiler.h:52:#define NULL_PTR            ((void *)0).. */
    u1_s_oxsec_fv_rx_ok = (U1)FALSE;
#endif /* #if (OXSEC_AUB_EN_SECOC == 1U) */

#if (OXSEC_AUB_EN_IDSM == 1U)
    IdsM_Init(NULL_PTR);
#endif /* #if (OXSEC_AUB_EN_IDSM == 1U) */

#if (OXSEC_AUB_EN_SEV_HB == 1U)
    u4_s_oxsec_tim_elpsd = (U4)0U;
    u4_s_oxsec_hb_intvl  = (U4)((U4)OXSEC_HEARTBEAT_FIRST_DELAY / (U4)OXSEC_MAIN_TICK_MID);
#endif /* #if (OXSEC_AUB_EN_SEV_HB == 1U) */

#if (OXSEC_AUB_EN_IED == 1U)
    vd_g_oXSECIedInit();
#endif /* (OXSEC_AUB_EN_IED == 1U) */

#if ((OXSEC_FV_EN_SET == 1U) || (OXSEC_FV_EN_RW == 1U))
    vd_g_oXSECFvInit();
#endif /* ((OXSEC_FV_EN_SET == 1U) || (OXSEC_FV_EN_RW == 1U)) */

}
/*===================================================================================================================================*/
/*  void    vd_g_oXSECDeInit(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXSECDeInit(void)
{
#if (OXSEC_AUB_EN_SECOC == 1U)
    SecOC_DeInit();
#endif /* #if (OXSEC_AUB_EN_SECOC == 1U) */
}
/*===================================================================================================================================*/
/*  U1      u1_g_oXSECShtdwnOk(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         Can Sleep Check Result                                                                                           */
/*===================================================================================================================================*/
U1      u1_g_oXSECShtdwnOk(void)
{
    return(u1_s_oxsec_shtdwn_ok);
}
/*===================================================================================================================================*/
/*  void    vd_g_oXSECMainPreMid(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXSECMainPreMid(void)
{
#if (OXSEC_AUB_EN_CRY_SO == 1U)
    Crypto_83_sw_Ab_MainFunctionOut();
#endif /* #if (OXSEC_AUB_EN_CRY_SO == 1U) */

/* --------------------------------------------------------------------------------------------------------------------------------- */
#if (OXSEC_MAIN_HIGH == 1U)
#else
/* --------------------------------------------------------------------------------------------------------------------------------- */

#if (OXSEC_AUB_EN_CRY_HA == 1U)
    vd_g_oXSECCryHaMainOut();
#endif /* #if (OXSEC_AUB_EN_CRY_HA == 1U) */

    Csm_MainFunction();

/* --------------------------------------------------------------------------------------------------------------------------------- */
#endif /* #if (OXSEC_MAIN_HIGH == 1U) */
/* --------------------------------------------------------------------------------------------------------------------------------- */
}
/*===================================================================================================================================*/
/*  void    vd_g_oXSECMainPosMid(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXSECMainPosMid(void)
{
    U4                  u4_t_mae;
    U1                  u1_t_shtdwn_ok;

/* --------------------------------------------------------------------------------------------------------------------------------- */
#if (OXSEC_MAIN_HIGH == 1U)
#else
/* --------------------------------------------------------------------------------------------------------------------------------- */

#if (OXSEC_AUB_EN_CRY_HA == 1U)
    vd_g_oXSECCryHaMainIn();
#endif /* #if (OXSEC_AUB_EN_CRY_HA == 1U) */

/* --------------------------------------------------------------------------------------------------------------------------------- */
#endif /* #if (OXSEC_MAIN_HIGH == 1U) */
/* --------------------------------------------------------------------------------------------------------------------------------- */

    u4_t_mae = (U4)0U;

#if (OXSEC_AUB_EN_CRY_SO == 1U)
    Crypto_83_sw_Ab_MainFunctionIn();
#endif  /* #if (OXSEC_AUB_EN_CRY_SO == 1U) */

#if (OXSEC_AUB_EN_SEV_HB == 1U)
    vd_s_oXCEC_Idsm_Heartbeat();
#endif  /* #if (OXSEC_AUB_EN_SEV_HB == 1U) */

#if (OXSEC_AUB_EN_IDSM == 1U)
    IdsM_MainFunction();
    IdsM_Ab_MainFunctionTx();
#endif  /* #if (OXSEC_AUB_EN_IDSM == 1U) */

#if (OXSEC_AUB_EN_SECOC == 1U)
    if(u1_s_oxsec_fv_rx_ok != (U1)TRUE){
        u1_s_oxsec_fv_rx_ok = u1_g_oXSECFvRx();
    }
#endif  /* #if (OXSEC_AUB_EN_SECOC == 1U) */

#if (OXSEC_AUB_EN_CSM == 1U)
    u4_t_mae  = u4_s_oXSECCsmMaEchk();
#endif /* #if (OXSEC_AUB_EN_CSM == 1U) */

#if (OXSEC_AUB_EN_SECOC == 1U)
    u4_t_mae |= u4_s_oXSECSecOCMaEchk();
#endif  /* #if (OXSEC_AUB_EN_SECOC == 1U) */

#if (OXSEC_AUB_EN_CRY_SO == 1U)
    u4_t_mae |= u4_s_oXSECCrySoMaEchk();
#endif /* #if (OXSEC_AUB_EN_CRY_SO == 1U) */

#if (OXSEC_AUB_EN_CRY_HA == 1U)
    u4_t_mae |= u4_g_oXSECCryHaMaEchk();
#endif /* #if (OXSEC_AUB_EN_CRY_HA == 1U) */

    u1_t_shtdwn_ok = (U1)TRUE;
    if(u4_t_mae >= (U4)OXSEC_ERR_RES_CSM){
     /* u1_t_shtdwn_ok = (U1)TRUE; */
        vd_g_oXSECCfgErrEvhk(u4_t_mae);
    }
    else if(u4_t_mae > (U4)0U){
        u1_t_shtdwn_ok = (U1)FALSE;
    }
    else{
     /* u1_t_shtdwn_ok = (U1)TRUE; */
    }
    u1_s_oxsec_shtdwn_ok = u1_t_shtdwn_ok;

    u4_t_mae &= (U4)OXSEC_ERR_RES_CHK;
    if(u4_t_mae != (U4)0U){
        vd_s_oXSECReset();
    }
}
/*===================================================================================================================================*/

#if (OXSEC_MAIN_HIGH == 1U)

/*===================================================================================================================================*/
/*  void    vd_g_oXSECMainPreHigh(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXSECMainPreHigh(void)
{
#if (OXSEC_AUB_EN_CRY_HA == 1U)
    vd_g_oXSECCryHaMainOut();
#endif /* #if (OXSEC_AUB_EN_CRY_HA == 1U) */

#if (OXSEC_AUB_EN_CSM == 1U)
    Csm_MainFunction();
#endif /* #if (OXSEC_AUB_EN_CSM == 1U) */

}
/*===================================================================================================================================*/
/*  void    vd_g_oXSECMainPosHigh(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXSECMainPosHigh(void)
{
#if (OXSEC_AUB_EN_CRY_HA == 1U)
    vd_g_oXSECCryHaMainIn();
#endif /* #if (OXSEC_AUB_EN_CRY_HA == 1U) */
}
/*===================================================================================================================================*/

#endif /* #if (OXSEC_MAIN_HIGH == 1U) */

#if (OXSEC_AUB_EN_CSM == 1U)
/*===================================================================================================================================*/
/*  static U4      u4_s_oXSECCsmMaEchk(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         OXSEC_MDE_XXX and/or OXSEC_ERR_XXX                                                                               */
/*===================================================================================================================================*/
static U4      u4_s_oXSECCsmMaEchk(void)
{
    U4                  u4_t_chk;
    U2                  u2_t_err;
    U1                  u1_t_mde;

    u2_t_err = CSM_AB_E_RAM_CHECK_FAIL;
    (void)Csm_Ab_GetErrorStatus(&u2_t_err);

    u1_t_mde = CSM_AB_M_ABNORMAL;
    (void)Csm_Ab_GetMode(&u1_t_mde);

    if((u2_t_err == CSM_AB_E_NOT_INITIALIZED) ||
       (u2_t_err == CSM_AB_E_RAM_CHECK_FAIL )){

        u4_t_chk = (U4)OXSEC_ERR_FAT_CSM;
    }
    else if(u1_t_mde == CSM_AB_M_RUN){

        u4_t_chk = (U4)OXSEC_MDE_RUN_CSM;
    }
    else if(u1_t_mde == CSM_AB_M_IDLE){

        u4_t_chk = (U4)0U;
    }        
    else{
        u4_t_chk = (U4)OXSEC_ERR_RES_CSM;
    }

    return(u4_t_chk);
}
/*===================================================================================================================================*/
#endif /* #if (OXSEC_AUB_EN_CSM == 1U) */

#if (OXSEC_AUB_EN_SECOC == 1U)

/*===================================================================================================================================*/
/*  static U4      u4_s_oXSECSecOCMaEchk(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         OXSEC_MDE_XXX and/or OXSEC_ERR_XXX                                                                               */
/*===================================================================================================================================*/
static U4      u4_s_oXSECSecOCMaEchk(void)
{
    U4                  u4_t_chk;
    U1                  u1_t_mde;

    u1_t_mde = SECOC_M_ABNORMAL;
    (void)SecOC_Ab_GetMode(&u1_t_mde);

    if(u1_t_mde == SECOC_M_IDLE){
        u4_t_chk = (U4)0U;
    }
    else if(u1_t_mde == SECOC_M_RUN){
        u4_t_chk = (U4)OXSEC_MDE_RUN_SECOC;
    }
    else{
        u4_t_chk = (U4)OXSEC_ERR_RES_SECOC;
    }

    return(u4_t_chk);
}
#endif  /* #if (OXSEC_AUB_EN_SECOC == 1U) */
/*===================================================================================================================================*/

#if (OXSEC_AUB_EN_CRY_SO == 1U)

/*===================================================================================================================================*/
/*  static U4      u4_s_oXSECCrySoMaEchk(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         OXSEC_MDE_XXX and/or OXSEC_ERR_XXX                                                                               */
/*===================================================================================================================================*/
static U4      u4_s_oXSECCrySoMaEchk(void)
{
    U4                  u4_t_chk;
    U2                  u2_t_err;                    /* ./inc/Crypto_83_sw.h:57:typedef uint16 Crypto_83_sw_Ab_ErrorStatusType;     */

    u2_t_err = CRYPTO_83_SW_AB_E_RAM_CHECK_FAIL;
    (void)Crypto_83_sw_Ab_GetErrorStatus(&u2_t_err);

    if((u2_t_err == CRYPTO_83_SW_AB_E_NOT_INITIALIZED) ||
       (u2_t_err == CRYPTO_83_SW_AB_E_RAM_CHECK_FAIL )){
        u4_t_chk  = (U4)OXSEC_ERR_FAT_CRYSO;
    }
    else if(u2_t_er != CRYPTO_83_SW_AB_E_NONE){
        u4_t_chk  = (U4)OXSEC_ERR_RES_CRYSO;
    }
    else{
        u4_t_chk  = (U4)0U;
    }

    return(u4_t_chk);
}
#endif /* #if (OXSEC_AUB_EN_CRY_SO == 1U) */
/*===================================================================================================================================*/
/*  static void    vd_s_oXSECReset(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXSECReset(void)
{
    U4                  u4_t_gli;

    u4_t_gli = u4_g_oXSEC_IRQ_DI();

#if (OXSEC_AUB_EN_SECOC == 1U)
    SecOC_DeInit();
#endif /* #if (OXSEC_AUB_EN_SECOC == 1U) */

#if (OXSEC_AUB_EN_CRY_SO == 1U)
    Crypto_83_sw_Init(NULL_PTR);
#endif /* #if (OXSEC_AUB_EN_CRY_SO == 1U) */

#if (OXSEC_AUB_EN_CRY_HA == 1U)
    vd_g_oXSECCryHaInit();
#endif /* #if (OXSEC_AUB_EN_CRY_HA == 1U) */

#if (OXSEC_AUB_EN_CSM == 1U)
    CryIf_Init(NULL_PTR);
    Csm_Init(NULL_PTR);
#endif /* #if (OXSEC_AUB_EN_CSM == 1U) */

#if (OXSEC_AUB_EN_SECOC == 1U)
    SecOC_Init(NULL_PTR);
#endif /* #if (OXSEC_AUB_EN_SECOC == 1U) */

#if (OXSEC_AUB_EN_IDSM == 1U)
    IdsM_Init(NULL_PTR);
#endif /* #if (OXSEC_AUB_EN_IDSM == 1U) */

    vd_g_oXSEC_IRQ_EI(u4_t_gli);
}

#if (OXSEC_AUB_EN_CSM == 1U)
/*===================================================================================================================================*/
/*  void    vd_g_oXSECBonKeyInit(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_oXSECBonKeyInit(void)
{
    U4              u4_t_loop_cnt;
    U1              u1_t_ret;
    
    for(u4_t_loop_cnt = (U4)0U;u4_t_loop_cnt < (U4)OXSEC_KEY_NUM;u4_t_loop_cnt++){

       u1_t_ret = u1_g_oXSECCryHaKeyGetValid(st_gp_OXSEC_KEY_IF_CFG[u4_t_loop_cnt].u4_Crypto_keyId);

       if( u1_t_ret == (U1)FALSE){
            u1_t_ret = Csm_KeyElementSet (st_gp_OXSEC_KEY_IF_CFG[u4_t_loop_cnt].u4_KeyId,
                                        st_gp_OXSEC_KEY_IF_CFG[u4_t_loop_cnt].u4_KeyElementId,
                                        st_gp_OXSEC_KEY_IF_CFG[u4_t_loop_cnt].u1_ap_KeyPtr,
                                        st_gp_OXSEC_KEY_IF_CFG[u4_t_loop_cnt].u4_KeyLength);
            if( u1_t_ret == E_OK ){
                u1_t_ret = Csm_KeySetValid (st_gp_OXSEC_KEY_IF_CFG[u4_t_loop_cnt].u4_KeyId);
                if( u1_t_ret == E_OK ){
                    /* Success */
                }
            }
        }
    }
    return;
}
#endif /* #if (OXSEC_AUB_EN_CSM == 1U) */


#if (OXSEC_AUB_EN_SEV_HB == 1U)
/*===================================================================================================================================*/
/*  static void    vd_s_oXCEC_Idsm_Heartbeat(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXCEC_Idsm_Heartbeat(void)
{

#if (OXSEC_HEARTBEAT_CYCLIC_TIME > 0U)
    u4_s_oxsec_tim_elpsd++;
    if(u4_s_oxsec_tim_elpsd >= u4_s_oxsec_hb_intvl){
        IdsM_SetSecurityEvent((IdsM_SecurityEventIdType)IdsMConf_IdsMEvent_Event_C500);
        u4_s_oxsec_tim_elpsd = (U4)0U;
        u4_s_oxsec_hb_intvl  = (U4)((U4)OXSEC_HEARTBEAT_CYCLIC_TIME / (U4)OXSEC_MAIN_TICK_MID);
    }
    return;
#endif /* #if (OXSEC_HEARTBEAT_CYCLIC_TIME > 0U) */

}
#endif /* #if (OXSEC_AUB_EN_SEV_HB == 1U) */


/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     2/28/2025  TN       oxcan v1.4.0 -> oxsec v1.0.0 was divided and redesgined for Toyota BEVStep3.                       */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, DENSO                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
