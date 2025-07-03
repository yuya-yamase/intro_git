/* 1.1.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Renesas RH850/U2A : Input Caputure Wakeup Factor Detection                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ICU_DRV_WK_CFG_C_MAJOR                   (1)
#define ICU_DRV_WK_CFG_C_MINOR                   (1)
#define ICU_DRV_WK_CFG_C_PATCH                   (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "icu_drv_wk_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((ICU_DRV_WK_CFG_C_MAJOR != ICU_DRV_WK_CFG_H_MAJOR) || \
     (ICU_DRV_WK_CFG_C_MINOR != ICU_DRV_WK_CFG_H_MINOR) || \
     (ICU_DRV_WK_CFG_C_PATCH != ICU_DRV_WK_CFG_H_PATCH))
#error "icu_drv_wk_cfg.c and icu_drv_wk_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#pragma ghs section rodata=".ICU_RODATA_CONST"

const ST_ICU_WK           st_gp_ICU_WK_CFG[ICU_WK_NUM_CFG] = {
    /* ICU_WK_CFG_MCU_STA_BY_RST (0) */
    {
        /* u4p_elc[ICU_WK_ELC_NUM_WORD] */
        {
            (U4)0x00212100U,                     /* 0 : INTP[0]  - INTP[7]  */
            (U4)0x00000000U,                     /* 1 : INTP[8]  - INTP[15] */
            (U4)0x00000000U,                     /* 2 : INTP[16] - INTP[23] */
            (U4)0x00000000U,                     /* 3 : INTP[24] - INTP[31] */
            (U4)0x01000000U,                     /* 4 : INTP[32] - INTP[39] */
            (U4)0x00000000U                      /* 5 : NMI                 */
        },
        /* u4p_ena[ICU_WK_NUM_GR]       */
        {
            (U4)0x00000f00U,                     /* GR_A0 : WUFMSK0_A0      */
            (U4)0x00000000U,                     /* GR_A1 : WUFMSK0_A1      */
            (U4)0x00000000U                      /* GR_A2 : WUFMSK0_A2      */
        },
        /* ---------------------------------------------------------------------------------- */
        /* Warning :                                                                          */
        /*                                                                                    */
        /* When MCU reset is performed, all WkRQs shall be cleared. Otherwise, unexpected     */
        /* WkRQss could be read.                                                              */
        /* 1b = clear, 0b = not clear                                                         */
        /* ---------------------------------------------------------------------------------- */
        /* u4p_clr[ICU_WK_NUM_GR]       */
        {
            (U4)0xffffffffU,                     /* GR_A0 : WUFMSK0_A0      */
            (U4)0xffffffffU,                     /* GR_A1 : WUFMSK0_A1      */
            (U4)0xffffffffU                      /* GR_A2 : WUFMSK0_A2      */
        }
    },
    /* ICU_WK_CFG_MCU_STA_BY_WK (1) */
    {
        /* u4p_elc[ICU_WK_ELC_NUM_WORD] */
        {
            (U4)0x00212100U,                     /* 0 : INTP[0]  - INTP[7]  */
            (U4)0x00000000U,                     /* 1 : INTP[8]  - INTP[15] */
            (U4)0x00000000U,                     /* 2 : INTP[16] - INTP[23] */
            (U4)0x00000000U,                     /* 3 : INTP[24] - INTP[31] */
            (U4)0x01000000U,                     /* 4 : INTP[32] - INTP[39] */
            (U4)0x00000000U                      /* 5 : NMI                 */
        },
        /* u4p_ena[ICU_WK_NUM_GR]       */
        {
            (U4)0x00000f00U,                     /* GR_A0 : WUFMSK0_A0      */
            (U4)0x00000000U,                     /* GR_A1 : WUFMSK0_A1      */
            (U4)0x00000000U                      /* GR_A2 : WUFMSK0_A2      */
        },
        /* ---------------------------------------------------------------------------------- */
        /* Warning :                                                                          */
        /*                                                                                    */
        /* When MCU reset is performed, all WkRQs shall be cleared. Otherwise, unexpected     */
        /* WkRQss could be read.                                                              */
        /* 1b = clear, 0b = not clear                                                         */
        /* ---------------------------------------------------------------------------------- */
        /* u4p_clr[ICU_WK_NUM_GR]       */
        {
            (U4)0xfffff0ffU,                     /* GR_A0 : WUFMSK0_A0      */
            (U4)0xffffffffU,                     /* GR_A1 : WUFMSK0_A1      */
            (U4)0xffffffffU                      /* GR_A2 : WUFMSK0_A2      */
        }
    },
    /* ICU_WK_CFG_PREP_MCU_TO_LPM (2) */
    {
        /* u4p_elc[ICU_WK_ELC_NUM_WORD] */
        {
            (U4)0x00212100U,                     /* 0 : INTP[0]  - INTP[7]  */
            (U4)0x00000000U,                     /* 1 : INTP[8]  - INTP[15] */
            (U4)0x00000000U,                     /* 2 : INTP[16] - INTP[23] */
            (U4)0x00000000U,                     /* 3 : INTP[24] - INTP[31] */
            (U4)0x00000000U,                     /* 4 : INTP[32] - INTP[39] */
            (U4)0x00000000U                      /* 5 : NMI                 */
        },
        /* u4p_ena[ICU_WK_NUM_GR]       */
        {
            (U4)0x00000f00U,                     /* GR_A0 : WUFMSK0_A0      */
            (U4)0x00000000U,                     /* GR_A1 : WUFMSK0_A1      */
            (U4)0x00000000U                      /* GR_A2 : WUFMSK0_A2      */
        },
        /* ---------------------------------------------------------------------------------- */
        /* Warning :                                                                          */
        /*                                                                                    */
        /* When MCU reset is performed, all WkRQs shall be cleared. Otherwise, unexpected     */
        /* WkRQss could be read.                                                              */
        /* 1b = clear, 0b = not clear                                                         */
        /* ---------------------------------------------------------------------------------- */
        /* u4p_clr[ICU_WK_NUM_GR]       */
        {
            (U4)0xfffff0ffU,                     /* GR_A0 : WUFMSK0_A0      */
            (U4)0xffffffffU,                     /* GR_A1 : WUFMSK0_A1      */
            (U4)0xffffffffU                      /* GR_A2 : WUFMSK0_A2      */
        }
    }
};
const U1                      u1_g_ICU_WK_NUM_CFG = (U1)ICU_WK_NUM_CFG;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ICU_EL_P0                                (1U)
#define ICU_EL_P1                                (2U)
#define ICU_EL_P2                                (3U)
#define ICU_EL_P3                                (4U)
#define ICU_EL_P4                                (5U)
#define ICU_EL_P5                                (6U)
#define ICU_EL_P6                                (7U)
#define ICU_EL_P7                                (8U)
#define ICU_EL_P8                                (9U)
#define ICU_EL_P9                                (10U)
#define ICU_EL_P10                               (11U)
#define ICU_EL_P11                               (12U)
#define ICU_EL_P12                               (13U)
#define ICU_EL_P13                               (14U)
#define ICU_EL_P14                               (15U)
#define ICU_EL_P15                               (16U)
#define ICU_EL_P16                               (17U)
#define ICU_EL_P17                               (18U)
#define ICU_EL_P18                               (19U)
#define ICU_EL_P19                               (20U)
#define ICU_EL_P20                               (21U)
#define ICU_EL_P21                               (22U)
#define ICU_EL_P22                               (23U)
#define ICU_EL_P23                               (24U)
#define ICU_EL_P24                               (25U)
#define ICU_EL_P25                               (26U)
#define ICU_EL_P26                               (27U)
#define ICU_EL_P27                               (28U)
#define ICU_EL_P28                               (29U)
#define ICU_EL_P29                               (30U)
#define ICU_EL_P30                               (31U)
#define ICU_EL_P31                               (32U)
#define ICU_EL_P32                               (33U)
#define ICU_EL_P33                               (34U)
#define ICU_EL_P34                               (35U)
#define ICU_EL_P35                               (36U)
#define ICU_EL_P36                               (37U)
#define ICU_EL_P37                               (38U)
#define ICU_EL_P38                               (39U)
#define ICU_EL_P39                               (40U)

