/* Dem_CmnLib_DataCtl_h(v5-5-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Dem/CmnLib_DataCtl/HEADER                                 */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_CMNLIB_DATACTL_H
#define DEM_CMNLIB_DATACTL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include "../cfg/Dem_Data_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_DC_FFRLEN_RECORDNUM                         ((Dem_u32_FFDStoredIndexType)1U)
#define DEM_DC_FFRLEN_NUMOFDIDS                         ((Dem_u32_FFDStoredIndexType)1U)
#define DEM_DC_FFRLEN_DID_MSB                           ((Dem_u32_FFDStoredIndexType)1U)
#define DEM_DC_FFRLEN_DID_LSB                           ((Dem_u32_FFDStoredIndexType)1U)
#define DEM_DC_FFRLEN_DID                               (DEM_DC_FFRLEN_DID_MSB + DEM_DC_FFRLEN_DID_LSB)
#define DEM_DC_DIDIDENTIFIER_SHIFT                      ((uint8)0x08U)
#define DEM_DC_DIDIDENTIFIER_MASK                       ((Dem_u16_DIDNumberType)0x00FFU)

#define DEM_DC_FFR_PADDING_DATA                         ((uint8)0xFFU)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    Dem_u16_EventStrgIndexType          EventStrgIndex;
    Dem_u16_AllFFDIndexType             FreezeFrameDataIndex;
    Dem_u08_FFRecordNumberType          RecordNumber;
    Dem_u08_FreezeFrameDataType         FreezeFrameDataType;

} Dem_TmpRecordNumberByDTCType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes - PreInit section                                    */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>


#define DEM_STOP_SEC_CODE_TRUST      /*  PreInit section     */
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*  get freezeframe config information      */
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_GetFreezeFrameRecordClassByRecordNumber
(
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameRecNumClassPtr,
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    P2CONST( AB_83_ConstV Dem_FreezeFrameRecordClassType, AUTOMATIC, DEM_CONFIG_DATA ) *FreezeFrameRecordClassPPtr,
    P2VAR( Dem_u08_FFListIndexType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordClassIndexPtr,
    P2VAR( Dem_u08_StorageTriggerType, AUTOMATIC, AUTOMATIC ) FreezeFrameRecordTriggerPtr
);

FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_Data_EditFreezeFrameRecord
(
    VAR( Dem_u08_FFRecordNumberType, AUTOMATIC ) RecordNumber,
    VAR( Dem_u08_FFDGetInfoType, AUTOMATIC ) FreezeFrameGetInfoType,
    P2CONST( uint8, AUTOMATIC, AUTOMATIC ) CapturedDataPtr,
    P2CONST( AB_83_ConstV Dem_FreezeFrameClassType, AUTOMATIC, DEM_CONFIG_DATA ) FreezeFrameClassPtr,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) DataPtr,
    P2VAR( Dem_u16_FFDStoredIndexType, AUTOMATIC, AUTOMATIC ) DataSizePtr
);


/*  sort recordNumber for SID1904/SID1918  */
FUNC( void, DEM_CODE ) Dem_Data_SortSaveRecordNumber
(
    VAR( Dem_u16_FFRecNumStoredIndexType, AUTOMATIC ) NumberOfSaveRecord,
    P2VAR( Dem_TmpRecordNumberByDTCType, AUTOMATIC, DEM_VAR_NO_INIT ) DataPtr
);


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

#endif /* DEM_CMNLIB_DATACTL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
