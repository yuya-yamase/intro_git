/* RpgLib_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | RpgLib/CODE                                                 */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <Rte.h>

#include <RpgLib.h>
#include "RpgLib_Local.h"
#include "RpgLib_Cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define RPGLIB_STAT_IDLE                ((uint8)0x00U)
#define RPGLIB_STAT_CHANGE_BAUDRATE     ((uint8)0x01U)
#define RPGLIB_STAT_APL_INVALID         ((uint8)0x02U)
#define RPGLIB_STAT_APL_VALID           ((uint8)0x03U)
#define RPGLIB_STAT_MEM_ERASE           ((uint8)0x04U)
#define RPGLIB_STAT_MEM_READ            ((uint8)0x05U)
#define RPGLIB_STAT_MEM_WRITE_PRE       ((uint8)0x06U)
#define RPGLIB_STAT_MEM_WRITE           ((uint8)0x07U)
#define RPGLIB_STAT_MEM_WRITE_FINISH    ((uint8)0x08U)

#define RPGLIB_E_PENDING                ((Std_ReturnType)0x02U)
#define RPGLIB_E_UPDATEIDLE             ((Std_ReturnType)0x03U)
#define RPGLIB_E_UPDATECOMPLETE         ((Std_ReturnType)0x04U)

#if 0   /* Nbr1503(CtrlFrame) */
#define RPGLIB_CTRLFRAME_INFO_MAX       ((uint8)8U)
#define RPGLIB_CTRLFRAME_INVALID_PDUID  ((PduIdType)0xFFFFU)
#endif

#define RPGLIB_STATUSMATRIXTBL_NUM      (sizeof(RpgLib_StatusMatrixTbl) / sizeof(RpgLib_StatusMatrixTbl[0]))


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint8 LocalStatus;
    uint8 RetStatus;
} RpgLib_StatusMatrixType;

typedef struct {
    uint8 LocalStatus;
    uint8 JobResult;
} RpgLib_JobInfoType;

#if 0   /* Nbr1503(CtrlFrame) */
typedef struct {
    PduIdType PduId;
    uint16 Reserved;
    RpgLib_CtrlFrameTxCallbackType TxCallback;
    RpgLib_CtrlFrameRxCallbackType RxCallback;
} RpgLib_CtrlFrameCallbackInfoType;
#endif

typedef struct {
    uint32 Num;
    P2CONST(RpgLib_StatusMatrixType, TYPEDEF, RPGLIB_APPL_CONST) MatrixPtr;
} RpgLib_StatusMatrixInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, RPGLIB_CODE_FAST) RpgLib_Main_InvalidApl (void);
static FUNC(void, RPGLIB_CODE_FAST) RpgLib_Main_ValidApl (void);
static FUNC(void, RPGLIB_CODE_FAST) RpgLib_Main_ReqErase (void);
static FUNC(void, RPGLIB_CODE_FAST) RpgLib_Main_ReqMemRead (void);
static FUNC(void, RPGLIB_CODE_FAST) RpgLib_Main_ReqWriteMemUpdate (void);
static FUNC(Std_ReturnType, RPGLIB_CODE_FAST) RpgLib_CheckMemMCondition (void);
static FUNC(Std_ReturnType, RPGLIB_CODE_FAST) RpgLib_CheckMemMUpdateCondition (void);
static FUNC(void, RPGLIB_CODE_FAST) RpgLib_UpdateJobInfo
(
    VAR(uint8, AUTOMATIC) JobResult,
    VAR(uint8, AUTOMATIC) LocalStatus
);
static FUNC(Std_ReturnType, RPGLIB_CODE_FAST) RpgLib_GetApiAcceptation (void);
static FUNC(void, RPGLIB_CODE_FAST) RpgLib_ReleaseApiAcceptation (void);
#if 0   /* Nbr1503(CtrlFrame) */
static FUNC(Std_ReturnType, RPGLIB_CODE_FAST) RpgLib_CtrlFrameRegistCallback
(
    VAR(PduIdType, AUTOMATIC) PduId,
    VAR(RpgLib_CtrlFrameTxCallbackType, AUTOMATIC) TxCallback,
    VAR(RpgLib_CtrlFrameRxCallbackType, AUTOMATIC) RxCallback
);
#endif


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define RPGLIB_START_SEC_VAR
#include <RpgLib_MemMap.h>

#if 0   /* Nbr1503(CtrlFrame) */
static VAR(RpgLib_CtrlFrameCallbackInfoType, RPGLIB_VAR_CLEARED) RpgLib_CtrlFrameCallbackInfo[RPGLIB_CTRLFRAME_INFO_MAX];
#endif
static VAR(RpgLib_JobInfoType, RPGLIB_VAR_CLEARED) RpgLib_JobInfo;
static VAR(uint8, RPGLIB_VAR_CLEARED) RpgLib_EraseAplFlg;
static VAR(uint8, RPGLIB_VAR_CLEARED) RpgLib_ApiAcceptingFlg;

#define RPGLIB_STOP_SEC_VAR
#include <RpgLib_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define RPGLIB_START_SEC_CST
#include <RpgLib_MemMap.h>

static CONST(RpgLib_StatusMatrixType, RPGLIB_CONST) RpgLib_StatusMatrixTbl[] = {
     { RPGLIB_STAT_IDLE,             RPGLIB_IDLE           }
    ,{ RPGLIB_STAT_CHANGE_BAUDRATE,  RPGLIB_BUSY           }
    ,{ RPGLIB_STAT_APL_INVALID,      RPGLIB_BUSY           }
    ,{ RPGLIB_STAT_APL_VALID,        RPGLIB_BUSY           }
    ,{ RPGLIB_STAT_MEM_ERASE,        RPGLIB_BUSY           }
    ,{ RPGLIB_STAT_MEM_READ,         RPGLIB_BUSY           }
    ,{ RPGLIB_STAT_MEM_WRITE_PRE,    RPGLIB_UPDATEIDLE     }
    ,{ RPGLIB_STAT_MEM_WRITE,        RPGLIB_UPDATEBUSY     }
    ,{ RPGLIB_STAT_MEM_WRITE_FINISH, RPGLIB_UPDATECOMPLETE }
};
static CONST(AB_83_ConstV RpgLib_StatusMatrixInfoType, RPGLIB_CONST) RpgLib_StatusMatrixInfo = {
    RPGLIB_STATUSMATRIXTBL_NUM,
    &RpgLib_StatusMatrixTbl[0]
};

