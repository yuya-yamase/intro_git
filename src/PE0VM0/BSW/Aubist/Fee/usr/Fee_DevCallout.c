/* Fee_DevCallout.c v1-0-0                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/DEV_CALLOUT/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        | Caution: Do not change this file by application users.    */
/*              |          This file permits AUBASS developers to change.   */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee.h>
#include "Fee_DevCallout.h"

#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Fee_DevCheckRequestAccept                                */
/* Description   | Service to reject a request from other module            */
/*               | to Fee module forcibly.                                  */
/* Preconditions | None                                                     */
/* Parameters    | None                                                     */
/* Return Value  | Std_ReturnType                                           */
/*               |   E_OK         : Fee is not forced to reject a request.  */
/*               |   E_NOT_OK     : Fee is forced to reject a request.      */
/* Notes         | None                                                     */
/****************************************************************************/

FUNC( Std_ReturnType, FEE_CODE ) Fee_DevCheckRequestAccept( void )
{
    return E_OK;
}

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
