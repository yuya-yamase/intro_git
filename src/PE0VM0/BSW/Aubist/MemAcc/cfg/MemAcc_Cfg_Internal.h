/* MemAcc_Cfg_Internal.h v2-0-0                                               */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright DENSO CORPORATION. All rights reserved.                          */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | MemAcc/CFG/INTERNAL/HEADER                                  */
/******************************************************************************/
#ifndef MEMACC_CFG_INTERNAL_H
#define MEMACC_CFG_INTERNAL_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <MemAcc_Types.h>

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/

/* MemAccMemNamePrefix */
#define MEMACC_NAMEPREFIX_DATAFLASH       ( (uint32)0U )

/* MemAccMemInvocation */
#define MEMACC_INVOKE_DIRECT_STATIC       ( (uint8)0x00U )
#define MEMACC_INVOKE_INDIRECT_DYNAMIC    ( (uint8)0x01U )
#define MEMACC_INVOKE_INDIRECT_STATIC     ( (uint8)0x02U )

/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
/* Mem Sector Batch Configuration Information Container */
typedef struct
{
    uint32              MemAcc_MemReadPageSize;            /* Memory Read Size                     */
    uint32              MemAcc_MemWritePageSize;           /* Memory Write Size                    */
    uint32              MemAcc_MemEraseSectorSize;         /* Memory Erase Size                    */
    uint32              MemAcc_MemSpecifiedEraseCycle;     /* Number of memory erase cycles        */
    uint32              MemAcc_MemStartAddress;            /* Sector physical start address        */
    uint16              MemAcc_MemNumberOfSectors;         /* Number of consecutive sectors        */
    uint32              MemAcc_MemReadBurstSize;           /* Memory Read Size                     */
    uint32              MemAcc_MemWriteBurstSize;          /* Memory Write Size                    */
    uint32              MemAcc_MemEraseBurstSize;          /* Memory Erase Size                    */
} MemAcc_Mem_SectorBatchType;


/* Sub address area configuration container */
typedef struct
{
    uint32              MemAccLogicalStartAddress;         /* Logical start address */
    uint32              MemAccNumberOfSectors;             /* Number of Pysical sector */
    uint32              MemAccSectorOffset;                /* Pysical sector offset */
    uint32              MemAccMemNamePrefix;               /* Prefix of Mem driver name */
    uint8               MemAccMemInvocation;               /* Mem driver activating method */
    uint8               MemAccNumberOfEraseRetries;        /* Number of erase retries */
    uint8               MemAccNumberOfWriteRetries;        /* Number of write retries */
    uint8               MemAccUseEraseBurst;               /* Enable/disable of erase burst */
    uint8               MemAccUseReadBurst;                /* Enable/disable read burst */
    uint8               MemAccUseWriteBurst;               /* Enable/disable write burst */
    P2CONST( AB_83_ConstV MemAcc_Mem_SectorBatchType, AUTOMATIC, TYPEDEF )MemAccSectorBatchRef;
} MemAcc_SubAddressAreaConfiguration;

/* Address area configuration container */
typedef struct
{
    uint16                                      MemAccAddressAreaId;                 /* AddressAreaId */
    uint16                                      MemAccAddressAreaPriority;           /* AddressArea priority */
    uint8                                       MemAccBufferAlignmentValue;          /* Buffer alignment value */
    MemAcc_JobEndNotificationType               MemAccJobEndNotificationName;        /* Job end notification function pointer */
    P2CONST( AB_83_ConstV MemAcc_SubAddressAreaConfiguration, AUTOMATIC, TYPEDEF ) MemAccSubAddressAreaConfiguration;   /* SubAddressAreaConfiguration infomation pointer */
} MemAcc_AddressAreaConfiguration;

/* Job control information (for external module) */
typedef struct
{
    MemAcc_JobStatusType        extJobStatus;                  /* MemAcc job status */
    MemAcc_JobType              extJobType;                    /* MemAcc job type */
    MemAcc_JobResultType        extJobResult;                  /* MemAcc job result */
    uint8                       Dummy_1;                       /* Dummy area-1 (for padding) */
} MemAcc_JobCtlExternalInfoType;

/* Job request manage information */
typedef struct
{
    uint8                                          innerJobStatus;                /* Job status (for inner use) */
    uint8                                          innerJobType;                  /* Job type (for inner use) */
    uint8                                          innerRetryCount;               /* Retry count (for inner use) */
    uint8                                          Dummy_1;                       /* Dummy area-1 (for padding) */
    MemAcc_HwIdType                                hwId;                          /* Hardware ID */
    MemAcc_MemHwServiceIdType                      hwServiceId;                   /* HW specific service ID */
    P2VAR( MemAcc_LengthType, AUTOMATIC, TYPEDEF ) lengthPtr;                     /* Data length pointer */
    MemAcc_AddressType                             targetAddress;                 /* Target address */
    P2CONST( MemAcc_DataType, AUTOMATIC, TYPEDEF ) sourceDataPtr;                 /* Source data pointer */
    P2VAR( MemAcc_DataType, AUTOMATIC, TYPEDEF )   destinationDataPtr;            /* Destination data pointer */
    MemAcc_LengthType                              length;                        /* Data length */
} MemAcc_JobRequestManageType;

/* Lock infomation managemant table */
typedef struct
{
    uint8 MemAccSemStatus;                                     /* Lock status                       */
    MemAcc_LockNotificationType  MemAccSemNotificationFunc;    /* Lock request notification function pointer */
} MemAcc_SemCtlLockInfoType;

/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/

#endif  /* MEMACC_CFG_INTERNAL_H */

/******************************************************************************/
/* History                                                                    */
/*  Version        :Date                                                      */
/*  2-0-0          :2024/10/24                                                */
/******************************************************************************/

/**** End of File *************************************************************/
