/* Dcm_Dsl_Ctrl_SecSrv_c(v5-5-0)                                            */
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

#include "../../Dsl/inc/Dcm_Dsl_SecurityMng.h"
#include "../../Dsl/inc/Dcm_Dsl_AuthMng.h"
#include "../../Dsl/cfg/Dcm_Dsl_Main_Cfg.h"

#include <Dcm/Dcm_Main_TmrSrv.h>
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
/* Function Name | Dcm_GetSecurityLevel                                     */
/* Description   | Call the function(Dcm_Dsl_SecurityMng_GetSecurityLevel)  */
/*               | to get the active security level value.                  */
/* Preconditions | -                                                        */
/* Parameters    | [out] SecLevel :                                         */
/*               |        Active Security Level value Conversion formula t- */
/*               |        o calculate SecurityLevel out of tester requeste- */
/*               |        d SecurityAccessType parameter: SecurityLevel = - */
/*               |        (SecurityAccessType + 1) / 2 Content of Security- */
/*               |        AccessType is according to "securityAccessType" - */
/*               |        parameter of SecurityAccess request               */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK: : this value is always returned.            */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_GetSecurityLevel
(
    P2VAR( Dcm_SecLevelType, AUTOMATIC, DCM_APPL_DATA ) SecLevel
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( SecLevel != NULL_PTR )
    {
        u1_RetVal = Dcm_Dsl_SecurityMng_GetSecurityLevel(SecLevel);
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;

}

/****************************************************************************/
/* Function Name | DslInternal_SetSecurityLevel                             */
/* Description   | Call the function(Dcm_Dsl_SecurityMng_SetSecurityLevel)  */
/*               | to set the active security level value.                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] SecurityLevel : active security level value         */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) DslInternal_SetSecurityLevel
(
    Dcm_SecLevelType SecurityLevel
)
{
    Dcm_Dsl_SecurityMng_SetSecurityLevel(SecurityLevel);

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_GetAuthState                                     */
/* Description   | This function gets the authentication status of          */
/*               | the active connection.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [In]  u2ConnectionId  : Connection ID(ClientIndex)       */
/*               |                                                          */
/* Return Value  | uint8                                                    */
/*               |   DCM_AUTHENTICATED   : authenticated                    */
/*               |   DCM_DEAUTHENTICATED : deauthenticated                  */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_AUTHENTICATION_USE == STD_ON )
#if( DCM_AUTHENTICATION_INTERNAL_USE == STD_ON )
FUNC( uint8, DCM_CODE ) Dcm_Dsl_GetAuthState
(
    const uint16 u2ConnectionId
)
{
    uint8 u1_Authenticated;
    Dcm_Dsl_AuthMng_GetAuthState(u2ConnectionId, &u1_Authenticated);

    return u1_Authenticated;
}
#endif /* DCM_AUTHENTICATION_INTERNAL_USE == STD_ON */
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_SetAuthState                                     */
/* Description   | This function sets the authentication status of          */
/*               | the active connection.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1Authenticated : authenticated/deauthenticated     */
/*               | [In] u2ConnectionId : Connection ID(ClientIndex)         */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_AUTHENTICATION_USE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_SetAuthState
(
    const uint8 u1Authenticated,
    const uint16 u2ConnectionId
)
{
    Dcm_Dsl_AuthMng_SetAuthState(u1Authenticated, u2ConnectionId, (boolean)TRUE);
    return;
}
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_SetAuthenticate                                  */
/* Description   | This function sets the authentication status at the      */
/*               | time of initialization.                                  */
/* Preconditions | none                                                     */
/* Parameters    | [In] u2ConnectionId : Connection ID(ClientIndex)         */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_NVM_AUTHENTICATION_USE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_SetAuthenticate
(
    const uint16 u2ConnectionId
)
{
    Dcm_Dsl_AuthMng_SetAuthState(DCM_AUTHENTICATED, u2ConnectionId, (boolean)FALSE);
    Dcm_Dsl_Ctrl_StartAuthTimer(u2ConnectionId);

    return;
}
#endif /* DCM_NVM_AUTHENTICATION_USE == STD_ON */

#if( DCM_AUTHENTICATION_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_isClientAuthenticated                       */
/* Description   | check if the authentication status of the specified      */
/*               | connection is authenticated or not                       */
/* Preconditions | none                                                     */
/* Parameters    | [In]  u2ConnectionId  : Connection ID(ClientIndex)       */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |   TRUE   : authenticated                                 */
/*               |   FALSE  : deauthenticated                               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_isClientAuthenticated
(
    const uint16 u2ConnectionId
)
{
    uint8 u1_Authenticated;
    boolean b_Result;
    
    u1_Authenticated = DCM_DEAUTHENTICATED;
    b_Result = (boolean)FALSE;

    Dcm_Dsl_AuthMng_GetAuthState(u2ConnectionId, &u1_Authenticated);

    if (u1_Authenticated == DCM_AUTHENTICATED)
    {
        b_Result = (boolean)TRUE;
    }

    return b_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_isAuthTimerRunning                          */
