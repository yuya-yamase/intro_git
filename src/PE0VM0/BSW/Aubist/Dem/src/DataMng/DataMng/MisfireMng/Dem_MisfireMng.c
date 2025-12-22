/* Dem_MisfireMng_c(v5-9-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/MisfireMng/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../../cfg/Dem_Cfg.h"

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include "../../../../cfg/Dem_Misfire_Cfg.h"
#include "../../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "../../../../inc/Dem_Rc_MisfireMng.h"
#include "../../../../inc/Dem_Rc_ClrInfoMng.h"
#include "../../../../usr/Dem_SavedZone_Callout.h"

#include "Dem_MisfireMng_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define     DEM_MISFIRE_ROMCHECK_FACTORY    ( DEM_NVBLOCK_FACTORY_VALUE )
#define     DEM_MISFIRE_ROMCHECK_SAVED      ((uint8)0x00)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( void, DEM_CODE ) Dem_MisfireMng_InitMisfireRecord
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex
);
static FUNC( void, DEM_CODE ) Dem_MisfireMng_InitMisfireComRecord
( void );

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_CmpWithFFDCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    P2CONST( Dem_MisfireRecordType, AUTOMATIC, AUTOMATIC ) CheckMisfireRecordPtr
);
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_CmpWithObdFFDCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    P2CONST( Dem_MisfireRecordType, AUTOMATIC, AUTOMATIC ) CheckMisfireRecordPtr
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_CmpWithNonObdFFDCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    P2CONST( Dem_MisfireRecordType, AUTOMATIC, AUTOMATIC ) CheckMisfireRecordPtr
);
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_CmpWithKindOfFFD
(
    P2CONST( Dem_MisfireComRecordType, AUTOMATIC, AUTOMATIC ) CheckMisfireComRecordPtr
);
#if ( DEM_OBDFFD_SUPPORT == STD_ON )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_CmpWithKindOfObdFFD
(
    P2CONST( Dem_MisfireComRecordType, AUTOMATIC, AUTOMATIC ) CheckMisfireComRecordPtr
);
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_CmpWithKindOfNonObdFFD
(
    P2CONST( Dem_MisfireComRecordType, AUTOMATIC, AUTOMATIC ) CheckMisfireComRecordPtr
);
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_MisfireMng_InitMisfireMirrorRecord
( void );
#if ( DEM_MISFIRE_RECORD_PADDING_EXIST == STD_ON )
static FUNC( void, DEM_CODE ) Dem_MisfireMng_InitPaddingMisfire
(
    P2VAR( Dem_MisfireRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) MisfireRecordPtr
);
#endif /* ( DEM_MISFIRE_RECORD_PADDING_EXIST == STD_ON ) */
static FUNC( void, DEM_CODE ) Dem_MisfireMng_InitMisfireComMirrorRecord
( void );
#if ( DEM_MISFIRECOM_RECORD_PADDING_EXIST == STD_ON )
static FUNC( void, DEM_CODE ) Dem_MisfireMng_InitPaddingMisfireCom
(
    P2VAR( Dem_MisfireComRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) MisfireComRecordPtr
);
#endif /* ( DEM_MISFIRECOM_RECORD_PADDING_EXIST == STD_ON ) */
static FUNC( void, DEM_CODE ) Dem_MisfireMng_GetMisfireRecordList
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    P2VAR( Dem_MisfireRecordType, AUTOMATIC, AUTOMATIC ) MisfireRecordPtr
);
#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */
#if ( DEM_PFC_SUPPORT == STD_ON )
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_ComparePFCMisfireComRecord
(
    P2CONST( Dem_PFCMisfireComRecordType, AUTOMATIC, AUTOMATIC ) CheckPFCMisfireComRecordPtr
);
static FUNC( void, DEM_CODE ) Dem_MisfireMng_InitPFCMisfireComRecord
( void );
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_MisfireMng_InitPFCMisfireComMirrorRecord
( void );
#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )  */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_MisfireNvMStatus[DEM_MISFIRE_RECORD_LIST_NUM];
VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_MisfireComNvMStatus;
/*  if DEM_NVM_SYNC_PROCESS_ENABLE is STD_OFF, these valiables are set but never used.  */
VAR( Dem_MisfireRecordType, DEM_VAR_NO_INIT ) Dem_TmpMisfireMirror;
VAR( Dem_MisfireComRecordType, DEM_VAR_NO_INIT ) Dem_TmpMisfireComMirror;

#if ( DEM_PFC_SUPPORT == STD_ON )
VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_PFCMisfireComNvMStatus;
VAR( Dem_PFCMisfireComRecordType, DEM_VAR_NO_INIT ) Dem_TmpPFCMisfireComMirror;
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )  */
#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#define DEM_START_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>

VAR( Dem_MisfireRecordType,         DEM_VAR_SAVED_ZONE ) Dem_MisfireRecordList[DEM_MISFIRE_RECORD_LIST_NUM];
VAR( Dem_MisfireComRecordType,      DEM_VAR_SAVED_ZONE ) Dem_MisfireComRecord;

#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>



#if ( DEM_PFC_SUPPORT == STD_ON )
#define DEM_START_SEC_VAR_SAVED_ZONE_PERMANENT
#include <Dem_MemMap.h>

VAR( Dem_PFCMisfireComRecordType,   DEM_VAR_SAVED_ZONE_PERMANENT ) Dem_PFCMisfireComRecord;

#define DEM_STOP_SEC_VAR_SAVED_ZONE_PERMANENT
#include <Dem_MemMap.h>
#endif /* ( DEM_PFC_SUPPORT == STD_ON ) */


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_MisfireMng_MisfireRecordDataVerify                   */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_MisfireRecordDataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    return DEM_IRT_OK;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_MisfireComRecordDataVerify                */
/* Description   | verify record data.                                      */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : DataVerify completed.         */
/*               |          DEM_IRT_PENDING : Continue DataVerify.          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_MisfireComRecordDataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    return DEM_IRT_OK;
}


#if ( DEM_PFC_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_MisfireMng_PFCMisfireComRecordDataVerify             */
/* Description   | verify record data.                                      */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : DataVerify completed.         */
/*               |          DEM_IRT_PENDING : Continue DataVerify.          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_PFCMisfireComRecordDataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    return DEM_IRT_OK;
}
#endif /* ( DEM_PFC_SUPPORT == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_MisfireMng_GetFactoryCheckResultOfMisfireRecord      */
/* Description   | get factory check result of Misfire record.              */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireIndex :                                      */
/* Return Value  | boolean                                                  */
/*               |          TRUE      : Factory default                     */
/*               |          FALSE     : Non Factory default                 */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_MisfireMng_GetFactoryCheckResultOfMisfireRecord
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex             /* [PRMCHK:CALLER] */
)
{
    VAR( boolean, AUTOMATIC ) resultOfFactoryCheck;

    resultOfFactoryCheck = (boolean)FALSE;

    if ( Dem_MisfireRecordList[MisfireIndex].FactoryCheck == DEM_MISFIRE_ROMCHECK_FACTORY ) /* [GUDCHK:CALLER]MisfireIndex */
    {
        resultOfFactoryCheck = (boolean)TRUE;
    }

    return resultOfFactoryCheck;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_GetFactoryCheckResultOfMisfireComRecord   */
/* Description   | get factory check result of MisfireCom record.           */
/* Preconditions |                                                          */
/* Parameters    | none                                                     */
/* Return Value  | boolean                                                  */
/*               |          TRUE      : Factory default                     */
/*               |          FALSE     : Non Factory default                 */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_MisfireMng_GetFactoryCheckResultOfMisfireComRecord
(void)
{
    VAR( boolean, AUTOMATIC ) resultOfFactoryCheck;

    resultOfFactoryCheck = (boolean)FALSE;

    if ( Dem_MisfireComRecord.FactoryCheck == DEM_MISFIRE_ROMCHECK_FACTORY )
    {
        resultOfFactoryCheck = (boolean)TRUE;
    }

    return resultOfFactoryCheck;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_CheckClearIdOfMisfireRecord               */
/* Description   | get clearID check result of Misfire record.              */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireIndex :                                      */
/*               | [in] ClearID :                                           */
/* Return Value  | boolean                                                  */
/*               |          TRUE      : ClearId check OK                    */
/*               |          FALSE     : ClearId check NG                    */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_MisfireMng_CheckClearIdOfMisfireRecord
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) ClearID
)
{
    VAR( boolean, AUTOMATIC ) resultOfClearIdCheck;

    resultOfClearIdCheck = (boolean)FALSE;

    if ( Dem_MisfireRecordList[MisfireIndex].ClearID == ClearID )   /* [GUDCHK:CALLER]MisfireIndex */
    {
        resultOfClearIdCheck = (boolean)TRUE;
    }

    return resultOfClearIdCheck;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_CheckClearIdOfMisfireComRecord            */
/* Description   | get clearID check result of MisfireCom record.           */
/* Preconditions |                                                          */
/* Parameters    | [in] ClearID :                                           */
/* Return Value  | boolean                                                  */
/*               |          TRUE      : ClearId check OK                    */
/*               |          FALSE     : ClearId check NG                    */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_MisfireMng_CheckClearIdOfMisfireComRecord
(
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) ClearID
)
{
    VAR( boolean, AUTOMATIC ) resultOfClearIdCheck;

    resultOfClearIdCheck = (boolean)FALSE;

    if ( Dem_MisfireComRecord.ClearID == ClearID )
    {
        resultOfClearIdCheck = (boolean)TRUE;
    }

    return resultOfClearIdCheck;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_CheckConsistencyIdOfMisfireRecord         */
/* Description   | get consistencyID check result of Misfire record.        */
/* Preconditions |                                                          */
/* Parameters    | [in] ConsistencyId :                                     */
/* Return Value  | boolean                                                  */
/*               |          TRUE      : consistencyID check OK              */
/*               |          FALSE     : consistencyID check NG              */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_MisfireMng_CheckConsistencyIdOfMisfireRecord
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
)
{
    VAR( boolean, AUTOMATIC ) resultOfConsistencyIdCheck;

    resultOfConsistencyIdCheck = (boolean)FALSE;

    if ( Dem_MisfireRecordList[MisfireIndex].ConsistencyId == ConsistencyId )   /* [GUDCHK:CALLER]MisfireIndex */
    {
        resultOfConsistencyIdCheck = (boolean)TRUE;
    }

    return resultOfConsistencyIdCheck;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_CheckConsistencyIdOfMisfireComRecord      */
/* Description   | get consistencyID check result of MisfireCom record.     */
/* Preconditions |                                                          */
/* Parameters    | [in] EventKind :                                         */
/*               | [in] ConsistencyId :                                     */
/* Return Value  | boolean                                                  */
/*               |          TRUE      : consistencyID check OK              */
/*               |          FALSE     : consistencyID check NG              */
/****************************************************************************/
FUNC( boolean, DEM_CODE ) Dem_MisfireMng_CheckConsistencyIdOfMisfireComRecord
(
    VAR( Dem_EventKindType, AUTOMATIC ) EventKind,
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
)
{
    VAR( boolean, AUTOMATIC ) resultOfConsistencyIdCheck;

    resultOfConsistencyIdCheck = (boolean)FALSE;

    if( ( EventKind & DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT ) != DEM_EVTKIND_TYPE_MISFIRE_CAT_EVENT )
    {
        if ( Dem_MisfireComRecord.ConsistencyIdForEmission == ConsistencyId )
        {
            resultOfConsistencyIdCheck = (boolean)TRUE;
        }
    }
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    else
    {
        if ( Dem_MisfireComRecord.ConsistencyIdForCAT == ConsistencyId )
        {
            resultOfConsistencyIdCheck = (boolean)TRUE;
        }
    }
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )           */

    return resultOfConsistencyIdCheck;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_MisfireRecordInitSavedZone                */
/* Description   | Initialize savedzone area(Misfire record).               */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in] InitType :                                          */
/*               |          Initialize savedzone type                       */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_MisfireRecordInitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType      /* MISRA DEVIATION */
)
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireEventNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindMisfire;

    recMngCmnKindMisfire = Dem_RecMngCmnKindMisfire;

    misfireEventNum = Dem_MisfireEventNum;
    for( misfireIndex = (Dem_u16_MisfireStrgIndexType)0U; misfireIndex < misfireEventNum; misfireIndex++ )  /* [GUD:for]misfireIndex */
    {
        /* Initializes the MisfireRecord. */
        Dem_MisfireMng_InitMisfireRecord( misfireIndex );                                                   /* [GUD]misfireIndex */
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindMisfire, ( Dem_u16_RecordIndexType )misfireIndex );   /* [GUD]misfireIndex */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_MisfireComRecordInitSavedZone             */
/* Description   | Initialize savedzone area(MisfireCom record).            */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in] InitType :                                          */
/*               |          Initialize savedzone type                       */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_MisfireComRecordInitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType      /* MISRA DEVIATION */
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindMisfireCom;

    recMngCmnKindMisfireCom = Dem_RecMngCmnKindMisfireCom;

    Dem_MisfireMng_InitMisfireComRecord();
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindMisfireCom, ( Dem_u16_RecordIndexType )0U );

    return;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_InitMisfireRecord                         */
