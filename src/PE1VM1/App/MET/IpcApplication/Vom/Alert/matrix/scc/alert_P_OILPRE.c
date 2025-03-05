/* 5.8.2 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert P_OILPRE                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_OILPRE_C_MAJOR                   (5)
#define ALERT_P_OILPRE_C_MINOR                   (8)
#define ALERT_P_OILPRE_C_PATCH                   (2)

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
#if (ALERT_P_OILPRE_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_P_OILPRE.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_P_OILPRE_WRN_NUM_DST               (31U)
#define ALERT_P_OILPRE_BC_NUM_DST                (64U)

#define ALERT_P_OILPRE_RPM_UNK                   (0x00U)
#define ALERT_P_OILPRE_RPM_LO                    (0x01U)
#define ALERT_P_OILPRE_RPM_HI                    (0x02U)

#define ALERT_P_OILPRE_THRSH_EHV_ECO             ((U2)5000U / (U2)OXCAN_MAIN_TICK)
#define ALERT_P_OILPRE_RXSTAT_NUM                (2U)
#define ALERT_P_OILPRE_RXSTAT_WRN                (0U)
#define ALERT_P_OILPRE_RXSTAT_BC                 (1U)
#define ALERT_P_OILPRE_JDG_NUM                   (8U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_alert_p_oilprewrn_ne1_elpsd;
static U4      u4_s_alert_p_oilprebc_ne1_elpsd;
static U4      u4_s_alert_p_oilprewrn_dly_elpsd;
static U4      u4_s_alert_p_oilprebc_dly_elpsd;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertP_oilpreWrnSrcchk  (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U4      u4_s_AlertP_oilpreBcSrcchk   (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U1      u1_s_AlertP_oilpreRxJudgeSgnl(const U1 u1_a_RXID);
static U1      u1_s_AlertP_oilpreRpmrng     (U4 * u4p_a_ne1_tm_elpsd);
static void    vd_s_AlertP_oilpreWrnRwTx    (const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST);
static U1      u1_s_AlertP_oilpreOilpreSw   (void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4  u4_sp_ALERT_P_OILPRE_WRN_CRIT[ALERT_P_OILPRE_WRN_NUM_DST] = {
    (U4)0x00000080U,                                                           /* 00 TT_ON                                           */
    (U4)0x00000181U,                                                           /* 01 WRN_ON                                          */
    (U4)0x00000191U,                                                           /* 02 WRN_OFF                                         */
    (U4)0x00000182U,                                                           /* 03 WRN_FLSH                                        */
    (U4)0x00000183U,                                                           /* 04 WRN_OFF                                         */
    (U4)0x000001A2U,                                                           /* 05 WRN_ON                                          */
    (U4)0x000000A4U,                                                           /* 06 TT_ON                                           */
    (U4)0x000001B1U,                                                           /* 07 WRN_OFF                                         */
    (U4)0x000001B2U,                                                           /* 08 WRN_FLSH                                        */
    (U4)0x000000C0U,                                                           /* 09 TT_ON                                           */
    (U4)0x000001C1U,                                                           /* 10 WRN_ON                                          */
    (U4)0x000001C2U,                                                           /* 11 WRN_FLSH                                        */
    (U4)0x000001C3U,                                                           /* 12 WRN_OFF                                         */
    (U4)0x000001C8U,                                                           /* 13 WRN_FLSH                                        */
    (U4)0x000001D1U,                                                           /* 14 WRN_OFF                                         */
    (U4)0x00000400U,                                                           /* 15 TT_ON                                           */
    (U4)0x00000500U,                                                           /* 16 TT_ON                                           */
    (U4)0x00000580U,                                                           /* 17 TT_ON                                           */
    (U4)0x00000581U,                                                           /* 18 WRN_ON                                          */
    (U4)0x00000582U,                                                           /* 19 WRN_FLSH                                        */
    (U4)0x00000584U,                                                           /* 20 TT_ON                                           */
    (U4)0x000005A1U,                                                           /* 21 WRN_ON                                          */
    (U4)0x000005A2U,                                                           /* 22 WRN_ON                                          */
    (U4)0x000005B2U,                                                           /* 23 WRN_FLSH                                        */
    (U4)0x000005B3U,                                                           /* 24 WRN_ON                                          */
    (U4)0x000005C0U,                                                           /* 25 TT_ON                                           */
    (U4)0x000005C1U,                                                           /* 26 WRN_ON                                          */
    (U4)0x000005C2U,                                                           /* 27 WRN_FLSH                                        */
    (U4)0x000005C4U,                                                           /* 28 TT_ON                                           */
    (U4)0x000005C8U,                                                           /* 29 WRN_FLSH                                        */
    (U4)0x00000700U                                                            /* 30 WRN_FLSH                                        */
};
static const U4  u4_sp_ALERT_P_OILPRE_WRN_MASK[ALERT_P_OILPRE_WRN_NUM_DST] = {
    (U4)0x000004D7U,                                                           /* 00 TT_ON                                           */
    (U4)0x000005D7U,                                                           /* 01 WRN_ON                                          */
    (U4)0x000005F7U,                                                           /* 02 WRN_OFF                                         */
    (U4)0x000005E7U,                                                           /* 03 WRN_FLSH                                        */
    (U4)0x000005E7U,                                                           /* 04 WRN_OFF                                         */
    (U4)0x000005F6U,                                                           /* 05 WRN_ON                                          */
    (U4)0x000004F4U,                                                           /* 06 TT_ON                                           */
    (U4)0x000005F5U,                                                           /* 07 WRN_OFF                                         */
    (U4)0x000005F7U,                                                           /* 08 WRN_FLSH                                        */
    (U4)0x000004FFU,                                                           /* 09 TT_ON                                           */
    (U4)0x000005FFU,                                                           /* 10 WRN_ON                                          */
    (U4)0x000005EFU,                                                           /* 11 WRN_FLSH                                        */
    (U4)0x000005FFU,                                                           /* 12 WRN_OFF                                         */
    (U4)0x000005E8U,                                                           /* 13 WRN_FLSH                                        */
    (U4)0x000005FDU,                                                           /* 14 WRN_OFF                                         */
    (U4)0x00000700U,                                                           /* 15 TT_ON                                           */
    (U4)0x00000780U,                                                           /* 16 TT_ON                                           */
    (U4)0x000007C7U,                                                           /* 17 TT_ON                                           */
    (U4)0x000007E5U,                                                           /* 18 WRN_ON                                          */
    (U4)0x000007E7U,                                                           /* 19 WRN_FLSH                                        */
    (U4)0x000007C4U,                                                           /* 20 TT_ON                                           */
    (U4)0x000007E7U,                                                           /* 21 WRN_ON                                          */
    (U4)0x000007F6U,                                                           /* 22 WRN_ON                                          */
    (U4)0x000007F7U,                                                           /* 23 WRN_FLSH                                        */
    (U4)0x000007F7U,                                                           /* 24 WRN_ON                                          */
    (U4)0x000007EFU,                                                           /* 25 TT_ON                                           */
    (U4)0x000007EDU,                                                           /* 26 WRN_ON                                          */
    (U4)0x000007EFU,                                                           /* 27 WRN_FLSH                                        */
    (U4)0x000007ECU,                                                           /* 28 TT_ON                                           */
    (U4)0x000007E8U,                                                           /* 29 WRN_FLSH                                        */
    (U4)0x00000700U                                                            /* 30 WRN_FLSH                                        */
};
static const U1  u1_sp_ALERT_P_OILPRE_WRN_DST[ALERT_P_OILPRE_WRN_NUM_DST] = {
    (U1)ALERT_REQ_P_OILPRE_WRN_TT_ON,                                          /* 00 TT_ON                                           */
    (U1)ALERT_REQ_P_OILPRE_WRN_WRN_ON,                                         /* 01 WRN_ON                                          */
    (U1)ALERT_REQ_P_OILPRE_WRN_WRN_OFF,                                        /* 02 WRN_OFF                                         */
    (U1)ALERT_REQ_P_OILPRE_WRN_WRN_FLSH,                                       /* 03 WRN_FLSH                                        */
    (U1)ALERT_REQ_P_OILPRE_WRN_WRN_OFF,                                        /* 04 WRN_OFF                                         */
    (U1)ALERT_REQ_P_OILPRE_WRN_WRN_ON,                                         /* 05 WRN_ON                                          */
    (U1)ALERT_REQ_P_OILPRE_WRN_TT_ON,                                          /* 06 TT_ON                                           */
    (U1)ALERT_REQ_P_OILPRE_WRN_WRN_OFF,                                        /* 07 WRN_OFF                                         */
    (U1)ALERT_REQ_P_OILPRE_WRN_WRN_FLSH,                                       /* 08 WRN_FLSH                                        */
    (U1)ALERT_REQ_P_OILPRE_WRN_TT_ON,                                          /* 09 TT_ON                                           */
    (U1)ALERT_REQ_P_OILPRE_WRN_WRN_ON,                                         /* 10 WRN_ON                                          */
    (U1)ALERT_REQ_P_OILPRE_WRN_WRN_FLSH,                                       /* 11 WRN_FLSH                                        */
    (U1)ALERT_REQ_P_OILPRE_WRN_WRN_OFF,                                        /* 12 WRN_OFF                                         */
    (U1)ALERT_REQ_P_OILPRE_WRN_WRN_FLSH,                                       /* 13 WRN_FLSH                                        */
    (U1)ALERT_REQ_P_OILPRE_WRN_WRN_OFF,                                        /* 14 WRN_OFF                                         */
    (U1)ALERT_REQ_P_OILPRE_WRN_TT_ON,                                          /* 15 TT_ON                                           */
    (U1)ALERT_REQ_P_OILPRE_WRN_TT_ON,                                          /* 16 TT_ON                                           */
    (U1)ALERT_REQ_P_OILPRE_WRN_TT_ON,                                          /* 17 TT_ON                                           */
    (U1)ALERT_REQ_P_OILPRE_WRN_WRN_ON,                                         /* 18 WRN_ON                                          */
    (U1)ALERT_REQ_P_OILPRE_WRN_WRN_FLSH,                                       /* 19 WRN_FLSH                                        */
    (U1)ALERT_REQ_P_OILPRE_WRN_TT_ON,                                          /* 20 TT_ON                                           */
    (U1)ALERT_REQ_P_OILPRE_WRN_WRN_ON,                                         /* 21 WRN_ON                                          */
    (U1)ALERT_REQ_P_OILPRE_WRN_WRN_ON,                                         /* 22 WRN_ON                                          */
    (U1)ALERT_REQ_P_OILPRE_WRN_WRN_FLSH,                                       /* 23 WRN_FLSH                                        */
    (U1)ALERT_REQ_P_OILPRE_WRN_WRN_ON,                                         /* 24 WRN_ON                                          */
    (U1)ALERT_REQ_P_OILPRE_WRN_TT_ON,                                          /* 25 TT_ON                                           */
    (U1)ALERT_REQ_P_OILPRE_WRN_WRN_ON,                                         /* 26 WRN_ON                                          */
    (U1)ALERT_REQ_P_OILPRE_WRN_WRN_FLSH,                                       /* 27 WRN_FLSH                                        */
    (U1)ALERT_REQ_P_OILPRE_WRN_TT_ON,                                          /* 28 TT_ON                                           */
    (U1)ALERT_REQ_P_OILPRE_WRN_WRN_FLSH,                                       /* 29 WRN_FLSH                                        */
    (U1)ALERT_REQ_P_OILPRE_WRN_WRN_FLSH                                        /* 30 WRN_FLSH                                        */
};
static const U1  u1_sp_ALERT_P_OILPRE_BC_DST[ALERT_P_OILPRE_BC_NUM_DST] = {
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
    (U1)ALERT_REQ_P_OILPRE_BC_ON,                                              /* 10 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 11 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 12 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 13 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILPRE_BC_ON,                                              /* 14 ON                                              */
    (U1)ALERT_REQ_P_OILPRE_BC_ON,                                              /* 15 ON                                              */
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
    (U1)ALERT_REQ_P_OILPRE_BC_ON,                                              /* 26 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 27 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 28 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 29 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILPRE_BC_ON,                                              /* 30 ON                                              */
    (U1)ALERT_REQ_P_OILPRE_BC_ON,                                              /* 31 ON                                              */
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
    (U1)ALERT_REQ_P_OILPRE_BC_ON,                                              /* 42 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 43 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 44 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 45 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILPRE_BC_ON,                                              /* 46 ON                                              */
    (U1)ALERT_REQ_P_OILPRE_BC_ON,                                              /* 47 ON                                              */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 48 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 49 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 50 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 51 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 52 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 53 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 54 UNKNOWN                                         */
    (U1)ALERT_REQ_UNKNOWN,                                                     /* 55 UNKNOWN                                         */
    (U1)ALERT_REQ_P_OILPRE_BC_ON,                                              /* 56 ON                                              */
    (U1)ALERT_REQ_P_OILPRE_BC_ON,                                              /* 57 ON                                              */
    (U1)ALERT_REQ_P_OILPRE_BC_ON,                                              /* 58 ON                                              */
    (U1)ALERT_REQ_P_OILPRE_BC_ON,                                              /* 59 ON                                              */
    (U1)ALERT_REQ_P_OILPRE_BC_ON,                                              /* 60 ON                                              */
    (U1)ALERT_REQ_P_OILPRE_BC_ON,                                              /* 61 ON                                              */
    (U1)ALERT_REQ_P_OILPRE_BC_ON,                                              /* 62 ON                                              */
    (U1)ALERT_REQ_P_OILPRE_BC_ON                                               /* 63 ON                                              */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_P_OILPRE_MTRX[2] = {
    {
        &u4_s_AlertP_oilpreWrnSrcchk,                                          /* fp_u4_SRC_CHK                                      */
        &vd_s_AlertP_oilpreWrnRwTx,                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_P_OILPRE_WRN_MASK[0],                                     /* u4p_MASK                                           */
        &u4_sp_ALERT_P_OILPRE_WRN_CRIT[0],                                     /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_OILPRE_WRN_DST[0],                                      /* u1p_DST                                            */
        (U2)ALERT_P_OILPRE_WRN_NUM_DST,                                        /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    },
    {
        &u4_s_AlertP_oilpreBcSrcchk,                                           /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        (const U4 *)vdp_PTR_NA,                                                /* u4p_MASK                                           */
        (const U4 *)vdp_PTR_NA,                                                /* u4p_CRIT                                           */

        &u1_sp_ALERT_P_OILPRE_BC_DST[0],                                       /* u1p_DST                                            */
        (U2)ALERT_P_OILPRE_BC_NUM_DST,                                         /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertP_oilpreInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertP_oilpreInit(void)
{
    u4_s_alert_p_oilprewrn_ne1_elpsd = (U4)0U;
    u4_s_alert_p_oilprebc_ne1_elpsd  = (U4)0U;
    u4_s_alert_p_oilprewrn_dly_elpsd = (U4)0U;
    u4_s_alert_p_oilprebc_dly_elpsd  = (U4)0U;
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_oilpreWrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_oilpreWrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U4 u4_s_ALERT_P_OILPRE_WRN_BIT_OPSW = (U4)0x00000080U;
    static const U4 u4_s_ALERT_P_OILPRE_WRN_DLY_CMP  = (U4)0x00000008U;
    static const U4 u4_s_ALERT_P_OILPRE_WRN_DLY_TM   = ((U4)1000U / (U4)ALERT_MAIN_TICK);
    static const U4 u4_s_ALERT_P_OILPRE_WRN_LAS_MSK  = (U4)0x00000007U;
    static const U2 u2_s_ALERT_P_OILPRE_WRN_TSH_PD01 = ((U2)3600U / (U2)OXCAN_MAIN_TICK);
    static const U1 u1_s_ALERT_P_OILPRE_WRN_LSB_JDG  = (U1)4U;
    static const U1 u1_s_ALERT_P_OILPRE_WRN_LSB_RPM  = (U1)5U;
    static const U1 u1_s_ALERT_P_OILPRE_WRN_LSB_IGP  = (U1)8U;
#ifdef ComConf_ComSignal_B_OILPL
    static const U1 u1_s_ALERT_P_OILPRE_WRN_LSB_SGN  = (U1)9U;
    U1              u1_t_sgnl_b_oilpl;
#endif /* ComConf_ComSignal_B_OILPL */
    U1              u1_t_rpmrng;
    U1              u1_t_msgsts;
    U1              u1_t_opsw_act;
    U1              u1_t_sgnl_jdg;
    U1              u1_t_msgstspdc;
    U1              u1_t_igp_pdc;
    U4              u4_t_src_chk;

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U){
        u1_t_rpmrng    = u1_s_AlertP_oilpreRpmrng(&u4_s_alert_p_oilprewrn_ne1_elpsd);
        u4_t_src_chk   = ((U4)u1_t_rpmrng   << u1_s_ALERT_P_OILPRE_WRN_LSB_RPM);
        u1_t_opsw_act  = u1_s_AlertP_oilpreOilpreSw();

        if(u1_t_opsw_act == (U1)IOHW_DIFLT_SWITCH_ACT){
            u4_t_src_chk |= u4_s_ALERT_P_OILPRE_WRN_BIT_OPSW;
        }

        u1_t_sgnl_jdg  = u1_s_AlertP_oilpreRxJudgeSgnl((U1)ALERT_P_OILPRE_RXSTAT_WRN);
        u4_t_src_chk  |= ((U4)u1_t_sgnl_jdg << u1_s_ALERT_P_OILPRE_WRN_LSB_JDG);

        if(u4_s_alert_p_oilprewrn_dly_elpsd >= u4_s_ALERT_P_OILPRE_WRN_DLY_TM){
            u4_s_alert_p_oilprewrn_dly_elpsd = u4_s_ALERT_P_OILPRE_WRN_DLY_TM;
            u4_t_src_chk                    |= u4_s_ALERT_P_OILPRE_WRN_DLY_CMP;
        }

        if((u1_t_opsw_act != (U1)IOHW_DIFLT_SWITCH_ACT) ||
           (u1_t_sgnl_jdg == (U1)TRUE                 ) ||
           (u1_t_rpmrng   != (U1)ALERT_P_OILPRE_RPM_HI)){
            u4_s_alert_p_oilprewrn_dly_elpsd = (U4)0U;
        }
        else{
            u4_s_alert_p_oilprewrn_dly_elpsd++;
        }
        u4_t_src_chk  |= ((U4)u1_a_LAS & u4_s_ALERT_P_OILPRE_WRN_LAS_MSK);

        u1_t_msgstspdc = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PDC1G01_RXCH0,
                                          (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                          u2_s_ALERT_P_OILPRE_WRN_TSH_PD01) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
        if(u1_t_msgstspdc == (U1)COM_NO_RX){
            u1_t_igp_pdc = (U1)0U;
        }
        else if((u1_t_msgstspdc & (U1)COM_TIMEOUT) != (U1)0U){
            u1_t_igp_pdc = (U1)1U;
        }
        else{
            u1_t_igp_pdc = (U1)0U;
            (void)Com_ReceiveSignal(ComConf_ComSignal_IGP_PDC, &u1_t_igp_pdc);
        }
        u4_t_src_chk  |= ((U4)u1_t_igp_pdc  << u1_s_ALERT_P_OILPRE_WRN_LSB_IGP);
#if defined(OXCAN_PDU_RX_CAN_ENG1G97)
        u1_t_msgsts    = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1G97,
                                          (U2)OXCAN_RX_SYS_NRX_IGR,
                                          (U2)U2_MAX) & (U1)COM_NO_RX;
#elif defined(OXCAN_PDU_RX_CAN_ENG1S92)
        u1_t_msgsts    = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1S92,
                                          (U2)OXCAN_RX_SYS_NRX_IGR,
                                          (U2)U2_MAX) & (U1)COM_NO_RX;
#else
        u1_t_msgsts    = (U1)COM_NO_RX;
#endif /* defined(OXCAN_PDU_RX_CAN_ENG1G97) */
        if(u1_t_msgsts == (U1)0U){
#ifdef ComConf_ComSignal_B_OILPL
            u1_t_sgnl_b_oilpl = (U1)0U;
            (void)Com_ReceiveSignal(ComConf_ComSignal_B_OILPL, &u1_t_sgnl_b_oilpl);
            u4_t_src_chk     |= ((U4)u1_t_sgnl_b_oilpl << u1_s_ALERT_P_OILPRE_WRN_LSB_SGN);
#endif /* ComConf_ComSignal_B_OILPL */
        }
    }
    else{
        u4_s_alert_p_oilprewrn_ne1_elpsd = (U4)0U;
        u4_s_alert_p_oilprewrn_dly_elpsd = (U4)0U;
        u4_t_src_chk                     = (U4)0U;
    }
    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertP_oilpreBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertP_oilpreBcSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U4 u4_s_ALERT_P_OILPRE_BC_DLY_CMP   = (U4)0x00000002U;
    static const U4 u4_s_ALERT_P_OILPRE_BC_DLY_TM    = ((U4)1000U / (U4)ALERT_MAIN_TICK);
    static const U2 u2_s_ALERT_P_OILPRE_BC_THSH_PD01 = ((U2)3600U / (U2)OXCAN_MAIN_TICK);
#if defined(OXCAN_PDU_RX_CAN_ENG1G97)
    static const U2 u2_s_ALERT_P_OILPRE_BC_THSH_G97  = ((U2)5000U / (U2)OXCAN_MAIN_TICK);
#elif defined(OXCAN_PDU_RX_CAN_ENG1S92)
    static const U2 u2_s_ALERT_P_OILPRE_BC_THSH_S92  = ((U2)5200U / (U2)OXCAN_MAIN_TICK);
#else
    /* Do Nothing */
#endif /* defined(OXCAN_PDU_RX_CAN_ENG1G97) */
    static const U4 u4_s_ALERT_P_OILPRE_BC_LAS_MSK   = (U4)0x00000001U;
    static const U4 u4_s_ALERT_P_OILPRE_BC_BIT_RPM   = (U4)0x00000004U;
    static const U1 u1_s_ALERT_P_OILPRE_BC_LSB_IGP   = (U1)3U;
#ifdef ComConf_ComSignal_B_OILPL
    static const U1 u1_s_ALERT_P_OILPRE_BC_LSB_SGN   = (U1)4U;
    U1              u1_t_sgnl_b_oilpl;
#endif /* ComConf_ComSignal_B_OILPL */
    U1              u1_t_msgsts;
    U1              u1_t_sgnl_jdg;
    U1              u1_t_opsw_act;
    U1              u1_t_rpmrng;
    U1              u1_t_msgstspdc;
    U1              u1_t_igp_pdc;
    U4              u4_t_src_chk;

    if((u1_a_VOM & (U1)ALERT_VOM_IGN_ON) != (U1)0U){
        u4_t_src_chk   = ((U4)u1_a_LAS & u4_s_ALERT_P_OILPRE_BC_LAS_MSK);
        u1_t_rpmrng    = u1_s_AlertP_oilpreRpmrng(&u4_s_alert_p_oilprebc_ne1_elpsd);
        u1_t_sgnl_jdg  = u1_s_AlertP_oilpreRxJudgeSgnl((U1)ALERT_P_OILPRE_RXSTAT_BC);
        u1_t_opsw_act  = u1_s_AlertP_oilpreOilpreSw();

        if(u1_t_opsw_act != (U1)IOHW_DIFLT_SWITCH_ACT){
            u4_s_alert_p_oilprebc_dly_elpsd = (U4)0U;
        }
        else if(u4_s_alert_p_oilprebc_dly_elpsd >= u4_s_ALERT_P_OILPRE_BC_DLY_TM){
            u4_s_alert_p_oilprebc_dly_elpsd = u4_s_ALERT_P_OILPRE_BC_DLY_TM;
            u4_t_src_chk                   |= u4_s_ALERT_P_OILPRE_BC_DLY_CMP;
        }
        else if(u1_t_sgnl_jdg == (U1)TRUE){
            u4_s_alert_p_oilprebc_dly_elpsd = (U4)0U;
        }
        else if(u1_t_rpmrng == (U1)ALERT_P_OILPRE_RPM_HI){
            u4_s_alert_p_oilprebc_dly_elpsd++;
        }
        else{
            u4_s_alert_p_oilprebc_dly_elpsd = (U4)0U;
        }

        if(u1_t_rpmrng == (U1)ALERT_P_OILPRE_RPM_HI){
            u4_t_src_chk |= u4_s_ALERT_P_OILPRE_BC_BIT_RPM;
        }

        u1_t_msgstspdc = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_PDC1G01_RXCH0,
                                          (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                          u2_s_ALERT_P_OILPRE_BC_THSH_PD01) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
        if(u1_t_msgstspdc == (U1)COM_NO_RX){
            u1_t_igp_pdc  = (U1)0U;
        }
        else if((u1_t_msgstspdc & (U1)COM_TIMEOUT) != (U1)0U){
            u1_t_igp_pdc  = (U1)1U;
        }
        else{
            u1_t_igp_pdc  = (U1)0U;
            (void)Com_ReceiveSignal(ComConf_ComSignal_IGP_PDC, &u1_t_igp_pdc);
        }
        u4_t_src_chk  |= ((U4)u1_t_igp_pdc << u1_s_ALERT_P_OILPRE_BC_LSB_IGP);
#if defined(OXCAN_PDU_RX_CAN_ENG1G97)
        u1_t_msgsts    = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1G97,
                                          (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                          u2_s_ALERT_P_OILPRE_BC_THSH_G97) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#elif defined(OXCAN_PDU_RX_CAN_ENG1S92)
        u1_t_msgsts    = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ENG1S92,
                                          (U2)OXCAN_RX_SYS_NRX_IGR | (U2)OXCAN_RX_SYS_TOE_IGR,
                                          u2_s_ALERT_P_OILPRE_BC_THSH_S92) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);
