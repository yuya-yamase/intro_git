/* Dem_h(v5-5-0)                                                            */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/HEADER                                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_H
#define DEM_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <Rte_Dem_Type.h>
#include <Dem/Dem_FuncTypes.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define DEM_DTCSTATUS_AVAILABILITY_MASK                 ((Dem_UdsStatusByteType)0x39U)  /* DemDtcStatusAvailabilityMask */
#define DEM_DTCSEVERITY_AVAILABILITY_MASK               ((Dem_DTCSeverityType)0x02U)  /* DemDtcSeverityAvailabilityMask */
#define DEM_DTCSTATUS_PRODUCT_SUPPORT_BIT               ((Dem_UdsStatusByteType)0x39U)  /* DemDTCStatusProductSupportBit */
#define DEM_TASKTIME_MSEC                               ((uint8)5U)  /* DemTaskTime */
#define DEM_TASKTIME_100USEC                            ((uint16)50U)  /* DemTaskTime */

#define DEM_PRIMEM_EVENT_NUM                            ((Dem_EventIdType)2U)
#define DEM_PRIMEM_EVENTENTRY_MAXNUM                    ((Dem_MaxNumOfEventEntryType)2U)
#define DEM_PRIMEM_DTC_NUM                              ((Dem_EventIdType)2U)

#define DEM_TOTAL_EVENT_NUM                             ((Dem_EventIdType)2U)


/* 01-02 EventID:Ignore the value of DemEventId, Numbering Definition order start from 1 to Define Name and Define Value */
/* Compliant - DemConf_DemEventParameter_ShortName */
#define DemConf_DemEventParameter_DemEventDTC_U0100                                               ((Dem_EventIdType)1U)
#define DemConf_DemEventParameter_DemEventDTC_B1500                                               ((Dem_EventIdType)2U)

/* Compliant - DemConf_DemOperationCycle_ShortName */
#define DemConf_DemOperationCycle_OBD_DCY                                                         ((uint8)0U)
#define DemConf_DemOperationCycle_WARMUP                                                          ((uint8)1U)
#define DemConf_DemOperationCycle_IGCycleCounter                                                  ((uint8)2U)
#define DemConf_DemOperationCycle_PFCCycle                                                        ((uint8)3U)
#define DemConf_DemOperationCycle_RkDemOperationCycle                                             ((uint8)0U)

/* Compliant - DemConf_DemIndicator_ShortName */
#define DemConf_DemIndicator_EcuInd                                                               ((uint8)0xF0U)
#define DemConf_DemIndicator_MILInd                                                               ((uint8)0xF1U)



/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif /* DEM_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-1-0         :2022-07-27                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-0-3-z0003                                        */
/*  BSW plug-in        :v5-5-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
