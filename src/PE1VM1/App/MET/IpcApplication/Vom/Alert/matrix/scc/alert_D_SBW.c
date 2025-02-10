/* 5.9.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert D_SBW                                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_D_SBW_C_MAJOR                      (5)
#define ALERT_D_SBW_C_MINOR                      (9)
#define ALERT_D_SBW_C_PATCH                      (0)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "alert_cfg_private.h"
#include "alert_mtrx_cfg_private.h"
#include "alert_brx.h"

#include "oxcan.h"
#if 0   /* BEV BSW provisionally */
#else
#include "Com_Cfg_STUB.h"
#include "oxcan_channel_STUB.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if (ALERT_D_SBW_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_D_SBW.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_D_SBW_BZ_BSFT_NUM_DST              (64U)
#define ALERT_D_SBW_BZ_IGSFT_NUM_DST             (64U)
#define ALERT_D_SBW_BZ_PT_NUM_DST                (16U)
#define ALERT_D_SBW_PD_ACTF_NUM_DST              (64U)
#define ALERT_D_SBW_PD_LBAT_NUM_DST              (16U)
#define ALERT_D_SBW_PD_PSWF_NUM_DST              (16U)
#define ALERT_D_SBW_PD_SBWF_NUM_DST              (16U)
#define ALERT_D_SBW_PD_CHK_NUM_DST               (6U)
#define ALERT_D_SBW_PD_SFTF_NUM_DST              (8U)
#define ALERT_D_SBW_PD_RIS_NUM_DST               (16U)
#define ALERT_D_SBW_PD_NSFT_NUM_DST              (16U)
#define ALERT_D_SBW_PD_PREQ_NUM_DST              (16U)
#define ALERT_D_SBW_PD_SFML_NUM_DST              (16U)
#define ALERT_D_SBW_PD_DAP_NUM_DST               (16U)
#define ALERT_D_SBW_PD_ACCN_NUM_DST              (16U)
#define ALERT_D_SBW_PD_SILUA_NUM_DST             (8U)
#define ALERT_D_SBW_PD_SFPF_NUM_DST              (8U)

#define ALERT_D_SBW_RWSGNL_SBW3                  (0U)
#define ALERT_D_SBW_RWSGNL_SBW8                  (1U)
#define ALERT_D_SBW_RWSGNL_SBW9                  (2U)

