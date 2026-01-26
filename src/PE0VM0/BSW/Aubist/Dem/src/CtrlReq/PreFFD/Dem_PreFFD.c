/* Dem_PreFFD_c(v5-5-0)                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/PreFFD/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )

#include "../../../cfg/Dem_Data_Cfg.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_Pm_PreFFD.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Utl.h"
#include "../../../inc/Dem_Rc_PreFFDMng.h"
#include "../../../inc/Dem_Rc_DataMng.h"
#include "../../../inc/Dem_CmnLib_DataElement.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../usr/Dem_PendingOBDFFD_Callout.h"

#include "Dem_PreFFD_FFDOutputJudge.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef struct
{
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
    boolean ObdPreFFDCaptureFlag;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */
    boolean NonObdPreFFDCaptureFlag;
} Dem_PreFFDCaptureMngType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PreFFD_GetFreezeFrameRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_PreFFDIndexType, AUTOMATIC, AUTOMATIC ) PreFFRecordIndexPtr,
    P2VAR( Dem_PreFFRecordMngType, AUTOMATIC, AUTOMATIC ) PreFFRecordMngPtr
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PreFFD_GetEmptyFreezeFrameRecord
(
    P2VAR( Dem_u08_PreFFDIndexType, AUTOMATIC, AUTOMATIC ) PreFFRecordIndexPtr,
    P2VAR( Dem_PreFFRecordMngType, AUTOMATIC, AUTOMATIC ) PreFFRecordMngPtr
);

static FUNC( void, DEM_CODE ) Dem_PreFFD_CaptureFreezeFrame
(
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) DTCAttributePtr,
    P2CONST( Dem_PreFFDCaptureMngType, AUTOMATIC, AUTOMATIC ) PreFFDCaptureMngPtr,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) PreFFDataPtr
);

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_PreFFD_CaptureObdFreezeFrame
(
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) OBDFreezeFrameClassRef,
    VAR( boolean, AUTOMATIC ) ObdPreFFDCaptureFlag,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) PreFFDataPtr
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

static FUNC( void, DEM_CODE ) Dem_PreFFD_CaptureNonObdFreezeFrame
(
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) FreezeFrameClassRef,
    VAR( boolean, AUTOMATIC ) NonObdPreFFDCaptureFlag,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) PreFFDataPtr
);

static FUNC( void, DEM_CODE ) Dem_PreFFD_CaptureFreezeFrameClass
(
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameClassPtr,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) FreezeFrameDataOffset,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) PreFFDataPtr
);

static FUNC( void, DEM_CODE ) Dem_PreFFD_SetPreFFDCaptureMng
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_PreFFDCaptureMngType, AUTOMATIC, AUTOMATIC ) PreFFDCaptureMngPtr
);

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_PreFFD_SetObdPreFFDCaptureFlag
(
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) DTCAttributePtr,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_PreFFDCaptureMngType, AUTOMATIC, AUTOMATIC ) PreFFDCaptureMngPtr
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

static FUNC( void, DEM_CODE ) Dem_PreFFD_SetNonObdPreFFDCaptureFlag
(
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) DTCAttributePtr,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_PreFFDCaptureMngType, AUTOMATIC, AUTOMATIC ) PreFFDCaptureMngPtr
);

static FUNC( void, DEM_CODE ) Dem_PreFFD_SetPreFFDCaptureFlag
(
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FFRClassPerDTCMaxNum,
    P2CONST( Dem_u08_FFDIndexType, AUTOMATIC, AUTOMATIC ) RecordNumberIndexPtr,
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameRecNumClassPtr,
    VAR( boolean, AUTOMATIC ) ObdFFDFlag,
    P2VAR( boolean, AUTOMATIC, DEM_VAR_NO_INIT ) PreFFDCaptureFlagPtr
);

static FUNC( boolean, DEM_CODE ) Dem_PreFFD_CheckPreFFDCaptureFlag
(
    P2CONST( Dem_PreFFDCaptureMngType, AUTOMATIC, AUTOMATIC ) PreFFDCaptureMngPtr
);

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( boolean, DEM_CODE ) Dem_PreFFD_CheckObdTriggerToRemovePreFFD
(
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) DTCAttributePtr,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) TriggerCondition
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

static FUNC( boolean, DEM_CODE ) Dem_PreFFD_CheckNonObdTriggerToRemovePreFFD
(
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) DTCAttributePtr,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) TriggerCondition
);

