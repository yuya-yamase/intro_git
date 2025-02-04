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
#define XPD_INIT_C_MAJOR                         (2U)
#define XPD_INIT_C_MINOR                         (2U)
#define XPD_INIT_C_PATCH                         (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "xpd_init_cfg_private.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Version Check                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#if ((XPD_INIT_C_MAJOR != XPD_INIT_H_MAJOR) || \
     (XPD_INIT_C_MINOR != XPD_INIT_H_MINOR) || \
     (XPD_INIT_C_PATCH != XPD_INIT_H_PATCH))
#error "xpd_init.c and xpd_init.h : source and header files are inconsistent!"
#endif

#if ((XPD_INIT_C_MAJOR != XPD_INIT_CFG_H_MAJOR) || \
     (XPD_INIT_C_MINOR != XPD_INIT_CFG_H_MINOR) || \
     (XPD_INIT_C_PATCH != XPD_INIT_CFG_H_PATCH))
#error "xpd_init.c and xpd_init_cfg_private.h : source and header files are inconsistent!"
#endif

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define XPDI_RES_AT_OFF                          (0x5aa5a55aU)    /* reseted at off state            */
#define XPDI_RES_AT_OTH                          (0xffffffffU)    /* reseted at other than off state */

#define XPDI_EAS_CHK_SEQ_FIN                     (0x01U)
#define XPDI_EAS_CHK_SDR_ACT                     (0x02U)
#define XPDI_EAS_CHK_ABO_MAX                     (0x04U)
#define XPDI_EAS_CHK_ABO_REQ                     (0x08U)
#define XPDI_EAS_CHK_PMIC_ON                     (0x10U)

/* #define XPDI_CTRL_SEQ_OFF                        (0U)   OFF      */
/* #define XPDI_CTRL_SEQ_STA                        (1U)   STArt    */
/* #define XPDI_CTRL_SEQ_RUN                        (2U)   RUN      */
/* #define XPDI_CTRL_SEQ_SHU                        (3U)   SHUtdown */
/* #define XPDI_CTRL_SEQ_ABO                        (4U)   ABOrt    */
/* #define XPDI_CTRL_SEQ_RST_OFF                    (5U)   RST OFF  */
/* #define XPDI_CTRL_SEQ_RST_STA                    (6U)   RST STArt */
/* #define XPDI_CTRL_SEQ_UNK                        (255U)          */
#define XPDI_CTRL_NEX_TO_OFF                     (0x10U)
#define XPDI_CTRL_NEX_OFF                        (0x00U)
#define XPDI_CTRL_NEX_TO_STA                     (0x11U)
#define XPDI_CTRL_NEX_STA                        (0x01U)
#define XPDI_CTRL_NEX_TO_RUN                     (0x12U)
#define XPDI_CTRL_NEX_RUN                        (0x02U)
#define XPDI_CTRL_NEX_TO_SHU                     (0x13U)
#define XPDI_CTRL_NEX_SHU                        (0x03U)
#define XPDI_CTRL_NEX_TO_ABO                     (0x34U)
#define XPDI_CTRL_NEX_ABO                        (0x04U)
#define XPDI_CTRL_NEX_TO_RST_OFF                 (0x15U)
#define XPDI_CTRL_NEX_RST_OFF                    (0x05U)
#define XPDI_CTRL_NEX_TO_RST_STA                 (0x16U)
#define XPDI_CTRL_NEX_RST_STA                    (0x06U)

#define XPDI_CTRL_NEX_BIT_SEQ                    (0x0fU)   /* Sequence        */
#define XPDI_CTRL_NEX_BIT_INI                    (0x10U)   /* Initialization  */
#define XPDI_CTRL_NEX_BIT_ABC                    (0x20U)   /* Abort Countup   */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U4              u4_s_xpdi_res_at    __attribute__((section(".bss_BACK")));

static U4              u4_s_xpdi_lap_start;
static U4              u4_s_xpdi_lap_elpsd;

static U2              u2_s_xpdi_stepcnt;
static U2              u2_s_xpdi_sdr_tocnt;
static U1              u1_s_xpdi_ctrl;
static U1              u1_s_xpdi_abocnt;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1      u1_s_XpdiSdrTOchk(void);
static void    vd_s_XpdiLapElpsd(void);

