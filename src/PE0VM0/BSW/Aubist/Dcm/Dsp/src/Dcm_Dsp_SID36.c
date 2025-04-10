/* Dcm_Dsp_SID36_c(v5-3-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID36/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

#if( DCM_SUPPORT_SID36 == STD_ON )

#include <Dcm/Dcm_Dsp_SID36.h>
#include <Dcm/Dcm_Dsp_SID36_Callout.h>
#include "../../Dsp/cfg/Dcm_Dsp_SID36_Cfg.h"
#include <Dcm/Dcm_Dsp_DataTfrMng.h>
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Main_EvtDistr.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Request Information */
#define DCM_DSP_SID36_REQ_LEN_MIN_DL    ((Dcm_MsgLenType)0x00000002U) /* blockSequenceCounter +                */
                                                                      /* transferRequestParameterRecord(1byte) */
#if ( DCM_UL_PROCESS_USE == STD_ON )
#define DCM_DSP_SID36_REQ_LEN_UL    ((Dcm_MsgLenType)0x00000001U)     /* blockSequenceCounter                  */
#endif /* DCM_UL_PROCESS_USE == STD_ON */
#define DCM_DSP_SID36_REQ_LEN_BSC       ((uint32)1U)
#define DCM_DSP_SID36_REQ_DATA_NEXTBSC  ((uint8)1U)
#define DCM_DSP_SID36_REQ_DATA_MAXBSC   ((uint8)0xFFU)
#define DCM_DSP_SID36_REQ_DATA_MINBSC   ((uint8)0x00U)
#define DCM_DSP_SID36_REQ_POS_BSC       ((uint8)0x00U)
#define DCM_DSP_SID36_REQ_POS_TRPR      ((uint8)0x01U)

/* Response Information */
#define DCM_DSP_SID36_RES_POS_BSC       ((uint8)0U)
#if ( DCM_UL_PROCESS_USE == STD_ON )
#define DCM_DSP_SID36_RES_POS_TRPR      ((uint8)1U)
#endif /* DCM_UL_PROCESS_USE == STD_ON */
#define DCM_DSP_SID36_RES_LEN_BSC       ((uint32)1U)

#if ( DCM_UL_PROCESS_USE == STD_ON )
/* Process Information */
#define DCM_DSP_SID36_REQ_PROC_INIT     ((uint8)0U)
#define DCM_DSP_SID36_REQ_PROC_DL       ((uint8)1U)
#define DCM_DSP_SID36_REQ_PROC_UL       ((uint8)2U)
#endif /* DCM_UL_PROCESS_USE == STD_ON */

#define DCM_DSP_SID36_BSC_START_VALUE   ((uint8)0x01U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID36_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID36_ChkMsgLen
(
    const Dcm_OpStatusType u1OpStatus,
    const uint8 u1MemoryIdentifier,
    const uint32 u4MemoryAddress
);

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID36_ChkReqSequence
(
    const Dcm_OpStatusType u1OpStatus,
    const uint8 u1MemoryIdentifier,
    const uint32 u4MemoryAddress
);

#if ( DCM_UL_PROCESS_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID36_ChkReqSequenceUpLoad
(
    const Dcm_OpStatusType u1OpStatus,
    const uint8 u1MemoryIdentifier,
    const uint32 u4MemoryAddress
);
#endif /* DCM_UL_PROCESS_USE == STD_ON */

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID36_ChkTfrDataSuspended
(
    const Dcm_OpStatusType u1OpStatus,
    const uint8 u1MemoryIdentifier,
    const uint32 u4MemoryAddress
);

#if ( DCM_UL_PROCESS_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID36_ChkTfrDataSuspendedUpLoad
(
    const Dcm_OpStatusType u1OpStatus,
    const uint8 u1MemoryIdentifier,
    const uint32 u4MemoryAddress
);
#endif /* DCM_UL_PROCESS_USE == STD_ON */

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID36_ChkBsc
(
    uint8 u1LatestBsc,
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA ) ptBscUpdated
);

#if ( DCM_UL_PROCESS_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID36_ChkBscUpLoad
(
    uint8 u1LatestBsc
);
#endif /* DCM_UL_PROCESS_USE == STD_ON */

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID36_TfrDataWriteProc
(
    const Dcm_OpStatusType u1OpStatus
);

