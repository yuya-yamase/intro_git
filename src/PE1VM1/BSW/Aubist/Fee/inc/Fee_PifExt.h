/* Fee_PifExt.h v1-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/PIFEXT/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FEE_PIFEXT_H
#define FEE_PIFEXT_H

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

FUNC( void, FEE_CODE ) Fee_PifExt_Init( void );

FUNC( void, FEE_CODE ) Fee_PifExt_CancelNotification( void );

FUNC( void, FEE_CODE ) Fee_PifExt_WriteVerifyFailedNotification( void );

FUNC( void, FEE_CODE ) Fee_PifExt_ReadJobSuccessNotification( void );

FUNC( void, FEE_CODE ) Fee_PifExt_WriteJobSuccessNotification( void );

FUNC( void, FEE_CODE ) Fee_PifExt_AcceptedReadJobNotification( uint16 BlockNumber );

FUNC( void, FEE_CODE ) Fee_PifExt_AcceptedWriteJobNotification( uint16 BlockNumber );

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

#endif /* FEE_PIFEXT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
