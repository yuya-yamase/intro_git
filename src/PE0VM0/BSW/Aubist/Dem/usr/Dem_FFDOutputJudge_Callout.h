/* Dem_FFDOutpuJugde_Callout_h(v5-0-0)                                      */
/****************************************************************************/
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/FFDOutpuJugde_Callout/HEADER                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_FFDOUTPUTJUDGE_CALLOUT_H
#define DEM_FFDOUTPUTJUDGE_CALLOUT_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_FFD_OUTPUT_JUDGE_SUPPORT == STD_ON )

#include <Dem/Dem_Common.h>
#include "../cfg/Dem_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8   Dem_FFDOutputJudgeType;                   /* FFDOutputJudge */

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_FFDOUTPUT_NOT_ALLOW              ((Dem_FFDOutputJudgeType)(0x11u))
#define DEM_FFDOUTPUT_ALLOW                  ((Dem_FFDOutputJudgeType)(0x22u))

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

FUNC( Dem_FFDOutputJudgeType, DEM_CODE_CALLOUT ) Dem_GetFFDOutputJudge
(
    VAR( uint16, AUTOMATIC ) DataId
);

#define DEM_STOP_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CONST
#include <Dem_MemMap.h>

#endif  /* ( DEM_FFD_OUTPUT_JUDGE_SUPPORT == STD_ON )    */

#endif  /* DEM_FFDOUTPUTJUDGE_CALLOUT_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-09-28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
