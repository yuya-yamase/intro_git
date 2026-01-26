/* Dcm_Dsp_SID09_c(v5-5-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID09/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

#if ( DCM_OBDTYPE_TYPE_OBD == STD_ON )
#if ( DCM_SUPPORT_SID09 == STD_ON )

#include <Dcm/Dcm_Dsp_SID09.h>
#include "../../Dsp/cfg/Dcm_Dsp_SID09_Cfg.h"
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Dsp_Main.h>
#include <Dcm/Dcm_Dsp_OBDIf.h>
#include "Dcm/Dcm_Main_EvtDistr.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SID09_REQ_DATA_LEN_MIN  ( (Dcm_MsgLenType)1U )
#define DCM_DSP_SID09_REQ_DATA_LEN_MAX  ( (Dcm_MsgLenType)6U )

#define DCM_DSP_SID09_INFTYP_MASK       ( (uint8)0x1FU )

#define DCM_DSP_SID09_INFTYPKIND_SUP    ( (uint8)0x00U )
#define DCM_DSP_SID09_INFTYPKIND_NORMAL ( (uint8)0x01U )

#define DCM_DSP_SID09_INFTYP_LEN        ( (Dcm_MsgLenType)1U )
#define DCM_DSP_SID09_SUPINFTYP_LEN     ( (Dcm_MsgLenType)4U )
#define DCM_DSP_SID09_NODI_LEN          ( (Dcm_MsgLenType)1U )

#define DCM_DSP_SID09_READ_DATA_NONE    ( (uint8)0x00U )
#define DCM_DSP_SID09_READ_DATA_OK      ( (uint8)0x01U )
#define DCM_DSP_SID09_READ_OVER_FLOW    ( (uint8)0x02U )
#define DCM_DSP_SID09_READ_DATA_PENDING ( (uint8)0x03U )

#define DCM_DSP_SID09_SUPINFTYP_BIT     ( (uint32)0x00000001U )
#define DCM_DSP_SID09_SUPINFTYP_BIT_TOP ( (uint8)31U )
#define DCM_DSP_SID09_SUPINFTYP_OFS     ( (uint8)1U )

#define DCM_DSP_SID09_BITSHIFT_5        ( (uint8)5U )
#define DCM_DSP_SID09_BITSHIFT_8        ( (uint8)8U )
#define DCM_DSP_SID09_BITSHIFT_16       ( (uint8)16U )
#define DCM_DSP_SID09_BITSHIFT_24       ( (uint8)24U )

#define DCM_DSP_SID09_RES_DATA_POS_1    ( (uint8)1U )
#define DCM_DSP_SID09_RES_DATA_POS_2    ( (uint8)2U )
#define DCM_DSP_SID09_RES_DATA_POS_3    ( (uint8)3U )

#define DCM_DSP_SID09_DIFF2NEXT_SUP_INFOTYPE    ( (uint8)0x20U )
#define DCM_DSP_SID09_SUPPORT_NONE              ( (uint32)0x00000000U )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID09_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID09_CancelProc
(
    void
);
static FUNC ( uint8, DCM_CODE ) Dcm_Dsp_SID09_InfTypKindCheck
(
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID09_InfTypSupCheck
(
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType
);
static FUNC ( uint8, DCM_CODE ) Dcm_Dsp_SID09_MakeNormInfTypDat
(
    CONST( Dcm_OpStatusType, AUTOMATIC ) u1OpStatus,
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType
);
static FUNC ( uint8, DCM_CODE ) Dcm_Dsp_SID09_MakeSupInfTypData
(
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID09_GetInfTypTableIdx
(
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptInfoTypeTableIndex
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID09_MakeNODIData
(
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType
);
static FUNC ( uint8, DCM_CODE ) Dcm_Dsp_SID09_NormInfTypProcess
(
    CONST( Dcm_OpStatusType, AUTOMATIC ) u1OpStatus,
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType
);
static FUNC ( uint8, DCM_CODE ) Dcm_Dsp_SID09_MakeNormInfTypDEM
(
    CONST( Dcm_OpStatusType, AUTOMATIC ) u1OpStatus,
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType
);
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID09_GenerateAvailInfoTypeTable
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

static VAR( uint32, DCM_VAR_NO_INIT ) Dcm_Dsp_SID09_u4AvailableInfoTypeTable[DCM_SUPINFOTYPE_TBL];
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_SID09_u1AvailableInfoTypeNumber;
static VAR( uint8, DCM_VAR_NO_INIT ) Dcm_Dsp_SID09_u1PendingElement;

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
/* Function Name | Dcm_SID09                                                */
/* Description   | SID09 request processing                                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus        : Operation state                   */
/*               | [IN] pMsgContext     : Message Context                   */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK               : Processing normal                 */
/*               |   DCM_E_PENDING      : Pending                           */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID09 /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = (Std_ReturnType)E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID09_InitialProc( pMsgContext );
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        Dcm_Dsp_SID09_CancelProc();
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID09_Cbk                                        */
/* Description   | Call Back Function to Continue SID09 Processing          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId       : Event Index                       */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID09_Cbk  /* MISRA DEVIATION */
(
    const uint8 u1EventId                 /* MISRA DEVIATION */
)
{
    Std_ReturnType               u1_Result;
    uint8                        u1_InfoTypeTableIndex;
    uint8                        u1_GetInfoTypeDataResult;
    Dcm_NegativeResponseCodeType u1_ErrorCode;
    Dcm_MsgItemType              u1_ReqInfoType;

    u1_ErrorCode = (Dcm_NegativeResponseCodeType)0x00U;
    u1_ReqInfoType = Dcm_Dsp_Main_stMsgContext.reqData[0];

    u1_Result = Dcm_Dsp_SID09_GetInfTypTableIdx( u1_ReqInfoType, &u1_InfoTypeTableIndex );
    if( u1_Result == (Std_ReturnType)E_OK )
    {
        u1_GetInfoTypeDataResult = Dcm_Dsp_SID09_MakeNormInfTypDat( (Dcm_OpStatusType)DCM_PENDING, u1_ReqInfoType );
        if( u1_GetInfoTypeDataResult == DCM_DSP_SID09_READ_DATA_PENDING )
        {
            /* Return value ignoring */
            (void)Dcm_Main_EvtDistr_SendEvent( (uint8)DCM_M_EVTID_SID09_GET_INFOTYPE );
        }
        else
        {
            if( u1_GetInfoTypeDataResult == DCM_DSP_SID09_READ_DATA_OK )
            {
                Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
            }
            else if( u1_GetInfoTypeDataResult == DCM_DSP_SID09_READ_OVER_FLOW )
            {
                /* NRC0x14 */
                u1_ErrorCode = DCM_E_RESPONSETOOLONG;
            }
            else
            {
                /* NRC0x31 */
                u1_ErrorCode = DCM_E_REQUESTOUTOFRANGE;
            }

            if( u1_ErrorCode != (Dcm_NegativeResponseCodeType)0x00U )
            {
                /* NRC */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
            }
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }
    }
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID09_InitialProc                                */
/* Description   | Initial process of SID09 request                         */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext    : Message Context                   */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK               : Processing normal                 */
/*               |   DCM_E_PENDING      : Pending                           */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID09_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Std_ReturnType               u1_RetVal;
    Std_ReturnType               u1_CheckResult;
    Dcm_NegativeResponseCodeType u1_ErrorCode;
    uint8                        u1_GetInfoTypeDataResult;
    uint8                        u1_TopReqInfoTypeKind;
    uint8                        u1_ReqInfoTypeKind;
    uint8                        u1_ReqInfoTypeNum;
    Dcm_MsgItemType              u1_ReqData;

    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    Dcm_Dsp_SID09_u1PendingElement = (uint8)0x00U;
    u1_RetVal = (Std_ReturnType)E_OK;
    u1_ErrorCode = (Dcm_NegativeResponseCodeType)0x00U;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    /* Request Data Length Check */
    if( Dcm_Dsp_Main_stMsgContext.reqDataLen >= DCM_DSP_SID09_REQ_DATA_LEN_MIN )
    {
        /* Initialize Reaponse Data Length */
        Dcm_Dsp_Main_stMsgContext.resDataLen = (Dcm_MsgLenType)0U;

        /* Genarate Available InfoType Table */
        Dcm_Dsp_SID09_GenerateAvailInfoTypeTable();

        /* Get Top InfoType Kind */
        u1_TopReqInfoTypeKind = Dcm_Dsp_SID09_InfTypKindCheck( Dcm_Dsp_Main_stMsgContext.reqData[0] );

        /* Request Data Length Check */
        if( ( ( u1_TopReqInfoTypeKind == DCM_DSP_SID09_INFTYPKIND_NORMAL ) &&
              ( Dcm_Dsp_Main_stMsgContext.reqDataLen == DCM_DSP_SID09_REQ_DATA_LEN_MIN ) ) ||
            ( ( u1_TopReqInfoTypeKind == DCM_DSP_SID09_INFTYPKIND_SUP ) &&
              ( Dcm_Dsp_Main_stMsgContext.reqDataLen <= DCM_DSP_SID09_REQ_DATA_LEN_MAX ) ) )
        {
            for( u1_ReqInfoTypeNum = (uint8)0U; u1_ReqInfoTypeNum < (uint8)Dcm_Dsp_Main_stMsgContext.reqDataLen; u1_ReqInfoTypeNum++ )
            {
                u1_ReqData = Dcm_Dsp_Main_stMsgContext.reqData[u1_ReqInfoTypeNum];
                u1_ReqInfoTypeKind = Dcm_Dsp_SID09_InfTypKindCheck( u1_ReqData );
                /* Mixed InfoType Check */
                if( u1_TopReqInfoTypeKind == u1_ReqInfoTypeKind )
                {
                    /* InfoType Support Check */
                    u1_CheckResult = Dcm_Dsp_SID09_InfTypSupCheck( u1_ReqData );
                    if( u1_CheckResult == (Std_ReturnType)E_OK )
                    {
                        if( u1_TopReqInfoTypeKind == DCM_DSP_SID09_INFTYPKIND_NORMAL )
                        {   /* Buffer Over Flow Check */
                            u1_GetInfoTypeDataResult = Dcm_Dsp_SID09_NormInfTypProcess( DCM_INITIAL, u1_ReqData );
                        }
                        else
                        {
                            /* Make Support InfoType Data */
                            u1_GetInfoTypeDataResult = Dcm_Dsp_SID09_MakeSupInfTypData( u1_ReqData );
                        }

                        if( u1_GetInfoTypeDataResult == DCM_DSP_SID09_READ_DATA_PENDING )
                        {
                            /* Return value ignoring */
                            (void)Dcm_Main_EvtDistr_SendEvent( (uint8)DCM_M_EVTID_SID09_GET_INFOTYPE );
                            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
                            u1_RetVal = (Std_ReturnType)DCM_E_PENDING;
                        }
                        else if( u1_GetInfoTypeDataResult == DCM_DSP_SID09_READ_DATA_OK )
                        {
                            if( u1_TopReqInfoTypeKind == DCM_DSP_SID09_INFTYPKIND_NORMAL )
                            {
                                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
                            }
                        }
                        else if( u1_GetInfoTypeDataResult == DCM_DSP_SID09_READ_OVER_FLOW )
                        {
                            /* NRC0x14 */
                            u1_ErrorCode = DCM_E_RESPONSETOOLONG;
                        }
                        else
                        {
                            /* Get Next InfoType Data */
                        }
                    }
                    else
                    {
                        /* Get Next InfoType Data */
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

            if( Dcm_Dsp_Main_stMsgContext.resDataLen == (Dcm_MsgLenType)0U )
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
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_ErrorCode );
    }
    else
    {
        if( u1_RetVal == (Std_ReturnType)E_OK )
        {
            Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
        }
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID09_CancelProc                                 */
/* Description   | Cancel process of SID09 request                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID09_CancelProc
(
    void
)
{
    Std_ReturnType     u1_Result;
    boolean            b_UserNotifyFlag;
    Dcm_MsgItemType    u1_ReqInfoType;
    uint8              u1_InfoTypeTableIndex;
    uint8              u1_WritableSize;
    
    b_UserNotifyFlag = Dcm_Dsp_Main_GetUserNotifyFlag();

    if( b_UserNotifyFlag == (boolean)TRUE )
    {
        u1_ReqInfoType = Dcm_Dsp_Main_stMsgContext.reqData[0];
        u1_WritableSize = (uint8)0U;

        u1_Result = Dcm_Dsp_SID09_GetInfTypTableIdx( u1_ReqInfoType, &u1_InfoTypeTableIndex );
        if( u1_Result == (Std_ReturnType)E_OK )
        {
#ifndef JGXSTACK
            /* Callout ignores the return value */
            (void)DcmDspInfoTypeTbl[u1_InfoTypeTableIndex].ptDcmDspVehInfoData[Dcm_Dsp_SID09_u1PendingElement].ptDcmDspVehInfoDataReadFnc( DCM_CANCEL , &u1_ReqInfoType ,&u1_WritableSize );
#else  /* JGXSTACK */
            /* user-defined */
#endif /* JGXSTACK */
        }
        /* Return value ignoring */
        (void)Dcm_Main_EvtDistr_DeleteEvent( (uint8)DCM_M_EVTID_SID09_GET_INFOTYPE, (boolean)FALSE );
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID09_InfTypKindCheck                            */
/* Description   | Check InfoType Kind SupportInfoType or NormalInfoType    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1reqInfoType                : Request InfoType     */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_SID09_INFTYPKIND_SUP    : Support InfoType     */
/*               |   DCM_DSP_SID09_INFTYPKIND_NORMAL : Normal InfoType      */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( uint8, DCM_CODE ) Dcm_Dsp_SID09_InfTypKindCheck
(
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType
)
{
    uint8 u1_InfoTypeKind;

    u1_InfoTypeKind = DCM_DSP_SID09_INFTYPKIND_NORMAL;

    if( (uint8)( u1reqInfoType & DCM_DSP_SID09_INFTYP_MASK ) == DCM_DSP_SID09_INFTYPKIND_SUP )
    {
        u1_InfoTypeKind = DCM_DSP_SID09_INFTYPKIND_SUP;
    }

    return u1_InfoTypeKind;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID09_InfTypSupCheck                             */
/* Description   | Check InfoType Support                                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1reqInfoType   : Request InfoType                  */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK               : InfoType Supported                */
/*               |   E_NOT_OK           : InfoType Not Supported            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID09_InfTypSupCheck
(
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType
)
{
    Std_ReturnType u1_CheckResult;
    uint8          u1_SupportInfoTypeTableIndex;
    uint8          u1_SupportBitShiftNum;
    uint32         u4_InfoTypeSupportBitMask;
    uint32         u4_InfoTypeSupportBit;
    uint8          u1_SupInfoTypeNumber;

    u1_CheckResult = (Std_ReturnType)E_NOT_OK;
    u1_SupInfoTypeNumber = Dcm_Dsp_SID09_u1AvailableInfoTypeNumber;

    if( u1reqInfoType != (Dcm_MsgItemType)0x00U )
    {
        /* Check InfoType Support From BIT of Support InfoType Table */
        u1_SupportInfoTypeTableIndex = (uint8)( (uint8)( u1reqInfoType - DCM_DSP_SID09_SUPINFTYP_OFS ) >> DCM_DSP_SID09_BITSHIFT_5 );
        if( u1_SupportInfoTypeTableIndex < u1_SupInfoTypeNumber )
        {
            u1_SupportBitShiftNum = DCM_DSP_SID09_SUPINFTYP_BIT_TOP - (uint8)( (uint8)( u1reqInfoType - DCM_DSP_SID09_SUPINFTYP_OFS ) & DCM_DSP_SID09_INFTYP_MASK );
            u4_InfoTypeSupportBitMask = (uint32)( DCM_DSP_SID09_SUPINFTYP_BIT << u1_SupportBitShiftNum );
            u4_InfoTypeSupportBit = (uint32)( u4_InfoTypeSupportBitMask & Dcm_Dsp_SID09_u4AvailableInfoTypeTable[u1_SupportInfoTypeTableIndex] );

            if( u4_InfoTypeSupportBit != (uint32)0x00000000U )
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
/* Function Name | Dcm_Dsp_SID09_MakeNormInfTypDat                          */
/* Description   | Make Normal InfoType Data                                */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus                   : Operation state      */
/* Parameters    | [IN] u1reqInfoType                : Request InfoType     */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_SID09_READ_DATA_NONE    : Read Data None       */
/*               |   DCM_DSP_SID09_READ_DATA_OK      : Read Data OK         */
/*               |   DCM_DSP_SID09_READ_OVER_FLOW    : Read Over Flow       */
/*               |   DCM_DSP_SID09_READ_DATA_PENDING : Read Data Pending    */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( uint8, DCM_CODE ) Dcm_Dsp_SID09_MakeNormInfTypDat
(
    CONST( Dcm_OpStatusType, AUTOMATIC ) u1OpStatus,
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType
)
{
    uint8                                                                     u1_cnt;
    Std_ReturnType                                                            u1_RetVal;
    Std_ReturnType                                                            u1_Result;
    uint8                                                                     u1_GetInfoTypeDataResult;
    Dcm_MsgLenType                                                            u4_ResDataLen;
    uint8                                                                     u1_InfoTypeTableIndex;
    uint8                                                                     u1_ElementNum;
    uint8                                                                     u1_InfoTypeSize;
    uint8                                                                     u1_InfoTypeBufIndex;
    Dcm_OpStatusType                                                          u1_opStatus;
    P2CONST( AB_83_ConstV DcmDspInfoTypeDataType, AUTOMATIC, DCM_APPL_CONST ) pt_VehInfoDataPtr;
    uint8                                                                     u1_NumOfVehInfoData;
    uint8                                                                     u1_WritableSize;

    u1_GetInfoTypeDataResult = DCM_DSP_SID09_READ_DATA_NONE;

    /* Get Normal InfoType Table Index */
    u1_Result = Dcm_Dsp_SID09_GetInfTypTableIdx( u1reqInfoType, &u1_InfoTypeTableIndex );
    if( u1_Result == (Std_ReturnType)E_OK )
    {
        u1_ElementNum = Dcm_Dsp_SID09_u1PendingElement;
        u1_opStatus = u1OpStatus;
        u1_NumOfVehInfoData = DcmDspInfoTypeTbl[u1_InfoTypeTableIndex].u1DcmDspVehInfoDataNum;
        u4_ResDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen;

        /* Get Normal InfoType Data */
        for( u1_cnt = u1_ElementNum; u1_cnt < u1_NumOfVehInfoData; u1_cnt++ )
        {
            pt_VehInfoDataPtr = &DcmDspInfoTypeTbl[u1_InfoTypeTableIndex].ptDcmDspVehInfoData[u1_ElementNum];
            u1_InfoTypeSize = pt_VehInfoDataPtr->u1DcmDspVehInfoDataSize;
            /* Buffer Over Flow Check */
            if( ( u4_ResDataLen + (Dcm_MsgLenType)u1_InfoTypeSize ) <= Dcm_Dsp_Main_stMsgContext.resMaxDataLen )    /* no wrap around */
            {
                u1_WritableSize = u1_InfoTypeSize;
                /* Initialize Reaponse Data */
                for( u1_InfoTypeBufIndex = (uint8)0U; u1_InfoTypeBufIndex < u1_InfoTypeSize; u1_InfoTypeBufIndex++ )
                {
                    Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataLen + u1_InfoTypeBufIndex] = (Dcm_MsgItemType)0x00U;    /* no wrap around */
                }
#ifndef JGXSTACK
                /* Callout */
                u1_RetVal = pt_VehInfoDataPtr->ptDcmDspVehInfoDataReadFnc( u1_opStatus, &Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataLen] ,&u1_WritableSize );
#else  /* JGXSTACK */
                u1_RetVal = E_OK;
                /* user-defined */
#endif /* JGXSTACK */
                if( u1_RetVal == (Std_ReturnType)E_OK )
                {
                    if( u1_WritableSize <= u1_InfoTypeSize )
                    {

                        u4_ResDataLen += (Dcm_MsgLenType)u1_WritableSize;   /* no wrap around */
                        u1_opStatus = DCM_INITIAL;
                        Dcm_Dsp_Main_stMsgContext.resDataLen += (Dcm_MsgLenType)u1_WritableSize;    /* no wrap around */
                        u1_GetInfoTypeDataResult = DCM_DSP_SID09_READ_DATA_OK;
                    }
                    else
                    {
                        u1_GetInfoTypeDataResult = DCM_DSP_SID09_READ_OVER_FLOW;
                    }
                }
                else
                {
                    if( u1_RetVal == (Std_ReturnType)DCM_E_PENDING )
                    {
                        Dcm_Dsp_SID09_u1PendingElement = u1_ElementNum;
                        u1_GetInfoTypeDataResult = DCM_DSP_SID09_READ_DATA_PENDING;
                    }
                    else
                    {
                        u1_GetInfoTypeDataResult = DCM_DSP_SID09_READ_DATA_NONE;
                        Dcm_Dsp_Main_stMsgContext.resDataLen = (Dcm_MsgLenType)0;
                    }
                }
            }
            else
            {
                u1_GetInfoTypeDataResult = DCM_DSP_SID09_READ_OVER_FLOW;
            }

            if( u1_GetInfoTypeDataResult != DCM_DSP_SID09_READ_DATA_OK )
            {
                break;
            }
            u1_ElementNum = (uint8)(u1_ElementNum + (uint8)1U);
        }
    }

    return u1_GetInfoTypeDataResult;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID09_MakeSupInfTypData                          */
/* Description   | Make Support InfoType Data                               */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1reqInfoType             : Request InfoType        */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_SID09_READ_DATA_NONE : Read Data None          */
/*               |   DCM_DSP_SID09_READ_DATA_OK   : Read Data OK            */
/*               |   DCM_DSP_SID09_READ_OVER_FLOW : Read Over Flow          */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( uint8, DCM_CODE ) Dcm_Dsp_SID09_MakeSupInfTypData
(
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType
)
{
    Dcm_MsgLenType u4_ResDataLen;
    uint8          u1_GetInfoTypeDataResult;
    uint8          u1_InfoTypeTableIndex;
    uint32         u4_SupportInfoTypeTbl;
    uint8          u1_SupInfoTypeNumber;

    u4_ResDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen;
    u1_GetInfoTypeDataResult = DCM_DSP_SID09_READ_DATA_NONE;
    u1_SupInfoTypeNumber = Dcm_Dsp_SID09_u1AvailableInfoTypeNumber;

    /* Buffer Over Flow Check */
    if( ( u4_ResDataLen + DCM_DSP_SID09_INFTYP_LEN + DCM_DSP_SID09_SUPINFTYP_LEN ) <= Dcm_Dsp_Main_stMsgContext.resMaxDataLen ) /* no wrap around */
    {
        /* Set Support InfoType Data */
        /* Calculate SupportInfoTypeTable Index from Request InfoType */
        u1_InfoTypeTableIndex = (uint8)( u1reqInfoType >> DCM_DSP_SID09_BITSHIFT_5 );
        if( u1_InfoTypeTableIndex < u1_SupInfoTypeNumber )
        {
            u4_SupportInfoTypeTbl = Dcm_Dsp_SID09_u4AvailableInfoTypeTable[u1_InfoTypeTableIndex];

            Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataLen] = u1reqInfoType;
            Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataLen + DCM_DSP_SID09_INFTYP_LEN] =   /* no wrap around */
                (Dcm_MsgItemType)( u4_SupportInfoTypeTbl >> DCM_DSP_SID09_BITSHIFT_24 );
            Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataLen + DCM_DSP_SID09_INFTYP_LEN + DCM_DSP_SID09_RES_DATA_POS_1] =    /* no wrap around */
                (Dcm_MsgItemType)( u4_SupportInfoTypeTbl >> DCM_DSP_SID09_BITSHIFT_16 );
            Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataLen + DCM_DSP_SID09_INFTYP_LEN + DCM_DSP_SID09_RES_DATA_POS_2] =    /* no wrap around */
                (Dcm_MsgItemType)( u4_SupportInfoTypeTbl >> DCM_DSP_SID09_BITSHIFT_8 );
            Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataLen + DCM_DSP_SID09_INFTYP_LEN + DCM_DSP_SID09_RES_DATA_POS_3] =    /* no wrap around */
                (Dcm_MsgItemType)u4_SupportInfoTypeTbl;
            Dcm_Dsp_Main_stMsgContext.resDataLen += DCM_DSP_SID09_INFTYP_LEN + DCM_DSP_SID09_SUPINFTYP_LEN; /* no wrap around */
            u1_GetInfoTypeDataResult = DCM_DSP_SID09_READ_DATA_OK;
        }
    }
    else
    {
        u1_GetInfoTypeDataResult = DCM_DSP_SID09_READ_OVER_FLOW;
    }

    return u1_GetInfoTypeDataResult;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID09_GetInfTypTableIdx                          */
/* Description   | Get InfoType Table Index                                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1reqInfoType        : Request InfoType             */
/*               | [OUT]ptInfoTypeTableIndex : InfoType Table Index         */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_NOT_OK                : Get InfoType Table Index NG  */
/*               |   E_OK                    : Get InfoType Table Index OK  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID09_GetInfTypTableIdx
(
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptInfoTypeTableIndex
)
{
    Std_ReturnType                                                       u1_Result;
    uint8                                                                u1_InfoTypeTableIndex;
    uint8                                                                u1_InfoTypeNumber;

    u1_Result = (Std_ReturnType)E_NOT_OK;
    u1_InfoTypeNumber = Dcm_P_SID09_u1InfoTypeNumber;

    for( u1_InfoTypeTableIndex = (uint8)0U; u1_InfoTypeTableIndex < u1_InfoTypeNumber; u1_InfoTypeTableIndex++ )
    {
        if( u1reqInfoType == (Dcm_MsgItemType)DcmDspInfoTypeTbl[u1_InfoTypeTableIndex].u1DcmDspVehInfoInfoType )
        {
            u1_Result = (Std_ReturnType)E_OK;
            *ptInfoTypeTableIndex = u1_InfoTypeTableIndex;
            break;
        }
    }

    return u1_Result;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID09_MakeNODIData                               */
/* Description   | Calculate number of data items                           */
/* Preconditions | None                                                     */
/* Parameters    | [in] u1reqInfoType :                                     */
/*               |        Request InfoType                                  */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID09_MakeNODIData
(
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType
)
{
    Std_ReturnType               u1_GetInfTypTableIdxResult;
    uint8                        u1_InfoTypeTableIndex;
    uint8                        u1_ElementNum;

    u1_GetInfTypTableIdxResult = Dcm_Dsp_SID09_GetInfTypTableIdx( u1reqInfoType, &u1_InfoTypeTableIndex );

    if( u1_GetInfTypTableIdxResult == (Std_ReturnType)E_OK )
    {
        if( DcmDspInfoTypeTbl[u1_InfoTypeTableIndex].u1DcmDspVehInfoInterNODI == (uint8)STD_ON )
        {
            u1_ElementNum = DcmDspInfoTypeTbl[u1_InfoTypeTableIndex].u1DcmDspVehInfoDataNum;

            Dcm_Dsp_Main_stMsgContext.resData[Dcm_Dsp_Main_stMsgContext.resDataLen] = (Dcm_MsgItemType)u1_ElementNum;
            Dcm_Dsp_Main_stMsgContext.resDataLen += DCM_DSP_SID09_NODI_LEN; /* no wrap around */
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID09_NormInfTypProcess                          */
/* Description   | Make Normal InfoType Data Process                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus                   : Operation state      */
/* Parameters    | [IN] u1reqInfoType                : Request InfoType     */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_SID09_READ_DATA_NONE    : Read Data None       */
/*               |   DCM_DSP_SID09_READ_DATA_OK      : Read Data OK         */
/*               |   DCM_DSP_SID09_READ_OVER_FLOW    : Read Over Flow       */
/*               |   DCM_DSP_SID09_READ_DATA_PENDING : Read Data Pending    */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( uint8, DCM_CODE ) Dcm_Dsp_SID09_NormInfTypProcess
(
    CONST( Dcm_OpStatusType, AUTOMATIC ) u1OpStatus,
    CONST( Dcm_MsgItemType, AUTOMATIC ) u1reqInfoType
)
{
    uint8                        u1_GetInfoTypeDataResult;
    boolean                      b_IsDemCall;

    /* Determining whether it is an application target of DEM-API */
    b_IsDemCall = Dcm_Dsp_SID09_JudgeDemIUMPRUse( u1reqInfoType );
    if( b_IsDemCall ==  (boolean)TRUE )
    {
        /* It is the target of DEM-API. */
        if( ( DCM_DSP_SID09_INFTYP_LEN ) <= Dcm_Dsp_Main_stMsgContext.resMaxDataLen )
        {
            Dcm_Dsp_Main_stMsgContext.resData[Dcm_Dsp_Main_stMsgContext.resDataLen] = u1reqInfoType;
            Dcm_Dsp_Main_stMsgContext.resDataLen += DCM_DSP_SID09_INFTYP_LEN;   /* no wrap around */
            /* Make Normal InfoType Data Dem */
            u1_GetInfoTypeDataResult = Dcm_Dsp_SID09_MakeNormInfTypDEM( u1OpStatus, u1reqInfoType );
        }
        else
        {
            u1_GetInfoTypeDataResult = DCM_DSP_SID09_READ_OVER_FLOW;
        }
    }
    else
    {
        /* It is the target of SWC-Callout. */
        if( ( DCM_DSP_SID09_INFTYP_LEN + DCM_DSP_SID09_NODI_LEN ) <= Dcm_Dsp_Main_stMsgContext.resMaxDataLen )
        {
            Dcm_Dsp_Main_stMsgContext.resData[Dcm_Dsp_Main_stMsgContext.resDataLen] = u1reqInfoType;
            Dcm_Dsp_Main_stMsgContext.resDataLen += DCM_DSP_SID09_INFTYP_LEN;   /* no wrap around */
            /* Make NoDI Data */
            Dcm_Dsp_SID09_MakeNODIData( u1reqInfoType );
            /* Make Normal InfoType Data */
            u1_GetInfoTypeDataResult = Dcm_Dsp_SID09_MakeNormInfTypDat( u1OpStatus, u1reqInfoType );
        }
        else
        {
            u1_GetInfoTypeDataResult = DCM_DSP_SID09_READ_OVER_FLOW;
        }
    }

    return u1_GetInfoTypeDataResult;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID09_MakeNormInfTypDEM                          */
/* Description   | Make InfoType Data Obtained From DEM                     */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1OpStatus                   : Operation state      */
/* Parameters    | [IN] u1reqInfoType                : Request InfoType     */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_SID09_READ_DATA_NONE    : Read Data None       */
/*               |   DCM_DSP_SID09_READ_DATA_OK      : Read Data OK         */
/*               |   DCM_DSP_SID09_READ_OVER_FLOW    : Read Over Flow       */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( uint8, DCM_CODE ) Dcm_Dsp_SID09_MakeNormInfTypDEM
(
    CONST( Dcm_OpStatusType, AUTOMATIC )    u1OpStatus,
    CONST( Dcm_MsgItemType, AUTOMATIC )     u1reqInfoType
)
{
    Std_ReturnType                                                              u1_RetVal;
    Std_ReturnType                                                              u1_Result;
    uint8                                                                       u1_GetInfoTypeDataResult;
    Dcm_MsgLenType                                                              u4_ResDataLen;
    uint8                                                                       u1_InfoTypeTableIndex;
    uint8                                                                       u1_ElementNum;
    uint8                                                                       u1_InfoTypeSize;
    uint8                                                                       u1_InfoTypeBufIndex;
    Dcm_OpStatusType                                                            u1_opStatus;
    P2CONST( AB_83_ConstV DcmDspInfoTypeDataType, AUTOMATIC, DCM_APPL_CONST )   pt_VehInfoDataPtr;
    uint8                                                                       u1_WritableSize;

    u1_GetInfoTypeDataResult = DCM_DSP_SID09_READ_DATA_NONE;

    /* Get Normal InfoType Table Index */
    u1_Result = Dcm_Dsp_SID09_GetInfTypTableIdx( u1reqInfoType, &u1_InfoTypeTableIndex );
    if( u1_Result == (Std_ReturnType)E_OK )
    {
        u1_ElementNum = Dcm_Dsp_SID09_u1PendingElement;
        u1_opStatus = u1OpStatus;
        pt_VehInfoDataPtr = &DcmDspInfoTypeTbl[u1_InfoTypeTableIndex].ptDcmDspVehInfoData[u1_ElementNum];
        u4_ResDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen;

        u1_InfoTypeSize = pt_VehInfoDataPtr->u1DcmDspVehInfoDataSize;
        /* Buffer Over Flow Check */
        if( ( u4_ResDataLen + (Dcm_MsgLenType)u1_InfoTypeSize ) <= Dcm_Dsp_Main_stMsgContext.resMaxDataLen )    /* no wrap around */
        {
            u1_WritableSize = u1_InfoTypeSize;
            /* Initialize Reaponse Data */
            for( u1_InfoTypeBufIndex = (uint8)0U; u1_InfoTypeBufIndex < u1_InfoTypeSize; u1_InfoTypeBufIndex++ )
            {
                Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataLen + u1_InfoTypeBufIndex] = (Dcm_MsgItemType)0x00U;    /* no wrap around */
            }
            /* Call DEM-API connector */
            u1_RetVal = Dcm_Dsp_SID09_GetInfoTypeValue( u1_opStatus, u1reqInfoType, &Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataLen], &u1_WritableSize );
            if( u1_RetVal == (Std_ReturnType)E_OK )
            {
                if( u1_WritableSize <= u1_InfoTypeSize )
                {
                    Dcm_Dsp_Main_stMsgContext.resDataLen += (Dcm_MsgLenType)u1_WritableSize;    /* no wrap around */
                    u1_GetInfoTypeDataResult = DCM_DSP_SID09_READ_DATA_OK;
                }
                else
                {
                    u1_GetInfoTypeDataResult = DCM_DSP_SID09_READ_OVER_FLOW;
                }
            }
            else
            {
                u1_GetInfoTypeDataResult = DCM_DSP_SID09_READ_DATA_NONE;
                Dcm_Dsp_Main_stMsgContext.resDataLen = (Dcm_MsgLenType)0;
            }
        }
        else
        {
            u1_GetInfoTypeDataResult = DCM_DSP_SID09_READ_OVER_FLOW;
        }
    }

    return u1_GetInfoTypeDataResult;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID09_GenerateAvailInfoTypeTable                 */
/* Description   | Generate Available Table                                 */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SID09_GenerateAvailInfoTypeTable
(
    void
)
{
    uint32                      u4_SupportedList;
    uint8                       u1_SupportedInfoTypeNumber;
    uint8                       u1_SupportedInfoType;
    uint8                       u1_LoopInfoTypeTableNum;
    boolean                     b_CalibUse;

    u1_SupportedInfoTypeNumber = Dcm_P_SID09_u1SupInfoTypeNumber;
    Dcm_Dsp_SID09_u1AvailableInfoTypeNumber = (uint8)0U;

    for( u1_LoopInfoTypeTableNum = (uint8)0U; u1_LoopInfoTypeTableNum < u1_SupportedInfoTypeNumber; u1_LoopInfoTypeTableNum++ )
    {
        u1_SupportedInfoType = (uint8)( DCM_DSP_SID09_DIFF2NEXT_SUP_INFOTYPE * u1_LoopInfoTypeTableNum );
        b_CalibUse  = (boolean)FALSE;
        u4_SupportedList = DCM_DSP_SID09_SUPPORT_NONE;

        Dcm_GetAvailableInfoType( u1_SupportedInfoType, &b_CalibUse, &u4_SupportedList );
        if( b_CalibUse == (boolean)TRUE )
        {
            Dcm_Dsp_SID09_u4AvailableInfoTypeTable[u1_LoopInfoTypeTableNum] = (uint32)( DcmDspSupportInfoTypeTbl[u1_LoopInfoTypeTableNum] & u4_SupportedList );
        }
        else
        {
            Dcm_Dsp_SID09_u4AvailableInfoTypeTable[u1_LoopInfoTypeTableNum] = (uint32)( DcmDspSupportInfoTypeTbl[u1_LoopInfoTypeTableNum] );
        }

        if( Dcm_Dsp_SID09_u4AvailableInfoTypeTable[u1_LoopInfoTypeTableNum] != DCM_DSP_SID09_SUPPORT_NONE )
        {
            Dcm_Dsp_SID09_u1AvailableInfoTypeNumber = (uint8)(Dcm_Dsp_SID09_u1AvailableInfoTypeNumber + (uint8)1U);
        }
    }

    return;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID09 == STD_ON */
#endif /* DCM_OBDTYPE_TYPE_OBD */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2018-12-25                                              */
/*  v3-0-0         :2019-09-26                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