#define ICU_NUM_EL                               (41U)
const ST_ICU_EL            st_gp_ICU_EL[ICU_NUM_EL] = {
/*  u4_wrqbit,          u2_ro,       u1_irq_off, u1_clsb        */
    {(U4)0x00000001U,   (U2)0x0000U, (U1)U1_MAX, (U1)160U},     /*   0 : WUF0_A0[0]  TNMI       */
    {(U4)0x00000040U,   (U2)0x0100U, (U1)0U,     (U1)0U  },     /*   1 : WUF0_A0[6]  INTP0      */
    {(U4)0x00000080U,   (U2)0x0104U, (U1)1U,     (U1)4U  },     /*   2 : WUF0_A0[7]  INTP1      */
    {(U4)0x00000100U,   (U2)0x0108U, (U1)2U,     (U1)8U  },     /*   3 : WUF0_A0[8]  INTP2      */
    {(U4)0x00000200U,   (U2)0x010CU, (U1)3U,     (U1)12U },     /*   4 : WUF0_A0[9]  INTP3      */
    {(U4)0x00000400U,   (U2)0x0110U, (U1)4U,     (U1)16U },     /*   5 : WUF0_A0[10] INTP4      */
    {(U4)0x00000800U,   (U2)0x0114U, (U1)5U,     (U1)20U },     /*   6 : WUF0_A0[11] INTP5      */
    {(U4)0x00001000U,   (U2)0x0118U, (U1)6U,     (U1)24U },     /*   7 : WUF0_A0[12] INTP6      */
    {(U4)0x00002000U,   (U2)0x011CU, (U1)7U,     (U1)28U },     /*   8 : WUF0_A0[13] INTP7      */
    {(U4)0x00004000U,   (U2)0x0200U, (U1)8U,     (U1)32U },     /*   9 : WUF0_A0[14] INTP8      */
    {(U4)0x00008000U,   (U2)0x0204U, (U1)9U,     (U1)36U },     /*  10 : WUF0_A0[15] INTP9      */
    {(U4)0x00010000U,   (U2)0x0208U, (U1)10U,    (U1)40U },     /*  11 : WUF0_A0[16] INTP10     */
    {(U4)0x00020000U,   (U2)0x020CU, (U1)11U,    (U1)44U },     /*  12 : WUF0_A0[17] INTP11     */
    {(U4)0x00040000U,   (U2)0x0210U, (U1)12U,    (U1)48U },     /*  13 : WUF0_A0[18] INTP12     */
    {(U4)0x00080000U,   (U2)0x0214U, (U1)13U,    (U1)52U },     /*  14 : WUF0_A0[19] INTP13     */
    {(U4)0x00100000U,   (U2)0x0218U, (U1)14U,    (U1)56U },     /*  15 : WUF0_A0[20] INTP14     */
    {(U4)0x00200000U,   (U2)0x021CU, (U1)15U,    (U1)60U },     /*  16 : WUF0_A0[21] INTP15     */
    {(U4)0x00000001U,   (U2)0x0300U, (U1)16U,    (U1)64U },     /*  17 : WUF0_A1[0]  INTP16     */
    {(U4)0x00000002U,   (U2)0x0304U, (U1)17U,    (U1)68U },     /*  18 : WUF0_A1[1]  INTP17     */
    {(U4)0x00000004U,   (U2)0x0308U, (U1)18U,    (U1)72U },     /*  19 : WUF0_A1[2]  INTP18     */
    {(U4)0x00000008U,   (U2)0x030CU, (U1)19U,    (U1)76U },     /*  20 : WUF0_A1[3]  INTP19     */
    {(U4)0x00000010U,   (U2)0x0310U, (U1)20U,    (U1)80U },     /*  21 : WUF0_A1[4]  INTP20     */
    {(U4)0x00000020U,   (U2)0x0314U, (U1)21U,    (U1)84U },     /*  22 : WUF0_A1[5]  INTP21     */
    {(U4)0x00000040U,   (U2)0x0318U, (U1)22U,    (U1)88U },     /*  23 : WUF0_A1[6]  INTP22     */
    {(U4)0x00000080U,   (U2)0x031CU, (U1)23U,    (U1)92U },     /*  24 : WUF0_A1[7]  INTP23     */
    {(U4)0x00000100U,   (U2)0x0400U, (U1)24U,    (U1)96U },     /*  25 : WUF0_A1[8]  INTP24     */
    {(U4)0x00000200U,   (U2)0x0404U, (U1)25U,    (U1)100U},     /*  26 : WUF0_A1[9]  INTP25     */
    {(U4)0x00000400U,   (U2)0x0408U, (U1)26U,    (U1)104U},     /*  27 : WUF0_A1[10] INTP26     */
    {(U4)0x00000800U,   (U2)0x040CU, (U1)27U,    (U1)108U},     /*  28 : WUF0_A1[11] INTP27     */
    {(U4)0x00001000U,   (U2)0x0410U, (U1)28U,    (U1)112U},     /*  29 : WUF0_A1[12] INTP28     */
    {(U4)0x00002000U,   (U2)0x0414U, (U1)29U,    (U1)116U},     /*  30 : WUF0_A1[13] INTP29     */
    {(U4)0x00004000U,   (U2)0x0418U, (U1)30U,    (U1)120U},     /*  31 : WUF0_A1[14] INTP30     */
    {(U4)0x00008000U,   (U2)0x041CU, (U1)31U,    (U1)124U},     /*  32 : WUF0_A1[15] INTP31     */
    {(U4)0x00010000U,   (U2)0x0500U, (U1)32U,    (U1)128U},     /*  33 : WUF0_A1[16] INTP32     */
    {(U4)0x00020000U,   (U2)0x0504U, (U1)33U,    (U1)132U},     /*  34 : WUF0_A1[17] INTP33     */
    {(U4)0x00040000U,   (U2)0x0508U, (U1)34U,    (U1)136U},     /*  35 : WUF0_A1[18] INTP34     */
    {(U4)0x00080000U,   (U2)0x050CU, (U1)35U,    (U1)140U},     /*  36 : WUF0_A1[19] INTP35     */
    {(U4)0x00100000U,   (U2)0x0510U, (U1)36U,    (U1)144U},     /*  37 : WUF0_A1[20] INTP36     */
    {(U4)0x00200000U,   (U2)0x0514U, (U1)37U,    (U1)148U},     /*  38 : WUF0_A1[21] INTP37     */
    {(U4)0x00400000U,   (U2)0x0518U, (U1)38U,    (U1)152U},     /*  39 : WUF0_A1[22] INTP38     */
    {(U4)0x00800000U,   (U2)0x051CU, (U1)39U,    (U1)156U}      /*  40 : WUF0_A1[23] INTP39     */
};
const U1                      u1_g_ICU_NUM_EL = (U1)ICU_NUM_EL;

