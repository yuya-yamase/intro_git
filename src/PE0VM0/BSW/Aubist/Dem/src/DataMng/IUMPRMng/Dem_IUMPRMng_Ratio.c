/* Dem_IUMPRMng_Ratio_c(v5-9-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/IUMPRMng_Ratio/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )

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
#define DEM_IUMPR_RATIO_REC_CNV_OFFSET          ((Dem_u16_IUMPRIndexType)0x01U)
#define DEM_IUMPR_RATIO_HIST_INF_BIT_MASK       ((Dem_u08_IUMPRRatioCondType)DEM_IUMPRMNG_RTO_COND_HST_500 | DEM_IUMPRMNG_RTO_COND_HST_GDN)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPRMng_GetRatioRecord
(
    VAR( Dem_RatioIdType, AUTOMATIC )                       RatioId,
    P2VAR( Dem_IUMPRRatioRecordType, AUTOMATIC, AUTOMATIC ) IUMPRRatioRecordPtr
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPRMng_CnvRatioIdToRecordIndex
(
    VAR( Dem_RatioIdType, AUTOMATIC )                       RatioId,
    P2VAR( Dem_u16_IUMPRIndexType, AUTOMATIC, AUTOMATIC )   RecordIndexPtr
);

static FUNC( void, DEM_CODE ) Dem_IUMPRMng_CnvRatioRecordToCommon
(
    P2CONST( Dem_IUMPRRatioRecordType, AUTOMATIC, AUTOMATIC )   IUMPRRatioRecordPtr,
    P2VAR( Dem_IUMPRCommonRecordInternalType, AUTOMATIC, AUTOMATIC )    IUMPRDataPtr
);

static FUNC( void, DEM_CODE ) Dem_IUMPRMng_SetIUMPRRecordData
(
    VAR( Dem_u16_IUMPRIndexType, AUTOMATIC )                    RecordIndex,
    P2CONST( Dem_IUMPRCommonRecordInternalType, AUTOMATIC, AUTOMATIC )  IUMPRDataPtr
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


#define DEM_START_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_VAR_SAVED_ZONE
#include <Dem_MemMap.h>


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

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
FUNC( void, DEM_CODE ) Dem_IUMPRMng_Ratio_ClearCondition
( void )
{
    VAR( Dem_u16_IUMPRIndexType, AUTOMATIC ) iumprIndex;
    VAR( Dem_u16_IUMPRIndexType, AUTOMATIC ) demIumprNum;
    VAR( uint8, AUTOMATIC ) tempCondition;
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindIUMPR;

    demIumprNum = Dem_IUMPRRecordNum;
    recMngCmnKindIUMPR = Dem_RecMngCmnKindIUMPR;

    /* Clear Ratio Condition Data */
    for( iumprIndex = DEM_IUMPR_RATIO_REC_START_INDEX; iumprIndex < demIumprNum; iumprIndex++ ) /* [GUD:if]iumprIndex */
    {
        /* Dem_IUMPRRecord[iumprIndex].CommonCounter1 is stay */
        /* Dem_IUMPRRecord[iumprIndex].CommonCounter2 is stay */
        tempCondition = (uint8)( (uint8)Dem_IUMPRRecord[ iumprIndex ].CommonCondition1 & DEM_IUMPR_RATIO_HIST_INF_BIT_MASK );   /*  Dem_IUMPRRatioRecordType.RatioCondition */  /* [GUD]iumprIndex */
        if( tempCondition != Dem_IUMPRRecord[ iumprIndex ].CommonCondition1 )       /*  Dem_IUMPRRatioRecordType.RatioCondition :   check bit status of another (DEM_IUMPRMNG_RTO_COND_HST_500 or DEM_IUMPRMNG_RTO_COND_HST_GDN )   */      /* [GUD]iumprIndex */
        {
            Dem_IUMPRRecord[ iumprIndex ].CommonCondition1 = tempCondition;         /*  clear bit : DEM_IUMPRMNG_RTO_COND_NUME_EST or DEM_IUMPRMNG_RTO_COND_NUME_ADD or DEM_IUMPRMNG_RTO_COND_DEN_EST or DEM_IUMPRMNG_RTO_COND_DEN_ADD  */  /* [GUD]iumprIndex */   /*[UpdRec]IUMPR */
            Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindIUMPR, (Dem_u16_RecordIndexType)iumprIndex );     /* [GUD]iumprIndex */
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_IUMPRMng_GetRatioByRatioId                           */
/* Description   | Get numerator and denominator for IUMPR.                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] RatioID :                                           */
/*               |          Ratio Identifier reporting that a respective    */
/*               |          monitor could have found a fault.               */
/*               | [out] NumeratorPtr   : Numerator.                        */
/*               | [out] DenominatorPtr : Denominator.                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Operation was successful.            */
/*               |        DEM_IRT_NG : Operation failed.                    */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPRMng_GetRatioByRatioId
(
    VAR( Dem_RatioIdType, AUTOMATIC )       RatioId,
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC )   NumeCounterPtr,
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC )   DenCounterPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                     retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                     retGetRecord;
    VAR( Dem_IUMPRRatioRecordType, AUTOMATIC )  iumprRatioRecord;

    retVal              = DEM_IRT_NG;
    *DenCounterPtr      = DEM_IUMPR_COUNTER_INITVALUE;
    *NumeCounterPtr     = DEM_IUMPR_COUNTER_INITVALUE;

    retGetRecord        = Dem_IUMPRMng_GetRatioRecord( RatioId, &iumprRatioRecord );    /* [GUD:RET:DEM_IRT_OK] RatioId */
    if( retGetRecord == DEM_IRT_OK )
    {
        *DenCounterPtr  = iumprRatioRecord.DenominatorCounter;
        *NumeCounterPtr = iumprRatioRecord.NumeratorCounter;
        retVal          = DEM_IRT_OK;
    }

    return retVal;

}


