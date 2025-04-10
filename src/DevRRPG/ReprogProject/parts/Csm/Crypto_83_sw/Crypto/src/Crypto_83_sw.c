/* Crypto_83_sw_c_v2-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Crypto_83_sw/CODE                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Crypto_83_sw.h>
#include <SchM_Crypto_83_sw.h>
#include "../inc/Crypto_83_sw_Internal.h"
#include "../../SWSHE/inc/Crypto_83_sw_SWSHE.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* CryptoDriverObject Status */
#define CRYPTO_83_SW_S_CDO_IDLE                     ((Crypto_83_sw_ObjectStatusType)0xF0U)
#define CRYPTO_83_SW_S_CDO_ACTIVE                   ((Crypto_83_sw_ObjectStatusType)0xE1U)
#define CRYPTO_83_SW_S_CDO_UPDATED                  ((Crypto_83_sw_ObjectStatusType)0xD2U)

/* CryptoDriverObject CallBack Status */
#define CRYPTO_83_SW_S_CDO_CB_NONE                  ((Crypto_83_sw_CallBackStatusType)0xF0U)
#define CRYPTO_83_SW_S_CDO_CB_WAIT                  ((Crypto_83_sw_CallBackStatusType)0xE1U)

/* Object Table Num */
#define CRYPTO_83_SW_OBJECT_00_SERVICE_TABLE_NUM    ((uint8)1U)
#define CRYPTO_83_SW_OBJECT_01_SERVICE_TABLE_NUM    ((uint8)1U)
#define CRYPTO_83_SW_OBJECT_02_SERVICE_TABLE_NUM    ((uint8)1U)
#define CRYPTO_83_SW_OBJECT_03_SERVICE_TABLE_NUM    ((uint8)1U)
#define CRYPTO_83_SW_OBJECT_04_SERVICE_TABLE_NUM    ((uint8)2U)
#define CRYPTO_83_SW_OBJECT_05_SERVICE_TABLE_NUM    ((uint8)2U)
#define CRYPTO_83_SW_OBJECT_06_SERVICE_TABLE_NUM    ((uint8)2U)
#define CRYPTO_83_SW_OBJECT_07_SERVICE_TABLE_NUM    ((uint8)1U)
#define CRYPTO_83_SW_OBJECT_08_SERVICE_TABLE_NUM    ((uint8)1U)

/* Object Ram Num */
#define CRYPTO_83_SW_OBJECT_00_RAM                  ((uint8)0U)
#define CRYPTO_83_SW_OBJECT_01_RAM                  ((uint8)1U)
#define CRYPTO_83_SW_OBJECT_02_RAM                  ((uint8)2U)
#define CRYPTO_83_SW_OBJECT_03_RAM                  ((uint8)3U)
#define CRYPTO_83_SW_OBJECT_04_RAM                  ((uint8)4U)
#define CRYPTO_83_SW_OBJECT_05_RAM                  ((uint8)5U)
#define CRYPTO_83_SW_OBJECT_06_RAM                  ((uint8)6U)
#define CRYPTO_83_SW_OBJECT_07_RAM                  ((uint8)7U)
#define CRYPTO_83_SW_OBJECT_08_RAM                  ((uint8)8U)

/* SA or SC Select */
#define CRYPTO_83_SW_SA_SELECT                      ((Crypto_83_sw_SaScSelectType)1U)
#define CRYPTO_83_SW_SC_SELECT                      ((Crypto_83_sw_SaScSelectType)2U)

#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
/*Init for RedundantData*/
#define CRYPTO_83_SW_RED_INIT_U4                    ((uint32)0xFFFFFFFFUL)
#endif

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8    Crypto_83_sw_ObjectStatusType;
typedef uint8    Crypto_83_sw_CallBackStatusType;
typedef uint8    Crypto_83_sw_SaScSelectType;
typedef P2FUNC(Std_ReturnType, CRYPTO_83_sw_CODE, Crypto_83_sw_CmdFuncType)(P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob);

typedef struct
{
    Crypto_ServiceInfoType        udService;
    Crypto_AlgorithmModeType      udMode;
    Crypto_AlgorithmFamilyType    udFamily;
    Crypto_83_sw_SaScSelectType   udSaScSelect;
    Crypto_83_sw_CmdFuncType      ptStartFunc;
    Crypto_83_sw_CmdFuncType      ptUpdateFunc;
    Crypto_83_sw_CmdFuncType      ptFinishFunc;
    Crypto_83_sw_CmdFuncType      ptSingleCallFunc;
} Crypto_83_sw_ServiceTableType;

typedef struct
{
    uint32                                                   u4JobId;
    P2VAR(Crypto_JobType, TYPEDEF, CRYPTO_83_sw_APPL_DATA)   ptJob;
    Crypto_83_sw_ObjectStatusType                            udCryptoDriverObjectStatus;
    Crypto_83_sw_CallBackStatusType                          udCallBackStatus;
    Crypto_ResultType                                        udResult;
    uint8                                                    u1ServiceIndex;
} Crypto_83_sw_ObjectRamType;

#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
typedef struct
{
    uint32 u4JobIdRed;
    uint32 u4JobRed;
    uint32 u4Job_JobInfoRed;
} Crypto_83_sw_ObjectRamRedType;
#endif

typedef struct
{
    P2CONST(AB_83_ConstV Crypto_83_sw_ServiceTableType, TYPEDEF, CRYPTO_83_sw_CONST)       ptServiceTable;
    uint32                                                                                 u4ServiceNum;
    P2VAR(Crypto_83_sw_ObjectRamType, TYPEDEF, CRYPTO_83_sw_VAR_NO_INIT)        ptObjectRam;
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
    P2VAR(Crypto_83_sw_ObjectRamRedType, TYPEDEF, CRYPTO_83_sw_VAR_NO_INIT)     ptObjectRamRed;
#endif
} Crypto_83_sw_ObjectTableType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_sw_START_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SearchServiceTable
(
    P2CONST(AB_83_ConstV Crypto_83_sw_ObjectTableType, AUTOMATIC, CRYPTO_83_sw_CONST) ptObjectTable,
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
);

static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SA_Start_ProcessJob
(
    P2CONST(AB_83_ConstV Crypto_83_sw_ObjectTableType, AUTOMATIC, CRYPTO_83_sw_CONST) ptObjectTable
);

