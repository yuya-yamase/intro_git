/* Dem_DTC_PFC_Misfire_c(v5-5-0)                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DTC_PFC_Misfire/CODE                                  */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "Dem_DTC_PFC_local.h"

#if ( DEM_PFC_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include "../../../../inc/Dem_Pm_DTC_PFC.h"
#include "../../../../inc/Dem_Pm_Misfire.h"
#include "../../../../inc/Dem_Rc_MisfireMng.h"
#include "../../../../inc/Dem_Rc_PFCMng.h"
#include "../../../../inc/Dem_Rc_DataMng.h"
#include "../../../../cfg/Dem_Misfire_Cfg.h"
#include "../../../../inc/Dem_Pm_DataCtl_OBD.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../usr/Dem_PFC_Callout.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
#define DEM_PFC_STORED_MISFIRE_EVENT ((boolean)TRUE)
#define DEM_PFC_NOT_STORED_MISFIRE_EVENT ((boolean)FALSE)
#endif  /*  ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  */

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
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetNextSpacePFCRecordIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC) EventStrgIndex,
    VAR( Dem_u08_PFCIndexType, AUTOMATIC) EmptyPFCRecordIndex,
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) EmptyPFCRecordSpaceNum,
    VAR( boolean, AUTOMATIC ) StoredMisfireEventState,
    P2VAR( Dem_u08_PFCIndexType, AUTOMATIC, AUTOMATIC ) PFCRecordIndexPtr
);
#endif  /*  ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  */

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

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_PFC_GetNextSpacePFCRecordIndex                       */
/* Description   | Get next space pfc record index.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] BasePFCRecordIndex :                                */
/*               | [out] PFCRecordIndexPtr :                                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK :                                      */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT :                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_PFC_GetNextSpacePFCRecordIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC) EventStrgIndex,
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) BasePFCRecordIndex, /* MISRA DEVIATION */
    P2VAR( Dem_u08_PFCIndexType, AUTOMATIC, AUTOMATIC ) PFCRecordIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckResult;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) emptyPFCRecordSpaceNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retDTCGetNextSpacePFCRecordIndex;
    VAR( boolean, AUTOMATIC ) storedMisfireEventState;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) loopCnt;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) maxNumberEventEntryPermanent;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) emptyPFCRecordIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC) eventStrgIndexPFC;
    VAR( boolean, AUTOMATIC ) misfireEventKind;

    retVal = DEM_IRT_NO_MATCHING_ELEMENT;
    maxNumberEventEntryPermanent = Dem_MaxNumberEventEntryPermanent;
    emptyPFCRecordSpaceNum = (Dem_u08_PFCIndexType)0U;
    emptyPFCRecordIndex = DEM_PFC_RECORD_INDEX_INITIAL;
    storedMisfireEventState = DEM_PFC_NOT_STORED_MISFIRE_EVENT;

    for( loopCnt = (Dem_u08_PFCIndexType)0U; loopCnt < maxNumberEventEntryPermanent; loopCnt++ )    /* [GUD:for]loopCnt */
    {
        /* Get event index in PFCRecord */
        (void)Dem_PFCMng_GetPFCRecordData( loopCnt, &eventStrgIndexPFC );    /* no return check required */ /* [GUD:]loopCnt */

        /* Check event available status, MIL indicator and OBD. */
        retCheckResult = Dem_DTC_CheckAvailableAndMILStatusByEventStrgIndex( eventStrgIndexPFC );          /* [GUD]eventStrgIndexPFC */
        if( retCheckResult == DEM_IRT_OK )
        {
            /*  check MISFIRE eventStrgIndex.       */
            misfireEventKind    =   Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( eventStrgIndexPFC );
            if( misfireEventKind == (boolean)TRUE )
            {
                storedMisfireEventState = DEM_PFC_STORED_MISFIRE_EVENT;
            }
        }
        else
        {
            if( emptyPFCRecordIndex == DEM_PFC_RECORD_INDEX_INITIAL )
            {
                emptyPFCRecordIndex = loopCnt;
            }
            emptyPFCRecordSpaceNum = emptyPFCRecordSpaceNum + (Dem_u08_PFCIndexType)1U;
        }
    }

    retDTCGetNextSpacePFCRecordIndex = Dem_DTC_GetNextSpacePFCRecordIndex( EventStrgIndex, emptyPFCRecordIndex, emptyPFCRecordSpaceNum, storedMisfireEventState, PFCRecordIndexPtr );

    if( retDTCGetNextSpacePFCRecordIndex == DEM_IRT_OK )
    {
        retVal = DEM_IRT_OK;
    }
    return retVal;

}


