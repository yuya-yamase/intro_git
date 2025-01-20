/* DiagSrv_0x22_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | DiagSrv/0x22/HEADER                                         */
/******************************************************************************/
#ifndef DIAGSRV_0X22_H
#define DIAGSRV_0X22_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <DiagCmn.h>


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DIAGSRV_0X22_USR_IDLE               ((uint8)0x00U)
#define DIAGSRV_0X22_USR_BUSY               ((uint8)0x01U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_Init (void);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_Time (void);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_Processing
(
    P2VAR(Diag_MsgContextType, AUTOMATIC, DIAGSRV_APPL_DATA) Msg
);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_Confirmation
(
    VAR(uint8, AUTOMATIC) Status
);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_Usr_Init (void);
FUNC(void, DIAGSRV_CODE_FAST) DiagSrv_0x22_Usr_Time (void);
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_Usr_ReqReadDidData
(
    VAR(uint16, AUTOMATIC) Did,
    P2VAR(uint8, AUTOMATIC, DIAGSRV_APPL_DATA) Data,
    VAR(uint16, AUTOMATIC) DataLength
);
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_Usr_GetStatus (void);
FUNC(uint8, DIAGSRV_CODE_FAST) DiagSrv_0x22_Usr_GetJobResult (void);


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

#endif /* DIAGSRV_0X22_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/03/09 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

