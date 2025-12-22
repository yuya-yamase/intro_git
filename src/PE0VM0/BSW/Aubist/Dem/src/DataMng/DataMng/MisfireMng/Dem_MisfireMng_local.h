/* Dem_MisfireMng_local_h(v5-9-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/MisfireMng_local/HEADER                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_MISFIREMNG_LOCAL_H
#define DEM_MISFIREMNG_LOCAL_H


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
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_MisfireMng_DataVerify
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) ClearID,
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) ClrInfoNvmReadResult
);
FUNC( void, DEM_CODE ) Dem_MisfireMng_UpdateFFDInfoByInitRecordNumberIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ConsistencyIdUpdateFlgPtr
);
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_MisfireMng_UpdateObdFFDInfoByInitRecordNumberIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) ObdFreezeFrameRecordIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ConsistencyIdUpdateFlgPtr
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )     */
FUNC( boolean, DEM_CODE ) Dem_MisfireMng_GetFactoryCheckResultOfMisfireRecord
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex
);
FUNC( boolean, DEM_CODE ) Dem_MisfireMng_GetFactoryCheckResultOfMisfireComRecord
( void );
FUNC( boolean, DEM_CODE ) Dem_MisfireMng_CheckClearIdOfMisfireRecord
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) ClearID
);
FUNC( boolean, DEM_CODE ) Dem_MisfireMng_CheckClearIdOfMisfireComRecord
(
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) ClearID
);
FUNC( boolean, DEM_CODE ) Dem_MisfireMng_CheckConsistencyIdOfMisfireRecord
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
);
FUNC( boolean, DEM_CODE ) Dem_MisfireMng_CheckConsistencyIdOfMisfireComRecord
(
    VAR( Dem_EventKindType, AUTOMATIC ) EventKind,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
);

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
#if ( DEM_OBDONUDS_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_MisfireMng_CopyAllObdFFDCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndexDest,
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndexSrc
);
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   */
#endif  /* ( DEM_OBDONUDS_SUPPORT == STD_ON )               */
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )                 */

#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )   */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_MISFIREMNG_LOCAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

