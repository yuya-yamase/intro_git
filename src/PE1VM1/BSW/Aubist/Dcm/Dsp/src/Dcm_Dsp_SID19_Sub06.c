/* Dcm_Dsp_SID19_Sub06_c(v5-3-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID19_Sub06/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID19_Sub06.h>
#if ( DCM_SUPPORT_SID19_SUB06 == STD_ON )
#include "../../Dsp/cfg/Dcm_Dsp_SID19_Sub06_Cfg.h"
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Dsl_Ctrl.h>
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dem_Dcm.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DCM_DSP_SID19_SUB06_OFST_DTCHB          ((uint32)0U)
#define DCM_DSP_SID19_SUB06_OFST_DTCMB          ((uint32)1U)
#define DCM_DSP_SID19_SUB06_OFST_DTCLB          ((uint32)2U)
#define DCM_DSP_SID19_SUB06_OFST_DTCEDRN        ((uint32)3U)
#define DCM_DSP_SID19_SUB06_OFST_SODTC          ((uint32)3U)
#define DCM_DSP_SID19_SUB06_SHFT_DTCHB          ((uint8)16U)
#define DCM_DSP_SID19_SUB06_SHFT_DTCMB          ((uint8)8U)
#define DCM_DSP_SID19_SUB06_LEN_DTC             ((Dcm_MsgLenType)3U)
#define DCM_DSP_SID19_SUB06_LEN_DTCEDRN         ((Dcm_MsgLenType)1U)
#define DCM_DSP_SID19_SUB06_LEN_SODTC           ((Dcm_MsgLenType)1U)
#define DCM_DSP_SID19_SUB06_LEN_REQ             ((Dcm_MsgLenType)(DCM_DSP_SID19_SUB06_LEN_DTC + DCM_DSP_SID19_SUB06_LEN_DTCEDRN))
#define DCM_DSP_SID19_SUB06_LEN_RES_MIN         ((Dcm_MsgLenType)(DCM_DSP_SID19_SUB06_LEN_DTC + DCM_DSP_SID19_SUB06_LEN_SODTC))
#define DCM_DSP_SID19_SUB06_DTCEDRN_NUM00       ((uint8)0x00U)
#define DCM_DSP_SID19_SUB06_DTCEDRN_NUM01       ((uint8)0x01U)
#define DCM_DSP_SID19_SUB06_DTCEDRN_NUMFD       ((uint8)0xFDU)
#define DCM_DSP_SID19_SUB06_DTCEDRN_OBDMIN      ((uint8)0x90U)
#define DCM_DSP_SID19_SUB06_DTCEDRN_EMIOBDMAX   ((uint8)0x9FU)
#define DCM_DSP_SID19_SUB06_DTCEDRN_OBDMAX      ((uint8)0xEFU)
#define DCM_DSP_SID19_SUB06_DTCEDRN_OBDALL      ((uint8)0xFEU)
#define DCM_DSP_SID19_SUB06_DTCEDRN_ALL         ((uint8)0xFFU)
#define DCM_DSP_SID19_SUB06_TGTALL_ALL          ((uint8)0x00U) /* 0x01 to 0xFD */
#define DCM_DSP_SID19_SUB06_TGTALL_OBDALL       ((uint8)0x02U) /* 0x90 to 0xEF */
#define DCM_DSP_SID19_SUB06_TGTALL_EMIOBDALL    ((uint8)0x03U) /* 0x90 to 0x9F */
#define DCM_DSP_SID19_SUB06_EDR_SIZE_MAX        ((uint16)0xFFFFU)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub06_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
);
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub06_CancelProc
(
    void
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub06_DisDTCRec
(
    void
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub06_GetStsDtc
(
    void
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub06_GetSizeOfEDR
(
    void
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub06_GetEDR
(
    void
);
static FUNC(boolean, DCM_CODE) Dcm_Dsp_SID19_Sub06_ChkLoopEnd
(
    uint32                                      u4EDRGetCount,
    uint8                                       u1NextRecNum,
    P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA)    ptSendEvent,
    P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA)    ptSendPosRes
);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub06_ChkEnableRecNum
(
    const uint8 u1DTCRecNum
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

static VAR(uint32, DCM_VAR_NO_INIT) Dcm_Dsp_SID19_Sub06_u4DTC;
static VAR(uint8, DCM_VAR_NO_INIT) Dcm_Dsp_SID19_Sub06_u1TgtAllPattern;
static VAR(uint8, DCM_VAR_NO_INIT) Dcm_Dsp_SID19_Sub06_u1TgtRecNum;
static VAR(boolean, DCM_VAR_NO_INIT) Dcm_Dsp_SID19_Sub06_bTgtAll;

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
/* Function Name | Dcm_SID19_Sub06                                          */
/* Description   | Request processing of SID 19 SF 06                       */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus    : Operation state                       */
/*               | [IN] pMsgContext : Message Context                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SID19_Sub06
(
    Dcm_OpStatusType OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
)
{
    Std_ReturnType  u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID19_Sub06_InitialProc( pMsgContext );
    }
    else
    {
        Dcm_Dsp_SID19_Sub06_CancelProc();
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub06_DisUpdCbk                            */
/* Description   | Call Back Function to Continue SID19_Sub06 Processing 1  */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub06_DisUpdCbk
(
    const uint8 u1EventId
)
{
    Std_ReturnType  u1_RetDisRec;
    Std_ReturnType  u1_RetGetSts;
    Std_ReturnType  u1_RetGetSize;
    Std_ReturnType  u1_RetGetEDR;
    Std_ReturnType  u1_RetVal;

    u1_RetVal = E_OK;

    u1_RetDisRec = Dcm_Dsp_SID19_Sub06_DisDTCRec();
    if( u1_RetDisRec == (Std_ReturnType)E_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        u1_RetGetSts = Dcm_Dsp_SID19_Sub06_GetStsDtc();
        if( u1_RetGetSts == (Std_ReturnType)E_OK )
        {
            u1_RetGetSize = Dcm_Dsp_SID19_Sub06_GetSizeOfEDR();
            if( u1_RetGetSize == (Std_ReturnType)E_OK )
            {
                u1_RetGetEDR = Dcm_Dsp_SID19_Sub06_GetEDR();
                if( u1_RetGetEDR == (Std_ReturnType)DCM_E_PENDING )
                {
                    u1_RetVal = (Std_ReturnType)DCM_E_PENDING;
                }
            }
        }

        if( u1_RetVal != (Std_ReturnType)DCM_E_PENDING )
        {
            (void)Dem_DcmEnableDTCRecordUpdate();   /* no return check required */
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub06_GetExtDataCbk                        */
/* Description   | Call Back Function to Continue SID19_Sub06 Processing 2  */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub06_GetExtDataCbk
(
    const uint8 u1EventId
)
{
    Std_ReturnType  u1_RetGetEDR;

    u1_RetGetEDR = Dcm_Dsp_SID19_Sub06_GetEDR();

    if( u1_RetGetEDR != (Std_ReturnType)DCM_E_PENDING )
    {
        (void)Dem_DcmEnableDTCRecordUpdate();   /* no return check required */
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }

    return ;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub06_InitialProc                          */
/* Description   | Initial process of SID 19 SF 06 request                  */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext : Message Context                      */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub06_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    Std_ReturnType                  u1_RetDedrn;
    Std_ReturnType                  u1_RetDisRec;
    Std_ReturnType                  u1_RetGetSts;
    Std_ReturnType                  u1_RetGetSize;
    Std_ReturnType                  u1_RetGetEDR;
    Std_ReturnType                  u1_RetVal;
    boolean                         b_SendNegResFlag;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );

    u1_RetVal = E_OK;
    b_SendNegResFlag = (boolean)FALSE;

    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    Dcm_Dsp_SID19_Sub06_u4DTC = (uint32)0x00000000U;
    Dcm_Dsp_SID19_Sub06_u1TgtRecNum = (uint8)0x00;
    Dcm_Dsp_SID19_Sub06_bTgtAll = (boolean)FALSE;

    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    /* Check Request Data Length */
    if( Dcm_Dsp_Main_stMsgContext.reqDataLen == DCM_DSP_SID19_SUB06_LEN_REQ )
    {
        Dcm_Dsp_SID19_Sub06_u4DTC = (((uint32)ptMsgContext->reqData[DCM_DSP_SID19_SUB06_OFST_DTCHB]) << DCM_DSP_SID19_SUB06_SHFT_DTCHB ) |
                                    (((uint32)ptMsgContext->reqData[DCM_DSP_SID19_SUB06_OFST_DTCMB]) << DCM_DSP_SID19_SUB06_SHFT_DTCMB ) |
                                    (uint32)ptMsgContext->reqData[DCM_DSP_SID19_SUB06_OFST_DTCLB];

        /* Check Request Record Number */
        u1_RetDedrn = Dcm_Dsp_SID19_Sub06_ChkEnableRecNum( ptMsgContext->reqData[DCM_DSP_SID19_SUB06_OFST_DTCEDRN] );
        if( u1_RetDedrn == (Std_ReturnType)E_OK )
        {
            /* Check Response Data Area Length */
            if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= DCM_DSP_SID19_SUB06_LEN_RES_MIN )
            {
                u1_RetDisRec = Dcm_Dsp_SID19_Sub06_DisDTCRec();
                if( u1_RetDisRec == (Std_ReturnType)E_OK )
                {
                    /* This Route DTC Record Update Disabled */
                    /* When Complete Operation, Carry Out a Function - Dem_DcmEnableDTCRecordUpdate */
                    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
                    u1_RetGetSts = Dcm_Dsp_SID19_Sub06_GetStsDtc();
                    if( u1_RetGetSts == (Std_ReturnType)E_OK )
                    {
                        u1_RetGetSize = Dcm_Dsp_SID19_Sub06_GetSizeOfEDR();
                        if( u1_RetGetSize == (Std_ReturnType)E_OK )
                        {
                            u1_RetGetEDR = Dcm_Dsp_SID19_Sub06_GetEDR();
                            if( u1_RetGetEDR == (Std_ReturnType)DCM_E_PENDING )
                            {
                                /* SID19_Sub06 Operation Continue */
                                u1_RetVal = (Std_ReturnType)DCM_E_PENDING;
                            }
                        }
                    }

                    if( u1_RetVal != (Std_ReturnType)DCM_E_PENDING )
                    {
                        /* SID19_Sub06 Operation Completed */
                        /* Enable DTC Record Update */
                        (void)Dem_DcmEnableDTCRecordUpdate();   /* no return check required */
                        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
                    }
                }
                else if( u1_RetDisRec == (Std_ReturnType)DCM_E_PENDING )
                {
                    /* SID19_Sub06 Operation Continue */
                    u1_RetVal = (Std_ReturnType)DCM_E_PENDING;
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
                b_SendNegResFlag = (boolean)TRUE;
            }
        }
        else
        {
            /* RecordNumber Check NG */
            u1_NegResCode = DCM_E_REQUESTOUTOFRANGE;
            b_SendNegResFlag = (boolean)TRUE;
        }
    }
    else
    {
        /* Request Length Check NG */
        u1_NegResCode = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        b_SendNegResFlag = (boolean)TRUE;
    }

    if( b_SendNegResFlag == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                     u1_NegResCode );
    }

    return u1_RetVal;

}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub06_CancelProc                           */
/* Description   | Cancel process of SID 19 SF 06 request                   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub06_CancelProc
(
    void
)
{
    boolean                         b_UserNotify;

    b_UserNotify = Dcm_Dsp_Main_GetUserNotifyFlag();

    if( b_UserNotify == (boolean)TRUE )
    {
        (void)Dem_DcmEnableDTCRecordUpdate();   /* no return check required */
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB06_GETEDR,    /* no return check required */
                                             (boolean)FALSE );
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }
    else
    {
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB06_DISREC,    /* no return check required */
                                             (boolean)FALSE );
    }


    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub06_ChkEnableRecNum                      */
/* Description   | Check if DTCExtDataRecordNumber is enbabled              */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1DTCRecNum : RecordNumber                          */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK           : Processing normal                     */
/*               |   E_NOT_OK       : Processing not normal                 */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub06_ChkEnableRecNum
(
    const uint8 u1DTCRecNum
)
{
    uint16          u2_ConnectionId;
    Std_ReturnType  u1_RetVal;
    uint8           u1_ProtocolGroup;
    boolean         b_AcceptRepRecNumFF;
    boolean         b_OutputOnlyOBDRecNum;

    u1_RetVal = E_NOT_OK;

    u2_ConnectionId = (uint16)0x0000U;
    (void)Dcm_GetActiveProtocol( NULL_PTR,
                                 &u2_ConnectionId,
                                 NULL_PTR );

    u1_ProtocolGroup = Dcm_Dsl_GetActiveProtocolGroup( u2_ConnectionId );

    if( u1_ProtocolGroup == DCM_DSL_UDS_PROTOCOL )
    {
        if( u1DTCRecNum == DCM_DSP_SID19_SUB06_DTCEDRN_ALL )
        {
            Dcm_Dsp_SID19_Sub06_u1TgtAllPattern = DCM_DSP_SID19_SUB06_TGTALL_ALL;
            Dcm_Dsp_SID19_Sub06_bTgtAll = (boolean)TRUE;
            Dcm_Dsp_SID19_Sub06_u1TgtRecNum = DCM_DSP_SID19_SUB06_DTCEDRN_NUM01;
            u1_RetVal = E_OK;
        }
        else if( u1DTCRecNum == DCM_DSP_SID19_SUB06_DTCEDRN_OBDALL )
        {
            Dcm_Dsp_SID19_Sub06_u1TgtAllPattern = DCM_DSP_SID19_SUB06_TGTALL_OBDALL;
            Dcm_Dsp_SID19_Sub06_bTgtAll         = (boolean)TRUE;
            Dcm_Dsp_SID19_Sub06_u1TgtRecNum     = DCM_DSP_SID19_SUB06_DTCEDRN_OBDMIN;
            u1_RetVal = E_OK;
        }
        else
        {
            if( u1DTCRecNum != DCM_DSP_SID19_SUB06_DTCEDRN_NUM00 )
            {
                /* TargetAllFlg has been already set in FALSE */
                Dcm_Dsp_SID19_Sub06_u1TgtRecNum = u1DTCRecNum;
                u1_RetVal = E_OK;
            }
        }
    }
    else /* u1_ProtocolGroup equal DCM_DSL_OBD_PROTOCOL */
    {
        b_OutputOnlyOBDRecNum = Dcm_Dsp_SID19_Sub06_bOutputOnlyEmiOBDRecNumToOBDClient;
        if( b_OutputOnlyOBDRecNum == (boolean)TRUE )
        {
            if( u1DTCRecNum == DCM_DSP_SID19_SUB06_DTCEDRN_ALL )
            {
                b_AcceptRepRecNumFF = Dcm_Dsp_SID19_Sub06_bAcceptRepRecNumFF;
                if( b_AcceptRepRecNumFF == (boolean)TRUE )
                {
                    Dcm_Dsp_SID19_Sub06_u1TgtAllPattern = DCM_DSP_SID19_SUB06_TGTALL_EMIOBDALL;
                    Dcm_Dsp_SID19_Sub06_bTgtAll         = (boolean)TRUE;
                    Dcm_Dsp_SID19_Sub06_u1TgtRecNum     = DCM_DSP_SID19_SUB06_DTCEDRN_OBDMIN;
                    u1_RetVal = E_OK;
                }
            }
            else if( u1DTCRecNum == DCM_DSP_SID19_SUB06_DTCEDRN_OBDALL )
            {
                Dcm_Dsp_SID19_Sub06_u1TgtAllPattern = DCM_DSP_SID19_SUB06_TGTALL_EMIOBDALL;
                Dcm_Dsp_SID19_Sub06_bTgtAll         = (boolean)TRUE;
                Dcm_Dsp_SID19_Sub06_u1TgtRecNum     = DCM_DSP_SID19_SUB06_DTCEDRN_OBDMIN;
                u1_RetVal = E_OK;
            }
            else
            {
                if( ( u1DTCRecNum >= DCM_DSP_SID19_SUB06_DTCEDRN_OBDMIN ) &&
                    ( u1DTCRecNum <= DCM_DSP_SID19_SUB06_DTCEDRN_EMIOBDMAX ) )
                {
                    /* TargetAllFlg has been already set in FALSE */
                    Dcm_Dsp_SID19_Sub06_u1TgtRecNum = u1DTCRecNum;
                    u1_RetVal = E_OK;
                }
            }
        }
        else
        {
            if( u1DTCRecNum == DCM_DSP_SID19_SUB06_DTCEDRN_ALL )
            {
                b_AcceptRepRecNumFF = Dcm_Dsp_SID19_Sub06_bAcceptRepRecNumFF;
                if( b_AcceptRepRecNumFF == (boolean)TRUE )
                {
                    Dcm_Dsp_SID19_Sub06_u1TgtAllPattern = DCM_DSP_SID19_SUB06_TGTALL_ALL;
                    Dcm_Dsp_SID19_Sub06_bTgtAll         = (boolean)TRUE;
                    Dcm_Dsp_SID19_Sub06_u1TgtRecNum     = DCM_DSP_SID19_SUB06_DTCEDRN_NUM01;
                    u1_RetVal = E_OK;
                }
            }
            else if( u1DTCRecNum == DCM_DSP_SID19_SUB06_DTCEDRN_OBDALL )
            {
                Dcm_Dsp_SID19_Sub06_u1TgtAllPattern = DCM_DSP_SID19_SUB06_TGTALL_OBDALL;
                Dcm_Dsp_SID19_Sub06_bTgtAll         = (boolean)TRUE;
                Dcm_Dsp_SID19_Sub06_u1TgtRecNum     = DCM_DSP_SID19_SUB06_DTCEDRN_OBDMIN;
                u1_RetVal = E_OK;
            }
            else
            {
                if( u1DTCRecNum != DCM_DSP_SID19_SUB06_DTCEDRN_NUM00 )
                {
                    /* TargetAllFlg has been already set in FALSE */
                    Dcm_Dsp_SID19_Sub06_u1TgtRecNum = u1DTCRecNum;
                    u1_RetVal = E_OK;
                }
            }
        }
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub06_DisDTCRec                            */
/* Description   | Call DEM-API Dem_DcmDisableDTCRecordUpdate               */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/*               |   E_NOT_OK          : Processing not normal              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub06_DisDTCRec
(
    void
)
{
    Std_ReturnType                          u1_RetVal;
    Dem_ReturnDisableDTCRecordUpdateType    u1_RetDisDTCRec;

    u1_RetVal = E_NOT_OK;

    u1_RetDisDTCRec = Dem_DcmDisableDTCRecordUpdate( Dcm_Dsp_SID19_Sub06_u4DTC,
                                                     DEM_DTC_ORIGIN_PRIMARY_MEMORY );

    switch( u1_RetDisDTCRec )
    {
        case DEM_DISABLE_DTCRECUP_OK:
            u1_RetVal = E_OK;
            break;
        case DEM_DISABLE_DTCRECUP_WRONG_DTC:
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                         DCM_E_REQUESTOUTOFRANGE );
            break;
        case DEM_DISABLE_DTCRECUP_PENDING:
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB06_DISREC );    /* no return check required */
            u1_RetVal = (Std_ReturnType)DCM_E_PENDING;
            break;
        case DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN:
        default:
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                         DCM_E_GENERALREJECT );
            break;
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub06_GetStsDtc                            */
/* Description   | Call DEM-API Dem_DcmGetStatusOfDTC                       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing not normal              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub06_GetStsDtc
(
    void
)
{
    Std_ReturnType                  u1_RetVal;
    Dem_ReturnGetStatusOfDTCType    u1_RetGetStsDTC;
    uint8                           u1_DTCStatus;

    u1_RetVal = E_NOT_OK;
    u1_DTCStatus = 0x00U;

    u1_RetGetStsDTC = Dem_DcmGetStatusOfDTC( Dcm_Dsp_SID19_Sub06_u4DTC,
                                             DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                             &u1_DTCStatus );

    switch( u1_RetGetStsDTC )
    {
        case DEM_STATUS_OK:
            Dcm_Dsp_Main_stMsgContext.resData[ DCM_DSP_SID19_SUB06_OFST_DTCHB ] = Dcm_Dsp_Main_stMsgContext.reqData[ DCM_DSP_SID19_SUB06_OFST_DTCHB ];
            Dcm_Dsp_Main_stMsgContext.resData[ DCM_DSP_SID19_SUB06_OFST_DTCMB ] = Dcm_Dsp_Main_stMsgContext.reqData[ DCM_DSP_SID19_SUB06_OFST_DTCMB ];
            Dcm_Dsp_Main_stMsgContext.resData[ DCM_DSP_SID19_SUB06_OFST_DTCLB ] = Dcm_Dsp_Main_stMsgContext.reqData[ DCM_DSP_SID19_SUB06_OFST_DTCLB ];
            Dcm_Dsp_Main_stMsgContext.resData[ DCM_DSP_SID19_SUB06_OFST_SODTC ] = u1_DTCStatus;
            Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID19_SUB06_LEN_RES_MIN;
            u1_RetVal = E_OK;
            break;
        case DEM_STATUS_WRONG_DTC:
        case DEM_STATUS_WRONG_DTCORIGIN:
        case DEM_STATUS_FAILED:
        default:
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                         DCM_E_GENERALREJECT );
            break;
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub06_GetSizeOfEDR                         */
/* Description   | Call DEM-API Dem_DcmGetSizeOfExtendedDataRecordByDTC     */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing not normal              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub06_GetSizeOfEDR
(
    void
)
{
    uint16                              u2_EDRSize;
    Std_ReturnType                      u1_RetVal;
    Dem_ReturnGetSizeOfDataByDTCType    u1_RetGetSizeData;

    u1_RetVal = E_NOT_OK;
    u2_EDRSize = 0U;

    /* Because of get size of All data ,use Requested EDRN. */
    u1_RetGetSizeData = Dem_DcmGetSizeOfExtendedDataRecordByDTC( Dcm_Dsp_SID19_Sub06_u4DTC,
                                                                 DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                                                 Dcm_Dsp_Main_stMsgContext.reqData[DCM_DSP_SID19_SUB06_OFST_DTCEDRN],
                                                                 &u2_EDRSize );

    switch( u1_RetGetSizeData )
    {
        case DEM_GETSIZEBYDTC_OK:
            u1_RetVal = E_OK;
            break;
        case DEM_GETSIZEBYDTC_WRONG_RECNUM:
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                         DCM_E_REQUESTOUTOFRANGE );
            break;
        case DEM_GETSIZEBYDTC_WRONG_DTC:
        default:
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                         DCM_E_GENERALREJECT );
            break;
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub06_GetEDR                               */
/* Description   | Call DEM-API Dem_DcmGetExtendedDataRecordByDTC           */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub06_GetEDR
(
    void
)
{
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)      pt_WriteBuff;
    uint32                                      u4_WritableSize;
    uint32                                      u4_EDRGetCount;
    uint16                                      u2_BuffSize;
    Std_ReturnType                              u1_RetVal;
    Dem_ReturnGetExtendedDataRecordByDTCType    u1_RetGetEDR;
    Dcm_NegativeResponseCodeType                u1_NegResCode;
    uint8                                       u1_NextRecNum;
    boolean                                     b_SendPosRes;
    boolean                                     b_SendEvent;
    boolean                                     b_LoopEnd;

    u4_EDRGetCount = (uint32)0U;
    u1_RetVal = E_OK;
    u1_NegResCode = DCM_E_GENERALREJECT;
    b_SendPosRes = (boolean)FALSE;
    b_SendEvent = (boolean)FALSE;

    b_LoopEnd = (boolean)FALSE;

    while( b_LoopEnd == (boolean)FALSE )
    {
        u4_EDRGetCount++;   /* no wrap around */

        u1_NextRecNum = (uint8)0x0;

        u4_WritableSize = (uint32)(Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen); /* no wrap around */
        if( (uint32)DCM_DSP_SID19_SUB06_EDR_SIZE_MAX < (uint32)u4_WritableSize )
        {
            u2_BuffSize = DCM_DSP_SID19_SUB06_EDR_SIZE_MAX;
        }
        else
        {
            u2_BuffSize = (uint16)u4_WritableSize;
        }
        pt_WriteBuff = &(Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen ]);

        u1_RetGetEDR = Dem_DcmGetExtendedDataRecordByDTC( Dcm_Dsp_SID19_Sub06_u4DTC,
                                                          DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                                          Dcm_Dsp_SID19_Sub06_u1TgtRecNum,
                                                          pt_WriteBuff,
                                                          &u2_BuffSize,
                                                          &u1_NextRecNum );

        switch( u1_RetGetEDR )
        {
            case DEM_RECORD_OK:
                if( u4_WritableSize >= (uint32)u2_BuffSize )
                {
                    Dcm_Dsp_Main_stMsgContext.resDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen + (Dcm_MsgLenType)u2_BuffSize;  /* no wrap around */

                    if( Dcm_Dsp_SID19_Sub06_bTgtAll == (boolean)TRUE )
                    {
                        /* Check loop processing continue */
                        b_LoopEnd = Dcm_Dsp_SID19_Sub06_ChkLoopEnd( u4_EDRGetCount,
                                                                    u1_NextRecNum,
                                                                    &b_SendEvent,
                                                                    &b_SendPosRes );
                    }
                    else
                    {
                        /* Got EDR Of Target Record Number. */
                        b_LoopEnd = (boolean)TRUE;
                        b_SendPosRes = (boolean)TRUE;
                    }
                }
                else
                {
                    /* u2_BuffSize is not an appropriate value */
                    b_LoopEnd       = (boolean)TRUE;
                }
                break;
            case DEM_RECORD_WRONG_NUMBER:
                if( Dcm_Dsp_SID19_Sub06_bTgtAll == (boolean)TRUE )
                {
                    /* Check loop processing continue */
                    b_LoopEnd = Dcm_Dsp_SID19_Sub06_ChkLoopEnd( u4_EDRGetCount,
                                                                u1_NextRecNum,
                                                                &b_SendEvent,
                                                                &b_SendPosRes );
                }
                else
                {
                    u1_NegResCode = DCM_E_REQUESTOUTOFRANGE;
                    b_LoopEnd = (boolean)TRUE;
                }
                break;
            case DEM_RECORD_WRONG_BUFFERSIZE:
                u1_NegResCode = DCM_E_RESPONSETOOLONG;
                b_LoopEnd = (boolean)TRUE;
                break;
            case DEM_RECORD_WRONG_DTC:
            default:
                /* Default u1_NegResCode is DCM_E_GENERALREJECT */
                b_LoopEnd = (boolean)TRUE;
                break;
        }
    }

    if( b_SendEvent == (boolean)TRUE )
    {
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB06_GETEDR );    /* no return check required */
        u1_RetVal   = (Std_ReturnType)DCM_E_PENDING;
    }
    else
    {
        if( b_SendPosRes == (boolean)TRUE )
        {
            Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
        }
        else
        {
            Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext,
                                         u1_NegResCode );
        }
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub06_ChkLoopEnd                           */
/* Description   | Confirm that a condition to finish a loop is concluded   */
/* Preconditions | None                                                     */
/* Parameters    | [IN]   u4EDRGetCount     : Counter of DEM-API call       */
/*               | [OUT]  ptSendEvent       : Request Send Event            */
/*               | [OUT]  ptSendPosRes      : Request Positive Response     */
/* Return Value  | boolean                                                  */
/*               |   TRUE              : loop end                           */
/*               |   FALSE             : loop continue                      */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_Dsp_SID19_Sub06_ChkLoopEnd
(
    uint32                                      u4EDRGetCount,
    uint8                                       u1NextRecNum,
    P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA)    ptSendEvent,
    P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA)    ptSendPosRes
)
{
    uint32          u4_MaxNumEDR;
    uint8           u1_TgtAllPattern;
    uint8           u1_TgtRecNum;
    boolean         b_LoopEnd;

    *ptSendEvent        = (boolean)FALSE;
    *ptSendPosRes       = (boolean)FALSE;
    b_LoopEnd           = (boolean)FALSE;
    u1_TgtAllPattern    = Dcm_Dsp_SID19_Sub06_u1TgtAllPattern;
    u1_TgtRecNum        = Dcm_Dsp_SID19_Sub06_u1TgtRecNum;
    u4_MaxNumEDR        = (uint32)Dcm_Dsp_SID19_Sub06_u1Max_Num_EDR;

    /* Confirm whether processing acquired all data. */
    if( u1NextRecNum == DEM_RECORDNUMBER_NEXT_NONE )
    {
        /* Acquired all EDR */
        b_LoopEnd = (boolean)TRUE;
        *ptSendPosRes = (boolean)TRUE;
    }
    else
    {
        if( u1_TgtRecNum < u1NextRecNum )
        {
            if( u1_TgtAllPattern == DCM_DSP_SID19_SUB06_TGTALL_OBDALL )
            {
                if( u1NextRecNum > DCM_DSP_SID19_SUB06_DTCEDRN_OBDMAX )
                {
                    /* Acquired all RegulatedOBD EDR ( from 0x90 to 0xEF )  */
                    b_LoopEnd = (boolean)TRUE;
                    *ptSendPosRes = (boolean)TRUE;
                }
            }
            else if( u1_TgtAllPattern == DCM_DSP_SID19_SUB06_TGTALL_EMIOBDALL )
            {
                if( u1NextRecNum > DCM_DSP_SID19_SUB06_DTCEDRN_EMIOBDMAX )
                {
                    /* Acquired all RegulatedEmissionsOBD EDR ( from 0x90 to 0x9F )  */
                    b_LoopEnd = (boolean)TRUE;
                    *ptSendPosRes = (boolean)TRUE;
                }
            }
            else
            {
                if( u1NextRecNum > DCM_DSP_SID19_SUB06_DTCEDRN_NUMFD )
                {
                    /* Acquired all EDR ( from 0x01 to 0xFD ) */
                    b_LoopEnd = (boolean)TRUE;
                    *ptSendPosRes = (boolean)TRUE;
                }
            }

            if( b_LoopEnd != (boolean)TRUE )
            {
                /* There are the data which processing has not yet acquired. */
                Dcm_Dsp_SID19_Sub06_u1TgtRecNum = u1NextRecNum;

                if( u4EDRGetCount >= u4_MaxNumEDR )
                {
                    /* Maximum Loop Number Over  */
                    b_LoopEnd = (boolean)TRUE;
                    *ptSendEvent = (boolean)TRUE;
                }
            }
        }
        else
        {
            /* OutPut of Dem_DcmGetExtendedDataRecordByDTC Method is Illegal */
            b_LoopEnd = (boolean)TRUE;
        }
    }

    return b_LoopEnd;
}


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID19_SUB06 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

