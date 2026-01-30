/* Dem_Misfire_PFC_c(v5-7-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Misfire_PFC/CODE                                      */
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
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Rc_PFCMng.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_DTC_PFC.h"
#include "Dem_Misfire_local.h"

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#if ( DEM_PFC_SUPPORT == STD_ON )

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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_CheckPFCRecord
( void );

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_PFCMisfireComRecordType, DEM_VAR_NO_INIT ) Dem_TmpMisfirePermanent;
#if ( DEM_PFC_OUTPUT_DEMINTERNALPFC_TODCM_SUPPORT == STD_ON )
static VAR( Dem_MisfireCylinderNumberType, DEM_VAR_NO_INIT ) Dem_MisfirePFCSearchCylinderNum;
#endif /* ( DEM_PFC_OUTPUT_DEMINTERNALPFC_TODCM_SUPPORT == STD_ON ) */
static VAR( Dem_MisfireCylinderType, DEM_VAR_NO_INIT ) Dem_TmpMisfirePermanent_BeforeAccumPermanentCyl;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Misfire_SavePermanentMemoryEntryToTmp                */
/* Description   | Save the temporary area.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_SavePermanentMemoryEntryToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) misfireEventKind;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
    if( misfireEventKind == (boolean)TRUE )
    {
        Dem_MisfireMng_GetPFCMisfireComRecord( &Dem_TmpMisfirePermanent );
        Dem_TmpMisfirePermanent_BeforeAccumPermanentCyl =   Dem_TmpMisfirePermanent.AccumPermanentCyl;
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_UpdatePermanentMemoryEntryToTmp              */
/* Description   | Update the temporary area.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               |        The event index corresponding to the event ID.    */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]PFCMisfire                                       */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_UpdatePermanentMemoryEntryToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) misfireEventKind;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
    if( misfireEventKind == (boolean)TRUE )
    {
        Dem_MisfireMng_SetPFCMisfireComRecord( &Dem_TmpMisfirePermanent );      /*[UpdRec]PFCMisfire */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_ClearTmpPermanentMemoryEntry                 */
/* Description   | Initializes temporary area.                              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_ClearTmpPermanentMemoryEntry
( void )
{
    /* Initializes the PFCMisfireComRecord. */
    Dem_TmpMisfirePermanent.FirstPermanentCyl = DEM_MISFIRE_CYLINDER_NON;
    Dem_TmpMisfirePermanent.FirstAccumPermanentCyl = DEM_MISFIRE_CYLINDER_NON;
    Dem_TmpMisfirePermanent.AccumPermanentCyl = DEM_MISFIRE_CYLINDER_NON;

    return;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_UpdatePermanentCylToTmp                      */
/* Description   | Update the permanent cylinder of temporary area.         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] MisfireCylinder :                                   */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_UpdatePermanentCylToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
)
{
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) getFirstAccumConfirmedCyl;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) getAccumConfirmedCyl;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
    if( misfireEventKind == (boolean)TRUE )
    {
        /* FirstPermanentCyl */
        if( Dem_TmpMisfirePermanent.FirstPermanentCyl == DEM_MISFIRE_CYLINDER_NON )
        {
            Dem_TmpMisfirePermanent.FirstPermanentCyl = MisfireCylinder;
        }

        /* FirstAccumPermanentCyl */
        if( Dem_TmpMisfirePermanent.FirstAccumPermanentCyl == DEM_MISFIRE_CYLINDER_NON )
        {
            Dem_Misfire_GetFirstAccumConfirmedCylToTmp( &getFirstAccumConfirmedCyl );
            Dem_TmpMisfirePermanent.FirstAccumPermanentCyl = getFirstAccumConfirmedCyl;
        }

        /* AccumPermanentCyl */
        Dem_Misfire_GetAccumConfirmedCylToTmp( EventStrgIndex, &getAccumConfirmedCyl);
        Dem_TmpMisfirePermanent.AccumPermanentCyl = (Dem_MisfireCylinderType)( Dem_TmpMisfirePermanent.AccumPermanentCyl | getAccumConfirmedCyl );
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_UpdateAccumPermanentCylToTmp                 */
/* Description   | Update the accumulation permanent cylinder of temporary. */
/*               | area.                                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireCylinder :                                   */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_UpdateAccumPermanentCylToTmp
(
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
)
{
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) accumPermanentCyl;

    /* Check if misfire event exists in PFC Record. */
    if( Dem_TmpMisfirePermanent.AccumPermanentCyl != DEM_MISFIRE_CYLINDER_NON )
    {
        accumPermanentCyl = Dem_TmpMisfirePermanent.AccumPermanentCyl;
        Dem_TmpMisfirePermanent.AccumPermanentCyl = (Dem_MisfireCylinderType)( accumPermanentCyl | MisfireCylinder );
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_RestoreAccumPermanentCylToTmp                */
/* Description   | Restore the accumulation permanent cylinder of temporary. */
/*               | area.                                                    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_RestoreAccumPermanentCylToTmp
( void )
{
    /*  restore to orginal information.     */
    Dem_TmpMisfirePermanent.AccumPermanentCyl   =   Dem_TmpMisfirePermanent_BeforeAccumPermanentCyl;

    return;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_ClearPermanentCylToTmp                       */
/* Description   | Clear the permanent cylinder of temporary.               */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_ClearPermanentCylToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetPFCRecordIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetMisfirePairEvent;
    VAR( boolean, AUTOMATIC ) clearRecord;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) misfirePairEventStrgIndex;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
    if( misfireEventKind == (boolean)TRUE )
    {
        clearRecord = (boolean)TRUE;

        resultGetMisfirePairEvent = Dem_CfgInfoPm_GetMisfirePairEventStrgIndexByStrgIndex( EventStrgIndex, &misfirePairEventStrgIndex );
        if( resultGetMisfirePairEvent == DEM_IRT_OK )
        {
            /*--------------------------------------*/
            /*  action to misfire pair event.       */
            retGetPFCRecordIndex = Dem_PFCMng_GetPFCRecordIndex( misfirePairEventStrgIndex, &pfcRecordIndex );
            if( retGetPFCRecordIndex == DEM_IRT_OK )
            {
                clearRecord = (boolean)FALSE;
            }
            /*--------------------------------------*/
        }
        if( clearRecord == (boolean)TRUE)
        {
            Dem_Misfire_ClearTmpPermanentMemoryEntry();
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_UpdatePermanentCylByOrder                    */
/* Description   | Update the permanent cylinder.                           */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]PFCMisfire                                       */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_UpdatePermanentCylByOrder
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_MisfireCylinderType, AUTOMATIC )     getAccumConfirmedCyl;
    VAR( Dem_MisfireComRecordType, AUTOMATIC )    misfireComRecord;
    VAR( Dem_PFCMisfireComRecordType, AUTOMATIC ) pfcMisfireComRecord;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );
    if( misfireEventKind == (boolean)TRUE )
    {
        /*  convert id.     */
        retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );

        if ( retCnvId == DEM_IRT_OK )
        {
            Dem_MisfireMng_GetMisfireComRecord( &misfireComRecord );
            Dem_MisfireMng_GetPFCMisfireComRecord( &pfcMisfireComRecord );

            /* FirstPermanentCyl */
            if( pfcMisfireComRecord.FirstPermanentCyl == DEM_MISFIRE_CYLINDER_NON )
            {
                pfcMisfireComRecord.FirstPermanentCyl = misfireComRecord.FirstConfirmedCyl;
            }

            /* FirstAccumPermanentCyl */
            if( pfcMisfireComRecord.FirstAccumPermanentCyl == DEM_MISFIRE_CYLINDER_NON )
            {
                pfcMisfireComRecord.FirstAccumPermanentCyl = misfireComRecord.FirstAccumConfirmedCyl;
            }

            /* AccumPermanentCyl */
            getAccumConfirmedCyl = Dem_MisfireMng_GetAccumConfirmedCyl( misfireIndex );
            pfcMisfireComRecord.AccumPermanentCyl = (Dem_MisfireCylinderType)( pfcMisfireComRecord.AccumPermanentCyl | getAccumConfirmedCyl );

            Dem_MisfireMng_SetPFCMisfireComRecord( &pfcMisfireComRecord );      /*[UpdRec]PFCMisfire */
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_GetPermanentUDSDTC                           */
/* Description   | Get permanentDTC.                                        */
/* Preconditions | none                                                     */
/* Parameters    | [out] PermanentDTCBufferPtr :                            */
/*               |        PermanentDTC                                      */
/*               | [out] PermanentDTCNumPtr :                               */
/*               |        PermanentDTC Num                                  */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_Misfire_GetPermanentOBDDTC.    */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_GetPermanentUDSDTC
(
    P2VAR( uint32, AUTOMATIC, DEM_APPL_DATA ) PermanentDTCBufferPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) PermanentDTCNumPtr
)
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcValue;
    VAR( Dem_PFCMisfireComRecordType, AUTOMATIC ) pfcMisfireComRecord;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) loopCnt;
    VAR( uint8, AUTOMATIC ) permanentDTCCnt;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckResult;

    misfireCylinderNum  = Dem_MisfireCylinderNum;
    permanentDTCCnt     =   (uint8)0U;

    Dem_MisfireMng_GetPFCMisfireComRecord( &pfcMisfireComRecord );
    pfcMisfireComRecord.AccumPermanentCyl = Dem_CfgInfoPm_MergeMultipleCylinderBit( pfcMisfireComRecord.AccumPermanentCyl );
    if( pfcMisfireComRecord.AccumPermanentCyl != DEM_MISFIRE_CYLINDER_NON )
    {
        /* Check misfire event state in PFCRecord. */
        retCheckResult = Dem_Misfire_CheckPFCRecord();
        if( retCheckResult == DEM_IRT_OK )
        {
            for( loopCnt = DEM_MISFIRE_CYL_NUM_RM; loopCnt < misfireCylinderNum; loopCnt++ )    /* [GUD:for] loopCnt */
            {
                if( ( pfcMisfireComRecord.AccumPermanentCyl & (Dem_MisfireCylinderType)(DEM_MISFIRE_CHECK_CYLINDER_BIT << loopCnt) ) != DEM_MISFIRE_CYLINDER_NON )
                {
                    dtcValue = Dem_CfgInfoPm_GetUdsDTCByMisfireCylinderNumber( loopCnt );
                    PermanentDTCBufferPtr[ permanentDTCCnt ]    =   (uint32)dtcValue;           /* [GUD]loopCnt *//* [GUD:SPC:IF_GUARDED: loopCnt ]permanentDTCCnt *//* [ARYCHK] DEM_MAX_NUMBER_EVENT_ENTRY_PERMANENT+DEM_MISFIRE_CYLINDER_NUMBER / 1 / permanentDTCCnt */

                    permanentDTCCnt = permanentDTCCnt + (uint8)1U;
                }
            }
        }
    }

    *PermanentDTCNumPtr =   permanentDTCCnt;
    return;
}