#if ( DCM_UL_PROCESS_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID36_TfrDataReadProc
(
    const Dcm_OpStatusType u1OpStatus
);
#endif /* DCM_UL_PROCESS_USE == STD_ON */

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID36_CancelProc
( void );

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_SID36_u1Bsc;
#if ( DCM_UL_PROCESS_USE == STD_ON )
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_SID36_u1ProcessRequest;
#endif /* DCM_UL_PROCESS_USE == STD_ON */

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
/* Function Name | Dcm_Dsp_SID36_Init                                       */
/* Description   | SID36 initialization                                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_UL_PROCESS_USE == STD_OFF )
FUNC( void, DCM_CODE ) Dcm_Dsp_SID36_Init
( void )
{
    Dcm_Dsp_SID36_u1Bsc = (uint8)0x00U;

    return;
}
#endif /* DCM_UL_PROCESS_USE == STD_OFF */
#if ( DCM_UL_PROCESS_USE == STD_ON )
FUNC( void, DCM_CODE ) Dcm_Dsp_SID36_Init
( void )
{
    Dcm_Dsp_SID36_u1Bsc = (uint8)0x00U;
    Dcm_Dsp_SID36_u1ProcessRequest = DCM_DSP_SID36_REQ_PROC_INIT;

    return;
}
#endif /* DCM_UL_PROCESS_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_SID36                                                */
/* Description   | Request processing of SID36                              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus    : Operation state                       */
/*               | [IN] pMsgContext : Message Context                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : Processing normal                      */
/*               |   DCM_E_PENDING : Pending                                */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_UL_PROCESS_USE == STD_OFF )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID36
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType  u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID36_InitialProc( pMsgContext );
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID36_CancelProc();
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_FORCE_RCRRP_OK )
    {
        u1_RetVal = Dcm_Dsp_SID36_TfrDataWriteProc( DCM_FORCE_RCRRP_OK );
    }
    else
    {
        /* no process */
    }

    if( u1_RetVal == (Std_ReturnType)E_NOT_OK )
    {
        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_UL_PROCESS_USE == STD_OFF */
#if ( DCM_UL_PROCESS_USE == STD_ON )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID36
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType  u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID36_InitialProc( pMsgContext );
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID36_CancelProc();
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_FORCE_RCRRP_OK )
    {
        if( Dcm_Dsp_SID36_u1ProcessRequest == DCM_DSP_SID36_REQ_PROC_UL )
        {
            u1_RetVal = Dcm_Dsp_SID36_TfrDataReadProc( DCM_FORCE_RCRRP_OK );
        }
        else
        {
            u1_RetVal = Dcm_Dsp_SID36_TfrDataWriteProc( DCM_FORCE_RCRRP_OK );
        }
    }
    else
    {
        /* no process */
    }

    if( u1_RetVal == (Std_ReturnType)E_NOT_OK )
    {
        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_UL_PROCESS_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID36_ChkMsgLenCbk                               */
/* Description   | Callback function for event delivery registration of     */
/*               | Xxx_CheckMessageLength                                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID36_ChkMsgLenCbk
(
    const uint8 u1EventId
)
{
    Dcm_Dsp_DataTfrMng_TfrInfoType  st_TfrInfo;
    uint8                           u1_NrcHandlingType;
    Std_ReturnType                  u1_RetVal;
    boolean                         b_BscUpdatedFlag;

    Dcm_Dsp_DataTfrMng_GetTfrInfo( &st_TfrInfo );
    u1_RetVal = Dcm_Dsp_SID36_ChkMsgLen( DCM_PENDING,
                                         st_TfrInfo.u1MemoryId,
                                         st_TfrInfo.u4MemoryAddress );
    if( u1_RetVal == (Std_ReturnType)E_OK )
    {
        u1_RetVal = Dcm_Dsp_SID36_ChkReqSequence( DCM_INITIAL,
                                                  st_TfrInfo.u1MemoryId,
                                                  st_TfrInfo.u4MemoryAddress );
        if( u1_RetVal == (Std_ReturnType)E_OK )
        {
            u1_NrcHandlingType = Dcm_Dsp_SID36_u1NrcHandlingType;
            if( u1_NrcHandlingType == DCM_DSP_SID36_NRCHANDLING_TYPE1 )
            {
                u1_RetVal = Dcm_Dsp_SID36_ChkTfrDataSuspended( DCM_INITIAL,
                                                               st_TfrInfo.u1MemoryId,
                                                               st_TfrInfo.u4MemoryAddress );
                if( u1_RetVal == (Std_ReturnType)E_OK )
                {
                    u1_RetVal = Dcm_Dsp_SID36_ChkBsc( st_TfrInfo.u1Bsc,
                                                      &b_BscUpdatedFlag );
                    if( u1_RetVal == (Std_ReturnType)E_OK )
                    {
                        if( b_BscUpdatedFlag == (boolean)TRUE )
                        {
                            (void)Dcm_Dsp_SID36_TfrDataWriteProc( DCM_INITIAL );                    /* no return check required */
                        }
                    }
                }
            }
            else
            {
                u1_RetVal = Dcm_Dsp_SID36_ChkBsc( st_TfrInfo.u1Bsc,
                                                  &b_BscUpdatedFlag );
                if( u1_RetVal == (Std_ReturnType)E_OK )
                {
                    if( b_BscUpdatedFlag == (boolean)TRUE )
                    {
                        u1_RetVal = Dcm_Dsp_SID36_ChkTfrDataSuspended( DCM_INITIAL,
                                                                       st_TfrInfo.u1MemoryId,
                                                                       st_TfrInfo.u4MemoryAddress );
                        if( u1_RetVal == (Std_ReturnType)E_OK )
                        {
                            (void)Dcm_Dsp_SID36_TfrDataWriteProc( DCM_INITIAL );                    /* no return check required */
                        }
                    }
                }
            }
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID36_ChkReqSequenceCbk                          */
/* Description   | Callback function for event delivery registration of     */
/*               | Xxx_CheckRequestSequence                                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID36_ChkReqSequenceCbk
(
    const uint8 u1EventId
)
{
    Dcm_Dsp_DataTfrMng_TfrInfoType  st_TfrInfo;
    uint8                           u1_NrcHandlingType;
    Std_ReturnType                  u1_RetVal;
    boolean                         b_BscUpdatedFlag;

    Dcm_Dsp_DataTfrMng_GetTfrInfo( &st_TfrInfo );
    u1_RetVal = Dcm_Dsp_SID36_ChkReqSequence( DCM_PENDING,
                                              st_TfrInfo.u1MemoryId,
                                              st_TfrInfo.u4MemoryAddress );
    if( u1_RetVal == (Std_ReturnType)E_OK )
    {
        u1_NrcHandlingType = Dcm_Dsp_SID36_u1NrcHandlingType;
        if( u1_NrcHandlingType == DCM_DSP_SID36_NRCHANDLING_TYPE1 )
        {
            u1_RetVal = Dcm_Dsp_SID36_ChkTfrDataSuspended( DCM_INITIAL,
                                                           st_TfrInfo.u1MemoryId,
                                                           st_TfrInfo.u4MemoryAddress );
            if( u1_RetVal == (Std_ReturnType)E_OK )
            {
                u1_RetVal = Dcm_Dsp_SID36_ChkBsc( st_TfrInfo.u1Bsc,
                                                  &b_BscUpdatedFlag );
                if( u1_RetVal == (Std_ReturnType)E_OK )
                {
                    if( b_BscUpdatedFlag == (boolean)TRUE )
                    {
                        (void)Dcm_Dsp_SID36_TfrDataWriteProc( DCM_INITIAL );                    /* no return check required */
                    }
                }
            }
        }
        else
        {
            u1_RetVal = Dcm_Dsp_SID36_ChkBsc( st_TfrInfo.u1Bsc,
                                              &b_BscUpdatedFlag );
            if( u1_RetVal == (Std_ReturnType)E_OK )
            {
                if( b_BscUpdatedFlag == (boolean)TRUE )
                {
                    u1_RetVal = Dcm_Dsp_SID36_ChkTfrDataSuspended( DCM_INITIAL,
                                                                   st_TfrInfo.u1MemoryId,
                                                                   st_TfrInfo.u4MemoryAddress );
                    if( u1_RetVal == (Std_ReturnType)E_OK )
                    {
                        (void)Dcm_Dsp_SID36_TfrDataWriteProc( DCM_INITIAL );                    /* no return check required */
                    }
                }
            }
        }
    }

    return;
}