static FUNC( boolean, DEM_CODE ) Dem_PreFFD_CheckTriggerCondition
(
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FFRClassPerDTCMaxNum,
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameRecNumClassPtr,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) TriggerCondition
);

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
/* External Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dem_PreFFD_PrestoreFreezeFrame                           */
/* Description   | Pre-stores freeze frame by the specified event index.    */
/* Preconditions |                                                          */
/* Parameters    | [in] EventCtrlIndex :                                    */
/*               |        The index for Dem_EventRecordList.                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |       DEM_IRT_OK : Pre-storing was succeded.             */
/*               |       DEM_IRT_NG : Pre-storing was failed.               */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PreFFD_PrestoreFreezeFrame
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetPreFFRecord;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetEmptyPreFFRecord;
    VAR( boolean, AUTOMATIC ) ffPrestorageSupported;
    VAR( boolean, AUTOMATIC ) chkPreFFDCaptureFlag;
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) preFFRecordIndex;
    VAR( Dem_PreFFRecordMngType, AUTOMATIC ) preFFRecordMng;
    VAR( Dem_PreFFDCaptureMngType, AUTOMATIC ) preFFDCaptureMng;
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0;
    VAR( Dem_EventIdType, AUTOMATIC ) eventId;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) dtcAttributePtr;

    retVal = DEM_IRT_NG;

    ffPrestorageSupported = Dem_CfgInfoPm_GetPreFFSupported_ByEvtCtrlIdx( EventCtrlIndex );
    if( ffPrestorageSupported == (boolean)TRUE )
    {
        /*  get EventStrgIndex          */
        eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );                /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */

        /*  create monitordata0         */
        (void)Dem_CfgInfoPm_CnvEventCtrlIndexToEventId( EventCtrlIndex, &eventId ); /* no return check required */                          /* [GUD:RET:DEM_IRT_OK]EventCtrlIndex */
        monitorData0 =  (Dem_MonitorDataType)eventId;
        monitorData0 |= DEM_MONITORDATA_PREFFD;

        /*  get DTC attribute reference */
        dtcAttributePtr    =   Dem_CfgInfoPm_GetDTCAttrTablePtr_PreFF( eventStrgIndex );    /* [GUD:RET:Not NULL_PTR]dtcAttributePtr *//* [GUD:RET:Not NULL_PTR]eventStrgIndex */
        if ( dtcAttributePtr != NULL_PTR )                                                  /* [GUD:if]dtcAttributePtr */
        {
            preFFRecordIndex = DEM_PREFFD_INDEX_INVALID;
            Dem_PreFFDMng_InitFreezeFrameRecord( &preFFRecordMng );

#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
            preFFDCaptureMng.ObdPreFFDCaptureFlag       =   (boolean)FALSE;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */
            preFFDCaptureMng.NonObdPreFFDCaptureFlag    =   (boolean)FALSE;

            /* Waits to finish the exclusive section in the DemMainFunction context. */
            SchM_Enter_Dem_PrestoreFreezeFrame();
            SchM_Exit_Dem_PrestoreFreezeFrame();

            resultOfGetPreFFRecord = Dem_PreFFD_GetFreezeFrameRecord( eventStrgIndex, &preFFRecordIndex, &preFFRecordMng );
            if( resultOfGetPreFFRecord == DEM_IRT_OK )
            {
                /* Found out the pre-stored freeze frame record corresponding to the specified event index. */

                /* Sets preFFD capture flags for OBD and non-OBD. */
                Dem_PreFFD_SetPreFFDCaptureMng( eventStrgIndex, &preFFDCaptureMng );

                /* Updates the pre-stored freeze frame record. */
                Dem_PreFFD_CaptureFreezeFrame( dtcAttributePtr, &preFFDCaptureMng, monitorData0, preFFRecordMng.DataPtr );  /* [GUD]dtcAttributePtr */

#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )
                Dem_PreFFDMng_SetChecksum( preFFRecordIndex );
#endif  /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON) */

                chkPreFFDCaptureFlag = Dem_PreFFD_CheckPreFFDCaptureFlag( &preFFDCaptureMng );
                if( chkPreFFDCaptureFlag == (boolean)TRUE )
                {
                    Dem_PreFFDMng_SetUpdateRequest( preFFRecordIndex );
                }

                retVal = DEM_IRT_OK;
            }
            else
            {
                /* Did not find out the pre-stored freeze frame record corresponding to the specified event index. */

                preFFRecordIndex = DEM_PREFFD_INDEX_INVALID;
                Dem_PreFFDMng_InitFreezeFrameRecord( &preFFRecordMng );

                resultOfGetEmptyPreFFRecord = Dem_PreFFD_GetEmptyFreezeFrameRecord( &preFFRecordIndex, &preFFRecordMng );
                if( resultOfGetEmptyPreFFRecord == DEM_IRT_OK )
                {
                    /* Found out an empty pre-store freeze frame record. */

                    /* Sets preFFD capture flags for OBD and non-OBD. */
                    Dem_PreFFD_SetPreFFDCaptureMng( eventStrgIndex, &preFFDCaptureMng );

                    /* Makes a new pre-store freeze frame record. */
                    Dem_PreFFD_CaptureFreezeFrame( dtcAttributePtr, &preFFDCaptureMng, monitorData0, preFFRecordMng.DataPtr );  /* [GUD]dtcAttributePtr */

#if ( DEM_FF_CHECKSUM_SUPPORT == STD_ON )
                    Dem_PreFFDMng_SetChecksum( preFFRecordIndex );
#endif  /* ( DEM_FF_CHECKSUM_SUPPORT == STD_ON) */

                    chkPreFFDCaptureFlag = Dem_PreFFD_CheckPreFFDCaptureFlag( &preFFDCaptureMng );
                    if( chkPreFFDCaptureFlag == (boolean)TRUE )
                    {
                        Dem_PreFFDMng_SetEventStrgIndex( preFFRecordIndex, eventStrgIndex );

                        Dem_PreFFDMng_SetUpdateRequest( preFFRecordIndex );
                    }

                    retVal = DEM_IRT_OK;
                }
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_PreFFD_ClearPrestoredFreezeFrame                     */
/* Description   | Clears pre-stored freeze frame by the specified event    */
/*               | index.                                                   */
/* Preconditions |                                                          */
/* Parameters    | [in] EventCtrlIndex :                                    */
/*               |        The index for Dem_EventRecordList.                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |       DEM_IRT_OK : Clearing was succeded.                */
/*               |       DEM_IRT_NG : Clearing was failed.                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PreFFD_ClearPrestoredFreezeFrame
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetPreFFRecord;
    VAR( boolean, AUTOMATIC ) ffPrestorageSupported;
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) preFFRecordIndex;
    VAR( Dem_PreFFRecordMngType, AUTOMATIC ) preFFRecordMng;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    retVal = DEM_IRT_NG;

    ffPrestorageSupported = Dem_CfgInfoPm_GetPreFFSupported_ByEvtCtrlIdx( EventCtrlIndex );
    if( ffPrestorageSupported == (boolean)TRUE )
    {
        /*  get EventStrgIndex          */
        eventStrgIndex  =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );                /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */

        preFFRecordIndex = DEM_PREFFD_INDEX_INVALID;
        Dem_PreFFDMng_InitFreezeFrameRecord( &preFFRecordMng );

        /* Waits to finish the exclusive section in the DemMainFunction context. */
        SchM_Enter_Dem_PrestoreFreezeFrame();
        SchM_Exit_Dem_PrestoreFreezeFrame();

        resultOfGetPreFFRecord = Dem_PreFFD_GetFreezeFrameRecord( eventStrgIndex, &preFFRecordIndex, &preFFRecordMng );
        if( resultOfGetPreFFRecord == DEM_IRT_OK )
        {
            /* Found out the pre-stored freeze frame record corresponding to the specified event index. */
            Dem_PreFFDMng_SetUpdateRequest( preFFRecordIndex );

            /* Clears the pre-stored freeze frame record corresponding to the specified event index. */
            Dem_PreFFDMng_SetEventStrgIndex( preFFRecordIndex, DEM_EVENTSTRGINDEX_INVALID );
        }

        retVal = DEM_IRT_OK;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_PreFFD_RemovePrestoredFreezeFrame                    */
/* Description   | Removes pre-stored freeze frame by the specified event   */
/*               | index.                                                   */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The index for Dem_EventRecordList.                */
/* Return Value  | void                                                     */
/* Notes         | Call from the context of main function.                  */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_PreFFD_RemovePrestoredFreezeFrame
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetPreFFRecord;
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) preFFRecordIndex;
    VAR( Dem_PreFFRecordMngType, AUTOMATIC ) preFFRecordMng;

    preFFRecordIndex = DEM_PREFFD_INDEX_INVALID;
    Dem_PreFFDMng_InitFreezeFrameRecord( &preFFRecordMng );

    SchM_Enter_Dem_PrestoreFreezeFrame();

    resultOfGetPreFFRecord = Dem_PreFFD_GetFreezeFrameRecord( EventStrgIndex, &preFFRecordIndex, &preFFRecordMng );
    if( resultOfGetPreFFRecord == DEM_IRT_OK )
    {
        /* Found out the pre-stored freeze frame record corresponding to the specified event index. */

        Dem_PreFFDMng_SetUpdateRequest( preFFRecordIndex );

        /* Removes the pre-stored freeze frame record corresponding to the specified event index. */
        Dem_PreFFDMng_SetEventStrgIndex( preFFRecordIndex, DEM_EVENTSTRGINDEX_INVALID );

    }

    SchM_Exit_Dem_PrestoreFreezeFrame();

    return ;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PreFFD_SetObdPreFFDToObdTriggerFFD                   */
