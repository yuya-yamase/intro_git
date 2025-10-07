/* 1.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  RH850/U2A16 Option Byte Configuration                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RH850_U2A16_OPBT_CFG_C_MAJOR             (1)
#define RH850_U2A16_OPBT_CFG_C_MINOR             (0)
#define RH850_U2A16_OPBT_CFG_C_PATCH             (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define RH850_U2A16_OPBT_CFG_NWORD               (32U)
#define RH850_U2A16_OPBT_SEC_NWORD               (8U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef unsigned long      U4;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#pragma ghs section rodata=".rh850u2a16_opbt_cfg"

const U4      u4_gp_RH850_U2A16_OPBT_CFG[RH850_U2A16_OPBT_CFG_NWORD] = {
    (U4)0x003C0000U,             /*  0       -- Reset Vector (PE0)         Shipping : 0x00000000 [Modified]      */
    (U4)0x003C0000U,             /*  1       -- Reset Vector (PE1)         Shipping : 0x00000000 [Modified]      */
    (U4)0x003C0000U,             /*  2       -- Reset Vector (PE2)         Shipping : 0x00800000 [Modified]      */
    (U4)0x003C0000U,             /*  3       -- Reset Vector (PE3)         Shipping : 0x00800000 [Modified]      */
    (U4)0xFFFFFFFFU,             /*  4       -- Reserved                   Shipping : 0xFFFFFFFF                 */
    (U4)0xFFFFFFFFU,             /*  5       -- Reserved                   Shipping : 0xFFFFFFFF                 */
    (U4)0xFFFFFFFFU,             /*  6       -- Reserved                   Shipping : 0xFFFFFFFF                 */
    (U4)0xFFFFFFFFU,             /*  7       -- Reserved                   Shipping : 0xFFFFFFFF                 */
    (U4)0x3FF20010U,             /*  8       -- Option byte  0 (OPBT0)     Shipping : 0x3FF30010 [Modified]      */
    (U4)0xFFFB0000U,             /*  9       -- Option byte  1 (OPBT1)     Shipping : 0xF0FB0000 [Modified]      */
    (U4)0x7FFFFFFFU,             /* 10       -- Option byte  2 (OPBT2)     Shipping : 0x7FFFFFFF                 */
    (U4)0xF1FFF4FDU,             /* 11       -- Option byte  3 (OPBT3)     Shipping : 0xF1FFFEFE [Modified]      */
    (U4)0x0C0C0C0FU,             /* 12       -- Option byte  4 (OPBT4)     Shipping : 0x0C0C0C0F                 */
    (U4)0xFFFFFFFFU,             /* 13       -- Reserved                   Shipping : 0xFFFFFFFF                 */
    (U4)0xFFFF0FC0U,             /* 14       -- Option byte  6 (OPBT6)     Shipping : 0xFFFF0FC3 [Modified]      */
    (U4)0xFFC3FFFFU,             /* 15       -- Option byte  7 (OPBT7)     Shipping : 0xFFFFFFFF [Modified]      */
    (U4)0xFFFFFFFEU,             /* 16       -- Option byte  8 (OPBT8)     Shipping : 0xFFFFFFFE                 */
    (U4)0xFFF1FFFFU,             /* 17       -- Option byte  9 (OPBT9)     Shipping : 0xFFF1FFFF                 */
    (U4)0xF9FD288EU,             /* 18       -- Option byte 10 (OPBT10)    Shipping : 0xFBFD288E                 */
    (U4)0xEFFFFFFFU,             /* 19       -- Option byte 11 (OPBT11)    Shipping : 0xFFFFFFFF [Modified]      */
    (U4)0xFFFFFFFCU,             /* 20       -- Option byte 12 (OPBT12)    Shipping : 0xFFFFFFFD [CFM  = Double] */

