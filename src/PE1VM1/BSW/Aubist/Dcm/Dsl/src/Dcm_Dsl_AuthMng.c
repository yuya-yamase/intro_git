/* Dcm_Dsl_AuthMng_c(v5-0-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dcm_Dsl_AuthMng/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsl/inc/Dcm_Dsl_Main.h"
#include "../../Dsl/inc/Dcm_Dsl_AuthMng.h"
#include "../../Dsl/usr/Dcm_Dsl_AuthMng_Connector.h"

#include <Dcm/Dcm_Dsp_Main.h>
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

#if( DCM_AUTHENTICATION_USE == STD_ON )
static FUNC(void, DCM_CODE) Dcm_Dsl_AuthMng_IndicateAuthStateChange
(
    const uint8 u1Authenticated,
    const uint16 u2ConnectionId
);
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

#if( DCM_AUTHENTICATION_USE == STD_ON )
static VAR(uint8, DCM_VAR_NO_INIT) Dcm_Dsl_u1Authenticated[DCM_DSL_CLIENT_NUM];
static VAR(uint8, DCM_VAR_NO_INIT) Dcm_Dsl_u1PostAuthenticated;
static VAR(boolean, DCM_VAR_NO_INIT) Dcm_Dsl_bAuthDelayUpdate;
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

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
/* Function Name | Dcm_Dsl_AuthMng_Init                                     */
/* Description   | This function calls the initialization function          */
/*               | of the DSL unit.                                         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
#if( DCM_AUTHENTICATION_USE == STD_ON )
FUNC(void, DCM_CODE) Dcm_Dsl_AuthMng_Init
(void)
{
    uint16 u2_ClientCnt;
    uint16 u2_ClientNumMax;

    u2_ClientNumMax = Dcm_Dsl_u2ClientNum;

    /* lock */
    SchM_Enter_Dcm_Dsl_SecLevel();

    for( u2_ClientCnt = (uint16)0U; u2_ClientCnt < u2_ClientNumMax; u2_ClientCnt++ )
    {
        Dcm_Dsl_u1Authenticated[u2_ClientCnt] = DCM_DEAUTHENTICATED;
    }

    /* unlock */
    SchM_Exit_Dcm_Dsl_SecLevel();

    Dcm_Dsl_u1PostAuthenticated = DCM_DEAUTHENTICATED;
    Dcm_Dsl_bAuthDelayUpdate    = (boolean)FALSE;

    return ;
}
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

