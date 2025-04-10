/* 5.7.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert S_ACC                                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_ACC_C_MAJOR                      (5)
#define ALERT_S_ACC_C_MINOR                      (7)
#define ALERT_S_ACC_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_S_ACC_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_S_ACC.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_S_ACC_TT_CC_NUM_DST                (16U)
#define ALERT_S_ACC_TT_RCC_NUM_DST               (16U)
#define ALERT_S_ACC_TT_VD_NUM_DST                (36U)
#define ALERT_S_ACC_BC_NUM_DST                   (64U)
#define ALERT_S_ACC_PD_NUM_DST                   (25U)

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
static U4      u4_s_AlertS_accTtCcSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertS_accTtRccSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertS_accTtVdSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertS_accBcSrcchk   (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertS_accPdSrcchk   (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertS_accPdRwTx     (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_S_ACC_TT_CC_DST[ALERT_S_ACC_TT_CC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_ACC_TT_CC_ON_W,                                            /* 01 ON_W                                            */
    (U1)ALERT_REQ_S_ACC_TT_CC_ON_G,                                            /* 02 ON_G                                            */
    (U1)ALERT_REQ_S_ACC_TT_CC_ON_Y,                                            /* 03 ON_Y                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_S_ACC_TT_RCC_DST[ALERT_S_ACC_TT_RCC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_ACC_TT_RCC_ON_W,                                           /* 01 ON_W                                            */
    (U1)ALERT_REQ_S_ACC_TT_RCC_ON_G,                                           /* 02 ON_G                                            */
    (U1)ALERT_REQ_S_ACC_TT_RCC_ON_Y,                                           /* 03 ON_Y                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U4  u4_sp_ALERT_S_ACC_TT_VD_CRIT[ALERT_S_ACC_TT_VD_NUM_DST] = {
    (U4)0x00000000U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x00000008U,                                                           /* 01 ON_W_DST4                                       */
    (U4)0x0000000AU,                                                           /* 02 ON_G_DST4                                       */
    (U4)0x0000000CU,                                                           /* 03 ON_G_DST4                                       */
    (U4)0x0000000EU,                                                           /* 04 ON_G_DST4                                       */
    (U4)0x00000009U,                                                           /* 05 ON_W_DST4                                       */
    (U4)0x0000000BU,                                                           /* 06 ON_G_DST4                                       */
    (U4)0x0000000DU,                                                           /* 07 ON_G_DST4                                       */
    (U4)0x0000000FU,                                                           /* 08 ON_G_DST4                                       */
    (U4)0x00000010U,                                                           /* 09 ON_W_DST3                                       */
    (U4)0x00000012U,                                                           /* 10 ON_G_DST3                                       */
    (U4)0x00000014U,                                                           /* 11 ON_G_DST3                                       */
    (U4)0x00000016U,                                                           /* 12 ON_G_DST3                                       */
    (U4)0x00000011U,                                                           /* 13 ON_W_DST3                                       */
    (U4)0x00000013U,                                                           /* 14 ON_G_DST3                                       */
    (U4)0x00000015U,                                                           /* 15 ON_G_DST3                                       */
    (U4)0x00000017U,                                                           /* 16 ON_G_DST3                                       */
    (U4)0x00000018U,                                                           /* 17 ON_W_DST2                                       */
    (U4)0x0000001AU,                                                           /* 18 ON_G_DST2                                       */
    (U4)0x0000001CU,                                                           /* 19 ON_G_DST2                                       */
    (U4)0x0000001EU,                                                           /* 20 ON_G_DST2                                       */
    (U4)0x00000019U,                                                           /* 21 ON_W_DST2                                       */
    (U4)0x0000001BU,                                                           /* 22 ON_G_DST2                                       */
    (U4)0x0000001DU,                                                           /* 23 ON_G_DST2                                       */
    (U4)0x0000001FU,                                                           /* 24 ON_G_DST2                                       */
    (U4)0x00000020U,                                                           /* 25 ON_W_DST1                                       */
    (U4)0x00000022U,                                                           /* 26 ON_G_DST1                                       */
    (U4)0x00000024U,                                                           /* 27 ON_G_DST1                                       */
    (U4)0x00000026U,                                                           /* 28 ON_G_DST1                                       */
    (U4)0x00000021U,                                                           /* 29 ON_W_DST1                                       */
    (U4)0x00000023U,                                                           /* 30 ON_G_DST1                                       */
    (U4)0x00000025U,                                                           /* 31 ON_G_DST1                                       */
    (U4)0x00000027U,                                                           /* 32 ON_G_DST1                                       */
    (U4)0x00000040U,                                                           /* 33 UNKNOWN                                         */
    (U4)0x00000080U,                                                           /* 34 UNKNOWN                                         */
    (U4)0x000000C0U                                                            /* 35 UNKNOWN                                         */
};
static const U4  u4_sp_ALERT_S_ACC_TT_VD_MASK[ALERT_S_ACC_TT_VD_NUM_DST] = {
    (U4)0x000000FFU,                                                           /* 00 UNKNOWN                                         */
    (U4)0x000000FFU,                                                           /* 01 ON_W_DST4                                       */
    (U4)0x000000FFU,                                                           /* 02 ON_G_DST4                                       */
    (U4)0x000000FFU,                                                           /* 03 ON_G_DST4                                       */
    (U4)0x000000FFU,                                                           /* 04 ON_G_DST4                                       */
    (U4)0x000000FFU,                                                           /* 05 ON_W_DST4                                       */
    (U4)0x000000FFU,                                                           /* 06 ON_G_DST4                                       */
    (U4)0x000000FFU,                                                           /* 07 ON_G_DST4                                       */
    (U4)0x000000FFU,                                                           /* 08 ON_G_DST4                                       */
    (U4)0x000000FFU,                                                           /* 09 ON_W_DST3                                       */
    (U4)0x000000FFU,                                                           /* 10 ON_G_DST3                                       */
    (U4)0x000000FFU,                                                           /* 11 ON_G_DST3                                       */
    (U4)0x000000FFU,                                                           /* 12 ON_G_DST3                                       */
    (U4)0x000000FFU,                                                           /* 13 ON_W_DST3                                       */
    (U4)0x000000FFU,                                                           /* 14 ON_G_DST3                                       */
    (U4)0x000000FFU,                                                           /* 15 ON_G_DST3                                       */
    (U4)0x000000FFU,                                                           /* 16 ON_G_DST3                                       */
    (U4)0x000000FFU,                                                           /* 17 ON_W_DST2                                       */
    (U4)0x000000FFU,                                                           /* 18 ON_G_DST2                                       */
    (U4)0x000000FFU,                                                           /* 19 ON_G_DST2                                       */
    (U4)0x000000FFU,                                                           /* 20 ON_G_DST2                                       */
    (U4)0x000000FFU,                                                           /* 21 ON_W_DST2                                       */
    (U4)0x000000FFU,                                                           /* 22 ON_G_DST2                                       */
    (U4)0x000000FFU,                                                           /* 23 ON_G_DST2                                       */
    (U4)0x000000FFU,                                                           /* 24 ON_G_DST2                                       */
    (U4)0x000000FFU,                                                           /* 25 ON_W_DST1                                       */
    (U4)0x000000FFU,                                                           /* 26 ON_G_DST1                                       */
    (U4)0x000000FFU,                                                           /* 27 ON_G_DST1                                       */
    (U4)0x000000FFU,                                                           /* 28 ON_G_DST1                                       */
    (U4)0x000000FFU,                                                           /* 29 ON_W_DST1                                       */
    (U4)0x000000FFU,                                                           /* 30 ON_G_DST1                                       */
    (U4)0x000000FFU,                                                           /* 31 ON_G_DST1                                       */
    (U4)0x000000FFU,                                                           /* 32 ON_G_DST1                                       */
    (U4)0x000000C0U,                                                           /* 33 UNKNOWN                                         */
    (U4)0x000000C0U,                                                           /* 34 UNKNOWN                                         */
    (U4)0x000000C0U                                                            /* 35 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_S_ACC_TT_VD_DST[ALERT_S_ACC_TT_VD_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_W_DST4,                                       /* 01 ON_W_DST4                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST4,                                       /* 02 ON_G_DST4                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST4,                                       /* 03 ON_G_DST4                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST4,                                       /* 04 ON_G_DST4                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_W_DST4,                                       /* 05 ON_W_DST4                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST4,                                       /* 06 ON_G_DST4                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST4,                                       /* 07 ON_G_DST4                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST4,                                       /* 08 ON_G_DST4                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_W_DST3,                                       /* 09 ON_W_DST3                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST3,                                       /* 10 ON_G_DST3                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST3,                                       /* 11 ON_G_DST3                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST3,                                       /* 12 ON_G_DST3                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_W_DST3,                                       /* 13 ON_W_DST3                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST3,                                       /* 14 ON_G_DST3                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST3,                                       /* 15 ON_G_DST3                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST3,                                       /* 16 ON_G_DST3                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_W_DST2,                                       /* 17 ON_W_DST2                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST2,                                       /* 18 ON_G_DST2                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST2,                                       /* 19 ON_G_DST2                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST2,                                       /* 20 ON_G_DST2                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_W_DST2,                                       /* 21 ON_W_DST2                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST2,                                       /* 22 ON_G_DST2                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST2,                                       /* 23 ON_G_DST2                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST2,                                       /* 24 ON_G_DST2                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_W_DST1,                                       /* 25 ON_W_DST1                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST1,                                       /* 26 ON_G_DST1                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST1,                                       /* 27 ON_G_DST1                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST1,                                       /* 28 ON_G_DST1                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_W_DST1,                                       /* 29 ON_W_DST1                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST1,                                       /* 30 ON_G_DST1                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST1,                                       /* 31 ON_G_DST1                                       */
    (U1)ALERT_REQ_S_ACC_TT_VD_ON_G_DST1,                                       /* 32 ON_G_DST1                                       */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 33 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 34 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 35 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_S_ACC_BC_DST[ALERT_S_ACC_BC_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_S_ACC_BC_WARN,                                               /* 01 WARN                                            */
    (U1)ALERT_REQ_S_ACC_BC_CANCEL,                                             /* 02 CANCEL                                          */
    (U1)ALERT_REQ_S_ACC_BC_REQ_BRK,                                            /* 03 REQ_BRK                                         */
    (U1)ALERT_REQ_S_ACC_BC_OVER_SPD,                                           /* 04 OVER_SPD                                        */
    (U1)ALERT_REQ_S_ACC_BC_START_APRVAL,                                       /* 05 START_APRVAL                                    */
    (U1)ALERT_REQ_S_ACC_BC_START,                                              /* 06 START                                           */
    (U1)ALERT_REQ_S_ACC_BC_REQ_OPE,                                            /* 07 REQ_OPE                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 09 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 16 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 17 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 18 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 19 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 20 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 21 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 22 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 23 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 24 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 25 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 26 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 27 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 28 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 29 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 30 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 31 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 32 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 33 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 34 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 35 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 36 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 37 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 38 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 39 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 40 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 41 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 42 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 43 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 44 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 45 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 46 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 47 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 48 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 49 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 50 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 51 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 52 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 53 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 54 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 55 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 56 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 57 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 58 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 59 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 60 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 61 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 62 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 63 UNKNOWN                                         */
};
static const U4  u4_sp_ALERT_S_ACC_PD_CRIT[ALERT_S_ACC_PD_NUM_DST] = {
    (U4)0x00000082U,                                                           /* 00 REQ_BRK_RW                                      */
    (U4)0x00000087U,                                                           /* 01 CC_DSBL1_RW                                     */
    (U4)0x00000088U,                                                           /* 02 JST_ACT2_RW                                     */
    (U4)0x00000089U,                                                           /* 03 CC_DSBL2_RW                                     */
    (U4)0x0000008AU,                                                           /* 04 CC_DSBL3_RW                                     */
    (U4)0x0000008BU,                                                           /* 05 CC_DSBL4_RW                                     */
    (U4)0x0000008EU,                                                           /* 06 RSM_RW                                          */
    (U4)0x0000008FU,                                                           /* 07 RSM_UNAVA_RW                                    */
    (U4)0x00000090U,                                                           /* 08 REQ_BRK2_RW                                     */
    (U4)0x00000092U,                                                           /* 09 CC_ACT_RW                                       */
    (U4)0x00000093U,                                                           /* 10 SFT_P_AUTO_RW                                   */
    (U4)0x00000002U,                                                           /* 11 REQ_BRK                                         */
    (U4)0x00000003U,                                                           /* 12 CC_MLFNK1                                       */
    (U4)0x00000006U,                                                           /* 13 UNKNOWN_RW                                      */
    (U4)0x00000007U,                                                           /* 14 CC_DSBL1                                        */
    (U4)0x00000008U,                                                           /* 15 JST_ACT2                                        */
    (U4)0x00000009U,                                                           /* 16 CC_DSBL2                                        */
    (U4)0x0000000AU,                                                           /* 17 CC_DSBL3                                        */
    (U4)0x0000000BU,                                                           /* 18 CC_DSBL4                                        */
    (U4)0x0000000EU,                                                           /* 19 RSM                                             */
    (U4)0x0000000FU,                                                           /* 20 RSM_UNAVA                                       */
    (U4)0x00000010U,                                                           /* 21 REQ_BRK2                                        */
    (U4)0x00000012U,                                                           /* 22 CC_ACT                                          */
    (U4)0x00000013U,                                                           /* 23 SFT_P_AUTO                                      */
    (U4)0x00000080U                                                            /* 24 UNKNOWN_RW                                      */
};
static const U4  u4_sp_ALERT_S_ACC_PD_MASK[ALERT_S_ACC_PD_NUM_DST] = {
    (U4)0x00000FFFU,                                                           /* 00 REQ_BRK_RW                                      */
    (U4)0x00000FFFU,                                                           /* 01 CC_DSBL1_RW                                     */
    (U4)0x00000FFFU,                                                           /* 02 JST_ACT2_RW                                     */
    (U4)0x00000FFFU,                                                           /* 03 CC_DSBL2_RW                                     */
    (U4)0x00000FFFU,                                                           /* 04 CC_DSBL3_RW                                     */
    (U4)0x00000FFFU,                                                           /* 05 CC_DSBL4_RW                                     */
    (U4)0x00000FFFU,                                                           /* 06 RSM_RW                                          */
    (U4)0x00000FFFU,                                                           /* 07 RSM_UNAVA_RW                                    */
    (U4)0x00000FFFU,                                                           /* 08 REQ_BRK2_RW                                     */
    (U4)0x00000FFFU,                                                           /* 09 CC_ACT_RW                                       */
    (U4)0x00000FFFU,                                                           /* 10 SFT_P_AUTO_RW                                   */
    (U4)0x0000007FU,                                                           /* 11 REQ_BRK                                         */
    (U4)0x0000007FU,                                                           /* 12 CC_MLFNK1                                       */
    (U4)0x0000007FU,                                                           /* 13 UNKNOWN_RW                                      */
    (U4)0x0000007FU,                                                           /* 14 CC_DSBL1                                        */
    (U4)0x0000007FU,                                                           /* 15 JST_ACT2                                        */
    (U4)0x0000007FU,                                                           /* 16 CC_DSBL2                                        */
    (U4)0x0000007FU,                                                           /* 17 CC_DSBL3                                        */
    (U4)0x0000007FU,                                                           /* 18 CC_DSBL4                                        */
    (U4)0x0000007FU,                                                           /* 19 RSM                                             */
    (U4)0x0000007FU,                                                           /* 20 RSM_UNAVA                                       */
    (U4)0x0000007FU,                                                           /* 21 REQ_BRK2                                        */
    (U4)0x0000007FU,                                                           /* 22 CC_ACT                                          */
    (U4)0x0000007FU,                                                           /* 23 SFT_P_AUTO                                      */
    (U4)0x00000F80U                                                            /* 24 UNKNOWN_RW                                      */
};
static const U1  u1_sp_ALERT_S_ACC_PD_DST[ALERT_S_ACC_PD_NUM_DST] = {
    (U1)ALERT_REQ_S_ACC_PD_REQ_BRK_RW,                                         /* 00 REQ_BRK_RW                                      */
    (U1)ALERT_REQ_S_ACC_PD_CC_DSBL1_RW,                                        /* 01 CC_DSBL1_RW                                     */
    (U1)ALERT_REQ_S_ACC_PD_JST_ACT2_RW,                                        /* 02 JST_ACT2_RW                                     */
    (U1)ALERT_REQ_S_ACC_PD_CC_DSBL2_RW,                                        /* 03 CC_DSBL2_RW                                     */
    (U1)ALERT_REQ_S_ACC_PD_CC_DSBL3_RW,                                        /* 04 CC_DSBL3_RW                                     */
    (U1)ALERT_REQ_S_ACC_PD_CC_DSBL4_RW,                                        /* 05 CC_DSBL4_RW                                     */
    (U1)ALERT_REQ_S_ACC_PD_RSM_RW,                                             /* 06 RSM_RW                                          */
    (U1)ALERT_REQ_S_ACC_PD_RSM_UNAVA_RW,                                       /* 07 RSM_UNAVA_RW                                    */
    (U1)ALERT_REQ_S_ACC_PD_REQ_BRK2_RW,                                        /* 08 REQ_BRK2_RW                                     */
    (U1)ALERT_REQ_S_ACC_PD_CC_ACT_RW,                                          /* 09 CC_ACT_RW                                       */
    (U1)ALERT_REQ_S_ACC_PD_SFT_P_AUTO_RW,                                      /* 10 SFT_P_AUTO_RW                                   */
    (U1)ALERT_REQ_S_ACC_PD_REQ_BRK,                                            /* 11 REQ_BRK                                         */
    (U1)ALERT_REQ_S_ACC_PD_CC_MLFNK1,                                          /* 12 CC_MLFNK1                                       */
    (U1)ALERT_REQ_S_ACC_PD_UNKNOWN_RW,                                         /* 13 UNKNOWN_RW                                      */
    (U1)ALERT_REQ_S_ACC_PD_CC_DSBL1,                                           /* 14 CC_DSBL1                                        */
    (U1)ALERT_REQ_S_ACC_PD_JST_ACT2,                                           /* 15 JST_ACT2                                        */
    (U1)ALERT_REQ_S_ACC_PD_CC_DSBL2,                                           /* 16 CC_DSBL2                                        */
    (U1)ALERT_REQ_S_ACC_PD_CC_DSBL3,                                           /* 17 CC_DSBL3                                        */
    (U1)ALERT_REQ_S_ACC_PD_CC_DSBL4,                                           /* 18 CC_DSBL4                                        */
    (U1)ALERT_REQ_S_ACC_PD_RSM,                                                /* 19 RSM                                             */
    (U1)ALERT_REQ_S_ACC_PD_RSM_UNAVA,                                          /* 20 RSM_UNAVA                                       */
    (U1)ALERT_REQ_S_ACC_PD_REQ_BRK2,                                           /* 21 REQ_BRK2                                        */
    (U1)ALERT_REQ_S_ACC_PD_CC_ACT,                                             /* 22 CC_ACT                                          */
    (U1)ALERT_REQ_S_ACC_PD_SFT_P_AUTO,                                         /* 23 SFT_P_AUTO                                      */
    (U1)ALERT_REQ_S_ACC_PD_UNKNOWN_RW                                          /* 24 UNKNOWN_RW                                      */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_S_ACC_MTRX[5] = {
    {
        &u4_s_AlertS_accTtCcSrcchk,                                            /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_ACC_TT_CC_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_S_ACC_TT_CC_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertS_accTtRccSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_ACC_TT_RCC_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_S_ACC_TT_RCC_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertS_accTtVdSrcchk,                                            /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_S_ACC_TT_VD_MASK[0],                                      /* u4p_MASK                                           */
        &u4_sp_ALERT_S_ACC_TT_VD_CRIT[0],                                      /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_ACC_TT_VD_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_S_ACC_TT_VD_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertS_accBcSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_ACC_BC_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_S_ACC_BC_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertS_accPdSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertS_accPdRwTx,                                                /* fp_vd_XDST                                         */

        &u4_sp_ALERT_S_ACC_PD_MASK[0],                                         /* u4p_MASK                                           */
        &u4_sp_ALERT_S_ACC_PD_CRIT[0],                                         /* u4p_CRIT                                           */

        &u1_sp_ALERT_S_ACC_PD_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_S_ACC_PD_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_accTtCcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_accTtCcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_FCM1S39_RXCH0) && defined(ComConf_ComSignal_ACCCCSID)
    static const U2 u2_s_ALERT_ACCCCSID_TO_THRESH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_ACCCCSID_LSB_MSGSTS = (U1)2U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_FCM1S39_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_ACCCCSID_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_ACCCCSID, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_ACCCCSID_LSB_MSGSTS);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_FCM1S39_RXCH0) && defined(ComConf_ComSignal_ACCCCSID) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_accTtRccSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_accTtRccSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_FCM1S39_RXCH0) && defined(ComConf_ComSignal_ACCID)
    static const U2 u2_s_ALERT_ACCID_TO_THRESH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_ACCID_LSB_MSGSTS = (U1)2U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_FCM1S39_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_ACCID_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_ACCID, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_ACCID_LSB_MSGSTS);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_FCM1S39_RXCH0) && defined(ComConf_ComSignal_ACCID) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_accTtVdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_accTtVdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_TTVVD_TO_THRESH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_FCM1S39_LSB_MSGSTS = (U1)6U;
    static const U1 u1_s_ALERT_ACCDST_LSB_MSGSTS = (U1)3U;
    static const U1 u1_s_ALERT_ACCDTST1_LSB_MSGSTS = (U1)1U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_FCM1S39_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_TTVVD_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_ACCDTST2, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_ACCDTST1, &u1_t_sgnl);
    u4_t_src_chk |= ((U4)u1_t_sgnl << u1_s_ALERT_ACCDTST1_LSB_MSGSTS);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_ACCDST, &u1_t_sgnl);
    u4_t_src_chk |= ((U4)u1_t_sgnl << u1_s_ALERT_ACCDST_LSB_MSGSTS);

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_FCM1S39_LSB_MSGSTS);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_accBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_accBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_FCM1S40_RXCH0) && defined(ComConf_ComSignal_ACCBZRQ)
    static const U2 u2_s_ALERT_ACCBZRQ_TO_THRESH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_ACCBZRQ_LSB_MSGSTS = (U1)4U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_FCM1S40_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_ACCBZRQ_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_ACCBZRQ, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_ACCBZRQ_LSB_MSGSTS);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_PDU_RX_CAN_FCM1S40_RXCH0) && defined(ComConf_ComSignal_ACCBZRQ) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertS_accPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertS_accPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_PDU_RX_CAN_FCM1S40_RXCH0)
    static const U2 u2_s_ALERT_ACCMSG3_TO_THRESH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