#if   ((!defined(RH850_U2A16_OPBT_CFM_HSM)) || \
       (RH850_U2A16_OPBT_CFM_HSM == 0     ) || \
       (RH850_U2A16_OPBT_CFM_HSM == 1     ))
    (U4)0xFFFFFFFFU,             /* 21       -- Option byte 13 (OPBT13)    Shipping : 0xFFFFFFFF [Bank = A/C   ] */
#elif (RH850_U2A16_OPBT_CFM_HSM == 2)
    (U4)0xFFFFFFFCU,             /* 21       -- Option byte 13 (OPBT13)    Shipping : 0xFFFFFFFF [Bank = B/D   ] */
#else
#error "rh850u2a16_opbt.c : RH850_U2A16_OPBT_CFM_HSM shall be defined."
#endif

    (U4)0x00000192U,             /* 22       -- Option byte 14 (OPBT14)    Shipping : 0x00000192                 */
    (U4)0xFFFFFFFFU,             /* 23       -- Reserved                   Shipping : 0xFFFFFFFF                 */
    (U4)0x6FFFFFFFU,             /* 24       -- Option byte 16 (OPBT16)    Shipping : 0x6FFFFFFF                 */
    (U4)0xFFFFFFFFU,             /* 25       -- Option byte 17 (OPBT17)    Shipping : 0xFFFFFFFF                 */
    (U4)0xFFFFFFFFU,             /* 26       -- Option byte 18 (OPBT18)    Shipping : 0xFFFFFFFF                 */
    (U4)0xFFFFFFFFU,             /* 27       -- Option byte 19 (OPBT19)    Shipping : 0xFFFFFFFF                 */
    (U4)0xF088FF00U,             /* 28       -- Option byte 20 (OPBT20)    Shipping : 0xF088FF00                 */
    (U4)0x000000CCU,             /* 29       -- Option byte 21 (OPBT21)    Shipping : 0x000000CC                 */
    (U4)0xC000C000U,             /* 30       -- Option byte 22 (OPBT22)    Shipping : 0xC000C000                 */
    (U4)0xFFFFC000U              /* 31       -- Option byte 23 (OPBT23)    Shipping : 0xFFFFC000                 */ 
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#pragma ghs section rodata=".rh850u2a16_opbt_sec"

const U4      u4_gp_RH850_U2A16_OPBT_SEC[RH850_U2A16_OPBT_SEC_NWORD] = {
#if (RH850_U2A16_OPBT_CFM_HSM == 1)
    (U4)0x0fffffffU,             /*  0       -- ICUM_OPBT0                 Shipping : 0xffffffff */
    (U4)0x007d4000U,             /*  1       -- ICUM_OPBT1                 Shipping : 0xffffffff */
    (U4)0x007d0000U,             /*  2       -- ICUM_OPBT2                 Shipping : 0xffffffff */
    (U4)0xff280000U,             /*  3       -- ICUM_OPBT3                 Shipping : 0xffffffff */
    (U4)0xfffd7fc6U,             /*  4       -- ICUM_OPBT4                 Shipping : 0xffff7fef */
#else
    (U4)0xffffffffU,             /*  0       -- ICUM_OPBT0                 Shipping : 0xffffffff */
    (U4)0xffffffffU,             /*  1       -- ICUM_OPBT1                 Shipping : 0xffffffff */
    (U4)0xffffffffU,             /*  2       -- ICUM_OPBT2                 Shipping : 0xffffffff */
    (U4)0xffffffffU,             /*  3       -- ICUM_OPBT3                 Shipping : 0xffffffff */
    (U4)0xffff7fefU,             /*  4       -- ICUM_OPBT4                 Shipping : 0xffff7fef */
#endif    

    (U4)0xffffffffU,             /*  5       -- Reserved                   Shipping : 0xffffffff */
    (U4)0xffffffffU,             /*  6       -- Reserved                   Shipping : 0xffffffff */
    (U4)0xffffffffU              /*  7       -- Reserved                   Shipping : 0xffffffff */
};

#pragma ghs section rodata=default

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     9/30/2025  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