#else
        u1_t_msgsts    = (U1)COM_NO_RX;
#endif /* defined(OXCAN_PDU_RX_CAN_ENG1G97) */
        if(u1_t_msgsts == (U1)0U){
#ifdef ComConf_ComSignal_B_OILPL
            u1_t_sgnl_b_oilpl = (U1)0U;
            (void)Com_ReceiveSignal(ComConf_ComSignal_B_OILPL, &u1_t_sgnl_b_oilpl);
            u4_t_src_chk     |= ((U4)u1_t_sgnl_b_oilpl << u1_s_ALERT_P_OILPRE_BC_LSB_SGN);
#endif /* ComConf_ComSignal_B_OILPL */
        }
    }
    else{
        u4_s_alert_p_oilprebc_ne1_elpsd = (U4)0U;
        u4_s_alert_p_oilprebc_dly_elpsd = (U4)0U;
        u4_t_src_chk                    = (U4)0U;
    }
    return(u4_t_src_chk);

}
/*===================================================================================================================================*/
/*  static U1      u1_s_AlertP_oilpreRxJudgeSgnl(const U1 u1_a_RXID)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_AlertP_oilpreRxJudgeSgnl(const U1 u1_a_RXID)
{
#if (defined(OXCAN_PDU_RX_CAN_EHV1S90_RXCH0) && defined(ComConf_ComSignal_MOPSINH)) || (defined(OXCAN_PDU_RX_CAN_ECO1S90) && defined(ComConf_ComSignal_OPLMPMSK))
    static const U2 u2_sp_ALERT_P_OILPRE_COMRX[ALERT_P_OILPRE_RXSTAT_NUM] = {
        (U2)(OXCAN_RX_SYS_NRX_IGR),
        (U2)(OXCAN_RX_SYS_NRX_IGR | OXCAN_RX_SYS_TOE_IGR)
    };
    static const U2 u2_sp_ALERT_P_OILPRE_THRSH[ALERT_P_OILPRE_RXSTAT_NUM] = {
        (U2)U2_MAX,
        (U2)ALERT_P_OILPRE_THRSH_EHV_ECO
    };
    static const U1 u1_sp_ALERT_P_OILPRE_COMOPT[ALERT_P_OILPRE_RXSTAT_NUM] = {
        (U1)(COM_NO_RX),
        ((U1)COM_TIMEOUT | (U1)COM_NO_RX)
    };
    static const U1 u1_sp_ALERT_P_OILPRE_JDG[ALERT_P_OILPRE_JDG_NUM] = {
        (U1)FALSE,
        (U1)TRUE,
        (U1)FALSE,
        (U1)FALSE,
        (U1)FALSE,
        (U1)FALSE,
        (U1)FALSE,
        (U1)FALSE
    };
    static const U1 u1_s_P_OILPRE_LSB_MSGSTS = (U1)1U;
    U1              u1_t_sgnl;
    U1              u1_t_sgnl_mopsinh;
    U1              u1_t_sgnl_oplmpmsk;
    U1              u1_t_msgsts;
    U1              u1_t_msg_jdg;
    U1              u1_t_sgnl_jdg;

#if defined(OXCAN_PDU_RX_CAN_EHV1S90_RXCH0) && defined(ComConf_ComSignal_MOPSINH)
    u1_t_msgsts        = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1S90_RXCH0,
                                               u2_sp_ALERT_P_OILPRE_COMRX[u1_a_RXID],
                                               u2_sp_ALERT_P_OILPRE_THRSH[u1_a_RXID]) & u1_sp_ALERT_P_OILPRE_COMOPT[u1_a_RXID];
    u1_t_sgnl          = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_MOPSINH, &u1_t_sgnl);
    u1_t_msg_jdg       = u1_t_sgnl | (U1)(u1_t_msgsts << u1_s_P_OILPRE_LSB_MSGSTS);
    u1_t_sgnl_mopsinh  = u1_sp_ALERT_P_OILPRE_JDG[u1_t_msg_jdg];
#else
    u1_t_sgnl_mopsinh  = (U1)0U;
#endif /* defined(OXCAN_PDU_RX_CAN_EHV1S90_RXCH0) && defined(ComConf_ComSignal_MOPSINH) */

