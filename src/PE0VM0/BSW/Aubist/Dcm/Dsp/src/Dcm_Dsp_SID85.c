/* Dcm_Dsp_SID85_c(v5-0-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Dsp_SID85/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dcm/Dcm_Dsp_SID85.h>
#if ( DCM_SUPPORT_SID85 == STD_ON )
#include "../../Dsp/cfg/Dcm_Dsp_SID85_Cfg.h"
#include "../../Dsp/usr/Dcm_Dsp_SID85_Connector.h"
#include <Dcm/Dcm_Dsp_Main.h>
#include "../../Dsp/inc/Dcm_Dsp_MsgMaker.h"
#include "../../Dsd/inc/Dcm_Dsd_ServiceMng.h"
#include <Dcm/Dcm_Main_EvtDistr.h>
#include <Dem_Dcm.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     DCM_DSP_SID85_SID                           ((uint8)0x85U)
#define     DCM_DSP_SID85_ENA_DTC                       ((uint8)0xAAU)
#define     DCM_DSP_SID85_DIS_DTC                       ((uint8)0x55U)
#define     DCM_DSP_SID85_INIT_PDUID_VAL                ((uint16)0xFFFFU)
#define     DCM_DSP_SID85_SET_PDUID                     ((uint8)0xAAU)
#define     DCM_DSP_SID85_UNSET_PDUID                   ((uint8)0x00U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID85_CtrlDtcSetting
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext,
    const uint8             u1CtrlMode
);
#if ( DCM_SUPPORT_SID85_SUB01 == STD_ON )
static FUNC(void, DCM_CODE) Dcm_Dsp_SID85_Sub01_CancelProc
(
    void
);
#endif /* DCM_SUPPORT_SID85_SUB01 == STD_ON */
#if ( DCM_SUPPORT_SID85_SUB02 == STD_ON )
static FUNC(void, DCM_CODE) Dcm_Dsp_SID85_Sub02_CancelProc
(
    void
);
#endif /* DCM_SUPPORT_SID85_SUB02 == STD_ON */
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID85_EnableDTCSetting
(
    const uint32            u4DTCGroup,
    const Dem_DTCKindType   u1DTCKind,
    P2VAR(Dem_ReturnControlDTCSettingType, AUTOMATIC, DCM_APPL_DATA) ptRetControlDTCSetting
);

#if ( DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_OFF )
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID85_DisableDTCSetting
(
    const uint32            u4DTCGroup,
    const Dem_DTCKindType   u1DTCKind,
    P2VAR(Dem_ReturnControlDTCSettingType, AUTOMATIC, DCM_APPL_DATA) ptRetControlDTCSetting
);

static FUNC(void, DCM_CODE) Dcm_Dsp_SID85_SetPduId
(
    const PduIdType         u2PduId
);
#endif /* DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_OFF */

static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID85_GetPduId
(
    P2VAR(PduIdType, AUTOMATIC, DCM_APPL_DATA) ptPduId
);
static FUNC(void, DCM_CODE) Dcm_Dsp_SID85_ClearPduId
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


static VAR(uint8, DCM_VAR_NO_INIT)              Dcm_Dsp_SID85_u1CtrlDTCSetting;
static VAR(uint8, DCM_VAR_NO_INIT)              Dcm_Dsp_SID85_u1SetPduId;
static VAR(PduIdType, DCM_VAR_NO_INIT)          Dcm_Dsp_SID85_u2PduId;
static VAR( uint8, DCM_VAR_NO_INIT )            Dcm_Dsp_SID85_CtrlMode;

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

