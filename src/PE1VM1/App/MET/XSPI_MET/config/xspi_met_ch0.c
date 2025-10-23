/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  Local Communication SPI                                                                                                          */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_CH0_C_MAJOR                     (0U)
#define XSPI_CH0_C_MINOR                     (0U)
#define XSPI_CH0_C_PATCH                     (0U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "xspi_met.h"
#include "xspi_met_ch0.h"
#include "xspi_met_ch1.h"
#include "xspi_met_ver.h"
#include "xspi_met_vptran.h"
#include "xspi_met_ch_private.h"
#if(AIP_STSW_SUPPORT == 1)
#include "xspi_aisstr.h"
#endif
#include "xspi_met_ch0_cfg.h"

/* Platform */
#include "oxcan.h"
#include "iohw_diflt.h"
#include "iohw_adc.h"
#include "iohw_adc_channel.h"
#if 0   /* BEV BSW provisionally */
#include "CxpiCdd_App.h"
#endif

#include "rim_ctl_cfg.h"
#include "veh_opemd.h"
#include "ivdsh.h"

/* VOM */
#include "dimmer.h"
#if 0   /* BEV Rebase provisionally */
#include "drvind_pwr_pct.h"

/* #include "alert.h" */
#endif   /* BEV Rebase provisionally */
#include "vehspd_kmph.h"
#if 0   /* BEV Rebase provisionally */
#include "ptsctmp_cel.h"
#endif   /* BEV Rebase provisionally */
#include "ambtmp.h"
#if 0   /* BEV Rebase provisionally */
#include "gagdst_attempovhtind.h"
#include "attmp_cel.h"
/* #include "hydrvol.h" */
#endif   /* BEV Rebase provisionally */
#include "tripcom.h"
#include "rcmmui.h"
#include "odo_km.h"
#include "odo_om_rst_if.h"
#include "vptran_sel.h"
#include "locale.h"
#if 0   /* BEV Rebase provisionally */
#include "oilmil.h"
#endif   /* BEV Rebase provisionally */
#include "avggrph.h"

#include "himgadj.h"
#include "hdimmgr_if.h"

/* VSV */
#include "gagdst_nxmph.h"
#include "wchime.h"
#include "illumi.h"

/* HMI */
#include "hmiodo.h"
#include "hmimaint.h"
#include "hmilocale.h"
#include "hmiputxt.h"
#include "hmitt.h"
#include "hmiwchime.h"
#include "hmitripcom.h"
#include "hmiscreen.h"
#include "hmihud.h"

/* EVC */
#include "vardef.h"
#include "vardef_dest.h"
#include "vardef_esopt.h"
#include "calibration.h"

/* Legacy */
#if 0   /* BEV BSW provisionally */
#include "es_inspect.h"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((XSPI_CH0_C_MAJOR != XSPI_CFG_H_MAJOR) || \
     (XSPI_CH0_C_MINOR != XSPI_CFG_H_MINOR) || \
     (XSPI_CH0_C_PATCH != XSPI_CFG_H_PATCH))
#error "xspi_ch0.c and xspi_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((XSPI_CH0_C_MAJOR != XSPI_CH_H_MAJOR) || \
     (XSPI_CH0_C_MINOR != XSPI_CH_H_MINOR) || \
     (XSPI_CH0_C_PATCH != XSPI_CH_H_PATCH))
#error "xspi_ch0.c and xspi_ch_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XSPI_UNKNOWN                        (0xFFFFFFFFU)
#define XSPI_STS_SHIFT                      (30U)
#if 0   /* BEV Rebase provisionally */
#define XSPI_OVERHEAT_SHIFT                 (29U)
#endif   /* BEV Rebase provisionally */
#define XSPI_EV_KM_ACOFF_STS_SHIFT          (27U)
#define XSPI_EV_KM_ACON_STS_SHIFT           (24U)
#if 0   /* BEV Rebase provisionally */
#define XSPI_PMCHGTH_SHIFT                  (16U)
#define XSPI_PMPWRTH_STS_SHIFT              (28U)
#endif   /* BEV Rebase provisionally */

#define XSPI_MSK_01BIT                      (0x00000001U)
#define XSPI_MSK_02BIT                      (0x00000003U)
#define XSPI_MSK_03BIT                      (0x00000007U)
#define XSPI_MSK_04BIT                      (0x0000000FU)
#define XSPI_MSK_05BIT                      (0x0000001FU)
#define XSPI_MSK_06BIT                      (0x0000003FU)
#define XSPI_MSK_07BIT                      (0x0000007FU)
#define XSPI_MSK_08BIT                      (0x000000FFU)
#define XSPI_MSK_09BIT                      (0x000001FFU)
#define XSPI_MSK_10BIT                      (0x000003FFU)
#define XSPI_MSK_11BIT                      (0x000007FFU)
#define XSPI_MSK_12BIT                      (0x00000FFFU)
#define XSPI_MSK_13BIT                      (0x00001FFFU)
#define XSPI_MSK_14BIT                      (0x00003FFFU)
#define XSPI_MSK_15BIT                      (0x00007FFFU)
#define XSPI_MSK_16BIT                      (0x0000FFFFU)
#define XSPI_MSK_17BIT                      (0x0001FFFFU)

#if 0   /* BEV Rebase provisionally */
#define XSPI_MSK_CSTMCLK                    (0x0001ffc0U)
#define XSPI_MSK_CSTMDAT                    (0xfffff1f0U)

#define XSPI_NUM_STRSW                      (1U)
#define XSPI_NUM_RHEO                       (2U)

#define XSPI_BLINKBIT                       (0x04U)

#define XSPI_TRIPCOM_FE_SUP                 (1U)
#define XSPI_TRIPCOM_HE_SUP                 (0U)
#define XSPI_TRIPCOM_EE_SUP                 (0U)
#define XSPI_TRIPCOM_IDLSTP_SUP             (0U)

#define XSPI_MAINT_SUP                      (1U)

#define XSPI_SPN_INVALID                    (0x3F3F3F3FU)

#define XSPI_POWERTRAIN_CONVE               (0U)
#define XSPI_POWERTRAIN_HYBRID              (1U)
#define XSPI_POWERTRAIN_FUELCELL            (2U)
#define XSPI_POWERTRAIN_UNDEF               (3U)

#define XSPI_HUDRESET_SEND_TIMS             (5U)

#define XSPI_NUM_DG_2F_2B01_HUD_TEST        (7U)
#define XSPI_HUD_BLACK                      (1U)
#define XSPI_HUD_WHITE                      (2U)
#define XSPI_HUD___RED                      (3U)
#define XSPI_HUD_GREEN                      (4U)
#define XSPI_HUD__BLUE                      (5U)
#define XSPI_HUD_CLBAR                      (6U)
#define XSPI_HUD_ADJST                      (7U)

#define XSPI_VER_NORX                       (0x00U)
#define XSPI_VER_UNDEF                      (0xFEU)
#define XSPI_NUM_ROB_STAMP                  (17U)

#define XSPI_RW_ADSW                        (0x01U)

#endif   /* BEV Rebase provisionally */
#define XSPI_SHIFT_3BYTE                    (24U)
#define XSPI_SHIFT_2BYTE                    (16U)
#define XSPI_SHIFT_1BYTE                    (8U)
#define XSPI_SHIFT_NON                      (0U)
#if 0   /* BEV Rebase provisionally */
#define XSPI_UNIT_LOW                       (0x0000007FU)
#define XSPI_UNIT_HI                        (0x00003F00U)

#define XSPI_USRNAME_SIZE                   (16U)

#define XSPI_MAINTEDIST_OFFSET              (32768)

#endif   /* BEV Rebase provisionally */
#define XSPI_AMB_CEL_MAX                    (10000U)
#define XSPI_AMB_FAH_MAX                    (18100U)
#define XSPI_AMB_LSB_1                      (100U)

/* @@@ Provisional @@@ */
#define XSPI_HUD_DTA_NUM                    (7U)
#if 0   /* BEV Rebase provisionally */

#define XSPI_NICKNAME_USERNUM               (3U)
#define XSPI_NICKNAME_TXTNUM                (10U)

#endif   /* BEV Rebase provisionally */
#define XSPI_UNIT_MPGIMP                    (4U)
#define XSPI_UNIT_VAL_ELECO_KMPKWH          (0U)   /* Electricity cost    : km/kWh                 */
#define XSPI_UNIT_VAL_ELECO_KWHP100KM       (1U)   /* Electricity cost    : kWh/100km              */
#define XSPI_UNIT_VAL_ELECO_MILEPKWH        (2U)   /* Electricity cost    : miles/kWh              */
#if 0   /* BEV Rebase provisionally */

#define XSPI_DESIGN_CLASSIC_SUP             (0x40U)
#define XSPI_DESIGN_METALIC_SUP             (0x80U)

#define XSPI_PWR_1MHV                       (3U)

#define XSPI_BELSTTYPE_3R6S_CVT             (2U)

#define XSPI_SIZE_U1                        (1U)
#define XSPI_SIZE_U2                        (2U)

#define XSPI_MCUID_NUM                      (137U)
#define XSPI_MCUID_MINMAXCHK_NUM            (5U)

#endif   /* BEV Rebase provisionally */
#define XSPI_VDF_AREA_SIZE                  (9U)
#if 0   /* BEV Rebase provisionally */

#define XSPI_CLOCK_UNKNOWN                  (0x1EFBEU)
#endif   /* BEV Rebase provisionally */

#define XSPI_VM_1WORD                       (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define u1_XSPI_MET_READ_BYTE(u4_buf , u1_pos)          ((U1)(((u4_buf) >> ((U1)8U * (u1_pos))) & ((U1)0xFFU)))
#define u1_XSPI_MET_READ__BIT(u4_buf , u1_pos , u1_len) ((U1)((U1)((u4_buf)  >> (u1_pos)) & (U1)((1U << (u1_len)) - 1U)))

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
typedef struct{
    U4                          u4_crit;
    U1                          u1_act;
}ST_XSPI_DG_HUD;

typedef struct{
    U1                          u1_rx;
    U1                          u1_fail;
}ST_XSPI_DTC;

typedef struct{
    const U2                    u2_xspiid;
    const U1                    u1_bitpos;
    const U1                    u1_size;
    volatile const void *       vdp_mcuid;
}ST_XSPI_CALIB;

