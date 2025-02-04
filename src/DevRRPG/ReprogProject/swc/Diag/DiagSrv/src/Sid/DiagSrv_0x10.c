/* DiagSrv_0x10_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/0x10/CODE                                           */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <DiagSrv.h>
#include <DiagLib.h>
#include <RpgMfr.h>
#include <RpgSpp.h>
#include <VehInf.h>
#include <ReprogOpt.h>
#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
#include <Rte.h>
#endif

#include "DiagSrv_0x10.h"
#include "DiagSrv_0x10_Cfg.h"
#include "DiagSrv_Local.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* Message Parameter Position */
#define DIAGSRV_0X10_SID_POS            ((uint8)0U)
#define DIAGSRV_0X10_SUBFUNC_POS        ((uint8)1U)
#define DIAGSRV_0X10_P2S_MAX_H_POS      ((uint8)2U)
#define DIAGSRV_0X10_P2S_MAX_L_POS      ((uint8)3U)
#define DIAGSRV_0X10_P2AS_MAX_H_POS     ((uint8)4U)
#define DIAGSRV_0X10_P2AS_MAX_L_POS     ((uint8)5U)

/* Data Length */
#define DIAGSRV_0X10_RSP_MSG_LEN        ((uint8)6U)

/* Bit Calculation */
#define DIAGSRV_0X10_BIT_SHIFT_8        ((uint8)8U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>

static VAR(uint8, DIAGSRV_VAR_CLEARED) DiagSrv_0x10_NewSession;

#define DIAGSRV_STOP_SEC_VAR
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_CST
#include <DiagSrv_MemMap.h>

#define DIAGSRV_STOP_SEC_CST
#include <DiagSrv_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define DIAGSRV_START_SEC_CODE
#include <DiagSrv_MemMap.h>

/******************************************************************************/
/* Function Name | DiagSrv_0x10_Init                                          */
/* Description   | Initialize                                                 */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x10_Init (void)
{
    DiagSrv_0x10_NewSession = DIAG_SESSION_OTH;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x10_Time                                          */
/* Description   | Time function                                              */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x10_Time (void)
{
    /* No process */
    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x10_Processing                                    */
/* Description   | Processing function                                        */
/* Preconditions |                                                            */
/* Parameters    | [IN] Msg : Message                                         */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x10_Processing
(
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_DATA) Msg
)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) Index;
    VAR(uint8, AUTOMATIC) NewSession;
    VAR(uint8, AUTOMATIC) ChangePrgSession;
    VAR(uint16, AUTOMATIC) MsgLen;
    VAR(uint16, AUTOMATIC) Volt;
    VAR(Std_ReturnType, AUTOMATIC) FuncRet;
#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
    VAR(uint8, AUTOMATIC) BootMode;
