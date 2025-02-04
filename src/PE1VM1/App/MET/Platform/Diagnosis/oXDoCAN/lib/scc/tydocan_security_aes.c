/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Diagnosis on Can for MET based on AUBIST/DEM, DCM                                                                                */
/*  SID27,KeyUpdate                                                                                                                  */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDOCAN_SECURITY_AES_C_MAJOR                 (1U)
#define TYDOCAN_SECURITY_AES_C_MINOR                 (0U)
#define TYDOCAN_SECURITY_AES_C_PATCH                 (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "oxdocan_cfg_private.h"
#include "tydocan_security_aes_cfg_private.h"
#include "oxdocan_aubif_security.h"
#include "oxdocan_aubif.h"
#include "Csm.h"
#include "Dcm.h"
#include "Crypto_83_sw.h"
#if ((defined(BSW_BSWM_CS_CFG_FUNC_CS)     ) && \
     (defined(BSW_BSWM_CS_CFG_FUNC_SECOC)  ) && \
     (BSW_BSWM_CS_CFG_FUNC_CS    == BSW_USE) && \
     (BSW_BSWM_CS_CFG_FUNC_SECOC == BSW_USE))
#include "SecOC_Cfg.h"
#endif /* #if ((defined(BSW_BSWM_CS_CFG_FUNC_CS)  ) && .. */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (TYDOCAN_SECURITY_AES_C_MAJOR != OXDOCAN_CFG_H_MAJOR)
#error "tydocan_security_aes.c and oxdocan_cfg_private.h : source and header files are inconsistent!"
#endif

#if (TYDOCAN_SECURITY_AES_C_MAJOR != OXDOCAN_SAL_H_MAJOR)
#error "tydocan_security_aes.c and oxdocan_sal.h : source and header files are inconsistent!"
#endif

#if ((TYDOCAN_SECURITY_AES_C_MAJOR != TYDOCAN_SECURITY_AES_CFG_H_MAJOR) || \
     (TYDOCAN_SECURITY_AES_C_MINOR != TYDOCAN_SECURITY_AES_CFG_H_MINOR) || \
     (TYDOCAN_SECURITY_AES_C_PATCH != TYDOCAN_SECURITY_AES_CFG_H_PATCH))
#error "tydocan_security_aes.c and tydocan_security_aes_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_SECURITY_SEED_NWORD                 (4U)
#define TYDC_SECURITY_SEED_NBYTE                 (16U)
#define TYDC_SECURITY_CRYPTO_NWORD               (4U)
#define TYDC_SECURITY_CRYPTO_NBYTE               (16U)

#define TYDC_SECURITY_CRPT_STAT_NONE             (0U)
#define TYDC_SECURITY_CRPT_STAT_SEED             (1U)
#define TYDC_SECURITY_CRPT_STAT_RAND             (2U)
#define TYDC_SECURITY_CRPT_STAT_CRPT             (3U)
#define TYDC_SECURITY_CRPT_STAT_PROC             (4U)
#define TYDC_SECURITY_CRPT_STAT_DONE             (5U)
#define TYDC_SECURITY_CRPT_STAT_FAIL             (6U)
#define TYDC_SECURITY_CRPT_STAT_DCPT             (7U)

#define TYDC_SECURITY_KEYID_KEY1                 (0U)
#define TYDC_SECURITY_KEYID_RAM                  (1U)
#define TYDC_SECURITY_KEYID_UID                  (2U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_SECURITY_UID_NOT_IMP                (0U)
#define TYDC_SECURITY_UID_IMP                    (1U)

#define TYDC_SECURITY_SAKEY_NUM                  (2U)
#define TYDC_SECURITY_PLAINKEY_NWORD             (4U)
#define TYDC_SECURITY_PLAINKEY_NBYTE             (16U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define TYDC_SECURITY_SEED_NOT_IMP               (0U)
#define TYDC_SECURITY_SEED_IMP                   (1U)

