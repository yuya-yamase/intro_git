/* 2.2.1 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  eXternal Peripheral Device Initialization                                                                                        */
/*                                                                                                                                   */
/*===================================================================================================================================*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version                                                                                                                          */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XPD_INIT_CFG_C_MAJOR                     (2U)
#define XPD_INIT_CFG_C_MINOR                     (2U)
#define XPD_INIT_CFG_C_PATCH                     (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "xpd_init_cfg_private.h"
#include "xpd_init_ota.h"

#include "dio_drv.h"
#include "port_drv.h"
#include "gpt_drv_j32.h"
#include "gpt_drv_b16.h"
#include "veh_opemd.h"
#if 0   /* BEV BSW provisionally */
#else
#include "veh_opemd_xmode_STUB.h"
#endif

#include "iohw_diflt.h"

#include "rim_ctl.h"
#include "rim_ctl_cfg.h"

#include "lcom_spi.h"
#include "esi_ssc.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((XPD_INIT_CFG_C_MAJOR != XPD_INIT_CFG_H_MAJOR) || \
     (XPD_INIT_CFG_C_MINOR != XPD_INIT_CFG_H_MINOR) || \
     (XPD_INIT_CFG_C_PATCH != XPD_INIT_CFG_H_PATCH))
#error "xpd_init_cfg.c and xpd_init_cfg_private.h : source and header files are inconsistent!"
#endif

#if ((XPD_INIT_CFG_C_MAJOR != XPD_INIT_OTA_H_MAJOR) || \
     (XPD_INIT_CFG_C_MINOR != XPD_INIT_OTA_H_MINOR) || \
     (XPD_INIT_CFG_C_PATCH != XPD_INIT_OTA_H_PATCH))
#error "xpd_init_cfg.c and xpd_init_ota.h : source and header files are inconsistent!"
#endif


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XPDI_MAIN_TICK                           (10U) /* 10 mseconds */

#define XPDI_VOL_UNKNWN                          (0x00U)
#define XPDI_VOL_LOW                             (0x01U)
#define XPDI_VOL_NML                             (0x02U)

#define XPDI_RCAR_MON_LO_VOLT                    (0x01U)
#define XPDI_RCAR_MON_LCOM_SPI                   (0x02U)
#define XPDI_RCAR_MON_LVD_BAT                    (0x04U)
#define XPDI_RCAR_MON_LVD_PMV                    (0x08U)
#define XPDI_RCAR_MON_LVD_PMI                    (0x10U)

#define XPDI_PORT_RCAR_PRIM_EN_LO                (PORT_PIN_MODE_P3_6_DO_LO)
#define XPDI_PORT_RCAR_PRIM_EN_HI                (PORT_PIN_MODE_P3_6_DO_HI)

#define XPDI_DIO_PMIC_EN                         (DIO_CH_PMIC_EN)

#define XPDI_DIO_RCAR_URPG_EN                    (DIO_CH_RCAR_REFLASH_EN)
#define XPDI_DIO_RCAR_GDC_BMONI                  (DIO_CH_GDC_B_MONI)

#define XPDI_GPT_LOEDGE_CH                       (GPT_J32_UN_0_CH_02)
#define XPDI_GPT_WAIT_CH                         (GPT_B16_UN_0_CH_03)

