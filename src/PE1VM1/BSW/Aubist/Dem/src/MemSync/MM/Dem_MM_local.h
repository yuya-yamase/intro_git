/* Dem_MM_local_h(v5-5-0)                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | Dem/MM_local/HEADER                                       */
/*--------------------------------------------------------------------------*/
/* Notes       |                                                            */
/****************************************************************************/

#ifndef DEM_MM_LOCAL_H
#define DEM_MM_LOCAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Dem.h>

#if ( DEM_NVM_SYNC_PROCESS_ENABLE == STD_ON )
#include "../../../usr/Dem_NvM_If_Connector.h"
#include "../../../usr/Dem_NvM_Connector.h"
#include "../../../usr/Dem_NvM_If_Connector.h"
#include "../../../usr/Dem_NvM_Connector.h"
#include "../../../usr/Dem_NotifyError_Callout.h"
#include "../../../cfg/Dem_MM_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
typedef uint8       Dem_u08_MMWriteExecType;        /*  write process mode  */
typedef uint8       Dem_u08_MMBlockStatusType;      /*  block status        */

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/****************/
/* Status       */
/****************/
#define DEM_MM_BLK_STS_INITIAL_VALUE          ((Dem_u08_MMBlockStatusType)0x00U)

/****************/
/* Data Initial */
/****************/
#define DEM_MM_RETRYCNT_INITIAL_VALUE               ((Dem_u08_MMRetryCountType)0x00U)
#define DEM_MM_TIMEOUTCNT_INITIAL_VALUE             ((Dem_u32_MMTimeOutCountType)0x00000000U)

#define DEM_MM_INDEX_INITIAL_VALUE                  ((Dem_u16_NvBlockIndexType)0U)

#define DEM_MM_WRITEEXEC_IDLE               ((Dem_u08_MMWriteExecType)0x00U)
#define DEM_MM_WRITEEXEC_PROCESSING         ((Dem_u08_MMWriteExecType)0x11U)
#define DEM_MM_WRITEEXEC_COMPLETE           ((Dem_u08_MMWriteExecType)0x22U)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct
{
    Dem_BlockIdType                               DemNvRamBlockId;          /* DemNvRamBlockId */
    Dem_u16_BlockSizeType                         DemNvBlockLength;         /* NvMBlockDescriptor_NvMNvBlockLength */
    P2VAR( uint8, TYPEDEF, DEM_VAR_SAVED_ZONE )   DemRamBlockDataAddress;   /* NvMBlockDescriptor_NvMRamBlockDataAddress */
    Dem_u16_MMBlockRecKindIndexType               BlockRecordKind;

} Dem_NvBlockType;     /*   NvBlock information - ROM -   */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define DEM_START_SEC_CODE
#include <Dem_MemMap.h>

/*----------------------*/
/*  Block Write         */
/*----------------------*/
FUNC( void, DEM_CODE ) Dem_MM_InitBlockWriteStatus
( void );
FUNC( Dem_u08_MMWriteExecType, DEM_CODE ) Dem_MM_ProcessIdle
( void );
FUNC( Dem_u08_MMWriteExecType, DEM_CODE ) Dem_MM_ProcessRequest
( void );


/*----------------------*/
/*  Block Read          */
/*----------------------*/
FUNC( void, DEM_CODE ) Dem_MM_InitBlockReadStatus
( void );
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MM_CheckNvBlockStatus
( void );

/*----------------------*/
/*  Block Table         */
/*----------------------*/
FUNC( void, DEM_CODE ) Dem_MM_GetNvBlockIndex
(
    VAR( Dem_u16_RecordIndexType, AUTOMATIC ) RecIndex,
    VAR( Dem_u16_RecordDataSizeType, AUTOMATIC ) DataOffset,
    VAR( Dem_u16_MMBlockRecKindIndexType, AUTOMATIC ) BlockRecordKind,
    P2VAR( Dem_u16_NvBlockIndexType, AUTOMATIC, AUTOMATIC ) ListIndexPtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MM_GetNvBlockInfo
(
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) ListIndex,
    P2VAR( Dem_NvBlockType, AUTOMATIC, AUTOMATIC ) NvBlockTypePtr
);
FUNC( Dem_u08_InternalReturnType, DEM_CODE ) Dem_MM_JudgmentErrorStatus
(
    VAR( Dem_NvM_RequestResultType, AUTOMATIC ) ErrorStatus
);

/*----------------------*/
/*  Block Status        */
/*----------------------*/
FUNC( void, DEM_CODE ) Dem_MM_InitNvBlockStatusOfList
( void );
FUNC( void, DEM_CODE ) Dem_MM_SetNvBlockStatusOfList
(
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) ListIndex,
    VAR( Dem_u08_MMBlockStatusType, AUTOMATIC ) Status
);
FUNC( Dem_u08_MMBlockStatusType, DEM_CODE ) Dem_MM_GetNvBlockStatusOfList
(
    VAR( Dem_u16_NvBlockIndexType, AUTOMATIC ) ListIndex
);


#define DEM_STOP_SEC_CODE
#include <Dem_MemMap.h>



#endif /* DEM_NVM_SYNC_PROCESS_ENABLE  -STD_ON- */


#endif /* DEM_MM_LOCAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2018-03-20                                              */
/*  v1-1-0         :2018-10-29                                              */
/*  v2-0-0         :2019-03-27                                              */
/*  v4-0-0         :2020-03-19                                              */
/*  v5-0-0         :2022-03-29                                              */
/*  v5-3-0         :2023-03-29                                              */
/*  v5-5-0         :2023-10-27                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