#define RPGLIB_STOP_SEC_CST
#include <RpgLib_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define RPGLIB_START_SEC_CODE
#include <RpgLib_MemMap.h>

/******************************************************************************/
/* Function Name | RpgLib_Init                                                */
/* Description   | Initializes RpgLib                                         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGLIB_CODE_SLOW) RpgLib_Init (void)
{
#if 0   /* Nbr1503(CtrlFrame) */
    VAR(uint8, AUTOMATIC) i;

    for( i = 0U; i < RPGLIB_CTRLFRAME_INFO_MAX; i++ )
    {
        RpgLib_CtrlFrameCallbackInfo[i].PduId = RPGLIB_CTRLFRAME_INVALID_PDUID;
        RpgLib_CtrlFrameCallbackInfo[i].TxCallback = NULL_PTR;
        RpgLib_CtrlFrameCallbackInfo[i].RxCallback = NULL_PTR;
    }
#endif

    RpgLib_EraseAplFlg = STD_OFF;
    RpgLib_ApiAcceptingFlg = STD_OFF;

    RpgLib_JobInfo.JobResult = RPGLIB_JOB_OK;
    RpgLib_JobInfo.LocalStatus = RPGLIB_STAT_IDLE;

    return;
}

/******************************************************************************/
/* Function Name | RpgLib_DeInit                                              */
/* Description   | Deinitializes RpgLib                                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGLIB_CODE_SLOW) RpgLib_DeInit (void)
{
#if 0   /* Nbr1503(CtrlFrame) */
    VAR(uint8, AUTOMATIC) i;
#endif

    RpgLib_JobInfo.LocalStatus = RPGLIB_STAT_IDLE;
    RpgLib_JobInfo.JobResult = RPGLIB_JOB_OK;

    RpgLib_ApiAcceptingFlg = STD_OFF;
    RpgLib_EraseAplFlg = STD_OFF;

#if 0   /* Nbr1503(CtrlFrame) */
    for( i = 0U; i < RPGLIB_CTRLFRAME_INFO_MAX; i++ )
    {
        RpgLib_CtrlFrameCallbackInfo[i].RxCallback = NULL_PTR;
        RpgLib_CtrlFrameCallbackInfo[i].TxCallback = NULL_PTR;
        RpgLib_CtrlFrameCallbackInfo[i].PduId = RPGLIB_CTRLFRAME_INVALID_PDUID;
    }
#endif

    return;
}

/******************************************************************************/
/* Function Name | RpgLib_Time                                                */
/* Description   | TimeFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGLIB_CODE_SLOW) RpgLib_Time (void)
{
    return;
}

/******************************************************************************/
/* Function Name | RpgLib_MainFunction                                        */
/* Description   | MainFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGLIB_CODE_SLOW) RpgLib_MainFunction (void)
{
    if( ( RpgLib_JobInfo.LocalStatus == RPGLIB_STAT_IDLE ) ||
        ( RpgLib_JobInfo.LocalStatus == RPGLIB_STAT_CHANGE_BAUDRATE ) ||
        ( RpgLib_JobInfo.LocalStatus == RPGLIB_STAT_MEM_WRITE_PRE ) ||
        ( RpgLib_JobInfo.LocalStatus == RPGLIB_STAT_MEM_WRITE_FINISH ) )
    {
        /* No process */
    }
    else if( RpgLib_JobInfo.LocalStatus == RPGLIB_STAT_APL_INVALID )
    {
        RpgLib_Main_InvalidApl();
    }
    else if( RpgLib_JobInfo.LocalStatus == RPGLIB_STAT_APL_VALID )
    {
        RpgLib_Main_ValidApl();
    }
    else if( RpgLib_JobInfo.LocalStatus == RPGLIB_STAT_MEM_ERASE )
    {
        RpgLib_Main_ReqErase();
    }
    else if( RpgLib_JobInfo.LocalStatus == RPGLIB_STAT_MEM_READ )
    {
        RpgLib_Main_ReqMemRead();
    }
    else if( RpgLib_JobInfo.LocalStatus == RPGLIB_STAT_MEM_WRITE )
    {
        RpgLib_Main_ReqWriteMemUpdate();
    }
    else
    {
        /* No process */
    }

    return;
}

/******************************************************************************/
/* Function Name | RpgLib_GetStatus                                           */
/* Description   | Acquires status of job                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Status                                                     */
/*               |  RPGLIB_IDLE                                               */
/*               |  RPGLIB_BUSY                                               */
/*               |  RPGLIB_UPDATEIDLE                                         */
/*               |  RPGLIB_UPDATEBUSY                                         */
/*               |  RPGLIB_UPDATECOMPLETE                                     */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, RPGLIB_CODE_SLOW) RpgLib_GetStatus (void)
{
    VAR(uint32, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) Status;

    Status = RPGLIB_BUSY;

    for( i = 0UL; i < RpgLib_StatusMatrixInfo.Num; i++ )
    {
        if( RpgLib_JobInfo.LocalStatus == RpgLib_StatusMatrixInfo.MatrixPtr[i].LocalStatus )
        {
            Status = RpgLib_StatusMatrixInfo.MatrixPtr[i].RetStatus;
            break;
        }
    }

    return Status;
}