/* Description   | Initialize the MisfireRecord.                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireIndex :                                      */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MisfireMng_InitMisfireRecord
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex             /* [PRMCHK:CALLER] */
)
{
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndex;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndexNum;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndex;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndexNum;

    Dem_MisfireRecordList[MisfireIndex].FailedCyl                           = DEM_MISFIRE_CYLINDER_FACTORY_DEFAULT; /* [GUDCHK:CALLER]MisfireIndex */
    Dem_MisfireRecordList[MisfireIndex].AccumCyl                            = DEM_MISFIRE_CYLINDER_FACTORY_DEFAULT; /* [GUDCHK:CALLER]MisfireIndex */
    Dem_MisfireRecordList[MisfireIndex].AccumFailedCylThisOC                = DEM_MISFIRE_CYLINDER_FACTORY_DEFAULT; /* [GUDCHK:CALLER]MisfireIndex */
    Dem_MisfireRecordList[MisfireIndex].AccumFailedCylSinceClear            = DEM_MISFIRE_CYLINDER_FACTORY_DEFAULT; /* [GUDCHK:CALLER]MisfireIndex */
    Dem_MisfireRecordList[MisfireIndex].AccumTestNotCompleteCylSinceClear   = DEM_MISFIRE_CYLINDER_FACTORY_DEFAULT; /* [GUDCHK:CALLER]MisfireIndex */
    Dem_MisfireRecordList[MisfireIndex].AccumPendingCyl                     = DEM_MISFIRE_CYLINDER_FACTORY_DEFAULT; /* [GUDCHK:CALLER]MisfireIndex */
    Dem_MisfireRecordList[MisfireIndex].AccumConfirmedCyl                   = DEM_MISFIRE_CYLINDER_FACTORY_DEFAULT; /* [GUDCHK:CALLER]MisfireIndex */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    misfireObdFFDCylIndexNum = Dem_MisfireObdFFDCylIndexNum;
    for( misfireObdFFDCylIndex = (Dem_u08_MisfireObdFFDCylIndexType)0U; misfireObdFFDCylIndex < misfireObdFFDCylIndexNum; misfireObdFFDCylIndex++ ) /* [GUD:for]misfireObdFFDCylIndex */
    {
        Dem_MisfireRecordList[MisfireIndex].OBDFFDCyl[misfireObdFFDCylIndex] = DEM_MISFIRE_CYLINDER_FACTORY_DEFAULT;    /* [GUDCHK:CALLER]MisfireIndex *//* [GUD]misfireObdFFDCylIndex */
    }
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    misfireFFDCylIndexNum = Dem_MisfireFFDCylIndexNum;
    for( misfireFFDCylIndex = (Dem_u08_MisfireFFDCylIndexType)0U; misfireFFDCylIndex < misfireFFDCylIndexNum; misfireFFDCylIndex++ )    /* [GUD:for]misfireFFDCylIndex */
    {
        Dem_MisfireRecordList[MisfireIndex].FFDCyl[misfireFFDCylIndex] = DEM_MISFIRE_CYLINDER_FACTORY_DEFAULT;  /* [GUDCHK:CALLER]MisfireIndex *//* [GUD]misfireFFDCylIndex */
    }
    Dem_MisfireRecordList[MisfireIndex].ExceedanceCounter        = DEM_MISFIRE_EXCOUNTER_FACTORY_DEFAULT;   /* [GUDCHK:CALLER]MisfireIndex */

    Dem_MisfireRecordList[MisfireIndex].ConsistencyId            = DEM_CONSISTENCY_INITIAL;             /* [GUDCHK:CALLER]MisfireIndex */
    Dem_MisfireRecordList[MisfireIndex].ClearID                  = DEM_CLRINFO_RECORD_INITIAL;          /* [GUDCHK:CALLER]MisfireIndex */
    Dem_MisfireRecordList[MisfireIndex].FactoryCheck             = DEM_MISFIRE_ROMCHECK_FACTORY;        /* [GUDCHK:CALLER]MisfireIndex */

    return;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_ClearMisfireComRecord                     */
/* Description   | Clear the MisfireComRecord.                              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-6-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MisfireMng_InitMisfireComRecord
(void)
{
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndex;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndexNum;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndex;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndexNum;
#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )     /*  [FuncSw]    */
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireConfirmedOrderIndex;
#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )  */

    Dem_MisfireComRecord.FirstPendingCyl        = DEM_MISFIRE_CYLINDER_FACTORY_DEFAULT;
    Dem_MisfireComRecord.FirstConfirmedCyl      = DEM_MISFIRE_CYLINDER_FACTORY_DEFAULT;
    Dem_MisfireComRecord.FirstAccumConfirmedCyl = DEM_MISFIRE_CYLINDER_FACTORY_DEFAULT;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    misfireObdFFDCylIndexNum = Dem_MisfireObdFFDCylIndexNum;
    for( misfireObdFFDCylIndex = (Dem_u08_MisfireObdFFDCylIndexType)0U; misfireObdFFDCylIndex < misfireObdFFDCylIndexNum; misfireObdFFDCylIndex++ ) /* [GUD:for]misfireObdFFDCylIndex */
    {
        Dem_MisfireComRecord.MisfireKindOfOBDFFD[misfireObdFFDCylIndex] = DEM_MISFIRE_KIND_INVALID; /* [GUD]misfireObdFFDCylIndex */
    }
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    misfireFFDCylIndexNum = Dem_MisfireFFDCylIndexNum;
    for( misfireFFDCylIndex = (Dem_u08_MisfireFFDCylIndexType)0U; misfireFFDCylIndex < misfireFFDCylIndexNum; misfireFFDCylIndex++ )    /* [GUD:for]misfireFFDCylIndex */
    {
        Dem_MisfireComRecord.MisfireKindOfFFD[misfireFFDCylIndex] = DEM_MISFIRE_KIND_INVALID;   /* [GUD]misfireFFDCylIndex */
    }

#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )     /*  [FuncSw]    */
    misfireCylinderNum = Dem_MisfireCylinderNum;
    for( misfireConfirmedOrderIndex = (Dem_MisfireCylinderNumberType)0U; misfireConfirmedOrderIndex < misfireCylinderNum; misfireConfirmedOrderIndex++ )    /* [GUD:for]misfireConfirmedOrderIndex */
    {
        Dem_MisfireComRecord.ConfirmedOrderCylList[misfireConfirmedOrderIndex] = DEM_MISFIRE_CYL_NUM_INVALID;   /* [GUD]misfireConfirmedOrderIndex */
        Dem_MisfireComRecord.OccurrenceOrderListOfConfirmedCyl[misfireConfirmedOrderIndex] = DEM_FAIL_OCCURRENCE_NUM_INVALID;   /* [GUD]misfireConfirmedOrderIndex */
    }
#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )  */

    Dem_MisfireComRecord.ConsistencyIdForEmission  = DEM_CONSISTENCY_INITIAL;
    Dem_MisfireComRecord.ConsistencyIdForCAT       = DEM_CONSISTENCY_INITIAL;
    Dem_MisfireComRecord.ClearID                = DEM_CLRINFO_RECORD_INITIAL;
    Dem_MisfireComRecord.FactoryCheck           = DEM_MISFIRE_ROMCHECK_FACTORY;

    return;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_GetAllMisfireRecordList                   */
/* Description   | Get the MisfireRecordList.                               */
/* Preconditions | none                                                     */
/* Parameters    | [out] MisfireRecordPtr :                                 */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_GetAllMisfireRecordList
(
    P2VAR( Dem_MisfireRecordType, AUTOMATIC, AUTOMATIC ) MisfireRecordPtr
)
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireEventNum;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndex;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndexNum;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndex;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndexNum;

    misfireEventNum = Dem_MisfireEventNum;

    for( misfireIndex = (Dem_u16_MisfireStrgIndexType)0U; misfireIndex < misfireEventNum; misfireIndex++ )  /* [GUD:for]misfireIndex */
    {
        MisfireRecordPtr[misfireIndex].FailedCyl                         = Dem_MisfireRecordList[misfireIndex].FailedCyl;                   /* [GUD]misfireIndex *//* [ARYCHK] DEM_MISFIRE_EVENT_NUM / 1 / misfireIndex */
        MisfireRecordPtr[misfireIndex].AccumCyl                          = Dem_MisfireRecordList[misfireIndex].AccumCyl;                    /* [GUD]misfireIndex *//* [ARYCHK] DEM_MISFIRE_EVENT_NUM / 1 / misfireIndex */
        MisfireRecordPtr[misfireIndex].AccumFailedCylThisOC              = Dem_MisfireRecordList[misfireIndex].AccumFailedCylThisOC;        /* [GUD]misfireIndex *//* [ARYCHK] DEM_MISFIRE_EVENT_NUM / 1 / misfireIndex */
        MisfireRecordPtr[misfireIndex].AccumFailedCylSinceClear          = Dem_MisfireRecordList[misfireIndex].AccumFailedCylSinceClear;    /* [GUD]misfireIndex *//* [ARYCHK] DEM_MISFIRE_EVENT_NUM / 1 / misfireIndex */
        MisfireRecordPtr[misfireIndex].AccumTestNotCompleteCylSinceClear = Dem_MisfireRecordList[misfireIndex].AccumTestNotCompleteCylSinceClear;   /* [GUD]misfireIndex *//* [ARYCHK] DEM_MISFIRE_EVENT_NUM / 1 / misfireIndex */
        MisfireRecordPtr[misfireIndex].AccumPendingCyl                   = Dem_MisfireRecordList[misfireIndex].AccumPendingCyl;             /* [GUD]misfireIndex *//* [ARYCHK] DEM_MISFIRE_EVENT_NUM / 1 / misfireIndex */
        MisfireRecordPtr[misfireIndex].AccumConfirmedCyl                 = Dem_MisfireRecordList[misfireIndex].AccumConfirmedCyl;           /* [GUD]misfireIndex *//* [ARYCHK] DEM_MISFIRE_EVENT_NUM / 1 / misfireIndex */
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
        misfireObdFFDCylIndexNum = Dem_MisfireObdFFDCylIndexNum;
        for( misfireObdFFDCylIndex = (Dem_u08_MisfireObdFFDCylIndexType)0U; misfireObdFFDCylIndex < misfireObdFFDCylIndexNum; misfireObdFFDCylIndex++ ) /* [GUD:for]misfireObdFFDCylIndex */
        {
            MisfireRecordPtr[misfireIndex].OBDFFDCyl[misfireObdFFDCylIndex] = Dem_MisfireRecordList[misfireIndex].OBDFFDCyl[misfireObdFFDCylIndex];     /* [GUD]misfireIndex *//* [GUD]misfireObdFFDCylIndex *//* [ARYCHK] DEM_MISFIRE_EVENT_NUM / 1 / misfireIndex *//* [ARYCHK] DEM_MISFIRE_OBD_FFDCYL_INDEX_NUM / 1 / misfireObdFFDCylIndex */
        }
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
        misfireFFDCylIndexNum = Dem_MisfireFFDCylIndexNum;
        for( misfireFFDCylIndex = (Dem_u08_MisfireFFDCylIndexType)0U; misfireFFDCylIndex < misfireFFDCylIndexNum; misfireFFDCylIndex++ )    /* [GUD:for]misfireFFDCylIndex */
        {
            MisfireRecordPtr[misfireIndex].FFDCyl[misfireFFDCylIndex] = Dem_MisfireRecordList[misfireIndex].FFDCyl[misfireFFDCylIndex];     /* [GUD]misfireIndex *//* [GUD]misfireFFDCylIndex *//* [ARYCHK] DEM_MISFIRE_EVENT_NUM / 1 / misfireIndex *//* [ARYCHK] DEM_MISFIRE_FFDCYL_INDEX_NUM / 1 / misfireFFDCylIndex */
        }
        MisfireRecordPtr[misfireIndex].ExceedanceCounter        = Dem_MisfireRecordList[misfireIndex].ExceedanceCounter;                /* [GUD]misfireIndex *//* [ARYCHK] DEM_MISFIRE_EVENT_NUM / 1 / misfireIndex */

        MisfireRecordPtr[misfireIndex].ClearID                  = Dem_MisfireRecordList[misfireIndex].ClearID;              /* [GUD]misfireIndex *//* [ARYCHK] DEM_MISFIRE_EVENT_NUM / 1 / misfireIndex */
        MisfireRecordPtr[misfireIndex].FactoryCheck             = DEM_MISFIRE_ROMCHECK_SAVED;                               /* [GUD]misfireIndex *//* [ARYCHK] DEM_MISFIRE_EVENT_NUM / 1 / misfireIndex */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_MisfireMng_SetMisfireRecordList                      */
/* Description   | Set the MisfireRecordList.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireIndex :                                      */
/*               | [out] MisfireRecordPtr :                                 */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetMisfireRecordList
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,                /* [PRMCHK:CALLER] */
    P2CONST( Dem_MisfireRecordType, AUTOMATIC, AUTOMATIC ) MisfireRecordPtr
)
{
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndex;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndexNum;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndex;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndexNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindMisfire;

    recMngCmnKindMisfire = Dem_RecMngCmnKindMisfire;


    Dem_MisfireRecordList[MisfireIndex].FailedCyl                         = MisfireRecordPtr->FailedCyl;    /* [GUDCHK:CALLER]MisfireIndex */
    Dem_MisfireRecordList[MisfireIndex].AccumCyl                          = MisfireRecordPtr->AccumCyl;     /* [GUDCHK:CALLER]MisfireIndex */
    Dem_MisfireRecordList[MisfireIndex].AccumFailedCylThisOC              = MisfireRecordPtr->AccumFailedCylThisOC;                 /* [GUDCHK:CALLER]MisfireIndex */
    Dem_MisfireRecordList[MisfireIndex].AccumFailedCylSinceClear          = MisfireRecordPtr->AccumFailedCylSinceClear;             /* [GUDCHK:CALLER]MisfireIndex */
    Dem_MisfireRecordList[MisfireIndex].AccumTestNotCompleteCylSinceClear = MisfireRecordPtr->AccumTestNotCompleteCylSinceClear;    /* [GUDCHK:CALLER]MisfireIndex */
    Dem_MisfireRecordList[MisfireIndex].AccumPendingCyl                   = MisfireRecordPtr->AccumPendingCyl;                      /* [GUDCHK:CALLER]MisfireIndex */
    Dem_MisfireRecordList[MisfireIndex].AccumConfirmedCyl                 = MisfireRecordPtr->AccumConfirmedCyl;                    /* [GUDCHK:CALLER]MisfireIndex */
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    misfireObdFFDCylIndexNum = Dem_MisfireObdFFDCylIndexNum;
    for( misfireObdFFDCylIndex = (Dem_u08_MisfireObdFFDCylIndexType)0U; misfireObdFFDCylIndex < misfireObdFFDCylIndexNum; misfireObdFFDCylIndex++ ) /* [GUD:for]misfireObdFFDCylIndex */
    {
        Dem_MisfireRecordList[MisfireIndex].OBDFFDCyl[misfireObdFFDCylIndex] = MisfireRecordPtr->OBDFFDCyl[misfireObdFFDCylIndex];  /* [GUDCHK:CALLER]MisfireIndex *//* [GUD]misfireObdFFDCylIndex *//* [ARYCHK] DEM_MISFIRE_OBD_FFDCYL_INDEX_NUM / 1 / misfireObdFFDCylIndex */
    }
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    misfireFFDCylIndexNum = Dem_MisfireFFDCylIndexNum;
    for( misfireFFDCylIndex = (Dem_u08_MisfireFFDCylIndexType)0U; misfireFFDCylIndex < misfireFFDCylIndexNum; misfireFFDCylIndex++ )    /* [GUD:for]misfireFFDCylIndex */
    {
        Dem_MisfireRecordList[MisfireIndex].FFDCyl[misfireFFDCylIndex] = MisfireRecordPtr->FFDCyl[misfireFFDCylIndex];  /* [GUDCHK:CALLER]MisfireIndex *//* [GUD]misfireFFDCylIndex *//* [ARYCHK] DEM_MISFIRE_FFDCYL_INDEX_NUM / 1 / misfireFFDCylIndex */
    }
    Dem_MisfireRecordList[MisfireIndex].ExceedanceCounter        = MisfireRecordPtr->ExceedanceCounter; /* [GUDCHK:CALLER]MisfireIndex */

    Dem_MisfireRecordList[MisfireIndex].ClearID                  = MisfireRecordPtr->ClearID;           /* [GUDCHK:CALLER]MisfireIndex */
    Dem_MisfireRecordList[MisfireIndex].FactoryCheck             = DEM_MISFIRE_ROMCHECK_SAVED;          /* [GUDCHK:CALLER]MisfireIndex */

    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindMisfire, ( Dem_u16_RecordIndexType )MisfireIndex );   /* [GUDCHK:CALLER]MisfireIndex */

    return;
}

