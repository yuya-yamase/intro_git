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

#define CXD4937_BANKSET_WRINUM              (1U)
#define CXD4957_GVIFSNDRERRCLEAR_SET_WRINUM (1U)

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

static U1 u1_s_gvifsnd_linkchk_sts;                     /* GVIF Sender Link Check Status */
static U2 u2_s_gvifsnd_linkchk_timer;                   /* GVIF Sender Link Check Wait Timer */
static U1 u1_s_gvifsnd_linkchk_err_cnt;                 /* GVIF Sender Link Check Err Counter */


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

static const ST_REG_WRI_REQ CXD4957_GVIFSNDRERRCLEAR_SET[CXD4957_GVIFSNDRERRCLEAR_SET_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         2,         0}
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

    u1_s_gvifsnd_linkchk_sts = (U1)GVIFSENDER_LINKCHK_STEP0;
    u2_s_gvifsnd_linkchk_timer = (U2)0U;
    u1_s_gvifsnd_linkchk_err_cnt = (U1)0U;

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

}

/*===================================================================================================================================*/
/*  void    vd_g_Pict_GvifSndrRoutine(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Pict_GvifSndrRoutine(void)
{
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
        case GVIFSNDR_CYCCHK_STEP1:                                       /* STEP1 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4937_BANKSET_WRINUM,
                                                           CXD4937_BANKSET, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4957_GVIFSNDRBANK0_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP2;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP2:                                       /* STEP2 */
        /* ----------100-4-7 定期監視制御 デバイス異常検知---------- */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4957_GVIFSNDRDEVERR_RD_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP3;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP3:                                       /* STEP3 */
            u1_t_reg_read_result = st_sp_CXD4957_GVIFSNDRDEVERR_RD_TBL[1].u1p_pdu[1];
            if(u1_t_reg_read_result != (U1)PICT_GVIFSNDRDEVERR_NML ){                   /* Device Error */
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
        case GVIFSNDR_CYCCHK_STEP4:                                       /* STEP4 */
        /* ----------100-4-7 定期監視制御 GVIF3リンク切れ検知---------- */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4957_GVIFSNDRDEVERR_RD_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP5;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP5:                                       /* STEP5 */
            u1_t_reg_read_result = st_sp_CXD4957_GVIFSNDRDEVERR_RD_TBL[1].u1p_pdu[1];
            u1_t_reg_read_result = u1_t_reg_read_result & (U1)PICT_CXD_REG_MASK_BIT_7;      /* Get Link Error Result */
            if(u1_t_reg_read_result != (U1)PICT_GVIFSNDRGVIFLINK_NML){                  /* Link Error */
                /* HDCP認証停止関数 */ /* 暫定 シス検未対応 */
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP6;
            }
            else{
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP8;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP6:                                       /* STEP6 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGSET(&u2_s_gvifsnd_regstep, (U2)CXD4937_BANKSET_WRINUM,
                                                           CXD4937_BANKSET, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                           st_sp_CXD4957_GVIFSNDRBANK0_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP7;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP7:                                       /* STEP7 */
            /* State Update */
            u1_s_gvifsnd_state = (U1)GVIFSENDER_SEQ_LINKCHK;
            /* Link Error Check */
            vd_s_Pict_GvifSndrGvifLinkChk();
            /* Process Reset */
            u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP0;
            break;
        case GVIFSNDR_CYCCHK_STEP8:                                       /* STEP8 */
        /* ----------100-4-7 定期監視制御 入力映像異常検知---------- */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                            st_sp_CXD4957_GVIFSNDRINPUTERR_RD_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP9;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP9:                                       /* STEP9 */
            u1_t_reg_read_result = st_sp_CXD4957_GVIFSNDRINPUTERR_RD_TBL[1].u1p_pdu[1];
            u1_t_reg_read_result = u1_t_reg_read_result & (U1)PICT_CXD_REG_MASK_BIT_0;      /* Get Input Error Result */
            if(u1_t_reg_read_result != (U1)PICT_CXD_REG_MASK_BIT_0){                        /* Input Error */
                /* ダイレコ保存 *//* 暫定 シス検ではダイレコ保存未対応 */
            }
            /* Next Process */
            u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP10;
            break;
        case GVIFSNDR_CYCCHK_STEP10:                                      /* STEP10 */
        /* ----------100-4-7 定期監視制御 LOADER異常検知---------- */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                            st_sp_CXD4957_GVIFSNDRLODERERR_RD_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP11;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP11:                                      /* STEP11 */
            u1_t_reg_read_result = st_sp_CXD4957_GVIFSNDRLODERERR_RD_TBL[1].u1p_pdu[1];
            u1_t_reg_read_result = u1_t_reg_read_result & ((U1)PICT_CXD_REG_MASK_BIT_7 | (U1)PICT_CXD_REG_MASK_BIT_6);   /* Get Loader Error Result */
            if(u1_t_reg_read_result != (U1)PICT_GVIFSNDRLODERERR_NML){                  /* Loader Error */
                /* ダイレコ保存 *//* 暫定 シス検ではダイレコ保存未対応 */
            }
            /* Next Process */
            u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP12;
            break;
        case GVIFSNDR_CYCCHK_STEP12:                                      /* STEP12 */
        /* ----------100-4-7 定期監視制御 GVIF3接続異常検知---------- */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_CXD_I2C_CTRL_REGREAD(&u2_s_gvifsnd_regstep, &u4_s_gvifsnd_i2c_ack_wait_time,
                                                            st_sp_CXD4957_GVIFSNDRCONNECTERR_RD_TBL, &u2_s_gvifsnd_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP13;
            }
            break;
        case GVIFSNDR_CYCCHK_STEP13:                                      /* STEP13 */
            u1_t_reg_read_result = st_sp_CXD4957_GVIFSNDRCONNECTERR_RD_TBL[1].u1p_pdu[1];
            u1_t_reg_read_result = u1_t_reg_read_result & (U1)PICT_CXD_REG_MASK_BIT_0;      /* Get Connect Error Result */
            if(u1_t_reg_read_result != (U1)PICT_CXD_REG_MASK_BIT_0){                        /* Connect Error */
                /* ダイレコ保存 *//* 暫定 シス検ではダイレコ保存未対応 */
            }
            /* Next Process */
            u1_s_gvifsnd_cycchk_sts = (U1)GVIFSNDR_CYCCHK_STEP14;
            break;
        case GVIFSNDR_CYCCHK_STEP14:                                      /* STEP14 */
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

            /* ダイレコ保存 *//* 暫定 シス検ではダイレコ保存未対応 */

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
                /* HDCP認証フロー */ /* 暫定 シス検未対応 */
                /* State Reset */
                u1_s_gvifsnd_state = (U1)GVIFSENDER_SEQ_CYC;
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