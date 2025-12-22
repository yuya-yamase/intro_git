/* Dcm_Dsp_SID34_c(v5-6-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID34/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

#if( DCM_SUPPORT_SID34 == STD_ON )

#include <Dcm/Dcm_Dsp_SID34.h>
#include <Dcm/Dcm_Dsp_SID34_Callout.h>
#include "../../Dsp/cfg/Dcm_Dsp_SID34_Cfg.h"
#include <Dcm/Dcm_Dsp_DataTfrMng.h>
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dcm/Dcm_Dsl_Ctrl.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Request Information */
#define DCM_DSP_SID34_REQ_LEN_MIN             ((Dcm_MsgLenType)0x00000004U) /* dataFormatIdentifier +             */
                                                                            /* addressAndLengthFormatIdentifier + */
                                                                            /* memoryAddress(1byte) +             */
                                                                            /* memorySize(1byte)                  */
#define DCM_DSP_SID34_REQ_LEN_DFIDANDALFID    ((uint32)2U)
#define DCM_DSP_SID34_REQ_LEN_VALID_MEMADDR   ((uint8)4U)
#define DCM_DSP_SID34_REQ_LEN_VALID_MEMSIZE   ((uint8)4U)
#define DCM_DSP_SID34_REQ_DATA_OFFMEMADDR     ((uint32)0x0000000FU)
#define DCM_DSP_SID34_REQ_DATA_ALFID45        ((uint8)0x45U)
#define DCM_DSP_SID34_REQ_POS_DFID            ((uint8)0x00U)
#define DCM_DSP_SID34_REQ_POS_ALFID           ((uint8)0x01U)
#define DCM_DSP_SID34_REQ_POS_MEMADDR1_OFS    ((uint8)0x01U)
#define DCM_DSP_SID34_REQ_POS_MEMADDR2_OFS    ((uint8)0x02U)
#define DCM_DSP_SID34_REQ_POS_MEMADDR3_OFS    ((uint8)0x03U)
#define DCM_DSP_SID34_REQ_POS_MEMSIZE1_OFS    ((uint8)0x01U)
#define DCM_DSP_SID34_REQ_POS_MEMSIZE2_OFS    ((uint8)0x02U)
#define DCM_DSP_SID34_REQ_POS_MEMSIZE3_OFS    ((uint8)0x03U)
#define DCM_DSP_SID34_REQ_POS_MEMID_MEMADDR0  ((uint8)0x02U)
#define DCM_DSP_SID34_REQ_POS_MEMID_MEMADDR1  ((uint8)0x03U)
#define DCM_DSP_SID34_REQ_POS_MEMID_MEMADDR2  ((uint8)0x04U)
#define DCM_DSP_SID34_REQ_POS_MEMID_MEMADDR3  ((uint8)0x05U)
#define DCM_DSP_SID34_REQ_POS_MEMID_MEMADDR4  ((uint8)0x06U)
#define DCM_DSP_SID34_REQ_POS_MEMID_MEMSIZE0  ((uint8)0x07U)
#define DCM_DSP_SID34_REQ_POS_MEMID_MEMSIZE1  ((uint8)0x08U)
#define DCM_DSP_SID34_REQ_POS_MEMID_MEMSIZE2  ((uint8)0x09U)
#define DCM_DSP_SID34_REQ_POS_MEMID_MEMSIZE3  ((uint8)0x0AU)

/* Response Information */
#define DCM_DSP_SID34_RES_POS_LFID             ((uint8)0U)
#define DCM_DSP_SID34_RES_POS_MNROB_0          ((uint8)1U)
#define DCM_DSP_SID34_RES_POS_MNROB_1          ((uint8)2U)
#define DCM_DSP_SID34_RES_POS_MNROB_2          ((uint8)3U)
#define DCM_DSP_SID34_RES_POS_MNROB_3          ((uint8)4U)
#define DCM_DSP_SID34_RES_LEN_LFID             ((uint32)1U)
#define DCM_DSP_SID34_RES_LEN_MNROB_4B         ((uint32)4U)
#define DCM_DSP_SID34_RES_LEN_MNROB_2B         ((uint32)2U)
#define DCM_DSP_SID34_RES_LEN_SIDANDBSC        ((uint32)2U)

