/* Dcm_Dsp_SID02_c(v5-3-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID02/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

#if ( DCM_OBDTYPE_TYPE_OBD == STD_ON )
#if ( DCM_SUPPORT_SID02 == STD_ON )

#include <Dcm/Dcm_Dsp_SID02.h>
#include <Dcm/Dcm_Dsp_SID02_Callout.h>
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Main_Common.h>
#include <Dem_Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SID02_REQ_DATA_LEN_MIN  ( (Dcm_MsgLenType)2U )
#define DCM_DSP_SID02_REQ_DATA_LEN_MAX  ( (Dcm_MsgLenType)6U )

#define DCM_DSP_SID02_PID_MASK          ( (uint8)0x1FU )

#define DCM_DSP_SID02_PIDKIND_SUP       ( (uint8)0x00U )
#define DCM_DSP_SID02_PIDKIND_NORMAL    ( (uint8)0x01U )

#define DCM_DSP_SID02_PID_LEN           ( (Dcm_MsgLenType)1U )
#define DCM_DSP_SID02_FRAME_LEN         ( (Dcm_MsgLenType)1U )
#define DCM_DSP_SID02_DTC_LEN           ( (Dcm_MsgLenType)( DCM_DSP_SID02_PID_LEN + DCM_DSP_SID02_FRAME_LEN + (Dcm_MsgLenType)2U ) )
#define DCM_DSP_SID02_SUPPID_LEN        ( (Dcm_MsgLenType)( DCM_DSP_SID02_PID_LEN + DCM_DSP_SID02_FRAME_LEN + (Dcm_MsgLenType)4U ) )

#define DCM_DSP_SID02_READ_DATA_NONE    ( (uint8)0x00U )
#define DCM_DSP_SID02_READ_DATA_OK      ( (uint8)0x01U )
#define DCM_DSP_SID02_READ_OVER_FLOW    ( (uint8)0x02U )

#define DCM_DSP_SID02_BIT_31            ( (uint8)31U )

#define DCM_DSP_SID02_NORMALPID_MASK    ( (uint8)0x1FU )
#define DCM_DSP_SID02_REQ_LEN_MASK      ( (uint8)0x01 )
#define DCM_DSP_SID02_REF_END           ( (uint16)0xFFFF )

#define DCM_DSP_SID02_SUPPID_BIT        ( (uint32)0x00000001U )
#define DCM_DSP_SID02_SUPPID_BIT_TOP    ( (uint8)31U )
#define DCM_DSP_SID02_SUPPID_OFS        ( (uint8)1U )


#define DCM_DSP_SID02_BITSHIFT_3        ( (uint8)3U )
#define DCM_DSP_SID02_BITSHIFT_5        ( (uint8)5U )
#define DCM_DSP_SID02_BITSHIFT_8        ( (uint8)8U )
#define DCM_DSP_SID02_BITSHIFT_16       ( (uint8)16U )
#define DCM_DSP_SID02_BITSHIFT_24       ( (uint8)24U )

#define DCM_DSP_SID02_FRAME_POS         ( (uint8)1U )
#define DCM_DSP_SID02_REQ_DATA_PID_POS  ( (uint8)2U )
#define DCM_DSP_SID02_DTC_HI_POS        ( (uint8)2U )
#define DCM_DSP_SID02_DTC_LO_POS        ( (uint8)3U )

#define DCM_DSP_SID02_SUPPID_POS_1      ( (uint8)1U )
#define DCM_DSP_SID02_SUPPID_POS_2      ( (uint8)2U )
#define DCM_DSP_SID02_SUPPID_POS_3      ( (uint8)3U )

#define DCM_DSP_SID02_FRAME_NUM0        ( (uint8)0U )
#define DCM_DSP_SID02_DTC_CLEAR         ( (uint32)0x00000000 )
#define DCM_DSP_SID02_PID_FOR_DTC_READ  ( (uint8)0x02 )
#define DCM_DSP_SID02_FILLBYTE          ( (uint8)0U )

#define DCM_DSP_SID02_DIFF2NEXT_SUP_PID ( (uint8)0x20U )
#define DCM_DSP_SID02_SUPPORT_NONE      ( (uint32)0x00000000U )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Internal Function Prototypes                                               */
/*----------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID02_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID02_CancelProc
(
    void
);

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID02_GetPidDataInfo
(
    CONST( uint8, AUTOMATIC ) u1pid,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptIndex,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptSize
);

static FUNC( uint8, DCM_CODE ) Dcm_Dsp_SID02_MakeDTCData
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext_temp,
    CONST( uint8, AUTOMATIC ) u1reqPID,
    CONST( uint32, AUTOMATIC ) u4dtc
);

static FUNC( uint8, DCM_CODE ) Dcm_Dsp_SID02_MakeSupPidData
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext_temp,
    CONST(uint8, AUTOMATIC) u1reqPID,
    P2CONST(AB_83_ConstV uint32, AUTOMATIC, DCM_CONST) ptSupportPidTblPtr,
    CONST(uint8, AUTOMATIC) u1supportPidNum
);

static FUNC( uint8, DCM_CODE ) Dcm_Dsp_SID02_MakeNormalPidData
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext_temp,
    CONST( uint8, AUTOMATIC ) u1reqPID
);

static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID02_PidSupportCheck
(
    CONST( uint8, AUTOMATIC ) u1reqPID,
    P2CONST( AB_83_ConstV uint32, AUTOMATIC, DCM_CONST ) ptSupportPidTblPtr,
    CONST( uint8, AUTOMATIC ) u1supportPidNum
);

static FUNC( uint8, DCM_CODE ) Dcm_Dsp_SID02_PidKindCheck
(
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqPID
);

static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID02_GenerateAvailPidTable
(
    const boolean bFFDAvail
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*----------------------------------------------------------------------------*/
/* data                                                                       */
/*----------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static VAR( uint32, DCM_VAR_NO_INIT ) Dcm_Dsp_SID02_u4AvailablePidTable[DCM_SID02_SUPPIDTBL];
static VAR( uint8,  DCM_VAR_NO_INIT ) Dcm_Dsp_SID02_u1AvailablePidNumber;

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_SID02                                                */
/* Description   | SID02 request processing                                 */
/* Preconditions |                                                          */
/* Parameters    | [IN]   Dcm_opStatusType             : OpStatus           */
/*               | [IN]   const Dcm_MsgContextType*    : pMsgContext        */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                : Processing normal  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID02 /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID02_InitialProc( pMsgContext );
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        u1_RetVal = Dcm_Dsp_SID02_CancelProc( );
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID02_InitialProc                                */
/* Description   | Execute SID 01 request processing                        */
/* Preconditions |                                                          */
/* Parameters    | [IN]   const Dcm_MsgContextType*    : ptMsgContext       */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                                : Processing normal  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID02_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Std_ReturnType                                          u1_RetVal;
    Dcm_NegativeResponseCodeType                            u1_ErrorCode;
    uint8                                                   u1_GetPidDataResult;
    uint8                                                   u1_TopReqPidKind;
    uint8                                                   u1_ReqPidKind;
    uint8                                                   u1_RetValGetDtc;
    uint8                                                   u1_Pid;
    uint8                                                   u1_FrameNum;
    uint8                                                   u1_CheckResult;
    uint8                                                   u1_ReqPidNum;
    uint32                                                  u4_DTC;
    boolean                                                 b_DemStandbyFlag;
    Dcm_MsgContextType                                      st_MsgContext_temp;

    u1_RetVal = (Std_ReturnType)E_OK;
    u1_ErrorCode = (Dcm_NegativeResponseCodeType)0x00U;
    u4_DTC = DCM_DSP_SID02_DTC_CLEAR;
    b_DemStandbyFlag = (boolean)FALSE;
    st_MsgContext_temp = *ptMsgContext;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    /* Request Data Length Check */
    if( ( st_MsgContext_temp.reqDataLen >= DCM_DSP_SID02_REQ_DATA_LEN_MIN ) &&
        ( st_MsgContext_temp.reqDataLen <= DCM_DSP_SID02_REQ_DATA_LEN_MAX ) &&
        ( (uint8)( st_MsgContext_temp.reqDataLen & DCM_DSP_SID02_REQ_LEN_MASK ) == (uint8)0x00 ) )
    {
        /* Initialize Reaponse Data Length */
        st_MsgContext_temp.resDataLen = (Dcm_MsgLenType)0U;

        /* Get DTC AND SupportPIDTable */
        u1_RetValGetDtc = Dem_DcmGetDTCOfOBDFreezeFrame( DCM_DSP_SID02_FRAME_NUM0, &u4_DTC );
        if ( u1_RetValGetDtc == (Std_ReturnType)E_OK )
        {
            b_DemStandbyFlag = (boolean)TRUE;
            Dcm_Dsp_SID02_GenerateAvailPidTable( (boolean)TRUE );
        }
        else if ( u1_RetValGetDtc == (Std_ReturnType)E_NOT_OK )
        {
            u4_DTC = DCM_DSP_SID02_DTC_CLEAR;
            b_DemStandbyFlag = (boolean)TRUE;
            Dcm_Dsp_SID02_GenerateAvailPidTable( (boolean)FALSE );
        }
        else
        {
            /* No Process */
        }
    }
    else
    {
        /* NRC0x13 */
        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    if( b_DemStandbyFlag == (boolean)TRUE )
    {
        /* Get Top PID Kind */
        u1_TopReqPidKind = Dcm_Dsp_SID02_PidKindCheck( st_MsgContext_temp.reqData[0] );

        /* Loop for all requested PID */
        for( u1_ReqPidNum = (uint8)0U; u1_ReqPidNum < (uint8)st_MsgContext_temp.reqDataLen; u1_ReqPidNum += DCM_DSP_SID02_REQ_DATA_PID_POS )
        {
            u1_Pid = (uint8)st_MsgContext_temp.reqData[u1_ReqPidNum];
            u1_ReqPidKind = Dcm_Dsp_SID02_PidKindCheck(u1_Pid);
            /* Mixed PID Check */
            if( u1_TopReqPidKind == u1_ReqPidKind )
            {
                u1_FrameNum = st_MsgContext_temp.reqData[u1_ReqPidNum + DCM_DSP_SID02_FRAME_POS];
                /* Frame Number Check */
                if( u1_FrameNum == DCM_DSP_SID02_FRAME_NUM0 )
                {
                    /* PID Support Check */
                    u1_CheckResult = Dcm_Dsp_SID02_PidSupportCheck( u1_Pid, Dcm_Dsp_SID02_u4AvailablePidTable, Dcm_Dsp_SID02_u1AvailablePidNumber );
                    if( u1_CheckResult == (Std_ReturnType)E_OK )
                    {
                        u1_GetPidDataResult = DCM_DSP_SID02_READ_DATA_NONE;

                        /* Support PID Process */
                        if( u1_ReqPidKind == DCM_DSP_SID02_PIDKIND_SUP )
                        {
                            u1_GetPidDataResult = Dcm_Dsp_SID02_MakeSupPidData( &st_MsgContext_temp, u1_Pid, Dcm_Dsp_SID02_u4AvailablePidTable, Dcm_Dsp_SID02_u1AvailablePidNumber );
                        }
                        else
                        {
                            if( u1_Pid == DCM_DSP_SID02_PID_FOR_DTC_READ )
                            {
                                /* Pid 0x02 Process */
                                 u1_GetPidDataResult = Dcm_Dsp_SID02_MakeDTCData( &st_MsgContext_temp, u1_Pid, u4_DTC );
                            }
                            else
                            {
                                if( u1_RetValGetDtc == (Std_ReturnType)E_OK )
                                {
                                    /* Normal PID Process */
                                    u1_GetPidDataResult = Dcm_Dsp_SID02_MakeNormalPidData( &st_MsgContext_temp, u1_Pid );
                                }
                            }
                        }

                        if( u1_GetPidDataResult == DCM_DSP_SID02_READ_DATA_OK )
                        {
                            /* No Process */
                        }
                        else if( u1_GetPidDataResult == DCM_DSP_SID02_READ_OVER_FLOW )
                        {
                            /* NRC0x14 */
                            u1_ErrorCode = DCM_E_RESPONSETOOLONG;
                        }
                        else
                        {
                            /* Get Next PID Data */
                        }
                    }
                }
            }
            else
            {
                /* NRC0x31 */
                u1_ErrorCode = DCM_E_REQUESTOUTOFRANGE;
            }


            if( u1_ErrorCode != (Dcm_NegativeResponseCodeType)0x00U )
            {
                break;
            }
        }
        if( st_MsgContext_temp.resDataLen == (Dcm_MsgLenType)0U )
        {
            if( u1_ErrorCode == (Dcm_NegativeResponseCodeType)0x00U )
            {
                /* NRC0x31 */
                u1_ErrorCode = DCM_E_REQUESTOUTOFRANGE;
            }
        }
    }
    else
    {
        if( u1_ErrorCode == (Dcm_NegativeResponseCodeType)0x00U )
        {
            /* NRC0x31 */
            u1_ErrorCode = DCM_E_REQUESTOUTOFRANGE;
        }
    }

    /* Response Data Check */
    if( u1_ErrorCode != (Dcm_NegativeResponseCodeType)0x00U )
    {
        /* NRC */
        Dcm_Dsp_MsgMaker_SendNegRes( &st_MsgContext_temp, u1_ErrorCode );
    }
    else
    {
        Dcm_Dsp_MsgMaker_SendPosRes( &st_MsgContext_temp );
    }

    return u1_RetVal;

}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID02_CancelProc                                 */
/* Description   | SID02 request cancel processing                          */
/* Preconditions |                                                          */
/* Parameters    | -                                                        */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK  : Processing cancel                                */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID02_CancelProc
(
    void
)
{
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return E_OK;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID02_PidKindCheck                               */
/* Description   | Check PID Kind SupportPID or NormalPID                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1reqPID                   : Request PID            */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_SID02_PIDKIND_SUP     : Support PID            */
/*               |   DCM_DSP_SID02_PIDKIND_NORMAL  : Normal PID             */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_SID02_PidKindCheck
(
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqPID
)
{
    uint8 u1_PidKind;

    u1_PidKind = DCM_DSP_SID02_PIDKIND_NORMAL;

    if( ( u1reqPID & DCM_DSP_SID02_PID_MASK ) == DCM_DSP_SID02_PIDKIND_SUP )
    {
        u1_PidKind = DCM_DSP_SID02_PIDKIND_SUP;
    }

    return u1_PidKind;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID02_PidSupportCheck                            */
/* Description   | Check PID Support Check                                  */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1reqPID               : Request PID                */
/*               | [IN] ptSupportPidTblPtr     : PID Support Table          */
/*               | [IN] u1supportPidNum        : Support PID Table Number   */
/* Return Value  | uint8                                                    */
/*               |   E_OK                      : PID Supported              */
/*               |   E_NOT_OK                  : PID Not Supported          */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID02_PidSupportCheck
(
    CONST( uint8, AUTOMATIC ) u1reqPID,
    P2CONST( AB_83_ConstV uint32, AUTOMATIC, DCM_CONST ) ptSupportPidTblPtr,
    CONST( uint8, AUTOMATIC ) u1supportPidNum
)
{
    Std_ReturnType u1_CheckResult;
    uint8          u1_SupportPidTableIndex;
    uint8          u1_SupportBitShiftNum;
    uint32         u4_PidSupportBitMask;
    uint32         u4_PidSupportBit;

    u1_CheckResult = (Std_ReturnType)E_NOT_OK;

    if( u1reqPID != (Dcm_MsgItemType)0x00U )
    {
        /* Check PID Support From BIT of Support PID Table */
        u1_SupportPidTableIndex = (uint8)( (uint8)( u1reqPID - DCM_DSP_SID02_SUPPID_OFS ) >> DCM_DSP_SID02_BITSHIFT_5 );
        if( u1_SupportPidTableIndex < u1supportPidNum )
        {
            u1_SupportBitShiftNum = DCM_DSP_SID02_SUPPID_BIT_TOP - ( (uint8)( u1reqPID - DCM_DSP_SID02_SUPPID_OFS ) & DCM_DSP_SID02_PID_MASK );
            u4_PidSupportBitMask = (uint32)( DCM_DSP_SID02_SUPPID_BIT << u1_SupportBitShiftNum );
            u4_PidSupportBit = u4_PidSupportBitMask & ptSupportPidTblPtr[u1_SupportPidTableIndex];
            if( u4_PidSupportBit != (uint32)0x00000000U )
            {
                u1_CheckResult = (Std_ReturnType)E_OK;
            }
        }
    }
    else
    {
        u1_CheckResult = (Std_ReturnType)E_OK;
    }

    return u1_CheckResult;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID02_MakeNormalPidData                          */
/* Description   | Make Normal PID Data                                     */
/* Preconditions | None                                                     */
/* Parameters    | [IN/OUT] ptMsgContext_temp     : Msg Context             */
/*               | [IN] u1reqPID                  : PID Data Index          */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_SID02_READ_DATA_NONE : Read Data None          */
/*               |   DCM_DSP_SID02_READ_DATA_OK   : Read Data OK            */
/*               |   DCM_DSP_SID02_READ_OVER_FLOW : Read Over Flow          */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_SID02_MakeNormalPidData
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext_temp,
    CONST( uint8, AUTOMATIC ) u1reqPID
)
{
    uint8                                                                    u1_GetPidDataResult;
    uint16                                                                   u2_bufSize;
    uint16                                                                   u2_PidDataSize;
    uint16                                                                   u2_bufIndex;
    uint8                                                                    u1_PidIndex;
    Std_ReturnType                                                           u1_RetValGetFfd;
    Std_ReturnType                                                           u1_RetValGetSize;
    P2CONST( AB_83_ConstV Dcm_Dsp_PidFfdDataType, AUTOMATIC, DCM_APPL_CONST) pt_PidDataPtr;
    uint16                                                                   u2_PidDataBytePos;

    u1_GetPidDataResult = DCM_DSP_SID02_READ_DATA_NONE;

    u2_PidDataSize = (uint16)0x00U;
    u1_PidIndex = (uint8)0x00U;

    u1_RetValGetSize = Dcm_Dsp_SID02_GetPidDataInfo( u1reqPID, &u1_PidIndex, &u2_PidDataSize );
    if( u1_RetValGetSize == (Std_ReturnType)E_OK )
    {
        /* Buffer Over Flow Check */
        if( ( ptMsgContext_temp->resDataLen + DCM_DSP_SID02_PID_LEN + DCM_DSP_SID02_FRAME_LEN + u2_PidDataSize ) <= ptMsgContext_temp->resMaxDataLen )  /* no wrap around */
        {
            for( u2_bufIndex = (uint16)0x00U; u2_bufIndex < ( DCM_DSP_SID02_PID_LEN + DCM_DSP_SID02_FRAME_LEN + u2_PidDataSize ); u2_bufIndex++ )   /* no wrap around */
            {
                ptMsgContext_temp->resData[ptMsgContext_temp->resDataLen + u2_bufIndex] = DCM_DSP_SID02_FILLBYTE;   /* no wrap around */
            }

            ptMsgContext_temp->resData[ptMsgContext_temp->resDataLen] = u1reqPID;
            ptMsgContext_temp->resData[ptMsgContext_temp->resDataLen + DCM_DSP_SID02_PID_LEN] = DCM_DSP_SID02_FRAME_NUM0;   /* no wrap around */

            pt_PidDataPtr = DcmDspPidFfdInfo[u1_PidIndex].ptPidData;

            /* Get Data of OBD Freeze Frame  */
            /* Note : It is a premise that parameter DcmDspPidDataSize and DcmDspPidDataPos are multiples of 8. */
            u2_bufSize = (uint16)( pt_PidDataPtr->u2DcmDspPidDataSize >> DCM_DSP_SID02_BITSHIFT_3 );
            u2_PidDataBytePos = (uint16)( pt_PidDataPtr->u2DcmDspPidDataPos >> DCM_DSP_SID02_BITSHIFT_3 );

            u1_RetValGetFfd = Dem_DcmReadDataOfOBDFreezeFrame(
                u1reqPID,
                (uint8)0x00,
                &ptMsgContext_temp->resData[ptMsgContext_temp->resDataLen + DCM_DSP_SID02_PID_LEN + DCM_DSP_SID02_FRAME_LEN + u2_PidDataBytePos],   /* no wrap around */
                &u2_bufSize);

            if( u1_RetValGetFfd == (Std_ReturnType)E_OK )
            {
                ptMsgContext_temp->resDataLen += (u2_PidDataSize + DCM_DSP_SID02_PID_LEN + DCM_DSP_SID02_FRAME_LEN);    /* no wrap around */
                u1_GetPidDataResult = DCM_DSP_SID02_READ_DATA_OK;
            }
            else
            {
                for( u2_bufIndex = (uint16)0x00U; u2_bufIndex < ( u2_PidDataSize + DCM_DSP_SID02_PID_LEN + DCM_DSP_SID02_FRAME_LEN ); u2_bufIndex++ )   /* no wrap around */
                {
                    ptMsgContext_temp->resData[ptMsgContext_temp->resDataLen + u2_bufIndex] = DCM_DSP_SID02_FILLBYTE;   /* no wrap around */
                }
            }
        }
        else
        {
            u1_GetPidDataResult = DCM_DSP_SID02_READ_OVER_FLOW;
        }
    }
    return u1_GetPidDataResult;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID02_MakeSupPidData                             */
/* Description   | Make Support PID Data                                    */
/* Preconditions | None                                                     */
/* Parameters    | [IN/OUT] ptMsgContext_temp    : Msg Context              */
/*               | [IN] u1reqPID                 : PID Data Index           */
/*               | [IN] ptSupportPidTblPtr       : Support PID Table        */
/*               | [IN] u1supportPidNum          : Support PID Table Number */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_SID02_READ_DATA_NONE : Read Data None          */
/*               |   DCM_DSP_SID02_READ_DATA_OK   : Read Data OK            */
/*               |   DCM_DSP_SID02_READ_OVER_FLOW : Read Over Flow          */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( uint8, DCM_CODE ) Dcm_Dsp_SID02_MakeSupPidData
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext_temp,
    CONST( uint8, AUTOMATIC ) u1reqPID,
    P2CONST( AB_83_ConstV uint32, AUTOMATIC, DCM_CONST ) ptSupportPidTblPtr,
    CONST( uint8, AUTOMATIC ) u1supportPidNum
)
{
    Dcm_MsgLenType u4_ResDataLen;
    uint8          u1_GetPidDataResult;
    uint8          u1_PidTableId;
    uint32         u4_supportPidTbl;

    u4_ResDataLen = ptMsgContext_temp->resDataLen;
    u1_GetPidDataResult = DCM_DSP_SID02_READ_DATA_NONE;

    /* Buffer Over Flow Check */
    if( ( u4_ResDataLen + DCM_DSP_SID02_SUPPID_LEN ) <= ptMsgContext_temp->resMaxDataLen )  /* no wrap around */
    {
        /* Set PIDIdentifier */
        ptMsgContext_temp->resData[u4_ResDataLen] = u1reqPID;
        ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID02_PID_LEN] = DCM_DSP_SID02_FRAME_NUM0;   /* no wrap around */
        /* Get Support PID Data */
        /* Calculate SupportPidTable Index from Request PID */
        u1_PidTableId = (uint8)( u1reqPID >> DCM_DSP_SID02_BITSHIFT_5 );
        u4_supportPidTbl = ptSupportPidTblPtr[u1_PidTableId];
        if( u1_PidTableId < u1supportPidNum )
        {
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID02_PID_LEN + DCM_DSP_SID02_FRAME_LEN] =   /* no wrap around */
                (Dcm_MsgItemType)( u4_supportPidTbl >> DCM_DSP_SID02_BITSHIFT_24 );
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID02_PID_LEN + DCM_DSP_SID02_FRAME_LEN + DCM_DSP_SID02_SUPPID_POS_1] =  /* no wrap around */
                (Dcm_MsgItemType)( u4_supportPidTbl >> DCM_DSP_SID02_BITSHIFT_16 );
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID02_PID_LEN + DCM_DSP_SID02_FRAME_LEN + DCM_DSP_SID02_SUPPID_POS_2] =  /* no wrap around */
                (Dcm_MsgItemType)( u4_supportPidTbl >> DCM_DSP_SID02_BITSHIFT_8 );
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID02_PID_LEN + DCM_DSP_SID02_FRAME_LEN + DCM_DSP_SID02_SUPPID_POS_3] =  /* no wrap around */
                (Dcm_MsgItemType)u4_supportPidTbl;
            ptMsgContext_temp->resDataLen += DCM_DSP_SID02_SUPPID_LEN;  /* no wrap around */
            u1_GetPidDataResult = DCM_DSP_SID02_READ_DATA_OK;
        }
    }
    else
    {
        u1_GetPidDataResult = DCM_DSP_SID02_READ_OVER_FLOW;
    }

    return u1_GetPidDataResult;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID02_MakeDTCData                                */
