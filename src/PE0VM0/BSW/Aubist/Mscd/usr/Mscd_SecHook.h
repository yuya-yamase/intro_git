/* Mscd_SecHook.h v1-0-0                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/SECHOOK/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef MSCD_SECHOOK_H
#define MSCD_SECHOOK_H

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define MSCD_START_SEC_CODE_CALLOUT
#include <Mscd_MemMap.h>

#if( MSCD_FRM_USE == STD_ON )
FUNC(void, MSCD_CALLOUT_CODE) Mscd_Frm_SuspendFlashAccessHook( uint8 u1SuspendResult );
#endif /*( MSCD_FRM_USE == STD_ON )*/

#define MSCD_STOP_SEC_CODE_CALLOUT
#include <Mscd_MemMap.h>

#endif /* MSCD_USERHOOK_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
