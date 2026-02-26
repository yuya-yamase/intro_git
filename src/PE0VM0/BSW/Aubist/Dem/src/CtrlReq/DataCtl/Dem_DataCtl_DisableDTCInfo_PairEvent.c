/* Dem_DataCtl_DisableDTCInfo_PairEvent_c(v5-5-0)                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_DisableDTCInfo/CODE                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_Misfire.h"

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )

#include "Dem_DataCtl_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/\

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

/****************************************************************************/
/* Saved temporary area of update prohibition record                        */
/****************************************************************************/
static VAR( Dem_TmpDisabledRecordType, DEM_VAR_NO_INIT ) Dem_TmpDisabledRecordPairEvent;


#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DataCtl_SaveTmpDisabledRecordPairEvent               */
/* Description   | Saves pair event info to temporary area.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex                                      */
/* Return Value  | boolean                                                  */
/*               |          TRUE    :   exist record data.                  */
/*               |          FALSE   :   not exist record data.              */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_DataCtl_SaveTmpDisabledRecordPairEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) pairEventStrgIndex;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_u08_MisfireKindBitType, DEM_VAR_NO_INIT ) misfireAvailableKind;
    VAR( boolean, AUTOMATIC ) existRecordData;

    /*  initialize RAM.                         */
    Dem_TmpDisabledRecordPairEvent.EventStrgIndex       = DEM_EVENTSTRGINDEX_INVALID;
    existRecordData =   (boolean)FALSE;

    /*  check event available.                  */
    misfireAvailableKind        =   Dem_DataAvl_GetMisfireCylDTCAvailable();

    if (( misfireAvailableKind & DEM_MISFIRE_KINDBIT_BOTH ) == DEM_MISFIRE_KINDBIT_BOTH )
    {
        /*  get pair event.                     */
        (void)Dem_CfgInfoPm_GetMisfirePairEventStrgIndexByStrgIndex( EventStrgIndex, &pairEventStrgIndex ); /* no return check required */

        Dem_TmpDisabledRecordPairEvent.EventStrgIndex           = pairEventStrgIndex;

        /*  get pair event's fault record.      */
        (void)Dem_DataMngC_GetER_FaultIndex( pairEventStrgIndex, &faultIndex );  /* no return check required */         /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */
        if( faultIndex != DEM_FAULTINDEX_INITIAL )
        {
            /*  exist fault record.         */
            (void)Dem_DataMngC_GetFR_FFDIndexListSt( faultIndex, &Dem_TmpDisabledRecordPairEvent.FFDIndexListSt );  /* no return check required */
            existRecordData =   (boolean)TRUE;
        }
    }

    return existRecordData;
}

/****************************************************************************/
/* Function Name | Dem_DataCtl_SaveRecordNumberByPairEvent                  */
/* Description   | Save pair event's FFD .                                  */
/* Preconditions | none                                                     */
/*               | [in/out] NumberOfSaveRecordPtr :                         */
/*               |        Total number of saved record numbers.             */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_Misfire_SaveRecordNumberByCat(v5-3-0).   */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataCtl_SaveRecordNumberByPairEvent
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireCylinderNumber,
    P2VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC, AUTOMATIC ) NumberOfSaveRecordPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) pairEventStrgIndex;

    if ( Dem_TmpDisabledRecordPairEvent.EventStrgIndex != DEM_EVENTSTRGINDEX_INVALID )
    {
        pairEventStrgIndex          =   Dem_TmpDisabledRecordPairEvent.EventStrgIndex;

#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
        Dem_Data_SaveObdRecordNumberByDTC( pairEventStrgIndex, MisfireCylinderNumber, &Dem_TmpDisabledRecordPairEvent.FFDIndexListSt, NumberOfSaveRecordPtr );
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

        Dem_Data_SaveRecordNumberByDTC( pairEventStrgIndex, MisfireCylinderNumber, &Dem_TmpDisabledRecordPairEvent.FFDIndexListSt, NumberOfSaveRecordPtr );

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )   /*  [FuncSw]    */
        Dem_Data_SaveTSFFRecordNumberByDTC( pairEventStrgIndex, MisfireCylinderNumber, &Dem_TmpDisabledRecordPairEvent.FFDIndexListSt, NumberOfSaveRecordPtr );
