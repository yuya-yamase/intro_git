/* NvM_Evt_Internal.h v2-0-0                                                */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | NVM/EVT/INTERNAL/HEADER                                   */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef     NVM_EVT_INTERNAL_H
#define     NVM_EVT_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include "NvM_Lib.h"
#include "../usr/NvM_Dem_Connector.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

#define NVM_EVT_ERR_EVENT_NUM                   ( 0x06U )

#define NVM_EVT_EVENT_STATUS_BIT_PASSED         ( 0x01U )
#define NVM_EVT_EVENT_STATUS_BIT_FAILED         ( 0x02U )
#define NVM_EVT_EVENT_STATUS_BIT_UNINSPECTED    ( 0x04U )

#define NVM_EVT_DETAIL_ERR_NUM                  ( 0x0CU )

#define NVM_EVT_FATALFAILED_HAPPENED            ( 0x0FU )
#define NVM_EVT_FATALFAILED_NOT_HAPPENED        ( 0xF0U )

#define NVM_EVT_MULTI_BLOCK_REQUEST_INVALID     ((NvM_MultiBlockRequestType)0xFFU)
#define NVM_EVT_SINGLE_BLOCK_REQUEST_INVALID    ((NvM_BlockRequestType)0xFFU)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

typedef uint8 NvM_Evt_EventStatusBitType;

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

extern VAR( NvM_Evt_EventStatusBitType, NVM_VAR_NO_INIT ) NvM_Evt_EventStatus[NVM_EVT_ERR_EVENT_NUM];
extern VAR( uint8,                      NVM_VAR_NO_INIT ) NvM_Evt_FatalFailedHappened;

#define NVM_STOP_SEC_VAR_NO_INIT_32
#include <NvM_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CONST_32
#include <NvM_MemMap.h>

extern CONST( AB_83_ConstV NvM_Lib_ValueConvertTableType,   NVM_CONST )  NvM_JobIdToBlockRequestTable;
extern CONST( AB_83_ConstV NvM_Lib_ValueConvertTableType,   NVM_CONST )  NvM_JobIdToMultiBlockRequestTable;
extern CONST( AB_83_ConstV NvM_Lib_ValueConvertPairType,    NVM_CONST )  NvM_JobIdToBlockRequestPair[NVM_SINGLE_JOBID_NUM];
extern CONST( AB_83_ConstV NvM_Lib_ValueConvertPairType,    NVM_CONST )  NvM_JobIdToMultiBlockRequestPair[NVM_MULTI_JOBID_NUM];
extern CONST( AB_83_ConstV NvM_Dem_EventIdType, NVM_CONST ) NvM_Evt_ErrEventToDemEventId[NVM_EVT_ERR_EVENT_NUM];
extern CONST( AB_83_ConstV uint32,              NVM_CONST ) NvM_Evt_DetailErrToErrRsltTbl[NVM_EVT_DETAIL_ERR_NUM];

#define NVM_STOP_SEC_CONST_32
#include <NvM_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/

#define NVM_START_SEC_CODE
#include <NvM_MemMap.h>

FUNC( void, NVM_CODE )
NvM_Evt_NfySingleBlockResult(
    NvM_BlockIdType BlockId,
    uint32 JobId,
    NvM_RequestResultType JobResult
);

FUNC( void, NVM_CODE )
NvM_Evt_NfyMultiBlockResult(
    uint32 JobId,
    NvM_RequestResultType JobResult
);

FUNC( void, NVM_CODE )
NvM_Evt_ReportProductionErrorStatus(
    uint8 ErrEvent
);

#define NVM_STOP_SEC_CODE
#include <NvM_MemMap.h>

#endif  /* NVM_EVT_INTERNAL_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2017/12/05                                              */
/*  1-1-0          :2018/10/25                                              */
/*  1-2-0          :2019/08/26                                              */
/*  2-0-0          :2020/12/22                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
