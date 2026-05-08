/* Dcm_Dsp_SID08_c(v5-0-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID08/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

#if ( DCM_OBDTYPE_TYPE_MOBD == STD_ON )
#if ( DCM_SUPPORT_SID08 == STD_ON )

#include "../../Dsp/cfg/Dcm_Dsp_SID08_Cfg.h"
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Dsp_SID08.h>
#include <Dcm/Dcm_Dsp_Main.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SID08_REQ_DATA_LEN_MIN  ( (Dcm_MsgLenType)1U )
#define DCM_DSP_SID08_REQ_DATA_LEN_MAX  ( (Dcm_MsgLenType)6U )

#define DCM_DSP_SID08_TID_MASK          ( (uint8)0x1FU )

#define DCM_DSP_SID08_TIDKIND_SUP       ( (uint8)0x00U )
#define DCM_DSP_SID08_TIDKIND_NORMAL    ( (uint8)0x01U )

#define DCM_DSP_SID08_TID_LEN           ( (Dcm_MsgLenType)1U )
#define DCM_DSP_SID08_SUPTID_LEN        ( (Dcm_MsgLenType)4U )

#define DCM_DSP_SID08_READ_DATA_NONE    ( (uint8)0x00U )
#define DCM_DSP_SID08_READ_DATA_OK      ( (uint8)0x01U )
#define DCM_DSP_SID08_READ_OVER_FLOW    ( (uint8)0x02U )

#define DCM_DSP_SID08_SUPTID_BIT        ( (uint32)0x00000001U )
#define DCM_DSP_SID08_SUPTID_BIT_TOP    ( (uint8)31U )
#define DCM_DSP_SID08_SUPTID_OFS        ( (uint8)1U )

#define DCM_DSP_SID08_BITSHIFT_5        ( (uint8)5U )
#define DCM_DSP_SID08_BITSHIFT_8        ( (uint8)8U )
#define DCM_DSP_SID08_BITSHIFT_16       ( (uint8)16U )
#define DCM_DSP_SID08_BITSHIFT_24       ( (uint8)24U )

#define DCM_DSP_SID08_RES_DATA_POS_0    ( (uint8)0U )
#define DCM_DSP_SID08_RES_DATA_POS_1    ( (uint8)1U )
#define DCM_DSP_SID08_RES_DATA_POS_2    ( (uint8)2U )
#define DCM_DSP_SID08_RES_DATA_POS_3    ( (uint8)3U )

#define DCM_DSP_SID08_REQ_DATA_POS_0    ( (uint8)0U )
#define DCM_DSP_SID08_REQ_DATA_POS_1    ( (uint8)1U )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID08_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID08_CancelProc
(
    void
);
static FUNC ( uint8, DCM_CODE ) Dcm_Dsp_SID08_CheckTidKind
(
    const Dcm_MsgItemType u1ReqTid
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID08_CheckTidSupport
(
    const Dcm_MsgItemType u1ReqTid
);
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID08_MakeNormalTidData
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext_temp,
    const Dcm_MsgItemType u1ReqTid,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);
static FUNC ( uint8, DCM_CODE ) Dcm_Dsp_SID08_MakeSupTidData
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext_temp,
    const Dcm_MsgItemType u1ReqTid
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID08_GetTidInfoIdx
(
    const Dcm_MsgItemType u1ReqTid,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptTidInfoIndex
);

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

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

/****************************************************************************/
/* Function Name | Dcm_SID08                                                */
/* Description   | SID08 request processing                                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus        : Operation state                   */
/*               | [IN] pMsgContext     : Message Context                   */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK               : Processing normal                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID08 /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = (Std_ReturnType)E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID08_InitialProc( pMsgContext );
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        Dcm_Dsp_SID08_CancelProc();
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
/* Function Name | Dcm_Dsp_SID08_InitialProc                                */
/* Description   | Initial process of SID08 request                         */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext    : Message Context                   */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK               : Processing normal                 */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID08_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Std_ReturnType               u1_CheckResult;
    Dcm_NegativeResponseCodeType u1_ErrorCode;
    uint8                        u1_MakeResDataResult;
    uint8                        u1_ReqTidKind;
    uint8                        u1_ReqTidNum;
    Dcm_MsgItemType              u1_ReqData;
    Dcm_MsgContextType           st_MsgContext_temp;

    u1_ErrorCode = (Dcm_NegativeResponseCodeType)0x00U;
    st_MsgContext_temp = *ptMsgContext;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    /* Request Data Length Check */
    if( ( st_MsgContext_temp.reqDataLen >= DCM_DSP_SID08_REQ_DATA_LEN_MIN ) &&
        ( st_MsgContext_temp.reqDataLen <= DCM_DSP_SID08_REQ_DATA_LEN_MAX ) )
    {
        /* Initialize Reaponse Data Length */
        st_MsgContext_temp.resDataLen = (Dcm_MsgLenType)0U;

        /* Get Top TID Kind */
        u1_ReqData = st_MsgContext_temp.reqData[DCM_DSP_SID08_REQ_DATA_POS_0];
        u1_ReqTidKind = Dcm_Dsp_SID08_CheckTidKind( u1_ReqData );

        if( u1_ReqTidKind == DCM_DSP_SID08_TIDKIND_SUP )
        {
            /* Process for Support TID */
            for( u1_ReqTidNum = (uint8)0U; u1_ReqTidNum < (uint8)st_MsgContext_temp.reqDataLen; u1_ReqTidNum++ )
            {
                u1_ReqData = st_MsgContext_temp.reqData[u1_ReqTidNum];
                u1_ReqTidKind = Dcm_Dsp_SID08_CheckTidKind( u1_ReqData );
                /* Mixed TID Check */
                if( u1_ReqTidKind == DCM_DSP_SID08_TIDKIND_SUP )
                {
                    /* TID Support Check */
                    u1_CheckResult = Dcm_Dsp_SID08_CheckTidSupport( u1_ReqData );
                    if( u1_CheckResult == (Std_ReturnType)E_OK )
                    {
                        /* Make Response data for Support TID */
                        u1_MakeResDataResult = Dcm_Dsp_SID08_MakeSupTidData( &st_MsgContext_temp, u1_ReqData );
                        if( u1_MakeResDataResult == DCM_DSP_SID08_READ_OVER_FLOW )
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
            /* Process for Normal TID */
            /* TID Support Check */
            u1_CheckResult = Dcm_Dsp_SID08_CheckTidSupport( u1_ReqData );
            if( u1_CheckResult == (Std_ReturnType)E_OK )
            {
                /* Make Response data for Normal TID */
                Dcm_Dsp_SID08_MakeNormalTidData( &st_MsgContext_temp, u1_ReqData, &u1_ErrorCode );
            }
            else
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

    return E_OK;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID08_CancelProc                                 */
/* Description   | Cancel process of SID08 request                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID08_CancelProc
(
    void
)
{
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID08_CheckTidKind                               */
/* Description   | Check TID Kind SupportTID or NormalTID                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1ReqTid                  : Request TID             */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_SID08_TIDKIND_SUP    : Support TID             */
/*               |   DCM_DSP_SID08_TIDKIND_NORMAL : Normal TID              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( uint8, DCM_CODE ) Dcm_Dsp_SID08_CheckTidKind
(
    const Dcm_MsgItemType u1ReqTid
)
{
    uint8 u1_TidKind;

    u1_TidKind = DCM_DSP_SID08_TIDKIND_NORMAL;

    if( (uint8)( u1ReqTid & DCM_DSP_SID08_TID_MASK ) == DCM_DSP_SID08_TIDKIND_SUP )
    {
        u1_TidKind = DCM_DSP_SID08_TIDKIND_SUP;
    }

    return u1_TidKind;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID08_CheckTidSupport                            */
/* Description   | Check TID Support                                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1ReqTid           : Request TID                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                  : TID Supported                  */
/*               |   E_NOT_OK              : TID Not Supported              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID08_CheckTidSupport
(
    const Dcm_MsgItemType u1ReqTid
)
{
    Std_ReturnType u1_CheckResult;
    uint8          u1_SupportTidTableIndex;
    uint8          u1_SupportBitShiftNum;
    uint32         u4_TidSupportBitMask;
    uint32         u4_TidSupportBit;
    uint8          u1_SupTidNumber;

    u1_CheckResult = (Std_ReturnType)E_NOT_OK;
    u1_SupTidNumber = Dcm_P_SID08_u1SupTidNumber;

    if( u1ReqTid != (Dcm_MsgItemType)0x00U )
    {
        /* Check TID Support From BIT of Support TID Table */
        u1_SupportTidTableIndex = (uint8)( (uint8)( u1ReqTid - DCM_DSP_SID08_SUPTID_OFS ) >> DCM_DSP_SID08_BITSHIFT_5 );
        if( u1_SupportTidTableIndex < u1_SupTidNumber )
        {
            u1_SupportBitShiftNum = DCM_DSP_SID08_SUPTID_BIT_TOP - (uint8)( (uint8)( u1ReqTid - DCM_DSP_SID08_SUPTID_OFS ) & DCM_DSP_SID08_TID_MASK );
            u4_TidSupportBitMask = (uint32)( DCM_DSP_SID08_SUPTID_BIT << u1_SupportBitShiftNum );
            u4_TidSupportBit = (uint32)( u4_TidSupportBitMask & DcmDspSupportTidTableForSid08[u1_SupportTidTableIndex] );
            if( u4_TidSupportBit != (uint32)0x00000000U )
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
/* Function Name | Dcm_Dsp_SID08_MakeNormalTidData                          */
/* Description   | Make Normal TID Data                                     */
/* Preconditions | None                                                     */
/* Parameters    | [IN/OUT] ptMsgContext_temp     : Msg Context             */
/*               | [IN] u1ReqTid                  : Request TID             */
/*               | [OUT] ptErrorCode              : Error code(NRC)         */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID08_MakeNormalTidData
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext_temp,
    const Dcm_MsgItemType u1ReqTid,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Dcm_MsgLenType                                                        u4_ReqDataLen;
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA)                              pt_InBuffData;
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)                                pt_OutBuffData;
    Std_ReturnType                                                        u1_Result;
    uint8                                                                 u1_TidInfoIndex;
    uint8                                                                 u1_InBuffSize;
    uint8                                                                 u1_OutBuffSize;

    u4_ReqDataLen = ptMsgContext_temp->reqDataLen;

    /* Get Normal TID Data Index */
    u1_Result = Dcm_Dsp_SID08_GetTidInfoIdx( u1ReqTid, &u1_TidInfoIndex );
    if( u1_Result == (Std_ReturnType)E_OK )
    {
        u1_InBuffSize = DcmDspTidInfo[u1_TidInfoIndex].u1DcmDspRequestControlInBufferSize;
        /* InBuffer size Check */
        if( u4_ReqDataLen  == ( DCM_DSP_SID08_TID_LEN + (Dcm_MsgLenType)u1_InBuffSize ) )   /* no wrap around */
        {
            ptMsgContext_temp->resData[DCM_DSP_SID08_RES_DATA_POS_0] = u1ReqTid;
            pt_OutBuffData = &ptMsgContext_temp->resData[DCM_DSP_SID08_RES_DATA_POS_1];
            pt_InBuffData  = &ptMsgContext_temp->reqData[DCM_DSP_SID08_REQ_DATA_POS_1];
#ifndef JGXSTACK
            /* Call Xxx_RequestControl function */
            u1_Result = DcmDspTidInfo[u1_TidInfoIndex].ptDcmDspTidReqControlFnc( pt_OutBuffData, pt_InBuffData );
#else  /* JGXSTACK */
            /* user-defined */
#endif /* JGXSTACK */
            if( u1_Result == (Std_ReturnType)E_OK )
            {
                u1_OutBuffSize = DcmDspTidInfo[u1_TidInfoIndex].u1DcmDspRequestControlOutBufferSize;
                ptMsgContext_temp->resDataLen += ( DCM_DSP_SID08_TID_LEN + (Dcm_MsgLenType)u1_OutBuffSize );    /* no wrap around */
            }
            else
            {
                /* NRC0x22 */
                *ptErrorCode = DCM_E_CONDITIONSNOTCORRECT;
            }
        }
        else
        {
            /* NRC0x13 */
            *ptErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
    }
    else
    {
        /* NRC0x31 */
        *ptErrorCode = DCM_E_REQUESTOUTOFRANGE;
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID08_MakeSupTidData                             */
/* Description   | Make Support TID Data                                    */
/* Preconditions | None                                                     */
/* Parameters    | [IN/OUT] ptMsgContext_temp     : Msg Context             */
/*               | [IN] u1ReqTid                  : Request TID             */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_SID08_READ_DATA_NONE : Read Data None          */
/*               |   DCM_DSP_SID08_READ_DATA_OK   : Read Data OK            */
/*               |   DCM_DSP_SID08_READ_OVER_FLOW : Read Over Flow          */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( uint8, DCM_CODE ) Dcm_Dsp_SID08_MakeSupTidData
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext_temp,
    const Dcm_MsgItemType u1ReqTid
)
{
    Dcm_MsgLenType u4_ResDataLen;
    uint8          u1_GetTidDataResult;
    uint8          u1_TidTableId;
    uint32         u4_SupportTidTable;
    uint8          u1_SupTidNumber;

    u4_ResDataLen = ptMsgContext_temp->resDataLen;
    u1_SupTidNumber = Dcm_P_SID08_u1SupTidNumber;
    u1_GetTidDataResult = DCM_DSP_SID08_READ_DATA_NONE;

    /* Buffer Over Flow Check */
    if( ( u4_ResDataLen + DCM_DSP_SID08_TID_LEN + DCM_DSP_SID08_SUPTID_LEN ) <= ptMsgContext_temp->resMaxDataLen )  /* no wrap around */
    {
        /* Get Support TID Data */
        /* Calculate SupportTidTable Index from Request TID */
        u1_TidTableId = (uint8)( u1ReqTid >> DCM_DSP_SID08_BITSHIFT_5 );
        if( u1_TidTableId < u1_SupTidNumber )
        {
            u4_SupportTidTable = DcmDspSupportTidTableForSid08[u1_TidTableId];
            ptMsgContext_temp->resData[u4_ResDataLen] = u1ReqTid;
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID08_TID_LEN] = /* no wrap around */
                (Dcm_MsgItemType)( u4_SupportTidTable >> DCM_DSP_SID08_BITSHIFT_24 );
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID08_TID_LEN + DCM_DSP_SID08_RES_DATA_POS_1] =  /* no wrap around */
                (Dcm_MsgItemType)( u4_SupportTidTable >> DCM_DSP_SID08_BITSHIFT_16 );
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID08_TID_LEN + DCM_DSP_SID08_RES_DATA_POS_2] =  /* no wrap around */
                (Dcm_MsgItemType)( u4_SupportTidTable >> DCM_DSP_SID08_BITSHIFT_8 );
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID08_TID_LEN + DCM_DSP_SID08_RES_DATA_POS_3] =  /* no wrap around */
                (Dcm_MsgItemType)u4_SupportTidTable;
            ptMsgContext_temp->resDataLen += DCM_DSP_SID08_TID_LEN + DCM_DSP_SID08_SUPTID_LEN;  /* no wrap around */
            u1_GetTidDataResult = DCM_DSP_SID08_READ_DATA_OK;
        }
    }
    else
    {
        u1_GetTidDataResult = DCM_DSP_SID08_READ_OVER_FLOW;
    }

    return u1_GetTidDataResult;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID08_GetTidInfoIdx                              */
/* Description   | Get TID DataInfo Index                                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1ReqTid             : Request TID                  */
/*               | [OUT]ptTidInfoIndex       : TID Info Index               */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_NOT_OK                : Get InfoType Table Index NG  */
/*               |   E_OK                    : Get InfoType Table Index OK  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID08_GetTidInfoIdx
(
    const Dcm_MsgItemType u1ReqTid,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptTidInfoIndex
)
{
    Std_ReturnType                                                             u1_Result;
    uint8                                                                      u1_TidInfoIndex;
    uint8                                                                      u1_TidNumber;

    u1_Result = (Std_ReturnType)E_NOT_OK;
    u1_TidNumber = Dcm_P_SID08_u1TidNumber;

    for( u1_TidInfoIndex = (uint8)0U; u1_TidInfoIndex < u1_TidNumber; u1_TidInfoIndex++ )
    {
        if( u1ReqTid == (Dcm_MsgItemType)DcmDspTidInfo[u1_TidInfoIndex].u1DcmDspTidIdentifier )
        {
            u1_Result = (Std_ReturnType)E_OK;
            *ptTidInfoIndex = u1_TidInfoIndex;
            break;
        }
    }

    return u1_Result;
}


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID08 == STD_ON */
#endif /* DCM_OBDTYPE_TYPE_MOBD */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
