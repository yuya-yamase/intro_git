/* 5.0.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert C_HCS                                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_HCS_C_MAJOR                      (5)
#define ALERT_C_HCS_C_MINOR                      (0)
#define ALERT_C_HCS_C_PATCH                      (1)

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
#if (ALERT_C_HCS_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_C_HCS.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_C_HCS_TTB_NUM_DST                  (32U)
#define ALERT_C_HCS_TT_NUM_DST                   (21U)
#define ALERT_C_HCS_PD_NUM_DST                   (27U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_alert_c_hcs_ttb_msgsts;
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertC_hcsTtbSrcchk     (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertC_hcsTtSrcchk      (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertC_hcsPdSrcchk      (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static void    vd_s_AlertC_hcsPdRwTx        (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U1  u1_sp_ALERT_C_HCS_TTB_DST[ALERT_C_HCS_TTB_NUM_DST] = {
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
    (U1)ALERT_REQ_C_HCS_TTB_ACCESS_MODE,                                       /* 19 ACCESS_MODE                                     */
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

static const U1  u1_sp_ALERT_C_HCS_TT_DST[ALERT_C_HCS_TT_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_C_HCS_TT_GRN_ON,                                             /* 01 GRN_ON                                          */
    (U1)ALERT_REQ_C_HCS_TT_GRN_FLASH,                                          /* 02 GRN_FLASH                                       */
    (U1)ALERT_REQ_C_HCS_TT_AMBER_ON,                                           /* 03 AMBER_ON                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 04 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 05 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 06 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 07 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 08 UNKNOWN                                         */
    (U1)ALERT_REQ_C_HCS_TT_AMBER_ON,                                           /* 09 AMBER_ON                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 10 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 16 UNKNOWN                                         */
    (U1)ALERT_REQ_C_HCS_TT_AMBER_ON,                                           /* 17 AMBER_ON                                        */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 18 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 19 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 20 UNKNOWN                                         */
};

static const U1  u1_sp_ALERT_C_HCS_PD_DST[ALERT_C_HCS_PD_NUM_DST] = {
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 00 UNKNOWN                                         */
    (U1)ALERT_REQ_C_HCS_PD_HCSMLFNC,                                           /* 01 HCSMLFNC                                        */
    (U1)ALERT_REQ_C_HCS_PD_ASUSMLFNC,                                          /* 02 ASUSMLFNC                                       */
    (U1)ALERT_REQ_C_HCS_PD_AHCMLFNC,                                           /* 03 AHCMLFNC                                        */
    (U1)ALERT_REQ_C_HCS_PD_ASUSTMODE,                                          /* 04 ASUSTMODE                                       */
    (U1)ALERT_REQ_C_HCS_PD_VHRISE,                                             /* 05 VHRISE                                          */
    (U1)ALERT_REQ_C_HCS_PD_VHLOW,                                              /* 06 VHLOW                                           */
    (U1)ALERT_REQ_C_HCS_PD_VSPD_HIGH,                                          /* 07 VSPD_HIGH                                       */
    (U1)ALERT_REQ_C_HCS_PD_SYSTMP_HIGH,                                        /* 08 SYSTMP_HIGH                                     */
    (U1)ALERT_REQ_C_HCS_PD_HCS_UNAVAIL,                                        /* 09 HCS_UNAVAIL                                     */
    (U1)ALERT_REQ_C_HCS_PD_FRLIFTMLFNC,                                        /* 10 FRLIFTMLFNC                                     */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 14 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 15 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 16 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 17 UNKNOWN                                         */
    (U1)ALERT_REQ_C_HCS_PD_HCSMLFNC,                                           /* 18 HCSMLFNC                                        */
    (U1)ALERT_REQ_C_HCS_PD_ASUSMLFNC,                                          /* 19 ASUSMLFNC                                       */
    (U1)ALERT_REQ_C_HCS_PD_AHCMLFNC,                                           /* 20 AHCMLFNC                                        */
    (U1)ALERT_REQ_C_HCS_PD_FRLIFTMLFNC,                                        /* 21 FRLIFTMLFNC                                     */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 22 UNKNOWN                                         */
    (U1)ALERT_REQ_C_HCS_PD_HCSMLFNC,                                           /* 23 HCSMLFNC                                        */
    (U1)ALERT_REQ_C_HCS_PD_ASUSMLFNC,                                          /* 24 ASUSMLFNC                                       */
    (U1)ALERT_REQ_C_HCS_PD_AHCMLFNC,                                           /* 25 AHCMLFNC                                        */
    (U1)ALERT_REQ_C_HCS_PD_FRLIFTMLFNC                                         /* 26 FRLIFTMLFNC                                     */
};

