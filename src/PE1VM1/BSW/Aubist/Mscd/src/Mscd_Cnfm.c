/* Mscd_Cnfm.c v2-0-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/CNFM/CODE                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Mscd.h>
#include <Mscd_Common.h>

#include <NvM_Mscd.h>

#include "../inc/Mscd_Cnfm.h"
#include "../inc/Mscd_Msif.h"
#include "../usr/Mscd_Cnfm_UserHook.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Global Variable                                                          */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define MSCD_START_SEC_CODE
#include <Mscd_MemMap.h>

/****************************************************************************/
/* Function Name | Mscd_Cnfm_CheckJobExecHook                               */
/* Description   | Make sure it is okay to start the JOB.                   */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                                                    */
/*               |  E_NOT_OK                                                */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(Std_ReturnType, MSCD_CODE) Mscd_Cnfm_CheckJobExecHook(void)
{
    Std_ReturnType u1Result = E_NOT_OK;
    Std_ReturnType u1Req_result;
    u1Req_result = Mscd_Cnfm_PreJobExecCheckHook();
    if (u1Req_result == (Std_ReturnType)E_OK) {
        u1Result = E_OK;
    }
    return u1Result;
}

/****************************************************************************/
/* Function Name | Mscd_Cnfm_CheckWcWriteHook                               */
/* Description   | Make sure it is okay to write write-check                */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                                                    */
/*               |  E_NOT_OK                                                */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(Std_ReturnType, MSCD_CODE) Mscd_Cnfm_CheckWcWriteHook(void)
{
    Std_ReturnType u1Result = E_NOT_OK;
    Std_ReturnType u1Req_result;

    u1Req_result = Mscd_Cnfm_CheckVoltHook();
    if (u1Req_result == (Std_ReturnType)E_OK) {
        u1Result = E_OK;
    }
    return u1Result;
}
#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
/****************************************************************************/
/* Function Name | Mscd_Cnfm_CheckRestoreHook                               */
/* Description   | Make sure it is okay to restore                          */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                                                    */
/*               |  E_NOT_OK                                                */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(Std_ReturnType, MSCD_CODE) Mscd_Cnfm_CheckRestoreHook( void)
{
    Std_ReturnType u1Return;
    Std_ReturnType u1IsRestorePermissionUser;
    NvM_MultiBlockRequestType u1BlockRequest;

    u1Return = E_NOT_OK;

    u1BlockRequest = Mscd_Msif_GetCurrentMultiBlockRequest();

    if( NVM_READ_ALL != u1BlockRequest )
    {
        u1IsRestorePermissionUser = Mscd_Cnfm_CheckRestoreInReadingHook();
        if( (Std_ReturnType)E_OK == u1IsRestorePermissionUser )
        {
            u1Return = E_OK;
        }
    }

    return( u1Return );
}
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */

/****************************************************************************/
/* Function Name | Mscd_Cnfm_CheckIntentRbld                                */
/* Description   | Make sure it is okay to execute intentional rebuild.     */
/* Preconditions | None                                                     */
/* Parameters    | AreaNo         : Target area of intentional rebuild      */
/* Return Value  | Std_ReturnType                                           */
/*               |  E_OK                                                    */
/*               |  E_NOT_OK                                                */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(Std_ReturnType, MSCD_CODE) Mscd_Cnfm_CheckIntentRbld(uint8 AreaNo)
{
    Std_ReturnType u1Result = E_NOT_OK;
    Std_ReturnType u1Req_result;

    u1Req_result = Mscd_Cnfm_CheckIntentRbldHook(AreaNo);
    if (u1Req_result == (Std_ReturnType)E_OK) {
        u1Result = E_OK;
    }
    return u1Result;
}

#define MSCD_STOP_SEC_CODE
#include <Mscd_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2019/08/20                                              */
/*  2-0-0          :2022/07/15                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
