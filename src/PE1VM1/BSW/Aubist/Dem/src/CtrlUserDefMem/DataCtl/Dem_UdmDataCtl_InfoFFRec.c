/* Dem_UdmDataCtl_InfoFFRec_c(v5-5-0)                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/UdmDataCtl_InfoFFRec/CODE                             */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Udm_Data.h"
#include "Dem_UdmDataCtl_local.h"
#include "Dem_UdmDataCtl_InfoTSFFD.h"

#if ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/

/****************************************************************************/
/* Internal Functions                                                       */
/****************************************************************************/
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
/* Function Name | Dem_UdmData_GetSizeOfFreezeFrameOfDisabledRecord         */
/* Description   | Gets the size of freeze frame record corresponding to t- */
/*               | he specified event index and the record number.          */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        The udm event index corresponding to the specifi- */
/*               |        c DTC value.                                      */
/*               | [in] RecordNumber :                                      */
/*               |        The record number corresponding to the specified  */
/*               |         event index.                                     */
/*               | [out] SizeOfFreezeFramePtr :                             */
/*               |        The size of freeze frame record corresponding to  */
/*               |         the specified event index and record number.     */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : success.                             */
/*               |        DEM_IRT_NG : parameter error.                     */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : wrong record number. */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_GetSizeOfFreezeFrameOfDisabledRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2VAR( Dem_u32_FFDOutputTotalSizeType, AUTOMATIC, AUTOMATIC ) SizeOfFreezeFramePtr
)
{
    VAR( Dem_u32_FFDOutputTotalSizeType, AUTOMATIC ) allSize;
    VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC ) sizeAtFFD;
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) triggerFFDCount;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retCheckRecNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetFFD;

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )   /*  [FuncSw]    */
    VAR( Dem_u32_FFDOutputTotalSizeType, AUTOMATIC ) allTSFFDSize;
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) storedTSFFRecordNumber;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) tsffdCount;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retGetTSFFD;
#endif  /*  ( DEM_TSFF_UDM_SUPPORT == STD_ON )          */

    /*  get saved FFD count.                    */
    allSize   =   ( Dem_u32_FFDOutputTotalSizeType )0U;
    triggerFFDCount =   Dem_UdmData_GetStoredRecordNumberCounts();

    retVal  =   DEM_IRT_WRONG_RECORDNUMBER;

    if ( triggerFFDCount > ( Dem_u16_FFRecNumStoredIndexType )0U )
    {
        /*  check record number.                */
        if ( RecordNumber < DEM_FFRECNUM_ALL_RECORDS )
        {
            /* Check whether RecordNumber is configured */
            retCheckRecNum = Dem_UdmData_CheckRecordNumberInDisabledRecord( UdmEventIndex, RecordNumber );

            if( retCheckRecNum == DEM_IRT_OK )
            {
                /* Get the FreezeFrameData for non-OBD */
                sizeAtFFD   =   ( Dem_u16_FFDStoredIndexType )0U;

                retVal  =   Dem_UdmData_GetFreezeFrameData( UdmEventIndex, RecordNumber, DEM_FFDGETTYPE_SIZE, NULL_PTR, &sizeAtFFD );
                if ( retVal == DEM_IRT_OK )
                {
                    allSize   =   ( Dem_u32_FFDOutputTotalSizeType )sizeAtFFD;
                }
            }
            else
            {
                /*  retVal : DEM_IRT_WRONG_RECORDNUMBER. */
            }
        }
        else
        {
            /*  get first record number size.           */
            sizeAtFFD   =   ( Dem_u16_FFDStoredIndexType )0U;
            retGetFFD = Dem_UdmData_GetFreezeFrameData( UdmEventIndex, DEM_FFRECNUM_FOR_NONOBD_START, DEM_FFDGETTYPE_SIZE, NULL_PTR, &sizeAtFFD );

            if ( retGetFFD == DEM_IRT_OK )
            {
                allSize       =   ( Dem_u32_FFDOutputTotalSizeType )(( Dem_u32_FFDOutputTotalSizeType )sizeAtFFD * ( Dem_u32_FFDOutputTotalSizeType )triggerFFDCount );   /*  no wrap around.     */

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )   /*  [FuncSw]    */
                /*  get first TSFFD record number size.     */
                tsffdCount  =   Dem_UdmData_GetTSFFStoredRecordNumber( &storedTSFFRecordNumber );
                if ( tsffdCount > (Dem_u16_UdmFFDIndexType)0U )
                {
                    sizeAtFFD   = ( Dem_u16_FFDStoredIndexType )0U;
                    retGetTSFFD = Dem_UdmData_GetFFDataFromTSFF( UdmEventIndex, storedTSFFRecordNumber, DEM_FFDGETTYPE_SIZE, NULL_PTR, &sizeAtFFD );
                    if ( retGetTSFFD == DEM_IRT_OK )
                    {
                        allTSFFDSize  =   ( Dem_u32_FFDOutputTotalSizeType )(( Dem_u32_FFDOutputTotalSizeType )sizeAtFFD * ( Dem_u32_FFDOutputTotalSizeType )tsffdCount );  /*  no wrap around.     */
                        allSize       =   allSize + allTSFFDSize;         /*  no wrap around.     */
                    }
                }

#endif  /*  ( DEM_TSFF_UDM_SUPPORT == STD_ON )          */
            }
            else
            {
                allSize   =   ( Dem_u32_FFDOutputTotalSizeType )0U;
            }
            retVal  =   DEM_IRT_OK;
        }
    }
    else
    {
        allSize   =   ( Dem_u32_FFDOutputTotalSizeType )0U;
        retVal  =   DEM_IRT_OK;
    }

    *SizeOfFreezeFramePtr   =   allSize;

    return retVal;
}


