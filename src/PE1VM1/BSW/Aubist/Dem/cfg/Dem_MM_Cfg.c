/* Dem_MM_Cfg_c(v5-6-0)                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/MM_Cfg/CODE                                           */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include "Dem_MM_Cfg.h"
#include "Dem_Data_Cfg.h"
#include "Dem_NvM_Cfg.h"

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

CONST( AB_83_ConstV Dem_RecordInfoType  ,DEM_CONFIG_DATA )  Dem_RecordInfo_NvBlockTable[DEM_MM_NVM_REC_KIND_NUM] =
{
    /* EventRecord */
    {
        0x0000U,                                                /* DemBlockIdFirst       */
        0x0000U,                                                /* DemBlockIndexFirst    */
        0x0014U,                                                /* DemBlockIndexLast     */
        DEM_EVENT_RECORD_NVBLOCK_SIZE,                          /* DemBlockSize          */
        1U,                                                     /* DemBlockNumPerRecord  */
        DEM_EVENT_RECORD_NVBLOCK_NUM,                           /* DemBlockTotalNum      */
        (void*)&Dem_EventRecordList[0]                          /* DemRamDataFirstPtr    */
    },
    /* FaultRecord */
    {
        0x0015U,                                                /* DemBlockIdFirst       */
        0x0015U,                                                /* DemBlockIndexFirst    */
        0x0029U,                                                /* DemBlockIndexLast     */
        DEM_FAIL_RECORD_NVBLOCK_SIZE,                           /* DemBlockSize          */
        1U,                                                     /* DemBlockNumPerRecord  */
        DEM_FAIL_RECORD_NVBLOCK_NUM,                            /* DemBlockTotalNum      */
        (void*)&Dem_FaultRecordList[0]                          /* DemRamDataFirstPtr    */
    },
    /* FreezeFrameRecord */
    {
        0x002AU,                                                /* DemBlockIdFirst       */
        0x002AU,                                                /* DemBlockIndexFirst    */
        0x003EU,                                                /* DemBlockIndexLast     */
        DEM_FFD_RECORD_NVBLOCK_SIZE,                            /* DemBlockSize          */
        DEM_FREEZE_FRAME_DATA_BLOCK_NUM,                        /* DemBlockNumPerRecord  */
        DEM_FFD_RECORD_NVBLOCK_NUM,                             /* DemBlockTotalNum      */
        (void*)&Dem_FreezeFrameRecordList[0].Data[0]            /* DemRamDataFirstPtr    */
    },
    /* ClrInfoRecord */
    {
        0x003FU,                                                /* DemBlockIdFirst       */
        0x003FU,                                                /* DemBlockIndexFirst    */
        0x003FU,                                                /* DemBlockIndexLast     */
        DEM_CLRINFO_RECORD_NVBLOCK_SIZE,                        /* DemBlockSize          */
        1U,                                                     /* DemBlockNumPerRecord  */
        DEM_CLRINFO_RECORD_NVBLOCK_NUM,                         /* DemBlockTotalNum      */
        (void*)&Dem_ClrInfoRecord                               /* DemRamDataFirstPtr    */
    },
    /* Udm_RkDemUDM_Occurrence1_EventRecord */
    {
        0x0040U,                                                /* DemBlockIdFirst       */
        0x0040U,                                                /* DemBlockIndexFirst    */
        0x0052U,                                                /* DemBlockIndexLast     */
        DEM_UDMEVENT_RECORD_NVBLOCK_SIZE,                       /* DemBlockSize          */
        1U,                                                     /* DemBlockNumPerRecord  */
        DEM_UDM_RKDEMUDM_OCCURRENCE1_EVENT_RECORD_NVBLOCK_NUM,                      /* DemBlockTotalNum      */
        (void*)&Dem_Udm_RkDemUDM_Occurrence1_EventRecordList[0]                     /* DemRamDataFirstPtr    */
    },
    /* Udm_RkDemUDM_Occurrence2_EventRecord */
    {
        0x0053U,                                                /* DemBlockIdFirst       */
        0x0053U,                                                /* DemBlockIndexFirst    */
        0x0053U,                                                /* DemBlockIndexLast     */
        DEM_UDMEVENT_RECORD_NVBLOCK_SIZE,                       /* DemBlockSize          */
        1U,                                                     /* DemBlockNumPerRecord  */
        DEM_UDM_RKDEMUDM_OCCURRENCE2_EVENT_RECORD_NVBLOCK_NUM,                      /* DemBlockTotalNum      */
        (void*)&Dem_Udm_RkDemUDM_Occurrence2_EventRecordList[0]                     /* DemRamDataFirstPtr    */
    },
    /* Udm_RkDemUDM_Occurrence2_NM_EventRecord */
    {
        0x0054U,                                                /* DemBlockIdFirst       */
        0x0054U,                                                /* DemBlockIndexFirst    */
        0x0057U,                                                /* DemBlockIndexLast     */
        DEM_UDMEVENT_RECORD_NVBLOCK_SIZE,                       /* DemBlockSize          */
        1U,                                                     /* DemBlockNumPerRecord  */
        DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_EVENT_RECORD_NVBLOCK_NUM,                      /* DemBlockTotalNum      */
        (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_EventRecordList[0]                     /* DemRamDataFirstPtr    */
    },
    /* Udm_RkDemUDM_Occurrence3_NM_EventRecord */
    {
        0x0058U,                                                /* DemBlockIdFirst       */
        0x0058U,                                                /* DemBlockIndexFirst    */
        0x0058U,                                                /* DemBlockIndexLast     */
        DEM_UDMEVENT_RECORD_NVBLOCK_SIZE,                       /* DemBlockSize          */
        1U,                                                     /* DemBlockNumPerRecord  */
        DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_EVENT_RECORD_NVBLOCK_NUM,                      /* DemBlockTotalNum      */
        (void*)&Dem_Udm_RkDemUDM_Occurrence3_NM_EventRecordList[0]                     /* DemRamDataFirstPtr    */
    },
    /* Udm_RkDemUDM_Occurrence7_NM_EventRecord */
    {
        0x0059U,                                                /* DemBlockIdFirst       */
        0x0059U,                                                /* DemBlockIndexFirst    */
        0x0059U,                                                /* DemBlockIndexLast     */
        DEM_UDMEVENT_RECORD_NVBLOCK_SIZE,                       /* DemBlockSize          */
        1U,                                                     /* DemBlockNumPerRecord  */
        DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_EVENT_RECORD_NVBLOCK_NUM,                      /* DemBlockTotalNum      */
        (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_EventRecordList[0]                     /* DemRamDataFirstPtr    */
    },
    /* Udm_RkDemUDM_Maintenance1_EventRecord */
    {
        0x005AU,                                                /* DemBlockIdFirst       */
        0x005AU,                                                /* DemBlockIndexFirst    */
        0x005CU,                                                /* DemBlockIndexLast     */
        DEM_UDMEVENT_RECORD_NVBLOCK_SIZE,                       /* DemBlockSize          */
        1U,                                                     /* DemBlockNumPerRecord  */
        DEM_UDM_RKDEMUDM_MAINTENANCE1_EVENT_RECORD_NVBLOCK_NUM,                      /* DemBlockTotalNum      */
        (void*)&Dem_Udm_RkDemUDM_Maintenance1_EventRecordList[0]                     /* DemRamDataFirstPtr    */
    },
    /* Udm_RkDemUDM_SystemOperation2_EventRecord */
    {
        0x005DU,                                                /* DemBlockIdFirst       */
        0x005DU,                                                /* DemBlockIndexFirst    */
        0x005EU,                                                /* DemBlockIndexLast     */
        DEM_UDMEVENT_RECORD_NVBLOCK_SIZE,                       /* DemBlockSize          */
        1U,                                                     /* DemBlockNumPerRecord  */
        DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_EVENT_RECORD_NVBLOCK_NUM,                      /* DemBlockTotalNum      */
        (void*)&Dem_Udm_RkDemUDM_SystemOperation2_EventRecordList[0]                     /* DemRamDataFirstPtr    */
    },
    /* Udm_RkDemUDM_Occurrence1_FaultRecord */
    {
        0x005FU,                                                /* DemBlockIdFirst       */
        0x005FU,                                                /* DemBlockIndexFirst    */
        0x0071U,                                                /* DemBlockIndexLast     */
        DEM_UDMFAULT_RECORD_NVBLOCK_SIZE,                       /* DemBlockSize          */
        1U,                                                     /* DemBlockNumPerRecord  */
        DEM_UDM_RKDEMUDM_OCCURRENCE1_FAULT_RECORD_NVBLOCK_NUM,                      /* DemBlockTotalNum      */
        (void*)&Dem_Udm_RkDemUDM_Occurrence1_FaultRecordList[0]                     /* DemRamDataFirstPtr    */
    },
    /* Udm_RkDemUDM_Occurrence2_FaultRecord */
    {
        0x0072U,                                                /* DemBlockIdFirst       */
        0x0072U,                                                /* DemBlockIndexFirst    */
        0x0072U,                                                /* DemBlockIndexLast     */
        DEM_UDMFAULT_RECORD_NVBLOCK_SIZE,                       /* DemBlockSize          */
        1U,                                                     /* DemBlockNumPerRecord  */
        DEM_UDM_RKDEMUDM_OCCURRENCE2_FAULT_RECORD_NVBLOCK_NUM,                      /* DemBlockTotalNum      */
        (void*)&Dem_Udm_RkDemUDM_Occurrence2_FaultRecordList[0]                     /* DemRamDataFirstPtr    */
    },
    /* Udm_RkDemUDM_Occurrence2_NM_FaultRecord */
    {
        0x0073U,                                                /* DemBlockIdFirst       */
        0x0073U,                                                /* DemBlockIndexFirst    */
        0x0076U,                                                /* DemBlockIndexLast     */
        DEM_UDMFAULT_RECORD_NVBLOCK_SIZE,                       /* DemBlockSize          */
        1U,                                                     /* DemBlockNumPerRecord  */
        DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_FAULT_RECORD_NVBLOCK_NUM,                      /* DemBlockTotalNum      */
        (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FaultRecordList[0]                     /* DemRamDataFirstPtr    */
    },
    /* Udm_RkDemUDM_Occurrence3_NM_FaultRecord */
    {
        0x0077U,                                                /* DemBlockIdFirst       */
        0x0077U,                                                /* DemBlockIndexFirst    */
        0x0077U,                                                /* DemBlockIndexLast     */
        DEM_UDMFAULT_RECORD_NVBLOCK_SIZE,                       /* DemBlockSize          */
        1U,                                                     /* DemBlockNumPerRecord  */
        DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_FAULT_RECORD_NVBLOCK_NUM,                      /* DemBlockTotalNum      */
        (void*)&Dem_Udm_RkDemUDM_Occurrence3_NM_FaultRecordList[0]                     /* DemRamDataFirstPtr    */
    },
    /* Udm_RkDemUDM_Occurrence7_NM_FaultRecord */
    {
        0x0078U,                                                /* DemBlockIdFirst       */
        0x0078U,                                                /* DemBlockIndexFirst    */
        0x0078U,                                                /* DemBlockIndexLast     */
        DEM_UDMFAULT_RECORD_NVBLOCK_SIZE,                       /* DemBlockSize          */
        1U,                                                     /* DemBlockNumPerRecord  */
        DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_FAULT_RECORD_NVBLOCK_NUM,                      /* DemBlockTotalNum      */
        (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_FaultRecordList[0]                     /* DemRamDataFirstPtr    */
    },
    /* Udm_RkDemUDM_Maintenance1_FaultRecord */
    {
        0x0079U,                                                /* DemBlockIdFirst       */
        0x0079U,                                                /* DemBlockIndexFirst    */
        0x007BU,                                                /* DemBlockIndexLast     */
        DEM_UDMFAULT_RECORD_NVBLOCK_SIZE,                       /* DemBlockSize          */
        1U,                                                     /* DemBlockNumPerRecord  */
        DEM_UDM_RKDEMUDM_MAINTENANCE1_FAULT_RECORD_NVBLOCK_NUM,                      /* DemBlockTotalNum      */
        (void*)&Dem_Udm_RkDemUDM_Maintenance1_FaultRecordList[0]                     /* DemRamDataFirstPtr    */
    },
    /* Udm_RkDemUDM_SystemOperation2_FaultRecord */
    {
        0x007CU,                                                /* DemBlockIdFirst       */
        0x007CU,                                                /* DemBlockIndexFirst    */
        0x007DU,                                                /* DemBlockIndexLast     */
        DEM_UDMFAULT_RECORD_NVBLOCK_SIZE,                       /* DemBlockSize          */
        1U,                                                     /* DemBlockNumPerRecord  */
        DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_FAULT_RECORD_NVBLOCK_NUM,                      /* DemBlockTotalNum      */
        (void*)&Dem_Udm_RkDemUDM_SystemOperation2_FaultRecordList[0]                     /* DemRamDataFirstPtr    */
    },
    /* Udm_RkDemUDM_Occurrence1_FFDRecord */
    {
        0x007EU,                                                /* DemBlockIdFirst       */
        0x007EU,                                                /* DemBlockIndexFirst    */
        0x00B6U,                                                /* DemBlockIndexLast     */
        DEM_UDM_RKDEMUDM_OCCURRENCE1_FFD_RECORD_NVBLOCK_SIZE,                       /* DemBlockSize          */
        DEM_UDM_RKDEMUDM_OCCURRENCE1_FFD_BLOCK_NUM,                                 /* DemBlockNumPerRecord  */
        DEM_UDM_RKDEMUDM_OCCURRENCE1_FFD_RECORD_NVBLOCK_NUM,                        /* DemBlockTotalNum      */
        (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[0].Data[0]       /* DemRamDataFirstPtr    */
    },
    /* Udm_RkDemUDM_Occurrence2_FFDRecord */
    {
        0x00B7U,                                                /* DemBlockIdFirst       */
        0x00B7U,                                                /* DemBlockIndexFirst    */
        0x00BCU,                                                /* DemBlockIndexLast     */
        DEM_UDM_RKDEMUDM_OCCURRENCE2_FFD_RECORD_NVBLOCK_SIZE,                       /* DemBlockSize          */
        DEM_UDM_RKDEMUDM_OCCURRENCE2_FFD_BLOCK_NUM,                                 /* DemBlockNumPerRecord  */
        DEM_UDM_RKDEMUDM_OCCURRENCE2_FFD_RECORD_NVBLOCK_NUM,                        /* DemBlockTotalNum      */
        (void*)&Dem_Udm_RkDemUDM_Occurrence2_FreezeFrameRecordList[0].Data[0]       /* DemRamDataFirstPtr    */
    },
    /* Udm_RkDemUDM_Occurrence2_NM_FFDRecord */
    {
        0x00BDU,                                                /* DemBlockIdFirst       */
        0x00BDU,                                                /* DemBlockIndexFirst    */
        0x00D4U,                                                /* DemBlockIndexLast     */
        DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_FFD_RECORD_NVBLOCK_SIZE,                       /* DemBlockSize          */
        DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_FFD_BLOCK_NUM,                                 /* DemBlockNumPerRecord  */
        DEM_UDM_RKDEMUDM_OCCURRENCE2_NM_FFD_RECORD_NVBLOCK_NUM,                        /* DemBlockTotalNum      */
        (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[0].Data[0]       /* DemRamDataFirstPtr    */
    },
    /* Udm_RkDemUDM_Occurrence3_NM_FFDRecord */
    {
        0x00D5U,                                                /* DemBlockIdFirst       */
        0x00D5U,                                                /* DemBlockIndexFirst    */
        0x00DDU,                                                /* DemBlockIndexLast     */
        DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_FFD_RECORD_NVBLOCK_SIZE,                       /* DemBlockSize          */
        DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_FFD_BLOCK_NUM,                                 /* DemBlockNumPerRecord  */
        DEM_UDM_RKDEMUDM_OCCURRENCE3_NM_FFD_RECORD_NVBLOCK_NUM,                        /* DemBlockTotalNum      */
        (void*)&Dem_Udm_RkDemUDM_Occurrence3_NM_FreezeFrameRecordList[0].Data[0]       /* DemRamDataFirstPtr    */
    },
    /* Udm_RkDemUDM_Occurrence7_NM_FFDRecord */
    {
        0x00DEU,                                                /* DemBlockIdFirst       */
        0x00DEU,                                                /* DemBlockIndexFirst    */
        0x00F2U,                                                /* DemBlockIndexLast     */
        DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_FFD_RECORD_NVBLOCK_SIZE,                       /* DemBlockSize          */
        DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_FFD_BLOCK_NUM,                                 /* DemBlockNumPerRecord  */
        DEM_UDM_RKDEMUDM_OCCURRENCE7_NM_FFD_RECORD_NVBLOCK_NUM,                        /* DemBlockTotalNum      */
        (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[0].Data[0]       /* DemRamDataFirstPtr    */
    },
    /* Udm_RkDemUDM_Maintenance1_FFDRecord */
    {
        0x00F3U,                                                /* DemBlockIdFirst       */
        0x00F3U,                                                /* DemBlockIndexFirst    */
        0x00F5U,                                                /* DemBlockIndexLast     */
        DEM_UDM_RKDEMUDM_MAINTENANCE1_FFD_RECORD_NVBLOCK_SIZE,                       /* DemBlockSize          */
        DEM_UDM_RKDEMUDM_MAINTENANCE1_FFD_BLOCK_NUM,                                 /* DemBlockNumPerRecord  */
        DEM_UDM_RKDEMUDM_MAINTENANCE1_FFD_RECORD_NVBLOCK_NUM,                        /* DemBlockTotalNum      */
        (void*)&Dem_Udm_RkDemUDM_Maintenance1_FreezeFrameRecordList[0].Data[0]       /* DemRamDataFirstPtr    */
    },
    /* Udm_RkDemUDM_SystemOperation2_FFDRecord */
    {
        0x00F6U,                                                /* DemBlockIdFirst       */
        0x00F6U,                                                /* DemBlockIndexFirst    */
        0x00F9U,                                                /* DemBlockIndexLast     */
        DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_FFD_RECORD_NVBLOCK_SIZE,                       /* DemBlockSize          */
        DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_FFD_BLOCK_NUM,                                 /* DemBlockNumPerRecord  */
        DEM_UDM_RKDEMUDM_SYSTEMOPERATION2_FFD_RECORD_NVBLOCK_NUM,                        /* DemBlockTotalNum      */
        (void*)&Dem_Udm_RkDemUDM_SystemOperation2_FreezeFrameRecordList[0].Data[0]       /* DemRamDataFirstPtr    */
    }
};

/*---------------------------------------------------------------------------------------------------------------------------*/
/* Data to be set in NvM_NvMBlockDescriptor                                                                                  */
/* NvMNvramBlockIdentifier, NvMNvBlockLength, NvMRamBlockDataAddress from left to right                                      */
/*---------------------------------------------------------------------------------------------------------------------------*/
/*     0x0000U  0x0008U  (void*)&Dem_EventRecordList[0]                                                                      */
/*     0x0001U  0x0008U  (void*)&Dem_EventRecordList[1]                                                                      */
/*     0x0002U  0x0008U  (void*)&Dem_EventRecordList[2]                                                                      */
/*     0x0003U  0x0008U  (void*)&Dem_EventRecordList[3]                                                                      */
/*     0x0004U  0x0008U  (void*)&Dem_EventRecordList[4]                                                                      */
/*     0x0005U  0x0008U  (void*)&Dem_EventRecordList[5]                                                                      */
/*     0x0006U  0x0008U  (void*)&Dem_EventRecordList[6]                                                                      */
/*     0x0007U  0x0008U  (void*)&Dem_EventRecordList[7]                                                                      */
/*     0x0008U  0x0008U  (void*)&Dem_EventRecordList[8]                                                                      */
/*     0x0009U  0x0008U  (void*)&Dem_EventRecordList[9]                                                                      */
/*     0x000AU  0x0008U  (void*)&Dem_EventRecordList[10]                                                                     */
/*     0x000BU  0x0008U  (void*)&Dem_EventRecordList[11]                                                                     */
/*     0x000CU  0x0008U  (void*)&Dem_EventRecordList[12]                                                                     */
/*     0x000DU  0x0008U  (void*)&Dem_EventRecordList[13]                                                                     */
/*     0x000EU  0x0008U  (void*)&Dem_EventRecordList[14]                                                                     */
/*     0x000FU  0x0008U  (void*)&Dem_EventRecordList[15]                                                                     */
/*     0x0010U  0x0008U  (void*)&Dem_EventRecordList[16]                                                                     */
/*     0x0011U  0x0008U  (void*)&Dem_EventRecordList[17]                                                                     */
/*     0x0012U  0x0008U  (void*)&Dem_EventRecordList[18]                                                                     */
/*     0x0013U  0x0008U  (void*)&Dem_EventRecordList[19]                                                                     */
/*     0x0014U  0x0008U  (void*)&Dem_EventRecordList[20]                                                                     */
/*     0x0015U  0x000CU  (void*)&Dem_FaultRecordList[0]                                                                      */
/*     0x0016U  0x000CU  (void*)&Dem_FaultRecordList[1]                                                                      */
/*     0x0017U  0x000CU  (void*)&Dem_FaultRecordList[2]                                                                      */
/*     0x0018U  0x000CU  (void*)&Dem_FaultRecordList[3]                                                                      */
/*     0x0019U  0x000CU  (void*)&Dem_FaultRecordList[4]                                                                      */
/*     0x001AU  0x000CU  (void*)&Dem_FaultRecordList[5]                                                                      */
/*     0x001BU  0x000CU  (void*)&Dem_FaultRecordList[6]                                                                      */
/*     0x001CU  0x000CU  (void*)&Dem_FaultRecordList[7]                                                                      */
/*     0x001DU  0x000CU  (void*)&Dem_FaultRecordList[8]                                                                      */
/*     0x001EU  0x000CU  (void*)&Dem_FaultRecordList[9]                                                                      */
/*     0x001FU  0x000CU  (void*)&Dem_FaultRecordList[10]                                                                     */
/*     0x0020U  0x000CU  (void*)&Dem_FaultRecordList[11]                                                                     */
/*     0x0021U  0x000CU  (void*)&Dem_FaultRecordList[12]                                                                     */
/*     0x0022U  0x000CU  (void*)&Dem_FaultRecordList[13]                                                                     */
/*     0x0023U  0x000CU  (void*)&Dem_FaultRecordList[14]                                                                     */
/*     0x0024U  0x000CU  (void*)&Dem_FaultRecordList[15]                                                                     */
/*     0x0025U  0x000CU  (void*)&Dem_FaultRecordList[16]                                                                     */
/*     0x0026U  0x000CU  (void*)&Dem_FaultRecordList[17]                                                                     */
/*     0x0027U  0x000CU  (void*)&Dem_FaultRecordList[18]                                                                     */
/*     0x0028U  0x000CU  (void*)&Dem_FaultRecordList[19]                                                                     */
/*     0x0029U  0x000CU  (void*)&Dem_FaultRecordList[20]                                                                     */
/*     0x002AU  0x0020U  (void*)&Dem_FreezeFrameRecordList[0].Data[0]                                                        */
/*     0x002BU  0x0020U  (void*)&Dem_FreezeFrameRecordList[1].Data[0]                                                        */
/*     0x002CU  0x0020U  (void*)&Dem_FreezeFrameRecordList[2].Data[0]                                                        */
/*     0x002DU  0x0020U  (void*)&Dem_FreezeFrameRecordList[3].Data[0]                                                        */
/*     0x002EU  0x0020U  (void*)&Dem_FreezeFrameRecordList[4].Data[0]                                                        */
/*     0x002FU  0x0020U  (void*)&Dem_FreezeFrameRecordList[5].Data[0]                                                        */
/*     0x0030U  0x0020U  (void*)&Dem_FreezeFrameRecordList[6].Data[0]                                                        */
/*     0x0031U  0x0020U  (void*)&Dem_FreezeFrameRecordList[7].Data[0]                                                        */
/*     0x0032U  0x0020U  (void*)&Dem_FreezeFrameRecordList[8].Data[0]                                                        */
/*     0x0033U  0x0020U  (void*)&Dem_FreezeFrameRecordList[9].Data[0]                                                        */
/*     0x0034U  0x0020U  (void*)&Dem_FreezeFrameRecordList[10].Data[0]                                                       */
/*     0x0035U  0x0020U  (void*)&Dem_FreezeFrameRecordList[11].Data[0]                                                       */
/*     0x0036U  0x0020U  (void*)&Dem_FreezeFrameRecordList[12].Data[0]                                                       */
/*     0x0037U  0x0020U  (void*)&Dem_FreezeFrameRecordList[13].Data[0]                                                       */
/*     0x0038U  0x0020U  (void*)&Dem_FreezeFrameRecordList[14].Data[0]                                                       */
/*     0x0039U  0x0020U  (void*)&Dem_FreezeFrameRecordList[15].Data[0]                                                       */
/*     0x003AU  0x0020U  (void*)&Dem_FreezeFrameRecordList[16].Data[0]                                                       */
/*     0x003BU  0x0020U  (void*)&Dem_FreezeFrameRecordList[17].Data[0]                                                       */
/*     0x003CU  0x0020U  (void*)&Dem_FreezeFrameRecordList[18].Data[0]                                                       */
/*     0x003DU  0x0020U  (void*)&Dem_FreezeFrameRecordList[19].Data[0]                                                       */
/*     0x003EU  0x0020U  (void*)&Dem_FreezeFrameRecordList[20].Data[0]                                                       */
/*     0x003FU  0x0008U  (void*)&Dem_ClrInfoRecord                                                                           */
/*     0x0040U  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_EventRecordList[0]                                             */
/*     0x0041U  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_EventRecordList[1]                                             */
/*     0x0042U  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_EventRecordList[2]                                             */
/*     0x0043U  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_EventRecordList[3]                                             */
/*     0x0044U  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_EventRecordList[4]                                             */
/*     0x0045U  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_EventRecordList[5]                                             */
/*     0x0046U  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_EventRecordList[6]                                             */
/*     0x0047U  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_EventRecordList[7]                                             */
/*     0x0048U  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_EventRecordList[8]                                             */
/*     0x0049U  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_EventRecordList[9]                                             */
/*     0x004AU  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_EventRecordList[10]                                            */
/*     0x004BU  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_EventRecordList[11]                                            */
/*     0x004CU  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_EventRecordList[12]                                            */
/*     0x004DU  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_EventRecordList[13]                                            */
/*     0x004EU  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_EventRecordList[14]                                            */
/*     0x004FU  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_EventRecordList[15]                                            */
/*     0x0050U  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_EventRecordList[16]                                            */
/*     0x0051U  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_EventRecordList[17]                                            */
/*     0x0052U  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_EventRecordList[18]                                            */
/*     0x0053U  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_EventRecordList[0]                                             */
/*     0x0054U  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_EventRecordList[0]                                          */
/*     0x0055U  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_EventRecordList[1]                                          */
/*     0x0056U  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_EventRecordList[2]                                          */
/*     0x0057U  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_EventRecordList[3]                                          */
/*     0x0058U  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence3_NM_EventRecordList[0]                                          */
/*     0x0059U  0x0004U  (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_EventRecordList[0]                                          */
/*     0x005AU  0x0004U  (void*)&Dem_Udm_RkDemUDM_Maintenance1_EventRecordList[0]                                            */
/*     0x005BU  0x0004U  (void*)&Dem_Udm_RkDemUDM_Maintenance1_EventRecordList[1]                                            */
/*     0x005CU  0x0004U  (void*)&Dem_Udm_RkDemUDM_Maintenance1_EventRecordList[2]                                            */
/*     0x005DU  0x0004U  (void*)&Dem_Udm_RkDemUDM_SystemOperation2_EventRecordList[0]                                        */
/*     0x005EU  0x0004U  (void*)&Dem_Udm_RkDemUDM_SystemOperation2_EventRecordList[1]                                        */
/*     0x005FU  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FaultRecordList[0]                                             */
/*     0x0060U  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FaultRecordList[1]                                             */
/*     0x0061U  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FaultRecordList[2]                                             */
/*     0x0062U  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FaultRecordList[3]                                             */
/*     0x0063U  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FaultRecordList[4]                                             */
/*     0x0064U  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FaultRecordList[5]                                             */
/*     0x0065U  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FaultRecordList[6]                                             */
/*     0x0066U  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FaultRecordList[7]                                             */
/*     0x0067U  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FaultRecordList[8]                                             */
/*     0x0068U  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FaultRecordList[9]                                             */
/*     0x0069U  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FaultRecordList[10]                                            */
/*     0x006AU  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FaultRecordList[11]                                            */
/*     0x006BU  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FaultRecordList[12]                                            */
/*     0x006CU  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FaultRecordList[13]                                            */
/*     0x006DU  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FaultRecordList[14]                                            */
/*     0x006EU  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FaultRecordList[15]                                            */
/*     0x006FU  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FaultRecordList[16]                                            */
/*     0x0070U  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FaultRecordList[17]                                            */
/*     0x0071U  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FaultRecordList[18]                                            */
/*     0x0072U  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_FaultRecordList[0]                                             */
/*     0x0073U  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FaultRecordList[0]                                          */
/*     0x0074U  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FaultRecordList[1]                                          */
/*     0x0075U  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FaultRecordList[2]                                          */
/*     0x0076U  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FaultRecordList[3]                                          */
/*     0x0077U  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence3_NM_FaultRecordList[0]                                          */
/*     0x0078U  0x0008U  (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_FaultRecordList[0]                                          */
/*     0x0079U  0x0008U  (void*)&Dem_Udm_RkDemUDM_Maintenance1_FaultRecordList[0]                                            */
/*     0x007AU  0x0008U  (void*)&Dem_Udm_RkDemUDM_Maintenance1_FaultRecordList[1]                                            */
/*     0x007BU  0x0008U  (void*)&Dem_Udm_RkDemUDM_Maintenance1_FaultRecordList[2]                                            */
/*     0x007CU  0x0008U  (void*)&Dem_Udm_RkDemUDM_SystemOperation2_FaultRecordList[0]                                        */
/*     0x007DU  0x0008U  (void*)&Dem_Udm_RkDemUDM_SystemOperation2_FaultRecordList[1]                                        */
/*     0x007EU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[0].Data[0]                               */
/*     0x007FU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[1].Data[0]                               */
/*     0x0080U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[2].Data[0]                               */
/*     0x0081U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[3].Data[0]                               */
/*     0x0082U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[4].Data[0]                               */
/*     0x0083U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[5].Data[0]                               */
/*     0x0084U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[6].Data[0]                               */
/*     0x0085U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[7].Data[0]                               */
/*     0x0086U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[8].Data[0]                               */
/*     0x0087U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[9].Data[0]                               */
/*     0x0088U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[10].Data[0]                              */
/*     0x0089U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[11].Data[0]                              */
/*     0x008AU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[12].Data[0]                              */
/*     0x008BU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[13].Data[0]                              */
/*     0x008CU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[14].Data[0]                              */
/*     0x008DU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[15].Data[0]                              */
/*     0x008EU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[16].Data[0]                              */
/*     0x008FU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[17].Data[0]                              */
/*     0x0090U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[18].Data[0]                              */
/*     0x0091U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[19].Data[0]                              */
/*     0x0092U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[20].Data[0]                              */
/*     0x0093U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[21].Data[0]                              */
/*     0x0094U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[22].Data[0]                              */
/*     0x0095U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[23].Data[0]                              */
/*     0x0096U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[24].Data[0]                              */
/*     0x0097U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[25].Data[0]                              */
/*     0x0098U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[26].Data[0]                              */
/*     0x0099U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[27].Data[0]                              */
/*     0x009AU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[28].Data[0]                              */
/*     0x009BU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[29].Data[0]                              */
/*     0x009CU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[30].Data[0]                              */
/*     0x009DU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[31].Data[0]                              */
/*     0x009EU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[32].Data[0]                              */
/*     0x009FU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[33].Data[0]                              */
/*     0x00A0U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[34].Data[0]                              */
/*     0x00A1U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[35].Data[0]                              */
/*     0x00A2U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[36].Data[0]                              */
/*     0x00A3U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[37].Data[0]                              */
/*     0x00A4U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[38].Data[0]                              */
/*     0x00A5U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[39].Data[0]                              */
/*     0x00A6U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[40].Data[0]                              */
/*     0x00A7U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[41].Data[0]                              */
/*     0x00A8U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[42].Data[0]                              */
/*     0x00A9U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[43].Data[0]                              */
/*     0x00AAU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[44].Data[0]                              */
/*     0x00ABU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[45].Data[0]                              */
/*     0x00ACU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[46].Data[0]                              */
/*     0x00ADU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[47].Data[0]                              */
/*     0x00AEU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[48].Data[0]                              */
/*     0x00AFU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[49].Data[0]                              */
/*     0x00B0U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[50].Data[0]                              */
/*     0x00B1U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[51].Data[0]                              */
/*     0x00B2U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[52].Data[0]                              */
/*     0x00B3U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[53].Data[0]                              */
/*     0x00B4U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[54].Data[0]                              */
/*     0x00B5U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[55].Data[0]                              */
/*     0x00B6U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence1_FreezeFrameRecordList[56].Data[0]                              */
/*     0x00B7U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_FreezeFrameRecordList[0].Data[0]                               */
/*     0x00B8U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_FreezeFrameRecordList[0].Data[32]                              */
/*     0x00B9U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_FreezeFrameRecordList[1].Data[0]                               */
/*     0x00BAU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_FreezeFrameRecordList[1].Data[32]                              */
/*     0x00BBU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_FreezeFrameRecordList[2].Data[0]                               */
/*     0x00BCU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_FreezeFrameRecordList[2].Data[32]                              */
/*     0x00BDU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[0].Data[0]                            */
/*     0x00BEU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[0].Data[32]                           */
/*     0x00BFU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[1].Data[0]                            */
/*     0x00C0U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[1].Data[32]                           */
/*     0x00C1U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[2].Data[0]                            */
/*     0x00C2U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[2].Data[32]                           */
/*     0x00C3U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[3].Data[0]                            */
/*     0x00C4U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[3].Data[32]                           */
/*     0x00C5U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[4].Data[0]                            */
/*     0x00C6U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[4].Data[32]                           */
/*     0x00C7U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[5].Data[0]                            */
/*     0x00C8U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[5].Data[32]                           */
/*     0x00C9U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[6].Data[0]                            */
/*     0x00CAU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[6].Data[32]                           */
/*     0x00CBU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[7].Data[0]                            */
/*     0x00CCU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[7].Data[32]                           */
/*     0x00CDU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[8].Data[0]                            */
/*     0x00CEU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[8].Data[32]                           */
/*     0x00CFU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[9].Data[0]                            */
/*     0x00D0U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[9].Data[32]                           */
/*     0x00D1U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[10].Data[0]                           */
/*     0x00D2U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[10].Data[32]                          */
/*     0x00D3U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[11].Data[0]                           */
/*     0x00D4U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence2_NM_FreezeFrameRecordList[11].Data[32]                          */
/*     0x00D5U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence3_NM_FreezeFrameRecordList[0].Data[0]                            */
/*     0x00D6U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence3_NM_FreezeFrameRecordList[0].Data[32]                           */
/*     0x00D7U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence3_NM_FreezeFrameRecordList[0].Data[64]                           */
/*     0x00D8U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence3_NM_FreezeFrameRecordList[1].Data[0]                            */
/*     0x00D9U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence3_NM_FreezeFrameRecordList[1].Data[32]                           */
/*     0x00DAU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence3_NM_FreezeFrameRecordList[1].Data[64]                           */
/*     0x00DBU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence3_NM_FreezeFrameRecordList[2].Data[0]                            */
/*     0x00DCU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence3_NM_FreezeFrameRecordList[2].Data[32]                           */
/*     0x00DDU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence3_NM_FreezeFrameRecordList[2].Data[64]                           */
/*     0x00DEU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[0].Data[0]                            */
/*     0x00DFU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[0].Data[32]                           */
/*     0x00E0U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[0].Data[64]                           */
/*     0x00E1U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[0].Data[96]                           */
/*     0x00E2U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[0].Data[128]                          */
/*     0x00E3U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[0].Data[160]                          */
/*     0x00E4U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[0].Data[192]                          */
/*     0x00E5U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[1].Data[0]                            */
/*     0x00E6U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[1].Data[32]                           */
/*     0x00E7U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[1].Data[64]                           */
/*     0x00E8U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[1].Data[96]                           */
/*     0x00E9U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[1].Data[128]                          */
/*     0x00EAU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[1].Data[160]                          */
/*     0x00EBU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[1].Data[192]                          */
/*     0x00ECU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[2].Data[0]                            */
/*     0x00EDU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[2].Data[32]                           */
/*     0x00EEU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[2].Data[64]                           */
/*     0x00EFU  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[2].Data[96]                           */
/*     0x00F0U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[2].Data[128]                          */
/*     0x00F1U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[2].Data[160]                          */
/*     0x00F2U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Occurrence7_NM_FreezeFrameRecordList[2].Data[192]                          */
/*     0x00F3U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Maintenance1_FreezeFrameRecordList[0].Data[0]                              */
/*     0x00F4U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Maintenance1_FreezeFrameRecordList[1].Data[0]                              */
/*     0x00F5U  0x0020U  (void*)&Dem_Udm_RkDemUDM_Maintenance1_FreezeFrameRecordList[2].Data[0]                              */
/*     0x00F6U  0x0020U  (void*)&Dem_Udm_RkDemUDM_SystemOperation2_FreezeFrameRecordList[0].Data[0]                          */
/*     0x00F7U  0x0020U  (void*)&Dem_Udm_RkDemUDM_SystemOperation2_FreezeFrameRecordList[0].Data[32]                         */
/*     0x00F8U  0x0020U  (void*)&Dem_Udm_RkDemUDM_SystemOperation2_FreezeFrameRecordList[1].Data[0]                          */
/*     0x00F9U  0x0020U  (void*)&Dem_Udm_RkDemUDM_SystemOperation2_FreezeFrameRecordList[1].Data[32]                         */
/*---------------------------------------------------------------------------------------------------------------------------*/



CONST( AB_83_ConstV Dem_u16_NvBlockIndexType       ,DEM_CONFIG_DATA )  Dem_NvMUseNvblockNum        = DEM_NVM_USE_NVBLOCK_NUM;

CONST( AB_83_ConstV uint8                          ,DEM_CONFIG_DATA )  Dem_MMReqAccessNvMMaxCnt    = DEM_MM_REQ_ACCESSNVM_MAXCNT;
CONST( AB_83_ConstV Dem_u32_MMTimeOutCountType     ,DEM_CONFIG_DATA )  Dem_MMReadAllTimeoutCnt     = DEM_MM_READALL_TIMEOUT_CNT;
CONST( AB_83_ConstV Dem_u32_MMTimeOutCountType     ,DEM_CONFIG_DATA )  Dem_MMSingleBlockTimeoutCnt = DEM_MM_SINGLEBLOCK_TIMEOUT_CNT;
CONST( AB_83_ConstV uint16                         ,DEM_CONFIG_DATA )  Dem_MMNvMBlockCheckNum      = DEM_MM_NVM_BLOCK_CHECK_NUM;

CONST( AB_83_ConstV Dem_u16_MMBlockRecKindIndexType    ,DEM_CONFIG_DATA )  Dem_MMNvMRecKindClrInfo     = DEM_MM_NVM_REC_KIND_CLRINFO;

CONST( AB_83_ConstV Dem_u16_MMBlockRecKindIndexType    ,DEM_CONFIG_DATA )  Dem_MMNvMRecKindNum         = DEM_MM_NVM_REC_KIND_NUM;

#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-07-27                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v3-0-0         :2019-07-29                                              */
/*  v4-0-0         :2020-12-23                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/*  v5-6-0         :2024-01-29                                              */
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-10-0                                             */
/****************************************************************************/

/**** End of File ***********************************************************/
