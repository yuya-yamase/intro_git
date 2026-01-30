/* Dem_DataCtl_DisReqUpd_GetFFIdx_c(v5-7-0)                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Dem_DataCtl_DisReqUpd_GetFFIdx/CODE                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#include "../../../inc/Dem_Rc_DataMng.h"
#include "Dem_DataCtl_local.h"

#if ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_OFF )

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

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetDisabledObdRecordNumberIndex                 */
/* Description   | Gets the ObdRecordNumberIndex from FFDIndexListStPtr co- */
/*               | rresponding to the FreezeFrameRecordClassRefIndex.       */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [in] FreezeFrameRecordClassRefIndex :                    */
/*               |        The index to array of FreezeFrameRecordClassRef.  */
/*               | [in] FreezeFrameRecordTrigger :                          */
/*               |        The DemFreezeFrameRecordTrigger.                  */
/*               | [in] FFDIndexListStPtr :                                 */
/*               |        Dem_TmpDisabledRecord.FFDIndexListSt pointer.     */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        The regular EventStrgIndex.                       */
/* Return Value  | Dem_u08_FFDIndexType                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_Data_GetDisabledObdRecordNumberIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassRefIndex,                   /* [PRMCHK:CALLER] */
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,                      /* MISRA DEVIATION */
    P2VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC, DEM_VAR_NO_INIT ) FFDIndexListStPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
)
{
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) freezeFrameIndex;

    freezeFrameIndex = FFDIndexListStPtr->ObdRecordNumberIndex[ FreezeFrameRecordClassRefIndex ];   /* [GUDCHK:CALLER]FreezeFrameRecordClassRefIndex *//* [ARYCHK] DEM_OBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / FreezeFrameRecordClassRefIndex */
    ( *EventStrgIndexPtr ) = EventStrgIndex;

    return freezeFrameIndex;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_Data_GetDisabledRecordNumberIndex                    */
/* Description   | Gets the RecordNumberIndex from FFDIndexListStPtr corre- */
/*               | sponding to the FreezeFrameRecordClassRefIndex.          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [in] FreezeFrameRecordClassRefIndex :                    */
/*               |        The index to array of FreezeFrameRecordClassRef.  */
/*               | [in] FreezeFrameRecordTrigger :                          */
/*               |        The DemFreezeFrameRecordTrigger.                  */
/*               | [in] FFDIndexListStPtr :                                 */
/*               |        Dem_TmpDisabledRecord.FFDIndexListSt pointer.     */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        The regular EventStrgIndex.                       */
/* Return Value  | Dem_u08_FFDIndexType                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_FFDIndexType, DEM_CODE ) Dem_Data_GetDisabledRecordNumberIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassRefIndex,                   /* [PRMCHK:CALLER] */
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,                      /* MISRA DEVIATION */
    P2VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC, DEM_VAR_NO_INIT ) FFDIndexListStPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
)
{
    VAR( Dem_u08_FFDIndexType, AUTOMATIC ) freezeFrameIndex;

    freezeFrameIndex = FFDIndexListStPtr->RecordNumberIndex[ FreezeFrameRecordClassRefIndex ];  /* [GUDCHK:CALLER]FreezeFrameRecordClassRefIndex *//* [ARYCHK] DEM_NONOBD_FFR_CLASS_PER_DTC_MAX_NUM / 1 / FreezeFrameRecordClassRefIndex */
    ( *EventStrgIndexPtr ) = EventStrgIndex;

    return freezeFrameIndex;
}

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetDisabledTimeSeriesFreezeFrameListIndex       */
/* Description   | Gets the TimeSeriesFreezeFrameListIndex from FFDIndexLi- */
/*               | stStPtr corresponding to the FreezeFrameRecordClassRefI- */
/*               | ndex.                                                    */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex                                      */
/*               |        The event ID for retrieving.                      */
/*               | [in] TSFFRecClassRefIndex :                              */
/*               |        The reference index to array of DemTimeSeriesFre- */
/*               |        ezeFrameRecordClassRef of the DemDTCAttribute.    */
/*               | [in] TSFFRecordTrigger :                                 */
/*               |        The DemFreezeFrameRecordTrigger.(for TSFFD)       */
/*               | [in] NumberOfSaveRecordForTriggerFFD :                   */
/*               |        The number of saved Dem_TmpDisabledRecord array   */
/*               |        for trigger FFD.                                  */
/*               | [in] FFDIndexListStPtr :                                 */
/*               |        Dem_TmpDisabledRecord.FFDIndexListSt pointer.     */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        The regular EventStrgIndex.                       */
/* Return Value  | Dem_u16_TSFFListIndexType                                */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u16_TSFFListIndexType, DEM_CODE ) Dem_Data_GetDisabledTimeSeriesFreezeFrameListIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_TSFFListPerDTCIndexType, AUTOMATIC ) TSFFRecClassRefIndex,             /* [PRMCHK:CALLER] */
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) TSFFRecordTrigger,                     /* MISRA DEVIATION */
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) NumberOfSaveRecordForTriggerFFD,  /* MISRA DEVIATION */
    P2VAR( Dem_FaultRecordPartsFFDIndexListStType, AUTOMATIC, DEM_VAR_NO_INIT ) FFDIndexListStPtr,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
)
{
    VAR( Dem_u16_TSFFListIndexType, AUTOMATIC ) tsFFListIndex;

    tsFFListIndex = FFDIndexListStPtr->TimeSeriesFreezeFrameListIndex[ TSFFRecClassRefIndex ];  /* [GUDCHK:CALLER]TSFFRecClassRefIndex *//* [ARYCHK] DEM_TSFF_RECORD_CLASS_NUM_PER_DTC_MAX_NUM / 1 / TSFFRecClassRefIndex */
    ( *EventStrgIndexPtr ) = EventStrgIndex;

    return tsFFListIndex;
}
#endif  /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /*   ( DEM_COMBINEDEVENT_ONRETRIEVAL_SUPPORT == STD_OFF )   */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