#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_GetPermanentOBDDTC                           */
/* Description   | Get permanentDTC.                                        */
/* Preconditions | none                                                     */
/* Parameters    | [out] PermanentDTCBufferPtr :                            */
/*               |        PermanentDTC                                      */
/*               | [out] PermanentDTCNumPtr :                               */
/*               |        PermanentDTC Num                                  */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | rename from Dem_Misfire_GetPermanentDTC(v5-3-0).         */
/*   v5-5-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_GetPermanentOBDDTC
(
    P2VAR( uint16, AUTOMATIC, DEM_APPL_DATA ) PermanentDTCBufferPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) PermanentDTCNumPtr
)
{
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) dtcValue;
    VAR( Dem_PFCMisfireComRecordType, AUTOMATIC ) pfcMisfireComRecord;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) loopCnt;
    VAR( uint8, AUTOMATIC ) permanentDTCCnt;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckResult;

    misfireCylinderNum = Dem_MisfireCylinderNum;
    permanentDTCCnt     =   (uint8)0U;

    Dem_MisfireMng_GetPFCMisfireComRecord( &pfcMisfireComRecord );
    pfcMisfireComRecord.AccumPermanentCyl = Dem_CfgInfoPm_MergeMultipleCylinderBit( pfcMisfireComRecord.AccumPermanentCyl );
    if( pfcMisfireComRecord.AccumPermanentCyl != DEM_MISFIRE_CYLINDER_NON )
    {
        /* Check misfire event state in PFCRecord. */
        retCheckResult = Dem_Misfire_CheckPFCRecord();
        if( retCheckResult == DEM_IRT_OK )
        {
            for( loopCnt = DEM_MISFIRE_CYL_NUM_RM; loopCnt < misfireCylinderNum; loopCnt++ )
            {
                if( ( pfcMisfireComRecord.AccumPermanentCyl & (Dem_MisfireCylinderType)(DEM_MISFIRE_CHECK_CYLINDER_BIT << loopCnt) ) != DEM_MISFIRE_CYLINDER_NON )
                {
                    dtcValue = Dem_CfgInfoPm_GetOBDDTCByMisfireCylinderNumber( loopCnt );
                    PermanentDTCBufferPtr[ permanentDTCCnt ]    =   (uint16)dtcValue;       /* [GUD]loopCnt *//* [GUD:SPC:IF_GUARDED: loopCnt ]permanentDTCCnt *//* [ARYCHK] DEM_MAX_NUMBER_EVENT_ENTRY_PERMANENT+DEM_MISFIRE_CYLINDER_NUMBER / 1 / permanentDTCCnt */

                    permanentDTCCnt = permanentDTCCnt + (uint8)1U;
                }
            }
        }
    }
    *PermanentDTCNumPtr =   permanentDTCCnt;

    return;
}
#endif  /*   ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )       */

