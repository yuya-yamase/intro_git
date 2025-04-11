/* 0.0.0 */
/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*  CXD4984ERCtl                                                                                                                     */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "CXD4984ERCtl.h"

#include "PictCtl.h"
#include "Dio.h"
#include "gpi2c_ma.h"
#include "Mcu_I2c_Ctrl_private.h"
#include "Mcu_Sys_Pwr_Gvif3Rx.h"
#include "gvif3rx.h"
#include "pictic.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GVIF3RX_CHKTIME                         (50U)
#define GVIF3RX_CNT_CLR                         (0U)

#define GVIF3RX_MAINTASK_STEP1                  (1U)
#define GVIF3RX_MAINTASK_STEP2                  (2U)
#define GVIF3RX_MAINTASK_STEP3                  (3U)

#define GVIF3RX_PERIMONI_STEP1                  (1U)
#define GVIF3RX_PERIMONI_STEP2                  (2U)
#define GVIF3RX_PERIMONI_STEP3                  (3U)
#define GVIF3RX_PERIMONI_STEP4                  (4U)
#define GVIF3RX_PERIMONI_STEP5                  (5U)
#define GVIF3RX_PERIMONI_STEP6                  (6U)
#define GVIF3RX_PERIMONI_STEP7                  (7U)
#define GVIF3RX_PERIMONI_STEP8                  (8U)
#define GVIF3RX_PERIMONI_STEP9                  (9U)
#define GVIF3RX_PERIMONI_STEP10                 (10U)
#define GVIF3RX_PERIMONI_STEP11                 (11U)
#define GVIF3RX_PERIMONI_STEP12                 (12U)
#define GVIF3RX_PERIMONI_STEP13                 (13U)
#define GVIF3RX_PERIMONI_STEP14                 (14U)
#define GVIF3RX_PERIMONI_STEP15                 (15U)
#define GVIF3RX_PERIMONI_STEP16                 (16U)
#define GVIF3RX_PERIMONI_STEP17                 (17U)
#define GVIF3RX_PERIMONI_STEP18                 (18U)
#define GVIF3RX_PERIMONI_STEP19                 (19U)
#define GVIF3RX_PERIMONI_STEP20                 (20U)
#define GVIF3RX_PERIMONI_STEP21                 (21U)
#define GVIF3RX_PERIMONI_STEP22                 (22U)
#define GVIF3RX_PERIMONI_STEP_FIN               (23U)

#define GVIF3RX_MIPI_STEP1                      (1U)
#define GVIF3RX_MIPI_STEP2                      (2U)
#define GVIF3RX_MIPI_STEP3                      (3U)

#define GVIF3RX_SIPERR_STEP1                    (1U)
#define GVIF3RX_SIPERR_STEP2                    (2U)
#define GVIF3RX_SIPERR_STEP3                    (3U)

#define GVIF3RX_LINK_STEP1                      (1U)
#define GVIF3RX_LINK_STEP2                      (2U)

#define GVIF3RX_ERROR1_STEP1                    (1U)
#define GVIF3RX_ERROR1_STEP2                    (2U)

#define GVIF3RX_ERROR2_STEP1                    (1U)
#define GVIF3RX_ERROR2_STEP2                    (2U)

#define GVIF3RX_ERROR3_STEP1                    (1U)
#define GVIF3RX_ERROR3_STEP2                    (2U)

#define GVIF3RX_ERROR4_STEP1                    (1U)
#define GVIF3RX_ERROR4_STEP2                    (2U)

/* キャプチャ準備状態検知処理レジスタ設定値 */
#define GVIF3RX_VIDEO_OUTPUT_ENABLE_0           (0x01U)
#define GVIF3RX_VIDEO_OUTPUT_ENABLE_1           (0x02U)

/* デバイス異常検知 */
#define GVIF3RX_GETREG_DEV_NORMAL               (0x20U)

/* 再起動フラグ */
#define GVIF3_RESTART_FLGON                     (1U)
#define GVIF3_RESTART_FLGOFF                    (0U)
#define GVIF3_RESTART_WAIT                      (5U)

/* カメラシステム種別(カメラ有/カメラ無) */
#define GVIF3RX_KIND_CAM_NONE                   (0U)
#define GVIF3RX_KIND_DOMECON_EXIST              (1U)

/* 未接続検知 */
#define GVIF3_UNCON_CNT_CNF                     (24U)
#define GVIF3_UNCON_IDLE                        (0x00U)
#define GVIF3_RX0_UNCON_MASK                    (0x10U)
#define GVIF3_RX1_UNCON_MASK                    (0x80U)
#define GVIF3_UNCON_FLGON                       (1U)
#define GVIF3_UNCON_FLGOFF                      (0U)

/* ダイレコ記憶回数 */
#define GVIF3_ERROR_MAXLOGCNT                   (3U)
#define GVIF3_ERRORCHK_NON                      (0x00U)
#define GVIF3_ERRORCHK_MASK                     (0x80U)

