/* Dem_SimilarMng_c(v5-9-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/SimilarMng/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../../cfg/Dem_Cfg.h"

#if ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )
#include "../../../../cfg/Dem_Similar_Cfg.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "../../../../inc/Dem_CmnLib_AsyncReqTable.h"
#include "../../../../inc/Dem_Rc_SimilarMng.h"
#include "../../../../inc/Dem_Utl_Similar.h"
#include "../../../../inc/Dem_Rc_ClrInfoMng.h"
#include "Dem_SimilarMng_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     DEM_SIMILAR_ROMCHECK_FACTORY    ( DEM_NVBLOCK_FACTORY_VALUE )
#define     DEM_SIMILAR_ROMCHECK_SAVED      ((uint8)0x00)
#define     DEM_SIMILAR_FLG_FACTORY         ( (boolean)DEM_NVBLOCK_FACTORY_VALUE )

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_SimilarMng_CmpWithConditionList
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,
    P2CONST( Dem_SimilarRecordType, AUTOMATIC, AUTOMATIC ) CheckSimilarRecordPtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_SimilarMng_CmpWithConditionStoredList
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,
    P2CONST( Dem_SimilarRecordType, AUTOMATIC, AUTOMATIC ) CheckSimilarRecordPtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_SimilarMng_CmpWithConditionLatchedList
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,
    P2CONST( Dem_SimilarRecordType, AUTOMATIC, AUTOMATIC ) CheckSimilarRecordPtr
);
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_SimilarMng_InitMirrorRecord
( void );
#if ( DEM_SIMILAR_RECORD_PADDING_EXIST == STD_ON )
static FUNC( void, DEM_CODE ) Dem_SimilarMng_InitPadding
(
    P2VAR( Dem_SimilarRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) SimilarRecordPtr
);
#endif /* ( DEM_SIMILAR_RECORD_PADDING_EXIST == STD_ON ) */
#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */
#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_SimilarNvMStatus[DEM_SIMILAR_RECORD_LIST_NUM];
/*  if DEM_NVM_SYNC_PROCESS_ENABLE is STD_OFF, these valiables are set but never used.  */
VAR( Dem_SimilarRecordType, DEM_VAR_NO_INIT ) Dem_TmpSimilarMirror;
#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_START_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

VAR( Dem_SimilarRecordType,      DEM_VAR_SAVED_ZONE ) Dem_SimilarRecordList[DEM_SIMILAR_RECORD_LIST_NUM];

