/***************************************************************************
[ Std_Types.h ] - Standard Type header file
****************************************************************************/

#ifndef STD_TYPES_H         /* SWS_Std_00014 */
#define STD_TYPES_H         /* SWS_Std_00014 */

#include "Compiler.h"       /* SWS_Std_00019 */
#include "Platform_Types.h" /* SWS_Std_00019 */

/*-----------------------------------------------------------------------------
    Type definitions
 -----------------------------------------------------------------------------*/
/* Std_Rerturn_Type - SWS_Std_00005, SWS_Std_00011 */
typedef uint8                           Std_ReturnType;

/* Std_VersionInfoType - SWS_Std_00015 */
struct Std_VersionInfoType_tag
{
    uint16                              vendorID;
    uint16                              moduleID;
    uint8                               sw_major_version;
    uint8                               sw_minor_version;
    uint8                               sw_patch_version;
};

typedef struct Std_VersionInfoType_tag  Std_VersionInfoType;

/*-----------------------------------------------------------------------------
    Symbol definitions
 -----------------------------------------------------------------------------*/
/* E_OK, E_NOT_OK - SWS_Std_00006 */
#ifndef STATUSTYPEDEFINED 
 #define STATUSTYPEDEFINED 
 #define E_OK  (0x00u)
 typedef unsigned char StatusType; /* OSEK compliance */ 
#endif

#define E_NOT_OK    (0x01u)

/* STD_LOW, STD_HIGH - SWS_Std_00007 */
#define STD_HIGH    (0x01u)           /* Physical state 5V or 3.3V */
#define STD_LOW     (0x00u)           /* Physical state 0V */

/* STD_IDLE, STD_ACTIVE - SWS_Std_00013 */
#define STD_ACTIVE  (0x01u)           /* Logical state active */
#define STD_IDLE    (0x00u)           /* Logical state idle */

/* STD_OFF, STD_ON -  SWS_Std_00010 */
#define STD_ON      (0x01u)
#define STD_OFF     (0x00u)

#endif    /* STD_TYPES_H *//* SWS_Std_00014 */
