/* Crypto_83_sw_h_v2-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Crypto_83_sw/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CRYPTO_83_SW_H
#define CRYPTO_83_SW_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <Crypto_GeneralTypes.h>
#include <Rte_Csm_Type.h>
#include <CryIf.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* CryptoDriver Version */
#define CRYPTO_83_SW_VENDOR_ID                    (0x0053U)
#define CRYPTO_83_SW_MODULE_ID                    (114U)
#define CRYPTO_83_SW_SW_MAJOR_VERSION             (1U)
#define CRYPTO_83_SW_SW_MINOR_VERSION             (0U)
#define CRYPTO_83_SW_SW_PATCH_VERSION             (0U)
#define CRYPTO_83_SW_AR_RELEASE_MAJOR_VERSION     (4U)
#define CRYPTO_83_SW_AR_RELEASE_MINOR_VERSION     (5U)
#define CRYPTO_83_SW_AR_RELEASE_REVISION_VERSION  (0U)

/* KeyElementId Parameter */
#define CRYPTO_83_SW_AB_KE_KEY                    ((uint32)1UL)
#define CRYPTO_83_SW_AB_KE_KEYCACHE               ((uint32)1000UL)
#define CRYPTO_83_SW_AB_KE_PLAINKEY               ((uint32)1001UL)
#define CRYPTO_83_SW_AB_KE_UID                    ((uint32)1002UL)
#define CRYPTO_83_SW_AB_KE_SHE_PROOF              ((uint32)1003UL)
#define CRYPTO_83_SW_AB_KE_ENC_CIPHER_IV          ((uint32)1004UL)
#define CRYPTO_83_SW_AB_KE_DEC_CIPHER_IV          ((uint32)1005UL)

/* Crypto_83_sw_Ab_ErrorStatusType */
#define CRYPTO_83_SW_AB_E_NONE                    ((Crypto_83_sw_Ab_ErrorStatusType)0x0000U)
#define CRYPTO_83_SW_AB_E_NOT_INITIALIZED         ((Crypto_83_sw_Ab_ErrorStatusType)0x0001U)
#define CRYPTO_83_SW_AB_E_RAM_CHECK_FAIL          ((Crypto_83_sw_Ab_ErrorStatusType)0x0002U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8                               Crypto_83_sw_ConfigType;
typedef uint16                              Crypto_83_sw_Ab_ErrorStatusType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_sw_START_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

/* Crypto_83_sw_Crypto */
extern FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_Init
(
    P2CONST(Crypto_83_sw_ConfigType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) configPtr
);

extern FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) versioninfo
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_ProcessJob
(
    uint32 objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) job
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_CancelJob
(
    uint32 objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) job
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_Ab_GetErrorStatus
(
    P2VAR(Crypto_83_sw_Ab_ErrorStatusType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptErrorStatus
);

/* Crypto_83_sw_KeyManagement */
extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyElementSet
(
    uint32 cryptoKeyId,
    uint32 keyElementId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) keyPtr,
    uint32 keyLength
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeySetValid
(
    uint32 cryptoKeyId
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyElementGet
(
    uint32 cryptoKeyId,
    uint32 keyElementId,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) resultPtr,
    P2VAR(uint32, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) resultLengthPtr
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_RandomSeed
(
    uint32 cryptoKeyId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) seedPtr,
    uint32 seedLength
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyElementCopy
(
    uint32 cryptoKeyId,
    uint32 keyElementId,
    uint32 targetCryptoKeyId,
    uint32 targetKeyElementId
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyElementCopyPartial
(
    uint32 cryptoKeyId,
    uint32 keyElementId,
    uint32 keyElementSourceOffset,
    uint32 keyElementTargetOffset,
    uint32 keyElementCopyLength,
    uint32 targetCryptoKeyId,
    uint32 targetKeyElementId
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyCopy
(
    uint32 cryptoKeyId,
    uint32 targetCryptoKeyId
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyGenerate
(
    uint32 cryptoKeyId
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyDerive
(
    uint32 cryptoKeyId,
    uint32 targetCryptoKeyId
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyExchangeCalcPubVal
(
    uint32 cryptoKeyId,
    P2VAR(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) publicValuePtr,
    P2VAR(uint32, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) publicValueLengthPtr
);

extern FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_KeyExchangeCalcSecret
(
    uint32 cryptoKeyId,
    P2CONST(uint8, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) partnerPublicValuePtr,
    uint32 partnerPublicValueLength
);

#define CRYPTO_83_sw_STOP_SEC_CODE
#include <Crypto_83_sw_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif  /* CRYPTO_83_SW_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2023/01/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
