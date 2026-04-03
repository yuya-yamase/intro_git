/* Dem_ClrInfoMng_local_h(v5-3-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/ClrInfoMng_local/HEADER                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_CLRINFOMNG_LOCAL_H
#define DEM_CLRINFOMNG_LOCAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../../../cfg/Dem_NvM_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
extern  VAR( volatile Dem_ClrInfoRecordType,    DEM_VAR_NO_INIT ) Dem_ClrInfoRecordVarNoInit;
#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )

FUNC( void, DEM_CODE ) Dem_ClrInfoMng_Init_AfterNvBlockReadComplete_UserDefMem
(
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) ClrInfoNvmReadResult
);
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_ClearRecord_UserDefMem
( void );

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_InitMirrorMemory_UserDefMem
( void );
FUNC( boolean, DEM_CODE ) Dem_ClrInfoMng_StartClearDTC_UserDefMem
(
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_WriteClearIDtoMirror_UserDefMem
( void );
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

FUNC( void, DEM_CODE ) Dem_ClrInfoMng_UpdateClearID_UserDefMem
(
   VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOrigin
);
FUNC( void, DEM_CODE ) Dem_ClrInfoMng_RefreshRAM_UserDefMem
( void );
#endif  /*   ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )        */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_CLRINFOMNG_LOCAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

