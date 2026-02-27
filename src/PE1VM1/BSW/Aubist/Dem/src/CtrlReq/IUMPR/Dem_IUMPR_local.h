/* Dem_IUMPR_local_h(v5-10-0)                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/IUMPR_local/HEADER                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_IUMPR_LOCAL_H
#define DEM_IUMPR_LOCAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_IUMPR_POS0                          ((uint8)0U)
#define DEM_IUMPR_POS1                          ((uint8)1U)
#define DEM_IUMPR_POS2                          ((uint8)2U)
#define DEM_IUMPR_POS3                          ((uint8)3U)
#define DEM_IUMPR_POS4                          ((uint8)4U)
#define DEM_IUMPR_POS5                          ((uint8)5U)
#define DEM_IUMPR_POS6                          ((uint8)6U)
#define DEM_IUMPR_POS7                          ((uint8)7U)
#define DEM_IUMPR_POS8                          ((uint8)8U)

#define DEM_IUMPR_COUNTER_SHIFT                 ((uint8)0x08U)
#define DEM_IUMPR_RATIO_DATA_SIZE               ((uint8)0x04U)

#define DEM_IUMPR_DATA_INITVALUE                ((uint8)0x00U)

#define DEM_IUMPR_COUNTER_MAXVALUE              ((Dem_u16_IUMPRCycleCounterType)0xFFFFU)
#define DEM_IUMPR_COUNTER_HALFVALUE             ((Dem_u16_IUMPRCycleCounterType)0x8000U)
#define DEM_IUMPR_COUNTER_HALFSHIFT             ((uint8)0x01U)
#define DEM_IUMPR_REMAIN_DEVIDED_TWO            ((Dem_u16_IUMPRCycleCounterType)0x0001U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

FUNC( void, DEM_CODE ) Dem_IUMPR_Ratio_GetInfoTypeValue
(
#ifndef DEM_SIT_RANGE_CHECK
#else   /* DEM_SIT_RANGE_CHECK */
    VAR( uint8, AUTOMATIC ) BuffSize,
#endif  /* DEM_SIT_RANGE_CHECK */
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA )        IumprdataPtr,
    VAR( Dem_u08_IUMPRGroupIndexType, AUTOMATIC )   NODIGroupNum
);

#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_IUMPR_Ratio_Init
( void );
FUNC( void, DEM_CODE ) Dem_IUMPR_UpdateRatioCounter
(
    VAR( boolean, AUTOMATIC )              FirstTime,
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  GenDenCondState,
    VAR( boolean, AUTOMATIC )                       GenDenFidPermission,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ProcessCompletePtr
);
#endif  /* ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )    */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_IUMPR_LOCAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