/* Description   | Sets data of pre-stored freeze frame record to the spec- */
/*               | ified freeze frame record.                               */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The index for Dem_EventRecordList.                */
/*               | [in] FreezeFrameRecordTrigger :                          */
/*               |        DemFreezeFrameRecordTrigger.                      */
/*               | [in] MisfireCylinder :                                   */
/*               |        Misfire cylinder.                                 */
/*               | [out] ObdFreezeFrameRecordPtr :                          */
/*               |        The pointer of OBD freeze frame record to set da- */
/*               |        ta.                                               */
/* Return Value  | boolean :                                                */
/*               |       TRUE  : After this function called trigger FFD sh- */
/*               |               ould be captured.                          */
/*               |       FALSE : After this function called trigger FFD sh- */
/*               |               ould not be captured.                      */
/* Notes         | Call from the context of main function.                  */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_PreFFD_SetObdPreFFDToObdTriggerFFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,             /* MISRA DEVIATION */
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder,    /* MISRA DEVIATION */
    P2VAR( Dem_ObdFreezeFrameRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) ObdFreezeFrameRecordPtr
)
{
    VAR( boolean, AUTOMATIC ) triggerFFDCaptureFlag;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetPreFFRecord;
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) preFFRecordIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) srcPoint;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) copySize;
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) preFFDPoint;
    P2VAR( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) triggerFFDPoint;
    VAR( Dem_PreFFRecordMngType, AUTOMATIC ) preFFRecordMng;

    /* After this function called trigger FFD should be captured. */
    triggerFFDCaptureFlag = (boolean)TRUE;

    preFFRecordIndex = DEM_PREFFD_INDEX_INVALID;
    Dem_PreFFDMng_InitFreezeFrameRecord( &preFFRecordMng );

    SchM_Enter_Dem_PrestoreFreezeFrame();

    resultOfGetPreFFRecord = Dem_PreFFD_GetFreezeFrameRecord( EventStrgIndex, &preFFRecordIndex, &preFFRecordMng );
    if( resultOfGetPreFFRecord == DEM_IRT_OK )
    {
        /* Found out the pre-stored freeze frame record corresponding to the specified event index. */

        /* In case OBD start point is set to 0. */
        srcPoint = (Dem_u16_FFDStoredIndexType)0U;
        preFFDPoint = &preFFRecordMng.DataPtr[srcPoint];
        copySize = Dem_ObdFFDSize;
        triggerFFDPoint = ObdFreezeFrameRecordPtr->Data;
        ObdFreezeFrameRecordPtr->EventStrgIndex = EventStrgIndex;
        ObdFreezeFrameRecordPtr->RecordStatus = DEM_FFD_STORED;

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        Dem_Misfire_UpdateObdFFDInfo( EventStrgIndex, FreezeFrameRecordTrigger, MisfireCylinder );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

        /* Copies data of the pre-stored freeze frame record to the specified freeze frame record. */
        Dem_UtlMem_CopyMemory( triggerFFDPoint, preFFDPoint, copySize );

        /* After this function called trigger FFD should not be captured. */
        triggerFFDCaptureFlag = (boolean)FALSE;
    }

    SchM_Exit_Dem_PrestoreFreezeFrame();

    return triggerFFDCaptureFlag;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_PreFFD_SetPreFFDToTriggerFFD                         */
/* Description   | Sets data of pre-stored freeze frame record to the spec- */
/*               | ified freeze frame record.                               */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The index for Dem_EventRecordList.                */
/*               | [in] FreezeFrameClassPtr :                               */
/*               |        The pointer of DemFreezeFrameClass.               */
/*               | [in] FreezeFrameRecordTrigger :                          */
/*               |        DemFreezeFrameRecordTrigger.                      */
/*               | [in] MisfireCylinder :                                   */
/*               |        Misfire cylinder.                                 */
/*               | [out] FreezeFrameRecordPtr :                             */
/*               |        The pointer of freeze frame record to set data.   */
/* Return Value  | boolean :                                                */
/*               |       TRUE  : After this function called trigger FFD sh- */
/*               |               ould be captured.                          */
/*               |       FALSE : After this function called trigger FFD sh- */
/*               |               ould not be captured.                      */
/* Notes         | Call from the context of main function.                  */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_PreFFD_SetPreFFDToTriggerFFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameClassPtr,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,             /* MISRA DEVIATION */
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder,    /* MISRA DEVIATION */
    P2VAR( Dem_FreezeFrameRecordForCtlType, AUTOMATIC, DEM_VAR_NO_INIT ) FreezeFrameRecordPtr
)
{
    VAR( boolean, AUTOMATIC ) triggerFFDCaptureFlag;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfGetPreFFRecord;
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) preFFRecordIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) srcPoint;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) copySize;
    P2CONST( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) preFFDPoint;
    P2VAR( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) triggerFFDPoint;
    VAR( Dem_PreFFRecordMngType, AUTOMATIC ) preFFRecordMng;

    /* After this function called trigger FFD should be captured. */
    triggerFFDCaptureFlag = (boolean)TRUE;

    preFFRecordIndex = DEM_PREFFD_INDEX_INVALID;
    Dem_PreFFDMng_InitFreezeFrameRecord( &preFFRecordMng );

    SchM_Enter_Dem_PrestoreFreezeFrame();

    resultOfGetPreFFRecord = Dem_PreFFD_GetFreezeFrameRecord( EventStrgIndex, &preFFRecordIndex, &preFFRecordMng );
    if( resultOfGetPreFFRecord == DEM_IRT_OK )
    {
        /* Found out the pre-stored freeze frame record corresponding to the specified event index. */

        /* In case non-OBD start point is set to end of PidClass's data. */
        srcPoint = Dem_ObdFFDSize;
        preFFDPoint = &preFFRecordMng.DataPtr[srcPoint];
        copySize = FreezeFrameClassPtr->DemDidClassSize;
        triggerFFDPoint = FreezeFrameRecordPtr->Data;
        FreezeFrameRecordPtr->EventStrgIndex = EventStrgIndex;
        FreezeFrameRecordPtr->RecordStatus = DEM_FFD_STORED;

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        Dem_Misfire_UpdateFFDInfo( EventStrgIndex, FreezeFrameRecordTrigger, MisfireCylinder );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

        /* Copies data of the pre-stored freeze frame record to the specified freeze frame record. */
        Dem_UtlMem_CopyMemory( triggerFFDPoint, preFFDPoint, copySize );

        /* After this function called trigger FFD should not be captured. */
        triggerFFDCaptureFlag = (boolean)FALSE;
    }

    SchM_Exit_Dem_PrestoreFreezeFrame();

    return triggerFFDCaptureFlag;
}

