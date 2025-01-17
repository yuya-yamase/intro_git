/* PrgChk_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | PrgChk/HEADER                                               */
/******************************************************************************/
#ifndef PRGCHK_H
#define PRGCHK_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define PRGCHK_IDLE             ((uint8)0x00U)
#define PRGCHK_BUSY             ((uint8)0x01U)

#define PRGCHK_JOB_OK           ((uint8)0x00U)
#define PRGCHK_JOB_FAILED       ((uint8)0x01U)
#define PRGCHK_JOB_PENDING      ((uint8)0x02U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, PRGCHK_CODE_SLOW) PrgChk_Init (void);
FUNC(void, PRGCHK_CODE_SLOW) PrgChk_DeInit (void);
FUNC(void, PRGCHK_CODE_SLOW) PrgChk_Time (void);
FUNC(void, PRGCHK_CODE_SLOW) PrgChk_MainFunction (void);
FUNC(uint8, PRGCHK_CODE_SLOW) PrgChk_GetStatus (void);
FUNC(uint8, PRGCHK_CODE_SLOW) PrgChk_GetJobResult (void);
FUNC(Std_ReturnType, PRGCHK_CODE_SLOW) PrgChk_PreCalcValue (void);
FUNC(Std_ReturnType, PRGCHK_CODE_SLOW) PrgChk_PostCalcValue (void);
FUNC(Std_ReturnType, PRGCHK_CODE_SLOW) PrgChk_ReqCalcValue
(
    VAR(uint32, AUTOMATIC) TargetAddr,
    VAR(uint32, AUTOMATIC) TargetSize,
    P2VAR(uint8, AUTOMATIC, PRGCHK_APPL_DATA) Value,
    VAR(uint16, AUTOMATIC) ValueSize
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define PRGCHK_START_SEC_VAR
#include <PrgChk_MemMap.h>

#define PRGCHK_STOP_SEC_VAR
#include <PrgChk_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define PRGCHK_START_SEC_CST
#include <PrgChk_MemMap.h>

#define PRGCHK_STOP_SEC_CST
#include <PrgChk_MemMap.h>


#endif /* PRGCHK_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2019/12/03 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

