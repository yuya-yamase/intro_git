/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "CXD4937Ctl.h"

#include "Dio.h"
#include "gpi2c_ma.h"
#include "Mcu_I2c_Ctrl_private.h"
#include "gvif3tx.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GVIFSENDER_TASK_TIME                (1U)

#define GVIFSENDER_SEQ_IDLE                 (0U)
#define GVIFSENDER_SEQ_CYC                  (1U)
#define GVIFSENDER_SEQ_DEVRST               (2U)
#define GVIFSENDER_SEQ_LINKCHK              (3U)

#define GVIFSNDR_CYCCHK_STEP0               (0U)
#define GVIFSNDR_CYCCHK_STEP1               (1U)
#define GVIFSNDR_CYCCHK_STEP2               (2U)
#define GVIFSNDR_CYCCHK_STEP3               (3U)
#define GVIFSNDR_CYCCHK_STEP4               (4U)
#define GVIFSNDR_CYCCHK_STEP5               (5U)
#define GVIFSNDR_CYCCHK_STEP6               (6U)
#define GVIFSNDR_CYCCHK_STEP7               (7U)
#define GVIFSNDR_CYCCHK_STEP8               (8U)
#define GVIFSNDR_CYCCHK_STEP9               (9U)
#define GVIFSNDR_CYCCHK_STEP10              (10U)
#define GVIFSNDR_CYCCHK_STEP11              (11U)
#define GVIFSNDR_CYCCHK_STEP12              (12U)
#define GVIFSNDR_CYCCHK_STEP13              (13U)
#define GVIFSNDR_CYCCHK_STEP14              (14U)
#define GVIFSNDR_CYCCHK_STEP15              (15U)
#define GVIFSNDR_CYCCHK_STEP16              (16U)
#define GVIFSNDR_CYCCHK_STEP17              (17U)
#define GVIFSNDR_CYCCHK_STEP18              (18U)
#define GVIFSNDR_CYCCHK_STEP19              (19U)
#define GVIFSNDR_CYCCHK_STEP20              (20U)
#define GVIFSNDR_CYCCHK_STEP21              (21U)
#define GVIFSNDR_CYCCHK_STEP22              (22U)
#define GVIFSNDR_CYCCHK_STEP23              (23U)
#define GVIFSNDR_CYCCHK_STEP24              (24U)
#define GVIFSNDR_CYCCHK_STEP25              (25U)
#define GVIFSNDR_CYCCHK_STEP26              (26U)
#define GVIFSNDR_CYCCHK_STEP27              (27U)
#define GVIFSNDR_CYCCHK_STEP28              (28U)

#define CXD4937_BANKSET_WRINUM              (1U)
#define CXD4937_GVIFSNDRHDCPSTOP_WRINUM     (4U)
#define CXD4957_GVIFSNDRERRCLEAR_SET_WRINUM (1U)
#define CXD4937_GVIFSNDREDPERR_SET1_WRINUM  (2U)
#define CXD4937_GVIFSNDREDPERR_SET2_WRINUM  (1U)

#define GVIFSENDER_DEVRST_STEP0             (0U)
#define GVIFSENDER_DEVRST_STEP1             (1U)

#define GVIFSENDER_LINKCHK_STEP0            (0U)
#define GVIFSENDER_LINKCHK_STEP1            (1U)
#define GVIFSENDER_LINKCHK_STEP2            (2U)
#define GVIFSENDER_LINKCHK_STEP3            (3U)
#define GVIFSENDER_LINKCHK_STEP4            (4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_gvifsnd_state;                           /* GVIF Sender State */

static U2 u2_s_gvifsnd_regstep;                         /* GVIF Sender Register Request Step */
static U4 u4_s_gvifsnd_i2c_ack_wait_time;               /* GVIF Sender I2C Request Ack Wait Timer */
static U2 u2_s_gvifsnd_reg_btwn_time;                   /* GVIF Sender Access Register Between Timer */

static U1 u1_s_gvifsnd_cycchk_sts;                      /* GVIF Sender Cycle Check Process Status */
static U2 u2_s_gvifsnd_cycchk_timer;                    /* GVIF Sender Cycle Check Poling Timer */

static U1 u1_s_gvifsnd_devrst_sts;                      /* GVIF Sender Device Reset Status */
static U2 u2_s_gvifsnd_devrst_timer;                    /* GVIF Sender Device Reset Wait Timer */
static U1 u1_s_gvifsnd_devrst_drec_cnt;                 /* GVIF Sender Device Reset Drec Counter */

static U1 u1_s_gvifsnd_linkchk_sts;                     /* GVIF Sender Link Check Status */
static U2 u2_s_gvifsnd_linkchk_timer;                   /* GVIF Sender Link Check Wait Timer */
static U1 u1_s_gvifsnd_linkchk_err_cnt;                 /* GVIF Sender Link Check Error Counter */

