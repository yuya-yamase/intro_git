/* WdgM_c_Revision(v2.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | WdgM/CODE                                                   */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <WdgM.h>

#include <WdgIf.h>
#include <EcuM.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define WDGM_ENTITYID_NUM           ((uint32)3UL)

#define WDGM_API_ID_INIT            (0x00U)
#define WDGM_API_ID_SETTRIGGERCOND  (0x01U)

#define WDGM_E_NO_INIT              (0x10U)
#define WDGM_E_PARAM_CONFIG         (0x11U)
#define WDGM_E_STATUS               (0x81U)

#define WDGM_UNINITED               ((uint8)0x00U)
#define WDGM_INITED                 ((uint8)0x11U)

#define WDGM_UINT32_MAX             ((uint32)0xFFFFFFFFUL)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint32 CurrentCnt;
    uint32 LastCnt;
} WdgM_AliveCntInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, WDGM_CODE_FAST) WdgM_ReportError
(
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define WDGM_START_SEC_VAR
#include <WdgM_MemMap.h>

static VAR(WdgM_AliveCntInfoType, WDGM_VAR_CLEARED) WdgM_AliveCnt[WDGM_ENTITYID_NUM];
static VAR(uint16, WDGM_VAR_CLEARED) WdgM_TimeoutVal;
static VAR(uint8, WDGM_VAR_CLEARED) WdgM_InitStatus;

#define WDGM_STOP_SEC_VAR
#include <WdgM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define WDGM_START_SEC_CST
#include <WdgM_MemMap.h>

#define WDGM_STOP_SEC_CST
#include <WdgM_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define WDGM_START_SEC_CODE
#include <WdgM_MemMap.h>

/******************************************************************************/
/* Function Name | WdgM_Init                                                  */
/* Description   | Initializes WdgM                                           */
/* Preconditions |                                                            */
/* Parameters    | [IN] ConfigPtr : Address of the WdgM configuration table   */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, WDGM_CODE_SLOW) WdgM_Init
(
    P2CONST(WdgM_ConfigType, AUTOMATIC, WDGM_APPL_CONST) ConfigPtr
)
{
    VAR(uint32, AUTOMATIC) index;

    if( WdgM_InitStatus == WDGM_UNINITED )
    {
        if( ConfigPtr == &WdgM_Cfg_Data )
        {
            WdgM_TimeoutVal = ConfigPtr->TimeoutVal;

            for( index = 0UL; index < WDGM_ENTITYID_NUM; index++ )
            {
                WdgM_AliveCnt[index].CurrentCnt = 0UL;
                WdgM_AliveCnt[index].LastCnt = 0UL;
            }

            WdgM_InitStatus = WDGM_INITED;
        }
        else
        {
            WdgM_ReportError(WDGM_API_ID_INIT, WDGM_E_PARAM_CONFIG);
        }
    }
    else
    {
        WdgM_ReportError(WDGM_API_ID_INIT, WDGM_E_STATUS);
    }

    return;
}

/******************************************************************************/
/* Function Name | WdgM_DeInit                                                */
/* Description   | Deinitializes WdgM                                         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, WDGM_CODE_SLOW) WdgM_DeInit (void)
{
    VAR(uint32, AUTOMATIC) index;

    WdgM_InitStatus = WDGM_UNINITED;

    for( index = 0UL; index < WDGM_ENTITYID_NUM; index++ )
    {
        WdgM_AliveCnt[index].CurrentCnt = 0UL;
        WdgM_AliveCnt[index].LastCnt = 0UL;
    }

    WdgM_TimeoutVal = 0U;

    return;
}

/******************************************************************************/
/* Function Name | WdgM_CheckpointReached                                     */
/* Description   | Indicates to WdgM that a Checkpoint within a Supervised    */
/*               | Entity has been reached                                    */
/* Preconditions |                                                            */
/* Parameters    | [IN] SeId : Identifier of the Supervised Entity            */
/*               | [IN] CheckpointId : Identifier of the Checkpoint           */
/* Return Value  | Result                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | Call this function between WdgM_Init() and WdgM_DeInit()   */
/******************************************************************************/
FUNC(Std_ReturnType, WDGM_CODE_SLOW) WdgM_CheckpointReached
(
    VAR(WdgM_SupervisedEntityIdType, AUTOMATIC) SeId,
    VAR(WdgM_CheckpointIdType, AUTOMATIC) CheckpointId
)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;

    Result = E_NOT_OK;

    if( WdgM_InitStatus == WDGM_INITED )
    {
        if( CheckpointId == WDGM_CHKPNTID_0 )
        {
            if( SeId < WDGM_ENTITYID_NUM )
            {
                if( WdgM_AliveCnt[SeId].CurrentCnt < WDGM_UINT32_MAX )
                {
                    WdgM_AliveCnt[SeId].CurrentCnt++;
                }
                else
                {
                    WdgM_AliveCnt[SeId].CurrentCnt = 0UL;
                }

                Result = E_OK;
            }
        }
    }

    return Result;
}

