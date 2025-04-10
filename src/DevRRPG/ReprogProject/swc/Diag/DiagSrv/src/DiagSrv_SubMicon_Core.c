/* DiagSrv_SubMicon_Core_c_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/SubMicon/Core/CODE                                  */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
#include <DiagSrv_SubMicon.h>

#include "DiagSrv_SubMicon_Core_Cfg.h"
#include "DiagSrv_SubMicon_Cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    uint8 Status;
    uint8 MiconId;
} DiagSrv_SubM_GwInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_SubM_GwCheck
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_CONST) Msg,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) MiconId,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) CheckResult
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_START_SEC_VAR
#include <DiagSrv_MemMap.h>

static VAR(DiagSrv_SubM_GwInfoType, DIAGSRV_VAR_CLEARED) DiagSrv_SubM_GwInfo;

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
/* Function Name | DiagSrv_SubM_JudgeGw                                       */
/* Description   | Judges whether the message is need to gateway to           */
/*               | Sub-microcontroller                                        */
/* Preconditions |                                                            */
/* Parameters    | [IN]  Msg     : Message                                    */
/*               | [OUT] MiconId : Microcontroller identifier                 */
/*               |        DIAGSRV_SUBM_ID_MAIN                                */
/*               |        DIAGSRV_SUBM_ID_SUB_XX [XX:1-31]                    */
/* Return Value  | Nrc                                                        */
/*               |  DIAG_NRC_PR                                               */
/*               |  DIAG_NRC_IMLOIF                                           */
/*               |  DIAG_NRC_ROOR                                             */
/*               |  DIAG_NRC_SAD                                              */
/*               |  DIAG_NRC_SFNS                                             */
/* Notes         | This function is valid when REPROG_CFG_SUBMICON_USE_MAIN   */
/*               | is defined.                                                */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_SLOW) DiagSrv_SubM_JudgeGw
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_CONST) Msg,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) MiconId
)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) ChkRet;
    VAR(uint8, AUTOMATIC) Sid;
    VAR(uint8, AUTOMATIC) Index;
    VAR(uint8, AUTOMATIC) CfgExistFlg;

    *MiconId = DIAGSRV_SUBM_ID_MAIN;
    Nrc = DIAG_NRC_PR;
    ChkRet = DIAGSRV_SUBM_GWTGT_OFF;
    CfgExistFlg = STD_OFF;

    Sid = DIAG_GET_SID(Msg);

    for( Index = 0U; Index < DiagSrv_SubMGatewayConfig.Num; Index++ )
    {
        if( Sid == DiagSrv_SubMGatewayConfig.InfoPtr[Index].Sid )
        {
            CfgExistFlg = STD_ON;
            break;
        }
    }

    if( CfgExistFlg == (uint8)STD_ON )
    {
        if( DiagSrv_SubMGatewayConfig.InfoPtr[Index].GwKind == DIAGSRV_SUBM_GW_DEPEND_MSG )
        {
            Nrc = DiagSrv_SubM_GwCheck(Msg, MiconId, &ChkRet);

            if( Nrc == DIAG_NRC_PR )
            {
                if( ( ChkRet == DIAGSRV_SUBM_GWTGT_ON_SEQ_START ) ||
                    ( ChkRet == DIAGSRV_SUBM_GWTGT_OFF_SEQ_START ) )
                {
                    if( *MiconId == DIAGSRV_SUBM_ID_MAIN )
                    {
                        DiagSrv_SubM_SetGwStatus(DIAGSRV_SUBM_GW_STAT_IDLE);
                    }
                    else
                    {
                        DiagSrv_SubM_SetGwStatus(DIAGSRV_SUBM_GW_STAT_EXEC);
                    }

                    DiagSrv_SubM_GwInfo.MiconId = *MiconId;
                }
                else if( ChkRet == DIAGSRV_SUBM_GWTGT_ON_SEQ_END )
                {
                    DiagSrv_SubM_SetGwStatus(DIAGSRV_SUBM_GW_STAT_FINISH);
                }
                else    /* DIAGSRV_SUBM_GWTGT_ON, DIAGSRV_SUBM_GWTGT_OFF, DIAGSRV_SUBM_GWTGT_OFF_SEQ_END */
                {
                    /* No process */
                }
            }
        }
        else
        {
            *MiconId = DiagSrv_SubM_GetSequenceMiconId();
        }
    }

    return Nrc;
}

/******************************************************************************/
/* Function Name | DiagSrv_SubM_ConvertRewriteArea2MiconId                    */
/* Description   | Converts from rewrite area number to Microcontroller       */
/*               | identifier                                                 */
/* Preconditions |                                                            */
/* Parameters    | [IN] RewriteAreaNum : Rewrite area number                  */
/* Return Value  | Microcontroller identifier                                 */
/*               |  DIAGSRV_SUBM_ID_MAIN                                      */
/*               |  DIAGSRV_SUBM_ID_SUB_XX [XX:1-31]                          */
/* Notes         | This function is valid when REPROG_CFG_SUBMICON_USE_MAIN   */
/*               | is defined.                                                */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_SLOW) DiagSrv_SubM_ConvertRewriteArea2MiconId
(
    VAR(uint8, AUTOMATIC) RewriteAreaNum
)
{
    VAR(uint8, AUTOMATIC) MiconId;
    VAR(uint8, AUTOMATIC) i;
    VAR(uint8, AUTOMATIC) j;

    MiconId = DIAGSRV_SUBM_ID_MAIN;

    for( i = 0U; i < DiagSrv_SubMRewriteConfig.MiconNum; i++ )
    {
        for( j = 0U; j < DiagSrv_SubMRewriteConfig.AreaPtr[i].InfoNum; j++ )
        {
            if( DiagSrv_SubMRewriteConfig.AreaPtr[i].InfoPtr[j] == RewriteAreaNum )
            {
                MiconId = DiagSrv_SubMRewriteConfig.AreaPtr[i].MiconId;
                break;
            }
        }
    }

    return MiconId;
}