/****************************************************************************/
/* Function Name | Dem_IUMPRMng_GetRatioInformation                         */
/* Description   | Get Information of RatioID                               */
/* Preconditions | none                                                     */
/* Parameters    | [in]  RatioId :                                          */
/*               |        Target RatioId.                                   */
/*               | [out] RatioConditionPtr :                                */
/*               |        Condition of RatioId.                             */
/*               | [out] NumeCounterPtr :                                   */
/*               |        Numerator Counter Value of RatioId.               */
/*               | [out] DenCounterPtr :                                    */
/*               |        Denominator Counter Value of RatioId.             */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] RatioId                             */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPRMng_GetRatioInformation
(
    VAR( Dem_RatioIdType, AUTOMATIC )       RatioId,
    P2VAR( Dem_u08_IUMPRRatioCondType, AUTOMATIC, AUTOMATIC )    RatioConditionPtr,
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC )   NumeCounterPtr,
    P2VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC, AUTOMATIC )   DenCounterPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     retGetRecord;
    VAR( Dem_IUMPRRatioRecordType, AUTOMATIC )  iumprRatioRecord;

    retVal                  = DEM_IRT_NG;

    retGetRecord            = Dem_IUMPRMng_GetRatioRecord( RatioId, &iumprRatioRecord );    /* [GUD:RET:DEM_IRT_OK] RatioId */
    if( retGetRecord == DEM_IRT_OK )
    {
        *DenCounterPtr      = iumprRatioRecord.DenominatorCounter;
        *NumeCounterPtr     = iumprRatioRecord.NumeratorCounter;
        *RatioConditionPtr  = iumprRatioRecord.RatioCondition;
        retVal              = DEM_IRT_OK;
    }

    return retVal;

}