/******************************************************************************/
/* Function Name | WdgM_Trigger                                               */
/* Description   | Clears the Watchdog timer                                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, WDGM_CODE_SLOW) WdgM_Trigger (void)
{
    WdgIf_Trigger();

    return;
}

/******************************************************************************/
/* Function Name | WdgM_SetTriggerCondition                                   */
/* Description   | Sets the value of the Watchdog timeout                     */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | Call this function between WdgM_Init() and WdgM_DeInit()   */
/******************************************************************************/
FUNC(void, WDGM_CODE_SLOW) WdgM_SetTriggerCondition (void)
{
    if( WdgM_InitStatus == WDGM_INITED )
    {
        WdgIf_SetTriggerCondition(WDGIF_DEVICEINDEX_0, WdgM_TimeoutVal);
    }
    else
    {
        WdgM_ReportError(WDGM_API_ID_SETTRIGGERCOND, WDGM_E_NO_INIT);
    }

    return;
}

/******************************************************************************/
/* Function Name | WdgM_MainFunction                                          */
/* Description   | MainFunction                                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, WDGM_CODE_SLOW) WdgM_MainFunction (void)
{
    VAR(uint32, AUTOMATIC) index;
    VAR(uint8, AUTOMATIC) AliveCntUpdataFlg;

    if( WdgM_InitStatus == WDGM_INITED )
    {
        AliveCntUpdataFlg = STD_ON;

        for( index = 0UL; index < WDGM_ENTITYID_NUM; index++ )
        {
            if( WdgM_AliveCnt[index].CurrentCnt == WdgM_AliveCnt[index].LastCnt )
            {
                AliveCntUpdataFlg = STD_OFF;
                break;
            }
        }

        if( AliveCntUpdataFlg == (uint8)STD_ON )
        {
            for( index = 0UL; index < WDGM_ENTITYID_NUM; index++ )
            {
                WdgM_AliveCnt[index].LastCnt = WdgM_AliveCnt[index].CurrentCnt;
            }

            WdgIf_SetTriggerCondition(WDGIF_DEVICEINDEX_0, WdgM_TimeoutVal);
        }
    }

    return;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/
/******************************************************************************/
/* Function Name | WdgM_ReportError                                           */
/* Description   | Notifies EcuM of the error information                     */
/* Preconditions |                                                            */
/* Parameters    | [IN] ApiId   : API ID                                      */
/*               | [IN] ErrorId : Error ID                                    */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, WDGM_CODE_FAST) WdgM_ReportError
(
    VAR(uint8, AUTOMATIC) ApiId,
    VAR(uint8, AUTOMATIC) ErrorId
)
{
    VAR(EcuM_ErrorType, AUTOMATIC) ErrorInfo;

    ErrorInfo.ModuleId = ECUM_MODULE_WDGM;
    ErrorInfo.ApiId = ApiId;
    ErrorInfo.ErrorId = ErrorId;
    EcuM_ReportError(&ErrorInfo);

    return;
}

#define WDGM_STOP_SEC_CODE
#include <WdgM_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2022/06/07 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