#if defined(OXCAN_PDU_RX_CAN_ECO1S90) && defined(ComConf_ComSignal_OPLMPMSK)
    u1_t_msgsts        = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_ECO1S90,
                                               u2_sp_ALERT_P_OILPRE_COMRX[u1_a_RXID],
                                               u2_sp_ALERT_P_OILPRE_THRSH[u1_a_RXID]) & u1_sp_ALERT_P_OILPRE_COMOPT[u1_a_RXID];
    u1_t_sgnl          = (U1)0U;
    (void)Com_ReceiveSignal(ComConf_ComSignal_OPLMPMSK, &u1_t_sgnl);
    u1_t_msg_jdg       = u1_t_sgnl | (U1)(u1_t_msgsts << u1_s_P_OILPRE_LSB_MSGSTS);
    u1_t_sgnl_oplmpmsk = u1_sp_ALERT_P_OILPRE_JDG[u1_t_msg_jdg];
#else
    u1_t_sgnl_oplmpmsk = (U1)0U;
#endif /* defined(OXCAN_PDU_RX_CAN_ECO1S90) && defined(ComConf_ComSignal_OPLMPMSK) */

    u1_t_sgnl_jdg      = (u1_t_sgnl_mopsinh | u1_t_sgnl_oplmpmsk);

    return(u1_t_sgnl_jdg);
