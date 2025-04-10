/* BswM_c_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | BswM/CODE                                                   */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <BswM.h>
#include <BswM_CanSM.h>
#include <BswM_EcuM.h>
#include "BswM_Local.h"

#include <EcuM.h>
#include <CanSM_BswM.h>

#if (REPROG_CFG_ETH_USE == STD_ON)
#include <EthSM.h>
#include <BswM_EthSM.h>
#endif
#if (REPROG_CFG_CXPI_USE == STD_ON)
#include <BswM_CxpiSM.h>
#endif
#if (REPROG_CFG_SUBMICONEVENT_TXCONFIRMATION_USE == STD_ON)
#include <SchM_BswM.h>
#include <SubMiconIf.h>
#endif


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define BSWM_START_SEC_VAR
#include <BswM_MemMap.h>

VAR(CanSM_BswMRequestedModeType, BSWM_VAR_CLEARED) BswM_CanSMState[CANSM_MAXNETWORK_NUM];
VAR(EcuM_StateType, BSWM_VAR_CLEARED) BswM_EcuMState;
VAR(uint8, BSWM_VAR_CLEARED) BswM_ComStartFlg;

#if (REPROG_CFG_ETH_USE == STD_ON)
VAR(EthSM_NetworkModeStateType, BSWM_VAR_CLEARED) BswM_EthSMState[BSWM_ETHSM_MAXNETWORK_NUM];
VAR(uint8, BSWM_VAR_CLEARED) BswM_ComStartFlg_Eth;
#endif

#if (REPROG_CFG_POSRES_AFTER_RESET == STD_ON)
#if (REPROG_CFG_ETH_USE != STD_ON)
static P2CONST(BswM_ConfigType, BSWM_VAR_CLEARED, BSWM_APPL_CONST) BswM_CfgPtrBackup;
#endif
#endif

#define BSWM_STOP_SEC_VAR
#include <BswM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define BSWM_START_SEC_CST
#include <BswM_MemMap.h>

#define BSWM_STOP_SEC_CST
#include <BswM_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define BSWM_START_SEC_CODE
#include <BswM_MemMap.h>

/******************************************************************************/
/* Function Name | BswM_Init                                                  */
/* Description   | Initializes BswM                                           */
/* Preconditions |                                                            */
/* Parameters    | [IN] ConfigPtr : Address of the BswM configuration table   */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, BSWM_CODE_SLOW) BswM_Init
(
    P2CONST(BswM_ConfigType, AUTOMATIC, BSWM_APPL_CONST) ConfigPtr
)
{
    VAR(uint8, AUTOMATIC) i;

    if( ConfigPtr != NULL_PTR )
    {
        BswM_CfgPtr = ConfigPtr;

#if (REPROG_CFG_POSRES_AFTER_RESET == STD_ON)
#if (REPROG_CFG_ETH_USE != STD_ON)
        BswM_CfgPtrBackup = ConfigPtr;
#endif
#endif

        BswM_EcuMState = ECUM_STATE_STARTUP;

        for( i = 0U; i < CANSM_MAXNETWORK_NUM; i++ )
        {
            BswM_CanSMState[i] = BswM_CfgPtr->InitValDataPtr->InitValCanSMState;
        }

        BswM_CtrlReqMode.Rewrite = BswM_CfgPtr->InitValDataPtr->InitValRewrite;
        BswM_CtrlReqMode.Session = BswM_CfgPtr->InitValDataPtr->InitValSession;
        BswM_CtrlReqMode.Security = BswM_CfgPtr->InitValDataPtr->InitValSecurity;
        BswM_CtrlReqMode.FlsPrg = BswM_CfgPtr->InitValDataPtr->InitValFlsPrg;
        BswM_CtrlReqMode.EcuReset = BswM_CfgPtr->InitValDataPtr->InitValEcuReset;
        BswM_CtrlReqMode.Finish = BswM_CfgPtr->InitValDataPtr->InitValFinish;
        BswM_CtrlReqMode.MainErr = BswM_CfgPtr->InitValDataPtr->InitValMainErr;
        BswM_CtrlReqMode.UsrReset = BswM_CfgPtr->InitValDataPtr->InitValUsrReset;
        BswM_CtrlReqMode.UsrSleep = BswM_CfgPtr->InitValDataPtr->InitValUsrSleep;
        BswM_CtrlReqMode.Acc = BswM_CfgPtr->InitValDataPtr->InitValAcc;
        BswM_CtrlReqMode.Ig = BswM_CfgPtr->InitValDataPtr->InitValIg;
#if (REPROG_CFG_ETH_USE == STD_ON)
        BswM_CtrlReqMode.EthSendRcv = BswM_CfgPtr->InitValDataPtr->InitValEthSendRcv;
#endif

        BswM_ComStartFlg = STD_OFF;

#if (REPROG_CFG_ETH_USE == STD_ON)
        for( i = 0U; i < BSWM_ETHSM_MAXNETWORK_NUM; i++ )
        {
            BswM_EthSMState[i] = BswM_CfgPtr->InitValDataPtr->InitValEthSMState;
        }

        BswM_ComStartFlg_Eth = STD_OFF;
#endif

    }
    else
    {
        BswM_CfgPtr = NULL_PTR;

#if (REPROG_CFG_POSRES_AFTER_RESET == STD_ON)
#if (REPROG_CFG_ETH_USE != STD_ON)
        BswM_CfgPtrBackup = NULL_PTR;
#endif
#endif

        BswM_ReportError(BSWM_API_ID_INIT, BSWM_E_NULL_POINTER);
    }

    return;
}

