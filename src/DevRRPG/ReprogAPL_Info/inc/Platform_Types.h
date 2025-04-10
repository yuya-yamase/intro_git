/***************************************************************************/
/*[ Platform_Types.h ] - Platform Type header file                         */
/***************************************************************************/

/*----------------------------------------------------------------------------*/
/*    SWS_Platform_00009 <NEC V850>                                           */
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*  Type definitions                                                          */
/*----------------------------------------------------------------------------*/
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

typedef unsigned long                   uint8_least;        /* SWS_Platform_00020 */
typedef unsigned long                   uint16_least;       /* SWS_Platform_00021 */
typedef unsigned long                   uint32_least;       /* SWS_Platform_00022 */
typedef signed long                     sint8_least;        /* SWS_Platform_00023 */
typedef signed long                     sint16_least;       /* SWS_Platform_00024 */
typedef signed long                     sint32_least;       /* SWS_Platform_00025 */

typedef float                           float32;            /* SWS_Platform_00041 */
typedef double                          float64;            /* SWS_Platform_00042 */

typedef uint8                           U1;
typedef uint16                          U2;
typedef uint32                          U4;

/*-----------------------------------------------------------------------------*/
/*    Symbol definitions                                                       */
/*-----------------------------------------------------------------------------*/

/* CPU_TYPE - SWS_Platform_00057, SWS_Platform_00064 */
#define CPU_TYPE_8                      (8U)                /* SWS_Platform_00045 */
#define CPU_TYPE_16                     (16U)               /* SWS_Platform_00045 */
#define CPU_TYPE_32                     (32U)               /* SWS_Platform_00045 */

/* CPU_BIT_ORDER - SWS_Platform_00057, SWS_Platform_00038 */
#define MSB_FIRST                       (0U)                /* SWS_Platform_00048 */
#define LSB_FIRST                       (1U)                /* SWS_Platform_00049 */

/* CPU_BYTE_ORDER - SWS_Platform_00057, SWS_Platform_00039 */
#define HIGH_BYTE_FIRST                 (0U)                /* SWS_Platform_00050 */
#define LOW_BYTE_FIRST                  (1U)                /* SWS_Platform_00051 */

/* TRUE, FALSE - SWS_Platform_00034, SWS_Platform_00054, SWS_Platform_00055, SWS_Platform_00056 */
#ifndef TRUE
#define TRUE                            (1U)
#endif /* TRUE */

#ifndef FALSE
#define FALSE                           (0U)
#endif /* FALSE */


/*-----------------------------------------------------------------------------*/
/*    Type definitions - SWS_Platform_00009                                    */
/*-----------------------------------------------------------------------------*/
#define CPU_TYPE         CPU_TYPE_32      /* SWS_Platform_00044, SWS_Platform_00045, SWS_Platform_00057 */
#define CPU_BIT_ORDER    LSB_FIRST        /* SWS_Platform_00043, SWS_Platform_00048, SWS_Platform_00049, SWS_Platform_00057 */
#define CPU_BYTE_ORDER   LOW_BYTE_FIRST   /* SWS_Platform_00046, SWS_Platform_00050, SWS_Platform_00051, SWS_Platform_00057 */

