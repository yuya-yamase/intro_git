/* Dem_EDR_FilEDR_c(v5-8-0)                                                 */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/EDR_FilEDR/CODE                                       */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_Pm_DataAvl.h"
#include "../../../inc/Dem_Pm_DataCtl.h"
#include "../../../inc/Dem_Pm_EDR.h"
#include "../../../inc/Dem_Pm_DTC.h"
#include "../../../inc/Dem_Pm_Misfire.h"
#include "../../../cfg/Dem_EDR_Cfg.h"
#include "Dem_EDR_FilEDR_local.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_EDR_FILEDR_FIND_REST_MASK_FFFFFFFF  ((uint32)0xFFFFFFFFU )
#define DEM_EDR_FILEDR_FIND_TARGET_MASK_1       ((uint32)0x00000001U )
#define DEM_EDR_FILEDR_DTC_BITMAP_TABLE_SIZE    ((Dem_u16_EventStrgIndexType)32U )


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

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EDR_CheckEDRSupportDTCBitmapTable
(
    VAR( Dem_u08_EDRSupDTCBmpIndexType, AUTOMATIC )             SearchDemEDRSupDTCBmpIndex,
    VAR( uint32, AUTOMATIC )                                    SearchDTCBitmapTable,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC )         DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC )        DTCStatusPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )                      BitMapTableCompleteFlgPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )                      DearchCylinderModePtr
);

static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EDR_CheckEDRNumberSupportBitmapTable
(
    VAR( Dem_u08_EDRNumberSupBmpIndexType, AUTOMATIC )              BmpTableIndex,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC )             DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC )            DTCStatusPtr
);

static FUNC( Dem_u08_EDRNumberSupBmpIndexType, DEM_CODE ) Dem_EDR_SearchEDRSupportRecNumFirstPos
(
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber
);

static FUNC( boolean, DEM_CODE ) Dem_EDR_CheckObdEventStrgIndexAvl
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
);

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

static VAR( Dem_u08_EDRRecordNumberType, DEM_VAR_NO_INIT ) Dem_EDRRequestExtendedDataNumber;

static VAR( Dem_u08_EDRNumberSupBmpIndexType, DEM_VAR_NO_INIT )  Dem_EDRSupportRecNumBmpTableIndex;
static VAR( Dem_u08_EDRSupDTCBmpIndexType, DEM_VAR_NO_INIT )     Dem_EDRSupDTCBmpIndex;
static VAR( Dem_u16_EventStrgIndexType, DEM_VAR_NO_INIT )        Dem_DtcBitmapTablePos;
static VAR( Dem_u16_EventStrgIndexType, DEM_VAR_NO_INIT )        Dem_FilteredEDRSearchLoopNum;

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
static VAR( boolean, DEM_VAR_NO_INIT )                           Dem_SearchCylinderMode;
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

#define DEM_STOP_SEC_VAR_NO_INIT
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CONST
#include <Dem_MemMap.h>
/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_EDR_GetExtendedDataRecord                            */
/* Description   | Sets the extended data record number filter.             */
/* Preconditions | none                                                     */
/* Parameters    | [in] ExtendedDataNumber :                                */
/*               |        Identification/Number of requested extended data  */
/*               |        record.                                           */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success.                             */
/*               |        DEM_IRT_WRONG_RECORDNUMBER :                      */
/*               |                  Record number is not supported.         */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no branch changed.                                       */
/*   v5-8-0      | no branch changed.                                       */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EDR_SetEDRNumberFilter
(
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )        retVal;
    VAR( Dem_u08_EDRNumberSupBmpIndexType, AUTOMATIC )  extendedDataNumberPos;

    /*  default : not supported.    */
    retVal                              = DEM_IRT_WRONG_RECORDNUMBER;
    Dem_EDRSupportRecNumBmpTableIndex   = DEM_EDRNUMBERSUPBMPINDEX_INVALID;

    extendedDataNumberPos = Dem_EDR_SearchEDRSupportRecNumPos( ExtendedDataNumber );

    if( extendedDataNumberPos != DEM_EDRNUMBERSUPBMPINDEX_INVALID )
    {
        /*  supported.                      */
        retVal                                  = DEM_IRT_OK;
        Dem_EDRSupportRecNumBmpTableIndex       = extendedDataNumberPos;
        Dem_EDRSupDTCBmpIndex                   = (Dem_u08_EDRSupDTCBmpIndexType)0U;
        Dem_DtcBitmapTablePos                   = (Dem_u16_EventStrgIndexType)0U;
        Dem_FilteredEDRSearchLoopNum            = (Dem_u16_EventStrgIndexType)0U;
        Dem_EDRRequestExtendedDataNumber        = ExtendedDataNumber;

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        Dem_SearchCylinderMode                  = (boolean)FALSE;
        /* misfire filtering */
        Dem_Misfire_SetFilteredDTCForCylinderForEDR( ExtendedDataNumber );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */
    }
    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_EDR_RestartSetEDRNumberFilter                        */