#if ( DCM_SUPPORT_SID85_SUB01 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_SID85_Sub01                                          */
/* Description   | Request processing of SID 85 SF 01                       */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus    : Operation state                       */
/*               | [IN] pMsgContext : Message Context                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SID85_Sub01           /* MISRA DEVIATION */
(
    Dcm_OpStatusType                                            OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA)       pMsgContext
)
{
    Std_ReturnType          u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID85_CtrlDtcSetting( pMsgContext , DCM_DSP_SID85_SF_ENABLE );
        /* This Return Value is check-free                                  */
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        Dcm_Dsp_SID85_Sub01_CancelProc();
    }
    else
    {
        /* No process                                                       */
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID85_SUB01 == STD_ON */


#if ( DCM_SUPPORT_SID85_SUB02 == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_SID85_Sub02                                          */
/* Description   | Request processing of SID 85 SF 02                       */
/* Preconditions | None                                                     */
/* Parameters    | [IN] OpStatus    : Operation state                       */
/*               | [IN] pMsgContext : Message Context                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_SID85_Sub02           /* MISRA DEVIATION */
(
    Dcm_OpStatusType                                            OpStatus,
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA)       pMsgContext
)
{
    Std_ReturnType          u1_RetVal;

    u1_RetVal = E_OK;

    if( OpStatus == (Dcm_OpStatusType)DCM_INITIAL )
    {
        u1_RetVal = Dcm_Dsp_SID85_CtrlDtcSetting( pMsgContext , DCM_DSP_SID85_SF_DISABLE );
        /* This Return Value is check-free                                  */
    }
    else if( OpStatus == (Dcm_OpStatusType)DCM_CANCEL )
    {
        Dcm_Dsp_SID85_Sub02_CancelProc();
    }
    else
    {
        /* No process                                                       */
    }

    return u1_RetVal;
}
#endif /* DCM_SUPPORT_SID85_SUB02 == STD_ON */


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID85_Init                                       */
/* Description   | SID 85 initialization                                    */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID85_Init                  /* MISRA DEVIATION */
(
    void
)
{
    /* Common Data Initialize                                               */
    /*  ControlDTCSetting Initial Status is Enable                          */
    Dcm_Dsp_SID85_u1CtrlDTCSetting = DCM_DSP_SID85_ENA_DTC;
    /*  PduId Data Clear                                                    */
    Dcm_Dsp_SID85_ClearPduId();

    return;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID85_NotifySesCtrl                              */
/* Description   | This function is started at the time of session control. */
/*               | It perform the reconstruction handling of DTCSetting     */
/*               | state with the session control.                          */
/* Preconditions | None                                                     */
/* Parameters    | [IN]   u1SesCtrlTypeOld    : Old Session Ctrl Type       */
/*               | [IN]   u1SesCtrlTypeNew    : New Session Ctrl Type       */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, DCM_CODE) Dcm_Dsp_SID85_NotifySesCtrl         /* MISRA DEVIATION */
(
    const Dcm_SesCtrlType   u1SesCtrlTypeOld,
    const Dcm_SesCtrlType   u1SesCtrlTypeNew
)
{
    Std_ReturnType      u1_RetGetPduId;
    PduIdType           u2_PduId;
    Std_ReturnType      u1_RetOldSesSpt;
    Std_ReturnType      u1_RetNewSesSpt;
    Dem_ReturnControlDTCSettingType     u1_RetControlDTCSetting;
    boolean             b_CheckReEnableDTCSet;

    b_CheckReEnableDTCSet = Dcm_Dsp_SID85_bReEnableDTCSet;
    if( b_CheckReEnableDTCSet == (boolean)TRUE )
    {
        u2_PduId            = DCM_DSP_SID85_INIT_PDUID_VAL;
        u1_RetControlDTCSetting = DEM_CONTROL_DTC_SETTING_OK;

        u1_RetGetPduId = Dcm_Dsp_SID85_GetPduId( &u2_PduId );
        if( (u1_RetGetPduId == (Std_ReturnType)E_OK) && (Dcm_Dsp_SID85_u1CtrlDTCSetting == DCM_DSP_SID85_DIS_DTC) )
        {
            /* This Route Dcm_Dsp_SID85_u2PduId is effective value          */
            /* Check u1SesCtrlTypeOld(old session state) supports SID85.    */
            u1_RetOldSesSpt = Dcm_Dsd_ChkServiceSupported( (uint8)DCM_DSP_SID85_SID, u2_PduId, u1SesCtrlTypeOld );
            if( u1_RetOldSesSpt == (Std_ReturnType)E_OK )
            {
                /* Supported                                                */
            /* Check u1SesCtrlTypeOld(old session state) supports SID85.    */
                u1_RetNewSesSpt = Dcm_Dsd_ChkServiceSupported( DCM_DSP_SID85_SID, u2_PduId, u1SesCtrlTypeNew );
                if( u1_RetNewSesSpt != (Std_ReturnType)E_OK )
                {
                    /* Not Supported                                        */
                    (void)Dcm_Dsp_SID85_EnableDTCSetting( (uint32)DEM_DTC_GROUP_ALL_DTCS, (Dem_DTCKindType)DEM_DTC_KIND_ALL_DTCS, &u1_RetControlDTCSetting);    /* no return check required */
                }
                else
                {
                    /* Supported                                            */
                    /* No process                                           */
                }
            }
            else
            {
                /* Not Supported                                            */
                /* No process                                               */
            }
        }
        else
        {
            /* This Route Dcm_Dsp_SID85_u2PduId is invalid value            */
            /* No process */
        }
    }
    else
    {
        /* Configuration Value is FALSE                                     */
        /* No process */
    }

    return;
}


#if ( DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID85_Confirmation                               */
/* Description   | Complete SID85 request.                                  */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1IdContext     : Id Context                        */
/*               | [IN] u2ConnectionId  : Source Address                    */
/*               | [IN] u1Status        : Status                            */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID85_Confirmation    /* MISRA DEVIATION */
(
    const Dcm_IdContextType u1IdContext,             /* MISRA DEVIATION */
    const uint16 u2ConnectionId,                     /* MISRA DEVIATION */
    const Dcm_ConfirmationStatusType u1Status
)
{
    uint8                           u1_SetTiming;
    uint8                           u1_CtrlMode;

    u1_CtrlMode = Dcm_Dsp_SID85_CtrlMode;

    if( u1Status == (Dcm_ConfirmationStatusType)DCM_RES_POS_OK )
    {
        u1_SetTiming = Dcm_Dsp_SID85_u1DTCSettingTiming;
        if( u1_SetTiming == DCM_P_DTCSETTING_CNF )
        {
            if( u1_CtrlMode == DCM_DSP_SID85_SF_ENABLE )
            {
                (void)Dcm_Dsp_SID85_Cnct_Sw_DTCSet( RTE_MODE_DcmControlDTCSetting_ENABLEDTCSETTING ); /* no return check required */
            }
            else if( u1_CtrlMode == DCM_DSP_SID85_SF_DISABLE )
            {
                (void)Dcm_Dsp_SID85_Cnct_Sw_DTCSet( RTE_MODE_DcmControlDTCSetting_DISABLEDTCSETTING ); /* no return check required */
            }
            else
            {
                /* No process */
            }
        }
    }

    return;
}

