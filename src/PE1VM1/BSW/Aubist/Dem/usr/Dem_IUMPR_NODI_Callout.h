/* Dem_IUMPR_NODI_Callout_h(v5-10-0)                                        */
/****************************************************************************/
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/IUMPR_NODI_Callout/HEADER                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_IUMPR_NODI_CALLOUT_H
#define DEM_IUMPR_NODI_CALLOUT_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_IUMPR_SUPPORT == STD_ON )
#include <Dem/Dem_Common.h>

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef uint8    Dem_u08_IUMPRNODIType;

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_IUMPRNODI_SPARK_1C          ((Dem_u08_IUMPRNODIType)0x1CU)
#define DEM_IUMPRNODI_SPARK_14          ((Dem_u08_IUMPRNODIType)0x14U)
#define DEM_IUMPRNODI_SPARK_10          ((Dem_u08_IUMPRNODIType)0x10U)
#define DEM_IUMPRNODI_COMPRESSION_12    ((Dem_u08_IUMPRNODIType)0x12U)
#define DEM_IUMPRNODI_COMPRESSION_10    ((Dem_u08_IUMPRNODIType)0x10U)

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

#if ( DEM_IUMPR_NODI_SELECT_BY_CALLOUT_SUPPORT == STD_ON )
FUNC( Dem_u08_IUMPRNODIType, DEM_CODE_CALLOUT ) Dem_IUMPR_SelectNODIValue
(
    VAR( Dem_u08_OBDEngineType, AUTOMATIC )   EngineType
);
#endif /* ( DEM_IUMPR_NODI_SELECT_BY_CALLOUT_SUPPORT == STD_ON ) */

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

#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON ) */

#endif  /* DEM_IUMPR_NODI_CALLOUT_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