#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_SimilarMng_DataVerify                                */
/* Description   | verify record data.                                      */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : DataVerify completed.         */
/*               |          DEM_IRT_PENDING : Continue DataVerify.          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_SimilarMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    return DEM_IRT_OK;
}


/****************************************************************************/
/* Function Name | Dem_SimilarMng_GetSimilarRecordList                      */
/* Description   | Get the SimilarRecordList.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] SimilarStrgIndex :                                  */
/*               | [out] SimilarRecordPtr :                                 */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_SimilarMng_GetSimilarRecordList
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,
    P2VAR( Dem_SimilarRecordType, AUTOMATIC, AUTOMATIC ) SimilarRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) similarEventNum;

    retVal = DEM_IRT_NG;

    similarEventNum = Dem_SimilarEventNum;

    if( SimilarStrgIndex < similarEventNum )    /* [GUD:if]SimilarStrgIndex */
    {
        Dem_UtlSimilar_CopySimilarConditionArray( &SimilarRecordPtr->SimilarConditionStoredList[0], &Dem_SimilarRecordList[SimilarStrgIndex].SimilarConditionStoredList[0] );   /* [GUD]SimilarStrgIndex *//* [ARYCHK] DEM_SIMILARTYPE_NUM / 1 / 0 */
        Dem_UtlSimilar_CopySimilarConditionArray( &SimilarRecordPtr->SimilarConditionLatchedList[0], &Dem_SimilarRecordList[SimilarStrgIndex].SimilarConditionLatchedList[0] ); /* [GUD]SimilarStrgIndex *//* [ARYCHK] DEM_SIMILARTYPE_NUM / 1 / 0 */
        SimilarRecordPtr->SimilarConditionStoredflg = Dem_SimilarRecordList[SimilarStrgIndex].SimilarConditionStoredflg;    /* [GUD]SimilarStrgIndex */
        SimilarRecordPtr->PendingEraseCycCounter = Dem_SimilarRecordList[SimilarStrgIndex].PendingEraseCycCounter;          /* [GUD]SimilarStrgIndex */
        SimilarRecordPtr->ExceedanceCounter = Dem_SimilarRecordList[SimilarStrgIndex].ExceedanceCounter;                    /* [GUD]SimilarStrgIndex */
        SimilarRecordPtr->SimilarPassedThisDcy = Dem_SimilarRecordList[SimilarStrgIndex].SimilarPassedThisDcy;              /* [GUD]SimilarStrgIndex */
        SimilarRecordPtr->PendingStoreBeforeDcy = Dem_SimilarRecordList[SimilarStrgIndex].PendingStoreBeforeDcy;            /* [GUD]SimilarStrgIndex */

        SimilarRecordPtr->ConsistencyId = Dem_SimilarRecordList[SimilarStrgIndex].ConsistencyId;                            /* [GUD]SimilarStrgIndex */
        SimilarRecordPtr->ClearID = Dem_SimilarRecordList[SimilarStrgIndex].ClearID;                                        /* [GUD]SimilarStrgIndex */
        SimilarRecordPtr->FactoryCheck = DEM_SIMILAR_ROMCHECK_SAVED;

        retVal = DEM_IRT_OK;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_SimilarMng_SetSimilarRecordList                      */
/* Description   | Set the SimilarRecordList.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] SimilarStrgIndex :                                  */
/*               | [out] SimilarRecordPtr :                                 */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_SimilarMng_SetSimilarRecordList
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,
    P2CONST( Dem_SimilarRecordType, AUTOMATIC, AUTOMATIC ) SimilarRecordPtr
)
{
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) similarEventNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindSimilar;


    similarEventNum = Dem_SimilarEventNum;

    if( SimilarStrgIndex < similarEventNum )    /* [GUD:if]SimilarStrgIndex */
    {
        Dem_UtlSimilar_CopySimilarConditionArray( &Dem_SimilarRecordList[SimilarStrgIndex].SimilarConditionStoredList[0], &SimilarRecordPtr->SimilarConditionStoredList[0] );   /* [GUD]SimilarStrgIndex *//* [ARYCHK] DEM_SIMILARTYPE_NUM / 1 / 0 */
        Dem_UtlSimilar_CopySimilarConditionArray( &Dem_SimilarRecordList[SimilarStrgIndex].SimilarConditionLatchedList[0], &SimilarRecordPtr->SimilarConditionLatchedList[0] ); /* [GUD]SimilarStrgIndex *//* [ARYCHK] DEM_SIMILARTYPE_NUM / 1 / 0 */
        Dem_SimilarRecordList[SimilarStrgIndex].SimilarConditionStoredflg = SimilarRecordPtr->SimilarConditionStoredflg;    /* [GUD]SimilarStrgIndex */
        Dem_SimilarRecordList[SimilarStrgIndex].PendingEraseCycCounter = SimilarRecordPtr->PendingEraseCycCounter;          /* [GUD]SimilarStrgIndex */
        Dem_SimilarRecordList[SimilarStrgIndex].ExceedanceCounter = SimilarRecordPtr->ExceedanceCounter;                    /* [GUD]SimilarStrgIndex */
        Dem_SimilarRecordList[SimilarStrgIndex].SimilarPassedThisDcy = SimilarRecordPtr->SimilarPassedThisDcy;              /* [GUD]SimilarStrgIndex */
        Dem_SimilarRecordList[SimilarStrgIndex].PendingStoreBeforeDcy = SimilarRecordPtr->PendingStoreBeforeDcy;            /* [GUD]SimilarStrgIndex */

        Dem_SimilarRecordList[SimilarStrgIndex].ClearID = SimilarRecordPtr->ClearID;                                        /* [GUD]SimilarStrgIndex */
        Dem_SimilarRecordList[SimilarStrgIndex].FactoryCheck = DEM_SIMILAR_ROMCHECK_SAVED;                                  /* [GUD]SimilarStrgIndex */

        recMngCmnKindSimilar = Dem_RecMngCmnKindSimilar;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindSimilar, ( Dem_u16_RecordIndexType )SimilarStrgIndex );               /* [GUD]SimilarStrgIndex */

    }
    else
    {
        /* No process */
    }

    return ;
}