#endif /* DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_ON */

#if ( DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID85_Confirmation                               */
/* Description   | Complete SID85 request.                                  */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1IdContext     : Id Context                        */
/*               | [IN] u2ConnectionId  : Source Address                    */
/*               | [IN] u1Status        : Status                            */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID85_Confirmation    /* MISRA DEVIATION */
(
    const Dcm_IdContextType u1IdContext,             /* MISRA DEVIATION */
    const uint16 u2ConnectionId,                     /* MISRA DEVIATION */
    const Dcm_ConfirmationStatusType u1Status
)
{
    uint8                           u1_SetTiming;
    uint32                          u4_DTCGroup;
    Dem_DTCKindType                 u1_DTCKind;
    Dem_ReturnControlDTCSettingType u1_RetControlDTCSetting;
    uint8                           u1_CtrlMode;

    u4_DTCGroup = (uint32)DEM_DTC_GROUP_ALL_DTCS;
    u1_DTCKind = (Dem_DTCKindType)DEM_DTC_KIND_ALL_DTCS;
    u1_RetControlDTCSetting = (Dem_ReturnControlDTCSettingType)DEM_CONTROL_DTC_SETTING_OK;
    u1_CtrlMode = Dcm_Dsp_SID85_CtrlMode;

    if( u1Status == (Dcm_ConfirmationStatusType)DCM_RES_POS_OK )
    {
        u1_SetTiming = Dcm_Dsp_SID85_u1DTCSettingTiming;
        if( u1_SetTiming == DCM_P_DTCSETTING_CNF )
        {
            if( u1_CtrlMode == DCM_DSP_SID85_SF_ENABLE )
            {
                (void)Dcm_Dsp_SID85_EnableDTCSetting( u4_DTCGroup, u1_DTCKind, &u1_RetControlDTCSetting ); /* no return check required */
            }
            else if( u1_CtrlMode == DCM_DSP_SID85_SF_DISABLE )
            {
                (void)Dcm_Dsp_SID85_DisableDTCSetting( u4_DTCGroup, u1_DTCKind, &u1_RetControlDTCSetting ); /* no return check required */
            }
            else
            {
                /* No process */
            }
        }
    }

    return;
}

#endif /* DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_OFF */

#if ( DCM_SUPPORT_SID85_SUB01 == STD_ON )
#if ( DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID85_Sub01_Cbk                                  */
/* Description   | Call Back Function to Continue SID85_Sub01 Processing    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID85_Sub01_Cbk  /* MISRA DEVIATION */
(
    const uint8 u1EventId   /* MISRA DEVIATION */
)
{
    uint8               u1_SetTiming;
    Std_ReturnType      u1_RetSetProc;

    u1_RetSetProc = Dcm_Dsp_SID85_ControlProcess( Dcm_Dsp_SID85_CtrlMode, DCM_PENDING, Dcm_Dsp_Main_stMsgContext.reqData );
    if( u1_RetSetProc == (Std_ReturnType)E_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        u1_SetTiming = Dcm_Dsp_SID85_u1DTCSettingTiming;
        if( u1_SetTiming == DCM_P_DTCSETTING_IND )
        {
            (void)Dcm_Dsp_SID85_Cnct_Sw_DTCSet( RTE_MODE_DcmControlDTCSetting_ENABLEDTCSETTING ); /* no return check required */
        }
        Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
    }
    else if( u1_RetSetProc == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID85_SUB01_ENA_DTC ); /* no return check required */
    }
    else
    {
        /* NRC 0x22 */
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_CONDITIONSNOTCORRECT );
    }

    return;
}
#endif /* DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_ON */