/****************************************************************************/
/* Function Name | Dem_PreFFD_CheckTriggerToRemovePreFFD                    */
/* Description   | Checks if remove the pre-stored freeze frame record.     */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The index for Dem_EventRecordList.                */
/*               | [in] TriggerCondition :                                  */
/*               |        An effective trigger condition.                   */
/* Return Value  | boolean :                                                */
/*               |       TRUE  : The pre-stored freeze frame record which   */
/*               |               is corresponding to the specified event s- */
/*               |               hould be removed.                          */
/*               |       FALSE : The pre-stored freeze frame record which   */
/*               |               is corresponding to the specified event s- */
/*               |               hould not be removed.                      */
/* Notes         | Call from the context of main function.                  */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_PreFFD_CheckTriggerToRemovePreFFD
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) TriggerCondition
)
{
    VAR( boolean, AUTOMATIC ) removePreFFDFlag;
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) dtcAttributePtr;

    removePreFFDFlag    =   (boolean)FALSE;
    dtcAttributePtr    =   Dem_CfgInfoPm_GetDTCAttrTablePtr_PreFF( EventStrgIndex ); /* [GUD:RET:Not NULL_PTR]dtcAttributePtr */
    if ( dtcAttributePtr != NULL_PTR )                                              /* [GUD:if]dtcAttributePtr */
    {
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
        removePreFFDFlag = Dem_PreFFD_CheckObdTriggerToRemovePreFFD( dtcAttributePtr, TriggerCondition );       /* [GUD]dtcAttributePtr */
        if( removePreFFDFlag == (boolean)FALSE )
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */
        {
            removePreFFDFlag = Dem_PreFFD_CheckNonObdTriggerToRemovePreFFD( dtcAttributePtr, TriggerCondition );    /* [GUD]dtcAttributePtr */
        }
    }
    return removePreFFDFlag;
}


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dem_PreFFD_GetFreezeFrameRecord                          */
/* Description   | Gets the pre-stored freeze frame record whose index mat- */
/*               | ches the specified event index.                          */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The index for Dem_EventRecordList.                */
/*               | [out] PreFFRecordIndexPtr :                              */
/*               |        The index of pre-store freeze frame record list   */
/*               |        to store pre-store freeze frame data.             */
/*               | [out] PreFFRecordMngPtr :                                */
/*               |        The pre-store freeze frame record to store pre-s- */
/*               |        tore freeze frame data.                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |       DEM_IRT_OK : Getting was succeded.                 */
/*               |       DEM_IRT_NG : Getting was failed.                   */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PreFFD_GetFreezeFrameRecord
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_u08_PreFFDIndexType, AUTOMATIC, AUTOMATIC ) PreFFRecordIndexPtr,
    P2VAR( Dem_PreFFRecordMngType, AUTOMATIC, AUTOMATIC ) PreFFRecordMngPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) preFFRecordIndex;
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) prestoredFFMaxNum;

    retVal = DEM_IRT_NG;
    prestoredFFMaxNum = Dem_PrestoredFFMaxNum;

    for( preFFRecordIndex = ( Dem_u08_PreFFDIndexType )0U; preFFRecordIndex < prestoredFFMaxNum; preFFRecordIndex++ )
    {
        (void)Dem_PreFFDMng_GetFreezeFrameRecord( preFFRecordIndex, PreFFRecordMngPtr );/* no return check required */
        if( PreFFRecordMngPtr->EventStrgIndex != DEM_EVENTSTRGINDEX_INVALID )
        {
            if( PreFFRecordMngPtr->EventStrgIndex == EventStrgIndex )
            {
                *PreFFRecordIndexPtr = preFFRecordIndex;
                retVal = DEM_IRT_OK;

                break;
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_PreFFD_GetEmptyFreezeFrameRecord                     */
/* Description   | Gets the pre-stored freeze frame record which is empty.  */
/* Preconditions |                                                          */
/* Parameters    | [out] PreFFRecordIndexPtr :                              */
/*               |        The index of pre-store freeze frame record list   */
/*               |        to store pre-store freeze frame data.             */
/*               | [out] PreFFRecordMngPtr :                                */
/*               |        The pre-store freeze frame record to store pre-s- */
/*               |        tore freeze frame data.                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |       DEM_IRT_OK : Getting was succeded.                 */
/*               |       DEM_IRT_NG : Getting was failed.                   */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PreFFD_GetEmptyFreezeFrameRecord
(
    P2VAR( Dem_u08_PreFFDIndexType, AUTOMATIC, AUTOMATIC ) PreFFRecordIndexPtr,
    P2VAR( Dem_PreFFRecordMngType, AUTOMATIC, AUTOMATIC ) PreFFRecordMngPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) preFFRecordIndex;
    VAR( Dem_u08_PreFFDIndexType, AUTOMATIC ) prestoredFFMaxNum;

    retVal = DEM_IRT_NG;
    prestoredFFMaxNum = Dem_PrestoredFFMaxNum;

    for( preFFRecordIndex = ( Dem_u08_PreFFDIndexType )0U; preFFRecordIndex < prestoredFFMaxNum; preFFRecordIndex++ )
    {
        (void)Dem_PreFFDMng_GetFreezeFrameRecord( preFFRecordIndex, PreFFRecordMngPtr );/* no return check required */
        if( PreFFRecordMngPtr->EventStrgIndex == DEM_EVENTSTRGINDEX_INVALID )
        {
            *PreFFRecordIndexPtr = preFFRecordIndex;
            retVal = DEM_IRT_OK;

            break;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_PreFFD_CaptureFreezeFrame                            */
/* Description   | Captures freeze frame for pre-storage.                   */
/* Preconditions |                                                          */
/* Parameters    | [in] DTCAttributePtr :                                   */
/*               |        DTCAttributeRef.                                  */
/*               | [in] PreFFDCaptureMngPtr :                               */
/*               |        The manage-information for preFFD capturing.      */
/*               | [out] PreFFDataPtr :                                     */
/*               |        The pointer to store pre-store freeze frame data. */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PreFFD_CaptureFreezeFrame
(
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) DTCAttributePtr,       /* [PRMCHK:CALLER] */
    P2CONST( Dem_PreFFDCaptureMngType, AUTOMATIC, AUTOMATIC ) PreFFDCaptureMngPtr,                  /* [PRMCHK:CALLER] */
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) PreFFDataPtr
)
{
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) obdFreezeFrameClassRef;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )            */


#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
    obdFreezeFrameClassRef  =   DTCAttributePtr->DemOBDFreezeFrameClassRef;     /* [GUDCHK:CALLER]DTCAttributePtr */
    Dem_PreFFD_CaptureObdFreezeFrame( obdFreezeFrameClassRef, PreFFDCaptureMngPtr->ObdPreFFDCaptureFlag, monitorData0, PreFFDataPtr );      /* [GUDCHK:CALLER]PreFFDCaptureMngPtr */
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )            */

    freezeFrameClassRef =   DTCAttributePtr->DemFreezeFrameClassRef;            /* [GUDCHK:CALLER]DTCAttributePtr */
    Dem_PreFFD_CaptureNonObdFreezeFrame( freezeFrameClassRef, PreFFDCaptureMngPtr->NonObdPreFFDCaptureFlag, monitorData0, PreFFDataPtr );   /* [GUDCHK:CALLER]PreFFDCaptureMngPtr */

    return;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PreFFD_CaptureObdFreezeFrame                         */
/* Description   | Captures OBD freeze frame for pre-storage.               */
/* Preconditions |                                                          */
/* Parameters    | [in] OBDFreezeFrameClassRef :                            */
/*               |        The DemDTCAttributes which is coresponding to the */
/*               |        event.                                            */
/*               | [in] ObdPreFFDCaptureFlag :                              */
/*               |        The preFFD capture flag for OBD.                  */
/*               | [in] monitorData0 :   monitorData0.                      */
/*               | [out] PreFFDataPtr :                                     */
/*               |        The pointer to store pre-store freeze frame data. */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PreFFD_CaptureObdFreezeFrame
(
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) OBDFreezeFrameClassRef,
    VAR( boolean, AUTOMATIC ) ObdPreFFDCaptureFlag,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) PreFFDataPtr
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) freezeFrameDataOffset;
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA) obdFreezeFrameClassPtr;

    if( OBDFreezeFrameClassRef != DEM_FFCLASSINDEX_INVALID )                            /* [GUD:if]OBDFreezeFrameClassRef */
    {
        obdFreezeFrameClassPtr = &Dem_FreezeFrameClassTable[OBDFreezeFrameClassRef];    /* [GUD]OBDFreezeFrameClassRef */

        if( ObdPreFFDCaptureFlag == (boolean)TRUE )
        {
            freezeFrameDataOffset = (Dem_u16_FFDStoredIndexType)0U;
            Dem_PreFFD_CaptureFreezeFrameClass( obdFreezeFrameClassPtr, freezeFrameDataOffset, monitorData0, PreFFDataPtr );
        }
    }

    return;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_PreFFD_CaptureNonObdFreezeFrame                      */