#if ( DCM_UL_PROCESS_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID36_ChkReqSequenceUpLoadCbk                    */
/* Description   | Callback function for event delivery registration of     */
/*               | Xxx_CheckRequestSequence at upload                       */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID36_ChkReqSequenceUpLoadCbk
(
    const uint8 u1EventId
)
{
    Dcm_Dsp_DataTfrMng_TfrInfoType  st_TfrInfo;
    uint8                           u1_NrcHandlingType;
    Std_ReturnType                  u1_RetVal;

    Dcm_Dsp_DataTfrMng_GetTfrInfo( &st_TfrInfo );
    u1_RetVal = Dcm_Dsp_SID36_ChkReqSequenceUpLoad( DCM_PENDING,
                                                    st_TfrInfo.u1MemoryId,
                                                    st_TfrInfo.u4MemoryAddress );
    if( u1_RetVal == (Std_ReturnType)E_OK )
    {
        u1_NrcHandlingType = Dcm_Dsp_SID36_u1NrcHandlingType;
        if( u1_NrcHandlingType == DCM_DSP_SID36_NRCHANDLING_TYPE1 )
        {
            u1_RetVal = Dcm_Dsp_SID36_ChkTfrDataSuspendedUpLoad( DCM_INITIAL,
                                                                 st_TfrInfo.u1MemoryId,
                                                                 st_TfrInfo.u4MemoryAddress );
            if( u1_RetVal == (Std_ReturnType)E_OK )
            {
                u1_RetVal = Dcm_Dsp_SID36_ChkBscUpLoad ( st_TfrInfo.u1Bsc );
                if( u1_RetVal == (Std_ReturnType)E_OK )
                {
                    (void)Dcm_Dsp_SID36_TfrDataReadProc( DCM_INITIAL );                     /* no return check required */
                }
            }
        }
        else
        {
            u1_RetVal = Dcm_Dsp_SID36_ChkBscUpLoad( st_TfrInfo.u1Bsc );
            if( u1_RetVal == (Std_ReturnType)E_OK )
            {
                u1_RetVal = Dcm_Dsp_SID36_ChkTfrDataSuspendedUpLoad( DCM_INITIAL,
                                                                     st_TfrInfo.u1MemoryId,
                                                                     st_TfrInfo.u4MemoryAddress );
                if( u1_RetVal == (Std_ReturnType)E_OK )
                {
                    (void)Dcm_Dsp_SID36_TfrDataReadProc( DCM_INITIAL );                     /* no return check required */
                }
            }
        }
    }

    return;
}
#endif  /* DCM_UL_PROCESS_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID36_ChkTfrDataSuspendedCbk                     */
/* Description   | Callback function for event delivery registration of     */
/*               | Xxx_CheckTransferDataSuspended                           */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID36_ChkTfrDataSuspendedCbk
(
    const uint8 u1EventId
)
{
    Dcm_Dsp_DataTfrMng_TfrInfoType  st_TfrInfo;
    uint8                           u1_NrcHandlingType;
    Std_ReturnType                  u1_RetVal;
    boolean                         b_BscUpdatedFlag;

    u1_NrcHandlingType = Dcm_Dsp_SID36_u1NrcHandlingType;

    Dcm_Dsp_DataTfrMng_GetTfrInfo( &st_TfrInfo );
    if( u1_NrcHandlingType == DCM_DSP_SID36_NRCHANDLING_TYPE1 )
    {
        u1_RetVal = Dcm_Dsp_SID36_ChkTfrDataSuspended( DCM_PENDING,
                                                       st_TfrInfo.u1MemoryId,
                                                       st_TfrInfo.u4MemoryAddress );
        if( u1_RetVal == (Std_ReturnType)E_OK )
        {
            u1_RetVal = Dcm_Dsp_SID36_ChkBsc( st_TfrInfo.u1Bsc,
                                              &b_BscUpdatedFlag );
            if( u1_RetVal == (Std_ReturnType)E_OK )
            {
                if( b_BscUpdatedFlag == (boolean)TRUE )
                {
                    (void)Dcm_Dsp_SID36_TfrDataWriteProc( DCM_INITIAL );                /* no return check required */
                }
            }
        }
    }
    else
    {
        u1_RetVal = Dcm_Dsp_SID36_ChkTfrDataSuspended( DCM_PENDING,
                                                       st_TfrInfo.u1MemoryId,
                                                       st_TfrInfo.u4MemoryAddress );
        if( u1_RetVal == (Std_ReturnType)E_OK )
        {
            (void)Dcm_Dsp_SID36_TfrDataWriteProc( DCM_INITIAL );                        /* no return check required */
        }
    }

    return;
}

#if ( DCM_UL_PROCESS_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID36_ChkTfrDataSuspendedUpLoadCbk               */
/* Description   | Callback function for event delivery registration of     */
/*               | Xxx_CheckTransferDataSuspended at upload                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID36_ChkTfrDataSuspendedUpLoadCbk
(
    const uint8 u1EventId
)
{
    Dcm_Dsp_DataTfrMng_TfrInfoType  st_TfrInfo;
    uint8                           u1_NrcHandlingType;
    Std_ReturnType                  u1_RetVal;

    u1_NrcHandlingType = Dcm_Dsp_SID36_u1NrcHandlingType;

    Dcm_Dsp_DataTfrMng_GetTfrInfo( &st_TfrInfo );
    if( u1_NrcHandlingType == DCM_DSP_SID36_NRCHANDLING_TYPE1 )
    {
        u1_RetVal = Dcm_Dsp_SID36_ChkTfrDataSuspendedUpLoad( DCM_PENDING,
                                                             st_TfrInfo.u1MemoryId,
                                                             st_TfrInfo.u4MemoryAddress );
        if( u1_RetVal == (Std_ReturnType)E_OK )
        {
            u1_RetVal = Dcm_Dsp_SID36_ChkBscUpLoad( st_TfrInfo.u1Bsc );
            if( u1_RetVal == (Std_ReturnType)E_OK )
            {
                (void)Dcm_Dsp_SID36_TfrDataReadProc( DCM_INITIAL );             /* no return check required */
            }
        }
    }
    else
    {
        u1_RetVal = Dcm_Dsp_SID36_ChkTfrDataSuspendedUpLoad( DCM_PENDING,
                                                             st_TfrInfo.u1MemoryId,
                                                             st_TfrInfo.u4MemoryAddress );
        if( u1_RetVal == (Std_ReturnType)E_OK )
        {
            (void)Dcm_Dsp_SID36_TfrDataReadProc( DCM_INITIAL );                 /* no return check required */
        }
    }

    return;
}
#endif  /* DCM_UL_PROCESS_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID36_ProcTfrDataWriteCbk                        */
/* Description   | Callback function for event delivery registration of     */
/*               | Xxx_ProcessTransferDataWrite                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID36_ProcTfrDataWriteCbk
(
    const uint8 u1EventId
)
{
    (void)Dcm_Dsp_SID36_TfrDataWriteProc( DCM_PENDING );                /* no return check required */

    return;
}

