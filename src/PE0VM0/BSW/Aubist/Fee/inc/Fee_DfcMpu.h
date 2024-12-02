/* Fee_DfcMpu.h v2-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/DFCMPU/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_DFCMPU_H
#define FEE_DFCMPU_H

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define FEE_DFCMPU_RESULT_OK                  ((uint8)0x00U) /* Success          */
#define FEE_DFCMPU_RESULT_BLANK               ((uint8)0x01U) /* Blank            */
#define FEE_DFCMPU_RESULT_NG_BLANKCHECK       ((uint8)0x02U) /* Blank error      */
#define FEE_DFCMPU_RESULT_NG_COMPARE          ((uint8)0x03U) /* Compare error    */
#define FEE_DFCMPU_RESULT_NG_READ             ((uint8)0x04U) /* Read error       */
#define FEE_DFCMPU_RESULT_ERROR               ((uint8)0x05U) /* General error    */
#define FEE_DFCMPU_RESULT_FATALERROR          ((uint8)0x06U) /* Fatal error      */
#define FEE_DFCMPU_RESULT_INOPERATIVE_HSM     ((uint8)0x07U) /* HSM in operation */
#define FEE_DFCMPU_RESULT_INTEGRITY_FAILED    ((uint8)0x08U) /* Data corruption  */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

FUNC( uint8, FEE_CODE )
Fee_DfcMpu_SyncRead(
    uint32                           SourceAddress,
    P2VAR(uint8, AUTOMATIC, TYPEDEF) TargetAddressPtr,
    uint32                           Length
);

FUNC( uint8, FEE_CODE )
Fee_DfcMpu_SyncReadUint16(
    uint32                            SourceAddress,
    P2VAR(uint16, AUTOMATIC, TYPEDEF) TargetAddressPtr 
);

FUNC( uint8, FEE_CODE )
Fee_DfcMpu_SyncReadUint32(
    uint32                            SourceAddress,
    P2VAR(uint32, AUTOMATIC, TYPEDEF) TargetAddressPtr 
);

FUNC( uint8, FEE_CODE )
Fee_DfcMpu_SyncCompare_EccFixSize(
    uint32                             SourceAddress,
    P2CONST(uint8, AUTOMATIC, TYPEDEF) TargetAddressPtr
);

FUNC( uint8, FEE_CODE )
Fee_DfcMpu_SyncBlankCheck(
    uint32 SourceAddress,
    uint32 Length
);

FUNC( uint8, FEE_CODE )
Fee_DfcMpu_SyncNotBlankAddress(
    uint32                            SourceAddress,
    uint32                            Length,
    P2VAR(uint32, AUTOMATIC, TYPEDEF) NotBlankAddress
);

FUNC( uint8, FEE_CODE )
Fee_DfcMpu_DirectRead(
    uint32                           SourceAddress,
    P2VAR(uint8, AUTOMATIC, TYPEDEF) TargetAddressPtr,
    uint32                           Length
);

FUNC( uint8, FEE_CODE )
Fee_DfcMpu_DirectBlankCheck(
    uint32 SourceAddress,
    uint32 Length
);

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

#endif /* FEE_DFCMPU_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