static U1 u1_s_gvifsnd_edperr1_pre_sts;                 /* GVIF Sender eDP Input LANE0/1 Error Previous Status */
static U1 u1_s_gvifsnd_edperr1_drec_cnt;                /* GVIF Sender eDP Input LANE0/1 Error Drec Counter */
static U1 u1_s_gvifsnd_edperr2_pre_sts;                 /* GVIF Sender eDP Input LANE2/3 Error Previous Status */
static U1 u1_s_gvifsnd_edperr2_drec_cnt;                /* GVIF Sender eDP Input LANE2/3 Error Drec Counter */
static U1 u1_s_gvifsnd_edperr3_pre_sts;                 /* GVIF Sender eDP Input Skew Adjustment Error Previous Status */
static U1 u1_s_gvifsnd_edperr3_drec_cnt;                /* GVIF Sender eDP Input Skew Adjustment Error Drec Counter */
static U1 u1_s_gvifsnd_videoerr_drec_cnt;               /* GVIF Sender Input Video Error Drec Counter */
static U1 u1_s_gvifsnd_loadererr_drec_cnt;              /* GVIF Sender Loader Error Drec Counter */
static U1 u1_s_gvifsnd_cncterr_drec_cnt;                /* GVIF Sender Connection Error Drec Counter */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_Pict_GvifSndrTimChk(const U2 u2_a_tim_cnt, const U2 u2_a_wait_tim);
static void vd_s_Pict_GvifSndrCycChk(void);
static void vd_s_Pict_GvifSndrDevRst(void);
static void vd_s_Pict_GvifSndrGvifLinkChk(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_REG_WRI_REQ CXD4937_BANKSET[CXD4937_BANKSET_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};

static const ST_REG_WRI_REQ CXD4937_BANKSET_WAIT_7MS[CXD4937_BANKSET_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         7 / GVIFSENDER_TASK_TIME}        /* 7ms wait */
};

static const ST_REG_WRI_REQ CXD4937_GVIFSNDRHDCPSTOP[CXD4937_GVIFSNDRHDCPSTOP_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         7 / GVIFSENDER_TASK_TIME},       /* 7ms wait */
    {        1,         1,         7 / GVIFSENDER_TASK_TIME},       /* 7ms wait */
    {        2,         1,         20 / GVIFSENDER_TASK_TIME},      /* 20ms wait */
    {        3,         1,         7 / GVIFSENDER_TASK_TIME}        /* 7ms wait */
};

static const ST_REG_WRI_REQ CXD4957_GVIFSNDRERRCLEAR_SET[CXD4957_GVIFSNDRERRCLEAR_SET_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         2,         0}
};

static const ST_REG_WRI_REQ CXD4937_GVIFSNDREDPERR_SET1[CXD4937_GVIFSNDREDPERR_SET1_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         3,         0},
    {        3,         1,         0}
};

static const ST_REG_WRI_REQ CXD4937_GVIFSNDREDPERR_SET2[CXD4937_GVIFSNDREDPERR_SET2_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};

const U1 u1_sp_CXD4957_GVIFSNDRBANK0_SET1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDRDEVERR_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x75U     /* Write Address */
};

U1 u1_sp_CXD4957_GVIFSNDRDEVERR_RD_PDU2[CXD4937_I2C_RWC_BYTE2];

const U1 u1_sp_CXD4957_GVIFSNDRLINKERR_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x11U     /* Write Address */
};

U1 u1_sp_CXD4957_GVIFSNDRLINKERR_RD_PDU2[CXD4937_I2C_RWC_BYTE2];

const U1 u1_sp_CXD4957_GVIFSNDRERRCLEAR_SET1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2EU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDRERRCLEAR_SET2[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4957_GVIFSNDRINPUTERR_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xE9U     /* Write Address */
};

U1 u1_sp_CXD4957_GVIFSNDRINPUTERR_RD_PDU2[CXD4937_I2C_RWC_BYTE2];

const U1 u1_sp_CXD4957_GVIFSNDRLODERERR_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U     /* Write Address */
};

U1 u1_sp_CXD4957_GVIFSNDRLODERERR_RD_PDU2[CXD4937_I2C_RWC_BYTE2];

const U1 u1_sp_CXD4957_GVIFSNDRCONNECTERR_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U     /* Write Address */
};

U1 u1_sp_CXD4957_GVIFSNDRCONNECTERR_RD_PDU2[CXD4937_I2C_RWC_BYTE2];

const U1 u1_sp_CXD4957_GVIFSNDRLINKCHK_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U     /* Write Address */
};

U1 u1_sp_CXD4957_GVIFSNDRLINKCHK_RD_PDU2[CXD4937_I2C_RWC_BYTE2];