const U1                      u1_gp_ICU_EL_BY_WK[ICU_WK_NUM_CH] = {
    (U1)U1_MAX,                 /* ICU_WK_CH_TNMI                        (0U)  */
    (U1)U1_MAX,
    (U1)U1_MAX,
    (U1)U1_MAX,
    (U1)U1_MAX,
    (U1)U1_MAX,
    (U1)ICU_EL_P0,              /* ICU_WK_CH_INTP0                       (6U)  */
    (U1)ICU_EL_P1,              /* ICU_WK_CH_INTP1                       (7U)  */
    (U1)ICU_EL_P2,              /* ICU_WK_CH_INTP2                       (8U)  */
    (U1)ICU_EL_P3,              /* ICU_WK_CH_INTP3                       (9U)  */
    (U1)ICU_EL_P4,              /* ICU_WK_CH_INTP4                       (10U) */
    (U1)ICU_EL_P5,              /* ICU_WK_CH_INTP5                       (11U) */
    (U1)ICU_EL_P6,              /* ICU_WK_CH_INTP6                       (12U) */
    (U1)ICU_EL_P7,              /* ICU_WK_CH_INTP7                       (13U) */
    (U1)ICU_EL_P8,              /* ICU_WK_CH_INTP8                       (14U) */
    (U1)ICU_EL_P9,              /* ICU_WK_CH_INTP9                       (15U) */
    (U1)ICU_EL_P10,             /* ICU_WK_CH_INTP10                      (16U) */
    (U1)ICU_EL_P11,             /* ICU_WK_CH_INTP11                      (17U) */
    (U1)ICU_EL_P12,             /* ICU_WK_CH_INTP12                      (18U) */
    (U1)ICU_EL_P13,             /* ICU_WK_CH_INTP13                      (19U) */
    (U1)ICU_EL_P14,             /* ICU_WK_CH_INTP14                      (20U) */
    (U1)ICU_EL_P15,             /* ICU_WK_CH_INTP15                      (21U) */
    (U1)U1_MAX,
    (U1)U1_MAX,
    (U1)U1_MAX,
    (U1)U1_MAX,
    (U1)U1_MAX,
    (U1)U1_MAX,
    (U1)U1_MAX,
    (U1)U1_MAX,
    (U1)U1_MAX,
    (U1)U1_MAX,
    (U1)ICU_EL_P16,             /* ICU_WK_CH_INTP16                      (32U) */
    (U1)ICU_EL_P17,             /* ICU_WK_CH_INTP17                      (33U) */
    (U1)ICU_EL_P18,             /* ICU_WK_CH_INTP18                      (34U) */
    (U1)ICU_EL_P19,             /* ICU_WK_CH_INTP19                      (35U) */
    (U1)ICU_EL_P20,             /* ICU_WK_CH_INTP20                      (36U) */
    (U1)ICU_EL_P21,             /* ICU_WK_CH_INTP21                      (37U) */
    (U1)ICU_EL_P22,             /* ICU_WK_CH_INTP22                      (38U) */
    (U1)ICU_EL_P23,             /* ICU_WK_CH_INTP23                      (39U) */
    (U1)ICU_EL_P24,             /* ICU_WK_CH_INTP24                      (40U) */
    (U1)ICU_EL_P25,             /* ICU_WK_CH_INTP25                      (41U) */
    (U1)ICU_EL_P26,             /* ICU_WK_CH_INTP26                      (42U) */
    (U1)ICU_EL_P27,             /* ICU_WK_CH_INTP27                      (43U) */
    (U1)ICU_EL_P28,             /* ICU_WK_CH_INTP28                      (44U) */
    (U1)ICU_EL_P29,             /* ICU_WK_CH_INTP29                      (45U) */
    (U1)ICU_EL_P30,             /* ICU_WK_CH_INTP30                      (46U) */
    (U1)ICU_EL_P31,             /* ICU_WK_CH_INTP31                      (47U) */
    (U1)ICU_EL_P32,             /* ICU_WK_CH_INTP32                      (48U) */
    (U1)ICU_EL_P33,             /* ICU_WK_CH_INTP33                      (49U) */
    (U1)ICU_EL_P34,             /* ICU_WK_CH_INTP34                      (50U) */
    (U1)ICU_EL_P35,             /* ICU_WK_CH_INTP35                      (51U) */
    (U1)ICU_EL_P36,             /* ICU_WK_CH_INTP36                      (52U) */
    (U1)ICU_EL_P37,             /* ICU_WK_CH_INTP37                      (53U) */
    (U1)ICU_EL_P38,             /* ICU_WK_CH_INTP38                      (54U) */
    (U1)ICU_EL_P39,             /* ICU_WK_CH_INTP39                      (55U) */
    (U1)U1_MAX,
    (U1)U1_MAX,
    (U1)U1_MAX,
    (U1)U1_MAX,
    (U1)U1_MAX,
    (U1)U1_MAX,
    (U1)U1_MAX,
    (U1)U1_MAX,                 /* ICU_WK_CH_WUTRG0                      (64U) */
    (U1)U1_MAX,                 /* ICU_WK_CH_WUTRG1                      (65U) */
    (U1)U1_MAX,                 /* ICU_WK_CH_INTDCUTDI                   (66U) */
    (U1)U1_MAX,                 /* ICU_WK_CH_INTTAUJ2I0                  (67U) */
    (U1)U1_MAX,                 /* ICU_WK_CH_INTTAUJ2I1                  (68U) */
    (U1)U1_MAX,                 /* ICU_WK_CH_INTTAUJ2I2                  (69U) */
    (U1)U1_MAX,                 /* ICU_WK_CH_INTTAUJ2I3                  (70U) */
    (U1)U1_MAX,                 /* ICU_WK_CH_INTTAUJ3I0                  (71U) */
    (U1)U1_MAX,                 /* ICU_WK_CH_INTTAUJ3I1                  (72U) */
    (U1)U1_MAX,                 /* ICU_WK_CH_INTTAUJ3I2                  (73U) */
    (U1)U1_MAX,                 /* ICU_WK_CH_INTTAUJ3I3                  (74U) */
    (U1)U1_MAX,                 /* ICU_WK_CH_INTRTCA01S                  (75U) */
    (U1)U1_MAX,                 /* ICU_WK_CH_INTRTCA0AL                  (76U) */
    (U1)U1_MAX,                 /* ICU_WK_CH_INTRTCA0R                   (77U) */
    (U1)U1_MAX,                 /* ICU_WK_CH_INTADCJ2I0                  (78U) */
    (U1)U1_MAX,                 /* ICU_WK_CH_INTADCJ2I1                  (79U) */
    (U1)U1_MAX,                 /* ICU_WK_CH_INTADCJ2I2                  (80U) */
    (U1)U1_MAX,                 /* ICU_WK_CH_INTADCJ2I3                  (81U) */
    (U1)U1_MAX                  /* ICU_WK_CH_INTADCJ2I4                  (82U) */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ICU_WK_GR            st_gp_ICU_WK_GR[ICU_WK_NUM_GR] = {
    {
        &st_gp_ICU_EL[ICU_EL_P0],                  /* stp_EL    */
        (U4)0x003FFFE1U,                           /* u4_wrqbit */
        (U4)0x003FFFC1U,                           /* u4_erqbit */
        (U2)ICU_EL_P16,                            /* u2_num_el */
        (U2)0x0000U                                /* u2_ro     */
    },
    {
        &st_gp_ICU_EL[ICU_EL_P16],                 /* stp_EL    */
        (U4)0x00FFFFFFU,                           /* u4_wrqbit */
        (U4)0x00FFFFFFU,                           /* u4_erqbit */
        ((U2)ICU_NUM_EL - (U2)ICU_EL_P16),         /* u2_num_el */
        (U2)0x0010U                                /* u2_ro     */
    },
    {
        vdp_PTR_NA,                                /* stp_EL    */
        (U4)0x0007FFFFU,                           /* u4_wrqbit */
        (U4)0x00000000U,                           /* u4_erqbit */
        (U2)0U,                                    /* u2_num_el */
        (U2)0x0020U                                /* u2_ro     */
    }
};

const ST_ICU_WK_INVLD       st_gp_ICU_WK_INVLD_GR[ICU_WK_NUM_INVLD_GR] =
{
    {   (U4)0xff98e120U,    (U4)0x003FFFE1U     },  /* WUF1_A0 */
    {   (U4)0xff98e130U,    (U4)0x003FFFFFU     },  /* WUF1_A1 */
    {   (U4)0xff98e140U,    (U4)0x0007FFFFU     },  /* WUF1_A2 */
    {   (U4)0xff98e200U,    (U4)0x0003FFFFU     },  /* WUF0_I0 */
    {   (U4)0xff98e320U,    (U4)0x0003FFFFU     },  /* WUF1_I0 */
    {   (U4)0xff98e210U,    (U4)0x00FFFFFFU     },  /* WUF0_I1 */
    {   (U4)0xff98e330U,    (U4)0x00FFFFFFU     }   /* WUF1_I1 */
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
/*  1.0.0    12/23/2021  TN       New                                                                                                */
/*  1.0.1     3/13/2023  KM       int_drv_wk v1.0.0 -> v1.0.1.                                                                       */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TN = Takashi Nagai, Denso                                                                                                      */
/*  * KM = Kazuyuki Makino, DENSO.                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
