/* Dem_AltIUMPRMng_c(v5-8-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/AltIUMPRMng/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_ALTIUMPR_SUPPORT == STD_ON )
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "../../../inc/Dem_Rc_AltIUMPRMng.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_ALTIUMPR_DENOMINATOR_RECORD_INDEX   ((Dem_u16_AltIUMPRIndexType)0U)
#define DEM_ALTIUMPR_MON_ACT_RECORD_START_INDEX ((Dem_u16_AltIUMPRIndexType)1U)

#define DEM_ALTIUMPR_DENOMINATOR_DATA_INDEX     ((uint8)0U)
#define DEM_ALTIUMPR_DENOMINATOR_DATA_NON_INDEX ((uint8)1U)
#define DEM_ALTIUMPR_NUMERATOR_DATA_INDEX       ((uint8)0U)
#define DEM_ALTIUMPR_RATIO_DATA_INDEX           ((uint8)1U)

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
#define DEM_ALTIUMPR_FIRST_DATA_INDEX           ((uint8)0U)
#define DEM_ALTIUMPR_SECOND_DATA_INDEX          ((uint8)1U)
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#define DEM_ALTIUMPR_DENOMINATOR_INIT_VAL       ((uint8)0U)
#define DEM_ALTIUMPR_NUMERATOR_INIT_VAL         ((uint8)0U)
#define DEM_ALTIUMPR_RATIO_INIT_VAL             ((uint8)0U)

#define DEM_ALTIUMPR_DENOMINATOR_MAX_VAL        ((uint8)254U)
#define DEM_ALTIUMPR_NUMERATOR_MAX_VAL          ((uint8)255U)

#define DEM_ALTIUMPR_DATA_FACTORY_DEFAULT       (DEM_NVBLOCK_FACTORY_VALUE)

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

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
#if ( DEM_ALTIUMPR_RECORD_PADDING_EXIST == STD_ON )
static FUNC( void, DEM_CODE ) Dem_AltIUMPRMng_InitPadding
(
    P2VAR( Dem_AltIUMPRRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) AltIUMPRRecordPtr
);
#endif  /* ( DEM_ALTIUMPR_RECORD_PADDING_EXIST == STD_ON )  */

static FUNC( void, DEM_CODE ) Dem_AltIUMPRMng_InitMirrorMemory
( void );
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

static FUNC( Dem_u16_AltIUMPRIndexType, DEM_CODE ) Dem_AltIUMPRMng_GetRecordIndex
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_AltIUMPRNvMStatus[ DEM_ALTIUMPR_RECORD_NUM ];
VAR( Dem_AltIUMPRRecordType, DEM_VAR_NO_INIT ) Dem_TmpAltIUMPRMirror;
#endif /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON ) */

static VAR( Dem_u16_AltIUMPRIndexType, DEM_VAR_NO_INIT ) Dem_AltIUMPRIndexForVerify;
static VAR( boolean, DEM_VAR_NO_INIT ) Dem_AltIUMPR_VerifyMode;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_START_SEC_VAR_SAVED_ZONE_ALTIUMPR
#include <Dem_MemMap.h>

VAR( Dem_AltIUMPRRecordType, DEM_VAR_SAVED_ZONE_ALTIUMPR ) Dem_AltIUMPRRecord[ DEM_ALTIUMPR_RECORD_NUM ];

#define DEM_STOP_SEC_VAR_SAVED_ZONE_ALTIUMPR
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_AltIUMPRMng_Init                                     */
/* Description   | initialize function.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_AltIUMPRMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    /* [FuncSw] */
    Dem_AltIUMPRMng_InitMirrorMemory();
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */
    Dem_AltIUMPRIndexForVerify          =   DEM_ALTIUMPR_DENOMINATOR_RECORD_INDEX;
    Dem_AltIUMPR_VerifyMode             =   (boolean)FALSE;
    return;
}