static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SA_Update_ProcessJob
(
    P2CONST(AB_83_ConstV Crypto_83_sw_ObjectTableType, AUTOMATIC, CRYPTO_83_sw_CONST) ptObjectTable
);

static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SA_Finish_ProcessJob
(
    P2CONST(AB_83_ConstV Crypto_83_sw_ObjectTableType, AUTOMATIC, CRYPTO_83_sw_CONST) ptObjectTable
);

static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SC_ProcessJob
(
    P2CONST(AB_83_ConstV Crypto_83_sw_ObjectTableType, AUTOMATIC, CRYPTO_83_sw_CONST) ptObjectTable
);

static FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_DetectError
(
    void
);

#define CRYPTO_83_sw_STOP_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_sw_START_SEC_VAR_CLEARED_WAKEUP
#include <Crypto_83_sw_MemMap.h>

static VAR(Crypto_83_sw_DriverStatusType, CRYPTO_83_sw_VAR_CLEARED_WAKEUP)                Crypto_83_sw_udDriverStatus;

#define CRYPTO_83_sw_STOP_SEC_VAR_CLEARED_WAKEUP
#include <Crypto_83_sw_MemMap.h>

#define CRYPTO_83_sw_START_SEC_VAR_NO_INIT
#include <Crypto_83_sw_MemMap.h>

static VAR(Crypto_83_sw_ObjectRamType, CRYPTO_83_sw_VAR_NO_INIT)                          Crypto_83_sw_stObjectRam[CRYPTO_83_SW_OBJECT_NUM];

#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
static VAR(Crypto_83_sw_ObjectRamRedType, CRYPTO_83_sw_VAR_NO_INIT)                       Crypto_83_sw_stObjectRamRed[CRYPTO_83_SW_OBJECT_NUM];
#endif

#define CRYPTO_83_sw_STOP_SEC_VAR_NO_INIT
#include <Crypto_83_sw_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define CRYPTO_83_sw_START_SEC_CONST
#include <Crypto_83_sw_MemMap.h>

static CONST(AB_83_ConstV Crypto_83_sw_ServiceTableType, CRYPTO_83_sw_CONST)    Crypto_83_sw_stObject00ServiceTable[CRYPTO_83_SW_OBJECT_00_SERVICE_TABLE_NUM] =
{
    {CRYPTO_MACVERIFY,        CRYPTO_ALGOMODE_CMAC,               CRYPTO_ALGOFAM_AES,       CRYPTO_83_SW_SC_SELECT,  NULL_PTR,                             NULL_PTR,                              NULL_PTR,                              &Crypto_83_sw_MacVer}
};

static CONST(AB_83_ConstV Crypto_83_sw_ServiceTableType, CRYPTO_83_sw_CONST)    Crypto_83_sw_stObject01ServiceTable[CRYPTO_83_SW_OBJECT_01_SERVICE_TABLE_NUM] =
{
    {CRYPTO_MACGENERATE,      CRYPTO_ALGOMODE_CMAC,               CRYPTO_ALGOFAM_AES,       CRYPTO_83_SW_SC_SELECT,  NULL_PTR,                             NULL_PTR,                              NULL_PTR,                              &Crypto_83_sw_MacGen}
};

static CONST(AB_83_ConstV Crypto_83_sw_ServiceTableType, CRYPTO_83_sw_CONST)    Crypto_83_sw_stObject02ServiceTable[CRYPTO_83_SW_OBJECT_02_SERVICE_TABLE_NUM] =
{
    {CRYPTO_RANDOMSEED,       CRYPTO_ALGOMODE_CTRDRBG,            CRYPTO_ALGOFAM_RNG,       CRYPTO_83_SW_SC_SELECT,  NULL_PTR,                             NULL_PTR,                              NULL_PTR,                              &Crypto_83_sw_JobRndSeed}
};

static CONST(AB_83_ConstV Crypto_83_sw_ServiceTableType, CRYPTO_83_sw_CONST)    Crypto_83_sw_stObject03ServiceTable[CRYPTO_83_SW_OBJECT_03_SERVICE_TABLE_NUM] =
{
    {CRYPTO_RANDOMGENERATE,   CRYPTO_ALGOMODE_CTRDRBG,            CRYPTO_ALGOFAM_RNG,       CRYPTO_83_SW_SC_SELECT,  NULL_PTR,                             NULL_PTR,                              NULL_PTR,                              &Crypto_83_sw_RndGen}
};

static CONST(AB_83_ConstV Crypto_83_sw_ServiceTableType, CRYPTO_83_sw_CONST)    Crypto_83_sw_stObject04ServiceTable[CRYPTO_83_SW_OBJECT_04_SERVICE_TABLE_NUM] =
{
    {CRYPTO_ENCRYPT,          CRYPTO_ALGOMODE_ECB,                CRYPTO_ALGOFAM_AES,       CRYPTO_83_SW_SC_SELECT,  NULL_PTR,                             NULL_PTR,                              NULL_PTR,                              &Crypto_83_sw_EcbEnc},
    {CRYPTO_ENCRYPT,          CRYPTO_ALGOMODE_CBC,                CRYPTO_ALGOFAM_AES,       CRYPTO_83_SW_SC_SELECT,  NULL_PTR,                             NULL_PTR,                              NULL_PTR,                              &Crypto_83_sw_CbcEnc}
};

static CONST(AB_83_ConstV Crypto_83_sw_ServiceTableType, CRYPTO_83_sw_CONST)    Crypto_83_sw_stObject05ServiceTable[CRYPTO_83_SW_OBJECT_05_SERVICE_TABLE_NUM] =
{
    {CRYPTO_DECRYPT,          CRYPTO_ALGOMODE_ECB,                CRYPTO_ALGOFAM_AES,       CRYPTO_83_SW_SA_SELECT,  &Crypto_83_sw_EcbDecStart,            &Crypto_83_sw_EcbDecUpdate,            &Crypto_83_sw_EcbDecFinish,            NULL_PTR},
    {CRYPTO_DECRYPT,          CRYPTO_ALGOMODE_CBC,                CRYPTO_ALGOFAM_AES,       CRYPTO_83_SW_SA_SELECT,  &Crypto_83_sw_CbcDecStart,            &Crypto_83_sw_CbcDecUpdate,            &Crypto_83_sw_CbcDecFinish,            NULL_PTR}
};

