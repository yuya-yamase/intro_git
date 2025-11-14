/* Fee_Legacy.h v2-0-0                                                      */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION. All rights reserved.                        */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FEE/LEGACY/HEADER                                         */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef FEE_LEGACY_H
#define FEE_LEGACY_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Fee_Ext.h>
#include "Fee_Mpu_Dev_Const.h"

#include "Fee_Common.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* API-related */
/* Common Return */
#define FEE_REQUEST_ACCEPT              ((uint8)0x00U)     /* SUCCESS REQUEST */
#define FEE_REQUEST_DECLINE             ((uint8)0x01U)     /* Request denied */
#define FEE_REQUEST_IRBLD_CNFM_NOT_OK   ((uint8)0x02U)     /* A confirmation result for intentional rebuilding is not OK. */

/* Data Flash operation status get request */
/* RETURN */
#define FEE_IDLING                  ((uint8)0x00U)      /* Waiting */
#define FEE_WRITING                 ((uint8)0x01U)      /* Writing */
#define FEE_ID_READING              ((uint8)0x02U)      /* Reading by ID */
#define FEE_REBUILDING              ((uint8)0x06U)      /* Data Restructuring */
#define FEE_FLS_ERROR               ((uint8)0x08U)      /* FLS abnormal */
#define FEE_DFC_ERROR               ((uint8)0x10U)      /* DFC abnormal operation */

/* Hook-related */
/* Common processing success/failure */
#define FEE_RSP_OK                  ((uint8)0x00U)     /* PROCESSING SUCCESSFUL */
#define FEE_RSP_NG                  ((uint8)0x80U)     /* Processing failed */
#define FEE_RSP_NG_DTF_CTRL         ((uint8)0x7FU)     /* Data Flash controller error */
#define FEE_RSP_TIMEOUT             ((uint8)0xFFU)     /* Timeout */
#define FEE_RSP_GARBLED_RAM         ((uint8)0x77U)     /* A garbled RAM was detected. */

/* Data write response Hook */
#define FEE_RSP_NG_INITIALIZE       ((uint8)0x01U)     /* Successful write, no target block */
#define FEE_RSP_NG_WRITE_DATA       ((uint8)0x81U)     /* WRITE FAILED */
#define FEE_RSP_NG_NODATA           ((uint8)0x82U)     /* Write failed, no target block */

/* Data read response Hook (ID-specified read) */
#define FEE_RSP_NODATA              ((uint8)0x83U)     /* Not applicable data */
#define FEE_RSP_UNUSED              ((uint8)0x84U)     /* Unblocked */

/* When to call for periodic processing */
#define FEE_CALL_TIMING_PERIODIC        (0U)    /* Call at regular intervals */
#define FEE_CALL_TIMING_NOT_PERIODIC    (1U)    /* Call at irregular intervals */

/* repair type */
#define FEE_RSP_RESTORE_KIND_RECOVER        (0U)    /* Large sector: area error, small sector: return */
#define FEE_RSP_RESTORE_KIND_RESTORE        (1U)    /* Small sector: repair (duplicate data inconsistency repair) */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define FEE_START_SEC_CODE
#include <Fee_MemMap.h>

/* API */
/* Data write request */
FUNC(uint8, FEE_CODE) Fee_Legacy_WriteData( uint16 data_id, P2CONST(uint8, AUTOMATIC, TYPEDEF) data_address, uint8 No );
/* Data read request (ID-specified read) */
FUNC(uint8, FEE_CODE) Fee_Legacy_ReadData( uint16 data_id, uint8 No, P2VAR( uint8, AUTOMATIC, FEE_APPL_DATA ) DataBufferPtr );
/* Data Flash Driver Initialization Request (on reset) */
FUNC(void, FEE_CODE) Fee_Legacy_PwonInit( void );
/* Data Flash Driver Forced Initialization */
FUNC(void, FEE_CODE) Fee_Legacy_Abort( void );
/* Data Flash operation status get request */
FUNC(uint8, FEE_CODE) Fee_Legacy_GetStatus( void );
/* Data Flash Periodic */
FUNC(void, FEE_CODE) Fee_Legacy_PeriodicFunc( void );

/* Data Flash irregular processing */
FUNC(void, FEE_CODE) Fee_Legacy_NonPeriodicFunc( void );

/* Get data length */
FUNC(Std_ReturnType, FEE_CODE) Fee_Legacy_GetDataLength( uint16 data_id, P2VAR(uint16, AUTOMATIC, TYPEDEF) DataLength);

/* Hook */
/* Data write response Hook */
FUNC(void, FEE_CODE) Fee_Write_Rsp_Hook(
    uint8   result,
    uint16  data_id,
    uint8   No
);
/* Data read response Hook (ID-specified read) */
FUNC(void, FEE_CODE) Fee_Read_Rsp_Hook(
    uint8   result,
    uint16  data_id,
    uint8   No
);

/* Data Restructuring Request */
FUNC(uint8, FEE_CODE) Fee_Legacy_Rebuild( uint8 No );  

FUNC( Fee_ExtFreeSpaceReturnType, FEE_CODE )
Fee_Legacy_GetFreeSpace(
    uint8  AreaNo,
    uint16 LimitSearchMngArea,
    uint32 LimitSearchDataArea,
    P2VAR( Fee_ExtFreeSpaceInfoType, AUTOMATIC, TYPEDEF ) FreeSpaceInfoPtr
);

/* Data Restructuring Response Hook */
FUNC(void, FEE_CODE) Fee_Rebuild_Rsp_Hook( uint8 result, uint8 No );    

#define FEE_STOP_SEC_CODE
#include <Fee_MemMap.h>

/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* FEE_LEGACY_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  1-0-0          :2019/02/01                                              */
/*  1-1-0          :2019/08/27                                              */
/*  2-0-0          :2022/08/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