/******************************************************************************/
/* Function Name | BswM_Deinit                                                */
/* Description   | Deinitializes BswM                                         */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, BSWM_CODE_SLOW) BswM_Deinit (void)
{
    BswM_CfgPtr = NULL_PTR;

    return;
}

/******************************************************************************/
/* Function Name | BswM_CanSM_CurrentState                                    */
/* Description   | This function called by CanSM to indicate its current state*/
/* Preconditions |                                                            */
/* Parameters    | [IN] Network      : Network identifier                     */
/*               | [IN] CurrentState : Current CanSM state                    */
/*               |       CANSM_BSWM_NO_COMMUNICATION                          */
/*               |       CANSM_BSWM_FULL_COMMUNICATION                        */
/*               |       CANSM_BSWM_CHANGE_BAUDRATE                           */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, BSWM_CODE_SLOW) BswM_CanSM_CurrentState
(
    VAR(NetworkHandleType, AUTOMATIC) Network,
    VAR(CanSM_BswMRequestedModeType, AUTOMATIC) CurrentState
)
{
    VAR(uint8, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) NetworkSearchFlg;

    if( BswM_CfgPtr != NULL_PTR )
    {
        NetworkSearchFlg = STD_OFF;

        for( i = 0U; i < BswM_CfgPtr->CanSMCfgDataPtr->NetworkInfoTbl->NetworkNum; i++ )
        {
            if( Network == BswM_CfgPtr->CanSMCfgDataPtr->NetworkInfoTbl->NetworkSettingTbl[i].NetworkId )
            {
                NetworkSearchFlg = STD_ON;

                if( CurrentState == CANSM_BSWM_NO_COMMUNICATION )
                {
                    BswM_Act_CanSMNoCom(Network, i);
                }
                else if( CurrentState == CANSM_BSWM_FULL_COMMUNICATION )
                {
                    BswM_Act_CanSMFullCom(Network, i);
                }
                else if( CurrentState == CANSM_BSWM_CHANGE_BAUDRATE )
                {
                    BswM_Act_CanSMChangeBaudrate(i);
                }
                else
                {
                    BswM_ReportError(BSWM_API_ID_CANSMCURRENTSTATE, BSWM_E_REQ_MODE_OUT_OF_RANGE);
                }

                break;
            }
        }

        /* Network was out of range */
        if( NetworkSearchFlg != (uint8)STD_ON )
        {
            BswM_ReportError(BSWM_API_ID_CANSMCURRENTSTATE, BSWM_E_PARAM_INVALID);
        }
    }
    else
    {
        BswM_ReportError(BSWM_API_ID_CANSMCURRENTSTATE, BSWM_E_NO_INIT);
    }

    return;
}

