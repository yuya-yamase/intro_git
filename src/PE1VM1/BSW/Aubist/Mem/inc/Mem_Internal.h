/* Mem_Internal_h                                                           */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | RH850/U2Ax/Mem/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef MEM_INTERNAL_H
#define MEM_INTERNAL_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Internal Flags */
#define MEM_U1_FALSE                    ((uint8)0x00U)                  /* False                                        */
#define MEM_U1_TRUE                     ((uint8)0x01U)                  /* True                                         */

/* Job Status */
#define MEM_UNINIT                      ((uint8)0x00U)                  /* Non-initialization                           */
#define MEM_IDLE                        ((uint8)0x01U)                  /* Idle                                         */
#define MEM_BUSY                        ((uint8)0x02U)                  /* Busy                                         */
#define MEM_SUSPEND                     ((uint8)0x03U)                  /* Suspend                                      */

/* Request Type */
#define MEM_REQ_WRITE                   (CODEFLS_REQ_WRITE)             /* Request: Write                               */
#define MEM_REQ_ERASE                   (CODEFLS_REQ_ERASE)             /* Request: Erase                               */
#define MEM_REQ_SWITCHVALIDAREA         (CODEFLS_REQ_SWITCHVALIDAREA)   /* Request: Switch Valid Area                   */
#define MEM_REQ_BLANKCHECK              (CODEFLS_REQ_BLANKCHECK)        /* Request: Blank Check                         */
#define MEM_REQ_READ                    ((uint8)0x05U)                  /* Request: Read                                */

/* Operation Information Settings */
#define MEM_U1_OPINFO_CMD_NONE          ((uint8)0xFFU)                  /* No command                                   */
#define MEM_U4_OPINFO_ADDR_NONE         ((uint32)0x00000000UL)          /* No address                                   */
#define MEM_U4_OPINFO_SIZE_NONE         ((uint32)0x00000000UL)          /* No size                                      */
#define MEM_PU1_OPINFO_BUFFER_NULL      (( uint8 *)0)                   /* No buffer                                    */

/* Code Flash Area Information Setting Table Number */
#define MEM_U1_INFONUM_0                ((uint8)0x00U)                  /* Initial value                                */
#define MEM_U1_INFONUM_NONE_KIND        ((uint8)0xFDU)                  /* Out of the code flash area range - kind      */
#define MEM_U1_INFONUM_NONE_LEN         ((uint8)0xFEU)                  /* Out of the code flash area range - size      */
#define MEM_U1_INFONUM_NONE_ADD         ((uint8)0xFFU)                  /* Out of the code flash area range - address   */

#define MEM_U1_VAL_0                    ((uint8)0U)
#define MEM_U4_VAL_0                    ((uint32)0x00000000UL)
#define MEM_U4_VAL_1                    ((uint32)0x00000001UL)
#define MEM_U4_VAL_MAX                  ((uint32)0xFFFFFFFFUL)

/* Version Info */
#define MEM_VERSIONINFO_VENDER_ID           ((uint16)0x0053U)
#define MEM_VERSIONINFO_MODULE_ID           MEM_MODULE_ID
#define MEM_VERSIONINFO_SW_MAJOR_VERSION    ((uint8)0x02U)
#define MEM_VERSIONINFO_SW_MINOR_VERSION    ((uint8)0x00U)
#define MEM_VERSIONINFO_SW_PATCH_VERSION    ((uint8)0x00U)

/* SectorBatch Number */
#define MEM_U1_SECTOR_BATCH_NUM_NONE        ((uint8)0xFFU)


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Operational Information */
typedef struct
{
    uint8 u1Cmd;                                                        /* command                                      */
    uint32 u4OpAddr;                                                    /* Current flash control start address          */
    P2VAR(uint8, TYPEDEF, MEM_APPL_DATA) pu1ReadBufAddr;                /* Read data storage address                    */
    P2CONST(uint8, TYPEDEF, MEM_APPL_DATA) pu1WriteBufAddr;             /* Write data storage address                   */
    uint32 u4OpSize;                                                    /* Remaining Size                               */
    uint8 u1SectorBatchNum;                                             /* Sector Batchs subject to processing          */
    uint8 u1CtrlStartFlag;                                              /* Control start flag                           */
    Mem_JobResultType u1ECCErrStatus;                                   /* ECC Error Status                             */
} Mem_MultiOpType;