/* Bitshift Information */
#define DCM_DSP_SID34_BITSHIFT_4               ((uint8)4U)
#define DCM_DSP_SID34_BITSHIFT_8               ((uint8)8U)
#define DCM_DSP_SID34_BITSHIFT_16              ((uint8)16U)
#define DCM_DSP_SID34_BITSHIFT_24              ((uint8)24U)

#define DCM_DSP_SID34_SUP_LFID_2B              ((uint8)0x20U)
#define DCM_DSP_SID34_MNROB_LEN_2BMAX          ((uint32)0x0000FFFFU)
#define DCM_DSP_SID34_MNROB_2BMAX_H            ((uint8)0xFFU)
#define DCM_DSP_SID34_MNROB_2BMAX_L            ((uint8)0xFFU)
#define DCM_DSP_SID34_VALID_REQDATA            ((uint8)0x00U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID34_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID34_ChkSupportedDfidDL
(
    const Dcm_OpStatusType u1OpStatus
);

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID34_ChkAndStoredRequestData
( void );

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID34_RequestDownLoadProc
(
    const Dcm_OpStatusType u1OpStatus
);

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID34_CancelProc
( void );

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static VAR( uint32, DCM_VAR_NO_INIT ) Dcm_Dsp_SID34_u4MemoryAddress;
static VAR( uint32, DCM_VAR_NO_INIT ) Dcm_Dsp_SID34_u4MemorySize;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_SID34_u1Dfid;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_SID34_u1MemoryId;

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
/* Function Name | Dcm_Dsp_SID34_Init                                       */
/* Description   | SID34 initialization                                     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID34_Init
( void )
{
    Dcm_Dsp_SID34_u4MemoryAddress = (uint32)0x00000000U;
    Dcm_Dsp_SID34_u4MemorySize    = (uint32)0x00000000U;
    Dcm_Dsp_SID34_u1Dfid          = (uint8)0x00U;
    Dcm_Dsp_SID34_u1MemoryId      = (uint8)0x00U;

    return;
}

/****************************************************************************/
/* Function Name | Dcm_SID34                                                */
/* Description   | Request processing of SID34                              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus    : Operation state                       */
/*               | [IN] pMsgContext : Message Context                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : Processing normal                      */
/*               |   DCM_E_PENDING : Pending                                */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID34
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType  u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID34_InitialProc( pMsgContext );
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID34_CancelProc();
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

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID34_ChkSupportedDfidDLCbk                      */
/* Description   | Callback function for event delivery registration of     */
/*               | Xxx_CheckSupportedDfidDL                                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID34_ChkSupportedDfidDLCbk
(
    const uint8 u1EventId
)
{
    Std_ReturnType  u1_RetVal;

    u1_RetVal = Dcm_Dsp_SID34_ChkSupportedDfidDL( DCM_PENDING );
    if( u1_RetVal == (Std_ReturnType)E_OK )
    {
        u1_RetVal = Dcm_Dsp_SID34_ChkAndStoredRequestData();
        if( u1_RetVal == (Std_ReturnType)E_OK )
        {
            (void)Dcm_Dsp_SID34_RequestDownLoadProc( DCM_INITIAL );             /* no return check required */
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID34_ProcReqDownloadCbk                         */
/* Description   | Callback function for event delivery registration of     */
/*               | Xxx_ProcessRequestDownload                               */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID34_ProcReqDownloadCbk
(
    const uint8 u1EventId
)
{
    (void)Dcm_Dsp_SID34_RequestDownLoadProc( DCM_PENDING );             /* no return check required */

    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID34_InitialProc                                */
/* Description   | Initial process of SID34                                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext : Message Context                      */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : Processing normal                      */
/*               |   E_NOT_OK      : Processing not normal                  */
/*               |   DCM_E_PENDING : Pending                                */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID34_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Std_ReturnType  u1_RetVal;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    u1_RetVal = E_OK;

    if( Dcm_Dsp_Main_stMsgContext.reqDataLen >= DCM_DSP_SID34_REQ_LEN_MIN )
    {
        Dcm_Dsp_SID34_u1Dfid = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID34_REQ_POS_DFID];
        u1_RetVal = Dcm_Dsp_SID34_ChkSupportedDfidDL( DCM_INITIAL );
        if( u1_RetVal == (Std_ReturnType)E_OK )
        {
            u1_RetVal = Dcm_Dsp_SID34_ChkAndStoredRequestData();
            if( u1_RetVal == (Std_ReturnType)E_OK )
            {
                u1_RetVal = Dcm_Dsp_SID34_RequestDownLoadProc( DCM_INITIAL );
            }
        }
    }
    else
    {
        /* NRC0x13 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT );
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID34_ChkSupportedDfidDL                         */
/* Description   | Check on supported dataFormatIdentifier for download     */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus : Operation state                        */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : DataFormat identifier is supported     */
/*               |   E_NOT_OK      : DataFormat identifier is not supported */
/*               |   DCM_E_PENDING : Check is not yet finished              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID34_ChkSupportedDfidDL
(
    const Dcm_OpStatusType u1OpStatus
)
{
    Std_ReturnType  u1_RetVal;

    u1_RetVal = Dcm_Dsp_SID34_CallCheckSupportedDfidDLFnc( u1OpStatus,
                                                           Dcm_Dsp_SID34_u1Dfid );
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
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID34_CHKDFID );             /* no return check required */
    }
    else if( u1_RetVal == (Std_ReturnType)E_NOT_OK )
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }

        /* NRC0x31 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     DCM_E_REQUESTOUTOFRANGE );
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
/* Function Name | Dcm_Dsp_SID34_ChkAndStoredRequestData                    */
/* Description   | Check request data and if it is correct then stored it   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK     : Check OK                                    */
/*               |   E_NOT_OK : Check NG                                    */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID34_ChkAndStoredRequestData
( void )
{
    uint32                        u4_DataFullLen;
    uint32                        u4_MemorySizeLen;
    uint32                        u4_MemoryAddressLen;
    uint8                         u1_InvalidMemAddrLen;
    uint8                         u1_InvalidMemSizeLen;
    uint8                         u1_InvalidMemAddrIdx;
    uint8                         u1_InvalidMemSizeIdx;
    uint8                         u1_InvalidMemAddrLenCnt;
    uint8                         u1_InvalidMemSizeLenCnt;
    uint8                         u1_MemAddrIdx;
    uint8                         u1_MemSizeIdx;
    Std_ReturnType                u1_RetChkAlfid;
    Std_ReturnType                u1_RetVal;
    Dcm_NegativeResponseCodeType  u1_ErrorCode;
    boolean                       b_SendNegResFlag;
    boolean                       b_IsValidMemAddr;
    boolean                       b_IsValidMemSize;

    u1_RetVal = E_NOT_OK;
    b_SendNegResFlag = (boolean)FALSE;

    u1_RetChkAlfid = Dcm_Dsp_DataTfrMng_ChkAlfid( Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID34_REQ_POS_ALFID] );
    if( u1_RetChkAlfid == (Std_ReturnType)E_OK )
    {
        u4_MemorySizeLen = (uint32)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID34_REQ_POS_ALFID] >> DCM_DSP_SID34_BITSHIFT_4;
        u4_MemoryAddressLen = (uint32)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID34_REQ_POS_ALFID] &
                              DCM_DSP_SID34_REQ_DATA_OFFMEMADDR;
        u4_DataFullLen = DCM_DSP_SID34_REQ_LEN_DFIDANDALFID +               /* no wrap around */
                         u4_MemorySizeLen +                                 /* no wrap around */
                         u4_MemoryAddressLen;
        if( Dcm_Dsp_Main_stMsgContext.reqDataLen == (Dcm_MsgLenType)u4_DataFullLen )
        {
            if( Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID34_REQ_POS_ALFID] == DCM_DSP_SID34_REQ_DATA_ALFID45 )
            {
                Dcm_Dsp_SID34_u1MemoryId = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID34_REQ_POS_MEMID_MEMADDR0];
                Dcm_Dsp_SID34_u4MemoryAddress = (uint32)((uint32)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID34_REQ_POS_MEMID_MEMADDR1] << DCM_DSP_SID34_BITSHIFT_24 ) |
                                                (uint32)((uint32)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID34_REQ_POS_MEMID_MEMADDR2] << DCM_DSP_SID34_BITSHIFT_16 ) |
                                                (uint32)((uint32)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID34_REQ_POS_MEMID_MEMADDR3] << DCM_DSP_SID34_BITSHIFT_8 ) |
                                                (uint32)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID34_REQ_POS_MEMID_MEMADDR4];

                Dcm_Dsp_SID34_u4MemorySize = (uint32)((uint32)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID34_REQ_POS_MEMID_MEMSIZE0] << DCM_DSP_SID34_BITSHIFT_24 ) |
                                             (uint32)((uint32)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID34_REQ_POS_MEMID_MEMSIZE1] << DCM_DSP_SID34_BITSHIFT_16 ) |
                                             (uint32)((uint32)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID34_REQ_POS_MEMID_MEMSIZE2] << DCM_DSP_SID34_BITSHIFT_8 ) |
                                             (uint32)Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID34_REQ_POS_MEMID_MEMSIZE3];
                u1_RetVal = E_OK;
            }
            else
            {
                b_IsValidMemAddr = (boolean)TRUE;

                /* u4_MemoryAddressLen is always 4byte or higher, since DcmDspSupportedAddressAndLengthFormatIdentifier cannot set less than 0x44 */
                u1_InvalidMemAddrLen = (uint8)( (uint8)u4_MemoryAddressLen - DCM_DSP_SID34_REQ_LEN_VALID_MEMADDR );
                for( u1_InvalidMemAddrLenCnt = (uint8)0U; u1_InvalidMemAddrLenCnt < u1_InvalidMemAddrLen; u1_InvalidMemAddrLenCnt++ )
                {
                    /* Check if MemoryAddress data value outside the valid range is 0x00 */
                    u1_InvalidMemAddrIdx = (uint8)( (uint8)DCM_DSP_SID34_REQ_LEN_DFIDANDALFID + u1_InvalidMemAddrLenCnt );
                    if( Dcm_Dsp_Main_stMsgContext.reqData[u1_InvalidMemAddrIdx] != DCM_DSP_SID34_VALID_REQDATA )
                    {
                        b_IsValidMemAddr = (boolean)FALSE;
                        break;
                    }
                }

                if( b_IsValidMemAddr == (boolean)TRUE )
                {
                    b_IsValidMemSize = (boolean)TRUE;

                    /* u4_MemorySizeLen is always 4byte or higher, since DcmDspSupportedAddressAndLengthFormatIdentifier cannot set less than 0x44 */
                    u1_InvalidMemSizeLen = (uint8)( (uint8)u4_MemorySizeLen - DCM_DSP_SID34_REQ_LEN_VALID_MEMSIZE );
                    for( u1_InvalidMemSizeLenCnt = (uint8)0U; u1_InvalidMemSizeLenCnt < u1_InvalidMemSizeLen; u1_InvalidMemSizeLenCnt++ )
                    {
                        /* Check if MemorySize data value outside the valid range is 0x00 */
                        u1_InvalidMemSizeIdx = (uint8)( (uint8)DCM_DSP_SID34_REQ_LEN_DFIDANDALFID + (uint8)u4_MemoryAddressLen + u1_InvalidMemSizeLenCnt );
                        if( Dcm_Dsp_Main_stMsgContext.reqData[u1_InvalidMemSizeIdx] != DCM_DSP_SID34_VALID_REQDATA )
                        {
                            b_IsValidMemSize = (boolean)FALSE;
                            break;
                        }
                    }

                    if( b_IsValidMemSize == (boolean)TRUE )
                    {
                        u1_MemAddrIdx = (uint8)( (uint8)DCM_DSP_SID34_REQ_LEN_DFIDANDALFID + u1_InvalidMemAddrLen );
                        u1_MemSizeIdx = (uint8)( (uint8)DCM_DSP_SID34_REQ_LEN_DFIDANDALFID + (uint8)u4_MemoryAddressLen + u1_InvalidMemSizeLen );

                        Dcm_Dsp_SID34_u1MemoryId = (uint8)0U;
                        Dcm_Dsp_SID34_u4MemoryAddress = (uint32)((uint32)Dcm_Dsp_Main_stMsgContext.reqData[u1_MemAddrIdx] << DCM_DSP_SID34_BITSHIFT_24 ) |
                                                        (uint32)((uint32)Dcm_Dsp_Main_stMsgContext.reqData[u1_MemAddrIdx + DCM_DSP_SID34_REQ_POS_MEMADDR1_OFS] << DCM_DSP_SID34_BITSHIFT_16 ) |
                                                        (uint32)((uint32)Dcm_Dsp_Main_stMsgContext.reqData[u1_MemAddrIdx + DCM_DSP_SID34_REQ_POS_MEMADDR2_OFS] << DCM_DSP_SID34_BITSHIFT_8 ) |
                                                        (uint32)Dcm_Dsp_Main_stMsgContext.reqData[u1_MemAddrIdx + DCM_DSP_SID34_REQ_POS_MEMADDR3_OFS];

                        Dcm_Dsp_SID34_u4MemorySize = (uint32)((uint32)Dcm_Dsp_Main_stMsgContext.reqData[u1_MemSizeIdx] << DCM_DSP_SID34_BITSHIFT_24 ) |
                                                     (uint32)((uint32)Dcm_Dsp_Main_stMsgContext.reqData[u1_MemSizeIdx + DCM_DSP_SID34_REQ_POS_MEMSIZE1_OFS] << DCM_DSP_SID34_BITSHIFT_16 ) |
                                                     (uint32)((uint32)Dcm_Dsp_Main_stMsgContext.reqData[u1_MemSizeIdx + DCM_DSP_SID34_REQ_POS_MEMSIZE2_OFS] << DCM_DSP_SID34_BITSHIFT_8 ) |
                                                     (uint32)Dcm_Dsp_Main_stMsgContext.reqData[u1_MemSizeIdx + DCM_DSP_SID34_REQ_POS_MEMSIZE3_OFS];
                        u1_RetVal = E_OK;
                    }
                    else
                    {
                        /* NRC0x31 */
                        u1_ErrorCode = DCM_E_REQUESTOUTOFRANGE;
                        b_SendNegResFlag = (boolean)TRUE;
                    }
                }
                else
                {
                    /* NRC0x31 */
                    u1_ErrorCode = DCM_E_REQUESTOUTOFRANGE;
                    b_SendNegResFlag = (boolean)TRUE;
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
        /* NRC0x31 */
        u1_ErrorCode = DCM_E_REQUESTOUTOFRANGE;
        b_SendNegResFlag = (boolean)TRUE;
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     u1_ErrorCode );
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID34_RequestDownLoadProc                        */
/* Description   | Process of request download                              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus : Operation state                          */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : Request was successful                 */
/*               |   E_NOT_OK      : Request was not successful             */
/*               |   DCM_E_PENDING : Request is not yet finished            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID34_RequestDownLoadProc
(
    const Dcm_OpStatusType u1OpStatus
)
{
    uint32                        u4_MaxNumOfBlockLen;
    uint32                        u4_BlockLen;
    uint8                         u1_SupportLengthFormatId;
    Std_ReturnType                u1_RetProcReqDl;
    Std_ReturnType                u1_RetVal;
    Dcm_NegativeResponseCodeType  u1_ErrorCode;

    u1_RetVal = E_NOT_OK;
    u1_ErrorCode = DCM_E_GENERALREJECT;

    u4_BlockLen = (uint32)Dcm_Dsl_GetRxBufSize( Dcm_Dsp_Main_stMsgContext.dcmRxPduId );
    u4_BlockLen = u4_BlockLen -                                                         /* no wrap around */
                  DCM_DSP_SID34_RES_LEN_SIDANDBSC;
    u1_RetProcReqDl = Dcm_Dsp_DataTfrMng_ProcReqDL( u1OpStatus,
                                                    Dcm_Dsp_SID34_u1Dfid,
                                                    Dcm_Dsp_SID34_u1MemoryId,
                                                    Dcm_Dsp_SID34_u4MemoryAddress,
                                                    Dcm_Dsp_SID34_u4MemorySize,
                                                    &u4_BlockLen,
                                                    &u1_ErrorCode );
    if( u1_RetProcReqDl == (Std_ReturnType)E_OK )
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }

        u4_MaxNumOfBlockLen = u4_BlockLen +                                             /* no wrap around */
                              DCM_DSP_SID34_RES_LEN_SIDANDBSC;
        u1_SupportLengthFormatId = Dcm_Dsp_SID34_u1SupportLengthFormatId;
        Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID34_RES_POS_LFID] = u1_SupportLengthFormatId;
        if( u1_SupportLengthFormatId == DCM_DSP_SID34_SUP_LFID_2B )
        {
            if( u4_MaxNumOfBlockLen > DCM_DSP_SID34_MNROB_LEN_2BMAX )
            {
                Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID34_RES_POS_MNROB_0] = DCM_DSP_SID34_MNROB_2BMAX_H;
                Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID34_RES_POS_MNROB_1] = DCM_DSP_SID34_MNROB_2BMAX_L;
            }
            else
            {
                Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID34_RES_POS_MNROB_0] = (uint8)(u4_MaxNumOfBlockLen >> DCM_DSP_SID34_BITSHIFT_8);
                Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID34_RES_POS_MNROB_1] = (uint8)u4_MaxNumOfBlockLen;
            }
            Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID34_RES_LEN_LFID +
                                                   DCM_DSP_SID34_RES_LEN_MNROB_2B;
        }
        else
        {
            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID34_RES_POS_MNROB_0] = (uint8)(u4_MaxNumOfBlockLen >> DCM_DSP_SID34_BITSHIFT_24);
            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID34_RES_POS_MNROB_1] = (uint8)(u4_MaxNumOfBlockLen >> DCM_DSP_SID34_BITSHIFT_16);
            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID34_RES_POS_MNROB_2] = (uint8)(u4_MaxNumOfBlockLen >> DCM_DSP_SID34_BITSHIFT_8);
            Dcm_Dsp_Main_stMsgContext.resData[DCM_DSP_SID34_RES_POS_MNROB_3] = (uint8)u4_MaxNumOfBlockLen;

            Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID34_RES_LEN_LFID +
                                                   DCM_DSP_SID34_RES_LEN_MNROB_4B;
        }
        
        Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );

        u1_RetVal = E_OK;
    }
    else if( u1_RetProcReqDl == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID34_PROCREQDL );               /* no return check required */

        u1_RetVal = DCM_E_PENDING;
    }
    else
    {
        if( u1OpStatus == (Dcm_OpStatusType)DCM_PENDING )
        {
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }

        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     u1_ErrorCode );
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID34_CancelProc                                 */
/* Description   | Cancel process of SID34                                  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK : Processing normal                               */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID34_CancelProc
( void )
{
    uint32                                 u4_DummyBlockLength;
    Std_ReturnType  u1_RetVal;
    Dcm_NegativeResponseCodeType           u1_DummyErrorCode;
    boolean         b_UserNotifyFlag;

    u1_RetVal = E_OK;
    u4_DummyBlockLength = (uint32)0U;
    u1_DummyErrorCode  = (uint8)0U;

    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();
    if( b_UserNotifyFlag == (boolean)TRUE )
    {
        (void)Dcm_Dsp_SID34_CallCheckSupportedDfidDLFnc( DCM_CANCEL,                /* no return check required */
                                                         0x00U );

        (void)Dcm_Dsp_DataTfrMng_ProcReqDL( DCM_CANCEL,                             /* no return check required */
                                            0x00U,
                                            0x00U,
                                            0x00000000U,
                                            0x00000000U,
                                            &u4_DummyBlockLength,
                                            &u1_DummyErrorCode );

        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID34_CHKDFID,                 /* no return check required */
                                         (boolean)FALSE );

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID34_PROCREQDL,               /* no return check required */
                                         (boolean)FALSE );

    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return u1_RetVal;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* DCM_SUPPORT_SID34 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-6-0         :2024-02-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

