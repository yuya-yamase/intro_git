/* Dem_Misfire_EventEntryMake_CylinderStatus_c(v5-5-0)                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Misfire_EventEntryMake_CylinderStatus/CODE            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../inc/Dem_Rc_MisfireMng.h"
#include "Dem_Misfire_EventEntry_local.h"
#include "Dem_Misfire_local.h"

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

static FUNC( void, DEM_CODE ) Dem_Misfire_RestoreFailedCylSinceClearToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
static FUNC( void, DEM_CODE ) Dem_Misfire_RestorePendingCylinderToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);
static FUNC( void, DEM_CODE ) Dem_Misfire_RestoreConfirmedCylinderToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
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
/* Function Name | Dem_Misfire_ClearFailedCylToTmp                          */
/* Description   | Clear FailedCyl in the temporary area.                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_ClearFailedCylToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;

    /*  convert id.     */
    retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );     /* [GUD:RET:DEM_IRT_OK] misfireIndex */

    if ( retCnvId == DEM_IRT_OK )
    {
        Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].FailedCyl = DEM_MISFIRE_CYLINDER_NON;  /* [GUD] misfireIndex */
    }
    return;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_ClearAccumCylToTmp                           */
/* Description   | Clear AccumCyl in the temporary area.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireIndex :                                      */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_ClearAccumCylToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;

    /*  convert id.     */
    retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );     /* [GUD:RET:DEM_IRT_OK] misfireIndex */

    if ( retCnvId == DEM_IRT_OK )
    {
        Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].AccumCyl = DEM_MISFIRE_CYLINDER_NON;   /* [GUD] misfireIndex */
    }
    return;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_ClearAccumFailedCylThisOCToTmp               */
/* Description   | Clear AccumFailedCylThisOC in the temporary area.        */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_ClearAccumFailedCylThisOCToTmp
( void )
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireEventNum;

    misfireEventNum = Dem_MisfireEventNum;

    for( misfireIndex = (Dem_u16_MisfireStrgIndexType)0U; misfireIndex < misfireEventNum; misfireIndex++ )                      /* [GUD:for] misfireIndex */
    {
        Dem_TmpMisfireEventMemoryEntry.MisfireRecord[misfireIndex].AccumFailedCylThisOC          = DEM_MISFIRE_CYLINDER_NON;    /* [GUD] misfireIndex */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_ClearAccumPendingCylToTmp                    */
/* Description   | Clear AccumPendingCyl in the temporary area.             */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_ClearAccumPendingCylToTmp
(void)
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireEventNum;

    misfireEventNum = Dem_MisfireEventNum;

    for( misfireIndex = (Dem_u16_MisfireStrgIndexType)0U; misfireIndex < misfireEventNum; misfireIndex++ )      /* [GUD:for] misfireIndex */
    {
        Dem_TmpMisfireEventMemoryEntry.MisfireRecord[misfireIndex].AccumPendingCyl = DEM_MISFIRE_CYLINDER_NON;  /* [GUD] misfireIndex */
    }

    return;
}

