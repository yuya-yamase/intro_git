/* Dcm_Dsp_SID19_Sub0E_c(v5-0-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID19_Sub0E/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID19_Sub0E.h>
#if ( DCM_SUPPORT_SID19_SUB0E == STD_ON )
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dem_Dcm.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SID19_SUB0E_SHFTDTC_HI      ((uint8)16U)
#define DCM_DSP_SID19_SUB0E_SHFTDTC_MI      ((uint8)8U)
#define DCM_DSP_SID19_SUB0E_RESP_MASK       ((Dcm_MsgLenType)0U)
#define DCM_DSP_SID19_SUB0E_RESP_DTC_HI     ((Dcm_MsgLenType)1U)
#define DCM_DSP_SID19_SUB0E_RESP_DTC_MI     ((Dcm_MsgLenType)2U)
#define DCM_DSP_SID19_SUB0E_RESP_DTC_LO     ((Dcm_MsgLenType)3U)
#define DCM_DSP_SID19_SUB0E_RESP_DTC_ST     ((Dcm_MsgLenType)4U)
#define DCM_DSP_SID19_SUB0E_MSGLEN          ((Dcm_MsgLenType)0U)
#define DCM_DSP_SID19_SUB0E_RESLEN_NODTC    ((Dcm_MsgLenType)1U)
#define DCM_DSP_SID19_SUB0E_RESLEN_DTC      ((Dcm_MsgLenType)5U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC( void, DCM_CODE ) Dcm_Dsp_SID19_Sub0E_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
);
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID19_Sub0E_CancelProc
( void );

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
/* Function Name | Dcm_SID19_Sub0E                                          */
/* Description   | Report most recent ConfirmedDTC                          */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus       : Status of the current operation    */
/*               | [IN] pMsgContext    : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK                : Result OK                          */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( Std_ReturnType, DCM_CODE ) Dcm_SID19_Sub0E /* MISRA DEVIATION */
(
    Dcm_OpStatusType OpStatus,
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) pMsgContext
)
{
    Std_ReturnType          u1_RetVal;
    
    u1_RetVal = (Std_ReturnType)E_OK;
    
    if( OpStatus == DCM_INITIAL )
    {
        Dcm_Dsp_SID19_Sub0E_InitialProc( pMsgContext );
    }
    else
    {
        Dcm_Dsp_SID19_Sub0E_CancelProc();
    }
    
    return u1_RetVal;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub0E_InitialProc                          */
/* Description   | Initial process of SID19_Sub0E                           */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID19_Sub0E_InitialProc
(
    P2CONST( Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA ) ptMsgContext
)
{
    Dcm_MsgContextType              st_MsgContext_temp;
    uint32                          u4_DTC;
    Std_ReturnType                  u1_RetGetDTCAvailMask;
    Std_ReturnType                  u1_RetGetDTCByOT;
    Dem_ReturnGetStatusOfDTCType    u1_RetGetStsDTC;
    Dem_UdsStatusByteType           u1_DTCStatusMask;
    Dem_UdsStatusByteType           u1_DTCStatus;
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    boolean                         b_SendPosResFlag;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    b_SendPosResFlag = (boolean)FALSE;

    st_MsgContext_temp = *ptMsgContext;

    if( st_MsgContext_temp.reqDataLen == DCM_DSP_SID19_SUB0E_MSGLEN )
    {
        /* Get AvailabilityMask */
        u1_DTCStatusMask = (Dem_UdsStatusByteType)0U;
        u1_RetGetDTCAvailMask = Dem_DcmGetDTCStatusAvailabilityMask( &u1_DTCStatusMask, DEM_DTC_ORIGIN_PRIMARY_MEMORY );
        if( u1_RetGetDTCAvailMask == (Std_ReturnType)E_OK )
        {
            /* Get MostRecentConfirmedDTC */
            u4_DTC = (uint32)0U;
            u1_RetGetDTCByOT = Dem_DcmGetDTCByOccurrenceTime( DEM_MOST_REC_DET_CONFIRMED_DTC, &u4_DTC );
            
            if( u1_RetGetDTCByOT == (Std_ReturnType)E_OK )
            {
                /* Get StatusOfDTC */
                u1_DTCStatus = (Dem_UdsStatusByteType)0U;
                u1_RetGetStsDTC = Dem_DcmGetStatusOfDTC( u4_DTC, DEM_DTC_ORIGIN_PRIMARY_MEMORY, &u1_DTCStatus );
                if( u1_RetGetStsDTC == DEM_STATUS_OK )
                {
                    st_MsgContext_temp.resData[DCM_DSP_SID19_SUB0E_RESP_MASK] = u1_DTCStatusMask;
                    st_MsgContext_temp.resData[DCM_DSP_SID19_SUB0E_RESP_DTC_HI] = (uint8)(u4_DTC >> DCM_DSP_SID19_SUB0E_SHFTDTC_HI);
                    st_MsgContext_temp.resData[DCM_DSP_SID19_SUB0E_RESP_DTC_MI] = (uint8)(u4_DTC >> DCM_DSP_SID19_SUB0E_SHFTDTC_MI);
                    st_MsgContext_temp.resData[DCM_DSP_SID19_SUB0E_RESP_DTC_LO] = (uint8)(u4_DTC);
                    st_MsgContext_temp.resData[DCM_DSP_SID19_SUB0E_RESP_DTC_ST] = u1_DTCStatus;
                    st_MsgContext_temp.resDataLen = DCM_DSP_SID19_SUB0E_RESLEN_DTC;
                    b_SendPosResFlag = (boolean)TRUE;
                }
                else
                {
                    /* NRC0x10 */
                    u1_NegResCode = DCM_E_GENERALREJECT;
                }
            }
            else if( u1_RetGetDTCByOT == (Std_ReturnType)DEM_NO_SUCH_ELEMENT )
            {
                st_MsgContext_temp.resData[DCM_DSP_SID19_SUB0E_RESP_MASK] = u1_DTCStatusMask;
                st_MsgContext_temp.resDataLen = DCM_DSP_SID19_SUB0E_RESLEN_NODTC;
                b_SendPosResFlag = (boolean)TRUE;
            }
            else
            {
                /* NRC0x10 */
                u1_NegResCode = DCM_E_GENERALREJECT;
            }
        }
        else
        {
            /* NRC0x10 */
             u1_NegResCode = DCM_E_GENERALREJECT;
        }
    }
    else
    {
        /* NRC0x13 Request Length Check NG */
        u1_NegResCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    if( b_SendPosResFlag == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendPosRes( &st_MsgContext_temp );
    }
    else
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &st_MsgContext_temp, u1_NegResCode );
    }

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub0E_CancelProc                           */
/* Description   | Cancel function for SID19 Sub0E                          */
/* Preconditions | None                                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( void, DCM_CODE ) Dcm_Dsp_SID19_Sub0E_CancelProc
( void )
{

    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID19_SUB0E == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File************************************************************/
