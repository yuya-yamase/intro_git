/* Dcm_Dsp_SID31_OBD_c(v5-5-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID31_OBD/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <Dcm.h>

#if( DCM_OBD_RANGE_RID_USE == STD_ON )

#include <Dcm/Dcm_Dsp_SID31_OBD.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SID31_OBD_SUBFUNC_LEN       ((Dcm_MsgLenType)1U)
#define DCM_DSP_SID31_OBD_RID_LEN           ((Dcm_MsgLenType)2U)
#define DCM_DSP_SID31_OBD_ROUTINEINFO_LEN   ((Dcm_MsgLenType)1U)
#define DCM_DSP_SID31_OBD_SUPDATA_LEN       ((Dcm_MsgLenType)4U)

#define DCM_DSP_SID31_OBD_SUBFUNC01         ((Dcm_MsgItemType)0x01U)
#define DCM_DSP_SID31_OBD_RID_HI_E0         ((Dcm_MsgItemType)0xE0U)

#define DCM_DSP_SID31_OBD_SUBFUNC_POS       ((uint8)0U)
#define DCM_DSP_SID31_OBD_RID_HI_POS        ((uint8)1U)
#define DCM_DSP_SID31_OBD_RID_LO_POS        ((uint8)2U)
#define DCM_DSP_SID31_OBD_ROUTINEINFO_POS   ((uint8)3U)
#define DCM_DSP_SID31_OBD_REQ_INDATA_POS    ((uint8)3U)

#define DCM_DSP_SID31_OBD_SUPRID_BIT        ((uint32)0x00000001U)
#define DCM_DSP_SID31_OBD_SUPRID_BIT_TOP    ((uint8)31U)
#define DCM_DSP_SID31_OBD_SUPRID_OFS        ((uint8)1U)

#define DCM_DSP_SID31_OBD_RID_MASK          ((uint8)0x1FU)
#define DCM_DSP_SID31_OBD_RIDKIND_SUP       ((uint8)0x00U)
#define DCM_DSP_SID31_OBD_RIDKIND_NORMAL    ((uint8)0x01U)

#define DCM_DSP_SID31_OBD_BITSHIFT_5        ((uint8)5U)
#define DCM_DSP_SID31_OBD_BITSHIFT_8        ((uint8)8U)
#define DCM_DSP_SID31_OBD_BITSHIFT_16       ((uint8)16U)
#define DCM_DSP_SID31_OBD_BITSHIFT_24       ((uint8)24U)

#define DCM_DSP_SID31_OBD_RES_DATA_POS_1    ((uint8)1U)
#define DCM_DSP_SID31_OBD_RES_DATA_POS_2    ((uint8)2U)
#define DCM_DSP_SID31_OBD_RES_DATA_POS_3    ((uint8)3U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_OBD_CheckRidSupport
(
    const Dcm_MsgItemType u1ReqRid
);
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_SID31_OBD_CheckRidKind
(
    const Dcm_MsgItemType u1ReqRid
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_OBD_MakeSupRidData
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const Dcm_MsgItemType u1ReqRid,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_OBD_MakeNormalRidData
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const Dcm_MsgItemType u1ReqRid,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID31_OBD_GetRidInfoIdx
(
    const Dcm_MsgItemType u1ReqRid,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptRidInfoIndex
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
/* Function Name | Dcm_Dsp_SID31_OBD_StartRoutineProc                       */
/* Description   | StartRoutine Process of SID31_OBD request                */
/* Preconditions | None                                                     */
/* Parameters    | [IN/OUT] ptMsgContext : Message Context                  */
/*               | [OUT]ptErrorCode : Negative Response Code                */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : Request was successful                     */
/*               |        E_NOT_OK : Request was not successful             */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_OBD_StartRoutineProc
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    uint8                        u1_ReqRidKind;
    Dcm_MsgItemType              u1_ReqRidLo;
    Std_ReturnType               u1_RetChkSup;
    Std_ReturnType               u1_RetVal;

    u1_RetVal          = (Std_ReturnType)E_NOT_OK;
    u1_ReqRidLo        = ptMsgContext->reqData[DCM_DSP_SID31_OBD_RID_LO_POS];
    *ptErrorCode       = DCM_E_GENERALREJECT; /* NRC0x10 */

    /* RID Support Check */
    u1_RetChkSup = Dcm_Dsp_SID31_OBD_CheckRidSupport( u1_ReqRidLo );
    if( u1_RetChkSup == (Std_ReturnType)E_OK )
    {
        /* Initialize Reaponse Data Length */
        ptMsgContext->resDataLen = (Dcm_MsgLenType)0U;

        u1_ReqRidKind = Dcm_Dsp_SID31_OBD_CheckRidKind( u1_ReqRidLo );
        if( u1_ReqRidKind == DCM_DSP_SID31_OBD_RIDKIND_SUP )
        {
            /* Make Response data of Support RID */
            u1_RetVal = Dcm_Dsp_SID31_OBD_MakeSupRidData( ptMsgContext, u1_ReqRidLo, ptErrorCode );
        }
        else
        {
            /* Make Response data for Normal RID */
            u1_RetVal = Dcm_Dsp_SID31_OBD_MakeNormalRidData( ptMsgContext, u1_ReqRidLo, ptErrorCode );
        }
    }
    else
    {
        /* NRC0x31 */
        *ptErrorCode = DCM_E_REQUESTOUTOFRANGE;
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_OBD_CheckRidSupportProc                    */
/* Description   | Check RID Support                                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN/OUT] ptMsgContext : Message Context                  */
/* Return Value  | Std_ReturnType                                           */
/*               |        E_OK : RID Supported                              */
/*               |        E_NOT_OK : RID Not Supported                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_OBD_CheckRidSupportProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Dcm_MsgItemType              u1_ReqRidLo;
    Std_ReturnType               u1_RetVal;

    u1_ReqRidLo        = ptMsgContext->reqData[DCM_DSP_SID31_OBD_RID_LO_POS];

    /* RID Support Check */
    u1_RetVal = Dcm_Dsp_SID31_OBD_CheckRidSupport( u1_ReqRidLo );

    return u1_RetVal;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_OBD_CheckRidSupport                        */
/* Description   | Check RID Support                                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1ReqRid           : Request RID                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                  : RID Supported                  */
/*               |   E_NOT_OK              : RID Not Supported              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_OBD_CheckRidSupport
(
    const Dcm_MsgItemType u1ReqRid
)
{
    uint32         u4_RidSupportBitMask;
    uint32         u4_RidSupportBit;
    uint8          u1_SupportRidTableIndex;
    uint8          u1_SupportBitShiftNum;
    uint8          u1_SupRidNumber;
    Std_ReturnType u1_RetVal;

    u1_RetVal = (Std_ReturnType)E_NOT_OK;
    u1_SupRidNumber = Dcm_Dsp_SID31_OBD_u1SupRidNumber;

    if( u1ReqRid != (Dcm_MsgItemType)0x00U )
    {
        /* Check RID Support From BIT of Support RID Table */
        u1_SupportRidTableIndex = (uint8)( (uint8)( u1ReqRid - DCM_DSP_SID31_OBD_SUPRID_OFS ) >> DCM_DSP_SID31_OBD_BITSHIFT_5 );
        if( u1_SupportRidTableIndex < u1_SupRidNumber )
        {
            u1_SupportBitShiftNum = DCM_DSP_SID31_OBD_SUPRID_BIT_TOP - (uint8)( (uint8)( u1ReqRid - DCM_DSP_SID31_OBD_SUPRID_OFS ) & DCM_DSP_SID31_OBD_RID_MASK );
            u4_RidSupportBitMask = (uint32)( DCM_DSP_SID31_OBD_SUPRID_BIT << u1_SupportBitShiftNum );
            u4_RidSupportBit = (uint32)( u4_RidSupportBitMask & Dcm_Dsp_SID31_OBD_SupportRidTbl[u1_SupportRidTableIndex] );
            if( u4_RidSupportBit != (uint32)0x00000000U )
            {
                u1_RetVal = (Std_ReturnType)E_OK;
            }
        }
    }
    else
    {
        u1_RetVal = (Std_ReturnType)E_OK;
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_OBD_CheckRidKind                           */
/* Description   | Check RID Kind SupportRID or NormalRID                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1ReqRid                  : Request RID             */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_SID31_OBD_RIDKIND_SUP    : Support RID         */
/*               |   DCM_DSP_SID31_OBD_RIDKIND_NORMAL : Normal RID          */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_SID31_OBD_CheckRidKind
(
    const Dcm_MsgItemType u1ReqRid
)
{
    uint8 u1_RidKind;

    u1_RidKind = DCM_DSP_SID31_OBD_RIDKIND_NORMAL;

    if( (uint8)( u1ReqRid & DCM_DSP_SID31_OBD_RID_MASK ) == DCM_DSP_SID31_OBD_RIDKIND_SUP )
    {
        u1_RidKind = DCM_DSP_SID31_OBD_RIDKIND_SUP;
    }

    return u1_RidKind;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_OBD_MakeSupRidData                         */
/* Description   | Make Support RID Data                                    */
/* Preconditions | None                                                     */
/* Parameters    | [IN/OUT] ptMsgContext          : Msg Context             */
/*               | [IN] u1ReqRid                  : Request RID             */
/*               | [OUT]ptErrorCode : Negative Response Code                */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK          : Processing normal                      */
/*               |   E_NOT_OK      : Processing not normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_OBD_MakeSupRidData
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const Dcm_MsgItemType u1ReqRid,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    Dcm_MsgLenType u4_ChkReqDataLen;
    Dcm_MsgLenType u4_ChkResDataLen;
    Dcm_MsgLenType u4_ResDataLen;
    uint32         u4_RidSupData;
    uint8          u1_RidSupTblIdx;
    uint8          u1_SupRidNumber;
    Std_ReturnType u1_RetVal;
    boolean        b_RoutineInfoUsed;

    u1_RetVal = (Std_ReturnType)E_NOT_OK;
    u1_SupRidNumber = Dcm_Dsp_SID31_OBD_u1SupRidNumber;

    /* Check Request message length */
    u4_ChkReqDataLen = (Dcm_MsgLenType)( DCM_DSP_SID31_OBD_SUBFUNC_LEN + DCM_DSP_SID31_OBD_RID_LEN );
    if( ptMsgContext->reqDataLen == u4_ChkReqDataLen )
    {
        /* Check Response message length */
        b_RoutineInfoUsed = Dcm_Dsp_SID31_OBD_bRoutineInfoUsed;
        if( b_RoutineInfoUsed == (boolean)TRUE )
        {
            u4_ChkResDataLen = (Dcm_MsgLenType)( DCM_DSP_SID31_OBD_SUBFUNC_LEN + DCM_DSP_SID31_OBD_RID_LEN + DCM_DSP_SID31_OBD_ROUTINEINFO_LEN + DCM_DSP_SID31_OBD_SUPDATA_LEN );
        }
        else
        {
            u4_ChkResDataLen = (Dcm_MsgLenType)( DCM_DSP_SID31_OBD_SUBFUNC_LEN + DCM_DSP_SID31_OBD_RID_LEN + DCM_DSP_SID31_OBD_SUPDATA_LEN );
        }
        if( u4_ChkResDataLen <= ptMsgContext->resMaxDataLen )
        {
            /* Set Subfunction and RID in response data */
            ptMsgContext->resData[DCM_DSP_SID31_OBD_SUBFUNC_POS] = DCM_DSP_SID31_OBD_SUBFUNC01;
            ptMsgContext->resData[DCM_DSP_SID31_OBD_RID_HI_POS]  = DCM_DSP_SID31_OBD_RID_HI_E0;
            ptMsgContext->resData[DCM_DSP_SID31_OBD_RID_LO_POS]  = u1ReqRid;

            if( b_RoutineInfoUsed == (boolean)TRUE )
            {
                /* Set RoutineInfo in response data */
                ptMsgContext->resData[DCM_DSP_SID31_OBD_ROUTINEINFO_POS] = (Dcm_MsgItemType)Dcm_Dsp_SID31_OBD_u1RoutineInfo;
                u4_ResDataLen = (Dcm_MsgLenType)( DCM_DSP_SID31_OBD_SUBFUNC_LEN + DCM_DSP_SID31_OBD_RID_LEN + DCM_DSP_SID31_OBD_ROUTINEINFO_LEN );
            }
            else
            {
                u4_ResDataLen = (Dcm_MsgLenType)( DCM_DSP_SID31_OBD_SUBFUNC_LEN + DCM_DSP_SID31_OBD_RID_LEN );
            }

            /* Calculate SupportRidTable Index from Request RID */
            u1_RidSupTblIdx = (uint8)( u1ReqRid >> DCM_DSP_SID31_OBD_BITSHIFT_5 );
            if( u1_RidSupTblIdx < u1_SupRidNumber )
            {
                u4_RidSupData = Dcm_Dsp_SID31_OBD_SupportRidTbl[u1_RidSupTblIdx];
                ptMsgContext->resData[u4_ResDataLen] = (Dcm_MsgItemType)( u4_RidSupData >> DCM_DSP_SID31_OBD_BITSHIFT_24 );
                ptMsgContext->resData[u4_ResDataLen + DCM_DSP_SID31_OBD_RES_DATA_POS_1] = (Dcm_MsgItemType)( u4_RidSupData >> DCM_DSP_SID31_OBD_BITSHIFT_16 ); /* no wrap around */
                ptMsgContext->resData[u4_ResDataLen + DCM_DSP_SID31_OBD_RES_DATA_POS_2] = (Dcm_MsgItemType)( u4_RidSupData >> DCM_DSP_SID31_OBD_BITSHIFT_8 );  /* no wrap around */
                ptMsgContext->resData[u4_ResDataLen + DCM_DSP_SID31_OBD_RES_DATA_POS_3] = (Dcm_MsgItemType)u4_RidSupData; /* no wrap around */
                ptMsgContext->resDataLen = u4_ChkResDataLen;
                u1_RetVal = (Std_ReturnType)E_OK;
            }
        }
        else
        {
            /* NRC0x14 */
            *ptErrorCode = DCM_E_RESPONSETOOLONG;
        }
    }
    else
    {
        /* NRC0x13 */
        *ptErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    return u1_RetVal;
}


/*****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_OBD_MakeNormalRidData                       */
/* Description   | Make Normal RID Data                                      */
/* Preconditions | None                                                      */
/* Parameters    | [IN/OUT] ptMsgContext          : Msg Context              */
/*               | [IN] u1ReqRid                  : Request RID              */
/*               | [OUT]ptErrorCode : Negative Response Code                 */
/* Return Value  | Std_ReturnType                                            */
/*               |   E_OK          : Processing normal                       */
/*               |   E_NOT_OK      : Processing not normal                   */
/* Notes         | None                                                      */
/*****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID31_OBD_MakeNormalRidData
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext,
    const Dcm_MsgItemType u1ReqRid,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode
)
{
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA)    pt_InBuffData;
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)      pt_OutBuffData;
    Dcm_MsgLenType                              u4_ChkReqDataLen;
    Dcm_MsgLenType                              u4_ChkResDataLen;
    Dcm_MsgLenType                              u4_ResDataLen;
    uint8                                       u1_RidInfoIndex;
    uint8                                       u1_InBuffSize;
    uint8                                       u1_OutBuffSize;
    Std_ReturnType                              u1_RetVal;
    Std_ReturnType                              u1_RetRidReqControl;
    boolean                                     b_RoutineInfoUsed;

    u1_RetVal = (Std_ReturnType)E_NOT_OK;

    /* Get RID Info Index */
    u1_RidInfoIndex = (uint8)0U;
    /* Since that u1ReqRid is in Dcm_Dsp_SID31_OBD_RidInfo[] is already checked, call Dcm_Dsp_SID31_OBD_GetRidInfoIdx() */
    Dcm_Dsp_SID31_OBD_GetRidInfoIdx( u1ReqRid, &u1_RidInfoIndex );

    /* Check Request message length */
    u1_InBuffSize = Dcm_Dsp_SID31_OBD_RidInfo[u1_RidInfoIndex].u1DcmDspRequestControlInBufferSize;
    u4_ChkReqDataLen = (Dcm_MsgLenType)( DCM_DSP_SID31_OBD_SUBFUNC_LEN + DCM_DSP_SID31_OBD_RID_LEN +(Dcm_MsgLenType)u1_InBuffSize ); /* no wrap around */
    if( ptMsgContext->reqDataLen == u4_ChkReqDataLen )
    {
        /* Check Response message length */
        u1_OutBuffSize = Dcm_Dsp_SID31_OBD_RidInfo[u1_RidInfoIndex].u1DcmDspRequestControlOutBufferSize;
        b_RoutineInfoUsed = Dcm_Dsp_SID31_OBD_bRoutineInfoUsed;
        if( b_RoutineInfoUsed == (boolean)TRUE )
        {
            u4_ChkResDataLen = (Dcm_MsgLenType)( DCM_DSP_SID31_OBD_SUBFUNC_LEN + DCM_DSP_SID31_OBD_RID_LEN + DCM_DSP_SID31_OBD_ROUTINEINFO_LEN + (Dcm_MsgLenType)u1_OutBuffSize ); /* no wrap around */
        }
        else
        {
            u4_ChkResDataLen = (Dcm_MsgLenType)( DCM_DSP_SID31_OBD_SUBFUNC_LEN + DCM_DSP_SID31_OBD_RID_LEN + (Dcm_MsgLenType)u1_OutBuffSize ); /* no wrap around */
        }
        if( u4_ChkResDataLen <= ptMsgContext->resMaxDataLen )
        {
            /* Set Subfunction and RID in response data */
            ptMsgContext->resData[DCM_DSP_SID31_OBD_SUBFUNC_POS] = DCM_DSP_SID31_OBD_SUBFUNC01;
            ptMsgContext->resData[DCM_DSP_SID31_OBD_RID_HI_POS]  = DCM_DSP_SID31_OBD_RID_HI_E0;
            ptMsgContext->resData[DCM_DSP_SID31_OBD_RID_LO_POS]  = u1ReqRid;

            if( b_RoutineInfoUsed == (boolean)TRUE )
            {
                /* Set RoutineInfo in response data */
                ptMsgContext->resData[DCM_DSP_SID31_OBD_ROUTINEINFO_POS] = (Dcm_MsgItemType)Dcm_Dsp_SID31_OBD_u1RoutineInfo;
                u4_ResDataLen = (Dcm_MsgLenType)( DCM_DSP_SID31_OBD_SUBFUNC_LEN + DCM_DSP_SID31_OBD_RID_LEN + DCM_DSP_SID31_OBD_ROUTINEINFO_LEN);
            }
            else
            {
                u4_ResDataLen = (Dcm_MsgLenType)( DCM_DSP_SID31_OBD_SUBFUNC_LEN + DCM_DSP_SID31_OBD_RID_LEN );
            }

            pt_InBuffData  = &ptMsgContext->reqData[DCM_DSP_SID31_OBD_REQ_INDATA_POS];
            pt_OutBuffData = &ptMsgContext->resData[u4_ResDataLen];
#ifndef JGXSTACK
            /* Call Xxx_RequestControl function */
            u1_RetRidReqControl = Dcm_Dsp_SID31_OBD_RidInfo[u1_RidInfoIndex].ptDcmDspRidReqControlFnc( pt_OutBuffData, pt_InBuffData );
#else  /* JGXSTACK */
            u1_RetRidReqControl = E_OK;
            /* user-defined */
#endif /* JGXSTACK */
            if( u1_RetRidReqControl == (Std_ReturnType)E_OK )
            {
                ptMsgContext->resDataLen = u4_ChkResDataLen;
                u1_RetVal = (Std_ReturnType)E_OK;
            }
            else if( u1_RetRidReqControl == (Std_ReturnType)DCM_E_SEQERROR )
            {
                /* NRC0x24 */
                *ptErrorCode = DCM_E_REQUESTSEQUENCEERROR;
            }
            else
            {
                /* NRC0x22 */
                *ptErrorCode = DCM_E_CONDITIONSNOTCORRECT;
            }
        }
        else
        {
            /* NRC0x14 */
            *ptErrorCode = DCM_E_RESPONSETOOLONG;
        }
    }
    else
    {
        /* NRC0x13 */
        *ptErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID31_OBD_GetRidInfoIdx                          */
/* Description   | Get RID Info Index                                       */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1ReqRid             : Request RID                  */
/*               | [OUT]ptRidInfoIndex       : RID Info Index               */
/* Return Value  | None                                                     */
/* Notes         | Only if Request RID is in Dcm_Dsp_SID31_OBD_RidInfo[]    */
/*               | should call this function                                */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID31_OBD_GetRidInfoIdx
(
    const Dcm_MsgItemType u1ReqRid,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptRidInfoIndex
)
{
    uint8             u1_RidInfoIndex;
    uint8             u1_RidNumber;

    u1_RidNumber = Dcm_Dsp_SID31_OBD_u1RidNumber;

    for( u1_RidInfoIndex = (uint8)0U; u1_RidInfoIndex < u1_RidNumber; u1_RidInfoIndex++ )
    {
        if( u1ReqRid == (Dcm_MsgItemType)Dcm_Dsp_SID31_OBD_RidInfo[u1_RidInfoIndex].u1DcmDspRidIdentifier )
        {
            *ptRidInfoIndex = u1_RidInfoIndex;
            break;
        }
    }

    return;
}


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* DCM_OBD_RANGE_RID_USE == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