#endif /* defined(OXCAN_PDU_RX_CAN_FCM1S40_RXCH0) */
    static const U1 u1_s_ALERT_ACCMSG3_LSB_MSGSTS = (U1)5U;
#if defined(ComConf_ComSignal_CCMSG)
    static const U1 u1_s_ALERT_CCMSG_LSB_VALUE    = (U1)7U;
#endif /* defined(ComConf_ComSignal_CCMSG) */
    static const U1 u1_s_ALERT_CCMSG_LSB_MSGSTS   = (U1)11U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

#if defined(OXCAN_PDU_RX_CAN_FCM1S40_RXCH0)
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_FCM1S40_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_ACCMSG3_TO_THRESH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#else
    u1_t_msgsts   = (U1)COM_NO_RX;
#endif /* defined(OXCAN_PDU_RX_CAN_FCM1S40_RXCH0) */

    u1_t_sgnl     = (U1)0U;
#if defined(ComConf_ComSignal_ACCMSG3)
    (void)Com_ReceiveSignal(ComConf_ComSignal_ACCMSG3, &u1_t_sgnl);
#endif /* defined(ComConf_ComSignal_ACCMSG3) */
    u4_t_src_chk  = (U4)u1_t_sgnl;

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_ACCMSG3_LSB_MSGSTS);