/****************************************************************************/
/* Function Name | Dem_AltIUMPRMng_InitSavedZone                            */
/* Description   | Initialize savedzone process of AltIUMPR.                */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in] InitType :                                          */
/*               |       Initialize savedzone type                          */
/*               |          DEM_SZINITTYPE_INITIALIZE_ALL                   */
/*               |          DEM_SZINITTYPE_INITIALIZE_WITHOUT_PFC           */
/*               |          DEM_SZINITTYPE_INITIALIZE_WITHOUT_PFC_AND_IUMPR */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR :   NotifySavedZone                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_AltIUMPRMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
)
{
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) recordNum;
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) idxRecord;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindAltIUMPR;

    recordNum = Dem_AltIUMPRRecordNum;

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - start.   */
    Dem_NotifySavedZoneIUMPRUpdate_Enter();  /*  notify start :  AltIUMPR savedzone area will be update.  */
    /*--------------------------------------*/

    if( InitType != DEM_SZINITTYPE_INITIALIZE_WITHOUT_PFC_AND_IUMPR )
    {
        /*--------------------------------------------------------------------------*/
        /*  DEM_SZINITTYPE_INITIALIZE_ALL / DEM_SZINITTYPE_INITIALIZE_WITHOUT_PFC   */
        /*--------------------------------------------------------------------------*/
        recMngCmnKindAltIUMPR = Dem_RecMngCmnKindAltIUMPR;

        Dem_AltIUMPRRecord[ DEM_ALTIUMPR_DENOMINATOR_RECORD_INDEX ].Data[ DEM_ALTIUMPR_DENOMINATOR_DATA_INDEX ]     = DEM_ALTIUMPR_DATA_FACTORY_DEFAULT;    /*[UpdRec]AltIUMPR */
        Dem_AltIUMPRRecord[ DEM_ALTIUMPR_DENOMINATOR_RECORD_INDEX ].Data[ DEM_ALTIUMPR_DENOMINATOR_DATA_NON_INDEX ] = DEM_ALTIUMPR_DATA_FACTORY_DEFAULT;    /*[UpdRec]AltIUMPR */
        Dem_AltIUMPRRecord[ DEM_ALTIUMPR_DENOMINATOR_RECORD_INDEX ].TestCompletedThisCycle = DEM_ALTIUMPR_TCTOC_NOTTESTCOMPLETE;                            /*[UpdRec]AltIUMPR */
        Dem_AltIUMPRRecord[ DEM_ALTIUMPR_DENOMINATOR_RECORD_INDEX ].ClearID = DEM_CLRINFO_RECORD_INITIAL;                                                   /*[UpdRec]AltIUMPR */

        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindAltIUMPR, ( Dem_u16_RecordIndexType )DEM_ALTIUMPR_DENOMINATOR_RECORD_INDEX );

        for( idxRecord = DEM_ALTIUMPR_MON_ACT_RECORD_START_INDEX; idxRecord < recordNum; idxRecord++ )                          /* [GUD:for]idxRecord */
        {
            Dem_AltIUMPRRecord[ idxRecord ].Data[ DEM_ALTIUMPR_NUMERATOR_DATA_INDEX ] = DEM_ALTIUMPR_DATA_FACTORY_DEFAULT;      /* [GUD]idxRecord */    /*[UpdRec]AltIUMPR */
            Dem_AltIUMPRRecord[ idxRecord ].Data[ DEM_ALTIUMPR_RATIO_DATA_INDEX ]     = DEM_ALTIUMPR_DATA_FACTORY_DEFAULT;      /* [GUD]idxRecord */    /*[UpdRec]AltIUMPR */
            Dem_AltIUMPRRecord[ idxRecord ].TestCompletedThisCycle                    = DEM_ALTIUMPR_TCTOC_NOTTESTCOMPLETE;     /* [GUD]idxRecord */    /*[UpdRec]AltIUMPR */
            Dem_AltIUMPRRecord[ idxRecord ].ClearID = DEM_CLRINFO_RECORD_INITIAL;                                               /* [GUD]idxRecord */    /*[UpdRec]AltIUMPR */

            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindAltIUMPR, ( Dem_u16_RecordIndexType )idxRecord );                     /* [GUD]idxRecord */
        }
    }
    else
    {
        /*--------------------------------------------------------------------------*/
        /*  DEM_SZINITTYPE_INITIALIZE_WITHOUT_PFC_AND_IUMPR                         */
        /*--------------------------------------------------------------------------*/
        /*  only reset TestCompletedThisCycle.          */

        recMngCmnKindAltIUMPR = Dem_RecMngCmnKindAltIUMPR;

        Dem_AltIUMPRRecord[ DEM_ALTIUMPR_DENOMINATOR_RECORD_INDEX ].TestCompletedThisCycle = DEM_ALTIUMPR_TCTOC_NOTTESTCOMPLETE;    /*[UpdRec]AltIUMPR */
        Dem_AltIUMPRRecord[ DEM_ALTIUMPR_DENOMINATOR_RECORD_INDEX ].ClearID = DEM_CLRINFO_RECORD_INITIAL;                           /*[UpdRec]AltIUMPR */

        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindAltIUMPR, ( Dem_u16_RecordIndexType )DEM_ALTIUMPR_DENOMINATOR_RECORD_INDEX );

        for( idxRecord = DEM_ALTIUMPR_MON_ACT_RECORD_START_INDEX; idxRecord < recordNum; idxRecord++ )              /* [GUD:for]idxRecord */
        {
            Dem_AltIUMPRRecord[ idxRecord ].TestCompletedThisCycle  = DEM_ALTIUMPR_TCTOC_NOTTESTCOMPLETE;           /* [GUD]idxRecord */    /*[UpdRec]AltIUMPR */
            Dem_AltIUMPRRecord[ idxRecord ].ClearID                 = DEM_CLRINFO_RECORD_INITIAL;                   /* [GUD]idxRecord */    /*[UpdRec]AltIUMPR */

            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindAltIUMPR, ( Dem_u16_RecordIndexType )idxRecord );
        }
    }
    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - end.     */
    Dem_NotifySavedZoneIUMPRUpdate_Exit();  /*  notify end :  AltIUMPR savedzone area will be update.    */
    /*--------------------------------------*/

    return;
}