#endif

    Index = 0x00U;
    Nrc = DiagLib_CheckSubfunctionSupport(Msg, &DiagSrv_0x10_SubfuncConfig, &Index);

    if( Nrc == DIAG_NRC_PR )
    {
        MsgLen = (DIAG_SUBFUNCMSG_MIN_SIZE + DiagSrv_0x10_SubfuncConfig.InfoPtr[Index].Length);
        if( Msg->ReqDataLen == MsgLen )
        {
            Nrc = RpgMfr_MsgCheckCondition(Msg);

            if( Nrc == DIAG_NRC_PR )
            {
                Nrc = RpgSpp_MsgCheckCondition(Msg);
            }

            if( Nrc == DIAG_NRC_PR )
            {
                NewSession = DIAG_GET_SUBFUNCTION(Msg);
                if( NewSession == DIAG_SESSION_PRG )
                {
#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
                    BootMode = Rte_EcuM_GetBootMode();
                    if( BootMode != RTE_ECUM_START_STAYINBOOT_ENTRY )
#endif
                    {
                        Volt = 0U;
                        Nrc = DIAG_NRC_GR;

                        FuncRet = VehInf_GetVoltForPrgSession(&Volt);
                        if( FuncRet == (Std_ReturnType)E_OK )
                        {
                            Nrc = RpgMfr_VoltCheckConditionForPrgSession(Volt);
                        }
                    }

                    if( Nrc == DIAG_NRC_PR )
                    {
                        ChangePrgSession = DiagSrv_CheckChangePrgSession();
                        if( ChangePrgSession == (uint8)STD_OFF )
                        {
                            Nrc = DIAG_NRC_CNC;
                        }
                    }
                }
            }
        }
        else
        {
            Nrc = DIAG_NRC_IMLOIF;
        }
    }

    if( Nrc == DIAG_NRC_PR )
    {
        DiagSrv_0x10_NewSession = NewSession;

        Msg->ResData[DIAGSRV_0X10_SID_POS] = DIAG_MAKE_POSRSP_SID(Msg);
        Msg->ResData[DIAGSRV_0X10_SUBFUNC_POS] = DiagSrv_0x10_NewSession;
        Msg->ResData[DIAGSRV_0X10_P2S_MAX_H_POS] = (uint8)(DiagSrv_0x10_TimingParamConfig.InfoPtr[Index].P2ServerMax >> DIAGSRV_0X10_BIT_SHIFT_8);
        Msg->ResData[DIAGSRV_0X10_P2S_MAX_L_POS] = (uint8)(DiagSrv_0x10_TimingParamConfig.InfoPtr[Index].P2ServerMax);
        Msg->ResData[DIAGSRV_0X10_P2AS_MAX_H_POS] = (uint8)(DiagSrv_0x10_TimingParamConfig.InfoPtr[Index].P2AsterServerMax >> DIAGSRV_0X10_BIT_SHIFT_8);
        Msg->ResData[DIAGSRV_0X10_P2AS_MAX_L_POS] = (uint8)(DiagSrv_0x10_TimingParamConfig.InfoPtr[Index].P2AsterServerMax);
        Msg->ResDataLen = DIAGSRV_0X10_RSP_MSG_LEN;

        DiagLib_SendPosRsp(Msg);
    }
    else
    {
        DiagLib_SendNegRsp(Nrc, Msg);
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x10_Confirmation                                  */
/* Description   | Confirmation function                                      */
/* Preconditions |                                                            */
/* Parameters    | [IN] Status : Transmission complete status                 */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x10_Confirmation
(
    VAR(uint8, AUTOMATIC) Status
)
{
    if( Status == DIAG_POSRSP_OK )
    {
        DiagLib_SetSession(DiagSrv_0x10_NewSession, DIAG_CHGSESSION_FACT_SID10);
    }

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_0x10_NotifyChangeSession                           */
/* Description   | Notify change session function                             */
/* Preconditions |                                                            */
/* Parameters    | [IN] OldSession : Before the changes                       */
/*               | [IN] NewSession : After the changes                        */
/*               | [IN] Factor     : Change factor                            */
/* Return Value  | None                                                       */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x10_NotifyChangeSession
(
    VAR(uint8, AUTOMATIC) OldSession,
    VAR(uint8, AUTOMATIC) NewSession,
    VAR(uint8, AUTOMATIC) Factor
)
{
    if( NewSession == DIAG_SESSION_PRG )
    {
        DiagSrv_SetRewriteStatus(DIAGSRV_REWRITESTAT_IDLE);
    }
    else if( NewSession == DIAG_SESSION_DEF )
    {
        if( ReprogOpt_SubMiconConfig != REPROGOPT_SUBMICON_TYPE_SUB )
        {
            DiagLib_EcuReset();
        }
    }
    else if( NewSession == DIAG_SESSION_EXT )
    {
        /* No process */
    }
    else
    {
        /* No process */
    }

    return;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define DIAGSRV_STOP_SEC_CODE
#include <DiagSrv_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/09/14 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

