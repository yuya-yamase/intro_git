/* Fee_Driver_Internal.h v1-0-0                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/DRIVER/INTERNAL/HEADER                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_DRIVER_INTERNAL_H
#define FEE_DRIVER_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

FUNC( void, FEE_CODE )
Fee_Driver_InitRam( void );

FUNC( void, FEE_CODE )
Fee_Driver_SetFatalError( void );

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#define FEE_START_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

extern VAR( boolean, FEE_VAR_NO_INIT ) Fee_Driver_WaitCancelFlag;

#define FEE_STOP_SEC_VAR_NO_INIT_32
#include <Fee_MemMap.h>

#endif /* FEE_DRIVER_INTERNAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
