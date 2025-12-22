/* Dem_IUMPRMng_c(v5-7-0)                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/IUMPRMng/CODE                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_IUMPR_SUPPORT == STD_ON )

#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../inc/Dem_Rc_RecMngCmn.h"
#include "../../../inc/Dem_Rc_RecMngCmn_Table.h"
#include "../../../cfg/Dem_IUMPR_Cfg.h"
#include "../../../inc/Dem_Rc_IUMPRMng.h"
#include "Dem_IUMPRMng_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_IUMPR_RATIO_IGCC_ADD_BIT_MASK       ((Dem_u08_IUMPRGenAddedCondType)0x01U)
#define DEM_IUMPR_RATIO_GENDEN_ADD_BIT_MASK     ((Dem_u08_IUMPRGenAddedCondType)0x01U)

#define DEM_IUMPR_CONDITION_FACTORY_DEFAULT     (DEM_NVBLOCK_FACTORY_VALUE)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
static FUNC( void, DEM_CODE ) Dem_IUMPRMng_InitMirrorRecord
( void );
#if ( DEM_IUMPR_RECORD_PADDING_EXIST == STD_ON )
static FUNC( void, DEM_CODE ) Dem_IUMPRMng_InitPadding
(
    P2VAR( Dem_IUMPRCommonRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) IUMPRRecordPtr
);
#endif /* DEM_IUMPR_RECORD_PADDING_EXIST -STD_ON- */
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

static FUNC( void, DEM_CODE ) Dem_IUMPRMng_SetIUMPRGenDenRecordData
(
    P2CONST( Dem_IUMPRCommonRecordInternalType, AUTOMATIC, AUTOMATIC )  IUMPRDataPtr
);

static FUNC( void, DEM_CODE ) Dem_IUMPRMng_GetInfoRecord
(
    P2VAR( Dem_IUMPRInfoRecordType, AUTOMATIC, AUTOMATIC ) InfoRecordTypePtr
);

static FUNC( void, DEM_CODE ) Dem_IUMPRMng_CnvInfoRecordToCommon
(
    P2CONST( Dem_IUMPRInfoRecordType, AUTOMATIC, AUTOMATIC )    IUMPRInfoRecordPtr,
    P2VAR( Dem_IUMPRCommonRecordInternalType, AUTOMATIC, AUTOMATIC )    IUMPRDataPtr
);


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
VAR( Dem_u08_RecMngMtxStsType, DEM_VAR_NO_INIT ) Dem_IUMPRNvMStatus[DEM_IUMPR_RECORD_NUM];
VAR( Dem_IUMPRCommonRecordType, DEM_VAR_NO_INIT ) Dem_TmpIUMPRMirror;
#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

static VAR( Dem_u16_IUMPRIndexType, DEM_VAR_NO_INIT ) Dem_IUMPRIndexForVerify;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


#define DEM_START_SEC_VAR_SAVED_ZONE_IUMPR
#include <Dem_MemMap.h>

VAR( Dem_IUMPRCommonRecordType,      DEM_VAR_SAVED_ZONE_IUMPR ) Dem_IUMPRRecord[DEM_IUMPR_RECORD_NUM];

#define DEM_STOP_SEC_VAR_SAVED_ZONE_IUMPR
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_IUMPRMng_Init                                        */
/* Description   | initialize function.                                     */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPRMng_Init
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    /* [FuncSw] */
    /*  initialize mirror memory area.      */
    Dem_IUMPRMng_InitMirrorRecord();
#endif  /* ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )    */
    Dem_IUMPRIndexForVerify = (Dem_u16_IUMPRIndexType)0U;

    return;
}

