/* Dem_UdmDataCtl_EventEntry01Latch_c(v5-9-0)                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl_Dem_DataCtl_EventEntry01Latch/CODE         */
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
#include "Dem_UdmDataCtl_EventEntry_local.h"
#include "../../../inc/Dem_Rc_UdmMng.h"


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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SaveNonObdFreezeFrameRecordToTmp
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
/* Function Name | Dem_UdmData_SaveEventMemoryEntry                         */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NG :                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SaveEventMemoryEntry
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex       /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetEventRec;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFaultRec;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfSaveFFRec;
    VAR( Dem_u08_UdmMemoryInfoTableIndexType, AUTOMATIC ) udmInfoTableIndex;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) userDefinedMemoryNum;

    retVal = DEM_IRT_OK;
    resultOfGetFaultRec = DEM_IRT_NG;

    userDefinedMemoryNum = Dem_UserDefinedMemoryNum;

    Dem_UdmData_InitTmpMemoryWithoutRecord();

    Dem_UdmTmpEventMemoryEntry.UdmEventIndex = UdmEventIndex;

    udmInfoTableIndex = Dem_CfgInfoUdm_GetMemoryDestination( UdmEventIndex );       /* [GUDCHK:CALLER]UdmEventIndex *//* [GUD:RET:IF_GUARDED: UdmEventIndex ]udmInfoTableIndex */
    Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex = Dem_CfgInfoUdm_GetUserDefinedMemoryGroupKindIndexByEventIndex( udmInfoTableIndex, UdmEventIndex );

    if( Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex < userDefinedMemoryNum )   /* [GUD:if]Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex */
    {
        resultOfGetEventRec = Dem_UdmEventMngC_GetRecord( UdmEventIndex, &Dem_UdmTmpEventMemoryEntry.EventRecord ); /* [GUD:RET:DEM_IRT_OK]Dem_UdmTmpEventMemoryEntry.EventRecord */

        if( resultOfGetEventRec == DEM_IRT_OK )
        {
            if( Dem_UdmTmpEventMemoryEntry.EventRecord.UdmFaultIndex != DEM_UDMFAULTINDEX_INITIAL )
            {
                resultOfGetFaultRec = Dem_UdmFaultMngC_GetRecord( Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex, Dem_UdmTmpEventMemoryEntry.EventRecord.UdmFaultIndex, &Dem_UdmTmpEventMemoryEntry.FaultRecord );/* [GUD]Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex */

                if( resultOfGetFaultRec != DEM_IRT_OK )
                {
                    retVal = DEM_IRT_NG;
                }
                else
                {
                    /* no processing. */
                }
            }
            else
            {
                Dem_UdmFaultMng_InitCtlRecordData( &Dem_UdmTmpEventMemoryEntry.FaultRecord );
            }
        }
        else
        {
            retVal = DEM_IRT_NG;
        }
    }
    else
    {
        retVal = DEM_IRT_NG;
    }

    if( resultOfGetFaultRec == DEM_IRT_OK )
    {
        resultOfSaveFFRec = Dem_UdmData_SaveNonObdFreezeFrameRecordToTmp();

        if( resultOfSaveFFRec != DEM_IRT_OK )
        {
            retVal = DEM_IRT_NG;
        }
        else
        {
            /* no processing. */
        }
    }
    else
    {
        /* no processing. */
    }

    if( retVal == DEM_IRT_OK )
    {
        Dem_UdmEventMngC_GetEventMemoryRecord( Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex, &Dem_UdmTmpEventMemoryEntry.EventMemoryRecord );

        /* Saves the number of event memory entries before being updated. */
        Dem_UdmTmpEventMemoryEntry.BeforeNumberOfEventMemoryEntries = Dem_UdmTmpEventMemoryEntry.EventMemoryRecord.NumberOfEventMemoryEntries;
    }
    else
    {
        /* no processing. */
    }

    return retVal;
}



/****************************************************************************/
/* Function Name | Dem_UdmData_SaveNonObdFreezeFrameRecordToTmp             */
/* Description   |                                                          */
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
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_SaveNonObdFreezeFrameRecordToTmp
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetNextFFInfo;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetFFRec;
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) udmGroupKindIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) startFreezeFrameRecordIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) maxNumberFreezeFrameRecords;
    VAR( Dem_UdmNextFreezeFrameType, AUTOMATIC ) udmNextFreezeFrameInfo;

    retVal = DEM_IRT_NG;

    startFreezeFrameRecordIndex = Dem_UdmTmpEventMemoryEntry.FaultRecord.RecordNumberIndex;
    if( startFreezeFrameRecordIndex != DEM_UDMFFRECINDEX_INITIAL )
    {
        udmGroupKindIndex = Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex;
        maxNumberFreezeFrameRecords = Dem_CfgInfoUdm_GetMaxNumberFreezeFrameRecords( Dem_UdmTmpEventMemoryEntry.UdmEventIndex );

        udmNextFreezeFrameInfo.FreezeFrameRecordIndex = DEM_UDMFFRECINDEX_INITIAL;
        udmNextFreezeFrameInfo.OccurrenceOrder = DEM_UDMOCCURRENCEORDER_INITIAL;
        udmNextFreezeFrameInfo.CidUdmFreezeFrameRecords = DEM_CONSISTENCY_INITIAL;

        resultOfGetNextFFInfo = Dem_UdmFFDMng_GetNextFreezeFrameInfo( (boolean)FALSE, udmGroupKindIndex, startFreezeFrameRecordIndex, maxNumberFreezeFrameRecords, &udmNextFreezeFrameInfo );
        if( resultOfGetNextFFInfo == DEM_IRT_OK )
        {
            /* Gets FaultIndex of the specified index for non-OBD FreezeFrameRecord. */
            resultOfGetFFRec = Dem_UdmFFDMng_GetFFR_MngInfo( Dem_UdmTmpEventMemoryEntry.UdmGroupKindIndex, udmNextFreezeFrameInfo.FreezeFrameRecordIndex, &Dem_UdmTmpEventMemoryEntry.FreezeFrameRecord );
            if( resultOfGetFFRec == DEM_IRT_OK )
            {
                Dem_UdmTmpEventMemoryEntry.OldestFreezeFrameRecordIndex = udmNextFreezeFrameInfo.FreezeFrameRecordIndex;
                Dem_UdmTmpEventMemoryEntry.FreezeFrameRecord.OccurrenceOrder = udmNextFreezeFrameInfo.OccurrenceOrder;
                Dem_UdmTmpEventMemoryEntry.FreezeFrameRecord.CidUdmFreezeFrameRecords = udmNextFreezeFrameInfo.CidUdmFreezeFrameRecords;

                retVal = DEM_IRT_OK;
            }
        }
    }
    else
    {
        retVal = DEM_IRT_OK;
    }

    return retVal;

}



#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