#if ( DCM_UL_PROCESS_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID36_ProcTfrDataReadCbk                         */
/* Description   | Callback function for event delivery registration of     */
/*               | Xxx_ProcessTransferDataRead                              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID36_ProcTfrDataReadCbk
(
    const uint8 u1EventId
)
{
    (void)Dcm_Dsp_SID36_TfrDataReadProc( DCM_PENDING );                /* no return check required */

    return;
}
#endif  /* DCM_UL_PROCESS_USE == STD_ON */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID36_InitialProc                                */
/* Description   | Initial process of SID36                                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext : Message Context                      */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : Processing normal                      */
/*               |   E_NOT_OK      : Processing not normal                  */
/*               |   DCM_E_PENDING : Pending                                */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_UL_PROCESS_USE == STD_OFF )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID36_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Dcm_Dsp_DataTfrMng_TfrInfoType  st_TfrInfo;
    uint8                           u1_TfrStatus;
    uint8                           u1_NrcHandlingType;
    Std_ReturnType                  u1_RetVal;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    boolean                         b_BscUpdatedFlag;
    boolean                         b_ChkSeqBeforeMinLenChk;
    boolean                         b_SendNegResFlag;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    u1_RetVal = E_OK;
    u1_ErrorCode = DCM_E_GENERALREJECT;
    b_SendNegResFlag = (boolean)FALSE;

    u1_TfrStatus = Dcm_Dsp_DataTfrMng_GetTfrStatus();
    if( ( u1_TfrStatus == DCM_TFR_DL_START )||( u1_TfrStatus == DCM_TFR_DL_PROCEED ) )
    {
        if( Dcm_Dsp_Main_stMsgContext.reqDataLen >= DCM_DSP_SID36_REQ_LEN_MIN_DL )
        {
            Dcm_Dsp_SID36_u1Bsc = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID36_REQ_POS_BSC];
            Dcm_Dsp_DataTfrMng_GetTfrInfo( &st_TfrInfo );
            u1_RetVal = Dcm_Dsp_SID36_ChkMsgLen( DCM_INITIAL,
                                                 st_TfrInfo.u1MemoryId,
                                                 st_TfrInfo.u4MemoryAddress );
            if( u1_RetVal == (Std_ReturnType)E_OK )
            {
                u1_RetVal = Dcm_Dsp_SID36_ChkReqSequence( DCM_INITIAL,
                                                          st_TfrInfo.u1MemoryId,
                                                          st_TfrInfo.u4MemoryAddress );
                if( u1_RetVal == (Std_ReturnType)E_OK )
                {
                    u1_NrcHandlingType = Dcm_Dsp_SID36_u1NrcHandlingType;
                    if( u1_NrcHandlingType == DCM_DSP_SID36_NRCHANDLING_TYPE1 )
                    {
                        u1_RetVal = Dcm_Dsp_SID36_ChkTfrDataSuspended( DCM_INITIAL,
                                                                       st_TfrInfo.u1MemoryId,
                                                                       st_TfrInfo.u4MemoryAddress );
                        if( u1_RetVal == (Std_ReturnType)E_OK )
                        {
                            u1_RetVal = Dcm_Dsp_SID36_ChkBsc( st_TfrInfo.u1Bsc,
                                                              &b_BscUpdatedFlag );
                            if( u1_RetVal == (Std_ReturnType)E_OK )
                            {
                                if( b_BscUpdatedFlag == (boolean)TRUE )
                                {
                                    u1_RetVal = Dcm_Dsp_SID36_TfrDataWriteProc( DCM_INITIAL );
                                }
                            }
                        }
                    }
                    else
                    {
                        u1_RetVal = Dcm_Dsp_SID36_ChkBsc( st_TfrInfo.u1Bsc,
                                                          &b_BscUpdatedFlag );
                        if( u1_RetVal == (Std_ReturnType)E_OK )
                        {
                            if( b_BscUpdatedFlag == (boolean)TRUE )
                            {
                                u1_RetVal = Dcm_Dsp_SID36_ChkTfrDataSuspended( DCM_INITIAL,
                                                                               st_TfrInfo.u1MemoryId,
                                                                               st_TfrInfo.u4MemoryAddress );
                                if( u1_RetVal == (Std_ReturnType)E_OK )
                                {
                                    u1_RetVal = Dcm_Dsp_SID36_TfrDataWriteProc( DCM_INITIAL );
                                }
                            }
                        }
                    }
                }
            }
        }
        else
        {
            /* NRC0x13 */
            u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            b_SendNegResFlag = (boolean)TRUE;
        }
    }
    else
    {
        b_ChkSeqBeforeMinLenChk = Dcm_Dsp_SID36_bCheckSeqBeforeMinLenCheck;
        if( b_ChkSeqBeforeMinLenChk == (boolean)FALSE )
        {
            if( Dcm_Dsp_Main_stMsgContext.reqDataLen >= DCM_DSP_SID36_REQ_LEN_MIN_DL )
            {
                /* NRC0x24 */
                u1_ErrorCode = DCM_E_REQUESTSEQUENCEERROR;
                b_SendNegResFlag = (boolean)TRUE;
            }
            else
            {
                /* NRC0x13 */
                u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                b_SendNegResFlag = (boolean)TRUE;
            }
        }
        else
        {
            /* NRC0x24 */
            u1_ErrorCode = DCM_E_REQUESTSEQUENCEERROR;
            b_SendNegResFlag = (boolean)TRUE;
        }
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     u1_ErrorCode );
    }

    return u1_RetVal;
}
#endif /* DCM_UL_PROCESS_USE == STD_OFF */
#if ( DCM_UL_PROCESS_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID36_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Dcm_Dsp_DataTfrMng_TfrInfoType  st_TfrInfo;
    uint8                           u1_TfrStatus;
    uint8                           u1_NrcHandlingType;
    Std_ReturnType                  u1_RetVal;
    Dcm_NegativeResponseCodeType    u1_ErrorCode;
    boolean                         b_BscUpdatedFlag;
    boolean                         b_ChkSeqBeforeMinLenChk;
    boolean                         b_SendNegResFlag;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    u1_RetVal = E_OK;
    u1_ErrorCode = DCM_E_GENERALREJECT;
    b_SendNegResFlag = (boolean)FALSE;

    u1_TfrStatus = Dcm_Dsp_DataTfrMng_GetTfrStatus();
    if( ( u1_TfrStatus == DCM_TFR_DL_START )||( u1_TfrStatus == DCM_TFR_DL_PROCEED ) )
    {
        Dcm_Dsp_SID36_u1ProcessRequest = DCM_DSP_SID36_REQ_PROC_DL;
        if( Dcm_Dsp_Main_stMsgContext.reqDataLen >= DCM_DSP_SID36_REQ_LEN_MIN_DL )
        {
            Dcm_Dsp_SID36_u1Bsc = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID36_REQ_POS_BSC];
            Dcm_Dsp_DataTfrMng_GetTfrInfo( &st_TfrInfo );
            u1_RetVal = Dcm_Dsp_SID36_ChkMsgLen( DCM_INITIAL,
                                                 st_TfrInfo.u1MemoryId,
                                                 st_TfrInfo.u4MemoryAddress );
            if( u1_RetVal == (Std_ReturnType)E_OK )
            {
                u1_RetVal = Dcm_Dsp_SID36_ChkReqSequence( DCM_INITIAL,
                                                          st_TfrInfo.u1MemoryId,
                                                          st_TfrInfo.u4MemoryAddress );
                if( u1_RetVal == (Std_ReturnType)E_OK )
                {
                    u1_NrcHandlingType = Dcm_Dsp_SID36_u1NrcHandlingType;
                    if( u1_NrcHandlingType == DCM_DSP_SID36_NRCHANDLING_TYPE1 )
                    {
                        u1_RetVal = Dcm_Dsp_SID36_ChkTfrDataSuspended( DCM_INITIAL,
                                                                       st_TfrInfo.u1MemoryId,
                                                                       st_TfrInfo.u4MemoryAddress );
                        if( u1_RetVal == (Std_ReturnType)E_OK )
                        {
                            u1_RetVal = Dcm_Dsp_SID36_ChkBsc( st_TfrInfo.u1Bsc,
                                                              &b_BscUpdatedFlag );
                            if( u1_RetVal == (Std_ReturnType)E_OK )
                            {
                                if( b_BscUpdatedFlag == (boolean)TRUE )
                                {
                                    u1_RetVal = Dcm_Dsp_SID36_TfrDataWriteProc( DCM_INITIAL );
                                }
                            }
                        }
                    }
                    else
                    {
                        u1_RetVal = Dcm_Dsp_SID36_ChkBsc( st_TfrInfo.u1Bsc,
                                                          &b_BscUpdatedFlag );
                        if( u1_RetVal == (Std_ReturnType)E_OK )
                        {
                            if( b_BscUpdatedFlag == (boolean)TRUE )
                            {
                                u1_RetVal = Dcm_Dsp_SID36_ChkTfrDataSuspended( DCM_INITIAL,
                                                                               st_TfrInfo.u1MemoryId,
                                                                               st_TfrInfo.u4MemoryAddress );
                                if( u1_RetVal == (Std_ReturnType)E_OK )
                                {
                                    u1_RetVal = Dcm_Dsp_SID36_TfrDataWriteProc( DCM_INITIAL );
                                }
                            }
                        }
                    }
                }
            }
        }
        else
        {
            /* NRC0x13 */
            u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            b_SendNegResFlag = (boolean)TRUE;
        }
    }
    else if( ( u1_TfrStatus == DCM_TFR_UL_START )||( u1_TfrStatus == DCM_TFR_UL_PROCEED ) )
    {
        Dcm_Dsp_SID36_u1ProcessRequest = DCM_DSP_SID36_REQ_PROC_UL;
        if( Dcm_Dsp_Main_stMsgContext.reqDataLen == DCM_DSP_SID36_REQ_LEN_UL )
        {
            Dcm_Dsp_SID36_u1Bsc = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID36_REQ_POS_BSC];
            Dcm_Dsp_DataTfrMng_GetTfrInfo( &st_TfrInfo );
            u1_RetVal = Dcm_Dsp_SID36_ChkReqSequenceUpLoad( DCM_INITIAL,
                                                            st_TfrInfo.u1MemoryId,
                                                            st_TfrInfo.u4MemoryAddress );
            if( u1_RetVal == (Std_ReturnType)E_OK )
            {
                u1_NrcHandlingType = Dcm_Dsp_SID36_u1NrcHandlingType;
                if( u1_NrcHandlingType == DCM_DSP_SID36_NRCHANDLING_TYPE1 )
                {
                    u1_RetVal = Dcm_Dsp_SID36_ChkTfrDataSuspendedUpLoad( DCM_INITIAL,
                                                                         st_TfrInfo.u1MemoryId,
                                                                         st_TfrInfo.u4MemoryAddress );
                    if( u1_RetVal == (Std_ReturnType)E_OK )
                    {
                        u1_RetVal = Dcm_Dsp_SID36_ChkBscUpLoad( st_TfrInfo.u1Bsc );
                        if( u1_RetVal == (Std_ReturnType)E_OK )
                        {
                            u1_RetVal = Dcm_Dsp_SID36_TfrDataReadProc( DCM_INITIAL );
                        }
                    }
                }
                else
                {
                    u1_RetVal = Dcm_Dsp_SID36_ChkBscUpLoad( st_TfrInfo.u1Bsc );
                    if( u1_RetVal == (Std_ReturnType)E_OK )
                    {
                        u1_RetVal = Dcm_Dsp_SID36_ChkTfrDataSuspendedUpLoad( DCM_INITIAL,
                                                                             st_TfrInfo.u1MemoryId,
                                                                             st_TfrInfo.u4MemoryAddress );
                        if( u1_RetVal == (Std_ReturnType)E_OK )
                        {
                            u1_RetVal = Dcm_Dsp_SID36_TfrDataReadProc( DCM_INITIAL );
                        }
                    }
                }
            }
        }
        else
        {
            /* NRC0x13 */
            u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            b_SendNegResFlag = (boolean)TRUE;
        }
    }
    else
    {
        b_ChkSeqBeforeMinLenChk = Dcm_Dsp_SID36_bCheckSeqBeforeMinLenCheck;
        if( b_ChkSeqBeforeMinLenChk == (boolean)FALSE )
        {
            if( Dcm_Dsp_Main_stMsgContext.reqDataLen >= DCM_DSP_SID36_REQ_LEN_MIN_DL )
            {
                /* NRC0x24 */
                u1_ErrorCode = DCM_E_REQUESTSEQUENCEERROR;
                b_SendNegResFlag = (boolean)TRUE;
            }
            else
            {
                /* NRC0x13 */
                u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                b_SendNegResFlag = (boolean)TRUE;
            }
        }
        else
        {
            /* NRC0x24 */
            u1_ErrorCode = DCM_E_REQUESTSEQUENCEERROR;
            b_SendNegResFlag = (boolean)TRUE;
        }
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     u1_ErrorCode );
    }

    return u1_RetVal;
}
#endif /* DCM_UL_PROCESS_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID36_ChkBsc                                     */
/* Description   | Check on blockSequenceCounter                            */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u1LatestBsc  : Latest blockSequenceCounter         */
/*               | [OUT] ptBscUpdated : Whether blockSequenseCounter is     */
/*               |                      updated                             */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK     : Check OK                                    */
/*               |   E_NOT_OK : Check NG                                    */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID36_ChkBsc
(
    uint8 u1LatestBsc,
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA ) ptBscUpdated
)
{
    uint8           u1_TfrStatus;
    uint8           u1_NextBsc;
    Std_ReturnType  u1_RetVal;

    u1_RetVal = E_NOT_OK;
    *ptBscUpdated = (boolean)FALSE;

    if( u1LatestBsc == DCM_DSP_SID36_REQ_DATA_MAXBSC )
    {
        u1_NextBsc = DCM_DSP_SID36_REQ_DATA_MINBSC;
    }
    else
    {
        u1_NextBsc = u1LatestBsc +
                     DCM_DSP_SID36_REQ_DATA_NEXTBSC;
    }
    u1_TfrStatus = Dcm_Dsp_DataTfrMng_GetTfrStatus();
    if( u1_TfrStatus == DCM_TFR_DL_START )
    {
        /* if first time of SID36, BSC  0x01 is Permitted  */
        if( Dcm_Dsp_SID36_u1Bsc == DCM_DSP_SID36_BSC_START_VALUE )
        {
            *ptBscUpdated = (boolean)TRUE;
            u1_RetVal = E_OK;
        }
        else
        {
            /* NRC0x73 */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                         DCM_E_WRONGBLOCKSEQUENCECOUNTER );
        }
    }
    else
    {
        if( Dcm_Dsp_SID36_u1Bsc == u1_NextBsc )
        {
            *ptBscUpdated = (boolean)TRUE;
            u1_RetVal = E_OK;
        }
        else if( Dcm_Dsp_SID36_u1Bsc == u1LatestBsc )
        {
            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID36_RES_POS_BSC] = Dcm_Dsp_SID36_u1Bsc;
            Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID36_RES_LEN_BSC;
            Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
            u1_RetVal = E_OK;
        }
        else
        {
            /* NRC0x73 */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                         DCM_E_WRONGBLOCKSEQUENCECOUNTER );
        }
    }

    return u1_RetVal;
}

