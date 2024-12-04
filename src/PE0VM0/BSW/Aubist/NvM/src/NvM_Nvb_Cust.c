/* NvM_Nvb_Cust.c v2-1-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/NVB/CUST/CODE                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <NvM.h>
#include "../inc/NvM_Internal.h"
#include "../inc/NvM_Nvb.h"
#include "../inc/NvM_Nvb_Cust.h"
#include <Fee.h>
#include <Fee_Ext.h>

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* Function Name | NvM_Nvb_CustExecMainFunction                             */
/* Description   | Function to execute other module's mainfunction.         */
/* Preconditions | None                                                     */
/* Parameters    | CallMode : Call mode of mainfunction.                    */
/* Return Value  | None                                                     */
/* Notes         | None                                                     */
/****************************************************************************/
FUNC( void, NVM_CODE )
NvM_Nvb_CustExecMainFunction(
    uint8 CallMode
){
    if( (uint8)NVM_NVB_CALLMODE_PERIODIC == CallMode )
    {
        Fee_MainFunction();
    }
    else /* NVM_NVB_CALLMODE_NONPERIODIC */
    {
        Fee_MainFunction_ExtNonPeriodic();
    }

    return;
}

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  2-0-0          :2021/09/01                                              */
/*  2-1-0          :2022/07/20                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
