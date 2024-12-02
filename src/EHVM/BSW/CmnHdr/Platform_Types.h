/* Platform_Types_h_v2-0-0                                                  */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Platform_Types/HEADER                                     */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include "./Platform/Platform_Cfg.h"
#include "./Platform/Platform_ExtDefs.h"

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* AUTOSAR specification version information [SWS_BSW_00059] */
#define PLATFORM_VENDOR_ID                    (0x0053U)
#define PLATFORM_MODULE_ID                    (0x00C7U)
#define PLATFORM_AR_RELEASE_MAJOR_VERSION     (4U)
#define PLATFORM_AR_RELEASE_MINOR_VERSION     (5U)
#define PLATFORM_AR_RELEASE_REVISION_VERSION  (0U)

/* File version information [SWS_BSW_00059] */
#define PLATFORM_SW_MAJOR_VERSION  (2U)
#define PLATFORM_SW_MINOR_VERSION  (0U)
#define PLATFORM_SW_PATCH_VERSION  (0U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
typedef unsigned char                   boolean;            /* SWS_Platform_00027 */
                                                            /* SWS_Platform_00026 */
                                                            /* SWS_Platform_00060 */
typedef unsigned char                   uint8;              /* SWS_Platform_00013 */
typedef unsigned short                  uint16;             /* SWS_Platform_00014 */
typedef unsigned long                   uint32;             /* SWS_Platform_00015 */
#if ( PLATFORM_TYPEDEF_UINT64_ENABLE == PLATFORM_ON )
typedef unsigned long long              uint64;             /* SWS_Platform_00066 */
#endif
typedef signed char                     sint8;              /* SWS_Platform_00016 */
typedef signed short                    sint16;             /* SWS_Platform_00017 */
typedef signed long                     sint32;             /* SWS_Platform_00018 */
#if ( PLATFORM_TYPEDEF_SINT64_ENABLE == PLATFORM_ON )
typedef signed long long                sint64;             /* SWS_Platform_00067 */
#endif

typedef float                           float32;            /* SWS_Platform_00041 */
#if ( PLATFORM_TYPEDEF_FLOAT64_ENABLE == PLATFORM_ON )
typedef double                          float64;            /* SWS_Platform_00042 */
#endif

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/* CPU_BYTE_ORDER - SWS_Platform_00039 */
#define HIGH_BYTE_FIRST                ( 0U )               /* SWS_Platform_00050 */
#define LOW_BYTE_FIRST                 ( 1U )               /* SWS_Platform_00051 */

/* TRUE, FALSE - SWS_Platform_00034, SWS_Platform_00054, SWS_Platform_00055, SWS_Platform_00056 */
#ifndef TRUE
#define TRUE                           ( 1U )
#endif /* TRUE */

#ifndef FALSE
#define FALSE                          ( 0U )
#endif /* FALSE */

/* CPU_BYTE_ORDER - SWS_Platform_00046, SWS_Platform_00050, SWS_Platform_00051 */
#define CPU_BYTE_ORDER   LOW_BYTE_FIRST

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif /* PLATFORM_TYPES_H */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2017/10/07                                              */
/*  v2-0-0         :2020/12/31                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