/****************************************************************************/
/* Function Name | Dem_AltIUMPRMng_DataVerify                               */
/* Description   | verify record data.                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : DataVerify completed.         */
/*               |          DEM_IRT_PENDING : Continue DataVerify.          */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR :   NotifySavedZone                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/*   v5-6-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AltIUMPRMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) recordNum;
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) idxRecord;
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) verifyLoopNumByCycle;
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) loopCount;
    VAR( Dem_u08_InternalReturnType,AUTOMATIC ) retVal;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindAltIUMPR;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) obdClearId;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) clrInfoNvmReadResult;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) cylinderStartIndex;
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )           */

    recordNum = Dem_AltIUMPRRecordNum;
    verifyLoopNumByCycle = Dem_AltIUMPRRecordNumForVerifyByCycle;
    retVal = DEM_IRT_OK;

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - start.   */
    Dem_NotifySavedZoneIUMPRUpdate_Enter();  /*  notify start :  AltIUMPR savedzone area will be update.  */
    /*--------------------------------------*/

    /*  check execute clearDTC.             */
    clrInfoNvmReadResult = Dem_ClrInfoMng_GetNvmReadResult();
    obdClearId = Dem_ClrInfoMng_GetObdClearID();

    /* Check only Denominator */
    recMngCmnKindAltIUMPR = Dem_RecMngCmnKindAltIUMPR;
    if( Dem_AltIUMPRIndexForVerify == DEM_ALTIUMPR_DENOMINATOR_RECORD_INDEX )
    {
        /*----------------------------------------------------------------------------------------------*/
        /*  Processing first verify devided cycle by Dem_AltIUMPRRecordNumForVerifyByCycle.             */
        /*----------------------------------------------------------------------------------------------*/
        if( Dem_AltIUMPRRecord[ DEM_ALTIUMPR_DENOMINATOR_RECORD_INDEX ].Data[ DEM_ALTIUMPR_DENOMINATOR_DATA_INDEX ] > DEM_ALTIUMPR_DENOMINATOR_MAX_VAL )
        {
            /*------------------------------------------------------*/
            /*  verify mode : data NG. all data clear.              */
            /*------------------------------------------------------*/
            Dem_AltIUMPR_VerifyMode =   (boolean)TRUE;

            /* Write Denominator after Numerator and Ratio according to the update process */
            Dem_AltIUMPRRecord[ DEM_ALTIUMPR_DENOMINATOR_RECORD_INDEX ].Data[ DEM_ALTIUMPR_DENOMINATOR_DATA_INDEX ]     = DEM_ALTIUMPR_DENOMINATOR_INIT_VAL;    /*[UpdRec]AltIUMPR */
            Dem_AltIUMPRRecord[ DEM_ALTIUMPR_DENOMINATOR_RECORD_INDEX ].Data[ DEM_ALTIUMPR_DENOMINATOR_DATA_NON_INDEX ] = (uint8)0U;                            /*[UpdRec]AltIUMPR */
            Dem_AltIUMPRRecord[ DEM_ALTIUMPR_DENOMINATOR_RECORD_INDEX ].TestCompletedThisCycle                          = DEM_ALTIUMPR_TCTOC_NOTTESTCOMPLETE;   /*[UpdRec]AltIUMPR */
            Dem_AltIUMPRRecord[ DEM_ALTIUMPR_DENOMINATOR_RECORD_INDEX ].ClearID                                         = obdClearId;                           /*[UpdRec]AltIUMPR */

            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindAltIUMPR, ( Dem_u16_RecordIndexType )DEM_ALTIUMPR_DENOMINATOR_RECORD_INDEX );

            /*  check next record.          */
            Dem_AltIUMPRIndexForVerify = DEM_ALTIUMPR_MON_ACT_RECORD_START_INDEX;
        }
        else
        {
            /*----------------------------------*/
            /*  check ClearId.                  */
            /*----------------------------------*/
            Dem_AltIUMPR_VerifyMode =   (boolean)FALSE;

            /*--------------------------------------------------------------------------------------------------------------*/
            /*  Dem_AltIUMPRRecord[ DEM_ALTIUMPR_DENOMINATOR_RECORD_INDEX ].TestCompletedThisCycle is unused member.        */
            /*  so, no need check clearID in Dem_AltIUMPRRecord[ DEM_ALTIUMPR_DENOMINATOR_RECORD_INDEX ].                   */
            /*--------------------------------------------------------------------------------------------------------------*/

            /*  check next record.          */
            Dem_AltIUMPRIndexForVerify = DEM_ALTIUMPR_MON_ACT_RECORD_START_INDEX;
        }
        loopCount = DEM_ALTIUMPR_MON_ACT_RECORD_START_INDEX;    /*  next verify record check position. start position : [DEM_ALTIUMPR_MON_ACT_RECORD_START_INDEX] record    */
    }
    else
    {
        /*----------------------------------------------------------------------------------------------*/
        /*  Processing after the second verify devided cycle by Dem_AltIUMPRRecordNumForVerifyByCycle.  */
        /*----------------------------------------------------------------------------------------------*/
        loopCount = ( Dem_u16_AltIUMPRIndexType )0U;            /*  next verify record check position. start position.  */
    }

    for( idxRecord = Dem_AltIUMPRIndexForVerify; idxRecord < recordNum; idxRecord++ )                                               /* [GUD:for]idxRecord */
    {
        if( loopCount < verifyLoopNumByCycle )
        {
            if ( Dem_AltIUMPR_VerifyMode == (boolean)TRUE )
            {
                /*------------------------------------------------------*/
                /*  verify mode : data NG. all data clear.              */
                /*------------------------------------------------------*/
                Dem_AltIUMPRRecord[ idxRecord ].Data[ DEM_ALTIUMPR_NUMERATOR_DATA_INDEX ] = DEM_ALTIUMPR_NUMERATOR_INIT_VAL;            /* [GUD]idxRecord */    /*[UpdRec]AltIUMPR */
                Dem_AltIUMPRRecord[ idxRecord ].Data[ DEM_ALTIUMPR_RATIO_DATA_INDEX ]     = DEM_ALTIUMPR_RATIO_INIT_VAL;                /* [GUD]idxRecord */    /*[UpdRec]AltIUMPR */
                Dem_AltIUMPRRecord[ idxRecord ].TestCompletedThisCycle                    = DEM_ALTIUMPR_TCTOC_NOTTESTCOMPLETE;         /* [GUD]idxRecord */    /*[UpdRec]AltIUMPR */
                Dem_AltIUMPRRecord[ idxRecord ].ClearID                                   = obdClearId;                                 /* [GUD]idxRecord */    /*[UpdRec]AltIUMPR */

                Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindAltIUMPR, ( Dem_u16_RecordIndexType )idxRecord );                         /* [GUD]idxRecord */
            }
            else
            {
                /*------------------------------------------------------*/
                /*  check ClearId.                                      */
                /*------------------------------------------------------*/
                if (( clrInfoNvmReadResult != DEM_IRT_OK ) || ( Dem_AltIUMPRRecord[ idxRecord ].ClearID != obdClearId ) )               /* [GUD]idxRecord */
                {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                    cylinderStartIndex = Dem_AltIUMPR_CylinderStartIndex;
                    if ( idxRecord < cylinderStartIndex )
#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )           */
                    {
                        /*------------------------------------------------------*/
                        /*  verify mode : only clear TestCompletedThisCycle.    */
                        /*------------------------------------------------------*/
                        Dem_AltIUMPRRecord[ idxRecord ].TestCompletedThisCycle  = DEM_ALTIUMPR_TCTOC_NOTTESTCOMPLETE;                   /* [GUD]idxRecord */    /*[UpdRec]AltIUMPR */
                        /*  set clear id and update NvM.    */
                        Dem_AltIUMPRRecord[ idxRecord ].ClearID  = obdClearId;                                                          /* [GUD]idxRecord */    /*[UpdRec]AltIUMPR */

                        /*  read of ClearInfoRecord is NG       */
                        if ( clrInfoNvmReadResult != DEM_IRT_OK )
                        {
                            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindAltIUMPR, ( Dem_u16_RecordIndexType )idxRecord );             /* [GUD]idxRecord */
                        }
                    }
                }
            }
            loopCount = loopCount + (Dem_u16_AltIUMPRIndexType)1U;
        }
        else
        {
            Dem_AltIUMPRIndexForVerify = idxRecord;
            retVal = DEM_IRT_PENDING;
            break;
        }
    }

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - end.     */
    Dem_NotifySavedZoneIUMPRUpdate_Exit();  /*  notify end :  AltIUMPR savedzone area will be update.    */
    /*--------------------------------------*/

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_AltIUMPRMng_SetTestCompleteThisCycle                 */
/* Description   | set SetTestCompleteThisCycle.                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex : Event index.                       */
/*               | [in] TestCompleteThisCycle : TestCompleteThisCycle.      */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_AltIUMPRMng_SetTestCompleteThisCycle
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u08_AltIUMPRTestCompletedThisCycleType, AUTOMATIC ) TestCompleteThisCycle
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindAltIUMPR;
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) recordIndex;
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) recordNum;
    VAR( Dem_u08_AltIUMPRTestCompletedThisCycleType, AUTOMATIC ) oldTestCompletedThisCycle;

    recMngCmnKindAltIUMPR = Dem_RecMngCmnKindAltIUMPR;

    recordNum   =   Dem_AltIUMPRRecordNum;

    recordIndex = Dem_AltIUMPRMng_GetRecordIndex( EventCtrlIndex );
    if( recordIndex < recordNum )                                                                                   /* [GUD:if]recordIndex */
    {
        oldTestCompletedThisCycle = Dem_AltIUMPRRecord[ recordIndex ].TestCompletedThisCycle;                       /* [GUD]recordIndex */
        if ( oldTestCompletedThisCycle != TestCompleteThisCycle )
        {
            Dem_AltIUMPRRecord[ recordIndex ].TestCompletedThisCycle = TestCompleteThisCycle;                       /* [GUD]recordIndex */  /*[UpdRec]AltIUMPR */
            Dem_AltIUMPRRecord[ recordIndex ].ClearID                = Dem_ClrInfoMng_GetObdClearID();              /* [GUD]recordIndex */  /*[UpdRec]AltIUMPR */
            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindAltIUMPR, ( Dem_u16_RecordIndexType )recordIndex );       /* [GUD]recordIndex */
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_AltIUMPRMng_GetTestCompleteThisCycle                 */
/* Description   | get SetTestCompleteThisCycle.                            */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex : Event index.                       */
/*               | [in] TestCompleteThisCycle : TestCompleteThisCycle.      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success.                             */
/*               |        DEM_IRT_NG : NG                                   */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AltIUMPRMng_GetTestCompleteThisCycle
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    P2VAR( Dem_u08_AltIUMPRTestCompletedThisCycleType, AUTOMATIC, AUTOMATIC ) TestCompleteThisCyclePtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) recordIndex;
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) recordNum;

    retVal = DEM_IRT_NG;

    recordNum   =   Dem_AltIUMPRRecordNum;

    recordIndex = Dem_AltIUMPRMng_GetRecordIndex( EventCtrlIndex );
    if( recordIndex < recordNum )                                                                                   /* [GUD:if]recordIndex */
    {
        *TestCompleteThisCyclePtr = Dem_AltIUMPRRecord[ recordIndex ].TestCompletedThisCycle;                       /* [GUD]recordIndex */
        retVal = DEM_IRT_OK;
    }
    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_AltIUMPRMng_GetDenominator                           */