#define XPDI_HARF_SHIFT                          (16U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1                   u1_s_xpdi_rcar_mon_act;
static U1                   u1_s_xpdi_rcar_fdrqst;
static U1                   u1_s_xpdi_bmoni_sts;
static U1                   u1_s_xpdi_igmoni_sts;
static U1                   u1_s_xpdi_gdc_bomi_lo;
static U1                   u1_s_xpdi_pmic_vin_sts;
static U1                   u1_s_xpdi_pmic_int_sts;
static U1                   u1_s_xpdi_ota_rstrqst;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_XpdiRCarLvdchk(U4 * u4_ap_ss);
static void    vd_s_XpdiRCarPwrOn(void);
static void    vd_s_XpdiRCarLComRun(void);
static void    vd_s_XpdiRCarDeAct(void);
static void    vd_s_XpdiRCarPwrOff(void);
static void    vd_s_XpdiBmoniJdg(void);
static void    vd_s_XpdiIgmoniJdg(void);
static void    vd_s_XpdiHudEnSet(void);
static U1      u1_s_XpdiGdcBJdg(void);
static void    vd_s_XpdiPmvJdg(void);
static void    vd_s_XpdiPmiJdg(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U4                    u4_g_XPDI_FRT_TO_LAPTM = (U4)GPT_FRT_1US;                 /*  1 microsecond               */
                                                                                      /* lap max = 268.435455 seconds */

const U2                    u2_g_XPDI_SDR_TOUT     = (U2)30U / (U2)XPDI_MAIN_TICK;    /* 30 milliseconds              */

/* ------------------------------------------------------------------------------------------ */
/* Note :                                                                                     */
/* ------------------------------------------------------------------------------------------ */
/* If u1_g_XPDI_CTRL_RST != XPDI_CTRL_SEQ_OFF, the sequence is started from XPDI_CTRL_SEQ_ABO */
/* If u1_g_XPDI_CTRL_RST == XPDI_CTRL_SEQ_OFF, the sequence is started from XPDI_CTRL_SEQ_OFF */
/* ------------------------------------------------------------------------------------------ */
const U1                    u1_g_XPDI_CTRL_RST     = (U1)XPDI_CTRL_SEQ_OFF;
const U1                    u1_g_XPDI_ABO_CNT_MAX  = (U1)3U;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_XPDI_STEP   st_sp_XPDI_STEP[] = {
    /* 00 : XPDI_CTRL_SEQ_STA      */
    {
        &vd_s_XpdiRCarPwrOn,                 /* fp_vd_STEP                      */
        ((U4)0U                    |         /* u4_tcpbit.XPDI_STEP_TCP_LAP_MIN */ /*   0 msec */
         (U4)XPDI_SEQ_EXE_4TH_W_EI |         /* u4_tcpbit.XPDI_STEP_TCP_SEQ_EXE */
         (U4)XPDI_STEP_TCP_LTM_STA)          /* u4_tcpbit.XPDI_STEP_TCP_LTM_STA */
    },
    /* 01 : XPDI_CTRL_SEQ_RUN      */
    {
        &vd_s_XpdiRCarLComRun,               /* fp_vd_STEP                      */
        ((U4)0U                    |         /* u4_tcpbit.XPDI_STEP_TCP_LAP_MIN */ /*   0 msec */
         (U4)XPDI_SEQ_EXE_4TH_W_EI |         /* u4_tcpbit.XPDI_STEP_TCP_SEQ_EXE */
         (U4)XPDI_STEP_TCP_LTM_STA)          /* u4_tcpbit.XPDI_STEP_TCP_LTM_STA */
    },
    /* 02 : XPDI_CTRL_SEQ_SHU      */
    /* 02 : XPDI_CTRL_SEQ_ABO      */
    {
        &vd_s_XpdiRCarDeAct,                 /* fp_vd_STEP                      */
        ((U4)0U                    |         /* u4_tcpbit.XPDI_STEP_TCP_LAP_MIN */ /*   0 msec */
         (U4)XPDI_SEQ_EXE_4TH_W_EI |         /* u4_tcpbit.XPDI_STEP_TCP_SEQ_EXE */
         (U4)XPDI_STEP_TCP_LTM_STA)          /* u4_tcpbit.XPDI_STEP_TCP_LTM_STA */
    },
    {
        &vd_s_XpdiRCarPwrOff,                /* fp_vd_STEP                      */
        ((U4)420000U               |         /* u4_tcpbit.XPDI_STEP_TCP_LAP_MIN */ /* 420 msec */
         (U4)XPDI_SEQ_EXE_1ST_W_EI |         /* u4_tcpbit.XPDI_STEP_TCP_SEQ_EXE */
         (U4)XPDI_STEP_TCP_LTM_STA)          /* u4_tcpbit.XPDI_STEP_TCP_LTM_STA */
    },
    {
        &vd_s_XpdiRCarPwrOff,                /* fp_vd_STEP                      */
        ((U4)9000U                 |         /* u4_tcpbit.XPDI_STEP_TCP_LAP_MIN */ /*  10 msec */
         (U4)XPDI_SEQ_EXE_1ST_W_EI |         /* u4_tcpbit.XPDI_STEP_TCP_SEQ_EXE */
         (U4)0U                   )          /* u4_tcpbit.XPDI_STEP_TCP_LTM_STA */
    },
    /* 05 : XPDI_CTRL_SEQ_OFF      */
    /* 05 : XPDI_CTRL_SEQ_RST_OFF  */
    {
        &vd_s_XpdiRCarPwrOff,                /* fp_vd_STEP                      */
        ((U4)0U                    |         /* u4_tcpbit.XPDI_STEP_TCP_LAP_MIN */ /*   0 msec */
         (U4)XPDI_SEQ_EXE_1ST_W_EI |         /* u4_tcpbit.XPDI_STEP_TCP_SEQ_EXE */
         (U4)XPDI_STEP_TCP_LTM_STA)          /* u4_tcpbit.XPDI_STEP_TCP_LTM_STA */
    },
    /* 06 : XPDI_CTRL_SEQ_RST_STA   */
    {
        &vd_s_XpdiRCarPwrOn,                 /* fp_vd_STEP                      */
        ((U4)0U                    |         /* u4_tcpbit.XPDI_STEP_TCP_LAP_MIN */ /*   0 msec */
         (U4)XPDI_SEQ_EXE_4TH_W_EI |         /* u4_tcpbit.XPDI_STEP_TCP_SEQ_EXE */
         (U4)XPDI_STEP_TCP_LTM_STA)          /* u4_tcpbit.XPDI_STEP_TCP_LTM_STA */
    },
    {
        vdp_PTR_NA,                          /* fp_vd_STEP                      */
        ((U4)420000U               |         /* u4_tcpbit.XPDI_STEP_TCP_LAP_MIN */ /* 420 msec */
         (U4)XPDI_SEQ_EXE_1ST_W_EI |         /* u4_tcpbit.XPDI_STEP_TCP_SEQ_EXE */
         (U4)0U                   )          /* u4_tcpbit.XPDI_STEP_TCP_LTM_STA */
    }
};

const ST_XPDI_SEQ           st_gp_XPDI_SEQ[XPDI_CTRL_NUM_SEQ] = {
    {&st_sp_XPDI_STEP[5], (U2)1U}, /*XPDI_CTRL_SEQ_OFF      (0U) */
    {&st_sp_XPDI_STEP[0], (U2)1U}, /*XPDI_CTRL_SEQ_STA      (1U) */
    {&st_sp_XPDI_STEP[1], (U2)1U}, /*XPDI_CTRL_SEQ_RUN      (2U) */
    {&st_sp_XPDI_STEP[2], (U2)3U}, /*XPDI_CTRL_SEQ_SHU      (3U) */
    {&st_sp_XPDI_STEP[2], (U2)3U}, /*XPDI_CTRL_SEQ_ABO      (4U) */
    {&st_sp_XPDI_STEP[5], (U2)1U}, /*XPDI_CTRL_SEQ_RST_OFF  (5U) */
    {&st_sp_XPDI_STEP[6], (U2)2U}  /*XPDI_CTRL_SEQ_RST_STA  (6U) */
};

static const U4     u4_sp_GDCB_LO_START[GPT_J32_START_NUM_CFG] = {
   (U4)GPT_J32_START_CTRL_BIT_IRQ_EN | (U4)GPT_J32_START_CTRL_BIT_TRG_ST | (U4)GPT_J32_START_CTRL_ELVL_FA,
   (U4)U4_MAX
};

static const U2     u2_sp_WAIT_START[GPT_B16_START_NUM_CFG] = {
    (U2)GPT_B16_START_CTRL_BIT_TRG_ST | (U2)GPT_B16_START_CTRL_BIT_IRQ_EN,
    u2_GPT_B16_ADT_US_TO_CNT(300)                    /* 300 [us] */
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_XpdiCfgRstInit(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XpdiCfgRstInit(void)
{
    U4                u4_t_bon;
    U1                u1_t_reflash;

    u1_s_xpdi_rcar_mon_act = (U1)XPDI_RCAR_MON_LO_VOLT;
    u1_s_xpdi_rcar_fdrqst  = (U1)0x00U;
    u1_s_xpdi_bmoni_sts    = (U1)XPDI_VOL_UNKNWN;
    u1_s_xpdi_igmoni_sts   = (U1)XPDI_VOL_UNKNWN;
    u1_s_xpdi_gdc_bomi_lo  = (U1)FALSE;
    u1_s_xpdi_pmic_vin_sts = (U1)XPDI_VOL_UNKNWN;
    u1_s_xpdi_pmic_int_sts = (U1)XPDI_VOL_UNKNWN;
	u1_s_xpdi_ota_rstrqst  = (U1)FALSE;

    u4_t_bon = u4_g_EcuMWkupReason() & (U4)ECU_M_WKUP_BY_BATT_ON;
    if(u4_t_bon != (U4)0U){
        u1_t_reflash = u1_g_Dio_ReadChannel((U2)XPDI_DIO_RCAR_URPG_EN);           /* RCAR_REFLASH_EN */
    }
    else{
        u1_t_reflash = (U1)DIO_LVL_HIGH;
    }
    vd_g_Rim_WriteU1((U2)RIMID_U1_XPDI_RCAR_RFLSH, u1_t_reflash);

    vd_g_Dio_WriteChannel((U2)XPDI_DIO_PMIC_EN, (U1)DIO_LVL_LOW);
    vd_g_Port_SetPinMode((U2)XPDI_PORT_RCAR_PRIM_EN_LO,   (U1)TRUE);

    vd_g_LComSpiInit();
    vd_g_Dio_WriteChannel((U2)DIO_CH_HUD_WAKE, (U1)DIO_LVL_LOW);
    vd_g_Dio_WriteChannel((U2)DIO_CH_DISP_WAKE, (U1)DIO_LVL_LOW);
}
/*===================================================================================================================================*/
/*  void    vd_g_XpdiCfgWkupInit(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XpdiCfgWkupInit(void)
{
    u1_s_xpdi_rcar_mon_act = (U1)XPDI_RCAR_MON_LO_VOLT;
    u1_s_xpdi_rcar_fdrqst  = (U1)0x00U;
    u1_s_xpdi_bmoni_sts    = (U1)XPDI_VOL_UNKNWN;
    u1_s_xpdi_igmoni_sts   = (U1)XPDI_VOL_UNKNWN;
    u1_s_xpdi_gdc_bomi_lo  = (U1)FALSE;
    u1_s_xpdi_pmic_vin_sts = (U1)XPDI_VOL_UNKNWN;
    u1_s_xpdi_pmic_int_sts = (U1)XPDI_VOL_UNKNWN;
	u1_s_xpdi_ota_rstrqst  = (U1)FALSE;

    vd_g_Rim_WriteU1((U2)RIMID_U1_XPDI_RCAR_RFLSH, (U1)DIO_LVL_HIGH);

    vd_g_Dio_WriteChannel((U2)XPDI_DIO_PMIC_EN, (U1)DIO_LVL_LOW);
    vd_g_Port_SetPinMode((U2)XPDI_PORT_RCAR_PRIM_EN_LO,   (U1)TRUE);

    vd_g_LComSpiInit();
    vd_g_Dio_WriteChannel((U2)DIO_CH_HUD_WAKE, (U1)DIO_LVL_LOW);
    vd_g_Dio_WriteChannel((U2)DIO_CH_DISP_WAKE, (U1)DIO_LVL_LOW);
}
/*===================================================================================================================================*/
/*  void    vd_g_XpdiCfgDeInit(const U1 u1_a_CTRL, const U2 u2_a_STEPCNT)                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XpdiCfgDeInit(const U1 u1_a_CTRL, const U2 u2_a_STEPCNT)
{
    vd_g_LComSpiDeInit();

    vd_g_Dio_WriteChannel((U2)XPDI_DIO_PMIC_EN, (U1)DIO_LVL_LOW);
    vd_g_Port_SetPinMode((U2)XPDI_PORT_RCAR_PRIM_EN_LO,   (U1)TRUE);

    vd_g_Dio_WriteChannel((U2)DIO_CH_HUD_WAKE, (U1)DIO_LVL_LOW);
    vd_g_Dio_WriteChannel((U2)DIO_CH_DISP_WAKE, (U1)DIO_LVL_LOW);
}
/*===================================================================================================================================*/
/*  void    vd_g_XpdiCfgPreTask(const U1 u1_a_CTRL, const U2 u2_a_STEPCNT)                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XpdiCfgPreTask(const U1 u1_a_CTRL, const U2 u2_a_STEPCNT)
{
    U4                u4_tp_ss[ESI_SSC_SS_NWORD];
    U1                u1_t_rcar_chk;
    U1                u1_t_rim_reflash;
    U1                u1_t_rim_chk;
    U1                u1_t_dio_reflash;
    U1                u1_t_lcom_spi;
    U2                u2_tp_lcom[LCOM_SPI_NUM_CH];


    u4_tp_ss[ESI_SSC_W0_MISC] = (U4)0U;
    u4_tp_ss[ESI_SSC_W1_LCOM] = (U4)0U;
    u2_tp_lcom[LCOM_SPI_CH_0] = (U2)0U;
    u2_tp_lcom[LCOM_SPI_CH_1] = (U2)0U;

    u1_t_rcar_chk = u1_s_XpdiRCarLvdchk(&u4_tp_ss[ESI_SSC_W0_MISC]);
/*@@@ 310D provisional @@@*/
    u1_t_lcom_spi = u1_g_LComSpiGetComSts();
    if(u1_t_lcom_spi == (U1)TRUE){
        u1_t_rcar_chk             |= (U1)XPDI_RCAR_MON_LCOM_SPI;
/*        u4_tp_ss[ESI_SSC_W1_LCOM]  = (U4)u2_tp_lcom[LCOM_SPI_CH_0];*/
/*        u4_tp_ss[ESI_SSC_W1_LCOM] |= (U4)u2_tp_lcom[LCOM_SPI_CH_1] << XPDI_HARF_SHIFT;*/
    }
/*@@@ 310D provisional @@@*/

    u1_t_rim_reflash = (U1)DIO_LVL_HIGH;
    u1_t_rim_chk     = u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_XPDI_RCAR_RFLSH, &u1_t_rim_reflash) & (U1)RIM_RESULT_KIND_MASK;
    u1_t_dio_reflash = u1_g_Dio_ReadChannel((U2)XPDI_DIO_RCAR_URPG_EN);                    /* RCAR_REFLASH_EN */
    if((u1_t_rim_reflash == (U1)DIO_LVL_LOW  ) &&
       (u1_t_rim_chk     == (U1)RIM_RESULT_OK) &&
       (u1_t_dio_reflash == (U1)DIO_LVL_LOW  )){

        u1_t_rcar_chk = (U1)0U;
    }
    else{
        vd_g_Rim_WriteU1((U2)RIMID_U1_XPDI_RCAR_RFLSH, (U1)DIO_LVL_HIGH);
    }

    u1_t_rcar_chk &= u1_s_xpdi_rcar_mon_act;
    if(u1_t_rcar_chk >= (U1)XPDI_RCAR_MON_LVD_PMV){

        u1_s_xpdi_rcar_fdrqst = (U1)XPDI_ABO_RQST_ACT | (U1)XPDI_ABO_RQST_CNT;
        vd_g_ESISscEvDtct(&u4_tp_ss[0]);
    }
    else if(u1_t_rcar_chk >= (U1)XPDI_RCAR_MON_LCOM_SPI){

        u1_s_xpdi_rcar_fdrqst = (U1)XPDI_ABO_RQST_ACT;
        vd_g_ESISscEvDtct(&u4_tp_ss[0]);
    }
    else if(u1_t_rcar_chk >= (U1)XPDI_RCAR_MON_LO_VOLT){
        u1_s_xpdi_rcar_fdrqst = (U1)XPDI_ABO_RQST_ACT;
    }
    else{
        u1_s_xpdi_rcar_fdrqst = (U1)0x00U;
    }
    vd_s_XpdiHudEnSet();
}
/*===================================================================================================================================*/
/*  U1      u1_g_XpdiCfgAboRqst(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_XpdiCfgAboRqst(void)
{
    return(u1_s_xpdi_rcar_fdrqst);
}
/*===================================================================================================================================*/
/*  void    vd_g_XpdiCfgPostTask(const U1 u1_a_CTRL, const U2 u2_a_STEPCNT)                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/ 
void    vd_g_XpdiCfgPostTask(const U1 u1_a_CTRL, const U2 u2_a_STEPCNT)
{
}
/*===================================================================================================================================*/
/*  U1      u1_g_XpdiCfgPmicOn(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         U1 u1_t_pmicon_event PMIC_VIN_MONI=HI:XPDI event XPDI_EAS_CHK_PMIC_ON                                            */
/*===================================================================================================================================*/
U1      u1_g_XpdiCfgPmicOn(void)
{
    U1                u1_t_pmicon_event;

    if(u1_s_xpdi_pmic_vin_sts == (U1)XPDI_VOL_NML){
        u1_t_pmicon_event = (U1)XPDI_EVNT_PMIC_ON;
    }
    else{
        u1_t_pmicon_event = (U1)0U;
    }

    return(u1_t_pmicon_event);
}

/*===================================================================================================================================*/
/*  void    vd_g_XpdiCfgGdcLoEdge(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XpdiCfgGdcLoEdge(void)
{
    /* GDC+B_MONI Lo Edge Interrupt Stop */
    vd_g_Gpt_J32Stop((U1)XPDI_GPT_LOEDGE_CH);

    /* GDC+B_MONI 300us Timer Interrupt Start */
    vd_g_Gpt_B16Start((U1)XPDI_GPT_WAIT_CH, &u2_sp_WAIT_START[0]);
}