/****************************************************************************/
/* Function Name | Dem_MisfireMng_ClearMisfireRecordList                    */
/* Description   | Clear the MisfireRecordList.                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireIndex :                                      */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_ClearMisfireRecordList
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex             /* [PRMCHK:CALLER] */
)
{
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndex;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndexNum;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndex;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndexNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindMisfire;


    Dem_MisfireRecordList[MisfireIndex].FailedCyl                         = DEM_MISFIRE_CYLINDER_NON;   /* [GUDCHK:CALLER]MisfireIndex */
    Dem_MisfireRecordList[MisfireIndex].AccumCyl                          = DEM_MISFIRE_CYLINDER_NON;   /* [GUDCHK:CALLER]MisfireIndex */
    Dem_MisfireRecordList[MisfireIndex].AccumFailedCylThisOC              = DEM_MISFIRE_CYLINDER_NON;   /* [GUDCHK:CALLER]MisfireIndex */
    Dem_MisfireRecordList[MisfireIndex].AccumFailedCylSinceClear          = DEM_MISFIRE_CYLINDER_NON;   /* [GUDCHK:CALLER]MisfireIndex */
    Dem_MisfireRecordList[MisfireIndex].AccumTestNotCompleteCylSinceClear = DEM_MISFIRE_CYLINDER_NON;   /* [GUDCHK:CALLER]MisfireIndex */
    Dem_MisfireRecordList[MisfireIndex].AccumPendingCyl                   = DEM_MISFIRE_CYLINDER_NON;   /* [GUDCHK:CALLER]MisfireIndex */
    Dem_MisfireRecordList[MisfireIndex].AccumConfirmedCyl                 = DEM_MISFIRE_CYLINDER_NON;   /* [GUDCHK:CALLER]MisfireIndex */
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    misfireObdFFDCylIndexNum = Dem_MisfireObdFFDCylIndexNum;
    for( misfireObdFFDCylIndex = (Dem_u08_MisfireObdFFDCylIndexType)0U; misfireObdFFDCylIndex < misfireObdFFDCylIndexNum; misfireObdFFDCylIndex++ ) /* [GUD:for]misfireObdFFDCylIndex */
    {
        Dem_MisfireRecordList[MisfireIndex].OBDFFDCyl[misfireObdFFDCylIndex] = DEM_MISFIRE_CYLINDER_NON;    /* [GUDCHK:CALLER]MisfireIndex *//* [GUD]misfireObdFFDCylIndex */
    }
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    misfireFFDCylIndexNum = Dem_MisfireFFDCylIndexNum;
    for( misfireFFDCylIndex = (Dem_u08_MisfireFFDCylIndexType)0U; misfireFFDCylIndex < misfireFFDCylIndexNum; misfireFFDCylIndex++ )    /* [GUD:for]misfireFFDCylIndex */
    {
        Dem_MisfireRecordList[MisfireIndex].FFDCyl[misfireFFDCylIndex] = DEM_MISFIRE_CYLINDER_NON;      /* [GUDCHK:CALLER]MisfireIndex *//* [GUD]misfireFFDCylIndex */
    }
    Dem_MisfireRecordList[MisfireIndex].ExceedanceCounter        = DEM_MISFIRE_EXCEEDANCECOUNTER_INIT;  /* [GUDCHK:CALLER]MisfireIndex */

    Dem_MisfireRecordList[MisfireIndex].ClearID                  = Dem_ClrInfoMng_GetObdClearID();      /* [GUDCHK:CALLER]MisfireIndex */
    Dem_MisfireRecordList[MisfireIndex].FactoryCheck             = DEM_MISFIRE_ROMCHECK_SAVED;          /* [GUDCHK:CALLER]MisfireIndex */

    recMngCmnKindMisfire = Dem_RecMngCmnKindMisfire;
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindMisfire, ( Dem_u16_RecordIndexType )MisfireIndex );

    return;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_CompareMisfireRecord                      */
/* Description   | compare Misfire record.                                  */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireIndex :                                      */
/*               |        Identification of an event by assigned EventId.   */
/*               | [in] CheckMisfireRecordPtr :                             */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | None                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_CompareMisfireRecord
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,                /* [PRMCHK:CALLER] */
    P2CONST( Dem_MisfireRecordType, AUTOMATIC, AUTOMATIC ) CheckMisfireRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfComWithFFDCyl;

    retVal = DEM_IRT_OK;

    if( Dem_MisfireRecordList[MisfireIndex].FailedCyl != CheckMisfireRecordPtr->FailedCyl )                                         /* [GUDCHK:CALLER]MisfireIndex */
    {
        retVal = DEM_IRT_NG;
    }
    else if( Dem_MisfireRecordList[MisfireIndex].AccumCyl != CheckMisfireRecordPtr->AccumCyl )                                      /* [GUDCHK:CALLER]MisfireIndex */
    {
        retVal = DEM_IRT_NG;
    }
    else if( Dem_MisfireRecordList[MisfireIndex].AccumFailedCylThisOC != CheckMisfireRecordPtr->AccumFailedCylThisOC )              /* [GUDCHK:CALLER]MisfireIndex */
    {
        retVal = DEM_IRT_NG;
    }
    else if( Dem_MisfireRecordList[MisfireIndex].AccumFailedCylSinceClear != CheckMisfireRecordPtr->AccumFailedCylSinceClear )      /* [GUDCHK:CALLER]MisfireIndex */
    {
        retVal = DEM_IRT_NG;
    }
    else if( Dem_MisfireRecordList[MisfireIndex].AccumTestNotCompleteCylSinceClear != CheckMisfireRecordPtr->AccumTestNotCompleteCylSinceClear )    /* [GUDCHK:CALLER]MisfireIndex */
    {
        retVal = DEM_IRT_NG;
    }
    else if( Dem_MisfireRecordList[MisfireIndex].AccumPendingCyl != CheckMisfireRecordPtr->AccumPendingCyl )                        /* [GUDCHK:CALLER]MisfireIndex */
    {
        retVal = DEM_IRT_NG;
    }
    else if( Dem_MisfireRecordList[MisfireIndex].AccumConfirmedCyl != CheckMisfireRecordPtr->AccumConfirmedCyl )                    /* [GUDCHK:CALLER]MisfireIndex */
    {
        retVal = DEM_IRT_NG;
    }
    else
    {
        resultOfComWithFFDCyl = Dem_MisfireMng_CmpWithFFDCyl( MisfireIndex, CheckMisfireRecordPtr );                                /* [GUDCHK:CALLER]MisfireIndex */
        if( resultOfComWithFFDCyl != DEM_IRT_OK )
        {
            retVal = DEM_IRT_NG;
        }
    }

    /* not compared member: */
    /* ExceedanceCounter, ConsistencyId, ClearID, FactoryCheck */

    return retVal;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
#if ( DEM_OBDONUDS_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_MisfireMng_CopyAllObdFFDCyl                          */
/* Description   | copy ObdFFDCyl of Misfire record.                        */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireIndexDest : MisfireRecordIndex: copy to.     */
/*               | [in] MisfireIndexSrc  : MisfireRecordIndex: copy from.   */
/*               |                                                          */
/* Return Value  | void                                                     */
/* Notes         | None                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created.based on Dem_MisfireMng_CmpWithObdFFDCyl().  */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_CopyAllObdFFDCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndexDest,    /*  [PRMCHK:CALLER] */
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndexSrc      /*  [PRMCHK:CALLER] */
)
{
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndex;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndexNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindMisfire;

    misfireObdFFDCylIndexNum = Dem_MisfireObdFFDCylIndexNum;
    recMngCmnKindMisfire = Dem_RecMngCmnKindMisfire;

    /* copy ObdFFDCyl. */
    for( misfireObdFFDCylIndex = (Dem_u08_MisfireObdFFDCylIndexType)0U; misfireObdFFDCylIndex < misfireObdFFDCylIndexNum; misfireObdFFDCylIndex++ ) /* [GUD:for]misfireObdFFDCylIndex */
    {
        Dem_MisfireRecordList[ MisfireIndexDest ].OBDFFDCyl[ misfireObdFFDCylIndex ] = Dem_MisfireRecordList[ MisfireIndexSrc ].OBDFFDCyl[ misfireObdFFDCylIndex ];   /* [GUDCHK:CALLER]MisfireIndexDest *//* [GUDCHK:CALLER]MisfireIndexSrc *//* [GUD]misfireObdFFDCylIndex */
    }

    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindMisfire, ( Dem_u16_RecordIndexType )MisfireIndexDest );   /* [GUDCHK:CALLER]MisfireIndexDest */

    return ;
}
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )   */
#endif  /* ( DEM_OBDONUDS_SUPPORT == STD_ON )               */
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )                 */

/****************************************************************************/
/* Function Name | Dem_MisfireMng_CmpWithFFDCyl                             */
/* Description   | compare FFDCyl of Misfire record.                        */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireIndex :                                      */
/*               |        Identification of an event by assigned EventId.   */
/*               | [in] CheckMisfireRecordPtr :                             */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | None                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_CmpWithFFDCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    P2CONST( Dem_MisfireRecordType, AUTOMATIC, AUTOMATIC ) CheckMisfireRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfCmpWithObdFFDCyl;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfCmpWithNonObdFFDCyl;

    retVal = DEM_IRT_NG;