/****************************************************************************/
/* Function Name | Dem_SimilarMng_SetConsistencyId                          */
/* Description   | Set consistenncyID.                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] SimilarStrgIndex :                                  */
/*               | [in] ConsistencyId :                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_SimilarMng_SetConsistencyId
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,        /* [PRMCHK:CALLER] */
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindSimilar;

    Dem_SimilarRecordList[SimilarStrgIndex].ConsistencyId = ConsistencyId;  /* [GUDCHK:CALLER]SimilarStrgIndex */

    recMngCmnKindSimilar = Dem_RecMngCmnKindSimilar;
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindSimilar, ( Dem_u16_RecordIndexType )SimilarStrgIndex );   /* [GUDCHK:CALLER]SimilarStrgIndex */

    return;
}


/****************************************************************************/
/* Function Name | Dem_SimilarMng_SetExceedanceCounter                      */
/* Description   | Set similar exceedance counter.                          */
/* Preconditions |                                                          */
/* Parameters    | [in] ExceedanceCounter :                                 */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_SimilarMng_SetExceedanceCounter
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,        /* [PRMCHK:CALLER] */
    VAR( Dem_u08_SimilarExceedanceCounterType, AUTOMATIC ) ExceedanceCounter
)
{
    Dem_SimilarRecordList[SimilarStrgIndex].ExceedanceCounter = ExceedanceCounter;  /* [GUDCHK:CALLER]SimilarStrgIndex */

    return;
}

/****************************************************************************/
/* Function Name | Dem_SimilarMng_GetExceedanceCounter                      */
/* Description   | Get similar exceedance counter.                          */
/* Preconditions |                                                          */
/* Parameters    | [in] SimilarStrgIndex :                                  */
/*               | [out] ExceedanceCounterPtr :                             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : get of counter was successful        */
/*               |        DEM_IRT_NG : get of counter failed                */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_SimilarMng_GetExceedanceCounter
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,
    P2VAR( Dem_u08_SimilarExceedanceCounterType, AUTOMATIC, AUTOMATIC ) ExceedanceCounterPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) similarEventNum;

    retVal = DEM_IRT_NG;
    similarEventNum = Dem_SimilarEventNum;

    if( SimilarStrgIndex < similarEventNum )    /* [GUD:if]SimilarStrgIndex */
    {
        *ExceedanceCounterPtr   =   Dem_SimilarRecordList[SimilarStrgIndex].ExceedanceCounter;  /* [GUD]SimilarStrgIndex */
        retVal = DEM_IRT_OK;
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_SimilarMng_GetPendingClearCounter                    */
/* Description   | Set similar PendingClear counter.                        */
/* Preconditions |                                                          */
/* Parameters    | [in] SimilarStrgIndex :                                  */
/*               | [out] PendingClearCounterPtr :                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : get of counter was successful        */
/*               |        DEM_IRT_NG : get of counter failed                */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_SimilarMng_GetExceedanceCounter. */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_SimilarMng_GetPendingClearCounter
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,
    P2VAR( Dem_u08_SimilarPendingClearCounterType, AUTOMATIC, AUTOMATIC ) PendingClearCounterPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) similarEventNum;

    retVal = DEM_IRT_NG;
    similarEventNum = Dem_SimilarEventNum;

    if( SimilarStrgIndex < similarEventNum )    /* [GUD:if]SimilarStrgIndex */
    {
        *PendingClearCounterPtr =   Dem_SimilarRecordList[SimilarStrgIndex].PendingEraseCycCounter; /* [GUD]SimilarStrgIndex */
        retVal = DEM_IRT_OK;
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_SimilarMng_GetSimilarConditionStoredflg              */
/* Description   | Get SimilarConditions stored flag.                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] SimilarStrgIndex :                                  */
/*               | [out] SimilarConditionStoredflgPtr :                     */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_SimilarMng_GetSimilarConditionStoredflg
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,    /* [PRMCHK:CALLER] */
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) SimilarConditionStoredflgPtr
)
{
    *SimilarConditionStoredflgPtr = Dem_SimilarRecordList[SimilarStrgIndex].SimilarConditionStoredflg;      /* [GUDCHK:CALLER]SimilarStrgIndex */
    return ;
}

