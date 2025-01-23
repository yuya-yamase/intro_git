/*
    Copyright (C) 2016 eSOL Co.,Ltd. Tokyo, Japan

    This software is protected by the law and the agreement concerning
    a Japanese country copyright method, an international agreement,
    and other intellectual property right and may be used and copied
    only in accordance with the terms of such license and with the inclusion
    of the above copyright notice.

    This software or any other copies thereof may not be provided
    or otherwise made available to any other person.  No title to
    and ownership of the software is hereby transferred.

    The information in this software is subject to change without
    notice and should not be construed as a commitment by eSOL Co.,Ltd.
*/
/***************************************************************************
[ Platform_Types_v850_gcc.h ] - Platform Type header file
****************************************************************************/

#ifndef PLATFORM_TYPES_V850_GCC_H_
#define PLATFORM_TYPES_V850_GCC_H_

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* AUTOSAR specification version information [SWS_BSW_00059] */
#define PLATFORM_VENDOR_ID                    (0x003DU)
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
typedef unsigned long long              uint64;             /* SWS_Platform_00066 */
typedef signed char                     sint8;              /* SWS_Platform_00016 */
typedef signed short                    sint16;             /* SWS_Platform_00017 */
typedef signed long                     sint32;             /* SWS_Platform_00018 */
typedef signed long long                sint64;             /* SWS_Platform_00067 */

typedef float                           float32;            /* SWS_Platform_00041 */
typedef double                          float64;            /* SWS_Platform_00042 */

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/

/* CPU_BYTE_ORDER - SWS_Platform_00057, SWS_Platform_00039 */
#define HIGH_BYTE_FIRST                ( 0U )               /* SWS_Platform_00050 */
#define LOW_BYTE_FIRST                 ( 1U )               /* SWS_Platform_00051 */

/* TRUE, FALSE - SWS_Platform_00034, SWS_Platform_00054, SWS_Platform_00055, SWS_Platform_00056 */
#ifndef TRUE
#define TRUE                           ( 1U )
#endif /* TRUE */

#ifndef FALSE
#define FALSE                          ( 0U )
#endif /* FALSE */

/*--------------------------------------------------------------------------*/
/*    Type definitions - No SWS (SWS_Platform_00009)                        */
/*--------------------------------------------------------------------------*/
#define CPU_BYTE_ORDER  LOW_BYTE_FIRST  /* SWS_Platform_00046, SWS_Platform_00050, SWS_Platform_00051, SWS_Platform_00057 */


#endif /* PLATFORM_TYPES_V850_GCC_H_ */
