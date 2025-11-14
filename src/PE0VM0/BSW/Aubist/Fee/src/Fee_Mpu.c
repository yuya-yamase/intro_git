/* Fee_Mpu.c v2-0-0                                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/MPU/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        | RH850/U2A16                                               */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>

#include "../inc/Fee_Mpu.h"
#include "../inc/Fee_Mpu_Internal.h"
#include "../inc/Fee_Api.h"
#include "../inc/Fee_Mpu_Regmap.h"

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* Function Name | Fee_Mpu_Init                                             */
/* Description   | Initialize the unit                                      */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) 
Fee_Mpu_Init( void ){

    return;
}

/****************************************************************************/
/* Function Name | Fee_Mpu_FlashAccessCheck                                 */
/*               | (Flash access permission decision)                       */
/* Description   | Determine Flash access                                   */
/* Preconditions |                                                          */
/* Parameters    | None                                                     */
/* Return Value  | uint32 : Flash accessibility status                      */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(uint32, FEE_CODE) 
Fee_Mpu_FlashAccessCheck( void )
{
    return FEE_FLASH_ACCESS_ENABLE;
}

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
