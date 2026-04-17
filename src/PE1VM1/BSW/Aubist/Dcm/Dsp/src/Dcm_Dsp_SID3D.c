/* Dcm_Dsp_SID3D_c(v5-6-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID3D/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID3D.h>
#include <Dcm.h>

#if ( DCM_SUPPORT_SID3D == STD_ON )

#include <Dcm/Dcm_Dsp_DidMng.h>
#include <Dcm/Dcm_Dsp_Main.h>
#include <Dcm/Dcm_Dsp_MemMng.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Main_Common.h>
#include <Dcm/Dcm_Main_EvtDistr.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SID3D_ALFID_LEN         ( (uint8)1U )
#define DCM_DSP_SID3D_ILLEGAL_MEMSIZE   ( (uint32)0U )
#define DCM_DSP_SID3D_MEMADDR_MASK      ( (uint8)0x0FU )
#define DCM_DSP_SID3D_MEMSIZE_MASK      ( (uint8)0xF0U )
#define DCM_DSP_SID3D_MEMSIZE_SHFT4     ( (uint8)4U )
#define DCM_DSP_SID3D_MEMADDR_SHFT8     ( (uint8)8U )
#define DCM_DSP_SID3D_MEMSIZE_SHFT8     ( (uint8)8U )
#define DCM_DSP_SID3D_MEMADDR_IDX0      ( (uint8)0U )
#define DCM_DSP_SID3D_MEMADDR_IDX1      ( (uint8)1U )
#define DCM_DSP_SID3D_REQDATA_LEN       ( (uint8)4U )
#define DCM_DSP_SID3D_REQOFST_ALFID     ( (uint8)0U )
#define DCM_DSP_SID3D_MEMDATA_SIZE_MAX  ( (uint32)( (uint32)0xFFFFFFFFU - (uint32)DCM_DSP_SID3D_ALFID_LEN - (uint32)0xFU - (uint32)0xFU ) ) /* 0xFU is maximum length of MemoryAddress and MemorySize */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID3D_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID3D_InitialProcSub
(
    const uint8 u1MemAddrLen,
    const uint8 u1MemSizeLen,
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA ) ptSendNegRes,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptNegResCode
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID3D_CancelProc
(void);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID3D_ChkAndSetMemSize
(
    const uint32 u4MemSize
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID3D_ChkAndSetMemAddr
(
    const uint32 u4MemAddr,
    const uint8  u1MemId,
    const uint8  u1MemIdFlag
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID3D_WriteMem
(
    const Dcm_OpStatusType u1OpStatus
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID3D_GetMemInfo
(
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_ALFID,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_MemAddrLen,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_MemSizeLen
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static VAR( uint32, DCM_VAR_NO_INIT ) Dcm_Dsp_SID3D_u4MemAddr;
static VAR( uint32, DCM_VAR_NO_INIT ) Dcm_Dsp_SID3D_u4MemSize;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_SID3D_u1MemId;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_SID3D_u1MemIdIndex;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_SID3D_u1MemRangeIndex;

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
/* Function Name | Dcm_SID3D                                                */
/* Description   | Request processing of SID 3D                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus      : Operation state                     */
/*               | [IN] pMsgContext   : Message Context                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID3D /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType  u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID3D_InitialProc( pMsgContext );
        /* This Return Value is check-free */
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        Dcm_Dsp_SID3D_CancelProc();
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_FORCE_RCRRP_OK )
    {
        u1_RetVal = Dcm_Dsp_SID3D_WriteMem( DCM_FORCE_RCRRP_OK );
        /* This Return Value is check-free */
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID3D_WriteMemoryCbk                             */
/* Description   | Call Back Function to Continue SID3D Processing          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID3D_WriteMemoryCbk /* MISRA DEVIATION */
(
    const uint8 u1EventId /* MISRA DEVIATION */
)
{
    (void)Dcm_Dsp_SID3D_WriteMem( DCM_PENDING ); /* no return check required */

    return;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID3D_InitialProc                                */
/* Description   | Initial process of SID3D                                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID3D_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    uint32                          u4_MemAddr;
    uint32                          u4_MemDataSize;
    uint8                           u1_ALFID;
    uint8                           u1_MemAddrLen;
    uint8                           u1_MemAddrRIdx;
    uint8                           u1_MemId;
    uint8                           u1_MemIdFlag;
    uint8                           u1_MemSizeLen;
    uint8                           u1_MemSzRIdx;
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    Std_ReturnType                  u1_RetChkALFID;
    Std_ReturnType                  u1_RetChkMemAddr;
    Std_ReturnType                  u1_RetChkMemSize;
    Std_ReturnType                  u1_RetVal;
    boolean                         b_CheckMemAddrUseAsMemoryId;
    boolean                         b_SendNegRes;

    u4_MemAddr          = (uint32)0U;
    u4_MemDataSize      = (uint32)0U;
    u1_MemId            = (uint8)0U;
    u1_NegResCode       = DCM_E_GENERALREJECT;
    u1_RetVal           = E_OK;
    b_SendNegRes        = (boolean)FALSE;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    /* Set Common Data */
    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    Dcm_Dsp_SID3D_u1MemId = (uint8)0U;
    Dcm_Dsp_SID3D_u4MemAddr = (uint32)0U;
    Dcm_Dsp_SID3D_u4MemSize = (uint32)0U;
    Dcm_Dsp_SID3D_u1MemIdIndex = (uint8)0U;
    Dcm_Dsp_SID3D_u1MemRangeIndex = (uint8)0U;

    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    /* Check Request Data Length */
    if( Dcm_Dsp_Main_stMsgContext.reqDataLen >= (Dcm_MsgLenType)DCM_DSP_SID3D_REQDATA_LEN )
    {
        /* Check Request addressAndLengthFormatIdentifier */
        u1_RetChkALFID = Dcm_Dsp_DidMng_ChkALFID( Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID3D_REQOFST_ALFID] );
        if( u1_RetChkALFID == (Std_ReturnType)E_OK )
        {
            Dcm_Dsp_SID3D_GetMemInfo( &u1_ALFID, &u1_MemAddrLen, &u1_MemSizeLen );

            /* Convert memorySize into uint32 */
            for( u1_MemSzRIdx = (uint8)0U; u1_MemSzRIdx < u1_MemSizeLen; u1_MemSzRIdx++ )
            {
                u4_MemDataSize <<= DCM_DSP_SID3D_MEMSIZE_SHFT8;
                u4_MemDataSize += Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID3D_ALFID_LEN + u1_MemAddrLen + u1_MemSzRIdx];  /* no wrap around */
            }

            /* Check MemoryData Size */
            if( DCM_DSP_SID3D_MEMDATA_SIZE_MAX >= u4_MemDataSize )
            {
                /* Check Request Data Length */
                if( Dcm_Dsp_Main_stMsgContext.reqDataLen == ( (Dcm_MsgLenType)DCM_DSP_SID3D_ALFID_LEN + /* no wrap around */
                                                              (Dcm_MsgLenType)u1_MemAddrLen +           /* no wrap around */
                                                              (Dcm_MsgLenType)u1_MemSizeLen +           /* no wrap around */
                                                              (Dcm_MsgLenType)u4_MemDataSize ) )
                {
                    /* Check And Set Request memorySize */
                    u1_RetChkMemSize = Dcm_Dsp_SID3D_ChkAndSetMemSize( u4_MemDataSize );
                    if( u1_RetChkMemSize == (Std_ReturnType)E_OK )
                    {
                        b_CheckMemAddrUseAsMemoryId = Dcm_Dsp_MemMng_GetUseAsMemoryId();
                        if( b_CheckMemAddrUseAsMemoryId == (boolean)TRUE )
                        {
                            u1_MemIdFlag = DCM_DSP_DIDMNG_MEM_ID_VALID;
                            u1_MemAddrRIdx = DCM_DSP_SID3D_MEMADDR_IDX1;
                            u1_MemId = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID3D_ALFID_LEN];
                        }
                        else
                        {
                            u1_MemIdFlag = DCM_DSP_DIDMNG_MEM_ID_INVALID;
                            u1_MemAddrRIdx = DCM_DSP_SID3D_MEMADDR_IDX0;
                        }

                        /* Convert memoryAddress into uint32 */
                        for( ; u1_MemAddrRIdx < u1_MemAddrLen; u1_MemAddrRIdx++ )
                        {
                            u4_MemAddr <<= DCM_DSP_SID3D_MEMADDR_SHFT8;
                            u4_MemAddr += Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID3D_ALFID_LEN + u1_MemAddrRIdx];  /* no wrap around */
                        }

                        /* Check And Set Request memoryAddress */
                        u1_RetChkMemAddr = Dcm_Dsp_SID3D_ChkAndSetMemAddr( u4_MemAddr, u1_MemId, u1_MemIdFlag );
                        if( u1_RetChkMemAddr == (Std_ReturnType)E_OK )
                        {
                            u1_RetVal = Dcm_Dsp_SID3D_InitialProcSub( u1_MemAddrLen,
                                                                      u1_MemSizeLen,
                                                                      &b_SendNegRes,
                                                                      &u1_NegResCode );
                        }
                        else
                        {
                            /*   MemoryAddress Illegal    -> 0x31              */
                            b_SendNegRes    = (boolean)TRUE;
                            u1_NegResCode   = DCM_E_REQUESTOUTOFRANGE;
                        }
                    }
                    else
                    {
                        /*   MemorySize Illegal    -> 0x31              */
                        b_SendNegRes    = (boolean)TRUE;
                        u1_NegResCode   = DCM_E_REQUESTOUTOFRANGE;
                    }
                }
                else
                {
                    /*   Request Length Check NG    -> 0x13                             */
                    b_SendNegRes    = (boolean)TRUE;
                    u1_NegResCode   = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                }
            }
            else
            {
                /*   Request Length Check NG    -> 0x13                             */
                b_SendNegRes    = (boolean)TRUE;
                u1_NegResCode   = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            }
        }
        else
        {
            /*   addressAndLengthFormatIdentifier Illegal    -> 0x31              */
            b_SendNegRes    = (boolean)TRUE;
            u1_NegResCode   = DCM_E_REQUESTOUTOFRANGE;
        }
    }
    else
    {
        /*   Request Length Check NG    -> 0x13                             */
        b_SendNegRes    = (boolean)TRUE;
        u1_NegResCode   = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    if( b_SendNegRes == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID3D_InitialProcSub                             */
/* Description   | Initial sub process of SID3D                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1MemAddrLen   : Write Memory Address Length        */
/*               | [IN] u1MemSizeLen   : Write Memory Size Length           */
/*               | [OUT] ptSendNegRes  : Request Send Negative Response     */
/*               | [OUT] ptNegResCode  : Negative Response Code             */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID3D_InitialProcSub
(
    const uint8 u1MemAddrLen,
    const uint8 u1MemSizeLen,
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA )  ptSendNegRes,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA )  ptNegResCode
)
{
    Std_ReturnType                  u1_RetChkMemSec;
    Std_ReturnType                  u1_RetChkMemSes;
    Std_ReturnType                  u1_RetVal;
    Dcm_SesCtrlType                 u1_SesCtrlType;
    Dcm_SecLevelType                u1_SecLevel;

    u1_RetVal           = E_OK;

    /* Get active session */
    u1_SesCtrlType = DCM_DEFAULT_SESSION;
    (void)Dcm_GetSesCtrlType( &u1_SesCtrlType ); /* no return check required */
    /* Check session support */
    u1_RetChkMemSes = Dcm_Dsp_DidMng_ChkMemSes( DCM_DSP_DIDMNG_MEM_WRITE,
                                                Dcm_Dsp_SID3D_u1MemIdIndex,
                                                Dcm_Dsp_SID3D_u1MemRangeIndex,
                                                u1_SesCtrlType );
    if( u1_RetChkMemSes == (Std_ReturnType)E_OK )
    {
        /* Get active security level */
        u1_SecLevel = DCM_SEC_LEV_LOCKED;
        (void)Dcm_GetSecurityLevel( &u1_SecLevel ); /* no return check required */
        /* Check Security lock is canceled */
        u1_RetChkMemSec = Dcm_Dsp_DidMng_ChkMemSec( DCM_DSP_DIDMNG_MEM_WRITE,
                                                    Dcm_Dsp_SID3D_u1MemIdIndex,
                                                    Dcm_Dsp_SID3D_u1MemRangeIndex,
                                                    u1_SecLevel );
        if( u1_RetChkMemSec == (Std_ReturnType)E_OK )
        {
            if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= ( (Dcm_MsgLenType)DCM_DSP_SID3D_ALFID_LEN +  /* no wrap around */
                                                             (Dcm_MsgLenType)u1MemAddrLen +             /* no wrap around */
                                                             (Dcm_MsgLenType)u1MemSizeLen ) )
            {
                /* Write Memory by Address */
                u1_RetVal = Dcm_Dsp_SID3D_WriteMem( DCM_INITIAL );
            }
            else
            {
                /* Response Length Too Long -> 0x14 */
                *ptSendNegRes = (boolean)TRUE;
                *ptNegResCode = DCM_E_RESPONSETOOLONG;
            }
        }
        else
        {
            /* Security lock is non-cancellation -> 0x33 */
            *ptSendNegRes    = (boolean)TRUE;
            *ptNegResCode   = DCM_E_SECURITYACCESSDENIED;
        }
    }
    else
    {
        /* Session Support Check NG -> NRC 0x31 */
        *ptSendNegRes    = (boolean)TRUE;
        *ptNegResCode   = DCM_E_REQUESTOUTOFRANGE;
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID3D_CancelProc                                 */
/* Description   | Cancel process of SID3D request                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID3D_CancelProc
( void )
{
    P2CONST( uint8, AUTOMATIC, DCM_APPL_DATA )  pt_WriteBuff;
    Dcm_NegativeResponseCodeType                u1_DummyErrorCode;
    boolean                                     b_UserNotify;

    pt_WriteBuff = NULL_PTR;
    u1_DummyErrorCode = (uint8)0U;
    b_UserNotify = Dcm_Dsp_Main_GetUserNotifyFlag();

    if( b_UserNotify == (boolean)TRUE )
    {
        (void)Dcm_Dsp_MemMng_WriteMemory( DCM_CANCEL,
                                          Dcm_Dsp_SID3D_u1MemId,
                                          Dcm_Dsp_SID3D_u4MemAddr,
                                          Dcm_Dsp_SID3D_u4MemSize,
                                          pt_WriteBuff,
                                          &u1_DummyErrorCode ); /* no return check required */

        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID3D_WRITEMEM, (boolean)FALSE ); /* no return check required */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID3D_ChkAndSetMemSize                           */
/* Description   | Check MemorySize and if it is correct then set it        */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u4MemSize : Write Memory Size                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK         : Check OK                                */
/*               |   E_NOT_OK     : Check NG                                */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID3D_ChkAndSetMemSize
(
    const uint32    u4MemSize
)
{
    uint32            u4_MaxMemorySize;
    Std_ReturnType    u1_RetVal;

    u1_RetVal       = E_NOT_OK;

    if( u4MemSize != DCM_DSP_SID3D_ILLEGAL_MEMSIZE )
    {
        u4_MaxMemorySize = Dcm_Dsp_MemMng_GetMaxWriteMemorySize();
        if( u4MemSize <= u4_MaxMemorySize )
        {
            Dcm_Dsp_SID3D_u4MemSize = u4MemSize;
            u1_RetVal = E_OK;
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID3D_ChkAndSetMemAddr                           */
/* Description   | Call DidMng-API Dcm_Dsp_DidMng_ChkMemAddress and         */
/*               | Dcm_Dsp_DidMng_ChkMemSize,                               */
/*               | Check MemoryAddress and if it is correct then set it     */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u4MemAddr  : Write Memory Address                   */
/*               | [IN] u1MemId    : Memory Id                              */
/*               | [IN] bMemIdFlag : Memory Id valid or invalid             */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : Check OK                               */
/*               |   E_NOT_OK      : Check NG                               */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID3D_ChkAndSetMemAddr
(
    const uint32    u4MemAddr,
    const uint8     u1MemId,
    const uint8     u1MemIdFlag
)
{
    Std_ReturnType  u1_RetChkMemAddr;
    Std_ReturnType  u1_RetChkMemSize;
    Std_ReturnType  u1_RetVal;

    u1_RetVal           = E_NOT_OK;

    u1_RetChkMemAddr = Dcm_Dsp_DidMng_ChkMemAddress( DCM_DSP_DIDMNG_MEM_WRITE,
                                                     u4MemAddr,
                                                     u1MemIdFlag,
                                                     u1MemId,
                                                     &Dcm_Dsp_SID3D_u1MemIdIndex,
                                                     &Dcm_Dsp_SID3D_u1MemRangeIndex );

    /* Check DidMng-API Return Value */
    if( u1_RetChkMemAddr == (Std_ReturnType)E_OK )
    {
        u1_RetChkMemSize = Dcm_Dsp_DidMng_ChkMemSize( DCM_DSP_DIDMNG_MEM_WRITE,
                                                      Dcm_Dsp_SID3D_u1MemIdIndex,
                                                      Dcm_Dsp_SID3D_u1MemRangeIndex,
                                                      u4MemAddr,
                                                      Dcm_Dsp_SID3D_u4MemSize );

        /* Check DidMng-API Return Value */
        if( u1_RetChkMemSize == (Std_ReturnType)E_OK )
        {
            Dcm_Dsp_SID3D_u4MemAddr = u4MemAddr;
            Dcm_Dsp_SID3D_u1MemId = u1MemId;
            u1_RetVal = E_OK;
        }
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID3D_WriteMem                                   */
/* Description   | Call the callout function and write to memory            */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus     : Operation state                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID3D_WriteMem
(
    const Dcm_OpStatusType    u1OpStatus
)
{
    Dcm_MsgLenType                      u4_ResDataLen;
    Dcm_NegativeResponseCodeType        u1_ErrCode;
    Dcm_NegativeResponseCodeType        u1_NegResCode;
    Std_ReturnType                      u1_RetVal;
    Dcm_ReturnWriteMemoryType           u1_RetWriteMem;
    uint8                               u1_ALFID;
    uint8                               u1_MemAddrIdx;
    uint8                               u1_MemSizeIdx;
    uint8                               u1_MemAddrLen;
    uint8                               u1_MemSizeLen;
    boolean                             b_SendEvent;
    boolean                             b_SendPosRes;

    u4_ResDataLen   = (Dcm_MsgLenType)0U;
    u1_RetVal       = E_OK;
    b_SendPosRes    = (boolean)FALSE;
    b_SendEvent     = (boolean)FALSE;
    u1_ErrCode      = DCM_E_GENERALREJECT;
    u1_NegResCode   = DCM_E_GENERALREJECT;

    Dcm_Dsp_SID3D_GetMemInfo( &u1_ALFID, &u1_MemAddrLen, &u1_MemSizeLen );

    u1_RetWriteMem = Dcm_Dsp_MemMng_WriteMemory( u1OpStatus,
                                                 Dcm_Dsp_SID3D_u1MemId,
                                                 Dcm_Dsp_SID3D_u4MemAddr,
                                                 Dcm_Dsp_SID3D_u4MemSize,
                                                 &Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID3D_ALFID_LEN + u1_MemAddrLen + u1_MemSizeLen],
                                                 &u1_ErrCode );
    /* Check Return Value */
    switch( u1_RetWriteMem )
    {
        case DCM_WRITE_OK:
            Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataLen] =
                Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID3D_REQOFST_ALFID];
            u4_ResDataLen = (Dcm_MsgLenType)DCM_DSP_SID3D_ALFID_LEN;

            for( u1_MemAddrIdx = (uint8)0U; u1_MemAddrIdx < u1_MemAddrLen; u1_MemAddrIdx++ )
            {
                Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataLen + u1_MemAddrIdx] =      /* no wrap around */
                    Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID3D_ALFID_LEN + u1_MemAddrIdx];
            }
            u4_ResDataLen = u4_ResDataLen + (Dcm_MsgLenType)u1_MemAddrLen;  /* no wrap around */

            for( u1_MemSizeIdx = (uint8)0U; u1_MemSizeIdx < u1_MemSizeLen; u1_MemSizeIdx++ )
            {
                Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataLen + u1_MemSizeIdx] =      /* no wrap around */
                    Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID3D_ALFID_LEN + u1_MemAddrLen + u1_MemSizeIdx];
            }
            u4_ResDataLen = u4_ResDataLen + (Dcm_MsgLenType)u1_MemSizeLen;  /* no wrap around */
            Dcm_Dsp_Main_stMsgContext.resDataLen = u4_ResDataLen;

            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
            b_SendPosRes = (boolean)TRUE;
            break;
        case DCM_WRITE_FAILED:
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
            u1_NegResCode = u1_ErrCode;
            break;
        case DCM_WRITE_PENDING:
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
            b_SendEvent = (boolean)TRUE;
            break;
        case DCM_WRITE_FORCE_RCRRP:
            /* NRC 0x78 */
            /*   Request    -> 0x78                              */
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
            u1_NegResCode = DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING;
            break;
        default:
            /*   General Reject    -> 0x10                              */
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
            break;
    }

    if( b_SendEvent == (boolean)TRUE )
    {
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID3D_WRITEMEM ); /* no return check required */
        u1_RetVal = DCM_E_PENDING;
    }
    else
    {
        if( b_SendPosRes == (boolean)TRUE )
        {
            Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
        }
        else
        {
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
        }
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID3D_GetMemInfo                                 */
/* Description   | Get ALFID, MemoryAddress Length and MemorySize Length    */
/*               | from Request Message                                     */
/* Preconditions | None                                                     */
/* Parameters    | [OUT] pt_ALFID      : ALFID                              */
/*               | [OUT] pt_MemAddrLen : Memory Address Length              */
/*               | [OUT] pt_MemSizeLen : Memory Size Length                 */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID3D_GetMemInfo
(
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_ALFID,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_MemAddrLen,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) pt_MemSizeLen
)
{
    uint8   u1_ALFID;

    u1_ALFID = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID3D_REQOFST_ALFID];
    *pt_ALFID = u1_ALFID;
    *pt_MemAddrLen = u1_ALFID & DCM_DSP_SID3D_MEMADDR_MASK;
    *pt_MemSizeLen = ( u1_ALFID & DCM_DSP_SID3D_MEMSIZE_MASK ) >> DCM_DSP_SID3D_MEMSIZE_SHFT4;

    return;
}


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID3D */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-6-0         :2024-02-27                                              */
/****************************************************************************/

/**** End of File************************************************************/
