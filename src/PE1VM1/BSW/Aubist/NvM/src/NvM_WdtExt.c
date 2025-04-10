/* NvM_WdtExt.c v1-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/WDTEXT/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <NvM.h>
#include "../inc/NvM_Internal.h"
#include "../inc/NvM_WdtExt.h"
#include "../inc/NvM_WdtExt_Internal.h"
#include "../inc/NvM_WdtExt_Cust.h"

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

VAR( uint32, NVM_VAR_NO_INIT ) NvM_WdtExt_WdtCounter[NVM_WDTEXT_ID_NUM];

#define NVM_STOP_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CONST_32
#include <NvM_MemMap.h>

CONST( AB_83_ConstV uint16, NVM_CONST ) NvM_WdtExt_IdNum = NVM_WDTEXT_ID_NUM;

#define NVM_STOP_SEC_CONST_32
#include <NvM_MemMap.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* Function Name | NvM_WdtExt_Init                                          */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_WdtExt_Init( void )
{
    uint16 Id;
    uint16 WdtExtIdNum = NvM_WdtExt_IdNum;

    for( Id = 0U; Id < WdtExtIdNum; Id++ )
    {
        NvM_WdtExt_WdtCounter[Id] = NVM_WDTEXT_TIMEOUT_COUNT;
    }
    return;
}

/****************************************************************************/
/* Function Name | NvM_WdtExt_MainFunction                                  */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_WdtExt_MainFunction( void )
{
    uint16 Id;
    uint32 Timer;
    uint16 WdtExtIdNum = NvM_WdtExt_IdNum;

    for( Id = 0U; Id < WdtExtIdNum; Id++ )
    {
        Timer =  NvM_WdtExt_WdtCounter[Id];
        
        if( Timer > (uint32)NVM_WDTEXT_TIMEOUT_COUNT )
        {
            Timer--;
            if( Timer == (uint32)NVM_WDTEXT_TIMEOUT_COUNT )
            {
                NvM_WdtExt_TimeoutActionFunc[Id](Id);
            }
            NvM_WdtExt_WdtCounter[Id] = Timer;
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | NvM_WdtExt_WatchDogStart                                 */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | Id: Watch dog timer ID.                                  */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_WdtExt_WatchDogStart(
    NvM_WdtExt_WdtIdType Id,
    uint32 TimeoutValue
){
    NvM_WdtExt_WdtCounter[Id] = TimeoutValue;
    return;
}

/****************************************************************************/
/* Function Name | NvM_WdtExt_WatchDogEnd                                   */
/* Description   |                                                          */
/* Preconditions | None                                                     */
/* Parameters    | Id: Watch dog timer ID.                                  */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_WdtExt_WatchDogEnd(
    NvM_WdtExt_WdtIdType Id
){
    NvM_WdtExt_WdtCounter[Id] = NVM_WDTEXT_TIMEOUT_COUNT;
    return;
}

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
