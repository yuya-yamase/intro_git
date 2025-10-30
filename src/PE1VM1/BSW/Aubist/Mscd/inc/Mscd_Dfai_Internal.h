/* Mscd_Dfai_Internal.h v2-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/DFAI/INTERNAL/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef MSCD_DFAI_INTERNAL_H
#define MSCD_DFAI_INTERNAL_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <Fls.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#if defined FLS_CFG_SECTOR_SIZE
#define MSCD_DFAI_FLASH_SECTOR_SIZE     ( FLS_CFG_SECTOR_SIZE )
#elif defined FLS_SECTOR_SIZE
#define MSCD_DFAI_FLASH_SECTOR_SIZE     ( FLS_SECTOR_SIZE )
#elif defined FLS_SECTOR_SIZE_000
#define MSCD_DFAI_FLASH_SECTOR_SIZE     ( FLS_SECTOR_SIZE_000 )
#else /* FLS_CFG_SECTOR_SIZE, FLS_SECTOR_SIZE, FLS_SECTOR_SIZE_000 */
#error "The flash sector size is not defined."
#endif /* FLS_CFG_SECTOR_SIZE, FLS_SECTOR_SIZE, FLS_SECTOR_SIZE_000 */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define MSCD_START_SEC_CODE
#include <Mscd_MemMap.h>

#if( MSCD_DFAI_USE == STD_ON )

/* adress range check */
FUNC(Std_ReturnType, MSCD_CODE) Mscd_Dfai_CheckAddrRange( uint32 u4Address, uint32 u4Length );

#endif /*( MSCD_DFAI_USE == STD_ON )*/

#define MSCD_STOP_SEC_CODE
#include <Mscd_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/



#endif  /* MSCD_DFAI_INTERNAL_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2019/02/14                                              */
/*  2-0-0          :2021/03/18                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
