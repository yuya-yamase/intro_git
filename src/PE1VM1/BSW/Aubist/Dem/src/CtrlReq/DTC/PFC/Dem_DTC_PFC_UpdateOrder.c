/* Dem_DTC_PFC_UpdateOrder_c(v5-6-0)                                        */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DTC_PFC_UpdateOrder/CODE                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_PFC_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_OFF )

#include "../../../../cfg/Dem_Cfg.h"
#include "../../../../inc/Dem_Rc_PFCMng.h"
#include "../../../../inc/Dem_Pm_DTC_PFC.h"
#include "../../../../inc/Dem_Pm_Misfire.h"
#include "Dem_DTC_PFC_local.h"


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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_SearchPFCUpdateTarget
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) OrderListIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_DTC_SearchPFCUpdateTarget                            */
/* Description   | Main process to search update target that unstored       */
/*               | memory for PFC.                                          */
/* Preconditions | none                                                     */
/* Parameters    | [in] OrderListIndex :                                    */
/*               |        Order List Index.                                 */
/*               | [out] EventStrgIndexPtr :                                */
/*               |        Get Update taget Index.                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Target matched.                      */
/*               |        DEM_IRT_NG : Target did not match.                */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTC_SearchPFCUpdateTarget
(
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) OrderListIndex,
    P2VAR( Dem_u16_EventStrgIndexType, AUTOMATIC, AUTOMATIC ) EventStrgIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckResult;
    VAR( boolean, AUTOMATIC ) retPFCRegist;
    VAR( boolean, AUTOMATIC ) OrderExistFlag;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_UdsStatusByteType, AUTOMATIC ) statusOfDTC;
    VAR( Dem_u08_FaultIndexType, AUTOMATIC ) faultIndex;

    retVal = DEM_IRT_NG;
    eventStrgIndex  = DEM_EVENTSTRGINDEX_INVALID;
    statusOfDTC = DEM_DTCSTATUS_BYTE_ALL_OFF;

    Dem_DTC_GetUpdateOrderEventStrgIndex( OrderListIndex, &eventStrgIndex, &faultIndex, &statusOfDTC, &OrderExistFlag );
    if( OrderExistFlag != (boolean)FALSE )
    {
        /* Check event available status, MIL indicator and OBD. */
        retCheckResult = Dem_DTC_CheckAvailableAndMILStatusByEventStrgIndex( eventStrgIndex );  /* [GUD:RET:DEM_IRT_OK]eventStrgIndex */
        if( retCheckResult == DEM_IRT_OK )
        {
            retPFCRegist    =   Dem_DTC_CheckRegistPFCRecord( eventStrgIndex );
            if( retPFCRegist == (boolean)TRUE )
            {
                *EventStrgIndexPtr = eventStrgIndex;
                retVal = DEM_IRT_OK;
            }
        }
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTC_UpdatePFCRecordByOrder                           */
/* Description   | Update Permanent memory record process.                  */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]PFC                                              */
/* UpdateRecord  | [UpdRec]PFCMisfire                                       */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTC_UpdatePFCRecordByOrder
( void )
{
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) pfcRecordIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetNextPFCRecordIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retSearchPFCUpdateTarget;
    VAR( Dem_u08_PFCIndexType, AUTOMATIC ) spacePFCRecordIndex;
    VAR( boolean, AUTOMATIC ) nextSearchFlag;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndex;
    VAR( Dem_u08_OrderIndexType, AUTOMATIC ) orderListIndexMax;

    nextSearchFlag = (boolean)TRUE;
    pfcRecordIndex = DEM_PFC_RECORD_INDEX_INITIAL;
    spacePFCRecordIndex = DEM_PFC_RECORD_INDEX_INITIAL;
    eventStrgIndex = DEM_EVENTSTRGINDEX_INVALID;
    retGetNextPFCRecordIndex    =   DEM_IRT_NG;

    /* Gets the event memory record of primary memory. */
    orderListIndexMax   =   Dem_DTC_GetUpdateOrderMaxCount();
    for( orderListIndex = (Dem_u08_OrderIndexType)0U; orderListIndex < orderListIndexMax; orderListIndex++ )
    {
        if( nextSearchFlag == (boolean)TRUE )
        {
            /* Obtain PFCRecord Index of the next Empty PFCRecord Index */
            retGetNextPFCRecordIndex = Dem_PFCMng_GetNextSpacePFCRecordIndex( spacePFCRecordIndex, &pfcRecordIndex );
            spacePFCRecordIndex = pfcRecordIndex;
        }
        else
        {
            /* No Process */
        }
        if( retGetNextPFCRecordIndex == DEM_IRT_OK )
        {
            retSearchPFCUpdateTarget = Dem_DTC_SearchPFCUpdateTarget( orderListIndex, &eventStrgIndex );
            if( retSearchPFCUpdateTarget == DEM_IRT_OK )
            {
                /* Set the PFCrecord. */
                Dem_DTC_SetPFCRecordWithClearCondition( pfcRecordIndex, eventStrgIndex );   /*[UpdRec]PFC */
                nextSearchFlag = (boolean)TRUE;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                Dem_Misfire_UpdatePermanentCylByOrder( eventStrgIndex );        /*[UpdRec]PFCMisfire */
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
            }
            else
            {
                nextSearchFlag = (boolean)FALSE;
            }
        }
        else
        {
            /* No Empty PFCRecord Index */
            break;
        }
    }
    return;
}
#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_OFF ) */
#endif  /* ( DEM_PFC_SUPPORT == STD_OFF )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
