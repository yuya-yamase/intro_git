/* Dem_FFDOutpuJugde_Callout_c(v5-0-0)                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/FFDOutpuJugde_Callout/CODE                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_FFD_OUTPUT_JUDGE_SUPPORT == STD_ON )

#include "Dem_FFDOutputJudge_Callout.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CODE
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

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_GetFFDOutputJudge                                    */
/* Description   | Returns FFD output judge, not allow or allow, correspon- */
/*               | ding to the specified DataId.                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] DataId :                                            */
/*               |        This parameter specifies the PID (ISO15031-5 map- */
/*               |        ped in UDS range 0xF400 - 0xF4FF) or DID (ISO142- */
/*               |        29-1) that shall be judge to outpu FFD.           */
/*               |                                                          */
/* Return Value  | Dem_FFDOutputJudgeType                                   */
/*               |        DEM_FFDOUTPUT_NOT_ALLOW : FFD output not allow.   */
/*               |        DEM_FFDOUTPUT_ALLOW : FFD output not allow.       */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_FFDOutputJudgeType, DEM_CODE_CALLOUT ) Dem_GetFFDOutputJudge
(
    VAR( uint16, AUTOMATIC ) DataId
)
{
    VAR( Dem_FFDOutputJudgeType, AUTOMATIC ) ffdOutputJudge;

    ffdOutputJudge = DEM_FFDOUTPUT_ALLOW;

    return ffdOutputJudge;
}


#define DEM_STOP_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#endif  /* ( DEM_FFD_OUTPUT_JUDGE_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-09-28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