/* Operational Mirror Information */
typedef struct
{
    uint8 u1CheckCmd;                                                   /* command                                      */
    uint32 u4CheckAddr;                                                 /* Current flash control start address          */
    P2VAR(uint8, TYPEDEF, MEM_APPL_DATA) pu1CheckReadBuf;               /* Read data storage address                    */
    P2CONST(uint8, TYPEDEF, MEM_APPL_DATA) pu1CheckWriteBuf;            /* Write data storage address                   */
    uint32 u4CheckSize;                                                 /* Remaining Size                               */
    uint8 u1CheckSectorBatchNum;                                        /* Sector Batchs subject to processing          */
    uint8 u1CheckCtrlStartFlag;                                         /* Control start flag                           */
    Mem_JobResultType u1CheckECCErrStatus;                              /* ECC Error Status                             */
} Mem_OpMirrorType;
/* [Device Individuality Config] MEM Control Setting Configuration Type */
typedef struct
{
    uint8 Mem_Ab_Erase_Delay_Count;                         /* Erase delay count                            */
    uint8 Mem_Ab_Write_Delay_Count;                         /* Write delay count                            */
} Mem_DevControlSettingType;

/* [Device Individuality Config] MEM Device Individuality Configuration Type */
typedef struct
{
    /* Start Address of MEM Control Setting Configuration Table */
    P2CONST (AB_83_ConstV Mem_DevControlSettingType, MEM_CONFIG_DATA, MEM_APPL_CONST) Mem_Ab_ControlSetting;
} Mem_DevConfigType;



/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define MEM_START_SEC_VAR_NO_INIT_32
#include <Mem_MemMap.h>

extern VAR(uint8, MEM_VAR_NO_INIT) Mem_u1gJobStatus;                        /* Job Status                                   */
extern VAR(uint8, MEM_VAR_NO_INIT) Mem_u1gMirrorJobStatus;                  /* Job Status Mirror Area                       */
extern VAR(uint8, MEM_VAR_NO_INIT) Mem_u1gJobResult;                        /* Job Processing Results                       */
extern VAR(uint8, MEM_VAR_NO_INIT) Mem_u1gMirrorJobResult;                  /* Job Processing Results Mirror Area           */
extern VAR(uint8, MEM_VAR_NO_INIT) Mem_u1gErrorNotifyFlag;                  /* Error Notification Receive Flag              */
extern VAR(uint8, MEM_VAR_NO_INIT) Mem_u1gMirrorErrorNotifyFlag;            /* Error Notification Receive Flag Mirror Area  */
extern VAR(Mem_MultiOpType, MEM_VAR_NO_INIT)  Mem_stgMultiOpInfo;           /* Operational Information                      */
extern VAR(Mem_OpMirrorType, MEM_VAR_NO_INIT) Mem_stgMirrorArea;            /* Operation Information Mirror Area            */
extern VAR(uint8, MEM_VAR_NO_INIT) Mem_u1gJobDelayCount;                    /* Job Delay Counter                            */

#define MEM_STOP_SEC_VAR_NO_INIT_32
#include <Mem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define MEM_START_SEC_CONST_CONFIG_32
#include <Mem_MemMap.h>

extern CONST (AB_83_ConstV Mem_DevConfigType, MEM_CONFIG_DATA) MEM_DEVCFG_DATA;

#define MEM_STOP_SEC_CONST_CONFIG_32
#include <Mem_MemMap.h>

#define MEM_START_SEC_CONST_32
#include <Mem_MemMap.h>

#define MEM_STOP_SEC_CONST_32
#include <Mem_MemMap.h>


#endif  /* MEM_INTERNAL_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1.00          :2025/03/24                                              */
/*  v1.01          :2025/04/14                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