/****************************************************************************/
/* Function Name | Dem_SimilarMng_GetSimilarConditionStoredList             */
/* Description   | Get SimilarConditions stored list data.                  */
/* Preconditions | none                                                     */
/* Parameters    | [in] SimilarStrgIndex :                                  */
/*               | [out] SimilarConditionArrayPtr :                         */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_SimilarMng_GetSimilarConditionStoredList
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,    /* [PRMCHK:CALLER] */
    P2VAR( Dem_SimilarConditionValueType, AUTOMATIC, DEM_APPL_DATA ) SimilarConditionArrayPtr
)
{
    Dem_UtlSimilar_CopySimilarConditionArray( SimilarConditionArrayPtr, &Dem_SimilarRecordList[SimilarStrgIndex].SimilarConditionStoredList[0] );   /* [GUDCHK:CALLER]SimilarStrgIndex */
    return ;
}

/****************************************************************************/
/* Function Name | Dem_SimilarMng_GetSimilarConditionLatchedList            */
/* Description   | Get SimilarConditions latched list data.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] SimilarStrgIndex :                                  */
/*               | [out] SimilarConditionArrayPtr :                         */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_SimilarMng_GetSimilarConditionLatchedList
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,    /* [PRMCHK:CALLER] */
    P2VAR( Dem_SimilarConditionValueType, AUTOMATIC, DEM_APPL_DATA ) SimilarConditionArrayPtr
)
{
    Dem_UtlSimilar_CopySimilarConditionArray( SimilarConditionArrayPtr, &Dem_SimilarRecordList[SimilarStrgIndex].SimilarConditionLatchedList[0] );  /* [GUDCHK:CALLER]SimilarStrgIndex */
    return ;
}

/****************************************************************************/
/* Function Name | Dem_SimilarMng_ClearSimilarRecordList                    */
/* Description   | Clear the SimilarRecordList.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] SimilarStrgIndex :                                  */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_SimilarMng_ClearSimilarRecordList
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindSimilar;

    Dem_UtlSimilar_SetSimilarConditionArray( &Dem_SimilarRecordList[SimilarStrgIndex].SimilarConditionStoredList[0], (Dem_SimilarConditionValueType)0U );   /* [GUDCHK:CALLER]SimilarStrgIndex */
    Dem_UtlSimilar_SetSimilarConditionArray( &Dem_SimilarRecordList[SimilarStrgIndex].SimilarConditionLatchedList[0], (Dem_SimilarConditionValueType)0U );  /* [GUDCHK:CALLER]SimilarStrgIndex */
    Dem_SimilarRecordList[SimilarStrgIndex].SimilarConditionStoredflg = (boolean)FALSE;                             /* [GUDCHK:CALLER]SimilarStrgIndex */
    Dem_SimilarRecordList[SimilarStrgIndex].PendingEraseCycCounter = DEM_SIMILAR_PENDINGERASECYCCOUNTER_INIT;       /* [GUDCHK:CALLER]SimilarStrgIndex */
    Dem_SimilarRecordList[SimilarStrgIndex].ExceedanceCounter = DEM_SIMILAR_EXCEEDANCECOUNTER_INIT;                 /* [GUDCHK:CALLER]SimilarStrgIndex */
    Dem_SimilarRecordList[SimilarStrgIndex].SimilarPassedThisDcy = (boolean)FALSE;                                  /* [GUDCHK:CALLER]SimilarStrgIndex */
    Dem_SimilarRecordList[SimilarStrgIndex].PendingStoreBeforeDcy = (boolean)FALSE;                                 /* [GUDCHK:CALLER]SimilarStrgIndex */

    Dem_SimilarRecordList[SimilarStrgIndex].ClearID      = Dem_ClrInfoMng_GetObdClearID();                          /* [GUDCHK:CALLER]SimilarStrgIndex */
    Dem_SimilarRecordList[SimilarStrgIndex].FactoryCheck = DEM_SIMILAR_ROMCHECK_SAVED;                              /* [GUDCHK:CALLER]SimilarStrgIndex */

    recMngCmnKindSimilar = Dem_RecMngCmnKindSimilar;
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindSimilar, ( Dem_u16_RecordIndexType )SimilarStrgIndex );           /* [GUDCHK:CALLER]SimilarStrgIndex */

    return;
}