#if ( DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID85_Sub01_Cbk                                  */
/* Description   | Call Back Function to Continue SID85_Sub01 Processing    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID85_Sub01_Cbk  /* MISRA DEVIATION */
(
    const uint8 u1EventId   /* MISRA DEVIATION */
)
{
    uint8                           u1_SetTiming;
    uint8                           u1_InvalidOpRecord;
    uint32                          u4_DTCGroup;
    Dem_DTCKindType                 u1_DTCKind;
    Dem_ReturnControlDTCSettingType u1_RetControlDTCSetting;
    Std_ReturnType                  u1_RetSetProc;
    Std_ReturnType                  u1_RetCtrlDTCSet;

    u4_DTCGroup             = (uint32)DEM_DTC_GROUP_ALL_DTCS;
    u1_DTCKind              = (Dem_DTCKindType)DEM_DTC_KIND_ALL_DTCS;
    u1_RetControlDTCSetting = (Dem_ReturnControlDTCSettingType)DEM_CONTROL_DTC_SETTING_OK;
    u1_InvalidOpRecord      = (uint8)0x00U;

    /* Set Dcm_Dsp_Main_UserNotifyFlag in FALSE */
    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    u1_RetSetProc = Dcm_Dsp_SID85_ControlProcess( Dcm_Dsp_SID85_CtrlMode, DCM_PENDING, &u1_InvalidOpRecord );
    if( u1_RetSetProc == (Std_ReturnType)E_OK )
    {
        u1_SetTiming = Dcm_Dsp_SID85_u1DTCSettingTiming;
        if( u1_SetTiming == DCM_P_DTCSETTING_IND )
        {
            u1_RetCtrlDTCSet = Dcm_Dsp_SID85_EnableDTCSetting( u4_DTCGroup, u1_DTCKind, &u1_RetControlDTCSetting );
            if( u1_RetCtrlDTCSet == (Std_ReturnType)E_OK )
            {
                Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
            }
            else if( u1_RetControlDTCSetting == (Dem_ReturnControlDTCSettingType)DEM_CONTROL_DTC_SETTING_N_OK )
            {
                /* NRC 0x22 */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_CONDITIONSNOTCORRECT );
            }
            else
            {
                /* No process */
            }
        }
        else
        {
            Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
        }
    }
    else if( u1_RetSetProc == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID85_SUB01_ENA_DTC ); /* no return check required */
    }
    else
    {
        /* NRC 0x22 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_CONDITIONSNOTCORRECT );
    }

    return;
}
#endif /* DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_OFF */
#endif /* DCM_SUPPORT_SID85_SUB01 == STD_ON */

#if ( DCM_SUPPORT_SID85_SUB02 == STD_ON )
#if ( DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID85_Sub02_Cbk                                  */
/* Description   | Call Back Function to Continue SID85_Sub02 Processing    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID85_Sub02_Cbk  /* MISRA DEVIATION */
(
    const uint8 u1EventId   /* MISRA DEVIATION */
)
{
    uint8               u1_SetTiming;
    Std_ReturnType      u1_RetSetProc;

    u1_RetSetProc = Dcm_Dsp_SID85_ControlProcess( Dcm_Dsp_SID85_CtrlMode, DCM_PENDING, Dcm_Dsp_Main_stMsgContext.reqData );
    if( u1_RetSetProc == (Std_ReturnType)E_OK )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        u1_SetTiming = Dcm_Dsp_SID85_u1DTCSettingTiming;
        if( u1_SetTiming == DCM_P_DTCSETTING_IND )
        {
            (void)Dcm_Dsp_SID85_Cnct_Sw_DTCSet( RTE_MODE_DcmControlDTCSetting_DISABLEDTCSETTING ); /* no return check required */
        }
        Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
    }
    else if( u1_RetSetProc == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID85_SUB02_DIS_DTC ); /* no return check required */
    }
    else
    {
        /* NRC 0x22 */
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_CONDITIONSNOTCORRECT );
    }

    return;
}
#endif /* DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_ON */

