/* Dem_DTR_c(v5-10-0)                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DTR/CODE                                              */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"

#if ( DEM_DTR_SUPPORT == STD_ON )

#include "../../../inc/Dem_Pm_DTR.h"
#include "../../../inc/Dem_Rc_DTRMng.h"
#include "../../../inc/Dem_CmnLib_Control.h"
#include "Dem_DTR_Convert.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_DTR_CAL_MID_1    ((Dem_u08_DTRObdMidType)1U)
#define DEM_DTR_CAL_POS_1    ((Dem_u16_DTRIndexType)1U)

#define DEM_DTR_BIT31 ((Dem_u08_DTRObdMidBmpBitCountType)31U)
#define DEM_DTR_BIT32 ((Dem_u08_DTRObdMidBmpBitCountType)32U)

#define DEM_DTR_INVISIBLE ((Dem_u32_DTRObdMidBmpType)0U)
#define DEM_DTR_VISIBLE   ((Dem_u32_DTRObdMidBmpType)1U)

/* support OBDMID : 0x00,0x20,0x40,0x60,0x80,0xA0,0xC0,0xE0   */
/*    available support OBDMID : ObdMid & 0x1F == 0           */
#define DEM_DTR_GETMID_PARAMMASK  ((Dem_u32_DTRObdMidBmpType)0x1FU)


#define DEM_DTR_GETMID_BITOFFSET  ((Dem_u08_DTRObdMidBmpBitCountType)5U)
#define DEM_DTR_GETMID_MASK       ((Dem_u08_DTRObdMidType)0x1FU)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

static FUNC(void, DEM_CODE) Dem_DTR_SetDTR_Normal
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) DTRId,
    VAR( Dem_s32_DTRValueRawType, AUTOMATIC) TestResult,
    VAR( Dem_s32_DTRValueRawType, AUTOMATIC) LowerLimit,
    VAR( Dem_s32_DTRValueRawType, AUTOMATIC) UpperLimit,
    VAR( Dem_DTRControlType, AUTOMATIC ) Ctrlval
);

static FUNC(void, DEM_CODE) Dem_DTR_SetDTR_CtrlVal
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) DTRId,
    VAR( Dem_DTRControlType, AUTOMATIC ) Ctrlval
);

static FUNC(void, DEM_CODE) Dem_DTR_SetDTR_ForFailedTid
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) DTRId
);

static FUNC(void, DEM_CODE) Dem_DTR_SetObdmidInfo
(
    VAR( Dem_u08_DTRMidIndexType, AUTOMATIC ) MidIndex
);

static FUNC( void, DEM_CODE) Dem_DTR_GetObdmidInfo
(
    VAR( Dem_u08_DTRObdMidType, AUTOMATIC ) Obdmid,
    P2VAR( Dem_u32_DTRObdMidBmpType, AUTOMATIC, AUTOMATIC ) ObdmidvaluePtr
);
static FUNC( void, DEM_CODE ) Dem_DTR_ClearDTRDataArea
(
    VAR( Dem_DTRControlType, AUTOMATIC ) Ctrlval,
    P2VAR( Dem_DtrDataType, AUTOMATIC, AUTOMATIC ) DtrDataPtr
);
#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_u32_DTRObdMidBmpType, DEM_VAR_NO_INIT ) Dem_DtrObdMidVisibleBitmap[DEM_DTR_SUPPORT_OBDMID_NUM];

static VAR( Dem_u08_DTRMidIndexType, DEM_VAR_NO_INIT ) Dem_DtrGetDataMidIndex;
static VAR( Dem_u08_DTRTidIndexType, DEM_VAR_NO_INIT ) Dem_DtrGetDataTidNum;
static VAR( Dem_u16_DTRIndexType, DEM_VAR_NO_INIT ) Dem_DtrGetDataRestartPos;

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>