#define TYDC_SECURITY_RAND_NOT_IMP               (0U)
#define TYDC_SECURITY_RAND_IMP                   (1U)
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1                    u1_s_tydc_security_stat;
static U1                    u1_s_tydc_security_seed_stat;
static U1                    u1_s_tydc_security_rand_stat;
static U1                    u1_sp_tydc_security_rnd_seed[TYDC_SECURITY_SEED_NBYTE];
static U4                    u4_sp_tydc_security_seed[TYDC_SECURITY_SEED_NWORD];
static U4                    u4_sp_tydc_security_seed_prev[TYDC_SECURITY_SEED_NWORD];
static U4                    u4_sp_tydc_security_key[TYDC_SECURITY_CRYPTO_NWORD];
static U4                    u4_s_tydc_security_resultLengthPtr;

static U4                    u4_sp_tydc_security_k_unlock[TYDC_SECURITY_PLAINKEY_NWORD];
static U4                    u4_sp_tydc_security_k_crypto[TYDC_SECURITY_PLAINKEY_NWORD];
static U4                    u4_sp_tydc_security_k_plain[TYDC_SECURITY_PLAINKEY_NWORD];
static U4                    u4_s_tydc_security_reqAdr;
static U1                    u1_s_tydc_uid_update_state;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void                  vd_s_TyDoCANSecurityAesRandomSeed(void);
static void                  vd_s_TyDoCANSecurityAesRandomGenerate(void);
static U1                    u1_s_TyDoCANSecurityAesEncryptECB(void);
static U1                    u1_s_TyDoCANSecurityAesDecryptECB(void);