#if ( DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID85_Sub02_Cbk                                  */
/* Description   | Call Back Function to Continue SID85_Sub02 Processing    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u1EventId : Event ID                                */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, DCM_CODE ) Dcm_Dsp_SID85_Sub02_Cbk  /* MISRA DEVIATION */
(
    const uint8 u1EventId   /* MISRA DEVIATION */
)
{
    uint8                           u1_SetTiming;
    uint8                           u1_InvalidOpRecord;
    uint32                          u4_DTCGroup;
    Dem_DTCKindType                 u1_DTCKind;
    Dem_ReturnControlDTCSettingType u1_RetControlDTCSetting;
    Std_ReturnType                  u1_RetSetProc;
    Std_ReturnType                  u1_RetCtrlDTCSet;

    u4_DTCGroup             = (uint32)DEM_DTC_GROUP_ALL_DTCS;
    u1_DTCKind              = (Dem_DTCKindType)DEM_DTC_KIND_ALL_DTCS;
    u1_RetControlDTCSetting = (Dem_ReturnControlDTCSettingType)DEM_CONTROL_DTC_SETTING_OK;
    u1_InvalidOpRecord      = (uint8)0x00U;

    /* Set Dcm_Dsp_Main_UserNotifyFlag in FALSE */
    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );

    u1_RetSetProc = Dcm_Dsp_SID85_ControlProcess( Dcm_Dsp_SID85_CtrlMode, DCM_PENDING, &u1_InvalidOpRecord );
    if( u1_RetSetProc == (Std_ReturnType)E_OK )
    {
        u1_SetTiming = Dcm_Dsp_SID85_u1DTCSettingTiming;
        if( u1_SetTiming == DCM_P_DTCSETTING_IND )
        {
            u1_RetCtrlDTCSet = Dcm_Dsp_SID85_DisableDTCSetting( u4_DTCGroup, u1_DTCKind, &u1_RetControlDTCSetting );
            if( u1_RetCtrlDTCSet == (Std_ReturnType)E_OK )
            {
                Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
            }
            else if( u1_RetControlDTCSetting == (Dem_ReturnControlDTCSettingType)DEM_CONTROL_DTC_SETTING_N_OK )
            {
                /* NRC 0x22 */
                Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_CONDITIONSNOTCORRECT );
            }
            else
            {
                /* No process */
            }
        }
        else
        {
            Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
        }
    }
    else if( u1_RetSetProc == (Std_ReturnType)DCM_E_PENDING )
    {
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID85_SUB02_DIS_DTC ); /* no return check required */
    }
    else
    {
        /* NRC 0x22 */
        Dcm_Dsp_MsgMaker_SendNegRes( &Dcm_Dsp_Main_stMsgContext, DCM_E_CONDITIONSNOTCORRECT );
    }

    return;
}
#endif /* DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_OFF */
#endif /* DCM_SUPPORT_SID85_SUB02 == STD_ON */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#if ( DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID85_CtrlDtcSetting                             */
/* Description   | SID85_Sub01/SID85_Sub02 Control Function                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/*               | [IN] u1CtrlMode     : Sub Function                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID85_CtrlDtcSetting
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext,
    const uint8    u1CtrlMode
)
{
    boolean                         b_SendPosRes;
    boolean                         b_SendNegRes;
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    Std_ReturnType                  u1_RetChkCond;
    uint32                          u4_DTCGroup;
    Dem_DTCKindType                 u1_DTCKind;
    Std_ReturnType                  u1_RetVal;
    uint8                           u1_SetTiming;
    Dcm_MsgContextType              st_MsgContext;
    Std_ReturnType                  u1_RetSetProc;
    Dcm_MsgLenType                  u4_OpRecordLen;

    b_SendPosRes        = (boolean)FALSE;
    b_SendNegRes        = (boolean)FALSE;                                   /* MISRA DEVIATION */
    u4_DTCGroup         = (uint32)DEM_DTC_GROUP_ALL_DTCS;
    u1_DTCKind          = (Dem_DTCKindType)DEM_DTC_KIND_ALL_DTCS;
    u1_RetVal           = E_OK;

    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE                                  */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    /* Set Dcm_Dsp_Main_UserNotifyFlag in FALSE */
    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    /* Set Common Data */
    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;
    st_MsgContext = *ptMsgContext;
    u4_OpRecordLen = (Dcm_MsgLenType)Dcm_Dsp_SID85_u1DTCSettingOpRecordLen;

    /* Check Request Data Length */
    if( (st_MsgContext.reqDataLen != (Dcm_MsgLenType)0U) && (st_MsgContext.reqDataLen == u4_OpRecordLen ) )
    {
        u1_RetChkCond = Dcm_Dsp_SID85_ControlOptionRecord( st_MsgContext.reqData );

        if( u1_RetChkCond == (Std_ReturnType)E_OK )
        {
            /* Call callout function */
            u1_RetChkCond = Dcm_Dsp_SID85_CheckControl( u1CtrlMode, u4_DTCGroup, u1_DTCKind );

            if( u1_RetChkCond == (Std_ReturnType)E_OK )
            {
                Dcm_Dsp_SID85_CtrlMode = u1CtrlMode;

                u1_RetSetProc = Dcm_Dsp_SID85_ControlProcess( u1CtrlMode, DCM_INITIAL, st_MsgContext.reqData );
                if( u1_RetSetProc == (Std_ReturnType)E_OK )
                {
                    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
                    u1_SetTiming = Dcm_Dsp_SID85_u1DTCSettingTiming;
                    if( u1_SetTiming == DCM_P_DTCSETTING_IND )
                    {
                        if( u1CtrlMode == DCM_DSP_SID85_SF_ENABLE )
                        {
                            (void)Dcm_Dsp_SID85_Cnct_Sw_DTCSet( RTE_MODE_DcmControlDTCSetting_ENABLEDTCSETTING ); /* no return check required */
                        }
                        else
                        {
                            (void)Dcm_Dsp_SID85_Cnct_Sw_DTCSet( RTE_MODE_DcmControlDTCSetting_DISABLEDTCSETTING ); /* no return check required */
                        }
                    }
                    b_SendPosRes = (boolean)TRUE;
                }
                else if( u1_RetSetProc == (Std_ReturnType)DCM_E_PENDING )
                {
                    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
                    if( u1CtrlMode == DCM_DSP_SID85_SF_ENABLE )
                    {
                        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID85_SUB01_ENA_DTC ); /* no return check required */
                    }
                    else
                    {
                        (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID85_SUB02_DIS_DTC ); /* no return check required */
                    }
                    u1_RetVal = DCM_E_PENDING;
                }
                else
                {
                    /* NRC 0x22 */
                    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
                    u1_NegResCode   = DCM_E_CONDITIONSNOTCORRECT;
                    b_SendNegRes    = (boolean)TRUE;
                }
            }
            else
            {
                /* NRC 0x22 */
                u1_NegResCode   = DCM_E_CONDITIONSNOTCORRECT;
                b_SendNegRes    = (boolean)TRUE;
            }
        }
        else
        {
            /* NRC 0x31 */
            u1_NegResCode   = DCM_E_REQUESTOUTOFRANGE;
            b_SendNegRes    = (boolean)TRUE;
        }
    }
    else{
        /* NRC 0x13 */
        u1_NegResCode   = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        b_SendNegRes    = (boolean)TRUE;
    }

    if( b_SendNegRes == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendNegRes( &st_MsgContext, u1_NegResCode );
    }
    else
    {
        if(b_SendPosRes == (boolean)TRUE )
        {
            Dcm_Dsp_MsgMaker_SendPosRes( &st_MsgContext );
        }
        else
        {
            /* No Process */
        }
    }

    return u1_RetVal;
}

#endif /* DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_ON */

