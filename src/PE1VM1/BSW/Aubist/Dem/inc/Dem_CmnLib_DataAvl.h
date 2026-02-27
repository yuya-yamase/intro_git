/* Dem_CmnLib_DataAvl_h(v5-5-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/CmnLib_DataAvl/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_CMNLIB_DATAAVL_H
#define DEM_CMNLIB_DATAAVL_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>


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

#if ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON )
FUNC( void, DEM_CODE_TRUST ) Dem_DataAvl_PreInitForAvl       /*  PreInit section     */
( void );

#endif  /* ( DEM_EVENT_AVAILABILITY_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*------------------------------------------*/
/*  PrimaryMemory / UserDefinedMemory       */
/*------------------------------------------*/
FUNC( boolean, DEM_CODE ) Dem_DataAvl_GetEvtAvlCommon
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);

FUNC( boolean, DEM_CODE ) Dem_DataAvl_ValidateDTC
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>



#endif /* DEM_CMNLIB_DATAAVL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
