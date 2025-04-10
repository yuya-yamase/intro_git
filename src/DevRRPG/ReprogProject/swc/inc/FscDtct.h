/* FscDtct_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | FscDtct/HEADER                                              */
/******************************************************************************/
#ifndef FSCDTCT_H
#define FSCDTCT_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define FSCDTCT_IDLE            ((uint8)0x00U)
#define FSCDTCT_BUSY            ((uint8)0x01U)

#define FSCDTCT_JOB_OK          ((uint8)0x00U)
#define FSCDTCT_JOB_FAILED      ((uint8)0x01U)
#define FSCDTCT_JOB_PENDING     ((uint8)0x02U)
#define FSCDTCT_JOB_VERIFYERR   ((uint8)0x03U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, FSCDTCT_CODE_SLOW) FscDtct_Init (void);
FUNC(void, FSCDTCT_CODE_SLOW) FscDtct_DeInit (void);
FUNC(void, FSCDTCT_CODE_SLOW) FscDtct_Time (void);
FUNC(void, FSCDTCT_CODE_SLOW) FscDtct_MainFunction (void);
FUNC(uint8, FSCDTCT_CODE_SLOW) FscDtct_GetStatus (void);
FUNC(uint8, FSCDTCT_CODE_SLOW) FscDtct_GetJobResult (void);
FUNC(void, FSCDTCT_CODE_SLOW) FscDtct_ReqPreSigVerify (void);
FUNC(void, FSCDTCT_CODE_SLOW) FscDtct_ReqPostSigVerify
(
    P2CONST(uint8, AUTOMATIC, FSCDTCT_APPL_CONST) SignatureAddr,
    VAR(uint32, AUTOMATIC) SignatureSize
);
FUNC(void, FSCDTCT_CODE_SLOW) FscDtct_ReqSigVerify
(
    VAR(uint32, AUTOMATIC) TargetAddress,
    VAR(uint32, AUTOMATIC) TargetSize
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define FSCDTCT_START_SEC_VAR
#include <FscDtct_MemMap.h>

#define FSCDTCT_STOP_SEC_VAR
#include <FscDtct_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define FSCDTCT_START_SEC_CST
#include <FscDtct_MemMap.h>

#define FSCDTCT_STOP_SEC_CST
#include <FscDtct_MemMap.h>


#endif /* FSCDTCT_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/

