/* Fee_Types.h v1-1-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/TYPES/HEADER                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_TYPES_H
#define FEE_TYPES_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>

/*----------------------------------------------------------------------------*/
/*  Types       */
/*----------------------------------------------------------------------------*/
typedef uint16      Fee_LengthType;
typedef uint16      Fee_IdType;
typedef uint32      Fee_ResultType;

typedef Fee_IdType  Fee_RecordIdType;
typedef uint32      Fee_AddressType;
typedef uint16      Fee_BlockNoType;
typedef uint8       Fee_LevelType;
typedef uint16      Fee_CheckCodeType;
typedef uint32      Fee_CheckCode2Type;
typedef uint32      Fee_DtfWriteUnitType;

typedef struct{
    uint16          BlockNo;
    Fee_LengthType  Length;
    uint8           Level;
}Fee_IdInfoTblType;

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define FEE_BYTE_NUM_01                 (1U)
#define FEE_BYTE_NUM_02                 (2U)
#define FEE_BYTE_NUM_04                 (4U)
#define FEE_BYTE_NUM_06                 (6U)
#define FEE_BYTE_NUM_08                 (8U)
#define FEE_BYTE_NUM_16                 (16U)
#define FEE_BYTE_NUM_32                 (32U)
#define FEE_BYTE_NUM_64                 (64U)

#define FEE_LEVEL_01                    (0U)
#define FEE_LEVEL_02                    (1U)
#define FEE_LEVEL_ERROR                 (0xFFU)

#define FEE_DATA_FLASH_SECTOR_BIG       (0U)
#define FEE_DATA_FLASH_SECTOR_SMALL     (1U)

#define FEE_INTENT_RBLD_BLOCK_ID_NONE   (0xFFFFU)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

#endif /* FEE_TYPES_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2019/07/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