/****************************************************************************/
/* Functions                                                                */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>
/****************************************************************************/
/* Function Name | Dem_DTR_Init_AfterRecordCheckComplete                    */
/* Description   | Inits Dem_Dtr.                                           */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | This function is called after Record check               */
/*               | because this function call DtrMng function.              */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-8-0      | branch changed.                                          */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_DTR_Init_AfterRecordCheckComplete
(void)
{
    VAR(Dem_u08_DTRSupportObdMidIndexType, AUTOMATIC) tblNum;
    VAR(Dem_u08_DTRObdMidBmpBitCountType , AUTOMATIC) bitNum;
    VAR(Dem_u32_DTRObdMidBmpType, AUTOMATIC) isSupport;
    VAR(Dem_u08_DTRObdMidType , AUTOMATIC) mid;
    VAR(Dem_u08_DTRMidIndexType , AUTOMATIC) midIndexNum;
    VAR(Dem_u08_DTRMidIndexType, AUTOMATIC) midNum;
    VAR(Dem_u16_DTRIndexType, AUTOMATIC) offsetTop;
    VAR(Dem_u08_DTRTidIndexType, AUTOMATIC)  tidNumMax;
    VAR(Dem_u08_DTRTidIndexType , AUTOMATIC) numTid;
    VAR(Dem_u08_DTRSupportObdMidIndexType , AUTOMATIC) lastvisibleTblNum;

    midNum = Dem_DtrMidNum;
    lastvisibleTblNum = ((Dem_u08_DTRSupportObdMidIndexType)0U);

    Dem_DtrGetDataMidIndex   = DEM_DTRMIDINDEX_INVALID;
    Dem_DtrGetDataTidNum     = DEM_DTRTIDINDEX_INVALID;
    Dem_DtrGetDataRestartPos = DEM_DTRINDEX_INVALID;


    /* Reflects invisible on OBDMID bitmaps */
    for ( tblNum = ((Dem_u08_DTRSupportObdMidIndexType)0U); tblNum < DEM_DTR_SUPPORT_OBDMID_NUM; tblNum++ )     /* [GUD:for]tblNum */
    {
        Dem_DtrObdMidVisibleBitmap[tblNum] = ((Dem_u32_DTRObdMidBmpType)0U);                                    /* [GUD]tblNum */

        for ( bitNum = ((Dem_u08_DTRObdMidBmpBitCountType)0U); bitNum < DEM_DTR_BIT31; bitNum++ )
        {
            /* Gets support state */
            isSupport = Dem_DtrObdMidSupportBitmapTable[tblNum].DemDtrSupportedObdMid & ( DEM_DTR_VISIBLE << ((Dem_u08_DTRObdMidBmpBitCountType)(DEM_DTR_BIT31 - bitNum)) );    /* [GUD]tblNum */

            /* If this MID of config's bitmap is invisible(0), this MID dosen't have TIDs */
            if ( isSupport != DEM_DTR_INVISIBLE )
            {
                mid = (DEM_DTR_BIT32 * tblNum) + bitNum + DEM_DTR_CAL_MID_1;

                /* Gets parameters for getting number of visible TID */
                for ( midIndexNum = ((Dem_u08_DTRMidIndexType)0U); midIndexNum < midNum; midIndexNum++ )    /* [GUD:for]midIndexNum */
                {
                    if ( Dem_DtrMidTable[midIndexNum].DemDtrMid == mid )                                    /* [GUD]midIndexNum */
                    {
                        offsetTop = Dem_DtrMidTable[midIndexNum].DemDtrIdOffsetTop;                         /* [GUD]midIndexNum */
                        tidNumMax = Dem_DtrMidTable[midIndexNum].DemDtrTidNum;                              /* [GUD]midIndexNum */

                        /* Gets number of visible TID */
                        numTid = Dem_DTRMng_GetNumTIDsOfOBDMID(offsetTop, tidNumMax);
                        if ( numTid > ((Dem_u08_DTRTidIndexType)0U) )
                        {
                            /* Sets visible state */
                            Dem_DtrObdMidVisibleBitmap[tblNum] = Dem_DtrObdMidVisibleBitmap[tblNum] | ( DEM_DTR_VISIBLE << ((uint8)(DEM_DTR_BIT31 - bitNum)) );     /* [GUD]tblNum */
                        }

                        break;
                    }
                }
            }
        }

        if ( Dem_DtrObdMidVisibleBitmap[tblNum] != ((Dem_u32_DTRObdMidBmpType)0U) )             /* [GUD]tblNum */
        {
            lastvisibleTblNum = tblNum;
        }
    }

    /* Sets last bits */
    for ( tblNum = ((Dem_u08_DTRSupportObdMidIndexType)0U); tblNum < lastvisibleTblNum; tblNum++ )          /* [GUD:for]tblNum */
    {
        /* Next table has visible state, so last bit is set */
        Dem_DtrObdMidVisibleBitmap[tblNum] = Dem_DtrObdMidVisibleBitmap[tblNum] | DEM_DTR_VISIBLE;          /* [GUD]tblNum */
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_DTR_SetDTR                                           */
/* Description   | Sets DTR result in DtrRecord                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTRId      : DTR identifier.                        */
/*               | [in] TestResult : Test result of DTR.                    */
/*               | [in] LowerLimit : Lower limit of DTR.                    */
/*               | [in] UpperLimit : Upper limit of DTR.                    */
/*               | [in] Ctrlval    : Control value of the DTR to support    */
/*               |                   its interpretation Dem-internally.     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(void, DEM_CODE) Dem_DTR_SetDTR
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC) DTRId,
    VAR( Dem_s32_DTRValueRawType, AUTOMATIC) TestResult,
    VAR( Dem_s32_DTRValueRawType, AUTOMATIC) LowerLimit,
    VAR( Dem_s32_DTRValueRawType, AUTOMATIC) UpperLimit,
    VAR( Dem_DTRControlType, AUTOMATIC) Ctrlval
)
{
    switch ( Ctrlval )
    {
        case DEM_DTR_CTL_NORMAL:
        case DEM_DTR_CTL_NO_MIN:
        case DEM_DTR_CTL_NO_MAX:

            /* Sets DTR result in DtrRecord */
            Dem_DTR_SetDTR_Normal(DTRId, TestResult, LowerLimit, UpperLimit, Ctrlval);

            break;

        case DEM_DTR_CTL_RESET:
        case DEM_DTR_CTL_INVISIBLE:

            /* Sets DTR result (only CtrlVal) in DtrRecord */
            Dem_DTR_SetDTR_CtrlVal(DTRId, Ctrlval);

            break;

        case DEM_DTR_CTL_RESET_FOR_FAILED_TID:

            /* If the DTR result is failed, resets the DTR report */
            Dem_DTR_SetDTR_ForFailedTid(DTRId);

            break;

        default:

            /* No Process */
            break;
    }

    return;
}