/******************************************************************************/
/* Function Name | RpgLib_GetJobResult                                        */
/* Description   | Acquires result of job                                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | JobResult                                                  */
/*               |  RPGLIB_JOB_OK                                             */
/*               |  RPGLIB_JOB_FAILED                                         */
/*               |  RPGLIB_JOB_PENDING                                        */
/*               |  RPGLIB_JOB_MEMERR                                         */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, RPGLIB_CODE_SLOW) RpgLib_GetJobResult (void)
{
    return RpgLib_JobInfo.JobResult;
}

/******************************************************************************/
/* Function Name | RpgLib_ReqInvalidApl                                       */
/* Description   | Requests invalidate apl                                    */
/* Preconditions |                                                            */
/* Parameters    | [IN] MemoryId : Memory Id                                  */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_ReqInvalidApl
(
    VAR(uint32, AUTOMATIC) MemoryId
)
{
    VAR(RpgLib_MemBlockInfoType, AUTOMATIC) BlockInfo;
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Ret = E_NOT_OK;

    FuncRet = RpgLib_GetApiAcceptation();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        if( RpgLib_JobInfo.LocalStatus == RPGLIB_STAT_IDLE )
        {
            if( RpgLib_EraseAplFlg == (uint8)STD_ON )
            {
                RpgLib_UpdateJobInfo(RPGLIB_JOB_OK, RPGLIB_STAT_IDLE);

                Ret = E_OK;
            }
            else
            {
                BlockInfo.BlockTopAddr = 0UL;
                BlockInfo.BlockSize = 0UL;
                FuncRet = RpgLib_GetMemBlockInfo(MemoryId, RpgLib_AplValidityConfig.InfoPtr[0].Address, &BlockInfo);
                if( FuncRet == (Std_ReturnType)E_OK )
                {
                    FuncRet = Rte_MemM_Erase(MemoryId, BlockInfo.BlockTopAddr, BlockInfo.BlockSize);
                    if( FuncRet == (Std_ReturnType)E_OK )
                    {
                        /* As the result of this function is always OK, there is no need to check the return value. */
                        (void)Rte_SchM_Switch_DcmRewriteControl(RTE_SCHM_BSWM_REWRITE_START);

                        RpgLib_UpdateJobInfo(RPGLIB_JOB_PENDING, RPGLIB_STAT_APL_INVALID);

                        Ret = E_OK;
                    }
                    else
                    {
                        RpgLib_UpdateJobInfo(RPGLIB_JOB_OK, RPGLIB_STAT_IDLE);
                    }
                }
                else
                {
                    RpgLib_UpdateJobInfo(RPGLIB_JOB_OK, RPGLIB_STAT_IDLE);
                }
            }
        }

        RpgLib_ReleaseApiAcceptation();
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | RpgLib_ReqValidApl                                         */
/* Description   | Requests validate apl                                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_ReqValidApl (void)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Ret = E_NOT_OK;

    FuncRet = RpgLib_GetApiAcceptation();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        if( RpgLib_JobInfo.LocalStatus == RPGLIB_STAT_IDLE )
        {
            if( RpgLib_EraseAplFlg == (uint8)STD_ON )
            {
                FuncRet = Rte_MemM_ReprogComplete();
                if( FuncRet == (Std_ReturnType)E_OK )
                {
                    RpgLib_UpdateJobInfo(RPGLIB_JOB_PENDING, RPGLIB_STAT_APL_VALID);

                    Ret = E_OK;
                }
                else
                {
                    RpgLib_UpdateJobInfo(RPGLIB_JOB_OK, RPGLIB_STAT_IDLE);
                }
            }
            else
            {
                RpgLib_UpdateJobInfo(RPGLIB_JOB_OK, RPGLIB_STAT_IDLE);
            }
        }

        RpgLib_ReleaseApiAcceptation();
    }

    return Ret;
}

#if 0   /* Nbr1503(ChangeBaudrate) */
/******************************************************************************/
/* Function Name | RpgLib_CheckChangeBaudrate                                 */
/* Description   | Check whether baudrate change                              */
/* Preconditions |                                                            */
/* Parameters    | [IN]  PduId               : PDU ID                         */
/*               | [IN]  BaudrateInfo        : Baudrate information           */
/*               | [OUT] CheckBaudrateResult : Baudrate check result          */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_CheckChangeBaudrate
(
    VAR(PduIdType, AUTOMATIC) PduId,
    P2CONST(RpgLib_BaudrateInfoType, AUTOMATIC, RPGLIB_APPL_CONST) BaudrateInfo,
    P2VAR(RpgLib_CheckBaudrateResultType, AUTOMATIC, RPGLIB_APPL_DATA) CheckBaudrateResult
)
{
    VAR(uint16, AUTOMATIC) BaudrateConfigId;
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(NetworkHandleType, AUTOMATIC) NetworkId;

    Ret = E_NOT_OK;

    NetworkId = 0U;
    FuncRet = Rte_CanSM_GetNetworkId(PduId, &NetworkId);
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        BaudrateConfigId = 0U;
        FuncRet = Rte_CanSM_GetBaudrateConfigId(BaudrateInfo, &BaudrateConfigId);
        if( FuncRet == (Std_ReturnType)E_OK )
        {
            FuncRet = Rte_CanSM_CheckBaudrate(NetworkId, BaudrateConfigId);
            if( FuncRet == (Std_ReturnType)E_OK )
            {
                CheckBaudrateResult->NetworkId = NetworkId;
                CheckBaudrateResult->BaudrateConfigId = BaudrateConfigId;

                Ret = E_OK;
            }
        }
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | RpgLib_ReqChangeBaudrate                                   */
/* Description   | Requests change baudrate                                   */
/* Preconditions |                                                            */
/* Parameters    | [IN] CheckBaudrateResult : Baudrate check result           */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | Specify the result of RpgLib_CheckChangeBaudrate()         */
/*               |  in CheckBaudrateResult.                                   */
/******************************************************************************/
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_ReqChangeBaudrate
(
    P2CONST(RpgLib_CheckBaudrateResultType, AUTOMATIC, RPGLIB_APPL_CONST) CheckBaudrateResult
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Ret = E_NOT_OK;

    FuncRet = RpgLib_GetApiAcceptation();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        if( RpgLib_JobInfo.LocalStatus == RPGLIB_STAT_IDLE )
        {
            FuncRet = Rte_CanSM_SetBaudrate(CheckBaudrateResult->NetworkId, CheckBaudrateResult->BaudrateConfigId);
            if( FuncRet == (Std_ReturnType)E_OK )
            {
                RpgLib_UpdateJobInfo(RPGLIB_JOB_PENDING, RPGLIB_STAT_CHANGE_BAUDRATE);

                Ret = E_OK;
            }
            else
            {
                RpgLib_UpdateJobInfo(RPGLIB_JOB_OK, RPGLIB_STAT_IDLE);
            }
        }

        RpgLib_ReleaseApiAcceptation();
    }

    return Ret;
}
#endif

/******************************************************************************/
/* Function Name | RpgLib_NotifyChangeBaudrate                                */
/* Description   | Notify change baudrate result                              */
/* Preconditions |                                                            */
/* Parameters    | [IN] ChangeResult : Change baudrate result                 */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGLIB_CODE_SLOW) RpgLib_NotifyChangeBaudrate
(
    VAR(uint8, AUTOMATIC) ChangeResult
)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    FuncRet = RpgLib_GetApiAcceptation();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        if( ChangeResult == RPGLIB_CHANGEBAUDRATE_OK )
        {
            RpgLib_UpdateJobInfo(RPGLIB_JOB_OK, RPGLIB_STAT_IDLE);
        }
        else
        {
            RpgLib_UpdateJobInfo(RPGLIB_JOB_FAILED, RPGLIB_STAT_IDLE);
        }

        RpgLib_ReleaseApiAcceptation();
    }

    return;
}

