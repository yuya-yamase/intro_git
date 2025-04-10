/* Fls_Cdd_h_Revision(v1_0_0)                                               */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS Corporation                                             */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | FLS/CDD/HEADER                                            */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef FLS_CDD_H
#define FLS_CDD_H


#include <Std_Types.h>
#include <Fls.h>
#include "../Fls/cfg/Fls_Cfg.h"
#include "../Fls/cfg/Fls_Cdd_Cfg.h"
#include "../Fls/cfg/Fls_Drv_Cfg.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
#define FLS_CDD_RSP_OK              ( ( Fls_Cdd_JobResultType )0x02U ) /* Normal end (Complex Driver) */
#define FLS_CDD_RSP_NG_PARAM        ( ( Fls_Cdd_JobResultType )0x03U ) /* Parameter error (Complex Driver) */
#define FLS_CDD_RSP_NG_BUSY         ( ( Fls_Cdd_JobResultType )0x04U ) /* Execution during the busy state (Complex Driver) */
#define FLS_CDD_RSP_NG_READ         ( ( Fls_Cdd_JobResultType )0x05U ) /* Read error (Complex Driver) */
#define FLS_CDD_RSP_NG_COMPARE      ( ( Fls_Cdd_JobResultType )0x06U ) /* Comparison error (Complex Driver) */
#define FLS_CDD_RSP_NG_BLANKCHECK   ( ( Fls_Cdd_JobResultType )0x07U ) /* Blank check error (Complex Driver) */
#define FLS_CDD_RSP_NG_INTERNAL     ( ( Fls_Cdd_JobResultType )0x08U ) /* Internal error (Complex Driver) */
#define FLS_CDD_RSP_NG_FATALFAILED  ( ( Fls_Cdd_JobResultType )0x09U ) /* Fatal error (Complex Driver) */
#define FLS_CDD_RSP_NG_AUTHID       ( ( Fls_Cdd_JobResultType )0x11U ) /* IDAuthentication  error (Complex Driver) */
#define FLS_CDD_RSP_NG_ALLBLANK     ( ( Fls_Cdd_JobResultType )0x14U ) /* All Blank error (Complex Driver) */

#define FLS_CDD_RSP_OK_SUSPENDED    ( ( Fls_Cdd_JobResultType )0x0AU ) /* Normal end(No Flash control/Suspend completion) */
#define FLS_CDD_RSP_NG_USED_HSM     ( ( Fls_Cdd_JobResultType )0x0BU ) /* Execution during HSM operation */
#define FLS_CDD_RSP_NG_SUSPEND      ( ( Fls_Cdd_JobResultType )0x0CU ) /* Unauthorized suspend state */
#define FLS_CDD_RSP_NO_SUSPEND      ( ( Fls_Cdd_SuspendStatusType )0x0EU ) /* Non-suspended state */
#define FLS_CDD_RSP_SUSPENDING      ( ( Fls_Cdd_SuspendStatusType )0x0FU ) /* The state in the suspend transition */
#define FLS_CDD_RSP_SUSPENDED       ( ( Fls_Cdd_SuspendStatusType )0x10U ) /* Suspended state */

/* API ID */
#define FLS_APIID_BLANKCHECK    ( ( uint8 )0x80U )      /* Blank check acquisition request */

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef struct {
    uint32 DataFlashID0;
    uint32 DataFlashID1;
    uint32 DataFlashID2;
    uint32 DataFlashID3;
    uint32 DataFlashID4;
    uint32 DataFlashID5;
    uint32 DataFlashID6;
    uint32 DataFlashID7;
}Fls_Cdd_DataFlashIDType;

typedef uint8 Fls_Cdd_JobResultType;
typedef uint8 Fls_Cdd_SuspendStatusType;

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define FLS_START_SEC_CODE
#include <Fls_MemMap.h>

#if ( FLS_CDD_READ_API == STD_ON )
extern FUNC( Fls_Cdd_JobResultType, FLS_CODE ) Fls_Cdd_Read(Fls_AddressType SourceAddress,  P2VAR( uint8, AUTOMATIC, FLS_APPL_DATA ) TargetAddressPtr, Fls_LengthType Length);
#endif /* FLS_CDD_READ_API == STD_ON */

#if ( FLS_CDD_COMPARE_API == STD_ON )
extern FUNC( Fls_Cdd_JobResultType, FLS_CODE ) Fls_Cdd_Compare(Fls_AddressType SourceAddress, P2CONST( uint8, AUTOMATIC, FLS_APPL_CONST ) TargetAddressPtr, Fls_LengthType Length);
#endif /* FLS_CDD_COMPARE_API == STD_ON */

#if ( FLS_CDD_BLANK_CHECK_API == STD_ON )
extern FUNC( Fls_Cdd_JobResultType, FLS_CODE ) Fls_Cdd_BlankCheck(Fls_AddressType TargetAddress, Fls_LengthType Length);
#endif /* FLS_CDD_BLANK_CHECK_API == STD_ON */

#if ( FLS_CDD_NOT_BLANK_ADDRESS_API == STD_ON )
extern FUNC( Fls_Cdd_JobResultType, FLS_CODE ) Fls_Cdd_NotBlankAddress(Fls_AddressType TargetAddress, Fls_LengthType Length, P2VAR( Fls_AddressType, AUTOMATIC, FLS_APPL_DATA ) NotBlankAddress);
#endif /* FLS_CDD_NOT_BLANK_ADDRESS_API == STD_ON */

#if ( FLS_CDD_SUSPEND_SYSTEM_API == STD_ON )
extern FUNC( Fls_Cdd_JobResultType, FLS_CODE ) Fls_Cdd_Suspend ( void );
extern FUNC( Fls_Cdd_JobResultType, FLS_CODE ) Fls_Cdd_Resume ( void );
extern FUNC( Fls_Cdd_SuspendStatusType, FLS_CODE ) Fls_Cdd_GetSuspendStatus(void);
#endif /* FLS_CDD_SUSPEND_SYSTEM_API == STD_ON */

#if ( FLS_CDD_AUTH_DFID_API == STD_ON )
extern FUNC( Fls_Cdd_JobResultType, FLS_CODE ) Fls_Cdd_AuthDFID( P2CONST( Fls_Cdd_DataFlashIDType, AUTOMATIC, FLS_APPL_CONST ) IDValue );
#endif/* FLS_CDD_AUTH_DFID_API == STD_ON */

#define FLS_STOP_SEC_CODE
#include <Fls_MemMap.h>
/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/

#endif /* FLS_CDD_H */


/****************************************************************************/
/* History                                                                  */
/* Version :Date                                                            */
/* [Number] :[Date]                                                         */
/****************************************************************************/

/**** End of File ***********************************************************/