#endif  /*   ( DEM_TSFF_PM_SUPPORT == STD_ON )         */

    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_DataCtl_ClearDisabledRecordPairEvent                 */
/* Description   | Clears the disabled record of temporary area.            */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Data_ClearDisabledRecord.      */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataCtl_ClearDisabledRecordPairEvent
( void )
{
    Dem_TmpDisabledRecordPairEvent.EventStrgIndex        =   DEM_EVENTSTRGINDEX_INVALID;

    Dem_TmpDisabledRecordPairEvent.UnderClearDTC         =   (boolean)FALSE;
    Dem_TmpDisabledRecordPairEvent.StatusOfDTC           =   DEM_DTCSTATUS_BYTE_DEFAULT;
    Dem_DataMngC_InitFR_FFDIndexListStData( &Dem_TmpDisabledRecordPairEvent.FFDIndexListSt );

    return ;
}


/****************************************************************************/
/* Function Name | Dem_DataCtl_GetEventStrgIndexOfDisabledRecordPairEvent   */
/* Description   | get EventStrgIndex of pair event.                        */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u16_EventStrgIndexType                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Data_GetIsUnderClearDTCOfDisabledRecord.  */
/****************************************************************************/
FUNC( Dem_u16_EventStrgIndexType, DEM_CODE ) Dem_DataCtl_GetEventStrgIndexOfDisabledRecordPairEvent
( void )
{
    /* Stores UDS DTC status byte from the disabled record of temporary area. */

    return Dem_TmpDisabledRecordPairEvent.EventStrgIndex;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DataCtl_GetTmpDisabledRecordObdFFRIndexAtPairEvent   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] FreezeFrameRecordClassIndex :                       */
/*               | [out] FreezeFrameRecordIndexPtr :                        */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataCtl_GetTmpDisabledRecordObdFFRIndexAtPairEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,          /* [PRMCHK:CALLER] */
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordIndexPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) pairEventStrgIndex;

    pairEventStrgIndex      =   Dem_TmpDisabledRecordPairEvent.EventStrgIndex;
    if ( pairEventStrgIndex != DEM_EVENTSTRGINDEX_INVALID )
    {
        if ( EventStrgIndex == pairEventStrgIndex )
        {
            *FreezeFrameRecordIndexPtr  =   Dem_TmpDisabledRecordPairEvent.FFDIndexListSt.ObdRecordNumberIndex[FreezeFrameRecordClassIndex];    /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
        }
    }
    return ;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )     */

/****************************************************************************/
/* Function Name | Dem_DataCtl_GetTmpDisabledRecordFFRIndexAtPairEvent      */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] FreezeFrameRecordClassIndex :                       */
/*               | [out] FreezeFrameRecordIndexPtr :                        */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DataCtl_GetTmpDisabledRecordFFRIndexAtPairEvent
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FreezeFrameRecordClassIndex,          /* [PRMCHK:CALLER] */
    P2VAR( Dem_u08_FFDIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordIndexPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) pairEventStrgIndex;

    pairEventStrgIndex      =   Dem_TmpDisabledRecordPairEvent.EventStrgIndex;
    if ( pairEventStrgIndex != DEM_EVENTSTRGINDEX_INVALID )
    {
        if ( EventStrgIndex == pairEventStrgIndex )
        {
            *FreezeFrameRecordIndexPtr  =   Dem_TmpDisabledRecordPairEvent.FFDIndexListSt.RecordNumberIndex[FreezeFrameRecordClassIndex];   /* [GUDCHK:CALLER]FreezeFrameRecordClassIndex */
        }
    }

    return ;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
