/* BswM_CanSM_c_Revision(v5.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | BswM/CanSM/CODE                                             */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <BswM.h>
#include <BswM_CanSM.h>
#include "BswM_Local.h"

#include <Rte.h>
#include <Sys.h>
#include <EcuM.h>
#include <CanSM_BswM.h>
#include <Gdn.h>
#include <UsrSoftIf.h>
#include <Int.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* Entry parameter */
#define BSWM_ENTRYPARAM_IDX_RECVCH      (0U)
#define BSWM_ENTRYPARAM_IDX_RECVID      (1U)
#define BSWM_ENTRYPARAM_IDX_SUBMICON    (5U)
#define BSWM_ENTRYPARAM_IDX_SIDSIZE     (6U)
#define BSWM_ENTRYPARAM_IDX_SIDADDR     (8U)

#define BSWM_ENTRYPARAM_MICON_MAIN      ((uint8)0x00U)
#define BSWM_ENTRYPARAM_MICON_UNMATCH   ((uint8)0xF0U)
#define BSWM_ENTRYPARAM_MICON_SUB       ((uint8)0xFFU)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(void, BSWM_CODE_FAST) BswM_CommunicationStart (void);
static FUNC(Std_ReturnType, BSWM_CODE_FAST) BswM_DcmDummyReception
(
    P2CONST(UsrSoftIf_EntryParamType, AUTOMATIC, BSWM_APPL_CONST) EntryParamPtr,
    VAR(Gdn_PduIdType, AUTOMATIC) PduId
);
static FUNC(Std_ReturnType, BSWM_CODE_FAST) BswM_CheckDummyReception
(
    P2CONST(UsrSoftIf_EntryParamType, AUTOMATIC, BSWM_APPL_CONST) EntryParamPtr,
    VAR(Gdn_PduIdType, AUTOMATIC) PduId
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define BSWM_START_SEC_VAR
#include <BswM_MemMap.h>

#define BSWM_STOP_SEC_VAR
#include <BswM_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define BSWM_START_SEC_CST
#include <BswM_MemMap.h>

static CONST(AB_83_ConstV Gdn_TimeoutValueType, BSWM_CONST) BswM_S3TimeCount = GDN_DCM_DCP_S3_TIMECNT;

#define BSWM_STOP_SEC_CST
#include <BswM_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define BSWM_START_SEC_CODE
#include <BswM_MemMap.h>

/******************************************************************************/
/* Function Name | BswM_Act_CanSMNoCom                                        */
/* Description   | Action of the CanSM mode control(No communication)         */
/* Preconditions |                                                            */
/* Parameters    | [IN] NetworkId  : Network identifier                       */
/*               | [IN] StateIndex : Index of the CanSM state                 */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, BSWM_CODE_FAST) BswM_Act_CanSMNoCom
(
    VAR(NetworkHandleType, AUTOMATIC) NetworkId,
    VAR(uint8, AUTOMATIC) StateIndex
)
{
    VAR(Gdn_Std_ReturnType, AUTOMATIC) DcmResult;
    VAR(uint8, AUTOMATIC) MaskLevel;
    VAR(uint8, AUTOMATIC) UpdateFlg;

    UpdateFlg = STD_OFF;

    MaskLevel = MaskInterruptAll(); /* for BswM_CanSMState[] */

    if( BswM_CanSMState[StateIndex] == CANSM_BSWM_CHANGE_BAUDRATE )
    {
        BswM_CanSMState[StateIndex] = CANSM_BSWM_NO_COMMUNICATION;
        UpdateFlg = STD_ON;
    }

    UnMaskInterruptAll(MaskLevel);  /* for BswM_CanSMState[] */

    if( UpdateFlg == (uint8)STD_ON )
    {
        DcmResult = GDN_E_NOT_OK;
        Gdn_Dcm_NotifyBaudrateSettingResult(NetworkId, &DcmResult);
    }

    return;
}