#if ( DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID85_CtrlDtcSetting                             */
/* Description   | SID85_Sub01/SID85_Sub02 Control Function                 */
/* Preconditions | None                                                     */
/* Parameters    | [IN] ptMsgContext   : Message Context                    */
/*               | [IN] u1CtrlMode     : Sub Function                       */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   DCM_E_PENDING     : Pending                            */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID85_CtrlDtcSetting
(
    P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) ptMsgContext,
    const uint8    u1CtrlMode
)
{
    Dcm_MsgLenType                  u4_DTCSettingOpRecordLen;
    boolean                         b_SendPosRes;
    boolean                         b_SendNegRes;
    Dcm_NegativeResponseCodeType    u1_NegResCode;
    Std_ReturnType                  u1_RetChkCond;
    uint32                          u4_DTCGroup;
    Dem_DTCKindType                 u1_DTCKind;
    Dem_ReturnControlDTCSettingType u1_RetControlDTCSetting;
    Std_ReturnType                  u1_RetCtrlDTCSet;
    Std_ReturnType                  u1_RetVal;
    uint8                           u1_SetTiming;
    uint8                           u1_InvalidOpRecord;
    Std_ReturnType                  u1_RetSetProc;

    b_SendPosRes        = (boolean)FALSE;
    b_SendNegRes        = (boolean)FALSE;                                   /* MISRA DEVIATION */
    u4_DTCGroup         = (uint32)DEM_DTC_GROUP_ALL_DTCS;
    u1_DTCKind          = (Dem_DTCKindType)DEM_DTC_KIND_ALL_DTCS;
    u1_RetControlDTCSetting = (Dem_ReturnControlDTCSettingType)DEM_CONTROL_DTC_SETTING_OK;
    u1_RetVal           = E_OK;
    u1_InvalidOpRecord  = (uint8)0x00U;

    /* Set Dcm_Dsp_Main_bIdleFlag in FALSE                                  */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)FALSE );
    /* Set Dcm_Dsp_Main_UserNotifyFlag in FALSE */
    Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    /* Set Common Data */
    Dcm_Dsp_Main_stMsgContext = *ptMsgContext;

    /* Check Request Data Length */
    u4_DTCSettingOpRecordLen = (Dcm_MsgLenType)Dcm_Dsp_SID85_u1DTCSettingOpRecordLen;
    if( Dcm_Dsp_Main_stMsgContext.reqDataLen == u4_DTCSettingOpRecordLen )
    {
        /* Call callout function                                        */
        u1_RetChkCond = Dcm_Dsp_SID85_CheckControl( u1CtrlMode, u4_DTCGroup, u1_DTCKind );

        if( u1_RetChkCond == (Std_ReturnType)E_OK )
        {
            Dcm_Dsp_SID85_CtrlMode = u1CtrlMode;
            u1_RetSetProc = Dcm_Dsp_SID85_ControlProcess( u1CtrlMode, DCM_INITIAL, &u1_InvalidOpRecord );
            if( u1_RetSetProc == (Std_ReturnType)E_OK )
            {
                u1_SetTiming = Dcm_Dsp_SID85_u1DTCSettingTiming;
                if( u1_SetTiming == DCM_P_DTCSETTING_IND )
                {
                    /* Callout function check OK                                    */
                    if( u1CtrlMode == DCM_DSP_SID85_SF_ENABLE )
                    {
                        u1_RetCtrlDTCSet = Dcm_Dsp_SID85_EnableDTCSetting( u4_DTCGroup, u1_DTCKind, &u1_RetControlDTCSetting );
                    }
                    else
                    {
                        u1_RetCtrlDTCSet = Dcm_Dsp_SID85_DisableDTCSetting( u4_DTCGroup, u1_DTCKind, &u1_RetControlDTCSetting );
                    }

                    if( u1_RetCtrlDTCSet == (Std_ReturnType)E_OK )
                    {
                        b_SendPosRes = (boolean)TRUE;
                    }
                    else if( u1_RetControlDTCSetting == (Dem_ReturnControlDTCSettingType)DEM_CONTROL_DTC_SETTING_N_OK )
                    {
                        /* NRC 0x22                                                 */
                        u1_NegResCode = DCM_E_CONDITIONSNOTCORRECT;
                        b_SendNegRes = (boolean)TRUE;
                    }
                    else
                    {
                        /* No process                                               */
                    }
                }
                else
                {
                    b_SendPosRes = (boolean)TRUE;
                }
            }
            else if( u1_RetSetProc == (Std_ReturnType)DCM_E_PENDING )
            {
                Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)TRUE );
                if( u1CtrlMode == DCM_DSP_SID85_SF_ENABLE )
                {
                    (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID85_SUB01_ENA_DTC ); /* no return check required */
                }
                else
                {
                    (void)Dcm_Main_EvtDistr_SendEvent( DCM_M_EVTID_SID85_SUB02_DIS_DTC ); /* no return check required */
                }
                u1_RetVal = DCM_E_PENDING;
            }
            else
            {
                /* NRC 0x22 */
                u1_NegResCode   = DCM_E_CONDITIONSNOTCORRECT;
                b_SendNegRes    = (boolean)TRUE;
            }
        }
        else
        {
            /* Callout Function check not OK                                */
            /* NRC 0x22                                                     */
            u1_NegResCode   = DCM_E_CONDITIONSNOTCORRECT;
            b_SendNegRes    = (boolean)TRUE;
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
    else if( b_SendPosRes == (boolean)TRUE )
    {
        Dcm_Dsp_MsgMaker_SendPosRes( &Dcm_Dsp_Main_stMsgContext );
    }
    else
    {
        /* No process                                                       */
    }

    return u1_RetVal;
}

#endif /* DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_OFF */

