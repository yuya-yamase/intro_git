/* Dem_RecMngCmn_c(v5-7-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/RecMngCmn/CODE                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/



/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../inc/Dem_Md_ModeMng.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "../../../inc/Dem_Rc_ClrInfoMng.h"
#include "../../../usr/Dem_SavedZone_Callout.h"

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
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_RecMngCmn_InitNvMStatus
(
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) RecordKind
);

static FUNC( void, DEM_CODE ) Dem_RecMngCmn_SetUpdateExistFlag
(
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) RecordKind,
    VAR( boolean, AUTOMATIC ) UpdateExistFlag
);
static FUNC( void, DEM_CODE ) Dem_RecMngCmn_SetBlockMirror
(
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) RecordKind,
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
);
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */
#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )

static VAR( volatile Dem_u16_RecordIndexType, DEM_VAR_NO_INIT ) Dem_RecMngCmn_NvMRequestIndex[ DEM_RECMNGCMN_KIND_MAX ];
static VAR( boolean, DEM_VAR_NO_INIT ) Dem_RecMngCmn_RequestOfNvMWrite;

static VAR( Dem_u16_NvBlockPerRecordNumType, DEM_VAR_NO_INIT ) Dem_RecMngCmn_BlockCountPerCurrentRecord;

static VAR( boolean, DEM_VAR_NO_INIT ) Dem_RecMngCmn_ExistNvMWriteData[DEM_RECMNGCMN_KIND_MAX];
static VAR( boolean, DEM_VAR_NO_INIT ) Dem_RecMngCmn_UpdateExistFlag[DEM_RECMNGCMN_KIND_MAX];


#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>



/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_RecMngCmn_Init                                       */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_RecMngCmn_Init
( void )
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnRecIndex;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindMax;
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) recordFieldIndex;

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )   /*  [FuncSw]    */
    Dem_RecMngCmn_ResetRequestOfNvMWrite();
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON-                  */

    recMngCmnKindMax = Dem_RecMngCmnKindMax;

    /* Initializes record Status and Index number */
    for( recMngCmnRecIndex = (Dem_u16_RecordKindIndexType)0U; recMngCmnRecIndex < recMngCmnKindMax; recMngCmnRecIndex++ )   /* [GUD:for]recMngCmnRecIndex */
    {
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )   /*  [FuncSw]    */
        Dem_RecMngCmn_InitNvMStatus( recMngCmnRecIndex );
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON-                  */

        recordFieldIndex = Dem_RecordFieldIndexTableForMemSyncFunc[recMngCmnRecIndex];  /* [GUD]recMngCmnRecIndex */

        /* Do not change the order in which InitFnc is called after Dem_RecMngCmn_InitNvMStatus */
#ifndef JGXSTACK
        /*  call record initialize function.        */
        Dem_RecordInitFuncTable[recMngCmnRecIndex].InitFnc( recordFieldIndex ); /* [GUD]recMngCmnRecIndex */
#else   /* JGXSTACK */
        Dem_RecMngCmnInitFnc_ForStack( recordFieldIndex );
#endif  /* JGXSTACK */
    }
    return;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_RecMngCmn_InitNvMStatus                              */
/* Description   | initialize NvM access status                             */
/* Preconditions |                                                          */
/* Parameters    | [in]  RecordKind :                                       */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_RecMngCmn_InitNvMStatus
(
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) RecordKind                /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) recMngCmnStsIndex;
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) recMngCmnStsMax;

    recMngCmnStsMax =   Dem_NvMWriteInfo[RecordKind].RecordNum;         /* [GUDCHK:CALLER]RecordKind */
    for( recMngCmnStsIndex = (Dem_u16_RecordIndexType)0U; recMngCmnStsIndex < recMngCmnStsMax ; recMngCmnStsIndex++ )   /* [GUD:for]recMngCmnStsIndex */
    {
        Dem_NvMWriteInfo[RecordKind].NvMStatusPtr[recMngCmnStsIndex] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;    /* [GUDCHK:CALLER]RecordKind *//* [GUD]recMngCmnStsIndex *//* [ARYCHK] recMngCmnStsMax / 1 / recMngCmnStsIndex */
    }
    Dem_RecMngCmn_NvMRequestIndex[RecordKind]            = DEM_RECORDINDEX_INVALID;                         /* [GUDCHK:CALLER]RecordKind */

    Dem_RecMngCmn_ExistNvMWriteData[RecordKind] = (boolean)FALSE;                                           /* [GUDCHK:CALLER]RecordKind */

    return ;
}
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */


