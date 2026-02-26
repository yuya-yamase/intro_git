/* Dem_MM_Cfg_c(v5-5-0)                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
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
        0x0001U,                                                /* DemBlockIndexLast     */
        DEM_EVENT_RECORD_NVBLOCK_SIZE,                          /* DemBlockSize          */
        1U,                                                     /* DemBlockNumPerRecord  */
        DEM_EVENT_RECORD_NVBLOCK_NUM,                           /* DemBlockTotalNum      */
        (void*)&Dem_EventRecordList[0]                          /* DemRamDataFirstPtr    */
    },
    /* FaultRecord */
    {
        0x0002U,                                                /* DemBlockIdFirst       */
        0x0002U,                                                /* DemBlockIndexFirst    */
        0x0003U,                                                /* DemBlockIndexLast     */
        DEM_FAIL_RECORD_NVBLOCK_SIZE,                           /* DemBlockSize          */
        1U,                                                     /* DemBlockNumPerRecord  */
        DEM_FAIL_RECORD_NVBLOCK_NUM,                            /* DemBlockTotalNum      */
        (void*)&Dem_FaultRecordList[0]                          /* DemRamDataFirstPtr    */
    },
    /* FreezeFrameRecord */
    {
        0x0004U,                                                /* DemBlockIdFirst       */
        0x0004U,                                                /* DemBlockIndexFirst    */
        0x0005U,                                                /* DemBlockIndexLast     */
        DEM_FFD_RECORD_NVBLOCK_SIZE,                            /* DemBlockSize          */
        DEM_FREEZE_FRAME_DATA_BLOCK_NUM,                        /* DemBlockNumPerRecord  */
        DEM_FFD_RECORD_NVBLOCK_NUM,                             /* DemBlockTotalNum      */
        (void*)&Dem_FreezeFrameRecordList[0].Data[0]            /* DemRamDataFirstPtr    */
    },
    /* ClrInfoRecord */
    {
        0x0006U,                                                /* DemBlockIdFirst       */
        0x0006U,                                                /* DemBlockIndexFirst    */
        0x0006U,                                                /* DemBlockIndexLast     */
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
/*     0x0002U  0x000CU  (void*)&Dem_FaultRecordList[0]                                                                      */
/*     0x0003U  0x000CU  (void*)&Dem_FaultRecordList[1]                                                                      */
/*     0x0004U  0x0020U  (void*)&Dem_FreezeFrameRecordList[0].Data[0]                                                        */
/*     0x0005U  0x0020U  (void*)&Dem_FreezeFrameRecordList[1].Data[0]                                                        */
/*     0x0006U  0x0004U  (void*)&Dem_ClrInfoRecord                                                                           */
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
/****************************************************************************/
/****************************************************************************/
/* AUBIST Configurator Version                                              */
/*  Framework          :v2-1-0                                              */
/*  BSW plug-in        :v5-5-0                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
