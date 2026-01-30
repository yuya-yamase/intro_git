/* Dem_IUMPR_NODI_Callout_c(v5-10-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/IUMPR_NODI_Callout/CODE                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_IUMPR_SUPPORT == STD_ON )

#include "Dem_IUMPR_NODI_Callout.h"

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

#if ( DEM_IUMPR_NODI_SELECT_BY_CALLOUT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_IUMPR_SelectNODIValue                                */
/* Description   | Called when requesting IUMPR data.                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] EngineType : Engine type                            */
/*               |        DEM_IGNITION_SPARK                                */
/*               |        DEM_IGNITION_COMPRESSION                          */
/* Return Value  | Dem_u08_IUMPRNODIType                                    */
/*               |        DEM_IUMPRNODI_SPARK_1C                            */
/*               |        DEM_IUMPRNODI_SPARK_14                            */
/*               |        DEM_IUMPRNODI_SPARK_10                            */
/*               |        DEM_IUMPRNODI_COMPRESSION_12                      */
/*               |        DEM_IUMPRNODI_COMPRESSION_10                      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-10-0     | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_IUMPRNODIType, DEM_CODE_CALLOUT ) Dem_IUMPR_SelectNODIValue
(
    VAR( Dem_u08_OBDEngineType, AUTOMATIC )   EngineType
)
{
    return DEM_IUMPRNODI_SPARK_1C;
}
#endif  /* ( DEM_IUMPR_NODI_SELECT_BY_CALLOUT_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_CODE_CALLOUT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
