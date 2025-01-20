/* DiagSrv_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/HEADER                                              */
/******************************************************************************/
#ifndef DIAGSRV_H
#define DIAGSRV_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <DiagCmn.h>
#if (REPROG_CFG_SUBMICON_USE_MAIN == STD_ON)
#include <DiagSrv_SubMicon.h>
#endif


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, DIAGSRV_CODE_SLOW) DiagSrv_Init (void);
FUNC(void, DIAGSRV_CODE_SLOW) DiagSrv_Processing
(
    VAR(uint8, AUTOMATIC) Op,
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_DATA) Msg
);
FUNC(void, DIAGSRV_CODE_SLOW) DiagSrv_Time (void);
FUNC(void, DIAGSRV_CODE_SLOW) DiagSrv_Confirmation
(
    VAR(uint8, AUTOMATIC) Status
);
FUNC(void, DIAGSRV_CODE_SLOW) DiagSrv_NotifyChangeSession
(
    VAR(uint8, AUTOMATIC) OldSession,
    VAR(uint8, AUTOMATIC) NewSession,
    VAR(uint8, AUTOMATIC) Factor
);
FUNC(uint8, DIAGSRV_CODE_SLOW) DiagSrv_GetMainServiceId (void);


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


#endif /* DIAGSRV_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2019/12/03 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

