/* 5.3.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Alert H_TEVRN                                                                                                                    */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_TEVRN_C_MAJOR                    (5)
#define ALERT_H_TEVRN_C_MINOR                    (3)
#define ALERT_H_TEVRN_C_PATCH                    (0)

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
#if (ALERT_H_TEVRN_C_MAJOR != ALERT_CFG_H_MAJOR)
#error "alert_H_TEVRN.c and alert_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ALERT_H_TEVRN_NUM_DST                    (7U)
#define ALERT_H_TEVRN_SPD_RNG_A                  (1U)
#define ALERT_H_TEVRN_SPD_RNG_B                  (0U)
#define ALERT_H_TEVRN_SPD_UNKNOWN                (2U)
#define ALERT_H_TEVRN_SPD_NUM_TBL                (48U)
#define ALERT_H_TEVRN_RPM_RNG_LO                 (0U)
#define ALERT_H_TEVRN_RPM_RNG_HI                 (1U)
#define ALERT_H_TEVRN_RPM_RNG_OV                 (2U)
#define ALERT_H_TEVRN_RPM_RNG_UNK                (3U)
#define ALERT_H_TEVRN_RPM_STS_VALID              (0U)
#define ALERT_H_TEVRN_RPM_STS_UNKNOWN            (1U)
#define ALERT_H_TEVRN_RPM_STS_INVALID            (2U)
#define ALERT_H_TEVRN_RPMRNG_NUM_TBL             (16U)
#define ALERT_H_TEVRN_RPM_JDG_MID                (1U)
#define ALERT_H_TEVRN_RPM_JDG_HI                 (2U)
#define ALERT_H_TEVRN_RPM_JDG_OV                 (3U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_alert_h_tevrn_spdrng;
static U1      u1_s_alert_h_tevrn_rpmrng;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4      u4_s_AlertH_tevrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS);
static U1      u1_s_AlertH_tevrnSpdrng(void);
static U1      u1_s_AlertH_tevrnRpmrng(U1 * u1p_a_rpmrng);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const U4  u4_sp_ALERT_H_TEVRN_CRIT[ALERT_H_TEVRN_NUM_DST] = {
    (U4)0x10000400U,                                                           /* 00 ON                                              */
    (U4)0x10000500U,                                                           /* 01 ON                                              */
    (U4)0x10000502U,                                                           /* 02 ON                                              */
    (U4)0x10000508U,                                                           /* 03 ON                                              */
    (U4)0x10000540U,                                                           /* 04 ON                                              */
    (U4)0x10000580U,                                                           /* 05 ON                                              */
    (U4)0x10000000U                                                            /* 06 UNKNOWN                                         */
};
static const U4  u4_sp_ALERT_H_TEVRN_MASK[ALERT_H_TEVRN_NUM_DST] = {
    (U4)0x100007F0U,                                                           /* 00 ON                                              */
    (U4)0x100007CEU,                                                           /* 01 ON                                              */
    (U4)0x100007EEU,                                                           /* 02 ON                                              */
    (U4)0x100007E8U,                                                           /* 03 ON                                              */
    (U4)0x100007CEU,                                                           /* 04 ON                                              */
    (U4)0x100007CEU,                                                           /* 05 ON                                              */
    (U4)0x10000400U                                                            /* 06 UNKNOWN                                         */
};
static const U1  u1_sp_ALERT_H_TEVRN_DST[ALERT_H_TEVRN_NUM_DST] = {
    (U1)ALERT_REQ_H_TEVRN_ON,                                                  /* 00 ON                                              */
    (U1)ALERT_REQ_H_TEVRN_ON,                                                  /* 01 ON                                              */
    (U1)ALERT_REQ_H_TEVRN_ON,                                                  /* 02 ON                                              */
    (U1)ALERT_REQ_H_TEVRN_ON,                                                  /* 03 ON                                              */
    (U1)ALERT_REQ_H_TEVRN_ON,                                                  /* 04 ON                                              */
    (U1)ALERT_REQ_H_TEVRN_ON,                                                  /* 05 ON                                              */
    (U1)ALERT_REQ_UNKNOWN                                                      /* 06 UNKNOWN                                         */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_ALERT_MTRX st_gp_ALERT_H_TEVRN_MTRX[1] = {
    {
        &u4_s_AlertH_tevrnSrcchk,                                              /* fp_u4_SRC_CHK                                      */
        vdp_PTR_NA,                                                            /* fp_vd_XDST                                         */

        &u4_sp_ALERT_H_TEVRN_MASK[0],                                          /* u4p_MASK                                           */
        &u4_sp_ALERT_H_TEVRN_CRIT[0],                                          /* u4p_CRIT                                           */

        &u1_sp_ALERT_H_TEVRN_DST[0],                                           /* u1p_DST                                            */
        (U2)ALERT_H_TEVRN_NUM_DST,                                             /* u2_num_srch                                        */
        (U1)ALERT_VOM_IGN_ON                                                   /* u1_vom_act                                         */
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_AlertH_tevrnInit(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_AlertH_tevrnInit(void)
{
    u1_s_alert_h_tevrn_spdrng = (U1)ALERT_H_TEVRN_SPD_UNKNOWN;
    u1_s_alert_h_tevrn_rpmrng = (U1)ALERT_H_TEVRN_RPM_RNG_LO;
}

/*===================================================================================================================================*/
/*  static U4      u4_s_AlertH_tevrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U4      u4_s_AlertH_tevrnSrcchk(const U1 u1_a_VOM, const U4 u4_a_IGN_TM, const U1 u1_a_LAS)
{
    static const U1 u1_s_ALERT_H_TEVRN_LSB_MSG_STS = (U1)2U;
    static const U1 u1_s_ALERT_H_TEVRN_LSB_RPMRNG  = (U1)4U;
    static const U1 u1_s_ALERT_H_TEVRN_LSB_RNG_STS = (U1)6U;
    static const U1 u1_s_ALERT_H_TEVRN_LSB_SPDRNG  = (U1)8U;
    static const U1 u1_s_ALERT_H_TEVRN_LSB_ENABLE  = (U1)10U;
    static const U2 u2_s_ALERT_H_TEVRN_THRSH_TO    = ((U2)3600U / (U2)OXCAN_MAIN_TICK);
    U4              u4_t_src_chk;
    U1              u1_t_msgsts;
    U1              u1_t_sgnl;
    U1              u1_t_spdrng;
    U1              u1_t_rpmrng;
    U1              u1_t_rpmrng_sts;
    U1              u1_t_enable;

    u1_t_enable = u1_g_AlertCfgH_tevrnIsEnable();
    if(u1_t_enable == (U1)TRUE){
        u1_t_msgsts     = u1_g_oXCANRxStat((U2)OXCAN_PDU_RX_CAN_EHV1G02,
                                           (U2)OXCAN_RX_SYS_NRX_POE | (U2)OXCAN_RX_SYS_TOE_POE,
                                           u2_s_ALERT_H_TEVRN_THRSH_TO) & ((U1)COM_TIMEOUT | (U1)COM_NO_RX);

        u4_t_src_chk    = ((U4)u1_t_msgsts     << u1_s_ALERT_H_TEVRN_LSB_MSG_STS);

        u1_t_sgnl       = (U1)0U;
        (void)Com_ReceiveSignal(ComConf_ComSignal_MODID_FS, &u1_t_sgnl);
        u4_t_src_chk   |= (U4)u1_t_sgnl;

        u1_t_spdrng     = u1_s_AlertH_tevrnSpdrng();
        u4_t_src_chk   |= ((U4)u1_t_spdrng     << u1_s_ALERT_H_TEVRN_LSB_SPDRNG);

        u1_t_rpmrng     = (U1)0U;
        u1_t_rpmrng_sts = u1_s_AlertH_tevrnRpmrng(&u1_t_rpmrng);
        u4_t_src_chk   |= ((U4)u1_t_rpmrng     << u1_s_ALERT_H_TEVRN_LSB_RPMRNG);
        u4_t_src_chk   |= ((U4)u1_t_rpmrng_sts << u1_s_ALERT_H_TEVRN_LSB_RNG_STS);

        u4_t_src_chk   |= ((U4)u1_t_enable     << u1_s_ALERT_H_TEVRN_LSB_ENABLE);
    }
    else{
        u4_t_src_chk    = (U4)0U; /* UNKNOWN */
    }

    return(u4_t_src_chk);
}

/*===================================================================================================================================*/
/*  static U1    u1_s_AlertH_tevrnSpdrng(void)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1    u1_s_AlertH_tevrnSpdrng(void)
{
    static const U1 u1_sp_ALERT_H_TEVRN_SPDRNG_TBL[ALERT_H_TEVRN_SPD_NUM_TBL] = {
        /* Spd < 14kmph           */
        /* Spd_rng_B */                /* Spd_rng_A */                /* Unknown */                  /* Undefine */
        (U1)ALERT_H_TEVRN_SPD_RNG_B,   (U1)ALERT_H_TEVRN_SPD_RNG_B,   (U1)ALERT_H_TEVRN_SPD_RNG_B,   (U1)ALERT_H_TEVRN_SPD_RNG_B,   /* Sts Valid         */
        (U1)ALERT_H_TEVRN_SPD_UNKNOWN, (U1)ALERT_H_TEVRN_SPD_UNKNOWN, (U1)ALERT_H_TEVRN_SPD_UNKNOWN, (U1)ALERT_H_TEVRN_SPD_UNKNOWN, /* Sts Unknown       */
        (U1)ALERT_H_TEVRN_SPD_RNG_B,   (U1)ALERT_H_TEVRN_SPD_RNG_B,   (U1)ALERT_H_TEVRN_SPD_RNG_B,   (U1)ALERT_H_TEVRN_SPD_RNG_B,   /* Sts Invalid       */
        (U1)ALERT_H_TEVRN_SPD_RNG_B,   (U1)ALERT_H_TEVRN_SPD_RNG_B,   (U1)ALERT_H_TEVRN_SPD_RNG_B,   (U1)ALERT_H_TEVRN_SPD_RNG_B,   /* Sts Invalid & Unk */
        /* 14kmph <= Spd < 16kmph */
        /* Spd_rng_B */                /* Spd_rng_A */                /* Unknown */                  /* Undefine */
        (U1)ALERT_H_TEVRN_SPD_RNG_B,   (U1)ALERT_H_TEVRN_SPD_RNG_A,   (U1)ALERT_H_TEVRN_SPD_RNG_B,   (U1)ALERT_H_TEVRN_SPD_RNG_B,   /* Sts Valid         */
        (U1)ALERT_H_TEVRN_SPD_UNKNOWN, (U1)ALERT_H_TEVRN_SPD_UNKNOWN, (U1)ALERT_H_TEVRN_SPD_UNKNOWN, (U1)ALERT_H_TEVRN_SPD_UNKNOWN, /* Sts Unknown       */
        (U1)ALERT_H_TEVRN_SPD_RNG_B,   (U1)ALERT_H_TEVRN_SPD_RNG_B,   (U1)ALERT_H_TEVRN_SPD_RNG_B,   (U1)ALERT_H_TEVRN_SPD_RNG_B,   /* Sts Invalid       */
        (U1)ALERT_H_TEVRN_SPD_RNG_B,   (U1)ALERT_H_TEVRN_SPD_RNG_B,   (U1)ALERT_H_TEVRN_SPD_RNG_B,   (U1)ALERT_H_TEVRN_SPD_RNG_B,   /* Sts Invalid & Unk */
        /* 16kmph <= Spd          */
        /* Spd_rng_B */                /* Spd_rng_A */                /* Unknown */                  /* Undefine */
        (U1)ALERT_H_TEVRN_SPD_RNG_A,   (U1)ALERT_H_TEVRN_SPD_RNG_A,   (U1)ALERT_H_TEVRN_SPD_RNG_A,   (U1)ALERT_H_TEVRN_SPD_RNG_A,   /* Sts Valid         */
        (U1)ALERT_H_TEVRN_SPD_UNKNOWN, (U1)ALERT_H_TEVRN_SPD_UNKNOWN, (U1)ALERT_H_TEVRN_SPD_UNKNOWN, (U1)ALERT_H_TEVRN_SPD_UNKNOWN, /* Sts Unknown       */
        (U1)ALERT_H_TEVRN_SPD_RNG_B,   (U1)ALERT_H_TEVRN_SPD_RNG_B,   (U1)ALERT_H_TEVRN_SPD_RNG_B,   (U1)ALERT_H_TEVRN_SPD_RNG_B,   /* Sts Invalid       */
        (U1)ALERT_H_TEVRN_SPD_RNG_B,   (U1)ALERT_H_TEVRN_SPD_RNG_B,   (U1)ALERT_H_TEVRN_SPD_RNG_B,   (U1)ALERT_H_TEVRN_SPD_RNG_B    /* Sts Invalid & Unk */
    };
    static const U2 u2_s_ALERT_H_TEVRN_SPD_HI_THRESH = (U2)1600U;     /* 16kmph */
    static const U2 u2_s_ALERT_H_TEVRN_SPD_LO_THRESH = (U2)1400U;     /* 14kmph */
    static const U1 u1_s_ALERT_H_TEVRN_SPD_HI_BIT    = (U1)0x20U;
    static const U1 u1_s_ALERT_H_TEVRN_SPD_HS_BIT    = (U1)0x10U;
    static const U1 u1_s_ALERT_H_TEVRN_SPD_LO_BIT    = (U1)0x00U;
    static const U1 u1_s_ALERT_H_TEVRN_SPD_MASK      = (U1)0x03U;
    static const U1 u1_s_ALERT_H_TEVRN_SPD_STS       = (U1)2U;
    U2              u2_t_vehspd;
    U1              u1_t_spd_sts;
    U1              u1_t_spdrng_judg;

    u2_t_vehspd  = (U2)0U;
    u1_t_spd_sts = (u1_g_AlertSpdKmphInst(&u2_t_vehspd, (U1)TRUE) & ((U1)ALERT_SPD_STSBIT_UNKNOWN | (U1)ALERT_SPD_STSBIT_INVALID));

    if(u2_t_vehspd >= u2_s_ALERT_H_TEVRN_SPD_HI_THRESH){
        u1_t_spdrng_judg = u1_s_ALERT_H_TEVRN_SPD_HI_BIT;
    }
    else if(u2_t_vehspd < u2_s_ALERT_H_TEVRN_SPD_LO_THRESH){
        u1_t_spdrng_judg = u1_s_ALERT_H_TEVRN_SPD_LO_BIT;
    }
    else{
        u1_t_spdrng_judg = u1_s_ALERT_H_TEVRN_SPD_HS_BIT;
    }

    u1_s_alert_h_tevrn_spdrng &= u1_s_ALERT_H_TEVRN_SPD_MASK;
    u1_t_spdrng_judg          |= u1_s_alert_h_tevrn_spdrng;
    u1_t_spdrng_judg          |= (U1)(u1_t_spd_sts << u1_s_ALERT_H_TEVRN_SPD_STS);

    u1_s_alert_h_tevrn_spdrng  = u1_sp_ALERT_H_TEVRN_SPDRNG_TBL[u1_t_spdrng_judg];

    return(u1_s_alert_h_tevrn_spdrng);
}