static const U4  u4_sp_ALERT_C_HCS_TT_CRIT[ALERT_C_HCS_TT_NUM_DST] = {
    (U4)0x00000000U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x00000001U,                                                           /* 01 GRN_ON                                          */
    (U4)0x00000002U,                                                           /* 02 GRN_FLASH                                       */
    (U4)0x00000003U,                                                           /* 03 AMBER_ON                                        */
    (U4)0x00000020U,                                                           /* 04 UNKNOWN                                         */
    (U4)0x00000040U,                                                           /* 05 UNKNOWN                                         */
    (U4)0x00000044U,                                                           /* 06 UNKNOWN                                         */
    (U4)0x00000048U,                                                           /* 07 UNKNOWN                                         */
    (U4)0x0000004CU,                                                           /* 08 UNKNOWN                                         */
    (U4)0x00000050U,                                                           /* 09 AMBER_ON                                        */
    (U4)0x00000054U,                                                           /* 10 UNKNOWN                                         */
    (U4)0x00000058U,                                                           /* 11 UNKNOWN                                         */
    (U4)0x0000005CU,                                                           /* 12 UNKNOWN                                         */
    (U4)0x00000060U,                                                           /* 13 UNKNOWN                                         */
    (U4)0x00000064U,                                                           /* 14 UNKNOWN                                         */
    (U4)0x00000068U,                                                           /* 15 UNKNOWN                                         */
    (U4)0x0000006CU,                                                           /* 16 UNKNOWN                                         */
    (U4)0x00000070U,                                                           /* 17 AMBER_ON                                        */
    (U4)0x00000074U,                                                           /* 18 UNKNOWN                                         */
    (U4)0x00000078U,                                                           /* 19 UNKNOWN                                         */
    (U4)0x0000007CU                                                            /* 20 UNKNOWN                                         */
};

static const U4  u4_sp_ALERT_C_HCS_TT_MASK[ALERT_C_HCS_TT_NUM_DST] = {
    (U4)0x00000063U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x00000063U,                                                           /* 01 GRN_ON                                          */
    (U4)0x00000063U,                                                           /* 02 GRN_FLASH                                       */
    (U4)0x00000063U,                                                           /* 03 AMBER_ON                                        */
    (U4)0x00000060U,                                                           /* 04 UNKNOWN                                         */
    (U4)0x0000007CU,                                                           /* 05 UNKNOWN                                         */
    (U4)0x0000007CU,                                                           /* 06 UNKNOWN                                         */
    (U4)0x0000007CU,                                                           /* 07 UNKNOWN                                         */
    (U4)0x0000007CU,                                                           /* 08 UNKNOWN                                         */
    (U4)0x0000007CU,                                                           /* 09 AMBER_ON                                        */
    (U4)0x0000007CU,                                                           /* 10 UNKNOWN                                         */
    (U4)0x0000007CU,                                                           /* 11 UNKNOWN                                         */
    (U4)0x0000007CU,                                                           /* 12 UNKNOWN                                         */
    (U4)0x0000007CU,                                                           /* 13 UNKNOWN                                         */
    (U4)0x0000007CU,                                                           /* 14 UNKNOWN                                         */
    (U4)0x0000007CU,                                                           /* 15 UNKNOWN                                         */
    (U4)0x0000007CU,                                                           /* 16 UNKNOWN                                         */
    (U4)0x0000007CU,                                                           /* 17 AMBER_ON                                        */
    (U4)0x0000007CU,                                                           /* 18 UNKNOWN                                         */
    (U4)0x0000007CU,                                                           /* 19 UNKNOWN                                         */
    (U4)0x0000007CU                                                            /* 20 UNKNOWN                                         */
};