#if ( DEM_PFC_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Misfire_GetFirstAccumConfirmedCylToTmp               */
/* Description   | Get FirstAccumConfirmedCyl in the temporary area.        */
/* Preconditions | none                                                     */
/* Parameters    | [out] FirstAccumConfirmedCylPtr :                        */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_GetFirstAccumConfirmedCylToTmp
(
    P2VAR( Dem_MisfireCylinderType, AUTOMATIC, AUTOMATIC ) FirstAccumConfirmedCylPtr
)
{
    *FirstAccumConfirmedCylPtr = Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.FirstAccumConfirmedCyl;
    return;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_GetAccumConfirmedCyllToTmp                   */
/* Description   | Get AccumConfirmedCyl in the temporary area.             */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [out] AccumConfirmedCylPtr :                             */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_GetAccumConfirmedCylToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    P2VAR( Dem_MisfireCylinderType, AUTOMATIC, AUTOMATIC ) AccumConfirmedCylPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;

    /*  convert id.     */
    retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );     /* [GUD:RET:DEM_IRT_OK] misfireIndex */

    if ( retCnvId == DEM_IRT_OK )
    {
        *AccumConfirmedCylPtr = Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].AccumConfirmedCyl; /* [GUD] misfireIndex */
    }
    return;
}
#endif /* ( DEM_PFC_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_Misfire_ClearAccumConfirmedCylToTmp_AtAging          */
/* Description   | Set AccumConfirmedCyl in the temporary area.             */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_ClearAccumConfirmedCylToTmp_AtAging
( void )
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireEventNum;
    VAR( Dem_u08_DTCStatusBitHandlingType, AUTOMATIC ) resetTestFailedSinceLastClearBit;

    misfireEventNum = Dem_MisfireEventNum;

    resetTestFailedSinceLastClearBit    =   Dem_StatusBitHandlingTestFailedSinceLastClear;

    for( misfireIndex = (Dem_u16_MisfireStrgIndexType)0U; misfireIndex < misfireEventNum; misfireIndex++ )          /* [GUD:for] misfireIndex */
    {
        Dem_TmpMisfireEventMemoryEntry.MisfireRecord[misfireIndex].AccumConfirmedCyl = DEM_MISFIRE_CYLINDER_NON;    /* [GUD] misfireIndex */

        if ( resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT )
        {
            /*------------------------------------------------------------------------------*/
            /*  bit5 OFF at Aging.                                                          */
            /*------------------------------------------------------------------------------*/
            /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT   */
            /*------------------------------------------------------------------------------*/
            Dem_TmpMisfireEventMemoryEntry.MisfireRecord[misfireIndex].AccumFailedCylSinceClear = DEM_MISFIRE_CYLINDER_NON; /* [GUD] misfireIndex */
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_SetFFDAccumCylinder                          */
/* Description   | Set the Accumulated Cylinder for each trigger of FFD.    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] FreezeFrameRecordTrigger :                          */
/*               | [in] MisfireCylinder :                                   */
/* Return Value  | Dem_MisfireCylinderType :                                */
/*               |      MisfireCylinder with accumulated cylinder set       */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_Misfire_SetFFDAccumCylinder
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_u08_StorageTriggerType, AUTOMATIC ) FreezeFrameRecordTrigger,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
)
{
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) retCylinder;
    VAR( Dem_u08_MisfJudgeFFCylinderType, AUTOMATIC ) misfJudgeFFCylinder;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;

    retCylinder = MisfireCylinder;
    /*  convert id.     */
    retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );     /* [GUD:RET:DEM_IRT_OK] misfireIndex */

    if ( retCnvId == DEM_IRT_OK )
    {
        misfJudgeFFCylinder = Dem_MisfireJudgeFreezeFrameCylinder;
        if( misfJudgeFFCylinder == DEM_MF_JUDGE_FFD_CYL_ACCUMULATED )
        {
            switch( FreezeFrameRecordTrigger )
            {
                case DEM_TRIGGER_ON_CONFIRMED:
                    retCylinder = retCylinder | (Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].AccumConfirmedCyl);   /* [GUD] misfireIndex */
                    break;
                case DEM_TRIGGER_ON_PENDING:
                    retCylinder = retCylinder | (Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].AccumPendingCyl);     /* [GUD] misfireIndex */
                    break;
                default:
                    /* No Process */
                    break;
            }
        }
    }

    return retCylinder;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_SetFirstPendingCylToTmp                      */
