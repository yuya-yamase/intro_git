/* Fee_Cust.c v1-1-0                                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/CUST/CODE                                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>
#include <Mscd_Common.h>

#include "../inc/Fee_Common.h"
#include "../inc/Fee_Mpu_Dev_Const.h"

#include "../inc/Fee_Legacy.h"
#include "../inc/Fee_Pif.h"

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* Function Name | Fee_Write_Rsp_Hook                                       */
/* Description   | Data write response Hook                                 */
/* Preconditions | None                                                     */
/* Parameters    | uint8  result     : result of execution                  */
/*               | uint16 data_id    : write DATA-ID                        */
/*               | uint8  No         : Number of write area                 */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_Write_Rsp_Hook(
    uint8   result,
    uint16  data_id,
    uint8   No
){
    Fee_Pif_WriteEndNotification( result );

    return;
}

/****************************************************************************/
/* Function Name | Fee_Read_Rsp_Hook                                        */
/* Description   | Data read response Hook (ID-specified read)              */
/* Preconditions | None                                                     */
/* Parameters    | uint8  result     : ProcessSuccess                       */
/*               | uint16 data _ id  : read DATA-ID                         */
/*               | uint8  No         : number of reading area               */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_Read_Rsp_Hook(
    uint8   result,
    uint16  data_id,
    uint8   No
){
    Fee_Pif_ReadEndNotification( result );
    
    return;
}

/****************************************************************************/
/* Function Name | Fee_Rebuild_Rsp_Hook                                     */
/* Description   | Data reorganization response Hook                        */
/* Preconditions | None                                                     */
/* Parameters    | uint8  result : ProcessSuccess                           */
/*               | uint8  No     : Number of the reorganization area        */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC(void, FEE_CODE) Fee_Rebuild_Rsp_Hook( uint8 result, uint8 No )
{
    Fee_Pif_RebuildEndNotification( result );
    return;
}

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/08/26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
