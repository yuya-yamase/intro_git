/* Dem_DataCtl_SamplingFFDAccess_c(v5-7-0)                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/DataCtl_SamplingFFDAccess/CODE                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

#include "../../../cfg/Dem_NvM_Cfg.h"
#include "../../../cfg/Dem_Cfg.h"
#include "../../../inc/Dem_CmnLib_DataCtl_SamplingFFDAccess.h"

#include "Dem_DataCtl_SamplingFFRecordTable.h"

#if ( DEM_TSFF_SUPPORT == STD_ON )

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

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
/* External Functions                                                       */
/****************************************************************************/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/****************************************************************************/
/* Function Name | Dem_Data_GetSamplingFreezeFrameRecordDataPtr             */
/* Description   | Calculates the pointer of the list of sampling freeze f- */
/*               | frame record by the specified SamplingFreezeFrameMemory- */
/*               | Ref and SamplingFreezeFrameRecordIndex.                  */
/* Preconditions | The specified SamplingFreezeFrameMemoryRef and FreezeFr- */
/*               | ameRecordIndex shall be within the range of each maximul */
/*               | size.                                                    */
/* Parameters    | [in] SamplingFreezeFrameMemoryRef                        */
/*               |        Index of sampling freeze frame record table.      */
/*               | [in] SamplingFreezeFrameRecordIndex :                    */
/*               |        The sampling freeze frame list index correspondi- */
/*               |        ng to the specific FreezeFrame record.            */
/* Return Value  | uint8 *                                                  */
/*               |        NULL_PTR : The calculation was failed             */
/*               |        not NULL_PTR : The calculation was successful     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:RET:Not NULL_PTR ] SamplingFreezeFrameMemoryRef     */
/* VariableGuard | [GUD:RET:Not NULL_PTR ] SamplingFreezeFrameRecordIndex   */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/*   v5-6-0      | no object changed.                                       */
/*   v5-7-0      | no object changed.                                       */
/****************************************************************************/
FUNC_P2VAR( uint8, DEM_VAR_NO_INIT, DEM_CODE ) Dem_Data_GetSamplingFreezeFrameRecordDataPtr
(
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) SamplingFreezeFrameMemoryRef,
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) SamplingFreezeFrameRecordIndex
)
{
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) smplFFRecordTableNum;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) smplFFDRecordNum;
    VAR( Dem_u16_UdmFFDIndexType, AUTOMATIC ) ffdStoredFormatSize;
    VAR( uint32, AUTOMATIC ) udmFFDOffset;
    P2VAR( uint8, AUTOMATIC, DEM_VAR_NO_INIT ) samplingFreezeFrameRecordDataPtr;

    samplingFreezeFrameRecordDataPtr = NULL_PTR;

    smplFFRecordTableNum = Dem_SamplingFFRecordMemoryNum;
    if( SamplingFreezeFrameMemoryRef < smplFFRecordTableNum )                                                       /* [GUD:if]SamplingFreezeFrameMemoryRef */
    {
        smplFFDRecordNum = Dem_SamplingFreezeFrameRecordTable[SamplingFreezeFrameMemoryRef].DemFFDRecordNum;        /* [GUD]SamplingFreezeFrameMemoryRef */
        if( SamplingFreezeFrameRecordIndex < smplFFDRecordNum )                                                     /* [GUD:if]SamplingFreezeFrameRecordIndex */
        {
            samplingFreezeFrameRecordDataPtr = Dem_SamplingFreezeFrameRecordTable[SamplingFreezeFrameMemoryRef].DemFreezeFrameRecordListStartDataPtr;   /* [GUD]SamplingFreezeFrameMemoryRef */
            ffdStoredFormatSize = Dem_SamplingFreezeFrameRecordTable[SamplingFreezeFrameMemoryRef].DemFFDStoredFormatSize;                              /* [GUD]SamplingFreezeFrameMemoryRef *//* [GUD:CFG:IF_GUARDED: SamplingFreezeFrameMemoryRef ]ffdStoredFormatSize */

            udmFFDOffset = (uint32)( (uint32)ffdStoredFormatSize * (uint32)SamplingFreezeFrameRecordIndex );/* no wrap around */                        /* [GUD:CFG:IF_GUARDED: ffdStoredFormatSize,SamplingFreezeFrameRecordIndex ]udmFFDOffset */

            samplingFreezeFrameRecordDataPtr = &samplingFreezeFrameRecordDataPtr[udmFFDOffset];                                                         /* [GUD]udmFFDOffset *//* [ARYCHK] (ffdStoredFormatSize*smplFFDRecordNum) / 1 / udmFFDOffset */
        }
    }

    return samplingFreezeFrameRecordDataPtr;
}

