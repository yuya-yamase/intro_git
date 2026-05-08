/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "PMIC.h"
#include "SysEcDrc.h"

#include "ivdsh.h"
#include "rim_ctl.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define PMIC_REG_MASK_BIT_5  (0x20U)  /* Register Bit Mask */
#define PMIC_VMCOM_WORD_1    (1U)
#define PMIC_BON_ST_RD_CAUSE (0U)
#define PMIC_BON_ST_WR_INIT  (1U)

#define PMIC_REG_SET_WRINUM  (4U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U2 u2_s_pmic_regstep;           /* Pmic Register Request Step */
static U4 u4_s_pmic_i2c_ack_wait_time; /* Pmic I2C Request Ack Wait Timer */
static U2 u2_s_pmic_reg_btwn_time;     /* Pmic Access Register Between Timer */
static U1 u1_s_pmic_bon_exec_flag;     /* Pmic BON init request flag */
static U1 u1_s_pmic_state;             /* Pmic BON init state */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void vd_s_Pmic_BonInitProc(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_REG_WRI_REQ PMIC_REG_SET[PMIC_REG_SET_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         4,         0},
    {        4,         4,         0},
    {        8,         4,         0},
    {       12,         1,         0}
};

const U1 u1_sp_PMIC_DATA_RD_PDU1[PMIC_I2C_RWC_BYTE2] = {
    (U1)PMIC_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x19U     /* Write Address */
};

U1 u1_sp_PMIC_DATA_RD_PDU2[PMIC_I2C_RWC_BYTE2];

const U1 u1_sp_PMIC_INIT_RD_PDU1[PMIC_I2C_RWC_BYTE2] = {
    (U1)PMIC_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x31U     /* Write Address */
};

U1 u1_sp_PMIC_INIT_RD_PDU2[PMIC_I2C_RWC_BYTE14];

U1 u1_sp_PMIC_INIT_SET_PDU1[PMIC_I2C_RWC_BYTE3];

U1 u1_sp_PMIC_INIT_SET_PDU2[PMIC_I2C_RWC_BYTE3];

U1 u1_sp_PMIC_INIT_SET_PDU3[PMIC_I2C_RWC_BYTE3];

U1 u1_sp_PMIC_INIT_SET_PDU4[PMIC_I2C_RWC_BYTE3];

U1 u1_sp_PMIC_INIT_SET_PDU5[PMIC_I2C_RWC_BYTE3];

U1 u1_sp_PMIC_INIT_SET_PDU6[PMIC_I2C_RWC_BYTE3];

U1 u1_sp_PMIC_INIT_SET_PDU7[PMIC_I2C_RWC_BYTE3];

U1 u1_sp_PMIC_INIT_SET_PDU8[PMIC_I2C_RWC_BYTE3];

U1 u1_sp_PMIC_INIT_SET_PDU9[PMIC_I2C_RWC_BYTE3];

U1 u1_sp_PMIC_INIT_SET_PDU10[PMIC_I2C_RWC_BYTE3];

U1 u1_sp_PMIC_INIT_SET_PDU11[PMIC_I2C_RWC_BYTE3];

U1 u1_sp_PMIC_INIT_SET_PDU12[PMIC_I2C_RWC_BYTE3];

U1 u1_sp_PMIC_INIT_SET_PDU13[PMIC_I2C_RWC_BYTE3];

const ST_GP_I2C_MA_REQ st_sp_PMIC_DATA_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_PMIC_DATA_RD_PDU1[0],
        (U4)0x00000002U
    },
    {
        (U1 *)&u1_sp_PMIC_DATA_RD_PDU2[0],
        (U4)0x00040002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_PMIC_INIT_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_PMIC_INIT_RD_PDU1[0],
        (U4)0x00080002U
    },
    {
        (U1 *)&u1_sp_PMIC_INIT_RD_PDU2[0],
        (U4)0x000C000EU
    }
};

