/* Fls_h_Revision(v1_0_2)                                                   */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS Corporation                                             */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FLS/HEADER                                                */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FLS_H
#define FLS_H


#include <Std_Types.h>
#include "../Fls/cfg/Fls_Cfg.h"
#include "../Fls/cfg/Fls_Cdd_Cfg.h"
#include "../Fls/cfg/Fls_Drv_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* AUTOSAR Version */
#define FLS_AR_RELEASE_MAJOR_VERSION        ( ( uint8 )0x04U )
#define FLS_AR_RELEASE_MINOR_VERSION        ( ( uint8 )0x05U )
#define FLS_AR_RELEASE_REVISION_VERSION     ( ( uint8 )0x00U )

/* Version Info */
#define FLS_SW_MAJOR_VERSION                ( ( uint8 )0x01U )
#define FLS_SW_MINOR_VERSION                ( ( uint8 )0x00U )
#define FLS_SW_PATCH_VERSION                ( ( uint8 )0x03U )

/* module ID */
#define FLS_MODULE_ID                       ( ( uint16 )0x005CU )   /* module ID of Data Flash driver */

/* instance ID */
#define FLS_INSTANCE_ID                     ( ( uint8 )0x00U )     /* instance ID of Data Flash driver */

/* vendor ID */
#define FLS_VENDOR_ID                       ( 0x0053U )

/* API ID */
#define FLS_APIID_INIT                      ( ( uint8 )0x00U )     /* API ID of Fls_Init */
#define FLS_APIID_WRITE                     ( ( uint8 )0x02U )     /* API ID of Fls_Write*/
#define FLS_APIID_READ                      ( ( uint8 )0x07U )     /* API ID of Fls_Read */
#define FLS_APIID_ERASE                     ( ( uint8 )0x01U )     /* API ID of Fls_Erase */
#define FLS_APIID_CANCEL                    ( ( uint8 )0x03U )     /* API ID of Fls_Cancel */
#define FLS_APIID_GETSTATUS                 ( ( uint8 )0x04U )     /* API ID of Fls_GetStatus */
#define FLS_APIID_MAINFUNCTION              ( ( uint8 )0x06U )     /* API ID of Fls_MainFunction */
#define FLS_APIID_GETJOBRESULT              ( ( uint8 )0x05U )     /* API ID of Fls_GetJobResult */
#define FLS_APIID_COMPARE                   ( ( uint8 )0x08U )     /* API ID of Fls_Compare */
#define FLS_APIID_SETMODE                   ( ( uint8 )0x09U )     /* API ID of Fls_SetMode */

/* error ID which is notified by the report function */
#define FLS_E_EXT_PARAM_CONFIG              ( ( uint8 )0x01U )      /* config parameter error notice *//* v1-0-1 */
#define FLS_E_EXT_PARAM_ADDRESS             ( ( uint8 )0x02U )      /* incorrect of the specified address */
#define FLS_E_EXT_PARAM_LENGTH              ( ( uint8 )0x03U )      /* incorrect of the specified data size */
#define FLS_E_EXT_PARAM_DATA                ( ( uint8 )0x04U )      /* incorrect of the specified data pointer(NULL_PTR) */
#define FLS_E_EXT_UNINIT                    ( ( uint8 )0x05U )      /* API was called at the state that a data Flash driver isn't initialized. */
#define FLS_E_EXT_BUSY                      ( ( uint8 )0x06U )      /* API calling when Data Flash driver state is "BUSY". */
#define FLS_E_EXT_ERASE_FATALFAILED         ( ( uint8 )0x80U )      /* Fatal erasure error */
#define FLS_E_EXT_WRITE_FATALFAILED         ( ( uint8 )0x81U )      /* Fatal write error */
#define FLS_E_EXT_USED_HSM                  ( ( uint8 )0x82U )      /* Error during HSM operation */
#define FLS_E_EXT_SUSPEND                   ( ( uint8 )0x83U )      /* Error during "suspending" or "suspended" */
#define FLS_E_EXT_ERASE_FAILED              ( ( uint8 )0x07U )      /* erasure error */
#define FLS_E_EXT_WRITE_FAILED              ( ( uint8 )0x08U )      /* write error */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    uint32      dummy;    /* < Flash hardware frequency in MHz */
} Fls_ConfigType;

typedef uint32 Fls_AddressType;
typedef uint32 Fls_LengthType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
/**** Prototype Declaration of opening to the public API ****/

#define FLS_START_SEC_CODE
#include <Fls_MemMap.h>

extern FUNC( void, FLS_CODE ) Fls_Init( P2CONST( Fls_ConfigType, AUTOMATIC, FLS_APPL_CONST ) ConfigPtr );

extern FUNC( Std_ReturnType, FLS_CODE ) Fls_Write( Fls_AddressType TargetAddress, P2CONST( uint8, AUTOMATIC, FLS_APPL_CONST ) SourceAddressPtr, Fls_LengthType Length );

#if ( FLS_READ_API == STD_ON )
extern FUNC( Std_ReturnType, FLS_CODE ) Fls_Read( Fls_AddressType SourceAddress, uint8* TargetAddressPtr, Fls_LengthType Length );
#endif /* FLS_READ_API == STD_ON */

extern FUNC( Std_ReturnType, FLS_CODE ) Fls_Erase( Fls_AddressType TargetAddress, Fls_LengthType Length );

#if ( FLS_CANCEL_API == STD_ON )   /* v1-0-1 */
extern FUNC( void, FLS_CODE ) Fls_Cancel( void );
#endif /* FLS_CANCEL_API == STD_ON */

#if ( FLS_GET_STATUS_API == STD_ON )
extern FUNC( MemIf_StatusType, FLS_CODE ) Fls_GetStatus( void );
#endif /* FLS_GET_STATUS_API == STD_ON */

extern FUNC( void, FLS_CODE ) Fls_MainFunction( void );

#if ( FLS_GET_JOB_RESULT_API == STD_ON )
extern FUNC( MemIf_JobResultType, FLS_CODE ) Fls_GetJobResult( void );
#endif /* FLS_GET_JOB_RESULT_API == STD_ON */

#if ( FLS_COMPARE_API == STD_ON )
extern FUNC( Std_ReturnType, FLS_CODE ) Fls_Compare( Fls_AddressType SourceAddress, P2CONST( uint8, AUTOMATIC, FLS_APPL_CONST ) TargetAddressPtr, Fls_LengthType Length );
#endif /* FLS_COMPARE_API == STD_ON */

#if ( FLS_SET_MODE_API == STD_ON )
extern FUNC( void, FLS_CODE ) Fls_SetMode( MemIf_ModeType Mode );
#endif /* FLS_SET_MODE_API == STD_ON */

#if ( FLS_VERSION_INFO_API == STD_ON )
extern FUNC( void, FLS_CODE ) Fls_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, FLS_APPL_DATA ) VersioninfoPtr );
#endif /* FLS_VERSION_INFO_API == STD_ON */


#define FLS_STOP_SEC_CODE
#include <Fls_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* FLS_H */


/****************************************************************************/
/* History                                                                  */
/* Version :Date                                                            */
/* [Number] :[Date]                                                         */
/****************************************************************************/

/**** End of File ***********************************************************/
