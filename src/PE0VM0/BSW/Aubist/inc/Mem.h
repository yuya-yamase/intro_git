/* Mem_h                                                                    */
/****************************************************************************/
/* Protected                                                                */
/* Copyright DENSO CORPORATION                                              */
/****************************************************************************/
/****************************************************************************/
/* Object Name  | RH850/U2Ax/Mem/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/
#ifndef MEM_H
#define MEM_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <Mem_Cfg.h>


/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* Module ID */
#define MEM_MODULE_ID                   ((uint16)0x0091U)           /* Module ID for MEM Driver             */

/* API ID */
#define MEM_API_ID_INIT                 ((uint8)0x01U)              /* Initialization process               */
#define MEM_API_ID_GETVERSIONINFO       ((uint8)0x02U)              /* Get Version information process      */
#define MEM_API_ID_MAINFUNCTION         ((uint8)0x03U)              /* Main Function Process                */ /* MISRA DEVIATION */ /* Unused */
#define MEM_API_ID_GETJOBRESULT         ((uint8)0x04U)              /* Get Job processing result process    */ /* MISRA DEVIATION */ /* Unused */
#define MEM_API_ID_READ                 ((uint8)0x05U)              /* Memory Read Process                  */
#define MEM_API_ID_WRITE                ((uint8)0x06U)              /* Memory Write Process                 */
#define MEM_API_ID_ERASE                ((uint8)0x07U)              /* Memory Erasure Process               */
#define MEM_API_ID_PROPAGATEERROR       ((uint8)0x08U)              /* Error notification Process           */
#define MEM_API_ID_BLANKCHECK           ((uint8)0x09U)              /* Memory blank check process           */
#define MEM_API_ID_HWSPECIFICSERVICE    ((uint8)0x0AU)              /* Hardware-specific service process    */
#define MEM_API_ID_DEINIT               ((uint8)0x0BU)              /* Uninitialization process             */ /* MISRA DEVIATION */ /* Unused */
#define MEM_API_ID_SUSPEND              ((uint8)0x0CU)              /* Suspend process                      */
#define MEM_API_ID_RESUME               ((uint8)0x0DU)              /* Resume Process                       */

/* service id */
#define MEM_SRV_ID_SWITCHVALIDAREA      ((uint32)0x00000001U)       /* Flash Memory valid area switching request id */

/* Development error codes */
#define MEM_E_UNINIT                    ((uint8)0x01U)              /* Uninitialized                        */
#define MEM_E_PARAM_POINTER             ((uint8)0x02U)              /* Invalid pointer                      */
#define MEM_E_PARAM_ADDRESS             ((uint8)0x03U)              /* Invalid address                      */
#define MEM_E_PARAM_LENGTH              ((uint8)0x04U)              /* Invalid data length                  */
#define MEM_E_PARAM_INSTANCE_ID         ((uint8)0x05U)              /* Invalid instance ID                  */
#define MEM_E_JOB_PENDING               ((uint8)0x06U)              /* Job in Progress                      */

/* Job Processing Result Type */
typedef uint8 Mem_JobResultType;                                    /* Job Processing Result Type           */
#define MEM_JOB_OK                      ((Mem_JobResultType)0x00U)  /* Successful completion                */
#define MEM_JOB_PENDING                 ((Mem_JobResultType)0x01U)  /* In Progress                          */
#define MEM_JOB_FAILED                  ((Mem_JobResultType)0x02U)  /* Failed                               */
#define MEM_INCONSISTENT                ((Mem_JobResultType)0x03U)  /* Blank check error                    */
#define MEM_ECC_UNCORRECTED             ((Mem_JobResultType)0x04U)  /* Unrecoverable ECC error              */
#define MEM_ECC_CORRECTED               ((Mem_JobResultType)0x05U)  /* Recoverable ECC error                */

#define E_MEM_SERVICE_NOT_AVAIL         ((Std_ReturnType)0x02U)     /* The service is not implemented       */
#define E_MEM_ERASE_SUSPEND_NOT_OK      ((Std_ReturnType)0x03U)     /* Suspend error in erase progress      */


/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/**********************************************************************************************/
/* Described from the configuration information of the AUTOSAR_SWS_MemoryDriver specification */
/**********************************************************************************************/
/* Burst Transfer Information Container */
typedef struct
{
    uint32 MemReadBurstSize;                                /* Memory Read Burst Size                       */
    uint32 MemWriteBurstSize;                               /* Memory Write Burst Size                      */
    uint32 MemEraseBurstSize;                               /* Memory Erase Burst Size                      */
} Mem_BurstSettingsType;