static const U4  u4_sp_ALERT_C_HCS_PD_CRIT[ALERT_C_HCS_PD_NUM_DST] = {
    (U4)0x00000000U,                                                           /* 00 UNKNOWN                                         */
    (U4)0x00000001U,                                                           /* 01 HCSMLFNC                                        */
    (U4)0x00000002U,                                                           /* 02 ASUSMLFNC                                       */
    (U4)0x00000003U,                                                           /* 03 AHCMLFNC                                        */
    (U4)0x00000004U,                                                           /* 04 ASUSTMODE                                       */
    (U4)0x00000005U,                                                           /* 05 VHRISE                                          */
    (U4)0x00000006U,                                                           /* 06 VHLOW                                           */
    (U4)0x00000007U,                                                           /* 07 VSPD_HIGH                                       */
    (U4)0x00000008U,                                                           /* 08 SYSTMP_HIGH                                     */
    (U4)0x00000009U,                                                           /* 09 HCS_UNAVAIL                                     */
    (U4)0x0000000AU,                                                           /* 10 FRLIFTMLFNC                                     */
    (U4)0x0000000BU,                                                           /* 11 UNKNOWN                                         */
    (U4)0x0000000CU,                                                           /* 12 UNKNOWN                                         */
    (U4)0x0000000DU,                                                           /* 13 UNKNOWN                                         */
    (U4)0x0000000EU,                                                           /* 14 UNKNOWN                                         */
    (U4)0x0000000FU,                                                           /* 15 UNKNOWN                                         */
    (U4)0x00000080U,                                                           /* 16 UNKNOWN                                         */
    (U4)0x00000100U,                                                           /* 17 UNKNOWN                                         */
    (U4)0x00000110U,                                                           /* 18 HCSMLFNC                                        */
    (U4)0x00000120U,                                                           /* 19 ASUSMLFNC                                       */
    (U4)0x00000130U,                                                           /* 20 AHCMLFNC                                        */
    (U4)0x00000140U,                                                           /* 21 FRLIFTMLFNC                                     */
    (U4)0x00000180U,                                                           /* 22 UNKNOWN                                         */
    (U4)0x00000190U,                                                           /* 23 HCSMLFNC                                        */
    (U4)0x000001A0U,                                                           /* 24 ASUSMLFNC                                       */
    (U4)0x000001B0U,                                                           /* 25 AHCMLFNC                                        */
    (U4)0x000001C0U                                                            /* 26 FRLIFTMLFNC                                     */
};

