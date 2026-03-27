/* Dcm_Dsp_SID10_c(v5-8-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID10/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID10.h>
#if ( DCM_SUPPORT_SID10 == STD_ON )
#include <Dcm/Dcm_Dsp_SID10_Callout.h>
#include "../../Dsp/usr/Dcm_Dsp_SID10_Connector.h"
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include "../../Dsl/inc/Dcm_Dsl_Main.h"
#include <Dcm/Dcm_Dsl_Ctrl.h>
#include <Dcm/Dcm_Main_Common.h>
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dcm/Dcm_Dsp_Main.h>

#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     DCM_DSP_SID10_REQDATA_LEN             ((uint8)0U)

#define     DCM_DSP_SID10_RESDATA_LEN_SET_SPREC   ((uint8)4U)
#define     DCM_DSP_SID10_RESDATA_LEN_NOSET_SPREC ((uint8)0U)
#define     DCM_DSP_SID10_RESDATA_P2_H            ((uint8)0U)
#define     DCM_DSP_SID10_RESDATA_P2_L            ((uint8)1U)
#define     DCM_DSP_SID10_RESDATA_P2S_H           ((uint8)2U)
#define     DCM_DSP_SID10_RESDATA_P2S_L           ((uint8)3U)

#define     DCM_DSP_SID10_RESDATA_SHFT_H          ((uint8)8U)

#define     DCM_DSP_SID10_BOOTSTATE_IDLE          ((uint8)0U)
#define     DCM_DSP_SID10_BOOTSTATE_START         ((uint8)1U)
#define     DCM_DSP_SID10_BOOTSTATE_PENDING       ((uint8)2U)
#define     DCM_DSP_SID10_BOOTSTATE_PROGOK        ((uint8)3U)
#define     DCM_DSP_SID10_BOOTSTATE_RESET         ((uint8)4U)

#define     DCM_DSP_SID10_SID                     ((uint8)0x10U)
#define     DCM_DSP_SID10_SF_REPROG               ((uint8)0x02U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID10_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint8 u1SubFunction
);
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID10_CancelProc
( void );
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID10_RcrrpProc
(
    const uint8 u1SubFunction
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID10_SesCtrlProc
(
    Dcm_OpStatusType u1OpStatus
);
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID10_SetSesCtrlTypeAndChgEcuReset
(
    const uint8 u1SesIndex
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static VAR( Dcm_ProgConditionsType, DCM_VAR_NO_INIT ) Dcm_Dsp_SID10_stProgCond;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_SID10_u1SesIndex;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_SID10_u1BootState;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_SID10_u1SubFunction;

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
/* Function Name | Dcm_Dsp_SID10_Init                                       */
/* Description   | SID 10 initialization                                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID10_Init    /* MISRA DEVIATION */
( void )
{
    Dcm_Dsp_SID10_u1BootState = DCM_DSP_SID10_BOOTSTATE_IDLE;

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID10                                            */
/* Description   | Request processing of SID 10                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus     : Operation state                    */
/*               | [IN] ptMsgContext   : Message Context                    */
/*               | [IN] u1SubFunction  : Sub Function                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID10    /* MISRA DEVIATION */
(
    Dcm_OpStatusType u1OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint8 u1SubFunction
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( u1OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID10_InitialProc( ptMsgContext, u1SubFunction );
    }
    else if( u1OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        Dcm_Dsp_SID10_CancelProc();
    }
    else if( u1OpStatus == (Dcm_OpStatusType)DCM_FORCE_RCRRP_OK )
    {
        u1_RetVal = Dcm_Dsp_SID10_RcrrpProc( u1SubFunction );
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID10_Confirmation                               */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1IdContext     : Id Context                        */
/*               | [IN] u2ConnectionId  : Connection Id                     */
/*               | [IN] u1Status        : Status                            */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID10_Confirmation    /* MISRA DEVIATION */
(
    const Dcm_IdContextType u1IdContext,             /* MISRA DEVIATION */
    const uint16 u2ConnectionId,
    const Dcm_ConfirmationStatusType u1Status
)
{
    uint8 u1_SessionRowNum;
    uint8 u1_SesIndex;
    uint8 u1_SetTiming;
    uint8  u1_SubFunction;
    uint8 u1_SessionLevel;
    uint16 u2_TesterAddress;
    Dcm_OpStatusType u1_OpStatus;
    Std_ReturnType  u1_RetSetProg;

    u1_SessionRowNum = Dcm_P_u1SessionRow_N;
    u1_SubFunction = Dcm_Dsp_SID10_u1SubFunction;
    u2_TesterAddress = (uint16)0U;
    u1_OpStatus = DCM_INITIAL;
    
    if( u1Status == (Dcm_ConfirmationStatusType)DCM_RES_POS_OK )
    {
        /* Positive response success */
        u1_SetTiming = Dcm_P_SID10_u1SessionSetTiming;
        u1_SesIndex = Dcm_Dsp_SID10_u1SesIndex;
        if( u1_SesIndex < u1_SessionRowNum ) /* MISRA DEVIATION */
        {
            if( u1_SetTiming == DCM_DSP_SID10_SETSES_CNF )
            {
                u1_SessionLevel = Dcm_P_SID10_stSessionRow_Tbl[u1_SesIndex].u1Level;
                (void)Dcm_Dsl_SwitchModeSesCtrl( u1_SessionLevel ); /* no return check required */ /* MISRA DEVIATION */
            }
            if( ( Dcm_P_SID10_stSessionRow_Tbl[u1_SesIndex].u1ForBoot == DCM_OEM_BOOT_RESPAPP ) ||
                ( Dcm_P_SID10_stSessionRow_Tbl[u1_SesIndex].u1ForBoot == DCM_SYS_BOOT_RESPAPP ) )
            {
                if( Dcm_Dsp_SID10_u1BootState == DCM_DSP_SID10_BOOTSTATE_START )
                {
                    /* Get ConnectionID & TesterAddress */
                    (void)Dcm_GetActiveProtocol( NULL_PTR, NULL_PTR, &u2_TesterAddress ); /* no return check required */
                    /* Set Dcm_ProgConditionsType */
                    Dcm_Dsp_SID10_stProgCond.ConnectionId       = u2ConnectionId;
                    Dcm_Dsp_SID10_stProgCond.TesterAddress      = u2_TesterAddress;
                    Dcm_Dsp_SID10_stProgCond.Sid                = DCM_DSP_SID10_SID;
                    Dcm_Dsp_SID10_stProgCond.SubFncId           = u1_SubFunction;
                    Dcm_Dsp_SID10_stProgCond.ApplUpdated        = (boolean)FALSE;

                    if( u1_SubFunction == DCM_DSP_SID10_SF_REPROG )
                    {
                        Dcm_Dsp_SID10_stProgCond.ReprogramingRequest = (boolean)TRUE;
                    }
                    else
                    {
                        Dcm_Dsp_SID10_stProgCond.ReprogramingRequest = (boolean)FALSE;
                    }

                    Dcm_Dsp_SID10_stProgCond.ResponseRequired = (boolean)FALSE;

                    /* To store relevant information prior to jumping to bootloader / jump due to ECUReset request. */
                    u1_RetSetProg = Dcm_SetProgConditions( u1_OpStatus, &Dcm_Dsp_SID10_stProgCond );

                    if( u1_RetSetProg == (Std_ReturnType)E_OK )
                    {
                        /* Ecu reset */
                        Dcm_Dsp_SID10_u1BootState = DCM_DSP_SID10_BOOTSTATE_RESET;

                        (void)Dcm_Dsp_SID10_Cnct_Sw_EcuReset( RTE_MODE_DcmEcuReset_EXECUTE ); /* no return check required */
                    }
                    else 
                    {
                        Dcm_Dsp_SID10_u1BootState = DCM_DSP_SID10_BOOTSTATE_IDLE;

                        (void)Dcm_Dsp_SID10_Cnct_Sw_EcuReset( RTE_MODE_DcmEcuReset_NONE ); /* no return check required */
                    }
                }
            }
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID10_Cbk                                        */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID10_Cbk    /* MISRA DEVIATION */
(
    const uint8 u1EventId                   /* MISRA DEVIATION */
)
{
    Std_ReturnType  u1_RetSetProg;
    Dcm_OpStatusType u1_OpStatus;

    u1_OpStatus = DCM_PENDING;

    /* To store relevant information prior to jumping to bootloader / jump due to ECUReset request. */
    u1_RetSetProg = Dcm_SetProgConditions( u1_OpStatus, &Dcm_Dsp_SID10_stProgCond );

    if( u1_RetSetProg == (Std_ReturnType)E_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

        Dcm_Dsp_SID10_u1BootState = DCM_DSP_SID10_BOOTSTATE_PROGOK;
    }
    else if( u1_RetSetProg == (Std_ReturnType)E_NOT_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

        Dcm_Dsp_SID10_u1BootState = DCM_DSP_SID10_BOOTSTATE_IDLE;

        (void)Dcm_Dsp_SID10_Cnct_Sw_EcuReset( RTE_MODE_DcmEcuReset_NONE ); /* no return check required */

        /* NRC0x22 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_CONDITIONSNOTCORRECT );
    }
    else if( u1_RetSetProg == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );

        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID10_SETPROG ); /* no return check required */
    }
    else
    {
        /* No process */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID10_ChkSesCtrlCbk                              */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID10_ChkSesCtrlCbk    /* MISRA DEVIATION */
(
    const uint8 u1EventId                             /* MISRA DEVIATION */
)
{
    Dcm_OpStatusType u1_OpStatus;

    u1_OpStatus = DCM_PENDING;

    (void)Dcm_Dsp_SID10_SesCtrlProc( u1_OpStatus ); /* no return check required */

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_GetP2ServerValue                                 */
/* Description   | Get P2Server Value Information                           */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1SesCtrlType        : SesCtrlType                  */
/*               | [IN] u1ProtocolType       : Protocol type                */
/*               | [OUT] ptP2ServerMax       : P2ServerMax                  */
/*               | [OUT] ptP2StarServerMax   : P2StarServerMax              */
/*               | [OUT] ptP2StarServerLsb   : P2StarServerLsb              */
/*               | [OUT] ptP2StarServerMin   : P2StarServerMin              */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK     : Processing normal                           */
/*               |   E_NOT_OK : Processing abnormal                         */
/* Notes         | This function could be called from other than            */
/*               | Dcm_MainFunction, so use exclusive control if setting    */
/*               | or referencing RAM.                                      */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_GetP2ServerValue
(
    const Dcm_SesCtrlType u1SesCtrlType,
    const Dcm_ProtocolType u1ProtocolType,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptP2ServerMax,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptP2StarServerMax,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptP2StarServerLsb,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptP2StarServerMin
)
{
    uint8   u1_SesIndex;
    uint8   u1_SessionRowNum;
    Std_ReturnType u1_RetVal;
    boolean b_SerchHit;
    boolean b_SupProtocolInfo;

    u1_RetVal = E_NOT_OK;
    u1_SessionRowNum = Dcm_P_u1SessionRow_N;
    b_SerchHit = (boolean)FALSE;
    b_SupProtocolInfo = Dcm_P_SID10_bSupportProtocolInfo;

    if( b_SupProtocolInfo == (boolean)TRUE )
    {
        for( u1_SesIndex = (uint8)0U; u1_SesIndex <= u1_SessionRowNum; u1_SesIndex++ )
        {
            if( u1SesCtrlType == (Dcm_SesCtrlType)Dcm_P_SID10_stSessionRow_Tbl[u1_SesIndex].u1Level )
            {
                if( u1ProtocolType == Dcm_P_SID10_stSessionRow_Tbl[u1_SesIndex].u1ProtocolType )
                {
                    b_SerchHit = (boolean)TRUE;
                    break;
                }
            }
        }
    }
    else
    {
        for( u1_SesIndex = (uint8)0U; u1_SesIndex <= u1_SessionRowNum; u1_SesIndex++ )
        {
            if( u1SesCtrlType == (Dcm_SesCtrlType)Dcm_P_SID10_stSessionRow_Tbl[u1_SesIndex].u1Level )
            {
                b_SerchHit = (boolean)TRUE;
                break;
            }
        }
    }

    if( b_SerchHit == (boolean)TRUE )
    {
        if( ptP2ServerMax != NULL_PTR )
        {
            *ptP2ServerMax = Dcm_P_SID10_stSessionRow_Tbl[u1_SesIndex].u2P2ServerMax;
        }
        if( ptP2StarServerMax != NULL_PTR )
        {
            *ptP2StarServerMax = Dcm_P_SID10_stSessionRow_Tbl[u1_SesIndex].u2P2StarServerMax;
        }
        if( ptP2StarServerLsb != NULL_PTR )
        {
            *ptP2StarServerLsb = Dcm_P_SID10_stSessionRow_Tbl[u1_SesIndex].u2P2StarServerLsb;
        }
        if( ptP2StarServerMin != NULL_PTR )
        {
            *ptP2StarServerMin = Dcm_P_SID10_stSessionRow_Tbl[u1_SesIndex].u2P2StarServerTimeoutMin;
        }
        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID10_InitialProc                                */
/* Description   | Initial process of SID 10 request                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext : Message Context                      */
/*               | [IN] u1SubFunction  : Sub Function                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID10_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const uint8 u1SubFunction
)
{
    Std_ReturnType  u1_RetVal;
    Dcm_OpStatusType  u1_OpStatus;

    u1_RetVal = E_OK;
    u1_OpStatus = DCM_INITIAL;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    Dcm_Dsp_SID10_u1BootState = DCM_DSP_SID10_BOOTSTATE_IDLE;

    /* Save message context */
    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    Dcm_Dsp_SID10_u1SesIndex = Dcm_P_u1SessionRow_N;
    Dcm_Dsp_SID10_u1SubFunction = u1SubFunction;

    /* Check request message length */
    if( ptMsgContext->reqDataLen == DCM_DSP_SID10_REQDATA_LEN )
    {
        u1_RetVal = Dcm_Dsp_SID10_SesCtrlProc( u1_OpStatus );
    }
    else
    {
        /* NRC0x13 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID10_CancelProc                                 */
/* Description   | Cancel process of SID 31 request                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID10_CancelProc
( void )
{
    uint8 u1_SessionRowNum;
    uint8 u1_SesIndex;
    Dcm_NegativeResponseCodeType u1_ErrorCode;
    Dcm_OpStatusType u1_OpStatus;
    boolean b_UserNotifyFlag;

    u1_SesIndex = Dcm_Dsp_SID10_u1SesIndex;
    u1_SessionRowNum = Dcm_P_u1SessionRow_N;
    u1_ErrorCode = (Dcm_NegativeResponseCodeType)0x00U;
    u1_OpStatus = DCM_CANCEL;

    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();

    if( b_UserNotifyFlag == (boolean)TRUE )
    {
        (void)Dcm_Dsp_SID10_CheckSesCtrl( Dcm_Dsp_SID10_u1SubFunction, u1_OpStatus, &u1_ErrorCode ); /* no return check required */

        if( u1_SesIndex < u1_SessionRowNum ) /* MISRA DEVIATION */
        {
            if( Dcm_P_SID10_stSessionRow_Tbl[u1_SesIndex].u1ForBoot != DCM_NO_BOOT ) /* MISRA DEVIATION */
            {
                if( Dcm_Dsp_SID10_u1BootState == DCM_DSP_SID10_BOOTSTATE_PENDING )
                {
                    (void)Dcm_SetProgConditions( u1_OpStatus, &Dcm_Dsp_SID10_stProgCond ); /* no return check required */
                }
            }
        }

        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
            
    }

    if( u1_SesIndex < u1_SessionRowNum ) /* MISRA DEVIATION */
    {
        if( Dcm_P_SID10_stSessionRow_Tbl[u1_SesIndex].u1ForBoot != DCM_NO_BOOT ) /* MISRA DEVIATION */
        {
            if( ( Dcm_Dsp_SID10_u1BootState == DCM_DSP_SID10_BOOTSTATE_START   ) ||
                ( Dcm_Dsp_SID10_u1BootState == DCM_DSP_SID10_BOOTSTATE_PENDING ) )
            {
                Dcm_Dsp_SID10_u1BootState = DCM_DSP_SID10_BOOTSTATE_IDLE;

                (void)Dcm_Dsp_SID10_Cnct_Sw_EcuReset( RTE_MODE_DcmEcuReset_NONE ); /* no return check required */
            }
        }
    }

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID10_CHKSESCTRL, (boolean)FALSE ); /* no return check required */
    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID10_SETPROG, (boolean)FALSE ); /* no return check required */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID10_RcrrpProc                                  */
/* Description   | Cancel process of SID 31 request                         */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1SubFunction  : Sub Function                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID10_RcrrpProc
(
    const uint8 u1SubFunction
)
{
    boolean b_NrcFlag;
    Std_ReturnType  u1_RetVal;
    Std_ReturnType  u1_RetSetProg;
    Dcm_NegativeResponseCodeType u1_ErrorCode;
    uint16 u2_ConnectionId;
    uint16 u2_TesterAddress;
    Dcm_OpStatusType u1_OpStatus;
    
    u1_RetVal = E_OK;
    b_NrcFlag = (boolean)FALSE;
    u2_ConnectionId  = (uint16)0U;
    u2_TesterAddress = (uint16)0U;
    u1_OpStatus = DCM_INITIAL;

    if( Dcm_Dsp_SID10_u1BootState == DCM_DSP_SID10_BOOTSTATE_START )
    {
        /* Get ConnectionID & TesterAddress */
        (void)Dcm_GetActiveProtocol( NULL_PTR, &u2_ConnectionId, &u2_TesterAddress ); /* no return check required */
        /* Set Dcm_ProgConditionsType */
        Dcm_Dsp_SID10_stProgCond.ConnectionId       = u2_ConnectionId;
        Dcm_Dsp_SID10_stProgCond.TesterAddress      = u2_TesterAddress;
        Dcm_Dsp_SID10_stProgCond.Sid                = DCM_DSP_SID10_SID;
        Dcm_Dsp_SID10_stProgCond.SubFncId           = u1SubFunction;
        Dcm_Dsp_SID10_stProgCond.ApplUpdated        = (boolean)FALSE;

        if( u1SubFunction == DCM_DSP_SID10_SF_REPROG )
        {
            Dcm_Dsp_SID10_stProgCond.ReprogramingRequest = (boolean)TRUE;
        }
        else
        {
            Dcm_Dsp_SID10_stProgCond.ReprogramingRequest = (boolean)FALSE;
        }

        Dcm_Dsp_SID10_stProgCond.ResponseRequired = (boolean)TRUE;

        /* To store relevant information prior to jumping to bootloader / jump due to ECUReset request. */
        u1_RetSetProg = Dcm_SetProgConditions( u1_OpStatus, &Dcm_Dsp_SID10_stProgCond );

        if( u1_RetSetProg == (Std_ReturnType)E_OK )
        {
            /* Ecu reset */
            Dcm_Dsp_SID10_u1BootState = DCM_DSP_SID10_BOOTSTATE_RESET;

            (void)Dcm_Dsp_SID10_Cnct_Sw_EcuReset( RTE_MODE_DcmEcuReset_EXECUTE ); /* no return check required */
        }
        else if( u1_RetSetProg == (Std_ReturnType)E_NOT_OK )
        {
            Dcm_Dsp_SID10_u1BootState = DCM_DSP_SID10_BOOTSTATE_IDLE;

            (void)Dcm_Dsp_SID10_Cnct_Sw_EcuReset( RTE_MODE_DcmEcuReset_NONE ); /* no return check required */

            /* NRC0x22 */
            b_NrcFlag = (boolean)TRUE;
            u1_ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
        }
        else if( u1_RetSetProg == (Std_ReturnType)DCM_E_PENDING )
        {
            u1_RetVal = DCM_E_PENDING;

            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );

            Dcm_Dsp_SID10_u1BootState = DCM_DSP_SID10_BOOTSTATE_PENDING;

            /* NRC0x78 */
            b_NrcFlag = (boolean)TRUE;
            u1_ErrorCode = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;

            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID10_SETPROG ); /* no return check required */
        }
        else
        {
            /* No process */
        }
    }
    else if( Dcm_Dsp_SID10_u1BootState == DCM_DSP_SID10_BOOTSTATE_PENDING )
    {
        /* NRC0x78 */
        b_NrcFlag = (boolean)TRUE;
        u1_ErrorCode = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
    }
    else if( Dcm_Dsp_SID10_u1BootState == DCM_DSP_SID10_BOOTSTATE_PROGOK )
    {
        /* Ecu reset */
        Dcm_Dsp_SID10_u1BootState = DCM_DSP_SID10_BOOTSTATE_RESET;

        (void)Dcm_Dsp_SID10_Cnct_Sw_EcuReset( RTE_MODE_DcmEcuReset_EXECUTE ); /* no return check required */
    }
    else
    {
        /* No process */
    }


    if( b_NrcFlag == (boolean)TRUE )
    {
        /* Negative response */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID10_SesCtrlProc                                */
/* Description   | Pre-check of session control, execution processing       */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus     : Operation state                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID10_SesCtrlProc
(
    Dcm_OpStatusType u1OpStatus
)
{
    uint8   u1_SesIndex;
    uint8   u1_SessionRowNum;
    uint8   u1_SubFunction;
    Std_ReturnType  u1_RetVal;
    Std_ReturnType  u1_RetCheck;
    Dcm_NegativeResponseCodeType u1_ErrorCode;
    Dcm_ProtocolType u1_ActiveProtocolType;
    boolean b_IndexFlag;
    boolean b_NoSetSPREC;
    boolean b_NrcFlag;
    boolean b_SupProtocolInfo;

    u1_RetVal = E_OK;
    b_NrcFlag = (boolean)FALSE;
    u1_SessionRowNum = Dcm_P_u1SessionRow_N;
    u1_ErrorCode = (Dcm_NegativeResponseCodeType)0x00U;
    u1_SubFunction = Dcm_Dsp_SID10_u1SubFunction;

    u1_RetCheck = Dcm_Dsp_SID10_CheckSesCtrl( u1_SubFunction, u1OpStatus, &u1_ErrorCode );

    if( u1_RetCheck == (Std_ReturnType)E_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

        /* Get session index */
        b_IndexFlag = (boolean)FALSE;
        b_SupProtocolInfo = Dcm_P_SID10_bSupportProtocolInfo;
        if( b_SupProtocolInfo == (boolean)TRUE )
        {
            u1_ActiveProtocolType = DCM_NO_ACTIVE_PROTOCOL;
            /* Get ActiveProtocolType */
            Dcm_Dsl_GetActiveProtocol( &u1_ActiveProtocolType, NULL_PTR, NULL_PTR );
            for( u1_SesIndex = (uint8)0U; u1_SesIndex <= u1_SessionRowNum; u1_SesIndex++ )
            {
                if( u1_SubFunction == Dcm_P_SID10_stSessionRow_Tbl[u1_SesIndex].u1Level )
                {
                    if( u1_ActiveProtocolType == Dcm_P_SID10_stSessionRow_Tbl[u1_SesIndex].u1ProtocolType )
                    {
                        Dcm_Dsp_SID10_u1SesIndex = u1_SesIndex;
                        b_IndexFlag = (boolean)TRUE;
                        break;
                    }
                }
            }
        }
        else
        {
            for( u1_SesIndex = (uint8)0U; u1_SesIndex <= u1_SessionRowNum; u1_SesIndex++ )
            {
                if( u1_SubFunction == Dcm_P_SID10_stSessionRow_Tbl[u1_SesIndex].u1Level )
                {
                    Dcm_Dsp_SID10_u1SesIndex = u1_SesIndex;
                    b_IndexFlag = (boolean)TRUE;
                    break;
                }
            }
        }

        if( b_IndexFlag == (boolean)TRUE )
        {
            if( ( Dcm_P_SID10_stSessionRow_Tbl[u1_SesIndex].u1ForBoot == DCM_NO_BOOT ) || 
                ( Dcm_P_SID10_stSessionRow_Tbl[u1_SesIndex].u1ForBoot == DCM_OEM_BOOT_RESPAPP ) ||
                ( Dcm_P_SID10_stSessionRow_Tbl[u1_SesIndex].u1ForBoot == DCM_SYS_BOOT_RESPAPP ) )
            {
                /* Not boot jump or Boot jump(RESPAPP) */
                b_NoSetSPREC = Dcm_P_SID10_bNoSetSPREC;
                if( b_NoSetSPREC == (boolean)TRUE )
                {
                    Dcm_Dsp_SID10_SetSesCtrlTypeAndChgEcuReset( u1_SesIndex );

                    Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID10_RESDATA_LEN_NOSET_SPREC;

                    /* Positive response */
                    Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
                }
                else
                {
                    /* Check response message length */
                    if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= DCM_DSP_SID10_RESDATA_LEN_SET_SPREC )
                    {
                        Dcm_Dsp_SID10_SetSesCtrlTypeAndChgEcuReset( u1_SesIndex );

                        /* Set positive response message */
                        Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID10_RESDATA_P2_H]  = (uint8)( Dcm_P_SID10_stSessionRow_Tbl[u1_SesIndex].u2P2ServerMax >> DCM_DSP_SID10_RESDATA_SHFT_H );
                        Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID10_RESDATA_P2_L]  = (uint8)( Dcm_P_SID10_stSessionRow_Tbl[u1_SesIndex].u2P2ServerMax );

                        Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID10_RESDATA_P2S_H] = (uint8)( Dcm_P_SID10_stSessionRow_Tbl[u1_SesIndex].u2P2StarServerLsb >> DCM_DSP_SID10_RESDATA_SHFT_H );
                        Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID10_RESDATA_P2S_L] = (uint8)( Dcm_P_SID10_stSessionRow_Tbl[u1_SesIndex].u2P2StarServerLsb );

                        Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID10_RESDATA_LEN_SET_SPREC;

                        /* Positive response */
                        Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
                    }
                }
            }
            else
            {
                /* Boot jump */

                Dcm_Dsp_SID10_u1BootState = DCM_DSP_SID10_BOOTSTATE_START;

                /* Change DcmEcuReset mode */
                if( Dcm_P_SID10_stSessionRow_Tbl[u1_SesIndex].u1ForBoot == DCM_OEM_BOOT )
                {
                    (void)Dcm_Dsp_SID10_Cnct_Sw_EcuReset( RTE_MODE_DcmEcuReset_JUMPTOBOOTLOADER ); /* no return check required */
                }
                else
                {
                    (void)Dcm_Dsp_SID10_Cnct_Sw_EcuReset( RTE_MODE_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER ); /* no return check required */
                }

                /* NRC0x78 */
                b_NrcFlag = (boolean)TRUE;
                u1_ErrorCode = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
            }
        }
        else
        {
            b_NrcFlag = (boolean)TRUE;
            u1_ErrorCode = DCM_E_GENERALREJECT;
        }
    }
    else if( u1_RetCheck == (Std_ReturnType)E_NOT_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

        b_NrcFlag = (boolean)TRUE;
    }
    else if( u1_RetCheck == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );

        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID10_CHKSESCTRL );            /* no return check required */
        u1_RetVal = DCM_E_PENDING;
    }
    else
    {
        /* No process */
    }

    if( b_NrcFlag == (boolean)TRUE )
    {
        /* Negative response */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID10_SetSesCtrlTypeAndChgEcuReset               */
/* Description   | set a session control type, change DcmEcuReset mode      */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1SesIndex     : SessionRow Index                   */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID10_SetSesCtrlTypeAndChgEcuReset
(
    const uint8 u1SesIndex
)
{
    uint8   u1_SetTiming;
    uint8   u1_SessionLevel;

    u1_SetTiming = Dcm_P_SID10_u1SessionSetTiming;
    u1_SessionLevel = Dcm_P_SID10_stSessionRow_Tbl[u1SesIndex].u1Level;
    if( u1_SetTiming == DCM_DSP_SID10_SETSES_IND )
    {
        DslInternal_SetSesCtrlType( u1_SessionLevel, (boolean)FALSE );
        (void)Dcm_Dsl_SwitchModeSesCtrl( u1_SessionLevel ); /* no return check required */
    }
    else
    {
        DslInternal_SetSesCtrlType( u1_SessionLevel, (boolean)TRUE );
    }
    /* Change DcmEcuReset mode */
    if( Dcm_P_SID10_stSessionRow_Tbl[u1SesIndex].u1ForBoot == DCM_OEM_BOOT_RESPAPP )
    {
        Dcm_Dsp_SID10_u1BootState = DCM_DSP_SID10_BOOTSTATE_START;
        (void)Dcm_Dsp_SID10_Cnct_Sw_EcuReset( RTE_MODE_DcmEcuReset_JUMPTOBOOTLOADER ); /* no return check required */
    }
    else if( Dcm_P_SID10_stSessionRow_Tbl[u1SesIndex].u1ForBoot == DCM_SYS_BOOT_RESPAPP )
    {
        Dcm_Dsp_SID10_u1BootState = DCM_DSP_SID10_BOOTSTATE_START;
        (void)Dcm_Dsp_SID10_Cnct_Sw_EcuReset( RTE_MODE_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER ); /* no return check required */
    }
    else
    {
        /* No process */
    }

    return;
}


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID10 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-07-27                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
