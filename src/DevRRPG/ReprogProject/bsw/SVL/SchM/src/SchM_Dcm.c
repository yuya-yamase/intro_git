/* SchM_Dcm_c_Revision(v3.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | SchM/Dcm/CODE                                               */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

#include <SchM.h>
#include <SchM_Dcm.h>
#include "SchM_Local.h"

#include <BswM.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define SCHM_RPRG_START_SEC_VAR
#include <SchM_Rprg_MemMap.h>

#define SCHM_RPRG_STOP_SEC_VAR
#include <SchM_Rprg_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define SCHM_RPRG_START_SEC_CST
#include <SchM_Rprg_MemMap.h>

#define SCHM_RPRG_STOP_SEC_CST
#include <SchM_Rprg_MemMap.h>


/******************************************************************************/
/* External Functions                                                         */
/******************************************************************************/
#define SCHM_RPRG_START_SEC_CODE
#include <SchM_Rprg_MemMap.h>

/******************************************************************************/
/* Function Name | SchM_Switch_DcmDiagnosticSessionControl                    */
/* Description   | Notifies BswM of a session                                 */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : Session mode                                   */
/*               |       SCHM_BSWM_SESSION_DEF                                */
/*               |       SCHM_BSWM_SESSION_EXT                                */
/*               |       SCHM_BSWM_SESSION_PRG                                */
/* Return Value  | Status                                                     */
/*               |  SCHM_E_OK                                                 */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, SCHM_CODE_SLOW) SchM_Switch_DcmDiagnosticSessionControl
(
    VAR(uint16, AUTOMATIC) Mode
)
{
    if( SchM_CfgPtr != NULL_PTR )
    {
        BswM_RequestMode(BSWM_USER_SCHM_SESSION, (BswM_ModeType)Mode);
#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
        if( Mode == SCHM_BSWM_SESSION_PRG )
        {
            /* Even if this function call returned with E_NOT_OK, nothing to do. */
            (void)SchM_SetStayInBootState(SCHM_STATE_STAYINBOOT_PRGRCV);
        }
#endif
    }
    else
    {
        SchM_ReportError(SCHM_API_ID_SW_SESSION, SCHM_E_UNINIT);
    }

    return SCHM_E_OK;
}

/******************************************************************************/
/* Function Name | SchM_Switch_DcmEcuReset                                    */
/* Description   | Notifies BswM of a ECU reset mode                          */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : ECU reset mode                                 */
/*               |       SCHM_BSWM_ECU_RESET_EXECUTE                          */
/* Return Value  | Status                                                     */
/*               |  SCHM_E_OK                                                 */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, SCHM_CODE_SLOW) SchM_Switch_DcmEcuReset
(
    VAR(uint16, AUTOMATIC) Mode
)
{
    if( SchM_CfgPtr != NULL_PTR )
    {
        BswM_RequestMode(BSWM_USER_SCHM_ECU_RESET, (BswM_ModeType)Mode);
    }
    else
    {
        SchM_ReportError(SCHM_API_ID_SW_RESET, SCHM_E_UNINIT);
    }

    return SCHM_E_OK;
}

/******************************************************************************/
/* Function Name | SchM_Switch_DcmSecurityControl                             */
/* Description   | Notifies BswM of a security control mode                   */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : Security control mode                          */
/*               |       SCHM_BSWM_SECURITY_LOCK                              */
/*               |       SCHM_BSWM_SECURITY_UNLOCK_LV1                        */
/*               |       SCHM_BSWM_SECURITY_UNLOCK_LV2                        */
/*               |       SCHM_BSWM_SECURITY_UNLOCK_LV3                        */
/*               |       SCHM_BSWM_SECURITY_UNLOCK_LV4                        */
/*               |       SCHM_BSWM_SECURITY_UNLOCK_LV5                        */
/*               |       SCHM_BSWM_SECURITY_UNLOCK_LV6                        */
/*               |       SCHM_BSWM_SECURITY_UNLOCK_LV7                        */
/*               |       SCHM_BSWM_SECURITY_UNLOCK_LV8                        */
/* Return Value  | Status                                                     */
/*               |  SCHM_E_OK                                                 */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, SCHM_CODE_SLOW) SchM_Switch_DcmSecurityControl
(
    VAR(uint16, AUTOMATIC) Mode
)
{
    if( SchM_CfgPtr != NULL_PTR )
    {
        BswM_RequestMode(BSWM_USER_SCHM_SECURITY, (BswM_ModeType)Mode);
    }
    else
    {
        SchM_ReportError(SCHM_API_ID_SW_SECURITY, SCHM_E_UNINIT);
    }

    return SCHM_E_OK;
}

/******************************************************************************/
/* Function Name | SchM_Switch_DcmRewriteControl                              */
/* Description   | Notifies BswM of a rewrite control mode                    */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : Rewrite control mode                           */
/*               |       SCHM_BSWM_REWRITE_START                              */
/*               |       SCHM_BSWM_REWRITE_FINISH                             */
/* Return Value  | Status                                                     */
/*               |  SCHM_E_OK                                                 */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, SCHM_CODE_SLOW) SchM_Switch_DcmRewriteControl
(
    VAR(uint16, AUTOMATIC) Mode
)
{
#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
    VAR(uint8, AUTOMATIC) RewriteCompFlg;
#endif

    if( SchM_CfgPtr != NULL_PTR )
    {
        BswM_RequestMode(BSWM_USER_SCHM_REWRITE, (BswM_ModeType)Mode);
#if (REPROG_CFG_STAYINBOOT_ENABLE == STD_ON)
        RewriteCompFlg = STD_OFF;
        if( Mode == SCHM_BSWM_REWRITE_FINISH )
        {
            RewriteCompFlg = STD_ON;
        }
        SchM_SetRewriteCompFlg(RewriteCompFlg);
#endif
    }
    else
    {
        SchM_ReportError(SCHM_API_ID_SW_REWRITE, SCHM_E_UNINIT);
    }

    return SCHM_E_OK;
}

/******************************************************************************/
/* Function Name | SchM_Switch_DcmFlsProgram                                  */
/* Description   | Notifies BswM of a flash program mode                      */
/* Preconditions |                                                            */
/* Parameters    | [IN] Mode : Flash program mode                             */
/*               |       SCHM_BSWM_FLS_PRG_NOTREADY                           */
/*               |       SCHM_BSWM_FLS_PRG_READY                              */
/* Return Value  | Status                                                     */
/*               |  SCHM_E_OK                                                 */
/* Notes         | None                                                       */
/******************************************************************************/
FUNC(Std_ReturnType, SCHM_CODE_SLOW) SchM_Switch_DcmFlsProgram
(
    VAR(uint16, AUTOMATIC) Mode
)
{
    if( SchM_CfgPtr != NULL_PTR )
    {
        BswM_RequestMode(BSWM_USER_SCHM_FLS_PRG, (BswM_ModeType)Mode);
    }
    else
    {
        SchM_ReportError(SCHM_API_ID_SW_FLSPRG, SCHM_E_UNINIT);
    }

    return SCHM_E_OK;
}


/******************************************************************************/
/* Internal Functions                                                         */
/******************************************************************************/

#define SCHM_RPRG_STOP_SEC_CODE
#include <SchM_Rprg_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*  v2.00       :2018/06/19 :Update                                rel.AUBASS */
/*  v3.00       :2021/09/14 :Update                                rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

