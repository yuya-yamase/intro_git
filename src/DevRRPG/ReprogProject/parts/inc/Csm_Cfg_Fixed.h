/* Csm_Cfg_Fixed_h_v2-0-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Csm/CfgFixed/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes                                                                    */
/****************************************************************************/

#ifndef CSM_CFG_FIXED_H
#define CSM_CFG_FIXED_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Csm.h>
#include "../Csm/Csm/cfg/Csm_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/* Csm */
#define CSM_S_JOB_IDLE                      ((Csm_JobStateType)0xE1U)
#define CSM_S_JOB_ACCEPT                    ((Csm_JobStateType)0xD2U)
#define CSM_S_JOB_BUSY                      ((Csm_JobStateType)0xC3U)
#define CSM_S_JOB_CANCEL_ACCEPT             ((Csm_JobStateType)0xB4U)
#define CSM_S_JOB_CANCEL_BUSY               ((Csm_JobStateType)0xA5U)

#define CSM_CFG_STRUCT_PADDING              (3U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/* Csm */

typedef struct {
    P2CONST(AB_83_ConstV uint32, TYPEDEF, CSM_CONFIG_DATA) ptConfig;
    uint32                                  u4ConfigNum;
} Csm_Cfg_KeyConfigAccessType;


typedef struct {
    volatile uint16                         u2JobIndex;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
    uint16                                  u2JobIndexRed;
#endif
} Csm_Cfg_Ram_QueueElementType;

typedef struct {
    uint16                                  u2HeadIndex;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
    uint16                                  u2HeadIndexRed;
#endif
    uint16                                  u2TailIndex;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
    uint16                                  u2TailIndexRed;
#endif
} Csm_Cfg_Ram_QueueRingBufferType;

typedef struct {
    uint32                                  u4QueueSize;
    P2VAR(Csm_Cfg_Ram_QueueElementType, TYPEDEF, CSM_VAR_NO_INIT) ptElementData;
    P2VAR(Csm_Cfg_Ram_QueueRingBufferType, TYPEDEF, CSM_VAR_NO_INIT) ptRingBuffData;
    uint16                                  u2Priority;
    uint16                                  u2Dummy;
} Csm_Cfg_QueuePriorityConfigType;

typedef struct {
    volatile uint32                         u4DequeueStopCount;
    uint16                                  u2HighestPriority;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
    uint16                                  u2HighestPriorityRed;
#endif
    uint16                                  u2TimeOutCount;
    volatile uint16                         u2JobProcessingNum;
#if (CSM_RAM_ERROR_CHECK == STD_ON)
    volatile uint16                         u2JobProcessingNumRed;
#endif
    uint8                                   u1DequeueFlag;
    uint8                                   u1Dummy;
} Csm_Cfg_Ram_QueueChannelDataType;

typedef struct {
    uint32                                  u4CryIfChannelId;
    uint32                                  u4DequeueStop;
    uint32                                  u4ConfigNum;
    P2CONST(AB_83_ConstV Csm_Cfg_QueuePriorityConfigType, TYPEDEF, CSM_CONFIG_DATA) ptPriorityConfig;
    P2VAR(Csm_Cfg_Ram_QueueChannelDataType, TYPEDEF, CSM_VAR_NO_INIT) ptChannelData;
    uint16                                  u2ChannelTimeOut;
    uint16                                  u2Dummy;
} Csm_Cfg_QueueConfigType;

typedef struct {
    P2CONST(AB_83_ConstV Csm_Cfg_QueueConfigType, TYPEDEF, CSM_CONFIG_DATA) ptConfig;
    uint32                                  u4ConfigNum;
} Csm_Cfg_QueueConfigAccessType;


typedef P2FUNC(void, CSM_APPL_CODE, Csm_JobPrimitiveCallbackType)( uint32 jobId, Crypto_ResultType result);

typedef struct {
    const Crypto_JobInfoType                stJobInfo;
    const Crypto_JobPrimitiveInfoType       stJobPrimitiveInfo;
} Csm_Cfg_JobConfigType;

typedef struct {
    P2CONST(AB_83_ConstV Crypto_JobRedirectionInfoType, TYPEDEF, CSM_CONFIG_DATA) ptJobRedirectionInfo;
    P2CONST(AB_83_ConstV uint32, TYPEDEF, CSM_CONFIG_DATA) ptJobKey;
    P2CONST(AB_83_ConstV Csm_Cfg_QueueConfigType, TYPEDEF, CSM_CONFIG_DATA) ptJobQueue;
    const Csm_JobPrimitiveCallbackType      ptJobPrimitiveCallbackFunc;
    uint16                                  u2QueuePriorityIndex;
    uint16                                  u2Dummy;
} Csm_Cfg_JobSubConfigType;