/******************************************************************************/
/* Function Name | BswM_Act_CanSMFullCom                                      */
/* Description   | Action of the CanSM mode control(Full communication)       */
/* Preconditions |                                                            */
/* Parameters    | [IN] NetworkId  : Network identifier                       */
/*               | [IN] StateIndex : Index of the CanSM state                 */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, BSWM_CODE_FAST) BswM_Act_CanSMFullCom
(
    VAR(NetworkHandleType, AUTOMATIC) NetworkId,
    VAR(uint8, AUTOMATIC) StateIndex
)
{
    VAR(Gdn_Std_ReturnType, AUTOMATIC) DcmResult;
    VAR(CanSM_BswMRequestedModeType, AUTOMATIC) PreState;
    VAR(uint8, AUTOMATIC) ComStartFlgUpdate;
    VAR(uint8, AUTOMATIC) CanSMFullFlg;
    VAR(uint8, AUTOMATIC) MaskLevel;
    VAR(uint8, AUTOMATIC) i;

    /* When PreState is CANSM_BSWM_FULL_COMMUNICATION, this function does nothing */
    PreState = CANSM_BSWM_FULL_COMMUNICATION;

    CanSMFullFlg = STD_ON;

    /* BswM_CanSMState[] update process */
    MaskLevel = MaskInterruptAll(); /* for BswM_CanSMState[] */

    if( BswM_CanSMState[StateIndex] == CANSM_BSWM_NO_COMMUNICATION )
    {
        BswM_CanSMState[StateIndex] = CANSM_BSWM_FULL_COMMUNICATION;
        PreState = CANSM_BSWM_NO_COMMUNICATION;

        for( i = 0U; i < BswM_CfgPtr->CanSMCfgDataPtr->NetworkInfoTbl->NetworkNum; i++ )
        {
            if( BswM_CanSMState[i] != CANSM_BSWM_FULL_COMMUNICATION )
            {
                CanSMFullFlg = STD_OFF;

                break;
            }
        }
    }
    else if( BswM_CanSMState[StateIndex] == CANSM_BSWM_CHANGE_BAUDRATE )
    {
        BswM_CanSMState[StateIndex] = CANSM_BSWM_FULL_COMMUNICATION;
        PreState = CANSM_BSWM_CHANGE_BAUDRATE;
    }
    else
    {
        /* No process */
    }

    UnMaskInterruptAll(MaskLevel);  /* for BswM_CanSMState[] */

    /* Executive operation in each state(BswM_CanSMState[]) */
    if( PreState == CANSM_BSWM_NO_COMMUNICATION )
    {
        if( CanSMFullFlg == (uint8)STD_ON )
        {
            ComStartFlgUpdate = STD_OFF;

            MaskLevel = MaskInterruptAll(); /* for BswM_ComStartFlg */

            if( BswM_ComStartFlg == (uint8)STD_OFF )
            {
                BswM_ComStartFlg = STD_ON;
                ComStartFlgUpdate = STD_ON;
            }

            UnMaskInterruptAll(MaskLevel);  /* for BswM_ComStartFlg */

            if( ComStartFlgUpdate == (uint8)STD_ON )
            {
                BswM_CommunicationStart();
            }
        }
    }
    else if( PreState == CANSM_BSWM_CHANGE_BAUDRATE )
    {
        DcmResult = GDN_E_OK;
        Gdn_Dcm_NotifyBaudrateSettingResult(NetworkId, &DcmResult);
    }
    else
    {
        /* No process */
    }

    return;
}