const U1 u1_sp_CXD4937_GVIFSNDRBANK4_SET_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR1_1_SET_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR1_1_SET_PDU2[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR1_1_SET_PDU3[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR1_1_SET_PDU4[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR1_2_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x44U     /* Write Address */
};

U1 u1_sp_CXD4937_GVIFSNDREDPERR1_2_RD_PDU2[CXD4937_I2C_RWC_BYTE2];

const U1 u1_sp_CXD4937_GVIFSNDREDPERR1_3_SET_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR2_1_SET_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR2_1_SET_PDU2[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR2_1_SET_PDU3[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR2_1_SET_PDU4[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR2_2_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x44U     /* Write Address */
};

U1 u1_sp_CXD4937_GVIFSNDREDPERR2_2_RD_PDU2[CXD4937_I2C_RWC_BYTE2];

const U1 u1_sp_CXD4937_GVIFSNDREDPERR2_3_SET_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR3_1_SET_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR3_1_SET_PDU2[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR3_1_SET_PDU3[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR3_1_SET_PDU4[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDREDPERR3_2_RD_PDU1[CXD4937_I2C_RWC_BYTE2] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x44U     /* Write Address */
};

U1 u1_sp_CXD4937_GVIFSNDREDPERR3_2_RD_PDU2[CXD4937_I2C_RWC_BYTE2];

const U1 u1_sp_CXD4937_GVIFSNDREDPERR3_3_SET_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDRHDCPSTOP_SET_PDU1[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDRHDCPSTOP_SET_PDU2[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U,    /* Write Address */
    (U1)0x83U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDRHDCPSTOP_SET_PDU3[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x11U     /* Write Data */
};

const U1 u1_sp_CXD4937_GVIFSNDRHDCPSTOP_SET_PDU4[CXD4937_I2C_RWC_BYTE3] = {
    (U1)CXD4937_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDRBANK0_TBL[1] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRBANK0_SET1[0],
        (U4)0x30040003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDRDEVERR_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRDEVERR_RD_PDU1[0],
        (U4)0x30080002U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRDEVERR_RD_PDU2[0],
        (U4)0x300C0002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDRLINKERR_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRLINKERR_RD_PDU1[0],
        (U4)0x30100002U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRLINKERR_RD_PDU2[0],
        (U4)0x30140002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDRERRCLEAR_TBL[2] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRERRCLEAR_SET1[0],
        (U4)0x30180003U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRERRCLEAR_SET2[0],
        (U4)0x301C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDRINPUTERR_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRINPUTERR_RD_PDU1[0],
        (U4)0x30200002U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRINPUTERR_RD_PDU2[0],
        (U4)0x30240002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDRLODERERR_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRLODERERR_RD_PDU1[0],
        (U4)0x30280002U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRLODERERR_RD_PDU2[0],
        (U4)0x302C0002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDRCONNECTERR_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRCONNECTERR_RD_PDU1[0],
        (U4)0x30300002U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRCONNECTERR_RD_PDU2[0],
        (U4)0x30340002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4957_GVIFSNDRLINKCHK_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRLINKCHK_RD_PDU1[0],
        (U4)0x30380002U
    },
    {
        (U1 *)&u1_sp_CXD4957_GVIFSNDRLINKCHK_RD_PDU2[0],
        (U4)0x303C0002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4937_GVIFSNDRBANK4_TBL[1] = {
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDRBANK4_SET_PDU1[0],
        (U4)0x30400003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4937_GVIFSNDREDPERR1_1_TBL[4] = {
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR1_1_SET_PDU1[0],
        (U4)0x30440003U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR1_1_SET_PDU2[0],
        (U4)0x30480003U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR1_1_SET_PDU3[0],
        (U4)0x304C0003U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR1_1_SET_PDU4[0],
        (U4)0x30500003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4937_GVIFSNDREDPERR1_2_TBL[2] = {
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR1_2_RD_PDU1[0],
        (U4)0x30540002U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR1_2_RD_PDU2[0],
        (U4)0x30580002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4937_GVIFSNDREDPERR1_3_TBL[1] = {
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR1_3_SET_PDU1[0],
        (U4)0x305C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4937_GVIFSNDREDPERR2_1_TBL[4] = {
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR2_1_SET_PDU1[0],
        (U4)0x30600003U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR2_1_SET_PDU2[0],
        (U4)0x30640003U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR2_1_SET_PDU3[0],
        (U4)0x30680003U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR2_1_SET_PDU4[0],
        (U4)0x306C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4937_GVIFSNDREDPERR2_2_TBL[2] = {
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR2_2_RD_PDU1[0],
        (U4)0x30700002U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR2_2_RD_PDU2[0],
        (U4)0x30740002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4937_GVIFSNDREDPERR2_3_TBL[1] = {
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR2_3_SET_PDU1[0],
        (U4)0x30780003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4937_GVIFSNDREDPERR3_1_TBL[4] = {
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR3_1_SET_PDU1[0],
        (U4)0x307C0003U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR3_1_SET_PDU2[0],
        (U4)0x30800003U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR3_1_SET_PDU3[0],
        (U4)0x30840003U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR3_1_SET_PDU4[0],
        (U4)0x30880003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4937_GVIFSNDREDPERR3_2_TBL[2] = {
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR3_2_RD_PDU1[0],
        (U4)0x308C0002U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR3_2_RD_PDU2[0],
        (U4)0x30900002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4937_GVIFSNDREDPERR3_3_TBL[1] = {
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDREDPERR3_3_SET_PDU1[0],
        (U4)0x30940003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_CXD4937_GVIFSNDRHDCPSTOP_TBL[4] = {
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDRHDCPSTOP_SET_PDU1[0],
        (U4)0x30980003U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDRHDCPSTOP_SET_PDU2[0],
        (U4)0x309C0003U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDRHDCPSTOP_SET_PDU3[0],
        (U4)0x30A00003U
    },
    {
        (U1 *)&u1_sp_CXD4937_GVIFSNDRHDCPSTOP_SET_PDU4[0],
        (U4)0x30A40003U
    }
};

/*===================================================================================================================================*/
/*  void    vd_g_Pict_GvifSndrInit(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Pict_GvifSndrInit(void)
{
    u1_s_gvifsnd_state = (U1)GVIFSENDER_SEQ_IDLE;

    u2_s_gvifsnd_regstep = (U2)0U;
    u4_s_gvifsnd_i2c_ack_wait_time = (U4)0U;
    u2_s_gvifsnd_reg_btwn_time = (U2)0xFFFFU;

    u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP0;
    u2_s_gvifsnd_cycchk_timer = (U2)0U;

    u1_s_gvifsnd_devrst_sts = (U1)GVIFSENDER_DEVRST_STEP0;
    u2_s_gvifsnd_devrst_timer = (U2)0U;
    u1_s_gvifsnd_devrst_drec_cnt = (U1)0U;

    u1_s_gvifsnd_linkchk_sts = (U1)GVIFSENDER_LINKCHK_STEP0;
    u2_s_gvifsnd_linkchk_timer = (U2)0U;
    u1_s_gvifsnd_linkchk_err_cnt = (U1)0U;
    u1_s_gvifsnd_edperr1_pre_sts = (U1)CXD4937_EDPERR_STS_INIT;
    u1_s_gvifsnd_edperr1_drec_cnt = (U1)0U;
    u1_s_gvifsnd_edperr2_pre_sts = (U1)CXD4937_EDPERR_STS_INIT;
    u1_s_gvifsnd_edperr2_drec_cnt = (U1)0U;
    u1_s_gvifsnd_edperr3_pre_sts = (U1)CXD4937_EDPERR_STS_INIT;
    u1_s_gvifsnd_edperr3_drec_cnt = (U1)0U;
    u1_s_gvifsnd_videoerr_drec_cnt = (U1)0U;
    u1_s_gvifsnd_loadererr_drec_cnt = (U1)0U;
    u1_s_gvifsnd_cncterr_drec_cnt = (U1)0U;

    /*  データリード用テーブル初期化 */
    u1_sp_CXD4957_GVIFSNDRDEVERR_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_CXD4957_GVIFSNDRDEVERR_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_CXD4957_GVIFSNDRLINKERR_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_CXD4957_GVIFSNDRLINKERR_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_CXD4957_GVIFSNDRINPUTERR_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_CXD4957_GVIFSNDRINPUTERR_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_CXD4957_GVIFSNDRLODERERR_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_CXD4957_GVIFSNDRLODERERR_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_CXD4957_GVIFSNDRCONNECTERR_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_CXD4957_GVIFSNDRCONNECTERR_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_CXD4957_GVIFSNDRLINKCHK_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_CXD4957_GVIFSNDRLINKCHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_CXD4937_GVIFSNDREDPERR1_2_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_CXD4937_GVIFSNDREDPERR1_2_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_CXD4937_GVIFSNDREDPERR2_2_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_CXD4937_GVIFSNDREDPERR2_2_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_CXD4937_GVIFSNDREDPERR3_2_RD_PDU2[0] = (U1)CXD4937_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_CXD4937_GVIFSNDREDPERR3_2_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */
}

/*===================================================================================================================================*/
/*  void    vd_g_Pict_GvifSndrRoutine(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Pict_GvifSndrRoutine(void)
{
    /* Ack Wait Timer Countr Increment */
    if(u4_s_gvifsnd_i2c_ack_wait_time < (U4)U4_MAX){        /* 暫定 I2Cアクセス時にカウンタクリアされるため定期では常にカウントアップする */
        u4_s_gvifsnd_i2c_ack_wait_time++;
    }

    switch (u1_s_gvifsnd_state){
        case GVIFSENDER_SEQ_IDLE:                                       /* IDLE */
            /* Timer Clear */
            u2_s_gvifsnd_cycchk_timer = (U2)0;
            /* Power ON Check */
            if(Mcu_OnStep_GVIF3TX_OVRALL == (U1)PICT_CXD_PWRON_COMP){
                /* State Update */
                u1_s_gvifsnd_state = (U1)GVIFSENDER_SEQ_CYC;
                /* Timer Start */
                u2_s_gvifsnd_cycchk_timer++;
            }
            break;
        case GVIFSENDER_SEQ_CYC:                                        /* CYCLIC */
            /* GvifSender Cyc Check */
            vd_s_Pict_GvifSndrCycChk();
            break;
        case GVIFSENDER_SEQ_DEVRST:                                     /* DEVRST */
            /* GvifSender Device Reset Wait */
            vd_s_Pict_GvifSndrDevRst();
            break;
        case GVIFSENDER_SEQ_LINKCHK:                                    /* LINKCHK */
            /* GvifSender Link Check Wait */
            vd_s_Pict_GvifSndrGvifLinkChk();
            break;
        default:                                                        /* FAIL */
            /* State Reset */
            u1_s_gvifsnd_state = (U1)GVIFSENDER_SEQ_IDLE;
            /* Process Reset */
            u1_s_gvifsnd_devrst_sts = (U1)GVIFSENDER_DEVRST_STEP0;
            break;
    }
}

/*===================================================================================================================================*/
/*  U1    u1_s_Pict_GvifSndrTimChk(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u2_a_tim_cnt  :  Timer Count /  u2_a_wait_tim  :  Wait Time                                                      */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1 u1_s_Pict_GvifSndrTimChk(const U2 u2_a_tim_cnt, const U2 u2_a_wait_tim)
{
    U1  u1_t_ret;

    u1_t_ret = (U1)FALSE;
    if(u2_a_tim_cnt >= u2_a_wait_tim){
        u1_t_ret = (U1)TRUE;
    }

    return(u1_t_ret);
}


/*===================================================================================================================================*/
/*  void    vd_g_Pict_GvifSndrCycChk(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Pict_GvifSndrCycChk(void)
{   /* 暫定　I/Fメモ 100-4-7 定期監視制御 */
    static const U2     GVIFSENDER_CYCCHK_POLING = (U2)(250U / GVIFSENDER_TASK_TIME);   /* t9 min:250ms */

    U1      u1_t_time_chk_flg;
    U1      u1_t_reg_req_sts;                                       /* Register Read/Write Request Status */
    U1      u1_t_reg_read_result;                                   /* Register Read Result */

    switch (u1_s_gvifsnd_cycchk_sts){
        case GVIFSNDR_CYCCHK_STEP0:                                       /* STEP0 */
            u1_t_time_chk_flg = u1_s_Pict_GvifSndrTimChk(u2_s_gvifsnd_cycchk_timer, GVIFSENDER_CYCCHK_POLING);
            if(u1_t_time_chk_flg == (U1)TRUE){
                /* Timer Clear */
                u2_s_gvifsnd_cycchk_timer = (U2)0;

                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP1;
            }
            else{
                u2_s_gvifsnd_cycchk_timer++;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP1:                                         /* STEP1 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4937_BANKSET_WRINUM,
                                                           CXD4937_BANKSET, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4957_GVIFSNDRBANK0_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP2;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP2:                                         /* STEP2 */
        /* ----------100-4-7 定期監視制御 デバイス異常検知---------- */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4957_GVIFSNDRDEVERR_RD_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP3;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP3:                                         /* STEP3 */
            u1_t_reg_read_result = st_sp_CXD4957_GVIFSNDRDEVERR_RD_TBL[1].u1p_pdu[1];
            if(u1_t_reg_read_result != (U1)PICT_GVIFSNDRDEVERR_NML){                   /* Device Error */
                /* State Update */
                u1_s_gvifsnd_state = (U1)GVIFSENDER_SEQ_DEVRST;
                /* Device Restart */
                vd_s_Pict_GvifSndrDevRst();
                /* Process Reset */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP0;
            }
            else {
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP4;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP4:                                         /* STEP4 */
        /* ----------100-4-7 定期監視制御 GVIF3リンク切れ検知---------- */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4957_GVIFSNDRLINKERR_RD_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_reg_read_result = st_sp_CXD4957_GVIFSNDRLINKERR_RD_TBL[1].u1p_pdu[1];
                u1_t_reg_read_result &= (U1)PICT_CXD_REG_MASK_BIT_7;                        /* Get Link Error Result */
                if(u1_t_reg_read_result == (U1)PICT_GVIFSNDRGVIFLINK_NML){                  /* Link Normal */
                    /* Next Process */
                    u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP8;
                }
                else{
                    /* Next Process */                                                      /* Link Error */
                    u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP5;
                }
            }
            break;
        case GVIFSNDR_CYCCHK_STEP5:                                         /* STEP5 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4937_GVIFSNDRHDCPSTOP_WRINUM,
                                                           CXD4937_GVIFSNDRHDCPSTOP, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4937_GVIFSNDRHDCPSTOP_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP6;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP6:                                         /* STEP6 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4937_BANKSET_WRINUM,
                                                           CXD4937_BANKSET_WAIT_7MS, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4957_GVIFSNDRBANK0_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP7;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP7:                                         /* STEP7 */
            /* State Update */
            u1_s_gvifsnd_state = (U1)GVIFSENDER_SEQ_LINKCHK;
            /* Link Error Check */
            vd_s_Pict_GvifSndrGvifLinkChk();
            /* Process Reset */
            u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP0;
            break;
        case GVIFSNDR_CYCCHK_STEP8:                                         /* STEP8 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4937_BANKSET_WRINUM,
                                                           CXD4937_BANKSET, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4937_GVIFSNDRBANK4_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP9;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP9:                                         /* STEP9 */
        /* ----------100-4-7 定期監視制御 eDP入力異常検知---------- */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4937_GVIFSNDREDPERR_SET1_WRINUM,
                                                           CXD4937_GVIFSNDREDPERR_SET1, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4937_GVIFSNDREDPERR1_1_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP10;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP10:                                        /* STEP10 */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                            st_sp_CXD4937_GVIFSNDREDPERR1_2_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP11;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP11:                                        /* STEP11 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4937_GVIFSNDREDPERR_SET2_WRINUM,
                                                           CXD4937_GVIFSNDREDPERR_SET2, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4937_GVIFSNDREDPERR1_3_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP12;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP12:                                        /* STEP12 */
            u1_t_reg_read_result = st_sp_CXD4937_GVIFSNDREDPERR1_2_TBL[1].u1p_pdu[1];
            u1_t_reg_read_result = u1_t_reg_read_result & (U1)PICT_GVIFSNDREDPERR_1;        /* Get eDP Input Error Result */
            if(u1_t_reg_read_result != (U1)PICT_GVIFSNDREDPERR_1){                          /* eDP Input Error */
                if((u1_s_gvifsnd_edperr1_drec_cnt < (U1)CXD4937_EDPERR1_DREC_CNT_MAX)       /* Drec Counter < 3 */
                && ((u1_s_gvifsnd_edperr1_pre_sts == (U1)CXD4937_EDPERR_STS_INIT)           /* Initial Error */
                 || (u1_s_gvifsnd_edperr1_pre_sts == (U1)CXD4937_EDPERR_STS_NORMAL))){      /* Normal -> Error */
                    u1_s_gvifsnd_edperr1_drec_cnt++;
                    vd_CXD4937_DREC_REQ((U1)SYSECDRC_DREC_ID_3, u1_s_gvifsnd_edperr1_drec_cnt, (U1)0x00U);
                    u1_s_gvifsnd_edperr1_pre_sts = (U1)CXD4937_EDPERR_STS_ERROR;
                }
            }
            else{
                u1_s_gvifsnd_edperr1_pre_sts = (U1)CXD4937_EDPERR_STS_NORMAL;
            }
            /* Next Process */
            u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP13;
            break;
        case GVIFSNDR_CYCCHK_STEP13:                                        /* STEP13 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4937_GVIFSNDREDPERR_SET1_WRINUM,
                                                           CXD4937_GVIFSNDREDPERR_SET1, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4937_GVIFSNDREDPERR2_1_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP14;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP14:                                        /* STEP14 */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                            st_sp_CXD4937_GVIFSNDREDPERR2_2_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP15;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP15:                                        /* STEP15 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4937_GVIFSNDREDPERR_SET2_WRINUM,
                                                           CXD4937_GVIFSNDREDPERR_SET2, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4937_GVIFSNDREDPERR2_3_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP16;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP16:                                        /* STEP16 */
            u1_t_reg_read_result = st_sp_CXD4937_GVIFSNDREDPERR2_2_TBL[1].u1p_pdu[1];
            u1_t_reg_read_result = u1_t_reg_read_result & (U1)PICT_GVIFSNDREDPERR_2;        /* Get eDP Input Error Result */
            if(u1_t_reg_read_result != (U1)PICT_GVIFSNDREDPERR_2){                          /* eDP Input Error */
                if((u1_s_gvifsnd_edperr2_drec_cnt < (U1)CXD4937_EDPERR2_DREC_CNT_MAX)       /* Drec Counter < 3 */
                && ((u1_s_gvifsnd_edperr2_pre_sts == (U1)CXD4937_EDPERR_STS_INIT)           /* Initial Error */
                 || (u1_s_gvifsnd_edperr2_pre_sts == (U1)CXD4937_EDPERR_STS_NORMAL))){      /* Normal -> Error */
                    u1_s_gvifsnd_edperr2_drec_cnt++;
                    vd_CXD4937_DREC_REQ((U1)SYSECDRC_DREC_ID_4, u1_s_gvifsnd_edperr2_drec_cnt, (U1)0x00U);
                    u1_s_gvifsnd_edperr2_pre_sts = (U1)CXD4937_EDPERR_STS_ERROR;
                }
            }
            else{
                u1_s_gvifsnd_edperr2_pre_sts = (U1)CXD4937_EDPERR_STS_NORMAL;
            }
            /* Next Process */
            u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP17;
            break;
        case GVIFSNDR_CYCCHK_STEP17:                                        /* STEP17 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4937_GVIFSNDREDPERR_SET1_WRINUM,
                                                           CXD4937_GVIFSNDREDPERR_SET1, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4937_GVIFSNDREDPERR3_1_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP18;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP18:                                        /* STEP18 */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                            st_sp_CXD4937_GVIFSNDREDPERR3_2_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP19;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP19:                                        /* STEP19 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4937_GVIFSNDREDPERR_SET2_WRINUM,
                                                           CXD4937_GVIFSNDREDPERR_SET2, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4937_GVIFSNDREDPERR3_3_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP20;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP20:                                        /* STEP20 */
            u1_t_reg_read_result = st_sp_CXD4937_GVIFSNDREDPERR3_2_TBL[1].u1p_pdu[1];
            u1_t_reg_read_result = u1_t_reg_read_result & (U1)PICT_CXD_REG_MASK_BIT_0;      /* Get eDP Input Error Result */
            if(u1_t_reg_read_result != (U1)PICT_CXD_REG_MASK_BIT_0){                        /* eDP Input Error */
                if((u1_s_gvifsnd_edperr3_drec_cnt < (U1)CXD4937_EDPERR3_DREC_CNT_MAX)       /* Drec Counter < 3 */
                && ((u1_s_gvifsnd_edperr3_pre_sts == (U1)CXD4937_EDPERR_STS_INIT)           /* Initial Error */
                 || (u1_s_gvifsnd_edperr3_pre_sts == (U1)CXD4937_EDPERR_STS_NORMAL))){      /* Normal -> Error */
                    u1_s_gvifsnd_edperr3_drec_cnt++;
                    vd_CXD4937_DREC_REQ((U1)SYSECDRC_DREC_ID_5, u1_s_gvifsnd_edperr3_drec_cnt, (U1)0x00U);
                    u1_s_gvifsnd_edperr3_pre_sts = (U1)CXD4937_EDPERR_STS_ERROR;
                }
            }
            else{
                u1_s_gvifsnd_edperr3_pre_sts = (U1)CXD4937_EDPERR_STS_NORMAL;
            }
            /* Next Process */
            u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP21;
            break;
        case GVIFSNDR_CYCCHK_STEP21:                                        /* STEP21 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4937_BANKSET_WRINUM,
                                                           CXD4937_BANKSET, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4957_GVIFSNDRBANK0_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP22;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP22:                                        /* STEP22 */
        /* ----------100-4-7 定期監視制御 入力映像異常検知---------- */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                            st_sp_CXD4957_GVIFSNDRINPUTERR_RD_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP23;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP23:                                        /* STEP23 */
            u1_t_reg_read_result = st_sp_CXD4957_GVIFSNDRINPUTERR_RD_TBL[1].u1p_pdu[1];
            u1_t_reg_read_result = u1_t_reg_read_result & (U1)PICT_CXD_REG_MASK_BIT_0;      /* Get Input Error Result */
            if(u1_t_reg_read_result != (U1)PICT_CXD_REG_MASK_BIT_0){                        /* Input Error */
                if(u1_s_gvifsnd_videoerr_drec_cnt < (U1)CXD4937_VIDEOERR_DREC_CNT_MAX){     /* Drec Counter < 3 */
                    u1_s_gvifsnd_videoerr_drec_cnt++;
                    vd_CXD4937_DREC_REQ((U1)SYSECDRC_DREC_ID_6, u1_s_gvifsnd_videoerr_drec_cnt, (U1)0x00U);
                }
            }
            /* Next Process */
            u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP24;
            break;
        case GVIFSNDR_CYCCHK_STEP24:                                        /* STEP24 */
        /* ----------100-4-7 定期監視制御 LOADER異常検知---------- */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                            st_sp_CXD4957_GVIFSNDRLODERERR_RD_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP25;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP25:                                        /* STEP25 */
            u1_t_reg_read_result = st_sp_CXD4957_GVIFSNDRLODERERR_RD_TBL[1].u1p_pdu[1];
            u1_t_reg_read_result = u1_t_reg_read_result & ((U1)PICT_CXD_REG_MASK_BIT_7 | (U1)PICT_CXD_REG_MASK_BIT_6);   /* Get Loader Error Result */
            if(u1_t_reg_read_result != (U1)PICT_GVIFSNDRLODERERR_NML){                      /* Loader Error */
                if(u1_s_gvifsnd_loadererr_drec_cnt < (U1)CXD4937_LOADERERR_DREC_CNT_MAX){   /* Drec Counter < 3 */
                    u1_s_gvifsnd_loadererr_drec_cnt++;
                    vd_CXD4937_DREC_REQ((U1)SYSECDRC_DREC_ID_7, u1_s_gvifsnd_loadererr_drec_cnt, u1_t_reg_read_result);
                }
            }
            /* Next Process */
            u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP26;
            break;
        case GVIFSNDR_CYCCHK_STEP26:                                        /* STEP26 */
        /* ----------100-4-7 定期監視制御 GVIF3接続異常検知---------- */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                            st_sp_CXD4957_GVIFSNDRCONNECTERR_RD_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP27;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP27:                                        /* STEP27 */
            u1_t_reg_read_result = st_sp_CXD4957_GVIFSNDRCONNECTERR_RD_TBL[1].u1p_pdu[1];
            u1_t_reg_read_result = u1_t_reg_read_result & (U1)PICT_CXD_REG_MASK_BIT_0;      /* Get Connect Error Result */
            if(u1_t_reg_read_result != (U1)PICT_CXD_REG_MASK_BIT_0){                        /* Connect Error */
                if(u1_s_gvifsnd_cncterr_drec_cnt < (U1)CXD4937_CNCTERR_DREC_CNT_MAX){       /* Drec Counter < 3 */
                    u1_s_gvifsnd_cncterr_drec_cnt++;
                    vd_CXD4937_DREC_REQ((U1)SYSECDRC_DREC_ID_8, u1_s_gvifsnd_cncterr_drec_cnt, (U1)0x00U);
                }
            }
            /* Next Process */
            u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP28;
            break;
        case GVIFSNDR_CYCCHK_STEP28:                                        /* STEP28 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4957_GVIFSNDRERRCLEAR_SET_WRINUM,
                                                           CXD4957_GVIFSNDRERRCLEAR_SET, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4957_GVIFSNDRERRCLEAR_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Process Reset */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP0;
            }
            break;
        default:                                                                /* FAIL */
            /* Process Reset */
            u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP0;
            break;
    }
}


/*===================================================================================================================================*/
/*  void    vd_s_Pict_GvifSndrDevRst(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Pict_GvifSndrDevRst(void)
{
    static const U2     GVIFSENDER_DEVRST_TIME = (U2)(10U / GVIFSENDER_TASK_TIME);  /* t10 min:10ms */

    U1  u1_t_rst_time_chk_flg;

    switch (u1_s_gvifsnd_devrst_sts){
        case GVIFSENDER_DEVRST_STEP0:                                       /* STEP0 */
            /* Timer Clear */
            u2_s_gvifsnd_devrst_timer = (U2)0;

            if(u1_s_gvifsnd_devrst_drec_cnt < (U1)CXD4937_DEVERR_DREC_CNT_MAX){     /* Drec Counter < 3 */
                u1_s_gvifsnd_devrst_drec_cnt++;
                vd_CXD4937_DREC_REQ((U1)SYSECDRC_DREC_ID_2, u1_s_gvifsnd_devrst_drec_cnt, (U1)0x00U);
            }

            /* GVIF-TC(C-DISP)-RST = L */
            vd_PICT_CXD_GVIF_TX_RST_L();
            /* Timer Start */
            u2_s_gvifsnd_devrst_timer++;
            /* Next Process */
            u1_s_gvifsnd_devrst_sts = (U1)GVIFSENDER_DEVRST_STEP1;
            break;
        case GVIFSENDER_DEVRST_STEP1:                                       /* STEP1 */
            u1_t_rst_time_chk_flg = u1_s_Pict_GvifSndrTimChk(u2_s_gvifsnd_devrst_timer, GVIFSENDER_DEVRST_TIME);
            if(u1_t_rst_time_chk_flg == (U1)TRUE){
                /* GVIF-TC(C-DISP)-RST = H */
                vd_PICT_CXD_GVIF_TX_RST_H();
                /* State Update */
                u1_s_gvifsnd_state = (U1)GVIFSENDER_SEQ_IDLE;
                /* Process Reset */
                u1_s_gvifsnd_devrst_sts = (U1)GVIFSENDER_DEVRST_STEP0;
            }
            else{
                u2_s_gvifsnd_devrst_timer++;
            }
            break;
        default:                                                                /* FAIL */
            /* State Reset */
            u1_s_gvifsnd_state = (U1)GVIFSENDER_SEQ_CYC;
            /* Process Reset */
            u1_s_gvifsnd_devrst_sts = (U1)GVIFSENDER_DEVRST_STEP0;
            break;
    }
}

/*===================================================================================================================================*/
/*  void    vd_s_Pict_GvifSndrGvifLinkChk(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Pict_GvifSndrGvifLinkChk(void)
{
    static const U2     GVIFSENDER_LINKCHK_WAIT_TIME = (U2)(500U / GVIFSENDER_TASK_TIME);  /* t11 min:500ms */

    U1      u1_t_gviflink_time_chk_flg;
    U1      u1_t_reg_req_sts;                                       /* Register Read/Write Request Status */
    U1      u1_t_reg_read_result;                                   /* Register Read Result */

    switch (u1_s_gvifsnd_linkchk_sts){
        case GVIFSENDER_LINKCHK_STEP0:                                                      /* STEP0 */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4957_GVIFSNDRLINKCHK_RD_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_linkchk_sts = (U1)GVIFSENDER_LINKCHK_STEP1;
            }
            break;
        case GVIFSENDER_LINKCHK_STEP1:                                                      /* STEP1 */
            u1_t_reg_read_result = st_sp_CXD4957_GVIFSNDRLINKCHK_RD_TBL[1].u1p_pdu[1];
            u1_t_reg_read_result = u1_t_reg_read_result & (U1)PICT_CXD_REG_MASK_BIT_0;          /* Get Link Check Result */
            if(u1_t_reg_read_result == (U1)PICT_CXD_REG_MASK_BIT_0){                            /* Link Check Error */
                /* Error Count Clear */
                u1_s_gvifsnd_linkchk_err_cnt = (U1)0U;
                /* Next Process */
                u1_s_gvifsnd_linkchk_sts = (U1)GVIFSENDER_LINKCHK_STEP2;
            }else{
                /* Error Count Increment */
                u1_s_gvifsnd_linkchk_err_cnt++;
                /* Next Process */
                u1_s_gvifsnd_linkchk_sts = (U1)GVIFSENDER_LINKCHK_STEP3;
            }
            break;
        case GVIFSENDER_LINKCHK_STEP2:                                                      /* STEP2 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4957_GVIFSNDRERRCLEAR_SET_WRINUM,
                                                           CXD4957_GVIFSNDRERRCLEAR_SET, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4957_GVIFSNDRERRCLEAR_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Return to HDCP Authentication Flow */
                vd_g_Gvif3txSeqCtl(MCU_STEP_GVIF3TX_OVERALL_4);
                /* State Reset */
                u1_s_gvifsnd_state = (U1)GVIFSENDER_SEQ_IDLE;
                /* Process Reset */
                u1_s_gvifsnd_linkchk_sts = (U1)GVIFSNDR_CYCCHK_STEP0;
            }
            break;
        case GVIFSENDER_LINKCHK_STEP3:                                                      /* STEP3 */
            if(u1_s_gvifsnd_linkchk_err_cnt >= (U1)PICT_GVIFSNDRGVIFLINK_CHK_CNT_MAX){
                /* Error Count Clear */
                u1_s_gvifsnd_linkchk_err_cnt = (U1)0U;
                /* State Reset */
                u1_s_gvifsnd_state = (U1)GVIFSENDER_SEQ_CYC;
                /* Process Reset */
                u1_s_gvifsnd_linkchk_sts = (U1)GVIFSNDR_CYCCHK_STEP0;
            }
            else {
                /* Timer Clear */
                u2_s_gvifsnd_linkchk_timer = (U2)0;
                /* Timer Start */
                u2_s_gvifsnd_linkchk_timer++;
                /* Next Process */
                u1_s_gvifsnd_linkchk_sts = (U1)GVIFSENDER_LINKCHK_STEP4;
            }

            break;
        case GVIFSENDER_LINKCHK_STEP4:                                                      /* STEP4 */
            u1_t_gviflink_time_chk_flg = u1_s_Pict_GvifSndrTimChk(u2_s_gvifsnd_linkchk_timer, GVIFSENDER_LINKCHK_WAIT_TIME);
            if(u1_t_gviflink_time_chk_flg == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_linkchk_sts = (U1)GVIFSENDER_LINKCHK_STEP0;
            }
            else{
                u2_s_gvifsnd_linkchk_timer++;
            }
            break;
        default:                                                                            /* FAIL */
            /* State Reset */
            u1_s_gvifsnd_state = (U1)GVIFSENDER_SEQ_CYC;
            /* Process Reset */
            u1_s_gvifsnd_linkchk_sts = (U1)GVIFSENDER_LINKCHK_STEP0;
            break;
    }
}