/* Dem_Rc_PIDMng_h(v5-5-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/Rc_PIDMng/HEADER                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_RC_PIDMNG_H
#define DEM_RC_PIDMNG_H


/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_PID_SUPPORT == STD_ON )
#include "../cfg/Dem_Cfg.h"
#include "../cfg/Dem_MM_Cfg.h"
#include "../cfg/Dem_NvM_Cfg.h"
#include "../inc/Dem_Mm_MemSync.h"
#include "../usr/Dem_SavedZone_Callout.h"

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

FUNC( void, DEM_CODE ) Dem_PIDMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);
FUNC( void, DEM_CODE ) Dem_PIDMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
);
FUNC( void, DEM_CODE ) Dem_PIDMngC_ClearDataOfPID30
( void );
FUNC( void, DEM_CODE ) Dem_PIDMngC_ReadDataOfPID21
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID21value
);
#if ( DEM_PID_WARMUPCYC_SUPPORT == STD_ON )
FUNC( Dem_u08_PIDByteValueType, DEM_CODE ) Dem_PIDMngC_ReadDataOfPID30
( void );
#endif  /*   ( DEM_PID_WARMUPCYC_SUPPORT == STD_ON )        */
FUNC( void, DEM_CODE ) Dem_PIDMngC_ReadDataOfPID31
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID31value
);
FUNC( void, DEM_CODE ) Dem_PIDMngC_ReadDataOfPID4D
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Dvalue
);
FUNC( void, DEM_CODE ) Dem_PIDMngC_ReadDataOfPID4E
(
    CONSTP2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Evalue
);
FUNC( void, DEM_CODE ) Dem_PIDMngC_SetDataOfPID21
(
    CONSTP2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID21value
);
FUNC( void, DEM_CODE ) Dem_PIDMngC_SetDataOfPID31
(
    CONSTP2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID31value
);
FUNC( void, DEM_CODE ) Dem_PIDMngC_SetDataOfPID4D
(
    CONSTP2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Dvalue
);
FUNC( void, DEM_CODE ) Dem_PIDMngC_SetDataOfPID4E
(
    CONSTP2CONST( uint8, AUTOMATIC, DEM_APPL_DATA ) PID4Evalue
);
#if ( DEM_PID_WARMUPCYC_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_PIDMngC_UpdateDataOfPID30
( void );
#endif  /*   ( DEM_PID_WARMUPCYC_SUPPORT == STD_ON )        */

#if ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_PIDMngC_ClearDataOfPID21
( void );
FUNC( void, DEM_CODE ) Dem_PIDMngC_ClearDataOfPID31
( void );
FUNC( void, DEM_CODE ) Dem_PIDMngC_ClearDataOfPID4D
( void );
FUNC( void, DEM_CODE ) Dem_PIDMngC_ClearDataOfPID4E
( void );
#endif  /* ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )    */


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_PidMng_DeployPIDRecordToMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PIDMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex
);

#if ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )
FUNC( void, DEM_CODE ) Dem_PIDMng_InitCalcTargetPIDRecord
( void );

FUNC( void, DEM_CODE ) Dem_PIDMngC_ClearDataOfPIDCalcTarget
( void );
#endif  /*   ( DEM_PID_CALC_DEMINTERNALPID_SUPPORT == STD_ON )       */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/*------------------------------*/
/*  get record data             */
/*------------------------------*/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PIDMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
extern VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_PidMng_NvMWriteStatus;
extern VAR( Dem_PIDRecordType, DEM_VAR_NO_INIT ) Dem_PIDRecordTmp;
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#endif  /* ( DEM_PID_SUPPORT == STD_ON )    */

#endif /* DEM_PIDMNG_OBD_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

