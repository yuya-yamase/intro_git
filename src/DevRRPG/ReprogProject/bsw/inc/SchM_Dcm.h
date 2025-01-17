/* SchM_Dcm_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | SchM/Dcm/HEADER                                             */
/******************************************************************************/
#ifndef SCHM_DCM_H
#define SCHM_DCM_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <BswM.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define SCHM_E_OK                       (E_OK)

/* Session */
#define SCHM_BSWM_SESSION_DEF           ((uint16)BSWM_MODE_SESSION_DEF)
#define SCHM_BSWM_SESSION_EXT           ((uint16)BSWM_MODE_SESSION_EXT)
#define SCHM_BSWM_SESSION_PRG           ((uint16)BSWM_MODE_SESSION_PRG)
/* Ecu Reset */
#define SCHM_BSWM_ECU_RESET_EXECUTE     ((uint16)BSWM_MODE_ECU_RESET_EXECUTE)
/* Security */
#define SCHM_BSWM_SECURITY_LOCK         ((uint16)BSWM_MODE_SECURITY_LOCK)
#define SCHM_BSWM_SECURITY_UNLOCK_LV1   ((uint16)BSWM_MODE_SECURITY_UNLOCK_LV1)
#define SCHM_BSWM_SECURITY_UNLOCK_LV2   ((uint16)BSWM_MODE_SECURITY_UNLOCK_LV2)
#define SCHM_BSWM_SECURITY_UNLOCK_LV3   ((uint16)BSWM_MODE_SECURITY_UNLOCK_LV3)
#define SCHM_BSWM_SECURITY_UNLOCK_LV4   ((uint16)BSWM_MODE_SECURITY_UNLOCK_LV4)
#define SCHM_BSWM_SECURITY_UNLOCK_LV5   ((uint16)BSWM_MODE_SECURITY_UNLOCK_LV5)
#define SCHM_BSWM_SECURITY_UNLOCK_LV6   ((uint16)BSWM_MODE_SECURITY_UNLOCK_LV6)
#define SCHM_BSWM_SECURITY_UNLOCK_LV7   ((uint16)BSWM_MODE_SECURITY_UNLOCK_LV7)
#define SCHM_BSWM_SECURITY_UNLOCK_LV8   ((uint16)BSWM_MODE_SECURITY_UNLOCK_LV8)
/* Memory rewrite */
#define SCHM_BSWM_REWRITE_START         ((uint16)BSWM_MODE_REWRITE_START)
#define SCHM_BSWM_REWRITE_FINISH        ((uint16)BSWM_MODE_REWRITE_FINISH)
/* Fls program */
#define SCHM_BSWM_FLS_PRG_NOTREADY      ((uint16)BSWM_MODE_FLS_PRG_NOTREADY)
#define SCHM_BSWM_FLS_PRG_READY         ((uint16)BSWM_MODE_FLS_PRG_READY)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(Std_ReturnType, SCHM_CODE_SLOW) SchM_Switch_DcmDiagnosticSessionControl
(
    VAR(uint16, AUTOMATIC) Mode
);
FUNC(Std_ReturnType, SCHM_CODE_SLOW) SchM_Switch_DcmEcuReset
(
    VAR(uint16, AUTOMATIC) Mode
);
FUNC(Std_ReturnType, SCHM_CODE_SLOW) SchM_Switch_DcmSecurityControl
(
    VAR(uint16, AUTOMATIC) Mode
);
FUNC(Std_ReturnType, SCHM_CODE_SLOW) SchM_Switch_DcmRewriteControl
(
    VAR(uint16, AUTOMATIC) Mode
);
FUNC(Std_ReturnType, SCHM_CODE_SLOW) SchM_Switch_DcmFlsProgram
(
    VAR(uint16, AUTOMATIC) Mode
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/


#endif /* SCHM_DCM_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2017/10/17 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

