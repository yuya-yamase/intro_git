/* Dcm_Dsp_SID23_c(v5-3-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID23/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID23.h>
#if ( DCM_SUPPORT_SID23 == STD_ON )
#include <Dcm/Dcm_Dsp_MemMng_Callout.h>
#include <Dcm/Dcm_Dsp_MemMng.h>
#include <Dcm/Dcm_Dsp_DidMng.h>
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     DCM_DSP_SID23_ALFIDLen                        ((uint8)1U)
#define     DCM_DSP_SID23_ReqOffALFID                     ((uint8)0U)
#define     DCM_DSP_SID23_MemAddr_Mask                    ((uint8)0x0FU)
#define     DCM_DSP_SID23_MemSize_Mask                    ((uint8)0xF0U)
#define     DCM_DSP_SID23_MemSize_Shft4                   ((uint8)4U)
#define     DCM_DSP_SID23_MemAddr_Shft8                   ((uint8)8U)
#define     DCM_DSP_SID23_MemSize_Shft8                   ((uint8)8U)
#define     DCM_DSP_SID23_Illegal_MemSize                 ((uint32)0U)
#define     DCM_DSP_SID23_NRC_Not_Set                     ((Dcm_NegativeResponseCodeType)0x00U)
#define     DCM_DSP_SID23_MemId_Not_Set                   ((uint8)0U)
#define     DCM_DSP_SID23_MemId_Set                       ((uint8)1U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID23_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID23_InitialProcSub
(void);
static FUNC(void, DCM_CODE) Dcm_Dsp_SID23_CancelProc
(void);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID23_ChkMemSize
(
    const uint8 u1MemAddrLength,
    const uint8 u1MemSizeLength
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID23_ChkMemAddr
(
    const uint8 u1MemAddrLength
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID23_ReadMem
(
    const Dcm_OpStatusType u1OpStatus
);
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID23_ChkResBufSize
(void);
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>


static VAR(uint8, DCM_VAR_NO_INIT)              Dcm_Dsp_SID23_u1MemId;
static VAR(uint32, DCM_VAR_NO_INIT)             Dcm_Dsp_SID23_u4MemAddr;
static VAR(uint32, DCM_VAR_NO_INIT)             Dcm_Dsp_SID23_u4MemSize;
static VAR(uint8, DCM_VAR_NO_INIT)              Dcm_Dsp_SID23_u1MemIdIndex;
static VAR(uint8, DCM_VAR_NO_INIT)              Dcm_Dsp_SID23_u1MemRangeIndex;

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
/* Function Name | Dcm_SID23                                                */
/* Description   | Request processing of SID 23                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus      : Operation state                     */
/*               | [IN] pMsgContext   : Message Context                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SID23 /* MISRA DEVIATION */
(
    Dcm_OpStatusType                                            OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA)       pMsgContext
)
{
    Std_ReturnType          u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID23_InitialProc( pMsgContext );
        /* This Return Value is check-free */
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        Dcm_Dsp_SID23_CancelProc();
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_FORCE_RCRRP_OK )
    {
        u1_RetVal = Dcm_Dsp_SID23_ReadMem( OpStatus );
        /* This Return Value is check-free */
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID23_Cbk                                        */
/* Description   | Call Back Function to Continue SID23 Processing          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID23_Cbk /* MISRA DEVIATION */
(
    const uint8 u1EventId /* MISRA DEVIATION */
)
{
    (void)Dcm_Dsp_SID23_ReadMem( DCM_PENDING ); /* no return check required */

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID23_UpdatePageCbk                              */
/* Description   | Call Back Function to Continue SID23 UpdatePage          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId      : Event Id                           */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON )
FUNC(void, DCM_CODE) Dcm_Dsp_SID23_UpdatePageCbk         /* MISRA DEVIATION */
(
    const uint8 u1EventId /* MISRA DEVIATION */
)
{
    Dcm_ReturnReadMemoryType               u1_RetReadMem;
    Dcm_NegativeResponseCodeType           u1_ErrCode;
    uint32                                 u4_MemorySize;
    Dcm_MsgType                            pt_ResData;

    u1_ErrCode         = (Dcm_NegativeResponseCodeType)0x00U;
    pt_ResData         = Dcm_Dsp_Main_stMsgContext.resData;

    if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= ( Dcm_Dsp_SID23_u4MemSize - Dcm_Dsp_Main_stMsgContext.resDataLen ) ) /* no wrap around */
    {
        u4_MemorySize = Dcm_Dsp_SID23_u4MemSize - Dcm_Dsp_Main_stMsgContext.resDataLen; /* no wrap around */
    }
    else
    {
        u4_MemorySize = Dcm_Dsp_Main_stMsgContext.resMaxDataLen;
    }

    u1_RetReadMem = Dcm_ReadMemory( DCM_PENDING,
                                    Dcm_Dsp_SID23_u1MemId,
                                    Dcm_Dsp_SID23_u4MemAddr,
                                    u4_MemorySize,
                                    Dcm_Dsp_SID23_u4MemSize,
                                    Dcm_Dsp_Main_stMsgContext.resDataLen,
                                    pt_ResData,
                                    &u1_ErrCode );

    /* Check Return Value */
    if( u1_RetReadMem == (Dcm_ReturnReadMemoryType)DCM_READ_OK )
    {
            Dcm_Dsp_Main_stMsgContext.resDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen + u4_MemorySize;    /* no wrap around */
            Dcm_Dsp_MsgMaker_ProcessPage( u4_MemorySize );
    }
    else if( u1_RetReadMem == (Dcm_ReturnReadMemoryType)DCM_READ_PENDING )
    {
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID23_UPDATEPAGE ); /* no return check required */
    }
    else
    {
        /* No process */
    }


    return;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON */


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID23_UpdatePage                                 */
/* Description   | UpdatePage of SID 23                                     */
/* Preconditions | None                                                     */
/* Parameters    | [OUT] ptResData       : Response Data                    */
/*               | [IN]  u4ResMaxDataLen : Buffer Size of Response Data     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing abnormal                */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON )
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID23_UpdatePage  /* MISRA DEVIATION */
(
    Dcm_MsgType     ptResData,
    Dcm_MsgLenType  u4ResMaxDataLen
)
{
    Std_ReturnType                         u1_RetVal;
    Dcm_ReturnReadMemoryType               u1_RetReadMem;
    Dcm_NegativeResponseCodeType           u1_ErrCode;
    uint32                                 u4_MemorySize;

    u1_RetVal          = E_OK;
    u1_ErrCode         = (Dcm_NegativeResponseCodeType)0x00U;

    if( u4ResMaxDataLen == (Dcm_MsgLenType)DCM_DSD_UPDATEPAGE_INITIAL_ACT )
    {
        Dcm_Dsp_MsgMaker_ProcessPage( Dcm_Dsp_Main_stMsgContext.resDataLen );
    }
    else
    {
        if( u4ResMaxDataLen >= ( Dcm_Dsp_SID23_u4MemSize - Dcm_Dsp_Main_stMsgContext.resDataLen ) ) /* no wrap around */
        {
            u4_MemorySize = Dcm_Dsp_SID23_u4MemSize - Dcm_Dsp_Main_stMsgContext.resDataLen; /* no wrap around */
        }
        else
        {
            u4_MemorySize = u4ResMaxDataLen;
        }

        u1_RetReadMem = Dcm_ReadMemory( DCM_INITIAL,
                                        Dcm_Dsp_SID23_u1MemId,
                                        Dcm_Dsp_SID23_u4MemAddr,
                                        u4_MemorySize,
                                        Dcm_Dsp_SID23_u4MemSize,
                                        Dcm_Dsp_Main_stMsgContext.resDataLen,
                                        ptResData,
                                        &u1_ErrCode );

        /* Check Return Value */
        switch( u1_RetReadMem )
        {
            case DCM_READ_OK:
                Dcm_Dsp_Main_stMsgContext.resDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen + u4_MemorySize;    /* no wrap around */
                Dcm_Dsp_MsgMaker_ProcessPage( u4_MemorySize );
                break;
            case DCM_READ_FAILED:
                u1_RetVal = E_NOT_OK;
                break;
            case DCM_READ_PENDING:
                (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID23_UPDATEPAGE ); /* no return check required */
                Dcm_Dsp_Main_stMsgContext.resData = ptResData;
                Dcm_Dsp_Main_stMsgContext.resMaxDataLen = u4ResMaxDataLen;
                break;
            default:
                u1_RetVal = E_NOT_OK;
                break;
        }
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON */


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID23_CancelPage                                 */
/* Description   | CancelPage of SID 23                                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON )
FUNC(void, DCM_CODE) Dcm_Dsp_SID23_CancelPage            /* MISRA DEVIATION */
(void)
{
    uint32                                                        u4_MemorySize;
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)                        pt_WriteBuff;
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pt_ErrCode;

    u4_MemorySize = (uint32)0U;
    pt_WriteBuff  = NULL_PTR;
    pt_ErrCode    = NULL_PTR;

    (void)Dcm_ReadMemory( DCM_CANCEL,
                          Dcm_Dsp_SID23_u1MemId,
                          Dcm_Dsp_SID23_u4MemAddr,
                          u4_MemorySize,
                          Dcm_Dsp_SID23_u4MemSize,
                          Dcm_Dsp_Main_stMsgContext.resDataLen,
                          pt_WriteBuff,
                          pt_ErrCode ); /* no return check required */

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID23_UPDATEPAGE, (boolean)FALSE ); /* no return check required */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID23_InitialProc                                */
/* Description   | Initial process of SID23                                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID23_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    boolean                         b_SendNegRes;
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    uint8                           u1_ALFID;
    uint8                           u1_MemAddrLen;
    uint8                           u1_MemSizeLen;
    uint8                           u1_MsgLenMin;
    Std_ReturnType                  u1_RetChkALFID;
    Std_ReturnType                  u1_RetChkMemSize;
    Std_ReturnType                  u1_RetChkMemAddr;
    Std_ReturnType                  u1_RetVal;

    b_SendNegRes        = (boolean)FALSE;
    u1_RetVal           = E_OK;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    /* Set Common Data */
    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    Dcm_Dsp_SID23_u1MemId = (uint8)0U;
    Dcm_Dsp_SID23_u4MemAddr = (uint32)0U;
    Dcm_Dsp_SID23_u4MemSize = (uint32)0U;
    Dcm_Dsp_SID23_u1MemIdIndex = (uint8)0U;
    Dcm_Dsp_SID23_u1MemRangeIndex = (uint8)0U;

    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    u1_MsgLenMin = Dcm_Dsp_SID23_u1MsgLenMin;

    /* Check Request Data Length */
    if( ptMsgContext->reqDataLen >= (Dcm_MsgLenType)u1_MsgLenMin )
    {
        /* Check Request addressAndLengthFormatIdentifier */
        u1_RetChkALFID = Dcm_Dsp_DidMng_ChkALFID( Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID23_ReqOffALFID] );
        if( u1_RetChkALFID == (Std_ReturnType)E_OK )
        {
            u1_ALFID = ptMsgContext->reqData[DCM_DSP_SID23_ReqOffALFID];
            u1_MemAddrLen = u1_ALFID & DCM_DSP_SID23_MemAddr_Mask;
            u1_MemSizeLen = (u1_ALFID & DCM_DSP_SID23_MemSize_Mask) >> DCM_DSP_SID23_MemSize_Shft4;

            /* Check Request Data Length */
            if( ptMsgContext->reqDataLen == ((Dcm_MsgLenType)DCM_DSP_SID23_ALFIDLen + (Dcm_MsgLenType)u1_MemAddrLen + (Dcm_MsgLenType)u1_MemSizeLen) )  /* no wrap around */
            {
                /* Check Request memorySize */
                u1_RetChkMemSize = Dcm_Dsp_SID23_ChkMemSize(u1_MemAddrLen, u1_MemSizeLen);
                if( u1_RetChkMemSize == (Std_ReturnType)E_OK )
                {
                    /* Check Request memoryAddress */
                    u1_RetChkMemAddr = Dcm_Dsp_SID23_ChkMemAddr(u1_MemAddrLen);
                    if( u1_RetChkMemAddr == (Std_ReturnType)E_OK )
                    {
                        u1_RetVal = Dcm_Dsp_SID23_InitialProcSub();
                    }
                    else
                    {
                        /* This Route                                      */
                        /*   MemoryAddress Illegal    -> 0x31              */
                        b_SendNegRes    = (boolean)TRUE;
                        u1_NegResCode   = DCM_E_REQUESTOUTOFRANGE;
                    }
                }
                else
                {
                    /* This Route                                   */
                    /*   MemorySize Illegal    -> 0x31              */
                    b_SendNegRes    = (boolean)TRUE;
                    u1_NegResCode   = DCM_E_REQUESTOUTOFRANGE;
                }
            }
            else
            {
                /* This Route                                                       */
                /*   Request Length Check NG    -> 0x13                             */
                b_SendNegRes    = (boolean)TRUE;
                u1_NegResCode   = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            }
        }
        else
        {
            /* This Route                                                         */
            /*   addressAndLengthFormatIdentifier Illegal    -> 0x31              */
            b_SendNegRes    = (boolean)TRUE;
            u1_NegResCode   = DCM_E_REQUESTOUTOFRANGE;
        }
    }
    else
    {
        /* This Route                                                       */
        /*   Request Length Check NG    -> 0x13                             */
        b_SendNegRes    = (boolean)TRUE;
        u1_NegResCode   = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    if( b_SendNegRes == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID23_InitialProcSub                             */
/* Description   | Initial sub process of SID23                             */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID23_InitialProcSub
(void)
{
    boolean                         b_SendNegRes;
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    Dcm_SecLevelType                u1_SecLevel;
    Std_ReturnType                  u1_RetChkMemSec;
    Std_ReturnType                  u1_RetChkCondition;
    Std_ReturnType                  u1_RetVal;

    b_SendNegRes        = (boolean)FALSE;
    u1_NegResCode       = (Dcm_NegativeResponseCodeType)0x00U;
    u1_SecLevel         = DCM_SEC_LEV_LOCKED;
    u1_RetVal           = E_OK;


    /* Get active security level */
    (void)Dcm_GetSecurityLevel( &u1_SecLevel ); /* no return check required */
    /* Check Security lock is canceled */
    u1_RetChkMemSec = Dcm_Dsp_DidMng_ChkMemSec( DCM_DSP_DIDMNG_MEM_READ,
                                                Dcm_Dsp_SID23_u1MemIdIndex,
                                                Dcm_Dsp_SID23_u1MemRangeIndex,
                                                u1_SecLevel );
    if( u1_RetChkMemSec == (Std_ReturnType)E_OK )
    {
        u1_RetChkCondition = Dcm_Dsp_MemMng_CheckCondition( Dcm_Dsp_SID23_u1MemId, Dcm_Dsp_SID23_u4MemAddr, Dcm_Dsp_SID23_u4MemSize, &u1_NegResCode );
        if( u1_RetChkCondition == (Std_ReturnType)E_OK )
        {
            /* Read Memory by Address */
            u1_RetVal = Dcm_Dsp_SID23_ReadMem(DCM_INITIAL);
        }
        else
        {
            b_SendNegRes    = (boolean)TRUE;
            /* u1_NegResCode have been already set by Dcm_Dsp_MemMng_CheckCondition function. */
        }
    }
    else
    {
        /* This Route                                                  */
        /*   Security lock is non-cancellation    -> 0x33              */
        b_SendNegRes    = (boolean)TRUE;
        u1_NegResCode   = DCM_E_SECURITYACCESSDENIED;
    }

    if( b_SendNegRes == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON */
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID23_InitialProcSub
(void)
{
    boolean                         b_SendNegRes;
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    Dcm_SecLevelType                u1_SecLevel;
    Std_ReturnType                  u1_RetChkMemSec;
    Std_ReturnType                  u1_RetChkCondition;
    Std_ReturnType                  u1_RetChkResBufSize;
    Std_ReturnType                  u1_RetVal;

    b_SendNegRes        = (boolean)FALSE;
    u1_NegResCode       = (Dcm_NegativeResponseCodeType)0x00U;
    u1_SecLevel         = DCM_SEC_LEV_LOCKED;
    u1_RetVal           = E_OK;


    /* Get active security level */
    (void)Dcm_GetSecurityLevel( &u1_SecLevel ); /* no return check required */
    /* Check Security lock is canceled */
    u1_RetChkMemSec = Dcm_Dsp_DidMng_ChkMemSec( DCM_DSP_DIDMNG_MEM_READ,
                                                Dcm_Dsp_SID23_u1MemIdIndex,
                                                Dcm_Dsp_SID23_u1MemRangeIndex,
                                                u1_SecLevel );
    if( u1_RetChkMemSec == (Std_ReturnType)E_OK )
    {
        u1_RetChkCondition = Dcm_Dsp_MemMng_CheckCondition( Dcm_Dsp_SID23_u1MemId, Dcm_Dsp_SID23_u4MemAddr, Dcm_Dsp_SID23_u4MemSize, &u1_NegResCode );
        if( u1_RetChkCondition == (Std_ReturnType)E_OK )
        {
            u1_RetChkResBufSize = Dcm_Dsp_SID23_ChkResBufSize();
            if( u1_RetChkResBufSize == (Std_ReturnType)E_OK )
            {
                /* Read Memory by Address */
                u1_RetVal = Dcm_Dsp_SID23_ReadMem(DCM_INITIAL);
            }
            else
            {
                /* NRC0x14 */
                b_SendNegRes = Dcm_Dsp_SID23_bNegativeResponseSendResponseTooLong;
                u1_NegResCode = DCM_E_RESPONSETOOLONG;
            }
        }
        else
        {
            b_SendNegRes    = (boolean)TRUE;
            /* u1_NegResCode have been already set by Dcm_Dsp_MemMng_CheckCondition function. */
        }
    }
    else
    {
        /* This Route                                                  */
        /*   Security lock is non-cancellation    -> 0x33              */
        b_SendNegRes    = (boolean)TRUE;
        u1_NegResCode   = DCM_E_SECURITYACCESSDENIED;
    }

    if( b_SendNegRes == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF */


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID23_CancelProc                                 */
/* Description   | Cancel process of SID23 request                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON )
static FUNC(void, DCM_CODE) Dcm_Dsp_SID23_CancelProc
(void)
{
    uint32                                                        u4_MemorySize;
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)                        pt_WriteBuff;
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pt_ErrCode;
    boolean                                                       b_UserNotify;

    u4_MemorySize = (uint32)0U;
    pt_WriteBuff  = NULL_PTR;
    pt_ErrCode    = NULL_PTR;
    b_UserNotify  = Dcm_Dsp_Main_GetUserNotifyFlag();

    if( b_UserNotify == (boolean)TRUE )
    {
        (void)Dcm_ReadMemory( DCM_CANCEL,
                              Dcm_Dsp_SID23_u1MemId,
                              Dcm_Dsp_SID23_u4MemAddr,
                              u4_MemorySize,
                              Dcm_Dsp_SID23_u4MemSize,
                              Dcm_Dsp_Main_stMsgContext.resDataLen,
                              pt_WriteBuff,
                              pt_ErrCode ); /* no return check required */

        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }
    else
    {
        /* No process */
    }

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID23_READMEM, (boolean)FALSE ); /* no return check required */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON */


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID23_CancelProc                                 */
/* Description   | Cancel process of SID23 request                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF )
static FUNC(void, DCM_CODE) Dcm_Dsp_SID23_CancelProc
(void)
{
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)                        pt_WriteBuff;
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pt_ErrCode;
    boolean                                                       b_UserNotify;

    pt_WriteBuff = NULL_PTR;
    pt_ErrCode   = NULL_PTR;
    b_UserNotify = Dcm_Dsp_Main_GetUserNotifyFlag();

    if( b_UserNotify == (boolean)TRUE )
    {
        (void)Dcm_ReadMemory( DCM_CANCEL,
                              Dcm_Dsp_SID23_u1MemId,
                              Dcm_Dsp_SID23_u4MemAddr,
                              Dcm_Dsp_SID23_u4MemSize,
                              pt_WriteBuff,
                              pt_ErrCode ); /* no return check required */

        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }
    else
    {
        /* No process */
    }

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID23_READMEM, (boolean)FALSE ); /* no return check required */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF */


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID23_ChkMemSize                                 */
/* Description   | Check MemorySize                                         */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1MemAddrLength : Memory Address Length             */
/*               | [IN] u1MemSizeLength : Memory Size Length                */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK        : Check OK                                 */
/*               |   E_NOT_OK    : Check NG                                 */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID23_ChkMemSize
(
    const uint8    u1MemAddrLength,
    const uint8    u1MemSizeLength
)
{
    uint32            u4_MaxMemorySize;
    Std_ReturnType    u1_RetVal;
    uint8             u1_MemSzRCnt;

    u1_RetVal       = E_NOT_OK;

    /* Convert memorySize into uint32 */
    for( u1_MemSzRCnt = (uint8)0U; u1_MemSzRCnt < u1MemSizeLength; u1_MemSzRCnt++ )
    {
        Dcm_Dsp_SID23_u4MemSize <<= DCM_DSP_SID23_MemSize_Shft8;
        Dcm_Dsp_SID23_u4MemSize += Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID23_ALFIDLen + u1MemAddrLength + u1_MemSzRCnt];  /* no wrap around */
    }

    if( Dcm_Dsp_SID23_u4MemSize != DCM_DSP_SID23_Illegal_MemSize )
    {
        u4_MaxMemorySize = Dcm_Dsp_MemMng_GetMaxMemorySize();
        if( Dcm_Dsp_SID23_u4MemSize <= u4_MaxMemorySize )
        {
            u1_RetVal = E_OK;
        }
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID23_ChkMemAddr                                 */
/* Description   | Call DidMng-API Dcm_Dsp_DidMng_ChkMemAddress and         */
/*               | Dcm_Dsp_DidMng_ChkMemSize                                */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1MemAddrLength : Memory Address Length             */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK        : Check OK                                 */
/*               |   E_NOT_OK    : Check NG                                 */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID23_ChkMemAddr
(
    const uint8    u1MemAddrLength
)
{
    Std_ReturnType    u1_RetVal;
    Std_ReturnType    u1_RetChkMemAddr;
    Std_ReturnType    u1_RetChkMemSize;
    uint8             u1_MemIdFlag;
    uint8             u1_MemAddrRCnt;
    boolean           b_CheckMemAddrUseAsMemoryId;

    u1_RetVal        = E_NOT_OK;

    b_CheckMemAddrUseAsMemoryId = Dcm_Dsp_MemMng_GetUseAsMemoryId();
    if( b_CheckMemAddrUseAsMemoryId == (boolean)TRUE )
    {
        u1_MemIdFlag = DCM_DSP_DIDMNG_MEM_ID_VALID;
        Dcm_Dsp_SID23_u1MemId = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID23_ALFIDLen];
        u1_MemAddrRCnt = DCM_DSP_SID23_MemId_Set;
    }
    else
    {
        u1_MemIdFlag = DCM_DSP_DIDMNG_MEM_ID_INVALID;
        u1_MemAddrRCnt = DCM_DSP_SID23_MemId_Not_Set;
    }

    /* Convert memoryAddress into uint32 */
    for( ; u1_MemAddrRCnt < u1MemAddrLength; u1_MemAddrRCnt++ )
    {
        Dcm_Dsp_SID23_u4MemAddr <<= DCM_DSP_SID23_MemAddr_Shft8;
        Dcm_Dsp_SID23_u4MemAddr += Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID23_ALFIDLen + u1_MemAddrRCnt];  /* no wrap around */
    }


    u1_RetChkMemAddr = Dcm_Dsp_DidMng_ChkMemAddress( DCM_DSP_DIDMNG_MEM_READ,
                                                     Dcm_Dsp_SID23_u4MemAddr,
                                                     u1_MemIdFlag,
                                                     Dcm_Dsp_SID23_u1MemId,
                                                     &Dcm_Dsp_SID23_u1MemIdIndex,
                                                     &Dcm_Dsp_SID23_u1MemRangeIndex );

    /* Check DidMng-API Return Value */
    if( u1_RetChkMemAddr == (Std_ReturnType)E_OK )
    {
        u1_RetChkMemSize = Dcm_Dsp_DidMng_ChkMemSize( DCM_DSP_DIDMNG_MEM_READ,
                                                      Dcm_Dsp_SID23_u1MemIdIndex,
                                                      Dcm_Dsp_SID23_u1MemRangeIndex,
                                                      Dcm_Dsp_SID23_u4MemAddr,
                                                      Dcm_Dsp_SID23_u4MemSize );

        /* Check DidMng-API Return Value */
        if( u1_RetChkMemSize == (Std_ReturnType)E_OK )
        {
            u1_RetVal = E_OK;
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        /* No process */
    }


    return u1_RetVal;
}

#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID23_ChkResBufSize                              */
/* Description   | Check response buffer size                               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK        : Check OK                                 */
/*               |   E_NOT_OK    : Check NG                                 */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID23_ChkResBufSize
(void)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_NOT_OK;

    if( Dcm_Dsp_SID23_u4MemSize <= ( Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen ) ) /* no wrap around */
    {
        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID23_ReadMem                                    */
/* Description   | Read Memory                                              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus : Operation state                        */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID23_ReadMem
(
    const Dcm_OpStatusType    u1OpStatus
)
{
    Std_ReturnType                         u1_RetVal;
    Dcm_ReturnReadMemoryType               u1_RetReadMem;
    boolean                                b_SendNegRes;
    Dcm_NegativeResponseCodeType           u1_NegResCode;
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pt_WriteBuff;
    Dcm_NegativeResponseCodeType           u1_ErrCode;
    uint16                                 u2_PbidSid23;
    uint32                                 u4_MemorySize;
    Dcm_MsgContextType                     st_MsgContext;

    u1_RetVal          = E_OK;
    b_SendNegRes       = (boolean)FALSE;
    pt_WriteBuff       = &(Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen ]);
    u1_ErrCode         = (Dcm_NegativeResponseCodeType)0x00U;
    u2_PbidSid23       = Dcm_P_u2Pbid_Sid23;
    st_MsgContext.reqData = NULL_PTR;
    st_MsgContext.reqDataLen = (Dcm_MsgLenType)0U;
    st_MsgContext.resData = NULL_PTR;
    st_MsgContext.msgAddInfo.reqType = (uint8)0U;
    st_MsgContext.msgAddInfo.suppressPosResponse = STD_OFF;
    st_MsgContext.resMaxDataLen = (Dcm_MsgLenType)0U;
    st_MsgContext.idContext = (Dcm_IdContextType)0U;
    st_MsgContext.dcmRxPduId = (PduIdType)0U;

    switch( u1OpStatus )
    {
        case DCM_INITIAL:
        case DCM_PENDING:
        case DCM_FORCE_RCRRP_OK:
            if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= Dcm_Dsp_SID23_u4MemSize )
            {
                u4_MemorySize = Dcm_Dsp_SID23_u4MemSize;
            }
            else
            {
                u4_MemorySize = Dcm_Dsp_Main_stMsgContext.resMaxDataLen;
            }

            u1_RetReadMem = Dcm_ReadMemory( u1OpStatus,
                                            Dcm_Dsp_SID23_u1MemId,
                                            Dcm_Dsp_SID23_u4MemAddr,
                                            u4_MemorySize,
                                            Dcm_Dsp_SID23_u4MemSize,
                                            Dcm_Dsp_Main_stMsgContext.resDataLen,
                                            pt_WriteBuff,
                                            &u1_ErrCode );
            /* Check Return Value */
            switch( u1_RetReadMem )
            {
                case DCM_READ_OK:
                    Dcm_Dsp_Main_stMsgContext.resDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen + u4_MemorySize;    /* no wrap around */
                    st_MsgContext.resDataLen = Dcm_Dsp_SID23_u4MemSize;
                    Dcm_Dsp_MsgMaker_StartPagedProcessing( &st_MsgContext, u2_PbidSid23 );
                    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
                    break;
                case DCM_READ_FAILED:
                    b_SendNegRes = (boolean)TRUE;
                    u1_NegResCode = u1_ErrCode;
                    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
                    break;
                case DCM_READ_PENDING:
                    (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID23_READMEM ); /* no return check required */
                    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
                    u1_RetVal = DCM_E_PENDING;
                    break;
                case DCM_READ_FORCE_RCRRP:
                    /* NRC 0x78 */
                    b_SendNegRes = (boolean)TRUE;
                    u1_NegResCode = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
                    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
                    break;
                default:
                    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
                    break;
            }
            break;
        default:
            /* No process */
            break;
    }


    if( b_SendNegRes == (boolean)TRUE )
    {
        if( u1_NegResCode != DCM_DSP_SID23_NRC_Not_Set )
        {
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_ON */


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID23_ReadMem                                    */
/* Description   | Read Memory                                              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus : Operation state                        */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID23_ReadMem
(
    const Dcm_OpStatusType    u1OpStatus
)
{
    Std_ReturnType                         u1_RetVal;
    Dcm_ReturnReadMemoryType               u1_RetReadMem;
    boolean                                b_SendNegRes;
    Dcm_NegativeResponseCodeType           u1_NegResCode;
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pt_WriteBuff;
    Dcm_NegativeResponseCodeType           u1_ErrCode;

    u1_RetVal          = E_OK;
    b_SendNegRes       = (boolean)FALSE;
    pt_WriteBuff       = &(Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen ]);
    u1_ErrCode         = (Dcm_NegativeResponseCodeType)0x00U;

    switch( u1OpStatus )
    {
        case DCM_INITIAL:
        case DCM_PENDING:
        case DCM_FORCE_RCRRP_OK:
            u1_RetReadMem = Dcm_ReadMemory( u1OpStatus,
                                            Dcm_Dsp_SID23_u1MemId,
                                            Dcm_Dsp_SID23_u4MemAddr,
                                            Dcm_Dsp_SID23_u4MemSize,
                                            pt_WriteBuff,
                                            &u1_ErrCode );
            /* Check Return Value */
            switch( u1_RetReadMem )
            {
                case DCM_READ_OK:
                    Dcm_Dsp_Main_stMsgContext.resDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen + Dcm_Dsp_SID23_u4MemSize;  /* no wrap around */
                    Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
                    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
                    break;
                case DCM_READ_FAILED:
                    b_SendNegRes = (boolean)TRUE;
                    u1_NegResCode = u1_ErrCode;
                    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
                    break;
                case DCM_READ_PENDING:
                    (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID23_READMEM ); /* no return check required */
                    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
                    u1_RetVal = DCM_E_PENDING;
                    break;
                case DCM_READ_FORCE_RCRRP:
                    /* NRC 0x78 */
                    b_SendNegRes = (boolean)TRUE;
                    u1_NegResCode = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
                    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
                    break;
                default:
                    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
                    break;
            }
            break;
        default:
            /* No process */
            break;
    }


    if( b_SendNegRes == (boolean)TRUE )
    {
        if( u1_NegResCode != DCM_DSP_SID23_NRC_Not_Set )
        {
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
        }
        else
        {
            /* No process */
        }
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID23_ENABLED == STD_OFF */


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID23 */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File************************************************************/
