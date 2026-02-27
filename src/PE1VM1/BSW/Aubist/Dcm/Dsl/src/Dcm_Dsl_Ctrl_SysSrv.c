/* Dcm_Dsl_Ctrl_SysSrv_c(v5-0-0)                                            */
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
#include "../../Dsl/inc/Dcm_Dsl_RxMsg.h"
#include "../../Dsl/inc/Dcm_Dsl_SessionMng.h"
#include "../../Dsl/inc/Dcm_Dsl_CommHandling.h"

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
/* Function Name | Dcm_Dsl_Ctrl_Init                                        */
/* Description   | Initialize ControllerUnit Data.                          */
/*               | (When Called by Dcm_Init)                                */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_Ctrl_Init
( void )
{
    Dcm_Dsl_Ctrl_ComSrv_Init();
    Dcm_Dsl_Ctrl_TxSrv_Init();
    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsl_GetSleepPermission                               */
/* Description   | Notify of sleep availability information of DCM.         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Sleep possible                            */
/*               |        FALSE : Sleep impossible                          */
/* Notes         |  -                                                       */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsl_GetSleepPermission
( void )
{
    boolean         b_Result;
    boolean         b_Active;
    boolean         b_ActiveSession;
    boolean         b_ActiveResponse;

    b_Result = (boolean)TRUE;

    b_ActiveSession = Dcm_Dsl_Ctrl_IsActiveSession();
    if( b_ActiveSession == (boolean)FALSE )
    {
        b_Active = Dcm_Dsl_Ctrl_IsActiveDiag();
        if( b_Active == (boolean)FALSE )
        {
            b_ActiveResponse = Dcm_Dsl_Ctrl_IsActiveResponse();
            if( b_ActiveResponse != (boolean)FALSE )
            {
                b_Result = (boolean)FALSE;
            }
        }
        else
        {
            b_Result = (boolean)FALSE;
        }
    }
    else
    {
        b_Result = (boolean)FALSE;
    }

    return b_Result;

}

/****************************************************************************/
/* Function Name | Dcm_Dsl_GetBusSleepPermission                            */
/* Description   | Notify of Bus Sleep availability information of DCM.     */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : BusSleep possible                         */
/*               |        FALSE : BusSleep impossible                       */
/* Notes         |  -                                                       */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsl_GetBusSleepPermission
( void )
{
    boolean         b_Result;
    boolean         b_ActiveSession;
    boolean         b_ActiveResponse;
    uint8           u1_DslState;
    uint16          u2_PduMapIndex;

    b_Result        = (boolean)TRUE;
    u2_PduMapIndex  = Dcm_Dsl_Ctrl_GetRxPduMapIndex();

    b_ActiveSession = Dcm_Dsl_Ctrl_IsActiveSession();
    if( b_ActiveSession == (boolean)FALSE )
    {
        u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2_PduMapIndex);
        if( ( u1_DslState == DCM_DSL_ST_IDLE )
         || ( u1_DslState == DCM_DSL_ST_RECEIVING ) )
        {
            b_ActiveResponse = Dcm_Dsl_Ctrl_IsActiveResponse();
            if( b_ActiveResponse != (boolean)FALSE )
            {
                b_Result = (boolean)FALSE;
            }
        }
        else
        {
            b_Result = (boolean)FALSE;
        }
    }
    else
    {
        b_Result = (boolean)FALSE;
    }

    return b_Result;

}

/****************************************************************************/
/* Function Name | Dcm_Dsl_IdleRefresh                                      */
/* Description   | Refresh the data at idle.                                */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsl_IdleRefresh
( void )
{
    uint16  u2_PduMapIndex;
    uint16  u2_RxPduMapIndex;
    uint16  u2_PduIDNum_Cnt;
    uint16  u2_PduIdNumMax;
    uint8   u1_DslState;

    u2_PduIdNumMax = Dcm_Dsl_u2PduIdNum;

    /* lock */
    SchM_Enter_Dcm_Dsl_Ctrl();

    u2_PduMapIndex   = Dcm_Dsl_Ctrl_GetPduMapIndex();
    u2_RxPduMapIndex = Dcm_Dsl_Ctrl_GetRxPduMapIndex();

    for( u2_PduIDNum_Cnt = (uint16)0U; u2_PduIDNum_Cnt < u2_PduIdNumMax; u2_PduIDNum_Cnt++ )
    {
        u1_DslState = Dcm_Dsl_Ctrl_GetDslState(u2_PduIDNum_Cnt);
        Dcm_Dsl_Ctrl_SetDslState(u2_PduIDNum_Cnt, u1_DslState);
    }

    Dcm_Dsl_Ctrl_SetPduMapIndex(u2_PduMapIndex);
    Dcm_Dsl_Ctrl_SetRxPduMapIndex(u2_RxPduMapIndex);

    Dcm_Dsl_Ctrl_TxSrv_Refresh();

    Dcm_Dsl_SessionMng_Refresh();
    Dcm_Dsl_CmHdl_Refresh();
    Dcm_Dsl_RxMsg_Refresh();

    /* unlock */
    SchM_Exit_Dcm_Dsl_Ctrl();

    return;
}


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
