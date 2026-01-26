/* Dcm_Dsp_SID19_Sub18_c(v5-5-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID19_Sub18/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID19_Sub18.h>
#if ( DCM_SUPPORT_SID19_SUB18 == STD_ON )
#include "../../Dsp/cfg/Dcm_Dsp_SID19_Sub18_Cfg.h"
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dem_Dcm.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     DCM_DSP_SID19_SUB18_SHFT_DTC_HI               (16U)
#define     DCM_DSP_SID19_SUB18_SHFT_DTC_MI               (8U)
#define     DCM_DSP_SID19_SUB18_REQ_OFS_DTC_HI            (0U)
#define     DCM_DSP_SID19_SUB18_REQ_OFS_DTC_MI            (1U)
#define     DCM_DSP_SID19_SUB18_REQ_OFS_DTC_LO            (2U)
#define     DCM_DSP_SID19_SUB18_REQ_OFS_UDDTCSSRN         (3U)
#define     DCM_DSP_SID19_SUB18_REQ_OFS_MEMYS             ((uint32)4U)
#define     DCM_DSP_SID19_SUB18_RES_OFS_DTC_MI            (1U)
#define     DCM_DSP_SID19_SUB18_RES_OFS_DTC_LO            (2U)
#define     DCM_DSP_SID19_SUB18_RES_OFS_SODTC             (3U)
#define     DCM_DSP_SID19_SUB18_SRNUM_ALL                 (0xFFU)
#define     DCM_DSP_SID19_SUB18_SRNUM_MIN                 (0x00U)
#define     DCM_DSP_SID19_SUB18_DTC_LEN                   (3U)
#define     DCM_DSP_SID19_SUB18_SRNUM_LEN                 (1U)
#define     DCM_DSP_SID19_SUB18_MEMYS_LEN                 ((uint32)1U)
#define     DCM_DSP_SID19_SUB18_SODTC_LEN                 (1U)
#define     DCM_DSP_SID19_SUB18_DASRNUM_LEN               (DCM_DSP_SID19_SUB18_DTC_LEN + DCM_DSP_SID19_SUB18_SRNUM_LEN)
#define     DCM_DSP_SID19_SUB18_DTCASR_LEN                (DCM_DSP_SID19_SUB18_DTC_LEN + DCM_DSP_SID19_SUB18_SODTC_LEN)
#define     DCM_DSP_SID19_SUB18_FFD_SIZE_MAX              (0xFFFFU)
#define     DCM_DSP_SID19_SUB18_DTCORIGIN_USRDEF          ((uint16)0x0100U)
#if ( DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_ON )
#define     DCM_DSP_SID19_SUB18_RESMAXLENGTH              ((uint32)((uint32)0xFFFFFFFFU - DCM_DSP_SID19_SUB18_RESDATAOFSTLEN ))
#define     DCM_DSP_SID19_SUB18_RESDATAOFSTLEN            ((uint32)0x00000007U) /* SID+SF+MEMSELCT+DTC+SODTC */
#endif /* DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_ON */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub18_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
);
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub18_CancelProc
(
    void
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub18_DisDTCRec
(
    void
);
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub18_EnableDTCRec
(
    void
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub18_GetStsDtc
(
    void
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub18_GetSizeOfFF
(
    void
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub18_ChkSizeOVFL
(
    const uint32 u4FFSize
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub18_GetFFData
(
    void
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub18_GetFFDataSingleRead
(
    void
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub18_GetFFDataMultipleRead
(
    void
);
static FUNC(boolean , DCM_CODE) Dcm_Dsp_SID19_Sub18_ChkLoopEnd
(
    uint32                                      u4FFGetCount,
    uint8                                       u1NextRecNum,
    P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA)    ptSendEvent,
    P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA)    ptSendPosRes
);
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub18_SetTargetRecNum
(
    const uint8 u1DTCRecNum
);
#if ( DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_ON )
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub18_AdjustDataLenForPage
(
    void
);
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub18_StartPage
(
    void
);
#endif /* DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>


static VAR(uint32, DCM_VAR_NO_INIT)             Dcm_Dsp_SID19_Sub18_u4DTC;
static VAR(uint16, DCM_VAR_NO_INIT)             Dcm_Dsp_SID19_Sub18_u2DTCOrigin;
static VAR(uint8, DCM_VAR_NO_INIT)              Dcm_Dsp_SID19_Sub18_u1TgtRecNum;
static VAR(boolean, DCM_VAR_NO_INIT)            Dcm_Dsp_SID19_Sub18_bGetFFDEnded;
static VAR(boolean, DCM_VAR_NO_INIT)            Dcm_Dsp_SID19_Sub18_bTgtAll;
#if ( DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_ON )
static VAR(uint32, DCM_VAR_NO_INIT)             Dcm_Dsp_SID19_Sub18_u4RemainingResDataLenforPB;
static VAR(uint32, DCM_VAR_NO_INIT)             Dcm_Dsp_SID19_Sub18_u4ResDataLenforPB;
static VAR(boolean, DCM_VAR_NO_INIT)            Dcm_Dsp_SID19_Sub18_bUpdatePageFlag;
#endif /* DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_ON */

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
/* Function Name | Dcm_SID19_Sub18                                          */
/* Description   | Request processing of SID 19 SF 18                       */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus    : Operation state                       */
/*               | [IN] pMsgContext : Message Context                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SID19_Sub18           /* MISRA DEVIATION */
(
    Dcm_OpStatusType                                            OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA)       pMsgContext
)
{
    Std_ReturnType          u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID19_Sub18_InitialProc( pMsgContext );
        /* This Return Value is check-free */
    }
    else
    {
        Dcm_Dsp_SID19_Sub18_CancelProc();
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub18_DisUpdCbk                            */
/* Description   | Call Back Function to Continue SID 19 SF 18              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub18_DisUpdCbk       /* MISRA DEVIATION */
(
    const uint8 u1EventId                                /* MISRA DEVIATION */
)
{
    Std_ReturnType      u1_RetDisRec;
    Std_ReturnType      u1_RetGetSts;
    Std_ReturnType      u1_RetGetSize;
    Std_ReturnType      u1_RetGetFFDt;
    Std_ReturnType      u1_RetVal;
    boolean             b_ContinueToRead;

    b_ContinueToRead  = (boolean)FALSE; 
    u1_RetVal           = E_OK;

    u1_RetDisRec = Dcm_Dsp_SID19_Sub18_DisDTCRec();
    if( u1_RetDisRec == (Std_ReturnType)E_OK )
    {
        /* This Route DTC Record Update Disabled */
        /* When Complete Operation, Carry Out a Function - Dem_DcmEnableDTCRecordUpdate */
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        u1_RetGetSts = Dcm_Dsp_SID19_Sub18_GetStsDtc();
        if( u1_RetGetSts == (Std_ReturnType)E_OK )
        {
            u1_RetGetSize = Dcm_Dsp_SID19_Sub18_GetSizeOfFF();
            if( u1_RetGetSize == (Std_ReturnType)E_OK )
            {
                u1_RetGetFFDt = Dcm_Dsp_SID19_Sub18_GetFFData();
                if( u1_RetGetFFDt == (Std_ReturnType)DCM_E_PENDING )
                {
                    u1_RetVal = DCM_E_PENDING;
                }
                else
                {
                    if( Dcm_Dsp_SID19_Sub18_bGetFFDEnded != (boolean)TRUE )
                    {
                        b_ContinueToRead = (boolean)TRUE;
                    }
                }
            }
            else if( u1_RetGetSize == (Std_ReturnType)DCM_E_PENDING )
            {
                u1_RetVal = DCM_E_PENDING;
            }
            else
            {
                /* No process */
            }
        }
        else if( u1_RetGetSts == (Std_ReturnType)DCM_E_PENDING )
        {
            u1_RetVal = DCM_E_PENDING;
        }
        else
        {
            /* No process */
        }

        /* Check Operation Completed */
        if( u1_RetVal != (Std_ReturnType)DCM_E_PENDING )
        {
            if( b_ContinueToRead != (boolean)TRUE )
            {
                Dcm_Dsp_SID19_Sub18_EnableDTCRec();
            }
        }
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub18_GetDtcStCbk                          */
/* Description   | Call Back Function to Continue SID 19 SF 18              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub18_GetDtcStCbk     /* MISRA DEVIATION */
(
    const uint8 u1EventId                                /* MISRA DEVIATION */
)
{
    Std_ReturnType      u1_RetGetSts;
    Std_ReturnType      u1_RetGetSize;
    Std_ReturnType      u1_RetGetFFDt;
    Std_ReturnType      u1_RetVal;
    boolean             b_ContinueToRead;

    b_ContinueToRead  = (boolean)FALSE; 
    u1_RetVal           = E_OK;

    /* This Route DTC Record Update Disabled */
    /* When Complete Operation, Carry Out a Function - Dem_DcmEnableDTCRecordUpdate */

    u1_RetGetSts = Dcm_Dsp_SID19_Sub18_GetStsDtc();
    if( u1_RetGetSts == (Std_ReturnType)E_OK )
    {
        u1_RetGetSize = Dcm_Dsp_SID19_Sub18_GetSizeOfFF();
        if( u1_RetGetSize == (Std_ReturnType)E_OK )
        {
            u1_RetGetFFDt = Dcm_Dsp_SID19_Sub18_GetFFData();
            if( u1_RetGetFFDt == (Std_ReturnType)DCM_E_PENDING )
            {
                u1_RetVal = DCM_E_PENDING;
            }
            else
            {
                if( Dcm_Dsp_SID19_Sub18_bGetFFDEnded != (boolean)TRUE )
                {
                    b_ContinueToRead = (boolean)TRUE;
                }
            }
        }
        else if( u1_RetGetSize == (Std_ReturnType)DCM_E_PENDING )
        {
            u1_RetVal = DCM_E_PENDING;
        }
        else
        {
            /* No process */
        }
    }
    else if( u1_RetGetSts == (Std_ReturnType)DCM_E_PENDING )
    {
        u1_RetVal = DCM_E_PENDING;
    }
    else
    {
        /* No process */
    }

    /* Check Operation Completed */
    if( u1_RetVal != (Std_ReturnType)DCM_E_PENDING )
    {
        if( b_ContinueToRead != (boolean)TRUE )
        {
            Dcm_Dsp_SID19_Sub18_EnableDTCRec();
        }
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub18_GetSzFrzCbk                          */
/* Description   | Call Back Function to Continue SID 19 SF 18              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub18_GetSzFrzCbk     /* MISRA DEVIATION */
(
    const uint8 u1EventId                                /* MISRA DEVIATION */
)
{
    Std_ReturnType      u1_RetGetSize;
    Std_ReturnType      u1_RetGetFFDt;
    Std_ReturnType      u1_RetVal;
    boolean             b_ContinueToRead;

    b_ContinueToRead  = (boolean)FALSE; 
    u1_RetVal           = E_OK;

    /* This Route DTC Record Update Disabled */
    /* When Complete Operation, Carry Out a Function - Dem_DcmEnableDTCRecordUpdate */

    u1_RetGetSize = Dcm_Dsp_SID19_Sub18_GetSizeOfFF();
    if( u1_RetGetSize == (Std_ReturnType)E_OK )
    {
        u1_RetGetFFDt = Dcm_Dsp_SID19_Sub18_GetFFData();
        if( u1_RetGetFFDt == (Std_ReturnType)DCM_E_PENDING )
        {
            u1_RetVal = DCM_E_PENDING;
        }
        else
        {
            if( Dcm_Dsp_SID19_Sub18_bGetFFDEnded != (boolean)TRUE )
            {
                b_ContinueToRead = (boolean)TRUE;
            }
        }
    }
    else if( u1_RetGetSize == (Std_ReturnType)DCM_E_PENDING )
    {
        u1_RetVal = DCM_E_PENDING;
    }
    else
    {
        /* No process */
    }

    /* Check Operation Completed */
    if( u1_RetVal != (Std_ReturnType)DCM_E_PENDING )
    {
        if( b_ContinueToRead != (boolean)TRUE )
        {
            Dcm_Dsp_SID19_Sub18_EnableDTCRec();
        }
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub18_GetFrzDtCbk                          */
/* Description   | Call Back Function to Continue SID 19 SF 18              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub18_GetFrzDtCbk     /* MISRA DEVIATION */
(
    const uint8 u1EventId                                /* MISRA DEVIATION */
)
{
    Std_ReturnType      u1_RetGetFFDt;

    /* This Route DTC Record Update Disabled */
    /* When Complete Operation, Carry Out a Function - Dem_DcmEnableDTCRecordUpdate */

    u1_RetGetFFDt = Dcm_Dsp_SID19_Sub18_GetFFData();
    if( u1_RetGetFFDt != (Std_ReturnType)DCM_E_PENDING )
    {
        if( Dcm_Dsp_SID19_Sub18_bGetFFDEnded == (boolean)TRUE )
        {
            Dcm_Dsp_SID19_Sub18_EnableDTCRec();
        }
    }

    return ;
}
#if ( DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub18_UpdatePage                           */
/* Description   | UpdatePage of SID 19 SF 18                               */
/* Preconditions | None                                                     */
/* Parameters    | [OUT] ptResData       : Response Data                    */
/*               | [IN]  u4ResMaxDataLen : Buffer Size of Response Data     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing abnormal                */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub18_UpdatePage
(
    Dcm_MsgType     ptResData,
    Dcm_MsgLenType  u4ResMaxDataLen
)
{
    Std_ReturnType      u1_RetGetFFDt;
    Std_ReturnType      u1_RetVal;
    
    u1_RetVal = E_OK;

    if( u4ResMaxDataLen == (Dcm_MsgLenType)DCM_DSD_UPDATEPAGE_INITIAL_ACT )
    {
        Dcm_Dsp_SID19_Sub18_bUpdatePageFlag = (boolean)TRUE;
        Dcm_Dsp_MsgMaker_ProcessPage( Dcm_Dsp_Main_stMsgContext.resDataLen );
    }
    else
    {
        Dcm_Dsp_Main_stMsgContext.resData          = ptResData;
        Dcm_Dsp_Main_stMsgContext.resMaxDataLen    = u4ResMaxDataLen;
        Dcm_Dsp_Main_stMsgContext.resDataLen       = (uint32)0U;

        u1_RetGetFFDt = Dcm_Dsp_SID19_Sub18_GetFFData();
        if( u1_RetGetFFDt == (Std_ReturnType)DCM_E_PENDING )
        {
            u1_RetVal = DCM_E_PENDING;
        }
        else
        {
            if( Dcm_Dsp_Main_stMsgContext.resDataLen == (uint32)0U )
            {
                u1_RetVal = E_NOT_OK;
            }
            
            if( Dcm_Dsp_SID19_Sub18_bGetFFDEnded == (boolean)TRUE )
            {
                Dcm_Dsp_SID19_Sub18_EnableDTCRec();
            }
        }
    }

    return u1_RetVal;
}
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub18_CancelPage                           */
/* Description   | CancelPage of SID 19 SF 18                               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub18_CancelPage
(void)
{
    boolean                         b_UserNotify;

    b_UserNotify    = Dcm_Dsp_Main_GetUserNotifyFlag();

    if( b_UserNotify == (boolean)TRUE )
    {
        /* SID19_Sub18 Operation Completed */
        /* Enable DTC Record Update */
        (void)Dem_DcmEnableDTCRecordUpdate();                                                           /* no return check required */
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB18_GETFFDT, (boolean)FALSE );
    }

    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}
#endif /* DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_ON */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub18_InitialProc                          */
/* Description   | Initial process of SID 19 SF 18 request                  */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext : Message Context                      */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub18_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    Std_ReturnType                  u1_RetDisRec;
    Std_ReturnType                  u1_RetGetSts;
    Std_ReturnType                  u1_RetGetSize;
    Std_ReturnType                  u1_RetGetFFDt;
    Std_ReturnType                  u1_RetVal;
    boolean                         b_ContinueToRead;
    boolean                         b_SendNegRes;

    b_ContinueToRead    = (boolean)FALSE; 
    b_SendNegRes        = (boolean)FALSE;
    u1_RetVal           = E_OK;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    /* Set Common Data */
    Dcm_Dsp_SID19_Sub18_u4DTC           = (uint32)0x00000000U;
    Dcm_Dsp_SID19_Sub18_u1TgtRecNum     = DCM_DSP_SID19_SUB18_SRNUM_MIN;
    Dcm_Dsp_SID19_Sub18_bTgtAll         = (boolean)FALSE;
    Dcm_Dsp_SID19_Sub18_bGetFFDEnded    = (boolean)FALSE;
    Dcm_Dsp_Main_stMsgContext           = *ptMsgContext;
    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    /* Check Request Data Length */
    if( Dcm_Dsp_Main_stMsgContext.reqDataLen == ( DCM_DSP_SID19_SUB18_DASRNUM_LEN + DCM_DSP_SID19_SUB18_MEMYS_LEN ) )
    {
        /* Check Response Data Area Length */
        if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= ( DCM_DSP_SID19_SUB18_DTCASR_LEN + DCM_DSP_SID19_SUB18_MEMYS_LEN ) )
        {
            Dcm_Dsp_SID19_Sub18_u4DTC = (((uint32)ptMsgContext->reqData[DCM_DSP_SID19_SUB18_REQ_OFS_DTC_HI]) << DCM_DSP_SID19_SUB18_SHFT_DTC_HI ) |
                                        (((uint32)ptMsgContext->reqData[DCM_DSP_SID19_SUB18_REQ_OFS_DTC_MI]) << DCM_DSP_SID19_SUB18_SHFT_DTC_MI ) |
                                        (uint32)ptMsgContext->reqData[DCM_DSP_SID19_SUB18_REQ_OFS_DTC_LO];

            Dcm_Dsp_SID19_Sub18_u2DTCOrigin = DCM_DSP_SID19_SUB18_DTCORIGIN_USRDEF + (uint16)ptMsgContext->reqData[DCM_DSP_SID19_SUB18_REQ_OFS_MEMYS];

            /* Set Target Record Number */
            Dcm_Dsp_SID19_Sub18_SetTargetRecNum( ptMsgContext->reqData[DCM_DSP_SID19_SUB18_REQ_OFS_UDDTCSSRN] );
            u1_RetDisRec = Dcm_Dsp_SID19_Sub18_DisDTCRec();
            if( u1_RetDisRec == (Std_ReturnType)E_OK )
            {
                /* This Route DTC Record Update Disabled */
                /* When Complete Operation, Carry Out a Function - Dem_DcmEnableDTCRecordUpdate */
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
                u1_RetGetSts = Dcm_Dsp_SID19_Sub18_GetStsDtc();
                if( u1_RetGetSts == (Std_ReturnType)E_OK )
                {
                    u1_RetGetSize = Dcm_Dsp_SID19_Sub18_GetSizeOfFF();
                    if( u1_RetGetSize == (Std_ReturnType)E_OK )
                    {
                        u1_RetGetFFDt = Dcm_Dsp_SID19_Sub18_GetFFData();
                        if( u1_RetGetFFDt == (Std_ReturnType)DCM_E_PENDING )
                        {
                            u1_RetVal = DCM_E_PENDING;
                        }
                        else
                        {
                            if( Dcm_Dsp_SID19_Sub18_bGetFFDEnded != (boolean)TRUE )
                            {
                                b_ContinueToRead = (boolean)TRUE;
                            }
                        }
                    }
                    else if( u1_RetGetSize == (Std_ReturnType)DCM_E_PENDING )
                    {
                        u1_RetVal = DCM_E_PENDING;
                    }
                    else
                    {
                        /* No process */
                    }
                }
                else if( u1_RetGetSts == (Std_ReturnType)DCM_E_PENDING )
                {
                    u1_RetVal = DCM_E_PENDING;
                }
                else
                {
                    /* No process */
                }

                /* Check Operation Completed */
                if( u1_RetVal != (Std_ReturnType)DCM_E_PENDING )
                {
                    if( b_ContinueToRead != (boolean)TRUE )
                    {
                        Dcm_Dsp_SID19_Sub18_EnableDTCRec();
                    }
                }
            }
            else if( u1_RetDisRec == (Std_ReturnType)DCM_E_PENDING )
            {
                /* SID19_Sub18 Operation Continue */
                u1_RetVal = DCM_E_PENDING;
            }
            else
            {
                /* No process */
            }
        }
        else
        {
            /* Not enough Response Message Buffer Size */
            u1_NegResCode = DCM_E_RESPONSETOOLONG;
            b_SendNegRes  = (boolean)TRUE;
        }
    }
    else
    {
        /* This Route                                                       */
        /*   Request Length Check NG    -> 0x13                             */
        u1_NegResCode   = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        b_SendNegRes    = (boolean)TRUE;
    }

    if( b_SendNegRes == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
    }

    return u1_RetVal;

}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub18_CancelProc                           */
/* Description   | Cancel process of SID 19 SF 18 request                   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub18_CancelProc
(
    void
)
{
    Dcm_Main_EvtDistr_RetType       u1_RetDelGetFFDt;
    Dcm_Main_EvtDistr_RetType       u1_RetDelGetSize;
    boolean                         b_UserNotify;

    b_UserNotify    = Dcm_Dsp_Main_GetUserNotifyFlag();

    if( b_UserNotify == (boolean)TRUE )
    {

        /* SID19_Sub18 Operation Completed */
        /* Enable DTC Record Update */
        (void)Dem_DcmEnableDTCRecordUpdate();                                                           /* no return check required */
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

        u1_RetDelGetFFDt = Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB18_GETFFDT, (boolean)FALSE );
        if( u1_RetDelGetFFDt != DCM_MAIN_EVTDISTR_E_OK )
        {
            u1_RetDelGetSize = Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB18_GETSIZE, (boolean)FALSE );
            if( u1_RetDelGetSize != DCM_MAIN_EVTDISTR_E_OK )
            {
                (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB18_GETSTS, (boolean)FALSE );  /* no return check required */
            }
        }
    }
    else
    {
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB18_DISREC, (boolean)FALSE );          /* no return check required */
    }
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub18_SetTargetRecNum                      */
/* Description   | Set DTCSnapShotRecordNumber for Read                     */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1DTCRecNum : RecordNumber                          */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub18_SetTargetRecNum
(
    const uint8 u1DTCRecNum
)
{
    if( u1DTCRecNum == (uint8)DCM_DSP_SID19_SUB18_SRNUM_ALL )
    {
        /* Dcm_Dsp_SID19_Sub18_u1TgtRecNum has been already set 0x00 */
        Dcm_Dsp_SID19_Sub18_bTgtAll = (boolean)TRUE;
    }
    else
    {
        /* TargetAllFlg has been already set in FALSE */
        Dcm_Dsp_SID19_Sub18_u1TgtRecNum = u1DTCRecNum;
    }

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub18_DisDTCRec                            */
/* Description   | Call DEM-API Dem_DcmDisableDTCRecordUpdate               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/*               |   E_NOT_OK          : Processing not normal              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub18_DisDTCRec
(
    void
)
{
    Std_ReturnType                          u1_RetVal;
    Dem_ReturnDisableDTCRecordUpdateType    u1_RetDisDTCRec;

    u1_RetVal = E_NOT_OK;

    u1_RetDisDTCRec = Dem_DcmDisableDTCRecordUpdate( Dcm_Dsp_SID19_Sub18_u4DTC, (Dem_DTCOriginType)Dcm_Dsp_SID19_Sub18_u2DTCOrigin );

    /* Check DEM-API Return Value */
    switch( u1_RetDisDTCRec )
    {
        case DEM_DISABLE_DTCRECUP_OK:
            u1_RetVal = E_OK;
            break;
        case DEM_DISABLE_DTCRECUP_WRONG_DTC:
            /* DTC Illegal. Set RequestOutOfRange(0x31) to NRC. */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
            break;
        case DEM_DISABLE_DTCRECUP_PENDING:
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB18_DISREC );                        /* no return check required */
            u1_RetVal = DCM_E_PENDING;
            break;
        case DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN:
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
            break;
        default:
            /* Dem_DcmDisableDTCRecordUpdate return value is out of range. */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
            break;
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub18_EnableDTCRec                         */
/* Description   | Call DEM-API Dem_DcmEnableDTCRecordUpdate                */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub18_EnableDTCRec
(
    void
)
{
    boolean b_UserNotify;

    b_UserNotify    = Dcm_Dsp_Main_GetUserNotifyFlag();
    if( b_UserNotify == (boolean)TRUE )
    {
        /* SID19_Sub18 Operation Completed */
        /* Enable DTC Record Update */
        (void)Dem_DcmEnableDTCRecordUpdate();                       /* no return check required */
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub18_GetStsDtc                            */
/* Description   | Call DEM-API Dem_DcmGetStatusOfDTC                       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/*               |   E_NOT_OK          : Processing not normal              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub18_GetStsDtc
(
    void
)
{
    Std_ReturnType                          u1_RetVal;
    Dem_ReturnGetStatusOfDTCType            u1_RetGetStsDTC;
    uint8                                   u1_DTCStatus;

    u1_RetVal = E_NOT_OK;
    u1_DTCStatus = 0x00U;

    u1_RetGetStsDTC = Dem_DcmGetStatusOfDTC( Dcm_Dsp_SID19_Sub18_u4DTC, (Dem_DTCOriginType)Dcm_Dsp_SID19_Sub18_u2DTCOrigin, &u1_DTCStatus );

    /* Check DEM-API Return Value */
    switch( u1_RetGetStsDTC )
    {
        case DEM_STATUS_OK:
            /* Set MemorySelection to response buffer  */
            Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen ] = Dcm_Dsp_Main_stMsgContext.reqData[ DCM_DSP_SID19_SUB18_REQ_OFS_MEMYS ];
            Dcm_Dsp_Main_stMsgContext.resDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen + (Dcm_MsgLenType)DCM_DSP_SID19_SUB18_MEMYS_LEN;  /* no wrap around */

            /* Server DTC Status Mask Data Set In Response Buffer */
            Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen ] = Dcm_Dsp_Main_stMsgContext.reqData[ DCM_DSP_SID19_SUB18_REQ_OFS_DTC_HI ];
            Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen + (Dcm_MsgLenType)DCM_DSP_SID19_SUB18_RES_OFS_DTC_MI ] = Dcm_Dsp_Main_stMsgContext.reqData[ DCM_DSP_SID19_SUB18_REQ_OFS_DTC_MI ]; /* no wrap around */
            Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen + (Dcm_MsgLenType)DCM_DSP_SID19_SUB18_RES_OFS_DTC_LO ] = Dcm_Dsp_Main_stMsgContext.reqData[ DCM_DSP_SID19_SUB18_REQ_OFS_DTC_LO ]; /* no wrap around */
            Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen + (Dcm_MsgLenType)DCM_DSP_SID19_SUB18_RES_OFS_SODTC ] = u1_DTCStatus; /* no wrap around */
            Dcm_Dsp_Main_stMsgContext.resDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen + (Dcm_MsgLenType)DCM_DSP_SID19_SUB18_DTCASR_LEN;  /* no wrap around */
            u1_RetVal = E_OK;
            break;
        case DEM_STATUS_PENDING:
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB18_GETSTS );                        /* no return check required */
            u1_RetVal = DCM_E_PENDING;
            break;
        case DEM_STATUS_WRONG_DTC:
        case DEM_STATUS_WRONG_DTCORIGIN:
        case DEM_STATUS_FAILED:
            /* Abnormality was detected for items that have been confirmed to be normal with Dem_DcmDisableDTCRecordUpdate. */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
            break;
        default:
            /* Dem_DcmGetStatusOfDTC return value is out of range. */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
            break;
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub18_GetSizeOfFF                          */
/* Description   | Call DEM-API Dem_DcmGetSizeOfFreezeFrameByDTC            */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/*               |   E_NOT_OK          : Processing not normal              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub18_GetSizeOfFF
(
    void
)
{
    uint32                                  u4_FFSize;
    Std_ReturnType                          u1_RetVal;
    Std_ReturnType                          u1_RetChkSizeOVFLVal;
    Dem_ReturnGetSizeOfDataByDTCType        u1_RetGetSizeData;

    u1_RetVal            = E_NOT_OK;
    u4_FFSize            = (uint32)0U;

    /* Get Size Of Freeze Frame Data */
    u1_RetGetSizeData = Dem_DcmGetSizeOfFreezeFrameByDTC( Dcm_Dsp_SID19_Sub18_u4DTC, (Dem_DTCOriginType)Dcm_Dsp_SID19_Sub18_u2DTCOrigin, Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB18_REQ_OFS_UDDTCSSRN], &u4_FFSize );

    /* Check DEM-API Return Value */
    switch( u1_RetGetSizeData )
    {
        case DEM_GETSIZEBYDTC_OK:
            u1_RetChkSizeOVFLVal = Dcm_Dsp_SID19_Sub18_ChkSizeOVFL( u4_FFSize );
            if( u1_RetChkSizeOVFLVal == (Std_ReturnType)E_OK )
            {
                u1_RetVal = E_OK;
            }
            else
            {
                /* Size Of Freeze Frame Data Exceeds Size Of the Response Buffer */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_RESPONSETOOLONG );
            }
            break;
        case DEM_GETSIZEBYDTC_WRONG_RECNUM:
            /* Record Number Illegal. Set RequestOutOfRange[0x31] to NRC. */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_REQUESTOUTOFRANGE );
            break;
        case DEM_GETSIZEBYDTC_PENDING:
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB18_GETSIZE );                       /* no return check required */
            u1_RetVal = DCM_E_PENDING;
            break;
        case DEM_GETSIZEBYDTC_WRONG_DTC:
        case DEM_GETSIZEBYDTC_WRONG_DTCORIGIN:
            /* Abnormality was detected for items that have been confirmed to be normal with Dem_DcmDisableDTCRecordUpdate. */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
            break;
        default:
            /* Dem_DcmGetSizeOfFreezeFrameByDTC return value is out of range. */
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_GENERALREJECT );
            break;
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub18_ChkSizeOVFL                          */
/* Description   | Check ResData into Max                                   */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u4FFSize : Freeze frame record size                 */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Check OK                           */
/*               |   E_NOT_OK          : Check NOT OK                       */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_OFF )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub18_ChkSizeOVFL
(
    const uint32 u4FFSize
)
{
    uint32                                  u4_ResBuffSize;
    Std_ReturnType                          u1_RetVal;

    u1_RetVal = E_NOT_OK;

    /* Calculate Size Of the Response Buffer */
    u4_ResBuffSize = Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen;    /* no wrap around */

    if( u4_ResBuffSize >= u4FFSize )
    {
        u1_RetVal = E_OK;
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_ON )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub18_ChkSizeOVFL
(
    const uint32 u4FFSize
)
{
    Std_ReturnType                          u1_RetVal;

    u1_RetVal = E_NOT_OK;

    /* Check cross language boundaries */
    if( DCM_DSP_SID19_SUB18_RESMAXLENGTH >= u4FFSize )
    {
        /* MEMSELCT(1) + DTC(3) + SODTC(1) + SSRData(Predict) */
        Dcm_Dsp_SID19_Sub18_u4ResDataLenforPB = Dcm_Dsp_Main_stMsgContext.resDataLen + u4FFSize; /* no wrap around */
        Dcm_Dsp_SID19_Sub18_u4RemainingResDataLenforPB = u4FFSize;
        Dcm_Dsp_SID19_Sub18_bUpdatePageFlag      = (boolean)FALSE;
        u1_RetVal = E_OK;

    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub18_GetFFData                            */
/* Description   | Call Dcm_Dsp_SID19_Sub18_GetFFDataSingleRead Or          */
/*               | Call Dcm_Dsp_SID19_Sub18_GetFFDataMultipleRead           */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub18_GetFFData
(
    void
)
{
    Std_ReturnType                          u1_RetVal;

    if( Dcm_Dsp_SID19_Sub18_bTgtAll == (boolean)TRUE )
    {
        u1_RetVal = Dcm_Dsp_SID19_Sub18_GetFFDataMultipleRead();
    }
    else
    {
        u1_RetVal = Dcm_Dsp_SID19_Sub18_GetFFDataSingleRead();
    }

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub18_GetFFDataSingleRead                  */
/* Description   | Call DEM-API Dem_DcmGetFreezeFrameDataByDTC(SingleRead)  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_OFF )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub18_GetFFDataSingleRead
(
    void
)
{
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)  pt_WriteBuff;
    uint32                                  u4_WritableSize;
    uint16                                  u2_BuffSize;
    Dcm_NegativeResponseCodeType            u1_NegResCode;
    uint8                                   u1_NextRecNum;
    Dem_ReturnGetFreezeFrameDataByDTCType   u1_RetGetFFData;
    Std_ReturnType                          u1_RetVal;
    boolean                                 b_SendEvent;
    boolean                                 b_SendPosRes;

    u1_RetVal       = E_OK;
    b_SendEvent     = (boolean)FALSE;
    b_SendPosRes    = (boolean)FALSE;
    u1_NegResCode   = DCM_E_GENERALREJECT;

    u1_NextRecNum   = (uint8)0x00U;
    u4_WritableSize = (uint32)(Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen); /* no wrap around */
    if( (uint32)DCM_DSP_SID19_SUB18_FFD_SIZE_MAX < (uint32)u4_WritableSize )
    {
        u2_BuffSize = (uint16)DCM_DSP_SID19_SUB18_FFD_SIZE_MAX;
    }
    else
    {
        u2_BuffSize = (uint16)u4_WritableSize;
    }
    pt_WriteBuff = &(Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen ]);
    /* Get FFData */
    u1_RetGetFFData = Dem_DcmGetFreezeFrameDataByDTC( Dcm_Dsp_SID19_Sub18_u4DTC, (Dem_DTCOriginType)Dcm_Dsp_SID19_Sub18_u2DTCOrigin, Dcm_Dsp_SID19_Sub18_u1TgtRecNum, pt_WriteBuff, &u2_BuffSize, &u1_NextRecNum );

    /* Check DEM-API Return Value */
    switch( u1_RetGetFFData )
    {
        case DEM_GET_FFDATABYDTC_OK:
            if( u4_WritableSize >= (uint32)u2_BuffSize )
            {
                /* Update Response Data Length */
                Dcm_Dsp_Main_stMsgContext.resDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen + u2_BuffSize;  /* no wrap around */
                /* Got FFData Of Target Record Number. */
                Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
                b_SendPosRes = (boolean)TRUE;
            }
            else
            {
                /* u2_BuffSize is not an appropriate value */
                Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
            }
            break;
        case DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER:
            Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
            u1_NegResCode   = DCM_E_REQUESTOUTOFRANGE;
            break;
        case DEM_GET_FFDATABYDTC_PENDING:
            b_SendEvent = (boolean)TRUE;
            break;
        case DEM_GET_FFDATABYDTC_WRONG_DTC:
        case DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN:
            /* Abnormality was detected for items that have been confirmed to be normal with Dem_DcmDisableDTCRecordUpdate. */
            Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
            break;
        case DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE:
            Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
            /* NRC0x14 */
            u1_NegResCode   = DCM_E_RESPONSETOOLONG;
            break;
        default:
            /* Dem_DcmGetFreezeFrameDataByDTC return value is out of range. */
            Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
            break;
    }

    if( b_SendEvent == (boolean)TRUE )
    {
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB18_GETFFDT );                           /* no return check required */
        u1_RetVal   = DCM_E_PENDING;
    }
    else
    {
        if( b_SendPosRes == (boolean)TRUE )
        {
            Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
        }
        else
        {
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
        }
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_ON )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub18_GetFFDataSingleRead
(
    void
)
{
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)  pt_WriteBuff;
    uint32                                  u4_WritableSize;
    uint16                                  u2_BuffSize;
    Dcm_NegativeResponseCodeType            u1_NegResCode;
    uint8                                   u1_NextRecNum;
    Dem_ReturnGetFreezeFrameDataByDTCType   u1_RetGetFFData;
    Std_ReturnType                          u1_RetVal;
    boolean                                 b_SendEvent;
    boolean                                 b_SendPosRes;

    u1_RetVal       = E_OK;
    b_SendEvent     = (boolean)FALSE;
    b_SendPosRes    = (boolean)FALSE;
    u1_NegResCode   = DCM_E_GENERALREJECT;

    if( Dcm_Dsp_SID19_Sub18_bGetFFDEnded == (boolean)TRUE )
    {
        b_SendPosRes    = (boolean)TRUE;
    }
    else
    {
        u1_NextRecNum   = (uint8)0x00U;
        u4_WritableSize = (uint32)(Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen); /* no wrap around */
        if( (uint32)DCM_DSP_SID19_SUB18_FFD_SIZE_MAX < (uint32)u4_WritableSize )
        {
            u2_BuffSize = (uint16)DCM_DSP_SID19_SUB18_FFD_SIZE_MAX;
        }
        else
        {
            u2_BuffSize = (uint16)u4_WritableSize;
        }
        pt_WriteBuff = &(Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen ]);
        /* Get FFData */
        u1_RetGetFFData = Dem_DcmGetFreezeFrameDataByDTC( Dcm_Dsp_SID19_Sub18_u4DTC, (Dem_DTCOriginType)Dcm_Dsp_SID19_Sub18_u2DTCOrigin, Dcm_Dsp_SID19_Sub18_u1TgtRecNum, pt_WriteBuff, &u2_BuffSize, &u1_NextRecNum );

        /* Check DEM-API Return Value */
        switch( u1_RetGetFFData )
        {
            case DEM_GET_FFDATABYDTC_OK:
                if( u4_WritableSize >= (uint32)u2_BuffSize )
                {
                    if( Dcm_Dsp_SID19_Sub18_u4RemainingResDataLenforPB >= u2_BuffSize ) 
                    {
                        /* Update Response Data Length */
                        Dcm_Dsp_Main_stMsgContext.resDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen + u2_BuffSize;  /* no wrap around */
                        Dcm_Dsp_SID19_Sub18_u4RemainingResDataLenforPB = Dcm_Dsp_SID19_Sub18_u4RemainingResDataLenforPB - u2_BuffSize;
                        /* Got FFData Of Target Record Number. */
                        Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
                        b_SendPosRes    = (boolean)TRUE;
                    }
                    else
                    {
                        /* If the data larger than the total length is returned, the data is not set and the Dem acquisition is completed. */
                        /* For the remaining part, adjust 0 with Dcm_Dsp_SID19_Sub18_AdjustDataLenForPage */
                        Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
                        b_SendPosRes    = (boolean)TRUE;
                    }
                }
                else
                {
                    /* u2_BuffSize is not an appropriate value */
                    Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
                }
                break;
            case DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER:
                Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
                u1_NegResCode   = DCM_E_REQUESTOUTOFRANGE;
                break;
            case DEM_GET_FFDATABYDTC_PENDING:
                b_SendEvent = (boolean)TRUE;
                break;
            case DEM_GET_FFDATABYDTC_WRONG_DTC:
            case DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN:
                /* Abnormality was detected for items that have been confirmed to be normal with Dem_DcmDisableDTCRecordUpdate. */
                Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
                break;
            case DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE:
                b_SendPosRes    = (boolean)TRUE;
                break;
            default:
                /* Dem_DcmGetFreezeFrameDataByDTC return value is out of range. */
                Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
                break;
        }
    }

    if( b_SendEvent == (boolean)TRUE )
    {
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB18_GETFFDT );                           /* no return check required */
        u1_RetVal   = DCM_E_PENDING;
    }
    else
    {
        if( Dcm_Dsp_SID19_Sub18_bUpdatePageFlag == (boolean)FALSE )
        {
            if( b_SendPosRes == (boolean)TRUE )
            {
                if( Dcm_Dsp_SID19_Sub18_bGetFFDEnded == (boolean)TRUE )
                {
                    /* If reading of all RecordNumbers is completed before updatePage, correct the total length of data to the current data length and send it all at once */
                    Dcm_Dsp_SID19_Sub18_u4ResDataLenforPB = Dcm_Dsp_Main_stMsgContext.resDataLen;
                    Dcm_Dsp_SID19_Sub18_u4RemainingResDataLenforPB = (uint32)0;
                }
                else
                {
                    if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= Dcm_Dsp_SID19_Sub18_u4ResDataLenforPB )
                    {
                        /* If the total length of data is within resMaxDataLen, correct the total length of data to the current data length and send it all at once */
                        Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
                        Dcm_Dsp_SID19_Sub18_u4ResDataLenforPB = Dcm_Dsp_Main_stMsgContext.resDataLen;
                        Dcm_Dsp_SID19_Sub18_u4RemainingResDataLenforPB = (uint32)0;
                    }
                }
                Dcm_Dsp_SID19_Sub18_StartPage();
            }
            else
            {
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
            }
        }
        else
        {
            Dcm_Dsp_SID19_Sub18_AdjustDataLenForPage();
            
            if( Dcm_Dsp_Main_stMsgContext.resDataLen != (uint32)0U )
            {
                Dcm_Dsp_MsgMaker_ProcessPage( Dcm_Dsp_Main_stMsgContext.resDataLen );
            }
        }
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub18_GetFFDataMultipleRead                */
/* Description   | Call DEM-API Dem_DcmGetFreezeFrameDataByDTC(MultipleRead)*/
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_OFF )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub18_GetFFDataMultipleRead
(
    void
)
{
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)  pt_WriteBuff;
    uint32                                  u4_FFGetCount;
    uint32                                  u4_WritableSize;
    uint16                                  u2_BuffSize;
    Dcm_NegativeResponseCodeType            u1_NegResCode;
    uint8                                   u1_NextRecNum;
    Dem_ReturnGetFreezeFrameDataByDTCType   u1_RetGetFFData;
    Std_ReturnType                          u1_RetVal;
    boolean                                 b_LoopEnd;
    boolean                                 b_SendEvent;
    boolean                                 b_SendPosRes;

    u1_RetVal       = E_OK;
    u4_FFGetCount   = (uint32)0U;
    b_SendEvent     = (boolean)FALSE;
    b_SendPosRes    = (boolean)FALSE;
    u1_NegResCode   = DCM_E_GENERALREJECT;
    b_LoopEnd       = (boolean)FALSE;

    while( b_LoopEnd == (boolean)FALSE )
    {
        u4_FFGetCount++;    /* no wrap around */

        u1_NextRecNum   = (uint8)0x00U;
        u4_WritableSize = (uint32)(Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen); /* no wrap around */
        if( (uint32)DCM_DSP_SID19_SUB18_FFD_SIZE_MAX < (uint32)u4_WritableSize )
        {
            u2_BuffSize = (uint16)DCM_DSP_SID19_SUB18_FFD_SIZE_MAX;
        }
        else
        {
            u2_BuffSize = (uint16)u4_WritableSize;
        }
        pt_WriteBuff = &(Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen ]);
        /* Get FFData */
        u1_RetGetFFData = Dem_DcmGetFreezeFrameDataByDTC( Dcm_Dsp_SID19_Sub18_u4DTC, (Dem_DTCOriginType)Dcm_Dsp_SID19_Sub18_u2DTCOrigin, Dcm_Dsp_SID19_Sub18_u1TgtRecNum, pt_WriteBuff, &u2_BuffSize, &u1_NextRecNum );

        /* Check DEM-API Return Value */
        switch( u1_RetGetFFData )
        {
            case DEM_GET_FFDATABYDTC_OK:
                if( u4_WritableSize >= (uint32)u2_BuffSize )
                {
                    /* Update Response Data Length */
                    Dcm_Dsp_Main_stMsgContext.resDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen + u2_BuffSize;  /* no wrap around */
                    /* Check loop processing continue */
                    b_LoopEnd = Dcm_Dsp_SID19_Sub18_ChkLoopEnd( u4_FFGetCount, u1_NextRecNum, &b_SendEvent, &b_SendPosRes );

                    /* If SendEvent flag and SendPosRes request flag are FALSE and LOOP end, execute SendNegRes (NRC0x10) */
                }
                else
                {
                    /* u2_BuffSize is not an appropriate value */
                    Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
                    b_LoopEnd = (boolean)TRUE;
                }
                break;
            case DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER:
                /* Check loop processing continue */
                b_LoopEnd = Dcm_Dsp_SID19_Sub18_ChkLoopEnd( u4_FFGetCount, u1_NextRecNum, &b_SendEvent, &b_SendPosRes );

                /* If SendEvent flag and SendPosRes request flag are FALSE and LOOP end, execute SendNegRes (NRC0x10) */
                
                break;
            case DEM_GET_FFDATABYDTC_PENDING:
                b_SendEvent = (boolean)TRUE;
                b_LoopEnd   = (boolean)TRUE;
                break;
            case DEM_GET_FFDATABYDTC_WRONG_DTC:
            case DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN:
                /* Abnormality was detected for items that have been confirmed to be normal with Dem_DcmDisableDTCRecordUpdate. */
                Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
                b_LoopEnd       = (boolean)TRUE;
                break;
            case DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE:
                Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
                /* NRC0x14 */
                u1_NegResCode   = DCM_E_RESPONSETOOLONG;
                b_LoopEnd       = (boolean)TRUE;
                break;
            default:
                /* Dem_DcmGetFreezeFrameDataByDTC return value is out of range. */
                Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
                b_LoopEnd       = (boolean)TRUE;
                break;
        }
    }

    if( b_SendEvent == (boolean)TRUE )
    {
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB18_GETFFDT );                           /* no return check required */
        u1_RetVal   = DCM_E_PENDING;
    }
    else
    {
        if( b_SendPosRes == (boolean)TRUE )
        {
            Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
        }
        else
        {
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
        }
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_ON )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub18_GetFFDataMultipleRead
(
    void
)
{
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)  pt_WriteBuff;
    uint32                                  u4_FFGetCount;
    uint32                                  u4_WritableSize;
    uint16                                  u2_BuffSize;
    Dcm_NegativeResponseCodeType            u1_NegResCode;
    uint8                                   u1_NextRecNum;
    Dem_ReturnGetFreezeFrameDataByDTCType   u1_RetGetFFData;
    Std_ReturnType                          u1_RetVal;
    boolean                                 b_LoopEnd;
    boolean                                 b_SendEvent;
    boolean                                 b_SendPosRes;

    u1_RetVal       = E_OK;
    u4_FFGetCount   = (uint32)0U;
    b_SendEvent     = (boolean)FALSE;
    b_SendPosRes    = (boolean)FALSE;
    u1_NegResCode   = DCM_E_GENERALREJECT;
    b_LoopEnd       = (boolean)FALSE;

    if( Dcm_Dsp_SID19_Sub18_bGetFFDEnded == (boolean)TRUE )
    {
        b_SendPosRes    = (boolean)TRUE;
        b_LoopEnd       = (boolean)TRUE;
    }

    while( b_LoopEnd == (boolean)FALSE )
    {
        u4_FFGetCount++;    /* no wrap around */

        u1_NextRecNum   = (uint8)0x00U;
        u4_WritableSize = (uint32)(Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen); /* no wrap around */
        if( (uint32)DCM_DSP_SID19_SUB18_FFD_SIZE_MAX < (uint32)u4_WritableSize )
        {
            u2_BuffSize = (uint16)DCM_DSP_SID19_SUB18_FFD_SIZE_MAX;
        }
        else
        {
            u2_BuffSize = (uint16)u4_WritableSize;
        }
        pt_WriteBuff = &(Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen ]);
        /* Get FFData */
        u1_RetGetFFData = Dem_DcmGetFreezeFrameDataByDTC( Dcm_Dsp_SID19_Sub18_u4DTC, (Dem_DTCOriginType)Dcm_Dsp_SID19_Sub18_u2DTCOrigin, Dcm_Dsp_SID19_Sub18_u1TgtRecNum, pt_WriteBuff, &u2_BuffSize, &u1_NextRecNum );

        /* Check DEM-API Return Value */
        switch( u1_RetGetFFData )
        {
            case DEM_GET_FFDATABYDTC_OK:
                if( u4_WritableSize >= (uint32)u2_BuffSize )
                {
                    if( Dcm_Dsp_SID19_Sub18_u4RemainingResDataLenforPB >= u2_BuffSize ) 
                    {
                        /* Update Response Data Length */
                        Dcm_Dsp_Main_stMsgContext.resDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen + u2_BuffSize;  /* no wrap around */
                        Dcm_Dsp_SID19_Sub18_u4RemainingResDataLenforPB = Dcm_Dsp_SID19_Sub18_u4RemainingResDataLenforPB - u2_BuffSize;
                        if( Dcm_Dsp_SID19_Sub18_u4RemainingResDataLenforPB != (uint32)0U )
                        {
                            b_LoopEnd = Dcm_Dsp_SID19_Sub18_ChkLoopEnd( u4_FFGetCount, u1_NextRecNum, &b_SendEvent, &b_SendPosRes );
                            /* If SendEvent flag and SendPosRes request flag are FALSE and LOOP end, execute SendNegRes (NRC0x10) */
                        }
                        else
                        {
                            Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
                            b_LoopEnd       = (boolean)TRUE;
                            b_SendPosRes    = (boolean)TRUE;
                        }
                    }
                    else
                    {
                        /* If the data larger than the total length is returned, the data is not set and the Dem acquisition is completed. */
                        /* For the remaining part, adjust 0 with Dcm_Dsp_SID19_Sub18_AdjustDataLenForPage */
                        Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
                        b_LoopEnd       = (boolean)TRUE;
                        b_SendPosRes    = (boolean)TRUE;
                    }
                }
                else
                {
                    /* u2_BuffSize is not an appropriate value */
                    Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
                    b_LoopEnd       = (boolean)TRUE;
                }
                break;
            case DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER:
                /* Check loop processing continue */
                b_LoopEnd = Dcm_Dsp_SID19_Sub18_ChkLoopEnd( u4_FFGetCount, u1_NextRecNum, &b_SendEvent, &b_SendPosRes );
                /* If SendEvent flag and SendPosRes request flag are FALSE and LOOP end, execute SendNegRes (NRC0x10) */
                break;
            case DEM_GET_FFDATABYDTC_PENDING:
                b_SendEvent = (boolean)TRUE;
                b_LoopEnd   = (boolean)TRUE;
                break;
            case DEM_GET_FFDATABYDTC_WRONG_DTC:
            case DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN:
                /* Abnormality was detected for items that have been confirmed to be normal with Dem_DcmDisableDTCRecordUpdate. */
                Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
                b_LoopEnd       = (boolean)TRUE;
                break;
            case DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE:
                b_LoopEnd       = (boolean)TRUE;
                b_SendPosRes    = (boolean)TRUE;
                break;
            default:
                /* Dem_DcmGetFreezeFrameDataByDTC return value is out of range. */
                Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
                b_LoopEnd       = (boolean)TRUE;
                break;
        }
    }

    if( b_SendEvent == (boolean)TRUE )
    {
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB18_GETFFDT );                           /* no return check required */
        u1_RetVal   = DCM_E_PENDING;
    }
    else
    {
        if( Dcm_Dsp_SID19_Sub18_bUpdatePageFlag == (boolean)FALSE )
        {
            if( b_SendPosRes == (boolean)TRUE )
            {
                if( Dcm_Dsp_SID19_Sub18_bGetFFDEnded == (boolean)TRUE )
                {
                    /* If reading of all RecordNumbers is completed before updatePage, correct the total length of data to the current data length and send it all at once */
                    Dcm_Dsp_SID19_Sub18_u4ResDataLenforPB = Dcm_Dsp_Main_stMsgContext.resDataLen;
                    Dcm_Dsp_SID19_Sub18_u4RemainingResDataLenforPB = (uint32)0;
                }
                else
                {
                    if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= Dcm_Dsp_SID19_Sub18_u4ResDataLenforPB )
                    {
                        /* If the total length of data is within resMaxDataLen, correct the total length of data to the current data length and send it all at once */
                        Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
                        Dcm_Dsp_SID19_Sub18_u4ResDataLenforPB = Dcm_Dsp_Main_stMsgContext.resDataLen;
                        Dcm_Dsp_SID19_Sub18_u4RemainingResDataLenforPB = (uint32)0;
                    }
                }
                Dcm_Dsp_SID19_Sub18_StartPage();
            }
            else
            {
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
            }
        }
        else
        {
            Dcm_Dsp_SID19_Sub18_AdjustDataLenForPage();
            
            if( Dcm_Dsp_Main_stMsgContext.resDataLen != (uint32)0U )
            {
                Dcm_Dsp_MsgMaker_ProcessPage( Dcm_Dsp_Main_stMsgContext.resDataLen );
            }
        }
    }

    return u1_RetVal;
}
#endif /* DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_ON */


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub18_ChkLoopEnd                           */
/* Description   | Confirm that a condition to finish a loop is concluded   */
/* Preconditions | None                                                     */
/* Parameters    | [IN]   u4FFGetCount      : Counter of DEM-API call       */
/*               | [OUT]  ptSendEvent       : Request Send Event            */
/*               | [OUT]  ptSendPosRes      : Request Positive Response     */
/* Return Value  | boolean                                                  */
/*               |   TRUE              : loop end                           */
/*               |   FALSE             : loop continue                      */
/* Notes         | None                                                     */
/****************************************************************************/
#if ( DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_OFF )
static FUNC(boolean, DCM_CODE) Dcm_Dsp_SID19_Sub18_ChkLoopEnd
(
    uint32                                      u4FFGetCount,
    uint8                                       u1NextRecNum,
    P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA)    ptSendEvent,
    P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA)    ptSendPosRes
)
{
    uint32          u4_MaxNumSSDat;
    boolean         b_LoopEnd;

    *ptSendEvent    = (boolean)FALSE;
    *ptSendPosRes   = (boolean)FALSE;
    b_LoopEnd       = (boolean)FALSE;
    u4_MaxNumSSDat  = (uint32)Dcm_Dsp_SID19_Sub18_u1Max_Num_SSDat;

    /* Confirm whether processing acquired all data. */
    if( u1NextRecNum == DEM_RECORDNUMBER_NEXT_NONE )
    {
        Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
        /* Acquired all FFData */
        b_LoopEnd       = (boolean)TRUE;
        *ptSendPosRes   = (boolean)TRUE;
    }
    else
    {
        if( Dcm_Dsp_SID19_Sub18_u1TgtRecNum < u1NextRecNum )
        {
            /* There are the data which processing has not yet acquired. */
            /* Target Report Number Update */
            Dcm_Dsp_SID19_Sub18_u1TgtRecNum = u1NextRecNum;
            /* Check Loop Counter */
            if( u4FFGetCount >= u4_MaxNumSSDat )
            {
                /* Maximum Loop Number Over  */
                b_LoopEnd       = (boolean)TRUE;
                *ptSendEvent    = (boolean)TRUE;
            }
        }
        else
        {
            Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
            /* OutPut of Dem_DcmGetFreezeFrameDataByDTC Method is Illegal */
            /* Loop End without SendEvent and SendPosRes */
            b_LoopEnd       = (boolean)TRUE;
        }
    }

    return b_LoopEnd;
}
#endif /* DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_OFF */
#if ( DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_ON )
static FUNC(boolean, DCM_CODE) Dcm_Dsp_SID19_Sub18_ChkLoopEnd
(
    uint32                                      u4FFGetCount,
    uint8                                       u1NextRecNum,
    P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA)    ptSendEvent,
    P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA)    ptSendPosRes
)
{
    uint32          u4_MaxNumSSDat;
    uint32          u4_WritableSize;
    boolean         b_LoopEnd;

    *ptSendEvent    = (boolean)FALSE;
    *ptSendPosRes   = (boolean)FALSE;
    b_LoopEnd       = (boolean)FALSE;
    u4_MaxNumSSDat  = (uint32)Dcm_Dsp_SID19_Sub18_u1Max_Num_SSDat;

    /* Confirm whether processing acquired all data. */
    if( u1NextRecNum == DEM_RECORDNUMBER_NEXT_NONE )
    {
        Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
        /* Acquired all FFData */
        b_LoopEnd       = (boolean)TRUE;
        *ptSendPosRes   = (boolean)TRUE;
    }
    else
    {
        if( Dcm_Dsp_SID19_Sub18_u1TgtRecNum < u1NextRecNum )
        {
            /* There are the data which processing has not yet acquired. */
            /* Target Report Number Update */
            Dcm_Dsp_SID19_Sub18_u1TgtRecNum = u1NextRecNum;
            u4_WritableSize                 = (uint32)(Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen); /* no wrap around */
            if( u4_WritableSize == (uint32)0U )
            {
                b_LoopEnd       = (boolean)TRUE;
                *ptSendPosRes   = (boolean)TRUE;
            }
            else
            {
                /* Check Loop Counter */
                if( u4FFGetCount >= u4_MaxNumSSDat )
                {
                    /* Maximum Loop Number Over  */
                    b_LoopEnd       = (boolean)TRUE;
                    *ptSendEvent    = (boolean)TRUE;
                }
            }
        }
        else
        {
            Dcm_Dsp_SID19_Sub18_bGetFFDEnded = (boolean)TRUE;
            /* OutPut of Dem_DcmGetFreezeFrameDataByDTC Method is Illegal */
            /* Loop End without SendEvent and SendPosRes */
            b_LoopEnd       = (boolean)TRUE;
        }
    }

    return b_LoopEnd;
}
#endif /* DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_ON */
#if ( DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub18_AdjustDataLenForPage                 */
/* Description   | Adjust data length for page                              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub18_AdjustDataLenForPage
(
    void
)
{
    uint32              u4_RemainingResDataLenforPB;
    uint32              u4_ResMaxPageLen;
    uint32              u4_ResRemainingPageLen;
    uint32              u4_ResDataLen;
    uint32              u4_ResDataPos;
    uint32              u4_PaddingMaxDataLen;
    uint32              u4_PaddingCnt;

    if( Dcm_Dsp_SID19_Sub18_bGetFFDEnded == (boolean)TRUE )
    {
        u4_RemainingResDataLenforPB = Dcm_Dsp_SID19_Sub18_u4RemainingResDataLenforPB;
        if( u4_RemainingResDataLenforPB > (uint32)0 )
        {
            u4_ResMaxPageLen       = Dcm_Dsp_Main_stMsgContext.resMaxDataLen;
            u4_ResDataLen          = Dcm_Dsp_Main_stMsgContext.resDataLen;
            u4_ResRemainingPageLen = u4_ResMaxPageLen - u4_ResDataLen; /* no wrap around */
            if( u4_RemainingResDataLenforPB > u4_ResRemainingPageLen )
            {
                u4_PaddingMaxDataLen = u4_ResMaxPageLen;
            }
            else
            {
                u4_PaddingMaxDataLen = u4_RemainingResDataLenforPB + u4_ResDataLen; /* no wrap around */
            }
            u4_PaddingCnt = u4_PaddingMaxDataLen - u4_ResDataLen; /* no wrap around */

            for( u4_ResDataPos = u4_ResDataLen; u4_ResDataPos < u4_PaddingMaxDataLen; u4_ResDataPos++ )
            {
                Dcm_Dsp_Main_stMsgContext.resData[u4_ResDataPos] = (uint8)0;
            }
            Dcm_Dsp_Main_stMsgContext.resDataLen  = u4_PaddingMaxDataLen;
            Dcm_Dsp_SID19_Sub18_u4RemainingResDataLenforPB = Dcm_Dsp_SID19_Sub18_u4RemainingResDataLenforPB - u4_PaddingCnt; /* no wrap around */
        }
    }
    return ;
}
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub18_StartPage                            */
/* Description   | Start paged processing of SID 19 SF 18                   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub18_StartPage
(
    void
)
{
    Dcm_MsgContextType  st_MsgContext;
    uint16              u2_PbidSid;

    u2_PbidSid = Dcm_P_u2Pbid_Sid19_Sub18;

    st_MsgContext.reqData                           = NULL_PTR;
    st_MsgContext.reqDataLen                        = (Dcm_MsgLenType)0U;
    st_MsgContext.resData                           = NULL_PTR;
    st_MsgContext.msgAddInfo.reqType                = (uint8)0U;
    st_MsgContext.msgAddInfo.suppressPosResponse    = STD_OFF;
    st_MsgContext.resMaxDataLen                     = (Dcm_MsgLenType)0U;
    st_MsgContext.idContext                         = (Dcm_IdContextType)0U;
    st_MsgContext.dcmRxPduId                        = (PduIdType)0U;
    st_MsgContext.resDataLen                        = Dcm_Dsp_SID19_Sub18_u4ResDataLenforPB;

    Dcm_Dsp_MsgMaker_StartPagedProcessing( &st_MsgContext, u2_PbidSid );

    return ;
}
#endif /* DCM_PAGEDBUFFER_SID19_SUB18_ENABLED == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID19_SUB18 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

