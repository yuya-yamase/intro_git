/* DiagSrv_SubMicon_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/SubMicon/CODE                                       */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
#include <DiagSrv.h>
#include <DiagLib.h>
#include <Rte.h>

#include "DiagSrv_SubMicon_Cfg.h"
#include "DiagSrv_0x2E_Cfg.h"
#include "DiagSrv_0x31_Cfg.h"

#include "DiagSrv_Local.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* SID 0x2E */
#define DIAGSRV_SUBM_0X2E_REQDATA_MIN_LEN       (DIAG_DIDMSG_MIN_SIZE + (uint16)1U)
#define DIAGSRV_SUBM_0X2E_DID_H_POS             ((uint8)1U)
#define DIAGSRV_SUBM_0X2E_DID_FINGERPRINT_0     ((uint16)0xF120U)
#define DIAGSRV_SUBM_0X2E_DID_FINGERPRINT_31    ((uint16)0xF13FU)
#define DIAGSRV_SUBM_MASK_DID_TO_REWRITEAREANUM ((uint16)0x001FU)

/* SID 0x31*/
#define DIAGSRV_SUBM_0X31_RID_CHECK_SBL         ((uint16)0xDD00U)
#define DIAGSRV_SUBM_0X31_RID_CHECK_APL         ((uint16)0xDD01U)
#define DIAGSRV_SUBM_0X31_RID_VALIDATE          ((uint16)0xDD02U)
#define DIAGSRV_SUBM_0X31_RID_H_POS             ((uint8)2U)
#define DIAGSRV_SUBM_0X31_CHKDATA_LEN_POS       ((uint8)5U)
#define DIAGSRV_SUBM_0X31_CHKDATA_POS           ((uint8)7U)

