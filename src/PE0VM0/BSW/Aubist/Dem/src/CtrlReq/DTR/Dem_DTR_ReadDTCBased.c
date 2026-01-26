/* Dem_DTR_ReadDTCBased_c(v5-5-0)                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DTR_ReadDTCBased/CODE                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_DTR_EDR_SUPPORT == STD_ON )

#include <Dem/Dem_InternalDataElement.h>
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_Pm_DTR.h"
#include "../../../inc/Dem_Rc_DTRMng.h"
#include "../../../inc/Dem_CmnLib_Control.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define DEM_DTR_DATABUF_TESTRESULT      ((uint16)0U)
#define DEM_DTR_DATABUF_DTR             ((uint16)1U)

#define DEM_DTR_DATA_SIZE_PER_DTR       ((uint16)8U)
#define DEM_DTR_BUF_OFFSET_UAS_ID_1     ((uint16)1U)
#define DEM_DTR_BUF_OFFSET_TEST_VAL_0   ((uint16)2U)
#define DEM_DTR_BUF_OFFSET_TEST_VAL_1   ((uint16)3U)
#define DEM_DTR_BUF_OFFSET_LIMIT_MIN_0  ((uint16)4U)
#define DEM_DTR_BUF_OFFSET_LIMIT_MIN_1  ((uint16)5U)
#define DEM_DTR_BUF_OFFSET_LIMIT_MAX_0  ((uint16)6U)
#define DEM_DTR_BUF_OFFSET_LIMIT_MAX_1  ((uint16)7U)

#define DEM_DTR_BITSHIFT_8              ((uint8)8U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTR_GetCurrentDTCBasedTestResult
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( boolean, AUTOMATIC ) ExecClearDTC,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOriginInClear,
    VAR( uint16, AUTOMATIC ) BufSizeIn,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) TestResultNumPtr,
    P2VAR( uint16, AUTOMATIC, AUTOMATIC ) BufDtrWriteIndexPtr,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) BufferPtr
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
/* Function Name | Dem_DTR_ReadDTCBasedTestResult                           */
/* Description   | Read DTC Based Test Result                               */
/* Preconditions | none                                                     */
/* Parameters    | [in]     EventCtrlIndex                                  */
/*               | [in]     DTCValue                                        */
/*               | [in]     GetExtendDataMode                               */
/*               | [out]    BufferPtr                                       */
/*               | [in/out] BufSizePtr                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |       DEM_IRT_OK : success                               */
/*               |       DEM_IRT_WRONG_RECORDNUMBER : wrong recordnumber    */
/*               |       DEM_IRT_WRONG_BUFFERSIZE : buffer size overflow    */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTR_ReadDTCBasedTestResult
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,                /* MISRA DEVIATION */
    VAR( Dem_u08_GetExtendDataModeType, AUTOMATIC ) GetExtendDataMode,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) BufferPtr,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr
)
{
    VAR( uint16, AUTOMATIC ) bufDtrWriteIndex;
    VAR( uint16, AUTOMATIC ) bufSizeIn;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetDTR;
    VAR( uint8, AUTOMATIC ) testResultNum;
    VAR( boolean, AUTOMATIC ) execClearDTC;
    VAR( Dem_u32_DTCGroupType, AUTOMATIC ) getDTCGroup;
    VAR( Dem_DTCOriginType, AUTOMATIC ) getDTCOrigin;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndex;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexCnt;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) eventCtrlIndexNum;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) eventStrgIndex;

    retVal = DEM_IRT_WRONG_RECORDNUMBER;
    bufSizeIn = (*BufSizePtr);

    /*  get current DTCclear information    */
    execClearDTC = Dem_Control_CheckExecClearDTCProcess();
    Dem_Control_GetClearType( &getDTCGroup, &getDTCOrigin );

    /*  initialize index and DTR number     */
    bufDtrWriteIndex = DEM_DTR_DATABUF_DTR;
    testResultNum = (uint8)0U;

    if ( GetExtendDataMode == DEM_EDR_GETEDRMODE_DTC )
    {
        /*------------------------------*/
        /*  DTC group.                  */
        /*------------------------------*/
        /*  primary event only.         */
        eventStrgIndex      =   Dem_CmbEvt_CnvEventCtrlIndex_ToEventStrgIndex( EventCtrlIndex );                    /* [GUD:RET:IF_GUARDED: EventCtrlIndex ]eventStrgIndex */

        /*  get target event    */
        eventCtrlIndexNum   =   Dem_CmbEvt_NumOfEventCtrlIndex_InEvtStrgGrp( eventStrgIndex );          /*  get EventCtrlIndex of EventStorageGroup max number  */
        eventCtrlIndex      =   EventCtrlIndex;    /*  get delegate eventCtrlIndex                         */

        for ( eventCtrlIndexCnt = ( Dem_u16_EventCtrlIndexType )0U; eventCtrlIndexCnt < eventCtrlIndexNum; eventCtrlIndexCnt++ )
        {
            /*  get DTR data.           */
            retGetDTR  =   Dem_DTR_GetCurrentDTCBasedTestResult( eventCtrlIndex, execClearDTC, getDTCOrigin, bufSizeIn, &testResultNum, &bufDtrWriteIndex, BufferPtr );

            if ( retGetDTR == DEM_IRT_OK )
            {
                retVal  =   DEM_IRT_OK;
            }
            else if ( retGetDTR == DEM_IRT_WRONG_BUFFERSIZE )
            {
                retVal  =   DEM_IRT_WRONG_BUFFERSIZE;
                break;
            }
            else
            {
                /*  DEM_IRT_NG : no process.    */
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
        /*  get DTR data.           */
        retVal  =   Dem_DTR_GetCurrentDTCBasedTestResult( EventCtrlIndex, execClearDTC, getDTCOrigin, bufSizeIn, &testResultNum, &bufDtrWriteIndex, BufferPtr );
    }

    if( retVal == DEM_IRT_OK )
    {
        /* Test Result Num */
        BufferPtr[ DEM_DTR_DATABUF_TESTRESULT ] = testResultNum;

        /* BufferPtr size */
        (*BufSizePtr) = bufDtrWriteIndex;
    }

    return retVal;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
/****************************************************************************/
/* Function Name | Dem_DTR_GetCurrentDTCBasedTestResult                     */
/* Description   | Read DTC Based DTR                                       */
/* Preconditions | none                                                     */
/* Parameters    | [in]     EventCtrlIndex                                  */
/*               | [in]     ExecClearDTC                                    */
/*               | [in]     DTCOriginInClear                                */
/*               | [in]     BufSizeIn                                       */
/*               | [in/out]    TestResultNumPtr                             */
/*               | [in/out]    BufDtrWriteIndexPtr                          */
/*               | [out]    BufferPtr                                       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |       DEM_IRT_OK : success                               */
/*               |       DEM_IRT_WRONG_RECORDNUMBER : wrong recordnumber    */
/*               |       DEM_IRT_WRONG_BUFFERSIZE : buffer size overflow    */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTR_GetCurrentDTCBasedTestResult
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( boolean, AUTOMATIC ) ExecClearDTC,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOriginInClear,
    VAR( uint16, AUTOMATIC ) BufSizeIn,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) TestResultNumPtr,
    P2VAR( uint16, AUTOMATIC, AUTOMATIC ) BufDtrWriteIndexPtr,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) BufferPtr
)
{
    VAR( Dem_DtrDataType, AUTOMATIC ) dtrData;
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) dtrId;
    VAR( Dem_u16_DtrRefObdEventCtrlIndexType, AUTOMATIC ) cnt;
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) dtrObdEventNum;
    VAR( Dem_u16_DtrRefObdEventCtrlIndexType, AUTOMATIC ) dtrRefObdEventOffsetTop;
    VAR( Dem_u16_DtrRefObdEventCtrlIndexType, AUTOMATIC ) dtrRefObdEventNum;
    VAR( Dem_u16_DtrRefObdEventCtrlIndexType, AUTOMATIC ) dtrIndex;
    VAR( uint16, AUTOMATIC ) bufDtrWriteIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) resultGetData;
    VAR( uint8, AUTOMATIC ) testResultNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    dtrObdEventNum = Dem_DtrObdEventNum;

    retVal = DEM_IRT_WRONG_RECORDNUMBER;

    if( EventCtrlIndex < dtrObdEventNum )                   /* [GUD:if]EventCtrlIndex */
    {
        bufDtrWriteIndex        =   *BufDtrWriteIndexPtr;
        testResultNum           =   *TestResultNumPtr;

        dtrRefObdEventOffsetTop = Dem_DtrOutputEdrTable[ EventCtrlIndex ].DtrRefObdEventOffsetTop;                                      /* [GUD]EventCtrlIndex *//* [GUD:CFG:IF_GUARDED: EventCtrlIndex ]dtrRefObdEventOffsetTop */
        dtrRefObdEventNum       = (Dem_u16_DtrRefObdEventCtrlIndexType)Dem_DtrOutputEdrTable[ EventCtrlIndex ].DtrRefObdEventNum;       /* [GUD]EventCtrlIndex *//* [GUD:CFG:IF_GUARDED: EventCtrlIndex ]dtrRefObdEventNum       */

        for( cnt = (Dem_u16_DtrRefObdEventCtrlIndexType)0U; cnt < dtrRefObdEventNum; cnt++ )        /* [GUD:for]cnt  */
        {
            dtrIndex = dtrRefObdEventOffsetTop + cnt;                                               /* [GUD:CFG:IF_GUARDED:dtrRefObdEventOffsetTop/dtrRefObdEventNum]dtrIndex */
            dtrId = Dem_DtrRefObdEventTable[ dtrIndex ];                                            /* [GUD]dtrIndex */

            dtrData.TIDValue   = (uint8)0U;
            dtrData.UaSID      = (uint8)0U;
            dtrData.CtrlVal    = DEM_DTR_CTL_NORMAL;
            resultGetData = Dem_DTRMng_GetDTRRecordData( dtrId, &dtrData );                         /* [GUD:RET:DEM_IRT_OK] dtrId */
            if( resultGetData == DEM_IRT_OK )
            {
                if ( ( ExecClearDTC == (boolean)TRUE ) && ( DTCOriginInClear == DEM_DTC_ORIGIN_PRIMARY_MEMORY ) )
                {
                    dtrData.TestResult = (Dem_u16_DTRValueStoreType)0U;
                    dtrData.LowerLimit = (Dem_u16_DTRValueStoreType)0U;
                    dtrData.UpperLimit = (Dem_u16_DTRValueStoreType)0U;
                }

                if( (uint32)( (uint32)bufDtrWriteIndex + (uint32)DEM_DTR_DATA_SIZE_PER_DTR ) <= (uint32)BufSizeIn )     /*  no wrap around      */
                {
                    /* Unit And Scaling ID */
                    BufferPtr[ bufDtrWriteIndex ] = (uint8)0U;
                    BufferPtr[ bufDtrWriteIndex + DEM_DTR_BUF_OFFSET_UAS_ID_1 ] = Dem_DtrTable[ dtrId ].DemDtrUasid;    /* [GUD] dtrId */

                    /* Test Value */
                    BufferPtr[ bufDtrWriteIndex + DEM_DTR_BUF_OFFSET_TEST_VAL_0 ] = (uint8)( dtrData.TestResult >> DEM_DTR_BITSHIFT_8 );
                    BufferPtr[ bufDtrWriteIndex + DEM_DTR_BUF_OFFSET_TEST_VAL_1 ] = (uint8)dtrData.TestResult;

                    /* Min. Test Limit */
                    BufferPtr[ bufDtrWriteIndex + DEM_DTR_BUF_OFFSET_LIMIT_MIN_0 ] = (uint8)( dtrData.LowerLimit >> DEM_DTR_BITSHIFT_8 );
                    BufferPtr[ bufDtrWriteIndex + DEM_DTR_BUF_OFFSET_LIMIT_MIN_1 ] = (uint8)dtrData.LowerLimit;

                    /* Max. Test Limit */
                    BufferPtr[ bufDtrWriteIndex + DEM_DTR_BUF_OFFSET_LIMIT_MAX_0 ] = (uint8)( dtrData.UpperLimit >> DEM_DTR_BITSHIFT_8 );
                    BufferPtr[ bufDtrWriteIndex + DEM_DTR_BUF_OFFSET_LIMIT_MAX_1 ] = (uint8)dtrData.UpperLimit;

                    testResultNum = testResultNum + (uint8)1U;
                    bufDtrWriteIndex = (uint16)( bufDtrWriteIndex + DEM_DTR_DATA_SIZE_PER_DTR );
                    retVal = DEM_IRT_OK;
                }
                else
                {
                    /* Buffer size overflow */
                    retVal = DEM_IRT_WRONG_BUFFERSIZE;
                    break;
                }
            }
        }
        *TestResultNumPtr       =   testResultNum;
        *BufDtrWriteIndexPtr    =   bufDtrWriteIndex;
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_DTR_EDR_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