#define GVIF3RX_RDTBL_NUM                       (2U)
#define GVIF3RX_WRTBL_NUM                       (1U)
#define GVIF3RX_MIPIWRTBL_NUM                   (4U)
#define GVIF3RX_REG_RWC_BYTE2                   (2U)
#define GVIF3RX_REG_RWC_BYTE3                   (3U)
#define GVIF3RX_SLAVEADR_WR                     (0x46U)
#define GVIF3RX_SLAVEADR_RD                     (0x47U)
#define GVIF3RX_OUTSET_WRINUM                   (1U)
#define GVIF3RX_CANKINDSET_WRINUM               (9U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define GVIF3RX_PORT_CAM_RST                    (DIO_ID_PORT10_CH6)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1    u1_s_gvif3rxstby3sts;
static U1    u1_s_gvif3rxcamkind_now;
static U1    u1_s_gvifcamKind_last;
static U1    u1_s_gvif3rxstartflg;
static U1    u1_s_gvif3rxsipfailflg;
static U1    u1_s_gvif3rxchkflg;
static U1    u1_s_gvif3rxchk_cnt;
static U1    u1_s_gvif3rxrestartcnt;
static U1    u1_s_gvif3rx0unconflg;
static U1    u1_s_gvif3rx1unconflg;
static U1    u1_s_gvif3rxrestartflg;
static U1    u1_s_gvif3rx0unconcnt;
static U1    u1_s_gvif3rx1unconcnt;
static U1    u1_s_gvif3rxerror1chkcnt;
static U1    u1_s_gvif3rxerror2chkcnt;
static U1    u1_s_gvif3rxerror3chkcnt;
static U1    u1_s_gvif3rxerror4chkcnt;
static U4    u4_s_gcif3acktime;
static U1    u1_s_gvif3maintask_step;
static U1    u1_s_gvif3perimoni_step;
static U1    u1_s_gvif3mipi_step;
static U1    u1_s_gvif3siperr_step;
static U1    u1_s_gvif3link_step;
static U1    u1_s_gvif3error1_step;
static U1    u1_s_gvif3error2_step;
static U1    u1_s_gvif3error3_step;
static U1    u1_s_gvif3error4_step;
static U2    u2_s_gvif3rx_regstep;
static U2    u2_s_gvif3rxregset_betwaittime_stub;
static U1    u1_s_gvif3rxmipitx_date;
static U1    u1_s_gvif3rxsiperr_date;

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static void   vd_s_Gvif3RxReadDateInit(void);
static U1     u1_s_Gvif3RxCamKindDatSet(void);
static void   vd_s_Gvif3RxCycChk(void);
static void   vd_s_Gvif3Restart(void);
static void   vd_s_Gvif3SipFailTask(void);
static U1     u1_s_Gvif3Mipijdg(void);
static U1     u1_s_Gvif3DevErrChk(void);
static U1     u1_s_Gvif3LinkChk(void);
static U1     u1_s_Gvif3Error1Chk(void);
static U1     u1_s_Gvif3Error2Chk(void);
static U1     u1_s_Gvif3Error3Chk(void);
static U1     u1_s_Gvif3Error4Chk(void);
static U1     u1_s_Gvif3Error5Chk(void);
static U1     u1_s_Gvif3Error6Chk(void);
static U1     u1_s_Gvif3Error7Chk(void);
static U1     u1_s_Gvif3Error8Chk(void);
static U1     u1_s_Gvif3Error9Chk(void);
static U1     u1_s_Gvif3Error10Chk(void);
static U1     u1_s_Gvif3Bank0Chg(void);
static U1     u1_s_Gvif3Bank2Chg(void);
static U1     u1_s_Gvif3Bank3Chg(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const ST_REG_WRI_REQ st_sp_GVIFRX_OUTSET[GVIF3RX_OUTSET_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};

const U1 u1_sp_GVIF3RX_REG_DEVERROR_RD_PDU1[GVIF3RX_REG_RWC_BYTE2] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x97U     /* Write Address */
};

U1 u1_sp_GVIF3RX_REG_DEVERROR_RD_PDU2[GVIF3RX_REG_RWC_BYTE2];

const U1 u1_sp_GVIF3RX_REG_MIPITX_0OFF_1OFF[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9CU,    /* Write Address */
    (U1)0xCCU     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_MIPITX_0ON_1OFF[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9CU,    /* Write Address */
    (U1)0xCDU     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_MIPITX_0OFF_1ON[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9CU,    /* Write Address */
    (U1)0xCEU     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_MIPITX_0ON_1ON[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x9CU,    /* Write Address */
    (U1)0xCFU     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_LINKCHK_RD_PDU1[GVIF3RX_REG_RWC_BYTE2] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U     /* Write Address */
};

U1 u1_sp_GVIF3RX_REG_LINKCHK_RD_PDU2[GVIF3RX_REG_RWC_BYTE2];

const U1 u1_sp_GVIF3RX_REG_EERROR1CHK_RD_PDU1[GVIF3RX_REG_RWC_BYTE2] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U     /* Write Address */
};

U1 u1_sp_GVIF3RX_REG_EERROR1CHK_RD_PDU2[GVIF3RX_REG_RWC_BYTE2];

const U1 u1_sp_GVIF3RX_REG_EERROR2CHK_RD_PDU1[GVIF3RX_REG_RWC_BYTE2] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x10U     /* Write Address */
};

U1 u1_sp_GVIF3RX_REG_EERROR2CHK_RD_PDU2[GVIF3RX_REG_RWC_BYTE2];

const U1 u1_sp_GVIF3RX_REG_EERROR3CHK_RD_PDU1[GVIF3RX_REG_RWC_BYTE2] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x13U     /* Write Address */
};

U1 u1_sp_GVIF3RX_REG_EERROR3CHK_RD_PDU2[GVIF3RX_REG_RWC_BYTE2];

const U1 u1_sp_GVIF3RX_REG_EERROR4CHK_RD_PDU1[GVIF3RX_REG_RWC_BYTE2] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1CU     /* Write Address */
};

U1 u1_sp_GVIF3RX_REG_EERROR4CHK_RD_PDU2[GVIF3RX_REG_RWC_BYTE2];

const U1 u1_sp_GVIF3RX_REG_EERROR5CHK_RD_PDU1[GVIF3RX_REG_RWC_BYTE2] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA0U     /* Write Address */
};

U1 u1_sp_GVIF3RX_REG_EERROR5CHK_RD_PDU2[GVIF3RX_REG_RWC_BYTE2];

const U1 u1_sp_GVIF3RX_REG_EERROR6CHK_RD_PDU1[GVIF3RX_REG_RWC_BYTE2] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA9U     /* Write Address */
};

U1 u1_sp_GVIF3RX_REG_EERROR6CHK_RD_PDU2[GVIF3RX_REG_RWC_BYTE2];

const U1 u1_sp_GVIF3RX_REG_EERROR7CHK_RD_PDU1[GVIF3RX_REG_RWC_BYTE2] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA0U     /* Write Address */
};

U1 u1_sp_GVIF3RX_REG_EERROR7CHK_RD_PDU2[GVIF3RX_REG_RWC_BYTE2];

const U1 u1_sp_GVIF3RX_REG_EERROR8CHK_RD_PDU1[GVIF3RX_REG_RWC_BYTE2] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA9U     /* Write Address */
};

U1 u1_sp_GVIF3RX_REG_EERROR8CHK_RD_PDU2[GVIF3RX_REG_RWC_BYTE2];

const U1 u1_sp_GVIF3RX_REG_EERROR9CHK_RD_PDU1[GVIF3RX_REG_RWC_BYTE2] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA0U     /* Write Address */
};

U1 u1_sp_GVIF3RX_REG_EERROR9CHK_RD_PDU2[GVIF3RX_REG_RWC_BYTE2];

