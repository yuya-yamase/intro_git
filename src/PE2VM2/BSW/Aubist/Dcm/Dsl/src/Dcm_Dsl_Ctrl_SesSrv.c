/* Dcm_Dsl_Ctrl_SesSrv_c(v5-9-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsl_Ctrl/CODE                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsl_Ctrl.h>
#include "../../Dsl/inc/Dcm_Dsl_Ctrl_local.h"

#include "../../Dsl/inc/Dcm_Dsl_Main.h"
#include "../../Dsl/inc/Dcm_Dsl_SecurityMng.h"
#include "../../Dsl/inc/Dcm_Dsl_SessionMng.h"
#include "../../Dsl/inc/Dcm_Dsl_RxAbt.h"
#include "../../Dsl/inc/Dcm_Dsl_TxAbt.h"
#include "../../Dsl/inc/Dcm_Dsl_CommHandling.h"

#include "../../Dsd/inc/Dcm_Dsd_ServiceMng.h"

#include <Dcm/Dcm_Dsd_SendMng.h>
#include <Dcm/Dcm_Main_TmrSrv.h>
#include <Dcm/Dcm_Main_EvtDistr.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsl_Ctrl_ResetToDefaultSession
( void );

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>


/****************************************************************************/
/* Function Name | Dcm_GetSesCtrlType                                       */
/* Description   | Call the function(Dcm_Dsl_SessionMng_GetSesCtrlType)     */
/*               | to get the active session control type value.            */
/* Preconditions |                                                          */
/* Parameters    | [out] SesCtrlType :                                      */
/*               |        Active Session Control Type value Content is acc- */
/*               |        ording to "diagnosticSessionType" parameter of D- */
/*               |        iagnosticSessionControl request                   */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : this value is always returned.             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_GetSesCtrlType
(
    P2VAR( Dcm_SesCtrlType, AUTOMATIC, DCM_APPL_DATA ) SesCtrlType
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( SesCtrlType != NULL_PTR )
    {
        u1_RetVal = Dcm_Dsl_SessionMng_GetSesCtrlType(SesCtrlType);
    }

    return u1_RetVal;

}

#if( DCM_ASYNC_RESETTODEFAULTSESSION == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_ResetToDefaultSession                                */
/* Description   | Allows the application to reset the current session to   */
/*               | Default session.                                         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Transition Acceptance Success              */
/*               |    E_NOT_OK : Transition Acceptance Failure              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_ResetToDefaultSession
( void )
{
    Dcm_Main_EvtDistr_RetType u1_EvtResult;
    Std_ReturnType            u1_RetVal;

    u1_RetVal = E_NOT_OK;

    /* Prevent queue overflow. Return value ignoring */
    (void)Dcm_Main_EvtDistr_DeleteEvent(DCM_M_EVTID_DSL_RESETTODEFSES, FALSE);
    u1_EvtResult = Dcm_Main_EvtDistr_SendEvent(DCM_M_EVTID_DSL_RESETTODEFSES);

    if( u1_EvtResult == (Dcm_Main_EvtDistr_RetType)DCM_MAIN_EVTDISTR_E_OK )
    {
        u1_RetVal = E_OK;
    }

    return u1_RetVal;

}
#endif /* DCM_ASYNC_RESETTODEFAULTSESSION == STD_ON */

#if( DCM_ASYNC_RESETTODEFAULTSESSION == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_ResetToDefaultSession                                */
/* Description   | Allows the application to reset the current session to   */
/*               | Default session.                                         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Transition Success                         */
/*               |    E_NOT_OK : Provisional(For a busy, retry it)          */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_ResetToDefaultSession
( void )
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = Dcm_Dsl_Ctrl_ResetToDefaultSession();

    return u1_RetVal;

}
#endif /* DCM_ASYNC_RESETTODEFAULTSESSION == STD_OFF */

#if( DCM_ASYNC_RESETTODEFAULTSESSION == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_ResetToDefaultSessionCbk                         */
/* Description   | Set default session. (Application request)               */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1EventId : DCM_M_EVTID_DSL_RESETTODEFSES           */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_ResetToDefaultSessionCbk
(
    const uint8 u1EventId /* MISRA DEVIATION */
)
{
    Std_ReturnType u1_RetSesChgResult;
    boolean        b_Qualified;

    b_Qualified = (boolean)FALSE;

    u1_RetSesChgResult = Dcm_Dsl_Ctrl_ResetToDefaultSession();

    if( u1_RetSesChgResult == (Std_ReturnType)E_OK )
    {
        b_Qualified = (boolean)TRUE;
    }
    
    /* Return value ignoring */
    (void)Dcm_Dsl_NotifyResetToDefaultSessionResult(b_Qualified);
    
    return;
}
#endif /* DCM_ASYNC_RESETTODEFAULTSESSION == STD_ON */

