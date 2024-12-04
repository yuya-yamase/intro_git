/* NvM_Pif_Internal.h v2-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/PIF/INTERNAL/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_PIF_INTERNAL_H
#define     NVM_PIF_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_VAR_NO_INIT_SHARE
#include <NvM_MemMap.h>

extern VAR( uint32, NVM_VAR_NO_INIT_SHARE ) NvM_Pif_InitFinished;

#define NVM_STOP_SEC_VAR_NO_INIT_SHARE
#include <NvM_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CONST_32
#include <NvM_MemMap.h>

extern CONST( AB_83_ConstV Std_VersionInfoType, NVM_CONST ) NvM_Pif_VersionInfo;

#define NVM_STOP_SEC_CONST_32
#include <NvM_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

FUNC( void, NVM_CODE )
NvM_Pif_Init( void );

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

#endif  /* NVM_PIF_INTERNAL_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  2-0-0          :2021/07/20                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
