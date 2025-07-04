/* 5.6.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert B_SMASTA                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_SMASTA_C_MAJOR                 (5)
#define ALERT_B_SMASTA_C_MINOR                 (6)
#define ALERT_B_SMASTA_C_PATCH                 (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"
#include "alert_brx.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "oxcan_channel_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_B_SMASTA_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_B_SMASTA.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_B_SMASTA_S1B_NUM_DST               (14U)
#define ALERT_B_SMASTA_S1IG_NUM_DST              (64U)
#define ALERT_B_SMASTA_S2B_NUM_DST               (64U)
#define ALERT_B_SMASTA_S2IG_NUM_DST              (14U)
#define ALERT_B_SMASTA_S3B_NUM_DST               (64U)
#define ALERT_B_SMASTA_S3IG_NUM_DST              (32U)
#define ALERT_B_SMASTA_BCDR_NUM_DST              (16U)
#define ALERT_B_SMASTA_BCI1_NUM_DST              (16U)
#define ALERT_B_SMASTA_BCI2_NUM_DST              (8U)
#define ALERT_B_SMASTA_BCI3_NUM_DST              (16U)
#define ALERT_B_SMASTA_BCS1_NUM_DST              (16U)
#define ALERT_B_SMASTA_BCS2_NUM_DST              (16U)
#define ALERT_B_SMASTA_ASDW_NUM_DST              (8U)
#define ALERT_B_SMASTA_BCD1B_NUM_DST             (64U)
#define ALERT_B_SMASTA_BCD1IG_NUM_DST            (32U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_alert_smasta_sts_swr1;
static U1      u1_s_alert_smasta_sts_swr2;
static U1      u1_s_alert_smasta_sts_swr3;
static U1      u1_s_alert_smasta_sts_nspb;
static U1      u1_s_alert_smasta_sts_bzdn;
static U1      u1_s_alert_smasta_sts_bzdn3;
static U1      u1_s_alert_smasta_sts_bz;
static U1      u1_s_alert_smasta_sts_bz2;
static U1      u1_s_alert_smasta_sts_d_swr1;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertB_smastaS1bSrcchk   (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertB_smastaS1igSrcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertB_smastaS2bSrcchk   (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertB_smastaS2igSrcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertB_smastaS3bSrcchk   (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertB_smastaS3igSrcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertB_smastaBcdrSrcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertB_smastaBci1Srcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertB_smastaBci2Srcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertB_smastaBci3Srcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertB_smastaBcs1Srcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertB_smastaBcs2Srcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertB_smastaAsdwSrcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertB_smastaBcd1bSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertB_smastaBcd1igSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertB_smastaS1igRwTx    (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);
static void    vd_s_AlertB_smastaAsdwRwTx    (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);
static void    vd_s_AlertB_smastaBcd1igRwTx  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4  u4_sp_ALERT_B_SMASTA_S1B_CRIT[ALERT_B_SMASTA_S1B_NUM_DST] = {
    (U4)0x02000001U,                                                           /* 00 MALFUNC                                         */
    (U4)0x02000002U,                                                           /* 01 NOTRELC                                         */
    (U4)0x02000003U,                                                           /* 02 NOTRELH                                         */
    (U4)0x02000004U,                                                           /* 03 CP_AT_NG                                        */
    (U4)0x02000005U,                                                           /* 04 CP_MT_NG                                        */
    (U4)0x02000006U,                                                           /* 05 BX_AT_NG                                        */
    (U4)0x02000007U,                                                           /* 06 NOTKEY                                          */
    (U4)0x0200000AU,                                                           /* 07 BATKEY                                          */
    (U4)0x0200000BU,                                                           /* 08 S_ENG1                                          */
    (U4)0x0200000CU,                                                           /* 09 S_ENG2                                          */
    (U4)0x0200000DU,                                                           /* 10 S_ENG3                                          */
    (U4)0x0200001BU,                                                           /* 11 BX_MT_NG                                        */
    (U4)0x0200001CU,                                                           /* 12 OT_AT_NG                                        */
    (U4)0x0200001DU                                                            /* 13 OT_MT_NG                                        */
};
static const U4  u4_sp_ALERT_B_SMASTA_S1B_MASK[ALERT_B_SMASTA_S1B_NUM_DST] = {
    (U4)0x0200003FU,                                                           /* 00 MALFUNC                                         */
    (U4)0x0200003FU,                                                           /* 01 NOTRELC                                         */
    (U4)0x0200003FU,                                                           /* 02 NOTRELH                                         */
    (U4)0x0200003FU,                                                           /* 03 CP_AT_NG                                        */
    (U4)0x0200003FU,                                                           /* 04 CP_MT_NG                                        */
    (U4)0x0200003FU,                                                           /* 05 BX_AT_NG                                        */
    (U4)0x0200003FU,                                                           /* 06 NOTKEY                                          */
    (U4)0x0200003FU,                                                           /* 07 BATKEY                                          */
    (U4)0x0200003FU,                                                           /* 08 S_ENG1                                          */
    (U4)0x0200003FU,                                                           /* 09 S_ENG2                                          */
    (U4)0x0200003FU,                                                           /* 10 S_ENG3                                          */
    (U4)0x0200003FU,                                                           /* 11 BX_MT_NG                                        */
    (U4)0x0200003FU,                                                           /* 12 OT_AT_NG                                        */
    (U4)0x0200003FU                                                            /* 13 OT_MT_NG                                        */
};
static const U1  u1_sp_ALERT_B_SMASTA_S1B_DST[ALERT_B_SMASTA_S1B_NUM_DST] = {
    (U1)ALERT_REQ_B_SMASTA_S1B_MALFUNC,                                        /* 00 MALFUNC                                         */
    (U1)ALERT_REQ_B_SMASTA_S1B_NOTRELC,                                        /* 01 NOTRELC                                         */
    (U1)ALERT_REQ_B_SMASTA_S1B_NOTRELH,                                        /* 02 NOTRELH                                         */
    (U1)ALERT_REQ_B_SMASTA_S1B_CP_AT_NG,                                       /* 03 CP_AT_NG                                        */
    (U1)ALERT_REQ_B_SMASTA_S1B_CP_MT_NG,                                       /* 04 CP_MT_NG                                        */
    (U1)ALERT_REQ_B_SMASTA_S1B_BX_AT_NG,                                       /* 05 BX_AT_NG                                        */
    (U1)ALERT_REQ_B_SMASTA_S1B_NOTKEY,                                         /* 06 NOTKEY                                          */
    (U1)ALERT_REQ_B_SMASTA_S1B_BATKEY,                                         /* 07 BATKEY                                          */
    (U1)ALERT_REQ_B_SMASTA_S1B_S_ENG1,                                         /* 08 S_ENG1                                          */
    (U1)ALERT_REQ_B_SMASTA_S1B_S_ENG2,                                         /* 09 S_ENG2                                          */
    (U1)ALERT_REQ_B_SMASTA_S1B_S_ENG3,                                         /* 10 S_ENG3                                          */
    (U1)ALERT_REQ_B_SMASTA_S1B_BX_MT_NG,                                       /* 11 BX_MT_NG                                        */
    (U1)ALERT_REQ_B_SMASTA_S1B_OT_AT_NG,                                       /* 12 OT_AT_NG                                        */
    (U1)ALERT_REQ_B_SMASTA_S1B_OT_MT_NG                                        /* 13 OT_MT_NG                                        */
};
static const U1  u1_sp_ALERT_B_SMASTA_S1IG_DST[ALERT_B_SMASTA_S1IG_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_B_SMASTA_S1IG_MALFNC,                                        /* 01 MALFNC                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
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
    (U1)ALERT_REQ_B_SMASTA_S1IG_NOTICE,                                        /* 14 NOTICE                                          */
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
static const U1  u1_sp_ALERT_B_SMASTA_S2B_DST[ALERT_B_SMASTA_S2B_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
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
    (U1)ALERT_REQ_B_SMASTA_S2B_POWOFF,                                         /* 33 POWOFF                                          */
    (U1)ALERT_REQ_B_SMASTA_S2B_PARK1,                                          /* 34 PARK1                                           */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 35 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 36 UNKNOWN                                         */
    (U1)ALERT_REQ_B_SMASTA_S2B_AUTO,                                           /* 37 AUTO                                            */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 38 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 39 UNKNOWN                                         */
    (U1)ALERT_REQ_B_SMASTA_S2B_RSTRT1,                                         /* 40 RSTRT1                                          */
    (U1)ALERT_REQ_B_SMASTA_S2B_RSTRT2,                                         /* 41 RSTRT2                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 42 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 43 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 44 UNKNOWN                                         */
    (U1)ALERT_REQ_B_SMASTA_S2B_RSTRT3,                                         /* 45 RSTRT3                                          */
    (U1)ALERT_REQ_B_SMASTA_S2B_DEALER,                                         /* 46 DEALER                                          */
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
static const U4  u4_sp_ALERT_B_SMASTA_S2IG_CRIT[ALERT_B_SMASTA_S2IG_NUM_DST] = {
    (U4)0x00000003U,                                                           /* 00 STOP                                            */
    (U4)0x000000A4U,                                                           /* 01 EVSTOP                                          */
    (U4)0x000000E4U,                                                           /* 02 FCSTOP                                          */
    (U4)0x00000004U,                                                           /* 03 HVSTOP                                          */
    (U4)0x00000006U,                                                           /* 04 EMG                                             */
    (U4)0x000000A7U,                                                           /* 05 EV_EMG                                          */
    (U4)0x000000E7U,                                                           /* 06 FC_EMG                                          */
    (U4)0x00000007U,                                                           /* 07 HV_EMG                                          */
    (U4)0x0000000AU,                                                           /* 08 START                                           */
    (U4)0x0000000BU,                                                           /* 09 SAFE                                            */
    (U4)0x000000ACU,                                                           /* 10 EVSAFE                                          */
    (U4)0x000000ECU,                                                           /* 11 FCSAFE                                          */
    (U4)0x0000000CU,                                                           /* 12 HVSAFE                                          */
    (U4)0x0000000FU                                                            /* 13 SHIFTP                                          */
};
static const U4  u4_sp_ALERT_B_SMASTA_S2IG_MASK[ALERT_B_SMASTA_S2IG_NUM_DST] = {
    (U4)0x0000001FU,                                                           /* 00 STOP                                            */
    (U4)0x000003FFU,                                                           /* 01 EVSTOP                                          */
    (U4)0x000003FFU,                                                           /* 02 FCSTOP                                          */
    (U4)0x0000001FU,                                                           /* 03 HVSTOP                                          */
    (U4)0x0000001FU,                                                           /* 04 EMG                                             */
    (U4)0x000003FFU,                                                           /* 05 EV_EMG                                          */
    (U4)0x000003FFU,                                                           /* 06 FC_EMG                                          */
    (U4)0x0000001FU,                                                           /* 07 HV_EMG                                          */
    (U4)0x0000001FU,                                                           /* 08 START                                           */
    (U4)0x0000001FU,                                                           /* 09 SAFE                                            */
    (U4)0x000003FFU,                                                           /* 10 EVSAFE                                          */
    (U4)0x000003FFU,                                                           /* 11 FCSAFE                                          */
    (U4)0x0000001FU,                                                           /* 12 HVSAFE                                          */
    (U4)0x0000001FU                                                            /* 13 SHIFTP                                          */
};
static const U1  u1_sp_ALERT_B_SMASTA_S2IG_DST[ALERT_B_SMASTA_S2IG_NUM_DST] = {
    (U1)ALERT_REQ_B_SMASTA_S2IG_STOP,                                          /* 00 STOP                                            */
    (U1)ALERT_REQ_B_SMASTA_S2IG_EVSTOP,                                        /* 01 EVSTOP                                          */
    (U1)ALERT_REQ_B_SMASTA_S2IG_FCSTOP,                                        /* 02 FCSTOP                                          */
    (U1)ALERT_REQ_B_SMASTA_S2IG_HVSTOP,                                        /* 03 HVSTOP                                          */
    (U1)ALERT_REQ_B_SMASTA_S2IG_EMG,                                           /* 04 EMG                                             */
    (U1)ALERT_REQ_B_SMASTA_S2IG_EV_EMG,                                        /* 05 EV_EMG                                          */
    (U1)ALERT_REQ_B_SMASTA_S2IG_FC_EMG,                                        /* 06 FC_EMG                                          */
    (U1)ALERT_REQ_B_SMASTA_S2IG_HV_EMG,                                        /* 07 HV_EMG                                          */
    (U1)ALERT_REQ_B_SMASTA_S2IG_START,                                         /* 08 START                                           */
    (U1)ALERT_REQ_B_SMASTA_S2IG_SAFE,                                          /* 09 SAFE                                            */
    (U1)ALERT_REQ_B_SMASTA_S2IG_EVSAFE,                                        /* 10 EVSAFE                                          */
    (U1)ALERT_REQ_B_SMASTA_S2IG_FCSAFE,                                        /* 11 FCSAFE                                          */
    (U1)ALERT_REQ_B_SMASTA_S2IG_HVSAFE,                                        /* 12 HVSAFE                                          */
    (U1)ALERT_REQ_B_SMASTA_S2IG_SHIFTP                                         /* 13 SHIFTP                                          */
};
static const U1  u1_sp_ALERT_B_SMASTA_S3B_DST[ALERT_B_SMASTA_S3B_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
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
    (U1)ALERT_REQ_B_SMASTA_S3B_ENG1,                                           /* 33 ENG1                                            */
    (U1)ALERT_REQ_B_SMASTA_S3B_ENG2,                                           /* 34 ENG2                                            */
    (U1)ALERT_REQ_B_SMASTA_S3B_POW,                                            /* 35 POW                                             */
    (U1)ALERT_REQ_B_SMASTA_S3B_KEY,                                            /* 36 KEY                                             */
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
static const U1  u1_sp_ALERT_B_SMASTA_S3IG_DST[ALERT_B_SMASTA_S3IG_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_B_SMASTA_S3IG_NTRDY1,                                        /* 05 NTRDY1                                          */
    (U1)ALERT_REQ_B_SMASTA_S3IG_NTRDY2,                                        /* 06 NTRDY2                                          */
    (U1)ALERT_REQ_B_SMASTA_S3IG_NTRDY3,                                        /* 07 NTRDY3                                          */
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
    (U1)ALERT_REQ_UNKNOWN                                                      /* 31 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_B_SMASTA_BCDR_DST[ALERT_B_SMASTA_BCDR_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_B_SMASTA_BCDR_ON,                                            /* 09 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_B_SMASTA_BCI1_DST[ALERT_B_SMASTA_BCI1_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_B_SMASTA_BCI1_ON,                                            /* 09 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_B_SMASTA_BCI2_DST[ALERT_B_SMASTA_BCI2_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_B_SMASTA_BCI2_ON,                                            /* 01 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 07 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_B_SMASTA_BCI3_DST[ALERT_B_SMASTA_BCI3_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_B_SMASTA_BCI3_ON,                                            /* 09 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_B_SMASTA_BCS1_DST[ALERT_B_SMASTA_BCS1_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_B_SMASTA_BCS1_ON,                                            /* 09 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_B_SMASTA_BCS2_DST[ALERT_B_SMASTA_BCS2_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_B_SMASTA_BCS2_ON,                                            /* 09 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_B_SMASTA_ASDW_DST[ALERT_B_SMASTA_ASDW_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_B_SMASTA_ASDW_RW,                                            /* 01 RW                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 07 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_B_SMASTA_BCD1B_DST[ALERT_B_SMASTA_BCD1B_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
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
    (U1)ALERT_REQ_B_SMASTA_BCD1B_DGK_MAL,                                      /* 33 DGK_MAL                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 34 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 35 UNKNOWN                                         */
    (U1)ALERT_REQ_B_SMASTA_BCD1B_L_AT_NG,                                      /* 36 L_AT_NG                                         */
    (U1)ALERT_REQ_B_SMASTA_BCD1B_L_MT_NG,                                      /* 37 L_MT_NG                                         */
    (U1)ALERT_REQ_B_SMASTA_BCD1B_R_AT_NG,                                      /* 38 R_AT_NG                                         */
    (U1)ALERT_REQ_B_SMASTA_BCD1B_R_MT_NG,                                      /* 39 R_MT_NG                                         */
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
static const U1  u1_sp_ALERT_B_SMASTA_BCD1IG_DST[ALERT_B_SMASTA_BCD1IG_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_B_SMASTA_BCD1IG_RW,                                          /* 01 RW                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
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
    (U1)ALERT_REQ_UNKNOWN                                                      /* 31 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_B_SMASTA_MTRX[15] = {
    {
        &u4_s_AlertB_smastaS1bSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_B_SMASTA_S1B_MASK[0],                                     /* u4p_MASK                                           */
        &u4_sp_ALERT_B_SMASTA_S1B_CRIT[0],                                     /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_SMASTA_S1B_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_B_SMASTA_S1B_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertB_smastaS1igSrcchk,                                         /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertB_smastaS1igRwTx,                                           /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_SMASTA_S1IG_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_B_SMASTA_S1IG_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertB_smastaS2bSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_SMASTA_S2B_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_B_SMASTA_S2B_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertB_smastaS2igSrcchk,                                         /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_B_SMASTA_S2IG_MASK[0],                                    /* u4p_MASK                                           */
        &u4_sp_ALERT_B_SMASTA_S2IG_CRIT[0],                                    /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_SMASTA_S2IG_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_B_SMASTA_S2IG_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertB_smastaS3bSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_SMASTA_S3B_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_B_SMASTA_S3B_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertB_smastaS3igSrcchk,                                         /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_SMASTA_S3IG_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_B_SMASTA_S3IG_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertB_smastaBcdrSrcchk,                                         /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_SMASTA_BCDR_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_B_SMASTA_BCDR_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertB_smastaBci1Srcchk,                                         /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_SMASTA_BCI1_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_B_SMASTA_BCI1_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_AO                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertB_smastaBci2Srcchk,                                         /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_SMASTA_BCI2_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_B_SMASTA_BCI2_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertB_smastaBci3Srcchk,                                         /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_SMASTA_BCI3_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_B_SMASTA_BCI3_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertB_smastaBcs1Srcchk,                                         /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_SMASTA_BCS1_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_B_SMASTA_BCS1_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertB_smastaBcs2Srcchk,                                         /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_SMASTA_BCS2_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_B_SMASTA_BCS2_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertB_smastaAsdwSrcchk,                                         /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertB_smastaAsdwRwTx,                                           /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_SMASTA_ASDW_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_B_SMASTA_ASDW_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertB_smastaBcd1bSrcchk,                                        /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_SMASTA_BCD1B_DST[0],                                    /* u1p_DST                                            */
        (U2)ALERT_B_SMASTA_BCD1B_NUM_DST,                                      /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertB_smastaBcd1igSrcchk,                                       /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertB_smastaBcd1igRwTx,                                         /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_B_SMASTA_BCD1IG_DST[0],                                   /* u1p_DST                                            */
        (U2)ALERT_B_SMASTA_BCD1IG_NUM_DST,                                     /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertB_smastaInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertB_smastaInit(void)
{
    u1_s_alert_smasta_sts_swr1   = (U1)COM_NO_RX;
    u1_s_alert_smasta_sts_swr2   = (U1)COM_NO_RX;
    u1_s_alert_smasta_sts_swr3   = (U1)COM_NO_RX;
    u1_s_alert_smasta_sts_nspb   = (U1)COM_NO_RX;
    u1_s_alert_smasta_sts_bzdn   = (U1)COM_NO_RX;
    u1_s_alert_smasta_sts_bzdn3  = (U1)COM_NO_RX;
    u1_s_alert_smasta_sts_bz     = (U1)COM_NO_RX;
    u1_s_alert_smasta_sts_bz2    = (U1)COM_NO_RX;
    u1_s_alert_smasta_sts_d_swr1 = (U1)COM_NO_RX;
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_smastaS1bSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_smastaS1bSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_B_SMASTA_S1B_TO_TRSH = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_B_SMASTA_S1B_LSB_MSG = (U1)5U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_trns_fact;

    u1_t_trns_fact = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_IDT1S02_CH0,
                                      (U4)ALERT_CAN_SYS_PNC_ALL,
                                      u2_s_ALERT_B_SMASTA_S1B_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) == (U1)0U){
        u1_t_trns_fact |= (U1)ALERT_BRX_FACT_NO_RX;
    }
    vd_g_AlertBRxTrnsSts(&u1_s_alert_smasta_sts_swr1, u1_t_trns_fact);

    u1_t_sgnl      = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_SWR1, &u1_t_sgnl);
    u4_t_src_chk   = (U4)u1_t_sgnl;
    u4_t_src_chk  |= (((U4)u1_s_alert_smasta_sts_swr1 & (U4)COM_NO_RX) << u1_s_ALERT_B_SMASTA_S1B_LSB_MSG);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_smastaS1igSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_smastaS1igSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_B_SMASTA_S1I_LSB_MSG = (U1)5U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_IDT1S02_CH0,
                                     (U4)OXCAN_SYS_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_SWR1, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_B_SMASTA_S1I_LSB_MSG);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_smastaS2bSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_smastaS2bSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_B_SMASTA_S2B_TO_TRSH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_B_SMASTA_S2B_LSB_MSG  = (U1)4U;
    static const U4 u4_s_ALERT_B_SMASTA_S2B_B_BAT_WT = (U4)0x00000020U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_trns_fact;

    u1_t_trns_fact = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_IDT1S02_CH0,
                                      (U4)ALERT_CAN_SYS_PNC_ALL,
                                      u2_s_ALERT_B_SMASTA_S2B_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) == (U1)0U){
        u1_t_trns_fact |= (U1)ALERT_BRX_FACT_NO_RX;
    }
    vd_g_AlertBRxTrnsSts(&u1_s_alert_smasta_sts_swr2, u1_t_trns_fact);

    u1_t_sgnl      = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_SWR2, &u1_t_sgnl);
    u4_t_src_chk   = (U4)u1_t_sgnl;
    u4_t_src_chk  |= (((U4)u1_s_alert_smasta_sts_swr2 & (U4)COM_NO_RX) << u1_s_ALERT_B_SMASTA_S2B_LSB_MSG);

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk   |= u4_s_ALERT_B_SMASTA_S2B_B_BAT_WT;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_smastaS2igSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_smastaS2igSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_B_SMASTA_S2I_LSB_ENG1G13_MSG = (U1)9U;
    static const U1 u1_s_ALERT_B_SMASTA_S2I_LSB_PTSYS_SIG   = (U1)5U;
    static const U1 u1_s_ALERT_B_SMASTA_S2I_LSB_IDT1S02_MSG = (U1)4U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_ENG1G13_CH0,
                                     (U4)OXCAN_SYS_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_B_SMASTA_S2I_LSB_ENG1G13_MSG);

    u1_t_sgnl     = (U1)0U;
    u4_t_src_chk |= ((U4)u1_t_sgnl << u1_s_ALERT_B_SMASTA_S2I_LSB_PTSYS_SIG);

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_IDT1S02_CH0,
                                     (U4)OXCAN_SYS_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_B_SMASTA_S2I_LSB_IDT1S02_MSG);

    (void)Com_ReceiveSignal(ComConf_ComSignal_SWR2, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_smastaS3bSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_smastaS3bSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_B_SMASTA_S3B_TO_TRSH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_B_SMASTA_S3B_LSB_MSG  = (U1)4U;
    static const U4 u4_s_ALERT_B_SMASTA_S3B_B_BAT_WT = (U4)0x00000020U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_trns_fact;

    u1_t_trns_fact = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_IDT1S02_CH0,
                                      (U4)ALERT_CAN_SYS_PNC_ALL,
                                      u2_s_ALERT_B_SMASTA_S3B_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) == (U1)0U){
        u1_t_trns_fact |= (U1)ALERT_BRX_FACT_NO_RX;
    }
    vd_g_AlertBRxTrnsSts(&u1_s_alert_smasta_sts_swr3, u1_t_trns_fact);

    u1_t_sgnl      = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_SWR3, &u1_t_sgnl);
    u4_t_src_chk   = (U4)u1_t_sgnl;
    u4_t_src_chk  |= (((U4)u1_s_alert_smasta_sts_swr3 & (U4)COM_NO_RX) << u1_s_ALERT_B_SMASTA_S3B_LSB_MSG);

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk   |= u4_s_ALERT_B_SMASTA_S3B_B_BAT_WT;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_smastaS3igSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_smastaS3igSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_B_SMASTA_S3I_LSB_MSG = (U1)4U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_IDT1S02_CH0,
                                     (U4)OXCAN_SYS_IGR,
                                     (U2)U2_MAX) & (U1)COM_NO_RX;
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_SWR3, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_B_SMASTA_S3I_LSB_MSG);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_smastaBcdrSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_smastaBcdrSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_B_SMASTA_BDR_TO_TRSH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_B_SMASTA_BDR_LSB_MSG  = (U1)1U;
    static const U4 u4_s_ALERT_B_SMASTA_BDR_B_BAT_WT = (U4)0x00000008U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_IDT1S02_CH0,
                                     (U4)ALERT_CAN_SYS_PNC_ALL,
                                     u2_s_ALERT_B_SMASTA_BDR_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    vd_g_AlertBRxTrnsSts(&u1_s_alert_smasta_sts_nspb, u1_t_msgsts);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_NSPB, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_s_alert_smasta_sts_nspb << u1_s_ALERT_B_SMASTA_BDR_LSB_MSG);

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_B_SMASTA_BDR_B_BAT_WT;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_smastaBci1Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_smastaBci1Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_B_SMASTA_BI1_TO_TRSH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_B_SMASTA_BI1_LSB_MSG  = (U1)1U;
    static const U4 u4_s_ALERT_B_SMASTA_BI1_B_BAT_AO = (U4)0x00000008U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_IDT1S02_CH0,
                                     (U4)ALERT_CAN_SYS_PNC_ALL,
                                     u2_s_ALERT_B_SMASTA_BI1_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    vd_g_AlertBRxTrnsSts(&u1_s_alert_smasta_sts_bzdn, u1_t_msgsts);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_BZDN, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_s_alert_smasta_sts_bzdn << u1_s_ALERT_B_SMASTA_BI1_LSB_MSG);

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_AO) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_B_SMASTA_BI1_B_BAT_AO;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_smastaBci2Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_smastaBci2Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_B_SMASTA_BI2_TO_TRSH = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_B_SMASTA_BI2_LSB_MSG = (U1)1U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_IDT1S02_CH0,
                                     (U4)OXCAN_SYS_IGR,
                                     u2_s_ALERT_B_SMASTA_BI2_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_BZDN2, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_B_SMASTA_BI2_LSB_MSG);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_smastaBci3Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_smastaBci3Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_B_SMASTA_BI3_TO_TRSH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_B_SMASTA_BI3_LSB_MSG  = (U1)1U;
    static const U4 u4_s_ALERT_B_SMASTA_BI3_B_BAT_WT = (U4)0x00000008U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_IDT1S02_CH0,
                                     (U4)ALERT_CAN_SYS_PNC_ALL,
                                     u2_s_ALERT_B_SMASTA_BI3_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    vd_g_AlertBRxTrnsSts(&u1_s_alert_smasta_sts_bzdn3, u1_t_msgsts);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_BZDN3, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_s_alert_smasta_sts_bzdn3 << u1_s_ALERT_B_SMASTA_BI3_LSB_MSG);

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_B_SMASTA_BI3_B_BAT_WT;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_smastaBcs1Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_smastaBcs1Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_B_SMASTA_BS1_TO_TRSH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_B_SMASTA_BS1_LSB_MSG  = (U1)1U;
    static const U4 u4_s_ALERT_B_SMASTA_BS1_B_BAT_WT = (U4)0x00000008U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_IDT1S02_CH0,
                                     (U4)ALERT_CAN_SYS_PNC_ALL,
                                     u2_s_ALERT_B_SMASTA_BS1_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    vd_g_AlertBRxTrnsSts(&u1_s_alert_smasta_sts_bz, u1_t_msgsts);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_BZ, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_s_alert_smasta_sts_bz << u1_s_ALERT_B_SMASTA_BS1_LSB_MSG);

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_B_SMASTA_BS1_B_BAT_WT;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_smastaBcs2Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_smastaBcs2Srcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_B_SMASTA_BS2_TO_TRSH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_B_SMASTA_BS2_LSB_MSG  = (U1)1U;
    static const U4 u4_s_ALERT_B_SMASTA_BS2_B_BAT_WT = (U4)0x00000008U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_IDT1S02_CH0,
                                     (U4)ALERT_CAN_SYS_PNC_ALL,
                                     u2_s_ALERT_B_SMASTA_BS2_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    vd_g_AlertBRxTrnsSts(&u1_s_alert_smasta_sts_bz2, u1_t_msgsts);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_BZ2, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_s_alert_smasta_sts_bz2 << u1_s_ALERT_B_SMASTA_BS2_LSB_MSG);

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_B_SMASTA_BS2_B_BAT_WT;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_smastaAsdwSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_smastaAsdwSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
#if defined(OXCAN_RXD_PDU_CAN_PMN1G03_CH0) && defined(ComConf_ComSignal_ASD_RWNG)
    static const U2 u2_s_ALERT_B_SMASTA_A1_TO_TRSH = ((U2)3600 / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_B_SMASTA_A1_LSB_MSG = (U1)1U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;

    u1_t_msgsts   = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_PMN1G03_CH0,
                                     (U4)OXCAN_SYS_IGR,
                                     u2_s_ALERT_B_SMASTA_A1_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_ASD_RWNG, &u1_t_sgnl);
    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_B_SMASTA_A1_LSB_MSG);

    return(u4_t_src_chk);