/****************************************************************************/
/* Function Name | Dem_SimilarMng_CompareSimilarRecord                      */
/* Description   | compare similar record.                                  */
/* Preconditions |                                                          */
/* Parameters    | [in] CheckSimilarRecordPtr :                             */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | None                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_SimilarMng_CompareSimilarRecord
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,        /* [PRMCHK:CALLER] */
    P2CONST( Dem_SimilarRecordType, AUTOMATIC, AUTOMATIC ) CheckSimilarRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfComWithConditionList;

    retVal = DEM_IRT_OK;

    if( Dem_SimilarRecordList[SimilarStrgIndex].SimilarConditionStoredflg != CheckSimilarRecordPtr->SimilarConditionStoredflg ) /* [GUDCHK:CALLER]SimilarStrgIndex */
    {
        retVal = DEM_IRT_NG;
    }
    else if( Dem_SimilarRecordList[SimilarStrgIndex].PendingEraseCycCounter != CheckSimilarRecordPtr->PendingEraseCycCounter )  /* [GUDCHK:CALLER]SimilarStrgIndex */
    {
        retVal = DEM_IRT_NG;
    }
    else if( Dem_SimilarRecordList[SimilarStrgIndex].SimilarPassedThisDcy != CheckSimilarRecordPtr->SimilarPassedThisDcy )      /* [GUDCHK:CALLER]SimilarStrgIndex */
    {
        retVal = DEM_IRT_NG;
    }
    else if( Dem_SimilarRecordList[SimilarStrgIndex].PendingStoreBeforeDcy != CheckSimilarRecordPtr->PendingStoreBeforeDcy )    /* [GUDCHK:CALLER]SimilarStrgIndex */
    {
        retVal = DEM_IRT_NG;
    }
    else
    {
        resultOfComWithConditionList = Dem_SimilarMng_CmpWithConditionList( SimilarStrgIndex, CheckSimilarRecordPtr );          /* [GUDCHK:CALLER]SimilarStrgIndex */
        if( resultOfComWithConditionList != DEM_IRT_OK )
        {
            retVal = DEM_IRT_NG;
        }
    }

    /* not compared member: */
    /* ExceedanceCounter, ConsistencyId, ClearID , FactoryCheck */

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_SimilarMng_CmpWithConditionList                      */
/* Description   | compare condition list of similar record.                */
/* Preconditions |                                                          */
/* Parameters    | [in] CheckSimilarRecordPtr :                             */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_SimilarMng_CmpWithConditionList
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,
    P2CONST( Dem_SimilarRecordType, AUTOMATIC, AUTOMATIC ) CheckSimilarRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfComWithConditionStoredList;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfComWithConditionLatchedList;

    resultOfComWithConditionStoredList = Dem_SimilarMng_CmpWithConditionStoredList( SimilarStrgIndex, CheckSimilarRecordPtr );
    if( resultOfComWithConditionStoredList == DEM_IRT_OK )
    {
        resultOfComWithConditionLatchedList = Dem_SimilarMng_CmpWithConditionLatchedList( SimilarStrgIndex, CheckSimilarRecordPtr );
        if( resultOfComWithConditionLatchedList == DEM_IRT_OK )
        {
            /* same. */
            retVal = DEM_IRT_OK;
        }
        else
        {
            /* different. */
            retVal = DEM_IRT_NG;
        }
    }
    else
    {
        /* different. */
        retVal = DEM_IRT_NG;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_SimilarMng_CmpWithConditionStoredList                */
/* Description   | compare condition list of similar record.                */
/* Preconditions |                                                          */
/* Parameters    | [in] CheckSimilarRecordPtr :                             */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | None                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_SimilarMng_CmpWithConditionStoredList
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,        /* [PRMCHK:CALLER] */
    P2CONST( Dem_SimilarRecordType, AUTOMATIC, AUTOMATIC ) CheckSimilarRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_SimilarConditionIndexType, AUTOMATIC ) idx;
    VAR( Dem_u08_SimilarConditionIndexType, AUTOMATIC ) similartypeNum;

    similartypeNum = Dem_SimilartypeNum;
    retVal = DEM_IRT_OK;    /* same. */

    /* check SimilarConditionStoredList. */
    for( idx = (Dem_u08_SimilarConditionIndexType)0U; idx < similartypeNum; idx++ ) /* [GUD:for]idx */
    {
        if( Dem_SimilarRecordList[SimilarStrgIndex].SimilarConditionStoredList[idx] != CheckSimilarRecordPtr->SimilarConditionStoredList[idx] ) /* [GUDCHK:CALLER]SimilarStrgIndex *//* [GUD]idx *//* [ARYCHK] DEM_SIMILARTYPE_NUM / 1 / idx */
        {
            retVal = DEM_IRT_NG;
            break;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_SimilarMng_CmpWithConditionLatchedList               */
/* Description   | compare condition list of similar record.                */
/* Preconditions |                                                          */
/* Parameters    | [in] CheckSimilarRecordPtr :                             */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | None                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_SimilarMng_CmpWithConditionLatchedList
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,        /* [PRMCHK:CALLER] */
    P2CONST( Dem_SimilarRecordType, AUTOMATIC, AUTOMATIC ) CheckSimilarRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_SimilarConditionIndexType, AUTOMATIC ) idx;
    VAR( Dem_u08_SimilarConditionIndexType, AUTOMATIC ) similartypeNum;

    similartypeNum = Dem_SimilartypeNum;
    retVal = DEM_IRT_OK;    /* same. */

    /* check SimilarConditionStoredList. */
    for( idx = (Dem_u08_SimilarConditionIndexType)0U; idx < similartypeNum; idx++ ) /* [GUD:for]idx */
    {
        if( Dem_SimilarRecordList[SimilarStrgIndex].SimilarConditionLatchedList[idx] != CheckSimilarRecordPtr->SimilarConditionLatchedList[idx] )   /* [GUDCHK:CALLER]SimilarStrgIndex *//* [GUD]idx *//* [ARYCHK] DEM_SIMILARTYPE_NUM / 1 / idx */
        {
            retVal = DEM_IRT_NG;
            break;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_SimilarMng_GetFactoryCheckResultOfSimilarRecord      */
/* Description   | get factory check result of Similar record.              */
/* Preconditions |                                                          */
/* Parameters    | [in] SimilarStrgIndex :                                  */
/* Return Value  | boolean                                                  */
/*               |          TRUE      : Factory default                     */
/*               |          FALSE     : Non Factory default                 */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_SimilarMng_GetFactoryCheckResult
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex         /* [PRMCHK:CALLER] */
)
{
    VAR( boolean, AUTOMATIC ) resultOfFactoryCheck;

    resultOfFactoryCheck = (boolean)FALSE;

    if ( Dem_SimilarRecordList[SimilarStrgIndex].FactoryCheck == DEM_SIMILAR_ROMCHECK_FACTORY ) /* [GUDCHK:CALLER]SimilarStrgIndex */
    {
        resultOfFactoryCheck = (boolean)TRUE;
    }

    return resultOfFactoryCheck;
}


/****************************************************************************/
/* Function Name | Dem_SimilarMng_CheckClearId                              */
/* Description   | get clearID check result of Similar record.              */
/* Preconditions |                                                          */
/* Parameters    | [in] SimilarStrgIndex :                                  */
/*               | [in] ClearID                                             */
/* Return Value  | boolean                                                  */
/*               |          TRUE      : clearID check OK                    */
/*               |          FALSE     : clearID check NG                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_SimilarMng_CheckClearId
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,        /* [PRMCHK:CALLER] */
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) ClearID
)
{
    VAR( boolean, AUTOMATIC ) resultOfClearIdCheck;

    resultOfClearIdCheck = (boolean)FALSE;

    if ( Dem_SimilarRecordList[SimilarStrgIndex].ClearID == ClearID )   /* [GUDCHK:CALLER]SimilarStrgIndex */
    {
        resultOfClearIdCheck = (boolean)TRUE;
    }

    return resultOfClearIdCheck;
}