typedef struct{
    const U2                    u2_xspiid;
    const U1                    u1_bitpos;
    volatile const U1 *         u1p_mcuid;
    const U4                    u4_min;
    const U4                    u4_max;
    const U4                    u4_def;
}ST_XSPI_CALIB_CHK;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1           u1_s_xspi_vipos_disp;
static U1           u1_s_xspi_dimsw;
static U1           u1_s_xspi_gvifsts;
static U1           u1_s_xspi_disp_gvifsts;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static inline void    vd_s_XSpiCfgTxPowerMd(       U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgTxTripCnt(       U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgTxVariation(     U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgTxLocale(        U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgTxStrsw(         U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgTxVehSpd(        U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgTxHybsys(        U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgTxPtsctmp(       U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgTxAmbtmp(        U4 * u4_ap_pdu_tx);
/* static inline void    vd_s_XSpiCfgTxHydrovol(      U4 * u4_ap_pdu_tx); */
static inline void    vd_s_XSpiCfgTxShift(         U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgTxDimming(       U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgTxClock(         U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgTxOdo(           U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgTxTripcom(       U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgTxTelltale(      U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgTxRcmmui(        U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgTxMaint(         U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgTxHud(           U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgTxWrnmsg(        U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgTxMulmed(        U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgTxCalib(         U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgTxAttmp(         U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgTxNickname(      U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgTxAvgGrph(       U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgTxMetcstmMcst(   U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgTxPwrmet(        U4 * u4_ap_pdu_tx);
static inline void    vd_s_XSpiCfgRxDispsts(    const U4 * u4_ap_PDU_RX);
static inline void    vd_s_XSpiCfgRxMcst(       const U4 * u4_ap_PDU_RX);
static inline void    vd_s_XSpiCfgRxMaint(      const U4 * u4_ap_PDU_RX);
static inline void    vd_s_XSpiCfgRxWchime(     const U4 * u4_ap_PDU_RX);
static inline void    vd_s_XSpiCfgRxLocale(     const U4 * u4_ap_PDU_RX);
static inline void    vd_s_XSpiCfgRxRcmmui(     const U4 * u4_ap_PDU_RX);
static inline void    vd_s_XSpiCfgRxRemoteWarn( const U4 * u4_ap_PDU_RX);
static inline void    vd_s_XSpiCfgRxOdo(        const U4 * u4_ap_PDU_RX);
static inline void    vd_s_XSpiCfgRxTripcom(    const U4 * u4_ap_PDU_RX);
static inline void    vd_s_XSpiCfgRxHUD(        const U4 * u4_ap_PDU_RX);
static inline void    vd_s_XSpiCfgRxMetcstm(    const U4 * u4_ap_PDU_RX);
static inline void    vd_s_XSpiCfgRxAvgGrph(    const U4 * u4_ap_PDU_RX);
static inline void    vd_s_XSpiCfgRxMETDISP(    const U4 * u4_ap_PDU_RX);


static inline void    vd_s_XSpiCfgEsopt(           U4 * u4_ap_pdu_tx);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Functions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxPowerMd(U4 * u4_ap_pdu_tx)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxPowerMd(       U4 * u4_ap_pdu_tx) {
#if 0   /* BEV Rebase provisionally */

    U4 u4_t_dspactrans;
    U1 u1_t_actransbon;
    U1 u1_t_ign_10p5v;
    U1 u1_t_ign_10p5v_cvt;                                                              /* IGVOL_AD10BIT CONVERT                     */

    u1_t_actransbon = u1_g_IoHwDifltSwitch((U2)IOHW_DISGNL_B_MONI_3P6V);
    u1_t_ign_10p5v  = u1_g_IoHwDifltSwitch((U2)IOHW_DISGNL_IGN_10P5V);

    if (u1_t_actransbon == (U1)FALSE) {
        u4_t_dspactrans = (U4)TRUE;
    }
    else {
        u4_t_dspactrans = (U4)FALSE;
    }

    if (u1_t_ign_10p5v == (U1)IOHW_DIFLT_SWITCH_ACT) {
        u1_t_ign_10p5v_cvt = (U1)TRUE;
    }
    else {
        u1_t_ign_10p5v_cvt = (U1)FALSE;
    }
    u4_ap_pdu_tx[0]   = ((U4)u1_g_VehopemdIgnOn());                                     /* IGR_ON                                    */
    u4_ap_pdu_tx[0]   |= ((U4)u1_t_ign_10p5v_cvt << 1);                                 /* IGVOL_AD10BIT                             */
    u4_ap_pdu_tx[0]   |= ((U4)u1_g_VehopemdStaOn() << 2);                               /* MST_ON                                    */
    u4_ap_pdu_tx[0]   |= ((U4)u1_g_VehopemdAccOn() << 3);                               /* ACC_ON                                    */
    u4_ap_pdu_tx[0]   |= (u4_t_dspactrans << 4);                                        /* ACTRANS_B_ON                              */
    u4_ap_pdu_tx[0]   |= ((U4)u1_g_VehopemdPtsOn((U1)VEH_OPEMD_PTS_INV_OFF) << 5);      /* CAN_MOVE_FLAG                             */
    u4_ap_pdu_tx[0]   |= ((U4)u1_g_VehopemdIgnpOn() << 7);                              /* IGP_ON                                    */
    u4_ap_pdu_tx[0]   |= ((U4)u1_g_VehopemdBaOn() << 8);                               /* BA ON                                     */
    u4_ap_pdu_tx[0]   |= ((U4)u1_g_VehspdGetStopFlg() << 9);                            /* STOP_JDG_FLAG                             */
#endif   /* BEV Rebase provisionally */
}

static inline void    vd_s_XSpiCfgTxTripCnt(       U4 * u4_ap_pdu_tx) {} /* @@Stub */

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxVariation(U4 * u4_ap_pdu_tx)                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxVariation(     U4 * u4_ap_pdu_tx) {

    U4  u4_t_loop;
    U1  u1_t_subdigspd;
    U1  u1_t_uniove;
    U1  u1_t_stpindcvt;                                                /*  STPLMPIND                                            */
    U1  u1_t_unitslct_fueco;                                           /*  UNITSLCT_FUECO                                       */
    U1  u1_t_tmnt_sup;                                                 /*  TMNT_SUP                                             */
    U1  u1_t_4wd_typ;                                                  /*  4WD_TYP                                              */
    U1  u1_t_engrpm_unit;                                              /*  ENGRPM_UNIT                                          */
    U1  u1_t_fugag_scale;                                              /*  FUGAG_SCALE                                          */
    U1  u1_t_spd_red_scale;                                            /*  SPD_RED_SCALE                                        */
    U1  u1_t_var_ecojdg_type;                                          /*  VAR_ECOJDG_TYPE                                      */
    U1  u1_t_langslct_type;                                            /*  LANGSLCT_TYPE                                        */
    U1  u1_t_smasta_na;                                                /*  SMASTA_NA                                            */
    U1  u1_t_var_4wdsys_disp;                                          /*  VAR_4WDSYS_DISP                                      */
    U1  u1_t_tempdest;                                                 /*  TEMPDEST                                             */
    U1  u1_t_cal_dsptyp;                                               /*  CALENDAR_DISP_TYPE                                   */
    U1  u1_t_hvsysind;
    U1  u1_t_sys_hcs;                                                  /*  SYS_HCS                                              */
    U1  u1_t_dist;

    /* Change for 970B/850B */
    u4_ap_pdu_tx[1] = ((U4)u1_g_VardefTtTrcoff() & (U4)0x01U);         /*  VAR_TT_TRCOFF                                        */

    u4_ap_pdu_tx[1] |= ((U4)u1_g_VardefTtBrake() & (U4)0x01U) << 1;    /*  VAR_TT_BRAKE                                         */

    u4_ap_pdu_tx[1] |= ((U4)u1_g_VardefTtAbs() & (U4)0x01U) << 2;      /*  VAR_TT_ABS                                           */

    u4_ap_pdu_tx[1] |= ((U4)u1_g_VardefTtEpbPkb() & (U4)0x01U) << 3;   /*  VAR_TT_EPBPKB                                        */

    u4_ap_pdu_tx[1] |= ((U4)u1_g_VardefTtTailHead() & (U4)0x01U) << 4; /*  VAR_TT_TAILHEAD                                      */

    u4_ap_pdu_tx[1] |= ((U4)u1_g_VardefTtCheckEG() & (U4)0x01U) << 5;  /*  VAR_TT_CHKEG                                         */

    u4_ap_pdu_tx[1] |= ((U4)u1_g_VardefTTVscExp() & (U4)0x01U) << 14; /*  VAR_TT_VSCEXP                                         */

    u4_ap_pdu_tx[1] |= ((U4)u1_g_VardefPtsRx() & (U4)0x1fU) << 16;     /*  VAR_PTSYS                                            */

    u1_t_subdigspd = u1_g_UnitSubSpd();
    u4_ap_pdu_tx[2] |= ((U4)u1_t_subdigspd & (U4)0x03U) << 11;         /*  SUBDIGSPD_DISP                                       */

    u1_t_uniove    = u1_g_VardefChainaReq();
    u4_ap_pdu_tx[2] |= ((U4)u1_t_uniove & (U4)0x01U) << 13;            /*  UNIOVE_ICON                                          */

    /* Redesign If STPIND-CSTD-0 is Applied */
    u1_t_stpindcvt = (U1)1U;
    u4_ap_pdu_tx[2] |= ((U4)u1_t_stpindcvt & (U4)0x01U) << 14;         /*  STPLMPIND                                            */

    u1_t_hvsysind = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_HVSYSIND);
    u4_ap_pdu_tx[2] |= ((U4)u1_t_hvsysind & (U4)0x01U) << 16;          /*  HV_SYS_IND                                           */

    u1_t_unitslct_fueco = u1_g_VardefUnitSlctTypeByPid();
    u4_ap_pdu_tx[2] |= ((U4)u1_t_unitslct_fueco & (U4)0x1FU) << 19;    /*  UNITSLCT_FUECO                                       */

    u1_t_tmnt_sup = u1_g_VardefTmntOpt();
    u4_ap_pdu_tx[2] |= ((U4)u1_t_tmnt_sup & (U4)0x01U) << 24;          /*  TMNT_SUP                                             */

    u1_t_4wd_typ = u1_g_Vardef4wdSysByPid();
    u4_ap_pdu_tx[2] |= ((U4)u1_t_4wd_typ & (U4)0x01U) << 25;           /*  4WD_TYP                                              */

    u1_t_engrpm_unit = u1_g_VardefEngUnit();
    u4_ap_pdu_tx[2] |= ((U4)u1_t_engrpm_unit & (U4)0x03U) << 26;       /*  ENGRPM_UNIT                                          */

    u1_t_fugag_scale = u1_g_VardefFuGauge();
    u4_ap_pdu_tx[2] |= ((U4)u1_t_fugag_scale & (U4)0x01U) << 28;       /*  FUGAG_SCALE                                          */

    u1_t_spd_red_scale = (U1)0U;
    u1_t_dist = u1_g_Unit((U1)UNIT_IDX_DIST);
    if(u1_t_dist == (U1)UNIT_VAL_DIST_KM){
        u1_t_spd_red_scale = u1_g_VardefEuSpdScaleByPid();
    }
    u4_ap_pdu_tx[2] |= ((U4)u1_t_spd_red_scale & (U4)0x01U) << 29;     /*  SPD_RED_SCALE                                        */

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)XSPI_VDF_AREA_SIZE; u4_t_loop++){
        u4_ap_pdu_tx[4U + u4_t_loop] = (U4)0x00U;
    }

    vd_s_XSpiCfgEsopt(&u4_ap_pdu_tx[4]);

#if 0   /* BEV Rebase provisionally */
    u4_ap_pdu_tx[9] |= (U4)TRUE << 17;                                 /*  SYS_MOP                  */ /* BEV SV1 provisionally */

    u4_ap_pdu_tx[10] |= (U4)TRUE << 30;                                /*  SYS_DMASSP               */ /* BEV SV1 provisionally */
    u4_ap_pdu_tx[10] |= (U4)TRUE << 31;                                /*  SYS_DMASEC               */ /* BEV SV1 provisionally */

    u4_ap_pdu_tx[11] |= (U4)TRUE;                                      /*  SYS_DMASDT               */ /* BEV SV1 provisionally */
    u4_ap_pdu_tx[11] |= (U4)TRUE << 1;                                 /*  SYS_DMASTM               */ /* BEV SV1 provisionally */
    u4_ap_pdu_tx[11] |= (U4)TRUE << 2;                                 /*  SYS_DMTODT               */ /* BEV SV1 provisionally */
    u4_ap_pdu_tx[11] |= (U4)TRUE << 3;                                 /*  SYS_DMTOTM               */ /* BEV SV1 provisionally */
    u4_ap_pdu_tx[11] |= (U4)TRUE << 4;                                 /*  SYS_DMTOSP               */ /* BEV SV1 provisionally */
    u4_ap_pdu_tx[11] |= (U4)TRUE << 5;                                 /*  SYS_DMINEC               */ /* BEV SV1 provisionally */
    u4_ap_pdu_tx[11] |= (U4)TRUE << 7;                                 /*  SYS_PERSET               */ /* BEV SV1 provisionally */
    u4_ap_pdu_tx[11] |= (U4)TRUE << 9;                                 /*  SYS_EPS_EPSSBW           */ /* BEV SV1 provisionally */
    u4_ap_pdu_tx[11] |= (U4)TRUE << 20;                                /*  SYS_SW_MULTI_WEATHERLAMP */ /* BEV SV1 provisionally */
    u4_ap_pdu_tx[11] |= (U4)TRUE << 28;                                /*  SYS_SW_CAMERA_WASHER     */ /* BEV SV1 provisionally */

    u4_ap_pdu_tx[12] |= (U4)TRUE;                                      /*  SYS_SW_OBBPBD            */ /* BEV SV1 provisionally */
    u4_ap_pdu_tx[12] |= (U4)TRUE << 5;                                 /*  SYS_DMEVRNGE             */ /* BEV SV1 provisionally */
    u4_ap_pdu_tx[12] |= (U4)TRUE << 6;                                 /*  SYS_DMTOEC               */ /* BEV SV1 provisionally */
    u4_ap_pdu_tx[12] |= (U4)TRUE << 7;                                 /*  SYS_DMM1EC               */ /* BEV SV1 provisionally */

#endif   /* BEV Rebase provisionally */
    u1_t_var_ecojdg_type = u1_g_VardefEcoJudge();
    u4_ap_pdu_tx[13]  = ((U4)u1_t_var_ecojdg_type & (U4)0x01U) << 9;   /*  VAR_ECOJDG_TYPE                                      */

    u1_t_langslct_type = u1_g_VardefLngDBTypeByPid();
    u4_ap_pdu_tx[13] |= ((U4)u1_t_langslct_type & (U4)0x3FU) << 10;    /*  LANGSLCT_TYPE                                        */

    u1_t_sys_hcs      = u1_g_VardefHcsAva();
    u4_ap_pdu_tx[13] |= ((U4)u1_t_sys_hcs & (U4)0x01U) << 22;          /*  SYS_HCS                                              */

    u1_t_var_4wdsys_disp = u1_g_VardefEsOptAvaByCh((U2)VDF_ESO_CH_4WDSYS);
    u4_ap_pdu_tx[13] |= ((U4)u1_t_var_4wdsys_disp & (U4)0x01U) << 23;  /*  VAR_4WDSYS_DISP                                      */

    u1_t_cal_dsptyp = u1_g_VardefCalenderDispTypeByPid();
    u4_ap_pdu_tx[13] |= ((U4)u1_t_cal_dsptyp & (U4)0x03U) << 24;       /*  CALENDAR_DISP_TYPE                                   */

    u1_t_smasta_na = u1_g_VardefSmaStaMIDByPid();
    u4_ap_pdu_tx[13] |= ((U4)u1_t_smasta_na & (U4)0x01U) << 28;        /*  SMASTA_NA                                            */

    u1_t_tempdest = u1_g_VardefTempChrByPid();
    u4_ap_pdu_tx[13] |= ((U4)u1_t_tempdest & (U4)0x01U) << 29;         /*  TEMPDEST                                             */

    /*  Variation:Dynamic Variartion No.1               */
    /*  Variation:Dynamic Variartion No.2               */
    /*  Variation:Dynamic Variartion No.3               */

}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgEsopt(U4 * u4_ap_pdu_tx)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void vd_s_XSpiCfgEsopt(U4 * u4_ap_pdu_tx) {

    U4 u4_tp_xspi_esopt[VDF_ESO_NOW_AVA];
    U4 u4_t_loop;

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)VDF_ESO_NOW_AVA ; u4_t_loop++){
        u4_tp_xspi_esopt[u4_t_loop] = (U4)0U;
    }

    vd_g_VardefEsOptAva(&u4_tp_xspi_esopt[0], (U1)VDF_ESO_NOW_AVA);

    u4_ap_pdu_tx[0] = u4_tp_xspi_esopt[0];
    u4_ap_pdu_tx[1] = u4_tp_xspi_esopt[1];
    u4_ap_pdu_tx[2] = u4_tp_xspi_esopt[2];
    u4_ap_pdu_tx[3] = u4_tp_xspi_esopt[3];
    u4_ap_pdu_tx[4] = u4_tp_xspi_esopt[4];
    u4_ap_pdu_tx[5] = u4_tp_xspi_esopt[5];
    u4_ap_pdu_tx[6] = u4_tp_xspi_esopt[6];
    u4_ap_pdu_tx[7] = u4_tp_xspi_esopt[7];
    u4_ap_pdu_tx[8] = u4_tp_xspi_esopt[8];

}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxLocale(U4 * u4_ap_pdu_tx)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxLocale(        U4 * u4_ap_pdu_tx) {

    U1    u1_t_unitslct;
    U1    u1_t_convert;
    U1    u1_t_convert_eleco;

    u4_ap_pdu_tx[0]  = (U4)u1_g_Language((U1)TRUE);                                 /* LANG         */

    u4_ap_pdu_tx[1]  = ((U4)u1_g_Unit((U1)UNIT_IDX_DIST)     & (U4)0x03U);          /* DISTANCE     */
    u4_ap_pdu_tx[1]  |= (((U4)u1_g_Unit((U1)UNIT_IDX_SPEED)  & (U4)0x03U)  << 2 );  /* SPEED        */

    u1_t_convert     = u1_g_Unit((U1)UNIT_IDX_FUECO);
    u1_t_unitslct    = u1_g_VardefUnitSlctFuecoByPid() & (U1)VDF_UNIT_FUECO_BIT_MPG_UKIMP;

    if((u1_t_convert == (U1)UNIT_VAL_FUECO_MPG_UK) && (u1_t_unitslct != (U1)0U)){
    /* Unit Convert MPG Imperial */
        u1_t_convert  = (U1)XSPI_UNIT_MPGIMP;
    }

    u1_t_convert_eleco = u1_g_Unit((U1)UNIT_IDX_ELECO);
    
    switch(u1_t_convert_eleco){
        case UNIT_VAL_ELECO_KMPKWH:
            u1_t_convert_eleco = (U1)XSPI_UNIT_VAL_ELECO_KMPKWH;
            break;
        case UNIT_VAL_ELECO_KWHP100KM:
            u1_t_convert_eleco = (U1)XSPI_UNIT_VAL_ELECO_KWHP100KM;
            break;
        case UNIT_VAL_ELECO_MILEPKWH:
            u1_t_convert_eleco = (U1)XSPI_UNIT_VAL_ELECO_MILEPKWH;
            break;
        default:
            u1_t_convert_eleco = (U1)XSPI_UNIT_VAL_ELECO_KWHP100KM;
            break;
    }

    u4_ap_pdu_tx[1]  |= (((U4)u1_t_convert & (U4)0x07U)  << 4 );                    /* FUELECO      */
    u4_ap_pdu_tx[1]  |= (((U4)u1_t_convert_eleco             & (U4)0x0FU)  << 8 );  /* ELE          */
    u4_ap_pdu_tx[1]  |= (((U4)u1_g_Unit((U1)UNIT_IDX_AMBTMP) & (U4)0x03U)  << 12);  /* AMBTMP       */
    u4_ap_pdu_tx[1]  |= ((U4)u1_g_TimeFormat12H24H()                       << 14);  /* TMFMT_12H24H */
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxStrsw(U4 * u4_ap_pdu_tx)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxStrsw(         U4 * u4_ap_pdu_tx) {
#if 0   /* BEV Rebase provisionally */

    vd_g_XSpiDsrUnlock((U4)XSPI_DSR_UNLOCK);
    vd_g_XSpiDsrTesmdOw(u1_t_stsw_back);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxVehSpd(U4 * u4_ap_pdu_tx)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxVehSpd(        U4 * u4_ap_pdu_tx) {
    U1  u1_t_sts;
    U2  u2_t_kmph;
    U2  u2_t_mph;

    u2_t_kmph          = (U2)0U;
    u1_t_sts           = u1_g_VehspdKmphInst(&u2_t_kmph, (U1)TRUE);
    u1_t_sts          &= (U1)(VEHSPD_STSBIT_INVALID | VEHSPD_STSBIT_UNKNOWN);
    u4_ap_pdu_tx[0]   = (U4)u2_t_kmph;                                         /* VEHICLE_SPD                                  */
    u4_ap_pdu_tx[0]  |= ((U4)u1_t_sts << XSPI_STS_SHIFT);                  /* VEHSPD_STS                                   */

    u1_t_sts           = u1_g_VehspdKmphBiased(&u2_t_kmph , (U1)FALSE);
    u4_ap_pdu_tx[1]   = (U4)u2_t_kmph;                                         /* VEHICLE_SPD_ANALOG                           */
    u4_ap_pdu_tx[1]  |= ((U4)u1_t_sts << XSPI_STS_SHIFT);                  /* VEHSPD_ANA_STS                               */

    u2_t_kmph          = u2_g_GagdstNxmphDsplyd((U1)GAGDST_NXMPH_KMPH);
    u4_ap_pdu_tx[2]   = (U4)u2_t_kmph;                                         /* VEHICLE_SPD_DIGITAL_KM                       */
    /* u4_ap_pdu_tx[2]  |= ((U4)u1_t_sts << XSPI_STS_SHIFT); */            /* VEHSPD_DIG_STS_KM                            */

    u2_t_mph           = u2_g_GagdstNxmphDsplyd((U1)GAGDST_NXMPH__MPH);
    u4_ap_pdu_tx[3]   = (U4)u2_t_mph;                                          /* VEHICLE_SPD_DIGITAL_MI                       */
    /* u4_ap_pdu_tx[3]  |= ((U4)u1_t_sts << XSPI_STS_SHIFT); */            /* VEHSPD_DIG_STS_MI                            */
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxHybsys(U4 * u4_ap_pdu_tx)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxHybsys(        U4 * u4_ap_pdu_tx) {
#if 0   /* BEV Rebase provisionally */
    U1  u1_t_sts;
    S2  s2_t_hybpct;
    U4  u4_t_putdata;

    s2_t_hybpct       = (S2)0;
    u1_t_sts          = u1_g_XSpiCfgGetHybsys(&s2_t_hybpct);
    /* @@@ Provisional Convert @@@ */
    if (s2_t_hybpct < (S2)0) {
         s2_t_hybpct = (S2)1024 + s2_t_hybpct;
    }
    u4_t_putdata = (U4)((U2)s2_t_hybpct);

    u4_ap_pdu_tx[0]   = u4_t_putdata;                                           /* HYBIND_PER                                   */
    u4_ap_pdu_tx[0]   |= ((U4)u1_t_sts << XSPI_STS_SHIFT);                      /* HYBIND_STS                                   */
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxPwrmet(U4 * u4_ap_pdu_tx)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxPwrmet(U4* u4_ap_pdu_tx) {
#if 0   /* BEV Rebase provisionally */
    U1 u1_t_sts;
    S2 s2_t_pmevcr;
    U2 u2_t_pmevcr;
    S1 s1_t_pmchgth;
    U1 u1_t_pmchgth;
    U2 u2_t_pmpwrth;

    s2_t_pmevcr = (S2)0;
    s1_t_pmchgth = (S1)0;
    u2_t_pmpwrth = (U2)0U;

    u1_t_sts = u1_g_DrvIndPwrPctFltrd(&s2_t_pmevcr);
    u2_t_pmevcr = (U2)s2_t_pmevcr;
    u4_ap_pdu_tx[0] = (U4)u2_t_pmevcr & (U4)XSPI_MSK_10BIT;                 /* PWRMET_PMEVCR                               */
    u4_ap_pdu_tx[0] |= ((U4)u1_t_sts << XSPI_STS_SHIFT);                    /* PWRMET_PMEVCR_STS                           */

    u1_t_sts = u1_g_DrvIndPwrPctChgth(&s1_t_pmchgth);
    u1_t_pmchgth = (U1)s1_t_pmchgth;
    u4_ap_pdu_tx[1] = ((U4)u1_t_pmchgth & (U4)XSPI_MSK_07BIT) << XSPI_PMCHGTH_SHIFT;    /* PWRMET_PMCHGTH              */
    u4_ap_pdu_tx[1] |= ((U4)u1_t_sts << XSPI_STS_SHIFT);                    /* PWRMET_PMCHGTH_STS                          */

    u1_t_sts = u1_g_DrvIndPwrPctPwrth(&u2_t_pmpwrth);
    u4_ap_pdu_tx[1] |= (U4)u2_t_pmpwrth & (U4)XSPI_MSK_09BIT;               /* PWRMET_PMPWRTH                              */
    u4_ap_pdu_tx[1] |= ((U4)u1_t_sts << XSPI_PMPWRTH_STS_SHIFT);            /* PWRMET_PMPWRTH_STS                          */
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxPtsctmp(U4 * u4_ap_pdu_tx)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxPtsctmp(       U4 * u4_ap_pdu_tx) {
#if 0   /* BEV Rebase provisionally */
    U1  u1_t_sts;
    U2  u2_t_ptsctmp;

    u2_t_ptsctmp      = (U2)0U;
    u1_t_sts          = u1_g_PtsctmpCelFltrd(&u2_t_ptsctmp);
    u4_ap_pdu_tx[0]   = (U4)u2_t_ptsctmp;                                      /* ENGINE_TEMP_CEL                              */
    u4_ap_pdu_tx[0]  |= ((U4)u1_t_sts << XSPI_SHIFT_2BYTE);                /* ENGTMP_STS                                   */
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxAmbtmp(U4 * u4_ap_pdu_tx)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxAmbtmp(        U4 * u4_ap_pdu_tx) {
    U1  u1_t_sts;
    U2  u2_t_tmp;

    u2_t_tmp = (U2)0U;

    u1_t_sts = u1_g_AmbtmpCel(&u2_t_tmp);
    if(u2_t_tmp > (U2)XSPI_AMB_CEL_MAX) {
        u2_t_tmp = (U2)XSPI_AMB_CEL_MAX;
    }

    u2_t_tmp /= (U2)XSPI_AMB_LSB_1;

    u4_ap_pdu_tx[0] =  (U4)u1_t_sts;                                           /* AMBTMP_STS                                         */
    u4_ap_pdu_tx[1] =  (U4)u2_t_tmp;                                           /* AMB_TEMP_CEL                                       */

    (void)u1_g_AmbtmpFah(&u2_t_tmp);
    if(u2_t_tmp > (U2)XSPI_AMB_FAH_MAX) {
        u2_t_tmp = (U2)XSPI_AMB_FAH_MAX;
    }

    u2_t_tmp /= (U2)XSPI_AMB_LSB_1;

    u4_ap_pdu_tx[1] |= ((U4)u2_t_tmp << XSPI_SHIFT_2BYTE);                     /* AMB_TEMP_FAH                                       */
}
/* static inline void    vd_s_XSpiCfgTxHydrovol(      U4 * u4_ap_pdu_tx) {} */ /* @@Stub */

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxShift(U4 * u4_ap_pdu_tx)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxShift(         U4 * u4_ap_pdu_tx) {

    U1  u1_t_shift_pos;
    U1  u1_t_shift_blnk;
    U1  u1_t_gear;
    U1  u1_t_gsi;

    u1_t_shift_pos  = (U1)XSPI_VPTRAN_SFT_OFF;
    u1_t_shift_blnk = (U1)XSPI_VPTRAN_SFT_POS_OFF;
    u1_t_gear       = (U1)0U;
    u1_t_gsi        = (U1)0U;

    vd_g_XSpiCfgCvtVptranShift(&u1_t_shift_blnk, &u1_t_shift_pos);
    u1_t_gear         = u1_g_XSpiCfgCvtVptranGear();
    u1_t_gsi          = u1_g_XSpiCfgCvtVptranGsi();

    u4_ap_pdu_tx[0]   = (U4)u1_t_gear;                                          /* SHIFT_GEAR_VAL */
    u4_ap_pdu_tx[0]   |= ((U4)u1_t_shift_pos << 4);                             /* SHIFT_POS_STS */
    u4_ap_pdu_tx[0]   |= ((U4)u1_t_shift_blnk << 8);                            /* SHIFT_BLNK_STS */

    u4_ap_pdu_tx[1]   = (U4)u1_t_gsi;                                           /* GSI DOWN / UP */
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxDimming(U4 * u4_ap_pdu_tx)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxDimming(       U4 * u4_ap_pdu_tx) {
    static const U2    u2_sp_XSPI_UB_DIM[] = {
        (U2)0x0000U, /* Up / Down = ina / ina */
        (U2)0x0200U, /* Up / Down = ina / act */
        (U2)0x0100U, /* Up / Down = act / ina */
        (U2)0x0300U  /* Up / Down = act / act */
    };

    U1  u1_t_daynight;
    U1  u1_t_rheosw;
    U2  u2_t_ub_act;
    U2  u2_t_rheo_lvl;
    U1  u1_t_illumi_mask;

    u1_t_daynight    = u1_g_DimLvlDaynight() & (U1)0x03U;
    u4_ap_pdu_tx[0]  = (U4)u1_t_daynight;                           /* DAYNIGHT                                                 */
    u2_t_rheo_lvl    = u2_g_DimLvlUsadjust(u1_t_daynight);          /* RHEOSTAT                                                 */
    u4_ap_pdu_tx[1]  = ((U4)u2_t_rheo_lvl & (U4)0x000000FFU);
    u2_t_ub_act      = (U2)0U;
    u1_t_rheosw      = u1_CALIB_MCUID0430_RHEOSW;
    u1_t_illumi_mask = u1_g_IllumiTftAlpha();

    switch(u1_t_rheosw){
        case (U1)CALIB_MCUID0430_1_INPUT:
        case (U1)CALIB_MCUID0430_2_INPUT:
            u4_ap_pdu_tx[1] |= (U4)u2_sp_XSPI_UB_DIM[u2_t_ub_act];
            break;
        case (U1)CALIB_MCUID0430_THUMB_WHEEL:
            u4_ap_pdu_tx[1] |= ((U4)u1_g_DimSwVrUpDown() << 8U);
            break;
     /* case (U1)CALIB_MCUID0430_SOFTSW: */
        default:
            /* Do Nothing */
            break;
    }

    u4_ap_pdu_tx[1] |= ((U4)u1_t_illumi_mask << 10U);
#if 0   /* BEV Rebase provisionally */
    u4_ap_pdu_tx[2]  = (U4)u2_g_IoHwAdcLv((U1)ADC_CH_TFT_TH);       /* TFT_BL_TH_AD */
#endif   /* BEV Rebase provisionally */
    u4_ap_pdu_tx[2]  = ((U4)u1_g_IllumiTftPct() << 16U);
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxClock(U4 * u4_ap_pdu_tx)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxClock(         U4 * u4_ap_pdu_tx) {
#if 0   /* BEV Rebase provisionally */

    U4  u4_t_disp_tim_now;
    U1  u1_t_read_sts;

    u4_t_disp_tim_now = (U4)0U;  
    u1_t_read_sts     = u1_g_iVDshReabyDid((U2)IVDSH_DID_REA_CPREQ_013, &u4_t_disp_tim_now, (U2)XSPI_VM_1WORD);

    if(u1_t_read_sts == (U1)IVDSH_NO_REA){
        u4_t_disp_tim_now = (U4)XSPI_CLOCK_UNKNOWN;
    }
    u4_ap_pdu_tx[0] = u4_t_disp_tim_now;
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxOdo(U4 * u4_ap_pdu_tx)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxOdo(           U4 * u4_ap_pdu_tx) {
    U4  u4_t_odo_dat;
    U1  u1_t_odo_sts;
    U4  u4_t_tripa_dat;
    U1  u1_t_tripa_sts;
    U4  u4_t_tripb_dat;
    U1  u1_t_tripb_sts;
    U4  u4_t_odo_km_dat;                                               /* ODO_KM                                       */
    U1  u1_t_tmnt_reset_sts;


    u4_t_odo_dat       = (U4)0U;
    u1_t_odo_sts = u1_g_OdoKmMileByUnit(&u4_t_odo_dat);
    u4_t_tripa_dat     = (U4)0U;
    u1_t_tripa_sts = u1_g_OdoTripKmMileByUnit((U1)ODO_TRIP_CH_A, &u4_t_tripa_dat);
    u4_t_tripb_dat     = (U4)0U;
    u1_t_tripb_sts = u1_g_OdoTripKmMileByUnit((U1)ODO_TRIP_CH_B, &u4_t_tripb_dat);
    u4_t_odo_km_dat    = (U4)0U;
    (void)u1_g_OdoKm(&u4_t_odo_km_dat);

    /* TMNT */
    u1_t_tmnt_reset_sts = u1_g_OdoCfgGetOmRstSts();

    u4_ap_pdu_tx[0]   = u1_t_tmnt_reset_sts;                           /* TMNT_RESET                                   */
    u4_ap_pdu_tx[0]  |= ((U4)u1_t_odo_sts   << XSPI_STS_SHIFT);    /* ODO_STS                                      */
    u4_ap_pdu_tx[1]   = u4_t_odo_dat;                                  /* ODO                                          */
    u4_ap_pdu_tx[2]   = ((U4)u1_t_tripa_sts << XSPI_STS_SHIFT);    /* TRIPA_STS                                    */
    u4_ap_pdu_tx[3]   = u4_t_tripa_dat;                                /* TRIP_A                                       */
    u4_ap_pdu_tx[4]   = ((U4)u1_t_tripb_sts << XSPI_STS_SHIFT);    /* TRIPB_STS                                    */
    u4_ap_pdu_tx[5]   = u4_t_tripb_dat;                                /* TRIP_B                                       */
    u4_ap_pdu_tx[6]   = u4_t_odo_km_dat;                               /* ODO_KM                                       */

}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxTripcom(U4 * u4_ap_pdu_tx)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxTripcom(       U4 * u4_ap_pdu_tx) {
    U1              u1_t_sts;
    U4              u4_t_data;
    U2              u2_t_data;
    U1              u1_t_data;
    U1              u1_t_acsts;

    u2_t_data        = (U2)0U;
    u1_t_sts         = u1_g_AvgVehspdKmph((U1)AVGVEHSPD_CNTT_TA , &u2_t_data);
    u4_ap_pdu_tx[ 4] = ((U4)u1_t_sts << XSPI_STS_SHIFT);                        /* AVG_SPD_KMPH_USRRST_STS              */
    u4_ap_pdu_tx[ 5] = (U4)u2_t_data;                                               /* AVG_SPD_KMPH_USRRST                  */

    u2_t_data        = (U2)0U;
    u1_t_sts         = u1_g_AvgVehspdKmph((U1)AVGVEHSPD_CNTT_DC , &u2_t_data);
    u4_ap_pdu_tx[ 6] = ((U4)u1_t_sts << XSPI_STS_SHIFT);                        /* AVG_SPD_KMPH_AFTSTRT_STS             */
    u4_ap_pdu_tx[ 7] = (U4)u2_t_data;                                               /* AVG_SPD_KMPH_AFTSTRT                 */

    u4_t_data         = (U4)0U;
    u1_t_sts          = u1_g_TripcomEvDteKmIgOffAcOff(&u4_t_data);
    u4_ap_pdu_tx[12] |= ((U4)u1_t_sts << (XSPI_EV_KM_ACOFF_STS_SHIFT));         /* DISTTOEMPTY_EV_KM_ACOFF_STS          */
    u4_ap_pdu_tx[14]  = u4_t_data;                                                  /* DISTTOEMPTY_EV_KM_ACOFF              */

    u4_t_data         = (U4)0U;
    u1_t_sts          = u1_g_TripcomEvDteKmIgOffAcOn(&u4_t_data);
    u4_ap_pdu_tx[12] |= ((U4)u1_t_sts << (XSPI_EV_KM_ACON_STS_SHIFT));          /* DISTTOEMPTY_EV_KM_ACON_STS           */
    u4_ap_pdu_tx[15]  = u4_t_data;                                                  /* DISTTOEMPTY_EV_KM_ACON               */

    u4_t_data        = (U4)0U;
    u1_t_sts         = u1_g_PtsRunDistKm((U1)PTSRUNDIST_CNTT_TR_A, &u4_t_data);
    u4_ap_pdu_tx[16] = ((U4)u1_t_sts << XSPI_STS_SHIFT);                        /* TRIPA_DIST_KM_USRRST_STS             */
    u4_ap_pdu_tx[17] = u4_t_data;                                                   /* TRIPA_DIST_KM_USRRST                 */

    u4_t_data        = (U4)0U;
    u1_t_sts         = u1_g_PtsRunDistKm((U1)PTSRUNDIST_CNTT_TR_B, &u4_t_data);
    u4_ap_pdu_tx[18] = ((U4)u1_t_sts << XSPI_STS_SHIFT);                        /* TRIPB_DIST_KM_USRRST_STS             */
    u4_ap_pdu_tx[19] = u4_t_data;                                                   /* TRIPB_DIST_KM_USRRST                 */

    u4_t_data        = (U4)0U;
    u1_t_sts         = u1_g_PtsRunDistKm((U1)PTSRUNDIST_CNTT_LC, &u4_t_data);
    u4_ap_pdu_tx[20] = ((U4)u1_t_sts << XSPI_STS_SHIFT);                        /* DIST_KM_USRRST_STS                   */
    u4_ap_pdu_tx[21] = u4_t_data;                                                   /* DIST_KM_USRRST                       */

    u4_t_data        = (U4)0U;
    u1_t_sts         = u1_g_PtsRunDistKm((U1)PTSRUNDIST_CNTT_DC, &u4_t_data);
    u4_ap_pdu_tx[22] = ((U4)u1_t_sts << XSPI_STS_SHIFT);                        /* DIST_KM_AFTSTRT_STS                  */
    u4_ap_pdu_tx[23] = u4_t_data;                                                   /* DIST_KM_AFTSTRT                      */

    u4_t_data        = (U4)0U;
    u1_t_sts         = u1_g_PtsRunTmHrs((U1)PTSRUNTM_CNTT_LC , &u4_t_data);
    u4_ap_pdu_tx[24] = ((U4)u1_t_sts << XSPI_STS_SHIFT);                        /* DRVTIME_USRRST_STS                   */
    u4_ap_pdu_tx[25] = u4_t_data;                                                   /* DRVTIME_HHHH_USRRST                  */
                                                                                    /* DRVTIME_MM_USRRST                    */
                                                                                    /* DRVTIME_SS_USRRST                    */

    u4_t_data        = (U4)0U;
    u1_t_sts         = u1_g_PtsRunTmHrs((U1)PTSRUNTM_CNTT_DC , &u4_t_data);
    u4_ap_pdu_tx[26] = ((U4)u1_t_sts << XSPI_STS_SHIFT);                        /* DRVTIME_AFTSTRT_STS                  */
    u4_ap_pdu_tx[27] = u4_t_data;                                                   /* DRVTIME_HHHH_AFTSTRT                 */
                                                                                    /* DRVTIME_MM_AFTSTRT                   */
                                                                                    /* DRVTIME_SS_AFTSTRT                   */

    u2_t_data        = (U2)0U;
    u1_t_sts         = u1_g_AvgVehspdKmph((U1)AVGVEHSPD_CNTT_TR_A , &u2_t_data);
    u4_ap_pdu_tx[28] = ((U4)u1_t_sts << XSPI_STS_SHIFT);                        /* TRIPA_AVG_SPD_KMPH_USRRST_STS        */
    u4_ap_pdu_tx[29] = (U4)u2_t_data;                                               /* TRIPA_AVG_SPD_KMPH_USRRST            */

    u4_t_data        = (U4)0U;
    u1_t_sts         = u1_g_PtsRunTmHrs((U1)PTSRUNTM_CNTT_TR_A , &u4_t_data);
    u4_ap_pdu_tx[30] = ((U4)u1_t_sts << XSPI_STS_SHIFT);                        /* TRIPA_DRVTIME_USRRST_STS             */
    u4_ap_pdu_tx[31] = u4_t_data;                                                   /* TRIPA_DRVTIME_HHHH_USRRST            */
                                                                                    /* TRIPA_DRVTIME_MM_USRRST              */
                                                                                    /* TRIPA_DRVTIME_SS_USRRST              */

    u2_t_data        = (U2)0U;
    u1_t_sts         = u1_g_AvgVehspdKmph((U1)AVGVEHSPD_CNTT_TR_B , &u2_t_data);
    u4_ap_pdu_tx[32] = ((U4)u1_t_sts << XSPI_STS_SHIFT);                        /* TRIPB_AVG_SPD_KMPH_USRRST_STS        */
    u4_ap_pdu_tx[33] = (U4)u2_t_data;                                               /* TRIPB_AVG_SPD_KMPH_USRRST            */

    u4_t_data        = (U4)0U;
    u1_t_sts         = u1_g_PtsRunTmHrs((U1)PTSRUNTM_CNTT_TR_B , &u4_t_data);
    u4_ap_pdu_tx[34] = ((U4)u1_t_sts << XSPI_STS_SHIFT);                        /* TRIPB_DRVTIME_USRRST_STS             */
    u4_ap_pdu_tx[35] = u4_t_data;                                                   /* TRIPB_DRVTIME_HHHH_USRRST            */
                                                                                    /* TRIPB_DRVTIME_MM_USRRST              */
                                                                                    /* TRIPB_DRVTIME_SS_USRRST              */

    u1_t_data         = (U1)0U;
    u1_t_sts          = u1_g_EvDtePct(&u1_t_data);
    u4_ap_pdu_tx[37]  = (U4)u1_t_sts;                                               /* DISTTOEMPTY_PHV_ENG_STS             */
    u4_ap_pdu_tx[37] |= ((U4)u1_t_data << 2);                                       /* DISTTOEMPTY_PHV_ENG                 */

    u4_t_data        = (U4)0U;
    u1_t_sts         = u1_g_InstEeKmpkwh(&u4_t_data);
    u4_ap_pdu_tx[40] = ((U4)u1_t_sts << XSPI_STS_SHIFT);                        /* INST_EE_KMPKWH_STS                   */
    u4_ap_pdu_tx[41] = u4_t_data;                                                   /* INST_EE_KMPKWH                       */

    u4_t_data        = (U4)0U;
    u1_t_sts         = u1_g_AvgEeKmpkwh((U1)AVGEE_CNTT_TA, &u4_t_data);
    u4_ap_pdu_tx[42] = ((U4)u1_t_sts << XSPI_STS_SHIFT);                        /* AVG_EE_KMPL_USRRST_STS               */
    u4_ap_pdu_tx[43] = u4_t_data;                                                   /* AVG_EE_KMPL_USRRST                   */

    u4_t_data        = (U4)0U;
    u1_t_sts         = u1_g_AvgEeKmpkwh((U1)AVGEE_CNTT_DC, &u4_t_data);
    u4_ap_pdu_tx[44] = ((U4)u1_t_sts << XSPI_STS_SHIFT);                        /* AVG_EE_KMPL_AFTSTRT_STS              */
    u4_ap_pdu_tx[45] = u4_t_data;                                                   /* AVG_EE_KMPL_AFTSTRT                  */

    u4_t_data         = (U4)0U;
    u2_t_data         = (U2)0U;
    u1_t_acsts        = (U1)0U;
    u1_t_sts          = u1_g_EvDteKm(&u4_t_data, &u1_t_acsts);
    u2_t_data         = u2_g_EvDteKmDiff();
    u4_ap_pdu_tx[46]  = ((U4)u1_t_sts << (XSPI_STS_SHIFT - 1U));                /* DISTTOEMPTY_EV_KM_STS                */
    u4_ap_pdu_tx[46] |= u2_t_data;                                                  /* DISTEMPTY_EV_KM_DIFF                 */
    u4_ap_pdu_tx[47]  = u4_t_data;                                                  /* DISTTOEMPTY_EV_KM                    */
    u4_ap_pdu_tx[37] |= ((U4)u1_t_acsts << 9);                                      /* DISTTOEMPTY_EV_AC_STS                */

}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxTelltale(U4 * u4_ap_pdu_tx)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxTelltale(      U4 * u4_ap_pdu_tx) {
    vd_g_HmiTt(&u4_ap_pdu_tx[0] , (U1)HMITT_NUM);
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxRcmmui(U4 * u4_ap_pdu_tx)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxRcmmui(        U4 * u4_ap_pdu_tx) {
    u4_ap_pdu_tx[0] = (U4)u1_g_RcmmUISelect();
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxMaint(U4 * u4_ap_pdu_tx)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxMaint(         U4 * u4_ap_pdu_tx) {
#if 0   /* BEV Rebase provisionally */
    S4 s4_t_m_dist;

    s4_t_m_dist     = (S4)s2_g_OilmilGetVal() + (S4)XSPI_MAINTEDIST_OFFSET;
    u4_ap_pdu_tx[0]  = (U4)s4_t_m_dist;
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxHud(U4 * u4_ap_pdu_tx)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxHud(           U4 * u4_ap_pdu_tx) {
    U1 u1_t_owdutyreq;
    U2 u2_t_owduty;

    u2_t_owduty = (U2)0U;
    u1_t_owdutyreq = u1_g_HdimmgrIfGetOwduty(&u2_t_owduty);

    u4_ap_pdu_tx[0]  = (U4)u2_t_owduty;                                                     /* HUD_BLDUTY_OW        */
    u4_ap_pdu_tx[0] |= (U4)u2_g_HudImgAdjGetGvOwPos() << 16;                                /* HUD_VIPOS_POS_OW     */
    u4_ap_pdu_tx[1]  = (U4)u2_g_HudImgAdjGetMovReqPos();                                    /* HUD_VIPOS_REQPOS     */
    u4_ap_pdu_tx[1] |= (U4)u2_g_HdimmgrIfGetAdjduty() << 16;                                /* HUD_DIM_ILLMN        */
    u4_ap_pdu_tx[2]  = (U4)u1_g_HudImgAdjGetMovReqID();                                     /* HUD_VIPOS_REQID      */
    u4_ap_pdu_tx[2] |= (U4)((U4)u1_g_HdimmgrIfGet_L_HUDBR_S() & (U4)0x0000001FU) << 8;      /* HUD_L_HUDBR_S        */
    u4_ap_pdu_tx[2] |= (U4)((U4)u1_t_owdutyreq & (U4)0x00000001U) << 13;                    /* HUD_BLDUTY_OWREQ     */
    u4_ap_pdu_tx[2] |= (U4)((U4)u1_s_xspi_vipos_disp & (U4)0x00000001U) << 14;              /* GV_VIPOS_DISP        */
    u4_ap_pdu_tx[2] |= (U4)((U4)u1_g_HudImgAdjGetGvOwReq() & (U4)0x00000001U) << 15;        /* HUD_VIPOS_POS_OWREQ  */
    u4_ap_pdu_tx[2] |= (U4)((U4)u1_g_HudImgAdjGetGvRtctlIniReq() & (U4)0x00000001U) << 16;  /* HUD_VIPOS_INIT_OWREQ */
    u4_ap_pdu_tx[2] |= (U4)((U4)u1_g_HudImgAdjIsUpSwOn() & (U4)0x00000001U) << 17;          /* HUD_VIPOS_UPSW       */
    u4_ap_pdu_tx[2] |= (U4)((U4)u1_g_HudImgAdjIsDnSwOn() & (U4)0x01U) << 18;                /* HUD_VIPOS_DNSW       */
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxWrnmsg(U4 * u4_ap_pdu_tx)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxWrnmsg(        U4 * u4_ap_pdu_tx) {
    vd_g_HmiPuTxt(&u4_ap_pdu_tx[0] , (U1)HMIPUTXT_NUM);
}
/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxMulmed(U4 * u4_ap_pdu_tx)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxMulmed(        U4 * u4_ap_pdu_tx) {
    U1              u1_t_bzlvl;
    U1              u1_t_bzlength;
    U1              u1_t_bzemg;
#if 0   /* BEV Rebase provisionally */
    U4              u4_t_loop;
    U4              u4_tp_usrname[XSPI_USRNAME_SIZE];
#endif   /* BEV Rebase provisionally */

    vd_g_wChimeMetBuzzInfo(&u1_t_bzlvl, &u1_t_bzlength, &u1_t_bzemg);
    u4_ap_pdu_tx[0]  = (U4)((U4)u1_t_bzlvl    & (U4)0x0000000FU)  << 1;
    u4_ap_pdu_tx[0] |= (U4)((U4)u1_t_bzlength & (U4)0x00000001U)  << 0;
    u4_ap_pdu_tx[0] |= (U4)((U4)u1_t_bzemg    & (U4)0x00000001U)  << 5;

#if 0   /* BEV Rebase provisionally */
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)XSPI_USRNAME_SIZE; u4_t_loop++) {
        u4_tp_usrname[u4_t_loop]  = (U4)0U;
    }

    (void)u1_g_McstReadUsrName(&u4_tp_usrname[0], (U1)XSPI_USRNAME_SIZE, (U1)0xFFU); /* Get current user name */

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)XSPI_USRNAME_SIZE; u4_t_loop++) {
        u4_ap_pdu_tx[5U + u4_t_loop]  = u4_tp_usrname[u4_t_loop];
    }
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxMetcstm(U4 * u4_ap_pdu_tx)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxMetcstmMcst(    U4 * u4_ap_pdu_tx) {
}
/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxNickname(U4 * u4_ap_pdu_tx)                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxNickname(    U4 * u4_ap_pdu_tx) {
#if 0   /* BEV Rebase provisionally */
    static const U1 u1_s_XSPI_NICKNAME_PAYLOAD_SIZE = (U1)5U;                                  /* PAYLOAD SIZE per User          */
    static const U1 u1_sp_XSPI_USERID[XSPI_NICKNAME_USERNUM] = {
        (U1)MCST_USR_USER1,
        (U1)MCST_USR_USER2,
        (U1)MCST_USR_USER3
    };

    U1              u1_t_user_offset;
    U1              u1_t_loop_user;
    U1              u1_t_loop_txt;
    U2              u2_tp_nicknametxt[XSPI_NICKNAME_TXTNUM];

    for(u1_t_loop_user = (U1)0U; u1_t_loop_user < (U1)XSPI_NICKNAME_USERNUM; u1_t_loop_user++){
        for(u1_t_loop_txt = (U1)0U; u1_t_loop_txt < (U1)XSPI_NICKNAME_TXTNUM; u1_t_loop_txt++){
            u2_tp_nicknametxt[u1_t_loop_txt] = (U2)0U;
        }
        (void)u1_g_McstReadNickName(&u2_tp_nicknametxt[0], u1_sp_XSPI_USERID[u1_t_loop_user]);
        u1_t_user_offset = u1_s_XSPI_NICKNAME_PAYLOAD_SIZE * u1_t_loop_user;
        for(u1_t_loop_txt = (U1)0U; u1_t_loop_txt < u1_s_XSPI_NICKNAME_PAYLOAD_SIZE; u1_t_loop_txt++){
            u4_ap_pdu_tx[u1_t_loop_txt + u1_t_user_offset]  =  (U4)u2_tp_nicknametxt[u1_t_loop_txt * 2U];
            u4_ap_pdu_tx[u1_t_loop_txt + u1_t_user_offset] |= ((U4)u2_tp_nicknametxt[(u1_t_loop_txt * 2U) + 1U] << XSPI_SHIFT_2BYTE);
        }
    }
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxAttmp(U4 * u4_ap_pdu_tx)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxAttmp(   U4 * u4_ap_pdu_tx)
{
#if 0   /* BEV Rebase provisionally */
    static const U4 u4_s_XSPI_ATTEMP_INVALID_16BIT = (U4)0x0000FFFFU;

    U2          u2_t_attmp;
    U1          u1_t_attmpsts;
    U1          u1_t_attmpoverheat;
    U4          u4_t_attmpputdate_cel;

    u2_t_attmp      = (U2)0U;
    u1_t_attmpsts = u1_g_AttmpCelFltrd(&u2_t_attmp);
    u1_t_attmpoverheat = u1_g_GagdstATTempOvhtIndSts();

    if(u1_t_attmpsts == (U1)ATTMP_STSBIT_VALID){
        u4_t_attmpputdate_cel = (U4)u2_t_attmp;                                 /*  LSB :0.01     offset :  -273.15[cel]             */
    }
    else{
        u4_t_attmpputdate_cel = u4_s_XSPI_ATTEMP_INVALID_16BIT;
    }

    u4_ap_pdu_tx[0]  = ((U4)u1_t_attmpoverheat & (U4)XSPI_MSK_01BIT) << 31;
    u4_ap_pdu_tx[1]  = (u4_t_attmpputdate_cel & (U4)XSPI_MSK_16BIT);
#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxCalib(U4 * u4_ap_pdu_tx)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxCalib(         U4 * u4_ap_pdu_tx)
{
#if 0   /* BEV Rebase provisionally */
    static const U4 u4_s_XSPI_NUM_PAYLOAD = (U4)41U;

    static const ST_XSPI_CALIB st_sp_XSPI_CALIB[XSPI_MCUID_NUM] = {
        /* u2_xspiid ,     u1_bitpos ,                 u1_size ,                vdp_mcuid                           */
           {(U2) 0U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0023_DISPTYPE,       },
           {(U2) 0U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0026_1MOTHV,         },
           {(U2) 1U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0217_STR_ANG,        },
           {(U2) 1U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0218_ACCELERATOR,    },
           {(U2) 1U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0219_G_GAUGE_MAX,    },
           {(U2) 1U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0220_GTRAJECTORY2,   },
           {(U2) 2U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0221_G_DISP_MAX,     },
           {(U2) 2U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0235_BODYSHAPE,      },
           {(U2) 3U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0236_NOOPTTM,        },
           {(U2) 3U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0238_XVMODE,         },
           {(U2) 3U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U2,    &u2_CALIB_MCUID0262_MAXSPEED_KM,    },
           {(U2) 4U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U2,    &u2_CALIB_MCUID0263_MAXSPEED_MPH,   },
           {(U2) 4U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0264_FSPO,           },
           {(U2) 4U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0265_REVIND,         },
           {(U2) 5U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0268_SWNUM,          },
           {(U2) 5U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0269_SWPOSI,         },
           {(U2) 5U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0572_FU_PORTPOS,     },
           {(U2) 5U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0576_DEGCW,          },
           {(U2) 6U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0577_DEGCCW,         },
           {(U2) 6U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0579_RESTIME,        },
           {(U2) 6U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0590_SOC_PORTPOS,    },
           {(U2) 7U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0591_UREA,           },
           {(U2) 7U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0592_SBELT_TT,       },
           {(U2) 7U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0602_LAUNCHTIME,     },
           {(U2) 7U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0659_MTSNORM,        },
           {(U2) 8U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0660_XMODE,          },
           {(U2) 8U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0661_GFX_DISSWING,   },
           {(U2) 8U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0662_0DIAL_VIEW,     },
           {(U2) 8U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0663_1DIAL_VIEW,     },
           {(U2) 9U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0664_2DIAL_VIEW,     },
           {(U2) 9U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0665_MAP_VIEW,       },
           {(U2) 9U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0666_ADAS_VIEW,      },
           {(U2) 9U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0667_ECO_VIEW,       },
           {(U2)10U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0668_1DIAL_TR_VIEW,  },
           {(U2)10U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0669_SHTUPIND_VIEW,  },
           {(U2)10U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0670_OFFROAD_VIEW,   },
           {(U2)10U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0671_6DIAL_VIEW,     },
           {(U2)11U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0672_FC_DEF,         },
           {(U2)11U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0673_PWR_DEF,        },
           {(U2)11U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0674_PHEV_FC_DEF,    },
           {(U2)11U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0675_ECOIND_DEF,     },
           {(U2)12U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0676_ECOSCR_DEF,     },
           {(U2)12U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0677_EVRATIO,        },
           {(U2)12U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0678_NAVI_DEF,       },
           {(U2)12U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0679_AUDIO_DEF,      },
           {(U2)13U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0680_DRVINFO_DEF,    },
           {(U2)13U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0681_TRIPA_DEF,      },
           {(U2)13U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0682_TRIPB_DEF,      },
           {(U2)13U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0683_EGMNTR_DEF,     },
           {(U2)14U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0684_TPMS_DEF,       },
           {(U2)14U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0685_4WD_DEF,        },
           {(U2)14U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0686_TRC_DEF,        },
           {(U2)14U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0687_STR_DEF,        },
           {(U2)15U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0688_PTCHROLL_DEF,   },
           {(U2)15U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0689_TRABRK_DEF,     },
           {(U2)15U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0690_TRABSM_DEF,     },
           {(U2)15U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0691_VOLTMET_DEF,    },
           {(U2)16U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0692_OILPRS_DEF,     },
           {(U2)16U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0693_EATOILTMP_DEF,  },
           {(U2)16U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0694_EOILTMP_DEF,    },
           {(U2)16U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0695_ATOILTMP_DEF,   },
           {(U2)17U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0696_TRBOGAG_W_L,    },
           {(U2)17U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0697_TRBOGAG_WO_L,   },
           {(U2)17U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0698_BOSTGAG_W_L,    },
           {(U2)17U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0699_BOSTGAG_WO_L,   },
           {(U2)18U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0700_MTRPWR,         },
           {(U2)18U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0701_SPRTSGAG,       },
           {(U2)18U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0702_GFORCE,         },
           {(U2)18U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0703_ADBLUE,         },
           {(U2)19U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0704_ENGCNSMP,       },
           {(U2)19U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0705_MET_CD_TACHO,   },
           {(U2)19U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0706_MET_CD_SPEED,   },
           {(U2)19U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0707_MET_CD_HVIND,   },
           {(U2)20U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0708_MET_CD_FCIND,   },
           {(U2)20U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0709_MET_CD_PWR,     },
           {(U2)20U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0754_MET_CD_DRVMD,   },
           {(U2)20U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0710_MET_LD_TACHO,   },
           {(U2)21U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0711_MET_LD_HVIND,   },
           {(U2)21U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0712_MET_LD_FCIND,   },
           {(U2)21U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0713_MET_LD_PWR,     },
           {(U2)21U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0755_MET_LD_DRVMD,   },
           {(U2)22U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0715_HUD_TACHO,      },
           {(U2)22U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0716_HUD_ECOIND,     },
           {(U2)22U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0717_HUD_HVIND,      },
           {(U2)22U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0718_HUD_FCIND,      },
           {(U2)23U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0719_HUD_PWR,        },
           {(U2)23U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0756_HUD_DRVMD,      },
           {(U2)23U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0720_PARK_S,         },
           {(U2)23U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0721_PARK,           },
           {(U2)24U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0722_LUD,            },
           {(U2)24U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0723_DIST_AFTSTRT,   },
           {(U2)24U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0726_DRVTM_AFTSTRT,  },
           {(U2)24U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0729_AVGFE_AFTSTRT,  },
           {(U2)25U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0732_EVRATIO,        },
           {(U2)25U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0735_AVGEE_AFTSTRT,  },
           {(U2)25U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U2,    &u2_CALIB_MCUID0738_TIMEOUT_TM,     },
           {(U2)26U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0740_OILLVL_DEF,     },
           {(U2)26U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0267_REVLSB,         },
           {(U2)26U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0593_ATTEMP_LO,      },
           {(U2)27U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0594_ATTEMP_MIDL,    },
           {(U2)27U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0595_ATTEMP_MIDH,    },
           {(U2)27U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0596_ATTEMP_HI,      },
           {(U2)28U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0430_RHEOSW,         },
           {(U2)28U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0599_RZSTART,        },
           {(U2)28U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0600_ATTEMPVAL_LO,   },
           {(U2)28U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0601_ATTEMPVAL_HI,   },
           {(U2)29U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U2,    &u2_CALIB_MCUID0608_OLPTLP,         },
           {(U2)29U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U2,    &u2_CALIB_MCUID0622_OLTTLP,         },
           {(U2)30U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U2,    &u2_CALIB_MCUID0630_TTLP,           },
           {(U2)30U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0631_TTLC,           },
           {(U2)30U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0632_TTLH,           },
           {(U2)31U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U2,    &u2_CALIB_MCUID0633_TTLMAXC,        },
           {(U2)31U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U2,    &u2_CALIB_MCUID0634_TTLMINC,        },
           {(U2)32U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U2,    &u2_CALIB_MCUID0635_TTLMAXF,        },
           {(U2)32U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U2,    &u2_CALIB_MCUID0636_TTLMINF,        },
           {(U2)33U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0637_OVHT,           },
           {(U2)33U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0638_HYS,            },
           {(U2)33U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0647_METHVSYSIND,    },
           {(U2)33U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0648_HUDHVSYSIND,    },
           {(U2)34U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0649_METNORM,        },
           {(U2)34U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0650_HUDNORM,        },
           {(U2)34U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0651_HUDNORM1,       },
           {(U2)35U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U2,    &u2_CALIB_MCUID0609_KPAOLPL,        },
           {(U2)35U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U2,    &u2_CALIB_MCUID0610_KPAOLPH,        },
           {(U2)36U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U2,    &u2_CALIB_MCUID0611_BAROLPL,        },
           {(U2)36U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U2,    &u2_CALIB_MCUID0612_BAROLPH,        },
           {(U2)37U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U2,    &u2_CALIB_MCUID0613_PSIOLPL,        },
           {(U2)37U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U2,    &u2_CALIB_MCUID0614_PSIOLPH,        },
           {(U2)38U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0623_OLTTLC,         },
           {(U2)38U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0624_OLTTLH,         },
           {(U2)38U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0209_RRCYM,          },
           {(U2)38U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0210_RLCYM,          },
           {(U2)39U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0211_BCTYM,          },
           {(U2)39U,       (U1)XSPI_SHIFT_1BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0212_LGCYM,          },
           {(U2)39U,       (U1)XSPI_SHIFT_2BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0213_HDCY_BDBM,      },
           {(U2)39U,       (U1)XSPI_SHIFT_3BYTE,   (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0214_RPSDWARNM,      },
           {(U2)40U,       (U1)XSPI_SHIFT_NON,     (U1)XSPI_SIZE_U1,    &u1_CALIB_MCUID0215_LPSDWARNM,      }
    };

    static const ST_XSPI_CALIB_CHK st_sp_XSPI_CALIB_MINMAXCHK[XSPI_MCUID_MINMAXCHK_NUM] = {
        /* u2_xspiid ,     u1_bitpos ,                 u1p_mcuid ,                         u4_min ,                            u4_max ,                            u4_def                            */
           {(U2) 0U,       (U1)XSPI_SHIFT_1BYTE,   &u1_CALIB_MCUID0024_BRAND,          (U4)CALIB_MCUID0024_TOYOTA,         (U4)(CALIB_MCUID0024_NUM - 1U),     (U4)CALIB_MCUID0024_DEF            },
           {(U2) 0U,       (U1)XSPI_SHIFT_2BYTE,   &u1_CALIB_MCUID0025_SPORTS,         (U4)CALIB_MCUID0025_NON,            (U4)(CALIB_MCUID0025_NUM - 1U),     (U4)CALIB_MCUID0025_DEF            },
           {(U2) 2U,       (U1)XSPI_SHIFT_1BYTE,   &u1_CALIB_MCUID0233_RDOOR,          (U4)CALIB_MCUID0233_MIN,            (U4)CALIB_MCUID0233_MAX,            (U4)CALIB_MCUID0233_DEF            },
           {(U2) 2U,       (U1)XSPI_SHIFT_2BYTE,   &u1_CALIB_MCUID0234_WALKTHROUGH,    (U4)CALIB_MCUID0234_MIN,            (U4)CALIB_MCUID0234_MAX,            (U4)CALIB_MCUID0234_DEF            },
           {(U2) 6U,       (U1)XSPI_SHIFT_1BYTE,   &u1_CALIB_MCUID0578_DEG_RTSTEP,     (U4)CALIB_MCUID0578_MIN,            (U4)CALIB_MCUID0578_MAX,            (U4)CALIB_MCUID0578_DEF            }
    };

    U4  u4_t_loop;
    U4  u4_t_calib_val;

    for (u4_t_loop = (U4)0U; u4_t_loop < u4_s_XSPI_NUM_PAYLOAD; u4_t_loop++) {
        u4_ap_pdu_tx[u4_t_loop] = (U4)0U;
    }

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)XSPI_MCUID_NUM; u4_t_loop++) {

        if (st_sp_XSPI_CALIB[u4_t_loop].vdp_mcuid != vdp_PTR_NA) {
            if (st_sp_XSPI_CALIB[u4_t_loop].u1_size == (U1)XSPI_SIZE_U1) {
                u4_t_calib_val = (U4) *((const volatile U1*)st_sp_XSPI_CALIB[u4_t_loop].vdp_mcuid);

                u4_ap_pdu_tx[st_sp_XSPI_CALIB[u4_t_loop].u2_xspiid] |=
                    ((u4_t_calib_val & (U4)XSPI_MSK_08BIT)
                    << st_sp_XSPI_CALIB[u4_t_loop].u1_bitpos);
            }
            else if (st_sp_XSPI_CALIB[u4_t_loop].u1_size == (U1)XSPI_SIZE_U2) {
                u4_t_calib_val = (U4) *((const volatile U2*)st_sp_XSPI_CALIB[u4_t_loop].vdp_mcuid);

                u4_ap_pdu_tx[st_sp_XSPI_CALIB[u4_t_loop].u2_xspiid] |=
                    ((u4_t_calib_val & (U4)XSPI_MSK_16BIT)
                    << st_sp_XSPI_CALIB[u4_t_loop].u1_bitpos);
            }
            else {
                /* Do Nothing */
            }
        }
    }
    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)XSPI_MCUID_MINMAXCHK_NUM; u4_t_loop++) {

        if (st_sp_XSPI_CALIB_MINMAXCHK[u4_t_loop].u1p_mcuid != vdp_PTR_NA) {
            u4_t_calib_val = (U4) *(st_sp_XSPI_CALIB_MINMAXCHK[u4_t_loop].u1p_mcuid);
                
            if ((u4_t_calib_val < st_sp_XSPI_CALIB_MINMAXCHK[u4_t_loop].u4_min) ||
                (u4_t_calib_val > st_sp_XSPI_CALIB_MINMAXCHK[u4_t_loop].u4_max)) {
                u4_t_calib_val = st_sp_XSPI_CALIB_MINMAXCHK[u4_t_loop].u4_def;
            }
            
                u4_ap_pdu_tx[st_sp_XSPI_CALIB_MINMAXCHK[u4_t_loop].u2_xspiid] |=
                    ((u4_t_calib_val & (U4)XSPI_MSK_08BIT)
                    << st_sp_XSPI_CALIB_MINMAXCHK[u4_t_loop].u1_bitpos);
        }
    }

#endif   /* BEV Rebase provisionally */
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgTxAvgGrph(U4 * u4_ap_pdu_tx)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgTxAvgGrph(         U4 * u4_ap_pdu_tx)
{
    U4          u4_t_1mfedata[AVGGRPH_SIZE_1M];
    U4          u4_t_1meedata[AVGGRPH_SIZE_1M];
    U4          u4_t_tafedata[AVGGRPH_SIZE_TA];
    U4          u4_t_taeedata[AVGGRPH_SIZE_TA];
    U1          u1_t_femonth[AVGGRPH_SIZE_TA];
    U1          u1_t_feday[AVGGRPH_SIZE_TA];
    U4          u4_t_femax;
    U1          u1_t_eemonth[AVGGRPH_SIZE_TA];
    U1          u1_t_eeday[AVGGRPH_SIZE_TA];
    U4          u4_t_eemax;
    U4 *        u4_tp_txdata;
    U4          u4_t_loop;
    U1          u1_t_1mferslt;
    U1          u1_t_1meerslt;
    U1          u1_t_taferslt;
    U1          u1_t_taeerslt;

    u4_tp_txdata = &u4_ap_pdu_tx[0];

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)AVGGRPH_SIZE_1M; u4_t_loop++) {
        u4_t_1mfedata[u4_t_loop] = (U4)0U;
        u4_t_1meedata[u4_t_loop] = (U4)0U;
    }

    for (u4_t_loop = (U4)0U; u4_t_loop < (U4)AVGGRPH_SIZE_TA; u4_t_loop++) {
        u4_t_tafedata[u4_t_loop] = (U4)0U;
        u4_t_taeedata[u4_t_loop] = (U4)0U;
        u1_t_femonth[u4_t_loop] = (U1)0U;
        u1_t_feday[u4_t_loop] = (U1)0U;
        u1_t_eemonth[u4_t_loop] = (U1)0U;
        u1_t_eeday[u4_t_loop] = (U1)0U;
    }

    (void)u4_g_AvgGrphData((U1)AVGGRPH_CNTT_1MFE, &u4_t_1mfedata[0], vdp_PTR_NA, vdp_PTR_NA);
    (void)u4_g_AvgGrphData((U1)AVGGRPH_CNTT_1MEE, &u4_t_1meedata[0], vdp_PTR_NA, vdp_PTR_NA);
    u4_t_femax = u4_g_AvgGrphData((U1)AVGGRPH_CNTT_TAFE, &u4_t_tafedata[0], &u1_t_femonth[0], &u1_t_feday[0]);
    u4_t_eemax = u4_g_AvgGrphData((U1)AVGGRPH_CNTT_TAEE, &u4_t_taeedata[0], &u1_t_eemonth[0], &u1_t_eeday[0]);

    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)AVGGRPH_SIZE_1M; u4_t_loop++) {
        *u4_tp_txdata = u4_t_1mfedata[u4_t_loop];
        u4_tp_txdata++;
    }
    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)AVGGRPH_SIZE_1M; u4_t_loop++) {
        *u4_tp_txdata = u4_t_1meedata[u4_t_loop];
        u4_tp_txdata++;
    }
    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)AVGGRPH_SIZE_TA; u4_t_loop++) {
        *u4_tp_txdata = u4_t_tafedata[u4_t_loop];
        u4_tp_txdata++;
    }
    for(u4_t_loop = (U4)0U; u4_t_loop < (U4)AVGGRPH_SIZE_TA; u4_t_loop++) {
        *u4_tp_txdata = u4_t_taeedata[u4_t_loop];
        u4_tp_txdata++;
    }

    u4_ap_pdu_tx[72] = u4_t_femax;
    u4_ap_pdu_tx[73] = u4_t_eemax;

    u4_ap_pdu_tx[74]  =  (U4)u1_t_femonth[0];
    u4_ap_pdu_tx[74] |= ((U4)u1_t_femonth[1] << XSPI_SHIFT_1BYTE);
    u4_ap_pdu_tx[74] |= ((U4)u1_t_femonth[2] << XSPI_SHIFT_2BYTE);
    u4_ap_pdu_tx[74] |= ((U4)u1_t_femonth[3] << XSPI_SHIFT_3BYTE);
    u4_ap_pdu_tx[75]  =  (U4)u1_t_femonth[4];
    u4_ap_pdu_tx[75] |= ((U4)u1_t_femonth[5] << XSPI_SHIFT_1BYTE);
    u4_ap_pdu_tx[75] |= ((U4)u1_t_eemonth[0] << XSPI_SHIFT_2BYTE);
    u4_ap_pdu_tx[75] |= ((U4)u1_t_eemonth[1] << XSPI_SHIFT_3BYTE);
    u4_ap_pdu_tx[76]  =  (U4)u1_t_eemonth[2];
    u4_ap_pdu_tx[76] |= ((U4)u1_t_eemonth[3] << XSPI_SHIFT_1BYTE);
    u4_ap_pdu_tx[76] |= ((U4)u1_t_eemonth[4] << XSPI_SHIFT_2BYTE);
    u4_ap_pdu_tx[76] |= ((U4)u1_t_eemonth[5] << XSPI_SHIFT_3BYTE);

    u4_ap_pdu_tx[77]  =  (U4)u1_t_feday[0];
    u4_ap_pdu_tx[77] |= ((U4)u1_t_feday[1] << XSPI_SHIFT_1BYTE);
    u4_ap_pdu_tx[77] |= ((U4)u1_t_feday[2] << XSPI_SHIFT_2BYTE);
    u4_ap_pdu_tx[77] |= ((U4)u1_t_feday[3] << XSPI_SHIFT_3BYTE);
    u4_ap_pdu_tx[78]  =  (U4)u1_t_feday[4];
    u4_ap_pdu_tx[78] |= ((U4)u1_t_feday[5] << XSPI_SHIFT_1BYTE);
    u4_ap_pdu_tx[78] |= ((U4)u1_t_eeday[0] << XSPI_SHIFT_2BYTE);
    u4_ap_pdu_tx[78] |= ((U4)u1_t_eeday[1] << XSPI_SHIFT_3BYTE);
    u4_ap_pdu_tx[79]  =  (U4)u1_t_eeday[2];
    u4_ap_pdu_tx[79] |= ((U4)u1_t_eeday[3] << XSPI_SHIFT_1BYTE);
    u4_ap_pdu_tx[79] |= ((U4)u1_t_eeday[4] << XSPI_SHIFT_2BYTE);
    u4_ap_pdu_tx[79] |= ((U4)u1_t_eeday[5] << XSPI_SHIFT_3BYTE);

    u1_t_1mferslt = u1_g_AvgGrphRslt((U1)AVGGRPH_CNTT_1MFE);
    u1_t_1meerslt = u1_g_AvgGrphRslt((U1)AVGGRPH_CNTT_1MEE);
    u1_t_taferslt = u1_g_AvgGrphRslt((U1)AVGGRPH_CNTT_TAFE);
    u1_t_taeerslt = u1_g_AvgGrphRslt((U1)AVGGRPH_CNTT_TAEE);

    u4_ap_pdu_tx[80]  =  (U4)u1_t_1mferslt & (U4)XSPI_MSK_02BIT;
    u4_ap_pdu_tx[80] |= ((U4)u1_t_1meerslt & (U4)XSPI_MSK_02BIT) << 2U;
    u4_ap_pdu_tx[80] |= ((U4)u1_t_taferslt & (U4)XSPI_MSK_02BIT) << 4U;
    u4_ap_pdu_tx[80] |= ((U4)u1_t_taeerslt & (U4)XSPI_MSK_02BIT) << 6U;
    u4_ap_pdu_tx[80] |= ((U4)u1_t_taferslt & (U4)XSPI_MSK_02BIT) << 8U;
    u4_ap_pdu_tx[80] |= ((U4)u1_t_taeerslt & (U4)XSPI_MSK_02BIT) << 10U;
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgRxDispsts(U4 * u4_ap_pdu_tx)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgRxDispsts(    const U4 * u4_ap_PDU_RX) {
    U1  u1_t_display_sts;

    u1_t_display_sts = u1_XSPI_MET_READ__BIT(u4_ap_PDU_RX[0], (U1)0U, (U1)2U);            /* DISPLAY_STS         */
    if(u1_t_display_sts == (U1)0x01U){
        vd_g_HmiScreenPut((U1)HMISCREEN_CH_DISP_STS,(U1)TRUE);
    }
    else{
        vd_g_HmiScreenPut((U1)HMISCREEN_CH_DISP_STS,(U1)FALSE);
    }

    u1_t_display_sts = u1_XSPI_MET_READ__BIT(u4_ap_PDU_RX[0], (U1)2U, (U1)2U);            /* DISPLAY_STS_WO_TURN */
    if (u1_t_display_sts == (U1)0x01U) {
        vd_g_HmiScreenPut((U1)HMISCREEN_CH_DISP_STS_WO_TURN,(U1)TRUE);
    }
    else{
        vd_g_HmiScreenPut((U1)HMISCREEN_CH_DISP_STS_WO_TURN,(U1)FALSE);
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgRxMetcstm(U4 * u4_ap_PDU_RX)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgRxMetcstm(    const U4 * u4_ap_PDU_RX) {

    /* Maint */
    vd_g_HmiMaintMetCstmPut(&u4_ap_PDU_RX[6]);

    /* CSTM_DIMSW */
    u1_s_xspi_dimsw = u1_XSPI_MET_READ__BIT(u4_ap_PDU_RX[0] , (U1)24U , (U1)2U);

}

/*===================================================================================================================================*/
/*  U1      u1_g_XSpiDimSw(void)                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_s_xspi_dimsw                                                                                                  */
/*===================================================================================================================================*/
U1  u1_g_XSpiDimSw(void) {
    return(u1_s_xspi_dimsw);
}

static inline void    vd_s_XSpiCfgRxMcst(       const U4 * u4_ap_PDU_RX) {} /* @@Stub */

static inline void    vd_s_XSpiCfgRxMaint(      const U4 * u4_ap_PDU_RX) {} /* @@Stub */

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgRxWchime(U4 * u4_ap_pdu_tx)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgRxWchime(     const U4 * u4_ap_PDU_RX) {
    U1  u1_t_wchime[HMIWCHIME_NUM];
    
    u1_t_wchime[HMIWCHIME_TSR_A]       = u1_XSPI_MET_READ__BIT(u4_ap_PDU_RX[0] , (U1)2U , (U1)2U);          /* TSR_BZ2        */
    u1_t_wchime[HMIWCHIME_TSR_P]       = (U1)0U;                                                        /* -              */
    u1_t_wchime[HMIWCHIME_MASTER]      = u1_XSPI_MET_READ__BIT(u4_ap_PDU_RX[1] , (U1)0U , (U1)2U);          /* MASTER_BZ      */
    u1_t_wchime[HMIWCHIME_CRUISE_RJCT] = u1_XSPI_MET_READ__BIT(u4_ap_PDU_RX[1] , (U1)2U , (U1)2U);          /* CRUISE_RJCT_BZ */
    vd_g_HmiWchimePut(&u1_t_wchime[0] , (U1)HMIWCHIME_NUM);
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgRxWchime(U4 * u4_ap_pdu_tx)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgRxLocale(     const U4 * u4_ap_PDU_RX) {
    ST_HMILOCALE st_t_hmilocale;

    st_t_hmilocale.u1_language    = (U1)u4_ap_PDU_RX[0];
    st_t_hmilocale.u1_unit_dist   = u1_XSPI_MET_READ__BIT(u4_ap_PDU_RX[1] , (U1) 0U , (U1)2U);
    st_t_hmilocale.u1_unit_speed  = u1_XSPI_MET_READ__BIT(u4_ap_PDU_RX[1] , (U1) 2U , (U1)2U);
    st_t_hmilocale.u1_unit_eleco  = u1_XSPI_MET_READ__BIT(u4_ap_PDU_RX[1] , (U1) 8U , (U1)4U);
    st_t_hmilocale.u1_unit_ambtmp = u1_XSPI_MET_READ__BIT(u4_ap_PDU_RX[1] , (U1)12U , (U1)2U);
    st_t_hmilocale.u1_timeformat  = u1_XSPI_MET_READ__BIT(u4_ap_PDU_RX[1] , (U1)14U , (U1)2U);
    vd_g_HmiLocalePut(&st_t_hmilocale);
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgRxRcmmui(U4 * u4_ap_pdu_tx)                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgRxRcmmui(     const U4 * u4_ap_PDU_RX) {
    U1                 u1_t_cid;
    U1                 u1_t_usract;

    u1_t_cid    = u1_XSPI_MET_READ_BYTE(u4_ap_PDU_RX[0] , (U1)1U);
    u1_t_usract = u1_XSPI_MET_READ_BYTE(u4_ap_PDU_RX[0] , (U1)0U);
    vd_g_RcmmUIUserAct(u1_t_cid , u1_t_usract);
}

static inline void    vd_s_XSpiCfgRxRemoteWarn( const U4 * u4_ap_PDU_RX) {} /* @@Stub */

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgRxOdo(U4 * u4_ap_pdu_tx)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgRxOdo(        const U4 * u4_ap_PDU_RX) {
    U4  u4_t_trip_a;
    U4  u4_t_trip_b;

#if 0   /* BEV BSW provisionally */
    u4_t_trip_a    = u4_ap_PDU_RX[0];                                        /* TRIP_A                               */
    u4_t_trip_b    = u4_ap_PDU_RX[2];                                        /* TRIP_B                               */
#else
    u4_t_trip_a    = (U4)U4_MAX;                                             /* TRIP_A                               */
    u4_t_trip_b    = (U4)U4_MAX;                                             /* TRIP_B                               */
#endif

    vd_g_HmiOdoPut(u4_t_trip_a , u4_t_trip_b);
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgRxTripcom(U4 * u4_ap_pdu_tx)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgRxTripcom(    const U4 * u4_ap_PDU_RX) {
    ST_HMITRIPCOM st_t_hmitripcom;

    st_t_hmitripcom.u2_avg_vehspd_kmph_ta  = (U2)u4_ap_PDU_RX[0];       /* AVG_SPD_KMPH_USRRST                  */
    st_t_hmitripcom.u4_avg_ee_kmpl_ta      = u4_ap_PDU_RX[2];           /* AVG_EE_KMPL_USRRST                   */
    st_t_hmitripcom.u4_dist_km_tr_a        = u4_ap_PDU_RX[5];           /* TRIPA_DIST_KM_USRRST                 */
    st_t_hmitripcom.u4_dist_km_tr_b        = u4_ap_PDU_RX[6];           /* TRIPB_DIST_KM_USRRST                 */
    st_t_hmitripcom.u2_avg_vehspd_tr_a     = (U2)u4_ap_PDU_RX[7];       /* TRIPA_AVG_SPD_KMPH_USRRST            */
    st_t_hmitripcom.u4_ptsruntm_tr_a       = u4_ap_PDU_RX[8];           /* TRIPA_DRVTIME_HHHH_USRRST            */
                                                                        /* TRIPA_DRVTIME_MM_USRRST              */
                                                                        /* TRIPA_DRVTIME_SS_USRRST              */
    st_t_hmitripcom.u2_avg_vehspd_tr_b     = (U2)u4_ap_PDU_RX[9];       /* TRIPB_AVG_SPD_KMPH_USRRST            */
    st_t_hmitripcom.u4_ptsruntm_tr_b       = u4_ap_PDU_RX[10];          /* TRIPB_DRVTIME_HHHH_USRRST            */
                                                                        /* TRIPB_DRVTIME_MM_USRRST              */
                                                                        /* TRIPB_DRVTIME_SS_USRRST              */
    st_t_hmitripcom.u4_avg_he_kmpkg_ta     = (U4)XSPI_UNKNOWN;      /* AVG_HE_KMPL_USRRST is not Applicable */
    st_t_hmitripcom.u4_idlstp_time_hrs_lc  = (U4)XSPI_UNKNOWN;      /* IDLSTP_USRRST is not Applicable      */
    st_t_hmitripcom.u4_save_fs_ml_lc       = (U4)XSPI_UNKNOWN;      /* FUELSAVE_ML_USRRST is not Applicable */

    vd_g_HmiTripcomPut(&st_t_hmitripcom);
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgRxHUD(U4 * u4_ap_pdu_tx)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgRxHUD(        const U4 * u4_ap_PDU_RX) {

    U4 u4_t_loop;
    U1 u1_t_gvifsts;
    U4 u4_tp_hud_dtabuf[XSPI_HUD_DTA_NUM];
    U1 u1_t_rxdata;    /* Receive data */

    for(u4_t_loop = (U4)0U ; u4_t_loop < (U4)XSPI_HUD_DTA_NUM ; u4_t_loop++){
        u4_tp_hud_dtabuf[u4_t_loop] = u4_ap_PDU_RX[u4_t_loop];
    }

    vd_g_HmiHudDataPut(&u4_tp_hud_dtabuf[0]);

    u1_t_gvifsts = u1_XSPI_MET_READ_BYTE(u4_ap_PDU_RX[2] , (U1)3U);

    if (u1_t_gvifsts == (U1)0U) {
        u1_s_xspi_vipos_disp = u1_XSPI_MET_READ__BIT(u4_ap_PDU_RX[15] , (U1)0U , (U1)1U);

        u1_t_rxdata = (U1)(u4_ap_PDU_RX[10] & (U4)0x03U);
        if(u1_t_rxdata == (U1)1U){
#if 0   /* BEV Rebase provisionally */
            vd_g_HmiMcstPut((U1)HMIMCST_GV_SYS_HW_ERR, u1_t_rxdata);    /* GV SYS HW ERR */
#endif   /* BEV Rebase provisionally */
        }
        else if(u1_t_rxdata == (U1)0U){
#if 0   /* BEV Rebase provisionally */
            vd_g_HmiMcstPut((U1)HMIMCST_GV_SYS_HW_ERR, u1_t_rxdata);    /* GV SYS HW NML */
#endif   /* BEV Rebase provisionally */
        }
        else {
            /* Do Nothing */
        }

        u1_t_rxdata = (U1)((u4_ap_PDU_RX[10] >> 2) & (U4)0x03U);
        u1_s_xspi_gvifsts = u1_t_rxdata;
        if(u1_t_rxdata == (U1)1U){
#if 0   /* BEV Rebase provisionally */
            vd_g_HmiMcstPut((U1)HMIMCST_GVIF_LINKDOWN, u1_t_rxdata);    /* GVIF LINKDOWN */
#endif   /* BEV Rebase provisionally */
        }
        else if(u1_t_rxdata == (U1)0U){
#if 0   /* BEV Rebase provisionally */
            vd_g_HmiMcstPut((U1)HMIMCST_GVIF_LINKDOWN, u1_t_rxdata);    /* GVIF LINK NML */
#endif   /* BEV Rebase provisionally */
        }
        else {
            /* Do Nothing */
        }
    } else {
        u1_s_xspi_vipos_disp = (U1)0U;
        u1_s_xspi_gvifsts = (U1)XSPI_GVIF_UNDEF2;
    }
}

/*===================================================================================================================================*/
/*  U1    u1_g_XSpiGvifSts(void)                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_s_xspi_gvifsts                                                                                                */
/*===================================================================================================================================*/
U1    u1_g_XSpiGvifSts(void) {
    return(u1_s_xspi_gvifsts);
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgRxAvgGrph(U4 * u4_ap_pdu_tx)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgRxAvgGrph(const U4 * u4_ap_PDU_RX) {
    vd_g_HmiTripcomGrphPut(&u4_ap_PDU_RX[0]);
}

/*===================================================================================================================================*/
/*  static void    vd_s_XSpiCfgRxMETDISP(U4 * u4_ap_PDU_RX)                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline void    vd_s_XSpiCfgRxMETDISP(const U4* u4_ap_PDU_RX) {
    U1 u1_t_gvifsts;

    u1_t_gvifsts = u1_XSPI_MET_READ__BIT(u4_ap_PDU_RX[3], (U1)24U, (U1)2U);    /* DISP_GVIF_ENABLE */
    if(u1_t_gvifsts == (U1)XSPI_GVIF_METDSP_NML){
        u1_s_xspi_disp_gvifsts = (U1)XSPI_GVIF_METDSP_NML;
    }
    else if(u1_t_gvifsts == (U1)XSPI_GVIF_METDSP_FAIL){
        u1_s_xspi_disp_gvifsts = (U1)XSPI_GVIF_METDSP_FAIL;
    }
    else{
        u1_s_xspi_disp_gvifsts = (U1)XSPI_GVIF_METDSP_UNDEF;
    }
}

/*===================================================================================================================================*/
/*  U1    u1_g_XSpiGvifSts_METDISP(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         u1_s_xspi_disp_gvifsts                                                                                           */
/*===================================================================================================================================*/
U1    u1_g_XSpiGvifSts_METDISP(void) {
    return(u1_s_xspi_disp_gvifsts);
}

/*===================================================================================================================================*/
/*  void    vd_g_XSpiCfgInitCh0(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiCfgInitCh0(void)
{
    u1_s_xspi_vipos_disp                      = (U1)0U;
    u1_s_xspi_dimsw                           = (U1)0U;
    u1_s_xspi_gvifsts                         = (U1)XSPI_GVIF_UNDEF2;
    u1_s_xspi_disp_gvifsts                    = (U1)XSPI_GVIF_METDSP_UNDEF;

}

/*===================================================================================================================================*/
/*  void    vd_g_XSpiCfgPduRxCh0(const U4 * u4_ap_PDU_RX)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiCfgPduRxCh0(const U4 * u4_ap_PDU_RX)
{
    vd_s_XSpiCfgRxDispsts(    &u4_ap_PDU_RX[ 10]);
    vd_s_XSpiCfgRxMcst(       &u4_ap_PDU_RX[  2]);
    vd_s_XSpiCfgRxMaint(      &u4_ap_PDU_RX[ 13]);
    vd_s_XSpiCfgRxWchime(     &u4_ap_PDU_RX[ 15]);
    vd_s_XSpiCfgRxLocale(     &u4_ap_PDU_RX[ 17]);
    vd_s_XSpiCfgRxRcmmui(     &u4_ap_PDU_RX[ 19]);
    vd_s_XSpiCfgRxRemoteWarn( &u4_ap_PDU_RX[ 21]);
    vd_s_XSpiCfgRxAvgGrph(    &u4_ap_PDU_RX[ 38]);
    vd_s_XSpiCfgRxOdo(        &u4_ap_PDU_RX[ 40]);
    vd_s_XSpiCfgRxTripcom(    &u4_ap_PDU_RX[ 44]);
    /* vd_s_XSpiCfgRxNvm(        &u4_ap_PDU_RX[ 57]); */ /* Delete for CV-R */
    vd_s_XSpiCfgRxHUD(        &u4_ap_PDU_RX[100]);
    vd_s_XSpiCfgRxMETDISP(    &u4_ap_PDU_RX[121]);
    vd_s_XSpiCfgRxMetcstm(    &u4_ap_PDU_RX[212]);
    /* vd_s_XSpiCfgRxDnPrdctAns( &u4_ap_PDU_RX[344]); */ /* Delete for CV-R */


    /* vd_s_XSpiCfgRxSPN(        &u4_ap_PDU_RX[387]); */ /* Delete for CV-R */
    /* vd_s_XSpiCfgRxDiag(       &u4_ap_PDU_RX[368]); */ /* Delete for CV-R */
    /* vd_s_XSpiCfgRxHwDiagFact( &u4_ap_PDU_RX[506]); */ /* Delete for CV-R */
    /* vd_s_XSpiRxEsiRcarE2PRes( &u4_ap_PDU_RX[346]); */ /* Delete for CV-R */
    /* vd_s_XSpiCfgRxSoftver(    &u4_ap_PDU_RX[507]); */ /* Delete for CV-R */
}

/*===================================================================================================================================*/
/*  void    vd_g_XSpiCfgPduTxCh0(U4 * u4_ap_pdu_tx)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XSpiCfgPduTxCh0(U4 * u4_ap_pdu_tx)
{
    volatile static const U4    u4_s_XSPI_LOCALCOMSPEC     = (U4)XSPI_LOCALCOM_SPEC;

                                                            /* Payload                                                      */
                                                            /* Sta - End    : Main Category                                 */
    vd_s_XSpiCfgTxPowerMd(       &u4_ap_pdu_tx[  9]);      /* 009 - 009    : PowerMode                                     */
    vd_s_XSpiCfgTxTripCnt(       &u4_ap_pdu_tx[ 11]);      /* 011 - 012    : Reprog                                        */
    vd_s_XSpiCfgTxVariation(     &u4_ap_pdu_tx[ 13]);      /* 013 - 025    : Variation                                     */
    vd_s_XSpiCfgTxLocale(        &u4_ap_pdu_tx[ 27]);      /* 027 - 028    : Locale                                        */
    vd_s_XSpiCfgTxStrsw(         &u4_ap_pdu_tx[ 29]);      /* 029 - 031    : Steering Switch                               */
    vd_s_XSpiCfgTxVehSpd(        &u4_ap_pdu_tx[ 32]);      /* 032 - 035    : Vehicle Speed                                 */
    vd_s_XSpiCfgTxHybsys(        &u4_ap_pdu_tx[ 39]);      /* 039 - 040    : Hybrid System Ind.                            */
    vd_s_XSpiCfgTxPtsctmp(       &u4_ap_pdu_tx[ 43]);      /* 043 - 043    : EngineTemp                                    */
    vd_s_XSpiCfgTxAmbtmp(        &u4_ap_pdu_tx[ 44]);      /* 044 - 045    : Ambient Temp                                  */
    /* vd_g_XSpiCfgTxHydrovol(      &u4_ap_pdu_tx[0]); */  /*     -        : Hydro Volume                                  */
    vd_s_XSpiCfgTxShift(         &u4_ap_pdu_tx[ 49]);      /* 049 - 053    : Shift                                         */
    vd_s_XSpiCfgTxDimming(       &u4_ap_pdu_tx[ 54]);      /* 054 - 056    : Dimming                                       */
    vd_s_XSpiCfgTxClock(         &u4_ap_pdu_tx[ 57]);      /* 057 - 058    : Clock                                         */
    vd_s_XSpiCfgTxOdo(           &u4_ap_pdu_tx[ 59]);      /* 059 - 065    : Odo Meter                                     */
    vd_s_XSpiCfgTxMaint(         &u4_ap_pdu_tx[ 66]);      /* 066 - 067    : Maintenance                                   */
    vd_s_XSpiCfgTxRcmmui(        &u4_ap_pdu_tx[ 68]);      /* 068 - 069    : Rcmmui                                        */
    vd_s_XSpiCfgTxPwrmet(        &u4_ap_pdu_tx[ 70]);      /* 070 - 071    : Pwrmet                                        */
    vd_s_XSpiCfgTxHud(           &u4_ap_pdu_tx[110]);      /* 110 - 134    : Hud                                           */
    vd_s_XSpiCfgTxWrnmsg(        &u4_ap_pdu_tx[135]);      /* 135 - 184    : Wrnmsg                                        */
    vd_s_XSpiCfgTxTripcom(       &u4_ap_pdu_tx[185]);      /* 185 - 234    : Tripcom                                       */
    vd_s_XSpiCfgTxTelltale(      &u4_ap_pdu_tx[235]);      /* 235 - 264    : Telltale                                      */
    vd_s_XSpiCfgTxMulmed(        &u4_ap_pdu_tx[265]);      /* 265 - 281    : MultimediaUserName                            */
    vd_s_XSpiCfgTxNickname(      &u4_ap_pdu_tx[362]);      /* 362 - 378    : MultimediaNickName                            */
    vd_s_XSpiCfgTxAttmp  (       &u4_ap_pdu_tx[417]);      /* 417 - 418    : Attmp                                         */
    vd_s_XSpiCfgTxMetcstmMcst(   &u4_ap_pdu_tx[566]);      /* 566 - 584    : Meter Customize                               */
    vd_s_XSpiCfgTxCalib(         &u4_ap_pdu_tx[585]);      /* 585 - 625    : Calibration                                   */

    u4_ap_pdu_tx[482]  = u4_s_XSPI_LOCALCOMSPEC;                   /* __LOCALCOMSPEC__                                        */
    u4_ap_pdu_tx[483]  = (U4)0U;                                        /* __CHECK_SUM_CH0__                                  */

    vd_s_XSpiCfgTxAvgGrph(       &u4_ap_pdu_tx[484]);      /* 484 - 564    : Average Graph                                 */
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     8/22/2018  TA       New.                                                                                               */
/*  1.3.0    10/05/2020  KM       Change for 800B CV-R.                                                                              */
/*  1.4.0    12/21/2020  TN       Change for 800B 1A.                                                                                */
/*  1.5.0    05/17/2021  TN       Change for 300D/178D/893B CV.                                                                      */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  970B/200D/220D                                                                                                                   */
/*           07/18/2022  TN       New for 970B/200D/220D Pre1A base on 178D.                                                         */
/*                                                                                                                                   */
/*  115D/117D/200D                                                                                                                   */
/*           08/30/2022  TN       Change for 115D/117D/200D 1A                                                                       */
/*                                                                                                                                   */
/*  115D/117D/200D                                                                                                                   */
/*           10/31/2022  TN       Change for 115D/117D/200D MPT                                                                      */
/*                                                                                                                                   */
/*  115D/117D/200D                                                                                                                   */
/*           11/15/2022  TN       Change for 970B/850B 1A                                                                            */
/*                                                                                                                                   */
/*  220D/970B/850B                                                                                                                   */
/*           01/20/2023  TN       Change for 970B/850B MPT, Change for 220D 1A.                                                      */
/*                                                                                                                                   */
/*  220D/130D HEV                                                                                                                    */
/*           04/04/2023  TN       Add DISTTOEMPTY_MILE. Change for 220D/130D HEV MPT.                                                */
/*                                                                                                                                   */
/*  19PFv3-1  01/23/2024 KH       Add vd_s_LcomSpiCfgTxCalib function.                                                               */
/*  19PFv3-2  02/07/2024 PG       Change for MET-M_DMTOEC-CSTD-1-01-E-C0                                                             */
/*  19PFv3-3  02/12/2024 PG       Change for MET-M_DMEVRNGE-CSTD-1-07-A-C1                                                           */
/*  19PFv3-4  02/19/2024 SW       Add parameter to st_sp_LCOM_CALIB for M_MCUCONST-CSTD-A0-012                                       */
/*  19PFv3-5  02/14/2024 DR       Add function for TIMCH                                                                             */
/*  19PFv3-6  02/20/2024 GM       Change config for 19PFv3 CV                                                                        */
/*  19PFv3-7  02/27/2024 DR       Update TMNT support interface                                                                      */
/*  19PFv3-8  02/29/2024 SW       Change config for 19PFv3 CV(add parameter to u2_sp_LCOM_ESOPT_ID[])                                */
/*  19PFv3-9  03/13/2024 SN       Fix BODY_SHAPE                                                                                     */
/*  19PFv3-10 04/04/2024 KH       Delete VRCTRL function                                                                             */
/*  19PFv3-12 04/12/2024 SH       Add calibration guard                                                                              */
/*  19PFv3-13 04/15/2024 SN       Change Esopt fot ADASCS                                                                            */
/*  19PFv3-14 04/18/2024 TN       Change for MCUOCNSTv012->v014                                                                      */
/*  19PFv3-15 05/07/2024 TR       Change config for 19PFv3 CV                                                                        */
/*  19PFv3-16 05/10/2024 KH       Add MET_DISP function                                                                              */
/*  19PFv3-17 05/02/2024 GM       Delete unnecessary items from METVARI                                                              */
/*  19PFv3-18 06/14/2024 TN       Add SOHDSP                                                                                         */
/*  19PFv3-19 06/20/2024 PG       Add SGAUGE config for 19PFv3 R1.2                                                                  */
/*  19PFv3-20 06/26/2024 TR       Add PWRMET and adjust TftCntts payload offset                                                      */
/*  19PFv3-21 06/27/2024 TN       Delete Calibration Guard Process.                                                                  */
/*  19PFv3-22 07/08/2024 SN       Add parameter st_sp_LCOM_CALIB for REVIND                                                          */
/*  19PFv3-23 07/08/2024 KH       Delete BOOST function                                                                              */
/*  19PFV3-24 07/11/2024 TN       Add Calibration Guard to Unify Vehicle Operation.                                                  */
/*  19PFv3-24 07/10/2024 YR       Add HCS config                                                                                     */
/*  19PFv3-25 07/15/2024 AA       Revised LcomIF used for HmiScreenPut                                                               */
/*  BEV-1     02/10/2025 RO       Change for BEV System_Consideration_1.(MET-M_ONOFF-CSTD-1-)                                        */
/*  BEV-2     02/10/2025 SF       Change for BEV System_Consideration_1.(MET-M_ONOFF-CSTD-1-02-A-C0)                                 */
/*  BEV-3     02/26/2025 RS       Change for BEV System_Consideration_1.(Requests from the SOC team for electricity cost units)      */
/*  BEV-4     03/06/2025 SF       Change for BEV System_Consideration_1.(Requests from the SOC team)                                 */
/*  BEV-5     04/25/2025 MN       Change for BEV System_Consideration_1.(MET-M_CLKCTL-CSTD-0-06-A-C1)                                */
/*  BEV-6     05/30/2025 SN(K)    Change for BEV System_Consideration_2.(MET-B_TITEBB-CSTD-0-00-A-C0)                                */
/*  BEV-7     05/30/2025 SN(K)    Change for BEV System_Consideration_2.(MET-C_HCSBSW-CSTD-0-01-A-C0)                                */
/*  BEV-8     05/30/2025 SN(K)    Change for BEV System_Consideration_2.(MET-S_ADBB-CSTD-0-01-A-C0)                                  */
/*  BEV-9     06/17/2025 JS       Change for BEV System_Consideration_2.(MET-B_WDICBB-CSTD-0-01-A-C0)                                */
/*  BEV-10    10/22/2025 TS       Change for BEV rebase.                                                                             */
/*                                                                                                                                   */
/*  * TA   = Teruyuki Anjima, Denso                                                                                                  */
/*  * KM   = Keisuke Mashita, Denso Techno                                                                                           */
/*  * TN   = Tetsushi Nakano, Denso Techno                                                                                           */
/*  * KH   = Kiko Huerte, DTPH                                                                                                       */
/*  * PG   = Patrick Garcia, DTPH                                                                                                    */
/*  * SW   = Shun Watanabe, Denso Techno                                                                                             */
/*  * DR   = Dyan Reyes,DTPH                                                                                                         */
/*  * GM   = Glen Monteposo, DTPH                                                                                                    */
/*  * SN   = Shimon Nambu, Denso Techno                                                                                              */
/*  * TR   = Tebs Ramos, DTPH                                                                                                        */
/*  * YR   = Yhana Regalario, DTPH                                                                                                   */
/*  * AA   = Anna Asuncion, Denso Techno                                                                                             */
/*  * RO   = Ryo Oohashi, KSE                                                                                                        */
/*  * SF   = Shiro Furui, Denso Techno                                                                                               */
/*  * RS   = Ryuki Sako, Denso Techno                                                                                                */
/*  * MN   = Mikiya Negishi, KSE                                                                                                     */
/*  * SN(K)= Shizuka Nakajima, KSE                                                                                                   */
/*  * JS   = Jun Sugiyama, KSE                                                                                                       */
/*  * TS   = Takuo Suganuma, Denso Techno                                                                                            */
/*                                                                                                                                   */
/*===================================================================================================================================*/