#if( DCM_AUTHENTICATION_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsl_AuthMng_GetAuthState                             */
/* Description   | This function gets the authentication status of the      */
/*               | specified connection.                                    */
/* Preconditions | -                                                        */
/* Parameters    | [in] u2ConnectionId : ConnectionId                       */
/*               | [out] ptAuthenticated : Auth/Deauth                      */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_AuthMng_GetAuthState
(
    const uint16 u2ConnectionId,
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ptAuthenticated
)
{
    /* lock */
    SchM_Enter_Dcm_Dsl_SecLevel();

    *ptAuthenticated = Dcm_Dsl_u1Authenticated[u2ConnectionId];

    /* unlock */
    SchM_Exit_Dcm_Dsl_SecLevel();

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsl_AuthMng_SetAuthState                             */
/* Description   | This function sets the authentication status of the      */
/*               | specified connection.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1Authenticated : Auth/Deauth                       */
/*               | [in] u2ConnectionId  : ConnectionId                      */
/*               | [in] bDelayUpdate  : TRUE : Confirmation Reception timing*/
/*               |                     FALSE : Immediate                    */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_AuthMng_SetAuthState
(
    const uint8 u1Authenticated,
    const uint16 u2ConnectionId,
    const boolean bDelayUpdate
)
{
    if( bDelayUpdate == (boolean)TRUE )
    {
        /* lock */
        SchM_Enter_Dcm_Dsl_SecLevel();

        Dcm_Dsl_u1PostAuthenticated = u1Authenticated;
        Dcm_Dsl_bAuthDelayUpdate    = (boolean)TRUE;

        /* unlock */
        SchM_Exit_Dcm_Dsl_SecLevel();
    }
    else
    {
        /* lock */
        SchM_Enter_Dcm_Dsl_SecLevel();

        Dcm_Dsl_u1Authenticated[u2ConnectionId] = u1Authenticated;
        Dcm_Dsl_u1PostAuthenticated             = u1Authenticated;
        Dcm_Dsl_bAuthDelayUpdate                = (boolean)FALSE;

        /* unlock */
        SchM_Exit_Dcm_Dsl_SecLevel();

        Dcm_Dsl_AuthMng_IndicateAuthStateChange(u1Authenticated, u2ConnectionId);
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_AuthMng_SetAuthConf                              */
/* Description   | This function sets the authentication status in the      */
/*               | context of transmission completion.                      */
/* Preconditions | none                                                     */
/* Parameters    | [In] u2ConnectionId : Connection ID(ClientIndex)         */
/*               | [in] bUpdateEnable :  TRUE : Session Update Enable       */
/*               |                      FALSE : Session Update Disable      */
/*               |                                                          */
/* Return Value  | none                                                     */
/* Notes         |  -                                                       */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_AuthMng_SetAuthConf
(
    const uint16 u2ConnectionId,
    const boolean bUpdateEnable
)
{
    /* lock */
    SchM_Enter_Dcm_Dsl_SecLevel();

    if( bUpdateEnable == (boolean)TRUE )
    {
        if( Dcm_Dsl_bAuthDelayUpdate == (boolean)TRUE )
        {
            Dcm_Dsl_u1Authenticated[u2ConnectionId] = Dcm_Dsl_u1PostAuthenticated;
        }
    }
    else
    {
        Dcm_Dsl_bAuthDelayUpdate = (boolean)FALSE;
    }

    /* unlock */
    SchM_Exit_Dcm_Dsl_SecLevel();
    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_AuthMng_ReqAuthStateChangeNotification           */
/* Description   | This function notifies SW-C of the change in             */
/*               | authentication status.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [In] u2ConnectionId : Connection ID(ClientIndex)         */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsl_AuthMng_ReqAuthStateChangeNotification
(
    const uint16 u2ConnectionId
)
{
    if( Dcm_Dsl_bAuthDelayUpdate == (boolean)TRUE )
    {
        Dcm_Dsl_AuthMng_IndicateAuthStateChange(Dcm_Dsl_u1PostAuthenticated, u2ConnectionId);
        Dcm_Dsl_bAuthDelayUpdate = (boolean)FALSE;
    }

    return ;
}

/****************************************************************************/
/* Function Name | Dcm_Dsl_AuthMng_IndicateAuthStateChange                  */
/* Description   | This function notifies SW-C of the change of the session */
/* Preconditions | none                                                     */
/* Parameters    | [in] bAuthenticated : TRUE/FALSE                         */
/*               | [in] u2ConnectionId : ConnectionId                       */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsl_AuthMng_IndicateAuthStateChange
(
    const uint8 u1Authenticated,
    const uint16 u2ConnectionId
)
{
    uint8 u1_Count;
    uint8 u1_IndAuthChgNumMax;

    u1_IndAuthChgNumMax = Dcm_Dsl_u1IndAuthChgNum;

    for( u1_Count = (uint8)0U; u1_Count < u1_IndAuthChgNumMax; u1_Count++ )
    {
#ifndef JGXSTACK

        Dcm_Dsl_IndAuthStateChgTable[u1_Count](u1Authenticated, u2ConnectionId);

#else   /* JGXSTACK */

        Dcm_Stack_IndAuthStateChgFunc(u1Authenticated, u2ConnectionId);

#endif  /* JGXSTACK */
    }

    /* no return check required */
    (void)Dcm_Dsl_Cnct_Switch_AuthState(u1Authenticated, u2ConnectionId);

    return ;
}
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
