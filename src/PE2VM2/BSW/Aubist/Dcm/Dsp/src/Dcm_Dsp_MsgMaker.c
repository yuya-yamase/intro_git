/* Dcm_Dsp_MsgMaker_c(v5-0-0)                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_MsgMaker/CODE                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Main_Common.h>
#include <Dcm/Dcm_Dsp_Main.h>
#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_MSGMAKER_PBID_INITIAL   ((uint16)0xFFFFU)

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

#if ( DCM_PAGEDBUFFER_ENABLED == STD_ON )
static VAR(uint16, DCM_VAR_NO_INIT) Dcm_Dsp_MsgMaker_u2PBId;
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */

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

#if ( DCM_USE_PROVIDE_SERVICE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_MsgMaker_SendNegRes                              */
/* Description   | This function provides send positive response.           */
/* Preconditions | None                                                     */
/* Parameters    | [in] ptMsgContext : Message Context                      */
/*               | [in] u1ErrorCode  : Negative Response Code               */
/*               |                                                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_MsgMaker_SendNegRes
(
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext,
    const Dcm_NegativeResponseCodeType u1ErrorCode
)
{
    Dcm_ExternalSetNegResponse( ptMsgContext, u1ErrorCode );

    if( u1ErrorCode == DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING )
    {
        /* no process */
    }
    else
    {
        Dcm_ExternalProcessingDone( ptMsgContext );
    }

    return ;
}
#endif /* DCM_USE_PROVIDE_SERVICE == STD_ON */

#if ( DCM_USE_PROVIDE_SERVICE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_MsgMaker_SendPosRes                              */
/* Description   | This function provides send negative response.           */
/* Preconditions | None                                                     */
/* Parameters    | [in] ptMsgContext : Message Context                      */
/*               |                                                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_MsgMaker_SendPosRes
(
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    Dcm_ExternalProcessingDone( ptMsgContext );

    return ;
}
#endif /* DCM_USE_PROVIDE_SERVICE == STD_ON */

/****************************************************************************/
/* Function Name | DspInternal_DcmConfirmation                              */
/* Description   | This function confirms the successful transmission or a  */
/*               | transmission error of a diagnostic service. This is the  */
/*               | right time to perform any application state transitions. */
/*               | This API is also called if the response to a diagnostic  */
/*               | service is suppressed.                                   */
/* Preconditions | None                                                     */
/* Parameters    | [in] idContext     : Id Context                          */
/*               | [in] ConnectionId  : Connection Id                       */
/*               | [in] status        : Status                              */
/*               |                                                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_ENABLED == STD_OFF )
FUNC( void, DCM_CODE ) DspInternal_DcmConfirmation
(
    Dcm_IdContextType idContext,
    uint16 ConnectionId,
    Dcm_ConfirmationStatusType status
)
{
    sint32 s4_Loop;
    sint32 s4_ConfNum;
    
    s4_ConfNum = (sint32)Dcm_P_Msgmaker_u1Conf_Num;

    for( s4_Loop = (sint32)0L; s4_Loop < s4_ConfNum; s4_Loop++ )
    {
        if( idContext == Dcm_P_MsgMaker_stConfTbl[s4_Loop].u1Sid )
        {
#ifndef JGXSTACK
            Dcm_P_MsgMaker_stConfTbl[s4_Loop].ptFnc( idContext, ConnectionId, status );
#else  /* JGXSTACK */
            Dcm_Stack_ConfirmationFunc( idContext, ConnectionId, status );
#endif /* JGXSTACK */
            break;
        }
    }

    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return ;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_OFF */


/****************************************************************************/
/* Function Name | DspInternal_DcmConfirmation                              */
/* Description   | This function confirms the successful transmission or a  */
/*               | transmission error of a diagnostic service. This is the  */
/*               | right time to perform any application state transitions. */
/*               | This API is also called if the response to a diagnostic  */
/*               | service is suppressed.                                   */
/* Preconditions | None                                                     */
/* Parameters    | [in] idContext     : Id Context                          */
/*               | [in] ConnectionId  : Connection Id                       */
/*               | [in] status        : Status                              */
/*               |                                                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_ENABLED == STD_ON )
FUNC( void, DCM_CODE ) DspInternal_DcmConfirmation
(
    Dcm_IdContextType idContext,
    uint16 ConnectionId,
    Dcm_ConfirmationStatusType status
)
{
    sint32 s4_Loop;
    sint32 s4_ConfNum;
    sint32 s4_PBNum;

    s4_ConfNum = (sint32)Dcm_P_Msgmaker_u1Conf_Num;
    s4_PBNum   = (sint32)Dcm_P_Msgmaker_u2PB_Num;
    
    for( s4_Loop = (sint32)0L; s4_Loop < s4_ConfNum; s4_Loop++ )
    {
        if( idContext == Dcm_P_MsgMaker_stConfTbl[s4_Loop].u1Sid )
        {
#ifndef JGXSTACK
            Dcm_P_MsgMaker_stConfTbl[s4_Loop].ptFnc( idContext, ConnectionId, status );
#else  /* JGXSTACK */
            Dcm_Stack_ConfirmationFunc( idContext, ConnectionId, status );
