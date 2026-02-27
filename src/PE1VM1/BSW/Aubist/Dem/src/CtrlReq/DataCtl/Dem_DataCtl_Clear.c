/* Dem_DataCtl_Clear_c(v5-6-0)                                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_Clear/CODE                                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_DataCtl_TSFFD.h"
#include "../../../inc/Dem_Pm_Event.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_PreFFD.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Pm_Similar.h"
#include "Dem_DataCtl_local.h"
#include "Dem_DataCtl_TSFFD_local.h"

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
/* Internal Functions                                                       */
/****************************************************************************/
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
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Unit External functions                                                  */
/*--------------------------------------------------------------------------*/

/****************************************************************************/
/* Function Name | Dem_Data_RequestFixedClear                               */
/* Description   | Requests to set completion the status of clear DTC corr- */
/*               | esponding to the event index.                            */
/* Preconditions | Calls this function when all of the non-volatile memory  */
/*               |  clear was completed.                                    */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_RequestFixedClear
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) isFaultOccurring;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultRec;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_FaultRecordType, AUTOMATIC ) faultRecord;
    VAR( Dem_EventMemoryRecordType, AUTOMATIC ) eventMemoryRecord;

    /* Initializes the fault occurrence flag to FALSE. */
    isFaultOccurring = (boolean)FALSE;
    /* Initializes the result of GetFaultRecord value to NG. */
    resultOfGetFaultRec = DEM_IRT_NG;

    /* Gets the event memory record of primary memory. */
    Dem_DataMngC_GetEventMemoryRecord( &eventMemoryRecord );
    /* Checks the result of retrieving the event memory record. */

    faultIndex = DEM_FAULTINDEX_INITIAL;

    /* Gets the fault index of the event record corresponding to the specified event index. */
    resultOfGetFaultIndex = Dem_DataMngC_GetER_FaultIndex( EventStrgIndex, &faultIndex );               /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */

    /* Checks the result of retrieving the fault index of the event record. */
    if( resultOfGetFaultIndex == DEM_IRT_OK )
    {
        /* Retrieving the event record was successful. */
        /* Checks whether the fault index is valid. */
        if( faultIndex != DEM_FAULTINDEX_INITIAL )
        {
            /* The fault index is valid. */
            /* Sets the fault occurrence flag to TRUE.  */
            isFaultOccurring = (boolean)TRUE;
            /* Gets the fault record corresponding to the specific fault index. */
            resultOfGetFaultRec = Dem_DataMngC_GetFaultRecord( faultIndex, &faultRecord );
        }
    }

    /* Because this function act in cyclic process, no need to exclude. */
    /* Starts exclusion. */
    SchM_Enter_Dem_EventMemory();

#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )     /*  [FuncSw]    */
    /* Removes pre-stored freeze frame corresponding to the specified event index. */
    /* PrestoreFreezeFrame exclusive section is controlled in this function. */
    Dem_PreFFD_RemovePrestoredFreezeFrame( EventStrgIndex );
#endif  /* ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )              */

    /* Checks the result of retrieving the freeze frame list record. */
    if( resultOfGetFaultRec == DEM_IRT_OK )
    {
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /* [FuncSw] */
        /* Retrieving the freeze frame list record was successful. */
        /* Clears the time-series freeze frame list record indexed by time-series freeze frame list index in the retrieved freeze frame list record, */
        /* after clears time-series freeze frame record(s) corresponding to the time-series freeze frame list record. */
        Dem_Data_ClearTSFFListRecord( &faultRecord );
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON )   */

        /* Clears the freeze frame record(s) indexed by record number index(es) in the retrieved freeze frame list record. */
        Dem_Data_ClearFreezeFrameRecord( &faultRecord, &eventMemoryRecord );

#if ( DEM_OBDFFD_SUPPORT == STD_ON )        /*  [FuncSw]    */
        /* Clears the OBD freeze frame record(s) indexed by record number index(es) in the retrieved freeze frame list record. */
        Dem_Data_ClearObdFreezeFrameRecord( &faultRecord, &eventMemoryRecord );
#endif  /*  ( DEM_OBDFFD_SUPPORT == STD_ON )               */

    }

    /* Checks the result of retrieving the fault index of the event record. */
    if( resultOfGetFaultIndex == DEM_IRT_OK )
    {
        /* Clears the fault record indexed by the fault index in the retrieved event record. */
        (void)Dem_Data_ClearFaultRecord( faultIndex );   /* no return check required */

        /* Clears the event record indexed by the specified event index. */
        /* and initializes the event record corresponding to the same index. */
        Dem_Data_ClearEventRecord( EventStrgIndex );

        /*  clear qualification.                        */
        Dem_Event_ClearQualificationInfo_NotTestedInCycle_InEvtStrg( EventStrgIndex );  /* [UpdRec]AltIUMPR */
    }

    /* Checks whether the fault is occurring in this event.  */
    if( isFaultOccurring == (boolean)TRUE )
    {
        /* Subtracts 1 from number of event memory entries of event memory record. */
        Dem_Data_SubtractOneFromNumOfEventMemoryEntries( &eventMemoryRecord );
    }

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_Similar_ClearSimilarRecord( EventStrgIndex );
#endif  /*   ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )         */

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_Misfire_ClearMisfireInfoOfEvent( EventStrgIndex );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

    /* Finishes exclusion. */
    SchM_Exit_Dem_EventMemory();


    return ;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
