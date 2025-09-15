/* Dem_MM_Cfg_h(v5-5-0)                                                     */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | DEM/MM_Cfg/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef DEM_MM_CFG_H
#define DEM_MM_CFG_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>
#include <Dem/Dem_Common.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Total number of blocks required by record */
#define DEM_EVENT_RECORD_NVBLOCK_NUM      ((Dem_u16_NvBlockIndexType)2U)
#define DEM_FAIL_RECORD_NVBLOCK_NUM       ((Dem_u16_NvBlockIndexType)2U)
#define DEM_FFD_RECORD_NVBLOCK_NUM        ((Dem_u16_NvBlockIndexType)2U)
#define DEM_CLRINFO_RECORD_NVBLOCK_NUM    ((Dem_u16_NvBlockIndexType)1U)

#define DEM_NVM_USE_NVBLOCK_NUM           ((Dem_u16_NvBlockIndexType)7U)

/****************************************************************************/
/* Extended config parameter                                                */
/****************************************************************************/
/* Dem_MM */
#define  DEM_MM_REQ_ACCESSNVM_MAXCNT             ((uint8)0U)
#define  DEM_MM_READALL_TIMEOUT_CNT              ((Dem_u32_MMTimeOutCountType)85899200U)
#define  DEM_MM_SINGLEBLOCK_TIMEOUT_CNT          ((Dem_u32_MMTimeOutCountType)85899200U)
#define  DEM_MM_NVM_BLOCK_CHECK_NUM              ((uint16)7U)

/* NvM Record Kind  */
#define  DEM_MM_NVM_REC_KIND_EVT                 ((Dem_u16_MMBlockRecKindIndexType)DEM_RECORDKIND_PRIMEM_EVENT)
#define  DEM_MM_NVM_REC_KIND_FLT                 ((Dem_u16_MMBlockRecKindIndexType)DEM_RECORDKIND_PRIMEM_FAULT)
#define  DEM_MM_NVM_REC_KIND_FFD                 ((Dem_u16_MMBlockRecKindIndexType)DEM_RECORDKIND_PRIMEM_FFD)
#define  DEM_MM_NVM_REC_KIND_CLRINFO             ((Dem_u16_MMBlockRecKindIndexType)DEM_RECORDKIND_CLRINFO)

#define  DEM_MM_NVM_REC_KIND_NUM                 ((Dem_u16_MMBlockRecKindIndexType)DEM_RECORDKIND_TOTALNUM)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    Dem_BlockIdType                               DemBlockIdFirst;
    Dem_u16_NvBlockIndexType                      DemBlockIndexFirst;
    Dem_u16_NvBlockIndexType                      DemBlockIndexLast;
    Dem_u16_BlockSizeType                         DemBlockSize;
    Dem_u16_NvBlockIndexType                      DemBlockNumPerRecord;
    Dem_u16_NvBlockIndexType                      DemBlockTotalNum;
    P2VAR( void, TYPEDEF, DEM_VAR_SAVED_ZONE )    DemRamDataFirstPtr;
} Dem_RecordInfoType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

extern CONST( AB_83_ConstV Dem_RecordInfoType  ,DEM_CONFIG_DATA)  Dem_RecordInfo_NvBlockTable[DEM_MM_NVM_REC_KIND_NUM];


extern CONST( AB_83_ConstV Dem_u16_NvBlockIndexType       ,DEM_CONFIG_DATA )  Dem_NvMUseNvblockNum;

extern CONST( AB_83_ConstV uint8                          ,DEM_CONFIG_DATA )  Dem_MMReqAccessNvMMaxCnt;
extern CONST( AB_83_ConstV Dem_u32_MMTimeOutCountType     ,DEM_CONFIG_DATA )  Dem_MMReadAllTimeoutCnt;
extern CONST( AB_83_ConstV Dem_u32_MMTimeOutCountType     ,DEM_CONFIG_DATA )  Dem_MMSingleBlockTimeoutCnt;
extern CONST( AB_83_ConstV uint16                         ,DEM_CONFIG_DATA )  Dem_MMNvMBlockCheckNum;

extern CONST( AB_83_ConstV Dem_u16_MMBlockRecKindIndexType    ,DEM_CONFIG_DATA )  Dem_MMNvMRecKindClrInfo;

extern CONST( AB_83_ConstV Dem_u16_MMBlockRecKindIndexType    ,DEM_CONFIG_DATA )  Dem_MMNvMRecKindNum;

#define DEM_STOP_SEC_CONST_CONFIG
#include <Dem_MemMap.h>

#endif  /* DEM_MM_CFG_H */

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