/****************************************************************************/
/* Function Name | Dem_SimilarMng_CheckConsistencyId                        */
/* Description   | get consistency ID check result of Similar record.       */
/* Preconditions |                                                          */
/* Parameters    | [in] SimilarStrgIndex :                                  */
/*               | [in] ConsistencyId                                       */
/* Return Value  | boolean                                                  */
/*               |          TRUE      : consistencyID check OK              */
/*               |          FALSE     : consistencyID check NG              */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_SimilarMng_CheckConsistencyId
(
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) SimilarStrgIndex,        /* [PRMCHK:CALLER] */
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
)
{
    VAR( boolean, AUTOMATIC ) resultOfConsistencyIdCheck;

    resultOfConsistencyIdCheck = (boolean)FALSE;

    if ( Dem_SimilarRecordList[SimilarStrgIndex].ConsistencyId == ConsistencyId )   /* [GUDCHK:CALLER]SimilarStrgIndex */
    {
        resultOfConsistencyIdCheck = (boolean)TRUE;
    }

    return resultOfConsistencyIdCheck;
}


/****************************************************************************/
/* Function Name | Dem_SimilarMng_Init                                      */
/* Description   | Initialize savedzone process of Similar.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_SimilarMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    /* [FuncSw] */
    Dem_SimilarMng_InitMirrorRecord();