/* Description   | Make Support PID Data                                    */
/* Preconditions | None                                                     */
/* Parameters    | [IN/OUT] ptMsgContext_temp     : Msg Context             */
/*               | [IN] u1reqPID                  : PID Data Index          */
/*               | [IN] u4dtc                     : DTC Data                */
/* Return Value  | Std_ReturnType                                           */
/*               |   DCM_DSP_SID02_READ_DATA_NONE : Read Data None          */
/*               |   DCM_DSP_SID02_READ_DATA_OK   : Read Data OK            */
/*               |   DCM_DSP_SID02_READ_OVER_FLOW : Read Over Flow          */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_SID02_MakeDTCData
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext_temp,
    CONST( uint8, AUTOMATIC ) u1reqPID,
    CONST( uint32, AUTOMATIC ) u4dtc
)
{
    uint8 u1_GetPidDataResult;

    /* Buffer Over Flow Check */
    if( ( ptMsgContext_temp->resDataLen + DCM_DSP_SID02_DTC_LEN ) <= ptMsgContext_temp->resMaxDataLen ) /* no wrap around */
    {
        ptMsgContext_temp->resData[ptMsgContext_temp->resDataLen] = u1reqPID;
        ptMsgContext_temp->resData[ptMsgContext_temp->resDataLen + DCM_DSP_SID02_PID_LEN] = DCM_DSP_SID02_FRAME_NUM0;   /* no wrap around */

        ptMsgContext_temp->resData[ptMsgContext_temp->resDataLen + DCM_DSP_SID02_DTC_HI_POS] =  /* no wrap around */
            (uint8)( u4dtc >> DCM_DSP_SID02_BITSHIFT_8 ); /* High byte*/

        ptMsgContext_temp->resData[ptMsgContext_temp->resDataLen + DCM_DSP_SID02_DTC_LO_POS] =  /* no wrap around */
            (uint8)u4dtc; /* Low byte*/

        ptMsgContext_temp->resDataLen += DCM_DSP_SID02_DTC_LEN; /* no wrap around */
        u1_GetPidDataResult = DCM_DSP_SID02_READ_DATA_OK;
    }
    else
    {
        u1_GetPidDataResult = DCM_DSP_SID02_READ_OVER_FLOW;
    }

    return u1_GetPidDataResult;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID02_GetPidDataInfo                             */
/* Description   | Get PID Datasize and index                               */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  u1pid     : PID Data Identifier                    */
/*               | [OUT] ptIndex : PID Data Index                           */
/*               | [OUT] ptSize  : PID Data Size                            */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : Read Data OK                           */
/*               |   E_NOT_OK      : Read Data NG                           */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID02_GetPidDataInfo
(
    CONST( uint8, AUTOMATIC ) u1pid,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptIndex,
    P2VAR( uint16, AUTOMATIC, DCM_APPL_DATA ) ptSize
)
{
    Std_ReturnType                                                           u1_RetVal;
    uint8                                                                    u1_PidIndex;
    uint8                                                                    u1_PidNumber;

    u1_RetVal = (Std_ReturnType)E_NOT_OK;
    u1_PidNumber = Dcm_P_SID02_u1PidNumber;

    for( u1_PidIndex = (uint8)0x00U; u1_PidIndex < u1_PidNumber; u1_PidIndex++ )
    {
        if( u1pid == DcmDspPidFfdInfo[u1_PidIndex].u1DcmDspPidIdentifier )
        {
            *ptIndex = u1_PidIndex;
            *ptSize = (uint16)DcmDspPidFfdInfo[u1_PidIndex].u1DcmDspPidSize;
            u1_RetVal = (Std_ReturnType)E_OK;
            break;
        }
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID02_GenerateAvailPidTable                      */
/* Description   | Generate Available Table                                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN]  bFFDAvail       : FFD Availability                 */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID02_GenerateAvailPidTable
(
    const boolean bFFDAvail
)
{
    P2CONST(AB_83_ConstV uint32, AUTOMATIC, DCM_APPL_CONST) pt_SupportPidTblPtr;
    uint32                      u4_SupportedList;
    uint8                       u1_SupportedPid;
    uint8                       u1_SupportedPidNumber;
    uint8                       u1_LoopPidTableNum;
    boolean                     b_CalibUse;

    if( bFFDAvail == (boolean)TRUE )
    {
        u1_SupportedPidNumber = Dcm_P_SID02_u1SupPidNum;
        pt_SupportPidTblPtr = DcmDspSupportPidTableForSid02;
    }
    else
    {
        u1_SupportedPidNumber = Dcm_P_SID02_u1SupPidNum_NoFfd;
        pt_SupportPidTblPtr = DcmDspSupportPidTableForSid02NoFfd;
    }

    Dcm_Dsp_SID02_u1AvailablePidNumber = (uint8)0U;

    for( u1_LoopPidTableNum = (uint8)0U; u1_LoopPidTableNum < u1_SupportedPidNumber; u1_LoopPidTableNum++ )
    {
        u1_SupportedPid = (uint8)(DCM_DSP_SID02_DIFF2NEXT_SUP_PID * u1_LoopPidTableNum);
        b_CalibUse = (boolean)FALSE;
        u4_SupportedList = DCM_DSP_SID02_SUPPORT_NONE;

        Dcm_GetAvailablePIDForSID02( u1_SupportedPid, bFFDAvail, &b_CalibUse, &u4_SupportedList );
        if( b_CalibUse == (boolean)TRUE )
        {
            Dcm_Dsp_SID02_u4AvailablePidTable[u1_LoopPidTableNum] = (uint32)( pt_SupportPidTblPtr[u1_LoopPidTableNum] & u4_SupportedList );
        }
        else
        {
            Dcm_Dsp_SID02_u4AvailablePidTable[u1_LoopPidTableNum] = (uint32)( pt_SupportPidTblPtr[u1_LoopPidTableNum] );
        }

        if( Dcm_Dsp_SID02_u4AvailablePidTable[u1_LoopPidTableNum] != DCM_DSP_SID02_SUPPORT_NONE )
        {
            Dcm_Dsp_SID02_u1AvailablePidNumber = (uint8)(Dcm_Dsp_SID02_u1AvailablePidNumber + (uint8)1U);
        }
    }

    return;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID02 == STD_ON */
#endif /* DCM_OBDTYPE_TYPE_OBD */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2018-12-25                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