#else
    return((U1)FALSE);
#endif /* (defined(OXCAN_PDU_RX_CAN_EHV1S90_RXCH0) && defined(ComConf_ComSignal_MOPSINH)) || (defined(OXCAN_PDU_RX_CAN_ECO1S90) && defined(ComConf_ComSignal_OPLMPMSK)) */ /* BSW VerUp */
}

/*===================================================================================================================================*/
/*  static U1      u1_s_AlertP_oilpreRpmrng(U4 * u4p_a_ne1_tm_elpsd)                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_AlertP_oilpreRpmrng(U4 * u4p_a_ne1_tm_elpsd)
{
    static const U2 u2_s_ALERT_P_OILPRE_RPM_HI_THRSH = (U2)400U;     /* 400rpm */
    static const U2 u2_s_ALERT_P_OILPRE_RPM_LO_THRSH = (U2)200U;     /* 200rpm */
    static const U4 u4_s_ALERT_P_OILPRE_RPM_HI_ELAPS = ((U4)10000U / (U4)ALERT_MAIN_TICK);
    U1              u1_t_rpmsts;
    U2              u2_t_rpm;
    U1              u1_t_rpmrng;

    u2_t_rpm    = (U2)0U;
    u1_t_rpmsts = u1_g_AlertEngspdRpmInst(&u2_t_rpm);
    if(u1_t_rpmsts == (U1)ALERT_RPM_STSBIT_VALID){
        if(u2_t_rpm < u2_s_ALERT_P_OILPRE_RPM_LO_THRSH){
            u1_t_rpmrng           = (U1)ALERT_P_OILPRE_RPM_LO;
            (*u4p_a_ne1_tm_elpsd) = (U1)0U;
        }
        else if(u2_t_rpm < u2_s_ALERT_P_OILPRE_RPM_HI_THRSH){
            u1_t_rpmrng           = (U1)ALERT_P_OILPRE_RPM_UNK;
            (*u4p_a_ne1_tm_elpsd) = (U1)0U;
        }
        else if((*u4p_a_ne1_tm_elpsd) >= u4_s_ALERT_P_OILPRE_RPM_HI_ELAPS){
            u1_t_rpmrng           = (U1)ALERT_P_OILPRE_RPM_HI;
            (*u4p_a_ne1_tm_elpsd) = u4_s_ALERT_P_OILPRE_RPM_HI_ELAPS;
        }
        else{
            u1_t_rpmrng           = (U1)ALERT_P_OILPRE_RPM_UNK;
            (*u4p_a_ne1_tm_elpsd)++;
        }
    }
    else if((u1_t_rpmsts & (U1)ALERT_RPM_STSBIT_INVALID) != (U1)0U){
        if((*u4p_a_ne1_tm_elpsd) >= u4_s_ALERT_P_OILPRE_RPM_HI_ELAPS){
            u1_t_rpmrng           = (U1)ALERT_P_OILPRE_RPM_HI;
            (*u4p_a_ne1_tm_elpsd) = u4_s_ALERT_P_OILPRE_RPM_HI_ELAPS;
        }
        else{
            u1_t_rpmrng           = (U1)ALERT_P_OILPRE_RPM_UNK;
            (*u4p_a_ne1_tm_elpsd)++;
        }
    }
    else{
        u1_t_rpmrng           = (U1)ALERT_P_OILPRE_RPM_LO;
        (*u4p_a_ne1_tm_elpsd) = (U1)0U;
    }

    return(u1_t_rpmrng);
}