/* Sector Batch Configuration Information Container */
typedef struct
{
    uint32 MemReadPageSize;                                 /* Memory Read Page Size                        */
    uint32 MemWritePageSize;                                /* Memory Write Page Size                       */
    uint32 MemEraseSectorSize;                              /* Memory Erase Sector Size                     */
    uint32 MemSpecifiedEraseCycle;                          /* Number of memory erase cycles                */
    uint32 MemStartAddress;                                 /* Sector physical start address                */
    uint16 MemNumberOfSectors;                              /* Number of consecutive sectors                */
    Mem_BurstSettingsType MemBurstSettings;                 /* Burst Transfer Information Container         */
} Mem_SectorBatchType;

/* Instance Information Container */
typedef struct
{
    uint32 MemSectorBatchNum;
    uint16 MemInstanceId;                                   /* MemInstance ID                               */
    Mem_SectorBatchType MemSectorBatch[(uint8)MEM_BANK_MAX_NUM];    /* Sector Batch Configuration Information Container */
} Mem_InstanceType;

/* Public Information Container */
typedef struct
{
    uint32 MemErasedValue;                                  /* Memory Erase Settings */
} Mem_PublishedInformationType;

typedef uint32 Mem_AddressType;                             /* Address type                                 */
typedef uint8 Mem_DataType;                                 /* Data storage space                           */
typedef uint32 Mem_InstanceIdType;                          /* Instance ID                                  */
typedef uint32 Mem_LengthType;                              /* Data length                                  */
typedef uint32 Mem_HwServiceIdType;                         /* Hardware-specific service identifier         */

/* Configuration data storage area */
typedef struct
{
    uint32  Dummy;                                          /* Dummy Definition                             */
} Mem_ConfigType;


/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
FUNC(void, MEM_CODE_FAR) Mem_Init
(
    P2CONST(Mem_ConfigType, AUTOMATIC, MEM_APPL_DATA) configPtr
);
FUNC(void, MEM_CODE_FAR) Mem_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, MEM_APPL_DATA) versionInfoPtr
);
FUNC(void, MEM_CODE_FAR) Mem_PropagateError
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId
);
FUNC(void, MEM_CODE_FAR) Mem_DeInit(void);
FUNC(void, MEM_CODE_FAR) Mem_MainFunction(void);
FUNC(Mem_JobResultType, MEM_CODE_FAR) Mem_GetJobResult
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId
);
FUNC(Std_ReturnType, MEM_CODE_FAR) Mem_Read
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId,
    VAR(Mem_AddressType, AUTOMATIC) sourceAddress,
    P2VAR(Mem_DataType, AUTOMATIC, MEM_APPL_DATA) destinationDataPtr,
    VAR(Mem_LengthType, AUTOMATIC) length
);
FUNC(Std_ReturnType, MEM_CODE_FAR) Mem_Write
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId,
    VAR(Mem_AddressType, AUTOMATIC) targetAddress,
    P2CONST(Mem_DataType, AUTOMATIC, MEM_APPL_DATA) sourceDataPtr,
    VAR(Mem_LengthType, AUTOMATIC) length
);
FUNC(Std_ReturnType, MEM_CODE_FAR) Mem_Erase
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId,
    VAR(Mem_AddressType, AUTOMATIC) targetAddress,
    VAR(Mem_LengthType, AUTOMATIC) length
);
FUNC(Std_ReturnType, MEM_CODE_FAR) Mem_BlankCheck
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId,
    VAR(Mem_AddressType, AUTOMATIC) targetAddress,
    VAR(Mem_LengthType, AUTOMATIC) length
);
FUNC(Std_ReturnType, MEM_CODE_FAR) Mem_HwSpecificService
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId,
    VAR(Mem_HwServiceIdType, AUTOMATIC) hwServiceId,
    P2VAR(Mem_DataType, AUTOMATIC, MEM_APPL_DATA) dataPtr,
    P2VAR(Mem_LengthType, AUTOMATIC, MEM_APPL_DATA) lengthPtr
);
FUNC(Std_ReturnType, MEM_CODE_FAR) Mem_Suspend
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId
);
FUNC(Std_ReturnType, MEM_CODE_FAR) Mem_Resume
(
    VAR(Mem_InstanceIdType, AUTOMATIC) instanceId
);


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/
#define MEM_START_SEC_VAR_NO_INIT_32
#include <Mem_MemMap.h>

#define MEM_STOP_SEC_VAR_NO_INIT_32
#include <Mem_MemMap.h>


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/
#define MEM_START_SEC_CONST_CONFIG_32
#include <Mem_MemMap.h>

extern CONST(AB_83_ConstV Mem_InstanceType, MEM_CONFIG_DATA) MemInstance;
extern CONST(AB_83_ConstV Mem_PublishedInformationType, MEM_CONFIG_DATA) MemPublishedInformation;

#define MEM_STOP_SEC_CONST_CONFIG_32
#include <Mem_MemMap.h>


#endif  /* MEM_H */

/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1.00          :2025/03/24                                              */
/****************************************************************************/

/**** End of File ***********************************************************/