/*===================================================================================================================================*/
/*  static U1      u1_s_AlertH_tevrnRpmrng(U1 * u1p_a_rpmrng)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_AlertH_tevrnRpmrng(U1 * u1p_a_rpmrng)
{
    static const U1 u1_sp_ALERT_H_TEVRN_RPMRNG_TBL[ALERT_H_TEVRN_RPMRNG_NUM_TBL] = {
        /* NE1 < 200rpm             , 200rpm <= NE1 < 400rpm      , NE1 = 400rpm                ,  400rpm < NE1 */
        (U1)ALERT_H_TEVRN_RPM_RNG_LO, (U1)ALERT_H_TEVRN_RPM_RNG_LO, (U1)ALERT_H_TEVRN_RPM_RNG_HI, (U1)ALERT_H_TEVRN_RPM_RNG_OV, /* RNG_LO    */
        (U1)ALERT_H_TEVRN_RPM_RNG_LO, (U1)ALERT_H_TEVRN_RPM_RNG_HI, (U1)ALERT_H_TEVRN_RPM_RNG_HI, (U1)ALERT_H_TEVRN_RPM_RNG_OV, /* RNG_HI    */
        (U1)ALERT_H_TEVRN_RPM_RNG_LO, (U1)ALERT_H_TEVRN_RPM_RNG_HI, (U1)ALERT_H_TEVRN_RPM_RNG_HI, (U1)ALERT_H_TEVRN_RPM_RNG_OV, /* RNG_OV    */
        (U1)ALERT_H_TEVRN_RPM_RNG_LO, (U1)ALERT_H_TEVRN_RPM_RNG_LO, (U1)ALERT_H_TEVRN_RPM_RNG_HI, (U1)ALERT_H_TEVRN_RPM_RNG_OV  /* RNG_UNK   */
    };
    static const U1 u1_s_ALERT_H_TEVRN_SFT_RPMRNG    = (U1)2U;
    static const U2 u2_s_ALERT_H_TEVRN_RPM_HI_THRESH = (U2)400U;     /* 400rpm */
    static const U2 u2_s_ALERT_H_TEVRN_RPM_LO_THRESH = (U2)200U;     /* 200rpm */
    static const U1 u1_s_ALERT_H_TEVRN_RPM_MASK      = (U1)0x03U;
    U1              u1_t_ret;
    U1              u1_t_rpmsts;
    U1              u1_t_rpmidx;
    U2              u2_t_rpm;

    u2_t_rpm      = (U2)0U;
    u1_t_rpmsts   = u1_g_AlertEngspdRpmInst(&u2_t_rpm);
    if(u1_t_rpmsts == (U1)ALERT_RPM_STSBIT_VALID){
        u1_t_rpmidx = (U1)((u1_s_alert_h_tevrn_rpmrng & u1_s_ALERT_H_TEVRN_RPM_MASK) << u1_s_ALERT_H_TEVRN_SFT_RPMRNG);
        if(u2_t_rpm < u2_s_ALERT_H_TEVRN_RPM_LO_THRESH){
            /* Do Nothing. RPM judgment is Low(00b). */
        }
        else if(u2_t_rpm < u2_s_ALERT_H_TEVRN_RPM_HI_THRESH){
            u1_t_rpmidx |= (U1)ALERT_H_TEVRN_RPM_JDG_MID;
        }
        else if(u2_t_rpm == u2_s_ALERT_H_TEVRN_RPM_HI_THRESH){
            u1_t_rpmidx |= (U1)ALERT_H_TEVRN_RPM_JDG_HI;
        }
        else{
            u1_t_rpmidx |= (U1)ALERT_H_TEVRN_RPM_JDG_OV;
        }

        u1_t_ret                  = (U1)ALERT_H_TEVRN_RPM_STS_VALID;
        u1_s_alert_h_tevrn_rpmrng = u1_sp_ALERT_H_TEVRN_RPMRNG_TBL[u1_t_rpmidx];

    }
    else if((u1_t_rpmsts & (U1)ALERT_RPM_STSBIT_INVALID) != (U1)0U){
        u1_t_ret                  = (U1)ALERT_H_TEVRN_RPM_STS_INVALID;
        u1_s_alert_h_tevrn_rpmrng = (U1)ALERT_H_TEVRN_RPM_RNG_UNK;
    }
    else{
        u1_t_ret                  = (U1)ALERT_H_TEVRN_RPM_STS_UNKNOWN;
        u1_s_alert_h_tevrn_rpmrng = (U1)ALERT_H_TEVRN_RPM_RNG_UNK;
    }

    *u1p_a_rpmrng = u1_s_alert_h_tevrn_rpmrng;

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  5.0.0     3/ 6/2020  TH       New.                                                                                               */
/*  5.1.0     8/18/2020  ZS       Fix Spdrng judge logic.                                                                            */
/*  5.1.1     1/27/2021  ZS       Fix QAC Warning.                                                                                   */
/*  5.1.2     3/25/2021  KT       Update how to get the Message Label.                                                               */
/*  5.2.0    10/28/2021  HU       Update for 840B 1A(Version update).                                                                */
/*  5.3.0     3/19/2024  KH       Update for 19PFv3 CV.                                                                              */
/*                                                                                                                                   */
/*  * TH   = Takuya Hiraide, NTTD MSE                                                                                                */
/*  * ZS   = Zenjiro Shamoto, NTTD MSE                                                                                               */
/*  * KT   = Kenichi Takahashi, NTTD MSE                                                                                             */
/*  * HU   = Hidekazu Usui, NTTD MSE                                                                                                 */
/*  * KH   = Kiko Huerte, DTPH                                                                                                       */
/*                                                                                                                                   */
/*===================================================================================================================================*/