#if 0   /* Nbr1503(CtrlFrame) */
/******************************************************************************/
/* Function Name | RpgLib_CtrlFrameRegistTxConfCallback                       */
/* Description   | Callback function registration at the completion of        */
/*               | control frame transmission                                 */
/* Preconditions |                                                            */
/* Parameters    | [IN] PduId    : PDU ID                                     */
/*               | [IN] Callback : Callback function                          */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_CtrlFrameRegistTxConfCallback
(
    VAR(PduIdType, AUTOMATIC) PduId,
    VAR(RpgLib_CtrlFrameTxCallbackType, AUTOMATIC) Callback
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Ret = E_NOT_OK;

    if( Callback != NULL_PTR )
    {
        FuncRet = RpgLib_CtrlFrameRegistCallback(PduId, Callback, NULL_PTR);
        if( FuncRet == (Std_ReturnType)E_OK )
        {
            Ret = E_OK;
        }
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | RpgLib_CtrlFrameRegistRxIndCallback                        */
/* Description   | Callback function registration when receiving notification */
/*               | of control frame                                           */
/* Preconditions |                                                            */
/* Parameters    | [IN] PduId    : PDU ID                                     */
/*               | [IN] Callback : Callback function                          */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_CtrlFrameRegistRxIndCallback
(
    VAR(PduIdType, AUTOMATIC) PduId,
    VAR(RpgLib_CtrlFrameRxCallbackType, AUTOMATIC) Callback
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Ret = E_NOT_OK;

    if( Callback != NULL_PTR )
    {
        FuncRet = RpgLib_CtrlFrameRegistCallback(PduId, NULL_PTR, Callback);
        if( FuncRet == (Std_ReturnType)E_OK )
        {
            Ret = E_OK;
        }
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | RpgLib_CtrlFrameTransmit                                   */
/* Description   | Transmit control frame                                     */
/* Preconditions |                                                            */
/* Parameters    | [IN] PduId   : PDU ID                                      */
/*               | [IN] PduInfo : PDU information                             */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_CtrlFrameTransmit
(
    VAR(PduIdType, AUTOMATIC) PduId,
    P2CONST(PduInfoType, AUTOMATIC, RPGLIB_APPL_CONST) PduInfo
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Ret = E_NOT_OK;

    FuncRet = Rte_CanIf_Transmit(PduId, PduInfo);
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        Ret = E_OK;
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | RpgLib_CtrlFrameTxConfirmation                             */
/* Description   | Confirmation of Tx control frame                           */
/* Preconditions |                                                            */
/* Parameters    | [IN] PduId : PDU ID                                        */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGLIB_CODE_SLOW) RpgLib_CtrlFrameTxConfirmation
(
    VAR(Gdn_PduIdType, AUTOMATIC) PduId
)
{
    VAR(uint8, AUTOMATIC) i;

    for( i = 0U; i < RPGLIB_CTRLFRAME_INFO_MAX; i++ )
    {
        /* This function is executed from above the interrupt, */
        /* so exclusive control is not necessary.              */
        if( ( RpgLib_CtrlFrameCallbackInfo[i].PduId == PduId ) &&
            ( RpgLib_CtrlFrameCallbackInfo[i].TxCallback != NULL_PTR ) )
        {
            RpgLib_CtrlFrameCallbackInfo[i].TxCallback(PduId);
            break;
        }
    }

    return;
}

/******************************************************************************/
/* Function Name | RpgLib_CtrlFrameRxIndication                               */
/* Description   | Indication of Rx control frame                             */
/* Preconditions |                                                            */
/* Parameters    | [IN] PduId   : PDU ID                                      */
/*               | [IN] PduInfo : PDU information                             */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGLIB_CODE_SLOW) RpgLib_CtrlFrameRxIndication
(
    VAR(Gdn_PduIdType, AUTOMATIC) PduId,
    P2CONST(Gdn_PduInfoType, AUTOMATIC, RPGLIB_APPL_CONST) PduInfo
)
{
    VAR(uint8, AUTOMATIC) i;
    VAR(PduInfoType, AUTOMATIC) ReplacePduInfo;

    for( i = 0U; i < RPGLIB_CTRLFRAME_INFO_MAX; i++ )
    {
        /* This function is executed from above the interrupt, */
        /* so exclusive control is not necessary.              */
        if( ( RpgLib_CtrlFrameCallbackInfo[i].PduId == PduId ) &&
            ( RpgLib_CtrlFrameCallbackInfo[i].RxCallback != NULL_PTR ) )
        {
            ReplacePduInfo.SduDataPtr = PduInfo->SduDataPtr;
            ReplacePduInfo.SduLength = PduInfo->SduLength;

            RpgLib_CtrlFrameCallbackInfo[i].RxCallback(PduId, &ReplacePduInfo);
            break;
        }
    }

    return;
}
#endif

/******************************************************************************/
/* Function Name | RpgLib_GetMemBlockInfo                                     */
/* Description   | Acquires block information about address and size          */
/* Preconditions |                                                            */
/* Parameters    | [IN]  MemoryId   : Memory Id                               */
/*               | [IN]  TargetAddr : Target address                          */
/*               | [OUT] BlockInfo  : Block information                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_GetMemBlockInfo
(
    VAR(uint32, AUTOMATIC) MemoryId,
    VAR(uint32, AUTOMATIC) TargetAddr,
    P2VAR(RpgLib_MemBlockInfoType, AUTOMATIC, RPGLIB_APPL_DATA) BlockInfo
)
{
    VAR(Rte_MemM_BlockInfoType, AUTOMATIC) MemMBlock;
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Ret = E_NOT_OK;

    MemMBlock.Addr = 0UL;
    MemMBlock.Size = 0UL;
    FuncRet = Rte_MemM_GetBlockInfo(MemoryId, TargetAddr, &MemMBlock);
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        BlockInfo->BlockTopAddr = MemMBlock.Addr;
        BlockInfo->BlockSize = MemMBlock.Size;

        Ret = E_OK;
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | RpgLib_ReqMemBlockErase                                    */
/* Description   | Requests MemM to erase block                               */
/* Preconditions |                                                            */
/* Parameters    | [IN] MemoryId  : Memory Id                                 */
/*               | [IN] BlockInfo : Block information                         */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_ReqMemBlockErase
(
    VAR(uint32, AUTOMATIC) MemoryId,
    P2CONST(RpgLib_MemBlockInfoType, AUTOMATIC, RPGLIB_APPL_CONST) BlockInfo
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Ret = E_NOT_OK;

    FuncRet = RpgLib_GetApiAcceptation();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        if( RpgLib_JobInfo.LocalStatus == RPGLIB_STAT_IDLE )
        {
            FuncRet = Rte_MemM_Erase(MemoryId, BlockInfo->BlockTopAddr, BlockInfo->BlockSize);
            if( FuncRet == (Std_ReturnType)E_OK )
            {
                RpgLib_UpdateJobInfo(RPGLIB_JOB_PENDING, RPGLIB_STAT_MEM_ERASE);

                Ret = E_OK;
            }
            else
            {
                RpgLib_UpdateJobInfo(RPGLIB_JOB_OK, RPGLIB_STAT_IDLE);
            }
        }

        RpgLib_ReleaseApiAcceptation();
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | RpgLib_WriteMemStart                                       */
/* Description   | Requests MemM to start writing                             */
/* Preconditions |                                                            */
/* Parameters    | [IN] MemoryId       : Memory Id                            */
/*               | [IN] WriteTopAddr   : Destination address                  */
/*               | [IN] WriteTotalSize : Total write size                     */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_WriteMemStart
(
    VAR(uint32, AUTOMATIC) MemoryId,
    VAR(uint32, AUTOMATIC) WriteTopAddr,
    VAR(uint32, AUTOMATIC) WriteTotalSize
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Ret = E_NOT_OK;

    FuncRet = RpgLib_GetApiAcceptation();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        if( RpgLib_JobInfo.LocalStatus == RPGLIB_STAT_IDLE )
        {
            FuncRet = Rte_MemM_WriteStart(MemoryId, WriteTopAddr, WriteTotalSize);
            if( FuncRet == (Std_ReturnType)E_OK )
            {
                RpgLib_UpdateJobInfo(RPGLIB_JOB_OK, RPGLIB_STAT_MEM_WRITE_PRE);

                Ret = E_OK;
            }
            else
            {
                RpgLib_UpdateJobInfo(RPGLIB_JOB_OK, RPGLIB_STAT_IDLE);
            }
        }

        RpgLib_ReleaseApiAcceptation();
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | RpgLib_ReqWriteMemUpdate                                   */
/* Description   | Requests MemM to update writing                            */
/* Preconditions |                                                            */
/* Parameters    | [IN] SrcAddr : Source address                              */
/*               | [IN] Size    : Write size                                  */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_ReqWriteMemUpdate
(
    P2CONST(uint8, AUTOMATIC, RPGLIB_APPL_CONST) SrcAddr,
    VAR(uint32, AUTOMATIC) Size
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Ret = E_NOT_OK;

    FuncRet = RpgLib_GetApiAcceptation();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        if( RpgLib_JobInfo.LocalStatus == RPGLIB_STAT_MEM_WRITE_PRE )
        {
            FuncRet = Rte_MemM_WriteUpdate(SrcAddr, Size);
            if( FuncRet == (Std_ReturnType)E_OK )
            {
                RpgLib_UpdateJobInfo(RPGLIB_JOB_PENDING, RPGLIB_STAT_MEM_WRITE);

                Ret = E_OK;
            }
            else
            {
                RpgLib_UpdateJobInfo(RPGLIB_JOB_OK, RPGLIB_STAT_IDLE);
            }
        }

        RpgLib_ReleaseApiAcceptation();
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | RpgLib_WriteMemFinish                                      */
/* Description   | Requests MemM to finish writing                            */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_WriteMemFinish (void)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Ret = E_NOT_OK;

    FuncRet = RpgLib_GetApiAcceptation();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        if( RpgLib_JobInfo.LocalStatus == RPGLIB_STAT_MEM_WRITE_FINISH )
        {
            FuncRet = Rte_MemM_WriteFinish();
            if( FuncRet == (Std_ReturnType)E_OK )
            {
                Ret = E_OK;
            }
            RpgLib_UpdateJobInfo(RPGLIB_JOB_OK, RPGLIB_STAT_IDLE);
        }

        RpgLib_ReleaseApiAcceptation();
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | RpgLib_ReqMemRead                                          */
/* Description   | Requests MemM to read                                      */
/* Preconditions |                                                            */
/* Parameters    | [IN]  MemoryId : Memory Id                                 */
/*               | [OUT] DestAddr : Destination address                       */
/*               | [IN]  SrcAddr  : Source address                            */
/*               | [IN]  Size     : Read size                                 */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_ReqMemRead
(
    VAR(uint32, AUTOMATIC) MemoryId,
    P2VAR(uint8, AUTOMATIC, RPGLIB_APPL_DATA) DestAddr,
    VAR(uint32, AUTOMATIC) SrcAddr,
    VAR(uint32, AUTOMATIC) Size
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    Ret = E_NOT_OK;

    FuncRet = RpgLib_GetApiAcceptation();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        if( RpgLib_JobInfo.LocalStatus == RPGLIB_STAT_IDLE )
        {
            Rte_MemErrM_ClearErrorInfo();
            FuncRet = Rte_MemM_Read(MemoryId, SrcAddr, DestAddr, Size);
            if( FuncRet == (Std_ReturnType)E_OK )
            {
                RpgLib_UpdateJobInfo(RPGLIB_JOB_PENDING, RPGLIB_STAT_MEM_READ);

                Ret = E_OK;
            }
            else
            {
                RpgLib_UpdateJobInfo(RPGLIB_JOB_OK, RPGLIB_STAT_IDLE);
            }
        }

        RpgLib_ReleaseApiAcceptation();
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | RpgLib_NotifyFlsCtrlMode                                   */
/* Description   | Notifies SchM of flash program mode                        */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : Flash program mode                             */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, RPGLIB_CODE_SLOW) RpgLib_NotifyFlsCtrlMode
(
    VAR(uint16, AUTOMATIC) Mode
)
{
    /* As the result of this function is always OK, there is no need to check the return value. */
    (void)Rte_SchM_Switch_DcmFlsProgram(Mode);

    return;
}

/******************************************************************************/
/* Function Name | RpgLib_CnvPhysicalAddr                                     */
/* Description   | Convert virtual address to physical address                */
/* Preconditions |                                                            */
/* Parameters    | [IN]  MemoryId      : Memory Id                            */
/*               | [IN]  VirtualAddr   : Virtual address                      */
/*               | [OUT] PhysicalAddr  : Physical address                     */
/*               | [OUT] DeviceType    : Device type                          */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, RPGLIB_CODE_SLOW) RpgLib_CnvPhysicalAddr
(
    VAR(uint32, AUTOMATIC) MemoryId,
    VAR(uint32, AUTOMATIC) VirtualAddr,
    P2VAR(uint32, AUTOMATIC, RPGLIB_APPL_DATA) PhysicalAddr,
    P2VAR(uint8, AUTOMATIC, RPGLIB_APPL_DATA) DeviceType
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;

    Ret = Rte_MemM_CnvPhysicalAddr(MemoryId, VirtualAddr, PhysicalAddr, DeviceType);

    return Ret;
}

/******************************************************************************/
/* Function Name | RpgLib_GetNextWriteAddr                                    */
/* Description   | Acquires next write address from CodeFlsIf                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Next write address                                         */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint32, RPGLIB_CODE_SLOW) RpgLib_GetNextWriteAddr (void)
{
    VAR(uint32, AUTOMATIC) NextWriteAddr;

    NextWriteAddr = Rte_CodeFlsIf_GetNextWriteAddr();

    return NextWriteAddr;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | RpgLib_Main_InvalidApl                                     */
/* Description   | MainFunction of RPGLIB_STAT_APL_INVALID                    */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, RPGLIB_CODE_FAST) RpgLib_Main_InvalidApl (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    FuncRet = RpgLib_CheckMemMCondition();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        RpgLib_EraseAplFlg = STD_ON;

        RpgLib_UpdateJobInfo(RPGLIB_JOB_OK, RPGLIB_STAT_IDLE);
    }
    else if( FuncRet == RPGLIB_E_PENDING )
    {
        /* No process */
    }
    else
    {
        RpgLib_UpdateJobInfo(RPGLIB_JOB_FAILED, RPGLIB_STAT_IDLE);
    }

    return;
}

/******************************************************************************/
/* Function Name | RpgLib_Main_ValidApl                                       */
/* Description   | MainFunction of RPGLIB_STAT_APL_VALID                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, RPGLIB_CODE_FAST) RpgLib_Main_ValidApl (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    FuncRet = RpgLib_CheckMemMCondition();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        /* As the result of this function is always OK, there is no need to check the return value. */
        (void)Rte_SchM_Switch_DcmRewriteControl(RTE_SCHM_BSWM_REWRITE_FINISH);

        RpgLib_EraseAplFlg = STD_OFF;

        RpgLib_UpdateJobInfo(RPGLIB_JOB_OK, RPGLIB_STAT_IDLE);
    }
    else if( FuncRet == RPGLIB_E_PENDING )
    {
        /* No process */
    }
    else
    {
        RpgLib_UpdateJobInfo(RPGLIB_JOB_FAILED, RPGLIB_STAT_IDLE);
    }

    return;
}

/******************************************************************************/
/* Function Name | RpgLib_Main_ReqErase                                       */
/* Description   | MainFunction of RPGLIB_STAT_MEM_ERASE                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, RPGLIB_CODE_FAST) RpgLib_Main_ReqErase (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    FuncRet = RpgLib_CheckMemMCondition();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        RpgLib_UpdateJobInfo(RPGLIB_JOB_OK, RPGLIB_STAT_IDLE);
    }
    else if( FuncRet == RPGLIB_E_PENDING )
    {
        /* No process */
    }
    else
    {
        RpgLib_UpdateJobInfo(RPGLIB_JOB_FAILED, RPGLIB_STAT_IDLE);
    }

    return;
}