/****************************************************************************/
/* Function Name | Dem_Data_GetSamplingFreezeFrameRecordPosition            */
/* Description   | Gets the position information of sampling freeze frame   */
/*               | record.                                                  */
/* Preconditions | The specified SamplingFreezeFrameMemoryRef shall be wit- */
/*               | hin the range of each maximul size.                      */
/* Parameters    | [in] SamplingFreezeFrameMemoryRef                        */
/*               |        Index of sampling freeze frame record table.      */
/*               | [out] SamplingFreezeFrameRecordPosPtr :                  */
/*               |        The pointer of position information for sampling  */
/*               |        freeze frame record.                              */
/* Return Value  | void                                                     */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* VariableGuard | [GUD:OUT:IF_GUARDED: SamplingFreezeFrameMemoryRef ] SamplingFreezeFrameRecordPosPtr  */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( void, DEM_CODE ) Dem_Data_GetSamplingFreezeFrameRecordPosition
(
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) SamplingFreezeFrameMemoryRef,
    P2VAR( Dem_SamplingFreezeFrameRecordPosType, AUTOMATIC, AUTOMATIC ) SamplingFreezeFrameRecordPosPtr
)
{
#if ( DEM_TSFF_PM_SUPPORT == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) primaryMemoryNum;
#endif /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )  /*  [FuncSw]    */
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) userDefinedMemoryNum;

    userDefinedMemoryNum = (Dem_u16_SmpRecMemIndexType)Dem_UserDefinedMemoryNum;
    if( SamplingFreezeFrameMemoryRef < userDefinedMemoryNum )                                               /* [GUD:if]SamplingFreezeFrameMemoryRef */
    {
        SamplingFreezeFrameRecordPosPtr->RecordStatus = Dem_UdmTimeSeriesFreezeFrameDataPosTable[SamplingFreezeFrameMemoryRef].RecordStatus;    /* [GUD]SamplingFreezeFrameMemoryRef */
        SamplingFreezeFrameRecordPosPtr->DataStart = Dem_UdmTimeSeriesFreezeFrameDataPosTable[SamplingFreezeFrameMemoryRef].DataStart;          /* [GUD]SamplingFreezeFrameMemoryRef */
    }
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */

#if ( DEM_TSFF_PM_SUPPORT == STD_ON )  /*  [FuncSw]    */
    primaryMemoryNum    =   Dem_SamplingFFRecordPrimaryMemory;
    if( SamplingFreezeFrameMemoryRef == primaryMemoryNum )                                                  /* [GUD:if]SamplingFreezeFrameMemoryRef */
    {
        SamplingFreezeFrameRecordPosPtr->RecordStatus = Dem_TimeSeriesFreezeFrameDataPosTable.RecordStatus;
        SamplingFreezeFrameRecordPosPtr->DataStart = Dem_TimeSeriesFreezeFrameDataPosTable.DataStart;
    }
#endif /* ( DEM_TSFF_PM_SUPPORT == STD_ON ) */

    return;
}

#if ( DEM_TSFF_UDM_SUPPORT == STD_ON )
/****************************************************************************/
/* Function Name | Dem_Data_GetSamplingFFDRecordNum                         */
/* Description   | Gets the number of sampling freeze frame records corres- */
/*               | ponding to the specific SamplingFreezeFrameMemoryRef.    */
/*               | record.                                                  */
/* Preconditions | The specified SamplingFreezeFrameMemoryRef shall be wit- */
/*               | hin the range of each maximul size.                      */
/* Parameters    | [in] SamplingFreezeFrameMemoryRef                        */
/*               |        Index of sampling freeze frame record table.      */
/* Return Value  | Dem_u16_SmpTSFFDIndexType                                */
/*               |        The number of sampling freeze frame records.      */
/* Notes         |                                                          */
/*--------------------------------------------------------------------------*/
/* History       |                                                          */
/*   v5-5-0      | no object changed.                                       */
/****************************************************************************/
FUNC( Dem_u16_SmpTSFFDIndexType, DEM_CODE ) Dem_Data_GetSamplingFFDRecordNum
(
    VAR( Dem_u16_SmpRecMemIndexType, AUTOMATIC ) SamplingFreezeFrameMemoryRef           /* [PRMCHK:CALLER] */
)
{
    VAR( Dem_u16_SmpTSFFDIndexType, AUTOMATIC ) ffdRecordNum;

    ffdRecordNum = Dem_SamplingFreezeFrameRecordTable[SamplingFreezeFrameMemoryRef].DemFFDRecordNum;        /* [GUDCHK:CALLER]SamplingFreezeFrameMemoryRef */

    return ffdRecordNum;
}
#endif /* ( DEM_TSFF_UDM_SUPPORT == STD_ON ) */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif  /* (DEM_TSFF_SUPPORT == STD_ON) */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