#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    resultOfCmpWithObdFFDCyl = Dem_MisfireMng_CmpWithObdFFDCyl( MisfireIndex, CheckMisfireRecordPtr );
    if( resultOfCmpWithObdFFDCyl == DEM_IRT_OK )
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    {
        resultOfCmpWithNonObdFFDCyl = Dem_MisfireMng_CmpWithNonObdFFDCyl( MisfireIndex, CheckMisfireRecordPtr );
        if( resultOfCmpWithNonObdFFDCyl == DEM_IRT_OK )
        {
            /* same. */
            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_MisfireMng_CmpWithObdFFDCyl                          */
/* Description   | compare ObdFFDCyl of Misfire record.                     */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireIndex :                                      */
/*               |        Identification of an event by assigned EventId.   */
/*               | [in] CheckMisfireRecordPtr :                             */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | None                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_CmpWithObdFFDCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    P2CONST( Dem_MisfireRecordType, AUTOMATIC, AUTOMATIC ) CheckMisfireRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndex;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndexNum;

    misfireObdFFDCylIndexNum = Dem_MisfireObdFFDCylIndexNum;

    retVal = DEM_IRT_OK;    /* same. */

    /* check ObdFFDCyl. */
    for( misfireObdFFDCylIndex = (Dem_u08_MisfireObdFFDCylIndexType)0U; misfireObdFFDCylIndex < misfireObdFFDCylIndexNum; misfireObdFFDCylIndex++ ) /* [GUD:for]misfireObdFFDCylIndex */
    {
        if( Dem_MisfireRecordList[MisfireIndex].OBDFFDCyl[misfireObdFFDCylIndex] != CheckMisfireRecordPtr->OBDFFDCyl[misfireObdFFDCylIndex] )   /* [GUD]misfireObdFFDCylIndex *//* [ARYCHK] DEM_MISFIRE_OBD_FFDCYL_INDEX_NUM / 1 / misfireObdFFDCylIndex */
        {
            retVal = DEM_IRT_NG;
            break;
        }
    }

    return retVal;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */


/****************************************************************************/
/* Function Name | Dem_MisfireMng_CmpWithNonObdFFDCyl                       */
/* Description   | compare FFDCyl of Misfire record.                        */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireIndex :                                      */
/*               |        Identification of an event by assigned EventId.   */
/*               | [in] CheckMisfireRecordPtr :                             */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | None                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_CmpWithNonObdFFDCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    P2CONST( Dem_MisfireRecordType, AUTOMATIC, AUTOMATIC ) CheckMisfireRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndex;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndexNum;

    misfireFFDCylIndexNum = Dem_MisfireFFDCylIndexNum;

    retVal = DEM_IRT_OK;    /* same. */

    /* check OBD freezeframe list. */
    for( misfireFFDCylIndex = (Dem_u08_MisfireFFDCylIndexType)0U; misfireFFDCylIndex < misfireFFDCylIndexNum; misfireFFDCylIndex++ )    /* [GUD:for]misfireFFDCylIndex */
    {
        if( Dem_MisfireRecordList[MisfireIndex].FFDCyl[misfireFFDCylIndex] != CheckMisfireRecordPtr->FFDCyl[misfireFFDCylIndex] )   /* [GUD]misfireFFDCylIndex *//* [ARYCHK] DEM_MISFIRE_FFDCYL_INDEX_NUM / 1 / misfireFFDCylIndex */
        {
            retVal = DEM_IRT_NG;
            break;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_CompareMisfireComRecord                   */
/* Description   | compare MisfireCom record.                               */
/* Preconditions |                                                          */
/* Parameters    | [in] CheckMisfireComRecordPtr :                          */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | None                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_CompareMisfireComRecord
(
    P2CONST( Dem_MisfireComRecordType, AUTOMATIC, AUTOMATIC ) CheckMisfireComRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfComWithKindOfFFD;

    retVal = DEM_IRT_OK;

    if( Dem_MisfireComRecord.FirstPendingCyl != CheckMisfireComRecordPtr->FirstPendingCyl )
    {
        retVal = DEM_IRT_NG;
    }
    else if( Dem_MisfireComRecord.FirstConfirmedCyl != CheckMisfireComRecordPtr->FirstConfirmedCyl )
    {
        retVal = DEM_IRT_NG;
    }
    else if( Dem_MisfireComRecord.FirstAccumConfirmedCyl != CheckMisfireComRecordPtr->FirstAccumConfirmedCyl )
    {
        retVal = DEM_IRT_NG;
    }
    else
    {
        resultOfComWithKindOfFFD = Dem_MisfireMng_CmpWithKindOfFFD( CheckMisfireComRecordPtr );
        if( resultOfComWithKindOfFFD != DEM_IRT_OK )
        {
            retVal = DEM_IRT_NG;
        }
    }

    /* not compared member: */
    /* ConsistencyIdForCAT, ConsistencyIdForEmission, ClearID , FactoryCheck */

    /* ConfirmedOrderCylList[] and OccurrenceOrderListOfConfirmedCyl[] are not compared */
    /* because they are registered after Event is processed. */

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_CmpWithKindOfFFD                          */
/* Description   | compare KindOfFFD of MisfireCom record.                  */
/* Preconditions |                                                          */
/* Parameters    | [in] CheckMisfireComRecordPtr :                          */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | None                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_CmpWithKindOfFFD
(
    P2CONST( Dem_MisfireComRecordType, AUTOMATIC, AUTOMATIC ) CheckMisfireComRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfComWithKindOfObdFFD;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultOfComWithKindOfNonObdFFD;

    retVal = DEM_IRT_NG;

#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    resultOfComWithKindOfObdFFD = Dem_MisfireMng_CmpWithKindOfObdFFD( CheckMisfireComRecordPtr );
    if( resultOfComWithKindOfObdFFD == DEM_IRT_OK )
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    {
        resultOfComWithKindOfNonObdFFD = Dem_MisfireMng_CmpWithKindOfNonObdFFD( CheckMisfireComRecordPtr );
        if( resultOfComWithKindOfNonObdFFD == DEM_IRT_OK )
        {
            /* same. */
            retVal = DEM_IRT_OK;
        }
    }

    return retVal;
}


#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_MisfireMng_CmpWithKindOfObdFFD                       */
/* Description   | compare KindOfOBDFFD of MisfireCom record.               */
/* Preconditions |                                                          */
/* Parameters    | [in] CheckMisfireComRecordPtr :                          */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | None                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_CmpWithKindOfObdFFD
(
    P2CONST( Dem_MisfireComRecordType, AUTOMATIC, AUTOMATIC ) CheckMisfireComRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndex;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndexNum;

    misfireObdFFDCylIndexNum = Dem_MisfireObdFFDCylIndexNum;

    retVal = DEM_IRT_OK;    /* same. */

    /* check KindOfOBDFFD. */
    for( misfireObdFFDCylIndex = (Dem_u08_MisfireObdFFDCylIndexType)0U; misfireObdFFDCylIndex < misfireObdFFDCylIndexNum; misfireObdFFDCylIndex++ ) /* [GUD:for]misfireObdFFDCylIndex */
    {
        if( Dem_MisfireComRecord.MisfireKindOfOBDFFD[misfireObdFFDCylIndex] != CheckMisfireComRecordPtr->MisfireKindOfOBDFFD[misfireObdFFDCylIndex] )   /* [GUD]misfireObdFFDCylIndex *//* [ARYCHK] DEM_MISFIRE_OBD_FFDCYL_INDEX_NUM / 1 / misfireObdFFDCylIndex */
        {
            retVal = DEM_IRT_NG;
            break;
        }
    }

    return retVal;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */


/****************************************************************************/
/* Function Name | Dem_MisfireMng_CmpWithKindOfNonObdFFD                    */
/* Description   | compare KindOfOBDFFD of MisfireCom record.               */
/* Preconditions |                                                          */
/* Parameters    | [in] CheckMisfireComRecordPtr :                          */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | None                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_CmpWithKindOfNonObdFFD
(
    P2CONST( Dem_MisfireComRecordType, AUTOMATIC, AUTOMATIC ) CheckMisfireComRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndex;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndexNum;

    misfireFFDCylIndexNum = Dem_MisfireFFDCylIndexNum;

    retVal = DEM_IRT_OK;    /* same. */

    /* check eKindOfFFD. */
    for( misfireFFDCylIndex = (Dem_u08_MisfireFFDCylIndexType)0U; misfireFFDCylIndex < misfireFFDCylIndexNum; misfireFFDCylIndex++ )    /* [GUD:for]misfireFFDCylIndex */
    {
        if( Dem_MisfireComRecord.MisfireKindOfFFD[misfireFFDCylIndex] != CheckMisfireComRecordPtr->MisfireKindOfFFD[misfireFFDCylIndex] )   /* [GUD]misfireFFDCylIndex *//* [ARYCHK] DEM_MISFIRE_FFDCYL_INDEX_NUM / 1 / misfireFFDCylIndex */
        {
            retVal = DEM_IRT_NG;
            break;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_SetConsistencyIdOfMisfireRecord           */
/* Description   | Set consistenncyID.                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireIndex :                                      */
/*               | [in] ConsistencyId :                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetConsistencyIdOfMisfireRecord
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindMisfire;

    recMngCmnKindMisfire = Dem_RecMngCmnKindMisfire;

    Dem_MisfireRecordList[MisfireIndex].ConsistencyId = ConsistencyId;                                  /* [GUDCHK:CALLER]MisfireIndex */
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindMisfire, ( Dem_u16_RecordIndexType )MisfireIndex );   /* [GUDCHK:CALLER]MisfireIndex */

    return;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_SetConsistencyIdOfMisfireComForEmission   */
/* Description   | Set consistencyID.                                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] ConsistencyId :                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetConsistencyIdOfMisfireComForEmission
(
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindMisfireCom;

    recMngCmnKindMisfireCom = Dem_RecMngCmnKindMisfireCom;

    Dem_MisfireComRecord.ConsistencyIdForEmission = ConsistencyId;
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindMisfireCom, ( Dem_u16_RecordIndexType )0U );

    return;
}


#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
/****************************************************************************/
/* Function Name | Dem_MisfireMng_SetConsistencyIdOfMisfireComForCAT        */
/* Description   | Set consistencyID.                                       */
/* Preconditions | none                                                     */
/* Parameters    | [in] ConsistencyId :                                     */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetConsistencyIdOfMisfireComForCAT
(
    VAR( Dem_u08_ConsistencyIdType, AUTOMATIC ) ConsistencyId
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindMisfireCom;

    recMngCmnKindMisfireCom = Dem_RecMngCmnKindMisfireCom;

    Dem_MisfireComRecord.ConsistencyIdForCAT = ConsistencyId;
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindMisfireCom, ( Dem_u16_RecordIndexType )0U );

    return;
}
#endif  /* ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )           */


/****************************************************************************/
/* Function Name | Dem_MisfireMng_SetExceedanceCounter                      */
/* Description   | Set misfire exceedance counter.                          */
/* Preconditions |                                                          */
/* Parameters    | [in] ExceedanceCounter :                                 */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetExceedanceCounter
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u08_MisfExceedanceCounterType, AUTOMATIC ) ExceedanceCounter
)
{
    Dem_MisfireRecordList[MisfireIndex].ExceedanceCounter = ExceedanceCounter;  /* [GUDCHK:CALLER]MisfireIndex */

    return;
}

/****************************************************************************/
/* Function Name | Dem_MisfireMng_GetExceedanceCounter                      */
/* Description   | Get misfire exceedance counter.                          */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireIndex :                                      */
/*               | [out] ExceedanceCounterPtr :                             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : get of counter was successful        */
/*               |        DEM_IRT_NG : get of counter failed                */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created. based on Dem_SimilarMng_GetExceedanceCounter*/
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_GetExceedanceCounter
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    P2VAR( Dem_u08_MisfExceedanceCounterType, AUTOMATIC, AUTOMATIC ) ExceedanceCounterPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireEventNum;

    retVal = DEM_IRT_NG;
    misfireEventNum = Dem_MisfireEventNum;

    if( MisfireIndex < misfireEventNum )    /* [GUD:if]MisfireIndex */
    {
        *ExceedanceCounterPtr   =   Dem_MisfireRecordList[ MisfireIndex ].ExceedanceCounter;    /* [GUD]MisfireIndex */
        retVal = DEM_IRT_OK;
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_MisfireMng_GetFailedCyl                              */
/* Description   | Get FailedCyl.                                           */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireIndex :                                      */
/*               |        Identification of an event by assigned EventId.   */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_MisfireMng_GetFailedCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex             /* [PRMCHK:CALLER] */
)
{
    return Dem_MisfireRecordList[MisfireIndex].FailedCyl;   /* [GUDCHK:CALLER]MisfireIndex */
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_GetAccumCyl                               */
/* Description   | Get AccumCyl.                                            */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireIndex :                                      */
/*               |        Identification of an event by assigned EventId.   */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_MisfireMng_GetAccumCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex             /* [PRMCHK:CALLER] */
)
{
    return Dem_MisfireRecordList[MisfireIndex].AccumCyl;        /* [GUDCHK:CALLER]MisfireIndex */
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_GetAFCylThisOC                            */
/* Description   | Get AccumFailedCylThisOC.                                */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireIndex :                                      */
/*               |        Identification of an event by assigned EventId.   */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_MisfireMng_GetAFCylThisOC
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex             /* [PRMCHK:CALLER] */
)
{
    return Dem_MisfireRecordList[MisfireIndex].AccumFailedCylThisOC;        /* [GUDCHK:CALLER]MisfireIndex */
}

/****************************************************************************/
/* Function Name | Dem_MisfireMng_GetAccumPendingCyl                        */
/* Description   | Get AccumPendingCyl.                                     */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireIndex :                                      */
/*               |        Identification of an event by assigned EventId.   */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_MisfireMng_GetAccumPendingCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex     /* [PRMCHK:CALLER] */
)
{
    return Dem_MisfireRecordList[MisfireIndex].AccumPendingCyl;     /* [GUDCHK:CALLER]MisfireIndex */
}

/****************************************************************************/
/* Function Name | Dem_MisfireMng_GetAccumConfirmedCyl                      */
/* Description   | Get AccumConfirmedCyl.                                   */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireIndex :                                      */
/*               |        Identification of an event by assigned EventId.   */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_MisfireMng_GetAccumConfirmedCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex         /* [PRMCHK:CALLER] */
)
{
    return Dem_MisfireRecordList[MisfireIndex].AccumConfirmedCyl;       /* [GUDCHK:CALLER]MisfireIndex */
}

/****************************************************************************/
/* Function Name | Dem_MisfireMng_GetAFCySinceClear                         */
/* Description   | Get AccumFailedCylSinceClear.                            */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireIndex :                                      */
/*               |        Identification of an event by assigned EventId.   */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_MisfireMng_GetAFCySinceClear
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex                 /* [PRMCHK:CALLER] */
)
{
    return Dem_MisfireRecordList[MisfireIndex].AccumFailedCylSinceClear;        /* [GUDCHK:CALLER]MisfireIndex */
}

#if ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_MisfireMng_GetATNCCySinceClear                       */
/* Description   | Get AccumTestNotCompleteCylSinceClear.                   */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireIndex :                                      */
/*               |        Identification of an event by assigned EventId.   */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_MisfireMng_GetATNCCySinceClear
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex                     /* [PRMCHK:CALLER] */
)
{
    return Dem_MisfireRecordList[MisfireIndex].AccumTestNotCompleteCylSinceClear;   /* [GUDCHK:CALLER]MisfireIndex */
}
#endif  /*  ( DEM_MISFIRE_CAT_EVENT_CONFIGURED == STD_ON )  */

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_MisfireMng_GetObdFFDCyl                              */
/* Description   | Get OBDFFDCyl.                                           */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireIndex :                                      */
/*               |        Identification of an event by assigned EventId.   */
/* Parameters    | [in] MisfireObdFFDCylIndex :                             */
/*               |        OBD FFD Cylinder Index.                           */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_MisfireMng_GetObdFFDCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,                    /* [PRMCHK:CALLER] */
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex       /* [PRMCHK:CALLER] */
)
{
    return Dem_MisfireRecordList[MisfireIndex].OBDFFDCyl[MisfireObdFFDCylIndex];    /* [GUDCHK:CALLER]MisfireIndex *//* [GUDCHK:CALLER]MisfireObdFFDCylIndex */
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

/****************************************************************************/
/* Function Name | Dem_MisfireMng_GetFFDCyl                                 */
/* Description   | Get FFDCyl.                                              */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireIndex :                                      */
/*               |        Identification of an event by assigned EventId.   */
/* Parameters    | [in] MisfireFFDCylIndex :                                */
/*               |        FFD Cylinder Index.                               */
/* Return Value  | Dem_MisfireCylinderType                                  */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_MisfireCylinderType, DEM_CODE ) Dem_MisfireMng_GetFFDCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) MisfireFFDCylIndex     /* [PRMCHK:CALLER] */
)
{
    return Dem_MisfireRecordList[MisfireIndex].FFDCyl[MisfireFFDCylIndex];  /* [GUDCHK:CALLER]MisfireIndex *//* [GUDCHK:CALLER]MisfireFFDCylIndex */
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_MisfireMng_GetMisfireKindOfObdFFD                    */
/* Description   | Get misfire kind of Obd FFD.                             */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireObdFFDCylIndex :                             */
/*               |        OBD FFD Cylinder Index.                           */
/* Return Value  | Dem_u08_MisfireKindType                                  */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_MisfireKindType, DEM_CODE ) Dem_MisfireMng_GetMisfireKindOfObdFFD
(
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex   /* [PRMCHK:CALLER] */
)
{
    return Dem_MisfireComRecord.MisfireKindOfOBDFFD[MisfireObdFFDCylIndex]; /* [GUDCHK:CALLER]MisfireObdFFDCylIndex */
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

/****************************************************************************/
/* Function Name | Dem_MisfireMng_GetMisfireKindOfFFD                       */
/* Description   | Get misfire kind of FFD.                                 */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireFFDCylIndex :                                */
/*               |        FFD Cylinder Index.                               */
/* Return Value  | Dem_u08_MisfireKindType                                  */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_MisfireKindType, DEM_CODE ) Dem_MisfireMng_GetMisfireKindOfFFD
(
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) MisfireFFDCylIndex     /* [PRMCHK:CALLER] */
)
{
    return Dem_MisfireComRecord.MisfireKindOfFFD[MisfireFFDCylIndex];   /* [GUDCHK:CALLER]MisfireFFDCylIndex */
}