/* Description   | Get Alternative IUMPR Denominator                        */
/* Preconditions | none                                                     */
/* Parameters    | [out] DenominatorPtr :  Alternative IUMPR Denominator    */
/* Return Value  | void                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_AltIUMPRMng_GetDenominator
(
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DenominatorPtr
)
{
    *DenominatorPtr = Dem_AltIUMPRRecord[ DEM_ALTIUMPR_DENOMINATOR_RECORD_INDEX ].Data[ DEM_ALTIUMPR_DENOMINATOR_DATA_INDEX ];
    if( *DenominatorPtr > DEM_ALTIUMPR_DENOMINATOR_MAX_VAL )
    {
        /* If it is out of the range, the upper limit is output */
        *DenominatorPtr = DEM_ALTIUMPR_DENOMINATOR_MAX_VAL;
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_AltIUMPRMng_IncNumeratorCounts                       */
/* Description   | Increment Numerator Counts                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex : Event index.                       */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_AltIUMPRMng_IncNumeratorCounts
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
)
{
    VAR( uint8, AUTOMATIC ) numerator;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindAltIUMPR;
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) recordIndex;
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) recordNum;

    recMngCmnKindAltIUMPR = Dem_RecMngCmnKindAltIUMPR;

    recordNum   =   Dem_AltIUMPRRecordNum;

    recordIndex = Dem_AltIUMPRMng_GetRecordIndex( EventCtrlIndex );
    if( recordIndex < recordNum )                                                                               /* [GUD:if]recordIndex */
    {
        numerator = Dem_AltIUMPRRecord[ recordIndex ].Data[ DEM_ALTIUMPR_NUMERATOR_DATA_INDEX ];                /* [GUD]recordIndex */
        if( numerator < DEM_ALTIUMPR_NUMERATOR_MAX_VAL )
        {
            numerator = numerator + (uint8)1U;
            Dem_AltIUMPRRecord[ recordIndex ].Data[ DEM_ALTIUMPR_NUMERATOR_DATA_INDEX ] = numerator;            /* [GUD]recordIndex */  /*[UpdRec]AltIUMPR */
            Dem_AltIUMPRRecord[ recordIndex ].ClearID                = Dem_ClrInfoMng_GetObdClearID();          /* [GUD]recordIndex */  /*[UpdRec]AltIUMPR */

            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindAltIUMPR, ( Dem_u16_RecordIndexType )recordIndex );   /* [GUD]recordIndex */
        }
    }

    return;
}

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_AltIUMPRMng_IncNumeratorCountsForCylinder            */
/* Description   | Increment Numerator Counts                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireCylinderNum : Cylinder Num.                  */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_AltIUMPRMng_IncNumeratorCountsForCylinder
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC )  MisfireCylinderNum
)
{
    VAR( uint8, AUTOMATIC ) numerator;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindAltIUMPR;
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) recordIndex;
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) cylinderStartIndex;
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) recordNum;

    recMngCmnKindAltIUMPR = Dem_RecMngCmnKindAltIUMPR;

    recordNum   =   Dem_AltIUMPRRecordNum;

    cylinderStartIndex = Dem_AltIUMPR_CylinderStartIndex;
    recordIndex = cylinderStartIndex + (Dem_u16_AltIUMPRIndexType)MisfireCylinderNum;
    if( recordIndex < recordNum )                                                                               /* [GUD:if]recordIndex */
    {
        numerator = Dem_AltIUMPRRecord[ recordIndex ].Data[ DEM_ALTIUMPR_NUMERATOR_DATA_INDEX ];                /* [GUD]recordIndex */
        if( numerator < DEM_ALTIUMPR_NUMERATOR_MAX_VAL )
        {
            numerator = numerator + (uint8)1U;
            Dem_AltIUMPRRecord[ recordIndex ].Data[ DEM_ALTIUMPR_NUMERATOR_DATA_INDEX ] = numerator;            /* [GUD]recordIndex */  /*[UpdRec]AltIUMPR */
            Dem_AltIUMPRRecord[ recordIndex ].ClearID                = Dem_ClrInfoMng_GetObdClearID();          /* [GUD]recordIndex */  /*[UpdRec]AltIUMPR */

            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindAltIUMPR, ( Dem_u16_RecordIndexType )recordIndex );   /* [GUD]recordIndex */
        }
    }

    return;
}
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_AltIUMPRMng_GetNumeratorAndRatio                     */
/* Description   | Get Numerator ande Ratio                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex : Event index.                       */
/*               | [out] NumeratorPtr : numerator                           */
/*               | [out] RatioPtr : ratio                                   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |       DEM_IRT_OK : success                               */
/*               |       DEM_IRT_NG : failed, When EDR Number 0x98 is conf- */
/*               |                    igured in non OBD event               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AltIUMPRMng_GetNumeratorAndRatio
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) NumeratorPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) RatioPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) recordIndex;
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) recordNum;

    retVal = DEM_IRT_NG;

    recordNum   =   Dem_AltIUMPRRecordNum;

    recordIndex = Dem_AltIUMPRMng_GetRecordIndex( EventCtrlIndex );
    if( recordIndex < recordNum )                                                                               /* [GUD:if]recordIndex */
    {
        /* Enter exclusive area */
        SchM_Enter_Dem_IUMPRRatioData();

        *NumeratorPtr = Dem_AltIUMPRRecord[ recordIndex ].Data[ DEM_ALTIUMPR_NUMERATOR_DATA_INDEX ];            /* [GUD]recordIndex */
        *RatioPtr = Dem_AltIUMPRRecord[ recordIndex ].Data[ DEM_ALTIUMPR_RATIO_DATA_INDEX ];                    /* [GUD]recordIndex */

        /* Exit exclusive area */
        SchM_Exit_Dem_IUMPRRatioData();

        retVal = DEM_IRT_OK;
    }

    return retVal;
}

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
/****************************************************************************/
/* Function Name | Dem_AltIUMPRMng_GetNumeratorAndRatioForCylinder          */
/* Description   | Get Numerator ande Ratio                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] MisfireCylinderNum : Cylinder Num.                  */
/*               | [out] NumeratorPtr : numerator                           */
/*               | [out] RatioPtr : ratio                                   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |       DEM_IRT_OK : success                               */
/*               |       DEM_IRT_NG : failed, When EDR Number 0x98 is conf- */
/*               |                    igured in non OBD event               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AltIUMPRMng_GetNumeratorAndRatioForCylinder
(
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC )  MisfireCylinderNum,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) NumeratorPtr,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) RatioPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) recordIndex;
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) cylinderStartIndex;
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) recordNum;

    retVal = DEM_IRT_NG;

    recordNum   =   Dem_AltIUMPRRecordNum;

    cylinderStartIndex = Dem_AltIUMPR_CylinderStartIndex;
    recordIndex = cylinderStartIndex + (Dem_u16_AltIUMPRIndexType)MisfireCylinderNum;
    if( recordIndex < recordNum )                                                                               /* [GUD:if]recordIndex */
    {
        /* Enter exclusive area */
        SchM_Enter_Dem_IUMPRRatioData();

        *NumeratorPtr = Dem_AltIUMPRRecord[ recordIndex ].Data[ DEM_ALTIUMPR_NUMERATOR_DATA_INDEX ];            /* [GUD]recordIndex */
        *RatioPtr = Dem_AltIUMPRRecord[ recordIndex ].Data[ DEM_ALTIUMPR_RATIO_DATA_INDEX ];                    /* [GUD]recordIndex */

        /* Exit exclusive area */
        SchM_Exit_Dem_IUMPRRatioData();

        retVal = DEM_IRT_OK;
    }

    return retVal;
}
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_AltIUMPRMng_IncDenominatorProccess                   */
/* Description   | Proccess for Increment Denominator                       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]AltIUMPR                                         */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_AltIUMPRMng_IncDenominatorProccess
( void )
{
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) recordNum;
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) idxRecord;
    VAR( uint8, AUTOMATIC ) denominator;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindAltIUMPR;
    VAR( Dem_u08_ClearIdType, AUTOMATIC ) obdClearId;

    denominator = Dem_AltIUMPRRecord[ DEM_ALTIUMPR_DENOMINATOR_RECORD_INDEX ].Data[ DEM_ALTIUMPR_DENOMINATOR_DATA_INDEX ];
    recMngCmnKindAltIUMPR = Dem_RecMngCmnKindAltIUMPR;
    obdClearId = Dem_ClrInfoMng_GetObdClearID();

    if( denominator < DEM_ALTIUMPR_DENOMINATOR_MAX_VAL )
    {
        denominator++;
    }
    else
    {
        denominator = DEM_ALTIUMPR_DENOMINATOR_INIT_VAL;

        recordNum = Dem_AltIUMPRRecordNum;
        for( idxRecord = DEM_ALTIUMPR_MON_ACT_RECORD_START_INDEX; idxRecord < recordNum; idxRecord++ )                                                              /* [GUD:for]idxRecord */
        {
            /* Enter exclusive area */
            SchM_Enter_Dem_IUMPRRatioData();

            Dem_AltIUMPRRecord[ idxRecord ].Data[ DEM_ALTIUMPR_RATIO_DATA_INDEX ]     = Dem_AltIUMPRRecord[ idxRecord ].Data[ DEM_ALTIUMPR_NUMERATOR_DATA_INDEX ];      /* [GUD]idxRecord */    /*[UpdRec]AltIUMPR */
            Dem_AltIUMPRRecord[ idxRecord ].Data[ DEM_ALTIUMPR_NUMERATOR_DATA_INDEX ] = DEM_ALTIUMPR_NUMERATOR_INIT_VAL;                                                /* [GUD]idxRecord */    /*[UpdRec]AltIUMPR */
            /* Exit exclusive area */
            SchM_Exit_Dem_IUMPRRatioData();

            Dem_AltIUMPRRecord[ idxRecord ].ClearID = obdClearId;                                                                                                       /* [GUD]idxRecord */    /*[UpdRec]AltIUMPR */
            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindAltIUMPR, ( Dem_u16_RecordIndexType )idxRecord );                                                             /* [GUD]idxRecord */
        }
    }

    /* Write Denominator at the end */
    Dem_AltIUMPRRecord[ DEM_ALTIUMPR_DENOMINATOR_RECORD_INDEX ].Data[ DEM_ALTIUMPR_DENOMINATOR_DATA_INDEX ] = denominator;  /*[UpdRec]AltIUMPR */
    Dem_AltIUMPRRecord[ DEM_ALTIUMPR_DENOMINATOR_RECORD_INDEX ].ClearID                                     = obdClearId;   /*[UpdRec]AltIUMPR */

    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindAltIUMPR, ( Dem_u16_RecordIndexType )DEM_ALTIUMPR_DENOMINATOR_RECORD_INDEX );

    return;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_AltIUMPRMng_SetRecordMirror                          */
