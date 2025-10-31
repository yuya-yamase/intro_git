/* MemAcc_Mpu_Const.h v2-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MEMACC/MPU/CONST/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        | RH850/U2A                                                 */
/****************************************************************************/

#ifndef MEMACC_MPU_CONST_H
#define MEMACC_MPU_CONST_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fls.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define MEMACC_DEVICE_U2Ax                                           /* Complie switch for U2A */

/* Microcontroller dependent constants for Data Flash */
#define MEMACC_SECTOR_SIZE                     (FLS_SECTOR_SIZE_000)
#define MEMACC_SECTOR_NUMBER                   (FLS_SECTOR_NUMBER_000)
#define MEMACC_WRITE_SIZE                      (FLS_WRITE_UNIT_SIZE_000)
#define MEMACC_READ_SIZE                       (FLS_WRITE_UNIT_SIZE_000)
#define MEMACC_BLANKCHECK_SIZE                 (FLS_WRITE_UNIT_SIZE_000)
#define MEMACC_ERASE_SIZE                      (1UL)                   /* Set 1 in order to invalid the integer multiple check of MemAcc_Erase's argument */

#define MEMACC_DATA_FLASH_ADDRESS_START        (FLS_BASE_ADDRESS_000)
#define MEMACC_DATA_FLASH_ADDRESS_END          ( ( MEMACC_DATA_FLASH_ADDRESS_START + ( MEMACC_SECTOR_SIZE * MEMACC_SECTOR_NUMBER ) ) - 1UL )

#endif /* MEMACC_MPU_CONST_H */



/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2024/08/08                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