/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_SubM_CheckVariableMsgLength_0x31
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_CONST) Msg,
    VAR(uint16, AUTOMATIC) Rid
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>


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
/* Function Name | DiagSrv_SubM_GwCheck_0x2E                                  */
/* Description   | Judges whether the message is need to gateway to           */
/*               | Sub-microcontroller for Service 0x2E                       */
/* Preconditions |                                                            */
/* Parameters    | [IN]  Msg         : Message                                */
/*               | [OUT] MiconId     : Microcontroller identifier             */
/*               |        DIAGSRV_SUBM_ID_MAIN                                */
/*               |        DIAGSRV_SUBM_ID_SUB_XX [XX:1-31]                    */
/*               | [OUT] CheckResult : Check result                           */
/*               |        DIAGSRV_SUBM_GWTGT_OFF_SEQ_START                    */
/*               |        DIAGSRV_SUBM_GWTGT_ON                               */
/*               |        DIAGSRV_SUBM_GWTGT_ON_SEQ_START                     */
/* Return Value  | Nrc                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_IMLOIF                                           */
/*               |  DIAG_NRC_ROOR                                             */
/*               |  DIAG_NRC_SAD                                              */
/* Notes         | This function is valid when REPROG_CFG_SUBMICON_USE_MAIN   */
/*               | is defined.                                                */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_SubM_GwCheck_0x2E
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_CONST) Msg,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) MiconId,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) CheckResult
)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) Index;
    VAR(uint8, AUTOMATIC) Status;
    VAR(uint8, AUTOMATIC) RewriteAreaNum;
    VAR(uint16, AUTOMATIC) Did;

    Nrc = DIAG_NRC_IMLOIF;

    Status = DiagSrv_SubM_GetGwStatus();
    if( ( Status == DIAGSRV_SUBM_GW_STAT_IDLE ) || ( Status == DIAGSRV_SUBM_GW_STAT_FINISH ) )
    {
        if( Msg->ReqDataLen >= DIAGSRV_SUBM_0X2E_REQDATA_MIN_LEN )
        {
            Did = (uint16)Rte_Rpg_ByteCombine(&Msg->ReqData[DIAGSRV_SUBM_0X2E_DID_H_POS], sizeof(Did));
            Index = 0U;
            Nrc = DiagLib_CheckDidSupport(Did, &DiagSrv_0x2E_DidConfig, &Index);
            if( Nrc == DIAG_NRC_PR )
            {
                if( (Did >= DIAGSRV_SUBM_0X2E_DID_FINGERPRINT_0) && (Did <= DIAGSRV_SUBM_0X2E_DID_FINGERPRINT_31) )
                {
                    RewriteAreaNum = (uint8)( Did & DIAGSRV_SUBM_MASK_DID_TO_REWRITEAREANUM );

                    *MiconId = DiagSrv_SubM_ConvertRewriteArea2MiconId(RewriteAreaNum);
                    if( *MiconId == DIAGSRV_SUBM_ID_MAIN )
                    {
                        *CheckResult = DIAGSRV_SUBM_GWTGT_OFF_SEQ_START;
                    }
                    else
                    {
                        *CheckResult = DIAGSRV_SUBM_GWTGT_ON_SEQ_START;
                    }
                }
                else
                {
                    *MiconId = DIAGSRV_SUBM_ID_MAIN;
                    *CheckResult = DIAGSRV_SUBM_GWTGT_OFF;
                }
            }
        }
    }
    else
    {
        *MiconId = DiagSrv_SubM_GetSequenceMiconId();
        *CheckResult = DIAGSRV_SUBM_GWTGT_ON;
        Nrc = DIAG_NRC_PR;
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_SubM_GwCheck_0x31                                  */
/* Description   | Judges whether the message is need to gateway to           */
/*               | Sub-microcontroller for Service 0x31                       */
/* Preconditions |                                                            */
/* Parameters    | [IN]  Msg         : Message                                */
/*               | [OUT] MiconId     : Microcontroller identifier             */
/*               |        DIAGSRV_SUBM_ID_MAIN                                */
/*               |        DIAGSRV_SUBM_ID_SUB_XX [XX:1-31]                    */
/*               | [OUT] CheckResult : Check result                           */
/*               |        DIAGSRV_SUBM_GWTGT_OFF                              */
/*               |        DIAGSRV_SUBM_GWTGT_OFF_SEQ_END                      */
/*               |        DIAGSRV_SUBM_GWTGT_ON                               */
/*               |        DIAGSRV_SUBM_GWTGT_ON_SEQ_END                       */
/* Return Value  | Nrc                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_IMLOIF                                           */
/*               |  DIAG_NRC_ROOR                                             */
/*               |  DIAG_NRC_SAD                                              */
/*               |  DIAG_NRC_SFNS                                             */
/* Notes         | This function is valid when REPROG_CFG_SUBMICON_USE_MAIN   */
/*               | is defined.                                                */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_SubM_GwCheck_0x31
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_CONST) Msg,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) MiconId,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) CheckResult
)
{
    VAR(uint16, AUTOMATIC) Rid;
    VAR(uint8, AUTOMATIC) tmpMiconId;
    VAR(uint8, AUTOMATIC) tmpResult;
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) Index;

    Index = 0U;

    Nrc = DiagLib_CheckRidSupport(Msg, &DiagSrv_0x31_RidConfig, &Index);
    if( Nrc == DIAG_NRC_RCRRP )
    {
        Nrc = DiagSrv_SubM_CheckVariableMsgLength_0x31(Msg, DiagSrv_0x31_RidConfig.InfoPtr[Index].Rid);
    }

    if( Nrc == DIAG_NRC_PR )
    {
        tmpMiconId = DIAGSRV_SUBM_ID_MAIN;
        tmpResult = DIAGSRV_SUBM_GWTGT_OFF;

        Rid = DiagSrv_0x31_RidConfig.InfoPtr[Index].Rid;
        if( Rid == DIAGSRV_SUBM_0X31_RID_CHECK_APL )
        {
            tmpMiconId = DiagSrv_SubM_GetSequenceMiconId();
            if( tmpMiconId == DIAGSRV_SUBM_ID_MAIN )
            {
                tmpResult = DIAGSRV_SUBM_GWTGT_OFF_SEQ_END;
            }
            else
            {
                tmpResult = DIAGSRV_SUBM_GWTGT_ON_SEQ_END;
            }
        }
        else if( Rid == DIAGSRV_SUBM_0X31_RID_VALIDATE )
        {
            /* No process */
        }
        else
        {
            tmpMiconId = DiagSrv_SubM_GetSequenceMiconId();
            if( tmpMiconId != DIAGSRV_SUBM_ID_MAIN )
            {
                tmpResult = DIAGSRV_SUBM_GWTGT_ON;
            }
        }

        *MiconId = tmpMiconId;
        *CheckResult = tmpResult;
    }

    return Nrc;
}

/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

/******************************************************************************/
/* Function Name | DiagSrv_SubM_CheckVariableMsgLength_0x31                   */
/* Description   | Variable message size check                                */
/* Preconditions |                                                            */
/* Parameters    | [IN] Msg : Message                                         */
/*               | [IN] Rid : RID                                             */
/* Return Value  | NRC                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_IMLOIF                                           */
/* Notes         | None                                                       */
/******************************************************************************/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_SubM_CheckVariableMsgLength_0x31
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_CONST) Msg,
    VAR(uint16, AUTOMATIC) Rid
)
{
    VAR(uint16, AUTOMATIC) CheckDataLength;
    VAR(uint16, AUTOMATIC) TotalLength;
    VAR(uint8, AUTOMATIC) Nrc;

    Nrc = DIAG_NRC_IMLOIF;

    if( (Rid == DIAGSRV_SUBM_0X31_RID_CHECK_SBL) || (Rid == DIAGSRV_SUBM_0X31_RID_CHECK_APL) )
    {
        CheckDataLength = (uint16)Rte_Rpg_ByteCombine(&Msg->ReqData[DIAGSRV_SUBM_0X31_CHKDATA_LEN_POS],
                                                    sizeof(CheckDataLength));

        TotalLength = DIAGSRV_SUBM_0X31_CHKDATA_POS + CheckDataLength;

        if( Msg->ReqDataLen == TotalLength )
        {
            Nrc = DIAG_NRC_PR;
        }
    }

    return Nrc;
}

#define DIAGSRV_STOP_SEC_CODE
#include <DiagSrv_MemMap.h>

#endif  /* (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON) */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/09/14 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

