/* Dem_UdmDataCtl_Clear_c(v5-9-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
#include "../../../cfg/Dem_UserDefMem_Cfg.h"
#include "../../../inc/Dem_Rc_UdmMng.h"
#include "../../../inc/Dem_Udm_Data.h"
#include "../../../inc/Dem_Rc_UdmMngTable.h"
#include "Dem_UdmDataCtl_EventEntry_local.h"
#include "Dem_UdmDataCtl_EventEntry_TSFFD_local.h"

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


/****************************************************************************/
/* Function Name | Dem_UdmData_RequestFixedClear                            */
/* Description   | Requests to set completion the status of clear DTC corr- */
/*               | esponding to the event index.                            */
/* Preconditions | Calls this function when all of the non-volatile memory  */
/*               |  clear was completed.                                    */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               | [in] UdmEventIndex :                                     */
/*               |        The event index corresponding to the event ID.    */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_RequestFixedClear
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,     /* [PRMCHK:CALLER] */
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
)
{
    VAR( boolean, AUTOMATIC ) isFaultOccurring;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetUdmFaultIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetUdmFaultRec;
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) udmFaultIndex;
    VAR( Dem_UdmFaultRecordType, AUTOMATIC ) udmFaultRecord;
    VAR( Dem_UdmEventMemoryRecordType, AUTOMATIC ) udmEventMemoryRecord;

    /* Initializes the fault occurrence flag to FALSE. */
    isFaultOccurring = (boolean)FALSE;
    /* Initializes the result of GetFaultRecord value to NG. */
    resultOfGetUdmFaultRec = DEM_IRT_NG;

    /* Gets the event memory record of User Defined Memory. */
    Dem_UdmEventMngC_GetEventMemoryRecord( UdmGroupKindIndex, &udmEventMemoryRecord );
    /* Checks the result of retrieving the event memory record. */

    udmFaultIndex = DEM_UDMFAULTINDEX_INITIAL;

    /* Gets the fault index of the event record corresponding to the specified event index. */
    resultOfGetUdmFaultIndex = Dem_UdmEventMngC_GetER_FaultIndex( UdmEventIndex, &udmFaultIndex );  /* [GUD:RET:DEM_IRT_OK] UdmEventIndex */

    /* Checks the result of retrieving the fault index of the event record. */
    if( resultOfGetUdmFaultIndex == DEM_IRT_OK )
    {
        /* Retrieving the event record was successful. */
        /* Checks whether the fault index is valid. */
        if( udmFaultIndex != DEM_UDMFAULTINDEX_INITIAL )
        {
            /* The fault index is valid. */
            /* Sets the fault occurrence flag to TRUE.  */
            isFaultOccurring = (boolean)TRUE;
            /* Gets the fault record corresponding to the specific fault index. */
            resultOfGetUdmFaultRec = Dem_UdmFaultMngC_GetRecord( UdmGroupKindIndex, udmFaultIndex, &udmFaultRecord );
        }
    }

    /* Because this function act in cyclic process, no need to exclude. */
#ifndef JGXSTACK
    /* Starts exclusion. */
    Dem_UdmExcFncTable[UdmGroupKindIndex].ExclusiveEnterFnc();  /* [GUDCHK:CALLER]UdmGroupKindIndex */
#else   /* JGXSTACK */
    Dem_UdmExcEnterFnc_ForStack();
#endif  /* JGXSTACK */

    /* Checks the result of retrieving the freeze frame list record. */
    if( resultOfGetUdmFaultRec == DEM_IRT_OK )
    {
        /* Clears the freeze frame record(s) indexed by record number index(es) in the retrieved fault record. */
        Dem_UdmData_ClearFreezeFrameRecord( UdmGroupKindIndex, UdmEventIndex, &udmFaultRecord, &udmEventMemoryRecord );

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )  /* [FuncSw]   */
        /* Clears the time series freeze frame records indexed by time series freeze frame list index in the retrieved fault record. */
        Dem_UdmData_ClearTimeSeriesFreezeFrameRecords( UdmGroupKindIndex, UdmEventIndex, &udmFaultRecord );
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */
    }

    /* Checks the result of retrieving the fault index of the event record. */
    if( resultOfGetUdmFaultIndex == DEM_IRT_OK )
    {
        /* Clears the fault record indexed by the fault index in the retrieved event record. */
        Dem_UdmData_ClearFaultRecord( UdmGroupKindIndex, udmFaultIndex );

        /* Clears the event record indexed by the specified event index. */
        /* and initializes the event record corresponding to the same index. */
        Dem_UdmData_ClearEventRecord( UdmEventIndex );

    }

    /* Checks whether the fault is occurring in this event.  */
    if( isFaultOccurring == (boolean)TRUE )
    {
        /* Subtracts 1 from number of event memory entries of event memory record. */
        Dem_UdmData_SubtractOneFromNumOfEventMemoryEntries( UdmGroupKindIndex, &udmEventMemoryRecord );
    }

#ifndef JGXSTACK
    /* Finishes exclusion. */
    Dem_UdmExcFncTable[UdmGroupKindIndex].ExclusiveExitFnc();   /* [GUDCHK:CALLER]UdmGroupKindIndex */
#else   /* JGXSTACK */
    Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */

    return ;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