/* Description   | Set FirstPendingCyl in the temporary area.               */
/* Preconditions | none                                                     */
/* Parameters    | [in] FirstPendingCyl :                                   */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_SetFirstPendingCylToTmp
(
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) FirstPendingCyl
)
{
    Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.FirstPendingCyl = FirstPendingCyl;
    return;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_SetFirstConfirmedCylToTmp                    */
/* Description   | Set FirstConfirmedCyl in the temporary area.             */
/* Preconditions | none                                                     */
/* Parameters    | [in] FirstConfirmedCyl :                                 */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_SetFirstConfirmedCylToTmp
(
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) FirstConfirmedCyl
)
{
    Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.FirstConfirmedCyl = FirstConfirmedCyl;
    return;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_SetFirstAccumConfirmedCylToTmp               */
/* Description   | Set FirstAccumConfirmedCyl in the temporary area.        */
/* Preconditions | none                                                     */
/* Parameters    | [in] FirstAccumConfirmedCyl :                            */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_SetFirstAccumConfirmedCylToTmp
(
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) FirstAccumConfirmedCyl
)
{
    Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.FirstAccumConfirmedCyl = FirstAccumConfirmedCyl;
    return;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_UpdateFailedCylToTmp                         */
/* Description   | Set the failed cylinder related.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] MisfireCylinder :                                   */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_UpdateFailedCylToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
)
{
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) failedCyl;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) accumCyl;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) accumFailedCylThisOC;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) accumFailedCylSinceClear;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) accumTestNotCompleteCylSinceClear;
    VAR( boolean, AUTOMATIC ) misfireAccumulateFailedCylinder;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;

    /*  convert id.     */
    retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );     /* [GUD:RET:DEM_IRT_OK] misfireIndex */

    if ( retCnvId == DEM_IRT_OK )
    {
        /* FailedCyl */
        misfireAccumulateFailedCylinder = Dem_MisfireAccumulateFailedCylinder;
        if( misfireAccumulateFailedCylinder == (boolean)TRUE )
        {
            failedCyl = Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].FailedCyl;                                                 /* [GUD] misfireIndex */
            Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].FailedCyl = (Dem_MisfireCylinderType)( failedCyl | MisfireCylinder );  /* [GUD] misfireIndex */
        }
        else
        {
            Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].FailedCyl = MisfireCylinder;                                           /* [GUD] misfireIndex */
        }

        /* AccumCyl */
        accumCyl = Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].AccumCyl;                                                       /* [GUD] misfireIndex */
        Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].AccumCyl = (Dem_MisfireCylinderType)( accumCyl | MisfireCylinder );        /* [GUD] misfireIndex */

        /* AccumFailedCylThisOC */
        accumFailedCylThisOC = Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].AccumFailedCylThisOC;                               /* [GUD] misfireIndex */
        Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].AccumFailedCylThisOC = (Dem_MisfireCylinderType)( accumFailedCylThisOC | MisfireCylinder );    /* [GUD] misfireIndex */

        /* AccumFailedCylSinceClear */
        accumFailedCylSinceClear = Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].AccumFailedCylSinceClear;                       /* [GUD] misfireIndex */
        Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].AccumFailedCylSinceClear = (Dem_MisfireCylinderType)( accumFailedCylSinceClear | MisfireCylinder );    /* [GUD] misfireIndex */

        /* AccumTestNotCompleteCylSinceClear */
        accumTestNotCompleteCylSinceClear = Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].AccumTestNotCompleteCylSinceClear;     /* [GUD] misfireIndex */
        Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].AccumTestNotCompleteCylSinceClear = (Dem_MisfireCylinderType)( accumTestNotCompleteCylSinceClear | MisfireCylinder );  /* [GUD] misfireIndex */

    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_UpdateFailedCylToTmp                         */
/* Description   | Set the failed cylinder related.                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Misfire_RestoreFailedCylSinceClearToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;

    /*  convert id.     */
    retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );     /* [GUD:RET:DEM_IRT_OK] misfireIndex */

    if ( retCnvId == DEM_IRT_OK )
    {
        /*  restore information     */
        Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].AccumFailedCylSinceClear   =   Dem_TmpMisfireEventMemoryEntry.MisfireRecordBeforeAccumFailedCylSinceClear; /* [GUD] misfireIndex */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_UpdatePendingCylinderToTmp                   */
