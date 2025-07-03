/* Dcm_Main_TmrSrv_h(v5-5-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DCM/Main_TmrSrv/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DCM_MAIN_TMRSRV_H
#define DCM_MAIN_TMRSRV_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include "../../Dcm/Main/cfg/Dcm_Main_TmrSrv_Cfg.h"

#include <Dcm.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CODE
#include <Dcm_MemMap.h>
FUNC( void, DCM_CODE ) Dcm_Main_TmrSrv_Init
( void );
FUNC( void, DCM_CODE ) Dcm_Main_TmrSrv_Main
( void );
FUNC( void, DCM_CODE ) Dcm_Main_TmrSrv_StartTimer
(
    const uint8 u1TimerId,
    const uint32 u4TimeoutValue
);
FUNC( void, DCM_CODE ) Dcm_Main_TmrSrv_StopTimer
(
    const uint8 u1TimerId
);

#if( DCM_AUTHENTICATION_USE == STD_ON  )
FUNC( Std_ReturnType, DCM_CODE ) Dcm_Main_TmrSrv_GetTimerState
(
    const uint8 u1TimerId,
    P2VAR( uint8, AUTOMATIC, DCM_APPL_DATA ) ptTmrState
);
#endif /* DCM_AUTHENTICATION_USE == STD_ON */

#define DCM_STOP_SEC_CODE
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_VAR_NO_INIT
#include <Dcm_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DCM_START_SEC_CONST
#include <Dcm_MemMap.h>


#define DCM_STOP_SEC_CONST
#include <Dcm_MemMap.h>

#endif /* DCM_MAIN_TMRSRV_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v3-2-0         :2020-10-28                                              */
/*  v5-5-0         :2023-07-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