#endif /* JGXSTACK */
            break;
        }
    }

    if( status == (Dcm_ConfirmationStatusType)DCM_RES_POS_NOT_OK )
    {
        if( (sint32)Dcm_Dsp_MsgMaker_u2PBId < s4_PBNum )
        {
#ifndef JGXSTACK
            Dcm_P_MsgMaker_stPBTbl[Dcm_Dsp_MsgMaker_u2PBId].ptCancelPageFnc();
#else  /* JGXSTACK */
            Dcm_Stack_CancelPageFunc();
#endif /* JGXSTACK */
        }
        else
        {
            Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );
        }
    }
    else
    {
        Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );
    }

    return ;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */


/****************************************************************************/
/* Function Name | Dcm_Dsp_MsgMaker_StartPagedProcessing                    */
/* Description   | This function Call DsdInternal_StartPagedProcessing      */
/* Preconditions | None                                                     */
/* Parameters    | [in] ptMsgContext    : Message Context                   */
/*               | [in] u2PagedBufferId : PagedBuffer Id                    */
/*               |                                                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_ENABLED == STD_ON )
#if ( DCM_USE_PROVIDE_SERVICE == STD_ON )
FUNC(void, DCM_CODE) Dcm_Dsp_MsgMaker_StartPagedProcessing
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext,
    const uint16 u2PagedBufferId
)
{
    Dcm_Dsp_MsgMaker_u2PBId = u2PagedBufferId;

    DsdInternal_StartPagedProcessing( ptMsgContext );

    return;
}
#endif /* DCM_USE_PROVIDE_SERVICE == STD_ON */
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */


/****************************************************************************/
/* Function Name | DspInternal_DcmUpdatePage                                */
/* Description   | This function call UpdatePage Function                   */
/* Preconditions | None                                                     */
/* Parameters    | [in] ptResData       : Response Data                     */
/*               | [in] u4ResMaxDataLen : Buffer Size of Response Data      */
/*               |                                                          */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing abnormal                */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_ENABLED == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) DspInternal_DcmUpdatePage
(
    Dcm_MsgType     ptResData,
    Dcm_MsgLenType  u4ResMaxDataLen
)
{
    sint32 s4_PBNum;
    Std_ReturnType u1_RetVal;

    s4_PBNum = (sint32)Dcm_P_Msgmaker_u2PB_Num;

    if( (sint32)Dcm_Dsp_MsgMaker_u2PBId < s4_PBNum )
    {
#ifndef JGXSTACK
        u1_RetVal = Dcm_P_MsgMaker_stPBTbl[Dcm_Dsp_MsgMaker_u2PBId].ptUpdatePageFnc( ptResData, u4ResMaxDataLen );
#else  /* JGXSTACK */
        u1_RetVal = Dcm_Stack_UpdatePageFunc( ptResData, u4ResMaxDataLen );
#endif /* JGXSTACK */
    }
    else
    {
        u1_RetVal = E_NOT_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */


/****************************************************************************/
/* Function Name | Dcm_Dsp_MsgMaker_ProcessPage                             */
/* Description   | This function call DsdInternal_ProcessPage               */
/* Preconditions | None                                                     */
/* Parameters    | [in] FilledPageLen : Filled Page Length                  */
/*               |                                                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_ENABLED == STD_ON )
#if ( DCM_USE_PROVIDE_SERVICE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsp_MsgMaker_ProcessPage
(
    const Dcm_MsgLenType FilledPageLen
)
{
    DsdInternal_ProcessPage( FilledPageLen );

    return;
}
#endif /* DCM_USE_PROVIDE_SERVICE == STD_ON */
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */


/****************************************************************************/
/* Function Name | DspInternal_CancelPagedBufferProcessing                  */
/* Description   | This function call CancelPage Function                   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_ENABLED == STD_ON )
FUNC( void, DCM_CODE ) DspInternal_CancelPagedBufferProcessing
(void)
{
    sint32 s4_PBNum;

    s4_PBNum = (sint32)Dcm_P_Msgmaker_u2PB_Num;
    
    if( (sint32)Dcm_Dsp_MsgMaker_u2PBId < s4_PBNum )
    {
#ifndef JGXSTACK
        Dcm_P_MsgMaker_stPBTbl[Dcm_Dsp_MsgMaker_u2PBId].ptCancelPageFnc();
#else  /* JGXSTACK */
        Dcm_Stack_CancelPageFunc();
#endif /* JGXSTACK */
    }
    else
    {
        /* No process */
    }

    return ;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */


#if ( DCM_PAGEDBUFFER_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_MsgMaker_SrvInit                                 */
/* Description   | This function initializes before starting the service    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_MsgMaker_SrvInit
(void)
{
    Dcm_Dsp_MsgMaker_u2PBId = DCM_DSP_MSGMAKER_PBID_INITIAL;

    return;
}
#endif /* DCM_PAGEDBUFFER_ENABLED == STD_ON */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-2-0         :2019-01-29                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