#if (CSM_RAM_ERROR_CHECK == STD_ON)
typedef struct {
    uint32                                  u4InputPtr;
    uint32                                  u4SecondaryInputPtr;
    uint32                                  u4TertiaryInputPtr;
    uint32                                  u4OutputPtr;
    uint32                                  u4OutputLengthPtr;
    uint32                                  u4SecondaryOutputPtr;
    uint32                                  u4SecondaryOutputLengthPtr;
    uint32                                  u4VerifyPtr;
    uint32                                  u4CryIfKeyId;
    uint32                                  u4TargetCryIfKeyId;
} Csm_Cfg_Ram_JobInOutRedType;
#endif

typedef uint8 Csm_JobStateType;

typedef struct {
    Crypto_JobType                          stJob;
    Crypto_JobRedirectionInfoType           stJobRedirectionInfo;
} Csm_Cfg_Ram_JobDataType;

typedef struct {
#if (CSM_RAM_ERROR_CHECK == STD_ON)
    Csm_Cfg_Ram_JobInOutRedType             stJobInOutRed;
#endif
    volatile Csm_JobStateType               udCsmJobState;
    uint8                                   u1Dummy[CSM_CFG_STRUCT_PADDING];
} Csm_Cfg_Ram_JobSubDataType;

typedef struct {
    P2CONST(Csm_Cfg_JobConfigType, TYPEDEF, CSM_SHARED_CONFIG_DATA) ptConfig;
    P2CONST(Csm_Cfg_JobSubConfigType, TYPEDEF, CSM_CONFIG_DATA)     ptSubConfig;
    P2VAR(Csm_Cfg_Ram_JobDataType, TYPEDEF, CSM_SHARED_VAR_NO_INIT) ptData;
    P2VAR(Csm_Cfg_Ram_JobSubDataType, TYPEDEF, CSM_VAR_NO_INIT)     ptSubData;
    uint32                                  u4ConfigNum;
} Csm_Cfg_JobConfigAccessType;


typedef P2FUNC(void, CSM_APPL_CODE, Csm_ErrorCalloutType)( Csm_Ab_ErrorStatusType udErrorStatus );

typedef struct {
    P2CONST(AB_83_ConstV Csm_ErrorCalloutType, TYPEDEF, CSM_CONFIG_DATA) ptConfig;
    uint32                                  u4ConfigNum;
} Csm_Cfg_ErrorCalloutConfigAccessType;

typedef P2FUNC(void, CSM_APPL_CODE, Csm_TimeOutCalloutType)( uint32 u4ChannelId );

typedef struct {
    P2CONST(AB_83_ConstV Csm_TimeOutCalloutType, TYPEDEF, CSM_CONFIG_DATA) ptConfig;
    uint32                                  u4ConfigNum;
} Csm_Cfg_TimeOutCalloutConfigAccessType;


/* CryIf */

typedef struct {
    uint32                                  u4CryptoKeyId;
    uint32                                  u4CryptoIndex;
} CryIf_Cfg_KeyConfigType;

typedef struct {
    P2CONST(AB_83_ConstV CryIf_Cfg_KeyConfigType, TYPEDEF, CSM_CONFIG_DATA) ptConfig;
    uint32                                  u4ConfigNum;
} CryIf_Cfg_KeyConfigAccessType;


typedef struct {
    uint32                                  u4ObjectId;
    uint32                                  u4CryptoIndex;
} CryIf_Cfg_ChannelConfigType;

typedef struct {
    P2CONST(AB_83_ConstV CryIf_Cfg_ChannelConfigType, TYPEDEF, CSM_CONFIG_DATA) ptConfig;
    uint32                                  u4ConfigNum;
} CryIf_Cfg_ChannelConfigAccessType;


typedef P2FUNC(Std_ReturnType, CSM_APPL_CODE, CryIf_FuncProcessJobType) ( uint32 channelId, P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job );
typedef P2FUNC(Std_ReturnType, CSM_APPL_CODE, CryIf_FuncCancelJobType) ( uint32 channelId, P2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job );
typedef P2FUNC(Std_ReturnType, CSM_APPL_CODE, CryIf_FuncKeyElementSetType) ( uint32 cryIfKeyId, uint32 keyElementId, P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) keyPtr, uint32 keyLength );
typedef P2FUNC(Std_ReturnType, CSM_APPL_CODE, CryIf_FuncKeySetValidType) ( uint32 cryIfKeyId );
typedef P2FUNC(Std_ReturnType, CSM_APPL_CODE, CryIf_FuncKeyElemGetType) ( uint32 cryIfKeyId, uint32 keyElementId, P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) resultPtr, P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) resultLengthPtr );
typedef P2FUNC(Std_ReturnType, CSM_APPL_CODE, CryIf_FuncKeyElemCopyType) ( uint32 cryIfKeyId, uint32 keyElementId, uint32 targetCryIfKeyId, uint32 targetKeyElementId );
typedef P2FUNC(Std_ReturnType, CSM_APPL_CODE, CryIf_FuncKeyElemCopyPartType) ( uint32 cryIfKeyId, uint32 keyElementId, uint32 keyElementSourceOffset, uint32 keyElementTargetOffset, uint32 keyElementCopyLength, uint32 targetCryIfKeyId, uint32 targetKeyElementId );
typedef P2FUNC(Std_ReturnType, CSM_APPL_CODE, CryIf_FuncKeyCopyType) ( uint32 cryIfKeyId, uint32 targetCryIfKeyId );
typedef P2FUNC(Std_ReturnType, CSM_APPL_CODE, CryIf_FuncRandomSeedType) ( uint32 cryIfKeyId, P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) seedPtr, uint32 seedLength );
typedef P2FUNC(Std_ReturnType, CSM_APPL_CODE, CryIf_FuncKeyGenerateType) ( uint32 cryIfKeyId );
typedef P2FUNC(Std_ReturnType, CSM_APPL_CODE, CryIf_FuncKeyDeriveType) ( uint32 cryIfKeyId, uint32 targetCryIfKeyId );
typedef P2FUNC(Std_ReturnType, CSM_APPL_CODE, CryIf_FuncKeyExCalcPubValType) ( uint32 cryIfKeyId, P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) publicValuePtr, P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) publicValueLengthPtr );
typedef P2FUNC(Std_ReturnType, CSM_APPL_CODE, CryIf_FuncKeyExCalcSecretType) ( uint32 cryIfKeyId, P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) partnerPublicValuePtr, uint32 partnerPublicValueLength );