#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_MisfireMng_GetConfirmedOrderCyl                      */
/* Description   | Get misfire confirmed order cylinder.                    */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireConfirmedOrderIndex :                        */
/*               |        misfire confirmed order.                          */
/* Return Value  | Dem_MisfireCylinderNumberType                            */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_MisfireCylinderNumberType, DEM_CODE ) Dem_MisfireMng_GetConfirmedOrderCyl
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireConfirmedOrderIndex  /* [PRMCHK:CALLER] */
)
{
    return Dem_MisfireComRecord.ConfirmedOrderCylList[MisfireConfirmedOrderIndex];  /* [GUDCHK:CALLER]MisfireConfirmedOrderIndex */
}

/****************************************************************************/
/* Function Name | Dem_MisfireMng_GetConfirmedOccurrenceOrder               */
/* Description   | Get misfire occurrence order.                            */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireConfirmedOrderIndex :                        */
/*               |        misfire confirmed order.                          */
/* Return Value  | Dem_u16_OccrOrderType                                    */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u16_OccrOrderType, DEM_CODE ) Dem_MisfireMng_GetConfirmedOccurrenceOrder
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) MisfireConfirmedOrderIndex  /* [PRMCHK:CALLER] */
)
{
    return Dem_MisfireComRecord.OccurrenceOrderListOfConfirmedCyl[MisfireConfirmedOrderIndex];  /* [GUDCHK:CALLER]MisfireConfirmedOrderIndex */
}
#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )  */


#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_MisfireMng_InitObdFFDCyl                             */
/* Description   | Initialize OBDFFDCyl.                                    */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireIndex :                                      */
/*               |        Identification of an event by assigned EventId.   */
/* Parameters    | [in] MisfireObdFFDCylIndex :                             */
/*               |        OBD FFD Cylinder Index.                           */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_InitObdFFDCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,                /* [PRMCHK:CALLER] */
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex   /* [PRMCHK:CALLER] */
)
{
    Dem_MisfireRecordList[MisfireIndex].OBDFFDCyl[MisfireObdFFDCylIndex] = DEM_MISFIRE_CYLINDER_NON;    /* [GUDCHK:CALLER]MisfireIndex *//* [GUDCHK:CALLER]MisfireObdFFDCylIndex */

    return;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

/****************************************************************************/
/* Function Name | Dem_MisfireMng_InitFFDCyl                                */
/* Description   | Initialize FFDCyl.                                       */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireIndex :                                      */
/*               |        Identification of an event by assigned EventId.   */
/* Parameters    | [in] MisfireFFDCylIndex :                                */
/*               |        FFD Cylinder Index.                               */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_InitFFDCyl
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,            /* [PRMCHK:CALLER] */
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) MisfireFFDCylIndex     /* [PRMCHK:CALLER] */
)
{
    Dem_MisfireRecordList[MisfireIndex].FFDCyl[MisfireFFDCylIndex] = DEM_MISFIRE_CYLINDER_NON;  /* [GUDCHK:CALLER]MisfireIndex *//* [GUDCHK:CALLER]MisfireFFDCylIndex */

    return;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_MisfireMng_InitMisfireKindOfObdFFD                   */
/* Description   | Initialize misfire kind of Obd FFD.                      */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireObdFFDCylIndex :                             */
/*               |        OBD FFD Cylinder Index.                           */
/* Return Value  | Dem_u08_MisfireKindType                                  */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_InitMisfireKindOfObdFFD
(
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex       /* [PRMCHK:CALLER] */
)
{
    Dem_MisfireComRecord.MisfireKindOfOBDFFD[MisfireObdFFDCylIndex] = DEM_MISFIRE_KIND_INVALID; /* [GUDCHK:CALLER]MisfireObdFFDCylIndex */

    return;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

/****************************************************************************/
/* Function Name | Dem_MisfireMng_InitMisfireKindOfFFD                      */
/* Description   | Initialize misfire kind of FFD.                          */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireFFDCylIndex :                                */
/*               |        FFD Cylinder Index.                               */
/* Return Value  | Dem_u08_MisfireKindType                                  */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_InitMisfireKindOfFFD
(
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) MisfireFFDCylIndex     /* [PRMCHK:CALLER] */
)
{
    Dem_MisfireComRecord.MisfireKindOfFFD[MisfireFFDCylIndex] = DEM_MISFIRE_KIND_INVALID;   /* [GUDCHK:CALLER]MisfireFFDCylIndex */

    return;
}

#if ( DEM_OBDFFD_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_MisfireMng_SetMisfireKindOfObdFFD                    */
/* Description   | Set misfire kind of Obd FFD.                             */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireObdFFDCylIndex :                             */
/*               |        OBD FFD Cylinder Index.                           */
/* Return Value  | Dem_u08_MisfireKindType                                  */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetMisfireKindOfObdFFD
(
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) MisfireObdFFDCylIndex,      /* [PRMCHK:CALLER] */
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) MisfireType
)
{
    Dem_MisfireComRecord.MisfireKindOfOBDFFD[MisfireObdFFDCylIndex] = MisfireType;  /* [GUDCHK:CALLER]MisfireObdFFDCylIndex */

    return;
}
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

/****************************************************************************/
/* Function Name | Dem_MisfireMng_SetMisfireKindOfFFD                       */
/* Description   | Set misfire kind of FFD.                                 */
/* Preconditions |                                                          */
/* Parameters    | [in] MisfireFFDCylIndex :                                */
/*               |        FFD Cylinder Index.                               */
/* Return Value  | Dem_u08_MisfireKindType                                  */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetMisfireKindOfFFD
(
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) MisfireFFDCylIndex,        /* [PRMCHK:CALLER] */
    VAR( Dem_u08_MisfireKindType, AUTOMATIC ) MisfireType
)
{
    Dem_MisfireComRecord.MisfireKindOfFFD[MisfireFFDCylIndex] = MisfireType;    /* [GUDCHK:CALLER]MisfireFFDCylIndex */

    return;
}

/****************************************************************************/
/* Function Name | Dem_MisfireMng_GetMisfireComRecord                       */
/* Description   |                                                          */
/* Preconditions | none                                                     */
/* Parameters    | [out] MisfireComRecordPtr :                              */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-6-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_GetMisfireComRecord
(
    P2VAR( Dem_MisfireComRecordType, AUTOMATIC, AUTOMATIC ) MisfireComRecordPtr
)
{
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndex;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndexNum;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndex;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndexNum;
#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )     /*  [FuncSw]    */
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireConfirmedOrderIndex;
#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )  */

    MisfireComRecordPtr->FirstPendingCyl        = Dem_MisfireComRecord.FirstPendingCyl;
    MisfireComRecordPtr->FirstConfirmedCyl      = Dem_MisfireComRecord.FirstConfirmedCyl;
    MisfireComRecordPtr->FirstAccumConfirmedCyl = Dem_MisfireComRecord.FirstAccumConfirmedCyl;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    misfireObdFFDCylIndexNum = Dem_MisfireObdFFDCylIndexNum;
    for( misfireObdFFDCylIndex = (Dem_u08_MisfireObdFFDCylIndexType)0U; misfireObdFFDCylIndex < misfireObdFFDCylIndexNum; misfireObdFFDCylIndex++ ) /* [GUD:for]misfireObdFFDCylIndex */
    {
        MisfireComRecordPtr->MisfireKindOfOBDFFD[misfireObdFFDCylIndex] = Dem_MisfireComRecord.MisfireKindOfOBDFFD[misfireObdFFDCylIndex];  /* [GUD]misfireObdFFDCylIndex *//* [ARYCHK] DEM_MISFIRE_OBD_FFDCYL_INDEX_NUM / 1 / misfireObdFFDCylIndex */
    }
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    misfireFFDCylIndexNum = Dem_MisfireFFDCylIndexNum;
    for( misfireFFDCylIndex = (Dem_u08_MisfireFFDCylIndexType)0U; misfireFFDCylIndex < misfireFFDCylIndexNum; misfireFFDCylIndex++ )    /* [GUD:for]misfireFFDCylIndex */
    {
        MisfireComRecordPtr->MisfireKindOfFFD[misfireFFDCylIndex] = Dem_MisfireComRecord.MisfireKindOfFFD[misfireFFDCylIndex];  /* [GUD]misfireFFDCylIndex *//* [ARYCHK] DEM_MISFIRE_FFDCYL_INDEX_NUM / 1 / misfireFFDCylIndex */
    }

#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )     /*  [FuncSw]    */
    misfireCylinderNum = Dem_MisfireCylinderNum;
    for( misfireConfirmedOrderIndex = (Dem_MisfireCylinderNumberType)0U; misfireConfirmedOrderIndex < misfireCylinderNum; misfireConfirmedOrderIndex++ )    /* [GUD:for]misfireConfirmedOrderIndex */
    {
        MisfireComRecordPtr->ConfirmedOrderCylList[misfireConfirmedOrderIndex] = Dem_MisfireComRecord.ConfirmedOrderCylList[misfireConfirmedOrderIndex];    /* [GUD]misfireConfirmedOrderIndex *//* [ARYCHK] DEM_MISFIRE_CYLINDER_AND_RM_NUM / 1 / misfireConfirmedOrderIndex */
        MisfireComRecordPtr->OccurrenceOrderListOfConfirmedCyl[misfireConfirmedOrderIndex] = Dem_MisfireComRecord.OccurrenceOrderListOfConfirmedCyl[misfireConfirmedOrderIndex];    /* [GUD]misfireConfirmedOrderIndex *//* [ARYCHK] DEM_MISFIRE_CYLINDER_AND_RM_NUM / 1 / misfireConfirmedOrderIndex */
    }
#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )  */

    MisfireComRecordPtr->ConsistencyIdForEmission     = Dem_MisfireComRecord.ConsistencyIdForEmission;
    MisfireComRecordPtr->ConsistencyIdForCAT          = Dem_MisfireComRecord.ConsistencyIdForCAT;

    MisfireComRecordPtr->ClearID                = Dem_MisfireComRecord.ClearID;
    MisfireComRecordPtr->FactoryCheck           = DEM_MISFIRE_ROMCHECK_SAVED;

    return;
}

