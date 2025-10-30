/* Mscd_Dfai_Internal.c v2-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/DFAI/INTERNAL/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Mscd.h>
#include <Fee_Ext.h>

#include "../inc/Mscd_Dfai.h"
#include "../inc/Mscd_Dfai_Internal.h"

#include "../cfg/Mscd_Lcfg.h"

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
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define MSCD_START_SEC_CODE
#include <Mscd_MemMap.h>

#if( MSCD_DFAI_USE == STD_ON )
/* common unit */
/****************************************************************************/
/* Function Name | Mscd_Dfai_CheckAddrRange                                 */
/*               |                         (address range check)            */
/* Description   | Check if the beginning of the address and the data length*/
/*               | are within the memory area specified by the user         */
/* Preconditions |                                                          */
/* Parameters    | u4Address    : top address of area to check              */
/*               | u4Length     : data length of area to check              */
/* Return Value  | Std_ReturnType                                           */
/*               |      E_OK        : parameter normal                      */
/*               |      E_NOT_OK    : parameter error                       */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(Std_ReturnType, MSCD_CODE)
Mscd_Dfai_CheckAddrRange( uint32 u4Address, uint32 u4Length )
{
    Std_ReturnType u1Result;
    uint16 u2StartUserAreaSectorNo_temp;
    uint32 u4AddToEndLen;
    uint32 u4StartUserAreaAddr;
    uint32 u4EndUserAreaAddr;
    u1Result = E_NOT_OK;
    
    u2StartUserAreaSectorNo_temp = Mscd_DFAI_u2StartUserAreaSectorNo;
    if( u2StartUserAreaSectorNo_temp != (uint16)MSCD_DFAI_SECTOR_NO_INVALID )
    {
        u4StartUserAreaAddr = ( (uint32)u2StartUserAreaSectorNo_temp * (uint32)MSCD_DFAI_FLASH_SECTOR_SIZE );
        u4EndUserAreaAddr = ( ( ( (uint32)u2StartUserAreaSectorNo_temp + (uint32)Mscd_DFAI_u2UserAreaSectorNum ) * (uint32)MSCD_DFAI_FLASH_SECTOR_SIZE ) - (uint32)MSCD_DFAI_1LSB );

        /* Returns E_NOT_OK if start address is less than start of user used space */
        if( u4Address >= u4StartUserAreaAddr )
        {
            /* Returns E_NOT_OK if start address is greater than end of user space */
            if( u4Address <= u4EndUserAreaAddr )
            {
                /* Find the size from the beginning of the request address to the end of the user-specified area */
                u4AddToEndLen = ( u4EndUserAreaAddr - u4Address ) + (uint32)MSCD_DFAI_1LSB;

                if( u4Length <= u4AddToEndLen )
                {
                    u1Result = E_OK;
                }
            }
        }
    }

    return ( u1Result );
}
#endif /*( MSCD_DFAI_USE == STD_ON ) */


#define MSCD_STOP_SEC_CODE
#include <Mscd_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2019/02/14                                              */
/*  2-0-0          :2021/07/29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
