/* Dem_DTR_ReadDTCBased_Misfire_c(v5-8-0)                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DTR_ReadDTCBased_Misfire/CODE                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_DTR_EDR_SUPPORT == STD_ON )
#if ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON )
#include "../../../cfg/Dem_Misfire_Cfg.h"
#include "../../../inc/Dem_CmnLib_CmbEvt.h"
#include "../../../inc/Dem_CmnLib_ConfigInfo.h"
#include "../../../inc/Dem_Pm_DTR.h"
#include "../../../inc/Dem_CmnLib_Control.h"
#include "Dem_DTR_ReadDTCBased.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/****************************************************************************/
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>


/****************************************************************************/
/* Function Name | Dem_DTR_ReadDTCBasedTestResultForCylinder                */
/* Description   | Read DTC Based Test Result for Cylinder                  */
/* Preconditions | none                                                     */
/* Parameters    | [in]     DTCValue                                        */
/*               | [in]     ExecClearDTC                                    */
/*               | [in]     DTCOriginInClear                                */
/*               | [in]     BufSizeIn                                       */
/*               | [out]    TestResultNumPtr                                */
/*               | [out]    BufDtrWriteIndexPtr                             */
/*               | [out]    BufferPtr                                       */
/* Return Value  | Dem_u08_InternalReturnType                               */
/*               |       DEM_IRT_OK : success                               */
/*               |       DEM_IRT_WRONG_RECORDNUMBER : wrong recordnumber    */
/*               |       DEM_IRT_WRONG_BUFFERSIZE : buffer size overflow    */
/* Notes         | -                                                        */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-8-0      | new created.                                             */
/****************************************************************************/
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_DTR_ReadDTCBasedTestResultForCylinder
(
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( boolean, AUTOMATIC ) ExecClearDTC,
    VAR( Dem_DTCOriginType, AUTOMATIC ) DTCOriginInClear,
    VAR( uint16, AUTOMATIC ) BufSizeIn,
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) TestResultNumPtr,
    P2VAR( uint16, AUTOMATIC, AUTOMATIC ) BufDtrWriteIndexPtr,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) BufferPtr
)
{
    VAR( Dem_u16_DtrOutputEdrTableIndexType, AUTOMATIC ) dtrOutputEdrTableIndex;
    VAR( Dem_u16_DtrOutputEdrTableIndexType, AUTOMATIC ) dtrOutputEdrTable_CylinderStartIndex;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNumber;
    VAR( Dem_MisfireCylinderNumberType, AUTOMATIC ) misfireCylinderNum;
    VAR( Dem_u08_InternalReturnType, AUTOMATIC ) retVal;

    retVal = DEM_IRT_WRONG_RECORDNUMBER;
    misfireCylinderNum = Dem_MisfireCylinderNum;
    dtrOutputEdrTable_CylinderStartIndex = Dem_DtrOutputEdrTable_CylinderStartIndex;

    if( dtrOutputEdrTable_CylinderStartIndex != DEM_DTROUTPUTEDRTABLEINDEX_INVALID )
    {
        /* When misfire cylinder is configured in DTR */
        misfireCylinderNumber = Dem_CfgInfoPm_GetMisfireCylinderNumberByUdsDTC( DTCValue );
        if( misfireCylinderNumber < misfireCylinderNum )
        {
            dtrOutputEdrTableIndex = dtrOutputEdrTable_CylinderStartIndex + (Dem_u16_DtrOutputEdrTableIndexType)misfireCylinderNumber;  /* [GUD:CFG]dtrOutputEdrTableIndex */
            retVal = Dem_DTR_GetCurrentDTCBasedTestResult( dtrOutputEdrTableIndex, ExecClearDTC, DTCOriginInClear, BufSizeIn, TestResultNumPtr, BufDtrWriteIndexPtr, BufferPtr );
        }
    }

    return retVal;
}

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* ( DEM_MISFIRE_EVENT_CONFIGURED == STD_ON ) */
#endif  /* ( DEM_DTR_EDR_SUPPORT == STD_ON )    */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-8-0         :2024-10-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

