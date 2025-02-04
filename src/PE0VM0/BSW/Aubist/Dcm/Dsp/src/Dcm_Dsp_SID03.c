/* Dcm_Dsp_SID03_c(v5-3-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID03/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm.h>

#if ( DCM_OBDTYPE_TYPE_OBD == STD_ON )
#if ( DCM_SUPPORT_SID03 == STD_ON )

#include <Dcm/Dcm_Dsp_SID03.h>
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dem_Dcm.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     DCM_DSP_SID03_ShftDTCHi         ( (uint32)8U )
#define     DCM_DSP_SID03_ResOffDTCHi       ( (uint8)0U )
#define     DCM_DSP_SID03_ResOffDTCLo       ( (uint8)1U )
#define     DCM_DSP_SID03_DTCLen            ( (Dcm_MsgLenType)2U )
#define     DCM_DSP_SID03_ReqDataLength     ( (Dcm_MsgLenType)0U )
#define     DCM_DSP_SID03_DASRLen           ( DCM_DSP_SID03_DTCLen )

#define     DCM_DSP_SID03_DTCNumMax         ( (uint8)127U )
#define     DCM_DSP_SID03_DTCStatusMask     ( (uint8)0x08U )
#define     DCM_DSP_SID03_DTCWriteStart     ( (Dcm_MsgLenType)0x01U )
#define     DCM_DSP_SID03_DTCNumberWrite    ( (Dcm_MsgLenType)0x00U )

#define     DCM_DSP_SID03_POSITIVE_RESP     ( (uint8)0U )
#define     DCM_DSP_SID03_NEGATIVE_RESP     ( (uint8)1U )
/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID03_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
);
static FUNC(void, DCM_CODE) Dcm_Dsp_SID03_CancelProc
( void );
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID03_GetDTC
(
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext_temp
);

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID03_WriteResDtc
(
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext_temp,
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) ptDtcAndStatusRecord
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
/* Function Name | Dcm_SID03                                                */
/* Description   | <Module>_<DiagnosticService>_<SubService>                */
/* Preconditions |                                                          */
/* Parameters    | [IN]   Dcm_OpStatusType             : OpStatus           */
/*               | [IN]   const Dcm_MsgContextType*    : pMsgContext        */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK          0x00                                       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SID03 /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
)
{
    Std_ReturnType          u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID03_InitialProc( pMsgContext );
        /* This Return Value is check-free */
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        Dcm_Dsp_SID03_CancelProc();
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
/* Function Name | Dcm_Dsp_SID03_InitialProc                                */
/* Description   | SID03                                                    */
/* Preconditions |                                                          */
/* Parameters    | [IN]   const Dcm_MsgContextType*    : ptMsgContext       */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK          0x00                                       */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID03_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    boolean                      b_SendNegResFlag;
    Std_ReturnType               u1_RetVal;
    Dcm_NegativeResponseCodeType u1_NegResCode;
    Dem_ReturnSetFilterType      u1_RetSetFilter;
    Dcm_MsgContextType           st_MsgContext_temp;


    u1_RetVal = (Std_ReturnType)E_OK;
    b_SendNegResFlag = (boolean)FALSE;
    st_MsgContext_temp = *ptMsgContext;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    if( st_MsgContext_temp.reqDataLen == (Dcm_MsgLenType)DCM_DSP_SID03_ReqDataLength  )
    {
        st_MsgContext_temp.resDataLen = DCM_DSP_SID03_DTCWriteStart;
        u1_RetSetFilter = Dem_DcmSetDTCFilter( DCM_DSP_SID03_DTCStatusMask,
                                               DEM_DTC_KIND_EMISSION_REL_DTCS,
                                               DEM_DTC_FORMAT_OBD,
                                               DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                               (boolean)FALSE,
                                               DEM_SEVERITY_NO_SEVERITY,
                                               (boolean)FALSE
                                               );
        if( u1_RetSetFilter == (Dem_ReturnSetFilterType)DEM_FILTER_ACCEPTED )
        {
            u1_RetVal = Dcm_Dsp_SID03_GetDTC( &st_MsgContext_temp );
            /* This Return Value is check-free */
        }
        else
        {
        /* This Route                                       */
        /* Status OUT of RANGE    -> 0x31                   */
           u1_NegResCode    = DCM_E_REQUESTOUTOFRANGE;
           b_SendNegResFlag = (boolean)TRUE;
        }

    }
    else
    {
        /* This Route                                                       */
        /*   Request Length Check NG    -> 0x13                             */
        u1_NegResCode    = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        b_SendNegResFlag = (boolean)TRUE;
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &st_MsgContext_temp, u1_NegResCode );
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;

}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID03_CancelProc                                 */
/* Description   | Receive Cancel request and Set Cancel Flag               */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID03_CancelProc
( void )
{
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );
    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID03_GetDTC                                     */
