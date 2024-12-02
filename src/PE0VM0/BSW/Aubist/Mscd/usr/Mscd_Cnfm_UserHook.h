/* Mscd_Cnfm_UserHook.h v2-0-0                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | MSCD/CNFM/USERHOOK/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef MSCD_CNFM_USERHOOK_H
#define MSCD_CNFM_USERHOOK_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <NvM_Mscd.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define MSCD_START_SEC_CODE_CALLOUT
#include <Mscd_MemMap.h>

FUNC(Std_ReturnType, MSCD_CALLOUT_CODE) Mscd_Cnfm_PreJobExecCheckHook(void);
FUNC(Std_ReturnType, MSCD_CALLOUT_CODE) Mscd_Cnfm_CheckVoltHook(void);
#if ( NVM_USE_REDUNDANT_BLOCK == STD_ON )
FUNC(Std_ReturnType, MSCD_CALLOUT_CODE) Mscd_Cnfm_CheckRestoreInReadingHook(void);
#endif /* NVM_USE_REDUNDANT_BLOCK == STD_ON */
FUNC(Std_ReturnType, MSCD_CALLOUT_CODE) Mscd_Cnfm_CheckIntentRbldHook(uint8 AreaNo);

#define MSCD_STOP_SEC_CODE_CALLOUT
#include <Mscd_MemMap.h>

#endif /* MSCD_CNFM_USERHOOK_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2019/08/20                                              */
/*  2-0-0          :2022/07/15                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
