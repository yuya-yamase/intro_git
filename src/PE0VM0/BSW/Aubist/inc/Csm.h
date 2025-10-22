/* Csm_h_v2-0-0                                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Csm/HEADER                                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CSM_H
#define CSM_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Crypto_GeneralTypes.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* CSM Version */
#define CSM_VENDOR_ID                       (0x0053U)
#define CSM_MODULE_ID                       (110U)
#define CSM_SW_MAJOR_VERSION                (1U)
#define CSM_SW_MINOR_VERSION                (0U)
#define CSM_SW_PATCH_VERSION                (0U)
#define CSM_AR_RELEASE_MAJOR_VERSION        (4U)
#define CSM_AR_RELEASE_MINOR_VERSION        (5U)
#define CSM_AR_RELEASE_REVISION_VERSION     (0U)

#define CSM_AB_M_UNINIT                     ((Csm_Ab_ModeType)0U)
#define CSM_AB_M_IDLE                       ((Csm_Ab_ModeType)1U)
#define CSM_AB_M_RUN                        ((Csm_Ab_ModeType)2U)
#define CSM_AB_M_ABNORMAL                   ((Csm_Ab_ModeType)3U)

#define CSM_AB_E_NONE                       ((Csm_Ab_ErrorStatusType)0x0000U)
#define CSM_AB_E_NOT_INITIALIZED            ((Csm_Ab_ErrorStatusType)0x0001U)
#define CSM_AB_E_RAM_CHECK_FAIL             ((Csm_Ab_ErrorStatusType)0x0002U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/* SWS_Csm_01085 */
typedef uint8       Csm_ConfigType;

typedef uint8       Csm_Ab_ModeType;
typedef uint16      Csm_Ab_ErrorStatusType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define CSM_START_SEC_CODE
#include <Csm_MemMap.h>

/* SWS_Csm_00646 */
extern FUNC(void, CSM_CODE) Csm_Init
(
    P2CONST(Csm_ConfigType, AUTOMATIC, CSM_APPL_DATA) configPtr
);

/* SWS_Csm_00705 */
extern FUNC(void, CSM_CODE) Csm_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, CSM_APPL_DATA) versioninfo
);

