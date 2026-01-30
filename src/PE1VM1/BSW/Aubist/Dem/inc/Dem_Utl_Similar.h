/* Dem_Utl_Similar_h(v5-9-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Utl_Similar/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_UTL_SIMILAR_H
#define DEM_UTL_SIMILAR_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )
#include "../cfg/Dem_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

FUNC( void, DEM_CODE ) Dem_UtlSimilar_CnvBinaryToSimilarConditionArray
(
    P2VAR( Dem_SimilarConditionValueType, AUTOMATIC, AUTOMATIC ) SimilarConditionArrayPtr,
    P2CONST( uint8, AUTOMATIC , DEM_APPL_DATA ) BufferPtr
);

FUNC( void, DEM_CODE ) Dem_UtlSimilar_CnvSimilarConditionArrayToBinary
(
    P2VAR( uint8, AUTOMATIC , DEM_APPL_DATA ) BufferPtr,
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, DEM_APPL_DATA ) SimilarConditionArrayPtr
);

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_UtlSimilar_CopySimilarConditionArray
(
    P2VAR( Dem_SimilarConditionValueType, AUTOMATIC, DEM_APPL_DATA ) DestSimilarConditionArrayPtr,
    P2CONST( Dem_SimilarConditionValueType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) SrcSimilarConditionArrayPtr
);

FUNC( void, DEM_CODE ) Dem_UtlSimilar_SetSimilarConditionArray
(
    P2VAR( Dem_SimilarConditionValueType, AUTOMATIC, DEM_VAR_SAVED_ZONE ) DestSimilarConditionArrayPtr,
    VAR( Dem_SimilarConditionValueType, AUTOMATIC ) Value
);
#endif /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>



#endif  /* ( DEM_SPECIFIC_EVENT_SUPPORT == STD_ON )    */

#endif /* DEM_UTL_SIMILAR_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

