/* Dem_UserDefMem_Cfg_c(v5-5-0)                                             */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/UserDefMem_Cfg/CODE                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include "Dem_UserDefMem_Cfg.h"
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

CONST( AB_83_ConstV Dem_UdmEventParameterType        ,DEM_CONFIG_DATA ) Dem_UdmEventParameterTable[ DEM_UDMEVENT_CONFIGURE_NUM ] =
{
    /*  DemCallbackEventStatusChangedFnc DemCallbackInitMForEFnc DemDtcValue DemEventAttribute DemDTCAttributesRef DemOperationCycleRef DemEventPriority  */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00AE0100U, 0x0200U, 11U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_B2E01 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00AE0200U, 0x0200U, 12U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_B2E02 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00AE0300U, 0x0200U, 13U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_B2E03 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00AE0400U, 0x0200U, 14U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_B2E04 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00AE0500U, 0x0200U, 15U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_B2E05 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00AE0600U, 0x0200U, 16U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_B2E06 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00AE0700U, 0x0200U, 17U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_B2E07 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00AE0800U, 0x0200U, 18U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_B2E08 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00AE1200U, 0x0200U, 19U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_B2E12 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00AE1500U, 0x0200U, 20U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_B2E15 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00AE2200U, 0x0200U, 22U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_B2E22 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00AE2300U, 0x0200U, 23U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_B2E23 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00AE2400U, 0x0200U, 24U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_B2E24 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00AE2500U, 0x0200U, 25U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_B2E25 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00AE2600U, 0x0200U, 26U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_B2E26 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00AE2700U, 0x0200U, 27U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_B2E27 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00AE2800U, 0x0200U, 28U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_B2E28 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00AE2900U, 0x0200U, 29U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_B2E29 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00AE3000U, 0x0200U, 30U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_B2E30 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00AE2000U, 0x0200U, 21U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_B2E20 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00EA0000U, 0x0200U, 0U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_U2A00 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00EA0100U, 0x0200U, 1U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_U2A01 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00EA1600U, 0x0200U, 2U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_U2A16 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00EA1700U, 0x0200U, 3U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_U2A17 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00EA1300U, 0x0200U, 5U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_U2A13 */
    {  &vd_g_oXDoCANAubIfUdmEvStsChg, NULL_PTR, 0x00EA1200U, 0x0200U, 4U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_U2A12 */
    {  NULL_PTR, NULL_PTR, 0x00E30351U, 0x0200U, 6U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_U2303 */
    {  NULL_PTR, NULL_PTR, 0x00E30257U, 0x0200U, 7U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_U2302 */
    {  NULL_PTR, NULL_PTR, 0x00D3A057U, 0x0200U, 8U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_U13A0 */
    {  NULL_PTR, NULL_PTR, 0x00E30000U, 0x0200U, 9U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  },   /* DemConf_DemEventParameter_DemEventDTC_U2300 */
    {  NULL_PTR, NULL_PTR, 0x00E30100U, 0x0200U, 10U, 0U, DEM_PRIORITY_NONOBD_DEFAULT  }    /* DemConf_DemEventParameter_DemEventDTC_U2301 */
};

CONST( AB_83_ConstV Dem_UdmDTCAttributeType          ,DEM_CONFIG_DATA ) Dem_UdmDTCAttributeTable[ DEM_UDM_DTC_ATT_CONFIGURE_NUM ] =
{
    /*  DemFreezeFrameClassRef DemMaxNumberFreezeFrameRecords DemExtendedDataClassRef DemMemoryDestinationRef  */
    {   5U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 2U   },
    {   6U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 2U   },
    {   1U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 2U   },
    {   2U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 2U   },
    {   3U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 4U   },
    {   4U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 3U   },
    {   0U, 0x0001U, DEM_EXDATACLASSINDEX_INVALID, 5U   },
    {   0U, 0x0001U, DEM_EXDATACLASSINDEX_INVALID, 5U   },
    {   0U, 0x0001U, DEM_EXDATACLASSINDEX_INVALID, 5U   },
    {   7U, 0x0001U, DEM_EXDATACLASSINDEX_INVALID, 6U   },
    {   7U, 0x0001U, DEM_EXDATACLASSINDEX_INVALID, 6U   },
    {   8U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 0U   },
    {   8U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 0U   },
    {   8U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 0U   },
    {   0U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 0U   },
    {   0U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 0U   },
    {   0U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 0U   },
    {   0U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 0U   },
    {   0U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 0U   },
    {   0U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 0U   },
    {   0U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 0U   },
    {   9U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 1U   },
    {   0U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 0U   },
    {   0U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 0U   },
    {   0U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 0U   },
    {   0U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 0U   },
    {   0U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 0U   },
    {   0U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 0U   },
    {   0U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 0U   },
    {   0U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 0U   },
    {   0U, 0x0003U, DEM_EXDATACLASSINDEX_INVALID, 0U   }
};

CONST( AB_83_ConstV Dem_UserDefinedMemoryGroupType            ,DEM_CONFIG_DATA ) Dem_UserDefinedMemoryGroupTable[ DEM_USER_DEFINED_MEMORY_NUM ] =
{
    /*  DemSearchStartIndexOfEventParameterTable DemConfigureEventNumOfMemorySelection DemMaxNumberFreezeFrameUserDefinedPerDTC DemMaxNumberEventEntryUserDefined DemEventDisplacementStrategy DemUserDefinedMemoryInfoTableIndex */
    {   0x0000U,  0x0013U,  0x0003U,  0x13U,  DEM_DISPLACEMENT_PRIO_OCC,  0U  },   /*  RkDemUDM_Occurrence1       */
    {   0x0013U,  0x0001U,  0x0003U,  0x01U,  DEM_DISPLACEMENT_PRIO_OCC,  0U  },   /*  RkDemUDM_Occurrence2       */
    {   0x0014U,  0x0004U,  0x0003U,  0x04U,  DEM_DISPLACEMENT_PRIO_OCC,  0U  },   /*  RkDemUDM_Occurrence2_NM    */
    {   0x0018U,  0x0001U,  0x0003U,  0x01U,  DEM_DISPLACEMENT_PRIO_OCC,  0U  },   /*  RkDemUDM_Occurrence3_NM    */
    {   0x0019U,  0x0001U,  0x0003U,  0x01U,  DEM_DISPLACEMENT_PRIO_OCC,  0U  },   /*  RkDemUDM_Occurrence7_NM    */
    {   0x001AU,  0x0003U,  0x0001U,  0x03U,  DEM_DISPLACEMENT_NONE,      1U  },   /*  RkDemUDM_Maintenance1      */
    {   0x001DU,  0x0002U,  0x0001U,  0x02U,  DEM_DISPLACEMENT_PRIO_OCC,  2U  }    /*  RkDemUDM_SystemOperation2  */
};

CONST( AB_83_ConstV Dem_UserDefinedMemoryInfoTableType        ,DEM_CONFIG_DATA ) Dem_UserDefinedMemoryInfoTable[ DEM_USER_DEFINED_MEMORY_INFO_NUM ] =
{
    /*  DemUserDefinedMemoryKindIndexStart DemUserDefinedMemoryKindIndexNum DemUserDefinedMemoryIdentifier DemDtcStatusAvailabilityMask DemMemoryType */
    {   0U, 5U, 0x11U, 0x39U, DEM_MEMORYTYPE_ASYNCEVENT  },
    {   5U, 1U, 0x12U, 0x39U, DEM_MEMORYTYPE_ASYNCEVENT  },
    {   6U, 1U, 0x13U, 0x39U, DEM_MEMORYTYPE_ASYNCEVENT  }
};

CONST( AB_83_ConstV Dem_u16_UdmEventIndexType        ,DEM_CONFIG_DATA ) Dem_UdmEventConfigureNum            = DEM_UDMEVENT_CONFIGURE_NUM;
CONST( AB_83_ConstV Dem_u16_FFRecNumStoredIndexType  ,DEM_CONFIG_DATA ) Dem_UdmMaxNumberFFPerDTC            = DEM_UDM_MAX_NUMBER_FF_PER_DTC;


#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