/******************************************************************************/
/* Function Name | BswM_EcuM_CurrentState                                     */
/* Description   | This function called by EcuM to indicate the current       */
/*               | ECU operation mode                                         */
/* Preconditions |                                                            */
/* Parameters    | [IN] CurrentState : Current EcuM state                     */
/*               |       ECUM_STATE_STARTUP                                   */
/*               |       ECUM_STATE_RUN                                       */
/*               |       ECUM_STATE_SHUTDOWN                                  */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, BSWM_CODE_SLOW) BswM_EcuM_CurrentState
(
    VAR(EcuM_StateType, AUTOMATIC) CurrentState
)
{
    if( BswM_CfgPtr != NULL_PTR )
    {
        if( CurrentState == ECUM_STATE_STARTUP )
        {
            BswM_Act_EcuMStartup();
        }
        else if( ( CurrentState == ECUM_STATE_RUN ) || ( CurrentState == ECUM_STATE_SHUTDOWN ) )
        {
            /* No process */
        }
        else
        {
            BswM_ReportError(BSWM_API_ID_ECUMCURRENTSTATE, BSWM_E_REQ_MODE_OUT_OF_RANGE);
        }
    }
    else
    {
        BswM_ReportError(BSWM_API_ID_ECUMCURRENTSTATE, BSWM_E_NO_INIT);
    }

    return;
}

#if (REPROG_CFG_ETH_USE == STD_ON)
/******************************************************************************/
/* Function Name | BswM_EthSM_CurrentState                                    */
/* Description   | This function called by EthSM to indicate its current state*/
/* Preconditions |                                                            */
/* Parameters    | [IN] Network      : Network identifier                     */
/*               | [IN] CurrentState : Current EthSM state                    */
/*               |       ETHSM_STATE_OFFLINE                                  */
/*               |       ETHSM_STATE_WAIT_TRCVLINK                            */
/*               |       ETHSM_STATE_WAIT_ONLINE                              */
/*               |       ETHSM_STATE_ONLINE                                   */
/*               |       ETHSM_STATE_ONHOLD                                   */
/*               |       ETHSM_STATE_WAIT_OFFLINE                             */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, BSWM_CODE_SLOW) BswM_EthSM_CurrentState
(
    VAR(NetworkHandleType, AUTOMATIC) Network,
    VAR(EthSM_NetworkModeStateType, AUTOMATIC) CurrentState
)
{
    VAR(uint8, AUTOMATIC) i;

    for( i = 0U; i < BswM_CfgPtr->EthSMCfgDataPtr->NetworkInfoTbl->NetworkNum; i++ )
    {
        if( Network == BswM_CfgPtr->EthSMCfgDataPtr->NetworkInfoTbl->NetworkSettingTbl[i].u1ComMNetwHnd )
        {
            if( CurrentState == ETHSM_STATE_ONLINE )
            {
                BswM_Act_EthSMFullCom(Network, i);
            }
            else if( (CurrentState == ETHSM_STATE_OFFLINE) ||
                         (CurrentState == ETHSM_STATE_WAIT_TRCVLINK) ||
                         (CurrentState == ETHSM_STATE_WAIT_ONLINE) ||
                         (CurrentState == ETHSM_STATE_ONHOLD) ||
                         (CurrentState == ETHSM_STATE_WAIT_OFFLINE) )
            {
                BswM_EthSMState[i] = CurrentState ;
            }
            else
            {
                /* No process */
            }
        }
    }

    return;
}
#endif