#else
    return((U4)0U);
#endif /* defined(OXCAN_RXD_PDU_CAN_PMN1G03_CH0) && defined(ComConf_ComSignal_ASD_RWNG) */
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_smastaBcd1bSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_smastaBcd1bSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_B_SMASTA_BCD1B_TO_TRSH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_B_SMASTA_BCD1B_LSB_MSG  = (U1)4U;
    static const U4 u4_s_ALERT_B_SMASTA_BCD1B_B_BAT_WT = (U4)0x00000020U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_trns_fact;

    u1_t_trns_fact = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_IDT1S02_CH0,
                                      (U4)ALERT_CAN_SYS_PNC_ALL,
                                      u2_s_ALERT_B_SMASTA_BCD1B_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) == (U1)0U){
        u1_t_trns_fact |= (U1)ALERT_BRX_FACT_NO_RX;
    }
    vd_g_AlertBRxTrnsSts(&u1_s_alert_smasta_sts_d_swr1, u1_t_trns_fact);

    u1_t_sgnl      = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_D_SWR1, &u1_t_sgnl);
    u4_t_src_chk   = (U4)u1_t_sgnl;
    u4_t_src_chk  |= (((U4)u1_s_alert_smasta_sts_d_swr1 & (U4)COM_NO_RX) << u1_s_ALERT_B_SMASTA_BCD1B_LSB_MSG);

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk   |= u4_s_ALERT_B_SMASTA_BCD1B_B_BAT_WT;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertB_smastaBcd1igSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertB_smastaBcd1igSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_B_SMASTA_BCD1IG_LSB_MSG = (U1)4U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts = u1_g_oXCANRxdStat((U2)OXCAN_RXD_PDU_CAN_IDT1S02_CH0,
                                   (U4)OXCAN_SYS_IGR,
                                   (U2)U2_MAX) & (U1)COM_NO_RX;
    u1_t_sgnl = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_D_SWR1, &u1_t_sgnl);
    u4_t_src_chk = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_B_SMASTA_BCD1IG_LSB_MSG);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertB_smastaS1igRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertB_smastaS1igRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    U1              u1_t_ssw;
    U1              u1_t_asdw2;

    u1_t_ssw   = (U1)ALERT_RW_SGNL_OFF;
    u1_t_asdw2 = (U1)ALERT_RW_SGNL_OFF;
    if((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U){
        if(u1_a_DST == (U1)ALERT_REQ_B_SMASTA_S1IG_MALFNC){
            u1_t_ssw   = (U1)ALERT_RW_SGNL_ON;
        }
        if(u1_a_DST == (U1)ALERT_REQ_B_SMASTA_S1IG_NOTICE){
            u1_t_asdw2 = (U1)ALERT_RW_SGNL_ON;
        }
    }

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_SSW, &u1_t_ssw);    /* COM Tx STUB delete */
    (void)Com_SendSignal(ComConf_ComSignal_ASDW2, &u1_t_asdw2);    /* COM Tx STUB delete */