/* Description   | Update the pending cylinder related.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] MisfireCylinder :                                   */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_UpdatePendingCylinderToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
)
{
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) accumPendingCyl;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;

    /*  convert id.     */
    retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );     /* [GUD:RET:DEM_IRT_OK] misfireIndex */

    if ( retCnvId == DEM_IRT_OK )
    {
        /* FirstPendingCyl */
        if( Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.FirstPendingCyl == DEM_MISFIRE_CYLINDER_NON )
        {
            Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.FirstPendingCyl =  MisfireCylinder;
        }

        /* AccumPendingCyl */
        accumPendingCyl =  Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].AccumPendingCyl;    /* [GUD] misfireIndex */
        Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].AccumPendingCyl = (Dem_MisfireCylinderType)( accumPendingCyl | MisfireCylinder );  /* [GUD] misfireIndex */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_Misfire_RestorePendingCylinderToTmp                  */
/* Description   | Restore the pending cylinder related.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Misfire_RestorePendingCylinderToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;

    /*  convert id.     */
    retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );     /* [GUD:RET:DEM_IRT_OK] misfireIndex */

    if ( retCnvId == DEM_IRT_OK )
    {
        /*  restore to orginal information.     */
        Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.FirstPendingCyl                 =   Dem_TmpMisfireEventMemoryEntry.MisfireRecordBeforeAccumPendingCyl;
        Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].AccumPendingCyl    =   Dem_TmpMisfireEventMemoryEntry.MisfireComBeforeFirstPendingCyl;     /* [GUD] misfireIndex */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_UpdateConfirmedCylinderToTmp                 */
/* Description   | Update the confirmed cylinder related.                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/*               | [in] MisfireCylinder :                                   */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_UpdateConfirmedCylinderToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex,
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) MisfireCylinder
)
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndexLoop;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireEventNum;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) accumPendingCyl;
    VAR( Dem_MisfireCylinderType, AUTOMATIC ) accumConfirmedCyl;
    VAR( boolean, AUTOMATIC ) misfireAccumulateBeforeConfirmed;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availCheck;
    VAR( Dem_u08_MisfireKindBitType, AUTOMATIC ) availableMisfireKind;

    /*  convert id.     */
    retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );     /* [GUD:RET:DEM_IRT_OK] misfireIndex */

    if ( retCnvId == DEM_IRT_OK )
    {
        /* FirstConfirmedCyl */
        if( Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.FirstConfirmedCyl == DEM_MISFIRE_CYLINDER_NON )
        {
            Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.FirstConfirmedCyl =  MisfireCylinder;
        }

        /* FirstAccumConfirmedCyl */
        if( Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.FirstAccumConfirmedCyl == DEM_MISFIRE_CYLINDER_NON )
        {
            /* AccumPendingCyl contains the notified cylinder. */
            accumPendingCyl = Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].AccumPendingCyl;     /* [GUD] misfireIndex */
            Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.FirstAccumConfirmedCyl = accumPendingCyl;
        }

        /* AccumConfirmedCyl */
        accumConfirmedCyl = Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].AccumConfirmedCyl;     /* [GUD] misfireIndex */

        misfireAccumulateBeforeConfirmed = Dem_MisfireAccumulateBeforeConfirmed;
        if( misfireAccumulateBeforeConfirmed == (boolean)TRUE )
        {
            if( accumConfirmedCyl == DEM_MISFIRE_CYLINDER_NON )
            {
                misfireEventNum = Dem_MisfireEventNum;

                /*----------------------------------------------------------------------------------*/
                /*  xx Available check. xxx                                                         */
                /*  DEM_MISFIRE_KINDBIT_FIRST : search start bit.(== DEM_MISFIRE_KINDBIT_EMISSION)  */
                /*      misfireIndex == 0U : DEM_MISFIRE_KINDBIT_EMISSION(0x01)                     */
                /*      misfireIndex == 1U : DEM_MISFIRE_KINDBIT_CAT     (0x02)                     */
                /*  so, check bit(availCheck) is left shifted.                                      */
                /*----------------------------------------------------------------------------------*/
                availableMisfireKind    =   Dem_DataAvl_GetMisfireCylDTCAvailable();
                availCheck              =   DEM_MISFIRE_KINDBIT_FIRST;
                for( misfireIndexLoop = (Dem_u16_MisfireStrgIndexType)0U; misfireIndexLoop < misfireEventNum; misfireIndexLoop++ )          /* [GUD:for] misfireIndexLoop */
                {
                    if (( availCheck & availableMisfireKind ) == availCheck )
                    {
                        accumConfirmedCyl = accumConfirmedCyl | Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndexLoop ].AccumCyl;  /* [GUD] misfireIndexLoop */
                    }
                    availCheck  =   availCheck << (Dem_u08_MisfireKindBitType)1U;
                }
            }
        }
        Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].AccumConfirmedCyl = (Dem_MisfireCylinderType)( accumConfirmedCyl | MisfireCylinder );  /* [GUD] misfireIndex */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_RestoreConfirmedCylinderToTmp                */
