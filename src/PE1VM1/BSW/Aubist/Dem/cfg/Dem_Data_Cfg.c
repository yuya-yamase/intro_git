/* Dem_Data_Cfg_c(v5-10-0)                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/Data_Cfg/CODE                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include "../cfg/Dem_Data_Cfg.h"
#include "../cfg/Dem_Rte_Connector_Cfg.h"


/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

CONST( AB_83_ConstV Dem_DataElementClassType,DEM_CONFIG_DATA) Dem_DataElementClassTable[DEM_DATAELEMENT_NUM] =
{
    /*  DemDataElementSize  */
          /*  DemDataElementReadFnc   */
    {   7U, &u1_g_oXDoCANAubIfTripcnt  },
    {   4U, &u1_g_oXDoCANAubIfOdo  },
    {   6U, &u1_g_oXDoCANAubIfGmt  }
};

CONST( AB_83_ConstV Dem_DidClassType                ,DEM_CONFIG_DATA )  Dem_DIDClassTable[ DEM_DID_NUM ] =
{
    /*  DemDidIdentifier DemDidDataSize  */
        /*  DemDataElementClassNum DemDataElementClassRef  */
    {   0xA800U, 7U, 1U, {    0U  }  },
    {   0xA002U, 6U, 1U, {    2U  }  },
    {   0xA003U, 4U, 1U, {    1U  }  }
};

CONST( AB_83_ConstV Dem_FreezeFrameClassType        ,DEM_CONFIG_DATA )  Dem_FreezeFrameClassTable[ DEM_DTC_FFR_CLASS_CONFIGURE_NUM ] =
{
    /*  DemFreezeFrameReadFnc DemDidClassRef DemDidClassNum DemDidClassSize  */
    {   NULL_PTR, {   0U, 1U, 2U  }, 3U, 17U  }
};

CONST( AB_83_ConstV Dem_DTCAttributeType            ,DEM_CONFIG_DATA )  Dem_DTCAttributeTable[ DEM_DTC_ATT_CONFIGURE_NUM + (uint16)1U ] =
{
    /*  DemFreezeFrameClassRef DemFreezeFrameRecNumClassRef  */
        /*  DemExtendedDataClassRef  */
            /*  DemAgingCycleCounterThreshold DemAgingAllowed  */
    {   0U, 0U, DEM_EXDATACLASSINDEX_INVALID, 0xFFU, (boolean)FALSE   },
    {   0U, 0U, DEM_EXDATACLASSINDEX_INVALID, 0xFFU, (boolean)FALSE   },
    {   DEM_FFCLASSINDEX_INVALID, DEM_FFRECNUMCLASSINDEX_INVALID, DEM_EXDATACLASSINDEX_INVALID, 0xFFU, (boolean)FALSE   }
};

CONST( AB_83_ConstV Dem_EventParameterType,DEM_CONFIG_DATA) Dem_EventParameterTable[ DEM_PRIMEM_EVENT_NUM ] =
{
    /*  DemCallbackEventStatusChangedFnc DemCallbackInitMForEFnc  */
        /*  DemEventAttribute  */
            /*  DemOperationCycleRef DemHealingAgingCycleRef  */
    {     NULL_PTR,    NULL_PTR,    0x0200U,    0U,    0U   },   /* DemConf_DemEventParameter_DemEventDTC_U0100 */
    {     NULL_PTR,    NULL_PTR,    0x0200U,    0U,    0U   }    /* DemConf_DemEventParameter_DemEventDTC_B1500 */
};

CONST( AB_83_ConstV Dem_EventParameterStorageType,DEM_CONFIG_DATA) Dem_EventParameterStorageTable[ DEM_PRIMEM_EVENTSTORAGE_NUM ] =
{
    /*  DemDtcValue  */
        /*  DemEventAttribute DemDTCAttributesRef  */
                /*  DemDTCClass  */
                    /*  DemIndicatorHealingCycleCounterThreshold  */
                        /*  DemEventPriority  */
    {    0x00C10087U,    0x0200U,    0U,    DEM_SEVERITY_NO_SEVERITY,    255U,    DEM_PRIORITY_NONOBD_DEFAULT   },   /* DemConf_DemEventParameter_DemEventDTC_U0100 */
    {    0x00950013U,    0x0200U,    1U,    DEM_SEVERITY_NO_SEVERITY,    255U,    DEM_PRIORITY_NONOBD_DEFAULT   }    /* DemConf_DemEventParameter_DemEventDTC_B1500 */
};

CONST( AB_83_ConstV Dem_FreezeFrameRecNumClassType,DEM_CONFIG_DATA )  Dem_FreezeFrameRecNumClassTable[ DEM_FFR_REC_NUM_CLASS_CONFIGURE_NUM ] =
{
    /*    DemFreezeFrameRecordClassIndex - 0xFF is data not exist -  */
    {  {   0x00U  }  }
};

CONST( AB_83_ConstV Dem_FreezeFrameRecordClassType,DEM_CONFIG_DATA)  Dem_FreezeFrameRecordClassTable[DEM_FFR_RECORD_CLASS_CONFIGURE_NUM] =
{
    /*  DemFreezeFrameRecordNumber DemFreezeFrameRecordTrigger DemFreezeFrameRecordUpdate DemFreezeFrameRecordToDcm */
    {   1U, DEM_TRIGGER_ON_CONFIRMED, DEM_UPDATE_RECORD_NO, TRUE  }
};

CONST( AB_83_ConstV Dem_u08_FFRecordClassIndexType     ,DEM_CONFIG_DATA )  Dem_FFRRecordClassConfigureNum           = DEM_FFR_RECORD_CLASS_CONFIGURE_NUM;

CONST( AB_83_ConstV Dem_u08_FFListIndexType            ,DEM_CONFIG_DATA )  Dem_FFRecordClassRefMaxNum               = DEM_FF_RECORD_CLASS_REF_MAX_NUM;

CONST( AB_83_ConstV Dem_u16_EventStrgIndexType         ,DEM_CONFIG_DATA )  Dem_ObdEventNum                          = DEM_OBD_EVENT_CONFIGURE_NUM;

CONST( AB_83_ConstV Dem_u16_FFDStoredIndexType         ,DEM_CONFIG_DATA )  Dem_FFRMaxLength                         = DEM_FFR_MAX_LENGTH;

CONST( AB_83_ConstV Dem_u08_FFDIndexType               ,DEM_CONFIG_DATA )  Dem_ObdFFDRecordNum                      = DEM_OBD_FFD_RECORD_NUM;
CONST( AB_83_ConstV Dem_u08_FFDIndexType               ,DEM_CONFIG_DATA )  Dem_NonObdFFDRecordNum                   = DEM_NON_OBD_FFD_RECORD_NUM;

CONST( AB_83_ConstV Dem_u16_FFRecNumStoredIndexType    ,DEM_CONFIG_DATA )  Dem_TotalNumOfRecNumPerDTC               = DEM_TOTAL_NUM_OF_RECNUM_PER_DTC;

CONST( AB_83_ConstV Dem_u16_TSFFDIndexType             ,DEM_CONFIG_DATA )  Dem_TSFFTotalTimeseriesFFRecordNum       = DEM_TSFF_TOTAL_TIMESERIES_FF_RECORD_NUM;

#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-07-27                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-05-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/*  v5-7-0         :2024-05-29                                              */
/*  v5-8-0         :2024-10-29                                              */
/*  v5-9-0         :2025-02-26                                              */
/*  v5-10-0        :2025-06-26                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