static void    vd_s_XpdiSeqExe(const ST_XPDI_SEQ * st_ap_SEQ, const U4 u4_a_EXE);

static inline U1      u1_s_XpdiCtrlNex(const U1 u1_a_NEX, const U1 u1_a_ABO);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_XpdiRstInit(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XpdiRstInit(void)
{
    U4                        u4_t_bon;
    U4                        u4_t_reset;

    u4_s_xpdi_res_at    = (U4)XPDI_RES_AT_OTH;
    u4_s_xpdi_lap_start = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA);
    u4_s_xpdi_lap_elpsd = (U4)0U;

    u2_s_xpdi_stepcnt   = (U2)U2_MAX;
    u2_s_xpdi_sdr_tocnt = (U2)U2_MAX;

    u4_t_bon    = u4_g_XpdiCfgWkupReason() & (U4)XPDI_WKUP_BY_BATT_ON;
    u4_t_reset  = u4_g_XpdiCfgMcurstReason() & (U4)XPDI_RESET_BY_FIELDS;

    if(u1_g_XPDI_CTRL_RST != (U1)XPDI_CTRL_SEQ_OFF){
        u1_s_xpdi_ctrl  = (U1)XPDI_CTRL_SEQ_UNK;
    }
    else if((u4_t_bon   != (U4)0U              ) ||
            (u4_t_reset == (U4)XPDI_RESET_BY_EXT)){
        u1_s_xpdi_ctrl  = (U1)XPDI_CTRL_SEQ_RST_OFF;
    }
    else{
        u1_s_xpdi_ctrl  = (U1)XPDI_CTRL_SEQ_OFF;
    }
    u1_s_xpdi_abocnt    = (U1)0U;

    vd_g_XpdiCfgRstInit();
}
/*===================================================================================================================================*/
/*  void    vd_g_XpdiWkupInit(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XpdiWkupInit(void)
{
    if(u4_s_xpdi_res_at == (U4)XPDI_RES_AT_OFF){

        u4_s_xpdi_lap_start = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA);
        u4_s_xpdi_lap_elpsd = (U4)0U;

        u2_s_xpdi_stepcnt   = (U2)U2_MAX;
        u2_s_xpdi_sdr_tocnt = (U2)U2_MAX;
        u1_s_xpdi_ctrl      = (U1)XPDI_CTRL_SEQ_OFF;
        u1_s_xpdi_abocnt    = (U1)0U;

        vd_g_XpdiCfgWkupInit();
    }
    else{

        vd_g_XpdiRstInit();
    }
}
/*===================================================================================================================================*/
/*  void    vd_g_XpdiMainTask(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XpdiMainTask(void)
{
    static const U1           u1_sp_XPDI_CTRL_NEX[] = {
        (U1)XPDI_CTRL_NEX_TO_STA,     (U1)XPDI_CTRL_NEX_STA,        (U1)XPDI_CTRL_NEX_RUN,        (U1)XPDI_CTRL_NEX_SHU,        (U1)XPDI_CTRL_NEX_ABO,        (U1)XPDI_CTRL_NEX_TO_RST_STA, (U1)XPDI_CTRL_NEX_RST_STA,
        (U1)XPDI_CTRL_NEX_TO_STA,     (U1)XPDI_CTRL_NEX_STA,        (U1)XPDI_CTRL_NEX_TO_RUN,     (U1)XPDI_CTRL_NEX_TO_STA,     (U1)XPDI_CTRL_NEX_TO_STA,     (U1)XPDI_CTRL_NEX_TO_RST_STA, (U1)XPDI_CTRL_NEX_RST_STA,
        (U1)XPDI_CTRL_NEX_OFF,        (U1)XPDI_CTRL_NEX_STA,        (U1)XPDI_CTRL_NEX_TO_SHU,     (U1)XPDI_CTRL_NEX_SHU,        (U1)XPDI_CTRL_NEX_ABO,        (U1)XPDI_CTRL_NEX_RST_OFF,    (U1)XPDI_CTRL_NEX_RST_STA,
        (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_SHU,     (U1)XPDI_CTRL_NEX_TO_SHU,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_RST_OFF, (U1)XPDI_CTRL_NEX_TO_SHU,
        (U1)XPDI_CTRL_NEX_OFF,        (U1)XPDI_CTRL_NEX_STA,        (U1)XPDI_CTRL_NEX_RUN,        (U1)XPDI_CTRL_NEX_SHU,        (U1)XPDI_CTRL_NEX_ABO,        (U1)XPDI_CTRL_NEX_RST_OFF,    (U1)XPDI_CTRL_NEX_RST_STA,
        (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_STA,        (U1)XPDI_CTRL_NEX_TO_RUN,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_RST_OFF, (U1)XPDI_CTRL_NEX_RST_STA,
        (U1)XPDI_CTRL_NEX_OFF,        (U1)XPDI_CTRL_NEX_STA,        (U1)XPDI_CTRL_NEX_TO_SHU,     (U1)XPDI_CTRL_NEX_SHU,        (U1)XPDI_CTRL_NEX_ABO,        (U1)XPDI_CTRL_NEX_RST_OFF,    (U1)XPDI_CTRL_NEX_RST_STA,
        (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_SHU,     (U1)XPDI_CTRL_NEX_TO_SHU,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_RST_OFF, (U1)XPDI_CTRL_NEX_TO_SHU,
        (U1)XPDI_CTRL_NEX_OFF,        (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_SHU,        (U1)XPDI_CTRL_NEX_ABO,        (U1)XPDI_CTRL_NEX_RST_OFF,    (U1)XPDI_CTRL_NEX_TO_ABO,
        (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_RST_OFF, (U1)XPDI_CTRL_NEX_TO_ABO,
        (U1)XPDI_CTRL_NEX_OFF,        (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_SHU,        (U1)XPDI_CTRL_NEX_ABO,        (U1)XPDI_CTRL_NEX_RST_OFF,    (U1)XPDI_CTRL_NEX_TO_ABO,
        (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_RST_OFF, (U1)XPDI_CTRL_NEX_TO_ABO,
        (U1)XPDI_CTRL_NEX_OFF,        (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_SHU,        (U1)XPDI_CTRL_NEX_ABO,        (U1)XPDI_CTRL_NEX_RST_OFF,    (U1)XPDI_CTRL_NEX_TO_ABO,
        (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_RST_OFF, (U1)XPDI_CTRL_NEX_TO_ABO,
        (U1)XPDI_CTRL_NEX_OFF,        (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_SHU,        (U1)XPDI_CTRL_NEX_ABO,        (U1)XPDI_CTRL_NEX_RST_OFF,    (U1)XPDI_CTRL_NEX_TO_ABO,
        (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_RST_OFF, (U1)XPDI_CTRL_NEX_TO_ABO,
        (U1)XPDI_CTRL_NEX_TO_STA,     (U1)XPDI_CTRL_NEX_STA,        (U1)XPDI_CTRL_NEX_RUN,        (U1)XPDI_CTRL_NEX_SHU,        (U1)XPDI_CTRL_NEX_ABO,        (U1)XPDI_CTRL_NEX_TO_RST_STA, (U1)XPDI_CTRL_NEX_RST_STA,
        (U1)XPDI_CTRL_NEX_TO_STA,     (U1)XPDI_CTRL_NEX_TO_RUN,     (U1)XPDI_CTRL_NEX_TO_RUN,     (U1)XPDI_CTRL_NEX_TO_STA,     (U1)XPDI_CTRL_NEX_TO_STA,     (U1)XPDI_CTRL_NEX_TO_RST_STA, (U1)XPDI_CTRL_NEX_TO_RUN,
        (U1)XPDI_CTRL_NEX_OFF,        (U1)XPDI_CTRL_NEX_STA,        (U1)XPDI_CTRL_NEX_TO_SHU,     (U1)XPDI_CTRL_NEX_SHU,        (U1)XPDI_CTRL_NEX_ABO,        (U1)XPDI_CTRL_NEX_RST_OFF,    (U1)XPDI_CTRL_NEX_RST_STA,
        (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_SHU,     (U1)XPDI_CTRL_NEX_TO_SHU,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_RST_OFF, (U1)XPDI_CTRL_NEX_TO_SHU,
        (U1)XPDI_CTRL_NEX_OFF,        (U1)XPDI_CTRL_NEX_STA,        (U1)XPDI_CTRL_NEX_RUN,        (U1)XPDI_CTRL_NEX_SHU,        (U1)XPDI_CTRL_NEX_ABO,        (U1)XPDI_CTRL_NEX_RST_OFF,    (U1)XPDI_CTRL_NEX_RST_STA,
        (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_RUN,     (U1)XPDI_CTRL_NEX_TO_RUN,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_RST_OFF, (U1)XPDI_CTRL_NEX_TO_RUN,
        (U1)XPDI_CTRL_NEX_OFF,        (U1)XPDI_CTRL_NEX_STA,        (U1)XPDI_CTRL_NEX_TO_SHU,     (U1)XPDI_CTRL_NEX_SHU,        (U1)XPDI_CTRL_NEX_ABO,        (U1)XPDI_CTRL_NEX_RST_OFF,    (U1)XPDI_CTRL_NEX_RST_STA,
        (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_SHU,     (U1)XPDI_CTRL_NEX_TO_SHU,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_RST_OFF, (U1)XPDI_CTRL_NEX_TO_SHU,
        (U1)XPDI_CTRL_NEX_OFF,        (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_SHU,        (U1)XPDI_CTRL_NEX_ABO,        (U1)XPDI_CTRL_NEX_RST_OFF,    (U1)XPDI_CTRL_NEX_TO_ABO,
        (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_RST_OFF, (U1)XPDI_CTRL_NEX_TO_ABO,
        (U1)XPDI_CTRL_NEX_OFF,        (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_SHU,        (U1)XPDI_CTRL_NEX_ABO,        (U1)XPDI_CTRL_NEX_RST_OFF,    (U1)XPDI_CTRL_NEX_TO_ABO,
        (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_RST_OFF, (U1)XPDI_CTRL_NEX_TO_ABO,
        (U1)XPDI_CTRL_NEX_OFF,        (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_SHU,        (U1)XPDI_CTRL_NEX_ABO,        (U1)XPDI_CTRL_NEX_RST_OFF,    (U1)XPDI_CTRL_NEX_TO_ABO,
        (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_RST_OFF, (U1)XPDI_CTRL_NEX_TO_ABO,
        (U1)XPDI_CTRL_NEX_OFF,        (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_SHU,        (U1)XPDI_CTRL_NEX_ABO,        (U1)XPDI_CTRL_NEX_RST_OFF,    (U1)XPDI_CTRL_NEX_TO_ABO,
        (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_TO_ABO,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_OFF,     (U1)XPDI_CTRL_NEX_TO_RST_OFF, (U1)XPDI_CTRL_NEX_TO_ABO
    };

    volatile U4               u4_t_gli;
    U2                        u2_t_num_step;
    U1                        u1_t_abo_rqst;
    U1                        u1_t_eas_chk;
    U1                        u1_t_ctrl_nex;
    U1                        u1_t_pmicon;
	U1                        u1_t_ota_rstqst;

    vd_g_XpdiCfgPreTask(u1_s_xpdi_ctrl, u2_s_xpdi_stepcnt);

    if(u1_s_xpdi_ctrl < (U1)XPDI_CTRL_NUM_SEQ){

        u1_t_eas_chk = u1_s_XpdiSdrTOchk();
        if(u1_s_xpdi_abocnt >= u1_g_XPDI_ABO_CNT_MAX){
            u1_t_eas_chk |= (U1)XPDI_EAS_CHK_ABO_MAX;
        }

        vd_s_XpdiLapElpsd();

        vd_s_XpdiSeqExe(&st_gp_XPDI_SEQ[u1_s_xpdi_ctrl], (U4)XPDI_SEQ_EXE_1ST_W_EI);

        /* ------------------------------------------------------------------------------------------------------------------------- */
        u4_t_gli = u4_g_IRQ_DI(); /* Disable Interrupts */

        vd_s_XpdiSeqExe(&st_gp_XPDI_SEQ[u1_s_xpdi_ctrl], (U4)XPDI_SEQ_EXE_2ND_W_DI);