#if ( DCM_UL_PROCESS_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID36_ChkBscUpLoad                               */
/* Description   | Check on blockSequenceCounter at upload                  */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u1LatestBsc  : Latest blockSequenceCounter         */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK     : Check OK                                    */
/*               |   E_NOT_OK : Check NG                                    */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID36_ChkBscUpLoad
(
    uint8 u1LatestBsc
)
{
    uint8           u1_TfrStatus;
    uint8           u1_NextBsc;
    Std_ReturnType  u1_RetVal;

    u1_RetVal = E_NOT_OK;

    if( u1LatestBsc == DCM_DSP_SID36_REQ_DATA_MAXBSC )
    {
        u1_NextBsc = DCM_DSP_SID36_REQ_DATA_MINBSC;
    }
    else
    {
        u1_NextBsc = u1LatestBsc +
                     DCM_DSP_SID36_REQ_DATA_NEXTBSC;
    }
    u1_TfrStatus = Dcm_Dsp_DataTfrMng_GetTfrStatus();
    if( u1_TfrStatus == DCM_TFR_UL_START )
    {
        /* if first time of SID36, BSC  0x01 is Permitted  */
        if( Dcm_Dsp_SID36_u1Bsc == DCM_DSP_SID36_BSC_START_VALUE )
        {
            u1_RetVal = E_OK;
        }
        else
        {
            /* NRC0x73 */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                         DCM_E_WRONGBLOCKSEQUENCECOUNTER );
        }
    }
    else
    {
        if( Dcm_Dsp_SID36_u1Bsc == u1_NextBsc )
        {
            u1_RetVal = E_OK;
        }
        else if( Dcm_Dsp_SID36_u1Bsc == u1LatestBsc )
        {
            u1_RetVal = E_OK;
        }
        else
        {
            /* NRC0x73 */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                         DCM_E_WRONGBLOCKSEQUENCECOUNTER );
        }
    }

    return u1_RetVal;
}
#endif /* DCM_UL_PROCESS_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID36_ChkMsgLen                                  */
/* Description   | Check whether requestMsg is appropriate                  */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus         : Operation state                */
/*               | [IN] u1MemoryIdentifier : Memory identifier              */
/*               | [IN] u4MemoryAddress    : Memory Address                 */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : Check was successful                   */
/*               |   E_NOT_OK      : Check was not successful               */
/*               |   DCM_E_PENDING : Check is not yet finished              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID36_ChkMsgLen
(
    const Dcm_OpStatusType u1OpStatus,
    const uint8 u1MemoryIdentifier,
    const uint32 u4MemoryAddress
)
{
    uint32          u4_MemorySize;
    Std_ReturnType  u1_RetVal;

    u4_MemorySize = Dcm_Dsp_Main_stMsgContext.reqDataLen -                              /* no wrap around */
                    DCM_DSP_SID36_REQ_LEN_BSC;
    u1_RetVal = Dcm_Dsp_SID36_CallCheckMessageLengthFnc( u1OpStatus,
                                                         Dcm_Dsp_SID36_u1Bsc,
                                                         u1MemoryIdentifier,
                                                         u4MemoryAddress,
                                                         u4_MemorySize,
                                                         &Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID36_REQ_POS_TRPR] );

    if( u1_RetVal == (Std_ReturnType)E_OK )
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }
    }
    else if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID36_CHKMSGLEN );               /* no return check required */
    }
    else if( u1_RetVal == (Std_ReturnType)E_NOT_OK )
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }
        /* NRC0x13 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
    }
    else
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }
        /* NRC0x10 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     DCM_E_GENERALREJECT );
        u1_RetVal = E_NOT_OK;
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID36_ChkReqSequence                             */
/* Description   | Check whether request sequence is correct                */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus         : Operation state                */
/*               | [IN] u1MemoryIdentifier : Memory identifier              */
/*               | [IN] u4MemoryAddress    : Memory Address                 */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : Check was successful                   */
/*               |   E_NOT_OK      : Check was not successful               */
/*               |   DCM_E_PENDING : Check is not yet finished              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID36_ChkReqSequence
(
    const Dcm_OpStatusType u1OpStatus,
    const uint8 u1MemoryIdentifier,
    const uint32 u4MemoryAddress
)
{
    uint32          u4_MemorySize;
    Std_ReturnType  u1_RetVal;

    u4_MemorySize = Dcm_Dsp_Main_stMsgContext.reqDataLen -                                   /* no wrap around */
                    DCM_DSP_SID36_REQ_LEN_BSC;
    u1_RetVal = Dcm_Dsp_SID36_CallCheckRequestSequenceFnc( u1OpStatus,
                                                           Dcm_Dsp_SID36_u1Bsc,
                                                           u1MemoryIdentifier,
                                                           u4MemoryAddress,
                                                           u4_MemorySize,
                                                           &Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID36_REQ_POS_TRPR] );

    if( u1_RetVal == (Std_ReturnType)E_OK )
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }
    }
    else if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID36_CHKREQSEQUENCE );               /* no return check required */
    }
    else if( u1_RetVal == (Std_ReturnType)E_NOT_OK )
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }

        /* NRC0x24 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     DCM_E_REQUESTSEQUENCEERROR );
    }
    else
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }

        /* NRC0x10 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     DCM_E_GENERALREJECT );

        u1_RetVal = E_NOT_OK;
    }

    return u1_RetVal;
}

#if ( DCM_UL_PROCESS_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID36_ChkReqSequenceUpLoad                       */
/* Description   | Check whether request sequence is correct at upload      */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus         : Operation state                */
/*               | [IN] u1MemoryIdentifier : Memory identifier              */
/*               | [IN] u4MemoryAddress    : Memory Address                 */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : Check was successful                   */
/*               |   E_NOT_OK      : Check was not successful               */
/*               |   DCM_E_PENDING : Check is not yet finished              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID36_ChkReqSequenceUpLoad
(
    const Dcm_OpStatusType u1OpStatus,
    const uint8 u1MemoryIdentifier,
    const uint32 u4MemoryAddress
)
{
    uint32          u4_MemorySize;
    uint8           u1_DummyMemoryData;
    Std_ReturnType  u1_RetVal;

    u4_MemorySize      = (uint32)0x00000000U;
    u1_DummyMemoryData = (uint8)0U;
    
    u1_RetVal = Dcm_Dsp_SID36_CallCheckRequestSequenceFnc( u1OpStatus,
                                                           Dcm_Dsp_SID36_u1Bsc,
                                                           u1MemoryIdentifier,
                                                           u4MemoryAddress,
                                                           u4_MemorySize,
                                                           &u1_DummyMemoryData );

    if( u1_RetVal == (Std_ReturnType)E_OK )
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }
    }
    else if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID36_CHKREQSEQUENCEUL );               /* no return check required */
    }
    else if( u1_RetVal == (Std_ReturnType)E_NOT_OK )
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }

        /* NRC0x24 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     DCM_E_REQUESTSEQUENCEERROR );
    }
    else
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }

        /* NRC0x10 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     DCM_E_GENERALREJECT );

        u1_RetVal = E_NOT_OK;
    }

    return u1_RetVal;
}
#endif  /* DCM_UL_PROCESS_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID36_ChkTfrDataSuspended                        */
/* Description   | Check whether transfer data is not suspended             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus         : Operation state                */
/*               | [IN] u1MemoryIdentifier : Memory identifier              */
/*               | [IN] u4MemoryAddress    : Memory Address                 */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : Check was successful                   */
/*               |   E_NOT_OK      : Check was not successful               */
/*               |   DCM_E_PENDING : Check is not yet finished              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID36_ChkTfrDataSuspended
(
    const Dcm_OpStatusType u1OpStatus,
    const uint8 u1MemoryIdentifier,
    const uint32 u4MemoryAddress
)
{
    uint32          u4_MemorySize;
    Std_ReturnType  u1_RetVal;

    u4_MemorySize = Dcm_Dsp_Main_stMsgContext.reqDataLen -                                     /* no wrap around */
                    DCM_DSP_SID36_REQ_LEN_BSC;
    u1_RetVal = Dcm_Dsp_SID36_CallCheckTransferDataSuspendedFnc( u1OpStatus,
                                                                 Dcm_Dsp_SID36_u1Bsc,
                                                                 u1MemoryIdentifier,
                                                                 u4MemoryAddress,
                                                                 u4_MemorySize,
                                                                 &Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID36_REQ_POS_TRPR] );

    if( u1_RetVal == (Std_ReturnType)E_OK )
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }
    }
    else if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID36_CHKTFRDATSUSPEND );               /* no return check required */
    }
    else if( u1_RetVal == (Std_ReturnType)E_NOT_OK )
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }

        /* NRC0x71 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     DCM_E_TRANSFERDATASUSPENDED );
    }
    else
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }

        /* NRC0x10 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     DCM_E_GENERALREJECT );

        u1_RetVal = E_NOT_OK;
    }

    return u1_RetVal;
}

#if ( DCM_UL_PROCESS_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID36_ChkTfrDataSuspendedUpLoad                  */
/* Description   | Check whether transfer data is not suspended at upload   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus         : Operation state                */
/*               | [IN] u1MemoryIdentifier : Memory identifier              */
/*               | [IN] u4MemoryAddress    : Memory Address                 */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : Check was successful                   */
/*               |   E_NOT_OK      : Check was not successful               */
/*               |   DCM_E_PENDING : Check is not yet finished              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID36_ChkTfrDataSuspendedUpLoad
(
    const Dcm_OpStatusType u1OpStatus,
    const uint8 u1MemoryIdentifier,
    const uint32 u4MemoryAddress
)
{
    uint32          u4_MemorySize;
    uint8           u1_DummyMemoryData;
    Std_ReturnType  u1_RetVal;

    u4_MemorySize      = (uint32)0x00000000U;
    u1_DummyMemoryData = (uint8)0U;
    
    u1_RetVal = Dcm_Dsp_SID36_CallCheckTransferDataSuspendedFnc( u1OpStatus,
                                                                 Dcm_Dsp_SID36_u1Bsc,
                                                                 u1MemoryIdentifier,
                                                                 u4MemoryAddress,
                                                                 u4_MemorySize,
                                                                 &u1_DummyMemoryData );

    if( u1_RetVal == (Std_ReturnType)E_OK )
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }
    }
    else if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID36_CHKTFRDATSUSPENDUL );               /* no return check required */
    }
    else if( u1_RetVal == (Std_ReturnType)E_NOT_OK )
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }

        /* NRC0x71 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     DCM_E_TRANSFERDATASUSPENDED );
    }
    else
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }

        /* NRC0x10 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     DCM_E_GENERALREJECT );

        u1_RetVal = E_NOT_OK;
    }

    return u1_RetVal;
}
#endif  /* DCM_UL_PROCESS_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID36_TfrDataWriteProc                           */
/* Description   | Process of writing transferdata                          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus : Operation state                        */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : Write was successful                   */
/*               |   E_NOT_OK      : Write was not successful               */
/*               |   DCM_E_PENDING : Write is not yet finished              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID36_TfrDataWriteProc
(
    const Dcm_OpStatusType u1OpStatus
)
{
    uint32                        u4_MemorySize;
    Std_ReturnType                u1_RetVal;
    Dcm_ReturnWriteMemoryType     u1_RetProcTfrDataWrite;
    Dcm_NegativeResponseCodeType  u1_ErrorCode;

    u1_RetVal = E_NOT_OK;
    u1_ErrorCode = DCM_E_GENERALREJECT;

    u4_MemorySize = Dcm_Dsp_Main_stMsgContext.reqDataLen -                                     /* no wrap around */
                    DCM_DSP_SID36_REQ_LEN_BSC;
    u1_RetProcTfrDataWrite = Dcm_Dsp_DataTfrMng_ProcTfrDataWrite( u1OpStatus,
                                                                  Dcm_Dsp_SID36_u1Bsc,
                                                                  u4_MemorySize,
                                                                  &Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID36_REQ_POS_TRPR],
                                                                  &u1_ErrorCode );
    if( u1_RetProcTfrDataWrite == DCM_WRITE_OK )
    {
        if( ( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING ) ||
            ( u1OpStatus == (Dcm_OpStatusType)DCM_FORCE_RCRRP_OK ) )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }

        Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID36_RES_POS_BSC] = Dcm_Dsp_SID36_u1Bsc;
        Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID36_RES_LEN_BSC;
        Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );

        u1_RetVal = E_OK;
    }
    else if( u1_RetProcTfrDataWrite == DCM_WRITE_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID36_PROCTFRDATAWRITE );               /* no return check required */

        u1_RetVal = DCM_E_PENDING;
    }
    else if( u1_RetProcTfrDataWrite == DCM_WRITE_FORCE_RCRRP )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING );

        u1_RetVal = E_OK;
    }
    else
    {
        if( ( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING ) ||
            ( u1OpStatus == (Dcm_OpStatusType)DCM_FORCE_RCRRP_OK ) )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }

        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     u1_ErrorCode );
    }

    return u1_RetVal;
}