/****************************************************************************/
/* Function Name | Dem_IUMPRMng_InitSavedZone                               */
/* Description   | Initialize savedzone process of IUMPR.                   */
/* Preconditions |                                                          */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/*               | [in] InitType :                                          */
/*               |          Initialize savedzone type                       */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]IUMPR    :   NotifySavedZone                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPRMng_InitSavedZone
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    VAR( Dem_SavedZoneInitializeType, AUTOMATIC ) InitType
)
{
    VAR( Dem_u16_IUMPRIndexType, AUTOMATIC ) iumprIndex;
    VAR( Dem_u16_IUMPRIndexType, AUTOMATIC ) demIumprNum;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindIUMPR;

    recMngCmnKindIUMPR = Dem_RecMngCmnKindIUMPR;
    demIumprNum = Dem_IUMPRRecordNum;

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - start.   */
    Dem_NotifySavedZoneIUMPRUpdate_Enter();  /*  notify start :  savedzone area will be update.  */
    /*--------------------------------------*/

    for( iumprIndex = (Dem_u16_IUMPRIndexType)0U; iumprIndex < demIumprNum; iumprIndex++ )              /* [GUD:for]iumprIndex */
    {
        if( Dem_IUMPRRecord[iumprIndex].CommonCondition4 !=  DEM_IUMPR_CONDITION_FACTORY_DEFAULT )      /* [GUD]iumprIndex */
        {
            if( InitType != DEM_SZINITTYPE_INITIALIZE_WITHOUT_PFC_AND_IUMPR )
            {
                /* DEM_SZINITTYPE_INITIALIZE_ALL */
                /* DEM_SZINITTYPE_INITIALIZE_WITHOUT_PFC */
                Dem_IUMPRRecord[iumprIndex].CommonCounter1      = (uint16)0U;                           /* [GUD]iumprIndex */   /*[UpdRec]IUMPR */
                Dem_IUMPRRecord[iumprIndex].CommonCounter2      = (uint16)0U;                           /* [GUD]iumprIndex */   /*[UpdRec]IUMPR */
            }

            Dem_IUMPRRecord[iumprIndex].CommonCondition1    = (uint8)0U;                                /* [GUD]iumprIndex */   /*[UpdRec]IUMPR */
            Dem_IUMPRRecord[iumprIndex].CommonCondition2    = (uint8)0U;                                /* [GUD]iumprIndex */   /*[UpdRec]IUMPR */
            Dem_IUMPRRecord[iumprIndex].CommonCondition3    = (uint8)0U;                                /* [GUD]iumprIndex */   /*[UpdRec]IUMPR */
            Dem_IUMPRRecord[iumprIndex].CommonCondition4    = (uint8)0U;                                /* [GUD]iumprIndex */   /*[UpdRec]IUMPR */

            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindIUMPR, (Dem_u16_RecordIndexType)iumprIndex ); /* [GUD]iumprIndex */
        }
    }

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - end.     */
    Dem_NotifySavedZoneIUMPRUpdate_Exit();  /*  notify end :  savedzone area will be update.    */
    /*--------------------------------------*/

    return;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_IUMPRMng_SetRecordMirror                             */
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
FUNC( void, DEM_CODE ) Dem_IUMPRMng_SetRecordMirror
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex,     /* MISRA DEVIATION */
    P2VAR( Dem_DataMirrorInfoType, AUTOMATIC, AUTOMATIC ) BlockMirrorPtr
)
{
    VAR( Dem_u16_IUMPRIndexType, AUTOMATIC ) demIumprNum;
    demIumprNum = Dem_IUMPRRecordNum;

    if( (Dem_u16_IUMPRIndexType)(BlockMirrorPtr->RecordIndex) < demIumprNum )                               /* [GUD:if]BlockMirrorPtr->RecordIndex */
    {
        Dem_TmpIUMPRMirror.CommonCounter1   = Dem_IUMPRRecord[BlockMirrorPtr->RecordIndex].CommonCounter1;      /* [GUD]BlockMirrorPtr->RecordIndex */
        Dem_TmpIUMPRMirror.CommonCounter2   = Dem_IUMPRRecord[BlockMirrorPtr->RecordIndex].CommonCounter2;      /* [GUD]BlockMirrorPtr->RecordIndex */
        Dem_TmpIUMPRMirror.CommonCondition1 = Dem_IUMPRRecord[BlockMirrorPtr->RecordIndex].CommonCondition1;    /* [GUD]BlockMirrorPtr->RecordIndex */
        Dem_TmpIUMPRMirror.CommonCondition2 = Dem_IUMPRRecord[BlockMirrorPtr->RecordIndex].CommonCondition2;    /* [GUD]BlockMirrorPtr->RecordIndex */
        Dem_TmpIUMPRMirror.CommonCondition3 = Dem_IUMPRRecord[BlockMirrorPtr->RecordIndex].CommonCondition3;    /* [GUD]BlockMirrorPtr->RecordIndex */
        Dem_TmpIUMPRMirror.CommonCondition4 = Dem_IUMPRRecord[BlockMirrorPtr->RecordIndex].CommonCondition4;    /* [GUD]BlockMirrorPtr->RecordIndex */
    }

    BlockMirrorPtr->MirrorPtr = &Dem_TmpIUMPRMirror;

    return;
}

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */


/****************************************************************************/
/* Function Name | Dem_IUMPRMng_DataVerify                                  */
/* Description   | Verifies IUMPR data.                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordFieldIndex :                                  */
/*               |        Same record field index                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |          DEM_IRT_OK      : DataVerify completed.         */
/*               |          DEM_IRT_PENDING : Continue DataVerify.          */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]IUMPR    :   NotifySavedZone                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPRMng_DataVerify
(
    VAR( Dem_u16_RecordFieldIndexType, AUTOMATIC ) RecordFieldIndex     /* MISRA DEVIATION */
)
{
    VAR( Dem_u16_IUMPRIndexType, AUTOMATIC ) iumprIndex;
    VAR( Dem_u16_IUMPRIndexType, AUTOMATIC ) demIumprNum;
    VAR( Dem_u16_IUMPRIndexType,AUTOMATIC ) verifyLoopNumByCycle;
    VAR( Dem_u16_IUMPRIndexType,AUTOMATIC ) loopCount;
    VAR( Dem_u08_InternalReturnType,AUTOMATIC ) retVal;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindIUMPR;

    recMngCmnKindIUMPR = Dem_RecMngCmnKindIUMPR;
    demIumprNum = Dem_IUMPRRecordNum;
    verifyLoopNumByCycle = Dem_IUMPRRecordNumForVerifyByCycle;
    loopCount = ( Dem_u16_IUMPRIndexType )0U;
    retVal = DEM_IRT_OK;

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - start.   */
    Dem_NotifySavedZoneIUMPRUpdate_Enter();  /*  notify start :  savedzone area will be update.  */
    /*--------------------------------------*/

    for( iumprIndex = Dem_IUMPRIndexForVerify; iumprIndex < demIumprNum; iumprIndex++ )     /* [GUD:if]iumprIndex */
    {

        if( loopCount < verifyLoopNumByCycle )
        {
            if( Dem_IUMPRRecord[iumprIndex].CommonCondition4 ==  DEM_IUMPR_CONDITION_FACTORY_DEFAULT )      /* [GUD]iumprIndex */
            {
                /*  CommonCondition4 value is default.      */
                /*  invalid data.               */
                /*  initialize IUMPR record.      */
                Dem_IUMPRRecord[iumprIndex].CommonCounter1      = (uint16)0U;                                   /* [GUD]iumprIndex */   /*[UpdRec]IUMPR */
                Dem_IUMPRRecord[iumprIndex].CommonCounter2      = (uint16)0U;                                   /* [GUD]iumprIndex */   /*[UpdRec]IUMPR */
                Dem_IUMPRRecord[iumprIndex].CommonCondition1    = (uint8)0U;                                    /* [GUD]iumprIndex */   /*[UpdRec]IUMPR */
                Dem_IUMPRRecord[iumprIndex].CommonCondition2    = (uint8)0U;                                    /* [GUD]iumprIndex */   /*[UpdRec]IUMPR */
                Dem_IUMPRRecord[iumprIndex].CommonCondition3    = (uint8)0U;                                    /* [GUD]iumprIndex */   /*[UpdRec]IUMPR */
                Dem_IUMPRRecord[iumprIndex].CommonCondition4    = (uint8)0U;                                    /* [GUD]iumprIndex */   /*[UpdRec]IUMPR */
                Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindIUMPR, (Dem_u16_RecordIndexType)iumprIndex );     /* [GUD]iumprIndex */
            }

            loopCount = loopCount + (Dem_u16_IUMPRIndexType)1U;
        }
        else
        {
            Dem_IUMPRIndexForVerify = iumprIndex;
            retVal = DEM_IRT_PENDING;
            break;
        }
    }

    /*--------------------------------------*/
    /*  notify SAVED_ZONE update - end.     */
    Dem_NotifySavedZoneIUMPRUpdate_Exit();  /*  notify end :  savedzone area will be update.    */
    /*--------------------------------------*/

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_IUMPRMng_ClearCondition                              */
/* Description   | Initializes the value of IUMPR condition for DC Start    */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]IUMPR                                            */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPRMng_ClearCondition
( void )
{
    VAR( boolean, AUTOMATIC ) changeRecord;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindIUMPR;

    /* Clear Den Condition and IG Cycle Data */
    changeRecord = (boolean)TRUE;
    /* Dem_IUMPRRecord[DEM_IUMPR_GENDEN_IGCC_REC_INDEX].CommonCounter1 is stay */
    /* Dem_IUMPRRecord[DEM_IUMPR_GENDEN_IGCC_REC_INDEX].CommonCounter2 is stay */
    /* If The Condition is Initial Value(Zero) , changeFlag set FALSE */
    if( Dem_IUMPRRecord[DEM_IUMPR_GENDEN_IGCC_REC_INDEX].CommonCondition1 == (uint8)0U )            /*  Dem_IUMPRInfoRecordType.DenominatorCondition        */
    {
        if( Dem_IUMPRRecord[DEM_IUMPR_GENDEN_IGCC_REC_INDEX].CommonCondition2 == (uint8)0U )        /*  Dem_IUMPRInfoRecordType.GeneralDenAddedCondition    */
        {
            if( Dem_IUMPRRecord[DEM_IUMPR_GENDEN_IGCC_REC_INDEX].CommonCondition3 == (uint8)0U )    /*  Dem_IUMPRInfoRecordType.IGCycleAddedCondition       */
            {
                /* Don't have to change the Condition */
                changeRecord = (boolean)FALSE;
            }
        }
    }

    recMngCmnKindIUMPR = Dem_RecMngCmnKindIUMPR;

    if( changeRecord == (boolean)TRUE )
    {
        /* Condition to Initial Value */
        Dem_IUMPRRecord[DEM_IUMPR_GENDEN_IGCC_REC_INDEX].CommonCondition1 = (uint8)0U;  /*  Dem_IUMPRInfoRecordType.DenominatorCondition        */  /*[UpdRec]IUMPR */
        Dem_IUMPRRecord[DEM_IUMPR_GENDEN_IGCC_REC_INDEX].CommonCondition2 = (uint8)0U;  /*  Dem_IUMPRInfoRecordType.GeneralDenAddedCondition    */  /*[UpdRec]IUMPR */
        Dem_IUMPRRecord[DEM_IUMPR_GENDEN_IGCC_REC_INDEX].CommonCondition3 = (uint8)0U;  /*  Dem_IUMPRInfoRecordType.IGCycleAddedCondition       */  /*[UpdRec]IUMPR */
        Dem_IUMPRRecord[DEM_IUMPR_GENDEN_IGCC_REC_INDEX].CommonCondition4 = (uint8)0U;  /*  Dem_IUMPRInfoRecordType.Reserve1                    */  /*[UpdRec]IUMPR */
        Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindIUMPR, (Dem_u16_RecordIndexType)DEM_IUMPR_GENDEN_IGCC_REC_INDEX );
    }