/* Description   | Get DTC and Edit Response or Register Event              */
/* Preconditions |                                                          */
/* Parameters    | [IN/OUT]   Dcm_MsgContextType*    : ptMsgContext_temp    */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK          0x00                                       */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID03_GetDTC
(
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext_temp
)
{
    Std_ReturnType                       u1_RetVal;
    Std_ReturnType                       u1_RetWriteDtc;
    uint32                               u4_DTC;
    Dem_UdsStatusByteType                u1_DtcStatus;
    Dem_ReturnGetNextFilteredElementType u1_RetNextDtc;
    boolean                              b_LoopEnd;
    uint8                                u1_DTCInfo[DCM_DSP_SID03_DASRLen];
    Dcm_NegativeResponseCodeType         u1_NegResCode;
    uint8                                u1_SendResKind;
    uint8                                u1_DTCNumber;

    u1_RetVal        = (Std_ReturnType)E_OK;
    u1_SendResKind   = DCM_DSP_SID03_POSITIVE_RESP;
    u1_DtcStatus     = (Dem_UdsStatusByteType)0U;
    b_LoopEnd        = (boolean)FALSE;
    u1_NegResCode    = (Dcm_NegativeResponseCodeType)0U;
    u1_DTCNumber     = (uint8)0U;
    u1_DTCInfo[DCM_DSP_SID03_ResOffDTCHi] = (uint8)0U;
    u1_DTCInfo[DCM_DSP_SID03_ResOffDTCLo] = (uint8)0U;

    while( ( b_LoopEnd == (boolean)FALSE ) && ( u1_DTCNumber < DCM_DSP_SID03_DTCNumMax ) )
    {
        u1_RetNextDtc = Dem_DcmGetNextFilteredDTC( &u4_DTC, &u1_DtcStatus );
        switch( u1_RetNextDtc )
        {
            case DEM_FILTERED_OK :
                /* Set u4_DTC(bit08-bit15) to u1_DTCInfo[0]                 */
                u1_DTCInfo[DCM_DSP_SID03_ResOffDTCHi] = (uint8)( u4_DTC >> DCM_DSP_SID03_ShftDTCHi );
                /* Set u4_DTC(bit00-bit07) to u1_DTCInfo[1]                 */
                u1_DTCInfo[DCM_DSP_SID03_ResOffDTCLo] = (uint8)( u4_DTC );

                u1_RetWriteDtc = Dcm_Dsp_SID03_WriteResDtc( ptMsgContext_temp, u1_DTCInfo );
                if( u1_RetWriteDtc == (Std_ReturnType)E_OK )
                {
                    u1_DTCNumber = (uint8)(u1_DTCNumber + (uint8)1U);
                }
                else
                {
                    /* Write Buffer Error Loop End                          */
                    b_LoopEnd = (boolean)TRUE;
                    u1_NegResCode    = DCM_E_RESPONSETOOLONG;
                    u1_SendResKind = DCM_DSP_SID03_NEGATIVE_RESP;

                }
                break;
            case DEM_FILTERED_NO_MATCHING_ELEMENT:
                /* Loop End , Processing completion                         */
                b_LoopEnd = (boolean)TRUE;
                break;
            default:
                /* Loop End , Illegal Return Value                          */
                b_LoopEnd = (boolean)TRUE;
                u1_NegResCode = DCM_E_REQUESTOUTOFRANGE;
                u1_SendResKind = DCM_DSP_SID03_NEGATIVE_RESP;
                break;
        }
    }/* while End */

    if( u1_SendResKind == DCM_DSP_SID03_NEGATIVE_RESP )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( ptMsgContext_temp, u1_NegResCode );
    }
    else
    {
        ptMsgContext_temp->resData[DCM_DSP_SID03_DTCNumberWrite] = u1_DTCNumber;
        Dcm_Dsp_MsgMaker_SendPosRes( ptMsgContext_temp );
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID03_WriteResDtc                                */
/* Description   | Write DTC Information Data In Responde Buffer            */
/* Preconditions |                                                          */
/* Parameters    | [IN/OUT]   Dcm_MsgContextType*    : ptMsgContext_temp    */
/*               | [IN]   uint8*                 : ptDtcAndStatusRecord     */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK          0x00                                       */
/*               | E_NOT_OK      0x01                                       */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID03_WriteResDtc
(
    P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext_temp,
    P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) ptDtcAndStatusRecord
)
{
    Std_ReturnType u1_RetVal;

    u1_RetVal = (Std_ReturnType)E_NOT_OK;

    if( (ptMsgContext_temp->resMaxDataLen - ptMsgContext_temp->resDataLen) >= DCM_DSP_SID03_DASRLen )   /* no wrap around */
    {
        /* DTC Data Set */
        ptMsgContext_temp->resData[ptMsgContext_temp->resDataLen] = ptDtcAndStatusRecord[DCM_DSP_SID03_ResOffDTCHi];
        ptMsgContext_temp->resData[ptMsgContext_temp->resDataLen + (Dcm_MsgLenType)DCM_DSP_SID03_ResOffDTCLo ] = ptDtcAndStatusRecord[DCM_DSP_SID03_ResOffDTCLo];   /* no wrap around */
        /* DTC Data Length Plus */
        ptMsgContext_temp->resDataLen += (Dcm_MsgLenType)DCM_DSP_SID03_DASRLen; /* no wrap around */
        /* Return Value Set */
        u1_RetVal = (Std_ReturnType)E_OK;
    }
    else
    {
        /* Pointer Illegal or Response Buffer Lack */
        /* No process */
    }

    return u1_RetVal;
}

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID03 == STD_ON */
#endif /* DCM_OBDTYPE_TYPE_OBD */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2018-12-25                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File************************************************************/