static void                  vd_s_oXDoCANMemSecRead_Rl(const U1 * u1_ap_FP, U1 * u1_ap_ans);
static U1                    u1_s_oxDoCANUidUpdate(void);
static U1                    u1_s_oXDoCANRAMKeyUpdate(const U1 * u1_tp_PLAIN);
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void   vd_g_TyDoCANSecurityAesSeedInit(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_g_TyDoCANSecurityAesSeedInit(void)
{
    u1_s_tydc_security_stat = (U1)TYDC_SECURITY_CRPT_STAT_NONE;
    vd_g_MemfillU4(&(u4_sp_tydc_security_seed[0]), (U4)0U, (U4)TYDC_SECURITY_SEED_NWORD);
    vd_g_MemfillU4(&(u4_sp_tydc_security_key[0]), (U4)0U, (U4)TYDC_SECURITY_CRYPTO_NWORD);
    vd_g_MemfillU4(&(u4_sp_tydc_security_k_plain[0]), (U4)0U, (U4)TYDC_SECURITY_PLAINKEY_NWORD);
    u4_s_tydc_security_resultLengthPtr = (U4)0U;
}
/*===================================================================================================================================*/
/*  void   vd_g_TyDoCANSecurityAesInit(void)                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_g_TyDoCANSecurityAesInit(void)
{
    vd_g_TyDoCANSecurityAesSeedInit();

    vd_g_MemfillU4(&(u4_sp_tydc_security_seed_prev[0]), (U4)0U, (U4)TYDC_SECURITY_SEED_NWORD);
    vd_g_MemfillU1(&(u1_sp_tydc_security_rnd_seed[0]), (U1)0U, (U4)TYDC_SECURITY_SEED_NBYTE);
    u1_s_tydc_security_seed_stat = (U1)TYDC_SECURITY_SEED_NOT_IMP;
    u1_s_tydc_security_rand_stat = (U1)TYDC_SECURITY_RAND_NOT_IMP;
    u4_s_tydc_security_reqAdr = (U4)0x00000000U;
    u1_s_tydc_uid_update_state = (U1)TYDC_SECURITY_UID_NOT_IMP;
}
/*===================================================================================================================================*/
/*  U1   u1_g_TyDoCANSecurityAesSeedJobStat(const U4 u1_a_KEY_ADR)                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1   u1_g_TyDoCANSecurityAesSeedJobStat(const U4 u1_a_KEY_ADR)
{
    U1                      u1_t_ret;

    if(u1_s_tydc_uid_update_state == (U1)TYDC_SECURITY_UID_NOT_IMP){
        vd_s_oXDoCANMemSecRead_Rl((const U1*)((U4)OXDC_SECURITY_KEYADR_UNLOCK), (U1*)&(u4_sp_tydc_security_k_unlock[0]));
        u1_t_ret = u1_s_oxDoCANUidUpdate();
    }
    else{
        u1_t_ret = (U1)E_OK;
    }

    if(u1_t_ret == (U1)E_OK){
        vd_g_TyDoCANSecurityAesSeedInit();
        if(u1_s_tydc_security_seed_stat == (U1)TYDC_SECURITY_SEED_NOT_IMP){
            vd_s_TyDoCANSecurityAesRandomSeed();
        }
        else{
            u1_s_tydc_security_stat = (U1)TYDC_SECURITY_CRPT_STAT_RAND;
        }

        u1_t_ret = (U1)DCM_E_PENDING;
        u4_s_tydc_security_reqAdr = u1_a_KEY_ADR;
    }

    return (u1_t_ret);
}
/*===================================================================================================================================*/
/*  U1   u1_g_TyDoCANSecurityAesSeedJobProc(U1 * u1_ap_seed)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1   u1_g_TyDoCANSecurityAesSeedJobProc(U1 * u1_ap_seed)
{
    U1                      u1_t_ret;
    U2                      u2_t_icus_er;

    switch (u1_s_tydc_security_stat)
    {
    case TYDC_SECURITY_CRPT_STAT_SEED:
        vd_s_TyDoCANSecurityAesRandomSeed();
        u1_t_ret = (U1)DCM_E_PENDING;
        break;
    case TYDC_SECURITY_CRPT_STAT_RAND:
        vd_s_TyDoCANSecurityAesRandomGenerate();
        u1_t_ret = (U1)DCM_E_PENDING;
        break;
    case TYDC_SECURITY_CRPT_STAT_DCPT:
        u1_t_ret = u1_s_TyDoCANSecurityAesDecryptECB();
        break;
    case TYDC_SECURITY_CRPT_STAT_CRPT:
        vd_g_MemcpyU4(&(u4_sp_tydc_security_seed_prev[0]),  &(u4_sp_tydc_security_seed[0]), (U4)TYDC_SECURITY_SEED_NWORD);
        u1_t_ret = u1_s_TyDoCANSecurityAesEncryptECB();
        break;
    case TYDC_SECURITY_CRPT_STAT_PROC:
        u2_t_icus_er = (U2)CRYPTO_83_ICUS_AB_E_RAM_CHECK_FAIL;
        (void)Crypto_83_icus_Ab_GetErrorStatus(&u2_t_icus_er);
        if((u2_t_icus_er == (U2)CRYPTO_83_ICUS_AB_E_HSM_FAULT) ||
            (u2_t_icus_er == (U2)CRYPTO_83_ICUS_AB_E_NOT_INITIALIZED) ||
            (u2_t_icus_er == (U2)CRYPTO_83_ICUS_AB_E_RAM_CHECK_FAIL) ||
            (u2_t_icus_er == (U2)CRYPTO_83_ICUS_AB_E_NVM_LOCK) ||
            (u2_t_icus_er == (U2)CRYPTO_83_ICUS_AB_E_CRYPTO_LOCK) ||
            (u2_t_icus_er == (U2)CRYPTO_83_ICUS_AB_E_ICUS_LOCK)){

            u1_t_ret = (U1)E_NOT_OK;
            u1_s_tydc_security_stat = (U1)TYDC_SECURITY_CRPT_STAT_NONE;
        }
        else{
            u1_t_ret = (U1)DCM_E_PENDING;
        }
        break;
    case TYDC_SECURITY_CRPT_STAT_DONE:
        vd_g_MemcpyU1(&(u1_ap_seed[0]),  (U1*)&(u4_sp_tydc_security_seed[0]), (U4)TYDC_SECURITY_SEED_NBYTE);
        vd_g_MemfillU4(&(u4_sp_tydc_security_seed[0]), (U4)0U, (U4)TYDC_SECURITY_SEED_NWORD);
        vd_g_MemfillU4(&(u4_sp_tydc_security_k_plain[0]), (U4)0U, (U4)TYDC_SECURITY_PLAINKEY_NWORD);

        u1_t_ret = (U1)E_OK;
        u1_s_tydc_security_stat = (U1)TYDC_SECURITY_CRPT_STAT_NONE;
        break;
    case TYDC_SECURITY_CRPT_STAT_FAIL:
        vd_g_TyDoCANSecurityAesSeedInit();
        u1_t_ret = (U1)E_NOT_OK;
        break;
    default:
        vd_g_TyDoCANSecurityAesSeedInit();
        u1_t_ret = (U1)E_NOT_OK;
        break;
    }

    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  static void vd_s_TyDoCANSecurityAesRandomSeed(void)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_TyDoCANSecurityAesRandomSeed(void)
{
    Std_ReturnType  u1_t_ret;

    /* random seed 128bit */
    vd_g_MemfillU1(&(u1_sp_tydc_security_rnd_seed[0]), (U1)0U, (U4)TYDC_SECURITY_SEED_NBYTE);

    u1_t_ret = Csm_JobRandomSeed((U4)TYDC_SECURITY_JOBID_SEED, (U4)TYDC_SECURITY_KEYID_KEY1, u1_sp_tydc_security_rnd_seed, (U4)TYDC_SECURITY_SEED_NBYTE);
    if(u1_t_ret == (U1)E_OK){
        u1_s_tydc_security_stat = (U1)TYDC_SECURITY_CRPT_STAT_PROC;
    }
    else{
        u1_s_tydc_security_stat = (U1)TYDC_SECURITY_CRPT_STAT_FAIL;
        vd_g_MemfillU4(&(u4_sp_tydc_security_seed[0]), (U4)0U, (U4)TYDC_SECURITY_SEED_NWORD);
        vd_g_MemfillU4(&(u4_sp_tydc_security_key[0]), (U4)0U, (U4)TYDC_SECURITY_CRYPTO_NWORD);
    }
}
/*===================================================================================================================================*/
/*  static void vd_s_TyDoCANSecurityAesRandomGenerate(void)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_TyDoCANSecurityAesRandomGenerate(void)
{
    Std_ReturnType  u1_t_ret;

    u4_s_tydc_security_resultLengthPtr = (U4)TYDC_SECURITY_SEED_NBYTE;
    u1_t_ret = Csm_RandomGenerate((U4)TYDC_SECURITY_JOBID_RANDOM, (U1*)&(u4_sp_tydc_security_seed[0]), &u4_s_tydc_security_resultLengthPtr);
    if(u1_t_ret == (U1)E_OK){
        u1_s_tydc_security_stat = (U1)TYDC_SECURITY_CRPT_STAT_PROC;
    }
    else{
        u1_s_tydc_security_stat = (U1)TYDC_SECURITY_CRPT_STAT_FAIL;
        vd_g_MemfillU4(&(u4_sp_tydc_security_seed[0]), (U4)0U, (U4)TYDC_SECURITY_SEED_NWORD);
        vd_g_MemfillU4(&(u4_sp_tydc_security_key[0]), (U4)0U, (U4)TYDC_SECURITY_CRYPTO_NWORD);
    }
}
/*===================================================================================================================================*/
/*  static U1 u1_s_TyDoCANSecurityAesEncryptECB(void)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_TyDoCANSecurityAesEncryptECB(void)
{
    U1  u1_t_ret;

    u1_t_ret = (U1)u1_s_oXDoCANRAMKeyUpdate((U1*)&(u4_sp_tydc_security_k_plain[0]));
    if(u1_t_ret == (U1)E_OK){
        u4_s_tydc_security_resultLengthPtr = (U4)TYDC_SECURITY_CRYPTO_NBYTE;
        u1_t_ret = (U1)Csm_Encrypt(
                                (U4)TYDC_SECURITY_JOBID_ENCPT_ECB, 
                                (U1)CRYPTO_OPERATIONMODE_SINGLECALL, 
                                (U1*)&(u4_sp_tydc_security_seed[0]), 
                                (U4)TYDC_SECURITY_SEED_NBYTE, 
                                (U1*)&(u4_sp_tydc_security_key[0]), 
                                &u4_s_tydc_security_resultLengthPtr);

        if(u1_t_ret == (U1)E_OK){
            u1_t_ret = (U1)DCM_E_PENDING;
            u1_s_tydc_security_stat = (U1)TYDC_SECURITY_CRPT_STAT_PROC;
        }
        else{
            u1_s_tydc_security_stat = (U1)TYDC_SECURITY_CRPT_STAT_FAIL;
        }
    }
    else{
        u1_s_tydc_security_stat = (U1)TYDC_SECURITY_CRPT_STAT_FAIL;
    }
    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  void   vd_g_oXDoCANAubIfCsmSeedAck(U4 u4_a_jobId, U1 u1_a_RSLT)                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_g_oXDoCANAubIfCsmSeedAck(U4 u4_a_jobId, U1 u1_a_RSLT)
{
    if(u1_a_RSLT == (U1)E_OK){
        if(u4_a_jobId == (U4)TYDC_SECURITY_JOBID_SEED){
            u1_s_tydc_security_seed_stat = (U1)TYDC_SECURITY_SEED_IMP;
            u1_s_tydc_security_stat = (U1)TYDC_SECURITY_CRPT_STAT_RAND;
        }
        else if(u4_a_jobId == (U4)TYDC_SECURITY_JOBID_RANDOM){
            if ((u1_s_tydc_security_rand_stat == (U1)TYDC_SECURITY_RAND_NOT_IMP) ||
                ((u4_sp_tydc_security_seed[0] == (U4)0x00000000U) &&
                  (u4_sp_tydc_security_seed[1] == (U4)0x00000000U) &&
                  (u4_sp_tydc_security_seed[2] == (U4)0x00000000U) &&
                  (u4_sp_tydc_security_seed[3] == (U4)0x00000000U)) ||
                 ((u4_sp_tydc_security_seed[0] == (U4)0xffffffffU) &&
                  (u4_sp_tydc_security_seed[1] == (U4)0xffffffffU) &&
                  (u4_sp_tydc_security_seed[2] == (U4)0xffffffffU) &&
                  (u4_sp_tydc_security_seed[3] == (U4)0xffffffffU)) ||
                 ((u4_sp_tydc_security_seed[0] == u4_sp_tydc_security_seed_prev[0]) &&
                  (u4_sp_tydc_security_seed[1] == u4_sp_tydc_security_seed_prev[1]) &&
                  (u4_sp_tydc_security_seed[2] == u4_sp_tydc_security_seed_prev[2]) &&
                  (u4_sp_tydc_security_seed[3] == u4_sp_tydc_security_seed_prev[3]))
               ){
                /* regenerate random value */
                u1_s_tydc_security_stat = (U1)TYDC_SECURITY_CRPT_STAT_RAND;
                u1_s_tydc_security_rand_stat = (U1)TYDC_SECURITY_RAND_IMP;
            }
            else{
                u1_s_tydc_security_stat = (U1)TYDC_SECURITY_CRPT_STAT_DCPT;
            }
        }
        else if(u4_a_jobId == (U4)TYDC_SECURITY_JOBID_ENCPT_ECB){
            u1_s_tydc_security_stat = (U1)TYDC_SECURITY_CRPT_STAT_DONE;
        }
        else{
            u1_s_tydc_security_stat = (U1)TYDC_SECURITY_CRPT_STAT_FAIL;
            vd_g_MemfillU4(&(u4_sp_tydc_security_seed[0]), (U4)0U, (U4)TYDC_SECURITY_SEED_NWORD);
            vd_g_MemfillU4(&(u4_sp_tydc_security_key[0]), (U4)0U, (U4)TYDC_SECURITY_CRYPTO_NWORD);
        }
    }
    else{
        if( (u4_a_jobId == (U4)TYDC_SECURITY_JOBID_RANDOM) && 
            (u1_a_RSLT == (U1)CRYPTO_83_ICUS_AB_E_ENTROPY_EXHAUSTION)){
            u1_s_tydc_security_seed_stat = (U1)TYDC_SECURITY_SEED_NOT_IMP;
            u1_s_tydc_security_stat = (U1)TYDC_SECURITY_CRPT_STAT_SEED;
        }
        else if(u4_a_jobId == (U4)TYDC_SECURITY_JOBID_ENCPT_ECB){
            u1_s_tydc_security_stat = (U1)TYDC_SECURITY_CRPT_STAT_FAIL;
        }
        else{
            u1_s_tydc_security_stat = (U1)TYDC_SECURITY_CRPT_STAT_FAIL;
            vd_g_MemfillU4(&(u4_sp_tydc_security_seed[0]), (U4)0U, (U4)TYDC_SECURITY_SEED_NWORD);
            vd_g_MemfillU4(&(u4_sp_tydc_security_key[0]), (U4)0U, (U4)TYDC_SECURITY_CRYPTO_NWORD);
        }
    }
}
/*===================================================================================================================================*/
/*  U1   u1_g_TyDoCANSecurityAesCompareKeyProc(const U1 * u1_ap_KEY)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1   u1_g_TyDoCANSecurityAesCompareKeyProc(const U1 * u1_ap_KEY)
{
    U1              u1_t_ret;
    U1              u1_t_cnt;
    U4              u4_t_src;
    U4              u4_t_dst;

    u1_t_ret = (U1)TRUE;

    for(u1_t_cnt = (U1)0U; u1_t_cnt < (U1)TYDC_SECURITY_CRYPTO_NWORD; u1_t_cnt++ ){
        u4_t_src = (U4)(((U4)u1_ap_KEY[u1_t_cnt * (U1)TYDC_SECURITY_CRYPTO_NWORD]) |
                        (((U4)u1_ap_KEY[(u1_t_cnt * (U1)TYDC_SECURITY_CRYPTO_NWORD) + 1U]) << 8U) |
                        (((U4)u1_ap_KEY[(u1_t_cnt * (U1)TYDC_SECURITY_CRYPTO_NWORD) + 2U]) << 16U) |
                        (((U4)u1_ap_KEY[(u1_t_cnt * (U1)TYDC_SECURITY_CRYPTO_NWORD) + 3U]) << 24U));
        u4_t_dst = u4_sp_tydc_security_key[u1_t_cnt];

        if (u4_t_src != u4_t_dst){
            u1_t_ret = (U1)FALSE;
            break;
        }
    }

    vd_g_MemfillU4(&(u4_sp_tydc_security_key[0]), (U4)0U, (U4)TYDC_SECURITY_CRYPTO_NWORD);
    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  static U1 vd_s_TyDoCANSecurityAesDeccryptECB(void)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_TyDoCANSecurityAesDecryptECB(void)
{
    U1  u1_t_ret;

    u1_t_ret = (U1)u1_s_oXDoCANRAMKeyUpdate((U1*)&(u4_sp_tydc_security_k_unlock[0]));
    if(u1_t_ret == (U1)E_OK){
        vd_s_oXDoCANMemSecRead_Rl((const U1*)u4_s_tydc_security_reqAdr, (U1*)&(u4_sp_tydc_security_k_crypto[0]));
        u4_s_tydc_security_resultLengthPtr = (U4)TYDC_SECURITY_PLAINKEY_NBYTE;
        u1_t_ret = (U1)Csm_Decrypt(
                                (U4)TYDC_SECURITY_JOBID_DECPT_ECB, 
                                (U1)CRYPTO_OPERATIONMODE_SINGLECALL, 
                                (U1*)&(u4_sp_tydc_security_k_crypto[0]), 
                                (U4)TYDC_SECURITY_SEED_NBYTE, 
                                (U1*)&(u4_sp_tydc_security_k_plain[0]), 
                                &u4_s_tydc_security_resultLengthPtr);
        if(u1_t_ret == (U1)E_OK){
            u1_t_ret = (U1)DCM_E_PENDING;
            u1_s_tydc_security_stat = (U1)TYDC_SECURITY_CRPT_STAT_PROC;
        }
        else{
            u1_s_tydc_security_stat = (U1)TYDC_SECURITY_CRPT_STAT_FAIL;
        }
    }
    else{
        u1_s_tydc_security_stat = (U1)TYDC_SECURITY_CRPT_STAT_FAIL;
    }

    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  static U1 u1_s_oxDoCANUidUpdate(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_oxDoCANUidUpdate(void)
{
    Std_ReturnType             u1_t_ret;

    u1_t_ret = Csm_KeyElementSet(   (U4)TYDC_SECURITY_KEYID_UID, 
                                    (U4)CRYPTO_83_SW_AB_KE_UID, 
                                    &u1_gp_TYDC_SECURITY_AES_UID[0U], 
                                    (U4)TYDC_SECURITY_AES_UID_NBYTE);
    if(u1_t_ret == (Std_ReturnType)E_OK){
        u1_s_tydc_uid_update_state = TYDC_SECURITY_UID_IMP;
    }

    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  static U1    u1_s_oXDoCANRAMKeyUpdate(const U1 * u1_tp_PLAIN)                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_oXDoCANRAMKeyUpdate(const U1 * u1_tp_PLAIN)
{
    Std_ReturnType             u1_t_ret;

    u1_t_ret = (U1)E_NOT_OK;
    if(u1_s_tydc_uid_update_state == (U1)TYDC_SECURITY_UID_IMP){
        u1_t_ret = Csm_KeyElementSet(   (U4)TYDC_SECURITY_KEYID_RAM, 
                                        (U4)CRYPTO_83_SW_AB_KE_PLAINKEY, 
                                        u1_tp_PLAIN, 
                                        (U4)TYDC_SECURITY_PLAINKEY_NBYTE);
        if(u1_t_ret == (Std_ReturnType)E_OK){
            u1_t_ret = Csm_KeySetValid((U4)TYDC_SECURITY_KEYID_RAM);
        }
    }
    return(u1_t_ret);
}
/*===================================================================================================================================*/
/*  void   vd_g_oXDoCANAubIfCsmDecrptAck(U4 u4_a_jobId, U1 u1_a_RSLT)                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void   vd_g_oXDoCANAubIfCsmDecrptAck(U4 u4_a_jobId, U1 u1_a_RSLT)
{
    if((u4_a_jobId == (U4)TYDC_SECURITY_JOBID_DECPT_ECB) && (u1_a_RSLT == (U1)E_OK)){
        u1_s_tydc_security_stat = (U1)TYDC_SECURITY_CRPT_STAT_CRPT;
    }
    else{
        u1_s_tydc_security_stat = (U1)TYDC_SECURITY_CRPT_STAT_FAIL;
    }
}
/*===================================================================================================================================*/
/*  static void    vd_s_oXDoCANMemSecRead_Rl(const U1 * u1_ap_FP, U1 * u1_ap_ans)                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_oXDoCANMemSecRead_Rl(const U1 * u1_ap_FP, U1 * u1_ap_ans)
{
    vd_g_MemcpyU1(&u1_ap_ans[0], &u1_ap_FP[0], (U4)TYDC_SECURITY_PLAINKEY_NBYTE);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0    11/12/2023  MI       New.                                                                                               */
/*                                                                                                                                   */
/*  * MI = Masahiko Izumi, DENSO                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
