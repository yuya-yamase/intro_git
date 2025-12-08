/* MemAcc.h v2-0-0                                                            */
/******************************************************************************/
/* Protected                                                                  */
/* Copyright DENSO CORPORATION. All rights reserved.                          */
/******************************************************************************/
/******************************************************************************/
/* Object Name  | MemAcc/HEADER                                               */
/******************************************************************************/
#ifndef MEMACC_H
#define MEMACC_H

/*----------------------------------------------------------------------------*/
/* Include Files                                                              */
/*----------------------------------------------------------------------------*/
#include <Std_Types.h>
#include <MemAcc_Types.h>
#include "../MemAcc/cfg/MemAcc_Cfg.h"
#include "../MemAcc/cfg/MemAcc_Lcfg.h"
#include "Fls.h"
#include "Fls_Cdd.h"

/*----------------------------------------------------------------------------*/
/* Macros                                                                     */
/*----------------------------------------------------------------------------*/
/* Version Info */
#define MEMACC_VENDOR_ID                   ( 0x0053U )
#define MEMACC_MODULE_ID                   ( 0x0029U )
#define MEMACC_AR_RELEASE_MAJOR_VERSION    ( 0x04U )
#define MEMACC_AR_RELEASE_MINOR_VERSION    ( 0x07U )
#define MEMACC_AR_RELEASE_REVISION_VERSION ( 0x00U )
#define MEMACC_SW_MAJOR_VERSION            ( 0x02U )
#define MEMACC_SW_MINOR_VERSION            ( 0x00U )
#define MEMACC_SW_PATCH_VERSION            ( 0x00U )

/* Generic literal */
#define MEMACC_U1_VAL_0               ( (uint8)0x00U )
#define MEMACC_U1_VAL_1               ( (uint8)0x01U )
#define MEMACC_U2_VAL_0               ( (uint16)0x0000U )
#define MEMACC_U2_VAL_1               ( (uint16)0x0001U )
#define MEMACC_U4_VAL_0               ( (uint32)0x00000000UL )
#define MEMACC_U4_VAL_1               ( (uint32)0x00000001UL )

/* MemAcc_LengthType literal */
#if ( MEMACC_64BIT_SUPPORT == STD_ON )
#define MEMACC_LENGTHTYPE_VAL_0       ( (uint64)0x0000000000000000ULL )
#define MEMACC_LENGTHTYPE_VAL_1       ( (uint64)0x0000000000000001ULL )
#else
#define MEMACC_LENGTHTYPE_VAL_0       ( (uint32)0x00000000UL )
#define MEMACC_LENGTHTYPE_VAL_1       ( (uint32)0x00000001UL )
#endif

/* MemAcc_AddressType literal */
#if ( MEMACC_64BIT_SUPPORT == STD_ON )
#define MEMACC_ADDRESSTYPE_VAL_0      ( (uint64)0x0000000000000000ULL )
#define MEMACC_ADDRESSTYPE_VAL_1      ( (uint64)0x0000000000000001ULL )
#else
#define MEMACC_ADDRESSTYPE_VAL_0      ( (uint32)0x00000000UL )
#define MEMACC_ADDRESSTYPE_VAL_1      ( (uint32)0x00000001UL )
#endif

/*----------------------------------------------------------------------------*/
/* Types                                                                      */
/*----------------------------------------------------------------------------*/
/* MemAcc_ConfigType (parameter of MemAcc_Init) */
typedef struct
{
    uint32        Dummy;                                                       /* Dummy */
} MemAcc_ConfigType;

/* MemAcc_MemoryInfoType */
typedef struct
{
    uint32                EraseSectorSize;                                     /* Erase sector size */
    uint32                EraseSectorBurstSize;                                /* Erase sector burst size (Same as erase sector size if burst is disabled) */
    uint32                ReadPageSize;                                        /* Read page size */
    uint32                WritePageSize;                                       /* Write page size */
    uint32                ReadPageBurstSize;                                   /* Read page burst size (Same as read page size if burst is disabled) */
    uint32                WritePageBurstSize;                                  /* Write page burst size (Same as write page size if burst is disabled) */
    uint32                HwId;                                                /* Hardware ID */
    MemAcc_AddressType    LogicalStartAddress;                                 /* Logical start address */
    MemAcc_AddressType    PhysicalStartAddress;                                /* Physical start address */
    MemAcc_LengthType     MaxOffset;                                           /* Maximum offset [Byte size of Subaddress area - 1] */
} MemAcc_MemoryInfoType;

/* MemAcc_JobInfoType */
typedef struct
{
    uint32                LogicalAddress;                                      /* Logical address of current job*/
    uint32                Length;                                              /* Length of current job */
    uint32                MemInstanceId;                                       /* Mem driver instance ID */
    uint32                MemAddress;                                          /* Requested physical address to Mem driver */
    uint32                MemLength;                                           /* Requested size to Mem driver */
    MemAcc_HwIdType       HwId;                                                /* Hardware ID */
    MemAcc_JobType        CurrentJob;                                          /* Current active MemAcc job */
    MemAcc_JobResultType  MemResult;                                           /* Result of the latest job */
} MemAcc_JobInfoType;

