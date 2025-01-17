/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/
/****************************************************************************/
/* Object Name | Std_Types/HEADER                                           */
/*----------------------------------------------------------------          */
/* Revision History                                                         */
/*   Revision    :Date       :Description                                   */
/*   v0_0_1      :2016/09/14 :New created                                   */
/*   v0_0_2      :2022/12/06 :Update                                        */
/*----------------------------------------------------------------          */
/* Notes                                                                    */
/****************************************************************************/

#ifndef STD_TYPES_H         /* SWS_Std_00014 */
#define STD_TYPES_H         /* SWS_Std_00014 */

#include <Compiler.h>       /* SWS_Std_00019 */
#include <Platform_Types.h> /* SWS_Std_00019 */

/*-----------------------------------------------------------------------------
    Type definitions
 -----------------------------------------------------------------------------*/
/* Std_Return_Type - SWS_Std_00005, SWS_Std_00011 */
typedef uint8                           Std_ReturnType;

/* Std_VersionInfoType - SWS_Std_00015 */
typedef struct {
    VAR(uint16, TYPEDEF)                vendorID;
    VAR(uint16, TYPEDEF)                moduleID;
    VAR(uint8, TYPEDEF)                 sw_major_version;
    VAR(uint8, TYPEDEF)                 sw_minor_version;
    VAR(uint8, TYPEDEF)                 sw_patch_version;
} Std_VersionInfoType;

/*-----------------------------------------------------------------------------
    Symbol definitions
 -----------------------------------------------------------------------------*/
/* E_OK, E_NOT_OK - SWS_Std_00006 */
#ifndef STATUSTYPEDEFINED 
 #define STATUSTYPEDEFINED 
 #define E_OK      ( 0x00U )
 typedef unsigned char StatusType; /* OSEK compliance */ 
#endif

#define E_NOT_OK   ( 0x01U )

/* STD_LOW, STD_HIGH - SWS_Std_00007 */
#define STD_HIGH   ( 0x01U )          /* Physical state 5V or 3.3V */
#define STD_LOW    ( 0x00U )          /* Physical state 0V */

/* STD_IDLE, STD_ACTIVE - SWS_Std_00013 */
#define STD_ACTIVE ( 0x01U )          /* Logical state active */
#define STD_IDLE   ( 0x00U )          /* Logical state idle */

/* STD_OFF, STD_ON - SWS_Std_00010 */
#define STD_ON     ( 0x01U )
#define STD_OFF    ( 0x00U )

#endif    /* STD_TYPES_H *//* SWS_Std_00014 */
