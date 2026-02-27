/* Dcm_Dsp_Main_c(v5-3-0)                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_Main/CODE                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/usr/Dcm_Dsp_Main_Callout.h"
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#if ( DCM_PERIODIC_SEND_USE == STD_ON )
#include <Dcm/Dcm_Dsp_PeriodicMng.h>
#endif  /* DCM_PERIODIC_SEND_USE == STD_ON */
#if ( DCM_ULDL_SERVICE_USE == STD_ON )
#include <Dcm/Dcm_Dsp_DataTfrMng.h>
#endif  /* DCM_ULDL_SERVICE_USE == STD_ON */
#include <Dcm/Dcm_Dsl_Ctrl.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_MAIN_INVALIDSID         ((uint8)0x00U)

#define DCM_DSP_MAIN_IDLE               ((uint32)0x00000000U)
#define DCM_DSP_MAIN_NONIDLE            ((uint32)0xA5A5A5A5U)

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

#if ( DCM_USE_PROVIDE_SERVICE == STD_ON )
VAR( Dcm_MsgContextType, DCM_VAR_NO_INIT ) Dcm_Dsp_Main_stMsgContext;
static VAR( boolean, DCM_VAR_NO_INIT ) Dcm_Dsp_Main_bUserNotifyFlag;
#endif /* DCM_USE_PROVIDE_SERVICE == STD_ON */

static VAR( uint32, DCM_VAR_NO_INIT ) Dcm_Dsp_Main_u4IdleFlag;

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
/* Function Name | Dcm_Dsp_Init                                             */
/* Description   | Service for basic initialization of Dsp submodule.       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_USE_PROVIDE_SERVICE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsp_Init
( void )
{
    sint32 s4_InitFuncNum;
    sint32 s4_cnt;

    s4_InitFuncNum = (sint32)Dcm_Dsp_Main_u1Init_Func_Num;
    Dcm_Dsp_Main_bUserNotifyFlag = ( boolean )FALSE;
    Dcm_Dsp_Main_u4IdleFlag = DCM_DSP_MAIN_IDLE;

    for( s4_cnt = ( sint32 )0L; s4_cnt < s4_InitFuncNum; s4_cnt++ )     /* MISRA DEVIATION */
    {
#ifndef JGXSTACK
        Dcm_Dsp_Main_InitFunc_Tbl[ s4_cnt ]();
#else /* JGXSTACK */
        Dcm_Stack_InitFunc();
#endif /* JGXSTACK */
    }

    return;
}
#endif /* DCM_USE_PROVIDE_SERVICE == STD_ON */
#if ( DCM_USE_PROVIDE_SERVICE == STD_OFF )
FUNC( void, DCM_CODE ) Dcm_Dsp_Init
( void )
{
    sint32 s4_InitFuncNum;
    sint32 s4_cnt;

    s4_InitFuncNum = (sint32)Dcm_Dsp_Main_u1Init_Func_Num;
    Dcm_Dsp_Main_u4IdleFlag = DCM_DSP_MAIN_IDLE;

    for( s4_cnt = ( sint32 )0L; s4_cnt < s4_InitFuncNum; s4_cnt++ )     /* MISRA DEVIATION */
    {
#ifndef JGXSTACK
        Dcm_Dsp_Main_InitFunc_Tbl[ s4_cnt ]();
#else /* JGXSTACK */
        Dcm_Stack_InitFunc();
#endif /* JGXSTACK */
    }

    return;
}
#endif /* DCM_USE_PROVIDE_SERVICE == STD_OFF */

#if ( DCM_PERIODIC_SEND_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_Main                                             */
/* Description   | Dsp periodic function                                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_Main
( void )
{

    /* Periodic Send */
    Dcm_Dsp_PeriodicMng_Main();

    return;
}
#endif  /* DCM_PERIODIC_SEND_USE == STD_ON */

#if ( DCM_USE_PROVIDE_SERVICE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_Main_SetUserNotifyFlag                           */
/* Description   | Set the UserNotifyFlag                                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN]   boolean    : bFlag                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_Main_SetUserNotifyFlag
(
    const boolean bFlag
)
{
    Dcm_Dsp_Main_bUserNotifyFlag = bFlag;

    return;
}
#endif /* DCM_USE_PROVIDE_SERVICE == STD_ON */