/* Description   | Restarts the extended data record number filter.         */
/* Preconditions | none                                                     */
/* Parameters    | none                                                     */
/* Return Value  | void                                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | new created.                                             */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_EDR_RestartSetEDRNumberFilter
( void )
{
    Dem_EDRSupDTCBmpIndex                   = (Dem_u08_EDRSupDTCBmpIndexType)0U;
    Dem_DtcBitmapTablePos                   = (Dem_u16_EventStrgIndexType)0U;
    Dem_FilteredEDRSearchLoopNum            = (Dem_u16_EventStrgIndexType)0U;

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    Dem_SearchCylinderMode                  = (boolean)FALSE;
    /* misfire filtering */
    Dem_Misfire_SetFilteredDTCForCylinderForEDR( Dem_EDRRequestExtendedDataNumber );
#endif  /*   ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )         */

    return;
}


/****************************************************************************/
/* Function Name | Dem_EDR_GetNextEDRNumFilteredDTC                         */
/* Description   | Gets the next filtered DTC and its DTC status.           */
/* Preconditions | Dem_EDR_SetEDRNumberFilter being executed.               */
/* Parameters    | [out] DTCValuePtr :                                      */
/*               |        Receives the DTC value in respective format of t- */
/*               |        he filter returned by this function.If the retur- */
/*               |        n value of the function is other than DEM_FILTER- */
/*               |        ED_OK this parameter does not contain valid data. */
/*               | [out] DTCStatusPtr :                                     */
/*               |        This parameter receives the status information o- */
/*               |        f the requested DTC.If the return value of the f- */
/*               |        unction call is other than DEM_STATUS_OK this pa- */
/*               |        rameter does not contain valid data.0x00...0xFF - */
/*               |        match DTCStatusMask as defined in ISO14229-1.     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Returned next filtered element       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No further element  */
/*               |         (matching the filter criteria) found             */
/*               |        DEM_IRT_PENDING : The requested value is calcula- */
/*               |        ted and currently not available. The caller can   */
/*               |        retry later.                                      */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EDR_GetNextEDRNumFilteredDTC
(
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC ) DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC ) DTCStatusPtr
)
{
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )        retVal;
    VAR( Dem_u08_EDRNumberSupBmpIndexType, AUTOMATIC ) bmpTableRecNum;

    retVal      = DEM_IRT_NO_MATCHING_ELEMENT;
    bmpTableRecNum = Dem_EDRSupportRecNumNum;

    if( Dem_EDRSupportRecNumBmpTableIndex < bmpTableRecNum )                                                                /* [GUD:if]Dem_EDRSupportRecNumBmpTableIndex */
    {
        retVal = Dem_EDR_CheckEDRNumberSupportBitmapTable( Dem_EDRSupportRecNumBmpTableIndex, DTCValuePtr, DTCStatusPtr );  /* [GUD]Dem_EDRSupportRecNumBmpTableIndex */

        if( retVal == DEM_IRT_OK )
        {
            /*------------------------------------------*/
            /*  convert to output statusOfDTC.          */
            /*------------------------------------------*/
            (*DTCStatusPtr) =   Dem_DTC_CnvDTCStatus_PmAvailabilityMask( (*DTCStatusPtr) );
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_EDR_SearchEDRSupportRecNumPos                        */
/* Description   | Gets the extended data record number Index.              */
/* Preconditions | none                                                     */
/* Parameters    | [in] ExtendedDataNumber :                                */
/*               |        Identification/Number of requested extended data  */
/*               |        record.                                           */
/* Return Value  | Dem_u08_EDRNumberSupBmpIndexType                         */
/*               |        DEM_EDRNUMBERSUPBMPINDEX_INVALID :                */
/*               |                  Record number is not supported.         */
/*               |        (others) : success.                               */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
FUNC( Dem_u08_EDRNumberSupBmpIndexType, DEM_CODE ) Dem_EDR_SearchEDRSupportRecNumPos
(
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber
)
{
    VAR( Dem_u08_EDRNumberSupBmpIndexType, AUTOMATIC ) searchFirstPos;
    VAR( Dem_s16_EDRNumberSupBmpIndexType, AUTOMATIC ) bmpTableRecNum;
    VAR( Dem_s16_EDRNumberSupBmpIndexType, AUTOMATIC ) edrSupportMin;
    VAR( Dem_s16_EDRNumberSupBmpIndexType, AUTOMATIC ) edrSupportMax;
    VAR( Dem_s16_EDRNumberSupBmpIndexType, AUTOMATIC ) edrSupportMid;
    VAR( Dem_u08_EDRNumberSupBmpIndexType, AUTOMATIC ) retExtendedDataNumberPos;
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC )      checkRecordNumber;

    /*  default : not supported.    */
    retExtendedDataNumberPos   = DEM_EDRNUMBERSUPBMPINDEX_INVALID;

    searchFirstPos = Dem_EDR_SearchEDRSupportRecNumFirstPos( ExtendedDataNumber );

    if( searchFirstPos != DEM_EDRNUMBERSUPBMPINDEX_INVALID )
    {
        bmpTableRecNum = (Dem_s16_EDRNumberSupBmpIndexType)Dem_EDRSupportRecNumNum;

        edrSupportMax = bmpTableRecNum - (Dem_s16_EDRNumberSupBmpIndexType)1;
        edrSupportMin = (Dem_s16_EDRNumberSupBmpIndexType)searchFirstPos;

        while( edrSupportMin <= edrSupportMax )
        {
            edrSupportMid = (Dem_s16_EDRNumberSupBmpIndexType)(( uint16 )(( (uint16)edrSupportMin + (uint16)edrSupportMax ) >> (uint16)1U ));

            checkRecordNumber = Dem_EDRNumberSupportBitmapTable[edrSupportMid].ExtendDataRecordNumber;      /* [GUD:logic]edrSupportMid */

            if( checkRecordNumber == ExtendedDataNumber )
            {
                /* Successful search */
                retExtendedDataNumberPos = (Dem_u08_EDRNumberSupBmpIndexType)edrSupportMid;

                /*  find it.        */
                break;
            }
            else if( checkRecordNumber < ExtendedDataNumber )
            {
                /*  search max : bmpTableRecNum     */
                edrSupportMin = edrSupportMid + (Dem_s16_EDRNumberSupBmpIndexType)1;
            }
            else
            {
                /*  search max : -1                 */
                edrSupportMax = edrSupportMid - (Dem_s16_EDRNumberSupBmpIndexType)1;
            }
        }
    }
    return retExtendedDataNumberPos;
}

/****************************************************************************/
/* Function Name | Dem_EDR_SearchEDRSupportRecNumPos                        */
/* Description   | Get extended data record number First Index.             */
/* Preconditions | none                                                     */
/* Parameters    | [in] ExtendedDataNumber :                                */
/*               |        Identification/Number of requested extended data  */
/*               |        record.                                           */
/* Return Value  | Dem_u08_EDRNumberSupBmpIndexType                         */
/*               |        DEM_EDRNUMBERSUPBMPINDEX_INVALID :                */
/*               |                  Record number is not supported.         */
/*               |        (others) : success.                               */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_EDRNumberSupBmpIndexType, DEM_CODE ) Dem_EDR_SearchEDRSupportRecNumFirstPos
(
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC ) ExtendedDataNumber
)
{
    VAR( Dem_u08_EDRNumberSupBmpIndexType, AUTOMATIC ) retExtendedDataNumberPos;
    VAR( Dem_u08_EDRRecordNumberType, AUTOMATIC )      startOfOBDRecordNumber;
    VAR( Dem_u08_EDRNumberSupBmpIndexType, AUTOMATIC ) bmpRecordNumberPos;
    VAR( Dem_u08_EDRNumberSupBmpIndexType, AUTOMATIC ) bmpTableRecNum;

    /*  default : not find.    */
    retExtendedDataNumberPos    = (Dem_u08_EDRNumberSupBmpIndexType)0U;
    bmpRecordNumberPos          = Dem_EDRSupportObdRecordNumberPos;
    bmpTableRecNum              = Dem_EDRSupportRecNumNum;

    if( ExtendedDataNumber >= DEM_EDR_RECNUM_90 )
    {
        if( bmpRecordNumberPos < bmpTableRecNum )                                                                   /* [GUD:if]bmpRecordNumberPos */
        {
            startOfOBDRecordNumber = Dem_EDRNumberSupportBitmapTable[bmpRecordNumberPos].ExtendDataRecordNumber;    /* [GUD]bmpRecordNumberPos */

            if( ExtendedDataNumber >= startOfOBDRecordNumber )
            {
                retExtendedDataNumberPos = bmpRecordNumberPos;
            }
            else
            {
                retExtendedDataNumberPos = DEM_EDRNUMBERSUPBMPINDEX_INVALID;
            }
        }
        else
        {
            retExtendedDataNumberPos = DEM_EDRNUMBERSUPBMPINDEX_INVALID;
        }
    }
    return retExtendedDataNumberPos;
}

