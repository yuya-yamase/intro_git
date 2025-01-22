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
[ Std_Types_v850_ghs.h ] - Standerd Type header file
****************************************************************************/

#ifndef STD_TYPES_V850_GHS_H_
#define STD_TYPES_V850_GHS_H_

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* AUTOSAR specification version information  [SWS_BSW_00059] */
#define STD_VENDOR_ID                   (0x003DU)
#define STD_MODULE_ID                   (0x00C5U)
#define STD_AR_RELEASE_MAJOR_VERSION    (4U)
#define STD_AR_RELEASE_MINOR_VERSION    (5U)
#define STD_AR_RELEASE_REVISION_VERSION (0U)

/* File version information [SWS_BSW_00059] */
#define STD_SW_MAJOR_VERSION            (2U)
#define STD_SW_MINOR_VERSION            (0U)
#define STD_SW_PATCH_VERSION            (0U)

/*--------------------------------------------------------------------------*/
/* Types                                                                    */
/*--------------------------------------------------------------------------*/
/* Std_Rerturn_Type - SWS_Std_00005, SWS_Std_00011 */
typedef uint8                           Std_ReturnType;

/* Std_VersionInfoType - SWS_Std_00015 */
typedef struct
{
    VAR(uint16, TYPEDEF)                vendorID;
    VAR(uint16, TYPEDEF)                moduleID;
    VAR(uint8, TYPEDEF)                 sw_major_version;
    VAR(uint8, TYPEDEF)                 sw_minor_version;
    VAR(uint8, TYPEDEF)                 sw_patch_version;
} Std_VersionInfoType;

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* E_OK, E_NOT_OK - SWS_Std_00006 */
#ifndef STATUSTYPEDEFINED
 #define STATUSTYPEDEFINED
 #define E_OK      ( 0x00U )
 typedef unsigned char         StatusType; /* OSEK compliance */
#endif

#define E_NOT_OK   ( 0x01U )

/* STD_LOW, STD_HIGH - SWS_Std_00007 */
#define STD_HIGH   ( 0x01U )          /* Physical state 5V or 3.3V */
#define STD_LOW    ( 0x00U )          /* Physical state 0V */

/* STD_IDLE, STD_ACTIVE - SWS_Std_00013 */
#define STD_ACTIVE ( 0x01U )          /* Logical state active */
#define STD_IDLE   ( 0x00U )          /* Logical state idle */

/* STD_OFF, STD_ON -  SWS_Std_00010 */
#define STD_ON     ( 0x01U )
#define STD_OFF    ( 0x00U )

/* range of Std_TransformerClass */
#define STD_TRANSFORMER_UNSPECIFIED  ( 0x00U )          /* unspecified */
#define STD_TRANSFORMER_SERIALIZER   ( 0x01U )          /* serializer */
#define STD_TRANSFORMER_SAFETY       ( 0x02U )          /* safety */
#define STD_TRANSFORMER_SECURITY     ( 0x03U )          /* security */
#define STD_TRANSFORMER_CUSTOM       ( 0xFFU )          /* custom */

#endif    /* STD_TYPES_V850_GHS_H_ */