/******************************************************************************/
/* Function Name | DiagSrv_SubM_ClearSequence                                 */
/* Description   | Clears information about gateway to Sub-microcontroller    */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | None                                                       */
/* Notes         | This function is valid when REPROG_CFG_SUBMICON_USE_MAIN   */
/*               | is defined.                                                */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_SLOW) DiagSrv_SubM_ClearSequence (void)
{
    DiagSrv_SubM_GwInfo.Status = DIAGSRV_SUBM_GW_STAT_IDLE;
    DiagSrv_SubM_GwInfo.MiconId = DIAGSRV_SUBM_ID_MAIN;

    return;
}

/******************************************************************************/
/* Function Name | DiagSrv_SubM_GetSequenceMiconId                            */
/* Description   | Acquires Microcontroller identifier to be rewriting        */
/*               | currently                                                  */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Microcontroller identifier                                 */
/*               |  DIAGSRV_SUBM_ID_MAIN                                      */
/*               |  DIAGSRV_SUBM_ID_SUB_XX [XX:1-31]                          */
/* Notes         | This function is valid when REPROG_CFG_SUBMICON_USE_MAIN   */
/*               | is defined.                                                */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_SLOW) DiagSrv_SubM_GetSequenceMiconId (void)
{
    return DiagSrv_SubM_GwInfo.MiconId;
}

/******************************************************************************/
/* Function Name | DiagSrv_SubM_GetGwStatus                                   */
/* Description   | Acquires status of gateway to Sub-microcontroller          */
/* Preconditions |                                                            */
/* Parameters    | None                                                       */
/* Return Value  | Gateway Status                                             */
/*               |  DIAGSRV_SUBM_GW_STAT_IDLE                                 */
/*               |  DIAGSRV_SUBM_GW_STAT_EXEC                                 */
/*               |  DIAGSRV_SUBM_GW_STAT_FINISH                               */
/* Notes         | This function is valid when REPROG_CFG_SUBMICON_USE_MAIN   */
/*               | is defined.                                                */
/******************************************************************************/
FUNC(uint8, DIAGSRV_CODE_SLOW) DiagSrv_SubM_GetGwStatus (void)
{
    return DiagSrv_SubM_GwInfo.Status;
}

/******************************************************************************/
/* Function Name | DiagSrv_SubM_SetGwStatus                                   */
/* Description   | Sets status of gateway to Sub-microcontroller              */
/* Preconditions |                                                            */
/* Parameters    | [IN] Status : Gateway Status                               */
/*               |       DIAGSRV_SUBM_GW_STAT_IDLE                            */
/*               |       DIAGSRV_SUBM_GW_STAT_EXEC                            */
/*               |       DIAGSRV_SUBM_GW_STAT_FINISH                          */
/* Return Value  | None                                                       */
/* Notes         | This function is valid when REPROG_CFG_SUBMICON_USE_MAIN   */
/*               | is defined.                                                */
/******************************************************************************/
FUNC(void, DIAGSRV_CODE_SLOW) DiagSrv_SubM_SetGwStatus
(
    VAR(uint8, AUTOMATIC) Status
)
{
    DiagSrv_SubM_GwInfo.Status = Status;

    return;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/
/******************************************************************************/
/* Function Name | DiagSrv_SubM_GwCheck                                       */
/* Description   | Judges whether the message is need to gateway to           */
/*               | Sub-microcontroller                                        */
/* Preconditions |                                                            */
/* Parameters    | [IN]  Msg         : Message                                */
/*               | [OUT] MiconId     : Microcontroller identifier             */
/*               |        DIAGSRV_SUBM_ID_MAIN                                */
/*               |        DIAGSRV_SUBM_ID_SUB_XX [XX:1-31]                    */
/*               | [OUT] CheckResult : Check result                           */
/*               |        DIAGSRV_SUBM_GWTGT_OFF                              */
/*               |        DIAGSRV_SUBM_GWTGT_OFF_SEQ_START                    */
/*               |        DIAGSRV_SUBM_GWTGT_OFF_SEQ_END                      */
/*               |        DIAGSRV_SUBM_GWTGT_ON                               */
/*               |        DIAGSRV_SUBM_GWTGT_ON_SEQ_START                     */
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
static FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_SubM_GwCheck
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_CONST) Msg,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) MiconId,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) CheckResult
)
{
    VAR(uint8, AUTOMATIC) Nrc;
    VAR(uint8, AUTOMATIC) Sid;
    VAR(uint8, AUTOMATIC) i;

    *MiconId = DIAGSRV_SUBM_ID_MAIN;
    *CheckResult = DIAGSRV_SUBM_GWTGT_OFF;
    Nrc = DIAG_NRC_PR;

    Sid = DIAG_GET_SID(Msg);

    for( i = 0U; i < DiagSrv_SubM_GwCheckConfig.Num; i++ )
    {
        if( Sid == DiagSrv_SubM_GwCheckConfig.InfoPtr[i].Sid )
        {
            Nrc = DiagSrv_SubM_GwCheckConfig.InfoPtr[i].GwCheckFunc(Msg, MiconId, CheckResult);
            break;
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

