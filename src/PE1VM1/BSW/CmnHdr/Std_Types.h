/* Std_Types_h_v2-0-0                                                       */
/****************************************************************************/
/* Protected                                                                */
/* Copyright AUBASS CO., LTD.                                               */
/****************************************************************************/

/****************************************************************************/
/* Object Name  | Std_Types/HEADER                                          */
/*--------------------------------------------------------------------------*/
/* Notes        |                                                           */
/****************************************************************************/

#ifndef STD_TYPES_H         /* SWS_Std_00014 */
#define STD_TYPES_H         /* SWS_Std_00014 */

/*--------------------------------------------------------------------------*/
/* Include Files                                                            */
/*--------------------------------------------------------------------------*/

#include <Compiler.h>
#include <Platform_Types.h>

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* AUTOSAR specification version information [SWS_BSW_00059] */
#define STD_VENDOR_ID                    (0x0053U)
#define STD_MODULE_ID                    (0x00C5U)
#define STD_AR_RELEASE_MAJOR_VERSION     (4U)
#define STD_AR_RELEASE_MINOR_VERSION     (5U)
#define STD_AR_RELEASE_REVISION_VERSION  (0U)

/* File version information [SWS_BSW_00059] */
#define STD_SW_MAJOR_VERSION  (2U)
#define STD_SW_MINOR_VERSION  (0U)
#define STD_SW_PATCH_VERSION  (0U)

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

/* Std_TransformerErrorCode */
typedef uint8                           Std_TransformerErrorCode;

/* Std_TransformerClass */
typedef uint8                           Std_TransformerClass;

/* Std_TransformerError */
typedef struct 
{
    VAR(Std_TransformerErrorCode, TYPEDEF)  errorCode;
    VAR(Std_TransformerClass, TYPEDEF)      transformerClass;
} Std_TransformerError;

/*--------------------------------------------------------------------------*/
/* Macros                                                                   */
/*--------------------------------------------------------------------------*/
/* E_OK, E_NOT_OK - SWS_Std_00006 */
#ifndef STATUSTYPEDEFINED 
#define STATUSTYPEDEFINED 
#define E_OK       ( 0x00U )
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

/* range of Std_TransformerClass */
#define STD_TRANSFORMER_UNSPECIFIED  ( 0x00U )          /* unspecified */
#define STD_TRANSFORMER_SERIALIZER   ( 0x01U )          /* serializer */
#define STD_TRANSFORMER_SAFETY       ( 0x02U )          /* safety */
#define STD_TRANSFORMER_SECURITY     ( 0x03U )          /* security */
#define STD_TRANSFORMER_CUSTOM       ( 0xFFU )          /* custom */

/*--------------------------------------------------------------------------*/
/* Function Prototypes                                                      */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Data                                                                     */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* Constants                                                                */
/*--------------------------------------------------------------------------*/


#endif    /* STD_TYPES_H *//* SWS_Std_00014 */


/****************************************************************************/
/* History                                                                  */
/*  Version        :Date                                                    */
/*  v1-0-0         :2017/10/07                                              */
/*  v2-0-0         :2020/12/31                                              */
/****************************************************************************/

/**** End of File ***********************************************************/