#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */

    return;
}


/****************************************************************************/
/* Function Name | Dem_SimilarMng_InitSavedZone                             */
/* Description   | Initialize the SimilarRecordList.                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in] InitType :                                          */
/*               |          Initialize savedzone type                       */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_SimilarMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType      /* MISRA DEVIATION */
)
{
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) similarStrgIndex;
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) similarEventNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindSimilar;

    similarEventNum = Dem_SimilarEventNum;
    recMngCmnKindSimilar = Dem_RecMngCmnKindSimilar;

    for( similarStrgIndex = (Dem_u16_SimilarStrgIndexType)0U; similarStrgIndex < similarEventNum; similarStrgIndex++ )  /* [GUD:for]similarStrgIndex */
    {
        Dem_UtlSimilar_SetSimilarConditionArray( &Dem_SimilarRecordList[similarStrgIndex].SimilarConditionStoredList[0], DEM_SIMILAR_CONDITION_FACTORY_DEFAULT );   /* [GUD]similarStrgIndex */
        Dem_UtlSimilar_SetSimilarConditionArray( &Dem_SimilarRecordList[similarStrgIndex].SimilarConditionLatchedList[0], DEM_SIMILAR_CONDITION_FACTORY_DEFAULT );  /* [GUD]similarStrgIndex */
        Dem_SimilarRecordList[similarStrgIndex].SimilarConditionStoredflg = DEM_SIMILAR_FLG_FACTORY;                    /* [GUD]similarStrgIndex */
        Dem_SimilarRecordList[similarStrgIndex].PendingEraseCycCounter = DEM_SIMILAR_COUNTER_FACTORY_DEFAULT;           /* [GUD]similarStrgIndex */
        Dem_SimilarRecordList[similarStrgIndex].ExceedanceCounter = DEM_SIMILAR_EXCEEDANCECOUNTER_FACTORY_DEFAULT;      /* [GUD]similarStrgIndex */
        Dem_SimilarRecordList[similarStrgIndex].SimilarPassedThisDcy = DEM_SIMILAR_FLG_FACTORY;                         /* [GUD]similarStrgIndex */
        Dem_SimilarRecordList[similarStrgIndex].PendingStoreBeforeDcy = DEM_SIMILAR_FLG_FACTORY;                        /* [GUD]similarStrgIndex */

        Dem_SimilarRecordList[similarStrgIndex].ConsistencyId  = DEM_CONSISTENCY_INITIAL;                               /* [GUD]similarStrgIndex */
        Dem_SimilarRecordList[similarStrgIndex].ClearID      = DEM_CLRINFO_RECORD_INITIAL;                              /* [GUD]similarStrgIndex */
        Dem_SimilarRecordList[similarStrgIndex].FactoryCheck = DEM_SIMILAR_ROMCHECK_FACTORY;                            /* [GUD]similarStrgIndex */

        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindSimilar, ( Dem_u16_RecordIndexType )similarStrgIndex );           /* [GUD]similarStrgIndex */
    }

    return;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_SimilarMng_SetRecordMirror                           */
