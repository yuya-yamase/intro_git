/* Mscd_Suspend_UserHook.h v1-0-0                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/SUSPEND/USERHOOK/HEADER                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef MSCD_SUSPEND_USERHOOK_H
#define MSCD_SUSPEND_USERHOOK_H

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define MSCD_START_SEC_CODE_CALLOUT
#include <Mscd_MemMap.h>

#if( MSCD_SUSPEND_USE == STD_ON )

FUNC(Std_ReturnType, MSCD_CALLOUT_CODE) Mscd_Suspend_GetOpeStateHook   ( uint8 u1MemoryIdentifier );

#endif /*( MSCD_SUSPEND_USE == STD_ON )*/

#define MSCD_STOP_SEC_CODE_CALLOUT
#include <Mscd_MemMap.h>

#endif /* MSCD_SUSPEND_USERHOOK_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