/****************************************************************************/
/* Function Name | Dem_UdmData_CheckRecordNumberInDisabledRecord            */
/* Description   | Checks the specified record number in the disabled reco- */
/*               | rd of temporary area.                                    */
/* Preconditions |                                                          */
/* Parameters    | [in] UdmEventIndex :                                     */
/*               |        The udm event index corresponding to the specifi- */
/*               |        c DTC value.                                      */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |        DEM_IRT_OK : Checking the record number was succ- */
/*               |        essful.                                           */
/*               |        DEM_IRT_NG : Checking the record number was fail- */
/*               |        ed.                                               */
/*               |        DEM_IRT_WRONG_RECORDNUMBER : Retrieving the size  */
/*               |         of freeze frame record was failed.               */
/* Notes         |                                                          */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_UdmData_CheckRecordNumberInDisabledRecord
(
    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) UdmEventIndex,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber /* MISRA DEVIATION */
)
{
    VAR( Dem_u16_FFClassIndexType, AUTOMATIC ) freezeFrameClassRef;

    VAR( Dem_u16_UdmEventIndexType, AUTOMATIC ) udmEventConfigureNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    /* Initializes the return value to NG. */
    retVal = DEM_IRT_NG;

    udmEventConfigureNum = Dem_UdmEventConfigureNum;

    /* Checks the specified event index be within the range. */
    if( UdmEventIndex < udmEventConfigureNum )
    {
        /* Checks the FreezeFrameClass table list Index of the held DTCAttribute table. */
        Dem_CfgInfoUdm_GetFreezeFrameClassRef( UdmEventIndex, &freezeFrameClassRef );

        if( freezeFrameClassRef == DEM_FFCLASSINDEX_INVALID )
        {
            /* The FreezeFrameClass table list Index is invalid. */

            /* Sets the return value to DEM_IRT_WRONG_RECORDNUMBER(Incorrect record number). */
            retVal = DEM_IRT_WRONG_RECORDNUMBER;
        }
        else
        {
            /* The FreezeFrameClass table list Index and the FreezeFrameRecNumClass table list Index are valid. */

            /* Sets the return value to OK. */
            retVal = DEM_IRT_OK;
        }
    }
    else
    {
        /* No process */
    }

    /* Returns with the result. */
    return retVal;
}



#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>


#endif  /* ( DEM_USERDEFINEDMEMORY_SUPPORT == STD_ON )      */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2021-09-28                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
