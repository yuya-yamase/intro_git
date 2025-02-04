/* RpgMfr_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | RpgMfr/HEADER                                               */
/******************************************************************************/
#ifndef RPGMFR_H
#define RPGMFR_H

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
/* RpgMfr.c */
FUNC(void, RPGMFR_CODE_SLOW) RpgMfr_Init (void);
FUNC(void, RPGMFR_CODE_SLOW) RpgMfr_DeInit (void);
FUNC(void, RPGMFR_CODE_SLOW) RpgMfr_Time (void);
FUNC(void, RPGMFR_CODE_SLOW) RpgMfr_MainFunction (void);
FUNC(uint8, RPGMFR_CODE_SLOW) RpgMfr_CommonCheckCondition (void);
FUNC(uint8, RPGMFR_CODE_SLOW) RpgMfr_MsgCheckCondition
(
    P2CONST(Diag_MsgContextType, AUTOMATIC, RPGMFR_APPL_CONST) Msg
);
FUNC(uint8, RPGMFR_CODE_SLOW) RpgMfr_VoltCheckConditionForDataWrite
(
    VAR(uint16, AUTOMATIC) Volt
);
/* RpgMfr_Core.c */
FUNC(uint8, RPGMFR_CODE_SLOW) RpgMfr_VoltCheckConditionForPrgSession
(
    VAR(uint16, AUTOMATIC) Volt
);
FUNC(Std_ReturnType, RPGMFR_CODE_SLOW) RpgMfr_ApEntryCheck
(
    VAR(uint8, AUTOMATIC) Sid,
    P2VAR(uint8, AUTOMATIC, RPGMFR_APPL_DATA) RespFlg
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define RPGMFR_START_SEC_VAR
#include <RpgMfr_MemMap.h>

#define RPGMFR_STOP_SEC_VAR
#include <RpgMfr_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define RPGMFR_START_SEC_CST
#include <RpgMfr_MemMap.h>

#define RPGMFR_STOP_SEC_CST
#include <RpgMfr_MemMap.h>


#endif /* RPGMFR_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2021/09/14 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