/****************************************************************************/
/* Function Name | Dem_MisfireMng_SetMisfireComRecord                       */
/* Description   | Set the MisfireComRecord.                                */
/* Preconditions | none                                                     */
/* Parameters    | [out] MisfireComRecordPtr :                              */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-6-0      | branch changed.                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetMisfireComRecord
(
    P2CONST( Dem_MisfireComRecordType, AUTOMATIC, AUTOMATIC ) MisfireComRecordPtr
)
{
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndex;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndexNum;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndex;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndexNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindMisfireCom;
#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )     /*  [FuncSw]    */
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireConfirmedOrderIndex;
#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )  */


    Dem_MisfireComRecord.FirstPendingCyl        = MisfireComRecordPtr->FirstPendingCyl;
    Dem_MisfireComRecord.FirstConfirmedCyl      = MisfireComRecordPtr->FirstConfirmedCyl;
    Dem_MisfireComRecord.FirstAccumConfirmedCyl = MisfireComRecordPtr->FirstAccumConfirmedCyl;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    misfireObdFFDCylIndexNum = Dem_MisfireObdFFDCylIndexNum;
    for( misfireObdFFDCylIndex = (Dem_u08_MisfireObdFFDCylIndexType)0U; misfireObdFFDCylIndex < misfireObdFFDCylIndexNum; misfireObdFFDCylIndex++ ) /* [GUD:for]misfireObdFFDCylIndex */
    {
        Dem_MisfireComRecord.MisfireKindOfOBDFFD[misfireObdFFDCylIndex] = MisfireComRecordPtr->MisfireKindOfOBDFFD[misfireObdFFDCylIndex];  /* [GUD]misfireObdFFDCylIndex *//* [ARYCHK] DEM_MISFIRE_OBD_FFDCYL_INDEX_NUM / 1 / misfireObdFFDCylIndex */
    }
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    misfireFFDCylIndexNum = Dem_MisfireFFDCylIndexNum;
    for( misfireFFDCylIndex = (Dem_u08_MisfireFFDCylIndexType)0U; misfireFFDCylIndex < misfireFFDCylIndexNum; misfireFFDCylIndex++ )    /* [GUD:for]misfireFFDCylIndex */
    {
        Dem_MisfireComRecord.MisfireKindOfFFD[misfireFFDCylIndex] = MisfireComRecordPtr->MisfireKindOfFFD[misfireFFDCylIndex];          /* [GUD]misfireFFDCylIndex *//* [ARYCHK] DEM_MISFIRE_FFDCYL_INDEX_NUM / 1 / misfireFFDCylIndex */
    }

#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )     /*  [FuncSw]    */
    misfireCylinderNum = Dem_MisfireCylinderNum;
    for( misfireConfirmedOrderIndex = (Dem_MisfireCylinderNumberType)0U; misfireConfirmedOrderIndex < misfireCylinderNum; misfireConfirmedOrderIndex++ )    /* [GUD:for]misfireConfirmedOrderIndex */
    {
        Dem_MisfireComRecord.ConfirmedOrderCylList[misfireConfirmedOrderIndex] = MisfireComRecordPtr->ConfirmedOrderCylList[misfireConfirmedOrderIndex];    /* [GUD]misfireConfirmedOrderIndex *//* [ARYCHK] DEM_MISFIRE_CYLINDER_AND_RM_NUM / 1 / misfireConfirmedOrderIndex */
        Dem_MisfireComRecord.OccurrenceOrderListOfConfirmedCyl[misfireConfirmedOrderIndex] = MisfireComRecordPtr->OccurrenceOrderListOfConfirmedCyl[misfireConfirmedOrderIndex];    /* [GUD]misfireConfirmedOrderIndex *//* [ARYCHK] DEM_MISFIRE_CYLINDER_AND_RM_NUM / 1 / misfireConfirmedOrderIndex */
    }
#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )  */

    Dem_MisfireComRecord.ClearID                = MisfireComRecordPtr->ClearID;
    Dem_MisfireComRecord.FactoryCheck           = DEM_MISFIRE_ROMCHECK_SAVED;

    recMngCmnKindMisfireCom = Dem_RecMngCmnKindMisfireCom;
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindMisfireCom, ( Dem_u16_RecordIndexType )0U );

    return;
}

#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )     /*  [FuncSw]    */
/****************************************************************************/
/* Function Name | Dem_MisfireMng_SetConfirmedOrderCyl                      */
/* Description   | Set the ConfirmedOrderCyl.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] ConfirmedOrderCylIndex :                            */
/*               | [in] ConfirmedOrderCyl :                                 */
/*               | [in] ConfirmedOccurrenceOrder :                          */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetConfirmedOrderCyl
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) ConfirmedOrderCylIndex,
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) ConfirmedOrderCyl,
    VAR( Dem_u16_OccrOrderType, AUTOMATIC ) ConfirmedOccurrenceOrder
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindMisfireCom;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;

    misfireCylinderNum = Dem_MisfireCylinderNum;
    if( ConfirmedOrderCylIndex < misfireCylinderNum )   /* [GUD:if]ConfirmedOrderCylIndex */
    {
        Dem_MisfireComRecord.ConfirmedOrderCylList[ConfirmedOrderCylIndex] = ConfirmedOrderCyl; /* [GUD]ConfirmedOrderCylIndex */
        Dem_MisfireComRecord.OccurrenceOrderListOfConfirmedCyl[ConfirmedOrderCylIndex] = ConfirmedOccurrenceOrder; /* [GUD]ConfirmedOrderCylIndex */
    }

    recMngCmnKindMisfireCom = Dem_RecMngCmnKindMisfireCom;
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindMisfireCom, ( Dem_u16_RecordIndexType )0U );

    return;
}
#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )  */

/****************************************************************************/
/* Function Name | Dem_MisfireMng_ClearMisfireComRecord                     */
/* Description   | Clear the MisfireComRecord.                              */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-6-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_ClearMisfireComRecord
(void)
{
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndex;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndexNum;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndex;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndexNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindMisfireCom;
#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )     /*  [FuncSw]    */
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireConfirmedOrderIndex;
#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )  */

    Dem_MisfireComRecord.FirstPendingCyl        = DEM_MISFIRE_CYLINDER_NON;
    Dem_MisfireComRecord.FirstConfirmedCyl      = DEM_MISFIRE_CYLINDER_NON;
    Dem_MisfireComRecord.FirstAccumConfirmedCyl = DEM_MISFIRE_CYLINDER_NON;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    misfireObdFFDCylIndexNum = Dem_MisfireObdFFDCylIndexNum;
    for( misfireObdFFDCylIndex = (Dem_u08_MisfireObdFFDCylIndexType)0U; misfireObdFFDCylIndex < misfireObdFFDCylIndexNum; misfireObdFFDCylIndex++ ) /* [GUD:for]misfireObdFFDCylIndex */
    {
        Dem_MisfireComRecord.MisfireKindOfOBDFFD[misfireObdFFDCylIndex] = DEM_MISFIRE_KIND_INVALID;     /* [GUD]misfireObdFFDCylIndex */
    }
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    misfireFFDCylIndexNum = Dem_MisfireFFDCylIndexNum;
    for( misfireFFDCylIndex = (Dem_u08_MisfireFFDCylIndexType)0U; misfireFFDCylIndex < misfireFFDCylIndexNum; misfireFFDCylIndex++ )    /* [GUD:for]misfireFFDCylIndex */
    {
        Dem_MisfireComRecord.MisfireKindOfFFD[misfireFFDCylIndex] = DEM_MISFIRE_KIND_INVALID;           /* [GUD]misfireFFDCylIndex */
    }

#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )     /*  [FuncSw]    */
    misfireCylinderNum = Dem_MisfireCylinderNum;
    for( misfireConfirmedOrderIndex = (Dem_MisfireCylinderNumberType)0U; misfireConfirmedOrderIndex < misfireCylinderNum; misfireConfirmedOrderIndex++ )    /* [GUD:for]misfireConfirmedOrderIndex */
    {
        Dem_MisfireComRecord.ConfirmedOrderCylList[misfireConfirmedOrderIndex] = DEM_MISFIRE_CYL_NUM_INVALID;   /* [GUD]misfireConfirmedOrderIndex */
        Dem_MisfireComRecord.OccurrenceOrderListOfConfirmedCyl[misfireConfirmedOrderIndex] = DEM_FAIL_OCCURRENCE_NUM_INVALID;   /* [GUD]misfireConfirmedOrderIndex */
    }
#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )  */

    Dem_MisfireComRecord.ClearID                = Dem_ClrInfoMng_GetObdClearID();
    Dem_MisfireComRecord.FactoryCheck           = DEM_MISFIRE_ROMCHECK_SAVED;
    recMngCmnKindMisfireCom = Dem_RecMngCmnKindMisfireCom;
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindMisfireCom, ( Dem_u16_RecordIndexType )0U );

    return;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_MisfireRecordInit                         */
/* Description   | Initialize savedzone process of Misfire record.          */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_MisfireRecordInit
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    /* [FuncSw] */
    Dem_MisfireMng_InitMisfireMirrorRecord();
#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */

    return;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_MisfireComRecordInit                      */
/* Description   | Initialize savedzone process of MisfireCom record.       */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_MisfireComRecordInit
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    /* [FuncSw] */
    Dem_MisfireMng_InitMisfireComMirrorRecord();
#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */

    return;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_MisfireMng_SetMisfireRecordMirror                    */
/* Description   | Set the Writing RamData.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in/out] BlockMirrorPtr :                                */
/*               |        Nonvolatile synchronous data information.         */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetMisfireRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    Dem_MisfireMng_GetMisfireRecordList( (Dem_u16_MisfireStrgIndexType)BlockMirrorPtr->RecordIndex, &Dem_TmpMisfireMirror );

    BlockMirrorPtr->MirrorPtr = &Dem_TmpMisfireMirror;

    return;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_SetMisfireComRecordMirror                 */
/* Description   | Set the Writing RamData.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in/out] BlockMirrorPtr :                                */
/*               |        Nonvolatile synchronous data information.         */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetMisfireComRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    Dem_MisfireMng_GetMisfireComRecord( &Dem_TmpMisfireComMirror );

    BlockMirrorPtr->MirrorPtr = &Dem_TmpMisfireComMirror;

    return;
}