/* SWS_Csm_00980 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_Hash
(
    uint32 jobId,
    Crypto_OperationModeType mode,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) dataPtr,
    uint32 dataLength,
    P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) resultPtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
);

/* SWS_Csm_00982 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_MacGenerate
(
    uint32 jobId,
    Crypto_OperationModeType mode,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) dataPtr,
    uint32 dataLength,
    P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) macPtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) macLengthPtr
);

/* SWS_Csm_01050 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_MacVerify
(
    uint32 jobId,
    Crypto_OperationModeType mode,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) dataPtr,
    uint32 dataLength,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) macPtr,
    const uint32 macLength,
    P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA) verifyPtr
);

/* SWS_Csm_00984 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_Encrypt
(
    uint32 jobId,
    Crypto_OperationModeType mode,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) dataPtr,
    uint32 dataLength,
    P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) resultPtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
);

/* SWS_Csm_00989 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_Decrypt
(
    uint32 jobId,
    Crypto_OperationModeType mode,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) dataPtr,
    uint32 dataLength,
    P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) resultPtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
);

/* SWS_Csm_01023 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_AEADEncrypt
(
    uint32 jobId,
    Crypto_OperationModeType mode,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) plaintextPtr,
    uint32 plaintextLength,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) associatedDataPtr,
    uint32 associatedDataLength,
    P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) ciphertextPtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) ciphertextLengthPtr,
    P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) tagPtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) tagLengthPtr
);

/* SWS_Csm_01026 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_AEADDecrypt
(
    uint32 jobId,
    Crypto_OperationModeType mode,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) ciphertextPtr,
    uint32 ciphertextLength,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) associatedDataPtr,
    uint32 associatedDataLength,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) tagPtr,
    uint32 tagLength,
    P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) plaintextPtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) plaintextLengthPtr,
    P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA) verifyPtr
);

/* SWS_Csm_00992 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_SignatureGenerate
(
    uint32 jobId,
    Crypto_OperationModeType mode,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) dataPtr,
    uint32 dataLength,
    P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) resultPtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
);

/* SWS_Csm_00996 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_SignatureVerify
(
    uint32 jobId,
    Crypto_OperationModeType mode,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) dataPtr,
    uint32 dataLength,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) signaturePtr,
    uint32 signatureLength,
    P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA) verifyPtr
);

/* SWS_Csm_01543 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_RandomGenerate
(
    uint32 jobId,
    P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) resultPtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
);

/* SWS_Csm_00957 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementSet
(
    uint32 keyId,
    uint32 keyElementId,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) keyPtr,
    uint32 keyLength
);

/* SWS_Csm_00958 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeySetValid
(
    uint32 keyId
);

/* SWS_Csm_00959 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementGet
(
    uint32 keyId,
    uint32 keyElementId,
    P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) keyPtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) keyLengthPtr
);

/* SWS_Csm_00969 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementCopy
(
    const uint32 keyId,
    const uint32 keyElementId,
    const uint32 targetKeyId,
    const uint32 targetKeyElementId
);

/* SWS_Csm_01034 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyCopy
(
    const uint32 keyId,
    const uint32 targetKeyId
);

/* SWS_Csm_91025 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyElementCopyPartial
(
    uint32 keyId,
    uint32 keyElementId,
    uint32 keyElementSourceOffset,
    uint32 keyElementTargetOffset,
    uint32 keyElementCopyLength,
    uint32 targetKeyId,
    uint32 targetKeyElementId
);

/* SWS_Csm_01051 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_RandomSeed
(
    uint32 keyId,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) seedPtr,
    uint32 seedLength
);

/* SWS_Csm_00955 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyGenerate
(
    uint32 keyId
);

/* SWS_Csm_00956 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyDerive
(
    uint32 keyId,
    uint32 targetKeyId
);

/* SWS_Csm_00966 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyExchangeCalcPubVal
(
    uint32 keyId,
    P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) publicValuePtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) publicValueLengthPtr
);

/* SWS_Csm_00967 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_KeyExchangeCalcSecret
(
    uint32 keyId,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) partnerPublicValuePtr,
    uint32 partnerPublicValueLength
);

/* SWS_Csm_91027 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeySetValid
(
    uint32 jobId,
    uint32 keyId
);

/* SWS_Csm_91028 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_JobRandomSeed
(
    uint32 jobId,
    uint32 keyId,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) seedPtr,
    uint32 seedLength
);

/* SWS_Csm_91029 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyGenerate
(
    uint32 jobId,
    uint32 keyId
);

/* SWS_Csm_91030 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyDerive
(
    uint32 jobId,
    uint32 keyId,
    uint32 targetKeyId
);

/* SWS_Csm_91031 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyExchangeCalcPubVal
(
    uint32 jobId,
    uint32 keyId,
    P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) publicValuePtr,
    P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) publicValueLengthPtr
);

/* SWS_Csm_91032 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeyExchangeCalcSecret
(
    uint32 jobId,
    uint32 keyId,
    P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) partnerPublicValuePtr,
    uint32 partnerPublicValueLength
);

/* SWS_Csm_00968 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_CancelJob
(
    uint32 job,
    Crypto_OperationModeType mode
);

/* SWS_Csm_00970 */
extern FUNC(void, CSM_CODE) Csm_CallbackNotification
(
    P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job,
    Crypto_ResultType result
);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_Ab_GetMode
(
    P2VAR(Csm_Ab_ModeType, AUTOMATIC, CSM_APPL_DATA) ptMode
);

extern FUNC(Std_ReturnType, CSM_CODE) Csm_Ab_GetErrorStatus
(
    P2VAR(Csm_Ab_ErrorStatusType, AUTOMATIC, CSM_APPL_DATA) ptErrorStatus
);

#define CSM_STOP_SEC_CODE
#include <Csm_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif /* CSM_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2023/01/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
