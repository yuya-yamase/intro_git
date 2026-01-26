/* Dcm_Dsp_SID19_Sub05_c(v5-0-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID19_Sub05/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID19_Sub05.h>
#if ( DCM_SUPPORT_SID19_SUB05 == STD_ON )
#include "../../Dsp/cfg/Dcm_Dsp_SID19_Sub05_Cfg.h"
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dem_Dcm.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     DCM_DSP_SID19_SUB05_ReqOffSDRNum              ((uint32)0U)
#define     DCM_DSP_SID19_SUB05_ResOffSDRNum              ((uint8)0U)
#define     DCM_DSP_SID19_SUB05_DSDRNumALL                ((uint8)0xFFU)
#define     DCM_DSP_SID19_SUB05_RecNumMin                 ((uint8)0x01U)
#define     DCM_DSP_SID19_SUB05_DSDRNumLen                ((uint32)1U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub05_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
);
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub05_CancelProc
(void);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub05_StDStDRec
(void);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub05_GetSizeOfDSDR
(void);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub05_GetDStDtRec
(void);
static FUNC(boolean , DCM_CODE) Dcm_Dsp_SID19_Sub05_ChkLoopEnd
(
    uint32                                      u4DSDRGetCount,
    uint8                                       u1NextRecNum,
    P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA)    ptSendEvent,
    P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA)    ptSendPosRes
);

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>


static VAR(uint8, DCM_VAR_NO_INIT)              Dcm_Dsp_SID19_Sub05_u1TgtRecNum;
static VAR(boolean, DCM_VAR_NO_INIT)            Dcm_Dsp_SID19_Sub05_bTgtAll;

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
/* Function Name | Dcm_SID19_Sub05                                          */
/* Description   | Request processing of SID 19_Sub05                       */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus      : Operation state                     */
/*               | [IN] pMsgContext   : Message Context                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SID19_Sub05 /* MISRA DEVIATION */
(
    Dcm_OpStatusType                                            OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA)       pMsgContext
)
{
    Std_ReturnType          u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID19_Sub05_InitialProc( pMsgContext );
        /* This Return Value is check-free */
    }
    else
    {
        Dcm_Dsp_SID19_Sub05_CancelProc();
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub05_StartStDCbk                          */
/* Description   | Call Back Function to Continue SID19_Sub05 Processing 1  */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub05_StartStDCbk /* MISRA DEVIATION */
(
    const uint8 u1EventId /* MISRA DEVIATION */
)
{
    Std_ReturnType      u1_RetStDStDRec;
    Std_ReturnType      u1_RetGetSize;
    Std_ReturnType      u1_RetGetDStDt;
    Std_ReturnType      u1_RetVal;

    u1_RetVal           = E_OK;

    u1_RetStDStDRec = Dcm_Dsp_SID19_Sub05_StDStDRec();
    if( u1_RetStDStDRec == (Std_ReturnType)E_OK )
    {
        /* This Route Acquire DTCStoredDataRecord */
        /* When Complete Operation, Carry Out a Function - Dem_DcmEndDTCStoredData */
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );

        u1_RetGetSize = Dcm_Dsp_SID19_Sub05_GetSizeOfDSDR();
        if( u1_RetGetSize == (Std_ReturnType)E_OK )
        {
            u1_RetGetDStDt = Dcm_Dsp_SID19_Sub05_GetDStDtRec();
            if( u1_RetGetDStDt == (Std_ReturnType)DCM_E_PENDING )
            {
                u1_RetVal = DCM_E_PENDING;
            }
            else
            {
                /* No process */
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
            /* SID19_Sub05 Operation Completed */
            /* Notify Acquisition of DTCStoredDataRecord was over */
            Dem_DcmEndDTCStoredData();
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        }
        else
        {
            /* SID19_Sub05 Operation Continue */
            /* No process */
        }
    }
    else
    {
        /* No process */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub05_GetSzStCbk                           */
/* Description   | Call Back Function to Continue SID19_Sub05 Processing 2  */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub05_GetSzStCbk /* MISRA DEVIATION */
(
    const uint8 u1EventId /* MISRA DEVIATION */
)
{
    Std_ReturnType      u1_RetGetSize;
    Std_ReturnType      u1_RetGetDStDt;
    Std_ReturnType      u1_RetVal;

    u1_RetVal           = E_OK;

    /* This Route Acquire DTCStoredDataRecord */
    /* When Complete Operation, Carry Out a Function - Dem_DcmEndDTCStoredData */

    u1_RetGetSize = Dcm_Dsp_SID19_Sub05_GetSizeOfDSDR();
    if( u1_RetGetSize == (Std_ReturnType)E_OK )
    {
        u1_RetGetDStDt = Dcm_Dsp_SID19_Sub05_GetDStDtRec();
        if( u1_RetGetDStDt == (Std_ReturnType)DCM_E_PENDING )
        {
            u1_RetVal = DCM_E_PENDING;
        }
        else
        {
            /* No process */
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
        /* SID19_Sub05 Operation Completed */
        /* Notify Acquisition of DTCStoredDataRecord was over */
        Dem_DcmEndDTCStoredData();
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }
    else
    {
        /* SID19_Sub05 Operation Continue */
        /* No process */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub05_GetStDtCbk                           */
/* Description   | Call Back Function to Continue SID19_Sub05 Processing 3  */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub05_GetStDtCbk /* MISRA DEVIATION */
(
    const uint8 u1EventId /* MISRA DEVIATION */
)
{
    Std_ReturnType      u1_RetGetDStDt;
    Std_ReturnType      u1_RetVal;

    u1_RetVal           = E_OK;

    /* This Route Acquire DTCStoredDataRecord */
    /* When Complete Operation, Carry Out a Function - Dem_DcmEndDTCStoredData */

    u1_RetGetDStDt = Dcm_Dsp_SID19_Sub05_GetDStDtRec();
    if( u1_RetGetDStDt == (Std_ReturnType)DCM_E_PENDING )
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
        /* SID19_Sub05 Operation Completed */
        /* Notify Acquisition of DTCStoredDataRecord was over */
        Dem_DcmEndDTCStoredData();
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }
    else
    {
        /* SID19_Sub05 Operation Continue */
        /* No process */
    }

    return;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub05_InitialProc                          */
/* Description   | Initial process of SID19_Sub05                           */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub05_InitialProc
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext
)
{
    boolean                         b_SendNegRes;
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    Std_ReturnType                  u1_RetStDStDRec;
    Std_ReturnType                  u1_RetGetSize;
    Std_ReturnType                  u1_RetGetDStDt;
    Std_ReturnType                  u1_RetVal;

    b_SendNegRes        = (boolean)FALSE;
    u1_RetVal           = E_OK;

    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    /* Set Common Data */
    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    Dcm_Dsp_SID19_Sub05_u1TgtRecNum = DCM_DSP_SID19_SUB05_DSDRNumALL;
    Dcm_Dsp_SID19_Sub05_bTgtAll     = (boolean)FALSE;

    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    /* Check Request Data Length */
    if( Dcm_Dsp_Main_stMsgContext.reqDataLen == DCM_DSP_SID19_SUB05_DSDRNumLen )
    {
        /* Check Request Record Number */
        if( ptMsgContext->reqData[DCM_DSP_SID19_SUB05_ReqOffSDRNum] == DCM_DSP_SID19_SUB05_DSDRNumALL )
        {
            /* Acquire Information for All Record Numbers [0xFF] */
            Dcm_Dsp_SID19_Sub05_bTgtAll = (boolean)TRUE;
            /* Maximum number has been already set in Target Record Number */
        }
        else
        {
            /* Acquire Information for One Record Number [0x00]-[0xFE] */
            Dcm_Dsp_SID19_Sub05_u1TgtRecNum = ptMsgContext->reqData[DCM_DSP_SID19_SUB05_ReqOffSDRNum];
        }

        u1_RetStDStDRec = Dcm_Dsp_SID19_Sub05_StDStDRec();
        if( u1_RetStDStDRec == (Std_ReturnType)E_OK )
        {
            /* This Route Acquire DTCStoredDataRecord */
            /* When Complete Operation, Carry Out a Function - Dem_DcmEndDTCStoredData */
            Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );

            u1_RetGetSize = Dcm_Dsp_SID19_Sub05_GetSizeOfDSDR();
            if( u1_RetGetSize == (Std_ReturnType)E_OK )
            {
                u1_RetGetDStDt = Dcm_Dsp_SID19_Sub05_GetDStDtRec();
                if( u1_RetGetDStDt == (Std_ReturnType)DCM_E_PENDING )
                {
                    u1_RetVal = DCM_E_PENDING;
                }
                else
                {
                    /* No process */
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
                /* SID19_Sub05 Operation Completed */
                /* Notify Acquisition of DTCStoredDataRecord was over */
                Dem_DcmEndDTCStoredData();
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
            }
            else
            {
                /* SID19_Sub05 Operation Continue */
                /* No process */
            }
        }
        else if( u1_RetStDStDRec == (Std_ReturnType)DCM_E_PENDING )
        {
            /* SID19_Sub05 Operation Continue */
            u1_RetVal = DCM_E_PENDING;
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
        b_SendNegRes    = (boolean)TRUE;
        u1_NegResCode   = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    if( b_SendNegRes == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub05_CancelProc                           */
/* Description   | Cancel process of SID19_Sub05 request                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID19_Sub05_CancelProc
(void)
{

    boolean                         b_UserNotify;
    Dcm_Main_EvtDistr_RetType       u1_RetDelGetDSDt;

    b_UserNotify    = Dcm_Dsp_Main_GetUserNotifyFlag();

    if( b_UserNotify == (boolean)TRUE )
    {
        /* SID19_Sub05 Operation Completed */
        /* End DTC Stored Data Call */
        Dem_DcmEndDTCStoredData();
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

        u1_RetDelGetDSDt = Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB05_GETDSDT, (boolean)FALSE );
        if( u1_RetDelGetDSDt != DCM_MAIN_EVTDISTR_E_OK )
        {
            (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB05_GETSIZE, (boolean)FALSE ); /* no return check required */
        }
    }
    else
    {
        (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID19_SUB05_STDSDATA, (boolean)FALSE ); /* no return check required */
    }
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub05_StDStDRec                            */
/* Description   | Call DEM-API Dem_DcmStartDTCStoredData                   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub05_StDStDRec
(void)
{
    Std_ReturnType                   u1_RetVal;
    Dem_ReturnStartStoredDataType    u1_RetStDStData;

    u1_RetVal = E_NOT_OK;

    u1_RetStDStData = Dem_DcmStartDTCStoredData();

    /* Check DEM-API Return Value */
    switch( u1_RetStDStData )
    {
        case DEM_START_STOREDDATA_OK:
            u1_RetVal = E_OK;
            break;
        case DEM_START_STOREDDATA_PENDING:
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB05_STDSDATA ); /* no return check required */
            u1_RetVal = DCM_E_PENDING;
            break;
        default:
            /* No process */
            break;
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub05_GetSizeOfDSDR                        */
/* Description   | Call DEM-API Dem_DcmGetSizeOfDTCStoredDataByRecNum       */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub05_GetSizeOfDSDR
(void)
{
    Std_ReturnType                          u1_RetVal;
    boolean                                 b_SendNegRes;
    Dcm_NegativeResponseCodeType            u1_NegResCode;
    Dem_ReturnGetSizeOfDataByRecNumType     u1_RetGetSizeData;
    uint32                                  u4_DSDRSize;

    u1_RetVal       = E_NOT_OK;
    b_SendNegRes    = (boolean)FALSE;
    u4_DSDRSize     = 0U;

    /* Get Size Of DTC Stored Data Record */
    u1_RetGetSizeData = Dem_DcmGetSizeOfDTCStoredDataByRecNum( Dcm_Dsp_SID19_Sub05_u1TgtRecNum, &u4_DSDRSize );

    /* Check DEM-API Return Value */
    switch( u1_RetGetSizeData )
    {
        case DEM_GETSIZE_STOREDDATA_OK:
            if( u4_DSDRSize == (uint32)0 )
            {
                u4_DSDRSize = DCM_DSP_SID19_SUB05_DSDRNumLen;
            }
            else
            {
                /* No process */
            }

            if( Dcm_Dsp_Main_stMsgContext.resMaxDataLen >= u4_DSDRSize )
            {
                if( Dcm_Dsp_SID19_Sub05_bTgtAll == (boolean)TRUE )
                {
                    Dcm_Dsp_SID19_Sub05_u1TgtRecNum = DCM_DSP_SID19_SUB05_RecNumMin;
                }
                else
                {
                    /* No process */
                }
                u1_RetVal = E_OK;
            }
            else
            {
                /* Size Of DTC Stored Data Record Exceeds Size Of the Response Buffer */
                /* Set ResponseTooLong[0x14] to NRC. */
                /* Send Negative Response */
                b_SendNegRes    = Dcm_Dsp_SID19_Sub05_bNegativeResponseSendResponseTooLong;
                /* Set Negative Response Code */
                u1_NegResCode   = DCM_E_RESPONSETOOLONG;
            }
            break;
        case DEM_GETSIZE_STOREDDATA_WRONG_RECNUM:
            /* Record Number Illegal. Set RequestOutOfRange[0x31] to NRC. */
            /* Send Negative Response */
            b_SendNegRes    = (boolean)TRUE;
            /* Set Negative Response Code */
            u1_NegResCode   = DCM_E_REQUESTOUTOFRANGE;
            break;
        case DEM_GETSIZE_STOREDDATA_PENDING:
            (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB05_GETSIZE ); /* no return check required */
            u1_RetVal = DCM_E_PENDING;
            break;
        case DEM_GETSIZE_STOREDDATA_FAILED:
            /* No process */
            break;
        default:
            /* No process */
            break;
    }

    if( b_SendNegRes == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, u1_NegResCode );
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub05_GetDStDtRec                          */
/* Description   | Call DEM-API Dem_DcmGetDTCStoredDataByRecNum             */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing abnormal                */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID19_Sub05_GetDStDtRec
(void)
{
    Std_ReturnType                          u1_RetVal;
    Dem_ReturnGetDTCStoredDataByRecNumType  u1_RetGetDStDt;
    uint32                                  u4_BuffSize;
    P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)  pt_WriteBuff;
    uint32                                  u4_DSDRGetCount;
    boolean                                 b_SendEvent;
    boolean                                 b_SendPosRes;
    boolean                                 b_LoopEnd;
    boolean                                 b_CheckNRCResponseTooLong;
    uint32                                  u4_BuffSize_bk;
    uint8                                   u1_NextRecNum;

    u4_DSDRGetCount = (uint32)0U;
    u1_RetVal       = E_NOT_OK;
    b_LoopEnd       = (boolean)FALSE;
    b_SendEvent     = (boolean)FALSE;
    b_SendPosRes    = (boolean)FALSE;

    while( b_LoopEnd == (boolean)FALSE )
    {
        u4_DSDRGetCount++;  /* no wrap around */
        u1_NextRecNum   = (uint8)0x0;

        u4_BuffSize  = (Dcm_Dsp_Main_stMsgContext.resMaxDataLen - Dcm_Dsp_Main_stMsgContext.resDataLen);    /* no wrap around */
        /* Take the backup of BuffSize */
        u4_BuffSize_bk = u4_BuffSize;
        pt_WriteBuff = &(Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen ]);
        /* Get DSData */
        u1_RetGetDStDt = Dem_DcmGetDTCStoredDataByRecNum( Dcm_Dsp_SID19_Sub05_u1TgtRecNum, pt_WriteBuff, &u4_BuffSize, &u1_NextRecNum );

        /* Check DEM-API Return Value */
        switch( u1_RetGetDStDt )
        {
            case DEM_GET_STOREDDATA_OK:
                if( u4_BuffSize <= u4_BuffSize_bk )
                {
                    /* Update Response Data Length */
                    Dcm_Dsp_Main_stMsgContext.resDataLen = Dcm_Dsp_Main_stMsgContext.resDataLen + u4_BuffSize;  /* no wrap around */
                    if( Dcm_Dsp_SID19_Sub05_bTgtAll == (boolean)TRUE )
                    {
                        /* Check loop processing continue */
                        b_LoopEnd = Dcm_Dsp_SID19_Sub05_ChkLoopEnd( u4_DSDRGetCount, u1_NextRecNum, &b_SendEvent, &b_SendPosRes );
                    }
                    else
                    {
                        /* Got DSData Of Target Record Number. */
                        /* Loop End */
                        b_LoopEnd       = (boolean)TRUE;
                        /* Positive Response */
                        b_SendPosRes    = (boolean)TRUE;
                    }
                }
                else
                {
                    /* Loop End */
                    b_LoopEnd       = (boolean)TRUE;
                }
                break;
            case DEM_GET_STOREDDATA_PENDING:
                /* Loop End */
                b_LoopEnd   = (boolean)TRUE;
                b_SendEvent = (boolean)TRUE;
                break;
            case DEM_GET_STOREDDATA_WRONG_RECNUM:
                if( Dcm_Dsp_SID19_Sub05_bTgtAll == (boolean)TRUE )
                {
                    /* Check loop processing continue */
                    b_LoopEnd = Dcm_Dsp_SID19_Sub05_ChkLoopEnd( u4_DSDRGetCount, u1_NextRecNum, &b_SendEvent, &b_SendPosRes );
                }
                else
                {
                    /* Loop End */
                    b_LoopEnd       = (boolean)TRUE;
                }
                break;
            case DEM_GET_STOREDDATA_WRONG_BUFFERSIZE:
                /* Loop End */
                b_LoopEnd       = (boolean)TRUE;
                b_CheckNRCResponseTooLong = Dcm_Dsp_SID19_Sub05_bNegativeResponseSendResponseTooLong;
                if( b_CheckNRCResponseTooLong == (boolean)TRUE )
                {
                    /* Record Number Illegal. Set ResponseTooLong[0x14] to NRC. */
                    Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_RESPONSETOOLONG );
                }
                else
                {
                    /* No process */
                }
                break;
            case DEM_GET_STOREDDATA_FAILED:
                /* Loop End */
                b_LoopEnd   = (boolean)TRUE;
                break;
            default:
                /* Loop End */
                b_LoopEnd   = (boolean)TRUE;
                break;
        }
    }

    if( b_SendPosRes == (boolean)TRUE )
    {
        if( Dcm_Dsp_Main_stMsgContext.resDataLen == (uint32)0 )
        {
            /* Server DTCStoredDataRecordNumber Set In Response Buffer */
            Dcm_Dsp_Main_stMsgContext.resData[ Dcm_Dsp_Main_stMsgContext.resDataLen ] = Dcm_Dsp_Main_stMsgContext.reqData[ DCM_DSP_SID19_SUB05_ReqOffSDRNum ];
            Dcm_Dsp_Main_stMsgContext.resDataLen = DCM_DSP_SID19_SUB05_DSDRNumLen;
        }
        else
        {
            /* No process */
        }
        Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
        u1_RetVal   = E_OK;
    }
    else if( b_SendEvent == (boolean)TRUE )
    {
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID19_SUB05_GETDSDT ); /* no return check required */
        u1_RetVal   = DCM_E_PENDING;
    }
    else
    {
        /* No process */
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID19_Sub05_ChkLoopEnd                           */
/* Description   | Confirm that a condition to finish a loop is concluded   */
/* Preconditions | None                                                     */
/* Parameters    | [IN]   u4DSDRGetCount  : DSDR Get Count                  */
/*               | [OUT]  ptSendEvent     : Send Event Flag                 */
/*               | [OUT]  ptSendPosRes    : Send Positive Response Flag     */
/* Return Value  | boolean                                                  */
/*               |   TRUE     : loop end                                    */
/*               |   FALSE    : loop continue                               */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_Dsp_SID19_Sub05_ChkLoopEnd
(
    uint32                                      u4DSDRGetCount,
    uint8                                       u1NextRecNum,
    P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA)    ptSendEvent,
    P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA)    ptSendPosRes
)
{
    boolean         b_LoopEnd;
    uint32          u4_MaxNumGetSDR;

    *ptSendPosRes   = (boolean)FALSE;
    *ptSendEvent    = (boolean)FALSE;
    b_LoopEnd       = (boolean)FALSE;
    u4_MaxNumGetSDR = (uint32)Dcm_Dsp_SID19_Sub05_u1MaxNumGetSDR_OnePeriod;

    /* Confirm whether processing acquired all data. */
    if( u1NextRecNum == DEM_RECORDNUMBER_NEXT_NONE )
    {
        /* Acquired all data */
        /* Loop End */
        b_LoopEnd       = (boolean)TRUE;
        /* Positive Response */
        *ptSendPosRes   = (boolean)TRUE;
    }
    else
    {
        if( Dcm_Dsp_SID19_Sub05_u1TgtRecNum < u1NextRecNum )
        {
            /* There are the data which processing has not yet acquired. */
            /* Target Record Number Update  */
            Dcm_Dsp_SID19_Sub05_u1TgtRecNum = u1NextRecNum;
            /* Check Loop Counter */
        if( u4DSDRGetCount >= u4_MaxNumGetSDR )
            {
                /* Maximum Loop Number Over  */
                /* Loop End */
                b_LoopEnd       = (boolean)TRUE;
                /* Set PENDING */
                *ptSendEvent    = (boolean)TRUE;
            }
            else
            {
                /* No process */
            }
        }
        else
        {
            /* OutPut of Dem_DcmGetDTCStoredDataByRecNum Method is Illegal */
            /* Loop End without SendEvent and SendPosRes */
            b_LoopEnd       = (boolean)TRUE;
        }
    }

    return b_LoopEnd;
}


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID19_SUB05 == STD_ON */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File************************************************************/