#define ALERT_D_SBW_NUM_RWSGNL                   (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_alert_sbw_msgsts_bsft;
static U1      u1_s_alert_sbw_msgsts_actf;
static U1      u1_s_alert_sbw_msgsts_lbat;
static U1      u1_s_alert_sbw_msgsts_pswf;
static U1      u1_s_alert_sbw_msgsts_sbwf;
static U1      u1_s_alert_sbw_msgsts_chk;
static U1      u1_s_alert_sbw_msgsts_preq;
static U1      u1_s_alert_sbw_msgsts_dap;
static U1      u1_s_alert_sbw_msgsts_accn;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertD_sbwBzBsftSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertD_sbwBzIgsftSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertD_sbwBzPtSrcchk   (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertD_sbwPdActfSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertD_sbwPdLbatSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertD_sbwPdPswfSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertD_sbwPdSbwfSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertD_sbwPdChkSrcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertD_sbwPdSftfSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertD_sbwPdRisSrcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertD_sbwPdNsftSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertD_sbwPdPreqSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertD_sbwPdSfmlSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertD_sbwPdDapSrcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertD_sbwPdAccnSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertD_sbwPdSiluaSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertD_sbwPdSfpfSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertD_sbwPdActfRwTx   (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);
static void    vd_s_AlertD_sbwPdPswfRwTx   (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);
static void    vd_s_AlertD_sbwPdSbwfRwTx   (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);
static void    vd_s_AlertD_sbwPdChkRwTx    (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);
static void    vd_s_AlertD_sbwPdSftfRwTx   (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4  u4_sp_ALERT_D_SBW_BZ_BSFT_CRIT[ALERT_D_SBW_BZ_BSFT_NUM_DST] = {
    (U4)0x02000000U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x02000001U,                                                           /* 01 SINGLESP                                        */
    (U4)0x02000002U,                                                           /* 02 SINGLE                                          */
    (U4)0x02000003U,                                                           /* 03 UNKNOWN                                         */
    (U4)0x02000004U,                                                           /* 04 DOUBLE                                          */
    (U4)0x02000005U,                                                           /* 05 UNKNOWN                                         */
    (U4)0x02000006U,                                                           /* 06 UNKNOWN                                         */
    (U4)0x02000007U,                                                           /* 07 UNKNOWN                                         */
    (U4)0x02000008U,                                                           /* 08 UNKNOWN                                         */
    (U4)0x02000009U,                                                           /* 09 UNKNOWN                                         */
    (U4)0x0200000AU,                                                           /* 10 UNKNOWN                                         */
    (U4)0x0200000BU,                                                           /* 11 UNKNOWN                                         */
    (U4)0x0200000CU,                                                           /* 12 UNKNOWN                                         */
    (U4)0x0200000DU,                                                           /* 13 UNKNOWN                                         */
    (U4)0x0200000EU,                                                           /* 14 UNKNOWN                                         */
    (U4)0x0200000FU,                                                           /* 15 UNKNOWN                                         */
    (U4)0x02000010U,                                                           /* 16 UNKNOWN                                         */
    (U4)0x02000011U,                                                           /* 17 UNKNOWN                                         */
    (U4)0x02000012U,                                                           /* 18 UNKNOWN                                         */
    (U4)0x02000013U,                                                           /* 19 UNKNOWN                                         */
    (U4)0x02000014U,                                                           /* 20 UNKNOWN                                         */
    (U4)0x02000015U,                                                           /* 21 UNKNOWN                                         */
    (U4)0x02000016U,                                                           /* 22 UNKNOWN                                         */
    (U4)0x02000017U,                                                           /* 23 UNKNOWN                                         */
    (U4)0x02000018U,                                                           /* 24 UNKNOWN                                         */
    (U4)0x02000019U,                                                           /* 25 UNKNOWN                                         */
    (U4)0x0200001AU,                                                           /* 26 UNKNOWN                                         */
    (U4)0x0200001BU,                                                           /* 27 UNKNOWN                                         */
    (U4)0x0200001CU,                                                           /* 28 UNKNOWN                                         */
    (U4)0x0200001DU,                                                           /* 29 UNKNOWN                                         */
    (U4)0x0200001EU,                                                           /* 30 UNKNOWN                                         */
    (U4)0x0200001FU,                                                           /* 31 UNKNOWN                                         */
    (U4)0x02000020U,                                                           /* 32 UNKNOWN                                         */
    (U4)0x02000021U,                                                           /* 33 UNKNOWN                                         */
    (U4)0x02000022U,                                                           /* 34 UNKNOWN                                         */
    (U4)0x02000023U,                                                           /* 35 UNKNOWN                                         */
    (U4)0x02000024U,                                                           /* 36 UNKNOWN                                         */
    (U4)0x02000025U,                                                           /* 37 UNKNOWN                                         */
    (U4)0x02000026U,                                                           /* 38 UNKNOWN                                         */
    (U4)0x02000027U,                                                           /* 39 UNKNOWN                                         */
    (U4)0x02000028U,                                                           /* 40 UNKNOWN                                         */
    (U4)0x02000029U,                                                           /* 41 UNKNOWN                                         */
    (U4)0x0200002AU,                                                           /* 42 UNKNOWN                                         */
    (U4)0x0200002BU,                                                           /* 43 UNKNOWN                                         */
    (U4)0x0200002CU,                                                           /* 44 UNKNOWN                                         */
    (U4)0x0200002DU,                                                           /* 45 UNKNOWN                                         */
    (U4)0x0200002EU,                                                           /* 46 UNKNOWN                                         */
    (U4)0x0200002FU,                                                           /* 47 UNKNOWN                                         */
    (U4)0x02000030U,                                                           /* 48 UNKNOWN                                         */
    (U4)0x02000031U,                                                           /* 49 UNKNOWN                                         */
    (U4)0x02000032U,                                                           /* 50 UNKNOWN                                         */
    (U4)0x02000033U,                                                           /* 51 UNKNOWN                                         */
    (U4)0x02000034U,                                                           /* 52 UNKNOWN                                         */
    (U4)0x02000035U,                                                           /* 53 UNKNOWN                                         */
    (U4)0x02000036U,                                                           /* 54 UNKNOWN                                         */
    (U4)0x02000037U,                                                           /* 55 UNKNOWN                                         */
    (U4)0x02000038U,                                                           /* 56 UNKNOWN                                         */
    (U4)0x02000039U,                                                           /* 57 UNKNOWN                                         */
    (U4)0x0200003AU,                                                           /* 58 UNKNOWN                                         */
    (U4)0x0200003BU,                                                           /* 59 UNKNOWN                                         */
    (U4)0x0200003CU,                                                           /* 60 UNKNOWN                                         */
    (U4)0x0200003DU,                                                           /* 61 UNKNOWN                                         */
    (U4)0x0200003EU,                                                           /* 62 UNKNOWN                                         */
    (U4)0x0200003FU                                                            /* 63 UNKNOWN                                         */
};
static const U4  u4_sp_ALERT_D_SBW_BZ_BSFT_MASK[ALERT_D_SBW_BZ_BSFT_NUM_DST] = {
    (U4)0x0200003FU,                                                           /* 00 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 01 SINGLESP                                        */
    (U4)0x0200003FU,                                                           /* 02 SINGLE                                          */
    (U4)0x0200003FU,                                                           /* 03 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 04 DOUBLE                                          */
    (U4)0x0200003FU,                                                           /* 05 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 06 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 07 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 08 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 09 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 10 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 11 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 12 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 13 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 14 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 15 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 16 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 17 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 18 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 19 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 20 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 21 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 22 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 23 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 24 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 25 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 26 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 27 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 28 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 29 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 30 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 31 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 32 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 33 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 34 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 35 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 36 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 37 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 38 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 39 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 40 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 41 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 42 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 43 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 44 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 45 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 46 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 47 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 48 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 49 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 50 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 51 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 52 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 53 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 54 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 55 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 56 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 57 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 58 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 59 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 60 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 61 UNKNOWN                                         */
    (U4)0x0200003FU,                                                           /* 62 UNKNOWN                                         */
    (U4)0x0200003FU                                                            /* 63 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_D_SBW_BZ_BSFT_DST[ALERT_D_SBW_BZ_BSFT_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SBW_BZ_BSFT_SINGLESP,                                      /* 01 SINGLESP                                        */
    (U1)ALERT_REQ_D_SBW_BZ_BSFT_SINGLE,                                        /* 02 SINGLE                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SBW_BZ_BSFT_DOUBLE,                                        /* 04 DOUBLE                                          */
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
static const U1  u1_sp_ALERT_D_SBW_BZ_IGSFT_DST[ALERT_D_SBW_BZ_IGSFT_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SBW_BZ_IGSFT_CYCLE,                                        /* 08 CYCLE                                           */
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
static const U1  u1_sp_ALERT_D_SBW_BZ_PT_DST[ALERT_D_SBW_BZ_PT_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SBW_BZ_PT_SINGLE,                                          /* 01 SINGLE                                          */
    (U1)ALERT_REQ_D_SBW_BZ_PT_CYCLE,                                           /* 02 CYCLE                                           */
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
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_D_SBW_PD_ACTF_DST[ALERT_D_SBW_PD_ACTF_NUM_DST] = {
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
    (U1)ALERT_REQ_D_SBW_PD_ACTF_MSG_02,                                        /* 17 MSG_02                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 18 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 19 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 20 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 21 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 22 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 23 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 24 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SBW_PD_ACTF_MSG_02,                                        /* 25 MSG_02                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 26 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 27 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SBW_PD_ACTF_MSG_02,                                        /* 28 MSG_02                                          */
    (U1)ALERT_REQ_D_SBW_PD_ACTF_MSG_02,                                        /* 29 MSG_02                                          */
    (U1)ALERT_REQ_D_SBW_PD_ACTF_MSG_02,                                        /* 30 MSG_02                                          */
    (U1)ALERT_REQ_D_SBW_PD_ACTF_MSG_02,                                        /* 31 MSG_02                                          */
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
    (U1)ALERT_REQ_D_SBW_PD_ACTF_MSG_02,                                        /* 49 MSG_02                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 50 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 51 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SBW_PD_ACTF_MSG_02,                                        /* 52 MSG_02                                          */
    (U1)ALERT_REQ_D_SBW_PD_ACTF_MSG_02,                                        /* 53 MSG_02                                          */
    (U1)ALERT_REQ_D_SBW_PD_ACTF_MSG_02,                                        /* 54 MSG_02                                          */
    (U1)ALERT_REQ_D_SBW_PD_ACTF_MSG_02,                                        /* 55 MSG_02                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 56 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SBW_PD_ACTF_MSG_02,                                        /* 57 MSG_02                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 58 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 59 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SBW_PD_ACTF_MSG_02,                                        /* 60 MSG_02                                          */
    (U1)ALERT_REQ_D_SBW_PD_ACTF_MSG_02,                                        /* 61 MSG_02                                          */
    (U1)ALERT_REQ_D_SBW_PD_ACTF_MSG_02,                                        /* 62 MSG_02                                          */
    (U1)ALERT_REQ_D_SBW_PD_ACTF_MSG_02                                         /* 63 MSG_02                                          */
};
static const U1  u1_sp_ALERT_D_SBW_PD_LBAT_DST[ALERT_D_SBW_PD_LBAT_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SBW_PD_LBAT_MSG_03,                                        /* 09 MSG_03                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_D_SBW_PD_PSWF_DST[ALERT_D_SBW_PD_PSWF_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SBW_PD_PSWF_MSG_04,                                        /* 09 MSG_04                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_D_SBW_PD_SBWF_DST[ALERT_D_SBW_PD_SBWF_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SBW_PD_SBWF_MSG_05,                                        /* 09 MSG_05                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U4  u4_sp_ALERT_D_SBW_PD_CHK_CRIT[ALERT_D_SBW_PD_CHK_NUM_DST] = {
    (U4)0x02000011U,                                                           /* 00 MSG6_SBW8                                       */
    (U4)0x02000012U,                                                           /* 01 MSG6_SBW9                                       */
    (U4)0x02000010U,                                                           /* 02 MSG_06                                          */
    (U4)0x02000003U,                                                           /* 03 MSG_06                                          */
    (U4)0x02000001U,                                                           /* 04 SBW8_ON                                         */
    (U4)0x02000002U                                                            /* 05 SBW9_ON                                         */
};
static const U4  u4_sp_ALERT_D_SBW_PD_CHK_MASK[ALERT_D_SBW_PD_CHK_NUM_DST] = {
    (U4)0x0200007FU,                                                           /* 00 MSG6_SBW8                                       */
    (U4)0x0200007FU,                                                           /* 01 MSG6_SBW9                                       */
    (U4)0x02000070U,                                                           /* 02 MSG_06                                          */
    (U4)0x0200000FU,                                                           /* 03 MSG_06                                          */
    (U4)0x0200000FU,                                                           /* 04 SBW8_ON                                         */
    (U4)0x0200000FU                                                            /* 05 SBW9_ON                                         */
};
static const U1  u1_sp_ALERT_D_SBW_PD_CHK_DST[ALERT_D_SBW_PD_CHK_NUM_DST] = {
    (U1)ALERT_REQ_D_SBW_PD_CHK_MSG6_SBW8,                                      /* 00 MSG6_SBW8                                       */
    (U1)ALERT_REQ_D_SBW_PD_CHK_MSG6_SBW9,                                      /* 01 MSG6_SBW9                                       */
    (U1)ALERT_REQ_D_SBW_PD_CHK_MSG_06,                                         /* 02 MSG_06                                          */
    (U1)ALERT_REQ_D_SBW_PD_CHK_MSG_06,                                         /* 03 MSG_06                                          */
    (U1)ALERT_REQ_D_SBW_PD_CHK_SBW8_ON,                                        /* 04 SBW8_ON                                         */
    (U1)ALERT_REQ_D_SBW_PD_CHK_SBW9_ON                                         /* 05 SBW9_ON                                         */
};
static const U1  u1_sp_ALERT_D_SBW_PD_SFTF_DST[ALERT_D_SBW_PD_SFTF_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SBW_PD_SFTF_MSG_07,                                        /* 01 MSG_07                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 07 UNKNOWN                                         */
};
static const U4  u4_sp_ALERT_D_SBW_PD_RIS_CRIT[ALERT_D_SBW_PD_RIS_NUM_DST] = {
    (U4)0x00000001U,                                                           /* 00 MSG_08                                          */
    (U4)0x00000003U,                                                           /* 01 MSG_11                                          */
    (U4)0x00000005U,                                                           /* 02 MSG_12                                          */
    (U4)0x00000006U,                                                           /* 03 MSG_38                                          */
    (U4)0x00000007U,                                                           /* 04 MSG_39                                          */
    (U4)0x00000008U,                                                           /* 05 MSG_33                                          */
    (U4)0x00000009U,                                                           /* 06 MSG_16                                          */
    (U4)0x0000000AU,                                                           /* 07 MSG_19                                          */
    (U4)0x0000000BU,                                                           /* 08 MSG_20                                          */
    (U4)0x0000000CU,                                                           /* 09 MSG_40                                          */
    (U4)0x0000000FU,                                                           /* 10 MSG_35                                          */
    (U4)0x00000010U,                                                           /* 11 MSG_36                                          */
    (U4)0x00000013U,                                                           /* 12 MSG_13                                          */
    (U4)0x00000014U,                                                           /* 13 MSG_14                                          */
    (U4)0x00000015U,                                                           /* 14 MSG_17                                          */
    (U4)0x00000016U                                                            /* 15 MSG_18                                          */
};
static const U4  u4_sp_ALERT_D_SBW_PD_RIS_MASK[ALERT_D_SBW_PD_RIS_NUM_DST] = {
    (U4)0x0000007FU,                                                           /* 00 MSG_08                                          */
    (U4)0x0000007FU,                                                           /* 01 MSG_11                                          */
    (U4)0x0000007FU,                                                           /* 02 MSG_12                                          */
    (U4)0x0000007FU,                                                           /* 03 MSG_38                                          */
    (U4)0x0000007FU,                                                           /* 04 MSG_39                                          */
    (U4)0x0000007FU,                                                           /* 05 MSG_33                                          */
    (U4)0x0000007FU,                                                           /* 06 MSG_16                                          */
    (U4)0x0000007FU,                                                           /* 07 MSG_19                                          */
    (U4)0x0000007FU,                                                           /* 08 MSG_20                                          */
    (U4)0x0000007FU,                                                           /* 09 MSG_40                                          */
    (U4)0x0000007FU,                                                           /* 10 MSG_35                                          */
    (U4)0x0000007FU,                                                           /* 11 MSG_36                                          */
    (U4)0x0000007FU,                                                           /* 12 MSG_13                                          */
    (U4)0x0000007FU,                                                           /* 13 MSG_14                                          */
    (U4)0x0000007FU,                                                           /* 14 MSG_17                                          */
    (U4)0x0000007FU                                                            /* 15 MSG_18                                          */
};
static const U1  u1_sp_ALERT_D_SBW_PD_RIS_DST[ALERT_D_SBW_PD_RIS_NUM_DST] = {
    (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_08,                                         /* 00 MSG_08                                          */
    (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_11,                                         /* 01 MSG_11                                          */
    (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_12,                                         /* 02 MSG_12                                          */
    (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_38,                                         /* 03 MSG_38                                          */
    (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_39,                                         /* 04 MSG_39                                          */
    (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_33,                                         /* 05 MSG_33                                          */
    (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_16,                                         /* 06 MSG_16                                          */
    (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_19,                                         /* 07 MSG_19                                          */
    (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_20,                                         /* 08 MSG_20                                          */
    (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_40,                                         /* 09 MSG_40                                          */
    (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_35,                                         /* 10 MSG_35                                          */
    (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_36,                                         /* 11 MSG_36                                          */
    (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_13,                                         /* 12 MSG_13                                          */
    (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_14,                                         /* 13 MSG_14                                          */
    (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_17,                                         /* 14 MSG_17                                          */
    (U1)ALERT_REQ_D_SBW_PD_RIS_MSG_18                                          /* 15 MSG_18                                          */
};
static const U1  u1_sp_ALERT_D_SBW_PD_NSFT_DST[ALERT_D_SBW_PD_NSFT_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SBW_PD_NSFT_MSG_24,                                        /* 01 MSG_24                                          */
    (U1)ALERT_REQ_D_SBW_PD_NSFT_MSG_21,                                        /* 02 MSG_21                                          */
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
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_D_SBW_PD_PREQ_DST[ALERT_D_SBW_PD_PREQ_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SBW_PD_PREQ_MSG_26,                                        /* 09 MSG_26                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_D_SBW_PD_SFML_DST[ALERT_D_SBW_PD_SFML_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SBW_PD_SFML_MSG_27,                                        /* 01 MSG_27                                          */
    (U1)ALERT_REQ_D_SBW_PD_SFML_MSG_28,                                        /* 02 MSG_28                                          */
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
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_D_SBW_PD_DAP_DST[ALERT_D_SBW_PD_DAP_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SBW_PD_DAP_MSG_29,                                         /* 09 MSG_29                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_D_SBW_PD_ACCN_DST[ALERT_D_SBW_PD_ACCN_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 01 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SBW_PD_ACCN_MSG_32,                                        /* 09 MSG_32                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 15 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_D_SBW_PD_SILUA_DST[ALERT_D_SBW_PD_SILUA_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SBW_PD_SILUA_MSG_41,                                       /* 01 MSG_41                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 07 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_D_SBW_PD_SFPF_DST[ALERT_D_SBW_PD_SFPF_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_D_SBW_PD_SFPF_MSG_42,                                        /* 01 MSG_42                                          */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 02 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 03 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 07 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_D_SBW_MTRX[17] = {
    {
        &u4_s_AlertD_sbwBzBsftSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_D_SBW_BZ_BSFT_MASK[0],                                    /* u4p_MASK                                           */
        &u4_sp_ALERT_D_SBW_BZ_BSFT_CRIT[0],                                    /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_SBW_BZ_BSFT_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_D_SBW_BZ_BSFT_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertD_sbwBzIgsftSrcchk,                                         /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_SBW_BZ_IGSFT_DST[0],                                    /* u1p_DST                                            */
        (U2)ALERT_D_SBW_BZ_IGSFT_NUM_DST,                                      /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertD_sbwBzPtSrcchk,                                            /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_SBW_BZ_PT_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_D_SBW_BZ_PT_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */

    },
    {
        &u4_s_AlertD_sbwPdActfSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertD_sbwPdActfRwTx,                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_SBW_PD_ACTF_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_D_SBW_PD_ACTF_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertD_sbwPdLbatSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_SBW_PD_LBAT_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_D_SBW_PD_LBAT_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertD_sbwPdPswfSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertD_sbwPdPswfRwTx,                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_SBW_PD_PSWF_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_D_SBW_PD_PSWF_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertD_sbwPdSbwfSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertD_sbwPdSbwfRwTx,                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_SBW_PD_SBWF_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_D_SBW_PD_SBWF_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertD_sbwPdChkSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertD_sbwPdChkRwTx,                                             /* fp_vd_XDST                                         */

        &u4_sp_ALERT_D_SBW_PD_CHK_MASK[0],                                     /* u4p_MASK                                           */
        &u4_sp_ALERT_D_SBW_PD_CHK_CRIT[0],                                     /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_SBW_PD_CHK_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_D_SBW_PD_CHK_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertD_sbwPdSftfSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertD_sbwPdSftfRwTx,                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_SBW_PD_SFTF_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_D_SBW_PD_SFTF_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertD_sbwPdRisSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_D_SBW_PD_RIS_MASK[0],                                     /* u4p_MASK                                           */
        &u4_sp_ALERT_D_SBW_PD_RIS_CRIT[0],                                     /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_SBW_PD_RIS_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_D_SBW_PD_RIS_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertD_sbwPdNsftSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_SBW_PD_NSFT_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_D_SBW_PD_NSFT_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertD_sbwPdPreqSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_SBW_PD_PREQ_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_D_SBW_PD_PREQ_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertD_sbwPdSfmlSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_SBW_PD_SFML_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_D_SBW_PD_SFML_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertD_sbwPdDapSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_SBW_PD_DAP_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_D_SBW_PD_DAP_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertD_sbwPdAccnSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_SBW_PD_ACCN_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_D_SBW_PD_ACCN_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertD_sbwPdSiluaSrcchk,                                         /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_SBW_PD_SILUA_DST[0],                                    /* u1p_DST                                            */
        (U2)ALERT_D_SBW_PD_SILUA_NUM_DST,                                      /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertD_sbwPdSfpfSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_D_SBW_PD_SFPF_DST[0],                                     /* u1p_DST                                            */
        (U2)ALERT_D_SBW_PD_SFPF_NUM_DST,                                       /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertD_sbwInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertD_sbwInit(void)
{
    u1_s_alert_sbw_msgsts_bsft   = (U1)COM_NO_RX;
    u1_s_alert_sbw_msgsts_actf   = (U1)COM_NO_RX;
    u1_s_alert_sbw_msgsts_lbat   = (U1)COM_NO_RX;
    u1_s_alert_sbw_msgsts_pswf   = (U1)COM_NO_RX;
    u1_s_alert_sbw_msgsts_sbwf   = (U1)COM_NO_RX;
    u1_s_alert_sbw_msgsts_chk    = (U1)COM_NO_RX;
    u1_s_alert_sbw_msgsts_preq   = (U1)COM_NO_RX;
    u1_s_alert_sbw_msgsts_dap    = (U1)COM_NO_RX;
    u1_s_alert_sbw_msgsts_accn   = (U1)COM_NO_RX;
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_sbwBzBsftSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_sbwBzBsftSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_SBW_BZ_BSFT_TO_TRSH  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_SBW_BZ_BSFT_LSB_MSG  = (U1)4U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PCN1S01_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_BAT | (U2)OXCAN_RX_SYS_TOE_BAT,
                                     u2_s_ALERT_SBW_BZ_BSFT_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    vd_g_AlertBRxTrnsSts(&u1_s_alert_sbw_msgsts_bsft, u1_t_msgsts);

    u4_t_src_chk = ((U4)u1_s_alert_sbw_msgsts_bsft << u1_s_ALERT_SBW_BZ_BSFT_LSB_MSG);

    u1_t_sgnl    = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_BZR_SFT1, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_sbwBzIgsftSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_sbwBzIgsftSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_SBW_BZ_IGSFT_TO_TRSH = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_SBW_BZ_IGSFT_LSB_MSG = (U1)4U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PCN1S01_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_SBW_BZ_IGSFT_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_SBW_BZ_IGSFT_LSB_MSG);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_BZR_SFT1, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_sbwBzPtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_sbwBzPtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_SBW_BZ_PT_TRSH_1G92  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;

   u1_t_msgsts                = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1G92_RXCH0,
                                                 (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                                 u2_s_ALERT_SBW_BZ_PT_TRSH_1G92) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl                  = (U1)0U;
    if(u1_t_msgsts == (U1)0U){
        #if defined(ComConf_ComSignal_BZR_PT) /*@@@ 19pvf CANFDItem  @@@*/
        (void)Com_ReceiveSignal(ComConf_ComSignal_BZR_PT, &u1_t_sgnl);
        #endif /* ComConf_ComSignal_BZR_PT */
    }
    u4_t_src_chk               = u1_t_sgnl;
    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_sbwPdActfSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_sbwPdActfSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_SBW_PD_ACTF_TO_TRSH   = ((U2)3600U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_SBW_PD_ACTF_LSB_MSG   = (U1)1U;
    static const U4 u4_s_ALERT_SBW_PD_ACTF_BIT_DSP   = (U4)0x00000008U;
    static const U4 u4_s_ALERT_SBW_PD_ACTF_BIT_BATWT = (U4)0x00000010U;
    static const U4 u4_s_ALERT_SBW_PD_ACTF_BIT_IGNON = (U4)0x00000020U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u4_t_src_chk  = (U4)0U;
    if((u1_a_LAS                                      == (U1)ALERT_REQ_D_SBW_PD_ACTF_MSG_02) &&
      ((u1_s_alert_sbw_msgsts_actf & (U1)COM_TIMEOUT) != (U1)0U                            )){
        u4_t_src_chk  = u4_s_ALERT_SBW_PD_ACTF_BIT_DSP;
    }

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_SBW1G02_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_BAT | (U2)OXCAN_RX_SYS_TOE_BAT,
                                     u2_s_ALERT_SBW_PD_ACTF_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    vd_g_AlertBRxTrnsSts(&u1_s_alert_sbw_msgsts_actf, u1_t_msgsts);
    u4_t_src_chk |= ((U4)u1_s_alert_sbw_msgsts_actf << u1_s_ALERT_SBW_PD_ACTF_LSB_MSG);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_MSG_ACTF, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_SBW_PD_ACTF_BIT_BATWT;
    }

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_SBW_PD_ACTF_BIT_IGNON;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_sbwPdLbatSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_sbwPdLbatSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_SBW_PD_LBAT_TO_TRSH   = ((U2)3600U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_SBW_PD_LBAT_LSB_MSG   = (U1)1U;
    static const U4 u4_s_ALERT_SBW_PD_LBAT_BIT_BATWT = (U4)0x00000008U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_SBW1G02_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_BAT | (U2)OXCAN_RX_SYS_TOE_BAT,
                                     u2_s_ALERT_SBW_PD_LBAT_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    vd_g_AlertBRxTrnsSts(&u1_s_alert_sbw_msgsts_lbat, u1_t_msgsts);

    u4_t_src_chk  = ((U4)u1_s_alert_sbw_msgsts_lbat << u1_s_ALERT_SBW_PD_LBAT_LSB_MSG);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_MSG_LBAT, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_SBW_PD_LBAT_BIT_BATWT;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_sbwPdPswfSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_sbwPdPswfSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_SBW_PD_PSWF_TO_TRSH   = ((U2)3600U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_SBW_PD_PSWF_LSB_MSG   = (U1)1U;
    static const U4 u4_s_ALERT_SBW_PD_PSWF_BIT_BATWT = (U4)0x00000008U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_SBW1G02_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_BAT | (U2)OXCAN_RX_SYS_TOE_BAT,
                                     u2_s_ALERT_SBW_PD_PSWF_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    vd_g_AlertBRxTrnsSts(&u1_s_alert_sbw_msgsts_pswf, u1_t_msgsts);

    u4_t_src_chk  = ((U4)u1_s_alert_sbw_msgsts_pswf << u1_s_ALERT_SBW_PD_PSWF_LSB_MSG);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_MSG_PSWF, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_SBW_PD_PSWF_BIT_BATWT;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_sbwPdSbwfSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_sbwPdSbwfSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_SBW_PD_SBWF_TO_TRSH   = ((U2)3600U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_SBW_PD_SBWF_LSB_MSG   = (U1)1U;
    static const U4 u4_s_ALERT_SBW_PD_SBWF_BIT_BATWT = (U4)0x00000008U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_SBW1G02_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_BAT | (U2)OXCAN_RX_SYS_TOE_BAT,
                                     u2_s_ALERT_SBW_PD_SBWF_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    vd_g_AlertBRxTrnsSts(&u1_s_alert_sbw_msgsts_sbwf, u1_t_msgsts);

    u4_t_src_chk  = ((U4)u1_s_alert_sbw_msgsts_sbwf << u1_s_ALERT_SBW_PD_SBWF_LSB_MSG);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_MSG_SBWF, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_SBW_PD_SBWF_BIT_BATWT;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_sbwPdChkSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_sbwPdChkSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_SBW_PD_CHK_TRSH_1G92  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U2 u2_s_ALERT_SBW_PD_CHK_TRSH_1S01  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_D_SBW_PD_CHK_LSB_PC01 = (U1)5U;
    static const U1 u1_s_ALERT_D_SBW_PD_CHK_LSB_MSHK = (U1)4U;
    static const U1 u1_s_ALERT_D_SBW_PD_CHK_LSB_EN92 = (U1)2U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PCN1S01_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_BAT | (U2)OXCAN_RX_SYS_TOE_BAT,
                                     u2_s_ALERT_SBW_PD_CHK_TRSH_1S01) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    vd_g_AlertBRxTrnsSts(&u1_s_alert_sbw_msgsts_chk, u1_t_msgsts);

    u4_t_src_chk  = ((U4)u1_s_alert_sbw_msgsts_chk << u1_s_ALERT_D_SBW_PD_CHK_LSB_PC01);
    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_MSG_CHK, &u1_t_sgnl);
    u4_t_src_chk |= ((U4)u1_t_sgnl << u1_s_ALERT_D_SBW_PD_CHK_LSB_MSHK);

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1G92_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_SBW_PD_CHK_TRSH_1G92) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_D_SBW_PD_CHK_LSB_EN92);

    u1_t_sgnl     = (U1)0U;
    #if defined(ComConf_ComSignal_MSG_SFML) /*@@@ 19pvf CANFDItem  @@@*/
    (void)Com_ReceiveSignal(ComConf_ComSignal_MSG_SFML, &u1_t_sgnl);
    #endif /* ComConf_ComSignal_MSG_SFML */
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_sbwPdSftfSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_sbwPdSftfSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_SBW_PD_SFTF_TO_TRSH = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_SBW_PD_SFTF_LSB_MSG = (U1)1U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PCN1S01_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_SBW_PD_SFTF_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_SBW_PD_SFTF_LSB_MSG);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_MSG_SFTF, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_sbwPdRisSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_sbwPdRisSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_SBW_PD_RIS_TO_TRSH    = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_D_SBW_PD_RIS_LSB_PC01 = (U1)5U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PCN1S01_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_SBW_PD_RIS_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_D_SBW_PD_RIS_LSB_PC01);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_MSG_RI_S, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_sbwPdNsftSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_sbwPdNsftSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_SBW_PD_NSFT_TO_TRSH = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_SBW_PD_NSFT_LSB_MSG = (U1)2U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PCN1S01_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_SBW_PD_NSFT_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_SBW_PD_NSFT_LSB_MSG);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_MSG_NSFT, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_sbwPdPreqSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_sbwPdPreqSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_SBW_PD_PREQ_TO_TRSH   = ((U2)3600U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_SBW_PD_PREQ_LSB_MSG   = (U1)1U;
    static const U4 u4_s_ALERT_SBW_PD_PREQ_BIT_BATWT = (U4)0x00000008U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_SBW1G02_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_BAT | (U2)OXCAN_RX_SYS_TOE_BAT,
                                     u2_s_ALERT_SBW_PD_PREQ_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    vd_g_AlertBRxTrnsSts(&u1_s_alert_sbw_msgsts_preq, u1_t_msgsts);

    u4_t_src_chk  = ((U4)u1_s_alert_sbw_msgsts_preq << u1_s_ALERT_SBW_PD_PREQ_LSB_MSG);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_MSG_PREQ, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_SBW_PD_PREQ_BIT_BATWT;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_sbwPdSfmlSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_sbwPdSfmlSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_SBW_PD_SFML_TRSH_1G92 = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_SBW_PD_SFML_LSB_MSG   = (U1)2U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1G92_RXCH0,
                                          (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                          u2_s_ALERT_SBW_PD_SFML_TRSH_1G92) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_SBW_PD_SFML_LSB_MSG);

    u1_t_sgnl     = (U1)0U;
    #if defined(ComConf_ComSignal_MSG_SFML) /*@@@ 19pvf CANFDItem  @@@*/
    (void)Com_ReceiveSignal(ComConf_ComSignal_MSG_SFML, &u1_t_sgnl);
    #endif /* ComConf_ComSignal_MSG_SFML */
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_sbwPdDapSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_sbwPdDapSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_SBW_PD_DAP_TO_TRSH    = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_D_SBW_PD_DAP_LSB_SB05 = (U1)1U;
    static const U4 u4_s_ALERT_SBW_PD_DAP_BIT_BATWT  = (U4)0x00000008U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PCN1S01_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_BAT | (U2)OXCAN_RX_SYS_TOE_BAT,
                                     u2_s_ALERT_SBW_PD_DAP_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    vd_g_AlertBRxTrnsSts(&u1_s_alert_sbw_msgsts_dap, u1_t_msgsts);

    u4_t_src_chk  = ((U4)u1_s_alert_sbw_msgsts_dap << u1_s_ALERT_D_SBW_PD_DAP_LSB_SB05);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_MSG_DAP, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_SBW_PD_DAP_BIT_BATWT;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_sbwPdAccnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_sbwPdAccnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_SBW_PD_ACCN_TO_TRSH   = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_SBW_PD_ACCN_LSB_MSG   = (U1)1U;
    static const U4 u4_s_ALERT_SBW_PD_ACCN_BIT_BATWT = (U4)0x00000008U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PCN1S01_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_BAT | (U2)OXCAN_RX_SYS_TOE_BAT,
                                     u2_s_ALERT_SBW_PD_ACCN_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    vd_g_AlertBRxTrnsSts(&u1_s_alert_sbw_msgsts_accn, u1_t_msgsts);

    u4_t_src_chk  = ((U4)u1_s_alert_sbw_msgsts_accn << u1_s_ALERT_SBW_PD_ACCN_LSB_MSG);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_MSG_ACCN, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    if((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U){
        u4_t_src_chk |= u4_s_ALERT_SBW_PD_ACCN_BIT_BATWT;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_sbwPdSiluaSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_sbwPdSiluaSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_D_SBW_SILUA_TO_TRSH = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_D_SBW_SILUA_LSB_MSG = (U1)1U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PCN1S01_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_D_SBW_SILUA_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_D_SBW_SILUA_LSB_MSG);

    u1_t_sgnl     = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_SILUASBW, &u1_t_sgnl);
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertD_sbwPdSfpfSrcchk (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertD_sbwPdSfpfSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_D_SBW_PD_SFPF_TO_TRSH = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_D_SBW_PD_SFPF_LSB_MSG = (U1)1U;
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PCN1S01_RXCH0,
                                     (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                     u2_s_ALERT_D_SBW_PD_SFPF_TO_TRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u4_t_src_chk  = ((U4)u1_t_msgsts << u1_s_ALERT_D_SBW_PD_SFPF_LSB_MSG);

    u1_t_sgnl     = (U1)0U;
    #if defined(ComConf_ComSignal_MSG_SFPF) /*@@@ BEV CANFDItem  @@@*/
    (void)Com_ReceiveSignal(ComConf_ComSignal_MSG_SFPF, &u1_t_sgnl);
    #endif /*@@@ ComConf_ComSignal_MSG_SFPF  @@@*/
    u4_t_src_chk |= (U4)u1_t_sgnl;

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertD_sbwPdActfRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertD_sbwPdActfRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U4 u4_s_ALERT_SBW_PD_ACTF_RW_ENBL = ((U4)15000U / (U4)ALERT_MAIN_TICK);
    U1              u1_t_shift_sbw;
    U1              u1_t_sgnl;

    u1_t_shift_sbw = u1_g_AlertShiftSbwFunc();

    if((u1_t_shift_sbw                    == (U1)TRUE                          ) &&
       ((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U                            ) &&
       (u4_a_IGN_TM                       >= u4_s_ALERT_SBW_PD_ACTF_RW_ENBL    ) &&
       (u1_a_DST                          == (U1)ALERT_REQ_D_SBW_PD_ACTF_MSG_02)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_SBW4, &u1_t_sgnl);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertD_sbwPdPswfRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertD_sbwPdPswfRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    U1              u1_t_sgnl;

    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U                            ) &&
       (u1_a_DST                          == (U1)ALERT_REQ_D_SBW_PD_PSWF_MSG_04)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_SBW6, &u1_t_sgnl);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertD_sbwPdSbwfRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertD_sbwPdSbwfRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U4 u4_s_ALERT_SBW_PD_SBWF_RW_ENBL = ((U4)15000U / (U4)ALERT_MAIN_TICK);
    U1              u1_t_sgnl;

    if(((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U                            ) &&
       (u4_a_IGN_TM                       >= u4_s_ALERT_SBW_PD_SBWF_RW_ENBL    ) &&
       (u1_a_DST                          == (U1)ALERT_REQ_D_SBW_PD_SBWF_MSG_05)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_SBW5, &u1_t_sgnl);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertD_sbwPdChkRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertD_sbwPdChkRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U1 u1_sp_ALERT_D_SBWRWTX_DST_CRT[ALERT_D_SBW_NUM_RWSGNL] = {
        ((U1)((U1)1U << ALERT_REQ_D_SBW_PD_CHK_MSG_06 ) | (U1)((U1)1U << ALERT_REQ_D_SBW_PD_CHK_MSG6_SBW8)
                                                        | (U1)((U1)1U << ALERT_REQ_D_SBW_PD_CHK_MSG6_SBW9)), /* SBW3 */
        ((U1)((U1)1U << ALERT_REQ_D_SBW_PD_CHK_SBW8_ON) | (U1)((U1)1U << ALERT_REQ_D_SBW_PD_CHK_MSG6_SBW8)), /* SBW8 */
        ((U1)((U1)1U << ALERT_REQ_D_SBW_PD_CHK_SBW9_ON) | (U1)((U1)1U << ALERT_REQ_D_SBW_PD_CHK_MSG6_SBW9))  /* SBW9 */
    };
    static const U1 u1_s_ALERT_D_SBWRWTX_DST_MSK = (U1)0x07U;

    U1              u1_tp_sgnl[ALERT_D_SBW_NUM_RWSGNL];
    U1              u1_t_rw;
    U4              u4_t_idx;

    u1_t_rw = (U1)0U;
    if(u1_a_DST != (U1)ALERT_REQ_UNKNOWN){
        u1_t_rw = ((U1)1U << (u1_a_DST & u1_s_ALERT_D_SBWRWTX_DST_MSK));
    }
    for(u4_t_idx = (U4)0U; u4_t_idx < (U4)ALERT_D_SBW_NUM_RWSGNL; u4_t_idx++){
        if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN)                    != (U1)0U) &&
           ((u1_t_rw  & u1_sp_ALERT_D_SBWRWTX_DST_CRT[u4_t_idx]) != (U1)0U)){

            u1_tp_sgnl[u4_t_idx] = (U1)ALERT_RW_SGNL_ON;
        }
        else{
            u1_tp_sgnl[u4_t_idx] = (U1)ALERT_RW_SGNL_OFF;
        }
    }
    (void)Com_SendSignal(ComConf_ComSignal_SBW3 , &u1_tp_sgnl[ALERT_D_SBW_RWSGNL_SBW3]);
    (void)Com_SendSignal(ComConf_ComSignal_SBW8 , &u1_tp_sgnl[ALERT_D_SBW_RWSGNL_SBW8]);
    (void)Com_SendSignal(ComConf_ComSignal_SBW9 , &u1_tp_sgnl[ALERT_D_SBW_RWSGNL_SBW9]);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertD_sbwPdSftfRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertD_sbwPdSftfRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    U1              u1_t_sgnl;

    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U                            ) &&
       (u1_a_DST                          == (U1)ALERT_REQ_D_SBW_PD_SFTF_MSG_07)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_SBW2, &u1_t_sgnl);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     3/24/2020  SN       New.                                                                                               */
/*  5.1.0     5/ 7/2020  DS       Fix matrix table for PD_RIS.                                                                       */
/*  5.2.0     9/ 8/2020  MO       Matrix table for PD_RIS, PD_ACCN and PD_PREQ and VOM for PD_ACCN and PD_PREQ was updated.          */
/*  5.3.0    10/19/2020  DS       Fix CAN Frame for B_R_SBW PCN1S01 -> SBW1G01.                                                      */
/*  5.4.0    12/16/2020  SO       Change matrix table for PD_ACTF, and change general module.                                        */
/*  5.5.0    12/16/2020  KT       Update for 032D CV.                                                                                */
/*  5.6.0     6/24/2021  KT       Add PD_SILUA CH.                                                                                   */
/*  5.6.1     1/20/2022  HU       Update for 840B #2 CV(Version update).                                                             */
/*  5.7.0     7/ 6/2022  RI       Fix by adding shift type condition to SBW4.(METHUD900B-5503)                                       */
/*  5.7.1     7/13/2022  KK       Update for 840B #2 1A(Version update).                                                             */
/*  5.8.0     1/15/2024  GM       Update for 19PFv3.                                                                                 */
/*  5.9.0     2/10/2025  HF       Change for BEV System_Consideration_1.(MET-D_SBW-CSTD-3-00-A-C0)                                   */
/*                                                                                                                                   */
/*  * SN   = Shinichiro Naito, NTTD MSE                                                                                              */
/*  * DS   = Daisuke Suzuki, NTTD MSE                                                                                                */
/*  * MO   = Masaya Ozawa, NTTD MSE                                                                                                  */
/*  * SO   = Syuhei Ooshima, NTTD MSE                                                                                                */
/*  * KT   = Kenichi Takahashi, NTTD MSE                                                                                             */
/*  * HU   = Hidekazu Usui, NTTD MSE                                                                                                 */
/*  * RI   = Ren Ito, NTTD MSE                                                                                                       */
/*  * KK   = Kenta Kawahara, NTTD MSE                                                                                                */
/*  * GM   = Glen Monteposo, DTPH                                                                                                    */
/*  * HF   = Hinari Fukamachi, KSE                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
