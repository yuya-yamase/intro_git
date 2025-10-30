/* Mscd_Cnfm_UserHook.c v2-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/CNFM/USERHOOK/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Mscd.h>

#include <NvM_Mscd.h>

#include "Mscd_Cnfm_UserHook.h"

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
#define MSCD_START_SEC_CODE_CALLOUT
#include <Mscd_MemMap.h>

/****************************************************************************/
/* Function Name | Mscd_Cnfm_PreJobExecCheckHook                            */
/* Description   | Service to check whether to start the next job           */
/*               | by the user.                                             */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                    : Start job OK                  */
/*               |  E_NOT_OK                : Start job NG                  */
/* Notes         | This function is described by the user.                  */
/****************************************************************************/
FUNC(Std_ReturnType, MSCD_CALLOUT_CODE)
Mscd_Cnfm_PreJobExecCheckHook(void)
{
    /* [Manual configuration] Add the necessary description for the user below. */
    return E_OK;
    /* [Manual configuration] Add the necessary description for the user above. */
}

/****************************************************************************/
/* Function Name | Mscd_Cnfm_CheckVoltHook                                  */
/* Description   | Service to check whether it is a writalbe voltage        */
/*               | by the user.                                             */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                    : Write OK                      */
/*               |  E_NOT_OK                : Write NG                      */
/* Notes         | This function is described by the user.                  */
/****************************************************************************/
FUNC(Std_ReturnType, MSCD_CALLOUT_CODE)
Mscd_Cnfm_CheckVoltHook(void)
{
    /* [Manual configuration] Add the necessary description for the user below. */
    return E_OK;
    /* [Manual configuration] Add the necessary description for the user above. */
}

#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Cnfm_CheckRestoreInReadingHook                      */
/* Description   | Service to check whether to restore during reading       */
/*               | by the user.                                             */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                    : Restore OK                    */
/*               |  E_NOT_OK                : Restore NG                    */
/* Notes         | This function is described by the user.                  */
/****************************************************************************/
FUNC(Std_ReturnType, MSCD_CALLOUT_CODE)
Mscd_Cnfm_CheckRestoreInReadingHook(void)
{
    /* [Manual configuration] Add the necessary description for the user below. */
    return E_OK;
    /* [Manual configuration] Add the necessary description for the user above. */
}
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */

/****************************************************************************/
/* Function Name | Mscd_Cnfm_CheckIntentRbldHook                            */
/* Description   | Service to check whether to execute intentional rebuild  */
/*               | by the user.                                             */
/* Preconditions | None                                                     */
/* Parameters    | AreaNo         : Target area of intentional rebuild      */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                   : Execute intentional rebuild OK */
/*               |  E_NOT_OK               : Execute intentional rebuild NG */
/* Notes         | This function is described by the user.                  */
/****************************************************************************/
FUNC(Std_ReturnType, MSCD_CALLOUT_CODE)
Mscd_Cnfm_CheckIntentRbldHook(uint8 AreaNo)
{
    /* [Manual configuration] Add the necessary description for the user below. */
    return E_OK;
    /* [Manual configuration] Add the necessary description for the user above. */
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#define MSCD_STOP_SEC_CODE_CALLOUT
#include <Mscd_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2019/08/20                                              */
/*  2-0-0          :2022/07/15                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
