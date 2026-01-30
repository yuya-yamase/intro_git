/* Dem_EDR_Cfg_h(v5-5-0)                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/EDR_Cfg/HEADER                                        */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_EDR_CFG_H
#define DEM_EDR_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_EX_DATA_CLASS_NUM               ((Dem_u16_ExDataClassIndexType)1U)             /* Number of DemExtendedDataClass           */
#define DEM_EDR_CLASS_REF_NUM               ((Dem_u08_EDRClassRefIndexType)1U)             /* Number of DemExtendedDataRecordClassRef  */
#define DEM_EDR_CLASS_NUM                   ((Dem_u08_EDRClassIndexType)1U)                /* Number of DemExtendedDataRecordClass     */
#define DEM_INTERNAL_DATAELEMENT_NUM        ((Dem_u16_DataElementClassIndexType)1U)        /* Number of internal DataElement functions */

#define DEM_EDR_SUPPORT_RECNUM_NUM          ((Dem_u08_EDRNumberSupBmpIndexType)1U)
#define DEM_EDR_SUPPORT_DTC_NUMBER          ((Dem_u08_EDRSupDTCBmpIndexType)1U)

#define DEM_EDR_SUPPORT_OBDRECORDNUMBER_POS    ((Dem_u08_EDRNumberSupBmpIndexType)DEM_EDRNUMBERSUPBMPINDEX_INVALID)

#define DEM_EDR_SUPPORT_ENDOFBHVRATFE_RECORDNUMBER_POS    ((Dem_u08_EDRNumberSupBmpIndexType)0U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    Dem_u08_EDRClassIndexType            DemEDRClassRef[ DEM_EDR_CLASS_REF_NUM ];
} Dem_ExDataClassType;

typedef struct {
    Dem_u16_DataElementClassIndexType    DemDataElementClassRef;
    Dem_u08_DataElementKindType          DemDataElementKind;
    Dem_u08_EDRRecordNumberType          DemEDRNumber;
} Dem_EDRClassType;

typedef struct {
    DemInternalDataElementReadFncPTR     DemInternalDataElementReadFnc;
} Dem_InternalDataElementClassType;

typedef struct {
    Dem_u08_EDRRecordNumberType          ExtendDataRecordNumber;
    uint8                                Reserve;
    Dem_u16_EventStrgIndexType           SupportDTCNumber;
    uint32                               SupportDTCBitmapTable[ DEM_EDR_SUPPORT_DTC_NUMBER ];
} Dem_EDRNumberSupportBitmapType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

#ifndef JGXSTACK
#else /* JGXSTACK */
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_InternalDataElementReadFnc_ForStack
(
    VAR( Dem_u16_EventCtrlIndexType, AUTOMATIC ) EventCtrlIndex,
    VAR( Dem_u32_DTCValueType, AUTOMATIC ) DTCValue,
    VAR( Dem_u08_GetExtendDataModeType, AUTOMATIC ) GetExtendDataMode,
    P2VAR( uint8, AUTOMATIC, DEM_APPL_DATA ) BufferPtr,
    P2VAR( Dem_u16_EDRRecordSizeType, AUTOMATIC, AUTOMATIC ) BufSizePtr
);
#endif /* JGXSTACK */

#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

extern CONST( AB_83_ConstV Dem_ExDataClassType                 ,DEM_CONFIG_DATA ) Dem_ExDataClassTable[ DEM_EX_DATA_CLASS_NUM ];
extern CONST( AB_83_ConstV Dem_EDRClassType                    ,DEM_CONFIG_DATA ) Dem_EDRClassTable[ DEM_EDR_CLASS_NUM ];
extern CONST( AB_83_ConstV Dem_InternalDataElementClassType    ,DEM_CONFIG_DATA ) Dem_InternalDataElementClassTable[ DEM_INTERNAL_DATAELEMENT_NUM ];
extern CONST( AB_83_ConstV Dem_EDRNumberSupportBitmapType      ,DEM_CONFIG_DATA ) Dem_EDRNumberSupportBitmapTable[ DEM_EDR_SUPPORT_RECNUM_NUM ];

extern CONST( AB_83_ConstV Dem_u16_ExDataClassIndexType        ,DEM_CONFIG_DATA ) Dem_ExDataClassNum;
extern CONST( AB_83_ConstV Dem_u08_EDRClassRefIndexType        ,DEM_CONFIG_DATA ) Dem_EDRClassRefNum;
extern CONST( AB_83_ConstV Dem_u08_EDRClassIndexType           ,DEM_CONFIG_DATA ) Dem_EDRClassNum;

extern CONST( AB_83_ConstV Dem_u08_EDRNumberSupBmpIndexType    ,DEM_CONFIG_DATA ) Dem_EDRSupportRecNumNum;
extern CONST( AB_83_ConstV Dem_u08_EDRSupDTCBmpIndexType       ,DEM_CONFIG_DATA ) Dem_EDRSupportDTCNumber;

extern CONST( AB_83_ConstV Dem_u08_EDRNumberSupBmpIndexType    ,DEM_CONFIG_DATA ) Dem_EDRSupportObdRecordNumberPos;

extern CONST( AB_83_ConstV Dem_u08_EDRNumberSupBmpIndexType    ,DEM_CONFIG_DATA ) Dem_EDRSupportEndOfBehaviorAt0xFERecordNumberPos;

#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

#endif /* DEM_EDR_CFG_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