/* Description   | Set the Writing RamData.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in/out] BlockMirrorPtr :                                */
/*               |        Nonvolatile synchronous data information.         */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_SimilarMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    (void)Dem_SimilarMng_GetSimilarRecordList( (Dem_u16_SimilarStrgIndexType)BlockMirrorPtr->RecordIndex, &Dem_TmpSimilarMirror ); /* no return check required */

    BlockMirrorPtr->MirrorPtr = &Dem_TmpSimilarMirror;

    return;
}
#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_SimilarMng_GetEventIdFromRecordData                  */
/* Description   | get event id from record data                            */
/* Preconditions | none                                                     */
/* Parameters    | [in]  RecordFieldIndex :                                 */
/*               | [in]  RecordIndex :                                      */
/*               | [out] EventIdPtr  :                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_SimilarMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_SimilarStrgIndexType, AUTOMATIC ) similarStrgIndex;

    retVal  =   DEM_IRT_NG;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    similarStrgIndex    =   ( Dem_u16_SimilarStrgIndexType )RecordIndex;
    eventStrgIndex      =   Dem_CfgInfoPm_CnvSimilarStrgIndexToEventStrgIndex( similarStrgIndex );

    if ( eventStrgIndex < eventStorageNum )                                                                 /* [GUD:if]eventStrgIndex */
    {
        retVal  =   Dem_CfgInfoPm_CnvEventStrgIndexToEventId( eventStrgIndex, EventIdPtr );                 /* [GUD]eventStrgIndex */
    }

    return retVal;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_SimilarMng_InitMirrorRecord                          */
/* Description   | Initializes the Mirror Memory of Similar record.         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_SimilarMng_InitMirrorRecord
( void )
{
    /* Initializes the mirror memory. */
    Dem_UtlSimilar_SetSimilarConditionArray( &Dem_TmpSimilarMirror.SimilarConditionStoredList[0], (Dem_SimilarConditionValueType)0U );
    Dem_UtlSimilar_SetSimilarConditionArray( &Dem_TmpSimilarMirror.SimilarConditionLatchedList[0], (Dem_SimilarConditionValueType)0U );
    Dem_TmpSimilarMirror.SimilarConditionStoredflg = (boolean)FALSE;
    Dem_TmpSimilarMirror.PendingEraseCycCounter = DEM_SIMILAR_PENDINGERASECYCCOUNTER_INIT;
    Dem_TmpSimilarMirror.ExceedanceCounter = DEM_SIMILAR_EXCEEDANCECOUNTER_INIT;
    Dem_TmpSimilarMirror.SimilarPassedThisDcy = (boolean)FALSE;
    Dem_TmpSimilarMirror.PendingStoreBeforeDcy = (boolean)FALSE;

    Dem_TmpSimilarMirror.ConsistencyId = DEM_CONSISTENCY_INITIAL;
    Dem_TmpSimilarMirror.ClearID = DEM_CLRINFO_RECORD_INITIAL;
    Dem_TmpSimilarMirror.FactoryCheck = DEM_SIMILAR_ROMCHECK_SAVED;

#if ( DEM_SIMILAR_RECORD_PADDING_EXIST == STD_ON )
    Dem_SimilarMng_InitPadding( &Dem_TmpSimilarMirror );
#endif /* ( DEM_SIMILAR_RECORD_PADDING_EXIST == STD_ON ) */

    return;
}


#if ( DEM_SIMILAR_RECORD_PADDING_EXIST == STD_ON )
/****************************************************************************/
/* Function Name | Dem_SimilarMng_InitPadding                               */
/* Description   | Initializes the record padding data.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] SimilarRecordPtr    :                               */
/*               |       The pointer of the record.                         */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_SimilarMng_InitPadding
(
    P2VAR( Dem_SimilarRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) SimilarRecordPtr
)
{
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingSize;
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingIndex;

    paddingSize = Dem_SimilarRecordBlockPaddingSize;

    for( paddingIndex = (Dem_u16_PaddingIndexType)0U; paddingIndex < paddingSize; paddingIndex++ )  /* [GUD:for]paddingIndex */
    {
        SimilarRecordPtr->Reserve[paddingIndex] = DEM_DATA_RESERVE_INITIAL_VALUE;   /* [GUD]paddingIndex *//* [ARYCHK] DEM_SIMILAR_RECORD_PADDINGSIZE_TO_BLOCKSIZE / 1 / paddingIndex */
    }

    return ;
}
#endif /* ( DEM_SIMILAR_RECORD_PADDING_EXIST == STD_ON ) */

#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_SIMILAR_EVENT_CONFIGURED == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-1-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