/****************************************************************************/
/* Function Name | Dem_IUMPRMng_SetRatioInformation                         */
/* Description   | Set Information of RatioID                               */
/* Preconditions | none                                                     */
/* Parameters    | [in]  RatioId :                                          */
/*               |        TarSet RatioId.                                   */
/*               | [in]  RatioCondition :                                   */
/*               |        Condition of RatioId.                             */
/*               | [in]  NumeCounter :                                      */
/*               |        Numerator Counter Value of RatioId.               */
/*               | [in]  DenCounter :                                       */
/*               |        Denominator Counter Value of RatioId.             */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]IUMPR                                            */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPRMng_SetRatioInformation
(
    VAR( Dem_RatioIdType, AUTOMATIC )   RatioId,
    VAR( Dem_u08_IUMPRRatioCondType,  AUTOMATIC )            RatioCondition,
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )            NumeCounter,
    VAR( Dem_u16_IUMPRCycleCounterType, AUTOMATIC )            DenCounter
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                     retGetRecord;
    VAR( Dem_IUMPRRatioRecordType, AUTOMATIC )  iumprRatioRecord;
    VAR( Dem_IUMPRCommonRecordInternalType, AUTOMATIC ) iumprRecord;
    VAR( Dem_u16_IUMPRIndexType, AUTOMATIC )    recordIndex;
    VAR( boolean, AUTOMATIC )                   changeRecord;

    changeRecord = (boolean)FALSE;
    retGetRecord = Dem_IUMPRMng_GetRatioRecord( RatioId, &iumprRatioRecord );   /* [GUD:RET:DEM_IRT_OK] RatioId */

    if( retGetRecord == DEM_IRT_OK )
    {
        if( DenCounter != iumprRatioRecord.DenominatorCounter )
        {
            iumprRatioRecord.DenominatorCounter = DenCounter;
            changeRecord = (boolean)TRUE;
        }
        if( NumeCounter != iumprRatioRecord.NumeratorCounter )
        {
            iumprRatioRecord.NumeratorCounter = NumeCounter;
            changeRecord = (boolean)TRUE;
        }
        if( RatioCondition != iumprRatioRecord.RatioCondition )
        {
            iumprRatioRecord.RatioCondition = RatioCondition;
            changeRecord = (boolean)TRUE;
        }

        if( changeRecord == (boolean)TRUE )
        {
            /* Convert data */
            Dem_IUMPRMng_CnvRatioRecordToCommon( &iumprRatioRecord, &iumprRecord );
            recordIndex =   (Dem_u16_IUMPRIndexType)0U;
            (void)Dem_IUMPRMng_CnvRatioIdToRecordIndex( RatioId, &recordIndex );    /* no return check required *//* [GUD]RatioId *//* [GUD:RET:DEM_IRT_OK]recordIndex */
            /* Regist NvM Record */
            Dem_IUMPRMng_SetIUMPRRecordData( recordIndex, &iumprRecord );           /* [GUD]recordIndex *//*[UpdRec]IUMPR */
        }

    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_IUMPRMng_SetRatioNumeAdditionCondition               */
/* Description   | Service for reporting that faults are possibly found     */
/*               | because all conditions are fullfilled.                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] RatioId :                                           */
/*               |          Ratio Identifier reporting that a respective    */
/*               |          monitor could have found a fault                */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]IUMPR                                            */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPRMng_SetRatioNumeAdditionCondition
(
    VAR( Dem_RatioIdType, AUTOMATIC ) RatioId
)
{

    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                     retGetRecord;
    VAR( Dem_IUMPRRatioRecordType, AUTOMATIC )  iumprRatioRecord;
    VAR( Dem_IUMPRCommonRecordInternalType, AUTOMATIC ) iumprRecord;
    VAR( Dem_u16_IUMPRIndexType, AUTOMATIC )    recordIndex;

    retGetRecord = Dem_IUMPRMng_GetRatioRecord( RatioId, &iumprRatioRecord );   /* [GUD:RET:DEM_IRT_OK] RatioId */

    if( retGetRecord == DEM_IRT_OK )
    {
        if( (Dem_u08_IUMPRRatioCondType)( iumprRatioRecord.RatioCondition & DEM_IUMPRMNG_RTO_COND_NUME_EST ) == (Dem_u08_IUMPRRatioCondType)0x00U )
        {
            iumprRatioRecord.RatioCondition = (uint8)( iumprRatioRecord.RatioCondition | DEM_IUMPRMNG_RTO_COND_NUME_EST );
            /* Convert data */
            Dem_IUMPRMng_CnvRatioRecordToCommon( &iumprRatioRecord, &iumprRecord );
            recordIndex =   (Dem_u16_IUMPRIndexType)0U;
            (void)Dem_IUMPRMng_CnvRatioIdToRecordIndex( RatioId, &recordIndex );    /* no return check required *//* [GUD]RatioId *//* [GUD:RET:DEM_IRT_OK]recordIndex */
            /* Regist NvM Record */
            Dem_IUMPRMng_SetIUMPRRecordData( recordIndex, &iumprRecord );           /* [GUD]recordIndex *//*[UpdRec]IUMPR */
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_IUMPRMng_SetRatioDenUnlockCondition                  */
/* Description   | Service for reporting that faults are possibly found     */
/*               | because all conditions are fullfilled.                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] RatioId :                                           */
/*               |          Ratio Identifier reporting that a respective    */
/*               |          monitor could have found a fault                */
/* Return Value  | none                                                     */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]IUMPR                                            */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_IUMPRMng_SetRatioDenUnlockCondition
(
    VAR( Dem_RatioIdType, AUTOMATIC ) RatioId
)
{

    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                     retGetRecord;
    VAR( Dem_IUMPRRatioRecordType, AUTOMATIC )  iumprRatioRecord;
    VAR( Dem_IUMPRCommonRecordInternalType, AUTOMATIC ) iumprRecord;
    VAR( Dem_u16_IUMPRIndexType, AUTOMATIC )    recordIndex;

    retGetRecord = Dem_IUMPRMng_GetRatioRecord( RatioId, &iumprRatioRecord );   /* [GUD:RET:DEM_IRT_OK] RatioId */

    if( retGetRecord == DEM_IRT_OK )
    {
        if( (Dem_u08_IUMPRRatioCondType)( iumprRatioRecord.RatioCondition & DEM_IUMPRMNG_RTO_COND_DEN_EST ) == (Dem_u08_IUMPRRatioCondType)0x00U )
        {
            iumprRatioRecord.RatioCondition = (Dem_u08_IUMPRRatioCondType)( iumprRatioRecord.RatioCondition | DEM_IUMPRMNG_RTO_COND_DEN_EST );
            /* Convert data */
            Dem_IUMPRMng_CnvRatioRecordToCommon( &iumprRatioRecord, &iumprRecord );
            recordIndex =   (Dem_u16_IUMPRIndexType)0U;
            (void)Dem_IUMPRMng_CnvRatioIdToRecordIndex( RatioId, &recordIndex );    /* no return check required *//* [GUD]RatioId *//* [GUD:RET:DEM_IRT_OK]recordIndex */
            /* Regist NvM Record */
            Dem_IUMPRMng_SetIUMPRRecordData( recordIndex, &iumprRecord );           /* [GUD]recordIndex *//*[UpdRec]IUMPR */
        }
    }

    return;
}


/****************************************************************************/
/* Function Name | Dem_IUMPRMng_GetRatioRecord                              */
/* Description   | Get Ratio Record Information                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] RatioId :                                           */
/*               |        Ratio ID                                          */
/*               | [out] IUMPRRatioRecordPtr :                              */
/*               |        Ratio Record information.                         */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] RatioId                             */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPRMng_GetRatioRecord
(
    VAR( Dem_RatioIdType, AUTOMATIC )                       RatioId,
    P2VAR( Dem_IUMPRRatioRecordType, AUTOMATIC, AUTOMATIC ) IUMPRRatioRecordPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     retCnvIdx;
    VAR( Dem_u16_IUMPRIndexType, AUTOMATIC )    iumprRatioRecord;

    retVal      = DEM_IRT_NG;

    retCnvIdx   = Dem_IUMPRMng_CnvRatioIdToRecordIndex( RatioId, &iumprRatioRecord );   /* [GUD:RET:DEM_IRT_OK] RatioId *//* [GUD:RET:DEM_IRT_OK] iumprRatioRecord */

    if( retCnvIdx == DEM_IRT_OK )
    {
        /* Enter exclusive area */
        SchM_Enter_Dem_IUMPRRatioData();

        IUMPRRatioRecordPtr->DenominatorCounter = ( Dem_u16_IUMPRCycleCounterType )Dem_IUMPRRecord[ iumprRatioRecord ].CommonCounter1;  /* [GUD]iumprRatioRecord */
        IUMPRRatioRecordPtr->NumeratorCounter   = ( Dem_u16_IUMPRCycleCounterType )Dem_IUMPRRecord[ iumprRatioRecord ].CommonCounter2;  /* [GUD]iumprRatioRecord */
        IUMPRRatioRecordPtr->RatioCondition     = ( Dem_u08_IUMPRRatioCondType )Dem_IUMPRRecord[ iumprRatioRecord ].CommonCondition1;   /* [GUD]iumprRatioRecord */
        IUMPRRatioRecordPtr->Reserve1           = (uint8)0U;
        IUMPRRatioRecordPtr->Reserve2           = (uint8)0U;
        IUMPRRatioRecordPtr->Reserve3           = (uint8)0U;

        /* Exit exclusive area */
        SchM_Exit_Dem_IUMPRRatioData();
        retVal                                  = DEM_IRT_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_IUMPRMng_CnvRatioIdToRecordIndex                     */
/* Description   | Get RecordIndex Corresponding To RatioId                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] RatioId :                                           */
/*               |        Target RatioId.                                   */
/*               | [out] RecordIndexPtr :                                   */
/*               |        RecordIndex.                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:DEM_IRT_OK] RatioId                             */
/* VariableGuard | [GUD:RET:DEM_IRT_OK] RecordIndexPtr                      */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-9-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPRMng_CnvRatioIdToRecordIndex
(
    VAR( Dem_RatioIdType, AUTOMATIC )                       RatioId,
    P2VAR( Dem_u16_IUMPRIndexType, AUTOMATIC, AUTOMATIC )   RecordIndexPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )     retVal;
    VAR( Dem_u16_IUMPRIndexType, AUTOMATIC ) demIumprNum;
    VAR( Dem_u16_IUMPRIndexType, AUTOMATIC ) recordIndex;

    demIumprNum     = Dem_IUMPRRecordNum;
    retVal          = DEM_IRT_NG;

    recordIndex     = (Dem_u16_IUMPRIndexType)( (Dem_u16_IUMPRIndexType)RatioId + DEM_IUMPR_RATIO_REC_CNV_OFFSET );

    if( recordIndex < demIumprNum )     /* [GUD:if]recordIndex */
    {
        *RecordIndexPtr = recordIndex;
        retVal          = DEM_IRT_OK;
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_IUMPRMng_CnvRatioRecordToCommon                      */
/* Description   | Get Ratio Record Information                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] IUMPRRatioRecordPtr :                               */
/*               |        RatioRecordData                                   */
/*               | [out] IUMPRDataPtr :                                     */
/*               |        IUMPRRecordData                                   */
/* Return Value  | none                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_IUMPRMng_CnvRatioRecordToCommon
(
    P2CONST( Dem_IUMPRRatioRecordType, AUTOMATIC, AUTOMATIC )   IUMPRRatioRecordPtr,
    P2VAR( Dem_IUMPRCommonRecordInternalType, AUTOMATIC, AUTOMATIC )    IUMPRDataPtr
)
{

    IUMPRDataPtr->CommonCounter1    = IUMPRRatioRecordPtr->DenominatorCounter   ;
    IUMPRDataPtr->CommonCounter2    = IUMPRRatioRecordPtr->NumeratorCounter     ;
    IUMPRDataPtr->CommonCondition1  = IUMPRRatioRecordPtr->RatioCondition       ;
    IUMPRDataPtr->CommonCondition2  = IUMPRRatioRecordPtr->Reserve1             ;
    IUMPRDataPtr->CommonCondition3  = IUMPRRatioRecordPtr->Reserve2             ;
    IUMPRDataPtr->CommonCondition4  = IUMPRRatioRecordPtr->Reserve3             ;

    return;
}

/****************************************************************************/
/* Function Name | Dem_IUMPRMng_SetIUMPRRecordData                          */
/* Description   | Set IUMPR Record Data.                                   */
/* Preconditions | none                                                     */
/* Parameters    | [in] RecordIndex :                                       */
/*               | [in] IUMPRDataPtr :                                      */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* UpdateRecord  | [UpdRec]IUMPR                                            */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_IUMPRMng_SetIUMPRRecordData
(
    VAR( Dem_u16_IUMPRIndexType, AUTOMATIC )                    RecordIndex,        /* [PRMCHK:CALLER] */
    P2CONST( Dem_IUMPRCommonRecordInternalType, AUTOMATIC, AUTOMATIC )  IUMPRDataPtr
)
{
    VAR( Dem_u16_RecordKindIndexType, AUTOMATIC ) recMngCmnKindIUMPR;

    /* Enter exclusive area */
    SchM_Enter_Dem_IUMPRRatioData();

    /* Set IumorRecord data for GenDen and IGCC */
    Dem_IUMPRRecord[RecordIndex].CommonCounter1   = IUMPRDataPtr->CommonCounter1;       /* [GUDCHK:CALLER]RecordIndex */    /*[UpdRec]IUMPR */
    Dem_IUMPRRecord[RecordIndex].CommonCounter2   = IUMPRDataPtr->CommonCounter2;       /* [GUDCHK:CALLER]RecordIndex */    /*[UpdRec]IUMPR */
    Dem_IUMPRRecord[RecordIndex].CommonCondition1 = IUMPRDataPtr->CommonCondition1;     /* [GUDCHK:CALLER]RecordIndex */    /*[UpdRec]IUMPR */
    Dem_IUMPRRecord[RecordIndex].CommonCondition2 = IUMPRDataPtr->CommonCondition2;     /* [GUDCHK:CALLER]RecordIndex */    /*[UpdRec]IUMPR */
    Dem_IUMPRRecord[RecordIndex].CommonCondition3 = IUMPRDataPtr->CommonCondition3;     /* [GUDCHK:CALLER]RecordIndex */    /*[UpdRec]IUMPR */
    Dem_IUMPRRecord[RecordIndex].CommonCondition4 = IUMPRDataPtr->CommonCondition4;     /* [GUDCHK:CALLER]RecordIndex */    /*[UpdRec]IUMPR */

    /* Exit exclusive area */
    SchM_Exit_Dem_IUMPRRatioData();

    /* Change status */
    recMngCmnKindIUMPR = Dem_RecMngCmnKindIUMPR;
    Dem_RecMngCmn_SetNvMWriteStatus( recMngCmnKindIUMPR, (Dem_u16_RecordIndexType)RecordIndex );    /* [GUDCHK:CALLER]RecordIndex */

    return;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_IUMPR_RATIO_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
