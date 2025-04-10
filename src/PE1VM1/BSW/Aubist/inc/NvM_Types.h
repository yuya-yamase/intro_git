/* NvM_Types.h v2-0-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/TYPES/HEADER                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_TYPES_H
#define     NVM_TYPES_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <Std_Types.h>
#include <Rte_NvM_Type.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define NVM_CRC8                (1U)
#define NVM_CRC16               (2U)
#define NVM_CRC32               (4U)

#define NVM_BLOCK_DATASET       (1U)
#define NVM_BLOCK_NATIVE        (2U)
#define NVM_BLOCK_REDUNDANT     (4U)

#define NVM_API_CONFIG_CLASS_1  (1U)
#define NVM_API_CONFIG_CLASS_2  (2U)
#define NVM_API_CONFIG_CLASS_3  (4U)

#define NVM_RAM_BLOCK_TYPE_TEMPORARY    (1U)
#define NVM_RAM_BLOCK_TYPE_SHARED       (2U)
#define NVM_RAM_BLOCK_TYPE_MIRROR       (4U)

#define NVM_BLOCK_FLAGS_ALL_FALSE           (0x0000U)
#define NVM_BLOCK_USE_AUTO_VALIDATION       (0x0001U)
#define NVM_BLOCK_USE_CRC_COMP_MECHANISM    (0x0002U)
#define NVM_BLOCK_USE_SET_RAM_BLOCK_STATUS  (0x0004U)
#define NVM_BLOCK_USE_SYNC_MECHANISM        (0x0008U)
#define NVM_BLOCK_WRITE_PROT                (0x0010U)
#define NVM_BSWM_BLOCK_STATUS_INFORMATION   (0x0020U)
#define NVM_CALC_RAM_BLOCK_CRC              (0x0040U)
#define NVM_RESISTANT_TO_CHANGED_SW         (0x0080U)
#define NVM_SELECT_BLOCK_FOR_READ_ALL       (0x0100U)
#define NVM_SELECT_BLOCK_FOR_WRITE_ALL      (0x0200U)
#define NVM_STATIC_BLOCKID_CHECK            (0x0400U)
#define NVM_WRITE_BLOCK_ONCE                (0x0800U)
#define NVM_WRITE_VERIFICATION              (0x1000U)

#ifndef NVM_READ_ALL
#define NVM_READ_ALL                    ((NvM_MultiBlockRequestType)0x00U)
#endif /* NVM_READ_ALL */
#ifndef NVM_WRITE_ALL
#define NVM_WRITE_ALL                   ((NvM_MultiBlockRequestType)0x01U)
#endif /* NVM_WRITE_ALL */
#ifndef NVM_VALIDATE_ALL
#define NVM_VALIDATE_ALL                ((NvM_MultiBlockRequestType)0x02U)
#endif /* NVM_VALIDATE_ALL */
#ifndef NVM_FIRST_INIT_ALL
#define NVM_FIRST_INIT_ALL              ((NvM_MultiBlockRequestType)0x03U)
#endif /* NVM_FIRST_INIT_ALL */
#ifndef NVM_CANCEL_WRITE_ALL
#define NVM_CANCEL_WRITE_ALL            ((NvM_MultiBlockRequestType)0x04U)
#endif /* NVM_CANCEL_WRITE_ALL */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef uint8 NvM_BlockCrcTypeType;             /* ECUC_NvM_00476 */
typedef uint8 NvM_BlockManagementTypeType;      /* ECUC_NvM_00062 */
typedef uint8 NvM_RamBlockTypeType;
typedef uint16 NvM_BlockFlagsType;

typedef P2FUNC ( Std_ReturnType, NVM_CODE, NvM_SingleBlockCallbackType )        ( NvM_BlockRequestType BlockRequest, NvM_RequestResultType JobResult );
typedef P2FUNC ( void,           NVM_CODE, NvM_MultiBlockCallbackType )         ( NvM_MultiBlockRequestType MultiBlockRequest, NvM_RequestResultType JobResult );
typedef P2FUNC ( Std_ReturnType, NVM_CODE, NvM_InitBlockCallbackType  )         ( void );
typedef P2FUNC ( Std_ReturnType, NVM_CODE, NvM_ReadRamBlockFromNvCallbackType ) ( P2CONST( void, AUTOMATIC, NVM_VAR_NO_INIT ) NvMBuffer );
typedef P2FUNC ( Std_ReturnType, NVM_CODE, NvM_WriteRamBlockToNvCallbackType )  ( P2VAR( void, AUTOMATIC, NVM_VAR_NO_INIT ) NvMBuffer );

typedef P2FUNC ( Std_ReturnType, NVM_CODE, NvM_CommonSingleBlockCallbackType )        ( NvM_BlockRequestType BlockRequest, NvM_BlockIdType BlockId, NvM_RequestResultType JobResult );
typedef P2FUNC ( Std_ReturnType, NVM_CODE, NvM_CommonInitBlockCallbackType  )         ( NvM_BlockIdType BlockId );
typedef P2FUNC ( Std_ReturnType, NVM_CODE, NvM_CommonReadRamBlockFromNvCallbackType ) ( NvM_BlockIdType BlockId, P2CONST( void, AUTOMATIC, NVM_VAR_NO_INIT ) NvMBuffer );
typedef P2FUNC ( Std_ReturnType, NVM_CODE, NvM_CommonWriteRamBlockToNvCallbackType )  ( NvM_BlockIdType BlockId, P2VAR( void, AUTOMATIC, NVM_VAR_NO_INIT ) NvMBuffer );

#endif  /* NVM_TYPES_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  2-0-0          :2021/05/13                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