/****************************************************************************/
/* Function Name | Dem_DTC_GetNextSpacePFCRecordIndex                       */
/* Description   | Get next space pfc record index.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] EmptyPFCRecordIndex :                               */
/*               | [in] EmptyPFCRecordSpaceNum :                            */
/*               | [in] StoredMisfireEventState :                           */
/*               | [out] PFCRecordIndexPtr :                                */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_GetNextSpacePFCRecordIndex
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC) EventStrgIndex,
    VAR( Dem_u08_PFCIndexType, AUTOMATIC) EmptyPFCRecordIndex,
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) EmptyPFCRecordSpaceNum,
    VAR( boolean, AUTOMATIC ) StoredMisfireEventState,
    P2VAR( Dem_u08_PFCIndexType, AUTOMATIC, AUTOMATIC ) PFCRecordIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckResult;
    VAR( boolean, AUTOMATIC ) misfireEventKind;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) storedMisFirePFCMisFireEventStrgIndex;

    retVal = DEM_IRT_NO_MATCHING_ELEMENT;
    storedMisFirePFCMisFireEventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;

    misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( EventStrgIndex );

    if( EmptyPFCRecordIndex != DEM_PFC_RECORD_INDEX_INITIAL )
    {
        if( misfireEventKind == (boolean)TRUE )
        {
            if( StoredMisfireEventState == DEM_PFC_NOT_STORED_MISFIRE_EVENT )
            {
                *PFCRecordIndexPtr = EmptyPFCRecordIndex;
            }
            else
            {
                *PFCRecordIndexPtr = DEM_MISFIRE_PFC_RECORD_INDEX;
            }
            retVal = DEM_IRT_OK;
        }
        else
        {
            if( EmptyPFCRecordSpaceNum >= DEM_PFC_RECORD_ENOUGH_EMPTY_SPACE_NUM )
            {
                *PFCRecordIndexPtr = EmptyPFCRecordIndex;
                retVal = DEM_IRT_OK;
            }
            else
            {
                /* Check event available status, MIL indicator and OBD. */
                retCheckResult = Dem_PFCMng_GetStoredMisfireSpaceEventStrgIndex( &storedMisFirePFCMisFireEventStrgIndex );
                if( retCheckResult == DEM_IRT_OK )
                {
                    if( StoredMisfireEventState == DEM_PFC_STORED_MISFIRE_EVENT )
                    {
                        *PFCRecordIndexPtr = EmptyPFCRecordIndex;
                        retVal = DEM_IRT_OK;
                    }
                }
                else
                {
                    *PFCRecordIndexPtr = EmptyPFCRecordIndex;
                    retVal = DEM_IRT_OK;
                }
            }
        }
    }
    else
    {
        if( misfireEventKind == (boolean)TRUE )
        {
            if( StoredMisfireEventState == DEM_PFC_STORED_MISFIRE_EVENT )
            {
                *PFCRecordIndexPtr = DEM_MISFIRE_PFC_RECORD_INDEX;
                retVal = DEM_IRT_OK;
            }
        }
    }
    return retVal;
}
#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
#endif /* ( DEM_PFC_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