#endif
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertB_smastaAsdwRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertB_smastaAsdwRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    U1              u1_t_asdw1;

    u1_t_asdw1 = (U1)ALERT_RW_SGNL_OFF;
    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U                          ) &&
       (u1_a_DST                          == (U1)ALERT_REQ_B_SMASTA_ASDW_RW)){
        u1_t_asdw1 = (U1)ALERT_RW_SGNL_ON;
    }

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_ASDW1, &u1_t_asdw1);    /* COM Tx STUB delete */
#endif
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertB_smastaBcd1igRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertB_smastaBcd1igRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U4 u4_s_ALERT_B_SMASTA_TIM_RW_ENBL = ((U4)15000U / (U4)ALERT_MAIN_TICK);
    U1              u1_t_digw;

    u1_t_digw = (U1)ALERT_RW_SGNL_OFF;
    if (((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U                          ) &&
        (u4_a_IGN_TM                       >= u4_s_ALERT_B_SMASTA_TIM_RW_ENBL ) &&
        (u1_a_DST                          == (U1)ALERT_REQ_B_SMASTA_BCD1IG_RW)) {
        u1_t_digw = (U1)ALERT_RW_SGNL_ON;
    }

#if 0   /* BEV BSW provisionally */
    (void)Com_SendSignal(ComConf_ComSignal_DIGW, &u1_t_digw);    /* COM Tx STUB delete */
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
/*  5.0.0     3/10/2020  SN       New.                                                                                               */
/*  5.1.0     5/11/2020  DS       Fix msgsts for BC_DR,BC_IN1.                                                                       */
/*  5.2.0     5/20/2020  DS       Fix power status for SWR2B,SWR2WT,SWR3B.                                                           */
/*  5.3.0     8/26/2020  SO       Add CH for ASDW1, and delete CH for SWR1WT,SWR2WT.                                                 */
/*  5.4.0    12/ 8/2020  TN       Update for 800B 1A(Version update).                                                                */
/*  5.4.1     3/30/2021  SO       Rename module name.                                                                                */
/*  5.4.2     8/ 4/2022  SAO      Update for 840B#2 1A(Version update).                                                              */
/*  5.4.2     8/ 4/2022  SAO      Update for 840B#2 1A(Version update).                                                              */
/*  5.5.0     1/17/2024  SW       Update for 19PFv3 CVInternalMarge#2(Version update).                                               */
/*  5.5.1     3/11/2024  SW       Fix u4_s_AlertB_smastaS2igSrcchk().                                                                */
/*  5.6.0     4/ 8/2024  AA       Added remote warning for DIGW.                                                                     */
/*                                                                                                                                   */
/*  * SN   = Shinichiro Naito, NTTD MSE                                                                                              */
/*  * DS   = Daisuke Suzuki, NTTD MSE                                                                                                */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*  * SAO  = Sachiko Oono, NTTD MSE                                                                                                  */
/*  * SW   = Shun Watanabe, Denso Techno                                                                                             */
/*  * AA   = Anna Asuncion, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
