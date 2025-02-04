/* Fee_DevCallout.h v1-0-0                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/DEV_CALLOUT/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes        | Caution: Do not change this file by application users.    */
/*              |          This file permits AUBASS developers to change.   */
/****************************************************************************/

#ifndef FEE_DEVCALLOUT_H
#define FEE_DEVCALLOUT_H

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

FUNC( Std_ReturnType, FEE_CODE ) Fee_DevCheckRequestAccept( void );

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

#endif /* FEE_DEVCALLOUT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
