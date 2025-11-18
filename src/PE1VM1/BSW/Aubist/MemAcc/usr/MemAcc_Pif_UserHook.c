/* MemAcc_Pif_UserHook.c v2-0-0                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MEMACC/PIF/USERHOOK/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "MemAcc_Pif_UserHook.h"

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/

#define MEMACC_START_SEC_CODE
#include <MemAcc_MemMap.h>

/****************************************************************************/
/* Function Name | MemAcc_Pif_InitCheckHook                                 */
/* Description   | Service to check whether to Initialize complete.         */
/*               | by the user.                                             */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Request result                                           */
/*               |  E_OK     : Initialize complete                          */
/*               |  E_NOT_OK : Initialize not complete                      */
/* Notes         | This function is described by the user.                  */
/****************************************************************************/
FUNC( Std_ReturnType, MEMACC_CODE ) 
MemAcc_Pif_InitCheckHook( void )
{
    /* [Manual configuration] Add the necessary description for the user below. */
    return E_OK;
    /* [Manual configuration] Add the necessary description for the user above. */
}

#define MEMACC_STOP_SEC_CODE
#include <MemAcc_MemMap.h>


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  2-0-0          :2025/02/28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
