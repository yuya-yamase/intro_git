/* Fee_Mpu_Const.c v1-0-0                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/MPU/CONST/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>

#include "../inc/Fee_Mpu_Const.h"
#include "../inc/Fee_Mpu_Const_Ext.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constant                                                                 */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_CONST_32
#include <Fee_MemMap.h>

/* Block head address */
CONST(AB_83_ConstV uint32, FEE_CONST) Fee_Mpu_Cau4SectorTopAddresse[] = {
    (uint32)( FEE_DATA_FLASH_ADDRESS_START ),                                                      /* Sector000 */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 2U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 1UL  )),        /* Sector001 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 2U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 3U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 2UL  )),        /* Sector002 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 3U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 4U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 3UL  )),        /* Sector003 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 4U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 5U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 4UL  )),        /* Sector004 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 5U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 6U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 5UL )),        /* Sector005 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 6U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 7U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 6UL )),        /* Sector006 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 7U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 8U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 7UL )),        /* Sector007 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 8U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 9U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 8UL )),        /* Sector008 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 9U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 10U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 9UL )),        /* Sector009 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 10U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 11U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 10UL  )),        /* Sector010 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 11U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 12U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 11UL  )),        /* Sector011 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 12U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 13U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 12UL  )),        /* Sector012 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 13U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 14U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 13UL  )),        /* Sector013 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 14U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 15U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 14UL  )),        /* Sector014 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 15U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 16U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 15UL  )),        /* Sector015 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 16U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 17U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 16UL  )),        /* Sector016 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 17U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 18U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 17UL  )),        /* Sector017 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 18U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 19U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 18UL  )),        /* Sector018 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 19U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 20U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 19UL  )),        /* Sector019 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 20U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 21U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 20UL  )),        /* Sector020 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 21U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 22U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 21UL  )),        /* Sector021 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 22U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 23U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 22UL  )),        /* Sector022 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 23U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 24U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 23UL  )),        /* Sector023 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 24U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 25U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 24UL  )),        /* Sector024 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 25U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 26U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 25UL  )),        /* Sector025 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 26U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 27U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 26UL  )),        /* Sector026 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 27U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 28U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 27UL  )),        /* Sector027 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 28U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 29U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 28UL  )),        /* Sector028 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 29U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 30U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 29UL  )),        /* Sector029 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 30U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 31U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 30UL  )),        /* Sector030 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 31U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 32U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 31UL  )),        /* Sector031 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 32U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 33U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 32UL  )),        /* Sector032 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 33U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 34U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 33UL  )),        /* Sector033 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 34U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 35U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 34UL  )),        /* Sector034 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 35U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 36U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 35UL  )),        /* Sector035 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 36U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 37U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 36UL  )),        /* Sector036 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 37U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 38U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 37UL  )),        /* Sector037 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 38U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 39U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 38UL  )),        /* Sector038 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 39U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 40U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 39UL  )),        /* Sector039 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 40U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 41U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 40UL  )),        /* Sector040 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 41U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 42U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 41UL  )),        /* Sector041 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 42U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 43U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 42UL  )),        /* Sector042 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 43U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 44U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 43UL  )),        /* Sector043 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 44U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 45U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 44UL  )),        /* Sector044 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 45U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 46U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 45UL  )),        /* Sector045 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 46U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 47U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 46UL  )),        /* Sector046 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 47U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 48U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 47UL  )),        /* Sector047 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 48U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 49U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 48UL  )),        /* Sector048 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 49U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 50U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 49UL  )),        /* Sector049 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 50U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 51U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 50UL  )),        /* Sector050 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 51U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 52U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 51UL  )),        /* Sector051 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 52U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 53U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 52UL  )),        /* Sector052 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 53U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 54U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 53UL  )),        /* Sector053 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 54U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 55U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 54UL  )),        /* Sector054 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 55U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 56U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 55UL  )),        /* Sector055 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 56U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 57U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 56UL  )),        /* Sector056 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 57U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 58U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 57UL  )),        /* Sector057 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 58U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 59U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 58UL  )),        /* Sector058 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 59U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 60U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 59UL  )),        /* Sector059 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 60U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 61U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 60UL  )),        /* Sector060 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 61U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 62U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 61UL  )),        /* Sector061 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 62U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 63U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 62UL  )),        /* Sector062 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 63U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 64U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 63UL  )),        /* Sector063 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 64U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 65U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 64UL  )),        /* Sector064 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 65U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 66U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 65UL  )),        /* Sector065 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 66U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 67U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 66UL  )),        /* Sector066 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 67U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 68U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 67UL  )),        /* Sector067 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 68U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 69U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 68UL  )),        /* Sector068 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 69U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 70U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 69UL  )),        /* Sector069 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 70U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 71U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 70UL  )),        /* Sector070 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 71U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 72U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 71UL  )),        /* Sector071 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 72U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 73U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 72UL  )),        /* Sector072 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 73U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 74U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 73UL  )),        /* Sector073 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 74U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 75U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 74UL  )),        /* Sector074 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 75U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 76U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 75UL  )),        /* Sector075 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 76U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 77U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 76UL  )),        /* Sector076 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 77U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 78U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 77UL  )),        /* Sector077 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 78U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 79U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 78UL  )),        /* Sector078 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 79U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 80U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 79UL  )),        /* Sector079 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 80U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 81U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 80UL  )),        /* Sector080 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 81U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 82U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 81UL  )),        /* Sector081 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 82U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 83U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 82UL  )),        /* Sector082 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 83U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 84U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 83UL  )),        /* Sector083 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 84U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 85U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 84UL  )),        /* Sector084 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 85U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 86U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 85UL  )),        /* Sector085 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 86U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 87U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 86UL  )),        /* Sector086 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 87U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 88U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 87UL  )),        /* Sector087 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 88U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 89U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 88UL  )),        /* Sector088 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 89U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 90U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 89UL  )),        /* Sector089 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 90U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 91U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 90UL  )),        /* Sector090 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 91U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 92U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 91UL  )),        /* Sector091 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 92U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 93U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 92UL  )),        /* Sector092 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 93U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 94U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 93UL  )),        /* Sector093 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 94U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 95U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 94UL  )),        /* Sector094 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 95U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 96U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 95UL  )),        /* Sector095 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 96U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 97U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 96UL  )),        /* Sector096 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 97U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 98U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 97UL  )),        /* Sector097 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 98U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 99U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 98UL  )),        /* Sector098 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 99U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 100U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 99UL  )),        /* Sector099 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 100U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 101U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 100UL  )),        /* Sector100 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 101U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 102U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 101UL  )),        /* Sector101 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 102U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 103U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 102UL  )),        /* Sector102 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 103U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 104U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 103UL  )),        /* Sector103 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 104U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 105U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 104UL  )),        /* Sector104 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 105U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 106U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 105UL  )),        /* Sector105 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 106U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 107U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 106UL  )),        /* Sector106 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 107U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 108U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 107UL  )),        /* Sector107 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 108U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 109U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 108UL  )),        /* Sector108 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 109U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 110U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 109UL  )),        /* Sector109 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 110U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 111U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 110UL  )),        /* Sector110 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 111U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 112U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 111UL  )),        /* Sector111 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 112U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 113U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 112UL  )),        /* Sector112 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 113U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 114U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 113UL  )),        /* Sector113 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 114U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 115U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 114UL  )),        /* Sector114 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 115U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 116U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 115UL  )),        /* Sector115 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 116U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 117U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 116UL  )),        /* Sector116 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 117U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 118U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 117UL  )),        /* Sector117 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 118U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 119U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 118UL  )),        /* Sector118 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 119U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 120U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 119UL  )),        /* Sector119 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 120U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 121U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 120UL  )),        /* Sector120 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 121U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 122U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 121UL  )),        /* Sector121 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 122U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 123U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 122UL  )),        /* Sector122 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 123U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 124U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 123UL  )),        /* Sector123 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 124U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 125U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 124UL  )),        /* Sector124 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 125U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 126U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 125UL  )),        /* Sector125 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 126U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 127U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 126UL  )),        /* Sector126 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 127U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 128U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 127UL  )),        /* Sector127 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 128U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 129U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 128UL  )),        /* Sector128 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 129U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 130U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 129UL  )),        /* Sector129 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 130U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 131U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 130UL  )),        /* Sector130 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 131U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 132U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 131UL  )),        /* Sector131 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 132U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 133U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 132UL  )),        /* Sector132 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 133U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 134U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 133UL  )),        /* Sector133 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 134U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 135U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 134UL  )),        /* Sector134 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 135U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 136U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 135UL  )),        /* Sector135 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 136U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 137U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 136UL  )),        /* Sector136 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 137U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 138U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 137UL  )),        /* Sector137 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 138U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 139U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 138UL  )),        /* Sector138 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 139U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 140U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 139UL  )),        /* Sector139 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 140U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 141U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 140UL  )),        /* Sector140 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 141U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 142U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 141UL  )),        /* Sector141 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 142U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 143U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 142UL  )),        /* Sector142 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 143U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 144U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 143UL  )),        /* Sector143 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 144U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 145U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 144UL  )),        /* Sector144 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 145U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 146U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 145UL  )),        /* Sector145 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 146U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 147U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 146UL  )),        /* Sector146 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 147U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 148U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 147UL  )),        /* Sector147 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 148U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 149U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 148UL  )),        /* Sector148 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 149U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 150U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 149UL  )),        /* Sector149 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 150U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 151U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 150UL  )),        /* Sector150 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 151U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 152U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 151UL  )),        /* Sector151 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 152U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 153U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 152UL  )),        /* Sector152 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 153U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 154U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 153UL  )),        /* Sector153 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 154U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 155U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 154UL  )),        /* Sector154 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 155U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 156U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 155UL  )),        /* Sector155 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 156U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 157U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 156UL  )),        /* Sector156 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 157U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 158U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 157UL  )),        /* Sector157 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 158U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 159U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 158UL  )),        /* Sector158 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 159U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 160U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 159UL  )),        /* Sector159 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 160U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 161U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 160UL  )),        /* Sector160 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 161U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 162U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 161UL  )),        /* Sector161 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 162U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 163U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 162UL  )),        /* Sector162 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 163U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 164U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 163UL  )),        /* Sector163 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 164U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 165U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 164UL  )),        /* Sector164 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 165U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 166U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 165UL  )),        /* Sector165 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 166U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 167U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 166UL  )),        /* Sector166 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 167U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 168U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 167UL  )),        /* Sector167 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 168U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 169U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 168UL  )),        /* Sector168 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 169U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 170U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 169UL  )),        /* Sector169 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 170U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 171U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 170UL  )),        /* Sector170 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 171U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 172U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 171UL  )),        /* Sector171 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 172U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 173U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 172UL  )),        /* Sector172 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 173U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 174U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 173UL  )),        /* Sector173 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 174U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 175U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 174UL  )),        /* Sector174 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 175U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 176U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 175UL  )),        /* Sector175 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 176U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 177U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 176UL  )),        /* Sector176 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 177U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 178U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 177UL  )),        /* Sector177 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 178U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 179U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 178UL  )),        /* Sector178 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 179U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 180U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 179UL  )),        /* Sector179 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 180U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 181U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 180UL  )),        /* Sector180 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 181U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 182U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 181UL  )),        /* Sector181 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 182U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 183U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 182UL  )),        /* Sector182 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 183U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 184U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 183UL  )),        /* Sector183 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 184U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 185U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 184UL  )),        /* Sector184 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 185U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 186U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 185UL  )),        /* Sector185 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 186U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 187U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 186UL  )),        /* Sector186 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 187U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 188U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 187UL  )),        /* Sector187 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 188U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 189U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 188UL  )),        /* Sector188 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 189U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 190U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 189UL  )),        /* Sector189 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 190U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 191U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 190UL  )),        /* Sector190 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 191U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 192U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 191UL  )),        /* Sector191 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 192U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 193U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 192UL  )),        /* Sector192 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 193U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 194U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 193UL  )),        /* Sector193 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 194U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 195U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 194UL  )),        /* Sector194 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 195U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 196U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 195UL  )),        /* Sector195 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 196U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 197U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 196UL  )),        /* Sector196 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 197U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 198U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 197UL  )),        /* Sector197 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 198U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 199U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 198UL  )),        /* Sector198 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 199U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 200U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 199UL  )),        /* Sector199 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 200U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 201U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 200UL  )),        /* Sector200 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 201U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 202U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 201UL  )),        /* Sector201 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 202U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 203U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 202UL  )),        /* Sector202 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 203U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 204U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 203UL  )),        /* Sector203 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 204U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 205U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 204UL  )),        /* Sector204 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 205U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 206U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 205UL  )),        /* Sector205 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 206U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 207U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 206UL  )),        /* Sector206 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 207U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 208U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 207UL  )),        /* Sector207 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 208U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 209U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 208UL  )),        /* Sector208 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 209U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 210U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 209UL  )),        /* Sector209 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 210U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 211U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 210UL  )),        /* Sector210 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 211U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 212U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 211UL  )),        /* Sector211 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 212U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 213U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 212UL  )),        /* Sector212 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 213U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 214U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 213UL  )),        /* Sector213 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 214U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 215U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 214UL  )),        /* Sector214 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 215U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 216U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 215UL  )),        /* Sector215 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 216U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 217U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 216UL  )),        /* Sector216 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 217U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 218U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 217UL  )),        /* Sector217 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 218U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 219U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 218UL  )),        /* Sector218 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 219U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 220U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 219UL  )),        /* Sector219 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 220U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 221U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 220UL  )),        /* Sector220 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 221U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 222U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 221UL  )),        /* Sector221 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 222U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 223U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 222UL  )),        /* Sector222 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 223U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 224U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 223UL  )),        /* Sector223 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 224U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 225U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 224UL  )),        /* Sector224 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 225U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 226U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 225UL  )),        /* Sector225 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 226U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 227U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 226UL  )),        /* Sector226 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 227U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 228U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 227UL  )),        /* Sector227 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 228U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 229U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 228UL  )),        /* Sector228 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 229U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 230U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 229UL  )),        /* Sector229 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 230U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 231U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 230UL  )),        /* Sector230 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 231U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 232U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 231UL  )),        /* Sector231 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 232U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 233U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 232UL  )),        /* Sector232 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 233U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 234U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 233UL  )),        /* Sector233 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 234U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 235U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 234UL  )),        /* Sector234 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 235U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 236U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 235UL  )),        /* Sector235 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 236U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 237U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 236UL  )),        /* Sector236 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 237U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 238U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 237UL  )),        /* Sector237 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 238U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 239U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 238UL  )),        /* Sector238 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 239U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 240U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 239UL  )),        /* Sector239 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 240U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 241U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 240UL  )),        /* Sector240 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 241U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 242U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 241UL  )),        /* Sector241 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 242U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 243U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 242UL  )),        /* Sector242 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 243U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 244U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 243UL  )),        /* Sector243 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 244U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 245U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 244UL  )),        /* Sector244 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 245U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 246U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 245UL  )),        /* Sector245 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 246U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 247U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 246UL  )),        /* Sector246 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 247U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 248U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 247UL  )),        /* Sector247 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 248U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 249U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 248UL  )),        /* Sector248 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 249U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 250U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 249UL  )),        /* Sector249 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 250U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 251U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 250UL  )),        /* Sector250 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 251U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 252U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 251UL  )),        /* Sector251 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 252U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 253U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 252UL  )),        /* Sector252 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 253U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 254U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 253UL  )),        /* Sector253 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 254U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 255U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 254UL  )),        /* Sector254 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 255U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER >= 256U)
    (uint32)( (uint32)FEE_DATA_FLASH_ADDRESS_START + ( (uint32)FEE_DATA_FLASH_SECTOR_SIZE * 255UL  )),        /* Sector255 */
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER >= 256U) */

#if       (FEE_DATA_FLASH_SECTOR_NUMBER > 256U)
#error "The number of sector is over system limitation."
#endif /* (FEE_DATA_FLASH_SECTOR_NUMBER > 256U) */

};

CONST(AB_83_ConstV uint16, FEE_CONST) Fee_Mpu_Cau4SectorTopAddresseSize = sizeof(Fee_Mpu_Cau4SectorTopAddresse) / sizeof(Fee_Mpu_Cau4SectorTopAddresse[0]);

#define FEE_STOP_SEC_CONST_32
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
