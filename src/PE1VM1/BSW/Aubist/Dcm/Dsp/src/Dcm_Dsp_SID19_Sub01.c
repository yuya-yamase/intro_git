/* Dcm_Dsp_SID19_Sub01_c(v5-0-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID19_Sub01/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID19_Sub01.h>
#if ( DCM_SUPPORT_SID19_SUB01 == STD_ON )
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dem_Dcm.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     DCM_DSP_SID19_SUB01_ShftCntHi                 (8U)
#define     DCM_DSP_SID19_SUB01_MASKCntLo                 (0x00FFU)
#define     DCM_DSP_SID19_SUB01_ReqOffDTCSM               (0U)
#define     DCM_DSP_SID19_SUB01_ResOffSAM                 (0U)
#define     DCM_DSP_SID19_SUB01_ResOffFmtId               (1U)
#define     DCM_DSP_SID19_SUB01_ResOffCHiB                (2U)
#define     DCM_DSP_SID19_SUB01_ResOffCLoB                (3U)
#define     DCM_DSP_SID19_SUB01_DTCCount_00               ((uint16)0x00U)
#define     DCM_DSP_SID19_SUB01_DTCStMsk_00               ((uint8)0x00U)
#define     DCM_DSP_SID19_SUB01_DTCStMskLen               (1U)
#define     DCM_DSP_SID19_SUB01_DTCFmtIdLen               (1U)
#define     DCM_DSP_SID19_SUB01_DTCCountLen               (2U)
#define     DCM_DSP_SID19_SUB01_PosResLen                 (DCM_DSP_SID19_SUB01_DTCStMskLen + DCM_DSP_SID19_SUB01_DTCFmtIdLen + DCM_DSP_SID19_SUB01_DTCCountLen)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub01_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
);
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub01_CancelProc
(
    void
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub01_GetNumOfDTC
(
    void
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub01_WriteResCnt
(
    const uint16    u2DTCCount
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
/* Function Name | Dcm_SID19_Sub01                                          */
/* Description   | Request processing of SID 19 SF 01                       */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus    : Operation state                       */
/*               | [IN] pMsgContext : Message Context                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SID19_Sub01           /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
)
{
    Std_ReturnType          u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID19_Sub01_InitialProc( pMsgContext );
        /* This Return Value is check-free */
    }
    else
    {
        Dcm_Dsp_SID19_Sub01_CancelProc();
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub01_Cbk                                  */
/* Description   | Call Back Function to Continue SID19_Sub01 Processing    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub01_Cbk             /* MISRA DEVIATION */
(
    const uint8 u1EventId                                /* MISRA DEVIATION */
)
{

    Std_ReturnType      u1_RetVal;

    u1_RetVal = Dcm_Dsp_SID19_Sub01_GetNumOfDTC();
    if( u1_RetVal == (Std_ReturnType)E_OK )
    {
        /* No process */
    }
    else
    {
        /* No process */
    }

    return ;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub01_InitialProc                          */
/* Description   | Initial process of SID 19 SF 01 request                  */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext : Message Context                      */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub01_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    boolean                         b_SendPosResFlag;
    boolean                         b_SendNegResFlag;
    Std_ReturnType                  u1_RetDDGDSAM;
    Dem_UdsStatusByteType           u1_DTCStatusMask;
    Dem_DTCTranslationFormatType    u1_DTCFormamtType;
    Std_ReturnType                  u1_RetVal;
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    uint8                           u1_InDTCStatusMask;
    Dem_ReturnSetFilterType         u1_RetSetFilter;


    u1_RetVal           = E_OK;
    b_SendPosResFlag    = (boolean)FALSE;
    b_SendNegResFlag    = (boolean)FALSE;
    u1_DTCStatusMask    = DCM_DSP_SID19_SUB01_DTCStMsk_00;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;

    if( Dcm_Dsp_Main_stMsgContext.reqDataLen == (Dcm_MsgLenType)DCM_DSP_SID19_SUB01_DTCStMskLen )
    {
        if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= (Dcm_MsgLenType)DCM_DSP_SID19_SUB01_PosResLen )
        {
            /* Get DTC Status Availability Mask From DEM                    */
            u1_RetDDGDSAM = Dem_DcmGetDTCStatusAvailabilityMask( &u1_DTCStatusMask, DEM_DTC_ORIGIN_PRIMARY_MEMORY );
            if( u1_RetDDGDSAM == (Std_ReturnType)E_OK )
            {
                if( Dcm_Dsp_Main_stMsgContext.resData != NULL_PTR )
                {
                    /* Write DTC Status Availability Mask                   */
                    /*                          to Response Buffer          */
                    Dcm_Dsp_Main_stMsgContext.resData[ DCM_DSP_SID19_SUB01_ResOffSAM ] = u1_DTCStatusMask;
                    /* DTC Status Data Length Plus */
                    Dcm_Dsp_Main_stMsgContext.resDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen + (Dcm_MsgLenType)DCM_DSP_SID19_SUB01_DTCStMskLen;  /* no wrap around */

                    /* Get DTC Translation Type from DEM                        */
                    u1_DTCFormamtType = Dem_DcmGetTranslationType();

                    /* DTC Format ID Data Set */
                    Dcm_Dsp_Main_stMsgContext.resData[ DCM_DSP_SID19_SUB01_ResOffFmtId ] = u1_DTCFormamtType;
                    /* DTC Format ID Data Length Plus */
                    Dcm_Dsp_Main_stMsgContext.resDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen + (Dcm_MsgLenType)DCM_DSP_SID19_SUB01_DTCFmtIdLen;  /* no wrap around */

                    /* Check DTC Status Mask in Request Buffer                  */
                    u1_InDTCStatusMask = Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB01_ReqOffDTCSM];
                    if( u1_InDTCStatusMask != DCM_DSP_SID19_SUB01_DTCStMsk_00 )
                    {
                        u1_RetSetFilter = Dem_DcmSetDTCFilter( u1_InDTCStatusMask,
                                                               DEM_DTC_KIND_ALL_DTCS,
                                                               DEM_DTC_FORMAT_UDS,
                                                               DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                                               (boolean)FALSE,
                                                               DEM_SEVERITY_NO_SEVERITY,
                                                               (boolean)FALSE
                                                               );
                        if( u1_RetSetFilter == (Dem_ReturnSetFilterType)DEM_FILTER_ACCEPTED )
                        {
                            u1_RetVal = Dcm_Dsp_SID19_Sub01_GetNumOfDTC();
                            /* This Return Value is check-free */
                        }
                        else
                        {
                            /* This Route                                       */
                            /*   Status Busy NG    -> 0x21                      */
                            u1_NegResCode    = DCM_E_BUSYREPEATREQUEST;
                            b_SendNegResFlag = (boolean)TRUE;
                        }
                    }
                    else
                    {
                        /* This Route                                           */
                        /*   Request DTCStatusMask Equal Zero                   */
                        /* Set DTC Count Zero                                   */
                        (void)Dcm_Dsp_SID19_Sub01_WriteResCnt( DCM_DSP_SID19_SUB01_DTCCount_00 );       /* no return check required */
                        /* Send Positive Response                               */
                        b_SendPosResFlag = (boolean)TRUE;
                    }
                }
            }
            else
            {
                /* This Route                                               */
                /*   General Reject    -> 0x10                              */
                u1_NegResCode    = DCM_E_GENERALREJECT;
                b_SendNegResFlag = (boolean)TRUE;
            }
        }
        else
        {
            /* No process */
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
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
    }
    else if( b_SendPosResFlag == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;

}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub01_CancelProc                           */
/* Description   | Cancel process of SID 19 SF 01 request                   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub01_CancelProc
(
    void
)
{

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB01_GETNOD, (boolean)FALSE );              /* no return check required */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub01_GetNumOfDTC                          */
/* Description   | Get Number Of DTC and Edit Response or Register Event    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub01_GetNumOfDTC
(
    void
)
{
    Std_ReturnType                          u1_RetVal;
    Dem_ReturnGetNumberOfFilteredDTCType    u1_RetNumOfDtc;
    uint16                                  u2_NumOfDTC;
    Std_ReturnType                          u1_RetWriteNum;

    u1_RetVal       = E_OK;
    u2_NumOfDTC     = (uint16)0;

    u1_RetNumOfDtc  = Dem_DcmGetNumberOfFilteredDTC( &u2_NumOfDTC );
    switch( u1_RetNumOfDtc )
    {
        case DEM_NUMBER_OK :

            u1_RetWriteNum = Dcm_Dsp_SID19_Sub01_WriteResCnt( u2_NumOfDTC );
            if( u1_RetWriteNum == (Std_ReturnType)E_OK )
            {
                /* Send Positive Response                                   */
                Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
            }
            else
            {
                /* No process                                               */
            }
            break;
        case DEM_NUMBER_PENDING:
            /* Wait a processing                                            */
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB01_GETNOD );                        /* no return check required */
            /* Return Pending                                               */
            u1_RetVal = DCM_E_PENDING;
            break;
        case DEM_NUMBER_FAILED:
            /* No process                                                   */
            break;
        default:
            /* No process                                                   */
            break;
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub01_WriteResCnt                          */
/* Description   | Write DTC Count In Responde Buffer                       */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u2DTCCount      : Nummber of DTC counts             */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK           : Processing Successful                 */
/*               |   E_NOT_OK       : Processing Not successful             */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub01_WriteResCnt
(
    const uint16    u2DTCCount
)
{
    Std_ReturnType              u1_RetVal;
    Dcm_MsgLenType              u4_UnusedDataLen;

    u1_RetVal           = E_NOT_OK;
    u4_UnusedDataLen    = (Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen); /* no wrap around */

    if( ( Dcm_Dsp_Main_stMsgContext.resData != NULL_PTR ) && ( u4_UnusedDataLen >= (Dcm_MsgLenType)DCM_DSP_SID19_SUB01_DTCCountLen ) )
    {
        /* DTC Count Data Set High-Byte */
        Dcm_Dsp_Main_stMsgContext.resData[ DCM_DSP_SID19_SUB01_ResOffCHiB ] = (uint8)( u2DTCCount >> DCM_DSP_SID19_SUB01_ShftCntHi );
        /* DTC Count Data Set Low-Byte */
        Dcm_Dsp_Main_stMsgContext.resData[ DCM_DSP_SID19_SUB01_ResOffCLoB ] = (uint8)( u2DTCCount & (uint16)DCM_DSP_SID19_SUB01_MASKCntLo );
        /* DTC Data Length Plus */
        Dcm_Dsp_Main_stMsgContext.resDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen + (Dcm_MsgLenType)DCM_DSP_SID19_SUB01_DTCCountLen;  /* no wrap around */
        /* Return Value Set */
        u1_RetVal = E_OK;
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
#endif /* DCM_SUPPORT_SID19_SUB01 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