/* Description   | Captures non-OBD freeze frame for pre-storage.           */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameClassRef :                               */
/*               |        The DemDTCAttributes which is coresponding to the */
/*               |        event.                                            */
/*               | [in] NonObdPreFFDCaptureFlag :                           */
/*               |        The preFFD capture flag for non-OBD.              */
/*               | [in] monitorData0 :   monitorData0.                      */
/*               | [out] PreFFDataPtr :                                     */
/*               |        The pointer to store pre-store freeze frame data. */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PreFFD_CaptureNonObdFreezeFrame
(
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) FreezeFrameClassRef,
    VAR( boolean, AUTOMATIC ) NonObdPreFFDCaptureFlag,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) PreFFDataPtr
)
{
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) freezeFrameDataOffset;
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA) nonObdFreezeFrameClassPtr;

    if( FreezeFrameClassRef != DEM_FFCLASSINDEX_INVALID )                               /* [GUD:if]FreezeFrameClassRef */
    {
        nonObdFreezeFrameClassPtr = &Dem_FreezeFrameClassTable[FreezeFrameClassRef];    /* [GUD]FreezeFrameClassRef */

        if( NonObdPreFFDCaptureFlag == (boolean)TRUE )
        {
            freezeFrameDataOffset = (Dem_u16_FFDStoredIndexType)Dem_ObdFFDSize;
            Dem_PreFFD_CaptureFreezeFrameClass( nonObdFreezeFrameClassPtr, freezeFrameDataOffset, monitorData0, PreFFDataPtr );
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_PreFFD_CaptureFreezeFrameClass                       */
/* Description   | Captures DemDataElementClasses of DemDidClasses of the   */
/*               | specified DemFreezeFrameClass.                           */
/* Preconditions |                                                          */
/* Parameters    | [in] FreezeFrameClassPtr :                               */
/*               |        DemFreezeFrameClass which has references to DemD- */
/*               |        idClass .                                         */
/*               | [in] FreezeFrameDataOffset :                             */
/*               |        The offset size of pre-store freeze frame data w- */
/*               |        hich read in.                                     */
/*               | [in] monitorData0 :   monitorData0.                      */
/*               | [out] PreFFDataPtr :                                     */
/*               |        The data area of the pre-store freeze frame reco- */
/*               |        rd to store pre-store freeze frame data.          */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PreFFD_CaptureFreezeFrameClass
(
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameClassPtr,
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) FreezeFrameDataOffset,
    VAR( Dem_MonitorDataType, AUTOMATIC ) monitorData0,
    P2VAR( uint8, AUTOMATIC, DEM_VAR_SAVED_ZONE ) PreFFDataPtr
)
{
    VAR( Std_ReturnType, AUTOMATIC ) resultOfCallback;
    VAR( boolean, AUTOMATIC ) ffdOutputAllow;
    VAR( Dem_u08_DtElNumPerDIDIndexType, AUTOMATIC ) dataElementClassRefIndex;
    VAR( Dem_u08_DtElNumPerDIDIndexType, AUTOMATIC ) dataElementClassNum;
    VAR( Dem_u08_DIDClassPerFFIndexType, AUTOMATIC ) didClassRefIndex;
    VAR( Dem_u32_DIDClassIndexType, AUTOMATIC ) didClassIndex;
    VAR( Dem_u16_DataElementClassIndexType, AUTOMATIC ) dataElementClassIndex;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) freezeFrameDataOffset;

    P2CONST( AB_83_ConstV Dem_DataElementClassType, AUTOMATIC, DEM_CONFIG_DATA ) dataElementClassPtr;
    P2CONST( AB_83_ConstV Dem_DidClassType, AUTOMATIC, DEM_CONFIG_DATA ) didClassPtr;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) demDataElementSize;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) demDidDataSize;

    freezeFrameDataOffset = FreezeFrameDataOffset;

    for( didClassRefIndex = (Dem_u08_DIDClassPerFFIndexType)0U; didClassRefIndex < FreezeFrameClassPtr->DemDidClassNum; didClassRefIndex++ )        /* [GUD:for]didClassRefIndex */
    {
        didClassIndex = FreezeFrameClassPtr->DemDidClassRef[didClassRefIndex];          /* [GUD]didClassRefIndex *//* [GUD:CFG:IF_GUARDED: didClassRefIndex ]didClassIndex */
        didClassPtr = &Dem_DIDClassTable[didClassIndex];                                /* [GUD]didClassIndex *//* [GUD:CFG:IF_GUARDED: didClassIndex ]didClassPtr */

        ffdOutputAllow = Dem_PreFFD_SetFFDOutputJudge( didClassPtr, PreFFDataPtr, &freezeFrameDataOffset );
        if( ffdOutputAllow == (boolean)TRUE )
        {
            dataElementClassNum = didClassPtr->DemDataElementClassNum;                  /* [GUD]didClassPtr */

            for( dataElementClassRefIndex = (Dem_u08_DtElNumPerDIDIndexType)0U; dataElementClassRefIndex < dataElementClassNum; dataElementClassRefIndex++ )    /* [GUD:for]dataElementClassRefIndex */
            {
                dataElementClassIndex = didClassPtr->DemDataElementClassRef[dataElementClassRefIndex];  /* [GUD]didClassPtr *//* [GUD]dataElementClassRefIndex *//* [GUD:CFG:IF_GUARDED: didClassPtr,dataElementClassRefIndex ]dataElementClassIndex */
                dataElementClassPtr = &Dem_DataElementClassTable[dataElementClassIndex];                /* [GUD]dataElementClassIndex *//* [GUD:CFG:IF_GUARDED: dataElementClassIndex ]dataElementClassPtr */

                resultOfCallback = Dem_DataElement_ReadData( dataElementClassPtr, &PreFFDataPtr[freezeFrameDataOffset] , monitorData0 );

                demDataElementSize = (Dem_u16_FFDStoredIndexType)dataElementClassPtr->DemDataElementSize;   /* [GUD:CFG]demDataElementSize */
                if( resultOfCallback != (Std_ReturnType)E_OK )
                {
                    Dem_UtlMem_SetMemory( &PreFFDataPtr[freezeFrameDataOffset], DEM_FF_PADDING_DATA, demDataElementSize );
                }

                freezeFrameDataOffset = freezeFrameDataOffset + demDataElementSize;
            }
        }
        else
        {
            demDidDataSize = (Dem_u16_FFDStoredIndexType)didClassPtr->DemDidDataSize;                           /* [GUD]didClassPtr *//* [GUD:CFG:IF_GUARDED: didClassPtr ]demDidDataSize */
            Dem_UtlMem_SetMemory( &PreFFDataPtr[freezeFrameDataOffset], DEM_FF_PADDING_DATA, demDidDataSize );  /* [GUD]freezeFrameDataOffset */
            freezeFrameDataOffset = freezeFrameDataOffset + demDidDataSize;                                     /* [GUD:CFG:demDidDataSize]freezeFrameDataOffset */
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_PreFFD_SetPreFFDCaptureMng                           */
/* Description   | Sets preFFD capture flags for OBD and non-OBD.           */
/* Preconditions |                                                          */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The index for Dem_EventRecordList.                */
/*               | [out] PreFFDCaptureMngPtr :                              */
/*               |        The manage-information for preFFD capturing.      */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PreFFD_SetPreFFDCaptureMng
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_PreFFDCaptureMngType, AUTOMATIC, AUTOMATIC ) PreFFDCaptureMngPtr
)
{
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;
    VAR( Dem_FaultRecordType, AUTOMATIC ) faultRecord;

    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) dtcAttributePtr;

    faultIndex = DEM_FAULTINDEX_INITIAL;
    Dem_DataMngC_InitFaultCtlRecordData( &faultRecord );

    (void)Dem_DataMngC_GetER_FaultIndex( EventStrgIndex, &faultIndex );/* no return check required */           /* [GUD:RET:DEM_IRT_OK] EventStrgIndex */
    (void)Dem_DataMngC_GetFaultRecord( faultIndex, &faultRecord );/* no return check required */

    dtcAttributePtr    =   Dem_CfgInfoPm_GetDTCAttrTablePtr_PreFF( EventStrgIndex );    /* [GUD:RET:Not NULL_PTR]dtcAttributePtr *//* [GUD:RET:Not NULL_PTR]EventStrgIndex */
    if ( dtcAttributePtr != NULL_PTR )                                                  /* [GUD:if]dtcAttributePtr */
    {
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
        Dem_PreFFD_SetObdPreFFDCaptureFlag( dtcAttributePtr, &faultRecord, PreFFDCaptureMngPtr );       /* [GUD]dtcAttributePtr */
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
        Dem_PreFFD_SetNonObdPreFFDCaptureFlag( dtcAttributePtr, &faultRecord, PreFFDCaptureMngPtr );    /* [GUD]dtcAttributePtr */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_PreFFD_SetObdPreFFDCaptureFlag                       */
/* Description   | Sets preFFD capture flag for OBD.                        */
/* Preconditions |                                                          */
/* Parameters    | [in] DTCAttributePtr :                                   */
/*               |        The DemDTCAttributes which is coresponding to the */
/*               |        event.                                            */
/*               | [in] FaultRecordPtr :                                    */
/*               |        The fault record corresponding to the specified   */
/*               |        event index.                                      */
/*               | [out] PreFFDCaptureMngPtr :                              */
/*               |        The manage-information for preFFD capturing.      */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( void, DEM_CODE ) Dem_PreFFD_SetObdPreFFDCaptureFlag
(
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) DTCAttributePtr,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_PreFFDCaptureMngType, AUTOMATIC, AUTOMATIC ) PreFFDCaptureMngPtr
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;

    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) ffRecNumClassRef;

    PreFFDCaptureMngPtr->ObdPreFFDCaptureFlag = (boolean)FALSE;

    obdFFRClassPerDTCMaxNum = Dem_OBDFFRClassPerDTCMaxNum;

    if( DTCAttributePtr->DemOBDFreezeFrameRecNumClassRef != DEM_FFRECNUMCLASSINDEX_INVALID )        /* [GUD:if]DTCAttributePtr->DemOBDFreezeFrameRecNumClassRef */
    {
        ffRecNumClassRef = DTCAttributePtr->DemOBDFreezeFrameRecNumClassRef;
        freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[ffRecNumClassRef];             /* [GUD]ffRecNumClassRef( == DTCAttributePtr->DemOBDFreezeFrameRecNumClassRef ) */

        Dem_PreFFD_SetPreFFDCaptureFlag( obdFFRClassPerDTCMaxNum, FaultRecordPtr->ObdRecordNumberIndex, freezeFrameRecNumClassPtr, (boolean)TRUE, &PreFFDCaptureMngPtr->ObdPreFFDCaptureFlag );
    }

    return;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_PreFFD_SetNonObdPreFFDCaptureFlag                    */