const ST_GP_I2C_MA_REQ st_sp_PMIC_INIT_SET_TBL[13] = {
    {
        (U1 *)&u1_sp_PMIC_INIT_SET_PDU1[0],
        (U4)0x00100003U
    },
    {
        (U1 *)&u1_sp_PMIC_INIT_SET_PDU2[0],
        (U4)0x00140003U
    },
    {
        (U1 *)&u1_sp_PMIC_INIT_SET_PDU3[0],
        (U4)0x00180003U
    },
    {
        (U1 *)&u1_sp_PMIC_INIT_SET_PDU4[0],
        (U4)0x001C0003U
    },
    {
        (U1 *)&u1_sp_PMIC_INIT_SET_PDU5[0],
        (U4)0x00200003U
    },
    {
        (U1 *)&u1_sp_PMIC_INIT_SET_PDU6[0],
        (U4)0x00240003U
    },
    {
        (U1 *)&u1_sp_PMIC_INIT_SET_PDU7[0],
        (U4)0x00280003U
    },
    {
        (U1 *)&u1_sp_PMIC_INIT_SET_PDU8[0],
        (U4)0x002C0003U
    },
    {
        (U1 *)&u1_sp_PMIC_INIT_SET_PDU9[0],
        (U4)0x00300003U
    },
    {
        (U1 *)&u1_sp_PMIC_INIT_SET_PDU10[0],
        (U4)0x00340003U
    },
    {
        (U1 *)&u1_sp_PMIC_INIT_SET_PDU11[0],
        (U4)0x00380003U
    },
    {
        (U1 *)&u1_sp_PMIC_INIT_SET_PDU12[0],
        (U4)0x003C0003U
    },
    {
        (U1 *)&u1_sp_PMIC_INIT_SET_PDU13[0],
        (U4)0x00400003U
    }
};

/* 0x31〜0x3Dのマスク定義 */
static const U1 u1_pmic_reg_mask_tbl[PMIC_I2C_RWC_BYTE14] = {
    0x00U, /* [0]  使用しない */
    0xFFU, /* [1]  0x31 */
    0xFFU, /* [2]  0x32 */
    0x0FU, /* [3]  0x33 */
    0x0FU, /* [4]  0x34 */
    0x0FU, /* [5]  0x35 */
    0x0FU, /* [6]  0x36 */
    0x0FU, /* [7]  0x37 */
    0x3FU, /* [8]  0x38 */
    0x3FU, /* [9]  0x39 */
    0x3FU, /* [10] 0x3A */
    0x3FU, /* [11] 0x3B */
    0x3FU, /* [12] 0x3C */
    0x18U  /* [13] 0x3D */
};