#if (REPROG_CFG_CXPI_USE == STD_ON)
/*******************************************************************************/
/* Function Name | BswM_CxpiSM_CurrentState                                    */
/* Description   | This function called by CxpiSM to indicate its current state*/
/* Preconditions |                                                             */
/* Parameters    | [IN] Network      : Network identifier                      */
/*               | [IN] CurrentState : Current CxpiSM state                    */
/*               |       CXPISM_BSWM_NO_COMMUNICATION                          */
/*               |       CXPISM_BSWM_FULL_COMMUNICATION                        */
/* Return Value  | None                                                        */
/* Notes         | None                                                        */
/*******************************************************************************/
FUNC(void, BSWM_CODE_SLOW) BswM_CxpiSM_CurrentState
(
    VAR(NetworkHandleType, AUTOMATIC) Network,
    VAR(CxpiSM_BswMCurrentStateType, AUTOMATIC) CurrentState
)
{
    if( BswM_CfgPtr != NULL_PTR )
    {
        if( Network == BswM_CfgPtr->CxpiSMCfgDataPtr->NetworkInfoTbl->NetworkSettingTbl->NetworkId )
        {
            if( CurrentState == (CxpiSM_BswMCurrentStateType)CXPISM_BSWM_FULL_COMMUNICATION )
            {
                BswM_Act_CxpiSMFullCom();
            }
            else
            {
                BswM_ReportError(BSWM_API_ID_CXPISMCURRENTSTATE, BSWM_E_REQ_MODE_OUT_OF_RANGE);
            }
        }
        else
        {
            BswM_ReportError(BSWM_API_ID_CXPISMCURRENTSTATE, BSWM_E_PARAM_INVALID);
        }
    }
    else
    {
        BswM_ReportError(BSWM_API_ID_CXPISMCURRENTSTATE, BSWM_E_NO_INIT);
    }

    return;
}

/******************************************************************************/
/* Function Name | BswM_CxpiCddGetNAD                                         */
/* Description   | Acquires the NAD information                               */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | NAD                                                        */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(uint8, BSWM_CODE_SLOW) BswM_CxpiCddGetNAD (void)
{
    return BswM_CfgPtr->CxpiSMCfgDataPtr->PduIdInfoTbl->PduIdSettingTbl[0].Nad;
}
#endif

#if (REPROG_CFG_POSRES_AFTER_RESET == STD_ON)
/******************************************************************************/
/* Function Name | BswM_Get_CommunicationInfo                                 */
/* Description   | Acquires communication Information                         */
/* Preconditions |                                                            */
/* Parameters    | [IN]  PduId          : Pdu id                              */
/*               | [OUT] ReceiveChannel : Receive channel                     */
/*               | [OUT] ReceiveId      : Receive id                          */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | - This function can be used when                           */
/*               |   REPROG_CFG_POSRES_AFTER_RESET is STD_ON.                 */
/*               | - This function can be called after calling BswM_Deinit()  */
/******************************************************************************/
FUNC(Std_ReturnType, BSWM_CODE_SLOW) BswM_Get_CommunicationInfo
(
    VAR(PduIdType, AUTOMATIC) PduId,
    P2VAR(uint8, AUTOMATIC, BSWM_APPL_DATA) ReceiveChannel,
    P2VAR(uint32, AUTOMATIC, BSWM_APPL_DATA) ReceiveId
)
#if (REPROG_CFG_ETH_USE == STD_ON)
{
    VAR(Std_ReturnType, AUTOMATIC) Result;

    Result = E_NOT_OK;

    if( (ReceiveChannel != NULL_PTR) &&
        (ReceiveId != NULL_PTR) )
    {
        *ReceiveChannel = 0U;
        *ReceiveId = 0UL;

        Result = E_OK;
    }

    return Result;
}
#elif (REPROG_CFG_CXPI_USE == STD_ON)
{
    P2CONST(BswM_CxpiSM_PduIdConfigType, AUTOMATIC, BSWM_APPL_CONST) PduIdCfgPtr;
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(uint8, AUTOMATIC) i;

    Result = E_NOT_OK;

    if( (BswM_CfgPtrBackup != NULL_PTR) &&
        (ReceiveChannel != NULL_PTR) &&
        (ReceiveId != NULL_PTR) )
    {
        PduIdCfgPtr = BswM_CfgPtrBackup->CxpiSMCfgDataPtr->PduIdInfoTbl;

        for( i = 0U; i < PduIdCfgPtr->PduIdNum; i++ )
        {
            if( PduId == PduIdCfgPtr->PduIdSettingTbl[i].PduId )
            {
                *ReceiveChannel = PduIdCfgPtr->PduIdSettingTbl[i].Controller;
                *ReceiveId = (uint32)PduIdCfgPtr->PduIdSettingTbl[i].Nad;
                Result = E_OK;
                break;
            }
        }
    }

    return Result;
}
#else
{
    P2CONST(CanSM_PduIdConfigType, AUTOMATIC, BSWM_APPL_CONST) PduIdCfgPtr;
    VAR(Std_ReturnType, AUTOMATIC) Result;
    VAR(uint8, AUTOMATIC) i;

    Result = E_NOT_OK;

    if( (BswM_CfgPtrBackup != NULL_PTR) &&
        (ReceiveChannel != NULL_PTR) &&
        (ReceiveId != NULL_PTR) )
    {
        PduIdCfgPtr = BswM_CfgPtrBackup->CanSMCfgDataPtr->PduIdInfoTbl;

        for( i = 0U; i < PduIdCfgPtr->PduIdNum; i++ )
        {
            if( PduId == PduIdCfgPtr->PduIdSettingTbl[i].PduId )
            {
                *ReceiveChannel = PduIdCfgPtr->PduIdSettingTbl[i].Controller;
                *ReceiveId = PduIdCfgPtr->PduIdSettingTbl[i].CanId;
                Result = E_OK;
                break;
            }
        }
    }

    return Result;
}
#endif
#endif /* (REPROG_CFG_POSRES_AFTER_RESET == STD_ON) */


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define BSWM_STOP_SEC_CODE
#include <BswM_MemMap.h>


