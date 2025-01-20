/* DiagSrv_Template_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/Template/HEADER                                     */
/******************************************************************************/
#ifndef DIAGSRV_TEMPLATE_H
#define DIAGSRV_TEMPLATE_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <DiagCmn.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_Template_Init (void);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_Template_Time (void);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_Template_Processing
(
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_DATA) Msg
);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_Template_Confirmation
(
    VAR(uint8, AUTOMATIC) Status
);
#if 0
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_Template_NotifyChangeSession
(
    VAR(uint8, AUTOMATIC) OldSession,
    VAR(uint8, AUTOMATIC) NewSession,
    VAR(uint8, AUTOMATIC) Factor
);
#endif

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

#endif /* DIAGSRV_TEMPLATE_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2019/12/03 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