/****************************************************************************/
/* Function Name | Dem_EDR_CheckEDRNumberSupportBitmapTable                 */
/* Description   | Gets the next filtered DTC and its DTC status.           */
/* Preconditions | Dem_EDR_SetEDRNumberFilter being executed.               */
/* Parameters    | [in] Dem_u08_EDRNumberSupBmpIndexType :                  */
/*               |        start of check range : extended record number.    */
/*               | [out] DTCValuePtr                                        */
/*               | [out] DTCStatusPtr                                       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Returned next filtered element       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No further element  */
/*               |         (matching the filter criteria) found             */
/*               |        DEM_IRT_PENDING : "DemFilteredEDRSearchLoopNum-   */
/*               |        ByCycle" is exceeded but the search process does  */
/*               |        not terminate                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EDR_CheckEDRNumberSupportBitmapTable
(
    VAR( Dem_u08_EDRNumberSupBmpIndexType, AUTOMATIC )              BmpTableIndex,      /* [PRMCHK:CALLER] */
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC )             DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC )            DTCStatusPtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )        filteredEDRSearchLoopNumMax;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )        supportDTCNumber;
    VAR( Dem_u08_EDRSupDTCBmpIndexType, AUTOMATIC )     searchDemEDRSupDTCBmpIndex;
    VAR( Dem_u08_EDRSupDTCBmpIndexType, AUTOMATIC )     searchDemEDRSupDTCBmpFirstIndex;
    VAR( Dem_u08_EDRSupDTCBmpIndexType, AUTOMATIC )     maxDemEDRSupDTCBmpIndex;

    VAR( uint32, AUTOMATIC )                            searchDTCBitmapTable;

    VAR( boolean, AUTOMATIC )                           bitMapTableCompleteFlg;
    VAR( boolean, AUTOMATIC )                           moveNextBitmapTblFlg;
    VAR( boolean, AUTOMATIC )                           searchCylinderMode;
    VAR( boolean, AUTOMATIC )                           loopExitFlag;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC )                           initialCheckEnd;
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */

    VAR( Dem_u08_InternalReturnType, AUTOMATIC )        retVal;

    retVal                          = DEM_IRT_NO_MATCHING_ELEMENT;
    searchCylinderMode              = (boolean)FALSE;
    moveNextBitmapTblFlg            = (boolean)FALSE;
    loopExitFlag                    = (boolean)FALSE;

    filteredEDRSearchLoopNumMax     = Dem_FilEDRSearchLoopNumByCycle;

    supportDTCNumber = Dem_EDRNumberSupportBitmapTable[BmpTableIndex].SupportDTCNumber;     /* [GUDCHK:CALLER]BmpTableIndex */

    if( supportDTCNumber > (Dem_u16_EventStrgIndexType)0U )
    {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
        initialCheckEnd                 = (boolean)FALSE;

        /* Searching for cylinder information? */
        if( Dem_SearchCylinderMode == (boolean)TRUE )
        {
            if( Dem_FilteredEDRSearchLoopNum < filteredEDRSearchLoopNumMax )
            {
                retVal = Dem_Misfire_GetNextFilterdDTCForCylinder( DTCValuePtr, DTCStatusPtr );

                if( retVal == DEM_IRT_OK )
                {
                    initialCheckEnd = (boolean)TRUE;
                }
                else
                {
                    Dem_SearchCylinderMode  = (boolean)FALSE;
                }

                Dem_FilteredEDRSearchLoopNum = Dem_FilteredEDRSearchLoopNum + (Dem_u16_EventStrgIndexType)1U;
            }
            else
            {
                initialCheckEnd = (boolean)TRUE;
                Dem_FilteredEDRSearchLoopNum = (Dem_u16_EventStrgIndexType)0U;
                retVal = DEM_IRT_PENDING;
            }
        }

        if( initialCheckEnd == (boolean)FALSE )
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
        {
            /* Search [ Dem_EDRNumberSupportBitmapTable ] */
            searchDemEDRSupDTCBmpFirstIndex = Dem_EDRSupDTCBmpIndex;
            maxDemEDRSupDTCBmpIndex = Dem_EDRSupportDTCNumber;

            for( searchDemEDRSupDTCBmpIndex = searchDemEDRSupDTCBmpFirstIndex; searchDemEDRSupDTCBmpIndex < maxDemEDRSupDTCBmpIndex; searchDemEDRSupDTCBmpIndex++ ) /* [GUD:for]searchDemEDRSupDTCBmpIndex */
            {
                if( Dem_FilteredEDRSearchLoopNum < filteredEDRSearchLoopNumMax )
                {
                    searchDTCBitmapTable = Dem_EDRNumberSupportBitmapTable[BmpTableIndex].SupportDTCBitmapTable[searchDemEDRSupDTCBmpIndex];                /* [GUDCHK:CALLER]BmpTableIndex *//* [GUD]searchDemEDRSupDTCBmpIndex */

                    /* Search [ SupportDTCBitmapTable ] */
                    retVal = Dem_EDR_CheckEDRSupportDTCBitmapTable( searchDemEDRSupDTCBmpIndex, searchDTCBitmapTable, DTCValuePtr, DTCStatusPtr, &bitMapTableCompleteFlg, &searchCylinderMode );

                    if( retVal != DEM_IRT_NO_MATCHING_ELEMENT )
                    {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                        Dem_SearchCylinderMode  = searchCylinderMode;
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
                        moveNextBitmapTblFlg    = bitMapTableCompleteFlg;
                        loopExitFlag            = (boolean)TRUE;
                    }
                }
                else
                {
                    Dem_FilteredEDRSearchLoopNum = (Dem_u16_EventStrgIndexType)0U;
                    retVal          = DEM_IRT_PENDING;
                    loopExitFlag    = (boolean)TRUE;
                }

                if( loopExitFlag == (boolean)TRUE )
                {
                    break;
                }
            }

#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
            if( Dem_SearchCylinderMode == (boolean)FALSE )
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
            {
                if( moveNextBitmapTblFlg  == (boolean)TRUE )
                {
                    Dem_EDRSupDTCBmpIndex       = searchDemEDRSupDTCBmpIndex + (Dem_u08_EDRSupDTCBmpIndexType)1U;
                }
                else
                {
                    Dem_EDRSupDTCBmpIndex       = searchDemEDRSupDTCBmpIndex;
                }
            }
        }
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_EDR_CheckEDRSupportDTCBitmapTable                    */
/* Description   | Gets the next filtered DTC and its DTC status.           */
/* Preconditions | Dem_EDR_SetEDRNumberFilter being executed.               */
/* Parameters    | [in]  SearchDemEDRSupDTCBmpIndexPtr                      */
/*               | [out] DTCValuePtr                                        */
/*               | [out] DTCStatusPtr                                       */
/*               | [out] BitMapTableCompleteFlgPtr                          */
/*               | [out] DearchCylinderModePtr                              */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Returned next filtered element       */
/*               |        DEM_IRT_NO_MATCHING_ELEMENT : No further element  */
/*               |         (matching the filter criteria) found             */
/*               |        DEM_IRT_PENDING : "DemFilteredEDRSearchLoopNum-   */
/*               |        ByCycle" is exceeded but the search process does  */
/*               |        not terminate                                     */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | branch changed.                                          */
/****************************************************************************/
static FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_EDR_CheckEDRSupportDTCBitmapTable
(
    VAR( Dem_u08_EDRSupDTCBmpIndexType, AUTOMATIC )             SearchDemEDRSupDTCBmpIndex,
    VAR( uint32, AUTOMATIC )                                    SearchDTCBitmapTable,
    P2VAR( Dem_u32_DTCValueType, AUTOMATIC, AUTOMATIC )         DTCValuePtr,
    P2VAR( Dem_UdsStatusByteType, AUTOMATIC, AUTOMATIC )        DTCStatusPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )                      BitMapTableCompleteFlgPtr,
    P2VAR( boolean, AUTOMATIC, AUTOMATIC )                      DearchCylinderModePtr
)
{
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )        filteredEDRSearchLoopNumMax;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )        searchDTCBitmapTablePos;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )        searchDTCBitmapTableFirstPos;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )        addNextTablePos;
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC )        eventStrgIndex;
    VAR( uint32, AUTOMATIC )                            tableCheck;
    VAR( uint32, AUTOMATIC )                            bmpIndexCheck;
    VAR( boolean, AUTOMATIC )                           loopExitFlag;

    VAR( boolean, AUTOMATIC )                           resultOfChecking;
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
    VAR( boolean, AUTOMATIC )                           misfireEventKind;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )        retChkCylDtc;
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )        retChkDtc;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC )        retVal;

    retVal                          = DEM_IRT_NO_MATCHING_ELEMENT;
    searchDTCBitmapTableFirstPos    = Dem_DtcBitmapTablePos;
    filteredEDRSearchLoopNumMax     = Dem_FilEDRSearchLoopNumByCycle;
    addNextTablePos                 = (Dem_u16_EventStrgIndexType)0U;
    loopExitFlag                    = (boolean)FALSE;

    *BitMapTableCompleteFlgPtr      = (boolean)FALSE;
    *DearchCylinderModePtr          = (boolean)FALSE;

    for( searchDTCBitmapTablePos = searchDTCBitmapTableFirstPos; searchDTCBitmapTablePos < DEM_EDR_FILEDR_DTC_BITMAP_TABLE_SIZE; searchDTCBitmapTablePos++ )
    {
        if( Dem_FilteredEDRSearchLoopNum < filteredEDRSearchLoopNumMax )
        {
            tableCheck  = ( DEM_EDR_FILEDR_FIND_REST_MASK_FFFFFFFF << (uint32)searchDTCBitmapTablePos );

            if( ( SearchDTCBitmapTable & tableCheck ) > (uint32)0x00000000U )
            {
                bmpIndexCheck = ( DEM_EDR_FILEDR_FIND_TARGET_MASK_1 << (uint32)searchDTCBitmapTablePos );

                if( (SearchDTCBitmapTable & bmpIndexCheck ) == bmpIndexCheck )
                {
                    eventStrgIndex = (Dem_u16_EventStrgIndexType)( (Dem_u16_EventStrgIndexType)SearchDemEDRSupDTCBmpIndex << (Dem_u16_EventStrgIndexType)DEM_FILEDR_BITSHIFT_5 );
                    eventStrgIndex = eventStrgIndex + searchDTCBitmapTablePos;

                    /* Checks the event-storage-index is OBD-DTC and available.  */
                    resultOfChecking = Dem_EDR_CheckObdEventStrgIndexAvl( eventStrgIndex );
                    if( resultOfChecking == (boolean)TRUE )
                    {
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )  /*  [FuncSw]    */
                        misfireEventKind = Dem_CfgInfoPm_CheckEventKindOfMisfire_InEvtStrgGrp( eventStrgIndex );

                        if( misfireEventKind == (boolean)TRUE )
                        {
                            retChkCylDtc = Dem_Misfire_GetNextFilterdDTCForCylinder( DTCValuePtr, DTCStatusPtr );
                            if( retChkCylDtc == DEM_IRT_OK )
                            {
                                *DearchCylinderModePtr  = (boolean)TRUE;
                                addNextTablePos         = (Dem_u16_EventStrgIndexType)1U;
                                loopExitFlag            = (boolean)TRUE;
                                retVal                  = DEM_IRT_OK;
                            }
                        }
                        else
#endif /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
                        {
                            retChkDtc = Dem_DTC_GetDTCStatusAndUdsDTC( eventStrgIndex, DTCValuePtr, DTCStatusPtr );
                            if( retChkDtc == DEM_IRT_OK )
                            {
                                addNextTablePos     = (Dem_u16_EventStrgIndexType)1U;
                                loopExitFlag        = (boolean)TRUE;
                                retVal              = DEM_IRT_OK;
                            }
                        }
                    }
                }
                Dem_FilteredEDRSearchLoopNum = Dem_FilteredEDRSearchLoopNum + (Dem_u16_EventStrgIndexType)1U;
            }
            else
            {
                Dem_FilteredEDRSearchLoopNum = Dem_FilteredEDRSearchLoopNum + (DEM_EDR_FILEDR_DTC_BITMAP_TABLE_SIZE - searchDTCBitmapTablePos);
                addNextTablePos     = DEM_EDR_FILEDR_DTC_BITMAP_TABLE_SIZE;
                loopExitFlag        = (boolean)TRUE;
            }
        }
        else
        {
            Dem_FilteredEDRSearchLoopNum = (Dem_u16_EventStrgIndexType)0U;
            retVal          = DEM_IRT_PENDING;
            loopExitFlag    = (boolean)TRUE;
        }

        if( loopExitFlag == (boolean)TRUE )
        {
            break;
        }
    }

    /* search position update */
    Dem_DtcBitmapTablePos = searchDTCBitmapTablePos + addNextTablePos;

    if( Dem_DtcBitmapTablePos >= DEM_EDR_FILEDR_DTC_BITMAP_TABLE_SIZE )
    {
        Dem_DtcBitmapTablePos       = (Dem_u16_EventStrgIndexType)0U;
        *BitMapTableCompleteFlgPtr  = (boolean)TRUE;
    }

    return retVal;
}

