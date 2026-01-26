/* Dem_DataMng_local_h(v5-5-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Dem_DataMng_local_h/HEADER                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_DATAMNG_LOCAL_H
#define DEM_DATAMNG_LOCAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_Rc_DataMng.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )
#define DEM_DATAMNG_CHECKSUM_SHIFT       ( (uint8)0x08U )
#endif  /*  ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )   */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------*/
/*  Dem_DataMng_RecDt_Fault.c           */
/*--------------------------------------*/
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
#if ( DEM_FAULT_RECORD_PADDING_EXIST == STD_ON )
FUNC( void, DEM_CODE ) Dem_DataMng_GetFR_PaddingRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr
);
#endif  /*   ( DEM_FAULT_RECORD_PADDING_EXIST == STD_ON )   */
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */


/*--------------------------------------*/
/*  Dem_DataMng_RecDt_TSFFList.c        */
/*  Dem_DataMng_RecDt_TSFFList_OFF.c    */
/*--------------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_CmpWithTSFFListRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) CheckFaultRecordPtr
);

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_DataMng_InitTSFFListRecordData
(
    P2VAR( Dem_u16_TSFFListIndexType, AUTOMATIC, DEM_VAR_NO_INIT ) TimeSeriesFreezeFrameListIndexArrayPtr
);
FUNC( void, DEM_CODE ) Dem_DataMng_InitTSFFListRecord
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
);
FUNC( void, DEM_CODE ) Dem_DataMng_InitSpecificTSFFListRecordData
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) TSFFListIndex
);
FUNC( void, DEM_CODE ) Dem_DataMng_GetTSFFListRecord_Ctl
(
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( Dem_u16_TSFFListIndexType, AUTOMATIC, DEM_VAR_NO_INIT ) TimeSeriesFreezeFrameListIndexArrayPtr
);
FUNC( void, DEM_CODE ) Dem_TSFFDMng_Verified
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
);
#endif /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */


/*--------------------------------------*/
/*  Dem_DataMng_RecDt_FFD.c             */
/*--------------------------------------*/
FUNC( void, DEM_CODE ) Dem_FFDMng_Verified
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ConsistencyIdUpdateFlgPtr
);


/*--------------------------------------*/
/*  Dem_DataMng_RecDt_OBD_FFD.c         */
/*--------------------------------------*/
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_ObdFFDMng_Verified
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ConsistencyIdUpdateFlgPtr
);
#endif /* ( DEM_OBDFFD_SUPPORT == STD_ON) */

/*--------------------------------------*/
/*  Dem_DataMngVld.c                    */
/*--------------------------------------*/
FUNC( void, DEM_CODE ) Dem_DataMng_Init
( void );
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DataMng_DataVerify
( void );
FUNC( void, DEM_CODE ) Dem_DataMng_VerifyTrigger
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) FaultIndex
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>



#endif  /* DEM_DATAMNG_LOCAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