#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )   /*  [FuncSw]    */
    Dem_IUMPRMng_Ratio_ClearCondition();    /*[UpdRec]IUMPR */
#endif  /* ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )            */

    return;
}



/****************************************************************************/
/* Function Name | Dem_IUMPRMng_GetIUMPRDenCondition                        */
/* Description   | In order to communicate the status of the (additional)   */
/*               | denominator conditions among the OBD relevant ECUs, the  */
/*               | API is used to retrieve the condition status from the    */
/*               | Dem of the ECU where the conditions are computed.        */
/* Preconditions | none                                                     */
/* Parameters    | [in] ConditionId :                                       */
/*               |          Identification of a IUMPR denominator           */
/*               |          condition ID.                                   */
/*               | [out] ConditionStatusPtr :                               */
/*               |          Status of the IUMPR denominator condition.      */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPRMng_GetIUMPRDenCondition
(
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC )                  ConditionId,
    P2VAR( Dem_IumprDenomCondStatusType, AUTOMATIC, AUTOMATIC ) ConditionStatusPtr
)
{
    VAR( Dem_IUMPRInfoRecordType, AUTOMATIC )       iumprInfoRecord;
    VAR( Dem_u08_IUMPRGenDenCondType, AUTOMATIC )                         checkCondBit;

    Dem_IUMPRMng_GetInfoRecord( &iumprInfoRecord );

    if( ConditionId == DEM_IUMPR_GENERAL_DENOMINATOR )
    {
        checkCondBit = DEM_IUMPRMNG_DEN_COND_GEN;
    }
    else if( ConditionId == DEM_IUMPR_DEN_COND_COLDSTART )
    {
        checkCondBit = DEM_IUMPRMNG_DEN_COND_COLD;
    }
    else if( ConditionId ==  DEM_IUMPR_DEN_COND_EVAP )
    {
        checkCondBit = DEM_IUMPRMNG_DEN_COND_EVAP;
    }
    else if( ConditionId == DEM_IUMPR_DEN_COND_500MI )
    {
        checkCondBit = DEM_IUMPRMNG_DEN_COND_500MI;
    }
    else
    {
        checkCondBit = DEM_IUMPRMNG_CONDITION_STATUS_INITVALUE;
    }

    *ConditionStatusPtr = DEM_IUMPR_DEN_STATUS_NOT_REACHED;
    if( (Dem_u08_IUMPRGenDenCondType)(iumprInfoRecord.DenominatorCondition & checkCondBit) != (Dem_u08_IUMPRGenDenCondType)0x00U )
    {
        *ConditionStatusPtr = DEM_IUMPR_DEN_STATUS_REACHED;
    }


    return;
}


/****************************************************************************/
/* Function Name | Dem_IUMPRMng_GetIGCycleCounter                           */
/* Description   | Get IG Cycle Counter Value                               */
/* Preconditions | none                                                     */
/* Parameters    | [out] IGCycleCounterPtr :                                */
/*               |        IGCycleCounter value.                             */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPRMng_GetIGCycleCounter
(
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC ) IGCycleCounterPtr
)
{
    VAR( Dem_IUMPRInfoRecordType, AUTOMATIC ) iumprInfoRecord;

    Dem_IUMPRMng_GetInfoRecord( &iumprInfoRecord );

    *IGCycleCounterPtr  = iumprInfoRecord.IGCycleCounter;

    return;
}