/******************************************************************************/
/* Function Name | RpgLib_Main_ReqMemRead                                     */
/* Description   | MainFunction of RPGLIB_STAT_MEM_READ                       */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, RPGLIB_CODE_FAST) RpgLib_Main_ReqMemRead (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    FuncRet = RpgLib_CheckMemMCondition();
    if( FuncRet == (Std_ReturnType)E_OK )
    {
        FuncRet = Rte_MemErrM_CheckErrorInfo();
        if( FuncRet == (Std_ReturnType)E_OK )
        {
            RpgLib_UpdateJobInfo(RPGLIB_JOB_OK, RPGLIB_STAT_IDLE);
        }
        else
        {
            RpgLib_UpdateJobInfo(RPGLIB_JOB_MEMERR, RPGLIB_STAT_IDLE);
        }
    }
    else if( FuncRet == RPGLIB_E_PENDING )
    {
        /* No process */
    }
    else
    {
        RpgLib_UpdateJobInfo(RPGLIB_JOB_FAILED, RPGLIB_STAT_IDLE);
    }

    return;
}

/******************************************************************************/
/* Function Name | RpgLib_Main_ReqWriteMemUpdate                              */
/* Description   | MainFunction of RPGLIB_STAT_MEM_WRITE                      */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, RPGLIB_CODE_FAST) RpgLib_Main_ReqWriteMemUpdate (void)
{
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;

    FuncRet = RpgLib_CheckMemMUpdateCondition();
    if( FuncRet == RPGLIB_E_UPDATEIDLE )
    {
        RpgLib_UpdateJobInfo(RPGLIB_JOB_OK, RPGLIB_STAT_MEM_WRITE_PRE);
    }
    else if( FuncRet == RPGLIB_E_UPDATECOMPLETE )
    {
        RpgLib_UpdateJobInfo(RPGLIB_JOB_OK, RPGLIB_STAT_MEM_WRITE_FINISH);
    }
    else if( FuncRet == RPGLIB_E_PENDING )
    {
        /* No process */
    }
    else
    {
        RpgLib_UpdateJobInfo(RPGLIB_JOB_FAILED, RPGLIB_STAT_IDLE);
    }

    return;
}