/****************************************************************************/
/* Function Name | DslInternal_SetSesCtrlType                               */
/* Description   | Call the function(Dcm_Dsl_SessionMng_SetSesCtrlType)     */
/*               | to set a new session control type value.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] SesCtrlType  : new session control type value       */
/*               | [in] bDelayUpdate :                                      */
/*               |                TRUE  : Confirmation Reception timing     */
/*               |                FALSE : Immediate                         */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) DslInternal_SetSesCtrlType
(
    Dcm_SesCtrlType SesCtrlType,
    const boolean bDelayUpdate
)
{
    Dcm_Dsl_SessionMng_SetSesCtrlType(SesCtrlType, bDelayUpdate, DCM_DSL_SESCHG_KIND_EXTERNAL);

    return;

}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_SetSesCtrlType                              */
/* Description   | Call the function(Dcm_Dsl_SessionMng_SetSesCtrlType)     */
/*               | to set a new session control type value.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] SesCtrlType  : new session control type value       */
/*               | [in] bDelayUpdate :                                      */
/*               |                TRUE  : Confirmation Reception timing     */
/*               |                FALSE : Immediate                         */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetSesCtrlType
(
    Dcm_SesCtrlType SesCtrlType,
    const boolean bDelayUpdate
)
{
    Dcm_Dsl_SessionMng_SetSesCtrlType(SesCtrlType, bDelayUpdate, DCM_DSL_SESCHG_KIND_INTERNAL);

    if( bDelayUpdate == (boolean)FALSE )
    {
      /* Return value ignoring */
      (void)Dcm_Dsl_SessionMng_SwitchModeSesCtrl(SesCtrlType);
    }

    return;

}

/* Because it is a function used only by SID10 */
#if( DCM_SUPPORT_SID10 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_SwitchModeSesCtrl                                */
/* Description   | Call the function (Dcm_Dsl_SessionMng_SwitchModeSesCtrl) */
/*               | to change DcmDiagnosticSessionControl mode.              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1Mode         : Next mode                          */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Failure                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsl_SwitchModeSesCtrl
(
    const uint8 u1Mode
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = Dcm_Dsl_SessionMng_SwitchModeSesCtrl(u1Mode);

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID10 == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_SetSesConf                                  */
/* Description   | Call the function(Dcm_Dsl_SessionMng_SetSesConf)         */
/*               | to set the session in Dcm_TpTxConfirmation.              */
/* Preconditions | none                                                     */
/* Parameters    | [in] bUpdateEnable :  TRUE : Session Update Enable       */
/*               |                      FALSE : Session Update Disable      */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         |  -                                                       */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetSesConf
(
    const boolean bUpdateEnable
)
{
    Dcm_Dsl_SessionMng_SetSesConf(bUpdateEnable);

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_ReqSesCtrlChgNotification                   */
/* Description   | Call the function                                        */
/*               | (Dcm_Dsl_SessionMng_ReqSesCtrlChgNotification)           */
/*               | to notify SW-C of the change of the session.             */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ReqSesCtrlChgNotification
( void )
{

    Dcm_Dsl_SessionMng_ReqSesCtrlChgNotification();

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_IsSesCtrlPermission                         */
/* Description   | This function obtains whether the current session has    */
/*               | the right to access the resource.                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2PduMapIndex   : PduMapIndex Value                 */
/* Return Value  | boolean                                                  */
/*               |        TRUE       : possible                             */
/*               |        FALSE      : impossible                           */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_IsSesCtrlPermission
(
    const uint16 u2PduMapIndex
)
{
    P2CONST( AB_83_ConstV Dcm_Dsl_RowType, AUTOMATIC, DCM_APPL_CONST ) pt_Row;
    P2CONST( AB_83_ConstV uint8, AUTOMATIC, DCM_APPL_CONST )           pt_SessionTbl;
    uint16          u2_RowIndex;
    Dcm_SesCtrlType u1_Session;
    uint8           u1_SessionNumMax;
    uint8           u1_SessionCnt;
    boolean         b_Result;
    boolean         b_InteractiveClient;

    b_Result = (boolean)FALSE;

    /* always success */
    (void)Dcm_Dsl_SessionMng_GetSesCtrlType(&u1_Session);

    if( u1_Session != DCM_DEFAULT_SESSION )
    {
        b_InteractiveClient = Dcm_Dsl_Ctrl_IsInteractiveClient(u2PduMapIndex);
        if( b_InteractiveClient == (boolean)TRUE )
        {
            u2_RowIndex      = Dcm_Dsl_PduIdMapTable[u2PduMapIndex].u2RowIndex;
            pt_Row           = &Dcm_Dsl_stRow[u2_RowIndex];
            u1_SessionNumMax = Dcm_Dsl_stRow->u1SessionNum;

            if( u1_SessionNumMax == (uint8)0U )
            {
                b_Result = (boolean)TRUE;
            }
            else
            {
                pt_SessionTbl = pt_Row->ptSessionRef;
                for( u1_SessionCnt = (uint8)0U; u1_SessionCnt < u1_SessionNumMax; u1_SessionCnt++ )
                {
                    if( u1_Session == pt_SessionTbl[u1_SessionCnt] )
                    {
                        b_Result = (boolean)TRUE;
                        break;
                    }
                }
            }
        }
    }
    return b_Result;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_ResetToDefaultSession                       */
/* Description   | This function transitions the current session to the     */
/*               | Default session.                                         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Transition Success                         */
/*               |    E_NOT_OK : Transition Failure                         */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsl_Ctrl_ResetToDefaultSession
( void )
{
    uint16         u2_PduMapIndex;
    Std_ReturnType u1_RetVal;
    boolean        b_Active;

    u1_RetVal      = E_NOT_OK;

    b_Active = Dcm_Dsl_Ctrl_IsActiveDiag();
    if( b_Active == (boolean)FALSE )
    {
        u2_PduMapIndex = Dcm_Dsl_Ctrl_GetRxPduMapIndex();
        Dcm_Dsl_Ctrl_SetDefSes(u2_PduMapIndex);
        u1_RetVal = E_OK;
    }

    return u1_RetVal;

}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2022-12-23                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