/****************************************************************************/
/* Function Name | Dem_EDR_CheckObdEventStrgIndexAvl                        */
/* Description   | Checks the event-storage-index is OBD-DTC and available. */
/* Preconditions | Dem_EDR_SetEDRNumberFilter being executed.               */
/* Parameters    | [in]  EventStrgIndex                                     */
/* Return Value  | boolean                                                  */
/*               |        TRUE : The specified event-storage-index is OBD-  */
/*               |               DTC and available.                         */
/*               |        FALSE : The specified event-storage-index is not  */
/*               |               OBD-DTC or available.                      */
/* Notes         | none                                                     */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | new created.                                             */
/****************************************************************************/
static FUNC( boolean, DEM_CODE ) Dem_EDR_CheckObdEventStrgIndexAvl
(
    VAR( Dem_u16_EventStrgIndexType, AUTOMATIC ) EventStrgIndex
)
{
    VAR( boolean, AUTOMATIC ) retVal;
    VAR( boolean, AUTOMATIC ) availableStatus;
    VAR( boolean, AUTOMATIC ) isObdDTC;

    retVal = ( boolean )FALSE;

    availableStatus = Dem_DataAvl_GetEvtAvl_InEvtStrgGrp( EventStrgIndex );
    if( availableStatus == ( boolean )TRUE )
    {
        if( ( DEM_EDR_RECNUM_90 <= Dem_EDRRequestExtendedDataNumber ) && ( DEM_EDR_RECNUM_9F >= Dem_EDRRequestExtendedDataNumber ) )
        {
            /*  OBD record number.      */
            isObdDTC = Dem_CfgInfoPm_CheckEventKindOfOBD_InEvtStrgGrp( EventStrgIndex );
            if( isObdDTC == ( boolean )TRUE )
            {
                retVal = ( boolean )TRUE;
            }
        }
        else
        {
            /*  nonOBD record number.   */
            retVal = ( boolean )TRUE;
        }
    }

    return retVal;
}

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