#if defined(OXCAN_PDU_RX_CAN_EHV1G40)
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1G40,
                                          (U2)OXCAN_RX_SYS_NRX_IGR,
                                          (U2)U2_MAX) & (U1)COM_NO_RX;
#else
    u1_t_msgsts   = (U1)COM_NO_RX;
#endif /* defined(OXCAN_PDU_RX_CAN_EHV1G40) */

#if defined(ComConf_ComSignal_CCMSG)
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_CCMSG, &u1_t_sgnl);
    u4_t_src_chk |= ((U4)u1_t_sgnl   << u1_s_ALERT_CCMSG_LSB_VALUE);
#endif /* defined(ComConf_ComSignal_CCMSG) */

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_CCMSG_LSB_MSGSTS);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertS_accPdRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertS_accPdRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U4 u4_s_ALERT_S_ACC_RW     = ((U4)((U4)1U << ALERT_REQ_S_ACC_PD_CC_MLFNK1     )
                                            |  (U4)((U4)1U << ALERT_REQ_S_ACC_PD_REQ_BRK_RW    )
                                            |  (U4)((U4)1U << ALERT_REQ_S_ACC_PD_CC_DSBL1_RW   )
                                            |  (U4)((U4)1U << ALERT_REQ_S_ACC_PD_JST_ACT2_RW   )
                                            |  (U4)((U4)1U << ALERT_REQ_S_ACC_PD_CC_DSBL2_RW   )
                                            |  (U4)((U4)1U << ALERT_REQ_S_ACC_PD_CC_DSBL3_RW   )
                                            |  (U4)((U4)1U << ALERT_REQ_S_ACC_PD_CC_DSBL4_RW   )
                                            |  (U4)((U4)1U << ALERT_REQ_S_ACC_PD_RSM_RW        )
                                            |  (U4)((U4)1U << ALERT_REQ_S_ACC_PD_RSM_UNAVA_RW  )
                                            |  (U4)((U4)1U << ALERT_REQ_S_ACC_PD_REQ_BRK2_RW   )
                                            |  (U4)((U4)1U << ALERT_REQ_S_ACC_PD_CC_ACT_RW     )
                                            |  (U4)((U4)1U << ALERT_REQ_S_ACC_PD_SFT_P_AUTO_RW )
                                            |  (U4)((U4)1U << ALERT_REQ_S_ACC_PD_UNKNOWN_RW    ));
    static const U1 u1_s_ALERT_S_ACC_RW_MSK = (U1)0x1FU;
    U4              u4_t_rw;
    U1              u1_t_sgnl;

    u4_t_rw = ((U4)1U << (u1_a_DST & u1_s_ALERT_S_ACC_RW_MSK));
    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U) &&
       ((u4_t_rw & u4_s_ALERT_S_ACC_RW  ) != (U4)0U)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_C_CW, &u1_t_sgnl);    /* COM Tx STUB delete */
