/* Dem_Clear_Callout_h(v5-0-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Clear_Callout/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes |                                                                  */
/****************************************************************************/

#ifndef DEM_CLEAR_CALLOUT_H
#define DEM_CLEAR_CALLOUT_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8    Dem_CalloutReturnType;           /* return value of Callout API */
typedef uint8    Dem_ClearDTCCallerType;           /*  ClearDTC Caller type                */

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/*                  Caller Type                                 :   uint8   */
#define DEM_CALLER_TYPE_DCM                         ((Dem_ClearDTCCallerType)0x00u)
#define DEM_CALLER_TYPE_SWC                         ((Dem_ClearDTCCallerType)0x01u)

/*                  Dem_CalloutReturnType                        :   uint8   */
#define DEM_CALLOUT_OK                              ((Dem_CalloutReturnType)(0x00u))
#define DEM_CALLOUT_PENDING                         ((Dem_CalloutReturnType)(0x01u))
#define DEM_CALLOUT_NG                              ((Dem_CalloutReturnType)(0x02u))

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

FUNC( Dem_CalloutReturnType, DEM_CODE_CALLOUT ) Dem_CheckClearCompleted
(
    VAR( Dem_ClearDTCCallerType, AUTOMATIC ) Caller,
    VAR( uint32, AUTOMATIC ) DTCValue,
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
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


#endif /* DEM_CLEAR_CALLOUT_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2021-09-28                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