#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_MisfireMng_InitMisfireMirrorRecord                   */
/* Description   | Initializes the Mirror Memory of Misfire record.         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MisfireMng_InitMisfireMirrorRecord
( void )
{
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndex;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndexNum;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndex;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndexNum;


    /* Initializes the mirror memory. */
    Dem_TmpMisfireMirror.FailedCyl                          = DEM_MISFIRE_CYLINDER_NON;
    Dem_TmpMisfireMirror.AccumCyl                           = DEM_MISFIRE_CYLINDER_NON;
    Dem_TmpMisfireMirror.AccumFailedCylThisOC               = DEM_MISFIRE_CYLINDER_NON;
    Dem_TmpMisfireMirror.AccumFailedCylSinceClear           = DEM_MISFIRE_CYLINDER_NON;
    Dem_TmpMisfireMirror.AccumTestNotCompleteCylSinceClear  = DEM_MISFIRE_CYLINDER_NON;
    Dem_TmpMisfireMirror.AccumPendingCyl                    = DEM_MISFIRE_CYLINDER_NON;
    Dem_TmpMisfireMirror.AccumConfirmedCyl                  = DEM_MISFIRE_CYLINDER_NON;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    misfireObdFFDCylIndexNum = Dem_MisfireObdFFDCylIndexNum;
    for( misfireObdFFDCylIndex = (Dem_u08_MisfireObdFFDCylIndexType)0U; misfireObdFFDCylIndex < misfireObdFFDCylIndexNum; misfireObdFFDCylIndex++ ) /* [GUD:for]misfireObdFFDCylIndex */
    {
        Dem_TmpMisfireMirror.OBDFFDCyl[misfireObdFFDCylIndex] = DEM_MISFIRE_CYLINDER_NON;   /* [GUD]misfireObdFFDCylIndex */
    }
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    misfireFFDCylIndexNum = Dem_MisfireFFDCylIndexNum;
    for( misfireFFDCylIndex = (Dem_u08_MisfireFFDCylIndexType)0U; misfireFFDCylIndex < misfireFFDCylIndexNum; misfireFFDCylIndex++ )    /* [GUD:for]misfireFFDCylIndex */
    {
        Dem_TmpMisfireMirror.FFDCyl[misfireFFDCylIndex] = DEM_MISFIRE_CYLINDER_NON;         /* [GUD]misfireFFDCylIndex */
    }
    Dem_TmpMisfireMirror.ExceedanceCounter        = DEM_MISFIRE_EXCEEDANCECOUNTER_INIT;

    Dem_TmpMisfireMirror.ConsistencyId            = DEM_CONSISTENCY_INITIAL;
    Dem_TmpMisfireMirror.ClearID                  = DEM_CLRINFO_RECORD_INITIAL;
    Dem_TmpMisfireMirror.FactoryCheck             = DEM_MISFIRE_ROMCHECK_SAVED;

#if ( DEM_MISFIRE_RECORD_PADDING_EXIST == STD_ON )
    Dem_MisfireMng_InitPaddingMisfire( &Dem_TmpMisfireMirror );
#endif /* ( DEM_MISFIRE_RECORD_PADDING_EXIST == STD_ON ) */

    return;
}


#if ( DEM_MISFIRE_RECORD_PADDING_EXIST == STD_ON )
/****************************************************************************/
/* Function Name | Dem_MisfireMng_InitPaddingMisfire                        */
/* Description   | Initializes the record padding data.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireRecordPtr    :                               */
/*               |       The pointer of the record.                         */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MisfireMng_InitPaddingMisfire
(
    P2VAR( Dem_MisfireRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) MisfireRecordPtr
)
{
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingSize;
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingIndex;

    paddingSize = Dem_MisfireRecordBlockPaddingSize;

    for( paddingIndex = (Dem_u16_PaddingIndexType)0U; paddingIndex < paddingSize; paddingIndex++ )  /* [GUD:for]paddingIndex */
    {
        MisfireRecordPtr->Reserve[paddingIndex] = DEM_DATA_RESERVE_INITIAL_VALUE;   /* [GUD]paddingIndex *//* [ARYCHK] DEM_MISFIRE_RECORD_PADDINGSIZE_TO_BLOCKSIZE / 1 / paddingIndex */
    }

    return;
}
#endif /* ( DEM_MISFIRE_RECORD_PADDING_EXIST == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_MisfireMng_InitMisfireComMirrorRecord                */
/* Description   | Initializes the Mirror Memory of MisfireCom record.      */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-6-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MisfireMng_InitMisfireComMirrorRecord
( void )
{
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndex;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndexNum;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndex;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndexNum;
#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )     /*  [FuncSw]    */
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireConfirmedOrderIndex;
#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )  */

    Dem_TmpMisfireComMirror.FirstPendingCyl        = DEM_MISFIRE_CYLINDER_NON;
    Dem_TmpMisfireComMirror.FirstConfirmedCyl      = DEM_MISFIRE_CYLINDER_NON;
    Dem_TmpMisfireComMirror.FirstAccumConfirmedCyl = DEM_MISFIRE_CYLINDER_NON;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    misfireObdFFDCylIndexNum = Dem_MisfireObdFFDCylIndexNum;
    for( misfireObdFFDCylIndex = (Dem_u08_MisfireObdFFDCylIndexType)0U; misfireObdFFDCylIndex < misfireObdFFDCylIndexNum; misfireObdFFDCylIndex++ ) /* [GUD:for]misfireObdFFDCylIndex */
    {
        Dem_TmpMisfireComMirror.MisfireKindOfOBDFFD[misfireObdFFDCylIndex] = DEM_MISFIRE_KIND_INVALID;      /* [GUD]misfireObdFFDCylIndex */
    }
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    misfireFFDCylIndexNum = Dem_MisfireFFDCylIndexNum;
    for( misfireFFDCylIndex = (Dem_u08_MisfireFFDCylIndexType)0U; misfireFFDCylIndex < misfireFFDCylIndexNum; misfireFFDCylIndex++ )    /* [GUD:for]misfireFFDCylIndex */
    {
        Dem_TmpMisfireComMirror.MisfireKindOfFFD[misfireFFDCylIndex] = DEM_MISFIRE_KIND_INVALID;            /* [GUD]misfireFFDCylIndex */
    }

#if ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )     /*  [FuncSw]    */
    misfireCylinderNum = Dem_MisfireCylinderNum;
    for( misfireConfirmedOrderIndex = (Dem_MisfireCylinderNumberType)0U; misfireConfirmedOrderIndex < misfireCylinderNum; misfireConfirmedOrderIndex++ )    /* [GUD:for]misfireConfirmedOrderIndex */
    {
        Dem_TmpMisfireComMirror.ConfirmedOrderCylList[misfireConfirmedOrderIndex] = DEM_MISFIRE_CYL_NUM_INVALID;    /* [GUD]misfireConfirmedOrderIndex */
        Dem_TmpMisfireComMirror.OccurrenceOrderListOfConfirmedCyl[misfireConfirmedOrderIndex] = DEM_FAIL_OCCURRENCE_NUM_INVALID;    /* [GUD]misfireConfirmedOrderIndex */
    }
#endif  /* ( DEM_GET_UDSDTC_BY_CONFIRMED_ORDER_SUPPORT == STD_ON )  */

    Dem_TmpMisfireComMirror.ConsistencyIdForEmission = DEM_CONSISTENCY_INITIAL;
    Dem_TmpMisfireComMirror.ConsistencyIdForCAT      = DEM_CONSISTENCY_INITIAL;
    Dem_TmpMisfireComMirror.ClearID                = DEM_CLRINFO_RECORD_INITIAL;
    Dem_TmpMisfireComMirror.FactoryCheck           = DEM_MISFIRE_ROMCHECK_SAVED;

#if ( DEM_MISFIRECOM_RECORD_PADDING_EXIST == STD_ON )
    Dem_MisfireMng_InitPaddingMisfireCom( &Dem_TmpMisfireComMirror );
#endif /* ( DEM_MISFIRECOM_RECORD_PADDING_EXIST == STD_ON ) */

    return;
}


#if ( DEM_MISFIRECOM_RECORD_PADDING_EXIST == STD_ON )
/****************************************************************************/
/* Function Name | Dem_MisfireMng_InitPaddingMisfireCom                     */
/* Description   | Initializes the record padding data.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireComRecordPtr    :                            */
/*               |       The pointer of the record.                         */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MisfireMng_InitPaddingMisfireCom
(
    P2VAR( Dem_MisfireComRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) MisfireComRecordPtr
)
{
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingSize;
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingIndex;

    paddingSize = Dem_MisfireComRecordBlockPaddingSize;

    for( paddingIndex = (Dem_u16_PaddingIndexType)0U; paddingIndex < paddingSize; paddingIndex++ )  /* [GUD:for]paddingIndex */
    {
        MisfireComRecordPtr->Reserve[paddingIndex] = DEM_DATA_RESERVE_INITIAL_VALUE;    /* [GUD]paddingIndex *//* [ARYCHK] DEM_MISFIRECOM_RECORD_PADDINGSIZE_TO_BLOCKSIZE / 1 / paddingIndex */
    }

    return;
}
#endif /* ( DEM_MISFIRECOM_RECORD_PADDING_EXIST == STD_ON ) */


/****************************************************************************/
/* Function Name | Dem_MisfireMng_GetMisfireRecordList                      */
/* Description   | Get the MisfireRecordList.                               */
/* Preconditions | none                                                     */
/* Parameters    | [out] MisfireRecordPtr :                                 */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MisfireMng_GetMisfireRecordList
(
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) MisfireIndex,
    P2VAR( Dem_MisfireRecordType, AUTOMATIC, AUTOMATIC ) MisfireRecordPtr
)
{
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireEventNum;
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndex;
    VAR( Dem_u08_MisfireObdFFDCylIndexType, AUTOMATIC ) misfireObdFFDCylIndexNum;
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndex;
    VAR( Dem_u08_MisfireFFDCylIndexType, AUTOMATIC ) misfireFFDCylIndexNum;

    misfireEventNum = Dem_MisfireEventNum;

    if( MisfireIndex < misfireEventNum )    /* [GUD:if]MisfireIndex */
    {
        MisfireRecordPtr->FailedCyl                         = Dem_MisfireRecordList[MisfireIndex].FailedCyl;                            /* [GUD]MisfireIndex */
        MisfireRecordPtr->AccumCyl                          = Dem_MisfireRecordList[MisfireIndex].AccumCyl;                             /* [GUD]MisfireIndex */
        MisfireRecordPtr->AccumFailedCylThisOC              = Dem_MisfireRecordList[MisfireIndex].AccumFailedCylThisOC;                 /* [GUD]MisfireIndex */
        MisfireRecordPtr->AccumFailedCylSinceClear          = Dem_MisfireRecordList[MisfireIndex].AccumFailedCylSinceClear;             /* [GUD]MisfireIndex */
        MisfireRecordPtr->AccumTestNotCompleteCylSinceClear = Dem_MisfireRecordList[MisfireIndex].AccumTestNotCompleteCylSinceClear;    /* [GUD]MisfireIndex */
        MisfireRecordPtr->AccumPendingCyl                   = Dem_MisfireRecordList[MisfireIndex].AccumPendingCyl;                      /* [GUD]MisfireIndex */
        MisfireRecordPtr->AccumConfirmedCyl                 = Dem_MisfireRecordList[MisfireIndex].AccumConfirmedCyl;                    /* [GUD]MisfireIndex */
#if ( DEM_OBDFFD_SUPPORT == STD_ON )    /*  [FuncSw]    */
        misfireObdFFDCylIndexNum = Dem_MisfireObdFFDCylIndexNum;
        for( misfireObdFFDCylIndex = (Dem_u08_MisfireObdFFDCylIndexType)0U; misfireObdFFDCylIndex < misfireObdFFDCylIndexNum; misfireObdFFDCylIndex++ ) /* [GUD:for]misfireObdFFDCylIndex */
        {
            MisfireRecordPtr->OBDFFDCyl[misfireObdFFDCylIndex] = Dem_MisfireRecordList[MisfireIndex].OBDFFDCyl[misfireObdFFDCylIndex];      /* [GUD]misfireObdFFDCylIndex *//* [GUD]MisfireIndex *//* [ARYCHK] DEM_MISFIRE_OBD_FFDCYL_INDEX_NUM / 1 / misfireObdFFDCylIndex */
        }
#endif  /* ( DEM_OBDFFD_SUPPORT == STD_ON )             */

        misfireFFDCylIndexNum = Dem_MisfireFFDCylIndexNum;
        for( misfireFFDCylIndex = (Dem_u08_MisfireFFDCylIndexType)0U; misfireFFDCylIndex < misfireFFDCylIndexNum; misfireFFDCylIndex++ )    /* [GUD:for]misfireFFDCylIndex */
        {
            MisfireRecordPtr->FFDCyl[misfireFFDCylIndex] = Dem_MisfireRecordList[MisfireIndex].FFDCyl[misfireFFDCylIndex];  /* [GUD]misfireFFDCylIndex *//* [GUD]MisfireIndex *//* [ARYCHK] DEM_MISFIRE_FFDCYL_INDEX_NUM / 1 / misfireFFDCylIndex */
        }
        MisfireRecordPtr->ExceedanceCounter        = Dem_MisfireRecordList[MisfireIndex].ExceedanceCounter;                 /* [GUD]MisfireIndex */

        MisfireRecordPtr->ConsistencyId            = Dem_MisfireRecordList[MisfireIndex].ConsistencyId;                     /* [GUD]MisfireIndex */
        MisfireRecordPtr->ClearID                  = Dem_MisfireRecordList[MisfireIndex].ClearID;                           /* [GUD]MisfireIndex */
        MisfireRecordPtr->FactoryCheck             = DEM_MISFIRE_ROMCHECK_SAVED;
    }

    return;
}


#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */

#if ( DEM_PFC_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_MisfireMng_PFCMisfireComRecordInit                   */
/* Description   | Initialize savedzone process of PFCMisfireCom record.    */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_PFCMisfireComRecordInit
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    /* [FuncSw] */
    Dem_MisfireMng_InitPFCMisfireComMirrorRecord();
#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */

    return;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_PFCMisfireComRecordInitSavedZone          */