/* Description   | Copy to the Mirror Memory.                               */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in/out] BlockMirrorPtr :                                */
/*               |        Nonvolatile synchronous data information.         */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_AltIUMPRMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) recordNum;

    recordNum = Dem_AltIUMPRRecordNum;
    if( BlockMirrorPtr->RecordIndex < recordNum )                                                                                                               /* [GUD:if]BlockMirrorPtr->RecordIndex */
    {
        Dem_TmpAltIUMPRMirror.Data[ DEM_ALTIUMPR_FIRST_DATA_INDEX ]  = Dem_AltIUMPRRecord[ BlockMirrorPtr->RecordIndex ].Data[ DEM_ALTIUMPR_FIRST_DATA_INDEX ];     /* [GUD]BlockMirrorPtr->RecordIndex */
        Dem_TmpAltIUMPRMirror.Data[ DEM_ALTIUMPR_SECOND_DATA_INDEX ] = Dem_AltIUMPRRecord[ BlockMirrorPtr->RecordIndex ].Data[ DEM_ALTIUMPR_SECOND_DATA_INDEX ];    /* [GUD]BlockMirrorPtr->RecordIndex */
        Dem_TmpAltIUMPRMirror.TestCompletedThisCycle                 = Dem_AltIUMPRRecord[ BlockMirrorPtr->RecordIndex ].TestCompletedThisCycle;                    /* [GUD]BlockMirrorPtr->RecordIndex */
        Dem_TmpAltIUMPRMirror.ClearID                                = Dem_AltIUMPRRecord[ BlockMirrorPtr->RecordIndex ].ClearID;                                   /* [GUD]BlockMirrorPtr->RecordIndex */
    }

    BlockMirrorPtr->MirrorPtr = &Dem_TmpAltIUMPRMirror;

    return;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */


