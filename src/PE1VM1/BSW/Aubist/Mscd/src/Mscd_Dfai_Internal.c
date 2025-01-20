/* Mscd_Dfai_Internal.c v2-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
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
/* common ユニット */
/****************************************************************************/
/* Function Name | Mscd_Dfai_CheckAddrRange                          */
/*               |                                 （アドレス範囲チェック） */
/* Description   | アドレスの先頭とデータ長がユーザが指定したメモリ領域の   */
/*               | 範囲内かチェック                                         */
/* Preconditions |                                                          */
/* Parameters    | u4Address            : チェックする領域の先頭アドレス    */
/*               | u4Length             : チェックする領域のデータ長        */
/* Return Value  | Std_ReturnType                                           */
/*               |           E_OK     : パラメータ正常                      */
/*               |           E_NOT_OK : パラメータ異常                      */
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

        /* 先頭アドレスがユーザ使用領域の先頭より小さい場合、E_NOT_OKを返す */
        if( u4Address >= u4StartUserAreaAddr )
        {
            /* 先頭アドレスがユーザ使用領域の末尾より大きい場合、E_NOT_OKを返す */
            if( u4Address <= u4EndUserAreaAddr )
            {
                /* 要求アドレスの先頭からユーザが指定した領域の末尾までのサイズを求める */
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