#if (XPDI_ABO_RQST_ACT != XPDI_EAS_CHK_ABO_REQ)
#error "xpd_init.c : XPDI_ABO_RQST_ACT shall be equal to XPDI_EAS_CHK_ABO_REQ."
#endif
        u1_t_abo_rqst  = u1_g_XpdiCfgAboRqst();
    	u1_t_ota_rstqst = u1_g_XpdinitOtaReqsts();
    	if(u1_t_ota_rstqst == (U1)TRUE){
    		u1_t_abo_rqst |= (U1)XPDI_ABO_RQST_ACT;
    	}
        u1_t_eas_chk  |= (u1_t_abo_rqst & (U1)XPDI_ABO_RQST_ACT);

        u2_t_num_step = st_gp_XPDI_SEQ[u1_s_xpdi_ctrl].u2_num_step;
        if(u2_s_xpdi_stepcnt >= u2_t_num_step){ 
            u1_t_eas_chk |= (U1)XPDI_EAS_CHK_SEQ_FIN;
        }
        /* PMIC_VIN_MONI=HI event */
#if (XPDI_EVNT_PMIC_ON != XPDI_EAS_CHK_PMIC_ON)
#error "xpd_init.c : XPDI_EVNT_PMIC_ON shall be equal to XPDI_EAS_CHK_PMIC_ON."
#endif
        u1_t_pmicon    = u1_g_XpdiCfgPmicOn();
        u1_t_eas_chk  |= (u1_t_pmicon & (U1)XPDI_EVNT_PMIC_ON);

        u1_t_ctrl_nex  = (u1_t_eas_chk * (U1)XPDI_CTRL_NUM_SEQ) + u1_s_xpdi_ctrl;
        u1_s_xpdi_ctrl = u1_s_XpdiCtrlNex(u1_sp_XPDI_CTRL_NEX[u1_t_ctrl_nex], u1_t_abo_rqst);

        vd_s_XpdiSeqExe(&st_gp_XPDI_SEQ[u1_s_xpdi_ctrl], (U4)XPDI_SEQ_EXE_3RD_W_DI);

        vd_g_IRQ_EI(u4_t_gli);    /* Enable Interrrupts */
        /* ------------------------------------------------------------------------------------------------------------------------- */
    }
    else{

        /* ------------------------------------------------------------------------------------------------------------------------- */
        u4_t_gli = u4_g_IRQ_DI(); /* Disable Interrupts */

        u1_s_xpdi_ctrl = u1_s_XpdiCtrlNex((U1)XPDI_CTRL_NEX_TO_ABO, (U1)0x00U);

        vd_s_XpdiSeqExe(&st_gp_XPDI_SEQ[u1_s_xpdi_ctrl], (U4)XPDI_SEQ_EXE_3RD_W_DI);

        vd_g_IRQ_EI(u4_t_gli);    /* Enable Interrrupts */
        /* ------------------------------------------------------------------------------------------------------------------------- */
    }

    vd_s_XpdiSeqExe(&st_gp_XPDI_SEQ[u1_s_xpdi_ctrl], (U4)XPDI_SEQ_EXE_4TH_W_EI);

    vd_g_XpdiCfgPostTask(u1_s_xpdi_ctrl, u2_s_xpdi_stepcnt);
}
/*===================================================================================================================================*/
/*  void    vd_g_XpdiDeInit(void)                                                                                                    */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XpdiDeInit(void)
{
    vd_g_XpdiCfgDeInit(u1_s_xpdi_ctrl, u2_s_xpdi_stepcnt);

    if(u1_s_xpdi_ctrl != (U1)XPDI_CTRL_SEQ_OFF){
        u2_s_xpdi_stepcnt = (U2)U2_MAX;
        u1_s_xpdi_ctrl    = (U1)XPDI_CTRL_SEQ_UNK;
    }
}
/*===================================================================================================================================*/
/*  U1      u1_g_XpdiAbocnt(const U1 u1_a_RTZ)                                                                                       */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_XpdiAbocnt(const U1 u1_a_RTZ)
{
    U1                        u1_t_abocnt;

    u1_t_abocnt = u1_s_xpdi_abocnt;
    if(u1_a_RTZ == (U1)TRUE){
        u1_s_xpdi_abocnt = (U1)0U;
    }

    return(u1_t_abocnt);
}
/*===================================================================================================================================*/
/*  U1      u1_g_XpdiShtdwnOk(const U1 u1_a_SHTDWN)                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_XpdiShtdwnOk(const U1 u1_a_SHTDWN)
{
    U1                        u1_t_ok;

    if(u1_a_SHTDWN != (U1)TRUE){
     /* Following statement is being intentionally commented out considering reprog use-case .*/
     /* u2_s_xpdi_sdr_tocnt = (U2)U2_MAX;                                                     */
        u1_t_ok             = (U1)FALSE;
    }
    else if((u1_s_xpdi_ctrl == (U1)XPDI_CTRL_SEQ_OFF    ) ||
            (u1_s_xpdi_ctrl == (U1)XPDI_CTRL_SEQ_RST_OFF)){
        u2_s_xpdi_sdr_tocnt = (U2)0U;
        u1_t_ok             = (U1)TRUE;
    }
    else{
        u2_s_xpdi_sdr_tocnt = (U2)0U;
        u1_t_ok             = (U1)FALSE;
    }

    return(u1_t_ok);
}
/*===================================================================================================================================*/
/*  U1      u1_g_XpdiIsRun(void)                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
U1      u1_g_XpdiIsRun(void)
{
    U1                        u1_t_run;

    if(u1_s_xpdi_ctrl == (U1)XPDI_CTRL_SEQ_RUN){
        u1_t_run = (U1)TRUE;
    }
    else{
        u1_t_run = (U1)FALSE;
    }

    return(u1_t_run);
}
/*===================================================================================================================================*/
/*  void    vd_g_XpdiGdcLoEdge(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XpdiGdcLoEdge(void)
{
    vd_g_XpdiCfgGdcLoEdge();
}

/*===================================================================================================================================*/
/*  void    vd_g_XpdiGdcLvdchk(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_XpdiGdcLvdchk(void)
{
    vd_g_XpdiCfgGdcLvdchk();
}
/*===================================================================================================================================*/
/*  static void    vd_s_XpdiLapElpsd(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XpdiLapElpsd(void)
{
    U4                u4_t_elpsd;

    /* Intentional wrap-around */
    u4_t_elpsd = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA) - u4_s_xpdi_lap_start;
    if(u4_g_XPDI_FRT_TO_LAPTM > (U4)0U){
        u4_t_elpsd /= u4_g_XPDI_FRT_TO_LAPTM;
    }

    if(u4_t_elpsd >= (U4)XPDI_STEP_TCP_LAP_MIN){
        u4_s_xpdi_lap_elpsd = (U4)XPDI_STEP_TCP_LAP_MIN;
    }
    else if(u4_t_elpsd >= u4_s_xpdi_lap_elpsd){
        u4_s_xpdi_lap_elpsd = u4_t_elpsd;
    }
    else{
        /* keep last */
    }
}
/*===================================================================================================================================*/
/*  static U1      u1_s_XpdiSdrTOchk(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1      u1_s_XpdiSdrTOchk(void)
{
    U1                        u1_t_eas_chk;

    if(u2_s_xpdi_sdr_tocnt < (U2)U2_MAX){
        u2_s_xpdi_sdr_tocnt++;
    }

    if(u2_s_xpdi_sdr_tocnt < u2_g_XPDI_SDR_TOUT){
        u1_t_eas_chk = (U1)XPDI_EAS_CHK_SDR_ACT;
    }
    else{
        u1_t_eas_chk = (U1)0U;
    }

    return(u1_t_eas_chk);
}
/*===================================================================================================================================*/
/*  static void    vd_s_XpdiSeqExe(const ST_XPDI_SEQ * st_ap_SEQ, const U4 u4_a_EXE)                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_XpdiSeqExe(const ST_XPDI_SEQ * st_ap_SEQ, const U4 u4_a_EXE)
{
    const ST_XPDI_STEP *      st_tp_STEP;
    U4                        u4_t_elpsd;
    U4                        u4_t_tcpbit;
    U4                        u4_t_lap_min;
    U4                        u4_t_seq_exe;

    U2                        u2_t_num_step;
    U2                        u2_t_step_cnt;

    st_tp_STEP    = st_ap_SEQ->stp_STEP;
    u2_t_num_step = st_ap_SEQ->u2_num_step;
    if((u2_t_num_step >  (U2)0U    ) &&
       (st_tp_STEP    != vdp_PTR_NA)){

        u4_t_elpsd    = u4_s_xpdi_lap_elpsd;
        u2_t_step_cnt = u2_s_xpdi_stepcnt;

        while(u2_t_step_cnt < u2_t_num_step){

            u4_t_tcpbit  = st_tp_STEP[u2_t_step_cnt].u4_tcpbit;
            u4_t_seq_exe = u4_t_tcpbit & (U4)XPDI_STEP_TCP_SEQ_EXE;
            u4_t_lap_min = u4_t_tcpbit & (U4)XPDI_STEP_TCP_LAP_MIN;

            if((u4_a_EXE   != u4_t_seq_exe) ||
               (u4_t_elpsd <  u4_t_lap_min)){
                break; /* while(u2_t_step_cnt < u2_t_num_step){ */
            }

            if(st_tp_STEP[u2_t_step_cnt].fp_vd_STEP != vdp_PTR_NA){
                (*st_tp_STEP[u2_t_step_cnt].fp_vd_STEP)();
            }

            if(u4_t_tcpbit >= (U4)XPDI_STEP_TCP_LTM_STA){
                u4_s_xpdi_lap_start = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA);
                u4_s_xpdi_lap_elpsd = (U4)0U;
                u4_t_elpsd          = (U4)0U;
            }

            u2_t_step_cnt++;
        }
    }
    else{
        u2_t_step_cnt = u2_t_num_step;
    }

    u2_s_xpdi_stepcnt = u2_t_step_cnt;
}
/*===================================================================================================================================*/
/*  static inline U1      u1_s_XpdiCtrlNex(const U1 u1_a_NEX, const U1 u1_a_ABO)                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static inline U1      u1_s_XpdiCtrlNex(const U1 u1_a_NEX, const U1 u1_a_ABO)
{
    U1                        u1_t_bit;

    u1_t_bit = u1_a_NEX & (U1)XPDI_CTRL_NEX_BIT_INI;
    if(u1_t_bit != (U1)0U){
        u4_s_xpdi_lap_start = u4_g_Gpt_FrtGetUsElapsed(vdp_PTR_NA);
        u4_s_xpdi_lap_elpsd = (U4)0U;
        u2_s_xpdi_stepcnt   = (U2)0U;
    }

    u1_t_bit = (u1_a_NEX & u1_a_ABO) & (U1)XPDI_ABO_RQST_CNT;
    if((u1_t_bit         != (U1)0U    ) &&
       (u1_s_xpdi_abocnt <  (U1)U1_MAX)){
        u1_s_xpdi_abocnt++;
    }

    u1_t_bit = u1_a_NEX & (U1)XPDI_CTRL_NEX_BIT_SEQ;
    if(u1_t_bit == (U1)XPDI_CTRL_SEQ_OFF){
        u4_s_xpdi_res_at = (U4)XPDI_RES_AT_OFF;
    }
    else{
        u4_s_xpdi_res_at = (U4)XPDI_RES_AT_OTH;
    }

    return(u1_t_bit);
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
/*  1.1.0     1/15/2016  TN       u4_XPDI_GL_DI->u4_g_XpdiCfg_DI, vd_XPDI_GL_EI->vd_g_XpdiCfg_EI.                                    */
/*  1.2.0     2/28/2019  TN       Bug Fix : The return of u1_g_XpdiShtdwnOk could be TRUE even if the parameter u1_a_SHTDWN = FALSE. */
/*  1.3.0     7/29/2020  TN       Improvement : u1_g_XpdiCfgFaildwnchk -> u1_g_XpdiCfgFaildwnRqst.                                   */
/*  2.0.0     6/10/2021  TN       Potential Bug Fix : The timing might not be met since Free-run timer was used.                     */
/*  2.1.0     8/ 3/2021  TN       Bug Fix : u4_t_tcpbit was not updated as st_tp_STEP[u2_s_xpdi_stepcnt].u4_tcpbit was configured.   */
/*  2.2.0     5/30/2023  TN       Bug Fix : vd_g_XpdiRstInit was NOT invoked when software reset was performed at esinspect          */

/*                                deactivatation.                                                                                    */
/*  2.2.1    11/ 7/2023  KN       Improvement : Warning MISRA-C-Rule7.2 and QAC warning CERT-INT30 was fixed.                        */
/*                                                                                                                                   */
/*  * TN   = Takashi Nagai, Denso                                                                                                    */
/*  * KN   = Keigo Nomura , Denso Create                                                                                             */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  893B-1   10/25/2021  KM       Change config for 22-24FGM 893B 1A                                                                 */
/*                                                                                                                                   */
/*  * KM   = Kiichiro Morii, KSE                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
