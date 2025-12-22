/* Dem_Control_DTR_c(v5-9-0)                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/Control_DTR/CODE                                      */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnLib_Control_AsyncReq.h"
#include "Dem_Control_local.h"

#if ( DEM_DTR_SUPPORT == STD_ON )

#include "../../../cfg/Dem_Dtr_Cfg.h"
#include "../../../inc/Dem_Pm_DTR.h"

#include "../../../inc/Dem_CmnLib_AsyncReqTable.h"
#include "../../../inc/Dem_Pm_Control_DTR.h"
#include "../../../usr/Dem_SavedZone_Callout.h"


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_CTLDTR_DATABUF_TESTRES_0  ((uint8) 0U)
#define DEM_CTLDTR_DATABUF_TESTRES_1  ((uint8) 1U)
#define DEM_CTLDTR_DATABUF_TESTRES_2  ((uint8) 2U)
#define DEM_CTLDTR_DATABUF_TESTRES_3  ((uint8) 3U)
#define DEM_CTLDTR_DATABUF_LOWERLIM_0 ((uint8) 4U)
#define DEM_CTLDTR_DATABUF_LOWERLIM_1 ((uint8) 5U)
#define DEM_CTLDTR_DATABUF_LOWERLIM_2 ((uint8) 6U)
#define DEM_CTLDTR_DATABUF_LOWERLIM_3 ((uint8) 7U)
#define DEM_CTLDTR_DATABUF_UPPERLIM_0 ((uint8) 8U)
#define DEM_CTLDTR_DATABUF_UPPERLIM_1 ((uint8) 9U)
#define DEM_CTLDTR_DATABUF_UPPERLIM_2 ((uint8)10U)
#define DEM_CTLDTR_DATABUF_UPPERLIM_3 ((uint8)11U)
#define DEM_CTLDTR_DATABUF_CTRLVAL    ((uint8)12U)

#define DEM_CTLDTR_BITSHIFT_8  ((Dem_u32_DTRValueRawType) 8U)
#define DEM_CTLDTR_BITSHIFT_16 ((Dem_u32_DTRValueRawType)16U)
#define DEM_CTLDTR_BITSHIFT_24 ((Dem_u32_DTRValueRawType)24U)

