/* Dcm_Dsp_SID19_Sub56(v5-3-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID19_Sub56/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID19_Sub56.h>
#if ( DCM_SUPPORT_SID19_SUB56 == STD_ON )
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dem_Dcm.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     DCM_DSP_SID19_SUB56_SHFT_DTC_HI                 ((uint8)16U)
#define     DCM_DSP_SID19_SUB56_SHFT_DTC_MI                 ((uint8)8U)
#define     DCM_DSP_SID19_SUB56_FGID_VALID_VAL              ((uint8)0x33U)
#define     DCM_DSP_SID19_SUB56_DTC_RGID_INVALID_VAL        ((uint8)0xFFU)
#define     DCM_DSP_SID19_SUB56_DTC_ST_MSK_00               ((uint8)0x00U)
#define     DCM_DSP_SID19_SUB56_FGID_LEN                    ((Dcm_MsgLenType)1U)
#define     DCM_DSP_SID19_SUB56_DTC_RGID_LEN                ((Dcm_MsgLenType)1U)
#define     DCM_DSP_SID19_SUB56_DTC_ST_AVAIL_MSK_LEN        ((Dcm_MsgLenType)1U)
#define     DCM_DSP_SID19_SUB56_DTC_FORMAT_ID_LEN           ((Dcm_MsgLenType)1U)
#define     DCM_DSP_SID19_SUB56_DTC_LEN                     ((Dcm_MsgLenType)3U)
#define     DCM_DSP_SID19_SUB56_DTC_ST_LEN                  ((Dcm_MsgLenType)1U)
#define     DCM_DSP_SID19_SUB56_DTC_DASR_LEN                ((Dcm_MsgLenType)(DCM_DSP_SID19_SUB56_DTC_LEN + DCM_DSP_SID19_SUB56_DTC_ST_LEN))
#define     DCM_DSP_SID19_SUB56_REQ_OFFSET_FGID             ((uint32)0U)
#define     DCM_DSP_SID19_SUB56_REQ_OFFSET_DTC_RGID         ((uint32)1U)
#define     DCM_DSP_SID19_SUB56_REQ_DATA_LEN                (DCM_DSP_SID19_SUB56_FGID_LEN + DCM_DSP_SID19_SUB56_DTC_RGID_LEN)
#define     DCM_DSP_SID19_SUB56_RES_OFFSET_FGID             ((uint32)0U)
#define     DCM_DSP_SID19_SUB56_RES_OFFSET_DTC_ST_AVAIL_MSK ((uint32)1U)
#define     DCM_DSP_SID19_SUB56_RES_OFFSET_DTC_FORMAT_ID    ((uint32)2U)
#define     DCM_DSP_SID19_SUB56_RES_OFFSET_DTC_RGID         ((uint32)3U)
#define     DCM_DSP_SID19_SUB56_RES_DATA_MIN_LEN            ((Dcm_MsgLenType)(DCM_DSP_SID19_SUB56_FGID_LEN + DCM_DSP_SID19_SUB56_DTC_ST_AVAIL_MSK_LEN + DCM_DSP_SID19_SUB56_DTC_FORMAT_ID_LEN + DCM_DSP_SID19_SUB56_DTC_RGID_LEN))


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub56_ChkReqParams
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
);

static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub56_GetDTC
(
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
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
/* Function Name | Dcm_SID19_Sub56                                          */
/* Description   | Request processing of SID19_Sub56                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus    : Operation state                       */
/*               | [IN] pMsgContext : Message Context                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK           : Processing normal                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SID19_Sub56
(
    Dcm_OpStatusType OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
)
{
    Dcm_MsgContextType              st_MsgContext_temp;
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    Dem_UdsStatusByteType           u1_DTCStatusMask;
    Dem_ReturnSetFilterType         u1_RetSetFilter;
    Dem_DTCTranslationFormatType    u1_DTCFormamt;
    Std_ReturnType                  u1_RetStatusAvailabilityMask;
    Std_ReturnType                  u1_RetChkReqParams;
    boolean                         b_SendNegResFlag;

    u1_NegResCode    = DCM_E_GENERALREJECT;
    b_SendNegResFlag = (boolean)FALSE;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
        st_MsgContext_temp = *pMsgContext;

        if( st_MsgContext_temp.reqDataLen == DCM_DSP_SID19_SUB56_REQ_DATA_LEN )
        {
            if( st_MsgContext_temp.resMaxDataLen >= DCM_DSP_SID19_SUB56_RES_DATA_MIN_LEN )
            {
                u1_RetChkReqParams = Dcm_Dsp_SID19_Sub56_ChkReqParams( &st_MsgContext_temp );
                if( u1_RetChkReqParams == (Std_ReturnType)E_OK )
                {
                    u1_DTCStatusMask = DCM_DSP_SID19_SUB56_DTC_ST_MSK_00;
                    u1_RetStatusAvailabilityMask = Dem_DcmGetDTCStatusAvailabilityMask( &u1_DTCStatusMask,
                                                                                        DEM_DTC_ORIGIN_PRIMARY_MEMORY );
                    if( u1_RetStatusAvailabilityMask == (Std_ReturnType)E_OK )
                    {
                        u1_DTCFormamt = Dem_DcmGetTranslationType();
                        if( ( u1_DTCFormamt == DEM_DTC_TRANSLATION_SAEJ1939_73 ) ||
                            ( u1_DTCFormamt == DEM_DTC_TRANSLATION_J2012DA_FORMAT_04 ) )
                        {
                            u1_RetSetFilter = Dem_DcmSetDTCFilterForReadiness( st_MsgContext_temp.reqData[DCM_DSP_SID19_SUB56_REQ_OFFSET_DTC_RGID] );

                            if( u1_RetSetFilter == DEM_FILTER_ACCEPTED )
                            {
                                /* Set FunctionalGroupIdentifier */
                                st_MsgContext_temp.resData[DCM_DSP_SID19_SUB56_RES_OFFSET_FGID] = st_MsgContext_temp.reqData[DCM_DSP_SID19_SUB56_REQ_OFFSET_FGID];
                                /* Set DTCStatusAvailableMask */
                                st_MsgContext_temp.resData[DCM_DSP_SID19_SUB56_RES_OFFSET_DTC_ST_AVAIL_MSK] = (Dcm_MsgItemType)u1_DTCStatusMask;
                                /* Set DTCFormatIdentifier */
                                st_MsgContext_temp.resData[DCM_DSP_SID19_SUB56_RES_OFFSET_DTC_FORMAT_ID] = (Dcm_MsgItemType)u1_DTCFormamt;
                                /* Set DTCReadinessGroupIdentifier */
                                st_MsgContext_temp.resData[DCM_DSP_SID19_SUB56_RES_OFFSET_DTC_RGID] = st_MsgContext_temp.reqData[DCM_DSP_SID19_SUB56_REQ_OFFSET_DTC_RGID];

                                st_MsgContext_temp.resDataLen = DCM_DSP_SID19_SUB56_FGID_LEN + 
                                                                DCM_DSP_SID19_SUB56_DTC_ST_AVAIL_MSK_LEN + 
                                                                DCM_DSP_SID19_SUB56_DTC_FORMAT_ID_LEN + 
                                                                DCM_DSP_SID19_SUB56_DTC_RGID_LEN;

                                Dcm_Dsp_SID19_Sub56_GetDTC( &st_MsgContext_temp );
                            }
                            else if( u1_RetSetFilter == DEM_WRONG_FILTER )
                            {
                                u1_NegResCode = DCM_E_REQUESTOUTOFRANGE;
                                b_SendNegResFlag = (boolean)TRUE;
                            }
                            else
                            {
                                /* Default u1_NegResCode is DCM_E_GENERALREJECT */
                                b_SendNegResFlag = (boolean)TRUE;
                            }
                        }
                        else
                        {
                            /* Default u1_NegResCode is DCM_E_GENERALREJECT */
                            b_SendNegResFlag = (boolean)TRUE;
                        }
                    }
                    else
                    {
                        /* Default u1_NegResCode is DCM_E_GENERALREJECT */
                        b_SendNegResFlag = (boolean)TRUE;
                    }
                }
                else
                {
                    u1_NegResCode = DCM_E_REQUESTOUTOFRANGE;
                    b_SendNegResFlag = (boolean)TRUE;
                }
            }
            else
            {
                u1_NegResCode = DCM_E_RESPONSETOOLONG;
                b_SendNegResFlag = (boolean)TRUE;
            }
        }
        else
        {
            u1_NegResCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            b_SendNegResFlag = (boolean)TRUE;
        }

        if( b_SendNegResFlag == (boolean)TRUE )
        {
            Dcm_Dsp_MsgMaker_SendNegRes( &st_MsgContext_temp,
                                         u1_NegResCode );
        }
    }

    return E_OK;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub56_ChkReqParams                         */
