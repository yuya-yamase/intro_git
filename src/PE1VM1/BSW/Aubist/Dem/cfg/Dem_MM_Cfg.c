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
/*     0x003FU  0x0004U  (void*)&Dem_ClrInfoRecord                                                                           */
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