#if ( DEM_PFC_OUTPUT_DEMINTERNALPFC_TODCM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_SetFilteredDTCForPFC                         */
/* Description   | The function set the Misfire DTC filter For PFC.         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_SetFilteredDTCForPFC
( void )
{
    Dem_MisfirePFCSearchCylinderNum = (Dem_MisfireCylinderNumberType)0U;

    return;
}
#endif /* ( DEM_PFC_OUTPUT_DEMINTERNALPFC_TODCM_SUPPORT == STD_ON ) */

#if ( DEM_PFC_OUTPUT_DEMINTERNALPFC_TODCM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_GetFilteredPFC                               */
/* Description   | Gets the next Permanent memory and its DTC status.       */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTCFormat :                                         */
/*               |        DTC Format                                        */
/*               | [out] DTCValuePtr :                                      */
/*               |        OBD DTC Value                                     */
/*               | [out] DTCStatusPtr :                                     */
/*               |        Status Of DTC                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Returned next filtered element       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No further element  */
/*               |         (matching the filter criteria) found             */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_GetFilteredPFC
(
    VAR( Dem_DTCFormatType, AUTOMATIC ) DTCFormat,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_PFCMisfireComRecordType, AUTOMATIC ) pfcMisfireComRecord;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) loopCnt;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckResult;
    VAR( boolean, AUTOMATIC ) retDTCClerTarget;

    retVal = DEM_IRT_NO_MATCHING_ELEMENT;

    SchM_Enter_Dem_PermanentMemory();   /* waits completion of updating Diag record data by Dem_MainFunction.      */
    SchM_Exit_Dem_PermanentMemory();

    misfireCylinderNum = Dem_MisfireCylinderNum;

    if( Dem_MisfirePFCSearchCylinderNum < misfireCylinderNum )
    {
        Dem_MisfireMng_GetPFCMisfireComRecord( &pfcMisfireComRecord );
        pfcMisfireComRecord.AccumPermanentCyl = Dem_CfgInfoPm_MergeMultipleCylinderBit( pfcMisfireComRecord.AccumPermanentCyl );
        if( pfcMisfireComRecord.AccumPermanentCyl != DEM_MISFIRE_CYLINDER_NON )
        {
            /* Check misfire event state in PFCRecord. */
            retCheckResult = Dem_Misfire_CheckPFCRecord();
            if( retCheckResult == DEM_IRT_OK )
            {
                for( loopCnt = Dem_MisfirePFCSearchCylinderNum; loopCnt < misfireCylinderNum; loopCnt++ )
                {
                    if( ( pfcMisfireComRecord.AccumPermanentCyl & (Dem_MisfireCylinderType)(DEM_MISFIRE_CHECK_CYLINDER_BIT << loopCnt) ) != DEM_MISFIRE_CYLINDER_NON )
                    {
                        if( DTCFormat == DEM_DTC_FORMAT_UDS )
                        {
                            /* set UDS DTC value for SID19-55 */
                            *DTCValuePtr = Dem_CfgInfoPm_GetUdsDTCByMisfireCylinderNumber( loopCnt );

                            retDTCClerTarget = Dem_Misfire_JudgeDTCClearTarget();
                            if( retDTCClerTarget == (boolean)FALSE )
                            {
                                SchM_Enter_Dem_EventMemory();   /* waits completion of updating Diag record data by Dem_MainFunction.      */
                                SchM_Exit_Dem_EventMemory();

                                (*DTCStatusPtr) = Dem_Misfire_GetCylinderDTCStatus( loopCnt );
                            }
                            else
                            {
                                (*DTCStatusPtr) = DEM_DTCSTATUS_BYTE_DEFAULT;
                            }
                        }
#if ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )    /*  [FuncSw]    */
                        else if ( DTCFormat == DEM_DTC_FORMAT_OBD )
                        {
                            /* set OBD DTC value for SID0A */
                            *DTCValuePtr    =   Dem_CfgInfoPm_GetOBDDTCByMisfireCylinderNumber( loopCnt );

                            (*DTCStatusPtr) = DEM_DTCSTATUS_BYTE_DEFAULT;
                        }
#endif  /* ( DEM_OBDDTC_FORMAT_SUPPORT == STD_ON )             */
                        else
                        {
                            /*  no match format.    */
                        }

                        Dem_MisfirePFCSearchCylinderNum = loopCnt + (Dem_MisfireCylinderNumberType)1U;
                        retVal = DEM_IRT_OK;
                        break;
                    }
                }
            }
        }

        if( retVal != DEM_IRT_OK )
        {
            Dem_MisfirePFCSearchCylinderNum = misfireCylinderNum;
        }
    }

    return retVal;
}
#endif /* ( DEM_PFC_OUTPUT_DEMINTERNALPFC_TODCM_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_Misfire_CheckPFCRecord                               */
/* Description   | Check misfire event available and MIL status in PFCRecord. */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Check result is OK.                  */
/*               |        DEM_IRT_NG : Check result is NG.                  */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Misfire_CheckPFCRecord
( void )
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) loopCnt;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( boolean, AUTOMATIC ) misfireEventKind;

    retVal = DEM_IRT_NG;
    pfcRecordNum = Dem_PFCRecordNum;

    for( loopCnt = (Dem_u08_PFCIndexType)0U; loopCnt < pfcRecordNum; loopCnt++ )    /* [GUD:for]loopCnt */
    {
        /* Get event index in PFCRecord */
        (void)Dem_PFCMng_GetPFCRecordData( loopCnt, &eventStrgIndex );    /* no return check required */ /* [GUD]loopCnt */

        /*  check MISFIRE eventStrgIndex.       */
        misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( eventStrgIndex );    /* [GUD]eventStrgIndex */
        if( misfireEventKind == (boolean)TRUE )
        {
            /* Check event available status and MIL indicator */
            retVal = Dem_DTC_CheckAvailableAndMILStatusByEventStrgIndex( eventStrgIndex );  /* [GUD]eventStrgIndex */
            if( retVal == DEM_IRT_OK )
            {
                /* Emmision or CAT is available. */
                break;
            }
        }
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_PFC_SUPPORT == STD_ON ) */

#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
