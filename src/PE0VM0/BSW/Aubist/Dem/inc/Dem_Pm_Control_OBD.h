/* Dem_Pm_Control_OBD_h(v5-5-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Pm_Control_OBD/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_PM_CONTROL_OBD_H
#define DEM_PM_CONTROL_OBD_H

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
FUNC( void, DEM_CODE ) Dem_Control_ReadDataOfPID01
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessCaller,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID01value
);
FUNC( void, DEM_CODE ) Dem_Control_ReadDataOfPID1C
(
    CONSTP2VAR( uint8, AUTOMATIC, AUTOMATIC ) PID1Cvalue
);
FUNC( void, DEM_CODE ) Dem_Control_ReadDataOfPID21
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID21value
);
FUNC( void, DEM_CODE ) Dem_Control_ReadDataOfPID30
(
    CONSTP2VAR( uint8, AUTOMATIC, AUTOMATIC ) PID30value
);
FUNC( void, DEM_CODE ) Dem_Control_ReadDataOfPID31
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID31value
);
FUNC( void, DEM_CODE ) Dem_Control_ReadDataOfPID41
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessCaller,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID41value
);
FUNC( void, DEM_CODE ) Dem_Control_ReadDataOfPID4D
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Dvalue
);
FUNC( void, DEM_CODE ) Dem_Control_ReadDataOfPID4E
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Evalue
);
FUNC( void, DEM_CODE ) Dem_Control_ReadDataOfPIDF501
(
    VAR( Dem_u08_ReadinessKindType, AUTOMATIC ) ReadinessCaller,
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PIDF501value
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetDataOfPID21
(
    CONSTP2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID21value
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetDataOfPID31
(
    CONSTP2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID31value
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetDataOfPID4D
(
    CONSTP2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Dvalue
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetDataOfPID4E
(
    CONSTP2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Evalue
);
#endif  /* ( DEM_PID_SUPPORT == STD_ON )    */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
#if ( DEM_OBDFFD_DID_SUPPORT == STD_OFF )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetDTCOfOBDFreezeFrame
(
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) FrameNumber,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTC
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ReadDataOfOBDFreezeFrame
(
    VAR( Dem_u08_RequestCallerType, AUTOMATIC ) Caller,
    VAR( Dem_u08_PIDNumberType, AUTOMATIC ) PID,
    VAR( Dem_u08_DtElNumPerDIDIndexType, AUTOMATIC ) DataElementIndexOfPID,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DestBuffer,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) BufSize
);
#endif  /* ( DEM_OBDFFD_DID_SUPPORT == STD_OFF )   */
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

#if ( DEM_PID_READINESS_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetEvtDisable
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId
);
#endif  /* ( DEM_PID_READINESS_SUPPORT == STD_ON )    */

#if ( DEM_PFC_RECORD_SUPPRESSION_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_DisablePFCRecordUpdate
( void );
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_EnablePFCRecordUpdate
( void );
#endif /* ( DEM_PFC_RECORD_SUPPRESSION_SUPPORT == STD_ON ) */

#if ( DEM_PFC_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetPermanentUDSDTC
(
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) PermanentDTCBufferPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) PermanentDTCNumPtr
);
#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetPermanentOBDDTC
(
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) PermanentDTCBufferPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) PermanentDTCNumPtr
);
#endif  /* ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )    */
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetClearPFCCycleQualified
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) PassedCycleQualifiedPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) DrivingConditionQualifiedPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) PFCCycleQualifiedPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_CheckExistPermanentDTCByEventId
(
    VAR( Dem_EventIdType, AUTOMATIC ) EventId,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) IsPermanentDTCPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetEventIdWithPermanentDTC
(
    P2VAR( Dem_EventIdType, AUTOMATIC, DEM_APPL_DATA ) EventIdBufferPtr,
    P2VAR( uint16, AUTOMATIC, AUTOMATIC ) EventIdNumPtr
);


#endif  /* ( DEM_PFC_SUPPORT == STD_ON )    */

/*----------------------------------*/
/*  Dem_Control_AltIUMPR            */
/*----------------------------------*/
#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_ReadDataOfAltIUMPRDenominator
(
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DenominatorPtr
);
#endif  /* ( DEM_ALTIUMPR_SUPPORT == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_PM_CONTROL_OBD_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

