/* Dcm_Dsp_SID06_c(v5-0-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID06/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

#if ( DCM_OBDTYPE_TYPE_OBD == STD_ON )
#if ( DCM_SUPPORT_SID06 == STD_ON )

#include "../../Dsp/cfg/Dcm_Dsp_SID06_Cfg.h"
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Dsp_SID06.h>
#include <Dcm/Dcm_Dsp_Main.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SID06_REQ_DATA_LEN_MIN     ( (Dcm_MsgLenType)1U )
#define DCM_DSP_SID06_REQ_DATA_LEN_MAX     ( (Dcm_MsgLenType)6U )

#define DCM_DSP_SID06_OBDMID_MASK          ( (uint8)0x1FU )

#define DCM_DSP_SID06_OBDMIDKIND_SUP       ( (uint8)0x00U )
#define DCM_DSP_SID06_OBDMIDKIND_NORMAL    ( (uint8)0x01U )

#define DCM_DSP_SID06_OBDMID_LEN           ( (Dcm_MsgLenType)1U )
#define DCM_DSP_SID06_SUPOBDMID_LEN        ( (Dcm_MsgLenType)4U )

#define DCM_DSP_SID06_READ_DATA_NONE       ( (uint8)0x00U )
#define DCM_DSP_SID06_READ_DATA_OK         ( (uint8)0x01U )
#define DCM_DSP_SID06_READ_OVER_FLOW       ( (uint8)0x02U )

#define DCM_DSP_SID06_DTRDATA_NUM          ( (uint8)9U )

#define DCM_DSP_SID06_BITSHIFT_8           ( (uint8)8U )
#define DCM_DSP_SID06_BITSHIFT_16          ( (uint8)16U )
#define DCM_DSP_SID06_BITSHIFT_24          ( (uint8)24U )

#define DCM_DSP_SID06_REQ_DATA_POS_0       ( (uint8)0U )

#define DCM_DSP_SID06_RES_POS_SUP1         ( (uint8)1U )
#define DCM_DSP_SID06_RES_POS_SUP2         ( (uint8)2U )
#define DCM_DSP_SID06_RES_POS_SUP3         ( (uint8)3U )
#define DCM_DSP_SID06_RES_POS_SUP4         ( (uint8)4U )

#define DCM_DSP_SID06_RES_POS_TIDVAL       ( (uint8)1U )
#define DCM_DSP_SID06_RES_POS_UASID        ( (uint8)2U )
#define DCM_DSP_SID06_RES_POS_TESTVAL_H    ( (uint8)3U )
#define DCM_DSP_SID06_RES_POS_TESTVAL_L    ( (uint8)4U )
#define DCM_DSP_SID06_RES_POS_LLIMVAL_H    ( (uint8)5U )
#define DCM_DSP_SID06_RES_POS_LLIMVAL_L    ( (uint8)6U )
#define DCM_DSP_SID06_RES_POS_ULIMVAL_H    ( (uint8)7U )
#define DCM_DSP_SID06_RES_POS_ULIMVAL_L    ( (uint8)8U )


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID06_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID06_CancelProc
(
    void
);
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_SID06_CheckObdmidKind
(
    const uint8 u1ReqObdmid
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID06_MakeDTRData
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext_temp,
    const uint8 u1ReqObdmid,
    const uint8 u1NumberOfTIDs
);
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_SID06_MakeObdmidSupData
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext_temp,
    const uint8 u1ReqObdmid
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
/* Function Name | Dcm_SID06                                                */
/* Description   | SID06 request processing                                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus        : Operation state                   */
/*               | [IN] pMsgContext     : Message Context                   */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK               : Processing normal                 */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID06 /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = (Std_ReturnType)E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID06_InitialProc( pMsgContext );
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        Dcm_Dsp_SID06_CancelProc();
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
/* Function Name | Dcm_Dsp_SID06_InitialProc                                */
/* Description   | Initial process of SID06 request                         */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext    : Message Context                   */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK               : Processing normal                 */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Std_ReturnType, DCM_CODE ) Dcm_Dsp_SID06_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Dcm_MsgContextType           st_MsgContext_temp;
    Std_ReturnType               u1_RetVal;
    Dcm_NegativeResponseCodeType u1_ErrorCode;
    uint8                        u1_MakeResDataResult;
    uint8                        u1_ReqObdmidKind;
    uint8                        u1_ReqObdmidNum;
    uint8                        u1_TidNum;
    Dcm_MsgItemType              u1_ReqData;

    u1_ErrorCode = (Dcm_NegativeResponseCodeType)0x00U;
    st_MsgContext_temp = *ptMsgContext;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    /* Request Data Length Check */
    if( ( st_MsgContext_temp.reqDataLen >= DCM_DSP_SID06_REQ_DATA_LEN_MIN ) &&
        ( st_MsgContext_temp.reqDataLen <= DCM_DSP_SID06_REQ_DATA_LEN_MAX ) )
    {
        /* Initialize Reaponse Data Length */
        st_MsgContext_temp.resDataLen = (Dcm_MsgLenType)0U;

        /* Get Top Obdmid Kind */
        u1_ReqData = st_MsgContext_temp.reqData[DCM_DSP_SID06_REQ_DATA_POS_0];
        u1_ReqObdmidKind = Dcm_Dsp_SID06_CheckObdmidKind( u1_ReqData );

        if( u1_ReqObdmidKind == DCM_DSP_SID06_OBDMIDKIND_SUP )
        {
            /* Process for Support Obdmid */
            for( u1_ReqObdmidNum = (uint8)0U; u1_ReqObdmidNum < (uint8)st_MsgContext_temp.reqDataLen; u1_ReqObdmidNum++ )
            {
                u1_ReqData = st_MsgContext_temp.reqData[u1_ReqObdmidNum];
                u1_ReqObdmidKind = Dcm_Dsp_SID06_CheckObdmidKind( u1_ReqData );
                /* Mixed Obdmid Check */
                if( u1_ReqObdmidKind == DCM_DSP_SID06_OBDMIDKIND_SUP )
                {
                    u1_MakeResDataResult = Dcm_Dsp_SID06_MakeObdmidSupData( &st_MsgContext_temp, u1_ReqData );
                    if( u1_MakeResDataResult == DCM_DSP_SID06_READ_OVER_FLOW )
                    {
                        /* NRC0x14 */
                        u1_ErrorCode = DCM_E_RESPONSETOOLONG;
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
            /* Request Data Length Check for Normal Obdmid */
            if( st_MsgContext_temp.reqDataLen == DCM_DSP_SID06_REQ_DATA_LEN_MIN )
            {
                /* Obdmid Support Check */
                u1_RetVal = Dcm_Dsp_SID06_GetNumTIDsOfOBDMID( u1_ReqData, &u1_TidNum );
                if( u1_RetVal == (Std_ReturnType)E_OK )
                {
                    /* Check Tid Num */
                    if( u1_TidNum > (uint8)0 )
                    {
                        if( (uint32)( (uint32)u1_TidNum * (uint32)DCM_DSP_SID06_DTRDATA_NUM ) <= st_MsgContext_temp.resMaxDataLen ) /* no wrap around */
                        {
                            Dcm_Dsp_SID06_MakeDTRData( &st_MsgContext_temp, u1_ReqData, u1_TidNum );
                        }
                        else
                        {
                            /* NRC0x14 */
                            u1_ErrorCode = DCM_E_RESPONSETOOLONG;
                        }
                    }
                    else
                    {
                        /* NRC0x31 */
                        u1_ErrorCode = DCM_E_REQUESTOUTOFRANGE;
                    }
                }
                else
                {
                    /* NRC0x31 */
                    u1_ErrorCode = DCM_E_REQUESTOUTOFRANGE;
                }
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
/* Function Name | Dcm_Dsp_SID06_CancelProc                                 */
/* Description   | Cancel process of SID06 request                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID06_CancelProc
(
    void
)
{
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID06_CheckObdmidKind                            */
/* Description   | Check Obdmid Kind SupportObdmid or NormalObdmid          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1ReqObdmid                  : Request Obdmid       */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_SID06_OBDMIDKIND_SUP    : Support Obdmid       */
/*               |   DCM_DSP_SID06_OBDMIDKIND_NORMAL : Normal Obdmid        */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_SID06_CheckObdmidKind
(
    const uint8 u1ReqObdmid
)
{
    uint8 u1_ObdmidKind;

    u1_ObdmidKind = DCM_DSP_SID06_OBDMIDKIND_NORMAL;

    if( (uint8)( u1ReqObdmid & DCM_DSP_SID06_OBDMID_MASK ) == DCM_DSP_SID06_OBDMIDKIND_SUP )
    {
        u1_ObdmidKind = DCM_DSP_SID06_OBDMIDKIND_SUP;
    }

    return u1_ObdmidKind;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID06_MakeDTRData                                */
/* Description   | Make DTR Data                                            */
/* Preconditions | None                                                     */
/* Parameters    | [IN/OUT] ptMsgContext_temp  : Msg Context                */
/*               | [IN] u1ReqObdmid            : Request Obdmid             */
/*               | [IN] u1NumberOfTIDs         : number of TID.             */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID06_MakeDTRData
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext_temp,
    const uint8 u1ReqObdmid,
    const uint8 u1NumberOfTIDs
)
{
    Dcm_MsgLenType     u4_ResDataLen;
    uint16             u2_Testvalue;
    uint16             u2_Lowlimvalue;
    uint16             u2_Upplimvalue;
    uint8              u1_TIDvalue;
    uint8              u1_UaSID;
    uint8              u1_Cnt;
    Std_ReturnType     u1_RetVal;

    u4_ResDataLen = ptMsgContext_temp->resDataLen;

    for( u1_Cnt = (uint8)0U; u1_Cnt < u1NumberOfTIDs; u1_Cnt++ )
    {
        u1_TIDvalue = (uint8)0;
        u1_UaSID = (uint8)0;
        u2_Testvalue = (uint16)0;
        u2_Lowlimvalue = (uint16)0;
        u2_Upplimvalue = (uint16)0;

        u1_RetVal = Dcm_Dsp_SID06_GetDTRData( u1ReqObdmid, u1_Cnt, &u1_TIDvalue, &u1_UaSID, &u2_Testvalue, &u2_Lowlimvalue, &u2_Upplimvalue );
        if( u1_RetVal == (Std_ReturnType)E_OK )
        {
            ptMsgContext_temp->resData[u4_ResDataLen] = u1ReqObdmid;
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID06_RES_POS_TIDVAL] = u1_TIDvalue; /* no wrap around */
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID06_RES_POS_UASID]  = u1_UaSID;    /* no wrap around */
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID06_RES_POS_TESTVAL_H] =   /* no wrap around */
                (Dcm_MsgItemType)( u2_Testvalue >> DCM_DSP_SID06_BITSHIFT_8 );
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID06_RES_POS_TESTVAL_L] =   /* no wrap around */
                (Dcm_MsgItemType)u2_Testvalue;
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID06_RES_POS_LLIMVAL_H] =   /* no wrap around */
                (Dcm_MsgItemType)( u2_Lowlimvalue >> DCM_DSP_SID06_BITSHIFT_8 );
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID06_RES_POS_LLIMVAL_L] =   /* no wrap around */
                (Dcm_MsgItemType)u2_Lowlimvalue;
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID06_RES_POS_ULIMVAL_H] =   /* no wrap around */
                (Dcm_MsgItemType)( u2_Upplimvalue >> DCM_DSP_SID06_BITSHIFT_8 );
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID06_RES_POS_ULIMVAL_L] =   /* no wrap around */
                (Dcm_MsgItemType)u2_Upplimvalue;
        }
        else
        {
            ptMsgContext_temp->resData[u4_ResDataLen] = u1ReqObdmid;
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID06_RES_POS_TIDVAL]     = (uint8)0;    /* no wrap around */
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID06_RES_POS_UASID]      = (uint8)0;    /* no wrap around */
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID06_RES_POS_TESTVAL_H]  = (uint8)0;    /* no wrap around */
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID06_RES_POS_TESTVAL_L]  = (uint8)0;    /* no wrap around */
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID06_RES_POS_LLIMVAL_H]  = (uint8)0;    /* no wrap around */
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID06_RES_POS_LLIMVAL_L]  = (uint8)0;    /* no wrap around */
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID06_RES_POS_ULIMVAL_H]  = (uint8)0;    /* no wrap around */
            ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID06_RES_POS_ULIMVAL_L]  = (uint8)0;    /* no wrap around */
        }
        u4_ResDataLen += DCM_DSP_SID06_DTRDATA_NUM; /* no wrap around */
    }
    ptMsgContext_temp->resDataLen = u4_ResDataLen;

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID06_MakeObdmidSupData                          */
/* Description   | Make Obdmid Support Data                                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN/OUT] ptMsgContext_temp     : Msg Context             */
/*               | [IN] u1ReqObdmid               : Request Obdmid          */
/* Return Value  | uint8                                                    */
/*               |   DCM_DSP_SID06_READ_DATA_NONE : Read Data None          */
/*               |   DCM_DSP_SID06_READ_DATA_OK   : Read Data OK            */
/*               |   DCM_DSP_SID06_READ_OVER_FLOW : Read Over Flow          */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( uint8, DCM_CODE ) Dcm_Dsp_SID06_MakeObdmidSupData
(
    P2VAR( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext_temp,
    const uint8 u1ReqObdmid
)
{
    Dcm_MsgLenType u4_ResDataLen;
    uint32         u4_ObdmidSupportInfo;
    uint8          u1_Result;
    Std_ReturnType u1_RetGetAvail;

    u4_ObdmidSupportInfo = ((uint32)0U);
    u4_ResDataLen = ptMsgContext_temp->resDataLen;
    u1_Result = DCM_DSP_SID06_READ_DATA_NONE;

    u1_RetGetAvail = Dcm_Dsp_SID06_GetAvailableOBDMIDs( u1ReqObdmid, &u4_ObdmidSupportInfo );
    if( u1_RetGetAvail == (Std_ReturnType)E_OK )
    {
        if( u4_ObdmidSupportInfo != ((uint32)0U) )
        {
            /* Buffer Over Flow Check */
            if( ( u4_ResDataLen + DCM_DSP_SID06_OBDMID_LEN + DCM_DSP_SID06_SUPOBDMID_LEN ) <= ptMsgContext_temp->resMaxDataLen )    /* no wrap around */
            {
                ptMsgContext_temp->resData[u4_ResDataLen] = u1ReqObdmid;
                ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID06_RES_POS_SUP1] =    /* no wrap around */
                    (Dcm_MsgItemType)( u4_ObdmidSupportInfo >> DCM_DSP_SID06_BITSHIFT_24 );
                ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID06_RES_POS_SUP2] =    /* no wrap around */
                    (Dcm_MsgItemType)( u4_ObdmidSupportInfo >> DCM_DSP_SID06_BITSHIFT_16 );
                ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID06_RES_POS_SUP3] =    /* no wrap around */
                    (Dcm_MsgItemType)( u4_ObdmidSupportInfo >> DCM_DSP_SID06_BITSHIFT_8 );
                ptMsgContext_temp->resData[u4_ResDataLen + DCM_DSP_SID06_RES_POS_SUP4] =    /* no wrap around */
                    (Dcm_MsgItemType)u4_ObdmidSupportInfo;
                ptMsgContext_temp->resDataLen += DCM_DSP_SID06_OBDMID_LEN + DCM_DSP_SID06_SUPOBDMID_LEN;    /* no wrap around */
                u1_Result = DCM_DSP_SID06_READ_DATA_OK;
            }
            else
            {
                u1_Result = DCM_DSP_SID06_READ_OVER_FLOW;
            }
        }
    }

    return u1_Result;
}


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID06 == STD_ON */
#endif /* DCM_OBDTYPE_TYPE_OBD */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