#if ( DCM_USE_PROVIDE_SERVICE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_Main_GetUserNotifyFlag                           */
/* Description   | Get the UserNotifyFlag                                   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | boolean                                                  */
/*               | TRUE                                                     */
/*               | FALSE                                                    */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsp_Main_GetUserNotifyFlag
( void )
{
    return ( Dcm_Dsp_Main_bUserNotifyFlag );
}
#endif /* DCM_USE_PROVIDE_SERVICE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_NotifiedWrongReq                                 */
/* Description   | Wrong request message is notified by DSD                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN]   uint8    : u1SID                                  */
/*               | [IN]   Dcm_NegativeResponseCodeType    : u1ErrorCode     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_NotifiedWrongReq
(
    const uint8 u1SID,
    const Dcm_NegativeResponseCodeType u1ErrorCode
)
{
    sint32 s4_NotifiwrongreqNum;
    sint32 s4_cnt;

    s4_NotifiwrongreqNum = (sint32)Dcm_Dsp_Main_u1Notifiwrongreq_Num;

    if( u1SID == DCM_DSP_MAIN_INVALIDSID )
    {
        /* No process */
    }
    else
    {
        for( s4_cnt = (sint32)0x00000000L; s4_cnt < s4_NotifiwrongreqNum; s4_cnt++ )     /* MISRA DEVIATION */
        {
            if( u1SID == Dcm_Dsp_Main_NtfiWroRq_Tbl[s4_cnt].u1SID )     /* MISRA DEVIATION */
            {
#ifndef JGXSTACK
                Dcm_Dsp_Main_NtfiWroRq_Tbl[s4_cnt].ptFunc( u1ErrorCode );
#else /* JGXSTACK */
                Dcm_Stack_NtfiWrongRqFunc( u1ErrorCode );
#endif /* JGXSTACK */
            }
            else
            {
                /* No process */
            }
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_GetSleepPermission                               */
/* Description   | Notify of sleep availability information of Dsp.         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE  : Sleep possible                            */
/*               |        FALSE : Sleep impossible                          */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( boolean, DCM_CODE ) Dcm_Dsp_GetSleepPermission
( void )
{
    sint32 s4_SlppermissionFncNum;
    sint32 s4_cnt;
    boolean b_RetVal;

    b_RetVal = (boolean)TRUE;   /* MISRA DEVIATION */
    s4_SlppermissionFncNum = (sint32)Dcm_Dsp_Main_u1Slppermission_Fnc_Num;

    if( Dcm_Dsp_Main_u4IdleFlag != DCM_DSP_MAIN_NONIDLE )
    {
        for( s4_cnt = (sint32)0L; s4_cnt < s4_SlppermissionFncNum; s4_cnt++ )     /* MISRA DEVIATION */
        {
#ifndef JGXSTACK
            b_RetVal = Dcm_P_Main_SlpPermissionFunc_Tbl[s4_cnt]();      /* MISRA DEVIATION */
#else /* JGXSTACK */
            b_RetVal = Dcm_Stack_SlpPermissionFunc();
#endif /* JGXSTACK */
            if( b_RetVal == (boolean)FALSE )
            {
                break;
            }
        }

        if( b_RetVal == (boolean)TRUE )     /* MISRA DEVIATION */
        {
            b_RetVal = Dcm_Apl_Sid_GetSleepPermission();
        }
    }
    else
    {
        b_RetVal = (boolean)FALSE;
    }

    return b_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_Main_SetIdleFlag                                 */
/* Description   | Set the IdleFlag                                         */
/* Preconditions | None                                                     */
/* Parameters    | [IN]   boolean    : bFlag                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_Main_SetIdleFlag
(
    const boolean bFlag
)
{
    if( bFlag ==(boolean)TRUE )
    {
        Dcm_Dsp_Main_u4IdleFlag = DCM_DSP_MAIN_IDLE;
    }
    else
    {
        Dcm_Dsp_Main_u4IdleFlag = DCM_DSP_MAIN_NONIDLE;
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_IdleRefresh                                      */
/* Description   | Service for basic Refresh of Dsp submodule.              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_IdleRefresh
( void )
{
    sint32 s4_cnt;
    sint32 s4_Refresh_Func_Num;
    uint32 u4_IdleFlag;
    P2VAR(volatile uint32, AUTOMATIC, DCM_APPL_DATA) pt_IdleFlag;

    if( Dcm_Dsp_Main_u4IdleFlag != DCM_DSP_MAIN_NONIDLE )
    {
        Dcm_Dsp_Main_u4IdleFlag = DCM_DSP_MAIN_IDLE;
    }
    else
    {
        pt_IdleFlag     = &Dcm_Dsp_Main_u4IdleFlag;
        u4_IdleFlag     = *pt_IdleFlag;
        *pt_IdleFlag    = u4_IdleFlag ;
    }

    s4_Refresh_Func_Num = ( sint32 )Dcm_Dsp_Main_u1Refresh_Func_Num;
    for( s4_cnt = ( sint32 )0L; s4_cnt < s4_Refresh_Func_Num; s4_cnt++ )
    {
#ifndef JGXSTACK
        Dcm_Dsp_Main_RefreshFunc_Tbl[ s4_cnt ]();     /* MISRA DEVIATION */
#else  /* JGXSTACK */
        Dcm_Stack_RefreshFunc();
#endif /* JGXSTACK */
    }

    return;
}

#if ( DCM_PAGEDBUFFER_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_ServiceInit                                      */
/* Description   | Dsp initialization before starting the service.          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_ServiceInit
( void )
{
    Dcm_Dsp_MsgMaker_SrvInit();

    return;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_Main_PreWriteAll                                 */
/* Description   | Preparatory process before writeall.                     */
/* Preconditions | none                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         |  -                                                       */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_Main_PreWriteAll
( void )
{
    sint32 s4_cnt;
    sint32 s4_PreWriteAllFunc_Num;

    s4_PreWriteAllFunc_Num = ( sint32 )Dcm_Dsp_Main_u1PreWriteAll_Fnc_Num;
    for( s4_cnt = ( sint32 )0L; s4_cnt < s4_PreWriteAllFunc_Num; s4_cnt++ )
    {
#ifndef JGXSTACK
        Dcm_Dsp_Main_PreWriteAllFunc_Tbl[ s4_cnt ]();
#else  /* JGXSTACK */
        Dcm_Stack_PreWriteAllFunc();
#endif /* JGXSTACK */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_GetActiveResponse                                    */
/* Description   | Get active response                                      */
/* Preconditions | none                                                     */
/* Parameters    | [out] ptActive :  Active state of each target service    */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : this value is always returned.             */
/* Notes         |  -                                                       */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_GetActiveResponse
(
    P2VAR( Dcm_ActiveStateType, AUTOMATIC, DCM_APPL_DATA ) ptActive
)
{
    uint8               u1_cnt;
    uint8               u1_ActiveResp_Func_Num;
    Dcm_ActiveStateType u1_ActiveStatus;
    Std_ReturnType      u1_RetVal;

    u1_RetVal = E_OK;
    u1_ActiveResp_Func_Num = Dcm_Dsp_Main_u1ActiveResp_Func_Num;

    if( ptActive != NULL_PTR )
    {
        u1_ActiveStatus = DCM_EXE_NONE;

        for( u1_cnt = (uint8)0U; u1_cnt < u1_ActiveResp_Func_Num; u1_cnt++ )
        {
#ifndef JGXSTACK
            Dcm_Dsp_Main_GetActiveRespFunc_Tbl[u1_cnt]( &u1_ActiveStatus );
#else /* JGXSTACK */
            Dcm_Stack_GetActiveRespFunc( &u1_ActiveStatus );
#endif /* JGXSTACK */
        }
        *ptActive = u1_ActiveStatus;
    }
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_SetActiveResponse                                    */
/* Description   | Set active response                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] u1TargetService:Active state of each target service */
/*               | [in] bActive        :Request Set Active Status           */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : this value is always returned.             */
/* Notes         |  -                                                       */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SetActiveResponse
(
    Dcm_ActiveStateType u1TargetService,
    boolean             bActive
)
{
    uint8    u1_cnt;
    uint8    u1_ActiveResp_Func_Num;
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( bActive == (boolean)TRUE )
    {
        u1_ActiveResp_Func_Num = Dcm_Dsp_Main_u1ActiveResp_Func_Num;

        for( u1_cnt = (uint8)0U; u1_cnt < u1_ActiveResp_Func_Num; u1_cnt++ )
        {
#ifndef JGXSTACK
            Dcm_Dsp_Main_SetActiveRespFunc_Tbl[u1_cnt]( u1TargetService );
#else  /* JGXSTACK */
            Dcm_Stack_SetActiveRespFunc( u1TargetService );
#endif /* JGXSTACK */
        }
    }
    else
    {
        /* Inactive the communication bus for all clients */
        Dcm_Dsl_SetComActive( DCM_DSL_ALL_TARGETS, (boolean)FALSE );
    }
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_GetTransferStatus                                    */
/* Description   | Get transfer status                                      */
/* Preconditions | none                                                     */
/* Parameters    | [out] ptTransferStatus : Transfer status                 */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK     : Request was successful                 */
/*               |        E_NOT_OK : Request was not successful             */
/* Notes         |  -                                                       */
/****************************************************************************/
#if ( DCM_ULDL_SERVICE_USE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_GetTransferStatus
(
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptTransferStatus
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_NOT_OK;

    if( ptTransferStatus != NULL_PTR )
    {
        *ptTransferStatus = Dcm_Dsp_DataTfrMng_GetTfrStatus();
        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_ULDL_SERVICE_USE == STD_ON */
#if ( DCM_ULDL_SERVICE_USE == STD_OFF )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_GetTransferStatus
(
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptTransferStatus
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_NOT_OK;

    if( ptTransferStatus != NULL_PTR )
    {
        *ptTransferStatus = DCM_TFR_NONE;
        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_ULDL_SERVICE_USE == STD_OFF */

/****************************************************************************/
/* Function Name | Dcm_InitTransferStatus                                   */
/* Description   | Initialize transfer status                               */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : this value is always returned.             */
/* Notes         |  -                                                       */
/****************************************************************************/
#if ( DCM_ULDL_SERVICE_USE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_InitTransferStatus
( void )
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    Dcm_Dsp_DataTfrMng_InitTfrStatus();
    Dcm_Dsp_DataTfrMng_InitTfrInfo();

    return u1_RetVal;
}
#endif /* DCM_ULDL_SERVICE_USE == STD_ON */
#if ( DCM_ULDL_SERVICE_USE == STD_OFF )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_InitTransferStatus
( void )
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    return u1_RetVal;
}
#endif /* DCM_ULDL_SERVICE_USE == STD_OFF */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