/******************************************************************************/
/* Function Name | RpgLib_CheckMemMCondition                                  */
/* Description   | Check MemM status and result                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  RPGLIB_E_PENDING                                          */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, RPGLIB_CODE_FAST) RpgLib_CheckMemMCondition (void)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Rte_MemM_StatusType, AUTOMATIC) RteMemMStatusRet;
    VAR(Rte_MemM_JobResultType, AUTOMATIC) RteMemMJobRet;

    Ret = E_NOT_OK;

    RteMemMStatusRet = Rte_MemM_GetStatus();
    if( RteMemMStatusRet == RTE_MEMM_IDLE )
    {
        RteMemMJobRet = Rte_MemM_GetJobResult();
        if( RteMemMJobRet == RTE_MEMM_JOB_OK )
        {
            Ret = E_OK;
        }
    }
    else if( RteMemMStatusRet == RTE_MEMM_BUSY )
    {
        Ret = RPGLIB_E_PENDING;
    }
    else
    {
        /* No process */
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | RpgLib_CheckMemMUpdateCondition                            */
/* Description   | Check MemM status and result for update writing            */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  RPGLIB_E_UPDATEIDLE                                       */
/*               |  RPGLIB_E_UPDATECOMPLETE                                   */
/*               |  RPGLIB_E_PENDING                                          */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, RPGLIB_CODE_FAST) RpgLib_CheckMemMUpdateCondition (void)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Rte_MemM_StatusType, AUTOMATIC) RteMemMStatusRet;
    VAR(Rte_MemM_JobResultType, AUTOMATIC) RteMemMJobRet;

    Ret = E_NOT_OK;

    RteMemMStatusRet = Rte_MemM_GetStatus();
    if( ( RteMemMStatusRet == RTE_MEMM_UPDATEIDLE ) ||
        ( RteMemMStatusRet == RTE_MEMM_UPDATECOMPLETE ) )
    {
        RteMemMJobRet = Rte_MemM_GetJobResult();
        if( RteMemMJobRet == RTE_MEMM_JOB_OK )
        {
            if( RteMemMStatusRet == RTE_MEMM_UPDATEIDLE )
            {
                Ret = RPGLIB_E_UPDATEIDLE;
            }
            else
            {
                Ret = RPGLIB_E_UPDATECOMPLETE;
            }
        }
    }
    else if( RteMemMStatusRet == RTE_MEMM_UPDATEBUSY )
    {
        Ret = RPGLIB_E_PENDING;
    }
    else
    {
        /* No process */
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | RpgLib_UpdateJobInfo                                       */
/* Description   | Update RpgLib job information                              */
/* Preconditions |                                                            */
/* Parameters    | [IN] JobResult   : Result of job                           */
/*               |       RPGLIB_JOB_OK                                        */
/*               |       RPGLIB_JOB_PENDING                                   */
/*               |       RPGLIB_JOB_FAILED                                    */
/*               | [IN] LocalStatus : Status of job                           */
/*               |       RPGLIB_STAT_IDLE                                     */
/*               |       RPGLIB_STAT_CHANGE_BAUDRATE                          */
/*               |       RPGLIB_STAT_APL_INVALID                              */
/*               |       RPGLIB_STAT_APL_VALID                                */
/*               |       RPGLIB_STAT_MEM_ERASE                                */
/*               |       RPGLIB_STAT_MEM_READ                                 */
/*               |       RPGLIB_STAT_MEM_WRITE_PRE                            */
/*               |       RPGLIB_STAT_MEM_WRITE                                */
/*               |       RPGLIB_STAT_MEM_WRITE_FINISH                         */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, RPGLIB_CODE_FAST) RpgLib_UpdateJobInfo
(
    VAR(uint8, AUTOMATIC) JobResult,
    VAR(uint8, AUTOMATIC) LocalStatus
)
{
    VAR(uint8, AUTOMATIC) MaskPattern;

    MaskPattern = Rte_MaskInterruptAll();   /* for JobResult/LocalStatus */
    RpgLib_JobInfo.JobResult = JobResult;
    RpgLib_JobInfo.LocalStatus = LocalStatus;
    Rte_UnMaskInterruptAll(MaskPattern);    /* for JobResult/LocalStatus */

    return;
}