/****************************************************************************/
/* Function Name | Dem_IUMPRMng_GetIGCycleInformation                       */
/* Description   | Get IG Cycle Counter Information                         */
/* Preconditions | none                                                     */
/* Parameters    | [out] AddedConditionPtr :                                */
/*               |        AddedCondition information of IG cyclecounter.    */
/*               | [out] IGCycleCounterPtr :                                */
/*               |        IGCycleCounter value.                             */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPRMng_GetIGCycleInformation
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) AddedConditionPtr,
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC ) IGCycleCounterPtr
)
{
    VAR( Dem_IUMPRInfoRecordType, AUTOMATIC ) iumprInfoRecord;

    Dem_IUMPRMng_GetInfoRecord( &iumprInfoRecord );

    *IGCycleCounterPtr  = iumprInfoRecord.IGCycleCounter;
    *AddedConditionPtr  = (boolean)FALSE;
    if( (uint8)(iumprInfoRecord.IGCycleAddedCondition & DEM_IUMPR_RATIO_IGCC_ADD_BIT_MASK) != (uint8)0x00U )
    {
        *AddedConditionPtr  = (boolean)TRUE;
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_IUMPRMng_SetIGCycleInformation                       */
/* Description   | Set IG Cycle Counter Information                         */
/* Preconditions | none                                                     */
/* Parameters    | [in]  AddedCondition :                                   */
/*               |        AddedCondition information of IG cyclecounter.    */
/*               | [in]  IGCycleCounter :                                   */
/*               |        IGCycleCounter value.                             */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]IUMPR                                            */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPRMng_SetIGCycleInformation
(
    VAR( boolean, AUTOMATIC )   AddedCondition,
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )    IGCycleCounter
)
{
    VAR( Dem_IUMPRInfoRecordType, AUTOMATIC )       iumprInfoRecord;
    VAR( Dem_IUMPRCommonRecordInternalType, AUTOMATIC )     iumprRecord;
    VAR( boolean, AUTOMATIC )                       changeRecord;

    changeRecord = (boolean)FALSE;
    Dem_IUMPRMng_GetInfoRecord( &iumprInfoRecord );

    if( IGCycleCounter != iumprInfoRecord.IGCycleCounter )
    {
        iumprInfoRecord.IGCycleCounter = IGCycleCounter;
        changeRecord = (boolean)TRUE;
    }
    if( AddedCondition == (boolean)TRUE )
    {
        if( (uint8)(iumprInfoRecord.IGCycleAddedCondition & DEM_IUMPR_RATIO_IGCC_ADD_BIT_MASK) == (uint8)0x00U )
        {
            iumprInfoRecord.IGCycleAddedCondition = (uint8)(iumprInfoRecord.IGCycleAddedCondition | DEM_IUMPR_RATIO_IGCC_ADD_BIT_MASK);
            changeRecord = (boolean)TRUE;
        }
    }
    if( changeRecord == (boolean)TRUE )
    {
        /* Convert data */
        Dem_IUMPRMng_CnvInfoRecordToCommon( &iumprInfoRecord, &iumprRecord );
        /* Regist NvM Record */
        Dem_IUMPRMng_SetIUMPRGenDenRecordData( &iumprRecord );  /*[UpdRec]IUMPR */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_IUMPRMng_GetGeneralDenominator                       */
/* Description   | Get GeneralDenominator Counter                           */
/* Preconditions | none                                                     */
/* Parameters    | [out] GenDenCounterPtr :                                 */
/*               |        GeneralDenominator Counter value.                 */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPRMng_GetGeneralDenominator
(
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC ) GenDenCounterPtr
)
{
    VAR( Dem_IUMPRInfoRecordType, AUTOMATIC ) iumprInfoRecord;

    Dem_IUMPRMng_GetInfoRecord( &iumprInfoRecord );

    *GenDenCounterPtr   = iumprInfoRecord.GeneralDenCounter;

    return;
}


/****************************************************************************/
/* Function Name | Dem_IUMPRMng_GetGenDenInformation                        */
/* Description   | Get GeneralDenominator Counter Information               */
/* Preconditions | none                                                     */
/* Parameters    | [out] AddedConditionPtr :                                */
/*               |        AddedCondition information of Gen-Den counter.    */
/*               | [out] GenDenCounterPtr :                                 */
/*               |        GeneralDenominator Counter value.                 */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPRMng_GetGenDenInformation
(
    P2VAR( boolean, AUTOMATIC, AUTOMATIC ) AddedConditionPtr,
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC ) GenDenCounterPtr
)
{
    VAR( Dem_IUMPRInfoRecordType, AUTOMATIC ) iumprInfoRecord;

    Dem_IUMPRMng_GetInfoRecord( &iumprInfoRecord );

    *GenDenCounterPtr       = iumprInfoRecord.GeneralDenCounter;
    *AddedConditionPtr      = (boolean)FALSE;
    if( (Dem_u08_IUMPRGenAddedCondType)(iumprInfoRecord.GeneralDenAddedCondition & DEM_IUMPR_RATIO_GENDEN_ADD_BIT_MASK) != (Dem_u08_IUMPRGenAddedCondType)0x00U )
    {
        *AddedConditionPtr  = (boolean)TRUE;
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_IUMPRMng_SetGenDenInformation                        */
/* Description   | Set GeneralDenominator Counter Information               */
/* Preconditions | none                                                     */
/* Parameters    | [in]  AddedCondition :                                   */
/*               |        AddedCondition information of Gen-Den counter.    */
/*               | [in]  GenDenCounter :                                    */
/*               |        GeneralDenominator Counter value.                 */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]IUMPR                                            */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPRMng_SetGenDenInformation
(
    VAR( boolean, AUTOMATIC )   AddedCondition,
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )    GenDenCounter
)
{
    VAR( Dem_IUMPRInfoRecordType, AUTOMATIC )       iumprInfoRecord;
    VAR( Dem_IUMPRCommonRecordInternalType, AUTOMATIC )     iumprRecord;
    VAR( boolean, AUTOMATIC )                       changeRecord;

    changeRecord = (boolean)FALSE;
    Dem_IUMPRMng_GetInfoRecord( &iumprInfoRecord );

    if( GenDenCounter != iumprInfoRecord.GeneralDenCounter )
    {
        iumprInfoRecord.GeneralDenCounter = GenDenCounter;
        changeRecord = (boolean)TRUE;
    }
    if( AddedCondition == (boolean)TRUE )
    {
        if( (Dem_u08_IUMPRGenAddedCondType)(iumprInfoRecord.GeneralDenAddedCondition & DEM_IUMPR_RATIO_GENDEN_ADD_BIT_MASK) == (Dem_u08_IUMPRGenAddedCondType)0x00U )
        {
            iumprInfoRecord.GeneralDenAddedCondition = (Dem_u08_IUMPRGenAddedCondType)(iumprInfoRecord.GeneralDenAddedCondition | DEM_IUMPR_RATIO_GENDEN_ADD_BIT_MASK);
            changeRecord = (boolean)TRUE;
        }
    }
    if( changeRecord == (boolean)TRUE )
    {
        /* Convert data */
        Dem_IUMPRMng_CnvInfoRecordToCommon( &iumprInfoRecord, &iumprRecord );
        /* Regist NvM Record */
        Dem_IUMPRMng_SetIUMPRGenDenRecordData( &iumprRecord );  /*[UpdRec]IUMPR */
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_IUMPRMng_SetIUMPRDenCondition                        */
/* Description   | In order to communicate the status of the (additional)   */
/*               | denominator conditions among the OBD relevant ECUs, the  */
/*               | API is used to forward the condition status to a Dem of  */
/*               | a particular ECU.                                        */
/* Preconditions | none                                                     */
/* Parameters    | [in] ConditionId :                                       */
/*               |          Identification of a IUMPR denominator           */
/*               |          condition ID.                                   */
/*               | [in] ConditionStatus :                                   */
/*               |          Status of the IUMPR denominator condition.      */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]IUMPR                                            */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPRMng_SetIUMPRDenCondition
(
    VAR( Dem_IumprDenomCondIdType, AUTOMATIC )      ConditionId,
    VAR( Dem_IumprDenomCondStatusType, AUTOMATIC )  ConditionStatus
)
{

    VAR( Dem_IUMPRInfoRecordType, AUTOMATIC )       iumprInfoRecord;
    VAR( Dem_IUMPRCommonRecordInternalType, AUTOMATIC )     iumprRecord;
    VAR( Dem_u08_IUMPRGenDenCondType, AUTOMATIC )                         checkCondBit;
    VAR( Dem_u08_IUMPRGenDenCondType, AUTOMATIC )                         preDenominatorCondition;

    Dem_IUMPRMng_GetInfoRecord( &iumprInfoRecord );
    preDenominatorCondition = iumprInfoRecord.DenominatorCondition;

    if( ConditionId == DEM_IUMPR_GENERAL_DENOMINATOR )
    {
        checkCondBit = DEM_IUMPRMNG_DEN_COND_GEN;
    }
    else if( ConditionId == DEM_IUMPR_DEN_COND_COLDSTART )
    {
        checkCondBit = DEM_IUMPRMNG_DEN_COND_COLD;
    }
    else if( ConditionId ==  DEM_IUMPR_DEN_COND_EVAP )
    {
        checkCondBit = DEM_IUMPRMNG_DEN_COND_EVAP;
    }
    else if( ConditionId == DEM_IUMPR_DEN_COND_500MI )
    {
        checkCondBit = DEM_IUMPRMNG_DEN_COND_500MI;
    }
    else
    {
        checkCondBit = DEM_IUMPRMNG_CONDITION_STATUS_INITVALUE;
    }

    if( ConditionStatus == DEM_IUMPR_DEN_STATUS_REACHED )
    {
        iumprInfoRecord.DenominatorCondition    = (Dem_u08_IUMPRGenDenCondType)( iumprInfoRecord.DenominatorCondition | checkCondBit );
    }

    if( iumprInfoRecord.DenominatorCondition != preDenominatorCondition )
    {
        /* Convert data */
        Dem_IUMPRMng_CnvInfoRecordToCommon( &iumprInfoRecord, &iumprRecord );
        /* Regist NvM Record */
        Dem_IUMPRMng_SetIUMPRGenDenRecordData( &iumprRecord );  /*[UpdRec]IUMPR */
    }

    return;

}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_IUMPRMng_InitMirrorRecord                            */
/* Description   | Initializes the Mirror Memory.                           */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_IUMPRMng_InitMirrorRecord
( void )
{
    /*  initialize mirror memory area.              */
    Dem_TmpIUMPRMirror.CommonCounter1   = (uint16)0U;
    Dem_TmpIUMPRMirror.CommonCounter2   = (uint16)0U;
    Dem_TmpIUMPRMirror.CommonCondition1 = (uint8)0U;
    Dem_TmpIUMPRMirror.CommonCondition2 = (uint8)0U;
    Dem_TmpIUMPRMirror.CommonCondition3 = (uint8)0U;
    Dem_TmpIUMPRMirror.CommonCondition4 = (uint8)0U;

#if ( DEM_IUMPR_RECORD_PADDING_EXIST == STD_ON )    /* [FuncSw] */
    /*  initialize padding area of mrror memory.    */
    Dem_IUMPRMng_InitPadding( &Dem_TmpIUMPRMirror );
#endif /* DEM_IUMPR_RECORD_PADDING_EXIST -STD_ON- */

    return;

}

#if ( DEM_IUMPR_RECORD_PADDING_EXIST == STD_ON )
/****************************************************************************/
/* Function Name | Dem_IUMPRMng_InitPadding                                 */
/* Description   | Initializes the record padding data.                     */
/* Preconditions | none                                                     */
/* Parameters    | [in] IUMPRRecordPtr    :                                 */
/*               |       The pointer of the record.                         */
/*               |          &Dem_TmpIUMPRMirror -DEM_VAR_NO_INIT-           */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_IUMPRMng_InitPadding
(
    P2VAR( Dem_IUMPRCommonRecordType, AUTOMATIC, DEM_VAR_NO_INIT ) IUMPRRecordPtr
)
{
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingSize;
    VAR( Dem_u16_PaddingIndexType, AUTOMATIC ) paddingIndex;

    paddingSize = Dem_IUMPRRecordBlockPaddingSize;

    for( paddingIndex = (Dem_u16_PaddingIndexType)0U; paddingIndex < paddingSize; paddingIndex++ )  /* [GUD:for]paddingIndex */
    {
        IUMPRRecordPtr->Reserve[paddingIndex] = (uint8)0U;                                          /* [GUD]paddingIndex *//* [ARYCHK] DEM_IUMPR_RECORD_PADDINGSIZE_TO_BLOCKSIZE / 1 / paddingIndex */
    }
    return ;
}
#endif /* DEM_IUMPR_RECORD_PADDING_EXIST -STD_ON- */

#endif /* DEM_NVM_SYNC_PROCESS_ENABLE -STD_ON- */

/****************************************************************************/
/* Function Name | Dem_IUMPRMng_SetIUMPRGenDenRecordData                    */
/* Description   | Set IUMPR Record Data.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] IUMPRDataPtr :                                      */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]IUMPR                                            */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_IUMPRMng_SetIUMPRGenDenRecordData
(
    P2CONST( Dem_IUMPRCommonRecordInternalType, AUTOMATIC, AUTOMATIC )  IUMPRDataPtr
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindIUMPR;

    /* Enter exclusive area */
    SchM_Enter_Dem_IUMPRRatioData();

    /* Set IumorRecord data for GenDen and IGCC */
    Dem_IUMPRRecord[DEM_IUMPR_GENDEN_IGCC_REC_INDEX].CommonCounter1   = IUMPRDataPtr->CommonCounter1;   /*[UpdRec]IUMPR */
    Dem_IUMPRRecord[DEM_IUMPR_GENDEN_IGCC_REC_INDEX].CommonCounter2   = IUMPRDataPtr->CommonCounter2;   /*[UpdRec]IUMPR */
    Dem_IUMPRRecord[DEM_IUMPR_GENDEN_IGCC_REC_INDEX].CommonCondition1 = IUMPRDataPtr->CommonCondition1; /*[UpdRec]IUMPR */
    Dem_IUMPRRecord[DEM_IUMPR_GENDEN_IGCC_REC_INDEX].CommonCondition2 = IUMPRDataPtr->CommonCondition2; /*[UpdRec]IUMPR */
    Dem_IUMPRRecord[DEM_IUMPR_GENDEN_IGCC_REC_INDEX].CommonCondition3 = IUMPRDataPtr->CommonCondition3; /*[UpdRec]IUMPR */
    Dem_IUMPRRecord[DEM_IUMPR_GENDEN_IGCC_REC_INDEX].CommonCondition4 = IUMPRDataPtr->CommonCondition4; /*[UpdRec]IUMPR */

    /* Exit exclusive area */
    SchM_Exit_Dem_IUMPRRatioData();

    /* Change status */
    recMngCmnKindIUMPR = Dem_RecMngCmnKindIUMPR;
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindIUMPR, (Dem_u16_RecordIndexType)DEM_IUMPR_GENDEN_IGCC_REC_INDEX );

    return;
}


