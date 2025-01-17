/* Decrypt_h_Revision(v1.00) */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright AUBASS CO., LTD.                                                 */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | Decrypt/HEADER                                              */
/******************************************************************************/
#ifndef DECRYPT_H
#define DECRYPT_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
#define DECRYPT_IDLE         ((uint8)0x00U)
#define DECRYPT_BUSY         ((uint8)0x01U)

#define DECRYPT_JOB_OK       ((uint8)0x00U)
#define DECRYPT_JOB_FAILED   ((uint8)0x01U)
#define DECRYPT_JOB_PENDING  ((uint8)0x02U)


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef struct {
    P2VAR(uint8, TYPEDEF, DECRYPT_APPL_DATA) Nonce;  /* &Nonce[0] needs to be 4 byte alignment. */
    uint16 NonceSize;
} Decrypt_NonceInfoType;


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
FUNC(void, DECRYPT_CODE_SLOW) Decrypt_Init (void);
FUNC(void, DECRYPT_CODE_SLOW) Decrypt_DeInit (void);
FUNC(void, DECRYPT_CODE_SLOW) Decrypt_Time (void);
FUNC(void, DECRYPT_CODE_SLOW) Decrypt_MainFunction (void);
FUNC(uint8, DECRYPT_CODE_SLOW) Decrypt_GetStatus (void);
FUNC(uint8, DECRYPT_CODE_SLOW) Decrypt_GetJobResult (void);
FUNC(void, DECRYPT_CODE_SLOW) Decrypt_ReqPreDecode
(
    P2CONST(Decrypt_NonceInfoType, AUTOMATIC, DECRYPT_APPL_CONST) NonceInfo
);
FUNC(void, DECRYPT_CODE_SLOW) Decrypt_ReqPostDecode (void);
FUNC(void, DECRYPT_CODE_SLOW) Decrypt_ReqDecode
(
    P2CONST(uint8, AUTOMATIC, DECRYPT_APPL_CONST) SrcAddr,
    P2VAR(uint8, AUTOMATIC, DECRYPT_APPL_DATA) DestAddr,
    VAR(uint16, AUTOMATIC) Size
);


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/
#define DECRYPT_START_SEC_VAR
#include <Decrypt_MemMap.h>

#define DECRYPT_STOP_SEC_VAR
#include <Decrypt_MemMap.h>


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DECRYPT_START_SEC_CST
#include <Decrypt_MemMap.h>

#define DECRYPT_STOP_SEC_CST
#include <Decrypt_MemMap.h>


#endif /* DECRYPT_H */

/*----------------------------------------------------------------------------*/
/* Revision History                                                           */
/*  Revision    :Date       :Description                                      */
/*  v1.00       :2022/10/04 :New                                   rel.AUBASS */
/*----------------------------------------------------------------------------*/
/* Notes        |                                                             */
/*----------------------------------------------------------------------------*/
/**** End of File *************************************************************/