#endif
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     3/17/2021  RI       New.                                                                                               */
/*  5.1.0    10/26/2021  KT       Update for 840B 1A(Version update).                                                                */
/*  5.2.0     1/ 6/2022  YN       Update for 840B MPT(Version update).                                                               */
/*  5.2.1     5/30/2022  KK       Update for 840B#2 1A(Version update).                                                              */
/*  5.2.2     8/ 4/2022  SAO      Update for 840B#2 1A(Version update).                                                              */
/*  5.3.0     3/ 9/2023  MY       Fix EHV1G40 / CCMSG compile switches.                                                              */
/*  5.4.0    11/10/2023  RO       Update for 19PFv3(Version update).                                                                 */
/*  5.5.0    02/14/2024  RO       Update for 19PFv3 CV.                                                                              */
/*  5.6.0     3/19/2024  RO       add Vehicle Dist.                                                                                  */
/*  5.7.0     4/11/2024  AA       Update condition of RW                                                                             */
/*                                                                                                                                   */
/*  * RI   = Ren Ito, NTTD MSE                                                                                                       */
/*  * KT   = Kenichi Takahashi, NTTD MSE                                                                                             */
/*  * YN   = Yuma Nagahara, NTTD MSE                                                                                                 */
/*  * KK   = Kenta Kawahara, NTTD MSE                                                                                                */
/*  * SAO  = Sachiko Oono, NTTD MSE                                                                                                  */
/*  * MY   = Masaki Yoshizawa, NTTD MSE                                                                                              */
/*  * RO   = Ryo Oohashi, KSE                                                                                                        */
/*  * AA   = Anna Asuncion, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