/****************************************************************************/
/* Function Name | Dem_IUMPRMng_GetInfoRecord                               */
/* Description   | Get GenDen and IG Cycle Information                      */
/* Preconditions | none                                                     */
/* Parameters    | [out] InfoRecordTypePtr :                                */
/*               |        GenDen and IG cycle information.                  */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_IUMPRMng_GetInfoRecord
(
    P2VAR( Dem_IUMPRInfoRecordType, AUTOMATIC, AUTOMATIC ) InfoRecordTypePtr
)
{
    /* Enter exclusive area */
    SchM_Enter_Dem_IUMPRRatioData();

    InfoRecordTypePtr->GeneralDenCounter            = ( Dem_u16_IUMPRCycleCounterType )Dem_IUMPRRecord[ DEM_IUMPR_GENDEN_IGCC_REC_INDEX ].CommonCounter1;
    InfoRecordTypePtr->IGCycleCounter               = ( Dem_u16_IUMPRCycleCounterType )Dem_IUMPRRecord[ DEM_IUMPR_GENDEN_IGCC_REC_INDEX ].CommonCounter2;
    InfoRecordTypePtr->DenominatorCondition         = ( Dem_u08_IUMPRGenDenCondType )Dem_IUMPRRecord[ DEM_IUMPR_GENDEN_IGCC_REC_INDEX ].CommonCondition1;
    InfoRecordTypePtr->GeneralDenAddedCondition     = ( Dem_u08_IUMPRGenAddedCondType )Dem_IUMPRRecord[ DEM_IUMPR_GENDEN_IGCC_REC_INDEX ].CommonCondition2;
    InfoRecordTypePtr->IGCycleAddedCondition        = ( Dem_u08_IUMPRGenAddedCondType )Dem_IUMPRRecord[ DEM_IUMPR_GENDEN_IGCC_REC_INDEX ].CommonCondition3;
    InfoRecordTypePtr->Reserve1                     = (uint8)0U;

    /* Exit exclusive area */
    SchM_Exit_Dem_IUMPRRatioData();

    return;
}