/*----------------------------------------------------------------------------*/
/* Function Prototypes                                                        */
/*----------------------------------------------------------------------------*/
#define MEMACC_START_SEC_CODE
#include <MemAcc_MemMap.h>

FUNC( void, MEMACC_CODE ) MemAcc_Init( P2CONST( MemAcc_ConfigType, AUTOMATIC, MEMACC_CONFIG_DATA ) configPtr );
FUNC( void, MEMACC_CODE ) MemAcc_DeInit( void );
FUNC( void, MEMACC_CODE ) MemAcc_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, MEMACC_APPL_DATA ) versionInfoPtr );
FUNC( MemAcc_JobResultType, MEMACC_CODE ) MemAcc_GetJobResult( MemAcc_AddressAreaIdType addressAreaId );
FUNC( MemAcc_JobStatusType, MEMACC_CODE ) MemAcc_GetJobStatus( MemAcc_AddressAreaIdType addressAreaId );
FUNC( Std_ReturnType, MEMACC_CODE ) MemAcc_GetMemoryInfo( MemAcc_AddressAreaIdType addressAreaId, MemAcc_AddressType address, P2VAR( MemAcc_MemoryInfoType, AUTOMATIC, TYPEDEF ) memoryInfoPtr);
FUNC( MemAcc_LengthType, MEMACC_CODE ) MemAcc_GetProcessedLength( MemAcc_AddressAreaIdType addressAreaId );
FUNC( void, MEMACC_CODE ) MemAcc_GetJobInfo( MemAcc_AddressAreaIdType addressAreaId, P2VAR( MemAcc_JobInfoType, AUTOMATIC, TYPEDEF ) jobInfoPtr );
FUNC( Std_ReturnType, MEMACC_CODE ) MemAcc_ActivateMem( MemAcc_AddressType headerAddress, MemAcc_HwIdType hwId );
FUNC( Std_ReturnType, MEMACC_CODE ) MemAcc_DeactivateMem( MemAcc_HwIdType hwId, MemAcc_AddressType headerAddress );
FUNC( void, MEMACC_CODE ) MemAcc_Cancel( MemAcc_AddressAreaIdType addressAreaId );
FUNC( Std_ReturnType, MEMACC_CODE ) MemAcc_Read( MemAcc_AddressAreaIdType addressAreaId, MemAcc_AddressType sourceAddress, P2VAR( MemAcc_DataType, AUTOMATIC, TYPEDEF ) destinationDataPtr, MemAcc_LengthType length );
FUNC( Std_ReturnType, MEMACC_CODE ) MemAcc_Write( MemAcc_AddressAreaIdType addressAreaId, MemAcc_AddressType targetAddress, P2CONST( MemAcc_DataType, AUTOMATIC, TYPEDEF ) sourceDataPtr, MemAcc_LengthType length );
FUNC( Std_ReturnType, MEMACC_CODE ) MemAcc_Erase( MemAcc_AddressAreaIdType addressAreaId, MemAcc_AddressType targetAddress, MemAcc_LengthType length );
FUNC( Std_ReturnType, MEMACC_CODE ) MemAcc_Compare( MemAcc_AddressAreaIdType addressAreaId, MemAcc_AddressType sourceAddress, P2CONST( MemAcc_DataType, AUTOMATIC, TYPEDEF ) dataPtr, MemAcc_LengthType length );
FUNC( Std_ReturnType, MEMACC_CODE ) MemAcc_BlankCheck( MemAcc_AddressAreaIdType addressAreaId, MemAcc_AddressType targetAddress, MemAcc_LengthType length );
FUNC( Std_ReturnType, MEMACC_CODE ) MemAcc_HwSpecificService( MemAcc_AddressAreaIdType addressAreaId, MemAcc_HwIdType hwId, MemAcc_MemHwServiceIdType hwServiceId, P2VAR(MemAcc_DataType, AUTOMATIC, TYPEDEF) dataPtr, P2VAR(MemAcc_LengthType, AUTOMATIC, TYPEDEF) lengthPtr );
FUNC( Std_ReturnType, MEMACC_CODE ) MemAcc_RequestLock( MemAcc_AddressAreaIdType addressAreaId, MemAcc_AddressType address, MemAcc_LengthType length, MemAcc_LockNotificationType lockNotificationFctPtr );
FUNC( Std_ReturnType, MEMACC_CODE ) MemAcc_ReleaseLock( MemAcc_AddressAreaIdType addressAreaId, MemAcc_AddressType address, MemAcc_LengthType length );

#define MEMACC_STOP_SEC_CODE
#include <MemAcc_MemMap.h>

/*----------------------------------------------------------------------------*/
/* Data                                                                       */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/* Constants                                                                  */
/*----------------------------------------------------------------------------*/

#endif  /* MEMACC_H */

/******************************************************************************/
/* History                                                                    */
/*  Version        :Date                                                      */
/*  2-0-0          :2025/02/28                                                */
/******************************************************************************/

/**** End of File *************************************************************/