/* Description   | Sets preFFD capture flag for non-OBD.                    */
/* Preconditions |                                                          */
/* Parameters    | [in] DTCAttributePtr :                                   */
/*               |        The DemDTCAttributes which is coresponding to the */
/*               |        event.                                            */
/*               | [in] FaultRecordPtr :                                    */
/*               |        The fault record corresponding to the specified   */
/*               |        event index.                                      */
/*               | [out] PreFFDCaptureMngPtr :                              */
/*               |        The manage-information for preFFD capturing.      */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PreFFD_SetNonObdPreFFDCaptureFlag
(
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) DTCAttributePtr,
    P2CONST( Dem_FaultRecordType, AUTOMATIC, AUTOMATIC ) FaultRecordPtr,
    P2VAR( Dem_PreFFDCaptureMngType, AUTOMATIC, AUTOMATIC ) PreFFDCaptureMngPtr
)
{
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) ffRecNumClassRef;

    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;

    PreFFDCaptureMngPtr->NonObdPreFFDCaptureFlag = (boolean)FALSE;

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;

    if( DTCAttributePtr->DemFreezeFrameRecNumClassRef != DEM_FFRECNUMCLASSINDEX_INVALID )       /* [GUD:if]DTCAttributePtr->DemFreezeFrameRecNumClassRef */
    {
        ffRecNumClassRef = DTCAttributePtr->DemFreezeFrameRecNumClassRef;
        freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[ffRecNumClassRef];         /* [GUD]ffRecNumClassRef( == DTCAttributePtr->DemFreezeFrameRecNumClassRef ) */

        Dem_PreFFD_SetPreFFDCaptureFlag( nonOBDFFRClassPerDTCMaxNum, FaultRecordPtr->RecordNumberIndex, freezeFrameRecNumClassPtr, (boolean)FALSE, &PreFFDCaptureMngPtr->NonObdPreFFDCaptureFlag );
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_PreFFD_SetPreFFDCaptureFlag                          */
/* Description   | Sets preFFD capture flag by the specified array of reco- */
/*               | rd number index the specified trigger of freeze frame r- */
/*               | ecord class.                                             */
/* Preconditions |                                                          */
/* Parameters    | [in] FFRClassPerDTCMaxNum :                              */
/*               |        The number of freeze frame record class per DTC.  */
/*               | [in] RecordNumberIndexPtr :                              */
/*               |        The pointer to the first item in (Obd)RecordNumb- */
/*               |        erIndex array.                                    */
/*               | [in] FreezeFrameRecNumClassPtr :                         */
/*               |        The pointer to the DemFreezeFrameRecNumClass.     */
/*               | [in] ObdFFDFlag :                                        */
/*               |        OBD FFD Flag.                                     */
/*               | [out] PreFFDCaptureFlagPtr :                             */
/*               |        The pointer to set preFFD capture flag.           */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_PreFFD_SetPreFFDCaptureFlag
(
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FFRClassPerDTCMaxNum,
    P2CONST( Dem_u08_FFDIndexType, AUTOMATIC, AUTOMATIC ) RecordNumberIndexPtr,
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameRecNumClassPtr,
    VAR( boolean, AUTOMATIC ) ObdFFDFlag,             /* MISRA DEVIATION */
    P2VAR( boolean, AUTOMATIC, DEM_VAR_NO_INIT ) PreFFDCaptureFlagPtr
)
{
    VAR( Dem_u08_UpdateRecordType, AUTOMATIC ) ffrUpdate;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordClassRefIndex;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) ffrRecordClassConfigureNum;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) freezeFrameRecordClassIndex;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) ffrTrigger;
    VAR( boolean, AUTOMATIC ) judgeUpdateObdPendingFFD;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )            */

    (*PreFFDCaptureFlagPtr) = (boolean)FALSE;

    ffrRecordClassConfigureNum = Dem_FFRRecordClassConfigureNum;

    for( freezeFrameRecordClassRefIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordClassRefIndex < FFRClassPerDTCMaxNum; freezeFrameRecordClassRefIndex++ )    /* [GUD:for]freezeFrameRecordClassRefIndex */
    {
        freezeFrameRecordClassIndex = FreezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[freezeFrameRecordClassRefIndex];          /* [GUD]freezeFrameRecordClassRefIndex */
        if( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum )                                                                  /* [GUD:if]freezeFrameRecordClassRefIndex */
        {
            ffrUpdate = Dem_FreezeFrameRecordClassTable[freezeFrameRecordClassIndex].DemFreezeFrameRecordUpdate;                        /* [GUD]freezeFrameRecordClassRefIndex */
            if( ffrUpdate == DEM_UPDATE_RECORD_YES )
            {
                (*PreFFDCaptureFlagPtr) = (boolean)TRUE;
            }
            else if( RecordNumberIndexPtr[freezeFrameRecordClassRefIndex] == DEM_FFRECINDEX_INITIAL )
            {
                (*PreFFDCaptureFlagPtr) = (boolean)TRUE;
            }
            else
            {
                /* check OBDFFD.   */
#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
                if( ObdFFDFlag == (boolean)TRUE )
                {
                    ffrTrigger = Dem_FreezeFrameRecordClassTable[freezeFrameRecordClassIndex].DemFreezeFrameRecordTrigger;
                    if( ffrTrigger == DEM_TRIGGER_ON_PENDING )
                    {
                        judgeUpdateObdPendingFFD = Dem_JudgePendingOBDFFDUpdateAtConfirmedTrigger();
                        if( judgeUpdateObdPendingFFD == (boolean)TRUE )
                        {
                            (*PreFFDCaptureFlagPtr) = (boolean)TRUE;
                        }
                    }
                }
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )            */
            }

            if( (*PreFFDCaptureFlagPtr) == (boolean)TRUE )
            {
                break;
            }
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_PreFFD_CheckPreFFDCaptureFlag                        */
/* Description   | Checks if PreFFD for OBD or non-OBD are should be captu- */
/*               | red.                                                     */
/* Preconditions |                                                          */
/* Parameters    | [in] PreFFDCaptureMngPtr :                               */
/*               |        The manage-information for preFFD capturing.      */
/* Return Value  | boolean :                                                */
/*               |       TRUE  : PreFFD for OBD or non OBD are should be c- */
/*               |               aptured.                                   */
/*               |       FALSE : PreFFD for OBD or non OBD are should not   */
/*               |               be captured.                               */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_PreFFD_CheckPreFFDCaptureFlag
(
    P2CONST( Dem_PreFFDCaptureMngType, AUTOMATIC, AUTOMATIC ) PreFFDCaptureMngPtr
)
{
    VAR( boolean, AUTOMATIC ) preFFDCaptureFlag;

    /* Initializes the return value to "should be captured". */
    preFFDCaptureFlag = (boolean)TRUE;

#if ( DEM_OBDFFD_SUPPORT == STD_ON )   /*  [FuncSw]    */
    if( PreFFDCaptureMngPtr->ObdPreFFDCaptureFlag == (boolean)FALSE )
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )            */
    {
        if( PreFFDCaptureMngPtr->NonObdPreFFDCaptureFlag == (boolean)FALSE )
        {
            /* Sets the return value to "should not captured". */
            preFFDCaptureFlag = (boolean)FALSE;
        }
    }

    return preFFDCaptureFlag;
}