#define DEM_DTR_CTL_MAX_NUM (DEM_DTR_CTL_RESET_FOR_FAILED_TID)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

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
/* Function Name | Dem_Control_SetDTR                                       */
/* Description   | Reports a DTR result with lower and upper limit.         */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTRId      : DTR identifier.                        */
/*               | [in] TestResult : Test result of DTR.                    */
/*               | [in] LowerLimit : Lower limit of DTR.                    */
/*               | [in] UpperLimit : Upper limit of DTR.                    */
/*               | [in] Ctrlval    : Control value of the DTR to support    */
/*               |                   its interpretation Dem-internally.     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK  : success                             */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_SetDTR
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) DtrId,
    VAR( Dem_s32_DTRValueRawType, AUTOMATIC) TestResult,
    VAR( Dem_s32_DTRValueRawType, AUTOMATIC) LowerLimit,
    VAR( Dem_s32_DTRValueRawType, AUTOMATIC) UpperLimit,
    VAR( Dem_DTRControlType, AUTOMATIC ) Ctrlval
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) dtrNum;
    VAR( uint8, AUTOMATIC ) data[DEM_ASYNCDATAQUE_DTR_ITEMSIZE];

    retVal = DEM_IRT_NG;
    dtrNum = Dem_DtrNum;

    /* Judges request condition */
    checkStatus = Dem_AsyncReq_JudgeReqCondition(DEM_ASYNCREQ_DTR, DtrId, DEM_ASYNCREQ_PARAM_STATUS_INVALID );
    if ( checkStatus == DEM_IRT_OK )
    {
        /* Judges DTR parameters */
        if ( (DtrId < dtrNum) && (Ctrlval <= DEM_DTR_CTL_MAX_NUM) )
        {
            /* Converts DTR result for data buffer */
            data[DEM_CTLDTR_DATABUF_TESTRES_0]  = (uint8)( TestResult );/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_TESTRES_0 */
            data[DEM_CTLDTR_DATABUF_TESTRES_1]  = (uint8)( ((Dem_u32_DTRValueRawType)TestResult) >> DEM_CTLDTR_BITSHIFT_8  );/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_TESTRES_1 */
            data[DEM_CTLDTR_DATABUF_TESTRES_2]  = (uint8)( ((Dem_u32_DTRValueRawType)TestResult) >> DEM_CTLDTR_BITSHIFT_16 );/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_TESTRES_2 */
            data[DEM_CTLDTR_DATABUF_TESTRES_3]  = (uint8)( ((Dem_u32_DTRValueRawType)TestResult) >> DEM_CTLDTR_BITSHIFT_24 );/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_TESTRES_3 */
            data[DEM_CTLDTR_DATABUF_LOWERLIM_0] = (uint8)( LowerLimit );/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_LOWERLIM_0 */
            data[DEM_CTLDTR_DATABUF_LOWERLIM_1] = (uint8)( ((Dem_u32_DTRValueRawType)LowerLimit) >> DEM_CTLDTR_BITSHIFT_8  );/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_LOWERLIM_1 */
            data[DEM_CTLDTR_DATABUF_LOWERLIM_2] = (uint8)( ((Dem_u32_DTRValueRawType)LowerLimit) >> DEM_CTLDTR_BITSHIFT_16 );/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_LOWERLIM_2 */
            data[DEM_CTLDTR_DATABUF_LOWERLIM_3] = (uint8)( ((Dem_u32_DTRValueRawType)LowerLimit) >> DEM_CTLDTR_BITSHIFT_24 );/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_LOWERLIM_3 */
            data[DEM_CTLDTR_DATABUF_UPPERLIM_0] = (uint8)( UpperLimit );/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_UPPERLIM_0 */
            data[DEM_CTLDTR_DATABUF_UPPERLIM_1] = (uint8)( ((Dem_u32_DTRValueRawType)UpperLimit) >> DEM_CTLDTR_BITSHIFT_8  );/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_UPPERLIM_1 */
            data[DEM_CTLDTR_DATABUF_UPPERLIM_2] = (uint8)( ((Dem_u32_DTRValueRawType)UpperLimit) >> DEM_CTLDTR_BITSHIFT_16 );/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_UPPERLIM_2 */
            data[DEM_CTLDTR_DATABUF_UPPERLIM_3] = (uint8)( ((Dem_u32_DTRValueRawType)UpperLimit) >> DEM_CTLDTR_BITSHIFT_24 );/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_UPPERLIM_3 */
            data[DEM_CTLDTR_DATABUF_CTRLVAL]    = (uint8)( Ctrlval );/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_CTRLVAL */

            /* Queues the DTR report */
            retVal = Dem_AsyncReq_EnqueueWithData( DEM_ASYNCREQ_DTR, (Dem_u16_AsyncReqItemAType)DtrId, &data[0] );  /* [GUD:FixVal]DEM_ASYNCREQ_EVENT_WITH_MONITORDATA *//* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / 0 */
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_SetDTRProcess                                */
/* Description   | Asynchronous processing function of SetDTR.              */
/* Preconditions | none                                                     */
/* Parameters    | [in] Index       : DTR identifier.                       */
/*               | [in] Status      :                                       */
/*               | [in] DataBuffPtr : DTR data.                             */
/* Return Value  | Dem_u08_AsyncExecReturnType                              */
/*               |       : See the description of the return value of       */
/*               |         "DemAsyncReqFncPTR" in Dem_CmnLib_Control_AsyncReq.h.   */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_AsyncExecReturnType, DEM_CODE ) Dem_Control_SetDTRProcess
(
    VAR( Dem_u16_AsyncReqItemAType, AUTOMATIC ) Index,
    VAR( Dem_u08_AsyncReqItemBType, AUTOMATIC ) Status,                     /* MISRA DEVIATION */
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) DataBuffPtr
)
{
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) dtrId;
    VAR( Dem_u08_AsyncExecReturnType, AUTOMATIC ) retVal;
    VAR( Dem_s32_DTRValueRawType, AUTOMATIC ) testResult;
    VAR( Dem_s32_DTRValueRawType, AUTOMATIC ) lowerLimit;
    VAR( Dem_s32_DTRValueRawType, AUTOMATIC ) upperLimit;
    VAR( Dem_u32_DTRValueRawType, AUTOMATIC ) tmpResult;
    VAR( Dem_u32_DTRValueRawType, AUTOMATIC ) tmpLowerLimit;
    VAR( Dem_u32_DTRValueRawType, AUTOMATIC ) tmpUpperLimit;
    VAR( Dem_DTRControlType, AUTOMATIC ) ctrlval;
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) dtrNum;

    /* Set return value. */
    /* Fault record is not updated, No need re-generate orderlist, Continue asynchronous processing. */
    retVal = ( DEM_ASYNCRET_NOUPD_FR | DEM_ASYNCRET_NONEED_REGEN_ODR | DEM_ASYNCRET_CONTINUE_ASYNC_PROC );

    dtrNum = Dem_DtrNum;
    dtrId  = (Dem_u16_DTRIndexType)Index;

    if ( dtrId < dtrNum )
    {
        /* Converts data buffer for DTR result */
        tmpResult = (Dem_u32_DTRValueRawType)(  ((Dem_u32_DTRValueRawType)DataBuffPtr[DEM_CTLDTR_DATABUF_TESTRES_0])                  |/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_TESTRES_0 */
                              ( ((Dem_u32_DTRValueRawType)DataBuffPtr[DEM_CTLDTR_DATABUF_TESTRES_1]) << DEM_CTLDTR_BITSHIFT_8  ) |/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_TESTRES_1 */
                              ( ((Dem_u32_DTRValueRawType)DataBuffPtr[DEM_CTLDTR_DATABUF_TESTRES_2]) << DEM_CTLDTR_BITSHIFT_16 ) |/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_TESTRES_2 */
                              ( ((Dem_u32_DTRValueRawType)DataBuffPtr[DEM_CTLDTR_DATABUF_TESTRES_3]) << DEM_CTLDTR_BITSHIFT_24 )  );/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_TESTRES_3 */
        testResult = (Dem_s32_DTRValueRawType)tmpResult;

        tmpLowerLimit = (Dem_u32_DTRValueRawType)(  ((Dem_u32_DTRValueRawType)DataBuffPtr[DEM_CTLDTR_DATABUF_LOWERLIM_0])                  |/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_LOWERLIM_0 */
                              ( ((Dem_u32_DTRValueRawType)DataBuffPtr[DEM_CTLDTR_DATABUF_LOWERLIM_1]) << DEM_CTLDTR_BITSHIFT_8  ) |/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_LOWERLIM_1 */
                              ( ((Dem_u32_DTRValueRawType)DataBuffPtr[DEM_CTLDTR_DATABUF_LOWERLIM_2]) << DEM_CTLDTR_BITSHIFT_16 ) |/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_LOWERLIM_2 */
                              ( ((Dem_u32_DTRValueRawType)DataBuffPtr[DEM_CTLDTR_DATABUF_LOWERLIM_3]) << DEM_CTLDTR_BITSHIFT_24 )  );/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_LOWERLIM_3 */
        lowerLimit = (Dem_s32_DTRValueRawType)tmpLowerLimit;

        tmpUpperLimit = (Dem_u32_DTRValueRawType)(  ((Dem_u32_DTRValueRawType)DataBuffPtr[DEM_CTLDTR_DATABUF_UPPERLIM_0])                  |/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_UPPERLIM_0 */
                              ( ((Dem_u32_DTRValueRawType)DataBuffPtr[DEM_CTLDTR_DATABUF_UPPERLIM_1]) << DEM_CTLDTR_BITSHIFT_8  ) |/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_UPPERLIM_1 */
                              ( ((Dem_u32_DTRValueRawType)DataBuffPtr[DEM_CTLDTR_DATABUF_UPPERLIM_2]) << DEM_CTLDTR_BITSHIFT_16 ) |/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_UPPERLIM_2 */
                              ( ((Dem_u32_DTRValueRawType)DataBuffPtr[DEM_CTLDTR_DATABUF_UPPERLIM_3]) << DEM_CTLDTR_BITSHIFT_24 )  );/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_UPPERLIM_3 */
        upperLimit = (Dem_s32_DTRValueRawType)tmpUpperLimit;

        ctrlval    = ((Dem_DTRControlType)DataBuffPtr[DEM_CTLDTR_DATABUF_CTRLVAL]);/* [ARYCHK] DEM_ASYNCDATAQUE_DTR_ITEMSIZE / 1 / DEM_CTLDTR_DATABUF_CTRLVAL */

        /* Sets DTR result in DtrRecord */
        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - start.   */
        Dem_NotifySavedZoneUpdate_Enter();      /*  notify start :  savedzone area will be update.  */
        /*--------------------------------------*/

        Dem_DTR_SetDTR( dtrId, testResult, lowerLimit, upperLimit, ctrlval);

        /*--------------------------------------*/
        /*  notify SAVED_ZONE update - end.     */
        Dem_NotifySavedZoneUpdate_Exit();       /*  notify end :  savedzone area will be update.    */
        /*--------------------------------------*/
    }

    return retVal;
}