/******************************************************************************/
/* Function Name | BswM_Act_CanSMChangeBaudrate                               */
/* Description   | Action of the CanSM mode control(Change baudrate)          */
/* Preconditions |                                                            */
/* Parameters    | [IN] StateIndex : Index of the CanSM state                 */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, BSWM_CODE_FAST) BswM_Act_CanSMChangeBaudrate
(
    VAR(uint8, AUTOMATIC) StateIndex
)
{
    VAR(uint8, AUTOMATIC) MaskLevel;

    MaskLevel = MaskInterruptAll(); /* for BswM_CanSMState[] */

    if( BswM_CanSMState[StateIndex] == CANSM_BSWM_FULL_COMMUNICATION )
    {
        BswM_CanSMState[StateIndex] = CANSM_BSWM_CHANGE_BAUDRATE;
    }

    UnMaskInterruptAll(MaskLevel);  /* for BswM_CanSMState[] */

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | BswM_CommunicationStart                                    */
/* Description   | Communication start process                                */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(void, BSWM_CODE_FAST) BswM_CommunicationStart (void)
{
    P2CONST(UsrSoftIf_EntryParamType, AUTOMATIC, BSWM_APPL_CONST) EntryParamPtr;
    P2CONST(CanSM_PduIdConfigType, AUTOMATIC, BSWM_APPL_CONST) PduIdCfgPtr;
    VAR(uint32, AUTOMATIC) RecvId;
    VAR(Gdn_PduIdType, AUTOMATIC) RecvPduId;
    VAR(uint8, AUTOMATIC) BootMode;
    VAR(uint8, AUTOMATIC) PduIdSearchFlg;
    VAR(uint8, AUTOMATIC) i;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(uint8, AUTOMATIC) ErrorFlg;

    ErrorFlg = STD_ON;

    BootMode = EcuM_GetBootMode();

#if (REPROG_CFG_POSRES_AFTER_RESET != STD_ON)
    if( BootMode == ECUM_START_AP_ENTRY )
#else
    if( ( BootMode == ECUM_START_AP_ENTRY ) || ( BootMode == ECUM_START_BOOT_POSRES_ENTRY ) )
#endif
    {
        EntryParamPtr = UsrSoftIf_GetEntryParam();

        /* Receive ID conversion */
        RecvId = Rpg_ByteCombine(&EntryParamPtr->EntryParam[BSWM_ENTRYPARAM_IDX_RECVID], (uint8)sizeof(RecvId));

        /* Receive PDU ID search */
        PduIdSearchFlg = STD_OFF;
        RecvPduId = 0U;
        PduIdCfgPtr = BswM_CfgPtr->CanSMCfgDataPtr->PduIdInfoTbl;

        for( i = 0U; i < PduIdCfgPtr->PduIdNum; i++ )
        {
            if( ( EntryParamPtr->EntryParam[BSWM_ENTRYPARAM_IDX_RECVCH] == PduIdCfgPtr->PduIdSettingTbl[i].Controller ) &&
                ( RecvId == PduIdCfgPtr->PduIdSettingTbl[i].CanId ) )
            {
                RecvPduId = PduIdCfgPtr->PduIdSettingTbl[i].PduId;

                /* Receive PDU ID search success */
                PduIdSearchFlg = STD_ON;

                break;
            }
        }

        if( PduIdSearchFlg == (uint8)STD_ON )
        {
            FuncRet = BswM_CheckDummyReception(EntryParamPtr, RecvPduId);
            if( FuncRet == (Std_ReturnType)E_OK )
            {
                ErrorFlg = STD_OFF;
            }
        }
        else
        {
            BswM_ReportError(BSWM_API_ID_COMSTART, BSWM_E_PDUIDSEARCH_ERR);
        }
    }
    else
    {
        ErrorFlg = STD_OFF;
    }

    if( ErrorFlg == (uint8)STD_OFF )
    {
        Int_SetMaskLevel(INT_MASK_NONE);

        Rte_RpgEvtHk_ModeEvt_CanStart();
    }

    return;
}

/******************************************************************************/
/* Function Name | BswM_CheckDummyReception                                   */
/* Description   | Check dummy reception requirement                          */
/* Preconditions |                                                            */
/* Parameters    | [IN] EntryParamPtr : Entry parameter address               */
/*               | [IN] PduId         : Pdu ID                                */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, BSWM_CODE_FAST) BswM_CheckDummyReception
(
    P2CONST(UsrSoftIf_EntryParamType, AUTOMATIC, BSWM_APPL_CONST) EntryParamPtr,
    VAR(Gdn_PduIdType, AUTOMATIC) PduId
)
{
    P2CONST(uint8, AUTOMATIC, BSWM_APPL_CONST) SidInfoAddr;
    VAR(uint8, AUTOMATIC) RespFlg;
    VAR(Std_ReturnType, AUTOMATIC) Ret;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
    VAR(Gdn_TimeoutValueType, AUTOMATIC) TimeCount;

    Ret = E_NOT_OK;

    if( EntryParamPtr->EntryParam[BSWM_ENTRYPARAM_IDX_SUBMICON] == BSWM_ENTRYPARAM_MICON_MAIN )
    {
        SidInfoAddr = (const uint8 *)Rpg_ByteCombine(&EntryParamPtr->EntryParam[BSWM_ENTRYPARAM_IDX_SIDADDR],
                                                    (uint8)sizeof(SidInfoAddr));

        RespFlg = STD_OFF;

        FuncRet = Rte_RpgMfr_ApEntryCheck(*SidInfoAddr, &RespFlg);
        if( FuncRet == (Std_ReturnType)E_OK )
        {
            if( RespFlg == (uint8)STD_ON )
            {
                FuncRet = BswM_DcmDummyReception(EntryParamPtr, PduId);
                if( FuncRet == (Std_ReturnType)E_OK )
                {
                    Ret = E_OK;
                }
            }
            else
            {
                TimeCount = BswM_S3TimeCount;
                Gdn_TmrSrv_SetTimer(GDN_DCM_DCP_S3_TIMER_ID, TimeCount, (gdn_uint16)0U);
                Ret = E_OK;
            }
        }
        else
        {
            BswM_ReportError(BSWM_API_ID_CHECKDUMMYRECEPTION, BSWM_E_APENTRYCHECK_ERR);
        }
    }
    else if( ( EntryParamPtr->EntryParam[BSWM_ENTRYPARAM_IDX_SUBMICON] == BSWM_ENTRYPARAM_MICON_UNMATCH ) ||
             ( EntryParamPtr->EntryParam[BSWM_ENTRYPARAM_IDX_SUBMICON] == BSWM_ENTRYPARAM_MICON_SUB ) )
    {
        Ret = E_OK;
    }
    else
    {
        BswM_ReportError(BSWM_API_ID_CHECKDUMMYRECEPTION, BSWM_E_PARAM_MICON_INVALID);
    }

    return Ret;
}

