/* Dem_UdmDataCtl_EventEntry02Clear_c(v5-9-0)                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl_EventEntry02Clear/CODE                     */
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
#include "../../../inc/Dem_CmnLib_DTC_DTCStatus.h"
#include "../../../inc/Dem_Rc_UdmMng.h"
#include "../../../cfg/Dem_UserDefMem_Cfg.h"
#include "Dem_UdmDataCtl_local.h"
#include "Dem_UdmDataCtl_EventEntry_local.h"

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
/* Function Name | Dem_UdmData_ClearUdmEventRecord                          */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventIndex :                                        */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_ClearEventRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex
)
{
    VAR( Dem_UdmEventRecordForCtlType, AUTOMATIC ) udmEventRecord;


    Dem_UdmEventMngC_InitRecord( &udmEventRecord );

    (void)Dem_UdmEventMngC_SetEventRecord( UdmEventIndex, &udmEventRecord );    /* no return check required */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_UdmData_ClearFaultRecord                             */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex                                   */
/*               | [in] FaultIndex :                                        */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_ClearFaultRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u08_UdmFaultIndexType, AUTOMATIC ) UdmFaultIndex
)
{
    if( UdmFaultIndex != DEM_UDMFAULTINDEX_INITIAL )
    {
        (void)Dem_UdmFaultMngC_ClearFaultRecord( UdmGroupKindIndex, UdmFaultIndex ); /* no return check required */
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_ClearFreezeFrameRecord                       */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               | [in] UdmEventIndex :                                     */
/*               | [in] UdmFaultRecordPtr :                                 */
/*               | [in/out] UdmEventMemoryRecordPtr :                       */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_ClearFreezeFrameRecord
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    P2CONST( Dem_UdmFaultRecordType, AUTOMATIC, AUTOMATIC ) UdmFaultRecordPtr,
    P2VAR( Dem_UdmEventMemoryRecordType, AUTOMATIC, AUTOMATIC ) UdmEventMemoryRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfSetFFRec;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) startUdmFreezeFrameRecordIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFFRIndexLimit;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) udmFreezeFrameRecordIndex;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) maxNumberFreezeFrameRecords;

    /* Initializes the return value to OK. */
    maxNumberFreezeFrameRecords = Dem_CfgInfoUdm_GetMaxNumberFreezeFrameRecords( UdmEventIndex );

    /* Checks the record number index corresponding to the loop counter of retrieved the freeze frame list.  */
    startUdmFreezeFrameRecordIndex = UdmFaultRecordPtr->RecordNumberIndex;
    if( startUdmFreezeFrameRecordIndex != DEM_UDMFFRECINDEX_INITIAL )
    {
        /* The record number index corresponding to the loop counter is valid. */

       udmFFRIndexLimit = startUdmFreezeFrameRecordIndex + maxNumberFreezeFrameRecords;
       for( udmFreezeFrameRecordIndex = startUdmFreezeFrameRecordIndex; udmFreezeFrameRecordIndex < udmFFRIndexLimit; udmFreezeFrameRecordIndex++ )
       {
            /* Initialize the freeze frame record corresponding to the record number index. */
            resultOfSetFFRec = Dem_UdmFFDMng_ClearStoredRecord( UdmGroupKindIndex, udmFreezeFrameRecordIndex );

            /* Checks the result of set to Dem_DataMng. */
            if( resultOfSetFFRec == DEM_IRT_OK )
            {
                /* The result means succeeded. */

                /* Decrements the number of freeze frame record. */
                if( UdmEventMemoryRecordPtr->NumberOfFreezeFrameRecords > (Dem_u16_UdmFFDIndexType)0U )
                {
                    /* Decrement the number of freeze frame records. */
                    UdmEventMemoryRecordPtr->NumberOfFreezeFrameRecords = UdmEventMemoryRecordPtr->NumberOfFreezeFrameRecords - (Dem_u16_UdmFFDIndexType)1U;
                }
                else
                {
                    /* The number of freeze frame records is 0 or less. */

                    /* no processing. */
                }
            }
        }
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_SubtractOneFromNumOfEventMemoryEntries       */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmGroupKindIndex :                                 */
/*               |        The record index corresponding to the specific    */
/*               |        Dem_UdmEventMemoryRecordList                      */
/*               | [in/out] EventMemoryRecordPtr :                          */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_UdmData_SubtractOneFromNumOfEventMemoryEntries
(
    VAR( Dem_u16_UdmDemMemKindIndexType, AUTOMATIC ) UdmGroupKindIndex,
    P2VAR( Dem_UdmEventMemoryRecordType, AUTOMATIC, AUTOMATIC ) UdmEventMemoryRecordPtr
)
{
    /* Decrements the number of event memory entry because the fault is occurring in this event. */

    if( UdmEventMemoryRecordPtr->NumberOfEventMemoryEntries > (Dem_u08_OrderIndexType)0U )
    {
        /* The number of event memory entries is over 0. */

        /* Decrement the number of event memory entries. */
        UdmEventMemoryRecordPtr->NumberOfEventMemoryEntries--;
    }
    else
    {
        /* The number of event memory entries is 0 or less. */

        /* no processing. */
    }

    /* Sets the event memory record. */
    Dem_UdmEventMngC_SetEventMemoryRecord( UdmGroupKindIndex, UdmEventMemoryRecordPtr );

    return;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )  */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