#if ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_DTR_GetDTR                                           */
/* Description   | Gets a DTR result with lower and upper limit.            */
/* Preconditions | none                                                     */
/* Parameters    | [in]  DTRId       : DTR identifier.                      */
/*               | [out] DtrDataPtr  : DTR data pointer.                    */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG : failed                               */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTR_GetDTR
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC) DTRId,
    P2VAR( Dem_DtrDataType, AUTOMATIC, AUTOMATIC ) DtrDataPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /* Gets the DTR report */
    retVal = Dem_DTRMng_GetDTR( DTRId, DtrDataPtr );

    return retVal;
}
#endif  /* ( DEM_DTR_RAWDATASTORAGE_SUPPORT == STD_ON ) */

/****************************************************************************/
/* Function Name | Dem_DTR_GetDTRConvertInfo                                */
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
/*   v5-9-0      | new created. based on Dem_DTRMng_GetDTRRecordData.       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTR_GetDTRConvertInfo
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) DTRId,
    P2VAR( Dem_u08_DTRObdMidType, AUTOMATIC, AUTOMATIC ) DtrMidPtr,
    P2VAR( Dem_u08_DTRTidIndexType, AUTOMATIC, AUTOMATIC ) DtrTidPtr,
    P2VAR( Dem_u08_DTRUasidType, AUTOMATIC, AUTOMATIC ) DtrUasidPtr,
    P2VAR( Dem_s32_DTRValueRawType, AUTOMATIC, AUTOMATIC ) CompuN0DivD0Ptr,
    P2VAR( Dem_s32_DTRValueRawType, AUTOMATIC, AUTOMATIC ) CompuN1DivD0Ptr
)
{
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) dtrNum;
    VAR( Dem_u08_DTRMidIndexType, AUTOMATIC ) dtrMidIndex;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_NG;

    dtrNum = Dem_DtrNum;
    if( DTRId < dtrNum )                                                        /* [GUD:if]DTRId */
    {
        *DtrTidPtr          = Dem_DtrTable[DTRId].DemDtrTid;                    /* [GUD]DTRId */
        *DtrUasidPtr        = Dem_DtrTable[DTRId].DemDtrUasid;                  /* [GUD]DTRId */
        *CompuN0DivD0Ptr    = Dem_DtrTable[DTRId].DemDtrCompuN0DivD0;           /* [GUD]DTRId */
        *CompuN1DivD0Ptr    = Dem_DtrTable[DTRId].DemDtrCompuN1DivD0;           /* [GUD]DTRId */

        dtrMidIndex         = Dem_DtrTable[DTRId].DemDtrMidIndex;               /* [GUD]DTRId *//* [GUD:CFG:IF_GUARDED: DTRId ]dtrMidIndex */
        *DtrMidPtr          = Dem_DtrMidTable[dtrMidIndex].DemDtrMid;           /* [GUD]dtrMidIndex */

        retVal = DEM_IRT_OK;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTR_GetAvailableOBDMIDs                              */
/* Description   | Gets value of OBDMID.                                    */
/* Preconditions | none                                                     */
/* Parameters    | [in]  Obdmid       : OBDMID.                             */
/*               | [out] Obdmidvalue  : value of OBDMID.                    */
/* Return Value  | uint8  DEM_IRT_OK  : success                             */
/*               |        DEM_IRT_NG  : failed                              */
/* Notes         | -                                                        */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTR_GetAvailableOBDMIDs
(
    VAR( Dem_u08_DTRObdMidType, AUTOMATIC ) Obdmid,
    P2VAR( Dem_u32_DTRObdMidBmpType, AUTOMATIC, AUTOMATIC ) ObdmidvaluePtr
)
{
    VAR( Dem_u08_InternalReturnType , AUTOMATIC ) retVal;
    retVal  =   DEM_IRT_NG;

    /*  check parameter bit0-bit4 is 0 or not.    */
    if (( Obdmid & DEM_DTR_GETMID_PARAMMASK ) == ( Dem_u32_DTRObdMidBmpType )0U )
    {
        Dem_DTR_GetObdmidInfo( Obdmid, ObdmidvaluePtr );
        retVal  =   DEM_IRT_OK;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTR_GetNumTIDsOfOBDMID                               */
/* Description   | Gets number of TID.                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in]  Mid             : Monitor ID of DTR.               */
/*               | [out] NumberOfTIDsPtr : number of TID.                   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG  : failed                              */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTR_GetNumTIDsOfOBDMID
(
    VAR( Dem_u08_DTRObdMidType, AUTOMATIC ) Obdmid,
    P2VAR( Dem_u08_DTRTidIndexType, AUTOMATIC, AUTOMATIC ) NumberOfTIDsPtr
)
{
    VAR( Dem_u08_InternalReturnType , AUTOMATIC ) retVal;
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) offsetTop;
    VAR( Dem_u08_DTRTidIndexType, AUTOMATIC )  tidNumMax;
    VAR( Dem_u08_DTRMidIndexType, AUTOMATIC ) midIndexNum;
    VAR( Dem_u08_DTRMidIndexType, AUTOMATIC ) midNum;

    retVal      = DEM_IRT_NG;
    midNum      = Dem_DtrMidNum;

    Dem_DtrGetDataMidIndex   = DEM_DTRMIDINDEX_INVALID;
    Dem_DtrGetDataTidNum     = DEM_DTRTIDINDEX_INVALID;
    Dem_DtrGetDataRestartPos = DEM_DTRINDEX_INVALID;

    /* Gets parameters for getting number of visible TID */
    for ( midIndexNum = ((Dem_u08_DTRMidIndexType)0U); midIndexNum < midNum; midIndexNum++ )        /* [GUD:for]midIndexNum */
    {
        if ( Dem_DtrMidTable[midIndexNum].DemDtrMid == Obdmid )                                     /* [GUD]midIndexNum */
        {
            offsetTop = Dem_DtrMidTable[midIndexNum].DemDtrIdOffsetTop;                             /* [GUD]midIndexNum */
            tidNumMax = Dem_DtrMidTable[midIndexNum].DemDtrTidNum;                                  /* [GUD]midIndexNum */

            /* Gets number of visible TID */
            *NumberOfTIDsPtr = Dem_DTRMng_GetNumTIDsOfOBDMID( offsetTop, tidNumMax );

            /* Resets variables for GetDTRData */
            Dem_DtrGetDataMidIndex   = midIndexNum;
            Dem_DtrGetDataTidNum     = ((Dem_u08_DTRTidIndexType)0U);
            Dem_DtrGetDataRestartPos = ((Dem_u16_DTRIndexType)0U);

            retVal = DEM_IRT_OK;

            break;
        }
    }

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_DTR_GetDTRData                                       */
/* Description   | Gets a DTR result.                                       */
/* Preconditions | none                                                     */
/* Parameters    | [in]   Obdmid      : Monitor ID of DTR.                  */
/*               | [in]   TidIndex    : Test ID Index of DTR.               */
/*               | [out]  DtrDataPtr  : DTR data pointer.                   */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success                              */
/*               |        DEM_IRT_NG  : failed                              */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/*   v5-10-0     | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTR_GetDTRData
(
    VAR( Dem_u08_DTRObdMidType, AUTOMATIC ) Obdmid,
    VAR( Dem_u08_DTRTidIndexType, AUTOMATIC ) TidIndex,
    P2VAR( Dem_DtrDataType, AUTOMATIC, AUTOMATIC ) DtrDataPtr
)
{
    VAR( Dem_u16_DTRIndexType , AUTOMATIC ) pos;
    VAR( Dem_u16_DTRIndexType , AUTOMATIC ) tidNum;
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) dtrId;
    VAR( Dem_u08_DTRMidIndexType, AUTOMATIC ) dtrMidNum;
    VAR( Dem_u08_DTRMidIndexType, AUTOMATIC ) midIndex;
    VAR( Dem_u08_InternalReturnType , AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) execClearDTC;
    VAR( Dem_DTCOriginType, AUTOMATIC ) getDTCOrigin;

    retVal = DEM_IRT_NG;
    midIndex = Dem_DtrGetDataMidIndex;
    dtrMidNum = Dem_DtrMidNum;

    if( midIndex < dtrMidNum )                              /* [GUD:if]midIndex */
    {
        /* Checks parameters */
        if ( (Obdmid   == Dem_DtrMidTable[midIndex].DemDtrMid ) && ( TidIndex == Dem_DtrGetDataTidNum ) )           /* [GUD]midIndex */
        {
            tidNum = ((Dem_u16_DTRIndexType)Dem_DtrMidTable[midIndex].DemDtrTidNum);                                /* [GUD]midIndex */

            /* Searchs visible DTR result */
            for ( pos = Dem_DtrGetDataRestartPos; pos < tidNum; pos++ )
            {
                dtrId = Dem_DtrMidTable[midIndex].DemDtrIdOffsetTop + pos;                                          /* [GUD]midIndex */

                /* Gets DTR result in DtrRecord */
                retVal = Dem_DTRMng_GetDTRRecordData( dtrId, DtrDataPtr );                              /* [GUD:RET:DEM_IRT_OK] dtrId */
                if ( retVal == DEM_IRT_OK )
                {
                    execClearDTC = Dem_Control_CheckExecClearDTCProcessActive();
                    getDTCOrigin = Dem_Control_GetClearDTCOrigin();

                    if ( ( execClearDTC == (boolean)TRUE ) && ( getDTCOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY ) )
                    {
                        DtrDataPtr->TestResult = (Dem_u16_DTRValueStoreType)0U;
                        DtrDataPtr->LowerLimit = (Dem_u16_DTRValueStoreType)0U;
                        DtrDataPtr->UpperLimit = (Dem_u16_DTRValueStoreType)0U;
                    }

                    DtrDataPtr->TIDValue = Dem_DtrTable[dtrId].DemDtrTid;                               /* [GUD]dtrId */
                    DtrDataPtr->UaSID    = Dem_DtrTable[dtrId].DemDtrUasid;                             /* [GUD]dtrId */

                    /* Holds number of TID got (= next TID index value) */
                    Dem_DtrGetDataTidNum = Dem_DtrGetDataTidNum + (Dem_u08_DTRTidIndexType)1U;

                    /* Holds restart position value */
                    Dem_DtrGetDataRestartPos = pos + DEM_DTR_CAL_POS_1;

                    break;
                }
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_DTR_ClearDTRData                                     */
/* Description   | Clear DTR results.                                       */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
FUNC(void, DEM_CODE) Dem_DTR_ClearDTRData
(void)
{
    /* Clears DTR results in DtrRecord */
    Dem_DTRMng_ClearDTRRecordData();

    return;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Function Name | Dem_DTR_SetDTR_Normal                                    */
/* Description   | Sets DTR result in DtrRecord                             */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTRId      : DTR identifier.                        */
/*               | [in] TestResult : Test result of DTR.                    */
/*               | [in] LowerLimit : Lower limit of DTR.                    */
/*               | [in] UpperLimit : Upper limit of DTR.                    */
/*               | [in] Ctrlval    : Control value of the DTR to support    */
/*               |                   its interpretation Dem-internally.     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC(void, DEM_CODE) Dem_DTR_SetDTR_Normal
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) DTRId,       /* [PRMCHK:CALLER] */
    VAR( Dem_s32_DTRValueRawType, AUTOMATIC) TestResult,
    VAR( Dem_s32_DTRValueRawType, AUTOMATIC) LowerLimit,
    VAR( Dem_s32_DTRValueRawType, AUTOMATIC) UpperLimit,
    VAR( Dem_DTRControlType, AUTOMATIC ) Ctrlval
)
{
    VAR( Dem_DTRConvertInputType, AUTOMATIC ) dtrConvertInput;
    VAR( Dem_DTRConvertOutputType, AUTOMATIC ) dtrConvertOutput;
    VAR(Dem_DtrDataType, AUTOMATIC) dtrData;
    VAR( Dem_u08_DTRMidIndexType, AUTOMATIC ) dtrMidIndex;

    /* Equivalent to NORMAL by Converting limit values */
    /*  set input information   */
    dtrConvertInput.TestResult      =   TestResult;
    dtrConvertInput.LowerLimit      =   LowerLimit;
    dtrConvertInput.UpperLimit      =   UpperLimit;
    dtrConvertInput.CompuN0DivD0    =   Dem_DtrTable[DTRId].DemDtrCompuN0DivD0;             /* [GUDCHK:CALLER]DTRId */
    dtrConvertInput.CompuN1DivD0    =   Dem_DtrTable[DTRId].DemDtrCompuN1DivD0;             /* [GUDCHK:CALLER]DTRId */
    dtrConvertInput.DtrUasid        =   Dem_DtrTable[DTRId].DemDtrUasid;                    /* [GUDCHK:CALLER]DTRId */
    dtrConvertInput.Ctrlval         =   Ctrlval;

    /*  clear output parameter  */
    dtrConvertOutput.TestResult     =   ( Dem_u16_DTRValueStoreType )0U;
    dtrConvertOutput.LowerLimit     =   ( Dem_u16_DTRValueStoreType )0U;
    dtrConvertOutput.UpperLimit     =   ( Dem_u16_DTRValueStoreType )0U;
    dtrConvertOutput.ConvertInfo    =   DEM_DTR_TESTRESULT_NORMAL;

    /* Converts linear */
    Dem_DTR_ConvertLinearAndAdjust( &dtrConvertInput, &dtrConvertOutput );

    /*  set DTR data.           */
    dtrData.RawTestResult   =   TestResult;
    dtrData.RawLowerLimit   =   LowerLimit;
    dtrData.RawUpperLimit   =   UpperLimit;
    dtrData.TIDValue        =   Dem_DtrTable[DTRId].DemDtrTid;              /* [GUDCHK:CALLER]DTRId */
    dtrData.UaSID           =   Dem_DtrTable[DTRId].DemDtrUasid;            /* [GUDCHK:CALLER]DTRId */
    dtrData.CtrlVal         =   DEM_DTR_CTL_NORMAL;

    dtrData.TestResult      =   dtrConvertOutput.TestResult;
    dtrData.LowerLimit      =   dtrConvertOutput.LowerLimit;
    dtrData.UpperLimit      =   dtrConvertOutput.UpperLimit;

    /* Sets DTR result in DtrRecord */
    Dem_DTRMng_SetDTRRecordData( DTRId, &dtrData );

    /* Updates ObdmidInfo table */
    dtrMidIndex = Dem_DtrTable[DTRId].DemDtrMidIndex;                       /* [GUDCHK:CALLER]DTRId *//* [GUD:CFG:IF_GUARDED: DTRId ]dtrMidIndex */
    Dem_DTR_SetObdmidInfo( dtrMidIndex );                                   /* [GUD:CFG:IF_GUARDED: DTRId ]dtrMidIndex */

    return;
}

/****************************************************************************/
/* Function Name | Dem_DTR_SetDTR_CtrlVal                                   */
/* Description   | Sets DTR result (only CtrlVal) in DtrRecord              */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTRId      : DTR identifier.                        */
/*               | [in] Ctrlval    : Control value of the DTR to support    */
/*               |                   its interpretation Dem-internally.     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC(void, DEM_CODE) Dem_DTR_SetDTR_CtrlVal
(
    VAR( Dem_u16_DTRIndexType, AUTOMATIC ) DTRId,       /* [PRMCHK:CALLER] */
    VAR( Dem_DTRControlType, AUTOMATIC ) Ctrlval
)
{
    VAR(Dem_DtrDataType, AUTOMATIC) dtrData;
    VAR(Dem_u08_DTRMidIndexType, AUTOMATIC) dtrMidIndex;

    Dem_DTR_ClearDTRDataArea( Ctrlval, &dtrData );

    /* Sets DTR result in DtrRecord */
    Dem_DTRMng_SetDTRRecordData( DTRId, &dtrData );             /* [GUDCHK:CALLER]DTRId */

    /* Updates ObdmidInfo table */
    dtrMidIndex = Dem_DtrTable[DTRId].DemDtrMidIndex;           /* [GUDCHK:CALLER]DTRId *//* [GUD:CFG:IF_GUARDED: DTRId ]dtrMidIndex */
    Dem_DTR_SetObdmidInfo( dtrMidIndex );                       /* [GUD:CFG:IF_GUARDED: DTRId ]dtrMidIndex */

    return ;
}

/****************************************************************************/
/* Function Name | Dem_DTR_SetDTR_ForFailedTid                              */
/* Description   | If the DTR result is failed, resets the DTR report       */
/* Preconditions | none                                                     */
/* Parameters    | [in] DTRId      : DTR identifier.                        */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC(void, DEM_CODE) Dem_DTR_SetDTR_ForFailedTid
(
    VAR(Dem_u16_DTRIndexType, AUTOMATIC) DTRId
)
{
    VAR(Dem_u08_InternalReturnType, AUTOMATIC) retVal;
    VAR(boolean , AUTOMATIC) failedTid;
    VAR(Dem_DtrDataType, AUTOMATIC) dtrData;

    failedTid = (boolean)FALSE;

    Dem_DTR_ClearDTRDataArea( DEM_DTR_CTL_RESET_FOR_FAILED_TID, &dtrData );

    /* Gets DTR result in DtrRecord */
    retVal = Dem_DTRMng_GetDTRRecordData( DTRId, &dtrData );    /* [GUD:RET:DEM_IRT_OK] DTRId  */
    if ( retVal == DEM_IRT_OK )
    {
        if ( Dem_DtrTable[DTRId].DemDtrUasid >= DEM_DTR_UASID_SIGNED )      /* [GUD]DTRId */
        {
            /* If DTR result is failed, resets the DTR report */
            if ( ((Dem_s16_DTRValueStoreType)(dtrData.TestResult) < (Dem_s16_DTRValueStoreType)(dtrData.LowerLimit)) ||
                 ((Dem_s16_DTRValueStoreType)(dtrData.TestResult) > (Dem_s16_DTRValueStoreType)(dtrData.UpperLimit)) )
            {
                failedTid = (boolean)TRUE;
            }
        }
        else
        {
            /* If DTR result is failed, resets the DTR report */
            if ( (dtrData.TestResult < dtrData.LowerLimit) ||
                 (dtrData.TestResult > dtrData.UpperLimit) )
            {
                failedTid = (boolean)TRUE;
            }
        }

        if ( failedTid == (boolean)TRUE )
        {
            dtrData.CtrlVal = DEM_DTR_CTL_RESET;

            /* Sets DTR result in DtrRecord */
            Dem_DTRMng_SetDTRRecordData( DTRId, &dtrData );
        }
    }

    return;
}

/****************************************************************************/
/* Function Name | Dem_DTR_SetObdmidInfo                                    */
/* Description   | Updates ObdmidInfo table                                 */
/* Preconditions | none                                                     */
/* Parameters    | [in] MidIndex : Monitor ID index                         */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/*   v5-8-0      | branch changed.                                          */
/*   v5-10-0     | no branch changed.                                       */
/****************************************************************************/
static FUNC(void, DEM_CODE) Dem_DTR_SetObdmidInfo
(
    VAR(Dem_u08_DTRMidIndexType, AUTOMATIC) MidIndex        /* [PRMCHK:CALLER] */
)
{
    VAR(Dem_u08_DTRSupportObdMidIndexType, AUTOMATIC) tblNum;
    VAR(Dem_u08_DTRTidIndexType, AUTOMATIC)  tids;
    VAR(Dem_u32_DTRObdMidBmpType, AUTOMATIC)  nowBitValue;
    VAR(Dem_u32_DTRObdMidBmpType, AUTOMATIC)  preBitValue;
    VAR(Dem_u08_DTRSupportObdMidIndexType, AUTOMATIC)  obdmidInfoNum;
    VAR(Dem_u08_DTRObdMidBmpBitCountType, AUTOMATIC)  bitOffset;
    VAR(Dem_u32_DTRObdMidBmpType, AUTOMATIC) obdmidInfoLocal[DEM_DTR_SUPPORT_OBDMID_NUM];
    VAR(Dem_u32_DTRObdMidBmpType, AUTOMATIC)  isSupported;
    VAR(Dem_u32_DTRObdMidBmpType, AUTOMATIC)  lastBitValue;
    VAR(sint8, AUTOMATIC)  modTblNum;
    VAR(sint8, AUTOMATIC)  updateTblNum;
    VAR(Dem_u16_DTRIndexType, AUTOMATIC) offsetTop;
    VAR(Dem_u08_DTRTidIndexType, AUTOMATIC)  tidNumMax;
    VAR(Dem_u08_DTRObdMidType, AUTOMATIC)  mid;
    VAR(Dem_u08_DTRObdMidType, AUTOMATIC)  checkSupportMidBit;

    isSupported      = DEM_DTR_INVISIBLE;
    offsetTop = Dem_DtrMidTable[MidIndex].DemDtrIdOffsetTop;        /* [GUDCHK:CALLER]MidIndex */
    tidNumMax = Dem_DtrMidTable[MidIndex].DemDtrTidNum;             /* [GUDCHK:CALLER]MidIndex */
    mid       = Dem_DtrMidTable[MidIndex].DemDtrMid;                /* [GUDCHK:CALLER]MidIndex */

    checkSupportMidBit = mid & DEM_DTR_GETMID_MASK;
    if ( checkSupportMidBit != (Dem_u08_DTRObdMidType)0U )
    {
        /* mid is not 0x00, 0x20, 0x40, 0x60, 0x80, 0xA0, 0xC0, or 0xE0 */

        /* Duplicates OBDMID bitmaps */
        for (tblNum = ((Dem_u08_DTRSupportObdMidIndexType)0U); tblNum < DEM_DTR_SUPPORT_OBDMID_NUM; tblNum++)       /* [GUD:for]tblNum */
        {
            obdmidInfoLocal[tblNum] = Dem_DtrObdMidVisibleBitmap[tblNum];       /* [GUD]tblNum *//* [ARYCHK] DEM_DTR_SUPPORT_OBDMID_NUM / 1 / tblNum */
        }

        /* Gets number of visible TID */
        tids = Dem_DTRMng_GetNumTIDsOfOBDMID(offsetTop, tidNumMax);

        nowBitValue = DEM_DTR_INVISIBLE;

        /* Checks if the MID is supported */
        if ( tids != ((Dem_u08_DTRTidIndexType)0U) )
        {
            nowBitValue = DEM_DTR_VISIBLE;
        }

        /* Gets element number of OBDMID bitmaps and bit offset */
        obdmidInfoNum = (Dem_u08_DTRSupportObdMidIndexType)( mid >> DEM_DTR_GETMID_BITOFFSET );     /*  right 5 bit shift is equal to divided by 32.    */  /* [GUD:logic]obdmidInfoNum */
        bitOffset     = DEM_DTR_BIT32 - (mid & DEM_DTR_GETMID_MASK);

        /* Gets previous bit state of the MID */
        preBitValue = (Dem_u32_DTRObdMidBmpType)( (obdmidInfoLocal[obdmidInfoNum] >> bitOffset) & DEM_DTR_VISIBLE );        /* [GUD]obdmidInfoNum *//* [ARYCHK] DEM_DTR_SUPPORT_OBDMID_NUM / 1 / obdmidInfoNum */

        /* Updates OBDMID bitmaps if the MID bit state is changed */
        if ( nowBitValue != preBitValue )
        {
            /* Updates the MID bit state and this last bit state of duplication */
            for ( modTblNum = (sint8)obdmidInfoNum; modTblNum >= ((sint8)0); modTblNum-- )                                  /* [GUD:for]modTblNum */
            {
                if ( modTblNum == (sint8)obdmidInfoNum )
                {
                    /* Updates the MID state of duplication */
                    obdmidInfoLocal[obdmidInfoNum] = obdmidInfoLocal[obdmidInfoNum] ^ ( DEM_DTR_VISIBLE << bitOffset );     /* [GUD]obdmidInfoNum *//* [ARYCHK] DEM_DTR_SUPPORT_OBDMID_NUM / 1 / obdmidInfoNum *//* [ARYCHK] DEM_DTR_SUPPORT_OBDMID_NUM / 1 / obdmidInfoNum */
                }
                else
                {
                    /* Gets this last bit state */
                    lastBitValue = ( obdmidInfoLocal[modTblNum] & DEM_DTR_VISIBLE );                                        /* [GUD]modTblNum *//* [ARYCHK] DEM_DTR_SUPPORT_OBDMID_NUM / 1 / modTblNum */

                    /* Ends the roop if this last bit doesn't need to be updated */
                    if ( lastBitValue == isSupported )
                    {
                        break;
                    }

                    /* Updates this last bit state of duplication */
                    obdmidInfoLocal[modTblNum] = obdmidInfoLocal[modTblNum] ^ DEM_DTR_VISIBLE ;                             /* [GUD]modTblNum *//* [ARYCHK] DEM_DTR_SUPPORT_OBDMID_NUM / 1 / modTblNum *//* [ARYCHK] DEM_DTR_SUPPORT_OBDMID_NUM / 1 / modTblNum */
                }

                /* Holds if this OBDMID is supported */
                if ( obdmidInfoLocal[modTblNum] == DEM_DTR_INVISIBLE )                                                      /* [GUD]modTblNum *//* [ARYCHK] DEM_DTR_SUPPORT_OBDMID_NUM / 1 / modTblNum */
                {
                    isSupported = DEM_DTR_INVISIBLE;
                }
                else
                {
                    isSupported = DEM_DTR_VISIBLE;
                }
            }

            SchM_Enter_Dem_DTR();

            /* Updates OBDMID bitmaps from BODMID has the target bit to last modified table number */
            for ( updateTblNum = (sint8)obdmidInfoNum; updateTblNum > modTblNum; updateTblNum-- )                           /* [GUD:for]updateTblNum */
            {
                Dem_DtrObdMidVisibleBitmap[updateTblNum] = obdmidInfoLocal[updateTblNum];                                   /* [GUD]updateTblNum *//* [ARYCHK] DEM_DTR_SUPPORT_OBDMID_NUM / 1 / updateTblNum */
            }

            SchM_Exit_Dem_DTR();
        }
    }
    return;
}

/****************************************************************************/
/* Function Name | Dem_DTR_GetObdmidInfo                                    */
/* Description   | Get ObdmidInfo table                                     */
/* Preconditions | none                                                     */
/* Parameters    | [in]   Obdmid                                            */
/*               | [out]  DtrDataPtr : DTR data pointer                     */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DTR_GetObdmidInfo
(
    VAR( Dem_u08_DTRObdMidType, AUTOMATIC ) Obdmid,
    P2VAR( Dem_u32_DTRObdMidBmpType, AUTOMATIC, AUTOMATIC ) ObdmidvaluePtr
)
{
    VAR( Dem_u08_DTRSupportObdMidIndexType, AUTOMATIC ) obdmidInfoNum;

    /* Gets element number of OBDMID bitmaps */
    obdmidInfoNum = Obdmid >> DEM_DTR_GETMID_BITOFFSET;             /* [GUD:logic]obdmidInfoNum */

    /*  [ obdmidInfoNum]  is always less than 8(DEM_DTR_SUPPORT_OBDMID_NUM).                    */
    /*  This is because if uint8 is shifted to the right by 5(DEM_DTR_GETMID_BITOFFSET) bits,   */
    /*  the maximum value is 7.                                                                 */
    SchM_Enter_Dem_DTR();

    /* Gets OBDMID bitmap */
    *ObdmidvaluePtr = Dem_DtrObdMidVisibleBitmap[obdmidInfoNum];    /* [GUD]obdmidInfoNum */

    SchM_Exit_Dem_DTR();


    return ;
}


/****************************************************************************/
/* Function Name | Dem_DTR_ClearDTRDataArea                                 */
/* Description   | Clear DTR data area                                      */
/* Preconditions | none                                                     */
/* Parameters    | [in] Ctrlval    : Control value of the DTR to support    */
/*               |                   its interpretation Dem-internally.     */
/*               | [in] DtrDataPtr  : DTR data pointer                      */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/****************************************************************************/
static FUNC( void, DEM_CODE ) Dem_DTR_ClearDTRDataArea
(
    VAR( Dem_DTRControlType, AUTOMATIC ) Ctrlval,
    P2VAR( Dem_DtrDataType, AUTOMATIC, AUTOMATIC ) DtrDataPtr
)
{
    DtrDataPtr->TestResult      = ((Dem_u16_DTRValueStoreType)0U);
    DtrDataPtr->LowerLimit      = ((Dem_u16_DTRValueStoreType)0U);
    DtrDataPtr->UpperLimit      = ((Dem_u16_DTRValueStoreType)0U);

    DtrDataPtr->RawTestResult   = ((Dem_s32_DTRValueRawType)0);
    DtrDataPtr->RawLowerLimit   = ((Dem_s32_DTRValueRawType)0);
    DtrDataPtr->RawUpperLimit   = ((Dem_s32_DTRValueRawType)0);

    DtrDataPtr->TIDValue        = ((Dem_u08_DTRTidIndexType)0U);
    DtrDataPtr->UaSID           = ((Dem_u08_DTRUasidType)0U);
    DtrDataPtr->CtrlVal         = Ctrlval;

    return;
}


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_DTR_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
