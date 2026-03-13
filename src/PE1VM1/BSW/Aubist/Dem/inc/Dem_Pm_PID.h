/* Dem_Pm_PID_h(v5-8-0)                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Pm_PID/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_PM_PID_H
#define DEM_PM_PID_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
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

#if ( DEM_PID_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_PID_Init
( void );
FUNC( void, DEM_CODE ) Dem_PID_Clear
( void );

FUNC( void, DEM_CODE ) Dem_PID_SetEventDisable
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);

#if ( DEM_PID_WARMUPCYC_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_PID_UpdateDataOfPID30
( void );
#endif  /* ( DEM_PID_WARMUPCYC_SUPPORT == STD_ON )  */

FUNC( void, DEM_CODE ) Dem_PID_ReadInitDataOfPID01
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessCaller,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID01value
);
FUNC( void, DEM_CODE ) Dem_PID_ReadInitDataOfPID21
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID21value
);
FUNC( void, DEM_CODE ) Dem_PID_ReadInitDataOfPID30
(
    CONSTP2VAR( uint8, AUTOMATIC, AUTOMATIC ) PID30value
);
FUNC( void, DEM_CODE ) Dem_PID_ReadInitDataOfPID31
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID31value
);
FUNC( void, DEM_CODE ) Dem_PID_ReadInitDataOfPID41
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessCaller,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID41value
);
FUNC( void, DEM_CODE ) Dem_PID_ReadInitDataOfPID4D
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Dvalue
);
FUNC( void, DEM_CODE ) Dem_PID_ReadInitDataOfPID4E
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Evalue
);
FUNC( void, DEM_CODE ) Dem_PID_ReadInitDataOfPIDF501
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessCaller,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PIDF501value
);
FUNC( void, DEM_CODE ) Dem_PID_ReadDataOfPID01AndPIDF501
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessCaller,
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessDataKind,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) ReadinessDataPtr
);
FUNC( void, DEM_CODE ) Dem_PID_ReadDataOfPID1C
(
    CONSTP2VAR( uint8, AUTOMATIC, AUTOMATIC ) PID1Cvalue
);
FUNC( void, DEM_CODE ) Dem_PID_ReadDataOfPID21
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID21value
);
#if ( DEM_PID_WARMUPCYC_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_PID_ReadDataOfPID30
(
    CONSTP2VAR( uint8, AUTOMATIC, AUTOMATIC ) PID30value
);
#endif  /* ( DEM_PID_WARMUPCYC_SUPPORT == STD_ON )      */

FUNC( void, DEM_CODE ) Dem_PID_ReadDataOfPID31
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID31value
);
FUNC( void, DEM_CODE ) Dem_PID_ReadDataOfPID41
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessCaller,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID41value
);
FUNC( void, DEM_CODE ) Dem_PID_ReadDataOfPID4D
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Dvalue
);
FUNC( void, DEM_CODE ) Dem_PID_ReadDataOfPID4E
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Evalue
);
FUNC( void, DEM_CODE ) Dem_PID_SetDataOfPID21
(
    CONSTP2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID21value
);
FUNC( void, DEM_CODE ) Dem_PID_SetDataOfPID31
(
    CONSTP2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID31value
);
FUNC( void, DEM_CODE ) Dem_PID_SetDataOfPID4D
(
    CONSTP2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Dvalue
);
FUNC( void, DEM_CODE ) Dem_PID_SetDataOfPID4E
(
    CONSTP2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Evalue
);
#endif  /* ( DEM_PID_SUPPORT == STD_ON )    */

#if ( DEM_OBDONEDS_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PID_ReadDataOfOBDFreezeFrame
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_PIDNumberType, AUTOMATIC ) PID,
    VAR( Dem_u08_DtElNumPerDIDIndexType, AUTOMATIC ) DataElementIndexOfPID,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBuffer,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSize
);
#endif  /* ( DEM_OBDONEDS_SUPPORT == STD_ON )    */

#if ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_PID_ConfirmedDTCClear
( void );
#endif  /* ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON ) */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>



#endif /* DEM_PM_PID_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