/****************************************************************************/
/* Function Name | Dem_IUMPRMng_CnvInfoRecordToCommon                       */
/* Description   | Get Ratio Record Information                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] IUMPRInfoRecordPtr :                                */
/*               |        InfoRecordData                                    */
/*               | [out] IUMPRDataPtr :                                     */
/*               |        IUMPRRecordData                                   */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_IUMPRMng_CnvInfoRecordToCommon
(
    P2CONST( Dem_IUMPRInfoRecordType, AUTOMATIC, AUTOMATIC )    IUMPRInfoRecordPtr,
    P2VAR( Dem_IUMPRCommonRecordInternalType, AUTOMATIC, AUTOMATIC )    IUMPRDataPtr
)
{

    IUMPRDataPtr->CommonCounter1    = IUMPRInfoRecordPtr->GeneralDenCounter         ;
    IUMPRDataPtr->CommonCounter2    = IUMPRInfoRecordPtr->IGCycleCounter            ;
    IUMPRDataPtr->CommonCondition1  = IUMPRInfoRecordPtr->DenominatorCondition      ;
    IUMPRDataPtr->CommonCondition2  = IUMPRInfoRecordPtr->GeneralDenAddedCondition  ;
    IUMPRDataPtr->CommonCondition3  = IUMPRInfoRecordPtr->IGCycleAddedCondition     ;
    IUMPRDataPtr->CommonCondition4  = IUMPRInfoRecordPtr->Reserve1                  ;

    return;
}


#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
/****************************************************************************/
/* Function Name | Dem_IUMPRMng_GetEventIdFromRecordData                    */
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
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPRMng_GetEventIdFromRecordData
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

#endif  /* ( DEM_IUMPR_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