/* Description   | Check Parameters of SID19_Sub56 request                  */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext : Message Context                      */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK            : Parameters Check OK                  */
/*               |   E_NOT_OK        : Parameters Check NG                  */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub56_ChkReqParams
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = E_NOT_OK;

    if( ptMsgContext->reqData[DCM_DSP_SID19_SUB56_REQ_OFFSET_FGID] == DCM_DSP_SID19_SUB56_FGID_VALID_VAL )
    {
        if( ptMsgContext->reqData[DCM_DSP_SID19_SUB56_REQ_OFFSET_DTC_RGID] != DCM_DSP_SID19_SUB56_DTC_RGID_INVALID_VAL )
        {
            u1_RetVal = E_OK;
        }
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub56_GetDTC                               */
/* Description   | Get DTC and Edit Response or Register Event              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext : Message Context                      */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub56_GetDTC
(
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    uint32                                  u4_DTC;
    Dcm_MsgLenType                          u4_ResDataPos;
    Dem_UdsStatusByteType                   u1_DTCStatus;
    Dem_ReturnGetNextFilteredElementType    u1_RetNextDTC;
    Dcm_NegativeResponseCodeType            u1_NegResCode;
    boolean                                 b_LoopEnd;
    boolean                                 b_SendPosRes;

    b_LoopEnd     = (boolean)FALSE;
    b_SendPosRes  = (boolean)FALSE;
    u1_DTCStatus  = (Dem_UdsStatusByteType)0U;
    u1_NegResCode = DCM_E_GENERALREJECT;
    u4_DTC        = (uint32)0U;

    while( b_LoopEnd == (boolean)FALSE )
    {
        u1_RetNextDTC = Dem_DcmGetNextFilteredDTCForReadiness( &u4_DTC,
                                                               &u1_DTCStatus );
        switch( u1_RetNextDTC )
        {
            case DEM_FILTERED_OK:

                if( (ptMsgContext->resMaxDataLen - ptMsgContext->resDataLen) >= DCM_DSP_SID19_SUB56_DTC_DASR_LEN )    /* no wrap around */
                {
                    /* DTC Data Set */
                    u4_ResDataPos = ptMsgContext->resDataLen;
                    /* Set DTCHighByte */
                    ptMsgContext->resData[u4_ResDataPos] = (uint8)(u4_DTC >> DCM_DSP_SID19_SUB56_SHFT_DTC_HI);
                    u4_ResDataPos++;    /* no wrap around */
                    /* Set DTCMiddleByte */
                    ptMsgContext->resData[u4_ResDataPos] = (uint8)(u4_DTC >> DCM_DSP_SID19_SUB56_SHFT_DTC_MI);
                    u4_ResDataPos++;    /* no wrap around */
                    /* Set DTCLowByte */
                    ptMsgContext->resData[u4_ResDataPos] = (uint8)(u4_DTC);
                    u4_ResDataPos++;    /* no wrap around */
                    /* Set statusOfDTC */
                    ptMsgContext->resData[u4_ResDataPos] = u1_DTCStatus;

                    ptMsgContext->resDataLen += DCM_DSP_SID19_SUB56_DTC_DASR_LEN;   /* no wrap around */
                }
                else
                {
                    b_LoopEnd = (boolean)TRUE;
                    u1_NegResCode = DCM_E_RESPONSETOOLONG;
                }
                break;
            case DEM_FILTERED_NO_MATCHING_ELEMENT:
                b_LoopEnd = (boolean)TRUE;
                b_SendPosRes = (boolean)TRUE;
                break;
            default:
                b_LoopEnd = (boolean)TRUE;
                /* Default u1_NegResCode is DCM_E_GENERALREJECT */
                break;
        }
    }/* while End */

    if( b_SendPosRes == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendPosRes( ptMsgContext );
    }
    else
    {
        Dcm_Dsp_MsgMaker_SendNegRes( ptMsgContext,
                                     u1_NegResCode );
    }

    return;
}


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID19_SUB56 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-2-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
