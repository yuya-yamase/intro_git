/* Dem_Control_cmn_local_h(v5-3-0)                                          */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_cmn_local/HEADER                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_CONTROL_CMN_LOCAL_H
#define DEM_CONTROL_CMN_LOCAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

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

/*----------------------------------*/
/*  Dem_Control_AsyncReq            */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_Control_SetEventProcess
( void );
FUNC( void, DEM_CODE ) Dem_Control_InitAsyncReq
( void );
FUNC( boolean, DEM_CODE ) Dem_Control_CheckExecAsyncProcess
( void );


/*----------------------------------*/
/*  Dem_Control_Clear               */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_Control_Clear_ClearDTCInfo
( void );
FUNC( void, DEM_CODE ) Dem_Control_ClearDTCProcess
( void );
FUNC( void, DEM_CODE ) Dem_Control_Clear_RefreshRAM
( void );

/*----------------------------------*/
/*  Dem_Control_OpCycle             */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_Control_InitInfoForOpCycleStart
( void );
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetOpCycleUpdateState
( void );

/*----------------------------------*/
/*  Dem_Control_OpCycle             */
/*----------------------------------*/
FUNC( void, DEM_CODE ) Dem_Control_RestartOpCycleInitProcess
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) IGCycleUpdatedPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) OBDDCYQualifiedPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) WarmUpQualifiedPtr
);
FUNC( void, DEM_CODE ) Dem_Control_RestartOpCycleInitEndProcess
(
    VAR( boolean, AUTOMATIC ) IGCycleUpdated,
    VAR( boolean, AUTOMATIC ) OBDDCYQualified,
    VAR( boolean, AUTOMATIC ) WarmUpQualified
);
FUNC( void, DEM_CODE ) Dem_Control_OpCycle_RefreshRAM
( void );


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif /* DEM_CONTROL_CMN_LOCAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
