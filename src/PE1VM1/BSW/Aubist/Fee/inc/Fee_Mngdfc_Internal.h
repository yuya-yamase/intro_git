/* Fee_Mngdfc_Internal.h v2-1-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/MNGDFC/INTERNAL/HEADER                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_MNGDFC_INTERNAL_H
#define FEE_MNGDFC_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define FEE_NEXT_CWRITENUM_OFFSET       (1U)    /* Offset next element of number of consecutive writes */
#define FEE_CWRITENUM_ZERO              (0U)    /* Consecutive writes 0 */
#define FEE_CWRITE_LAST_INDEX_OFFSET    (1U)    /* Offset to calculate index indicating last continuous write data */
#define FEE_HALFWORD_DATA_INVALID       (0U)    /* Invalid half-word data */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/* Data Flash Control Management Write Termination */
FUNC(void, FEE_CODE) Fee_MngDfcEndWriteProcess( void );
/* Data Flash Control Management blank check termination processing */
FUNC(void, FEE_CODE) Fee_MngDfcEndBlanckCheckProcess( void );
/* Data Flash Control Management blank check termination processing */
FUNC(void, FEE_CODE) Fee_MngDfcEndEraseProcess( void );

FUNC(uint32, FEE_CODE) Fee_MngDfcComCWrite(
    uint32 u4tDFCResult
);
FUNC(uint32, FEE_CODE) Fee_MngDfcComRetry( void );
FUNC(void, FEE_CODE) Fee_MngDfcReqWrite( void );
/* Data Flash Control Management Common Process */
FUNC(uint32, FEE_CODE) Fee_MngDfcCom( uint8 u1_callmode );

FUNC( uint32, FEE_CODE )
Fee_MngDfc_ExecDfcAndCheckStatus( uint8 u1_callmode );

FUNC( void, FEE_CODE )
Fee_MngDfc_VolChkWrite(
    const uint32 u4Address,
    P2CONST(uint8, AUTOMATIC, TYPEDEF) ptu1Data,
    const uint16 u2Len,
    const uint16 u2Flag
);

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* FEE_MNGDFC_INTERNAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  2-0-0          :2021/06/02                                              */
/*  2-1-0          :2024/07/19                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