/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
#if ( DEM_ALTIUMPR_RECORD_PADDING_EXIST == STD_ON )
/****************************************************************************/
/* Function Name | Dem_AltIUMPRMng_InitPadding                              */
/* Description   | Initializes the AltIUMPR record padding data.            */
/* Preconditions | none                                                     */
/* Parameters    | [in] AltIUMPRRecordPtr    :                              */
/*               |       The pointer of the operation cycle record.         */
/*               |       &Dem_TmpAltIUMPRMirror -DEM_VAR_NO_INIT-           */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_AltIUMPRMng_InitPadding
(
    P2VAR( Dem_AltIUMPRRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) AltIUMPRRecordPtr
)
{
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingSize;
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingIndex;

    paddingSize = Dem_AltIUMPRRecordBlockPaddingSize;

    for( paddingIndex = (Dem_u16_PaddingIndexType)0U; paddingIndex < paddingSize; paddingIndex++ )      /* [GUD:for]paddingIndex */
    {
        AltIUMPRRecordPtr->Reserve[paddingIndex] = (uint8)0U;                                           /* [GUD]paddingIndex *//* [ARYCHK] DEM_ALTIUMPR_RECORD_PADDINGSIZE_TO_BLOCKSIZE / 1 / paddingIndex */
    }

    return;
}
#endif  /* ( DEM_ALTIUMPR_RECORD_PADDING_EXIST == STD_ON )  */