static CONST(AB_83_ConstV Crypto_83_sw_ServiceTableType, CRYPTO_83_sw_CONST)    Crypto_83_sw_stObject06ServiceTable[CRYPTO_83_SW_OBJECT_06_SERVICE_TABLE_NUM] =
{
    {CRYPTO_SIGNATUREVERIFY,  CRYPTO_ALGOMODE_RSASSA_PKCS1_v1_5,  CRYPTO_ALGOFAM_RSA,       CRYPTO_83_SW_SA_SELECT,  &Crypto_83_sw_RSA_PKCS1_SigVerStart,  &Crypto_83_sw_RSA_PKCS1_SigVerUpdate,  &Crypto_83_sw_RSA_PKCS1_SigVerFinish,  NULL_PTR},
    {CRYPTO_SIGNATUREVERIFY,  CRYPTO_ALGOMODE_RSASSA_PSS,         CRYPTO_ALGOFAM_RSA,       CRYPTO_83_SW_SA_SELECT,  &Crypto_83_sw_RSA_PSS_SigVerStart,    &Crypto_83_sw_RSA_PSS_SigVerUpdate,    &Crypto_83_sw_RSA_PSS_SigVerFinish,    NULL_PTR}
};

static CONST(AB_83_ConstV Crypto_83_sw_ServiceTableType, CRYPTO_83_sw_CONST)    Crypto_83_sw_stObject07ServiceTable[CRYPTO_83_SW_OBJECT_07_SERVICE_TABLE_NUM] =
{
    {CRYPTO_KEYSETVALID,      CRYPTO_ALGOMODE_NOT_SET,            CRYPTO_ALGOFAM_NOT_SET,   CRYPTO_83_SW_SC_SELECT,  NULL_PTR,                             NULL_PTR,                              NULL_PTR,                              &Crypto_83_sw_JobKeySetValid}
};

static CONST(AB_83_ConstV Crypto_83_sw_ServiceTableType, CRYPTO_83_sw_CONST)    Crypto_83_sw_stObject08ServiceTable[CRYPTO_83_SW_OBJECT_08_SERVICE_TABLE_NUM] =
{
    {CRYPTO_HASH,             CRYPTO_ALGOMODE_NOT_SET,            CRYPTO_ALGOFAM_SHA2_256,  CRYPTO_83_SW_SC_SELECT,  NULL_PTR,                             NULL_PTR,                              NULL_PTR,                              &Crypto_83_sw_Hash}
};

static CONST(AB_83_ConstV Crypto_83_sw_ObjectTableType, CRYPTO_83_sw_CONST)     Crypto_83_sw_stObjectTable[CRYPTO_83_SW_OBJECT_NUM] = 
{
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
    {&Crypto_83_sw_stObject00ServiceTable[0],   CRYPTO_83_SW_OBJECT_00_SERVICE_TABLE_NUM,   &Crypto_83_sw_stObjectRam[CRYPTO_83_SW_OBJECT_00_RAM],   &Crypto_83_sw_stObjectRamRed[CRYPTO_83_SW_OBJECT_00_RAM]},
    {&Crypto_83_sw_stObject01ServiceTable[0],   CRYPTO_83_SW_OBJECT_01_SERVICE_TABLE_NUM,   &Crypto_83_sw_stObjectRam[CRYPTO_83_SW_OBJECT_01_RAM],   &Crypto_83_sw_stObjectRamRed[CRYPTO_83_SW_OBJECT_01_RAM]},
    {&Crypto_83_sw_stObject02ServiceTable[0],   CRYPTO_83_SW_OBJECT_02_SERVICE_TABLE_NUM,   &Crypto_83_sw_stObjectRam[CRYPTO_83_SW_OBJECT_02_RAM],   &Crypto_83_sw_stObjectRamRed[CRYPTO_83_SW_OBJECT_02_RAM]},
    {&Crypto_83_sw_stObject03ServiceTable[0],   CRYPTO_83_SW_OBJECT_03_SERVICE_TABLE_NUM,   &Crypto_83_sw_stObjectRam[CRYPTO_83_SW_OBJECT_03_RAM],   &Crypto_83_sw_stObjectRamRed[CRYPTO_83_SW_OBJECT_03_RAM]},
    {&Crypto_83_sw_stObject04ServiceTable[0],   CRYPTO_83_SW_OBJECT_04_SERVICE_TABLE_NUM,   &Crypto_83_sw_stObjectRam[CRYPTO_83_SW_OBJECT_04_RAM],   &Crypto_83_sw_stObjectRamRed[CRYPTO_83_SW_OBJECT_04_RAM]},
    {&Crypto_83_sw_stObject05ServiceTable[0],   CRYPTO_83_SW_OBJECT_05_SERVICE_TABLE_NUM,   &Crypto_83_sw_stObjectRam[CRYPTO_83_SW_OBJECT_05_RAM],   &Crypto_83_sw_stObjectRamRed[CRYPTO_83_SW_OBJECT_05_RAM]},
    {&Crypto_83_sw_stObject06ServiceTable[0],   CRYPTO_83_SW_OBJECT_06_SERVICE_TABLE_NUM,   &Crypto_83_sw_stObjectRam[CRYPTO_83_SW_OBJECT_06_RAM],   &Crypto_83_sw_stObjectRamRed[CRYPTO_83_SW_OBJECT_06_RAM]},
    {&Crypto_83_sw_stObject07ServiceTable[0],   CRYPTO_83_SW_OBJECT_07_SERVICE_TABLE_NUM,   &Crypto_83_sw_stObjectRam[CRYPTO_83_SW_OBJECT_07_RAM],   &Crypto_83_sw_stObjectRamRed[CRYPTO_83_SW_OBJECT_07_RAM]},
    {&Crypto_83_sw_stObject08ServiceTable[0],   CRYPTO_83_SW_OBJECT_08_SERVICE_TABLE_NUM,   &Crypto_83_sw_stObjectRam[CRYPTO_83_SW_OBJECT_08_RAM],   &Crypto_83_sw_stObjectRamRed[CRYPTO_83_SW_OBJECT_08_RAM]}
#else
    {&Crypto_83_sw_stObject00ServiceTable[0],   CRYPTO_83_SW_OBJECT_00_SERVICE_TABLE_NUM,   &Crypto_83_sw_stObjectRam[CRYPTO_83_SW_OBJECT_00_RAM]},
    {&Crypto_83_sw_stObject01ServiceTable[0],   CRYPTO_83_SW_OBJECT_01_SERVICE_TABLE_NUM,   &Crypto_83_sw_stObjectRam[CRYPTO_83_SW_OBJECT_01_RAM]},
    {&Crypto_83_sw_stObject02ServiceTable[0],   CRYPTO_83_SW_OBJECT_02_SERVICE_TABLE_NUM,   &Crypto_83_sw_stObjectRam[CRYPTO_83_SW_OBJECT_02_RAM]},
    {&Crypto_83_sw_stObject03ServiceTable[0],   CRYPTO_83_SW_OBJECT_03_SERVICE_TABLE_NUM,   &Crypto_83_sw_stObjectRam[CRYPTO_83_SW_OBJECT_03_RAM]},
    {&Crypto_83_sw_stObject04ServiceTable[0],   CRYPTO_83_SW_OBJECT_04_SERVICE_TABLE_NUM,   &Crypto_83_sw_stObjectRam[CRYPTO_83_SW_OBJECT_04_RAM]},
    {&Crypto_83_sw_stObject05ServiceTable[0],   CRYPTO_83_SW_OBJECT_05_SERVICE_TABLE_NUM,   &Crypto_83_sw_stObjectRam[CRYPTO_83_SW_OBJECT_05_RAM]},
    {&Crypto_83_sw_stObject06ServiceTable[0],   CRYPTO_83_SW_OBJECT_06_SERVICE_TABLE_NUM,   &Crypto_83_sw_stObjectRam[CRYPTO_83_SW_OBJECT_06_RAM]},
    {&Crypto_83_sw_stObject07ServiceTable[0],   CRYPTO_83_SW_OBJECT_07_SERVICE_TABLE_NUM,   &Crypto_83_sw_stObjectRam[CRYPTO_83_SW_OBJECT_07_RAM]},
    {&Crypto_83_sw_stObject08ServiceTable[0],   CRYPTO_83_SW_OBJECT_08_SERVICE_TABLE_NUM,   &Crypto_83_sw_stObjectRam[CRYPTO_83_SW_OBJECT_08_RAM]}
#endif
};