typedef struct {
    CryIf_FuncProcessJobType                ptProcessJob;
    CryIf_FuncCancelJobType                 ptCancelJob;
    CryIf_FuncKeyElementSetType             ptKeyElementSet;
    CryIf_FuncKeySetValidType               ptKeySetValid;
    CryIf_FuncKeyElemGetType                ptKeyElementGet;
    CryIf_FuncKeyElemCopyType               ptKeyElementCopy;
    CryIf_FuncKeyElemCopyPartType           ptKeyElemCopyPart;
    CryIf_FuncKeyCopyType                   ptKeyCopy;
    CryIf_FuncRandomSeedType                ptRandomSeed;
    CryIf_FuncKeyGenerateType               ptKeyGenerate;
    CryIf_FuncKeyDeriveType                 ptKeyDerive;
    CryIf_FuncKeyExCalcPubValType           ptKeyExCalcPubVal;
    CryIf_FuncKeyExCalcSecretType           ptKeyExCalcSecret;
} CryIf_Cfg_FuncConfigType;

typedef struct {
    P2CONST(AB_83_ConstV CryIf_Cfg_FuncConfigType, TYPEDEF, CSM_CONFIG_DATA) ptConfig;
    uint32                                  u4ConfigNum;
} CryIf_Cfg_FuncConfigAccessType;


typedef struct {
    P2VAR(uint8, TYPEDEF, CSM_SHARED_VAR_NO_INIT) ptConfig;
    uint32                                  u4ConfigNum;
} CryIf_Cfg_ElemConfigAccessType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define CSM_START_SEC_CONST_CONFIG
#include <Csm_MemMap.h>

/* Csm */
extern CONST(AB_83_ConstV boolean, CSM_CONFIG_DATA) Csm_Cfg_bVersionInfoApi;
extern CONST(AB_83_ConstV Csm_Cfg_KeyConfigAccessType, CSM_CONFIG_DATA) Csm_Cfg_stKey;
extern CONST(AB_83_ConstV Csm_Cfg_QueueConfigAccessType, CSM_CONFIG_DATA) Csm_Cfg_stQueue;
extern CONST(Csm_Cfg_JobConfigAccessType, CSM_CONFIG_DATA) Csm_Cfg_stJob;
extern CONST(AB_83_ConstV Csm_Cfg_ErrorCalloutConfigAccessType, CSM_CONFIG_DATA) Csm_Cfg_stErrorCallout;
extern CONST(AB_83_ConstV Csm_Cfg_TimeOutCalloutConfigAccessType, CSM_CONFIG_DATA) Csm_Cfg_stTimeOutCallout;

/* CryIf */
extern CONST(AB_83_ConstV boolean, CSM_CONFIG_DATA) CryIf_Cfg_bVersionInfoApi;
extern CONST(AB_83_ConstV CryIf_Cfg_KeyConfigAccessType, CSM_CONFIG_DATA) CryIf_Cfg_stKey;
extern CONST(AB_83_ConstV CryIf_Cfg_ChannelConfigAccessType, CSM_CONFIG_DATA) CryIf_Cfg_stChannel;
extern CONST(AB_83_ConstV CryIf_Cfg_FuncConfigAccessType, CSM_CONFIG_DATA) CryIf_Cfg_stFunc;
extern CONST(AB_83_ConstV CryIf_Cfg_ElemConfigAccessType, CSM_CONFIG_DATA) CryIf_Cfg_stElem;

#define CSM_STOP_SEC_CONST_CONFIG
#include <Csm_MemMap.h>

#endif /* CSM_CFG_FIXED_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2022/12/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
