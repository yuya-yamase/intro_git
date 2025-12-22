/* Dem_Misfire_local_h(v5-9-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Misfire_local/HEADER                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_MISFIRE_LOCAL_H
#define DEM_MISFIRE_LOCAL_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../../../cfg/Dem_Cfg.h"
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include "../../../inc/Dem_Rc_MisfireMng.h"

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

FUNC( boolean, DEM_CODE ) Dem_Misfire_JudgeDTCClearTarget
( void );

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
FUNC( void, DEM_CODE ) Dem_Misfire_SetPendingStoreOfEmission
(
    VAR( boolean, AUTOMATIC ) PendingStoreOfEmission
);
FUNC( boolean, DEM_CODE ) Dem_Misfire_GetMILBlinkingStatus_CAT
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) StatusOfDTC
);
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   */

FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit0Cylinder
(
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind
);
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit1Cylinder
(
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind
);
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit2Cylinder
(
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind
);
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit3Cylinder
(
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind
);
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit4Cylinder
(
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind
);
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit5Cylinder
(
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind
);
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetBit7Cylinder
(
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) Bit3Cylinder
);

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( Dem_u16_MisfireStrgIndexType, DEM_CODE ) Dem_Misfire_GetMisfireStrgIndexOfStoredObdFFD
(
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex
);
#endif /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

FUNC( Dem_u16_MisfireStrgIndexType, DEM_CODE ) Dem_Misfire_GetMisfireStrgIndexOfStoredFFD
(
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) MisfireFFDCylIndex
);

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( Dem_u16_MisfireStrgIndexType, DEM_CODE ) Dem_Misfire_JudgeMisfireStrgIndexOfStoredObdFFD
(
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex,
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) MisfireKindOfFFD
);
#endif /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

FUNC( Dem_u16_MisfireStrgIndexType, DEM_CODE ) Dem_Misfire_JudgeMisfireStrgIndexOfStoredFFD
(
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) MisfireFFDCylIndex,
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) MisfireKindOfFFD
);

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_GetOutputObdFFDCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex
);
#endif /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */

#if ( DEM_PFC_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_Misfire_RestoreAccumPermanentCylToTmp
( void );
#endif  /* ( DEM_PFC_SUPPORT == STD_ON )    */

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
FUNC( boolean, DEM_CODE )  Dem_Misfire_CheckWIRBitAtIndicatorBlinking_CAT
(
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) CatStatusOfDTC
);
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )    */

#endif /* DEM_MISFIRE_LOCAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
