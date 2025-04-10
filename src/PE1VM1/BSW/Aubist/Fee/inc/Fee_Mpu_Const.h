/* Fee_Mpu_Const.h v2-0-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/MPU/CONST/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        | RH850/U2A16                                               */
/****************************************************************************/

#ifndef FEE_MPU_CONST_H
#define FEE_MPU_CONST_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fls.h>
#include "../inc/Fee_Mpu_Id.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#ifdef FEE_TEST_GENERAL_MACHINE
#define FEE_ENDIAN                          (FEE_ENDIAN_LITTLE)
#else
#define FEE_ENDIAN                          (FEE_ENDIAN_LITTLE)
#endif  /* #ifdef FEE_TEST_GENERAL_MACHINE */

#define FEE_DATA_FLASH_SECTOR_SIZE          ((uint32)FLS_SECTOR_SIZE_000 * (uint32)FEE_PHYSICAL_SECTOR_NUM_PER_VIRTUAL)
#define FEE_DATA_FLASH_SECTOR_NUMBER        (FLS_SECTOR_NUMBER_000 / FEE_PHYSICAL_SECTOR_NUM_PER_VIRTUAL)
#define FEE_DATA_FLASH_ECC_FIX_SIZE         (FEE_BYTE_NUM_04)
#define FEE_DATA_FLASH_PHYS_SECTOR_SIZE     (FLS_SECTOR_SIZE_000)

#define FEE_DATA_FLASH_ADDRESS_START        (FLS_BASE_ADDRESS_000)
#define FEE_DATA_FLASH_ADDRESS_END          (FLS_END_ADDRESS_000)

#define FEE_DATA_FLASH_READ_SIZE            (FEE_DATA_FLASH_ECC_FIX_SIZE)

#define FEE_DATA_FLASH_BLANK_VAL_TYPE       (FEE_DATA_FLASH_BLANK_VAL_TYPE_FF)

/* Timeout value*/
#define FEE_TIMEOUT_PERIODIC_FEE_WRITE      (60000U)
#define FEE_TIMEOUT_PERIODIC_FEE_READ_ID    (60000U)
#define FEE_TIMEOUT_PERIODIC_FEE_REBUILD    (60000U)
#define FEE_TIMEOUT_PERIODIC_FLS_ERASE      (2865U)
#define FEE_TIMEOUT_PERIODIC_FLS_WRITE      (4U)

#define FEE_WC_DIVIDE_WRITE                 (STD_OFF)

#define FEE_FORCE_TRUSTED                   (STD_ON)

#endif /* FEE_MPU_CONST_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/07/03                                              */
/*  2-0-0          :2021/11/12                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