/******************************************************************************/
/* Function Name | RpgLib_GetApiAcceptation                                   */
/* Description   | Acquires the acceptation of executing API                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, RPGLIB_CODE_FAST) RpgLib_GetApiAcceptation (void)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(uint8, AUTOMATIC) MaskPattern;

    Ret = E_NOT_OK;

    MaskPattern = Rte_MaskInterruptAll();   /* prevent multiple execution */
    if( RpgLib_ApiAcceptingFlg == (uint8)STD_OFF )
    {
        RpgLib_ApiAcceptingFlg = STD_ON;

        Ret = E_OK;
    }
    Rte_UnMaskInterruptAll(MaskPattern);    /* prevent multiple execution */

    return Ret;
}

/******************************************************************************/
/* Function Name | RpgLib_ReleaseApiAcceptation                               */
/* Description   | Releases the acceptation of executing API                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, RPGLIB_CODE_FAST) RpgLib_ReleaseApiAcceptation (void)
{
    RpgLib_ApiAcceptingFlg = STD_OFF;

    return;
}

#if 0   /* Nbr1503(CtrlFrame) */
/******************************************************************************/
/* Function Name | RpgLib_CtrlFrameRegistCallback                             */
/* Description   | Registers the callback function to                         */
/*               | RpgLib_CtrlFrameCallbackInfo                               */
/* Preconditions |                                                            */
/* Parameters    | [IN] PduId      : PDU ID                                   */
/*               | [IN] TxCallback : Callback function for Tx                 */
/*               | [IN] RxCallback : Callback function for Rx                 */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, RPGLIB_CODE_FAST) RpgLib_CtrlFrameRegistCallback
(
    VAR(PduIdType, AUTOMATIC) PduId,
    VAR(RpgLib_CtrlFrameTxCallbackType, AUTOMATIC) TxCallback,
    VAR(RpgLib_CtrlFrameRxCallbackType, AUTOMATIC) RxCallback
)
{
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(uint8, AUTOMATIC) MaskPattern;
    VAR(uint8, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) LoopEnd;

    Ret = E_NOT_OK;
    LoopEnd = STD_OFF;

    MaskPattern = Rte_MaskInterruptAll();   /* for RpgLib_CtrlFrameCallbackInfo */

    for( i = 0U; i < RPGLIB_CTRLFRAME_INFO_MAX; i++ )
    {
        if( RpgLib_CtrlFrameCallbackInfo[i].PduId == RPGLIB_CTRLFRAME_INVALID_PDUID )
        {
            if( TxCallback != NULL_PTR )
            {
                RpgLib_CtrlFrameCallbackInfo[i].TxCallback = TxCallback;
            }
            else
            {
                RpgLib_CtrlFrameCallbackInfo[i].RxCallback = RxCallback;
            }

            RpgLib_CtrlFrameCallbackInfo[i].PduId = PduId;

            LoopEnd = STD_ON;
            Ret = E_OK;
        }
        else if( RpgLib_CtrlFrameCallbackInfo[i].PduId == PduId )
        {
            if( TxCallback != NULL_PTR )
            {
                if( RpgLib_CtrlFrameCallbackInfo[i].TxCallback == NULL_PTR )
                {
                    RpgLib_CtrlFrameCallbackInfo[i].TxCallback = TxCallback;

                    Ret = E_OK;
                }
            }
            else
            {
                if( RpgLib_CtrlFrameCallbackInfo[i].RxCallback == NULL_PTR )
                {
                    RpgLib_CtrlFrameCallbackInfo[i].RxCallback = RxCallback;

                    Ret = E_OK;
                }
            }

            LoopEnd = STD_ON;
        }
        else
        {
            /* No process */
        }

        if( LoopEnd == (uint8)STD_ON )
        {
            break;
        }
    }

    Rte_UnMaskInterruptAll(MaskPattern);    /* for RpgLib_CtrlFrameCallbackInfo */

    return Ret;
}
#endif

#define RPGLIB_STOP_SEC_CODE
#include <RpgLib_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