/* Description   | Check if the authentication timer of the specified       */
/*               | connection is runninng or not                            */
/* Preconditions | none                                                     */
/* Parameters    | [In]  u2ConnectionId  : Connection ID(ClientIndex)       */
/*               |                                                          */
/* Return Value  | boolean                                                  */
/*               |   TRUE                : running                          */
/*               |   FALSE               : stopped                          */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsl_Ctrl_isAuthTimerRunning
(
    const uint16 u2ConnectionId
)
{
    Std_ReturnType u1_RetGetTimerState;
    uint8   u1_TimerId;
    uint8   u1_TimerState;
    boolean b_Result;

    b_Result = (boolean)FALSE;
    
    u1_TimerId    = Dcm_Dsl_u1AuthClientBase + (uint8)u2ConnectionId;
    u1_TimerState = (uint8)STD_OFF;
    u1_RetGetTimerState = Dcm_Main_TmrSrv_GetTimerState(u1_TimerId, &u1_TimerState);

    if( u1_RetGetTimerState ==  (Std_ReturnType)E_OK)
    {
        if( u1_TimerState == (uint8)STD_ON)
        {
            b_Result = (boolean)TRUE;
        }
    }

    return b_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_StartAuthTimer                              */
/* Description   | Start the authentication timer for                       */
/*               | the specified connection                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2ConnectionId : Connection ID(ClientIndex)         */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_StartAuthTimer
(
    const uint16 u2ConnectionId
)
{
    uint32  u4_AuthTimerValue;
    uint8   u1_TimerId;

    u1_TimerId        = Dcm_Dsl_u1AuthClientBase + (uint8)u2ConnectionId;
    u4_AuthTimerValue = Dcm_Dsl_u4AuthTimerValue;
    Dcm_Main_TmrSrv_StartTimer(u1_TimerId, u4_AuthTimerValue);

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_StopAuthTimer                               */
/* Description   | Stop the authentication timer for                        */
/*               | the specified connection                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] u2ConnectionId : Connection ID(ClientIndex)         */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_StopAuthTimer
(
    const uint16 u2ConnectionId
)
{
    uint8 u1_TimerId;

    u1_TimerId = Dcm_Dsl_u1AuthClientBase + (uint8)u2ConnectionId;
    Dcm_Main_TmrSrv_StopTimer(u1_TimerId);
    
    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_StopAuthAllTimers                           */
/* Description   | This function stops all authentication timers.           */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_StopAuthAllTimers
( void )
{
    uint16  u2_ClientCnt;
    uint16  u2_ClientNumMax;
    uint8   u1_TimerId;

    u2_ClientNumMax = Dcm_Dsl_u2ClientNum;
    for( u2_ClientCnt = (uint16)0U; u2_ClientCnt < u2_ClientNumMax; u2_ClientCnt++ )
    {
        u1_TimerId = Dcm_Dsl_u1AuthClientBase + (uint8)u2_ClientCnt;
        Dcm_Main_TmrSrv_StopTimer(u1_TimerId);
    }

    return;
}
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

/**********                Timer Handlers                          **********/
/****************************************************************************/
/* Function Name | Dcm_Dsl_AuthTOCbk                                        */
/* Description   | Perform a process in the Authentication timeout.         */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1TimerId : not use                                 */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_AUTHENTICATION_USE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_AuthTOCbk
(
    const uint8 u1TimerId
)
{
    uint16 u2_ConnectionId;

    u2_ConnectionId = (uint16)u1TimerId - Dcm_Dsl_u1AuthClientBase;

    Dcm_Dsl_AuthMng_SetAuthState(DCM_DEAUTHENTICATED, u2_ConnectionId, (boolean)FALSE);

    return ;
}
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_SetDeauthenticateAll                        */
/* Description   | This function makes the authentication status            */
/*               | deauthenticated                                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_AUTHENTICATION_USE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetDeauthenticateAll
( void )
{
    uint16 u2_ClientCnt;
    uint16 u2_ClientNumMax;

    u2_ClientNumMax = Dcm_Dsl_u2ClientNum;

    for( u2_ClientCnt = (uint16)0U; u2_ClientCnt < u2_ClientNumMax; u2_ClientCnt++ )
    {
        Dcm_Dsl_AuthMng_SetAuthState(DCM_DEAUTHENTICATED, u2_ClientCnt, (boolean)FALSE);
    }

    return ;
}
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_SetDeauthenticate                           */
/* Description   | This function sets the authentication status of          */
/*               | the active connection.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [In] u2ConnectionId : Connection ID(ClientIndex)         */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_AUTHENTICATION_USE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetDeauthenticate
(
    const uint16 u2ConnectionId
)
{
    Dcm_Dsl_AuthMng_SetAuthState(DCM_DEAUTHENTICATED, u2ConnectionId, (boolean)FALSE);
    return;
}
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_SetAuthConf                                 */
/* Description   | This function sets the authentication status in the      */
/*               | context of transmission completion.                      */
/* Preconditions | none                                                     */
/* Parameters    | [In] u2ConnectionId : Connection ID(ClientIndex)         */
/*               | [in] bUpdateEnable :  TRUE : AuthState Update Enable     */
/*               |                      FALSE : AuthState Update Disable    */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         |  -                                                       */
/****************************************************************************/
#if( DCM_AUTHENTICATION_USE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_SetAuthConf
(
    const uint16 u2ConnectionId,
    const boolean bUpdateEnable
)
{
    Dcm_Dsl_AuthMng_SetAuthConf(u2ConnectionId, bUpdateEnable);
    return;
}
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsl_Ctrl_ReqAuthStateChangeNotification              */
/* Description   | This function notifies SW-C of the change in             */
/*               | authentication status.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [In] u2ConnectionId : Connection ID(ClientIndex)         */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_AUTHENTICATION_USE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_ReqAuthStateChangeNotification
(
    const uint16 u2ConnectionId
)
{
    Dcm_Dsl_AuthMng_ReqAuthStateChangeNotification(u2ConnectionId);

    return ;
}
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-5-0         :2023-07-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
