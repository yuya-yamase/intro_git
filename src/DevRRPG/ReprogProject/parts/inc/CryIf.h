/* CryIf_h_v2-0-0                                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | CryIf/HEADER                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef CRYIF_H
#define CRYIF_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Crypto_GeneralTypes.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/* CryIf Version */
#define CRYIF_VENDOR_ID                       (0x0053U)
#define CRYIF_MODULE_ID                       (112U)
#define CRYIF_SW_MAJOR_VERSION                (1U)
#define CRYIF_SW_MINOR_VERSION                (0U)
#define CRYIF_SW_PATCH_VERSION                (0U)
#define CRYIF_AR_RELEASE_MAJOR_VERSION        (4U)
#define CRYIF_AR_RELEASE_MINOR_VERSION        (5U)
#define CRYIF_AR_RELEASE_REVISION_VERSION     (0U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/* SWS_CryIf_91118 */
typedef uint8      CryIf_ConfigType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define CRYIF_START_SEC_CODE
#include <CryIf_MemMap.h>

/* SWS_CryIf_91000 */
extern FUNC(void, CRYIF_CODE) CryIf_Init
(
    P2CONST(CryIf_ConfigType, AUTOMATIC, CRYIF_APPL_DATA) configPtr
);

/* SWS_CryIf_91001 */
extern FUNC(void, CRYIF_CODE) CryIf_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, CRYIF_APPL_DATA) versioninfo
);

/* SWS_CryIf_91003 */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_ProcessJob
(
    uint32 channelId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYIF_APPL_DATA) job
);

/* SWS_CryIf_91014 */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_CancelJob
(
    uint32 channelId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYIF_APPL_DATA) job
);

/* SWS_CryIf_91013 */
extern FUNC(void, CRYIF_CODE) CryIf_CallbackNotification
(
    P2VAR(Crypto_JobType, AUTOMATIC, CRYIF_APPL_DATA) job,
    Crypto_ResultType result
);

/* SWS_CryIf_91004 */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyElementSet
(
    uint32 cryIfKeyId,
    uint32 keyElementId,
    P2CONST(uint8, AUTOMATIC, CRYIF_APPL_DATA) keyPtr,
    uint32 keyLength
);

/* SWS_CryIf_91005 */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeySetValid
(
    uint32 cryIfKeyId
);

/* SWS_CryIf_91006 */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyElementGet
(
    uint32 cryIfKeyId,
    uint32 keyElementId,
    P2VAR(uint8, AUTOMATIC, CRYIF_APPL_DATA) resultPtr,
    P2VAR(uint32, AUTOMATIC, CRYIF_APPL_DATA) resultLengthPtr
);

/* SWS_CryIf_91015 */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyElementCopy
(
    uint32 cryIfKeyId,
    uint32 keyElementId,
    uint32 targetCryIfKeyId,
    uint32 targetKeyElementId
);

/* SWS_CryIf_91018 */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyElementCopyPartial
(
    uint32 cryIfKeyId,
    uint32 keyElementId,
    uint32 keyElementSourceOffset,
    uint32 keyElementTargetOffset,
    uint32 keyElementCopyLength,
    uint32 targetCryIfKeyId,
    uint32 targetKeyElementId
);

/* SWS_CryIf_91016 */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyCopy
(
    uint32 cryIfKeyId,
    uint32 targetCryIfKeyId
);

/* SWS_CryIf_91007 */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_RandomSeed
(
    uint32 cryIfKeyId,
    P2CONST(uint8, AUTOMATIC, CRYIF_APPL_DATA) seedPtr,
    uint32 seedLength
);

/* SWS_CryIf_91008 */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyGenerate
(
    uint32 cryIfKeyId
);

/* SWS_CryIf_91009 */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyDerive
(
    uint32 cryIfKeyId,
    uint32 targetCryIfKeyId
);

/* SWS_CryIf_91010 */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyExchangeCalcPubVal
(
    uint32 cryIfKeyId,
    P2VAR(uint8, AUTOMATIC, CRYIF_APPL_DATA) publicValuePtr,
    P2VAR(uint32, AUTOMATIC, CRYIF_APPL_DATA) publicValueLengthPtr
);

/* SWS_CryIf_91011 */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyExchangeCalcSecret
(
    uint32 cryIfKeyId,
    P2CONST(uint8, AUTOMATIC, CRYIF_APPL_DATA) partnerPublicValuePtr,
    uint32 partnerPublicValueLength
);

#define CRYIF_STOP_SEC_CODE
#include <CryIf_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif /* CRYIF_H */


/****************************************************************************/
/*  History                                                                 */
/*  Version        :Date                                                    */
/*  v2-0-0         :2023/01/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
