/* MemAcc_Types.h v2-0-0                                                      */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright DENSO CORPORATION. All rights reserved.                          */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | MEMACC/TYPES/HEADER                                         */
/******************************************************************************/
#ifndef MEMACC_TYPES_H
#define MEMACC_TYPES_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* MemAcc_JobResultType */
typedef uint8    MemAcc_JobResultType;
#define MEMACC_MEM_OK                 ( (MemAcc_JobResultType)0x00U )          /* Succeeded */
#define MEMACC_MEM_FAILED             ( (MemAcc_JobResultType)0x01U )          /* Failed */
#define MEMACC_MEM_INCONSISTENT       ( (MemAcc_JobResultType)0x02U )          /* Inconsistent */
#define MEMACC_MEM_CANCELED           ( (MemAcc_JobResultType)0x03U )          /* Canceled */
#define MEMACC_MEM_ECC_UNCORRECTED    ( (MemAcc_JobResultType)0x04U )          /* Uncorrected ECC error */
#define MEMACC_MEM_ECC_CORRECTED      ( (MemAcc_JobResultType)0x05U )          /* Corrected ECC error */

/* MemAcc_JobStatusType */
typedef uint8   MemAcc_JobStatusType;
#define MEMACC_JOB_IDLE               ( (MemAcc_JobStatusType)0x00U )          /* Job idle */
#define MEMACC_JOB_PENDING            ( (MemAcc_JobStatusType)0x01U )          /* Job processing */

/* MemAcc_JobType */
typedef uint8   MemAcc_JobType;
#define MEMACC_NO_JOB                 ( (MemAcc_JobType)0x00U )                /* No job running */
#define MEMACC_WRITE_JOB              ( (MemAcc_JobType)0x01U )                /* Write job running */
#define MEMACC_READ_JOB               ( (MemAcc_JobType)0x02U )                /* Read job running */
#define MEMACC_COMPARE_JOB            ( (MemAcc_JobType)0x03U )                /* Compare job running */
#define MEMACC_ERASE_JOB              ( (MemAcc_JobType)0x04U )                /* Erase job running */
#define MEMACC_MEMHWSPECIFIC_JOB      ( (MemAcc_JobType)0x05U )                /* HW specific job running */
#define MEMACC_BLANKCHECK_JOB         ( (MemAcc_JobType)0x06U )                /* Blankcheck job running */
#define MEMACC_REQUESTLOCK_JOB        ( (MemAcc_JobType)0x07U )                /* Lock request executing */

/* MemAcc_HwIdType */
typedef uint32  MemAcc_HwIdType;
#define MEMACC_HWID_CODEFLASH         ( (MemAcc_HwIdType)0x00000001UL )        /* HW ID: CodeFlash */

/* MemAcc_MemHwServiceIdType */
typedef uint32  MemAcc_MemHwServiceIdType;
#define MEMACC_SRV_ID_SWITCHVALIDAREA ( (MemAcc_MemHwServiceIdType)0x00000001UL )  /* Request ID for switching active Memory area */

/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
typedef uint16  MemAcc_AddressAreaIdType;                           /* AddressAreaId type */
typedef uint32  MemAcc_AddressType;                               /* Logical address type: 32bit Only */
typedef uint32  MemAcc_LengthType;                                /* Length type: 32bit Only */
typedef uint8   MemAcc_DataType;                                  /* Data type */

/* Notification API Type */
typedef P2FUNC ( void, MEMACC_CODE, MemAcc_LockNotificationType )  ( void );
/* Job end notification function */
typedef P2FUNC ( void, MEMACC_CODE, MemAcc_JobEndNotificationType ) ( MemAcc_AddressAreaIdType addressAreaId, MemAcc_JobResultType jobResult );

#endif  /* MEMACC_TYPES_H */

/******************************************************************************/
/* History                                                                    */
/*  Version        :Date                                                      */
/*  2-0-0          :2025/02/28                                                */
/******************************************************************************/

/**** End of File *************************************************************/