#define CRYPTO_83_sw_STOP_SEC_CONST
#include <Crypto_83_sw_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define CRYPTO_83_sw_START_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

/****************************************************************************/
/* Function Name | Crypto_83_sw_Init                                        */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | configPtr :                                              */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_Init
(
    P2CONST(Crypto_83_sw_ConfigType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) configPtr
)
{
    uint8    u1_ObjectNum;

    Crypto_83_sw_If_SwsheInit();
    Crypto_83_sw_If_RsaInit();

    for( u1_ObjectNum = (uint8)0U; u1_ObjectNum < CRYPTO_83_SW_OBJECT_NUM; u1_ObjectNum++ )
    {
        Crypto_83_sw_stObjectTable[u1_ObjectNum].ptObjectRam->u4JobId = (uint32)0UL;
        Crypto_83_sw_stObjectTable[u1_ObjectNum].ptObjectRam->ptJob = NULL_PTR;
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
        Crypto_83_sw_stObjectTable[u1_ObjectNum].ptObjectRamRed->u4JobIdRed = CRYPTO_83_SW_RED_INIT_U4;
        Crypto_83_sw_stObjectTable[u1_ObjectNum].ptObjectRamRed->u4JobRed = CRYPTO_83_SW_RED_INIT_U4;
        Crypto_83_sw_stObjectTable[u1_ObjectNum].ptObjectRamRed->u4Job_JobInfoRed = CRYPTO_83_SW_RED_INIT_U4;
#endif
        Crypto_83_sw_stObjectTable[u1_ObjectNum].ptObjectRam->udResult = (Crypto_ResultType)E_NOT_OK;
        Crypto_83_sw_stObjectTable[u1_ObjectNum].ptObjectRam->u1ServiceIndex = (uint8)0U;
        Crypto_83_sw_stObjectTable[u1_ObjectNum].ptObjectRam->udCryptoDriverObjectStatus = CRYPTO_83_SW_S_CDO_IDLE;
        Crypto_83_sw_stObjectTable[u1_ObjectNum].ptObjectRam->udCallBackStatus = CRYPTO_83_SW_S_CDO_CB_NONE;
    }

    Crypto_83_sw_udDriverStatus = CRYPTO_83_SW_S_CD_INIT;

    return;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_GetVersionInfo                              */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | versioninfo :                                            */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) versioninfo
)
{
    boolean b_VersionInfoApi = Crypto_83_sw_Cfg_bVersionInfoApi;

    if( b_VersionInfoApi == (boolean)TRUE )
    {
        if( versioninfo != NULL_PTR )
        {
            versioninfo->vendorID = (uint16)CRYPTO_83_SW_VENDOR_ID;
            versioninfo->moduleID = (uint16)CRYPTO_83_SW_MODULE_ID;
            versioninfo->sw_major_version = (uint8)CRYPTO_83_SW_SW_MAJOR_VERSION;
            versioninfo->sw_minor_version = (uint8)CRYPTO_83_SW_SW_MINOR_VERSION;
            versioninfo->sw_patch_version = (uint8)CRYPTO_83_SW_SW_PATCH_VERSION;
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_ProcessJob                                  */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | objectId :                                               */
/*               | job      :                                               */
/* Return Value  | Std_Return_Type                                          */
/*               |  E_OK                        :                           */
/*               |  E_NOT_OK                    :                           */
/*               |  CRYPTO_E_BUSY               :                           */
/*               |  CRYPTO_E_KEY_NOT_VALID      :                           */
/*               |  CRYPTO_E_ENTROPY_EXHAUSTED  :                           */
/*               |  CRYPTO_E_KEY_EMPTY          :                           */
/*               |  CSM_AB_E_SHE_KEY_INVALID    :                           */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE :                           */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR  :                           */
/*               |  CSM_AB_E_SHE_RNG_SEED       :                           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_ProcessJob
(
    uint32 objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) job
)
{
    Std_ReturnType           ud_Ret;
    Crypto_OperationModeType ud_Mode;

    if( ( Crypto_83_sw_udDriverStatus == CRYPTO_83_SW_S_CD_INIT )
     && ( objectId < CRYPTO_83_SW_OBJECT_NUM ) )
    {
        if( Crypto_83_sw_stObjectTable[objectId].ptObjectRam->udCallBackStatus == CRYPTO_83_SW_S_CDO_CB_NONE )
        {
            if( ( job != NULL_PTR )
             && ( job->jobPrimitiveInfo != NULL_PTR )
             && ( job->jobPrimitiveInfo->primitiveInfo != NULL_PTR ) )
            {
                ud_Ret = Crypto_83_sw_SearchServiceTable( &Crypto_83_sw_stObjectTable[objectId], (const Crypto_JobType *)job );
            }
            else
            {
                ud_Ret = (Std_ReturnType)E_NOT_OK;
            }
        }
        else
        {
            ud_Ret = (Std_ReturnType)CRYPTO_E_BUSY;
        }
    }
    else
    {
        ud_Ret = (Std_ReturnType)E_NOT_OK;
    }

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        Crypto_83_sw_stObjectTable[objectId].ptObjectRam->ptJob = job;
        
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
        Crypto_83_sw_stObjectTable[objectId].ptObjectRamRed->u4JobRed = ~(uint32)job;                   /* MISRA DEVIATION */
        Crypto_83_sw_stObjectTable[objectId].ptObjectRamRed->u4Job_JobInfoRed = ~(uint32)job->jobInfo;  /* MISRA DEVIATION */
#endif
        
        ud_Mode = Crypto_83_sw_stObjectTable[objectId].ptObjectRam->ptJob->jobPrimitiveInputOutput.mode;

        if( Crypto_83_sw_stObjectTable[objectId].ptServiceTable->udSaScSelect == CRYPTO_83_SW_SA_SELECT )
        {
            if( ( ud_Mode & CRYPTO_OPERATIONMODE_START ) == CRYPTO_OPERATIONMODE_START )
            {
                ud_Ret = Crypto_83_sw_SA_Start_ProcessJob( &Crypto_83_sw_stObjectTable[objectId] );
            }
            if( ( ( ud_Mode & CRYPTO_OPERATIONMODE_UPDATE ) == CRYPTO_OPERATIONMODE_UPDATE )
             && ( ud_Ret == (Std_ReturnType)E_OK ) )
            {
                ud_Ret = Crypto_83_sw_SA_Update_ProcessJob( &Crypto_83_sw_stObjectTable[objectId] );
            }
            if( ( ( ud_Mode & CRYPTO_OPERATIONMODE_FINISH ) == CRYPTO_OPERATIONMODE_FINISH )
             && ( ud_Ret == (Std_ReturnType)E_OK ) )
            {
                ud_Ret = Crypto_83_sw_SA_Finish_ProcessJob( &Crypto_83_sw_stObjectTable[objectId] );
            }
            if( ( ( ud_Mode & CRYPTO_OPERATIONMODE_START ) != CRYPTO_OPERATIONMODE_START )
             && ( ( ud_Mode & CRYPTO_OPERATIONMODE_UPDATE ) != CRYPTO_OPERATIONMODE_UPDATE )
             && ( ( ud_Mode & CRYPTO_OPERATIONMODE_FINISH ) != CRYPTO_OPERATIONMODE_FINISH ) )
            {
                ud_Ret = (Std_ReturnType)E_NOT_OK;
            }
        }
        else
        {
            if( ( ud_Mode & CRYPTO_OPERATIONMODE_SINGLECALL ) == CRYPTO_OPERATIONMODE_SINGLECALL )
            {
                ud_Ret = Crypto_83_sw_SC_ProcessJob( &Crypto_83_sw_stObjectTable[objectId] );
            }
            else
            {
                ud_Ret = (Std_ReturnType)E_NOT_OK;
            }
        }
    }

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        if( Crypto_83_sw_stObjectTable[objectId].ptObjectRam->ptJob->jobPrimitiveInfo->processingType == CRYPTO_PROCESSING_ASYNC )
        {
            Crypto_83_sw_stObjectTable[objectId].ptObjectRam->udResult = (Crypto_ResultType)ud_Ret;
            Crypto_83_sw_stObjectTable[objectId].ptObjectRam->udCallBackStatus = CRYPTO_83_SW_S_CDO_CB_WAIT;
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_CancelJob                                   */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | objectId :                                               */
/*               | job      :                                               */
/* Return Value  | Std_Return_Type                                          */
/*               |  E_NOT_OK :                                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_CancelJob
(
    uint32 objectId,
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) job
)
{
    return (Std_ReturnType)E_NOT_OK;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_Ab_MainFunctionIn                           */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_Ab_MainFunctionIn
(
    void
)
{
    return;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_Ab_MainFunctionOut                          */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_Ab_MainFunctionOut
(
    void
)
{
    uint8   u1_ObjectNum;
    Crypto_83_sw_CallBackStatusType ud_callBackStatus;
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) pt_job;
    Crypto_ResultType ud_Ret;

    if( Crypto_83_sw_udDriverStatus == CRYPTO_83_SW_S_CD_INIT )
    {
        for( u1_ObjectNum = (uint8)0U; u1_ObjectNum < CRYPTO_83_SW_OBJECT_NUM; u1_ObjectNum++ )
        {
            ud_callBackStatus = Crypto_83_sw_stObjectTable[u1_ObjectNum].ptObjectRam->udCallBackStatus;
            if( ud_callBackStatus == CRYPTO_83_SW_S_CDO_CB_WAIT )
            {
                pt_job = Crypto_83_sw_stObjectTable[u1_ObjectNum].ptObjectRam->ptJob;
                ud_Ret = Crypto_83_sw_stObjectTable[u1_ObjectNum].ptObjectRam->udResult;
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
                if( ( (uint32)pt_job == ~Crypto_83_sw_stObjectTable[u1_ObjectNum].ptObjectRamRed->u4JobRed )                        /* MISRA DEVIATION */
                  && ( (uint32)pt_job->jobInfo == ~Crypto_83_sw_stObjectTable[u1_ObjectNum].ptObjectRamRed->u4Job_JobInfoRed ) )    /* MISRA DEVIATION */
                {
#endif
                    Crypto_83_sw_stObjectTable[u1_ObjectNum].ptObjectRam->udCallBackStatus = CRYPTO_83_SW_S_CDO_CB_NONE;
                    CryIf_CallbackNotification( pt_job,
                                                ud_Ret );
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
                }
                else
                {
                    Crypto_83_sw_udDriverStatus = CRYPTO_83_SW_S_CD_FAULT;
                }
#endif
            }
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
            else if (ud_callBackStatus == CRYPTO_83_SW_S_CDO_CB_NONE)
            {
                ; /* No Processing */
            }
            else
            {
                Crypto_83_sw_udDriverStatus = CRYPTO_83_SW_S_CD_FAULT;
            }
#endif
        }
    }
    Crypto_83_sw_DetectError();

    return;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_Ab_GetErrorStatus                           */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | ptErrorStatus :                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     :                                              */
/*               |  E_NOT_OK :                                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_Ab_GetErrorStatus
(
    P2VAR(Crypto_83_sw_Ab_ErrorStatusType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptErrorStatus
)
{
    Std_ReturnType ud_Ret = (Std_ReturnType)E_NOT_OK;
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
    Std_ReturnType ud_SWSHERet;
#endif
    Crypto_83_sw_DriverStatusType ud_Status;

    if( ptErrorStatus != NULL_PTR )
    {
        ud_Ret = (Std_ReturnType)E_OK;
        ud_Status = Crypto_83_sw_udDriverStatus;

        if( ud_Status == CRYPTO_83_SW_S_CD_INIT )
        {
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
            ud_SWSHERet = Crypto_83_sw_SWSHE_GetErrorStatus();
            
            if( ud_SWSHERet == (Std_ReturnType)E_OK )
            {
                *ptErrorStatus = CRYPTO_83_SW_AB_E_NONE;
            }
            else
            {
                *ptErrorStatus = CRYPTO_83_SW_AB_E_RAM_CHECK_FAIL;
            }
#else
            *ptErrorStatus = CRYPTO_83_SW_AB_E_NONE;
#endif
        }
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
        else if( ud_Status == CRYPTO_83_SW_S_CD_UNINIT )
        {
            *ptErrorStatus = CRYPTO_83_SW_AB_E_NOT_INITIALIZED;
        }
        else
        {
            *ptErrorStatus = CRYPTO_83_SW_AB_E_RAM_CHECK_FAIL;
        }
#else
        else
        {
            *ptErrorStatus = CRYPTO_83_SW_AB_E_NOT_INITIALIZED;
        }
#endif
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_GetStatus                                   */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | Crypto_83_sw_DriverStatusType                            */
/*               |  CRYPTO_83_SW_S_CD_UNINIT  :                             */
/*               |  CRYPTO_83_SW_S_CD_INIT    :                             */
/*               |  CRYPTO_83_SW_S_CD_FAULT   :                             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Crypto_83_sw_DriverStatusType, CRYPTO_83_sw_CODE) Crypto_83_sw_GetStatus
(
    void
)
{
    Crypto_83_sw_DriverStatusType   ud_Ret;

    ud_Ret = Crypto_83_sw_udDriverStatus;

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_IntervalCallout                             */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_IntervalCallout
(
    void
)
{
    CONST(Crypto_83_sw_IntervalCalloutType, AUTOMATIC) pt_IntervalCalloutFunc = Crypto_83_sw_Cfg_ptIntervalCalloutFunc;

    if( pt_IntervalCalloutFunc != NULL_PTR )
    {
        pt_IntervalCalloutFunc();
    }

    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Crypto_83_sw_SearchServiceTable                          */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | ptObjectTable :                                          */
/*               | ptJob         :                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK     :                                              */
/*               |  E_NOT_OK :                                              */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SearchServiceTable
(
    P2CONST(AB_83_ConstV Crypto_83_sw_ObjectTableType, AUTOMATIC, CRYPTO_83_sw_CONST) ptObjectTable,
    P2CONST(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) ptJob
)
{
    Std_ReturnType  ud_Ret = (Std_ReturnType)E_NOT_OK;
    uint8           u1_ServiceTableIndex;

    for( u1_ServiceTableIndex = (uint8)0U; u1_ServiceTableIndex < ptObjectTable->u4ServiceNum; u1_ServiceTableIndex++ )
    {
        if( ( ptJob->jobPrimitiveInfo->primitiveInfo->service == ptObjectTable->ptServiceTable[u1_ServiceTableIndex].udService )
         && ( ptJob->jobPrimitiveInfo->primitiveInfo->algorithm.mode == ptObjectTable->ptServiceTable[u1_ServiceTableIndex].udMode )
         && ( ptJob->jobPrimitiveInfo->primitiveInfo->algorithm.family == ptObjectTable->ptServiceTable[u1_ServiceTableIndex].udFamily ) )
        {
            ptObjectTable->ptObjectRam->u1ServiceIndex = u1_ServiceTableIndex;
            ud_Ret = (Std_ReturnType)E_OK;
            break;
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SA_Start_ProcessJob                         */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | ptObjectTable :                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                   :                                */
/*               |  E_NOT_OK               :                                */
/*               |  CRYPTO_E_BUSY          :                                */
/*               |  CRYPTO_E_KEY_NOT_VALID :                                */
/*               |  CRYPTO_E_EMPTY         :                                */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SA_Start_ProcessJob
(
    P2CONST(AB_83_ConstV Crypto_83_sw_ObjectTableType, AUTOMATIC, CRYPTO_83_sw_CONST) ptObjectTable
)
{
    Std_ReturnType                ud_Ret = (Std_ReturnType)E_OK;
    Crypto_83_sw_ObjectStatusType ud_Status;
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) pt_job;

    ud_Status = ptObjectTable->ptObjectRam->udCryptoDriverObjectStatus;
    pt_job = ptObjectTable->ptObjectRam->ptJob;

    if( ud_Status == CRYPTO_83_SW_S_CDO_IDLE )
    {
        ; /* No Processing */
    }
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
    else if( ( ud_Status == CRYPTO_83_SW_S_CDO_ACTIVE )
          || ( ud_Status == CRYPTO_83_SW_S_CDO_UPDATED ) )
    {
        if( ptObjectTable->ptObjectRam->u4JobId == ~(uint32)ptObjectTable->ptObjectRamRed->u4JobIdRed )
        {
            if( ptObjectTable->ptObjectRam->u4JobId != pt_job->jobId )
            {
                ud_Ret = (Std_ReturnType)CRYPTO_E_BUSY;
            }
        }
        else
        {
            Crypto_83_sw_udDriverStatus = CRYPTO_83_SW_S_CD_FAULT;
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }
    }
    else
    {
        Crypto_83_sw_udDriverStatus = CRYPTO_83_SW_S_CD_FAULT;
        ud_Ret = (Std_ReturnType)E_NOT_OK;
    }
#else
    else
    {
        if( ptObjectTable->ptObjectRam->u4JobId != pt_job->jobId )
        {
            ud_Ret = (Std_ReturnType)CRYPTO_E_BUSY;
        }
    }
#endif

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        ptObjectTable->ptObjectRam->udCryptoDriverObjectStatus = CRYPTO_83_SW_S_CDO_ACTIVE;
        pt_job->jobState = CRYPTO_JOBSTATE_ACTIVE;
        ptObjectTable->ptObjectRam->u4JobId = pt_job->jobId;
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
        ptObjectTable->ptObjectRamRed->u4JobIdRed = ~(uint32)pt_job->jobId;
#endif

        ud_Ret = ptObjectTable->ptServiceTable[ptObjectTable->ptObjectRam->u1ServiceIndex].ptStartFunc( (const Crypto_JobType*)pt_job );

        if( ud_Ret != (Std_ReturnType)E_OK )
        {
            ptObjectTable->ptObjectRam->udCryptoDriverObjectStatus = CRYPTO_83_SW_S_CDO_IDLE;
            pt_job->jobState = CRYPTO_JOBSTATE_IDLE;
        }
    }


    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SA_Update_ProcessJob                        */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | ptObjectTable :                                          */
/*               | ptJob         :                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                        :                           */
/*               |  E_NOT_OK                    :                           */
/*               |  CRYPTO_E_BUSY               :                           */
/*               |  CRYPTO_E_KEY_NOT_VALID      :                           */
/*               |  CRYPTO_E_EMPTY              :                           */
/*               |  CSM_AB_E_SHE_KEY_INVALID    :                           */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE :                           */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR  :                           */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SA_Update_ProcessJob
(
    P2CONST(AB_83_ConstV Crypto_83_sw_ObjectTableType, AUTOMATIC, CRYPTO_83_sw_CONST) ptObjectTable
)
{
    Std_ReturnType                ud_Ret = (Std_ReturnType)E_OK;
    Crypto_83_sw_ObjectStatusType ud_Status;
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) pt_job;

    ud_Status = ptObjectTable->ptObjectRam->udCryptoDriverObjectStatus;
    pt_job = ptObjectTable->ptObjectRam->ptJob;

    if( ud_Status == CRYPTO_83_SW_S_CDO_IDLE )
    {
        ud_Ret = (Std_ReturnType)E_NOT_OK;
    }
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
    else if( ( ud_Status == CRYPTO_83_SW_S_CDO_ACTIVE )
     || ( ud_Status == CRYPTO_83_SW_S_CDO_UPDATED ) )
    {
        if( ptObjectTable->ptObjectRam->u4JobId == ~(uint32)ptObjectTable->ptObjectRamRed->u4JobIdRed )
        {
            if( ptObjectTable->ptObjectRam->u4JobId != pt_job->jobId )
            {
                ud_Ret = (Std_ReturnType)E_NOT_OK;
            }
        }
        else
        {
            Crypto_83_sw_udDriverStatus = CRYPTO_83_SW_S_CD_FAULT;
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }
    }
    else
    {
        Crypto_83_sw_udDriverStatus = CRYPTO_83_SW_S_CD_FAULT;
        ud_Ret = (Std_ReturnType)E_NOT_OK;
    }
#else
    else
    {
        if( ptObjectTable->ptObjectRam->u4JobId != pt_job->jobId )
        {
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }
    }
#endif

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        ptObjectTable->ptObjectRam->udCryptoDriverObjectStatus = CRYPTO_83_SW_S_CDO_UPDATED;
        pt_job->jobState = CRYPTO_JOBSTATE_ACTIVE;

        ud_Ret = ptObjectTable->ptServiceTable[ptObjectTable->ptObjectRam->u1ServiceIndex].ptUpdateFunc( (const Crypto_JobType*)pt_job );

        if( ud_Ret != (Std_ReturnType)E_OK )
        {
            ptObjectTable->ptObjectRam->udCryptoDriverObjectStatus = CRYPTO_83_SW_S_CDO_IDLE;
            pt_job->jobState = CRYPTO_JOBSTATE_IDLE;
        }
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SA_Finish_ProcessJob                        */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | ptObjectTable :                                          */
/*               | ptJob         :                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                        :                           */
/*               |  E_NOT_OK                    :                           */
/*               |  CRYPTO_E_BUSY               :                           */
/*               |  CRYPTO_E_KEY_NOT_VALID      :                           */
/*               |  CRYPTO_E_EMPTY              :                           */
/*               |  CSM_AB_E_SHE_KEY_INVALID    :                           */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE :                           */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR  :                           */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SA_Finish_ProcessJob
(
    P2CONST(AB_83_ConstV Crypto_83_sw_ObjectTableType, AUTOMATIC, CRYPTO_83_sw_CONST) ptObjectTable
)
{
    Std_ReturnType                ud_Ret = (Std_ReturnType)E_OK;
    Crypto_83_sw_ObjectStatusType ud_Status;
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) pt_job;

    ud_Status = ptObjectTable->ptObjectRam->udCryptoDriverObjectStatus;
    pt_job = ptObjectTable->ptObjectRam->ptJob;

    if( ud_Status == CRYPTO_83_SW_S_CDO_IDLE )
    {
        ud_Ret = (Std_ReturnType)E_NOT_OK;
    }
    else if( ud_Status == CRYPTO_83_SW_S_CDO_ACTIVE )
    {
        ud_Ret = (Std_ReturnType)E_NOT_OK;
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
        if( ptObjectTable->ptObjectRam->u4JobId == ~(uint32)ptObjectTable->ptObjectRamRed->u4JobIdRed )
        {
#endif
            if( ptObjectTable->ptObjectRam->u4JobId == pt_job->jobId )
            {
                ptObjectTable->ptObjectRam->udCryptoDriverObjectStatus = CRYPTO_83_SW_S_CDO_IDLE;
                pt_job->jobState = CRYPTO_JOBSTATE_IDLE;
            }
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
        }
        else
        {
            Crypto_83_sw_udDriverStatus = CRYPTO_83_SW_S_CD_FAULT;
        }
#endif
    }
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
    else if( ud_Status == CRYPTO_83_SW_S_CDO_UPDATED )
    {
        if( ptObjectTable->ptObjectRam->u4JobId == ~(uint32)ptObjectTable->ptObjectRamRed->u4JobIdRed )
        {
            if( ptObjectTable->ptObjectRam->u4JobId != pt_job->jobId )
            {
                ud_Ret = (Std_ReturnType)E_NOT_OK;
            }
        }
        else
        {
            Crypto_83_sw_udDriverStatus = CRYPTO_83_SW_S_CD_FAULT;
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }
    }
    else
    {
        Crypto_83_sw_udDriverStatus = CRYPTO_83_SW_S_CD_FAULT;
        ud_Ret = (Std_ReturnType)E_NOT_OK;
    }
#else
    else
    {
        if( ptObjectTable->ptObjectRam->u4JobId != pt_job->jobId )
        {
            ud_Ret = (Std_ReturnType)E_NOT_OK;
        }
    }
#endif

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        ud_Ret = ptObjectTable->ptServiceTable[ptObjectTable->ptObjectRam->u1ServiceIndex].ptFinishFunc( (const Crypto_JobType*)pt_job );

        ptObjectTable->ptObjectRam->udCryptoDriverObjectStatus = CRYPTO_83_SW_S_CDO_IDLE;
        pt_job->jobState = CRYPTO_JOBSTATE_IDLE;
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_SC_ProcessJob                               */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | ptObjectTable :                                          */
/*               | ptJob         :                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                        :                           */
/*               |  E_NOT_OK                    :                           */
/*               |  CRYPTO_E_BUSY               :                           */
/*               |  CRYPTO_E_ENTROPY_EXHAUSTED  :                           */
/*               |  CRYPTO_E_KEY_NOT_VALID      :                           */
/*               |  CRYPTO_E_EMPTY              :                           */
/*               |  CSM_AB_E_SHE_KEY_INVALID    :                           */
/*               |  CSM_AB_E_SHE_RNG_SEED       :                           */
/*               |  CSM_AB_E_SHE_MEMORY_FAILURE :                           */
/*               |  CSM_AB_E_SHE_GENERAL_ERROR  :                           */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(Std_ReturnType, CRYPTO_83_sw_CODE) Crypto_83_sw_SC_ProcessJob
(
    P2CONST(AB_83_ConstV Crypto_83_sw_ObjectTableType, AUTOMATIC, CRYPTO_83_sw_CONST) ptObjectTable
)
{
    Std_ReturnType  ud_Ret = (Std_ReturnType)E_OK;
    Crypto_83_sw_ObjectStatusType ud_Status;
    P2VAR(Crypto_JobType, AUTOMATIC, CRYPTO_83_sw_APPL_DATA) pt_job;

    ud_Status = ptObjectTable->ptObjectRam->udCryptoDriverObjectStatus;
    pt_job = ptObjectTable->ptObjectRam->ptJob;

    if( ud_Status == CRYPTO_83_SW_S_CDO_IDLE )
    {
        ; /* No Processing */
    }
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
    else if( ( ud_Status == CRYPTO_83_SW_S_CDO_ACTIVE )
          || ( ud_Status == CRYPTO_83_SW_S_CDO_UPDATED ) )
    {
        ud_Ret = (Std_ReturnType)CRYPTO_E_BUSY;
    }
    else
    {
        Crypto_83_sw_udDriverStatus = CRYPTO_83_SW_S_CD_FAULT;
        ud_Ret = (Std_ReturnType)E_NOT_OK;
    }
#else
    else
    {
        ud_Ret = (Std_ReturnType)CRYPTO_E_BUSY;
    }
#endif

    if( ud_Ret == (Std_ReturnType)E_OK )
    {
        ptObjectTable->ptObjectRam->u4JobId = pt_job->jobId;
#if (CRYPTO_83_SW_RAM_ERROR_CHECK == STD_ON)
        ptObjectTable->ptObjectRamRed->u4JobIdRed = ~(uint32)pt_job->jobId;
#endif

        ud_Ret = ptObjectTable->ptServiceTable[ptObjectTable->ptObjectRam->u1ServiceIndex].ptSingleCallFunc( (const Crypto_JobType*)pt_job );

        pt_job->jobState = CRYPTO_JOBSTATE_IDLE;
    }

    return ud_Ret;
}

/****************************************************************************/
/* Function Name | Crypto_83_sw_DetectError                                 */
/* Description   | -                                                        */
/* Preconditions | -                                                        */
/* Parameters    | -                                                        */
/* Return Value  | -                                                        */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, CRYPTO_83_sw_CODE) Crypto_83_sw_DetectError
(
    void
)
{
    P2CONST(AB_83_ConstV Crypto_83_sw_ErrorCalloutType, AUTOMATIC, CRYPTO_83_sw_CONFIG_DATA)   pt_errorCalloutConfig = Crypto_83_sw_Cfg_stErrorCallout.ptConfig;
    Crypto_83_sw_Ab_ErrorStatusType  ud_errorStatus;
    uint16                           u2_loop;

    (void)Crypto_83_sw_Ab_GetErrorStatus( &ud_errorStatus ); /* no return check required */
    if( ud_errorStatus != CRYPTO_83_SW_AB_E_NONE )
    {
        for( u2_loop = 0U; u2_loop < (uint16)Crypto_83_sw_Cfg_stErrorCallout.u4ConfigNum; u2_loop++ )
        {
            if( pt_errorCalloutConfig[u2_loop] != NULL_PTR )
            {
                pt_errorCalloutConfig[u2_loop]( ud_errorStatus );
            }
        }
    }

    return;
}

#define CRYPTO_83_sw_STOP_SEC_CODE
#include <Crypto_83_sw_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2023/01/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
