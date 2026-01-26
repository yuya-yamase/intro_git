/* Dcm_Dsl_SessionMng_c(v5-3-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsl_SessionMng/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsl_Ctrl.h>
#include "../../Dsl/inc/Dcm_Dsl_SessionMng.h"
#include "../../Dsl/usr/Dcm_Dsl_SessionMng_Connector.h"

#include "../../Dsl/inc/Dcm_Dsl_Ctrl_local.h"
#include "../../Dsl/inc/Dcm_Dsl_Main.h"
#include "../../Dsl/inc/Dcm_Dsl_SecurityMng.h"

#include <Dcm.h>
#include <SchM_Dcm.h>

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

static FUNC(void, DCM_CODE) Dcm_Dsl_SessionMng_IndicateSesCtrlChange
(
    const Dcm_SesCtrlType u1SesCtrlTypeOld,
    const Dcm_SesCtrlType u1SesCtrlTypeNew
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static VAR(volatile Dcm_SesCtrlType, DCM_VAR_NO_INIT) Dcm_Dsl_u1Session;
static VAR(Dcm_SesCtrlType, DCM_VAR_NO_INIT) Dcm_Dsl_u1PreSession;
static VAR(Dcm_SesCtrlType, DCM_VAR_NO_INIT) Dcm_Dsl_u1PostSession;
static VAR(uint8, DCM_VAR_NO_INIT)           Dcm_Dsl_u1SesChgKind;

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
/* Function Name | Dcm_Dsl_SessionMng_Init                                  */
/* Description   | This function initializes Dsl_SessionMng.                */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_SessionMng_Init
(void)
{
    Dcm_Dsl_u1Session      = DCM_DEFAULT_SESSION;
    Dcm_Dsl_u1PreSession   = DCM_DEFAULT_SESSION;
    Dcm_Dsl_u1PostSession  = DCM_DEFAULT_SESSION;
    Dcm_Dsl_u1SesChgKind   = DCM_DSL_SESCHG_KIND_NONE;
    return ;
}