static const U4  u4_sp_ALERT_C_HCS_PD_MASK[ALERT_C_HCS_PD_NUM_DST] = {
    (U4)0x0000018FU,                                                           /* 00 UNKNOWN                                         */
    (U4)0x0000018FU,                                                           /* 01 HCSMLFNC                                        */
    (U4)0x0000018FU,                                                           /* 02 ASUSMLFNC                                       */
    (U4)0x0000018FU,                                                           /* 03 AHCMLFNC                                        */
    (U4)0x0000018FU,                                                           /* 04 ASUSTMODE                                       */
    (U4)0x0000018FU,                                                           /* 05 VHRISE                                          */
    (U4)0x0000018FU,                                                           /* 06 VHLOW                                           */
    (U4)0x0000018FU,                                                           /* 07 VSPD_HIGH                                       */
    (U4)0x0000018FU,                                                           /* 08 SYSTMP_HIGH                                     */
    (U4)0x0000018FU,                                                           /* 09 HCS_UNAVAIL                                     */
    (U4)0x0000018FU,                                                           /* 10 FRLIFTMLFNC                                     */
    (U4)0x0000018FU,                                                           /* 11 UNKNOWN                                         */
    (U4)0x0000018FU,                                                           /* 12 UNKNOWN                                         */
    (U4)0x0000018FU,                                                           /* 13 UNKNOWN                                         */
    (U4)0x0000018FU,                                                           /* 14 UNKNOWN                                         */
    (U4)0x0000018FU,                                                           /* 15 UNKNOWN                                         */
    (U4)0x00000180U,                                                           /* 16 UNKNOWN                                         */
    (U4)0x000001F0U,                                                           /* 17 UNKNOWN                                         */
    (U4)0x000001F0U,                                                           /* 18 HCSMLFNC                                        */
    (U4)0x000001F0U,                                                           /* 19 ASUSMLFNC                                       */
    (U4)0x000001F0U,                                                           /* 20 AHCMLFNC                                        */
    (U4)0x000001F0U,                                                           /* 21 FRLIFTMLFNC                                     */
    (U4)0x000001F0U,                                                           /* 22 UNKNOWN                                         */
    (U4)0x000001F0U,                                                           /* 23 HCSMLFNC                                        */
    (U4)0x000001F0U,                                                           /* 24 ASUSMLFNC                                       */
    (U4)0x000001F0U,                                                           /* 25 AHCMLFNC                                        */
    (U4)0x000001F0U                                                            /* 26 FRLIFTMLFNC                                     */
};

