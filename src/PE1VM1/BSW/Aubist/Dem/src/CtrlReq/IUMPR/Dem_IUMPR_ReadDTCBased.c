/* Dem_IUMPR_ReadDTCBased_c(v5-9-0)                                         */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/IUMPR_ReadDTCBased/CODE                               */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#if ( DEM_IUMPR_EDR_SUPPORT == STD_ON )

#include <Dem/Dem_InternalDataElement.h>
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_IUMPR.h"
#include "../../../inc/Dem_Rc_IUMPRMng.h"
/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_IUMPR_BITSHIFT_8             ((uint8)8U)

#define DEM_IUMPR_DATABUF_SIZE           ((uint16)4U)
#define DEM_IUMPR_DATABUF_NUMERATOR_0    ((uint8)0U)
#define DEM_IUMPR_DATABUF_NUMERATOR_1    ((uint8)1U)
#define DEM_IUMPR_DATABUF_DENOMINATOR_0  ((uint8)2U)
#define DEM_IUMPR_DATABUF_DENOMINATOR_1  ((uint8)3U)



/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( void, DEM_CODE ) Dem_IUMPR_GetCurrentReadDTCBasedIUMPR
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    P2VAR( uint16, AUTOMATIC, AUTOMATIC )        CurrentNumeratorPtr,
    P2VAR( uint16, AUTOMATIC, AUTOMATIC )        CurrentDenominatorPtr
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
/* Function Name | Dem_IUMPR_ReadDTCBasedIUMPR                              */
/* Description   | Read DTC Based IUMPR                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in]     EventCtrlIndex                                  */
/*               | [in]     DTCValue                                        */
/*               | [in]     GetExtendDataMode                               */
/*               | [out]    BufferPtr                                       */
/*               | [in/out] BufSizePtr                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |       DEM_IRT_OK : success                               */
/*               |       DEM_IRT_WRONG_BUFFERSIZE : buffer size overflow    */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-9-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_IUMPR_ReadDTCBasedIUMPR
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,        /* [PRMCHK:CALLER] */
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,                /* MISRA DEVIATION */
    VAR( Dem_u08_GetExtendDataModeType, AUTOMATIC ) GetExtendDataMode,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) BufferPtr,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr
)
{
    VAR( uint16, AUTOMATIC )                    currentNumerator;
    VAR( uint16, AUTOMATIC )                    currentDenominator;
    VAR( uint16, AUTOMATIC )                    bufSizeIn;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )                     retVal;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexCnt;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;
    VAR( boolean, AUTOMATIC ) availableStatus;

    currentNumerator = DEM_IUMPR_COUNTER_INITVALUE;
    currentDenominator = DEM_IUMPR_COUNTER_INITVALUE;
    bufSizeIn = (*BufSizePtr);
    retVal = DEM_IRT_OK;

    if( bufSizeIn < DEM_IUMPR_DATABUF_SIZE )
    {
        /* Buffer size overflow */
        retVal = DEM_IRT_WRONG_BUFFERSIZE;
    }
    else
    {
        if ( GetExtendDataMode == DEM_EDR_GETEDRMODE_DTC )
        {
            /*------------------------------*/
            /*  DTC group.                  */
            /*------------------------------*/
            /*  primary event only.         */
            eventStrgIndex      =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );                    /* [GUDCHK:CALLER]EventCtrlIndex *//* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */

            /*  get target event    */
            eventCtrlIndexNum   =   Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp( eventStrgIndex );          /*  get EventCtrlIndex of EventStorageGroup max number  */
            eventCtrlIndex      =   EventCtrlIndex;    /*  get delegate eventCtrlIndex                         */

            for ( eventCtrlIndexCnt = ( Dem_u16_EventCtrlIndexType )0U; eventCtrlIndexCnt < eventCtrlIndexNum; eventCtrlIndexCnt++ )
            {
                availableStatus = Dem_DataAvl_GetEvtAvl( eventCtrlIndex );
                if( availableStatus == (boolean)TRUE )
                {
                    Dem_IUMPR_GetCurrentReadDTCBasedIUMPR( eventCtrlIndex, &currentNumerator, &currentDenominator );        /* [GUDCHK:CALLER]EventCtrlIndex */
                }
                /*  get next Index.         */
                eventCtrlIndex  =   Dem_CmbEvt_GetNextEventCtrlIndex_InEvtStrgGrp( eventCtrlIndex );
            }
        }
        else
        {
            /*------------------------------*/
            /*  event Id.                   */
            /*------------------------------*/
            Dem_IUMPR_GetCurrentReadDTCBasedIUMPR( EventCtrlIndex, &currentNumerator, &currentDenominator );            /* [GUDCHK:CALLER]EventCtrlIndex */
        }

        BufferPtr[DEM_IUMPR_DATABUF_NUMERATOR_0] = (uint8)( currentNumerator >> DEM_IUMPR_BITSHIFT_8 );/* [ARYCHK] *BufSizePtr/1/DEM_IUMPR_DATABUF_NUMERATOR_0 */
        BufferPtr[DEM_IUMPR_DATABUF_NUMERATOR_1] = (uint8)( currentNumerator ); /* [ARYCHK] *BufSizePtr/1/DEM_IUMPR_DATABUF_NUMERATOR_1 */
        BufferPtr[DEM_IUMPR_DATABUF_DENOMINATOR_0] = (uint8)( currentDenominator >> DEM_IUMPR_BITSHIFT_8 ); /* [ARYCHK] *BufSizePtr/1/DEM_IUMPR_DATABUF_DENOMINATOR_0 */
        BufferPtr[DEM_IUMPR_DATABUF_DENOMINATOR_1] = (uint8)( currentDenominator ); /* [ARYCHK] *BufSizePtr/1/DEM_IUMPR_DATABUF_DENOMINATOR_1 */
        (*BufSizePtr) = DEM_IUMPR_DATABUF_SIZE;
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_IUMPR_GetCurrentReadDTCBasedIUMPR                    */
/* Description   | Read DTC Based IUMPR                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in]     EventCtrlIndex                                  */
/*               | [in/out]    CurrentNumeratorPtr                          */
/*               | [in/out]    CurrentDenominatorPtr                        */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_IUMPR_GetCurrentReadDTCBasedIUMPR
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,        /* [PRMCHK:CALLER] */
    P2VAR( uint16, AUTOMATIC, AUTOMATIC )        CurrentNumeratorPtr,
    P2VAR( uint16, AUTOMATIC, AUTOMATIC )        CurrentDenominatorPtr
)
{
    VAR( Dem_RatioIdType, AUTOMATIC )                       ratioId;
    VAR( Dem_u16_RatioIndexType, AUTOMATIC )                tableIndex;
    VAR( Dem_u16_RatioIndexType, AUTOMATIC )                ratioIdTableNum;
    VAR( Dem_u16_RatioIdListAdrIndexType, AUTOMATIC )       ratioIdListAdrIndex;
    VAR( uint16, AUTOMATIC )                    currentNumerator;
    VAR( uint16, AUTOMATIC )                    currentDenominator;
    VAR( uint16, AUTOMATIC )                    targetNumerator;
    VAR( uint16, AUTOMATIC )                    targetDenominator;
    VAR( boolean, AUTOMATIC )                   resultJudge;

    currentNumerator    =   *CurrentNumeratorPtr;
    currentDenominator  =   *CurrentDenominatorPtr;

    targetNumerator = DEM_IUMPR_COUNTER_INITVALUE;
    targetDenominator = DEM_IUMPR_COUNTER_INITVALUE;

    ratioIdTableNum = Dem_RatioDataTable[ EventCtrlIndex ].TableNum;                                    /* [GUDCHK:CALLER]EventCtrlIndex *//* [GUD:CFG:IF_GUARDED: EventCtrlIndex ]ratioIdTableNum */
    ratioIdListAdrIndex = Dem_RatioDataTable[ EventCtrlIndex ].RatioIdListAdrTableIdx;                  /* [GUDCHK:CALLER]EventCtrlIndex *//* [GUD:CFG:IF_GUARDED: EventCtrlIndex ]ratioIdListAdrIndex */

    for( tableIndex = (Dem_u16_RatioIndexType)0U; tableIndex < ratioIdTableNum; tableIndex++ )
    {
        ratioId = Dem_RatioIdListAdrTable[ ratioIdListAdrIndex ].RatioIdListAdr[ tableIndex ];          /* [GUDCHK:CALLER]EventCtrlIndex *//* [ARYCHK] ratioIdTableNum / 1 / tableIndex */

        (void)Dem_IUMPRMng_GetRatioByRatioId( ratioId, &targetNumerator, &targetDenominator );  /* no return check required */
        resultJudge = Dem_IUMPR_JudgeMinThanCurrentRatio( currentNumerator, currentDenominator, targetNumerator, targetDenominator );
        if( resultJudge == (boolean)TRUE )
        {
            currentNumerator    = targetNumerator;
            currentDenominator  = targetDenominator;
        }
    }
    *CurrentNumeratorPtr    =   currentNumerator;
    *CurrentDenominatorPtr  =   currentDenominator;

    return ;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_IUMPR_EDR_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