#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */


/****************************************************************************/
/* Function Name | Dem_AltIUMPRMng_GetRecordIndex                           */
/* Description   | Get Record Index                                         */
/* Preconditions | none                                                     */
/* Parameters    | [in] EventCtrlIndex : Event index.                       */
/*               | [out] RecordIndexPtr : Index to an array of Dem_AltIUMP- */
/*               | RRecord                                                  */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |       DEM_IRT_OK : success                               */
/*               |       DEM_IRT_NG : failed                                */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u16_AltIUMPRIndexType, DEM_CODE ) Dem_AltIUMPRMng_GetRecordIndex
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex
)
{
    VAR( Dem_u16_AltIUMPRIndexType, AUTOMATIC ) recordIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) altIUMPRRefObdEventNum;

    altIUMPRRefObdEventNum  =   Dem_AltIUMPRRefObdEventNum;
    recordIndex             =   DEM_ALTIUMPRINDEX_INVALID;

    if ( EventCtrlIndex < altIUMPRRefObdEventNum )                              /* [GUD:if]EventCtrlIndex */
    {
        recordIndex =   Dem_AltIUMPRRefObdEventTable[ EventCtrlIndex ];         /* [GUD]EventCtrlIndex */
    }
    return recordIndex;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_AltIUMPRMng_InitMirrorMemory                         */
