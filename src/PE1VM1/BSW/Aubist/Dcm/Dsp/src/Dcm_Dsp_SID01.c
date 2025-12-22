/* Dcm_Dsp_SID01_c(v5-3-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID01/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

#if ( DCM_OBDTYPE_TYPE_OBD == STD_ON )
#if ( DCM_SUPPORT_SID01 == STD_ON )

#include <Dcm/Dcm_Dsp_SID01.h>
#include "../../Dsp/cfg/Dcm_Dsp_SID01_Cfg.h"
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Dsp_Main.h>
#include <Dcm/Dcm_Dsp_OBDIf.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SID01_REQ_DATA_LEN_MIN  ( (Dcm_MsgLenType)1U )
#define DCM_DSP_SID01_REQ_DATA_LEN_MAX  ( (Dcm_MsgLenType)6U )

#define DCM_DSP_SID01_PID_MASK          ( (uint8)0x1FU )

#define DCM_DSP_SID01_PIDKIND_SUP       ( (uint8)0x00U )
#define DCM_DSP_SID01_PIDKIND_NORMAL    ( (uint8)0x01U )

#define DCM_DSP_SID01_PID_LEN           ( (Dcm_MsgLenType)1U )
#define DCM_DSP_SID01_SUPPID_LEN        ( (Dcm_MsgLenType)4U )

#define DCM_DSP_SID01_READ_DATA_NONE    ( (uint8)0x00U )
#define DCM_DSP_SID01_READ_DATA_OK      ( (uint8)0x01U )
#define DCM_DSP_SID01_READ_OVER_FLOW    ( (uint8)0x02U )

#define DCM_DSP_SID01_SUPPID_BIT        ( (uint32)0x00000001U )
#define DCM_DSP_SID01_SUPPID_BIT_TOP    ( (uint8)31U )
#define DCM_DSP_SID01_SUPPID_OFS        ( (uint8)1U )

#define DCM_DSP_SID01_BITSHIFT_3        ( (uint8)3U )
#define DCM_DSP_SID01_BITSHIFT_5        ( (uint8)5U )
#define DCM_DSP_SID01_BITSHIFT_8        ( (uint8)8U )
#define DCM_DSP_SID01_BITSHIFT_16       ( (uint8)16U )
#define DCM_DSP_SID01_BITSHIFT_24       ( (uint8)24U )

#define DCM_DSP_SID01_RES_DATA_POS_1    ( (uint8)1U )
#define DCM_DSP_SID01_RES_DATA_POS_2    ( (uint8)2U )
#define DCM_DSP_SID01_RES_DATA_POS_3    ( (uint8)3U )

#define DCM_DSP_SID01_DIFF2NEXT_SUP_PID ( (uint8)0x20U )
#define DCM_DSP_SID01_SUPPORT_NONE      ( (uint32)0x00000000U )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID01_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID01_CancelProc
(
    void
);
static FUNC ( uint8, DCM_CODE ) Dcm_Dsp_SID01_PidKindCheck
(
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1ReqPid
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID01_PidSupportCheck
(
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1ReqPid
);
static FUNC ( uint8, DCM_CODE ) Dcm_Dsp_SID01_MakeNormalPidData
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext_temp,
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1ReqPid
);
static FUNC ( uint8, DCM_CODE ) Dcm_Dsp_SID01_MakeSupPidData
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext_temp,
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1ReqPid
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID01_GetPidDataInfoIdx
(
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1ReqPid,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptPidDataInfoIndex
);
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID01_GenerateAvailPidTable
(
    void
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static VAR( uint32, DCM_VAR_NO_INIT ) Dcm_Dsp_SID01_u4AvailablePidTable[DCM_SID01_SUPPIDTBL];
static VAR( uint8,  DCM_VAR_NO_INIT ) Dcm_Dsp_SID01_u1AvailablePidNumber;

#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_SID01                                                */
/* Description   | SID01 request processing                                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus        : Operation state                   */
/*               | [IN] pMsgContext     : Message Context                   */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK               : Processing normal                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID01 /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = (Std_ReturnType)E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID01_InitialProc( pMsgContext );
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        Dcm_Dsp_SID01_CancelProc();
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
/* Function Name | Dcm_Dsp_SID01_InitialProc                                */
/* Description   | Initial process of SID01 request                         */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext    : Message Context                   */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK               : Processing normal                 */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID01_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Std_ReturnType               u1_RetVal;
    Std_ReturnType               u1_CheckResult;
    Dcm_NegativeResponseCodeType u1_ErrorCode;
    uint8                        u1_GetPidDataResult;
    uint8                        u1_TopReqPidKind;
    uint8                        u1_ReqPidKind;
    uint8                        u1_ReqPidNum;
    Dcm_MsgItemType              u1_ReqData;
    Dcm_MsgContextType           st_MsgContext_temp;

    u1_RetVal = (Std_ReturnType)E_OK;
    u1_ErrorCode = (Dcm_NegativeResponseCodeType)0x00U;
    st_MsgContext_temp = *ptMsgContext;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    /* Request Data Length Check */
    if( ( st_MsgContext_temp.reqDataLen >= DCM_DSP_SID01_REQ_DATA_LEN_MIN ) &&
        ( st_MsgContext_temp.reqDataLen <= DCM_DSP_SID01_REQ_DATA_LEN_MAX ) )
    {
        /* Initialize Reaponse Data Length */
        st_MsgContext_temp.resDataLen = (Dcm_MsgLenType)0U;

        /* Genarate Available PID Table */
        Dcm_Dsp_SID01_GenerateAvailPidTable();

        /* Get Top PID Kind */
        u1_TopReqPidKind = Dcm_Dsp_SID01_PidKindCheck( st_MsgContext_temp.reqData[0] );

        for( u1_ReqPidNum = (uint8)0U; u1_ReqPidNum < (uint8)st_MsgContext_temp.reqDataLen; u1_ReqPidNum++ )
        {
            u1_ReqData = st_MsgContext_temp.reqData[u1_ReqPidNum];
            u1_ReqPidKind = Dcm_Dsp_SID01_PidKindCheck( u1_ReqData );
            /* Mixed PID Check */
            if( u1_TopReqPidKind == u1_ReqPidKind )
            {
                /* PID Support Check */
                u1_CheckResult = Dcm_Dsp_SID01_PidSupportCheck( u1_ReqData );
                if( u1_CheckResult == (Std_ReturnType)E_OK )
                {
                    /* Normal PID Process */
                    if( u1_ReqPidKind == DCM_DSP_SID01_PIDKIND_NORMAL )
                    {
                        /* Make Normal PID Data */
                        u1_GetPidDataResult = Dcm_Dsp_SID01_MakeNormalPidData( &st_MsgContext_temp, u1_ReqData );
                    }
                    /* Support PID Process */
                    else
                    {
                        /* Make Support PID Data */
                        u1_GetPidDataResult = Dcm_Dsp_SID01_MakeSupPidData( &st_MsgContext_temp, u1_ReqData );
                    }

                    if( u1_GetPidDataResult == DCM_DSP_SID01_READ_OVER_FLOW )
                    {
                        /* NRC0x14 */
                        u1_ErrorCode = DCM_E_RESPONSETOOLONG;
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
        /* NRC0x13 */
        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
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
/* Function Name | Dcm_Dsp_SID01_CancelProc                                 */
/* Description   | Cancel process of SID01 request                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID01_CancelProc
(
    void
)
{
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID01_PidKindCheck                               */
/* Description   | Check PID Kind SupportPID or NormalPID                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1ReqPid                  : Request PID             */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_SID01_PIDKIND_SUP    : Support PID             */
/*               |   DCM_DSP_SID01_PIDKIND_NORMAL : Normal PID              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( uint8, DCM_CODE ) Dcm_Dsp_SID01_PidKindCheck
(
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1ReqPid
)
{
    uint8 u1_PidKind;

    u1_PidKind = DCM_DSP_SID01_PIDKIND_NORMAL;

    if( (uint8)( u1ReqPid & DCM_DSP_SID01_PID_MASK ) == DCM_DSP_SID01_PIDKIND_SUP )
    {
        u1_PidKind = DCM_DSP_SID01_PIDKIND_SUP;
    }

    return u1_PidKind;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID01_PidSupportCheck                            */
/* Description   | Check PID Support                                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1ReqPid           : Request PID                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                  : PID Supported                  */
/*               |   E_NOT_OK              : PID Not Supported              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID01_PidSupportCheck
(
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1ReqPid
)
{
    Std_ReturnType u1_CheckResult;
    uint8          u1_SupportPidTableIndex;
    uint8          u1_SupportBitShiftNum;
    uint32         u4_PidSupportBitMask;
    uint32         u4_PidSupportBit;
    uint8          u1_SupPidNumber;

    u1_CheckResult = (Std_ReturnType)E_NOT_OK;
    u1_SupPidNumber = Dcm_Dsp_SID01_u1AvailablePidNumber;

    if( u1ReqPid != (Dcm_MsgItemType)0x00U )
    {
        /* Check PID Support From BIT of Support PID Table */
        u1_SupportPidTableIndex = (uint8)( (uint8)( u1ReqPid - DCM_DSP_SID01_SUPPID_OFS ) >> DCM_DSP_SID01_BITSHIFT_5 );
        if( u1_SupportPidTableIndex < u1_SupPidNumber )
        {
            u1_SupportBitShiftNum = DCM_DSP_SID01_SUPPID_BIT_TOP - (uint8)( (uint8)( u1ReqPid - DCM_DSP_SID01_SUPPID_OFS ) & DCM_DSP_SID01_PID_MASK );
            u4_PidSupportBitMask = (uint32)( DCM_DSP_SID01_SUPPID_BIT << u1_SupportBitShiftNum );
            u4_PidSupportBit = (uint32)( u4_PidSupportBitMask & Dcm_Dsp_SID01_u4AvailablePidTable[u1_SupportPidTableIndex] );
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
/* Function Name | Dcm_Dsp_SID01_MakeNormalPidData                          */
/* Description   | Make Normal PID Data                                     */
/* Preconditions | None                                                     */
/* Parameters    | [IN/OUT] ptMsgContext_temp     : Msg Context             */
/*               | [IN] u1ReqPid                  : Request PID             */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_SID01_READ_DATA_NONE : Read Data None          */
/*               |   DCM_DSP_SID01_READ_DATA_OK   : Read Data OK            */
/*               |   DCM_DSP_SID01_READ_OVER_FLOW : Read Over Flow          */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( uint8, DCM_CODE ) Dcm_Dsp_SID01_MakeNormalPidData
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext_temp,
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1ReqPid
)
{
    Std_ReturnType                                                        u1_Result;
    uint8                                                                 u1_GetPidDataResult;
    Dcm_MsgLenType                                                        u4_ResDataLen;
    uint8                                                                 u1_PidDataInfoIndex;
    uint16                                                                u2_PidPosOffset;
    uint8                                                                 u1_PidSize;
    Dcm_MsgLenType                                                        u4_PidBufIndex;
    P2CONST(AB_83_ConstV Dcm_Dsp_PidDataType, AUTOMATIC, DCM_APPL_CONST ) pt_PidDataPtr;

    u1_GetPidDataResult = DCM_DSP_SID01_READ_DATA_NONE;
    u4_ResDataLen = ptMsgContext_temp->resDataLen;

    /* Get Normal PID Data Index */
    u1_Result = Dcm_Dsp_SID01_GetPidDataInfoIdx( u1ReqPid, &u1_PidDataInfoIndex );
    if( u1_Result == (Std_ReturnType)E_OK )
    {
        u1_PidSize = DcmDspPidDataInfo[u1_PidDataInfoIndex].u1DcmDspPidSize;
        /* Buffer Over Flow Check */
        if( ( u4_ResDataLen + DCM_DSP_SID01_PID_LEN + (Dcm_MsgLenType)u1_PidSize ) <= ptMsgContext_temp->resMaxDataLen )    /* no wrap around */
        {
            pt_PidDataPtr = DcmDspPidDataInfo[u1_PidDataInfoIndex].ptPidData;

            /* Get Normal PID Data */
            /* Note : It is a premise that parameter DcmDspPidDataSize and DcmDspPidDataPos are multiples of 8. */
            if( pt_PidDataPtr->ptDcmDspPidDataReadFnc != NULL_PTR )
            {
                /* Initialize Reaponse Data */
                for( u4_PidBufIndex = (Dcm_MsgLenType)0U; u4_PidBufIndex < ( (Dcm_MsgLenType)u1_PidSize + DCM_DSP_SID01_PID_LEN ); u4_PidBufIndex++ )   /* no wrap around */
                {
                    ptMsgContext_temp->resData[u4_ResDataLen + u4_PidBufIndex] = (Dcm_MsgItemType)0x00U;    /* no wrap around */
                }

                /* Set PIDIdentifier */
                ptMsgContext_temp->resData[u4_ResDataLen] = u1ReqPid;
                u4_ResDataLen += DCM_DSP_SID01_PID_LEN; /* no wrap around */

                u2_PidPosOffset = (uint16)( pt_PidDataPtr->u2DcmDspPidDataPos >> DCM_DSP_SID01_BITSHIFT_3 );
#ifndef JGXSTACK
                /* Return value always E_OK */
                (void)pt_PidDataPtr->ptDcmDspPidDataReadFnc( &ptMsgContext_temp->resData[u4_ResDataLen + u2_PidPosOffset] );    /* no wrap around */
#else  /* JGXSTACK */
                /* user-defined */
#endif /* JGXSTACK */
                ptMsgContext_temp->resDataLen += ( DCM_DSP_SID01_PID_LEN + (Dcm_MsgLenType)u1_PidSize );    /* no wrap around */
                u1_GetPidDataResult = DCM_DSP_SID01_READ_DATA_OK;
            }
        }
        else
        {
            u1_GetPidDataResult = DCM_DSP_SID01_READ_OVER_FLOW;
        }
    }

    return u1_GetPidDataResult;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID01_MakeSupPidData                             */
/* Description   | Make Support PID Data                                    */
/* Preconditions | None                                                     */
/* Parameters    | [IN/OUT] ptMsgContext_temp     : Msg Context             */
/*               | [IN] u1ReqPid                  : Request PID             */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_SID01_READ_DATA_NONE : Read Data None          */
/*               |   DCM_DSP_SID01_READ_DATA_OK   : Read Data OK            */
/*               |   DCM_DSP_SID01_READ_OVER_FLOW : Read Over Flow          */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( uint8, DCM_CODE ) Dcm_Dsp_SID01_MakeSupPidData
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext_temp,
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1ReqPid
)
{
    Dcm_MsgLenType u4_ResDataLen;
    uint8          u1_GetPidDataResult;
    uint8          u1_PidTableId;
    uint32         u4_SupportPidTable;
    uint8          u1_SupPidNumber;

    u4_ResDataLen = ptMsgContext_temp->resDataLen;
    u1_SupPidNumber = Dcm_Dsp_SID01_u1AvailablePidNumber;
    u1_GetPidDataResult = DCM_DSP_SID01_READ_DATA_NONE;

    /* Buffer Over Flow Check */
    if( ( u4_ResDataLen + DCM_DSP_SID01_PID_LEN + DCM_DSP_SID01_SUPPID_LEN ) <= ptMsgContext_temp->resMaxDataLen )  /* no wrap around */
    {
        /* Get Support PID Data */
        /* Calculate SupportPidTable Index from Request PID */
        u1_PidTableId = (uint8)( u1ReqPid >> DCM_DSP_SID01_BITSHIFT_5 );
        u4_SupportPidTable = Dcm_Dsp_SID01_u4AvailablePidTable[u1_PidTableId];
        if( u1_PidTableId < u1_SupPidNumber )
        {
            ptMsgContext_temp->resData[u4_ResDataLen] = u1ReqPid;
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID01_PID_LEN] = /* no wrap around */
                (Dcm_MsgItemType)( u4_SupportPidTable >> DCM_DSP_SID01_BITSHIFT_24 );
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID01_PID_LEN + DCM_DSP_SID01_RES_DATA_POS_1] =  /* no wrap around */
                (Dcm_MsgItemType)( u4_SupportPidTable >> DCM_DSP_SID01_BITSHIFT_16 );
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID01_PID_LEN + DCM_DSP_SID01_RES_DATA_POS_2] =  /* no wrap around */
                (Dcm_MsgItemType)( u4_SupportPidTable >> DCM_DSP_SID01_BITSHIFT_8 );
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID01_PID_LEN + DCM_DSP_SID01_RES_DATA_POS_3] =  /* no wrap around */
                (Dcm_MsgItemType)u4_SupportPidTable;
            ptMsgContext_temp->resDataLen += DCM_DSP_SID01_PID_LEN + DCM_DSP_SID01_SUPPID_LEN;  /* no wrap around */
            u1_GetPidDataResult = DCM_DSP_SID01_READ_DATA_OK;
        }
    }
    else
    {
        u1_GetPidDataResult = DCM_DSP_SID01_READ_OVER_FLOW;
    }

    return u1_GetPidDataResult;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID01_GetPidDataInfoIdx                          */
/* Description   | Get PID DataInfo Index                                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1ReqPid             : Request PID                  */
/*               | [OUT]ptPidDataInfoIndex   : PID DataInfo Index           */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_NOT_OK                : Get InfoType Table Index NG  */
/*               |   E_OK                    : Get InfoType Table Index OK  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID01_GetPidDataInfoIdx
(
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1ReqPid,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptPidDataInfoIndex
)
{
    Std_ReturnType                                                             u1_Result;
    uint8                                                                      u1_PidDataInfoIndex;
    uint8                                                                      u1_PidNumber;

    u1_Result = (Std_ReturnType)E_NOT_OK;
    u1_PidNumber = Dcm_P_SID01_u1PidNumber;

    for( u1_PidDataInfoIndex = (uint8)0U; u1_PidDataInfoIndex < u1_PidNumber; u1_PidDataInfoIndex++ )
    {
        if( u1ReqPid == (Dcm_MsgItemType)DcmDspPidDataInfo[u1_PidDataInfoIndex].u1DcmDspPidIdentifier )
        {
            u1_Result = (Std_ReturnType)E_OK;
            *ptPidDataInfoIndex = u1_PidDataInfoIndex;
            break;
        }
    }

    return u1_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID01_GenerateAvailPidTable                      */
/* Description   | Generate Available Table                                 */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID01_GenerateAvailPidTable
(
    void
)
{
    uint32                      u4_SupportedList;
    uint8                       u1_SupportedPidNumber;
    uint8                       u1_SupportedPid;
    uint8                       u1_LoopPidTableNum;
    boolean                     b_CalibUse;

    u1_SupportedPidNumber = Dcm_P_SID01_u1SupPidNumber;
    Dcm_Dsp_SID01_u1AvailablePidNumber = (uint8)0U;

    for( u1_LoopPidTableNum = (uint8)0U; u1_LoopPidTableNum < u1_SupportedPidNumber; u1_LoopPidTableNum++ )
    {
        u1_SupportedPid = (uint8)( DCM_DSP_SID01_DIFF2NEXT_SUP_PID * u1_LoopPidTableNum );
        b_CalibUse  = (boolean)FALSE;
        u4_SupportedList = DCM_DSP_SID01_SUPPORT_NONE;

        Dcm_GetAvailablePIDForSID01( u1_SupportedPid, &b_CalibUse, &u4_SupportedList );
        if( b_CalibUse == (boolean)TRUE )
        {
            Dcm_Dsp_SID01_u4AvailablePidTable[u1_LoopPidTableNum] = (uint32)( DcmDspSupportPidTableForSid01[u1_LoopPidTableNum] & u4_SupportedList );
        }
        else
        {
            Dcm_Dsp_SID01_u4AvailablePidTable[u1_LoopPidTableNum] = (uint32)( DcmDspSupportPidTableForSid01[u1_LoopPidTableNum] );
        }

        if( Dcm_Dsp_SID01_u4AvailablePidTable[u1_LoopPidTableNum] != DCM_DSP_SID01_SUPPORT_NONE )
        {
            Dcm_Dsp_SID01_u1AvailablePidNumber = (uint8)(Dcm_Dsp_SID01_u1AvailablePidNumber + (uint8)1U);
        }
    }

    return;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID01 == STD_ON */
#endif /* DCM_OBDTYPE_TYPE_OBD */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2018-12-25                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
