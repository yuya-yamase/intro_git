/* Rte_Csm_Type_h_v2-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name | Rte/Csm/Type/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes                                                                    */
/****************************************************************************/

#ifndef RTE_CSM_TYPE_H
#define RTE_CSM_TYPE_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h> /* ! */

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
typedef Std_ReturnType Csm_ResultType;
typedef Std_ReturnType Crypto_ResultType;

typedef uint8 Crypto_OperationModeType;
#define CRYPTO_OPERATIONMODE_START             ((Crypto_OperationModeType)0x01U)
#define CRYPTO_OPERATIONMODE_UPDATE            ((Crypto_OperationModeType)0x02U)
#define CRYPTO_OPERATIONMODE_STREAMSTART       ((Crypto_OperationModeType)0x03U)
#define CRYPTO_OPERATIONMODE_FINISH            ((Crypto_OperationModeType)0x04U)
#define CRYPTO_OPERATIONMODE_SINGLECALL        ((Crypto_OperationModeType)0x07U)

typedef uint8 Crypto_VerifyResultType;
#define CRYPTO_E_VER_OK                        ((Crypto_VerifyResultType)0x00U)
#define CRYPTO_E_VER_NOT_OK                    ((Crypto_VerifyResultType)0x01U)

#define E_ENTROPY_EXHAUSTED                    (0x03U)
#define E_KEY_READ_FAIL                        (0x04U)
#define E_KEY_NOT_AVAILABLE                    (0x05U)
#define E_KEY_NOT_VALID                        (0x06U)
#define E_JOB_CANCELED                         (0x07U)
#define E_KEY_EMPTY                            (0x08U)

#define CRYPTO_E_BUSY                          (0x02U)
#define CRYPTO_E_ENTROPY_EXHAUSTED             (0x04U)
#define CRYPTO_E_KEY_READ_FAIL                 (0x06U)
#define CRYPTO_E_KEY_WRITE_FAIL                (0x07U)
#define CRYPTO_E_KEY_NOT_AVAILABLE             (0x08U)
#define CRYPTO_E_KEY_NOT_VALID                 (0x09U)
#define CRYPTO_E_KEY_SIZE_MISMATCH             (0x0AU)
#define CRYPTO_E_JOB_CANCELED                  (0x0CU)
#define CRYPTO_E_KEY_EMPTY                     (0x0DU)

#define CSM_AB_E_SHE_NO_ERROR                  (0x10U)
#define CSM_AB_E_SHE_SEQUENCE_ERROR            (0x11U)
#define CSM_AB_E_SHE_KEY_NOT_AVAILABLE         (0x12U)
#define CSM_AB_E_SHE_KEY_INVALID               (0x13U)
#define CSM_AB_E_SHE_KEY_EMPTY                 (0x14U)
#define CSM_AB_E_SHE_NO_SECURE_BOOT            (0x15U)
#define CSM_AB_E_SHE_KEY_WRITE_PROTECTED       (0x16U)
#define CSM_AB_E_SHE_KEY_UPDATE_ERROR          (0x17U)
#define CSM_AB_E_SHE_RNG_SEED                  (0x18U)
#define CSM_AB_E_SHE_NO_DEBUGGING              (0x19U)
#define CSM_AB_E_SHE_BUSY                      (0x1AU)
#define CSM_AB_E_SHE_MEMORY_FAILURE            (0x1BU)
#define CSM_AB_E_SHE_GENERAL_ERROR             (0x1CU)

#define CRYPTO_KE_MAC_KEY                      (1U)
#define CRYPTO_KE_MAC_PROOF                    (2U)
#define CRYPTO_KE_KEYGENERATE_SEED             (16U)
#define CRYPTO_KE_SIGNATURE_KEY                (1U)
#define CRYPTO_KE_SIGNATURE_CURVETYPE          (29U)
#define CRYPTO_KE_RANDOM_SEED_STATE            (3U)
#define CRYPTO_KE_RANDOM_ALGORITHM             (4U)
#define CRYPTO_KE_CIPHER_KEY                   (1U)
#define CRYPTO_KE_CIPHER_IV                    (5U)
#define CRYPTO_KE_CIPHER_PROOF                 (6U)
#define CRYPTO_KE_CIPHER_2NDKEY                (7U)
#define CRYPTO_KE_KEYEXCHANGE_BASE             (8U)
#define CRYPTO_KE_KEYEXCHANGE_PRIVKEY          (9U)
#define CRYPTO_KE_KEYEXCHANGE_OWNPUBKEY        (10U)
#define CRYPTO_KE_KEYEXCHANGE_SHAREDVALUE      (1U)
#define CRYPTO_KE_KEYEXCHANGE_ALGORITHM        (12U)
#define CRYPTO_KE_KEYEXCHANGE_CURVETYPE        (29U)
#define CRYPTO_KE_KEYDERIVATION_PASSWORD       (1U)
#define CRYPTO_KE_KEYDERIVATION_SALT           (13U)
#define CRYPTO_KE_KEYDERIVATION_ITERATIONS     (14U)
#define CRYPTO_KE_KEYDERIVATION_ALGORITHM      (15U)
#define CRYPTO_KE_KEYDERIVATION_CURVETYPE      (29U)
#define CRYPTO_KE_KEYGENERATE_KEY              (1U)
#define CRYPTO_KE_KEYGENERATE_SEED             (16U)
#define CRYPTO_KE_KEYGENERATE_ALGORITHM        (17U)
#define CRYPTO_KE_KEYGENERATE_CURVETYPE        (29U)