/* Description   | Initialize the Mirror Memory.                            */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_AltIUMPRMng_InitMirrorMemory
( void )
{
    /* Initializes the temporary permanent memory. */
    Dem_TmpAltIUMPRMirror.Data[ DEM_ALTIUMPR_FIRST_DATA_INDEX ] = (uint8)0U;
    Dem_TmpAltIUMPRMirror.Data[ DEM_ALTIUMPR_SECOND_DATA_INDEX ] = (uint8)0U;
    Dem_TmpAltIUMPRMirror.TestCompletedThisCycle                = DEM_ALTIUMPR_TCTOC_NOTTESTCOMPLETE;
    Dem_TmpAltIUMPRMirror.ClearID                               = DEM_CLRINFO_RECORD_INITIAL;

#if ( DEM_ALTIUMPR_RECORD_PADDING_EXIST == STD_ON ) /*  [FuncSw]    */
    Dem_AltIUMPRMng_InitPadding( &Dem_TmpAltIUMPRMirror );
#endif  /* ( DEM_ALTIUMPR_RECORD_PADDING_EXIST == STD_ON )          */

    return;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_AltIUMPRMng_GetEventIdFromRecordData                 */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_AltIUMPRMng_GetEventIdFromRecordData
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecordIndex,      /* MISRA DEVIATION */
    P2VAR( Dem_EventIdType, AUTOMATIC, AUTOMATIC ) EventIdPtr   /* MISRA DEVIATION */
)
{
    /*  this record has no event id.        */
    return DEM_IRT_NG;
}
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* ( DEM_ALTIUMPR_SUPPORT == STD_ON ) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