/*===================================================================================================================================*/
/*  static U1      u1_s_AlertP_oilpreOilpreSw(void)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_AlertP_oilpreOilpreSw(void)
{
    U1              u1_t_opsw_act;

#if (defined(ALERT_HW_ID_P_OILPRE_OP_SW) && (ALERT_HW_ID_P_OILPRE_OP_SW != U2_MAX))
    u1_t_opsw_act = u1_g_IoHwDifltSwitch((U2)ALERT_HW_ID_P_OILPRE_OP_SW);
#else
    u1_t_opsw_act = (U1)IOHW_DIFLT_SWITCH_INACT;
#endif
    return(u1_t_opsw_act);
}

/*===================================================================================================================================*/
/*  static void    vd_s_AlertP_oilpreWrnRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_AlertP_oilpreWrnRwTx(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_DST)
{
    static const U1 u1_s_ALERT_P_OILPRE_RWTX_CRT = ((U1)((U1)1U << ALERT_REQ_P_OILPRE_WRN_WRN_ON  )
                                                 |  (U1)((U1)1U << ALERT_REQ_P_OILPRE_WRN_WRN_FLSH)
                                                 |  (U1)((U1)1U << ALERT_REQ_P_OILPRE_WRN_WRN_OFF ));
    static const U1 u1_s_ALERT_P_OILPRE_RWTX_MSK = (U1)0x07U;
    U1              u1_t_sgnl;
    U1              u1_t_rw;

    u1_t_rw = ((U1)1U << (u1_a_DST & u1_s_ALERT_P_OILPRE_RWTX_MSK));
    if(((u1_a_VOM & (U1)ALERT_VOM_RWT_EN        ) != (U1)0U) &&
       ((u1_t_rw  & u1_s_ALERT_P_OILPRE_RWTX_CRT) != (U1)0U)){
        u1_t_sgnl = (U1)ALERT_RW_SGNL_ON;
    }
    else{
        u1_t_sgnl = (U1)ALERT_RW_SGNL_OFF;
    }

    (void)Com_SendSignal(ComConf_ComSignal_OPW, &u1_t_sgnl);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     4/ 8/2020  FN       New.                                                                                               */