#if ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Control_GetDTR                                       */
/* Description   | Gets a DTR result with lower and upper limit.            */
/* Preconditions | none                                                     */
/* Parameters    | [in]  DTRId       : DTR identifier.                      */
/*               | [out] DtrDataPtr  : DTR data pointer.                    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK  : success                             */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetDTR
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) DTRId,
    P2VAR( Dem_DtrDataType, AUTOMATIC, AUTOMATIC ) DtrDataPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) checkStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;

    /* Check if the status is initialization complete */
    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /* Gets the DTR report */
        retVal = Dem_DTR_GetDTR(DTRId, DtrDataPtr);
    }

    return retVal;
}
#endif  /* ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_Control_GetDTRConvertInfo                            */
/* Description   | Gets the DTR convert information.                        */
/* Preconditions | none                                                     */
/* Parameters    | [in]  DTRId           : DTR identifier.                  */
/*               | [out] DtrMidPtr       : MonitorID of DTR.                */
/*               | [out] DtrTidPtr       : TestID of DTR.                   */
/*               | [out] DtrUasidPtr     : Unit and ScalingID of DTR.       */
/*               | [out] CompuN0DivD0Ptr : The value of CompuNumerator0 divided by CompuDenominator0. */
/*               | [out] CompuN1DivD0Ptr : The value of CompuNumerator1 divided by CompuDenominator0. */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-9-0      | new created. based on Dem_DTR_GetDTR.                    */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetDTRConvertInfo
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) DTRId,
    P2VAR( Dem_u08_DTRObdMidType, AUTOMATIC, AUTOMATIC ) DtrMidPtr,
    P2VAR( Dem_u08_DTRTidIndexType, AUTOMATIC, AUTOMATIC ) DtrTidPtr,
    P2VAR( Dem_u08_DTRUasidType, AUTOMATIC, AUTOMATIC ) DtrUasidPtr,
    P2VAR( Dem_s32_DTRValueRawType, AUTOMATIC, AUTOMATIC ) CompuN0DivD0Ptr,
    P2VAR( Dem_s32_DTRValueRawType, AUTOMATIC, AUTOMATIC ) CompuN1DivD0Ptr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /* Gets the DTR convert info */
    retVal = Dem_DTR_GetDTRConvertInfo( DTRId, DtrMidPtr, DtrTidPtr, DtrUasidPtr, CompuN0DivD0Ptr, CompuN1DivD0Ptr );

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_GetAvailableOBDMIDs                          */
/* Description   | Gets value of OBDMID.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in]  Obdmid       : OBDMID.                             */
/*               | [out] Obdmidvalue  : value of OBDMID.                    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK  : success                             */
/*               |        DEM_IRT_NG  : failed                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetAvailableOBDMIDs
(
    VAR( Dem_u08_DTRObdMidType, AUTOMATIC ) Obdmid,
    P2VAR( Dem_u32_DTRObdMidBmpType, AUTOMATIC, AUTOMATIC ) ObdmidvaluePtr
)
{
    VAR(Dem_u08_InternalReturnType, AUTOMATIC) checkStatus;
    VAR(Dem_u08_InternalReturnType, AUTOMATIC) retVal;

    retVal = DEM_IRT_NG;

    /* Check if the status is initialization complete */
    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /* Gets value of OBDMID */
        retVal  =   Dem_DTR_GetAvailableOBDMIDs(Obdmid, ObdmidvaluePtr);
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_GetNumTIDsOfOBDMID                           */
/* Description   | Gets number of TID.                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in]  Obdmid          : Monitor ID of DTR.               */
/*               | [out] NumberOfTIDsPtr : number of TID.                   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK  : success                             */
/*               |        DEM_IRT_NG  : failed                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetNumTIDsOfOBDMID
(
    VAR( Dem_u08_DTRObdMidType, AUTOMATIC ) Obdmid,
    P2VAR( Dem_u08_DTRTidIndexType, AUTOMATIC, AUTOMATIC) NumberOfTIDsPtr
)
{
    VAR(Dem_u08_InternalReturnType, AUTOMATIC) checkStatus;
    VAR(Dem_u08_InternalReturnType, AUTOMATIC) retVal;

    retVal = DEM_IRT_NG;

    /* Check if the status is initialization complete */
    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /* Gets value of OBDMID */
        retVal = Dem_DTR_GetNumTIDsOfOBDMID( Obdmid, NumberOfTIDsPtr);
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_Control_GetDTRData                                   */
/* Description   | Gets a DTR result.                                       */
/* Preconditions | none                                                     */
/* Parameters    | [in]  Obdmid          : Monitor ID of DTR.               */
/*               | [in]   TidIndex    : Test ID Index of DTR.               */
/*               | [out]  DtrDataPtr  : DTR data pointer.                   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK  : success                             */
/*               |        DEM_IRT_NG  : failed                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Control_GetDTRData
(
    VAR( Dem_u08_DTRObdMidType, AUTOMATIC ) Obdmid,
    VAR( Dem_u08_DTRTidIndexType, AUTOMATIC ) TidIndex,
    P2VAR( Dem_DtrDataType, AUTOMATIC, AUTOMATIC ) DtrDataPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC) checkStatus;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC) retVal;

    retVal = DEM_IRT_NG;

    /* Check if the status is initialization complete */
    checkStatus = Dem_Control_ChkAfterCompleteInit();
    if( checkStatus == DEM_IRT_OK )
    {
        /* Gets a DTR result */
        retVal = Dem_DTR_GetDTRData( Obdmid, TidIndex, DtrDataPtr );
    }

    return retVal;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_DTR_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2021-12-24                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
