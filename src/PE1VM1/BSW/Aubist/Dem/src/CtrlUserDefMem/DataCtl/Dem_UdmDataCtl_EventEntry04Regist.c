/* Dem_UdmDataCtl_EventEntry04Regist_c(v5-9-0)                              */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl_EventEntry04Regist/CODE                    */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../cfg/Dem_UserDefMem_Cfg.h"
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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_StoreEventRecordFromTmp
( void );

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_StoreFaultRecordFromTmp
( void );

static FUNC( void, DEM_CODE ) Dem_UdmData_StoreFreezeFrameRecordFromTmp
( void );

static FUNC( void, DEM_CODE ) Dem_UdmData_StoreEventMemoryRecordFromTmp
( void );


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
/* Function Name | Dem_UdmData_StoreEventOverwitten                         */
/* Description   | Store overwritten Event.                                 */
/* Preconditions | None                                                     */
/* Parameters    | [in]  FaultRecordOverwriteFlag                           */
/*               |              FALSE : overwrite isn't occurred.           */
/*               |              TRUE  : overwrite occurred.                 */
/*               | [in]  UdmEventIndexOverwritten                           */
/*               |              overwritten event.                          */
/*               | [in]  DTCStatusAtOverwritten                             */
/*               |              statusOfDTC of overwritten event.           */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_StoreEventOverwitten
(
    VAR( boolean, AUTOMATIC ) FaultRecordOverwriteFlag,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndexOverwritten,
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) DTCStatusAtOverwritten
)
{
    VAR( Dem_UdmEventRecordForCtlType, AUTOMATIC ) udmEventRecordOverwritten;

    if( FaultRecordOverwriteFlag == (boolean)TRUE )
    {
        (void)Dem_UdmEventMngC_GetRecord( UdmEventIndexOverwritten, &udmEventRecordOverwritten );   /* no return check required */

        udmEventRecordOverwritten.UdmFaultIndex = DEM_UDMFAULTINDEX_INITIAL;
        udmEventRecordOverwritten.StatusOfDTC = DTCStatusAtOverwritten;

#ifndef JGXSTACK
        /* Starts exclusion. */
        Dem_UdmExcFncTable[Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex].ExclusiveEnterFnc();       /* [GUDCHK:SETVAL]Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex */
#else   /* JGXSTACK */
        Dem_UdmExcEnterFnc_ForStack();
#endif  /* JGXSTACK */
        (void)Dem_UdmEventMngC_SetEventRecord( UdmEventIndexOverwritten, &udmEventRecordOverwritten );  /* no return check required */

#ifndef JGXSTACK
        /* Finishes exclusion. */
        Dem_UdmExcFncTable[Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex].ExclusiveExitFnc();        /* [GUDCHK:SETVAL]Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex */
#else   /* JGXSTACK */
        Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_StoreEventMemoryEntryFromTmp                 */
/* Description   | Store the event memory entry from temporary area corres- */
/*               | ponding to the event index of temporary area.            */
/* Parameters    | [in]  TSFFListIndexOverwritten                           */
/*               |              TimeSeriesFreezeFrameListIndex of overwrit- */
/*               |              ten event.                                  */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_StoreEventMemoryEntryFromTmp
(
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) TSFFListIndexOverwritten    /* MISRA DEVIATION */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfStoreEventRec;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfStoreFaultRec;

    /* When the storage of FFD at the first time, FFD other than the first time shall be cleared. */
    if( Dem_UdmTmpEventMemoryEntry.StorageOfFFDAtFirstTimeFlag == (boolean)TRUE )
    {
        Dem_UdmFFDMng_ClearFFDOtherThanTheFirstTime( Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex, Dem_UdmTmpEventMemoryEntry.UdmEventIndex, Dem_UdmTmpEventMemoryEntry.OldestFreezeFrameRecordIndex );
    }

#ifndef JGXSTACK
    /* Starts exclusion. */
    Dem_UdmExcFncTable[Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex].ExclusiveEnterFnc();       /* [GUDCHK:SETVAL]Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex */
#else   /* JGXSTACK */
    Dem_UdmExcEnterFnc_ForStack();
#endif  /* JGXSTACK */

    /* Updates the freeze frame record from temporary area's one. */
    Dem_UdmData_StoreFreezeFrameRecordFromTmp();

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )    /* [FuncSw]   */
    Dem_UdmData_PrepareStoreTSFFRecordFromSample( TSFFListIndexOverwritten );
#endif  /* ( DEM_TSFF_UDM_SUPPORT == STD_ON )           */

    /* Updates the event record from temporary area's one. */
    resultOfStoreEventRec = Dem_UdmData_StoreEventRecordFromTmp();

    /* Checks the result of updating the event record. */
    if( resultOfStoreEventRec == DEM_IRT_OK )
    {
        /* Updating the event record was successful. */

        /* Updates the fault record from temporary area's one. */
        resultOfStoreFaultRec = Dem_UdmData_StoreFaultRecordFromTmp();

        /* Checks the result of updating the fault record. */
        if( resultOfStoreFaultRec == DEM_IRT_OK )
        {
            /* Updating the fault record was successful. */

            /* Updates the event memory record from temporary area's one. */
            Dem_UdmData_StoreEventMemoryRecordFromTmp();

        }
        else
        {
            /* In case that there is no fault (the invalid fault index was given).  */
            /* no processing. */
        }
    }
    else
    {
        /* In case that the invalid event index was given. */
        /* no processing. */
    }

#ifndef JGXSTACK
    /* Finishes exclusion. */
    Dem_UdmExcFncTable[Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex].ExclusiveExitFnc();        /* [GUDCHK:SETVAL]Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex */
#else   /* JGXSTACK */
    Dem_UdmExcExitFnc_ForStack();
#endif  /* JGXSTACK */

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )    /* [FuncSw]   */
    /* Updates the time-series freeze frame record from sampling freeze frame record list. */
    Dem_UdmData_StoreTSFFRecordFromSample( TSFFListIndexOverwritten );