/* Description   | Restore the confirmed cylinder related.                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_Misfire_RestoreConfirmedCylinderToTmp
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCnvId;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;

    /*  convert id.     */
    retCnvId    =   Dem_CfgInfoPm_CnvEventStrgIndexToMisfireStrgIndex( EventStrgIndex, &misfireIndex );     /* [GUD:RET:DEM_IRT_OK] misfireIndex */

    if ( retCnvId == DEM_IRT_OK )
    {
        /*  restore to orginal information.     */
        Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.FirstConfirmedCyl               =   Dem_TmpMisfireEventMemoryEntry.MisfireComBeforeFirstConfirmedCyl;
        Dem_TmpMisfireEventMemoryEntry.MisfireComRecord.FirstAccumConfirmedCyl          =   Dem_TmpMisfireEventMemoryEntry.MisfireComBeforeFirstAccumConfirmedCyl;
        Dem_TmpMisfireEventMemoryEntry.MisfireRecord[ misfireIndex ].AccumConfirmedCyl  =   Dem_TmpMisfireEventMemoryEntry.MisfireRecordBeforeAccumConfirmedCyl;    /* [GUD] misfireIndex */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_Misfire_RestoreCylinderToTmp_OnOverflow              */
/* Description   | Restore the pending cylinder related.                    */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventStrgIndex :                                    */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Misfire_RestoreCylinderToTmp_OnOverflow
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( Dem_u08_ResetConfirmedBitOnOverflowType, AUTOMATIC ) resetConfirmedBitOnOverflow;
    VAR( Dem_u08_DTCStatusBitHandlingType, AUTOMATIC ) resetTestFailedSinceLastClearBit;

    /*  get configure value.            */
    resetConfirmedBitOnOverflow =   Dem_ResetConfirmedBitOnOverflow;

    if( resetConfirmedBitOnOverflow == DEM_STATUS_BIT_RESET_CDTC_WITH_PDTC )
    {
        /*------------------------------------------------------------------------------------------*/
        /*  resetConfirmedBitOnOverflow == DEM_STATUS_BIT_RESET_CDTC_WITH_PDTC : reset bit 2/3/7    */
        /*------------------------------------------------------------------------------------------*/
        Dem_Misfire_RestorePendingCylinderToTmp( EventStrgIndex );

        Dem_Misfire_RestoreConfirmedCylinderToTmp( EventStrgIndex );
#if ( DEM_PFC_SUPPORT == STD_ON )   /*  [FuncSw]    */
        Dem_Misfire_RestoreAccumPermanentCylToTmp();
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )          */

        resetTestFailedSinceLastClearBit    =   Dem_StatusBitHandlingTestFailedSinceLastClear;
        if ( resetTestFailedSinceLastClearBit != DEM_STATUS_BIT_NORMAL )
        {
            /*------------------------------------------------------------------------------*/
            /*  bit5 OFF on Overflow.                                                       */
            /*------------------------------------------------------------------------------*/
            /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_AGING_AND_DISPLACEMENT   */
            /*  resetTestFailedSinceLastClearBit == DEM_STATUS_BIT_DISPLACEMENT             */
            /*------------------------------------------------------------------------------*/
            Dem_Misfire_RestoreFailedCylSinceClearToTmp( EventStrgIndex );
        }
    }
    else
    {
        /*-----------------------------------------------------------------------------------*/
        /*  resetConfirmedBitOnOverflow == DEM_STATUS_BIT_NO_RESET                           */
        /*-----------------------------------------------------------------------------------*/
        /*  no process.     */
    }
    return;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

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