static U1* const u1_sp_PMIC_INIT_SET_PDU_TBL[] = {
    u1_sp_PMIC_INIT_SET_PDU1,
    u1_sp_PMIC_INIT_SET_PDU2,
    u1_sp_PMIC_INIT_SET_PDU3,
    u1_sp_PMIC_INIT_SET_PDU4,
    u1_sp_PMIC_INIT_SET_PDU5,
    u1_sp_PMIC_INIT_SET_PDU6,
    u1_sp_PMIC_INIT_SET_PDU7,
    u1_sp_PMIC_INIT_SET_PDU8,
    u1_sp_PMIC_INIT_SET_PDU9,
    u1_sp_PMIC_INIT_SET_PDU10,
    u1_sp_PMIC_INIT_SET_PDU11,
    u1_sp_PMIC_INIT_SET_PDU12,
    u1_sp_PMIC_INIT_SET_PDU13
};
static const U1 u1_sp_PMIC_INIT_SET_PDU_NUM = (U1)(sizeof(u1_sp_PMIC_INIT_SET_PDU_TBL) / sizeof(u1_sp_PMIC_INIT_SET_PDU_TBL[0]));
/*===================================================================================================================================*/
/*  void    vd_g_Pmic_Init(void)                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Pmic_BonInit(void)
{
    U2 u2_t_cnt;
    U4 u4_t_vmcom_req;

    u1_s_pmic_bon_exec_flag = (U1)TRUE;
    vd_g_Rim_WriteU1((U2)RIMID_U1_PMIC_EXEC_FLG, u1_s_pmic_bon_exec_flag);

    u2_s_pmic_regstep = (U2)0U;
    u4_s_pmic_i2c_ack_wait_time = (U4)0U;
    u2_s_pmic_reg_btwn_time = (U2)0xFFFFU;
    u1_s_pmic_state = (U1)PMIC_BON_ST_RD_CAUSE;

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_PMIC_INIT_RD_PDU2[0] = (U1)PMIC_I2C_SLAVEADR_RD;    /* Slave Address */
    for(u2_t_cnt = (U2)1U; u2_t_cnt < (U2)PMIC_I2C_RWC_BYTE14; u2_t_cnt++) {
        u1_sp_PMIC_INIT_RD_PDU2[u2_t_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /* レジスタ初期設定 書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU1[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU1[1] = (U1)0x31U;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU1[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU2[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU2[1] = (U1)0x32U;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU2[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU3[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU3[1] = (U1)0x33U;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU3[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU4[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU4[1] = (U1)0x34U;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU4[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU5[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU5[1] = (U1)0x35U;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU5[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU6[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU6[1] = (U1)0x36U;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU6[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU7[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU7[1] = (U1)0x37U;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU7[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU8[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU8[1] = (U1)0x38U;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU8[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU9[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU9[1] = (U1)0x39U;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU9[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU10[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU10[1] = (U1)0x3AU;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU10[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU11[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU11[1] = (U1)0x3BU;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU11[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU12[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU12[1] = (U1)0x3CU;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU12[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU13[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU13[1] = (U1)0x3DU;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU13[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  データリード用テーブル初期化 */
    u1_sp_PMIC_DATA_RD_PDU2[0] = (U1)PMIC_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_PMIC_DATA_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    u4_t_vmcom_req = (U4)PMIC_VMCOM_POWER_OFF;
    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO3_DIN2_STAT, &u4_t_vmcom_req, (U2)PMIC_VMCOM_WORD_1);    /* To VM3 */

}
/*===================================================================================================================================*/
/*  void    vd_g_Pmic_Init(void)                                                                                                     */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Pmic_Init(void)
{
    U2 u2_t_cnt;
    U1 u1_t_rim_sts;
    U1 u1_t_rim_data;
    U4 u4_t_vmcom_req;


    u1_t_rim_data = (U1)0U;
    u1_t_rim_sts  = u1_g_Rim_ReadU1withStatus((U2)RIMID_U1_PMIC_EXEC_FLG, &u1_t_rim_data);
    if((u1_t_rim_sts & (U1)RIM_RESULT_KIND_MASK) == (U1)RIM_RESULT_KIND_OK){
        u1_s_pmic_bon_exec_flag = u1_t_rim_data;
    }

    u2_s_pmic_regstep = (U2)0U;
    u4_s_pmic_i2c_ack_wait_time = (U4)0U;
    u2_s_pmic_reg_btwn_time = (U2)0xFFFFU;
    u1_s_pmic_state = (U1)PMIC_BON_ST_RD_CAUSE;

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_PMIC_INIT_RD_PDU2[0] = (U1)PMIC_I2C_SLAVEADR_RD;    /* Slave Address */
    for(u2_t_cnt = (U2)1U; u2_t_cnt < (U2)PMIC_I2C_RWC_BYTE14; u2_t_cnt++) {
        u1_sp_PMIC_INIT_RD_PDU2[u2_t_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /* レジスタ初期設定 書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU1[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU1[1] = (U1)0x31U;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU1[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU2[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU2[1] = (U1)0x32U;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU2[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU3[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU3[1] = (U1)0x33U;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU3[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU4[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU4[1] = (U1)0x34U;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU4[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU5[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU5[1] = (U1)0x35U;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU5[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU6[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU6[1] = (U1)0x36U;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU6[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU7[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU7[1] = (U1)0x37U;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU7[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU8[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU8[1] = (U1)0x38U;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU8[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU9[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU9[1] = (U1)0x39U;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU9[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU10[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU10[1] = (U1)0x3AU;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU10[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU11[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU11[1] = (U1)0x3BU;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU11[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU12[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU12[1] = (U1)0x3CU;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU12[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  書込み用テーブル(Data可変)初期化 */
    u1_sp_PMIC_INIT_SET_PDU13[0] = (U1)PMIC_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_PMIC_INIT_SET_PDU13[1] = (U1)0x3DU;    /* Write Address */
    u1_sp_PMIC_INIT_SET_PDU13[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  データリード用テーブル初期化 */
    u1_sp_PMIC_DATA_RD_PDU2[0] = (U1)PMIC_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_PMIC_DATA_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    u4_t_vmcom_req = (U4)PMIC_VMCOM_POWER_OFF;
    vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO3_DIN2_STAT, &u4_t_vmcom_req, (U2)PMIC_VMCOM_WORD_1);    /* To VM3 */

}

/*===================================================================================================================================*/
/*  void    vd_g_Pmic_Routine(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Pmic_Routine(void)
{
    U1 u1_t_reg_req_sts;
    U1 u1_t_reg_read_result;
    U4 u4_t_vmcom_req;

    if(u4_s_pmic_i2c_ack_wait_time < (U4)U4_MAX){
        u4_s_pmic_i2c_ack_wait_time++;
    }

    /* Initial configuration at startup */
    if(u1_s_pmic_bon_exec_flag == (U1)TRUE){
        vd_s_Pmic_BonInitProc();
    }
    else{
        u1_t_reg_req_sts = u1_PMIC_I2C_CTRL_REGREAD(&u2_s_pmic_regstep, &u4_s_pmic_i2c_ack_wait_time,  /* Read Register */
                                                    st_sp_PMIC_DATA_RD_TBL, &u2_s_pmic_reg_btwn_time);
        if(u1_t_reg_req_sts == (U1)TRUE){
            u1_t_reg_read_result = st_sp_PMIC_DATA_RD_TBL[1].u1p_pdu[1];
            u1_t_reg_read_result &= (U1)PMIC_REG_MASK_BIT_5;
            if(u1_t_reg_read_result == (U1)PMIC_REG_MASK_BIT_5){
                u4_t_vmcom_req = (U4)PMIC_VMCOM_POWER_ON;
            }
            else{
                u4_t_vmcom_req = (U4)PMIC_VMCOM_POWER_OFF;
            }
            vd_g_iVDshWribyDid((U2)IVDSH_DID_WRI_VM2TO3_DIN2_STAT, &u4_t_vmcom_req, (U2)PMIC_VMCOM_WORD_1);    /* To VM3 */
        }
    }
}
/*===================================================================================================================================*/
/*  void    vd_s_Pmic_BonInitProc(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void vd_s_Pmic_BonInitProc(void)
{
    U1 u1_t_reg_req_sts;
    U1 u1_t_cnt;
    U1 u1_t_reg_val1;
    U1 u1_t_reg_val2;
    U1 u1_t_reg_idx1;
    U1 u1_t_reg_idx2;
    U1 u1_t_rd_mask1;
    U1 u1_t_rd_mask2;
    U1 u1_t_drec_id;

    switch (u1_s_pmic_state){
        case PMIC_BON_ST_RD_CAUSE:
            /* Check error causes */
            u1_t_reg_req_sts = u1_PMIC_I2C_CTRL_REGREAD(&u2_s_pmic_regstep, &u4_s_pmic_i2c_ack_wait_time,  /* Read Register */
                                                        st_sp_PMIC_INIT_RD_TBL, &u2_s_pmic_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Check registers in pairs (2 bytes per record) and log if any masked bit is set */
                for (u1_t_cnt = 0U; u1_t_cnt < (U1)(PMIC_I2C_RWC_BYTE14 / 2U); u1_t_cnt++){

                    u1_t_reg_idx1 = (U1)(1U + (2U * u1_t_cnt));
                    u1_t_reg_idx2 = (U1)(u1_t_reg_idx1 + 1U);

                    u1_t_reg_val1 = u1_sp_PMIC_INIT_RD_PDU2[u1_t_reg_idx1];
                    u1_t_rd_mask1 = u1_pmic_reg_mask_tbl[u1_t_reg_idx1];

                    if(u1_t_reg_idx2 < (U1)PMIC_I2C_RWC_BYTE14){
                        u1_t_reg_val2 = u1_sp_PMIC_INIT_RD_PDU2[u1_t_reg_idx2];
                        u1_t_rd_mask2 = u1_pmic_reg_mask_tbl[u1_t_reg_idx2];
                    }
                    else{
                        u1_t_reg_val2 = (U1)0U;
                        u1_t_rd_mask2 = (U1)0U;
                    }

                    if (((u1_t_reg_val1 & u1_t_rd_mask1) != 0U)
                    ||  ((u1_t_reg_val2 & u1_t_rd_mask2) != 0U)){
                        u1_t_drec_id = u1_t_cnt + 1U;
                        /* Store abnormal/fault details */
                        vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_PWRCTRL, u1_t_drec_id, u1_t_reg_val1, u1_t_reg_val2);
                    }
                }
                /* Clear the status bits by writing 1s to the corresponding bit positions (W1C) */
                for (u1_t_cnt = 0U; u1_t_cnt < u1_sp_PMIC_INIT_SET_PDU_NUM; u1_t_cnt++) {
                    u1_sp_PMIC_INIT_SET_PDU_TBL[u1_t_cnt][2] = u1_pmic_reg_mask_tbl[u1_t_cnt + 1];
                }
                u1_s_pmic_state = (U1)PMIC_BON_ST_WR_INIT;
            }
            break;
        case PMIC_BON_ST_WR_INIT:
            /* Initialize registers (register initial setup) */
            u1_t_reg_req_sts = u1_PMIC_I2C_CTRL_REGSET(&u2_s_pmic_regstep, (U2)PMIC_REG_SET_WRINUM,
                                                        PMIC_REG_SET, &u4_s_pmic_i2c_ack_wait_time,
                                                        st_sp_PMIC_INIT_SET_TBL, &u2_s_pmic_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_s_pmic_state = (U1)PMIC_BON_ST_RD_CAUSE;
                u1_s_pmic_bon_exec_flag = (U1)FALSE;
                vd_g_Rim_WriteU1((U2)RIMID_U1_PMIC_EXEC_FLG, u1_s_pmic_bon_exec_flag);
            }
            break;
        default:
            u1_s_pmic_state = (U1)PMIC_BON_ST_RD_CAUSE;
            break;
    }
}