/******************************************************************************/
/* External Functions(SEC2)                                                   */
/******************************************************************************/
#define BSWM_START_SEC2_CODE
#include <BswM_MemMap.h>

#if (REPROG_CFG_SUBMICONEVENT_TXCONFIRMATION_USE == STD_ON)
/******************************************************************************/
/* Function Name | BswM_SubMiconEventTxConfirmation                           */
/* Description   | Notification of events to SubMicon completed               */
/* Preconditions |                                                            */
/* Parameters    | [IN] User : Request User                                   */
/*               | [IN] Mode : Request Mode                                   */
/* Return Value  | None                                                       */
/* Notes         | - This function can be used when                           */
/*               |   REPROG_CFG_SUBMICONEVENT_TXCONFIRMATION_USE is STD_ON.   */
/*               | - Call this function when the event information            */
/*               |   notification processing of SubMiconIf_Main_NotifyEvent() */
/*               |   is completed.                                            */
/*               | - Set the same value as the parameters of                  */
/*               |   SubMiconIf_Main_NotifyEvent() in the parameters(User and */
/*               |   Mode).                                                   */
/******************************************************************************/
FUNC(void, BSWM_CODE_SLOW) BswM_SubMiconEventTxConfirmation
(
    VAR(uint16, AUTOMATIC) User,
    VAR(uint16, AUTOMATIC) Mode
)
{
    VAR(uint8, AUTOMATIC) FinEvtFlg;

    FinEvtFlg = STD_OFF;

    if( BswM_CfgPtr != NULL_PTR )
    {
        if( ( User == SUBMICONIF_USER_BSWM_ECU_RESET ) ||
            ( User == SUBMICONIF_USER_BSWM_MAIN_ERR )  ||
            ( User == SUBMICONIF_USER_BSWM_USR_RESET ) ||
            ( User == SUBMICONIF_USER_BSWM_USR_SLEEP ) )
        {
            FinEvtFlg = STD_ON;
        }
        else if( ( User == SUBMICONIF_USER_BSWM_ACC ) && ( Mode == SUBMICONIF_MODE_ACC_OFF ) )
        {
            if( BswM_CfgPtr->AccIgActDataPtr->ActAcc != BSWM_SHUTDOWN_NONE )
            {
                FinEvtFlg = STD_ON;
            }
        }
        else if( ( User == SUBMICONIF_USER_BSWM_IG ) && ( Mode == SUBMICONIF_MODE_IG_OFF ) )
        {
            if( BswM_CfgPtr->AccIgActDataPtr->ActIg != BSWM_SHUTDOWN_NONE )
            {
                FinEvtFlg = STD_ON;
            }
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        BswM_ReportError(BSWM_API_ID_SUBMICONEVENT_TXCONFIRMATION, BSWM_E_NO_INIT);
    }

    if( FinEvtFlg == (uint8)STD_ON )
    {
        SchM_Finish_SubMiconFinEvtWait();
    }

    return;
}
#endif


/******************************************************************************/
/* Internal Functions(SEC2)                                                   */
/******************************************************************************/

#define BSWM_STOP_SEC2_CODE
#include <BswM_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/06/19 :Update                                rel.AUBASS */
/*  v3.00       :2019/07/16 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