#endif  /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_StoreEventRecordFromTmp                      */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_StoreEventRecordFromTmp
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfSetEventRec;

    retVal = DEM_IRT_NG;

    if( Dem_UdmTmpEventMemoryEntry.ResultOfComparingEventRecords == DEM_IRT_NG )
    {
        /* In the event record, there was difference between RAM and temporary. */

        resultOfSetEventRec = Dem_UdmEventMngC_SetEventRecord( Dem_UdmTmpEventMemoryEntry.UdmEventIndex, &Dem_UdmTmpEventMemoryEntry.EventRecord );

        if( resultOfSetEventRec == DEM_IRT_OK )
        {
            retVal = DEM_IRT_OK;
        }
        else
        {
            /* No Process */
        }
    }
    else
    {
        /* In the fault record, there was no difference between RAM and temporary, so only returns OK. */
        retVal = DEM_IRT_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_StoreFaultRecordFromTmp                      */
/* Description   | Update(Store) the fault record from temporary area.      */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_StoreFaultRecordFromTmp
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfSetFaultRec;

    retVal = DEM_IRT_OK;

    if( Dem_UdmTmpEventMemoryEntry.ResultOfComparingFaultRecords == DEM_IRT_NG )
    {
        /* In the fault record, there was difference between RAM and temporary. */

        resultOfSetFaultRec = Dem_UdmFaultMngC_SetFaultRecord( Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex, Dem_UdmTmpEventMemoryEntry.EventRecord.UdmFaultIndex, &Dem_UdmTmpEventMemoryEntry.FaultRecord );   /* [GUDCHK:SETVAL]Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex */

        if( resultOfSetFaultRec == DEM_IRT_OK )
        {
            /* do nothing. (OrderList is not use) */
        }
        else
        {
            retVal = DEM_IRT_NG;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_StoreFreezeFrameRecordFromTmp                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmData_StoreFreezeFrameRecordFromTmp
( void )
{
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) recordNumberIndex;

    recordNumberIndex = Dem_UdmTmpEventMemoryEntry.OldestFreezeFrameRecordIndex;

    if( recordNumberIndex != DEM_UDMFFRECINDEX_INITIAL )
    {
        if( Dem_UdmTmpEventMemoryEntry.ResultOfComparingFFRecords == DEM_IRT_NG )
        {
            /* In the freeze frame record, there was difference between RAM and temporary. */

            Dem_UdmFFDMng_SetFreezeFrameRecord( Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex, recordNumberIndex, &Dem_UdmTmpEventMemoryEntry.FreezeFrameRecord );
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_StoreEventMemoryRecordFromTmp                */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | uint8                                                    */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_UdmData_StoreEventMemoryRecordFromTmp
( void )
{
    Dem_UdmEventMngC_SetEventMemoryRecord( Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex, &Dem_UdmTmpEventMemoryEntry.EventMemoryRecord );

    return ;
}



#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