#if ( DCM_UL_PROCESS_USE == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID36_TfrDataReadProc                            */
/* Description   | Process of reading transferdata                          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus : Operation state                        */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : Read was successful                    */
/*               |   E_NOT_OK      : Read was not successful                */
/*               |   DCM_E_PENDING : Read is not yet finished               */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID36_TfrDataReadProc
(
    const Dcm_OpStatusType u1OpStatus
)
{
    uint32                        u4_MemorySize;
    Std_ReturnType                u1_RetVal;
    Dcm_ReturnReadMemoryType      u1_RetProcTfrDataRead;
    Dcm_NegativeResponseCodeType  u1_ErrorCode;

    u1_RetVal = E_NOT_OK;
    u1_ErrorCode = DCM_E_GENERALREJECT;

    u4_MemorySize = Dcm_Dsp_Main_stMsgContext.resMaxDataLen -                                             /* no wrap around */
                    DCM_DSP_SID36_REQ_LEN_BSC;
    u1_RetProcTfrDataRead = Dcm_Dsp_DataTfrMng_ProcTfrDataRead( u1OpStatus,
                                                                Dcm_Dsp_SID36_u1Bsc,
                                                                &u4_MemorySize,
                                                                &Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID36_RES_POS_TRPR],
                                                                &u1_ErrorCode );
    if( u1_RetProcTfrDataRead == DCM_READ_OK )
    {
        if( ( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING ) ||
            ( u1OpStatus == (Dcm_OpStatusType)DCM_FORCE_RCRRP_OK ) )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }
        
        if( u4_MemorySize <= ( Dcm_Dsp_Main_stMsgContext.resMaxDataLen - DCM_DSP_SID36_RES_LEN_BSC ))      /* no wrap around */
        {
            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID36_RES_POS_BSC] = Dcm_Dsp_SID36_u1Bsc;
            Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID36_RES_LEN_BSC + u4_MemorySize; /* no wrap around */
            Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
            u1_RetVal = E_OK;
        }
        else
        {
            /* NRC0x14 */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                         DCM_E_RESPONSETOOLONG );
        }
    }
    else if( u1_RetProcTfrDataRead == DCM_READ_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID36_PROCTFRDATAREAD );               /* no return check required */

        u1_RetVal = DCM_E_PENDING;
    }
    else if( u1_RetProcTfrDataRead == DCM_READ_FORCE_RCRRP )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        /* NRC0x78 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING );

        u1_RetVal = E_OK;
    }
    else
    {
        if( ( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING ) ||
            ( u1OpStatus == (Dcm_OpStatusType)DCM_FORCE_RCRRP_OK ) )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }

        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     u1_ErrorCode );
    }

    return u1_RetVal;
}
#endif  /* DCM_UL_PROCESS_USE == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID36_CancelProc                                 */
/* Description   | Cancel process of SID36                                  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK : Processing normal                               */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_UL_PROCESS_USE == STD_OFF )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID36_CancelProc
( void )
{
    Std_ReturnType                         u1_RetVal;
    uint8                                  u1_DummyMemoryData;
    Dcm_NegativeResponseCodeType           u1_DummyErrorCode;
    boolean                                b_UserNotifyFlag;

    u1_RetVal = E_OK;
    u1_DummyMemoryData = (uint8)0U;
    u1_DummyErrorCode  = (uint8)0U;

    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();
    if( b_UserNotifyFlag == (boolean)TRUE )
    {
        (void)Dcm_Dsp_SID36_CallCheckMessageLengthFnc( DCM_CANCEL,                      /* no return check required */
                                                       0x00U,
                                                       0x00U,
                                                       0x00000000U,
                                                       0x00000000U,
                                                       &u1_DummyMemoryData );
        
        (void)Dcm_Dsp_SID36_CallCheckRequestSequenceFnc( DCM_CANCEL,                    /* no return check required */
                                                         0x00U,
                                                         0x00U,
                                                         0x00000000U,
                                                         0x00000000U,
                                                         &u1_DummyMemoryData );

        (void)Dcm_Dsp_SID36_CallCheckTransferDataSuspendedFnc( DCM_CANCEL,              /* no return check required */
                                                               0x00U,
                                                               0x00U,
                                                               0x00000000U,
                                                               0x00000000U,
                                                               &u1_DummyMemoryData );

        (void)Dcm_Dsp_DataTfrMng_ProcTfrDataWrite( DCM_CANCEL,                          /* no return check required */
                                                   0x00U,
                                                   0x00000000U,
                                                   &u1_DummyMemoryData,
                                                   &u1_DummyErrorCode );

        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID36_CHKMSGLEN,                   /* no return check required */
                                         (boolean)FALSE );

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID36_CHKREQSEQUENCE,              /* no return check required */
                                         (boolean)FALSE );

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID36_CHKTFRDATSUSPEND,            /* no return check required */
                                         (boolean)FALSE );

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID36_PROCTFRDATAWRITE,            /* no return check required */
                                         (boolean)FALSE );

    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return u1_RetVal;
}
#endif /* DCM_UL_PROCESS_USE == STD_OFF */
#if ( DCM_UL_PROCESS_USE == STD_ON )
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID36_CancelProc
( void )
{
    uint32                                 u4_DummyMemorySize;
    Std_ReturnType                         u1_RetVal;
    uint8                                  u1_DummyMemoryData;
    Dcm_NegativeResponseCodeType           u1_DummyErrorCode;
    boolean                                b_UserNotifyFlag;

    u1_RetVal = E_OK;
    u4_DummyMemorySize = (uint32)0U;
    u1_DummyMemoryData = (uint8)0U;
    u1_DummyErrorCode  = (uint8)0U;

    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();
    if( b_UserNotifyFlag == (boolean)TRUE )
    {
        (void)Dcm_Dsp_SID36_CallCheckRequestSequenceFnc( DCM_CANCEL,                    /* no return check required */
                                                         0x00U,
                                                         0x00U,
                                                         0x00000000U,
                                                         0x00000000U,
                                                         &u1_DummyMemoryData );

        (void)Dcm_Dsp_SID36_CallCheckTransferDataSuspendedFnc( DCM_CANCEL,              /* no return check required */
                                                               0x00U,
                                                               0x00U,
                                                               0x00000000U,
                                                               0x00000000U,
                                                               &u1_DummyMemoryData );

        if( Dcm_Dsp_SID36_u1ProcessRequest == DCM_DSP_SID36_REQ_PROC_UL )
        {
            (void)Dcm_Dsp_DataTfrMng_ProcTfrDataRead( DCM_CANCEL,                       /* no return check required */
                                                      0x00U,
                                                      &u4_DummyMemorySize,
                                                      &u1_DummyMemoryData,
                                                      &u1_DummyErrorCode );
        }
        else
        {
            (void)Dcm_Dsp_SID36_CallCheckMessageLengthFnc( DCM_CANCEL,                  /* no return check required */
                                                       0x00U,
                                                       0x00U,
                                                       0x00000000U,
                                                       0x00000000U,
                                                       &u1_DummyMemoryData );

            (void)Dcm_Dsp_DataTfrMng_ProcTfrDataWrite( DCM_CANCEL,                      /* no return check required */
                                                       0x00U,
                                                       0x00000000U,
                                                       &u1_DummyMemoryData,
                                                       &u1_DummyErrorCode );
        }
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }

    if( Dcm_Dsp_SID36_u1ProcessRequest == DCM_DSP_SID36_REQ_PROC_UL )
    {
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID36_CHKREQSEQUENCEUL,        /* no return check required */
                                             (boolean)FALSE );
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID36_CHKTFRDATSUSPENDUL,      /* no return check required */
                                             (boolean)FALSE );
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID36_PROCTFRDATAREAD,         /* no return check required */
                                             (boolean)FALSE );
    }
    else
    {
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID36_CHKMSGLEN,               /* no return check required */
                                             (boolean)FALSE );
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID36_CHKREQSEQUENCE,          /* no return check required */
                                             (boolean)FALSE );
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID36_CHKTFRDATSUSPEND,        /* no return check required */
                                             (boolean)FALSE );
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID36_PROCTFRDATAWRITE,        /* no return check required */
                                             (boolean)FALSE );
    }
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return u1_RetVal;
}
#endif /* DCM_UL_PROCESS_USE == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* DCM_SUPPORT_SID36 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

