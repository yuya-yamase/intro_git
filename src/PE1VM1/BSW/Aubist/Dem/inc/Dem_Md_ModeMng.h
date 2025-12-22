/* Dem_Md_ModeMng_h(v5-3-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/


/****************************************************************************/
/* Object Name  | Dem/Md_ModeMng/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/

#ifndef DEM_MD_MODEMNG_H
#define DEM_MD_MODEMNG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_MM_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes - PreInit section                                    */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

FUNC( void, DEM_CODE_TRUST ) Dem_ModeMng_PreInit       /*  PreInit section     */
( void );

#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>



FUNC( void, DEM_CODE ) Dem_ModeMng_Init
( void );


FUNC( void, DEM_CODE ) Dem_ModeMng_InitComplete
( void );


FUNC( void, DEM_CODE ) Dem_ModeMng_Shutdown
( void );


FUNC( void, DEM_CODE ) Dem_ModeMng_SetMode
(
    VAR( Dem_ModeType, AUTOMATIC ) Mode
);


FUNC( void, DEM_CODE ) Dem_ModeMng_ClearMode
(
    VAR( Dem_ModeType, AUTOMATIC ) Mode
);


FUNC( Dem_ModeType, DEM_CODE ) Dem_ModeMng_GetMode
( void );

FUNC( void, DEM_CODE ) Dem_ModeMng_RefreshRAM
( void );

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST
#include <Dem_MemMap.h>

#define DEM_STOP_SEC_CONST
#include <Dem_MemMap.h>


#endif /* DEM_MD_MODEMNG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