const ST_ALERT_MTRX st_gp_ALERT_C_HCS_MTRX[3] = {
    {
        &u4_s_AlertC_hcsTtbSrcchk,                                             /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4*)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4*)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_HCS_TTB_DST[0],                                         /* u1p_DST                                            */
        (U2)ALERT_C_HCS_TTB_NUM_DST,                                           /* u2_num_srch                                        */
        (U1)ALERT_VOM_BAT_WT                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertC_hcsTtSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_C_HCS_TT_MASK[0],                                         /* u4p_MASK                                           */
        &u4_sp_ALERT_C_HCS_TT_CRIT[0],                                         /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_HCS_TT_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_C_HCS_TT_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertC_hcsPdSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertC_hcsPdRwTx,                                                /* fp_vd_XDST                                         */

        &u4_sp_ALERT_C_HCS_PD_MASK[0],                                         /* u4p_MASK                                           */
        &u4_sp_ALERT_C_HCS_PD_CRIT[0],                                         /* u4p_CRIT                                           */

        &u1_sp_ALERT_C_HCS_PD_DST[0],                                          /* u1p_DST                                            */
        (U2)ALERT_C_HCS_PD_NUM_DST,                                            /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertC_hcsInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertC_hcsInit(void)
{
    u1_s_alert_c_hcs_ttb_msgsts = (U1)COM_NO_RX;
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_hcsTtbSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_hcsTtbSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_C_HCS_TTB_TO_THRSH  = ((U2)10000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_C_HCS_TTB_MSGSTS    = (U1)2U;
    static const U4 u4_s_ALERT_C_HCS_BIT_BAT_WT    = (U4)0x00000010U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ASC1S90,
                                     (U2)OXCAN_RX_SYS_NRX_PAR | (U2)OXCAN_RX_SYS_TOE_PAR,
                                     u2_s_ALERT_C_HCS_TTB_TO_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    vd_g_AlertBRxTrnsSts(&u1_s_alert_c_hcs_ttb_msgsts, u1_t_msgsts);

    u1_t_sgnl = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_B_LSUS10, &u1_t_sgnl);

    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_s_alert_c_hcs_ttb_msgsts << u1_s_ALERT_C_HCS_TTB_MSGSTS);

    if ((u1_a_VOM & (U1)ALERT_VOM_BAT_WT) != (U1)0U) {
        u4_t_src_chk |= u4_s_ALERT_C_HCS_BIT_BAT_WT;
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_hcsTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_hcsTtSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_C_HCS_TT_TO_THRSH   = ((U2)10000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_C_HCS_TT_LSB_MSGSTS = (U1)5U;
    static const U1 u1_s_ALERT_C_HCS_TT_LSB_ASCEXT = (U1)2U;
    static const U1 u1_s_ALERT_C_HCS_TT_ASCEXT_MSK = (U1)7U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;
    U1              u1_t_ascext;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ASC1S90,
                                     (U2)OXCAN_RX_SYS_NRX_POE | (U2)OXCAN_RX_SYS_TOE_POE,
                                     u2_s_ALERT_C_HCS_TT_TO_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

    u1_t_sgnl     = (U1)0U;
    u1_t_ascext   = u1_g_AlertHcsAscext() & u1_s_ALERT_C_HCS_TT_ASCEXT_MSK;
    (void)Com_ReceiveSignal(ComConf_ComSignal_LFTIND, &u1_t_sgnl);

    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_ascext << u1_s_ALERT_C_HCS_TT_LSB_ASCEXT);
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_C_HCS_TT_LSB_MSGSTS);

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertC_hcsPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertC_hcsPdSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U2 u2_s_ALERT_C_HCS_PD_TO_THRSH   = ((U2)10000U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_C_HCS_PD_LSB_MSGSTS = (U1)7U;
    static const U1 u1_s_ALERT_C_HCS_PD_LSB_ASCEXT = (U1)4U;
    static const U1 u1_s_ALERT_C_HCS_PD_ASCEXT_MSK = (U1)7U;
    U4              u4_t_src_chk;
    U1              u1_t_sgnl;
    U1              u1_t_msgsts;
    U1              u1_t_ascext;

    u1_t_msgsts   = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ASC1S90,
                                     (U2)OXCAN_RX_SYS_NRX_POE | (U2)OXCAN_RX_SYS_TOE_POE,
                                     u2_s_ALERT_C_HCS_PD_TO_THRSH) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
    u1_t_sgnl   = (U1)0U;
    u1_t_ascext = u1_g_AlertHcsAscext() & u1_s_ALERT_C_HCS_PD_ASCEXT_MSK;
    (void)Com_ReceiveSignal(ComConf_ComSignal_ASCMINF, &u1_t_sgnl);

    u4_t_src_chk  = (U4)u1_t_sgnl;
    u4_t_src_chk |= ((U4)u1_t_ascext << u1_s_ALERT_C_HCS_PD_LSB_ASCEXT);
    u4_t_src_chk |= ((U4)u1_t_msgsts << u1_s_ALERT_C_HCS_PD_LSB_MSGSTS);

    return(u4_t_src_chk);
}


/*===================================================================================================================================*/
/*  static void    vd_s_AlertC_hcsPdRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertC_hcsPdRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    U1              u1_t_sgnl;

    if (((u1_a_VOM & (U1)ALERT_VOM_RWT_EN) != (U1)0U                              )&&
        ((u1_a_DST                          == (U1)ALERT_REQ_C_HCS_PD_HCSMLFNC   )||
         (u1_a_DST                          == (U1)ALERT_REQ_C_HCS_PD_ASUSMLFNC  )||
         (u1_a_DST                          == (U1)ALERT_REQ_C_HCS_PD_AHCMLFNC   )||
         (u1_a_DST                          == (U1)ALERT_REQ_C_HCS_PD_FRLIFTMLFNC))){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else {
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_SUSW, &u1_t_sgnl);
}
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0    07/09/2024  YR       Newly created for 19PFv3                                                                           */
/*  5.0.1    07/26/2024  YR       QAC Fix                                                                                            */
/*                                                                                                                                   */
/*                                                                                                                                   */
/*  * YR   = Yhana Regalario, DTPH                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