#if ( DCM_SUPPORT_SID85_SUB01 == STD_ON )
#if ( DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID85_Sub01_CancelProc                           */
/* Description   | Cancel process of SID 85 SF 01 request                   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID85_Sub01_CancelProc
(
    void
)
{
    boolean                         b_UserNotify;

    b_UserNotify = Dcm_Dsp_Main_GetUserNotifyFlag();

    if( b_UserNotify == (boolean)TRUE )
    {
        (void)Dcm_Dsp_SID85_ControlProcess( Dcm_Dsp_SID85_CtrlMode, DCM_CANCEL, Dcm_Dsp_Main_stMsgContext.reqData ); /* no return check required */
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }
    else
    {
        /* No process */
    }

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID85_SUB01_ENA_DTC, (boolean)FALSE ); /* no return check required */
    /* Set Dcm_Dsp_Main_bIdleFlag in TRUE                                   */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}

#endif /* DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_ON */

#if ( DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID85_Sub01_CancelProc                           */
/* Description   | Cancel process of SID 85 SF 01 request                   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID85_Sub01_CancelProc
(
    void
)
{
    boolean                         b_UserNotify;
    uint8                           u1_InvalidOpRecord;

    u1_InvalidOpRecord = (uint8)0x00U;
    b_UserNotify = Dcm_Dsp_Main_GetUserNotifyFlag();

    if( b_UserNotify == (boolean)TRUE )
    {
        (void)Dcm_Dsp_SID85_ControlProcess( Dcm_Dsp_SID85_CtrlMode, DCM_CANCEL, &u1_InvalidOpRecord ); /* no return check required */
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }
    else
    {
        /* No process */
    }

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID85_SUB01_ENA_DTC, (boolean)FALSE ); /* no return check required */
    /* Set Dcm_Dsp_Main_bIdleFlag in TRUE                                   */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}
#endif /* DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_OFF */
#endif /* DCM_SUPPORT_SID85_SUB01 == STD_ON */

#if ( DCM_SUPPORT_SID85_SUB02 == STD_ON )
#if ( DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_ON )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID85_Sub02_CancelProc                           */
/* Description   | Cancel process of SID 85 SF 02 request                   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID85_Sub02_CancelProc
(
    void
)
{
    boolean                         b_UserNotify;

    b_UserNotify = Dcm_Dsp_Main_GetUserNotifyFlag();

    if( b_UserNotify == (boolean)TRUE )
    {
        (void)Dcm_Dsp_SID85_ControlProcess( Dcm_Dsp_SID85_CtrlMode, DCM_CANCEL, Dcm_Dsp_Main_stMsgContext.reqData ); /* no return check required */
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }
    else
    {
        /* No process */
    }
    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID85_SUB02_DIS_DTC, (boolean)FALSE ); /* no return check required */
    /* Set Dcm_Dsp_Main_bIdleFlag in TRUE                                   */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}

#endif /* DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_ON */

#if ( DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID85_Sub02_CancelProc                           */
/* Description   | Cancel process of SID 85 SF 02 request                   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID85_Sub02_CancelProc
(
    void
)
{
    boolean                         b_UserNotify;
    uint8                           u1_InvalidOpRecord;

    u1_InvalidOpRecord = (uint8)0x00U;
    b_UserNotify = Dcm_Dsp_Main_GetUserNotifyFlag();

    if( b_UserNotify == (boolean)TRUE )
    {
        (void)Dcm_Dsp_SID85_ControlProcess( Dcm_Dsp_SID85_CtrlMode, DCM_CANCEL, &u1_InvalidOpRecord ); /* no return check required */
        Dcm_Dsp_Main_SetUserNotifyFlag( (boolean)FALSE );
    }
    else
    {
        /* No process */
    }

    (void)Dcm_Main_EvtDistr_DeleteEvent( DCM_M_EVTID_SID85_SUB02_DIS_DTC, (boolean)FALSE ); /* no return check required */
    /* Set Dcm_Dsp_Main_bIdleFlag in TRUE                                   */
    Dcm_Dsp_Main_SetIdleFlag( (boolean)TRUE );

    return;
}
#endif /* DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_OFF */
#endif /* DCM_SUPPORT_SID85_SUB02 == STD_ON */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID85_EnableDTCSetting                           */
/* Description   | Call DEM-API Dem_DcmEnableDTCSetting                     */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u4DTCGroup : Group of DTC                           */
/*               | [IN] u1DTCKind  : Requested DTC Kind                     */
/*               | [IN] ptRetControlDTCSetting  : Return Value of DEM-API   */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing not normal              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID85_EnableDTCSetting
(
    const uint32            u4DTCGroup,
    const Dem_DTCKindType   u1DTCKind,
    P2VAR(Dem_ReturnControlDTCSettingType, AUTOMATIC, DCM_APPL_DATA) ptRetControlDTCSetting
)
{
    Std_ReturnType                          u1_RetVal;
    Dem_ReturnControlDTCSettingType         u1_RetCtrlDTCSet;

    u1_RetVal = E_NOT_OK;

    u1_RetCtrlDTCSet = Dem_DcmEnableDTCSetting( u4DTCGroup, u1DTCKind );

    /* Check DEM-API Return Value                                           */
    switch( u1_RetCtrlDTCSet )
    {
        case DEM_CONTROL_DTC_SETTING_OK:
            /* Internal Status change to ENABLE                             */
            Dcm_Dsp_SID85_u1CtrlDTCSetting = DCM_DSP_SID85_ENA_DTC;
            /* Clear PduId-Information notified of by DSD                   */
            Dcm_Dsp_SID85_ClearPduId();
            /* ENABLEDTCSETTING Mode set (for SchM)                         */
            (void)Dcm_Dsp_SID85_Cnct_Sw_DTCSet( RTE_MODE_DcmControlDTCSetting_ENABLEDTCSETTING );   /* no return check required */
            u1_RetVal = E_OK;
            break;
        case DEM_CONTROL_DTC_SETTING_N_OK:
        case DEM_CONTROL_DTC_WRONG_DTCGROUP:
            /* No process                                                   */
            break;
        default:
            /* No process                                                   */
            break;
    }

    *ptRetControlDTCSetting = u1_RetCtrlDTCSet;

    return u1_RetVal;
}