/****************************************************************************/
/* Function Name | Dem_RecMngCmn_AfterNvBlockReadComplete                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_RecMngCmn_AfterNvBlockReadComplete
( void )
{
    /*  Initialize before DataVerify.           */
    Dem_ClrInfoMng_Init_AfterNvBlockReadComplete();

    return;
}


/****************************************************************************/
/* Function Name | Dem_RecMngCmn_Shutdown                                   */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_RecMngCmn_Shutdown
( void )
{
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )   /*  [FuncSw]    */
    Dem_RecMngCmn_ResetRequestOfNvMWrite();
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON-                  */

    return;
}

/****************************************************************************/
/* Function Name | Dem_RecMngCmn_InitSavedZone                              */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_RecMngCmn_InitSavedZone
( void )
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnRecIndex;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindMax;
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) recordFieldIndex;
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) savedZoneInitType;

    recMngCmnKindMax = Dem_RecMngCmnKindMax;

    savedZoneInitType = Dem_GetSavedZoneInitializeType();

    if( ( savedZoneInitType == DEM_SZINITTYPE_INITIALIZE_WITHOUT_PFC_AND_IUMPR )
     || ( savedZoneInitType == DEM_SZINITTYPE_INITIALIZE_WITHOUT_PFC           )
     || ( savedZoneInitType == DEM_SZINITTYPE_INITIALIZE_ALL                   ) )
    {
        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - start.   */
        Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------*/

        /* Initializes savedzone area */
        for( recMngCmnRecIndex = (Dem_u16_RecordKindIndexType)0U; recMngCmnRecIndex < recMngCmnKindMax; recMngCmnRecIndex++ )   /* [GUD:for]recMngCmnRecIndex */
        {
            recordFieldIndex = Dem_RecordFieldIndexTableForMemSyncFunc[recMngCmnRecIndex];  /* [GUD]recMngCmnRecIndex */

#ifndef JGXSTACK
            /*  call record initialize function.        */
            Dem_RecordInitFuncTable[recMngCmnRecIndex].InitSavedZoneFnc( recordFieldIndex, savedZoneInitType ); /* [GUD]recMngCmnRecIndex */
#else   /* JGXSTACK */
            Dem_RecMngCmnInitSavedZoneFnc_ForStack( recordFieldIndex, savedZoneInitType );
#endif  /* JGXSTACK */
        }

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - end.     */
        Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
        /*--------------------------------------*/
    }
    else if( savedZoneInitType == DEM_SZINITTYPE_INITIALIZE_SAMEAS_CLEARDTC )
    {
        /* set NvMReadResult NG */
        /* perform the initialization that is equal to DTCClear by verification process. */
        Dem_ClrInfoMng_NvMReadError();
    }
    else
    {
        /* No process */
    }

    return;
}

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_RecMngCmn_SetNvMWriteStatus                          */
/* Description   | Change the value of NvMWriteStatus.                      */
/* Preconditions | If exclusion is required for record data and NvMStatusP- */
/*               | tr, the caller of this function should be exclusive.     */
/* Parameters    | [in] RecordKind :                                        */
/*               | [in] RecordIndex :                                       */
/* Return Value  | none                                                     */
/* Notes         | Setting exclusive at the caller.                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_RecMngCmn_SetNvMWriteStatus
(
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) RecordKind,               /* [PRMCHK:CALLER] */
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex
)
{
    if( RecordIndex < Dem_NvMWriteInfo[RecordKind].RecordNum )                                              /* [GUDCHK:CALLER]RecordKind *//* [GUD:if]RecordIndex */
    {
        if ( Dem_NvMWriteInfo[RecordKind].NvMStatusPtr[RecordIndex] == DEM_RECMNGCMN_NVM_STS_WRITING )      /* [GUDCHK:CALLER]RecordKind *//* [GUD]RecordIndex *//* [ARYCHK] Dem_NvMWriteInfo[RecordKind].RecordNum / 1 / RecordIndex */
        {
            Dem_NvMWriteInfo[RecordKind].NvMStatusPtr[RecordIndex] = DEM_RECMNGCMN_NVM_STS_UPDATA_WRITING;  /* [GUDCHK:CALLER]RecordKind *//* [GUD]RecordIndex *//* [ARYCHK] Dem_NvMWriteInfo[RecordKind].RecordNum / 1 / RecordIndex */

            /* The same exclusion as ExclusiveEnterFnc and ExclusiveExitFnc is applied by the caller of this function, */
            /* so exclusion is not required here. */
            Dem_RecMngCmn_UpdateExistFlag[RecordKind] = (boolean)TRUE;                                      /* [GUDCHK:CALLER]RecordKind */
            Dem_RecMngCmn_ExistNvMWriteData[RecordKind] = (boolean)TRUE;                                    /* [GUDCHK:CALLER]RecordKind */

        }
        else if ( ( Dem_NvMWriteInfo[RecordKind].NvMStatusPtr[RecordIndex] == DEM_RECMNGCMN_NVM_STS_TARGET ) ||         /* [GUDCHK:CALLER]RecordKind *//* [GUD]RecordIndex *//* [ARYCHK] Dem_NvMWriteInfo[RecordKind].RecordNum / 1 / RecordIndex */
                  ( Dem_NvMWriteInfo[RecordKind].NvMStatusPtr[RecordIndex] == DEM_RECMNGCMN_NVM_STS_UPDATA_WRITING ) )  /* [GUDCHK:CALLER]RecordKind *//* [GUD]RecordIndex *//* [ARYCHK] Dem_NvMWriteInfo[RecordKind].RecordNum / 1 / RecordIndex */
        {
            /* No process */
        }
        else
        {
            /*   Dem_NvMWriteInfo[RecordKind].NvMStatusPtr[RecordIndex] == DEM_RECMNGCMN_NVM_STS_NON_TARGET         */
            /*   Dem_NvMWriteInfo[RecordKind].NvMStatusPtr[RecordIndex] == DEM_RECMNGCMN_NVM_STS_NOT_VERIFIED       */
            /*   invalid value                                                                                      */
            Dem_NvMWriteInfo[RecordKind].NvMStatusPtr[RecordIndex] = DEM_RECMNGCMN_NVM_STS_TARGET;                      /* [GUDCHK:CALLER]RecordKind *//* [GUD]RecordIndex *//* [ARYCHK] Dem_NvMWriteInfo[RecordKind].RecordNum / 1 / RecordIndex */

            /*  Set mode :  DEM_MODE_SYNCING_NVRAM  */
            SchM_Enter_Dem_NvMRecordAccess();

            /*  NvM WriteRequest is Available.      */
            Dem_RecMngCmn_RequestOfNvMWrite =   (boolean)TRUE;
            Dem_ModeMng_SetMode( DEM_MODE_SYNCING_NVRAM );

            SchM_Exit_Dem_NvMRecordAccess();

            /* The same exclusion as ExclusiveEnterFnc and ExclusiveExitFnc is applied by the caller of this function, */
            /* so exclusion is not required here. */
            Dem_RecMngCmn_UpdateExistFlag[RecordKind] = (boolean)TRUE;                                                  /* [GUDCHK:CALLER]RecordKind */
            Dem_RecMngCmn_ExistNvMWriteData[RecordKind] = (boolean)TRUE;                                                /* [GUDCHK:CALLER]RecordKind */
        }
    }

    return;
}
/****************************************************************************/
/* Function Name | Dem_RecMngCmn_GetNvMWriteData                            */
/* Description   | Set nonvolatile synchronous data of Record               */
/* Preconditions | none                                                     */
/* Parameters    | [in]  RecordKind :                                       */
/*               | [out] BlockMirrorPtr :                                   */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success.                             */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No relevant data.   */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_RecMngCmn_GetNvMWriteData
(
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) RecordKind,               /* [PRMCHK:CALLER] */
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) recNvMReqIndex;
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) recMngCmnIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) breakFlg;

    retVal = DEM_IRT_NO_MATCHING_ELEMENT;
    breakFlg = (boolean)FALSE;

    recNvMReqIndex  =   Dem_RecMngCmn_NvMRequestIndex[RecordKind];                      /* [GUDCHK:CALLER]RecordKind */
    if( recNvMReqIndex == DEM_RECORDINDEX_INVALID )
    {
        Dem_RecMngCmn_SetUpdateExistFlag( RecordKind, (boolean)FALSE );                 /* [GUDCHK:CALLER]RecordKind */

        if( Dem_RecMngCmn_ExistNvMWriteData[RecordKind] == (boolean)TRUE )              /* [GUDCHK:CALLER]RecordKind */
        {
            Dem_RecMngCmn_BlockCountPerCurrentRecord = (Dem_u16_NvBlockPerRecordNumType)0U;

            for ( recMngCmnIndex = (Dem_u16_RecordIndexType)0U; recMngCmnIndex < Dem_NvMWriteInfo[RecordKind].RecordNum; recMngCmnIndex++ ) /* [GUD:for]recMngCmnIndex *//* [GUDCHK:CALLER]RecordKind */
            {
#ifndef JGXSTACK
                /* Enter exclusive area */
                Dem_NvMWriteInfo[RecordKind].ExclusiveEnterFnc();                       /* [GUDCHK:CALLER]RecordKind */
#else   /* JGXSTACK */
                Dem_RecMngCmnExcEnterFnc_ForStack();
#endif /* JGXSTACK */

                if ( Dem_NvMWriteInfo[RecordKind].NvMStatusPtr[recMngCmnIndex] == DEM_RECMNGCMN_NVM_STS_TARGET )        /* [GUDCHK:CALLER]RecordKind *//* [GUD]recMngCmnIndex *//* [ARYCHK] Dem_NvMWriteInfo[RecordKind].RecordNum / 1 / recMngCmnIndex */
                {
                    /* Set record index */
                    Dem_RecMngCmn_NvMRequestIndex[RecordKind] = recMngCmnIndex;                                         /* [GUDCHK:CALLER]RecordKind */

                    Dem_RecMngCmn_SetBlockMirror( RecordKind, BlockMirrorPtr );                                         /* [GUDCHK:CALLER]RecordKind */

                    /* Change status */
                    Dem_NvMWriteInfo[RecordKind].NvMStatusPtr[recMngCmnIndex] = DEM_RECMNGCMN_NVM_STS_WRITING;          /* [GUDCHK:CALLER]RecordKind *//* [GUD]recMngCmnIndex *//* [ARYCHK] Dem_NvMWriteInfo[RecordKind].RecordNum / 1 / recMngCmnIndex */

                    /* Set flag */
                    breakFlg = (boolean)TRUE;
                }

#ifndef JGXSTACK
                /* Exit exclusive area */
                Dem_NvMWriteInfo[RecordKind].ExclusiveExitFnc();
#else   /* JGXSTACK */
                Dem_RecMngCmnExcExitFnc_ForStack();
#endif /* JGXSTACK */

                if (breakFlg == (boolean)TRUE)
                {
                    Dem_RecMngCmn_BlockCountPerCurrentRecord = Dem_RecMngCmn_BlockCountPerCurrentRecord + (Dem_u16_NvBlockPerRecordNumType)1U;
                    retVal = DEM_IRT_OK;
                    break;
                }
            }

            if( retVal == DEM_IRT_NO_MATCHING_ELEMENT )
            {
#ifndef JGXSTACK
                /* Enter exclusive area */
                Dem_NvMWriteInfo[RecordKind].ExclusiveEnterFnc();                                   /* [GUDCHK:CALLER]RecordKind */
#else   /* JGXSTACK */
                Dem_RecMngCmnExcEnterFnc_ForStack();
#endif /* JGXSTACK */
                if( Dem_RecMngCmn_UpdateExistFlag[RecordKind] != (boolean)TRUE )                    /* [GUDCHK:CALLER]RecordKind */
                {
                    Dem_RecMngCmn_ExistNvMWriteData[RecordKind] = (boolean)FALSE;                   /* [GUDCHK:CALLER]RecordKind */
                }
#ifndef JGXSTACK
                /* Exit exclusive area */
                Dem_NvMWriteInfo[RecordKind].ExclusiveExitFnc();                                    /* [GUDCHK:CALLER]RecordKind */
#else   /* JGXSTACK */
                Dem_RecMngCmnExcExitFnc_ForStack();
#endif /* JGXSTACK */
            }
        }
    }
    else
    {
        /* In case of acquisition after the second block */
#ifndef JGXSTACK
        /* Enter exclusive area */
        Dem_NvMWriteInfo[RecordKind].ExclusiveEnterFnc();                           /* [GUDCHK:CALLER]RecordKind */
#else   /* JGXSTACK */
        Dem_RecMngCmnExcEnterFnc_ForStack();
#endif /* JGXSTACK */

        Dem_RecMngCmn_SetBlockMirror(RecordKind, BlockMirrorPtr);                   /* [GUDCHK:CALLER]RecordKind */

#ifndef JGXSTACK
        /* Exit exclusive area */
        Dem_NvMWriteInfo[RecordKind].ExclusiveExitFnc();                            /* [GUDCHK:CALLER]RecordKind */
#else   /* JGXSTACK */
        Dem_RecMngCmnExcExitFnc_ForStack();
#endif /* JGXSTACK */

        Dem_RecMngCmn_BlockCountPerCurrentRecord = Dem_RecMngCmn_BlockCountPerCurrentRecord + (Dem_u16_NvBlockPerRecordNumType)1U;

        retVal = DEM_IRT_OK;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_RecMngCmn_NotifyCompleteNvMWrite                     */
/* Description   | Notify of completion of NvM write processing.            */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordKind                                          */
/* Parameters    | [in] Result                                              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : When writing of record data is comp- */
/*               |                     leted or writing fails               */
/*               |        DEM_IRT_PENDING :                                 */
/*               |          When block of record data to write still exists */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_RecMngCmn_NotifyCompleteNvMWrite
(
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) RecordKind,               /* [PRMCHK:CALLER] */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) Result
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) recMngCmnIndex;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindClrInfo;

    retVal = DEM_IRT_OK;
    recMngCmnIndex = Dem_RecMngCmn_NvMRequestIndex[RecordKind];                     /* [GUDCHK:CALLER]RecordKind */

    if( ( Dem_RecMngCmn_BlockCountPerCurrentRecord >= Dem_NvMWriteInfo[RecordKind].BlockNumPerRecord ) || ( Result != DEM_IRT_OK ) )    /* [GUDCHK:CALLER]RecordKind */
    {
        if( recMngCmnIndex < Dem_NvMWriteInfo[RecordKind].RecordNum )               /* [GUDCHK:CALLER]RecordKind *//* [GUD:if]recMngCmnIndex */
        {
#ifndef JGXSTACK
            /* Enter exclusive area */
            Dem_NvMWriteInfo[RecordKind].ExclusiveEnterFnc();                       /* [GUDCHK:CALLER]RecordKind */
#else   /* JGXSTACK */
            Dem_RecMngCmnExcEnterFnc_ForStack();
#endif /* JGXSTACK */

            if ( Dem_NvMWriteInfo[RecordKind].NvMStatusPtr[recMngCmnIndex] == DEM_RECMNGCMN_NVM_STS_WRITING )               /* [GUDCHK:CALLER]RecordKind *//* [GUD]recMngCmnIndex *//* [ARYCHK] Dem_NvMWriteInfo[RecordKind].RecordNum / 1 / recMngCmnIndex */
            {
                /* Nvm Write Success or Failure */
                Dem_NvMWriteInfo[RecordKind].NvMStatusPtr[recMngCmnIndex] = DEM_RECMNGCMN_NVM_STS_NON_TARGET;               /* [GUDCHK:CALLER]RecordKind *//* [GUD]recMngCmnIndex *//* [ARYCHK] Dem_NvMWriteInfo[RecordKind].RecordNum / 1 / recMngCmnIndex */
            }
            else if( Dem_NvMWriteInfo[RecordKind].NvMStatusPtr[recMngCmnIndex] == DEM_RECMNGCMN_NVM_STS_UPDATA_WRITING )    /* [GUDCHK:CALLER]RecordKind *//* [GUD]recMngCmnIndex *//* [ARYCHK] Dem_NvMWriteInfo[RecordKind].RecordNum / 1 / recMngCmnIndex */
            {
                Dem_NvMWriteInfo[RecordKind].NvMStatusPtr[recMngCmnIndex] = DEM_RECMNGCMN_NVM_STS_TARGET;                   /* [GUDCHK:CALLER]RecordKind *//* [GUD]recMngCmnIndex *//* [ARYCHK] Dem_NvMWriteInfo[RecordKind].RecordNum / 1 / recMngCmnIndex */

                /*  Set mode :  DEM_MODE_SYNCING_NVRAM  */
                SchM_Enter_Dem_NvMRecordAccess();

                /*  NvM WriteRequest is Available.      */
                Dem_RecMngCmn_RequestOfNvMWrite =   (boolean)TRUE;
                Dem_ModeMng_SetMode( DEM_MODE_SYNCING_NVRAM );

                SchM_Exit_Dem_NvMRecordAccess();
            }
            else
            {
                /* No process */
            }

#ifndef JGXSTACK
            /* Exit exclusive area */
            Dem_NvMWriteInfo[RecordKind].ExclusiveExitFnc();                            /* [GUDCHK:CALLER]RecordKind */
#else   /* JGXSTACK */
            Dem_RecMngCmnExcExitFnc_ForStack();
#endif /* JGXSTACK */

            Dem_RecMngCmn_NvMRequestIndex[RecordKind] = DEM_RECORDINDEX_INVALID;        /* [GUDCHK:CALLER]RecordKind */
        }
    }
    else
    {
        /* When there is write data from the second block onward */
        recMngCmnKindClrInfo = Dem_RecMngCmnKindClrInfo;                                /* [GUD:CFG]recMngCmnKindClrInfo */
        if( Dem_RecMngCmn_ExistNvMWriteData[recMngCmnKindClrInfo] == (boolean)TRUE )    /* [GUD]recMngCmnKindClrInfo */
        {
            /* When clear is requested */
            if( recMngCmnIndex < Dem_NvMWriteInfo[RecordKind].RecordNum )               /* [GUDCHK:CALLER]RecordKind */
            {
#ifndef JGXSTACK
                /* Enter exclusive area */
                Dem_NvMWriteInfo[RecordKind].ExclusiveEnterFnc();                       /* [GUDCHK:CALLER]RecordKind */
#else   /* JGXSTACK */
                Dem_RecMngCmnExcEnterFnc_ForStack();
#endif /* JGXSTACK */

                Dem_NvMWriteInfo[RecordKind].NvMStatusPtr[recMngCmnIndex] = DEM_RECMNGCMN_NVM_STS_TARGET;       /* [GUDCHK:CALLER]RecordKind *//* [GUD]recMngCmnIndex *//* [ARYCHK] Dem_NvMWriteInfo[RecordKind].RecordNum / 1 / recMngCmnIndex */

#ifndef JGXSTACK
                /* Exit exclusive area */
                Dem_NvMWriteInfo[RecordKind].ExclusiveExitFnc();                        /* [GUDCHK:CALLER]RecordKind */
#else   /* JGXSTACK */
                Dem_RecMngCmnExcExitFnc_ForStack();
#endif /* JGXSTACK */

                Dem_RecMngCmn_NvMRequestIndex[RecordKind] = DEM_RECORDINDEX_INVALID;    /* [GUDCHK:CALLER]RecordKind */
            }
        }
        else
        {
            retVal = DEM_IRT_PENDING;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_RecMngCmn_GetRequestOfNvMWriteStatus                 */
/* Description   | Get WriteRecord requested status.                        */
/* Preconditions | none                                                     */
/* Parameters    | void                                                     */
/* Return Value  | boolean                                                  */
/*               |        FALSE : no requested.                             */
/*               |        TRUE  : requested.                                */
/* Notes         | none.                                                    */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_RecMngCmn_GetRequestOfNvMWrite
( void )
{
    return Dem_RecMngCmn_RequestOfNvMWrite;
}

/****************************************************************************/
/* Function Name | Dem_RecMngCmn_ResetRequestOfNvMWrite                     */
/* Description   | Reset WriteRecord requested status.                      */
/* Preconditions | none                                                     */
/* Parameters    | void                                                     */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_RecMngCmn_ResetRequestOfNvMWrite
( void )
{
    Dem_RecMngCmn_RequestOfNvMWrite =   (boolean)FALSE;
}

/****************************************************************************/
/* Function Name | Dem_RecMngCmn_ExclusiveDummy                             */
/* Description   |                                                          */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | Dummy function for Dem_NvMWriteInfo table                */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_RecMngCmn_ExclusiveDummy
( void )
{
    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Dem_RecMngCmn_SetUpdateExistFlag                         */
/* Description   | Set Dem_RecMngCmn_UpdateExistFlag                        */
/* Preconditions | none                                                     */
/* Parameters    | [in]  RecordKind :                                       */
/*               | [in]  UpdateExistFlag :                                  */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_RecMngCmn_SetUpdateExistFlag
(
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) RecordKind,           /* [PRMCHK:CALLER] */
    VAR( boolean, AUTOMATIC ) UpdateExistFlag
)
{
#ifndef JGXSTACK
    /* Enter exclusive area */
    Dem_NvMWriteInfo[RecordKind].ExclusiveEnterFnc();                   /* [GUDCHK:CALLER]RecordKind */
#else   /* JGXSTACK */
    Dem_RecMngCmnExcEnterFnc_ForStack();
#endif /* JGXSTACK */

    Dem_RecMngCmn_UpdateExistFlag[RecordKind] = UpdateExistFlag;        /* [GUDCHK:CALLER]RecordKind */

#ifndef JGXSTACK
    /* Exit exclusive area */
    Dem_NvMWriteInfo[RecordKind].ExclusiveExitFnc();                    /* [GUDCHK:CALLER]RecordKind */
#else   /* JGXSTACK */
    Dem_RecMngCmnExcExitFnc_ForStack();
#endif /* JGXSTACK */

    return;
}

/****************************************************************************/
/* Function Name | Dem_RecMngCmn_SetBlockMirror                             */
/* Description   | Set BlockMirror                                          */
/* Preconditions | Use after setting Dem_RecMngCmn_NvMRequestIndex[RecordK- */
/*               | ind] and Dem_RecMngCmn_BlockCountPerCurrentRecord        */
/* Parameters    | [in]  RecordKind :                                       */
/*               | [out] BlockMirrorPtr :                                   */
/* Return Value  | void                                                     */
/* Notes         | none.                                                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_RecMngCmn_SetBlockMirror
(
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) RecordKind,               /* [PRMCHK:CALLER] */
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{

    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) recordFieldIndex;

    recordFieldIndex = Dem_RecordFieldIndexTableForMemSyncFunc[RecordKind]; /* [GUDCHK:CALLER]RecordKind */

    /* Set record info for NvM */
    BlockMirrorPtr->RecordIndex = Dem_RecMngCmn_NvMRequestIndex[RecordKind];    /* [GUDCHK:CALLER]RecordKind */
    BlockMirrorPtr->BlockRecordKind = Dem_NvMWriteInfo[RecordKind].BlockRecordKind; /* [GUDCHK:CALLER]RecordKind */
    BlockMirrorPtr->RecordDataOffset = Dem_RecMngCmn_BlockCountPerCurrentRecord;
    BlockMirrorPtr->MirrorLength = Dem_NvMWriteInfo[RecordKind].DemBlockSize;   /* [GUDCHK:CALLER]RecordKind */
#ifndef JGXSTACK
    /* Set mirror */
    Dem_NvMWriteInfo[RecordKind].SetRecordMirrorFnc( recordFieldIndex, BlockMirrorPtr );    /* [GUDCHK:CALLER]RecordKind */
#else   /* JGXSTACK */
    Dem_RecMngCmnSetMirrorDataFnc_ForStack( recordFieldIndex, BlockMirrorPtr );
#endif /* JGXSTACK */

    return;
}

/****************************************************************************/
/* Function Name | Dem_RecMngCmn_RefreshRAM                                 */
/* Description   | Refresh RAM  - RecMngCmn                                 */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | Called from Dem_MainFunction                             */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_RecMngCmn_RefreshRAM
( void )
{
    VAR( volatile Dem_u16_RecordIndexType, AUTOMATIC )                      u16_dummy;      /*  for store GlobalVariable data    */
    P2VAR( volatile Dem_u16_RecordIndexType, AUTOMATIC, DEM_VAR_NO_INIT )   u16_dummyPtr;   /*  for GlobalVariable address       */

    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnRecIndex;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindMax;
    recMngCmnKindMax = Dem_RecMngCmnKindMax;

    for( recMngCmnRecIndex = (Dem_u16_RecordKindIndexType)0U; recMngCmnRecIndex < recMngCmnKindMax; recMngCmnRecIndex++ )   /* [GUD:for]recMngCmnRecIndex */
    {
        /*  set GlobalVariable pointer  */
        u16_dummyPtr      = &Dem_RecMngCmn_NvMRequestIndex[ recMngCmnRecIndex ];        /* [GUD]recMngCmnRecIndex *//* [GUD]u16_dummyPtr */

        /* Exclusion is not necessary   */
        u16_dummy         = *u16_dummyPtr;          /*  read GlobalVariable data    */  /* [GUD]u16_dummyPtr */
        *u16_dummyPtr     = u16_dummy;              /*  rewrite GlobalVariable data */

    }

    return;
}

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