/* Description   | Initialize savedzone area(PFCMisfireCom record).         */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in] InitType :                                          */
/*               |          Initialize savedzone type                       */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]PFCMisfire   :   NotifySavedZone                 */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_PFCMisfireComRecordInitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPFCMisfireCom;

    recMngCmnKindPFCMisfireCom = Dem_RecMngCmnKindPFCMisfireCom;

    if( InitType == DEM_SZINITTYPE_INITIALIZE_ALL )
    {
        /*--------------------------------------------------*/
        /*  notify SAVED_ZONE_PERMANENT update - start.     */
        Dem_NotifySavedZonePermanentUpdate_Enter();         /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------------------*/

        Dem_MisfireMng_InitPFCMisfireComRecord();       /*[UpdRec]PFCMisfire */
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPFCMisfireCom, ( Dem_u16_RecordIndexType )0U );

        /*--------------------------------------------------*/
        /*  notify SAVED_ZONE_PERMANENT update - end.       */
        Dem_NotifySavedZonePermanentUpdate_Exit();          /*  notify end :  savedzone area will be update.  */
        /*--------------------------------------------------*/

    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_PFCMisfireComDataVerify                   */
/* Description   | Verify PFCMisfireCom record.                             */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | Dem_NotifySavedZonePermanentUpdate_Enter/Exit() is called at caller function.   */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]PFCMisfire                                       */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/*   v5-7-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_PFCMisfireComDataVerify
(
    VAR( boolean, AUTOMATIC ) ExistMisfireRecordflg,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) ClearMisfirePFCRecordflgPtr
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPFCMisfireCom;

    recMngCmnKindPFCMisfireCom = Dem_RecMngCmnKindPFCMisfireCom;

    if ( Dem_PFCMisfireComRecord.FactoryCheck != DEM_MISFIRE_ROMCHECK_FACTORY )
    {
        if( ExistMisfireRecordflg == (boolean)TRUE )
        {
            if( Dem_PFCMisfireComRecord.AccumPermanentCyl == DEM_MISFIRE_CYLINDER_NON )
            {
                /* clear PFC record of misfire */
                *ClearMisfirePFCRecordflgPtr = (boolean)TRUE;
            }
        }
        else
        {
            if( Dem_PFCMisfireComRecord.AccumPermanentCyl != DEM_MISFIRE_CYLINDER_NON )
            {
                Dem_PFCMisfireComRecord.FirstPermanentCyl      = DEM_MISFIRE_CYLINDER_NON;      /*[UpdRec]PFCMisfire */
                Dem_PFCMisfireComRecord.FirstAccumPermanentCyl = DEM_MISFIRE_CYLINDER_NON;      /*[UpdRec]PFCMisfire */
                Dem_PFCMisfireComRecord.AccumPermanentCyl      = DEM_MISFIRE_CYLINDER_NON;      /*[UpdRec]PFCMisfire */
                Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPFCMisfireCom, ( Dem_u16_RecordIndexType )0U );
            }
        }
    }
    else
    {
        /* Initializes the PFCMisfireComRecord. */
        Dem_PFCMisfireComRecord.FirstPermanentCyl      = DEM_MISFIRE_CYLINDER_NON;      /*[UpdRec]PFCMisfire */
        Dem_PFCMisfireComRecord.FirstAccumPermanentCyl = DEM_MISFIRE_CYLINDER_NON;      /*[UpdRec]PFCMisfire */
        Dem_PFCMisfireComRecord.AccumPermanentCyl      = DEM_MISFIRE_CYLINDER_NON;      /*[UpdRec]PFCMisfire */
        Dem_PFCMisfireComRecord.FactoryCheck           = DEM_MISFIRE_ROMCHECK_SAVED;        /*[UpdRec]PFCMisfire */

        if( ExistMisfireRecordflg == (boolean)TRUE )
        {
            /* clear PFC record of misfire */
            *ClearMisfirePFCRecordflgPtr = (boolean)TRUE;
        }

        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPFCMisfireCom, ( Dem_u16_RecordIndexType )0U );
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_GetPFCMisfireComRecord                    */
/* Description   | Get the PFCMisfireComRecord.                             */
/* Preconditions | none                                                     */
/* Parameters    | [out] PFCMisfireComRecordPtr :                           */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_GetPFCMisfireComRecord
(
    P2VAR( Dem_PFCMisfireComRecordType, AUTOMATIC, AUTOMATIC ) PFCMisfireComRecordPtr
)
{
    PFCMisfireComRecordPtr->FirstPermanentCyl      = Dem_PFCMisfireComRecord.FirstPermanentCyl;
    PFCMisfireComRecordPtr->FirstAccumPermanentCyl = Dem_PFCMisfireComRecord.FirstAccumPermanentCyl;
    PFCMisfireComRecordPtr->AccumPermanentCyl      = Dem_PFCMisfireComRecord.AccumPermanentCyl;

    PFCMisfireComRecordPtr->FactoryCheck           = DEM_MISFIRE_ROMCHECK_SAVED;

    return;
}

/****************************************************************************/
/* Function Name | Dem_MisfireMng_SetPFCMisfireComRecord                    */
/* Description   | Set the PFCMisfireComRecord.                             */
/* Preconditions | none                                                     */
/* Parameters    | [out] PFCMisfireComRecordPtr :                           */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]PFCMisfire                                       */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetPFCMisfireComRecord
(
    P2CONST( Dem_PFCMisfireComRecordType, AUTOMATIC, AUTOMATIC ) PFCMisfireComRecordPtr
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPFCMisfireCom;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCompareResult;

    retCompareResult = Dem_MisfireMng_ComparePFCMisfireComRecord( PFCMisfireComRecordPtr );

    if( retCompareResult != DEM_IRT_OK )
    {
        SchM_Enter_Dem_PermanentMemory();

        Dem_PFCMisfireComRecord.FirstPermanentCyl      = PFCMisfireComRecordPtr->FirstPermanentCyl;         /*[UpdRec]PFCMisfire */
        Dem_PFCMisfireComRecord.FirstAccumPermanentCyl = PFCMisfireComRecordPtr->FirstAccumPermanentCyl;    /*[UpdRec]PFCMisfire */
        Dem_PFCMisfireComRecord.AccumPermanentCyl      = PFCMisfireComRecordPtr->AccumPermanentCyl;         /*[UpdRec]PFCMisfire */

        SchM_Exit_Dem_PermanentMemory();

        Dem_PFCMisfireComRecord.FactoryCheck           = DEM_MISFIRE_ROMCHECK_SAVED;                        /*[UpdRec]PFCMisfire */

        recMngCmnKindPFCMisfireCom = Dem_RecMngCmnKindPFCMisfireCom;
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPFCMisfireCom, ( Dem_u16_RecordIndexType )0U );
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_MisfireMng_ClearPFCMisfireComRecord                  */
/* Description   | Clear the PFCMisfireComRecord.                           */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]PFCMisfire                                       */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_ClearPFCMisfireComRecord
( void )
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindPFCMisfireCom;

    SchM_Enter_Dem_PermanentMemory();

    Dem_PFCMisfireComRecord.FirstPermanentCyl      = DEM_MISFIRE_CYLINDER_NON;         /*[UpdRec]PFCMisfire */
    Dem_PFCMisfireComRecord.FirstAccumPermanentCyl = DEM_MISFIRE_CYLINDER_NON;         /*[UpdRec]PFCMisfire */
    Dem_PFCMisfireComRecord.AccumPermanentCyl      = DEM_MISFIRE_CYLINDER_NON;         /*[UpdRec]PFCMisfire */

    SchM_Exit_Dem_PermanentMemory();

    recMngCmnKindPFCMisfireCom = Dem_RecMngCmnKindPFCMisfireCom;
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindPFCMisfireCom, ( Dem_u16_RecordIndexType )0U );

    return;
}

/****************************************************************************/
/* Function Name | Dem_MisfireMng_ComparePFCMisfireComRecord                */
/* Description   | compare PFCMisfireCom record.                            */
/* Preconditions |                                                          */
/* Parameters    | [in] CheckMisfireRecordPtr :                             */
/*               |                                                          */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         | None                                                     */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_ComparePFCMisfireComRecord
(
    P2CONST( Dem_PFCMisfireComRecordType, AUTOMATIC, AUTOMATIC ) CheckPFCMisfireComRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_OK;

    if( Dem_PFCMisfireComRecord.FirstPermanentCyl != CheckPFCMisfireComRecordPtr->FirstPermanentCyl )
    {
        retVal = DEM_IRT_NG;
    }
    else if( Dem_PFCMisfireComRecord.FirstAccumPermanentCyl != CheckPFCMisfireComRecordPtr->FirstAccumPermanentCyl )
    {
        retVal = DEM_IRT_NG;
    }
    else if( Dem_PFCMisfireComRecord.AccumPermanentCyl != CheckPFCMisfireComRecordPtr->AccumPermanentCyl )
    {
        retVal = DEM_IRT_NG;
    }
    else
    {
        /* Non mismatch */
    }

    /* not compared member: */
    /* FactoryCheck */

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_InitPFCMisfireComRecord                   */
/* Description   | Initialize PFCMisfireComRecord.                          */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]PFCMisfire                                       */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MisfireMng_InitPFCMisfireComRecord
( void )
{
    Dem_PFCMisfireComRecord.FirstPermanentCyl      = DEM_MISFIRE_CYLINDER_FACTORY_DEFAULT;      /*[UpdRec]PFCMisfire */
    Dem_PFCMisfireComRecord.FirstAccumPermanentCyl = DEM_MISFIRE_CYLINDER_FACTORY_DEFAULT;      /*[UpdRec]PFCMisfire */
    Dem_PFCMisfireComRecord.AccumPermanentCyl      = DEM_MISFIRE_CYLINDER_FACTORY_DEFAULT;      /*[UpdRec]PFCMisfire */

    Dem_PFCMisfireComRecord.FactoryCheck           = DEM_MISFIRE_ROMCHECK_FACTORY;              /*[UpdRec]PFCMisfire */

    return;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_MisfireMng_SetPFCMisfireComRecordMirror              */
/* Description   | Set the Writing RamData.                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in/out] BlockMirrorPtr :                                */
/*               |        Nonvolatile synchronous data information.         */
/* Return Value  | none                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_MisfireMng_SetPFCMisfireComRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    Dem_MisfireMng_GetPFCMisfireComRecord( &Dem_TmpPFCMisfireComMirror );

    BlockMirrorPtr->MirrorPtr = &Dem_TmpPFCMisfireComMirror;

    return;
}


/****************************************************************************/
/* Function Name | Dem_MisfireMng_InitPFCMisfireComMirrorRecord             */
/* Description   | Initializes the Mirror Memory of PFCMisfireCom record.   */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_MisfireMng_InitPFCMisfireComMirrorRecord
( void )
{
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) pfcMisfireComRecordBlockPaddingSize;
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) idx;

    Dem_TmpPFCMisfireComMirror.FirstPermanentCyl      = DEM_MISFIRE_CYLINDER_NON;
    Dem_TmpPFCMisfireComMirror.FirstAccumPermanentCyl = DEM_MISFIRE_CYLINDER_NON;
    Dem_TmpPFCMisfireComMirror.AccumPermanentCyl      = DEM_MISFIRE_CYLINDER_NON;

    Dem_TmpPFCMisfireComMirror.FactoryCheck           = DEM_MISFIRE_ROMCHECK_SAVED;

    pfcMisfireComRecordBlockPaddingSize = Dem_PFCMisfireComRecordBlockPaddingSize;

    for ( idx = (Dem_u16_PaddingIndexType)0U; idx < pfcMisfireComRecordBlockPaddingSize; idx++ )    /* [GUD:for]idx */
    {
        Dem_TmpPFCMisfireComMirror.Reserve[idx] = DEM_DATA_RESERVE_INITIAL_VALUE;   /* [GUD]idx */
    }

    return;
}
#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */
#endif /* ( DEM_PFC_SUPPORT == STD_ON ) */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_MisfireMng_GetEventIdFromRecordData                  */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStorageNum;
    VAR( Dem_u16_MisfireStrgIndexType, AUTOMATIC ) misfireIndex;

    retVal  =   DEM_IRT_NG;
    eventStorageNum = Dem_PrimaryMemEventStorageNum;

    misfireIndex    =   ( Dem_u16_MisfireStrgIndexType )RecordIndex;
    (void)Dem_CfgInfoPm_CnvMisfireStrgIndexToEventStrgIndex( misfireIndex, &eventStrgIndex );   /* no return check required */

    if ( eventStrgIndex < eventStorageNum )                                                                 /* [GUD:if]eventStrgIndex */
    {
        retVal  =   Dem_CfgInfoPm_CnvEventStrgIndexToEventId( eventStrgIndex, EventIdPtr );                 /* [GUD]eventStrgIndex */
    }
    return retVal;
}
/****************************************************************************/
/* Function Name | Dem_MisfireMng_MisfireCom_GetEventIdFromRecordData       */
/* Description   | get event id from record data                            */
/* Preconditions | none                                                     */
/* Parameters    | [in]  RecordIndex :                                      */
/*               | [out] EventIdPtr  :                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_MisfireCom_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,      /* MISRA DEVIATION */
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr   /* MISRA DEVIATION */
)
{
    return DEM_IRT_NG;
}

#if ( DEM_PFC_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_MisfireMng_PFCMisfireCom_GetEventIdFromRecordData    */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MisfireMng_PFCMisfireCom_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,      /* MISRA DEVIATION */
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr   /* MISRA DEVIATION */
)
{
    return DEM_IRT_NG;
}
#endif  /*   ( DEM_PFC_SUPPORT == STD_ON )  */

#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )    */

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
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