#define CsmConf_CsmJob_Job00_MacGenerate_AVN1SB7 (0U)
#define CsmConf_CsmJob_Job01_MacGenerate_AVN1SC1 (1U)
#define CsmConf_CsmJob_Job02_MacGenerate_AVN1SC2 (2U)
#define CsmConf_CsmJob_Job03_MacGenerate_AVN1SC3 (3U)
#define CsmConf_CsmJob_Job04_MacGenerate_AVN1SC4 (4U)
#define CsmConf_CsmJob_Job05_MacGenerate_AVN1SC5 (5U)
#define CsmConf_CsmJob_Job06_MacGenerate_AVN1SC6 (6U)
#define CsmConf_CsmJob_Job07_MacGenerate_AVN1SC7 (7U)
#define CsmConf_CsmJob_Job08_MacGenerate_AVN1SC8 (8U)
#define CsmConf_CsmJob_Job09_MacGenerate_AVN1SC9 (9U)
#define CsmConf_CsmJob_Job10_MacGenerate_AVN1SD1 (10U)
#define CsmConf_CsmJob_Job11_MacGenerate_AVN1SD2 (11U)
#define CsmConf_CsmJob_Job12_MacGenerate_AVN1SD3 (12U)
#define CsmConf_CsmJob_Job13_MacGenerate_CDC1S01 (13U)
#define CsmConf_CsmJob_Job14_MacGenerate_MET1S30 (14U)
#define CsmConf_CsmJob_Job15_MacGenerate_MET1S44 (15U)
#define CsmConf_CsmJob_Job16_MacVerify_BDC1S13 (16U)
#define CsmConf_CsmJob_Job17_MacVerify_BDC1SC1 (17U)
#define CsmConf_CsmJob_Job18_MacVerify_BDC1SC2 (18U)
#define CsmConf_CsmJob_Job19_MacVerify_BDC1SC3 (19U)
#define CsmConf_CsmJob_Job20_MacVerify_BDC1SC4 (20U)
#define CsmConf_CsmJob_Job21_MacVerify_BDC1SC5 (21U)
#define CsmConf_CsmJob_Job22_MacVerify_BDC1SC6 (22U)
#define CsmConf_CsmJob_Job23_MacVerify_BDC1SC7 (23U)
#define CsmConf_CsmJob_Job24_MacVerify_BDC1SC8 (24U)
#define CsmConf_CsmJob_Job25_MacVerify_BDC1SC9 (25U)
#define CsmConf_CsmJob_Job26_MacVerify_BDC1SD1 (26U)
#define CsmConf_CsmJob_Job27_MacVerify_BDC1SD2 (27U)
#define CsmConf_CsmJob_Job28_MacVerify_BDC1SD3 (28U)
#define CsmConf_CsmJob_Job29_MacVerify_BDC1SD4 (29U)
#define CsmConf_CsmJob_Job30_MacVerify_BDC1SD5 (30U)
#define CsmConf_CsmJob_Job31_MacVerify_BDC1SD6 (31U)
#define CsmConf_CsmJob_Job32_MacVerify_BDC1SD7 (32U)
#define CsmConf_CsmJob_Job33_MacVerify_BDC1SD8 (33U)
#define CsmConf_CsmJob_Job34_MacVerify_BDC1SD9 (34U)
#define CsmConf_CsmJob_Job35_MacVerify_BDC1SE1 (35U)
#define CsmConf_CsmJob_Job36_MacVerify_BDC1SE2 (36U)
#define CsmConf_CsmJob_Job37_MacVerify_BDC1SE3 (37U)
#define CsmConf_CsmJob_Job38_MacVerify_BDC1SE4 (38U)
#define CsmConf_CsmJob_Job39_MacVerify_BDC1SE5 (39U)
#define CsmConf_CsmJob_Job40_MacVerify_BDC1SE6 (40U)
#define CsmConf_CsmJob_Job41_MacVerify_BDC1SE7 (41U)
#define CsmConf_CsmJob_Job42_MacVerify_BDC1SH3 (42U)
#define CsmConf_CsmJob_Job43_MacVerify_BDC1SJ5 (43U)
#define CsmConf_CsmJob_Job44_MacVerify_PCN1S01 (44U)
#define CsmConf_CsmJob_Job45_MacGenerate_UseByKeyVerify (45U)
#define CsmConf_CsmJob_Job46_KeySetValid_MasterEcuKey (46U)
#define CsmConf_CsmJob_Job47_KeySetValid_MacKey (47U)
#define CsmConf_CsmJob_Job48_Encrypt_UseByKeyVerify (48U)
#define CsmConf_CsmKey_MacKey (1U)
#define CsmConf_CsmKey_MasterEcuKey (0U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif /* RTE_CSM_TYPE_H */

/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v2-0-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