const U1 u1_sp_GVIF3RX_REG_EERROR10CHK_RD_PDU1[GVIF3RX_REG_RWC_BYTE2] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA9U     /* Write Address */
};

U1 u1_sp_GVIF3RX_REG_EERROR10CHK_RD_PDU2[GVIF3RX_REG_RWC_BYTE2];

const U1 u1_sp_GVIF3RX_REG_ERRCLRSET[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2EU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_ERRCLRRLS[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_BANK0[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_BANK1[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_BANK2[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_GVIF3RX_REG_BANK3[GVIF3RX_REG_RWC_BYTE3] = {
    (U1)GVIF3RX_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_DEVERROR[GVIF3RX_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_DEVERROR_RD_PDU1[0],
        (U4)0x20000002U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_DEVERROR_RD_PDU2[0],
        (U4)0x20000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_MIPI_WR[GVIF3RX_MIPIWRTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_MIPITX_0OFF_1OFF[0],
        (U4)0x20000003U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_MIPITX_0ON_1OFF[0],
        (U4)0x20000003U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_MIPITX_0OFF_1ON[0],
        (U4)0x20000003U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_MIPITX_0ON_1ON[0],
        (U4)0x20000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_LINKCHK[GVIF3RX_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_LINKCHK_RD_PDU1[0],
        (U4)0x20000002U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_LINKCHK_RD_PDU2[0],
        (U4)0x20000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_EERROR1CHK[GVIF3RX_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR1CHK_RD_PDU1[0],
        (U4)0x20000002U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR1CHK_RD_PDU2[0],
        (U4)0x20000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_EERROR2CHK[GVIF3RX_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR2CHK_RD_PDU1[0],
        (U4)0x20000002U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR2CHK_RD_PDU2[0],
        (U4)0x20000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_EERROR3CHK[GVIF3RX_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR3CHK_RD_PDU1[0],
        (U4)0x20000002U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR3CHK_RD_PDU2[0],
        (U4)0x20000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_EERROR4CHK[GVIF3RX_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR4CHK_RD_PDU1[0],
        (U4)0x20000002U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR4CHK_RD_PDU2[0],
        (U4)0x20000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_EERROR5CHK[GVIF3RX_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR5CHK_RD_PDU1[0],
        (U4)0x20000002U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR5CHK_RD_PDU2[0],
        (U4)0x20000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_EERROR6CHK[GVIF3RX_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR6CHK_RD_PDU1[0],
        (U4)0x20000002U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR6CHK_RD_PDU2[0],
        (U4)0x20000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_EERROR7CHK[GVIF3RX_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR7CHK_RD_PDU1[0],
        (U4)0x20000002U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR7CHK_RD_PDU2[0],
        (U4)0x20000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_EERROR8CHK[GVIF3RX_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR8CHK_RD_PDU1[0],
        (U4)0x20000002U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR8CHK_RD_PDU2[0],
        (U4)0x20000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_EERROR9CHK[GVIF3RX_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR9CHK_RD_PDU1[0],
        (U4)0x20000002U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR9CHK_RD_PDU2[0],
        (U4)0x20000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_EERROR10CHK[GVIF3RX_RDTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR10CHK_RD_PDU1[0],
        (U4)0x20000002U
    },
    {
        (U1 *)&u1_sp_GVIF3RX_REG_EERROR10CHK_RD_PDU2[0],
        (U4)0x20000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_ERRCLRSET[GVIF3RX_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_ERRCLRSET[0],
        (U4)0x20000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_ERRCLRRLS[GVIF3RX_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_ERRCLRRLS[0],
        (U4)0x20000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_BANK0[GVIF3RX_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_BANK0[0],
        (U4)0x20000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_BANK1[GVIF3RX_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_BANK1[0],
        (U4)0x20000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_BANK2[GVIF3RX_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_BANK2[0],
        (U4)0x20000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_GVIF3RX_REG_BANK3[GVIF3RX_WRTBL_NUM] = {
    {
        (U1 *)&u1_sp_GVIF3RX_REG_BANK3[0],
        (U4)0x20000003U
    }
};

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*  void    vd_g_HmiProxyMainTask(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gvif3RxInit(void)
{
    u1_s_gvif3rxstby3sts = (U1)FALSE;
    u1_s_gvif3rxcamkind_now = (U1)GVIF3RX_KIND_CAM_NONE; /* DTF読み出し値(暫定) */
    u1_s_gvifcamKind_last = (U1)GVIF3RX_KIND_CAM_NONE;   /* DTF読み出し値(暫定) */
    u1_s_gvif3rxstartflg = (U1)FALSE;
    u1_s_gvif3rxsipfailflg = (U1)FALSE;
    u1_s_gvif3rxchkflg = (U1)FALSE;
    u1_s_gvif3rxchk_cnt = (U1)GVIF3RX_CNT_CLR;
    u1_s_gvif3rxrestartcnt = (U1)GVIF3RX_CNT_CLR;
    u1_s_gvif3rx0unconflg = (U1)GVIF3_UNCON_FLGOFF;
    u1_s_gvif3rx0unconcnt = (U1)GVIF3RX_CNT_CLR;
    u1_s_gvif3rx1unconflg = (U1)GVIF3_UNCON_FLGOFF;
    u1_s_gvif3rx1unconcnt = (U1)GVIF3RX_CNT_CLR;
    u1_s_gvif3rxrestartflg = (U1)GVIF3_RESTART_FLGOFF;
    u1_s_gvif3rxerror1chkcnt = (U1)GVIF3RX_CNT_CLR;
    u1_s_gvif3rxerror2chkcnt = (U1)GVIF3RX_CNT_CLR;
    u1_s_gvif3rxerror3chkcnt = (U1)GVIF3RX_CNT_CLR;
    u1_s_gvif3rxerror4chkcnt = (U1)GVIF3RX_CNT_CLR;
    u4_s_gcif3acktime = (U1)GVIF3RX_CNT_CLR;
    u1_s_gvif3maintask_step = (U1)GVIF3RX_MAINTASK_STEP1;
    u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP1;
    u1_s_gvif3mipi_step = (U1)GVIF3RX_MIPI_STEP1;
    u1_s_gvif3siperr_step = (U1)GVIF3RX_SIPERR_STEP1;
    u1_s_gvif3link_step = (U1)GVIF3RX_LINK_STEP1;
    u1_s_gvif3error1_step = (U1)GVIF3RX_ERROR1_STEP1;
    u1_s_gvif3error2_step = (U1)GVIF3RX_ERROR2_STEP1;
    u1_s_gvif3error3_step = (U1)GVIF3RX_ERROR3_STEP1;
    u1_s_gvif3error4_step = (U1)GVIF3RX_ERROR4_STEP1;
    u2_s_gvif3rx_regstep = (U2)0U;
    u2_s_gvif3rxregset_betwaittime_stub = (U2)0xFFFFU;
    u1_s_gvif3rxmipitx_date = (U1)0U;
    vd_s_Gvif3RxReadDateInit();
}

/*===================================================================================================================================*/
/*  static void    vd_s_Gvif3RxCycChk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_Gvif3RxReadDateInit(void)
{
    /*  データリード用テーブル初期化 */
    u1_sp_GVIF3RX_REG_DEVERROR_RD_PDU2[0] = (U1)GVIF3RX_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GVIF3RX_REG_DEVERROR_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_GVIF3RX_REG_LINKCHK_RD_PDU2[0] = (U1)GVIF3RX_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GVIF3RX_REG_LINKCHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_GVIF3RX_REG_EERROR1CHK_RD_PDU2[0] = (U1)GVIF3RX_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GVIF3RX_REG_EERROR1CHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_GVIF3RX_REG_EERROR2CHK_RD_PDU2[0] = (U1)GVIF3RX_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GVIF3RX_REG_EERROR2CHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_GVIF3RX_REG_EERROR3CHK_RD_PDU2[0] = (U1)GVIF3RX_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GVIF3RX_REG_EERROR3CHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_GVIF3RX_REG_EERROR4CHK_RD_PDU2[0] = (U1)GVIF3RX_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GVIF3RX_REG_EERROR4CHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_GVIF3RX_REG_EERROR5CHK_RD_PDU2[0] = (U1)GVIF3RX_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GVIF3RX_REG_EERROR5CHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_GVIF3RX_REG_EERROR6CHK_RD_PDU2[0] = (U1)GVIF3RX_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GVIF3RX_REG_EERROR6CHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_GVIF3RX_REG_EERROR7CHK_RD_PDU2[0] = (U1)GVIF3RX_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GVIF3RX_REG_EERROR7CHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_GVIF3RX_REG_EERROR8CHK_RD_PDU2[0] = (U1)GVIF3RX_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GVIF3RX_REG_EERROR8CHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_GVIF3RX_REG_EERROR9CHK_RD_PDU2[0] = (U1)GVIF3RX_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GVIF3RX_REG_EERROR9CHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_GVIF3RX_REG_EERROR10CHK_RD_PDU2[0] = (U1)GVIF3RX_SLAVEADR_RD;    /* Slave Address */
    u1_sp_GVIF3RX_REG_EERROR10CHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

}

/*===================================================================================================================================*/
/*  void    vd_g_HmiProxyMainTask(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gvif3RxMainTask(void)
{
    /* Ackタイムアウト用カウンタインクリメント */
    if(u4_s_gcif3acktime < (U4)U4_MAX){
        u4_s_gcif3acktime++;
    }
    /* 定期監視ポーリング周期カウント(50ms) */
    if(u1_s_gvif3rxchk_cnt < (U1)U1_MAX){
        u1_s_gvif3rxchk_cnt++;
    }

    switch (u1_s_gvif3maintask_step)
    {
        case GVIF3RX_MAINTASK_STEP1:
            if(Mcu_OnStep_GVIF3RX_OVRALL == (uint8)MCU_STEP_GVIF3RX_OVERALL_FIN){ /* 初期化完了待ち */
                u1_s_gvif3maintask_step = (U1)GVIF3RX_MAINTASK_STEP2;
            }
        break;
    
        case GVIF3RX_MAINTASK_STEP2:
            u1_s_gvif3rxstartflg = (U1)TRUE;
            u1_s_gvif3rxchkflg = (U1)TRUE;
            u1_s_gvif3rxchk_cnt = (U1)GVIF3RX_CNT_CLR;
            u1_s_gvif3maintask_step = (U1)GVIF3RX_MAINTASK_STEP3;
            break;
    
        case GVIF3RX_MAINTASK_STEP3:
            if(u1_s_gvif3rxchk_cnt >= (U1)GVIF3RX_CHKTIME){
                u1_s_gvif3rxchkflg = (U1)TRUE;
            }
            break;
    
        default:
            u1_s_gvif3maintask_step = (U1)GVIF3RX_MAINTASK_STEP1;
            break;
    }

    if(u1_s_gvif3rxchkflg == (U1)TRUE){
        vd_s_Gvif3RxCycChk();
    }
    if(u1_s_gvif3rxstartflg == (U1)TRUE){
        vd_s_Gvif3Restart();
    }
    if(u1_s_gvif3rxsipfailflg == (U1)TRUE){
        vd_s_Gvif3SipFailTask();
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_Gvif3RxCycChk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_Gvif3RxCycChk(void)
{
    U1 u1_t_stasts;
    U1 u1_t_date;
    U1 u1_t_jdg;
    
    u1_t_stasts = u1_g_PictCtl_StartSts();/* 見た目オン起動情報取得(暫定) */
    u1_t_date = (U1)0U;
    u1_t_jdg = (U1)FALSE;


    switch (u1_s_gvif3perimoni_step)
    {
        case GVIF3RX_PERIMONI_STEP1:
            if(u1_s_gvifcamKind_last != u1_s_gvif3rxcamkind_now){
                u1_s_gvifcamKind_last = u1_s_gvif3rxcamkind_now;
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP2;
            }
            else{
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP3;
            }
            break;
        case GVIF3RX_PERIMONI_STEP2:
            u1_t_jdg = u1_s_Gvif3RxCamKindDatSet();
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP3;
            }
            break;
        case GVIF3RX_PERIMONI_STEP3:
            if(u1_s_gvif3rxcamkind_now != (U1)GVIF3RX_KIND_CAM_NONE){
                u1_t_jdg = u1_s_Gvif3Mipijdg();
                if(u1_t_jdg == (U1)TRUE){
                    u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP4;
                }
            }
            else{
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP12;/* カメラ有無共通のSTEPへ */
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP4:  /* デバイス異常レジスタ読み出し */
            u1_t_jdg = u1_s_Gvif3DevErrChk();
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP5;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP5:
            u1_t_date = (U1)st_sp_GVIF3RX_REG_DEVERROR[1].u1p_pdu[1];
            if(u1_t_date != (U1)GVIF3RX_GETREG_DEV_NORMAL){
                /* ダイレコ 再起動要求(暫定) */
                u1_s_gvif3rxrestartflg = (U1)GVIF3_RESTART_FLGON;
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP_FIN; /* 定期終了 */
            }
            else{
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP6;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP6:
            if(u1_t_stasts == (U1)PICT_NOREDUN_STATE_APPON){/* 見た目オン起動(暫定) */
                u1_t_jdg = u1_s_Gvif3LinkChk();
                if(u1_t_jdg == (U1)TRUE){
                    u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP7;
                }
            }
            else{
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP7;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP7:
            if(u1_s_gvif3rx0unconflg == (U1)GVIF3_UNCON_FLGOFF){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP8;
            }
            else{
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP10;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP8:
            u1_t_jdg = u1_s_Gvif3Error1Chk();
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP9;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP9:
            u1_t_jdg = u1_s_Gvif3Error3Chk();
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP10;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP10:
            if(u1_s_gvif3rx1unconflg == (U1)GVIF3_UNCON_FLGOFF){
                u1_t_jdg = u1_s_Gvif3Error2Chk();
                if(u1_t_jdg == (U1)TRUE){
                    u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP11;
                }
            }
            else{
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP11;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP11:
            if((u1_s_gvif3rx0unconflg == (U1)GVIF3_UNCON_FLGOFF) && (u1_s_gvif3rx1unconflg == (U1)GVIF3_UNCON_FLGOFF)){
                u1_t_jdg = u1_s_Gvif3Error4Chk();
                if(u1_t_jdg == (U1)TRUE){
                    u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP12;
                }
            }
            else{
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP12;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP12:
            u1_t_jdg = u1_s_Gvif3Error5Chk();
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP13;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP13:
            u1_t_jdg = u1_s_Gvif3Error6Chk();
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP14;
            }
            break;

        case GVIF3RX_PERIMONI_STEP14:
            u1_t_jdg = u1_s_Gvif3Bank2Chg();
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP15;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP15:
            u1_t_jdg = u1_s_Gvif3Error7Chk();
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP16;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP16:
            u1_t_jdg = u1_s_Gvif3Error8Chk();
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP17;
            }
            break;

        case GVIF3RX_PERIMONI_STEP17:
            u1_t_jdg = u1_s_Gvif3Bank3Chg();
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP18;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP18:
            u1_t_jdg = u1_s_Gvif3Error9Chk();
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP19;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP19:
            u1_t_jdg = u1_s_Gvif3Error10Chk();
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP20;
            }
            break;

        case GVIF3RX_PERIMONI_STEP20:
            u1_t_jdg = u1_s_Gvif3Bank0Chg();
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP21;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP21:
            u1_t_jdg = (U1)Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (U2)GVIF3RX_OUTSET_WRINUM,
                                       (U1)GP_I2C_MA_SLA_2_GVIF_RX, st_sp_GVIFRX_OUTSET, &u4_s_gcif3acktime,
                                       st_sp_GVIF3RX_REG_ERRCLRSET, &u2_s_gvif3rxregset_betwaittime_stub);
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP22;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP22:
            u1_t_jdg = (U1)Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (U2)GVIF3RX_OUTSET_WRINUM,
                                       (U1)GP_I2C_MA_SLA_2_GVIF_RX, st_sp_GVIFRX_OUTSET, &u4_s_gcif3acktime,
                                       st_sp_GVIF3RX_REG_ERRCLRRLS, &u2_s_gvif3rxregset_betwaittime_stub);
            if(u1_t_jdg == (U1)TRUE){
                u1_s_gvif3rxchkflg = (U1)FALSE;
                u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP1;
            }
            break;
    
        case GVIF3RX_PERIMONI_STEP_FIN:
            /* 何もしない */
            break;
    
        default:
            u1_s_gvif3perimoni_step = (U1)GVIF3RX_PERIMONI_STEP1;
            break;
    }
}

/*===================================================================================================================================*/
/*  void    vd_g_HmiProxyMainTask(void)                                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gvif3RxCamKindPut(U1 u1_a_CAMEXSIT)
{
    if(u1_a_CAMEXSIT == (U1)PICT_KIND_DOMECON_EXIST){
        u1_s_gvif3rxcamkind_now = (U1)GVIF3RX_KIND_DOMECON_EXIST;
    }
    else{
        u1_s_gvif3rxcamkind_now = (U1)GVIF3RX_KIND_CAM_NONE;
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_Gvif3RxCamKindDatSet(void)                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3RxCamKindDatSet(void)
{
    static const ST_REG_WRI_REQ st_sp_GVIF3RX_CANKINDSET[GVIF3RX_CANKINDSET_WRINUM] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},
        {        1,         2,         0},
        {        3,         1,         0},
        {        4,         2,         0},
        {        6,         1,         0},
        {        7,         2,         0},
        {        9,         1,         0},
        {       10,         2,         0},
        {       12,         1,         0}
    };
    
    U1 u1_t_return;
    U1 u1_t_sts;

    if(u1_s_gvifcamKind_last == (U1)GVIF3RX_KIND_DOMECON_EXIST){
        u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (U2)GVIF3RX_CANKINDSET_WRINUM,
                                               (U1)GP_I2C_MA_SLA_2_GVIF_RX, st_sp_GVIF3RX_CANKINDSET, &u4_s_gcif3acktime,
                                               st_sp_MCU_SYS_PWR_GVIF3RX_REG_DOMCON, &u2_s_gvif3rxregset_betwaittime_stub);
    }
    else{
        u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (U2)GVIF3RX_CANKINDSET_WRINUM,
                                               (U1)GP_I2C_MA_SLA_2_GVIF_RX, st_sp_GVIF3RX_CANKINDSET, &u4_s_gcif3acktime,
                                                st_sp_MCU_SYS_PWR_GVIF3RX_REG_CAMNON, &u2_s_gvif3rxregset_betwaittime_stub);
    }
    
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  void    vd_g_Gvif3RxStby3StsSet(U1 u1_a_stby3sts)                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Gvif3RxStby3StsSet(U1 u1_a_stby3sts)
{
    u1_s_gvif3rxstby3sts = u1_a_stby3sts;
}

/*===================================================================================================================================*/
/*  static void    vd_s_Gvif3Mipijdg(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Mipijdg(void)
{
    U1 u1_t_return;
    U1 u1_t_siperr;
    U1 u1_t_sts;
    U1 u1_t_writedate;
    
    u1_t_return = (U1)FALSE;
    u1_t_siperr = u1_s_PictCtl_SiPErrstsInfo();
    u1_t_sts = (U1)FALSE;
    u1_t_writedate = (U1)0U;

    switch (u1_s_gvif3mipi_step)
    {
        case GVIF3RX_MIPI_STEP1:
            u1_t_sts = u1_s_Gvif3Bank0Chg();
            if(u1_t_sts == (U1)TRUE){
               /* 全書込み完了 次状態に遷移 */
                u1_s_gvif3mipi_step = (U1)GVIF3RX_MIPI_STEP2;
            }
            break;

        case GVIF3RX_MIPI_STEP2:
            if(Mcu_OnStep_EIZOIC_OVRALL == (uint8)MCU_STEP_EIZOIC_OVERALL_FIN){ /* 映像IC初期化済み(暫定) */
                u1_t_writedate |= (U1)GVIF3RX_VIDEO_OUTPUT_ENABLE_0;
            }
            if((u1_s_gvif3rxstby3sts == (U1)TRUE) && (u1_t_siperr == (U1)PICT_SIP_ERR_OFF)){
                u1_t_writedate |= (U1)GVIF3RX_VIDEO_OUTPUT_ENABLE_1;
            }
            u1_s_gvif3rxmipitx_date = u1_t_writedate;
            u1_s_gvif3mipi_step = (U1)GVIF3RX_MIPI_STEP3;
            break;
    
        case GVIF3RX_MIPI_STEP3:
            u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (U2)GVIF3RX_OUTSET_WRINUM,
                                                   (U1)GP_I2C_MA_SLA_2_GVIF_RX, st_sp_GVIFRX_OUTSET, &u4_s_gcif3acktime,
                                                    &st_sp_GVIF3RX_REG_MIPI_WR[u1_s_gvif3rxmipitx_date], &u2_s_gvif3rxregset_betwaittime_stub);
            if(u1_t_sts == (U1)TRUE){
                u1_t_return = (U1)TRUE;
                u1_s_gvif3mipi_step = (U1)GVIF3RX_MIPI_STEP1;
            }

            break;
    
        default:
            u1_s_gvif3mipi_step = (U1)GVIF3RX_MIPI_STEP1;
        
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static void    vd_s_Gvif3Error1Chk(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3DevErrChk(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (uint8)GP_I2C_MA_SLA_2_GVIF_RX,
                                            &u4_s_gcif3acktime, st_sp_GVIF3RX_REG_DEVERROR, &u2_s_gvif3rxregset_betwaittime_stub);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  void    vd_g_Gvif3SipFail(void)                                                                                                  */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void     vd_g_Gvif3SipFail(void)
{
    u1_s_gvif3rxsipfailflg = (U1)TRUE;
}

/*===================================================================================================================================*/
/*  static void     vd_s_Gvif3SipFailTask(void)                                                                                      */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_Gvif3SipFailTask(void)
{
    U1 u1_t_sts;
    U1 u1_t_writedate;
    
    u1_t_sts = (U1)FALSE;
    u1_t_writedate = (U1)0U;

    switch (u1_s_gvif3siperr_step)
    {
        case GVIF3RX_SIPERR_STEP1:
    /* BANK0への書き換えが必要 */
            u1_t_sts = u1_s_Gvif3Bank0Chg();
            if(u1_t_sts == (U1)TRUE){
               /* 全書込み完了 次状態に遷移 */
                u1_s_gvif3siperr_step = (U1)GVIF3RX_SIPERR_STEP2;
            }
            break;

        case GVIF3RX_SIPERR_STEP2:
            if(Mcu_OnStep_EIZOIC_OVRALL == (uint8)MCU_STEP_EIZOIC_OVERALL_FIN){ /* 映像IC初期化済み(暫定) */
                u1_t_writedate |= (U1)GVIF3RX_VIDEO_OUTPUT_ENABLE_0;
            }
            u1_s_gvif3rxsiperr_date = u1_t_writedate;
            u1_s_gvif3siperr_step = (U1)GVIF3RX_MIPI_STEP3;
            break;
    
        case GVIF3RX_MIPI_STEP3:
            u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (U2)GVIF3RX_OUTSET_WRINUM,
                                                   (U1)GP_I2C_MA_SLA_2_GVIF_RX, st_sp_GVIFRX_OUTSET, &u4_s_gcif3acktime,
                                                    &st_sp_GVIF3RX_REG_MIPI_WR[u1_s_gvif3rxsiperr_date], &u2_s_gvif3rxregset_betwaittime_stub);
            if(u1_t_sts == (U1)TRUE){
                u1_s_gvif3rxsipfailflg = (U1)FALSE;
                u1_s_gvif3siperr_step = (U1)GVIF3RX_SIPERR_STEP1;
            }
            break;
    
        default:
            u1_s_gvif3siperr_step = (U1)GVIF3RX_SIPERR_STEP1;
            break;
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_Gvif3Restar(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void     vd_s_Gvif3Restart(void)
{
    U1 u1_t_sts;
    
    u1_t_sts = (U1)Dio_ReadChannel(GVIF3RX_PORT_CAM_RST);
    if(u1_s_gvif3rxrestartcnt < (U1)U1_MAX){
        u1_s_gvif3rxrestartcnt++;
    }
    
    if(u1_s_gvif3rxrestartflg == (U1)GVIF3_RESTART_FLGON){
        if(u1_t_sts == (U1)TRUE){
            Dio_WriteChannel(GVIF3RX_PORT_CAM_RST, (Dio_LevelType)FALSE);
            u1_s_gvif3rxrestartcnt = (U1)GVIF3RX_CNT_CLR;
        }
        if(u1_s_gvif3rxrestartcnt >= GVIF3_RESTART_WAIT){
            Dio_WriteChannel(GVIF3RX_PORT_CAM_RST, (Dio_LevelType)TRUE);
            vd_g_Gvif3RxInit();
        }
    }
}

/*===================================================================================================================================*/
/*  static void    vd_s_Gvif3LinkChk(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3LinkChk(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;
    U1 u1_t_jdg;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)0U;
    u1_t_jdg = (U1)0U;


    switch (u1_s_gvif3link_step)
    {
        case GVIF3RX_LINK_STEP1:
            u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (uint8)GP_I2C_MA_SLA_2_GVIF_RX,
                                                     &u4_s_gcif3acktime, st_sp_GVIF3RX_REG_LINKCHK, &u2_s_gvif3rxregset_betwaittime_stub);
            if(u1_t_sts == (U1)TRUE){
               /* 全書込み完了 次状態に遷移 */
                u1_s_gvif3link_step = (U1)GVIF3RX_LINK_STEP2;
            }
            break;

        case GVIF3RX_LINK_STEP2:
            u1_t_jdg = (U1)st_sp_GVIF3RX_REG_LINKCHK[1].u1p_pdu[1] & (U1)GVIF3_RX0_UNCON_MASK;
            if(u1_t_jdg == (U1)GVIF3_UNCON_IDLE){
                if(u1_s_gvif3rx0unconcnt < (U1)U1_MAX){
                    u1_s_gvif3rx0unconcnt++;
                }
                if(u1_s_gvif3rx0unconcnt >= (U1)GVIF3_UNCON_CNT_CNF){
                    if(u1_s_gvif3rx0unconflg == (U1)GVIF3_UNCON_FLGOFF){
                        /* ダイレコ Rob①(暫定) */
                        u1_s_gvif3rx0unconflg = (U1)GVIF3_UNCON_FLGON;
                    }
                }
            }
            else{
                u1_s_gvif3rx0unconcnt = (U1)GVIF3RX_CNT_CLR;
            }
            u1_t_jdg = (U1)st_sp_GVIF3RX_REG_LINKCHK[1].u1p_pdu[1] & (U1)GVIF3_RX1_UNCON_MASK;
            if(u1_t_jdg == (U1)GVIF3_UNCON_IDLE){
                if(u1_s_gvif3rx1unconcnt < (U1)U1_MAX){
                    u1_s_gvif3rx1unconcnt++;
                }
                if(u1_s_gvif3rx1unconcnt >= (U1)GVIF3_UNCON_CNT_CNF){
                    if(u1_s_gvif3rx1unconflg == (U1)GVIF3_UNCON_FLGOFF){
                        /* ダイレコ Rob②(暫定) */
                        u1_s_gvif3rx1unconflg = (U1)GVIF3_UNCON_FLGON;
                    }
                }
            }
            else{
                u1_s_gvif3rx1unconcnt = (U1)GVIF3RX_CNT_CLR;
            }
            u1_t_return = (U1)TRUE;
            u1_s_gvif3link_step = (U1)GVIF3RX_LINK_STEP1;
            break;

        default:
            u1_s_gvif3link_step = (U1)GVIF3RX_LINK_STEP1;
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static void    vd_s_Gvif3Error1Chk(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error1Chk(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;
    U1 u1_t_jdg;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)0U;
    u1_t_jdg = (U1)0U;

    switch (u1_s_gvif3error1_step)
    {
        case GVIF3RX_ERROR1_STEP1:
            u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (uint8)GP_I2C_MA_SLA_2_GVIF_RX,
                                                     &u4_s_gcif3acktime, st_sp_GVIF3RX_REG_EERROR1CHK, &u2_s_gvif3rxregset_betwaittime_stub);
            if(u1_t_sts == (U1)TRUE){
               /* 全書込み完了 次状態に遷移 */
                u1_s_gvif3error1_step = (U1)GVIF3RX_ERROR1_STEP2;
            }
            break;

        case GVIF3RX_ERROR1_STEP2:
            u1_t_jdg = (U1)st_sp_GVIF3RX_REG_EERROR1CHK[1].u1p_pdu[1] & (U1)GVIF3_ERRORCHK_MASK;
            if(u1_t_jdg != (U1)GVIF3_ERRORCHK_NON){
                if(u1_s_gvif3rxerror1chkcnt < (U1)GVIF3_ERROR_MAXLOGCNT){
                    /* ダイレコ */
                    u1_s_gvif3rxerror1chkcnt++;
                }
            }
    		u1_t_return = (U1)TRUE;
            u1_s_gvif3error1_step = (U1)GVIF3RX_ERROR1_STEP1;
            break;

        default:
            u1_s_gvif3error1_step = (U1)GVIF3RX_ERROR1_STEP1;
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static void    vd_s_Gvif3Error2Chk(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error2Chk(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;
    U1 u1_t_jdg;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)0U;
    u1_t_jdg = (U1)0U;

    switch (u1_s_gvif3error2_step)
    {
        case GVIF3RX_ERROR2_STEP1:
            u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (uint8)GP_I2C_MA_SLA_2_GVIF_RX,
                                                     &u4_s_gcif3acktime, st_sp_GVIF3RX_REG_EERROR2CHK, &u2_s_gvif3rxregset_betwaittime_stub);
            if(u1_t_sts == (U1)TRUE){
               /* 全書込み完了 次状態に遷移 */
                u1_s_gvif3error2_step = (U1)GVIF3RX_ERROR2_STEP2;
            }
            break;

        case GVIF3RX_ERROR2_STEP2:
            u1_t_jdg = (U1)st_sp_GVIF3RX_REG_EERROR2CHK[1].u1p_pdu[1] & (U1)GVIF3_ERRORCHK_MASK;
            if(u1_t_jdg != (U1)GVIF3_ERRORCHK_NON){
                if(u1_s_gvif3rxerror2chkcnt < (U1)GVIF3_ERROR_MAXLOGCNT){
                    /* ダイレコ */
                    u1_s_gvif3rxerror2chkcnt++;
                }
            }
    		u1_t_return = (U1)TRUE;
            u1_s_gvif3error2_step = (U1)GVIF3RX_ERROR2_STEP1;
            break;

        default:
            u1_s_gvif3error2_step = (U1)GVIF3RX_ERROR2_STEP1;
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static void    vd_s_Gvif3Error3Chk(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error3Chk(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;
    U1 u1_t_jdg;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)0U;
    u1_t_jdg = (U1)0U;

    switch (u1_s_gvif3error3_step)
    {
        case GVIF3RX_ERROR3_STEP1:
            u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (uint8)GP_I2C_MA_SLA_2_GVIF_RX,
                                                     &u4_s_gcif3acktime, st_sp_GVIF3RX_REG_EERROR3CHK, &u2_s_gvif3rxregset_betwaittime_stub);
            if(u1_t_sts == (U1)TRUE){
               /* 全書込み完了 次状態に遷移 */
                u1_s_gvif3error3_step = (U1)GVIF3RX_ERROR3_STEP2;
            }
            break;

        case GVIF3RX_ERROR3_STEP2:
            u1_t_jdg = (U1)st_sp_GVIF3RX_REG_EERROR3CHK[1].u1p_pdu[1] & (U1)GVIF3_ERRORCHK_MASK;
            if(u1_t_jdg != (U1)GVIF3_ERRORCHK_NON){
                if(u1_s_gvif3rxerror3chkcnt < (U1)GVIF3_ERROR_MAXLOGCNT){
                    /* ダイレコ */
                    u1_s_gvif3rxerror3chkcnt++;
                }
            }
    		u1_t_return = (U1)TRUE;
            u1_s_gvif3error3_step = (U1)GVIF3RX_ERROR3_STEP1;
            break;

        default:
            u1_s_gvif3error3_step = (U1)GVIF3RX_ERROR3_STEP1;
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static void    vd_s_Gvif3Error4Chk(void)                                                                                         */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error4Chk(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;
    U1 u1_t_jdg;

    u1_t_return = (U1)FALSE;
    u1_t_sts = (U1)0U;
    u1_t_jdg = (U1)0U;

    switch (u1_s_gvif3error4_step)
    {
        case GVIF3RX_ERROR4_STEP1:
            u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (uint8)GP_I2C_MA_SLA_2_GVIF_RX,
                                                     &u4_s_gcif3acktime, st_sp_GVIF3RX_REG_EERROR4CHK, &u2_s_gvif3rxregset_betwaittime_stub);
            if(u1_t_sts == (U1)TRUE){
               /* 全書込み完了 次状態に遷移 */
                u1_s_gvif3error4_step = (U1)GVIF3RX_ERROR4_STEP2;
            }
            break;

        case GVIF3RX_ERROR4_STEP2:
            u1_t_jdg = (U1)st_sp_GVIF3RX_REG_EERROR4CHK[1].u1p_pdu[1] & (U1)GVIF3_ERRORCHK_MASK;
            if(u1_t_jdg != (U1)GVIF3_ERRORCHK_NON){
                if(u1_s_gvif3rxerror4chkcnt < (U1)GVIF3_ERROR_MAXLOGCNT){
                    /* ダイレコ */
                    u1_s_gvif3rxerror4chkcnt++;
                }
            }
    		u1_t_return = (U1)TRUE;
            u1_s_gvif3error4_step = (U1)GVIF3RX_ERROR4_STEP1;
            break;

        default:
            u1_s_gvif3error4_step = (U1)GVIF3RX_ERROR4_STEP1;
            break;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error5Chk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error5Chk(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (uint8)GP_I2C_MA_SLA_2_GVIF_RX,
                                            &u4_s_gcif3acktime, st_sp_GVIF3RX_REG_EERROR5CHK, &u2_s_gvif3rxregset_betwaittime_stub);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error6Chk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error6Chk(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (uint8)GP_I2C_MA_SLA_2_GVIF_RX,
                                            &u4_s_gcif3acktime, st_sp_GVIF3RX_REG_EERROR6CHK, &u2_s_gvif3rxregset_betwaittime_stub);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error7Chk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error7Chk(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (uint8)GP_I2C_MA_SLA_2_GVIF_RX,
                                            &u4_s_gcif3acktime, st_sp_GVIF3RX_REG_EERROR7CHK, &u2_s_gvif3rxregset_betwaittime_stub);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error8Chk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error8Chk(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (uint8)GP_I2C_MA_SLA_2_GVIF_RX,
                                            &u4_s_gcif3acktime, st_sp_GVIF3RX_REG_EERROR8CHK, &u2_s_gvif3rxregset_betwaittime_stub);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error9Chk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error9Chk(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (uint8)GP_I2C_MA_SLA_2_GVIF_RX,
                                            &u4_s_gcif3acktime, st_sp_GVIF3RX_REG_EERROR9CHK, &u2_s_gvif3rxregset_betwaittime_stub);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Error10Chk(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Error10Chk(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegRead((uint8)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (uint8)GP_I2C_MA_SLA_2_GVIF_RX,
                                            &u4_s_gcif3acktime, st_sp_GVIF3RX_REG_EERROR10CHK, &u2_s_gvif3rxregset_betwaittime_stub);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Bank0Chg(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Bank0Chg(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;
    
    u1_t_return = (U1)FALSE;
	u1_t_sts = (U1)FALSE;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (U2)GVIF3RX_OUTSET_WRINUM,
                                           (U1)GP_I2C_MA_SLA_2_GVIF_RX, st_sp_GVIFRX_OUTSET, &u4_s_gcif3acktime,
                                           st_sp_GVIF3RX_REG_BANK0, &u2_s_gvif3rxregset_betwaittime_stub);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Bank2Chg(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Bank2Chg(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;
    
    u1_t_return = (U1)FALSE;
	u1_t_sts = (U1)FALSE;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (U2)GVIF3RX_OUTSET_WRINUM,
                                           (U1)GP_I2C_MA_SLA_2_GVIF_RX, st_sp_GVIFRX_OUTSET, &u4_s_gcif3acktime,
                                           st_sp_GVIF3RX_REG_BANK2, &u2_s_gvif3rxregset_betwaittime_stub);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*  static U1     u1_s_Gvif3Bank3Chg(void)                                                                                           */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static U1     u1_s_Gvif3Bank3Chg(void)
{
    U1 u1_t_return;
    U1 u1_t_sts;
    
    u1_t_return = (U1)FALSE;
	u1_t_sts = (U1)FALSE;

    u1_t_sts = (U1)Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_GVIF_RX, &u2_s_gvif3rx_regstep, (U2)GVIF3RX_OUTSET_WRINUM,
                                           (U1)GP_I2C_MA_SLA_2_GVIF_RX, st_sp_GVIFRX_OUTSET, &u4_s_gcif3acktime,
                                           st_sp_GVIF3RX_REG_BANK3, &u2_s_gvif3rxregset_betwaittime_stub);
    if(u1_t_sts == (U1)TRUE){
        u1_t_return = (U1)TRUE;
    }
    return(u1_t_return);
}

/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  0.0.0    01/28/2025  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  Revision Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*                                                                                                                                   */
/*  * TN   = Tatsuya Niimi, KSE                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