#if ( DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_OFF )
/****************************************************************************/
/* Function Name | Dcm_Dsp_SID85_DisableDTCSetting                          */
/* Description   | Call DEM-API Dem_DcmDisableDTCSetting                    */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u4DTCGroup : group of DTC                           */
/*               | [IN] u1DTCKind  : requested DTC kind                     */
/*               | [IN] ptRetControlDTCSetting  : Return Value of DEM-API   */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK              : Processing normal                  */
/*               |   E_NOT_OK          : Processing not normal              */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID85_DisableDTCSetting
(
    const uint32            u4DTCGroup,
    const Dem_DTCKindType   u1DTCKind,
    P2VAR(Dem_ReturnControlDTCSettingType, AUTOMATIC, DCM_APPL_DATA) ptRetControlDTCSetting
)
{
    Std_ReturnType                          u1_RetVal;
    Dem_ReturnControlDTCSettingType         u1_RetCtrlDTCSet;

    u1_RetVal = E_NOT_OK;

    u1_RetCtrlDTCSet = Dem_DcmDisableDTCSetting( u4DTCGroup, u1DTCKind );

    /* Check DEM-API Return Value                                           */
    switch( u1_RetCtrlDTCSet )
    {
        case DEM_CONTROL_DTC_SETTING_OK:
            /* Internal Status change to DISABLE                            */
            Dcm_Dsp_SID85_u1CtrlDTCSetting = DCM_DSP_SID85_DIS_DTC;
            /* Save PduId-Information notified of by DSD                    */
            Dcm_Dsp_SID85_SetPduId( Dcm_Dsp_Main_stMsgContext.dcmRxPduId );
            /* DISABLEDTCSETTING Mode set (for SchM)                        */
            (void)Dcm_Dsp_SID85_Cnct_Sw_DTCSet( RTE_MODE_DcmControlDTCSetting_DISABLEDTCSETTING );  /* no return check required */
            u1_RetVal = E_OK;
            break;
        case DEM_CONTROL_DTC_SETTING_N_OK:
        case DEM_CONTROL_DTC_WRONG_DTCGROUP:
            /* No process                                                   */
            break;
        default:
            /* No process                                                   */
            break;
    }

    *ptRetControlDTCSetting = u1_RetCtrlDTCSet;

    return u1_RetVal;
}

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID85_SetPduId                                   */
/* Description   | Save PduId to RAM                                        */
/* Preconditions | None                                                     */
/* Parameters    | [IN] u2PduId    : PduId                                  */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID85_SetPduId
(
    const PduIdType         u2PduId
)
{
    Dcm_Dsp_SID85_u2PduId       = u2PduId;
    Dcm_Dsp_SID85_u1SetPduId    = DCM_DSP_SID85_SET_PDUID;

    return;
}
#endif /* DCM_P_DTCSETTING_SUPPORT_OPTION_RECORD == STD_OFF */

/****************************************************************************/
/* Function Name | Dcm_Dsp_SID85_GetPduId                                   */
/* Description   | Get PduId from RAM                                       */
/* Preconditions | None                                                     */
/* Parameters    | [OUT] ptPduId      : Pointer of PduId                    */
/* Return Value  | Std_ReturnType                                           */
/*               | E_OK          : Processing normal                        */
/*               | E_NOT_OK      : PduId has not been yet saved             */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(Std_ReturnType, DCM_CODE) Dcm_Dsp_SID85_GetPduId
(
    P2VAR(PduIdType, AUTOMATIC, DCM_APPL_DATA) ptPduId
)
{
    Std_ReturnType                          u1_RetVal;

    u1_RetVal = E_NOT_OK;

    if( Dcm_Dsp_SID85_u1SetPduId == DCM_DSP_SID85_SET_PDUID )
    {
        *ptPduId    = Dcm_Dsp_SID85_u2PduId;
        u1_RetVal   = E_OK;
    }
    else
    {
        /* No process                                                       */
    }

    return u1_RetVal;
}


/****************************************************************************/
/* Function Name | Dcm_Dsp_SID85_ClearPduId                                 */
/* Description   | Initialize PduId(value and set-information)              */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Node                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC(void, DCM_CODE) Dcm_Dsp_SID85_ClearPduId
(
    void
)
{
    /* Initial value set DCM_DSP_SID85_UNSET_PDUID                          */
    Dcm_Dsp_SID85_u1SetPduId    = DCM_DSP_SID85_UNSET_PDUID;
    /* Initial value set DCM_DSP_SID85_INIT_PDUID_VAL                       */
    Dcm_Dsp_SID85_u2PduId       = DCM_DSP_SID85_INIT_PDUID_VAL;

    return;
}


#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>
#endif /* DCM_SUPPORT_SID85 == STD_ON */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-2-0         :2019-01-29                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

