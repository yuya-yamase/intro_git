/* Dcm_Dsp_SIDB9_c(v5-3-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SIDB9/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

#if( DCM_SUPPORT_SIDB9 == STD_ON )

#include <Dcm/Dcm_Dsp_SIDB9.h>
#include "../../Dsp/cfg/Dcm_Dsp_SIDB9_Cfg.h"
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define DCM_DSP_SIDB9_SUB01                 ((uint8)0x01U)
#define DCM_DSP_SIDB9_SUB02                 ((uint8)0x02U)
#define DCM_DSP_SIDB9_SUB03                 ((uint8)0x03U)
#define DCM_DSP_SIDB9_SUB04                 ((uint8)0x04U)
#define DCM_DSP_SIDB9_SUB05                 ((uint8)0x05U)
#define DCM_DSP_SIDB9_SUB06                 ((uint8)0x06U)
#define DCM_DSP_SIDB9_SUB07                 ((uint8)0x07U)
#define DCM_DSP_SIDB9_SUB08                 ((uint8)0x08U)
#define DCM_DSP_SIDB9_SUB09                 ((uint8)0x09U)
#define DCM_DSP_SIDB9_SUB0A                 ((uint8)0x0AU)

#define DCM_DSP_SIDB9_SUBFUNC_MASK          ((uint8)0x7FU)
#define DCM_DSP_SIDB9_SUBFUNC_SUPBIT        ((uint8)0x80U)
#define DCM_DSP_SIDB9_SUBFUNC_LEN           ((uint8)1U)
#define DCM_DSP_SIDB9_SUBFUNC_BYTE          ((uint8)0U)

#define DCM_DSP_SIDB9_SYSID_BYTE            ((uint8)1U)
#define DCM_DSP_SIDB9_SYSID_LEN             ((uint8)1U)
#define DCM_DSP_SIDB9_SYSID_INVALID         ((uint8)0U)

#define DCM_DSP_SIDB9_REQDATALEN_1BCHK      ((uint8)1U)
#define DCM_DSP_SIDB9_REQDATALEN_2BCHK      ((uint8)2U)
#define DCM_DSP_SIDB9_REQDATALEN_3BCHK      ((uint8)3U)
#define DCM_DSP_SIDB9_REQDATALEN_4BCHK      ((uint8)4U)
#define DCM_DSP_SIDB9_REQDATALEN_5BCHK      ((uint8)5U)
#define DCM_DSP_SIDB9_REQDATALEN_6BCHK      ((uint8)6U)

#define DCM_DSP_SIDB9_SF01_SYSIDBYTE        ((uint8)1U)
#define DCM_DSP_SIDB9_SF01_TRIGGERBYTE      ((uint8)2U)
#define DCM_DSP_SIDB9_SF02_SYSIDBYTE        ((uint8)1U)
#define DCM_DSP_SIDB9_SF03_SYSIDBYTE        ((uint8)1U)
#define DCM_DSP_SIDB9_SF03_BNKNUMBYTE       ((uint8)2U)
#define DCM_DSP_SIDB9_SF04_SYSIDBYTE        ((uint8)1U)
#define DCM_DSP_SIDB9_SF04_BNKNUMBYTE       ((uint8)2U)
#define DCM_DSP_SIDB9_SF04_BLKNUMBYTE       ((uint8)3U)
#define DCM_DSP_SIDB9_SF05_SYSIDBYTE        ((uint8)1U)
#define DCM_DSP_SIDB9_SF05_BNKNUMBYTE       ((uint8)2U)
#define DCM_DSP_SIDB9_SF05_BLKNUMBYTE       ((uint8)3U)
#define DCM_DSP_SIDB9_SF05_SRNUMBYTE_H      ((uint8)4U)
#define DCM_DSP_SIDB9_SF05_SRNUMBYTE_L      ((uint8)5U)
#define DCM_DSP_SIDB9_SF07_BNKNUMBYTE       ((uint8)1U)
#define DCM_DSP_SIDB9_SF07_TRIGGERBYTE      ((uint8)2U)
#define DCM_DSP_SIDB9_SF08_BNKNUMBYTE       ((uint8)1U)
#define DCM_DSP_SIDB9_SF09_BNKNUMBYTE       ((uint8)1U)
#define DCM_DSP_SIDB9_SF09_BLKNUMBYTE       ((uint8)2U)
#define DCM_DSP_SIDB9_SF0A_BNKNUMBYTE       ((uint8)1U)
#define DCM_DSP_SIDB9_SF0A_BLKNUMBYTE       ((uint8)2U)
#define DCM_DSP_SIDB9_SF0A_SRNUMBYTE_H      ((uint8)3U)
#define DCM_DSP_SIDB9_SF0A_SRNUMBYTE_L      ((uint8)4U)

#define DCM_DSP_SIDB9_REQDATA_SHIFT         ((uint8)8U)
#define DCM_DSP_SIDB9_MSGLEN_MIN            ((uint8)1U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SIDB9_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SIDB9_ObsReportRequest
(
    const uint8 u1SubFunc,
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext_temp,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode,
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA ) ptNrcFlag
);
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SIDB9_CancelProc
(
    void
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SIDB9_ReqLenMinChk
(
    const Dcm_MsgLenType u4ReqDataLen,
    const uint8 u1SubFunc
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SIDB9_SupportSubChk
(
    const uint8 u1SubFunc
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SIDB9_ReqMsgLenChk
(
    const Dcm_MsgLenType u4ReqDataLen,
    const uint8 u1SubFunc
);
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SIDB9_SecLvChk
(
    void
);
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SIDB9_SetReqDataIn
(
    P2CONST( Dcm_MsgItemType, AUTOMATIC, DCM_APPL_DATA ) ptReqData,
    const uint8 u1SubFunc,
    P2VAR( Dcm_SIDExt03_ReqDataInType, AUTOMATIC, DCM_APPL_DATA ) ptReqDataIn
);
static FUNC( void, DCM_CODE) Dcm_Dsp_SIDB9_GetSystemId
(
    P2CONST( Dcm_MsgItemType, AUTOMATIC, DCM_APPL_DATA ) ptReqData,
    const uint8 u1SubFunc,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA) ptSystemId
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
/* Function Name | Dcm_SIDB9                                                */
/* Description   | Request processing of SID B9                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus    : Operation state                       */
/*               | [IN] pMsgContext : Message Context                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SIDB9
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;
    
    u1_RetVal = E_OK;
    
    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SIDB9_InitialProc( pMsgContext );
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        Dcm_Dsp_SIDB9_CancelProc();
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
/* Function Name | Dcm_Dsp_SIDB9_InitialProc                                */
/* Description   | Initial process of SID B9 request                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SIDB9_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Dcm_MsgContextType           st_MsgContext_temp;
    Std_ReturnType               u1_RetVal;
    Std_ReturnType               u1_RetCheckPrm;
    Std_ReturnType               u1_CheckRet;
    Dcm_NegativeResponseCodeType u1_ErrorCode;
    uint8                        u1_SubFunc;
    uint8                        u1_SystemId;
    boolean                      b_NrcFlag;
    
    u1_RetVal    = E_OK;
    b_NrcFlag    = (boolean)FALSE;
    u1_ErrorCode = (Dcm_NegativeResponseCodeType)0x00U;
    u1_SystemId  = DCM_DSP_SIDB9_SYSID_INVALID;
    
    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    /* Save message context */
    st_MsgContext_temp = *ptMsgContext;
        
    /* Check minimum message length */
    if( st_MsgContext_temp.reqDataLen >= DCM_DSP_SIDB9_MSGLEN_MIN )
    {
        if( (st_MsgContext_temp.reqData[DCM_DSP_SIDB9_SUBFUNC_BYTE] & DCM_DSP_SIDB9_SUBFUNC_SUPBIT) == DCM_DSP_SIDB9_SUBFUNC_SUPBIT )
        {
            st_MsgContext_temp.msgAddInfo.suppressPosResponse = STD_ON;
        }
        u1_SubFunc = st_MsgContext_temp.reqData[DCM_DSP_SIDB9_SUBFUNC_BYTE] & DCM_DSP_SIDB9_SUBFUNC_MASK;
        /* Check minimum message length  */
        u1_CheckRet = Dcm_Dsp_SIDB9_ReqLenMinChk( st_MsgContext_temp.reqDataLen, u1_SubFunc );
        if( u1_CheckRet == (Std_ReturnType)E_OK )
        {
            /* Check Support subfunction */
            u1_CheckRet = Dcm_Dsp_SIDB9_SupportSubChk( u1_SubFunc );
            if( u1_CheckRet == (Std_ReturnType)E_OK )
            {
                /* Get System Id */
                Dcm_Dsp_SIDB9_GetSystemId( st_MsgContext_temp.reqData, u1_SubFunc, &u1_SystemId );
                /* Check Parameter */
                u1_RetCheckPrm = Dcm_Dsp_SIDB9_Obs_CheckParam( u1_SubFunc, u1_SystemId, &u1_ErrorCode );
                if( u1_RetCheckPrm == (Std_ReturnType)E_OK )
                {
                    /* Check request message length  */
                    u1_CheckRet = Dcm_Dsp_SIDB9_ReqMsgLenChk( st_MsgContext_temp.reqDataLen, u1_SubFunc );
                    if( u1_CheckRet == (Std_ReturnType)E_OK )
                    {
                        /* Check active security level */
                        u1_CheckRet = Dcm_Dsp_SIDB9_SecLvChk();
                        if( u1_CheckRet == (Std_ReturnType)E_OK )
                        {
                            Dcm_Dsp_SIDB9_ObsReportRequest( u1_SubFunc, &st_MsgContext_temp,  &u1_ErrorCode, &b_NrcFlag );
                        }
                        else
                        {
                            /* NRC0x33 */
                            b_NrcFlag = (boolean)TRUE;
                            u1_ErrorCode = DCM_E_SECURITYACCESSDENIED;
                        }
                    }
                    else
                    {
                        /* NRC0x13 */
                        b_NrcFlag = (boolean)TRUE;
                        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                    }
                }
                else
                {
                    b_NrcFlag = (boolean)TRUE;
                }
            }
            else
            {
                /* NRC0x12 */
                b_NrcFlag = (boolean)TRUE;
                u1_ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
            }
        }
        else
        {
            /* NRC0x13 */
            b_NrcFlag = (boolean)TRUE;
            u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
    }
    else
    {
        /* NRC0x13 */
        b_NrcFlag = (boolean)TRUE;
        u1_ErrorCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
        
    if( b_NrcFlag != (boolean)FALSE )
    {
        /* Negative response */
        Dcm_Dsp_MsgMaker_SendNegRes( &st_MsgContext_temp, u1_ErrorCode );
    }
    
    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SIDB9_ObsReportRequest                           */
/* Description   | OBS Report Request                                       */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1SubFunc               : Sub function              */
/*               | [IN/OUT] ptMsgContext_temp   : Message context           */
/*               | [OUT] ptErrorCode            : Error code                */
/*               | [OUT] ptNrcFlag              : NRC Flag                  */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SIDB9_ObsReportRequest
(
    const uint8 u1SubFunc,
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext_temp,
    P2VAR( Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA ) ptErrorCode,
    P2VAR( boolean, AUTOMATIC, DCM_APPL_DATA ) ptNrcFlag
)
{
    Dcm_SIDExt03_ReqDataInType         st_ReqDataIn;
    uint32                          u4_DataLength;
    Std_ReturnType                  u1_RetReportReq;
    
    
    /* Set Subfunction in response data */
    ptMsgContext_temp->resData[DCM_DSP_SIDB9_SUBFUNC_BYTE] = u1SubFunc;
    /* Set Subfunction length in response length */
    ptMsgContext_temp->resDataLen = DCM_DSP_SIDB9_SUBFUNC_LEN;
    
    u4_DataLength = ptMsgContext_temp->resMaxDataLen - ptMsgContext_temp->resDataLen; /* no wrap around */
    
    /* Set Dcm_SIDExt03_ReqDataInType */
    Dcm_Dsp_SIDB9_SetReqDataIn( ptMsgContext_temp->reqData, u1SubFunc, &st_ReqDataIn );
    
    u1_RetReportReq = Dcm_Dsp_SIDB9_Obs_ReportRequest( u1SubFunc, 
                                             &st_ReqDataIn, 
                                             &u4_DataLength,
                                             &ptMsgContext_temp->resData[ptMsgContext_temp->resDataLen],
                                             ptErrorCode);
    
    if( u1_RetReportReq == (Std_ReturnType)E_OK )
    {
        if( ( ptMsgContext_temp->resMaxDataLen - ptMsgContext_temp->resDataLen ) >= u4_DataLength ) /* no wrap around */
        {
            ptMsgContext_temp->resDataLen += u4_DataLength; /* no wrap around */
            Dcm_Dsp_MsgMaker_SendPosRes( ptMsgContext_temp );
        }
        else
        {
            /* NRC 0x10 */
            *ptErrorCode = DCM_E_GENERALREJECT;
            *ptNrcFlag = (boolean)TRUE;
        }
    }
    else
    {
        *ptNrcFlag = (boolean)TRUE;
    }
    

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SIDB9_CancelProc                                 */
/* Description   | Cancel process of SID B9 request                         */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SIDB9_CancelProc
(
    void
)
{
    /* Set Dcm_Dsp_Main_bIdleFlag in TRUE  */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SIDB9_ReqLenMinChk                               */
/* Description   | Request message length Minimum check                     */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u4ReqDataLen        : Request Data Len              */
/*               | [IN] u1SubFunc           : Sub function                  */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                   : Check OK                      */
/*               |   E_NOT_OK               : Check NG                      */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SIDB9_ReqLenMinChk
(
    const Dcm_MsgLenType u4ReqDataLen,
    const uint8 u1SubFunc
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_NOT_OK;

    switch( u1SubFunc )
    {
        case DCM_DSP_SIDB9_SUB01:
        case DCM_DSP_SIDB9_SUB02:
        case DCM_DSP_SIDB9_SUB03:
        case DCM_DSP_SIDB9_SUB04:
        case DCM_DSP_SIDB9_SUB05:
            if( u4ReqDataLen >= ( DCM_DSP_SIDB9_MSGLEN_MIN + DCM_DSP_SIDB9_SYSID_LEN ) )
            {
                u1_RetVal = E_OK;
            }
            break;
        default:
            u1_RetVal = E_OK;
            break;
    }
    
    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SIDB9_SupportSubChk                              */
/* Description   | Support SubFunction Check                                */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1SubFunc           : Sub function                  */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                   : Check OK                      */
/*               |   E_NOT_OK               : Check NG                      */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SIDB9_SupportSubChk
(
    const uint8 u1SubFunc
)
{
    Std_ReturnType u1_RetVal;
   
    u1_RetVal = E_NOT_OK;
    
    switch( u1SubFunc )
    {
        case DCM_DSP_SIDB9_SUB01:
        case DCM_DSP_SIDB9_SUB02:
        case DCM_DSP_SIDB9_SUB03:
        case DCM_DSP_SIDB9_SUB04:
        case DCM_DSP_SIDB9_SUB05:
        case DCM_DSP_SIDB9_SUB06:
        case DCM_DSP_SIDB9_SUB07:
        case DCM_DSP_SIDB9_SUB08:
        case DCM_DSP_SIDB9_SUB09:
        case DCM_DSP_SIDB9_SUB0A:
            u1_RetVal = E_OK;
            break;
        default:
            /* No process */
            break;
    }
    
    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SIDB9_ReqMsgLenChk                               */
/* Description   | Request message length check                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u4ReqDataLen        : Request Data Len              */
/*               | [IN] u1SubFunc           : Sub function                  */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                   : Check OK                      */
/*               |   E_NOT_OK               : Check NG                      */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SIDB9_ReqMsgLenChk
(
    const Dcm_MsgLenType u4ReqDataLen,
    const uint8 u1SubFunc
)
{
    Std_ReturnType  u1_RetVal;
    uint8           u1_ChkLength;

    u1_RetVal = E_NOT_OK;

    switch( u1SubFunc )
    {
        case DCM_DSP_SIDB9_SUB02:
        case DCM_DSP_SIDB9_SUB08:
            u1_ChkLength = DCM_DSP_SIDB9_REQDATALEN_2BCHK;
            break;
        case DCM_DSP_SIDB9_SUB04:
            u1_ChkLength = DCM_DSP_SIDB9_REQDATALEN_4BCHK;
            break;
        case DCM_DSP_SIDB9_SUB05:
            u1_ChkLength = DCM_DSP_SIDB9_REQDATALEN_6BCHK;
            break;
        case DCM_DSP_SIDB9_SUB06:
            u1_ChkLength = DCM_DSP_SIDB9_REQDATALEN_1BCHK;
            break;
        case DCM_DSP_SIDB9_SUB0A:
            u1_ChkLength = DCM_DSP_SIDB9_REQDATALEN_5BCHK;
            break;
        default: /* SubFunction=0x01,0x03,0x07,0x09 */
            u1_ChkLength = DCM_DSP_SIDB9_REQDATALEN_3BCHK;
            break;
    }
    if( u4ReqDataLen == u1_ChkLength )
    {
        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SIDB9_SecLvChk                                   */
/* Description   | Active security level check                              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK                   : Check OK                      */
/*               |   E_NOT_OK               : Check NG                      */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SIDB9_SecLvChk
(
    void
)
{
    Std_ReturnType        u1_RetVal;
    Dcm_SecLevelType      u1_SecLevel;
    uint8                 u1_CurrentSecurityLevel;
    uint8                 u1_SecChkCnt;
    uint8                 u1_SecLvNum;
    boolean               b_SecLevelUsed;
    
    u1_RetVal = E_NOT_OK;

    b_SecLevelUsed = Dcm_Dsp_SIDB9_u1SecLevelUsed;
    if( b_SecLevelUsed == (boolean)TRUE )
    {
        ( void )Dcm_GetSecurityLevel( &u1_CurrentSecurityLevel );      /* no return check required */
        
        /* Support security level check */
        u1_SecLvNum = Dcm_Dsp_SIDB9_u1SecLvNum ;
        
        for( u1_SecChkCnt = (uint8)0U; u1_SecChkCnt < u1_SecLvNum; u1_SecChkCnt++ )
        {
            /* Get active security level */
            u1_SecLevel = Dcm_Dsp_SIDB9_u1SecLv_Tbl[u1_SecChkCnt];
            
            if( u1_CurrentSecurityLevel == u1_SecLevel )
            {
                u1_RetVal = E_OK;
                break;
            }
        }
    }
    else
    {
        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SIDB9_SetReqDataIn                               */
/* Description   | Request data setting                                     */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptReqData           : Request Data                  */
/*               | [IN] u1SubFunc           : Sub function                  */
/*               | [OUT] ptReqDataIn        : Request data In               */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC ( void, DCM_CODE ) Dcm_Dsp_SIDB9_SetReqDataIn
(
    P2CONST( Dcm_MsgItemType, AUTOMATIC, DCM_APPL_DATA ) ptReqData,
    const uint8 u1SubFunc,
    P2VAR( Dcm_SIDExt03_ReqDataInType, AUTOMATIC, DCM_APPL_DATA ) ptReqDataIn
)
{

    /* ReqDataIn Init */
    ptReqDataIn->u2SampleRecordNum = (uint16)0U;
    ptReqDataIn->u1SystemId        = DCM_DSP_SIDB9_SYSID_INVALID;
    ptReqDataIn->u1TriggerMode     = (uint8)0U;
    ptReqDataIn->u1BankNum         = (uint8)0U;
    ptReqDataIn->u1BlockNum        = (uint8)0U;

    switch( u1SubFunc )
    {
        case DCM_DSP_SIDB9_SUB01:
            ptReqDataIn->u1SystemId        = ptReqData[DCM_DSP_SIDB9_SF01_SYSIDBYTE];
            ptReqDataIn->u1TriggerMode     = ptReqData[DCM_DSP_SIDB9_SF01_TRIGGERBYTE];
            break;
        case DCM_DSP_SIDB9_SUB02:
            ptReqDataIn->u1SystemId        = ptReqData[DCM_DSP_SIDB9_SF02_SYSIDBYTE];
            break;
        case DCM_DSP_SIDB9_SUB03:
            ptReqDataIn->u1SystemId        = ptReqData[DCM_DSP_SIDB9_SF03_SYSIDBYTE];
            ptReqDataIn->u1BankNum         = ptReqData[DCM_DSP_SIDB9_SF03_BNKNUMBYTE];
            break;
        case DCM_DSP_SIDB9_SUB04:
            ptReqDataIn->u1SystemId        = ptReqData[DCM_DSP_SIDB9_SF04_SYSIDBYTE];
            ptReqDataIn->u1BankNum         = ptReqData[DCM_DSP_SIDB9_SF04_BNKNUMBYTE];
            ptReqDataIn->u1BlockNum        = ptReqData[DCM_DSP_SIDB9_SF04_BLKNUMBYTE];
            break;
        case DCM_DSP_SIDB9_SUB05:
            ptReqDataIn->u1SystemId        = ptReqData[DCM_DSP_SIDB9_SF05_SYSIDBYTE];
            ptReqDataIn->u1BankNum         = ptReqData[DCM_DSP_SIDB9_SF05_BNKNUMBYTE];
            ptReqDataIn->u1BlockNum        = ptReqData[DCM_DSP_SIDB9_SF05_BLKNUMBYTE];
            ptReqDataIn->u2SampleRecordNum = (uint16)((uint16)(ptReqData[DCM_DSP_SIDB9_SF05_SRNUMBYTE_H]) << DCM_DSP_SIDB9_REQDATA_SHIFT ) |
                                                      (uint16)(ptReqData[DCM_DSP_SIDB9_SF05_SRNUMBYTE_L]);
            break;
        case DCM_DSP_SIDB9_SUB06:
            break;
        case DCM_DSP_SIDB9_SUB07:
            ptReqDataIn->u1BankNum         = ptReqData[DCM_DSP_SIDB9_SF07_BNKNUMBYTE];
            ptReqDataIn->u1TriggerMode     = ptReqData[DCM_DSP_SIDB9_SF07_TRIGGERBYTE];
            break;
        case DCM_DSP_SIDB9_SUB08:
            ptReqDataIn->u1BankNum         = ptReqData[DCM_DSP_SIDB9_SF08_BNKNUMBYTE];
            break;
        case DCM_DSP_SIDB9_SUB09:
            ptReqDataIn->u1BankNum         = ptReqData[DCM_DSP_SIDB9_SF09_BNKNUMBYTE];
            ptReqDataIn->u1BlockNum        = ptReqData[DCM_DSP_SIDB9_SF09_BLKNUMBYTE];
            break;
        default:  /* SubFunction=0x0A */
            ptReqDataIn->u1BankNum         = ptReqData[DCM_DSP_SIDB9_SF0A_BNKNUMBYTE];
            ptReqDataIn->u1BlockNum        = ptReqData[DCM_DSP_SIDB9_SF0A_BLKNUMBYTE];
            ptReqDataIn->u2SampleRecordNum = (uint16)((uint16)(ptReqData[DCM_DSP_SIDB9_SF0A_SRNUMBYTE_H]) << DCM_DSP_SIDB9_REQDATA_SHIFT ) |
                                                      (uint16)(ptReqData[DCM_DSP_SIDB9_SF0A_SRNUMBYTE_L]);
            break;
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SIDB9_GetSystemId                                */
/* Description   | Get SystemID from RequestMsg                             */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptReqData           : Request Data                  */
/*               | [IN] u1SubFunc           : Sub function                  */
/*               | [OUT] ptSystemId         : SystemIdentifier              */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE) Dcm_Dsp_SIDB9_GetSystemId
(
    P2CONST( Dcm_MsgItemType, AUTOMATIC, DCM_APPL_DATA ) ptReqData,
    const uint8 u1SubFunc,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA) ptSystemId
)
{
    
    switch( u1SubFunc )
    {
        case DCM_DSP_SIDB9_SUB01:
        case DCM_DSP_SIDB9_SUB02:
        case DCM_DSP_SIDB9_SUB03:
        case DCM_DSP_SIDB9_SUB04:
        case DCM_DSP_SIDB9_SUB05:
            *ptSystemId = ptReqData[DCM_DSP_SIDB9_SYSID_BYTE];
            break;
        default:
            *ptSystemId = DCM_DSP_SIDB9_SYSID_INVALID;
            break;
    }

    return;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

#endif /* DCM_SUPPORT_SIDB9 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-09-26                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