/*  5.1.0     5/21/2020  ZS       Fix delay timer countup timing and RPM judg bit timing.                                            */
/*  5.2.0     6/ 1/2020  ZS       Fix u1_s_ALERT_P_OILPRE_BC_BIT_RPM bit on timing.                                                  */
/*  5.3.0     8/27/2020  TN       Modify matrix table for WRN. Modify index table for BC.                                            */
/*  5.4.0    12/ 8/2020  MO       Update for 800B 1A(Version update).                                                                */
/*  5.4.1     1/26/2021  ZS       Modify BIT_RPM data type to U4 for bc.                                                             */
/*  5.5.0     3/17/2021  MO       Change communication disruption time for ENG1S92, ENG1G97.                                         */
/*  5.6.0     8/26/2021  RI       Change timer thresh.                                                                               */
/*  5.7.0    11/11/2021  YN       Add ConfigIF for OP_SW.                                                                            */
/*  5.7.1    11/24/2021  TM       Fix QAC Warning.                                                                                   */
/*  5.7.2    12/16/2021  TM       Fix QAC Warning.                                                                                   */
/*  5.8.0     8/ 5/2022  SAO      Fix Matrix table for WRN CH(Add the ending condition).                                             */
/*  5.8.1     2/16/2023  MY       Change compile switch for ENG1G97 / ENG1S92.                                                       */
/*  5.8.2    10/13/2023  GM       Change compile switch Hard switch input                                                            */
/*                                                                                                                                   */
/*  * FN   = Farah Niwa, NTTD MSE                                                                                                    */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * TN   = Toshiaki Nagashima, NTTD MSE                                                                                            */
/*  * MO   = Masayuki Oofuji, NTTD MSE                                                                                               */
/*  * RI   = Ren Ito, NTTD MSE                                                                                                       */
/*  * YN   = Yuma Nagahara, NTTD MSE                                                                                                 */
/*  * TM   = Tatsuya Mori, NTTD MSE                                                                                                  */
/*  * SAO  = Sachiko Oono, NTTD MSE                                                                                                  */
/*  * MY   = Masaki Yoshizawa, NTTD MSE                                                                                              */
/*  * GM   = Glen Monteposo, DTPH                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/