/****************************************************************************/
/* Function Name | Dem_PreFFD_CheckObdTriggerToRemovePreFFD                 */
/* Description   | Sets preFFD capture flag for OBD.                        */
/* Preconditions |                                                          */
/* Parameters    | [in] DTCAttributePtr :                                   */
/*               |        The DemDTCAttributes which is coresponding to the */
/*               |        event.                                            */
/*               | [in] TriggerCondition :                                  */
/*               |        An effective trigger condition.                   */
/* Return Value  | boolean :                                                */
/*               |       TRUE  : PreFFD for OBD or non OBD are should be r- */
/*               |               emoved.                                    */
/*               |       FALSE : PreFFD for OBD or non OBD are should not   */
/*               |               be removed.                                */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( boolean, DEM_CODE ) Dem_PreFFD_CheckObdTriggerToRemovePreFFD
(
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) DTCAttributePtr,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) TriggerCondition
)
{
    VAR( boolean, AUTOMATIC ) chkTriggerCondition;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) obdFFRClassPerDTCMaxNum;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) ffRecNumClassRef;
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;

    chkTriggerCondition = (boolean)FALSE;

    obdFFRClassPerDTCMaxNum = Dem_OBDFFRClassPerDTCMaxNum;

    if( DTCAttributePtr->DemOBDFreezeFrameRecNumClassRef != DEM_FFRECNUMCLASSINDEX_INVALID )        /* [GUD:if]DTCAttributePtr->DemOBDFreezeFrameRecNumClassRef */
    {
        ffRecNumClassRef = DTCAttributePtr->DemOBDFreezeFrameRecNumClassRef;
        freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[ffRecNumClassRef];             /* [GUD]ffRecNumClassRef( == DTCAttributePtr->DemOBDFreezeFrameRecNumClassRef ) */

        chkTriggerCondition = Dem_PreFFD_CheckTriggerCondition( obdFFRClassPerDTCMaxNum, freezeFrameRecNumClassPtr, TriggerCondition );
    }

    return chkTriggerCondition;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )    */

