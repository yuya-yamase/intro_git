/* Mscd_ErrorInfo_UserHook.h v2-0-0                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/ERRORINFO/USERHOOK/HEADER                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef MSCD_ERRORINFO_USERHOOK_H
#define MSCD_ERRORINFO_USERHOOK_H

#define MSCD_START_SEC_CODE_CALLOUT
#include <Mscd_MemMap.h>

#if( MSCD_ERRORINFO_USE == STD_ON )

FUNC(Std_ReturnType, MSCD_CALLOUT_CODE) Mscd_ErrorInfo_ErrorFactorHook( P2VAR(Mscd_ErrorInfo_ErrorFactorInfoType, AUTOMATIC, MSCD_VAR_NO_INIT) stErrorFactorInfo );

#endif /*( MSCD_ERRORINFO_USE == STD_ON )*/

#define MSCD_STOP_SEC_CODE_CALLOUT
#include <Mscd_MemMap.h>

#endif /* MSCD_ERRORINFO_USERHOOK_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  2-0-0          :2021/03/29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