/******************************************************************************/
/* Function Name | BswM_DcmDummyReception                                     */
/* Description   | Dummy Reception process                                    */
/* Preconditions |                                                            */
/* Parameters    | [IN] EntryParamPtr : Entry parameter address               */
/*               | [IN] PduId         : Pdu ID                                */
/* Return Value  | Status                                                     */
/*               |  E_OK                                                      */
/*               |  E_NOT_OK                                                  */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(Std_ReturnType, BSWM_CODE_FAST) BswM_DcmDummyReception
(
    P2CONST(UsrSoftIf_EntryParamType, AUTOMATIC, BSWM_APPL_CONST) EntryParamPtr,
    VAR(Gdn_PduIdType, AUTOMATIC) PduId
)
{
    VAR(Gdn_PduInfoType, AUTOMATIC) PduInfo;
    VAR(Gdn_PduLengthType, AUTOMATIC) BufferRemained;
    VAR(Gdn_BufReq_ReturnType, AUTOMATIC) GdnRet;
    VAR(Std_ReturnType, AUTOMATIC) StdRet;

    StdRet = E_NOT_OK;

    PduInfo.SduDataPtr = (uint8 *)Rpg_ByteCombine(&EntryParamPtr->EntryParam[BSWM_ENTRYPARAM_IDX_SIDADDR],
                                                  (uint8)sizeof(PduInfo.SduDataPtr));

    PduInfo.SduLength = (uint16)Rpg_ByteCombine(&EntryParamPtr->EntryParam[BSWM_ENTRYPARAM_IDX_SIDSIZE],
                                                (uint8)sizeof(PduInfo.SduLength));

    BufferRemained = 0U;

    GdnRet = Gdn_Dcm_StartOfReception(PduId, &PduInfo, PduInfo.SduLength, &BufferRemained);
    if( ( GdnRet == GDN_BUFREQ_OK ) && ( BufferRemained >= PduInfo.SduLength ) )
    {
        GdnRet = Gdn_Dcm_CopyRxData(PduId, &PduInfo, &BufferRemained);
        if( GdnRet == GDN_BUFREQ_OK )
        {
            Gdn_Dcm_TpRxIndication(PduId, GDN_NTFRSLT_OK);
            StdRet = E_OK;
        }
        else
        {
            BswM_ReportError(BSWM_API_ID_DCMDUMMYRECEPTION, BSWM_E_COPYRXDATA_ERR);
        }
    }
    else
    {
        BswM_ReportError(BSWM_API_ID_DCMDUMMYRECEPTION, BSWM_E_STARTOFRECEPTION_ERR);
    }

    return StdRet;
}

#define BSWM_STOP_SEC_CODE
#include <BswM_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/06/19 :Update                                rel.AUBASS */
/*  v3.00       :2018/10/23 :Update                                rel.AUBASS */
/*  v4.00       :2020/03/10 :Update                                rel.AUBASS */
/*  v5.00       :2022/03/01 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