/****************************************************************************/
/* Function Name | Dem_PreFFD_CheckNonObdTriggerToRemovePreFFD              */
/* Description   | Sets preFFD capture flag for non-OBD.                    */
/* Preconditions |                                                          */
/* Parameters    | [in] DTCAttributePtr :                                   */
/*               |        The DemDTCAttributes which is coresponding to the */
/*               |        event.                                            */
/*               | [in] TriggerCondition :                                  */
/*               |        An effective trigger condition.                   */
/* Return Value  | boolean :                                                */
/*               |       TRUE  : PreFFD for OBD or non OBD are should be r- */
/*               |               emoved.                                    */
/*               |       FALSE : PreFFD for OBD or non OBD are should not   */
/*               |               be removed.                                */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_PreFFD_CheckNonObdTriggerToRemovePreFFD
(
    P2CONST( AB_83_ConstV Dem_DTCAttributeType, AUTOMATIC, DEM_CONFIG_DATA ) DTCAttributePtr,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) TriggerCondition
)
{
    VAR( boolean, AUTOMATIC ) chkTriggerCondition;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) nonOBDFFRClassPerDTCMaxNum;

    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) freezeFrameRecNumClassPtr;
    VAR( Dem_u16_FFRecNumClassIndexType, AUTOMATIC ) ffRecNumClassRef;

    chkTriggerCondition = (boolean)FALSE;

    nonOBDFFRClassPerDTCMaxNum = Dem_NonOBDFFRClassPerDTCMaxNum;

    if( DTCAttributePtr->DemFreezeFrameRecNumClassRef != DEM_FFRECNUMCLASSINDEX_INVALID )       /* [GUD:if]DTCAttributePtr->DemFreezeFrameRecNumClassRef */
    {
        ffRecNumClassRef = DTCAttributePtr->DemFreezeFrameRecNumClassRef;
        freezeFrameRecNumClassPtr = &Dem_FreezeFrameRecNumClassTable[ffRecNumClassRef];         /* [GUD]ffRecNumClassRef( == DTCAttributePtr->DemFreezeFrameRecNumClassRef ) */

        chkTriggerCondition = Dem_PreFFD_CheckTriggerCondition( nonOBDFFRClassPerDTCMaxNum, freezeFrameRecNumClassPtr, TriggerCondition );
    }

    return chkTriggerCondition;
}

/****************************************************************************/
/* Function Name | Dem_PreFFD_CheckTriggerCondition                         */
/* Description   | Checks trigger condition to match.                       */
/* Preconditions |                                                          */
/* Parameters    | [in] FFRClassPerDTCMaxNum :                              */
/*               |        The number of freeze frame record class per DTC.  */
/*               | [in] FreezeFrameRecNumClassPtr :                         */
/*               |        The pointer to the DemFreezeFrameRecNumClass.     */
/*               | [in] TriggerCondition :                                  */
/*               |        An effective trigger condition.                   */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_PreFFD_CheckTriggerCondition
(
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) FFRClassPerDTCMaxNum,
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameRecNumClassPtr,
    VAR( Dem_u08_FFValidTriggerType, AUTOMATIC ) TriggerCondition
)
{
    VAR( boolean, AUTOMATIC ) chkTriggerCondition;
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) ffrTrigger;
    VAR( Dem_u08_FFListIndexType, AUTOMATIC ) freezeFrameRecordClassRefIndex;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) ffrRecordClassConfigureNum;
    VAR( Dem_u08_FFRecordClassIndexType, AUTOMATIC ) freezeFrameRecordClassIndex;

    chkTriggerCondition = (boolean)FALSE;

    ffrRecordClassConfigureNum = Dem_FFRRecordClassConfigureNum;

    for( freezeFrameRecordClassRefIndex = (Dem_u08_FFListIndexType)0U; freezeFrameRecordClassRefIndex < FFRClassPerDTCMaxNum; freezeFrameRecordClassRefIndex++ )    /* [GUD:for]freezeFrameRecordClassRefIndex */
    {
        freezeFrameRecordClassIndex = FreezeFrameRecNumClassPtr->DemFreezeFrameRecordClassRef[freezeFrameRecordClassRefIndex];  /* [GUD]freezeFrameRecordClassRefIndex */
        if( freezeFrameRecordClassIndex < ffrRecordClassConfigureNum )                                                          /* [GUD:if]freezeFrameRecordClassIndex */
        {
            ffrTrigger = Dem_FreezeFrameRecordClassTable[freezeFrameRecordClassIndex].DemFreezeFrameRecordTrigger;              /* [GUD]freezeFrameRecordClassIndex */
            chkTriggerCondition = Dem_CfgInfo_CheckTrigger( ffrTrigger, TriggerCondition );
            if( chkTriggerCondition == (boolean)TRUE )
            {
                break;
            }
        }
    }

    return chkTriggerCondition;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_FF_PRESTORAGE_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