/*===================================================================================================================================*/
/*  void    vd_g_XpdiCfgGdcLvdchk(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XpdiCfgGdcLvdchk(void)
{
    U1                u1_t_lvd_chk;

    /* GDC+B_MONI 300us Timer Interrupt Stop */
    vd_g_Gpt_B16Stop((U1)XPDI_GPT_WAIT_CH);

    u1_t_lvd_chk = u1_g_Dio_ReadChannel((U2)XPDI_DIO_RCAR_GDC_BMONI);
    if(u1_t_lvd_chk == (U1)DIO_LVL_LOW){
        u1_s_xpdi_gdc_bomi_lo  = (U1)TRUE;

    }
    else{
        u1_s_xpdi_gdc_bomi_lo  = (U1)FALSE;
        /* GDC+B_MONI Lo Edge Interrupt Start */
        vd_g_Gpt_J32Start((U1)XPDI_GPT_LOEDGE_CH, &u4_sp_GDCB_LO_START[0]);
    }
}

/*===================================================================================================================================*/
/*  static U1      u1_s_XpdiRCarLvdchk(U4 * u4_ap_ss)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_XpdiRCarLvdchk(U4 * u4_ap_ss)
{
    volatile U4       u4_t_gli;
    U1                u1_t_rcar_chk;
    U1                u1_t_lvd_chk;

    vd_s_XpdiBmoniJdg();
    vd_s_XpdiIgmoniJdg();
    if((u1_s_xpdi_bmoni_sts  == (U1)XPDI_VOL_NML) ||
       (u1_s_xpdi_igmoni_sts == (U1)XPDI_VOL_NML)){
        u1_t_rcar_chk  = (U1)0U;
    }
    else{
        u1_t_rcar_chk  = (U1)XPDI_RCAR_MON_LO_VOLT;
    }

    u4_t_gli     = u4_g_XpdiCfg_DI(); /* Disable Interrupts */
    u1_t_lvd_chk = u1_s_XpdiGdcBJdg();
    vd_g_XpdiCfg_EI(u4_t_gli);    /* Enable Interrrupts */
    if(u1_t_lvd_chk == (U1)TRUE){
        u1_t_rcar_chk |= (U1)XPDI_RCAR_MON_LVD_BAT;
        (*u4_ap_ss)   |= (U4)ESI_SSC_MISC_LVD_BAT;
    }

    vd_s_XpdiPmvJdg();
    if(u1_s_xpdi_pmic_vin_sts == (U1)XPDI_VOL_LOW){
        u1_t_rcar_chk |= (U1)XPDI_RCAR_MON_LVD_PMV;
        (*u4_ap_ss)   |= (U4)ESI_SSC_MISC_LVD_PMV;
    }

    vd_s_XpdiPmiJdg();
    if(u1_s_xpdi_pmic_int_sts == (U1)XPDI_VOL_LOW){
        u1_t_rcar_chk |= (U1)XPDI_RCAR_MON_LVD_PMI;
        (*u4_ap_ss)   |= (U4)ESI_SSC_MISC_LVD_PMI;
    }

    return(u1_t_rcar_chk);
}
/*===================================================================================================================================*/
/*  static void    vd_s_XpdiRCarPwrOn(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XpdiRCarPwrOn(void)
{
    u1_s_xpdi_rcar_mon_act = (U1)XPDI_RCAR_MON_LVD_BAT | (U1)XPDI_RCAR_MON_LVD_PMV;

    /* ---------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                    */
    /* ---------------------------------------------------------------------------------------------- */
    /* XPDI_PORT_RCAR_PMIC_RST_ACT is being set in vd_s_XpdiRCarPwrOff.                               */
    /* vd_s_XpdiRCarPwrOff is being invoked if xpd_init is in XPDI_CTRL_STS_OFF.                      */
    /* ---------------------------------------------------------------------------------------------- */
 /* vd_g_Dio_WriteChannel((U2)XPDI_DIO_PMIC_EN, (U1)DIO_LVL_LOW); */
    vd_g_Port_SetPinMode((U2)XPDI_PORT_RCAR_PRIM_EN_HI,   (U1)TRUE);

    /* GDC+B_MONI Lo Edge Interrupt Start */
    vd_g_Gpt_J32Start((U1)XPDI_GPT_LOEDGE_CH, &u4_sp_GDCB_LO_START[0]);

    vd_g_Dio_WriteChannel((U2)DIO_CH_DISP_WAKE, (U1)DIO_LVL_HIGH);
}
/*===================================================================================================================================*/
/*  static void    vd_s_XpdiRCarLComRun(void)                                                                                        */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XpdiRCarLComRun(void)
{
    u1_s_xpdi_rcar_mon_act = (U1)XPDI_RCAR_MON_LCOM_SPI | (U1)XPDI_RCAR_MON_LVD_BAT | (U1)XPDI_RCAR_MON_LVD_PMV | (U1)XPDI_RCAR_MON_LVD_PMI;

    vd_g_Dio_WriteChannel((U2)XPDI_DIO_PMIC_EN, (U1)DIO_LVL_HIGH);

    /* ---------------------------------------------------------------------------------------------- */
    /* Attention :                                                                                    */
    /* ---------------------------------------------------------------------------------------------- */
    /* XPDI_PORT_RCAR_PRIM_EN_HI is not being set intentionally since low voltage detection is enabled. */
    /* ---------------------------------------------------------------------------------------------- */
 /* vd_g_Port_SetPinMode((U2)XPDI_PORT_RCAR_PRIM_EN_HI,   (U1)TRUE); */
}
/*===================================================================================================================================*/
/*  static void    vd_s_XpdiRCarDeAct(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XpdiRCarDeAct(void)
{
    u1_s_xpdi_rcar_mon_act = (U1)XPDI_RCAR_MON_LO_VOLT;
    vd_g_LComSpiDeInit();

    vd_g_Dio_WriteChannel((U2)XPDI_DIO_PMIC_EN, (U1)DIO_LVL_LOW);
    /* 310D Noise Sample                                                 */
    vd_g_LComSpiClearComSts();
    /* 310D Noise Sample                                                 */

    /* GDC+B_MONI Lo Edge & Timer Interrupt Stop */
    vd_g_Gpt_J32Stop((U1)XPDI_GPT_LOEDGE_CH);
    vd_g_Gpt_B16Stop((U1)XPDI_GPT_WAIT_CH);
}
/*===================================================================================================================================*/
/*  static void    vd_s_XpdiRCarPwrOff(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XpdiRCarPwrOff(void)
{
    u1_s_xpdi_rcar_mon_act = (U1)XPDI_RCAR_MON_LO_VOLT;
    u1_s_xpdi_ota_rstrqst  = (U1)FALSE;

    vd_g_Dio_WriteChannel((U2)XPDI_DIO_PMIC_EN, (U1)DIO_LVL_LOW);
    vd_g_Port_SetPinMode((U2)XPDI_PORT_RCAR_PRIM_EN_LO,   (U1)TRUE);
    vd_g_Dio_WriteChannel((U2)DIO_CH_DISP_WAKE, (U1)DIO_LVL_LOW);
}
/*===================================================================================================================================*/
/*  static void    vd_s_XpdiBmoniJdg(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XpdiBmoniJdg(void)
{
    U1                u1_t_bmoni_lo;
    U1                u1_t_bmoni_hi;

    u1_t_bmoni_lo = u1_g_IoHwDifltSwitch((U2)IOHW_DISGNL_B_MONI_6P7V_6);
    u1_t_bmoni_hi = u1_g_IoHwDifltSwitch((U2)IOHW_DISGNL_B_MONI_7P2V_6);

    if((u1_t_bmoni_lo == (U1)IOHW_DIFLT_SWITCH_INACT) && 
       (u1_t_bmoni_hi == (U1)IOHW_DIFLT_SWITCH_INACT)){
        u1_s_xpdi_bmoni_sts = (U1)XPDI_VOL_LOW;
    }
    else if((u1_t_bmoni_lo == (U1)IOHW_DIFLT_SWITCH_ACT) && 
            (u1_t_bmoni_hi == (U1)IOHW_DIFLT_SWITCH_ACT)){
        u1_s_xpdi_bmoni_sts = (U1)XPDI_VOL_NML;
    }
    else if((u1_t_bmoni_lo == (U1)IOHW_DIFLT_SWITCH_UNKNWN) && 
            (u1_t_bmoni_hi == (U1)IOHW_DIFLT_SWITCH_UNKNWN)){
        u1_s_xpdi_bmoni_sts = (U1)XPDI_VOL_UNKNWN;
    }
    else{
        /* Do nothing */
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_XpdiIgmoniJdg(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XpdiIgmoniJdg(void)
{
    U1                u1_t_igmoni_lo;
    U1                u1_t_igmoni_hi;

    u1_t_igmoni_lo = u1_g_IoHwDifltSwitch((U2)IOHW_DISGNL_IGN__6P7V_6);
    u1_t_igmoni_hi = u1_g_IoHwDifltSwitch((U2)IOHW_DISGNL_IGN__7P2V_6);

    if((u1_t_igmoni_lo == (U1)IOHW_DIFLT_SWITCH_INACT) && 
       (u1_t_igmoni_hi == (U1)IOHW_DIFLT_SWITCH_INACT)){
        u1_s_xpdi_igmoni_sts = (U1)XPDI_VOL_LOW;
    }
    else if((u1_t_igmoni_lo == (U1)IOHW_DIFLT_SWITCH_ACT) && 
            (u1_t_igmoni_hi == (U1)IOHW_DIFLT_SWITCH_ACT)){
        u1_s_xpdi_igmoni_sts = (U1)XPDI_VOL_NML;
    }
    else if((u1_t_igmoni_lo == (U1)IOHW_DIFLT_SWITCH_UNKNWN) && 
            (u1_t_igmoni_hi == (U1)IOHW_DIFLT_SWITCH_UNKNWN)){
        u1_s_xpdi_igmoni_sts = (U1)XPDI_VOL_UNKNWN;
    }
    else{
        /* Do nothing */
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_XpdiHudEnSet(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XpdiHudEnSet(void)
{
    U1                u1_t_igon;
    U1                u1_t_accon;
    U1                u1_t_baon;
    U1                u1_t_baofon;

    u1_t_igon   = u1_g_VehopemdIgnOn();
    u1_t_accon  = u1_g_VehopemdAccOn();
    u1_t_baon   = u1_g_VehopemdBaOn();
    u1_t_baofon = u1_g_VehopemdBaofOn();

    if((u1_t_igon  == (U1)TRUE) ||
       (u1_t_accon == (U1)TRUE) ||
       ((u1_t_baon  == (U1)TRUE) && (u1_t_baofon == (U1)FALSE))){
        vd_g_Dio_WriteChannel((U2)DIO_CH_HUD_WAKE, (U1)DIO_LVL_HIGH);
    }
    else{
        vd_g_Dio_WriteChannel((U2)DIO_CH_HUD_WAKE, (U1)DIO_LVL_LOW);
    }
}

/*===================================================================================================================================*/
/*  static U1      u1_s_XpdiGdcBJdg(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:        U1 u1_t_lvd_chk TRUE:GDC+B_MONI Lo detection                                                                      */
/*===================================================================================================================================*/
static U1      u1_s_XpdiGdcBJdg(void)
{
    U1                u1_t_lvd_chk;

    if(u1_s_xpdi_gdc_bomi_lo == (U1)TRUE){
        u1_t_lvd_chk          = (U1)TRUE;
        u1_s_xpdi_gdc_bomi_lo = (U1)FALSE;
    }
    else{
        u1_t_lvd_chk          = (U1)FALSE;
    }
    return(u1_t_lvd_chk);
}

/*===================================================================================================================================*/
/*  static void    vd_s_XpdiPmvJdg(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XpdiPmvJdg(void)
{
    U1                u1_t_pmic_vin_lo;
    U1                u1_t_pmic_vin_hi;

    u1_t_pmic_vin_lo = u1_g_IoHwDifltSwitch((U2)IOHW_DISGNL_PMIC_VIN_20);
    u1_t_pmic_vin_hi = u1_g_IoHwDifltSwitch((U2)IOHW_DISGNL_PMIC_VIN_6);

    if(u1_t_pmic_vin_lo == (U1)IOHW_DIFLT_SWITCH_ACT){
        u1_s_xpdi_pmic_vin_sts = (U1)XPDI_VOL_LOW;
    }
    else if(u1_t_pmic_vin_hi == (U1)IOHW_DIFLT_SWITCH_ACT){
        u1_s_xpdi_pmic_vin_sts = (U1)XPDI_VOL_NML;
    }
    else if((u1_t_pmic_vin_lo == (U1)IOHW_DIFLT_SWITCH_UNKNWN) && 
            (u1_t_pmic_vin_hi == (U1)IOHW_DIFLT_SWITCH_UNKNWN)){
        u1_s_xpdi_pmic_vin_sts = (U1)XPDI_VOL_UNKNWN;
    }
    else{
        /* Do nothing */
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_XpdiPmiJdg(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XpdiPmiJdg(void)
{
    U1                u1_t_pmic_int_lo;
    U1                u1_t_pmic_int_hi;

    u1_t_pmic_int_lo = u1_g_IoHwDifltSwitch((U2)IOHW_DISGNL_PMIC_INT_20);
    u1_t_pmic_int_hi = u1_g_IoHwDifltSwitch((U2)IOHW_DISGNL_PMIC_INT_6);

    if(u1_t_pmic_int_lo == (U1)IOHW_DIFLT_SWITCH_ACT){
        u1_s_xpdi_pmic_int_sts = (U1)XPDI_VOL_LOW;
    }
    else if(u1_t_pmic_int_hi == (U1)IOHW_DIFLT_SWITCH_ACT){
        u1_s_xpdi_pmic_int_sts = (U1)XPDI_VOL_NML;
    }
    else if((u1_t_pmic_int_lo == (U1)IOHW_DIFLT_SWITCH_UNKNWN) && 
            (u1_t_pmic_int_hi == (U1)IOHW_DIFLT_SWITCH_UNKNWN)){
        u1_s_xpdi_pmic_int_sts = (U1)XPDI_VOL_UNKNWN;
    }
    else{
        /* Do nothing */
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_XpdinitOtaActivateReq(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XpdinitOtaActivateReq(void)
{
	u1_s_xpdi_ota_rstrqst = (U1)TRUE;
}

/*===================================================================================================================================*/
/*  U1      u1_g_XpdinitOtaReqsts(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_XpdinitOtaReqsts(void)
{
    return(u1_s_xpdi_ota_rstrqst);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  1.0.0     6/22/2015  TN       New.                                                                                               */
/*  1.1.0     1/15/2016  TN       xpd_init v1.0.0 -> v1.1.0.                                                                         */
/*  1.2.0     2/28/2019  TN       xpd_init v1.1.0 -> v1.2.0.                                                                         */
/*  1.3.0     7/29/2020  TN       xpd_init v1.2.0 -> v1.3.0.                                                                         */
/*  2.0.0     6/10/2021  TN       xpd_init v1.3.0 -> v2.0.0.                                                                         */
/*  2.1.0     8/ 3/2021  TN       xpd_init v2.0.0 -> v2.1.0.                                                                         */
/*  2.2.0     5/30/2023  TN       xpd_init v2.1.0 -> v2.2.0.                                                                         */
/*  2.2.1    11/ 7/2023  KN       xpd_init v2.2.0 -> v2.2.1.                                                                         */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * KN   = Keigo Nomura , Denso Create                                                                                             */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  893B-1   10/25/2021  KM       Change config for 22-24FGM 893B 1A                                                                 */
/*  893B-2   11/15/2021  KM       Fix T8 timer & ABO_CNT_MAX value                                                                   */
/*  893B-3   11/22/2021  KM       Fix XPDI_STEP_TCP_LTM_STA at SEQ_OFF                                                               */
/*  19PFv3-1 02/15/2024  SN       Delete SPI_REQ Write process                                                                       */
/*  19PFv3-2 04/16/2024  RO       add port DISP_WAKE                                                                                 */
/*  19PFv3-3 05/24/2024  SM       Delete vd_g_GpLedInit, vd_g_GpLedDeInit                                                            */
/*                                                                                                                                   */
/*  * KM   = Kiichiro Morii, KSE                                                                                                     */
/*  * SN   = Shimon Nambu, Denso Techno                                                                                              */
/*  * RO   = Ryo Ohashi, KSE                                                                                                         */
/*  * SM   = Shota Maegawa, Denso Techno                                                                                             */
/*                                                                                                                                   */
/*===================================================================================================================================*/
