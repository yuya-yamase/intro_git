/* Dem_DataCtl_c(v5-9-0)                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl/CODE                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_DataEeo.h"
#include "../../../inc/Dem_Pm_DataOeo.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_Utl.h"
#include "Dem_DataCtl_local.h"
#include "Dem_DataCtl_EventEntry_local.h"

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

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Data_InitForControl                                  */
/* Description   | Init process of Dem_DataCtl unit.                        */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataCtl_Init
( void )
{
    Dem_Data_SetEventMemoryUpdatingStatus( DEM_EVENT_MEMORY_NOT_UPDATING );

    return;
}


/****************************************************************************/
/* Function Name | Dem_DataCtl_Init_AfterRecordCheckComplete                */
/* Description   | Init process of Dem_DataCtl unit.                        */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataCtl_Init_AfterRecordCheckComplete
( void )
{
    /* Initializes the temporary area of event memory entry. */
    Dem_Data_InitTmpEventMemoryEntry();

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /* [FuncSw] */
    Dem_Misfire_InitTmpEventMemoryEntry();
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )     */

#if ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )    /*  [FuncSw]    */
    /* Initialize Dem_DcEeo unit. */
    Dem_DcEeo_Init_AfterRecordCheckComplete();
#endif  /*   ( DEM_EVENT_DISPLACEMENT_SUPPORT == STD_ON )           */

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /* [FuncSw] */
    Dem_Misfire_Init_AfterRecordCheckComplete();
#endif  /*   ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )     */

    return;
}

/****************************************************************************/
/* Function Name | Dem_Data_SetNumOfFaultAndFFD                             */
/* Description   | Count and set the number of Fault and FFD                */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_SetNumOfFaultAndFFD
( void )
{
    VAR( Dem_EventMemoryRecordType, AUTOMATIC ) eventMemoryRecord;

    Dem_DataMngC_InitEvtMemRecData( &eventMemoryRecord );

    eventMemoryRecord.NumberOfEventMemoryEntries = Dem_FaultMng_GetNumOfStoredFault();
    eventMemoryRecord.NumberOfFreezeFrameRecords = Dem_FFDMng_GetNumOfStoredNonObdFFD();
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    eventMemoryRecord.NumberOfObdFreezeFrameRecords = Dem_ObdFFDMng_GetNumOfStoredObdFFD();
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

    Dem_DataMngC_SetEventMemoryRecord( &eventMemoryRecord );

    return;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