#if( DCM_M_RESPONSE_AFTER_REBOOT == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_SessionMng_SetInitialSession                     */
/* Description   | This function sets the initial session.                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1SesCtrlType : new session control type value      */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_SessionMng_SetInitialSession
(
    const Dcm_SesCtrlType u1SesCtrlType
)
{
    Dcm_Dsl_u1Session = u1SesCtrlType;
    return ;
}
#endif /* DCM_M_RESPONSE_AFTER_REBOOT == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_SessionMng_GetSesCtrlType                        */
/* Description   | This function provides the active session control type - */
/*               | value.                                                   */
/* Preconditions |                                                          */
/* Parameters    | [out] ptSesCtrlType :                                    */
/*               |        Active Session Control Type value Content is acc- */
/*               |        ording to "diagnosticSessionType" parameter of D- */
/*               |        iagnosticSessionControl request                   */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : this value is always returned.             */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_SessionMng_GetSesCtrlType
(
    P2VAR(Dcm_SesCtrlType, AUTOMATIC, DCM_APPL_DATA) ptSesCtrlType
)
{
    /* lock */
    SchM_Enter_Dcm_Dsl_Session();

    *ptSesCtrlType = Dcm_Dsl_u1Session;

    /* unlock */
    SchM_Exit_Dcm_Dsl_Session();

    return E_OK;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_SessionMng_SetSesCtrlType                        */
/* Description   | This function sets a new session control type value      */
/*               | in the DCM Component.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1SesCtrlType : new session control type value      */
/*               | [in] bDelayUpdate  : TRUE : Confirmation Reception timing*/
/*               |                     FALSE : Immediate                    */
/*               | [in] u1SesChgKind : session change kind                  */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_SessionMng_SetSesCtrlType
(
    const Dcm_SesCtrlType u1SesCtrlType,
    const boolean bDelayUpdate,
    const uint8 u1SesChgKind
)
{
    boolean b_SecurityLockOnlyDefSes;

    if( bDelayUpdate == (boolean)TRUE )
    {
        /* lock */
        SchM_Enter_Dcm_Dsl_Session();

        Dcm_Dsl_u1PostSession = u1SesCtrlType;
        Dcm_Dsl_u1PreSession  = Dcm_Dsl_u1Session;

        if( u1SesChgKind == DCM_DSL_SESCHG_KIND_EXTERNAL )
        {
            Dcm_Dsl_u1SesChgKind  = DCM_DSL_SESCHG_KIND_DM_OFF;
        }
        else
        {
            Dcm_Dsl_u1SesChgKind  = DCM_DSL_SESCHG_KIND_DM_ON;
        }

        /* unlock */
        SchM_Exit_Dcm_Dsl_Session();
    }
    else
    {
        /* lock */
        SchM_Enter_Dcm_Dsl_Session();

        Dcm_Dsl_u1PreSession  = Dcm_Dsl_u1Session;
        Dcm_Dsl_u1PostSession = u1SesCtrlType;
        Dcm_Dsl_u1Session     = u1SesCtrlType;
        Dcm_Dsl_u1SesChgKind  = DCM_DSL_SESCHG_KIND_NONE;

        /* unlock */
        SchM_Exit_Dcm_Dsl_Session();

        b_SecurityLockOnlyDefSes = Dcm_Dsl_bSecLockOnlyDefSes;
        if( b_SecurityLockOnlyDefSes == (boolean)TRUE )
        {
            if( Dcm_Dsl_u1PostSession == DCM_DEFAULT_SESSION )
            {
                DslInternal_SetSecurityLevel(DCM_SEC_LEV_LOCKED);
            }
        }
        else
        {
            DslInternal_SetSecurityLevel(DCM_SEC_LEV_LOCKED);
        }

        Dcm_Dsl_SessionMng_IndicateSesCtrlChange(Dcm_Dsl_u1PreSession, u1SesCtrlType);
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_SessionMng_SwitchModeSesCtrl                     */
/* Description   | This function changes DcmDiagnosticSessionControl mode   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1Mode         : Next mode                          */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : failure                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsl_SessionMng_SwitchModeSesCtrl
(
    const uint8 u1Mode
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = Dcm_Dsl_Cnct_Switch_SesCtrl(u1Mode);

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_SessionMng_SetSesConf                            */
/* Description   | This function sets a new session control type value      */
/*               | in the DCM Dcm_TpTxConfirmation.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] bUpdateEnable :  TRUE : Session Update Enable       */
/*               |                      FALSE : Session Update Disable      */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_SessionMng_SetSesConf
(
    const boolean bUpdateEnable
)
{
    /* lock */
    SchM_Enter_Dcm_Dsl_Session();

    if( bUpdateEnable == (boolean)TRUE )
    {
        if( ( Dcm_Dsl_u1SesChgKind == DCM_DSL_SESCHG_KIND_DM_OFF )
         || ( Dcm_Dsl_u1SesChgKind == DCM_DSL_SESCHG_KIND_DM_ON ) )
        {
            Dcm_Dsl_u1Session = Dcm_Dsl_u1PostSession;
        }
        else  /* Dcm_Dsl_u1SesChgKind == DCM_DSL_SESCHG_KIND_NONE */
        {
            /* No Process */
        }
    }
    else
    {
        Dcm_Dsl_u1SesChgKind = DCM_DSL_SESCHG_KIND_NONE;
    }

    /* unlock */
    SchM_Exit_Dcm_Dsl_Session();
    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_SessionMng_ReqSesCtrlChgNotification             */
/* Description   | This function sets a new security level(lock) value and  */
/*               | notifies SW-C of the change of the session in the        */
/*               | Dcm_Dsl_DataConfFunctionalityCbk.                        */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_SessionMng_ReqSesCtrlChgNotification
(void)
{
    boolean b_SecurityLockOnlyDefSes;

    b_SecurityLockOnlyDefSes = Dcm_Dsl_bSecLockOnlyDefSes;

    if( Dcm_Dsl_u1SesChgKind == DCM_DSL_SESCHG_KIND_DM_OFF )
    {
        if( b_SecurityLockOnlyDefSes == (boolean)TRUE )
        {
            if( Dcm_Dsl_u1PostSession == DCM_DEFAULT_SESSION )
            {
                DslInternal_SetSecurityLevel(DCM_SEC_LEV_LOCKED);
            }
        }
        else
        {
            DslInternal_SetSecurityLevel(DCM_SEC_LEV_LOCKED);
        }
        Dcm_Dsl_SessionMng_IndicateSesCtrlChange(Dcm_Dsl_u1PreSession, Dcm_Dsl_u1PostSession);
        Dcm_Dsl_u1SesChgKind  = DCM_DSL_SESCHG_KIND_NONE;
    }
    else if( Dcm_Dsl_u1SesChgKind == DCM_DSL_SESCHG_KIND_DM_ON )
    {
        if( b_SecurityLockOnlyDefSes == (boolean)TRUE )
        {
            if( Dcm_Dsl_u1PostSession == DCM_DEFAULT_SESSION )
            {
                DslInternal_SetSecurityLevel(DCM_SEC_LEV_LOCKED);
            }
        }
        else
        {
            DslInternal_SetSecurityLevel(DCM_SEC_LEV_LOCKED);
        }
        Dcm_Dsl_SessionMng_IndicateSesCtrlChange(Dcm_Dsl_u1PreSession, Dcm_Dsl_u1PostSession);
        /* no return check required */
        (void)Dcm_Dsl_Cnct_Switch_SesCtrl(Dcm_Dsl_u1PostSession);
        Dcm_Dsl_u1SesChgKind  = DCM_DSL_SESCHG_KIND_NONE;
    }
    else
    {
        /* No Process */
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsl_SessionMng_Refresh                               */
/* Description   | This function refresh active session control type value. */
/* Preconditions | The user must exclude this access data.                  */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_SessionMng_Refresh
(void)
{
    Dcm_SesCtrlType u1_SesCtrlType;
    P2VAR(volatile Dcm_SesCtrlType, AUTOMATIC, DCM_APPL_DATA) pt_SesCtrlType;

    pt_SesCtrlType  = &Dcm_Dsl_u1Session;
    u1_SesCtrlType  = *pt_SesCtrlType;
    *pt_SesCtrlType = u1_SesCtrlType;
    return ;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsl_SessionMng_IndicateSesCtrlChange                 */
/* Description   | This function notifies SW-C of the change of the session */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1SesCtrlTypeOld : old session control type value   */
/*               | [in] u1SesCtrlTypeNew : new session control type value   */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsl_SessionMng_IndicateSesCtrlChange
(
    const Dcm_SesCtrlType u1SesCtrlTypeOld,
    const Dcm_SesCtrlType u1SesCtrlTypeNew
)
{
    uint8 u1_Count;
    uint8 u1_IndSesChgNumMax;

    u1_IndSesChgNumMax = Dcm_Dsl_u1IndSesChgNum;

    for( u1_Count = (uint8)0U; u1_Count < u1_IndSesChgNumMax; u1_Count++ )
    {
#ifndef JGXSTACK

        Dcm_Dsl_IndSesCtrlChgTable[u1_Count](u1SesCtrlTypeOld, u1SesCtrlTypeNew);

#else   /* JGXSTACK */

        Dcm_Stack_IndSesCtrlChgFunc(u1SesCtrlTypeOld, u1SesCtrlTypeNew);

#endif  /* JGXSTACK */
    }

    /* Return value ignoring */
    (void)Dcm_Dsl_IndicateSesCtrlChange(u1SesCtrlTypeOld, u1SesCtrlTypeNew);
    return ;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2022-08-30                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
