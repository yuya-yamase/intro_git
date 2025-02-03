/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "ML86294Ctl.h"

#include "Dio.h"
#include "gpi2c_ma.h"
#include "Mcu_I2c_Ctrl_private.h"
#include "pictic.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define ML86294_TASK_TIME       (1U)

#define ML86294_SEQ_IDLE        (0U)
#define ML86294_SEQ_CYC         (1U)
#define ML86294_SEQ_DEV_RST     (2U)
#define ML86294_SEQ_FRZ_INT     (3U)

#define ML86294_BANKSET_WRINUM  (1U)

#define ML86294_CYCCHK_STEP0    (0U)
#define ML86294_CYCCHK_STEP1    (1U)
#define ML86294_CYCCHK_STEP2    (2U)
#define ML86294_CYCCHK_STEP3    (3U)
#define ML86294_CYCCHK_STEP4    (4U)
#define ML86294_CYCCHK_STEP5    (5U)
#define ML86294_CYCCHK_STEP6    (6U)
#define ML86294_CYCCHK_STEP7    (7U)
#define ML86294_CYCCHK_STEP8    (8U)
#define ML86294_CYCCHK_STEP9    (9U)
#define ML86294_CYCCHK_STEP10   (10U)


#define ML86294_FRZDAT_CYCCHK_STEP0    (0U)
#define ML86294_FRZDAT_CYCCHK_STEP1    (1U)
#define ML86294_FRZDAT_CYCCHK_STEP2    (2U)
#define ML86294_FRZDAT_CYCCHK_STEP3    (3U)
#define ML86294_FRZDAT_CYCCHK_STEP4    (4U)
#define ML86294_FRZDAT_CYCCHK_STEP5    (5U)
#define ML86294_FRZDAT_CYCCHK_STEP6    (6U)
#define ML86294_FRZDAT_CYCCHK_STEP7    (7U)
#define ML86294_FRZDAT_CYCCHK_STEP8    (8U)
#define ML86294_FRZDAT_CYCCHK_STEP9    (9U)
#define ML86294_FRZDAT_CYCCHK_STEP10   (10U)
#define ML86294_FRZDAT_CYCCHK_STEP11   (11U)
#define ML86294_FRZDAT_CYCCHK_STEP12   (12U)
#define ML86294_FRZDAT_CYCCHK_STEP13   (13U)
#define ML86294_FRZDAT_CYCCHK_STEP14   (14U)
#define ML86294_FRZDAT_CYCCHK_STEP15   (15U)
#define ML86294_FRZDAT_CYCCHK_STEP16   (16U)
#define ML86294_FRZDAT_CYCCHK_STEP17   (17U)
#define ML86294_FRZDAT_CYCCHK_STEP18   (18U)


#define ML86294_IRQHPD_CYCCHK_STEP0    (0U)
#define ML86294_IRQHPD_CYCCHK_STEP1    (1U)
#define ML86294_IRQHPD_CYCCHK_STEP2    (2U)
#define ML86294_IRQHPD_CYCCHK_STEP3    (3U)
#define ML86294_IRQHPD_CYCCHK_STEP4    (4U)
#define ML86294_IRQHPD_CYCCHK_STEP5    (5U)
#define ML86294_IRQHPD_CYCCHK_STEP6    (6U)
#define ML86294_IRQHPD_CYCCHK_STEP7    (7U)
#define ML86294_IRQHPD_CYCCHK_STEP8    (8U)
#define ML86294_IRQHPD_CYCCHK_STEP9    (9U)
#define ML86294_IRQHPD_CYCCHK_STEP10   (10U)
#define ML86294_IRQHPD_CYCCHK_STEP11   (11U)
#define ML86294_IRQHPD_CYCCHK_STEP12   (12U)
#define ML86294_IRQHPD_CYCCHK_STEP13   (13U)
#define ML86294_IRQHPD_CYCCHK_STEP14   (14U)

#define ML86294_IRQHPD_DPCD_SET1_WRINUM    (1U)
#define ML86294_IRQHPD_DPCD_READSET_SET_WRINUM    (1U)
#define ML86294_IRQHPD_DPCD_REGNUM_SET_WRINUM    (1U)
#define ML86294_IRQHPD_DPCD_AUXSND_READSET_SET_WRINUM    (1U)
#define ML86294_IRQHPD_DPCD_SET2_WRINUM    (1U)
#define ML86294_IRQHPD_DPCD_SET3_WRINUM    (15U)


#define ML86294_CAMAREA_SET_STEP0    (0U)
#define ML86294_CAMAREA_SET_STEP1    (1U)
#define ML86294_CAMAREA_SET_STEP2    (2U)
#define ML86294_CAMAREA_SET_STEP3    (3U)
#define ML86294_CAMAREA_SET_STEP4    (4U)
#define ML86294_CAMAREA_SET_STEP5    (5U)
#define ML86294_CAMAREA_SET_STEP6    (6U)
#define ML86294_CAMAREA_SET_STEP7    (7U)
#define ML86294_CAMAREA_SET_STEP8    (8U)
#define ML86294_CAMAREA_SET_STEP9    (9U)
#define ML86294_CAMAREA_SET_STEP10   (10U)

#define ML86294_CAMAREA_SET_WRINUM    (24U)

#define ML86294_MIPI_SET_WRINUM    (2U)

#define ML86294_FRZCHG_SET_ON_WRINUM    (10U)
#define ML86294_FRZCHG_SET_OFF_WRINUM   (10U)

#define ML86294_CAMPATH_SET_WRINUM    (4U)


#define ML86294_RCVVICSTATUS_STEP0    (0U)
#define ML86294_RCVVICSTATUS_STEP1    (1U)
#define ML86294_RCVVICSTATUS_STEP2    (2U)

#define ML86294_RCVVICSTATUS_CLEAR_SET_WRINUM    (1U)

#define ML86294_FRZCHG_ON_SET_WRINUM    (10U)
#define ML86294_FRZCHG_OFF_SET_WRINUM   (10U)

#define ML86294_I2CMUTE_SET_WRINUM    (2U)
#define ML86294_NOAISMUTE_SET_WRINUM    (2U)

#define ML86294_REGGET_STEP0            (0U)
#define ML86294_REGGET_STEP1            (1U)
#define ML86294_REGGET_STEP2            (2U)
#define ML86294_REGGET_FLAG_STOP        (0U)
#define ML86294_REGGET_FLAG_START       (1U)
#define ML86294_REGGET_FLAG_COMP        (2U)

#define ML86294_DEV_RST_STEP0    (0U)
#define ML86294_DEV_RST_STEP1    (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_pict_ml_state;                   /* ML86294 Sequence State */

static U2 u2_s_pict_ml_regstep;                 /* ML86294 Register Request Step */
static U4 u4_s_pict_ml_i2c_ack_wait_time;       /* ML86294 I2C Request Ack Wait Timer */
static U2 u2_s_pict_ml_reg_btwn_time;           /* ML86294 Access Register Between Timer */

static U1 u1_s_pict_dev_sts;                    /* MLDevice Status */
static U1 u1_s_pict_pre_dev_sts;                /* Previous MLDevice Status */

static U1 u1_s_pict_ml_frzint_chk_flg;          /* Freeze Detection Interrupt Check Flag */
static U1 u1_s_pict_ml_pre_v_ic_sts1_sts;       /* Previous V-IC-STATUS1 Status */


static U1 u1_s_pict_mlcycchk_sts;               /* Cycle Check Function Status */
static U2 u2_s_pict_ml_cycchk_timer;            /* Cycle Check Poling Timer */
static U1 u1_s_pict_mlcyc_dev_reset_cnt;        /* Device Error Device Reset Counter */
static U1 u1_s_pict_mlcyc_dev_rst_timer;        /* Device Restart Wait Poling Timer */

static U1 u1_s_pict_mlfrzdatcycchk_sts;         /* Freeze Cycle Check Function Status */
static U2 u2_s_pict_ml_frzdat_cycchk_timer;     /* Freeze Cycle Check Poling Timer */
static U1 u1_s_pict_mlfrzdatcyc_n1_cnt;         /* Freeze Cycle Check N1 Counter */
static U1 u1_s_pict_mlfrzdatcyc_n2_cnt;         /* Freeze Cycle Check N2 Counter */
static U1 u1_s_pict_mlfrzdatcyc_frz_drec_cnt;   /* Freeze Cycle Freeze Drec Counter */
static U1 u1_s_pict_mlfrzdatcyc_route_drec_cnt; /* Freeze Cycle Route Drec Counter */
static U1 u1_s_pict_mlfrzdatcyc_gpio0_sts;      /* Freeze Cycle Check DISP-REQ-GPIO0 Status */

static U1 u1_s_pict_mlirqhpdcycchk_sts;         /* IRQ_HPD Cycle Check Function Status */
static U2 u2_s_pict_ml_irqhpd_cycchk_timer;     /* IRQ_HPD Cycle Check Poling Timer */
static U1 u1_s_pict_mlirqhpdcyc_assert_drec_cnt; /* IRQ_HPD Cycle Assert Drec Counter */

static U1 u1_s_pict_mlcamarea_set_sts;          /* Camera Area Set Function Status */

static U1 u1_s_pict_mlrcvvicstatus_sts;         /* V-IC-STATUS1 Interrupt Function Status */

static U1 u1_s_pict_mlfrz_drec_cnt;             /* Freeze Detection Drec Counter */
static U1 u1_s_pict_mlfail_drec_cnt;            /* Device Error Drec Counter */
static U1 u1_s_pict_mlsync_pre_sip_sync_err;    /* Previous Sip Error Status */
static U1 u1_s_pict_mlsync_sip_drec_cnt;        /* Sync Error Sip Drec Counter */
static U1 u1_s_pict_mlsync_pre_cam_sync_err;    /* Previous Camera Error Status */
static U1 u1_s_pict_mlsync_cam_drec_cnt;        /* Sync Error Camera Drec Counter */
static U1 u1_s_pict_mlroute_pre_v_ic_sts2_sts;  /* Previous V-IC-STATUS2 Status */
static U1 u1_s_pict_mlroute_drec_cnt;           /* Route Change Drec Counter */
static U1 u1_s_pict_mlmipircv_drec_cnt;         /* Receiver Error Drec Counter */
static U1 u1_s_pict_mldevrst_sts;               /* Device Restart Status */

static U2 u2_s_pict_mlregget_timer;             /* MIPI Synchronize Function Poling Timer */
static U1 u1_s_pict_mlregget_flag;              /* MIPI Synchronize Function Start Flag */
static U1 u1_s_pict_mlregget_sts;               /* MIPI Synchronize Function Status */
static U1 u1_s_pict_mlregget_result;            /* MIPI Synchronize Read Result */

static U1 u1_s_pict_mldevrst_notif;             /* Device Restart Notification */

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static U1 u1_s_Pict_MLCycChk(void);
static U1 u1_s_Pict_Ml86294_TimChk(const U2 u2_a_tim_cnt, const U2 u2_a_wait_tim);
static U1 u1_s_Pict_MLFrzDatCycChk(void);
static U1 u1_s_Pict_MLIrqHpdCycChk(void);
static U1 u1_s_Pict_MlRcvVIcStatusNty(void);
static U1 u1_s_Pict_MLMIPISyncCheck(void);
static void vd_s_Pict_MLDevRst(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
static const ST_REG_WRI_REQ ML86294_BANKSET[ML86294_BANKSET_WRINUM] = {
    /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
    {        0,         1,         0}
};

const U1 u1_sp_ML86294_SET_BANK12[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x60U     /* Write Data */
};

const U1 u1_sp_ML86294_MLFRZDATCYCFRZBIT_RD_PDU1[ML86294_I2C_RWC_BYTE2] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x29U     /* Write Address */
};

U1 u1_sp_ML86294_MLFRZDATCYCFRZBIT_RD_PDU2[ML86294_I2C_RWC_BYTE2];

const U1 u1_sp_ML86294_SET_BANK2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_ML86294_MLFRZDATCYCROUTEBIT_RD_PDU1[ML86294_I2C_RWC_BYTE2] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xBEU     /* Write Address */
};

U1 u1_sp_ML86294_MLFRZDATCYCROUTEBIT_RD_PDU2[ML86294_I2C_RWC_BYTE2];

const U1 u1_sp_ML86294_SET_BANK8[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x40U     /* Write Data */
};

const U1 u1_sp_ML86294_MLIRQHPD_ASSERT_RD_PDU1[ML86294_I2C_RWC_BYTE2] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U     /* Write Address */
};

U1 u1_sp_ML86294_MLIRQHPD_ASSERT_RD_PDU2[ML86294_I2C_RWC_BYTE2];

const U1 u1_sp_MLIRQHPD_DPCD_SET1_DCPC202_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET1_DCPC202_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x25U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET1_DCPC202_SET3[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_READSET_RD_PDU1[ML86294_I2C_RWC_BYTE2] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U     /* Write Address */
};

U1 u1_sp_MLIRQHPD_DPCD_READSET_RD_PDU2[ML86294_I2C_RWC_BYTE2];

U1 u1_sp_MLIRQHPD_DPCD_READSET_SET_PDU[ML86294_I2C_RWC_BYTE3];

const U1 u1_sp_MLIRQHPD_DPCD_REGNUM_SET[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x27U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_AUXSND_READSET_RD_PDU1[ML86294_I2C_RWC_BYTE2] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x38U     /* Write Address */
};

U1 u1_sp_MLIRQHPD_DPCD_AUXSND_READSET_RD_PDU2[ML86294_I2C_RWC_BYTE2];

U1 u1_sp_MLIRQHPD_DPCD_AUXSND_READSET_SET_PDU[ML86294_I2C_RWC_BYTE3];

const U1 u1_sp_MLIRQHPD_DPCD_AUXCOM_RD1_PDU1[ML86294_I2C_RWC_BYTE2] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x28U     /* Write Address */
};

U1 u1_sp_MLIRQHPD_DPCD_AUXCOM_RD1_PDU2[ML86294_I2C_RWC_BYTE2];

const U1 u1_sp_MLIRQHPD_DPCD_AUXCOM_RD2_PDU1[ML86294_I2C_RWC_BYTE2] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x29U     /* Write Address */
};

U1 u1_sp_MLIRQHPD_DPCD_AUXCOM_RD2_PDU2[ML86294_I2C_RWC_BYTE2];

const U1 u1_sp_MLIRQHPD_DPCD_SET2_CLEAR_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET2_CLEAR_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET2_CLEAR_SET3[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_ALTMOFF_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x48U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_ALTMOFF_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x40U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x20U,    /* Write Address */
    (U1)0x0DU     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET3[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x21U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET4[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x80U,    /* Write Address */
    (U1)0x12U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET5[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x92U,    /* Write Address */
    (U1)0x20U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET6[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x48U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET7[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET8[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET9[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x08U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET10[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET11[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0xFCU     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET12[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x50U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET13[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x7FU     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET14[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x21U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET15[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x22U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET16[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x06U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET17[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET18[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x25U,    /* Write Address */
    (U1)0x14U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET19[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x15U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET20[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x27U,    /* Write Address */
    (U1)0x16U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET21[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x28U,    /* Write Address */
    (U1)0x16U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET22[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x29U,    /* Write Address */
    (U1)0x24U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET23[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2AU,    /* Write Address */
    (U1)0x25U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET24[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2BU,    /* Write Address */
    (U1)0x25U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET25[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2CU,    /* Write Address */
    (U1)0x25U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET26[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2DU,    /* Write Address */
    (U1)0x34U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET27[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2EU,    /* Write Address */
    (U1)0x34U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET28[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2FU,    /* Write Address */
    (U1)0x34U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET29[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x30U,    /* Write Address */
    (U1)0x34U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET30[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x31U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET31[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x32U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET32[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x33U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_CLEAR_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x40U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_CLEAR_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_CLEAR_SET3[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_CLEAR_SET4[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_ALTMON_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x48U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_ALTMON_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_VTSTART_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x40U     /* Write Data */
};

const U1 u1_sp_MLIRQHPD_DPCD_SET3_VTSTART_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x80U,    /* Write Address */
    (U1)0x92U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET3[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET4[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC7U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET5[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC8U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET6[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC9U,    /* Write Address */
    (U1)0x37U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET7[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCAU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET8[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCBU,    /* Write Address */
    (U1)0x7FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET9[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCCU,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET10[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF0U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET11[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF1U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET12[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF2U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET13[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF3U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET14[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF4U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET15[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET16[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET17[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET18[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET19[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x20U,    /* Write Address */
    (U1)0x6FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET20[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x21U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET21[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x22U,    /* Write Address */
    (U1)0x9FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET22[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET23[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET24[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x25U,    /* Write Address */
    (U1)0x09U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET25[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x37U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET26[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x38U,    /* Write Address */
    (U1)0x7EU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET27[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x39U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET28[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3AU,    /* Write Address */
    (U1)0x7EU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET29[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET30[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3CU,    /* Write Address */
    (U1)0x0CU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET31[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET32[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3EU,    /* Write Address */
    (U1)0x0CU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET33[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x58U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET34[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD0U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET35[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD1U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET36[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD2U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET37[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD3U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET38[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD4U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET39[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD5U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET40[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET41[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD7U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET42[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x60U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET43[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x6FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET44[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET45[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET46[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET47[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET48[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET49[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET50[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET51[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x08U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET52[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET53[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET54[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET55[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET56[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET57[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET58[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET59[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x10U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET60[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x11U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET61[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET62[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x13U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET63[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x14U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET64[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET65[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x16U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET66[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x17U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET67[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x18U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET68[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x19U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET69[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET70[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET71[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET72[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET73[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET74[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET75[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET76[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET77[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET78[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET79[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET80[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET81[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET82[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET83[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET84[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0x38U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET85[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET86[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x68U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET87[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x69U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET88[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET89[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET90[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET91[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET92[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET93[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET94[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x70U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET95[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x71U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET96[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x72U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET97[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x73U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET98[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x74U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET99[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x75U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET100[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x76U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET101[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x77U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET102[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x78U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET103[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x79U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET104[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET105[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET106[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET107[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET108[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET109[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET110[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET111[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x33U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET112[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET113[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x78U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET114[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA6U,    /* Write Address */
    (U1)0x7FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET115[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA7U,    /* Write Address */
    (U1)0x87U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET116[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xB0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET117[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x38U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET118[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET119[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET120[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET121[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xC8U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET122[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET123[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET124[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET125[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET126[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET127[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET128[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0x38U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET129[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET130[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET131[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x33U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET132[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET133[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET134[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET135[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET136[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET137[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET138[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET139[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET140[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET141[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET142[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET143[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET3[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET4[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC7U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET5[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC8U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET6[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC9U,    /* Write Address */
    (U1)0xB9U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET7[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCAU,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET8[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCBU,    /* Write Address */
    (U1)0x7FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET9[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCCU,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET10[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF0U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET11[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF1U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET12[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF2U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET13[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF3U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET14[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF4U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET15[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET16[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET17[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET18[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET19[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x20U,    /* Write Address */
    (U1)0x6FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET20[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x21U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET21[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x22U,    /* Write Address */
    (U1)0xF7U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET22[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET23[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET24[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x25U,    /* Write Address */
    (U1)0x09U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET25[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x37U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET26[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x38U,    /* Write Address */
    (U1)0x7EU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET27[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x39U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET28[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3AU,    /* Write Address */
    (U1)0x7EU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET29[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET30[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3CU,    /* Write Address */
    (U1)0x0CU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET31[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET32[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3EU,    /* Write Address */
    (U1)0x0CU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET33[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x58U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET34[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD0U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET35[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD1U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET36[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD2U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET37[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD3U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET38[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD4U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET39[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD5U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET40[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET41[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD7U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET42[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x60U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET43[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x6FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET44[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET45[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET46[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET47[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET48[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET49[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET50[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET51[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x08U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET52[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET53[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET54[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET55[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET56[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET57[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET58[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET59[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x10U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET60[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x11U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET61[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET62[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x13U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET63[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x14U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET64[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET65[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x16U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET66[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x17U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET67[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x18U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET68[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x19U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET69[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET70[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET71[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET72[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET73[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET74[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET75[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET76[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET77[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET78[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET79[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET80[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET81[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET82[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET83[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET84[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0xBAU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET85[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET86[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x68U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET87[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x69U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET88[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET89[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET90[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET91[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET92[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET93[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET94[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x70U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET95[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x71U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET96[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x72U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET97[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x73U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET98[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x74U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET99[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x75U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET100[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x76U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET101[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x77U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET102[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x78U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET103[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x79U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET104[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET105[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET106[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET107[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET108[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET109[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET110[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET111[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x33U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET112[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET113[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x78U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET114[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA6U,    /* Write Address */
    (U1)0x7FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET115[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA7U,    /* Write Address */
    (U1)0x87U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET116[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xB0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET117[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0xBAU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET118[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET119[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET120[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET121[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xC8U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET122[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET123[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET124[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET125[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET126[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET127[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET128[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0xBAU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET129[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET130[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET131[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x33U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET132[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET133[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET134[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET135[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET136[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET137[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET138[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET139[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET140[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET141[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET142[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET143[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET3[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET4[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC7U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET5[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC8U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET6[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC9U,    /* Write Address */
    (U1)0x83U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET7[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCAU,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET8[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCBU,    /* Write Address */
    (U1)0x7FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET9[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCCU,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET10[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF0U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET11[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF1U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET12[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF2U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET13[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF3U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET14[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF4U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET15[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET16[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET17[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET18[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET19[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x20U,    /* Write Address */
    (U1)0x6FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET20[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x21U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET21[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x22U,    /* Write Address */
    (U1)0xAFU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET22[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET23[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET24[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x25U,    /* Write Address */
    (U1)0x09U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET25[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x37U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET26[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x38U,    /* Write Address */
    (U1)0x7EU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET27[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x39U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET28[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3AU,    /* Write Address */
    (U1)0x7EU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET29[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET30[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3CU,    /* Write Address */
    (U1)0x0CU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET31[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET32[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3EU,    /* Write Address */
    (U1)0x0CU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET33[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x58U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET34[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD0U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET35[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD1U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET36[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD2U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET37[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD3U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET38[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD4U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET39[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD5U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET40[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET41[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD7U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET42[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x60U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET43[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x6FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET44[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET45[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET46[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET47[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET48[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET49[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET50[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET51[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x08U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET52[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET53[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET54[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET55[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET56[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET57[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET58[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET59[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x10U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET60[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x11U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET61[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET62[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x13U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET63[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x14U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET64[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET65[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x16U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET66[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x17U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET67[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x18U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET68[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x19U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET69[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET70[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET71[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET72[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET73[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET74[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET75[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET76[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET77[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET78[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET79[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET80[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET81[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET82[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET83[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET84[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0x84U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET85[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET86[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x68U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET87[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x69U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET88[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET89[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET90[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET91[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET92[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET93[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET94[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x70U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET95[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x71U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET96[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x72U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET97[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x73U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET98[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x74U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET99[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x75U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET100[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x76U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET101[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x77U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET102[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x78U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET103[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x79U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET104[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET105[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET106[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET107[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET108[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET109[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET110[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET111[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x33U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET112[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET113[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x78U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET114[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA6U,    /* Write Address */
    (U1)0x7FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET115[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA7U,    /* Write Address */
    (U1)0x87U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET116[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xB0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET117[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x84U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET118[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET119[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET120[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET121[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xC8U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET122[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET123[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET124[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET125[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET126[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET127[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET128[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0x84U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET129[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET130[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET131[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x33U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET132[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET133[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET134[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET135[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET136[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET137[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET138[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET139[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET140[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET141[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET142[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET143[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET3[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET4[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC7U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET5[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC8U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET6[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC9U,    /* Write Address */
    (U1)0xCFU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET7[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCAU,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET8[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCBU,    /* Write Address */
    (U1)0x7FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET9[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCCU,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET10[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF0U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET11[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF1U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET12[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF2U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET13[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF3U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET14[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF4U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET15[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET16[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET17[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET18[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET19[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x20U,    /* Write Address */
    (U1)0x6FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET20[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x21U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET21[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x22U,    /* Write Address */
    (U1)0xBFU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET22[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET23[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET24[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x25U,    /* Write Address */
    (U1)0x09U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET25[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x37U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET26[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x38U,    /* Write Address */
    (U1)0x7EU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET27[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x39U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET28[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3AU,    /* Write Address */
    (U1)0x7EU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET29[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET30[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3CU,    /* Write Address */
    (U1)0x0CU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET31[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET32[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3EU,    /* Write Address */
    (U1)0x0CU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET33[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x58U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET34[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD0U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET35[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD1U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET36[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD2U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET37[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD3U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET38[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD4U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET39[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD5U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET40[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET41[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD7U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET42[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x60U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET43[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x6FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET44[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET45[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET46[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET47[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET48[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET49[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET50[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET51[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x08U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET52[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET53[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET54[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET55[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET56[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET57[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET58[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET59[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x10U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET60[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x11U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET61[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET62[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x13U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET63[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x14U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET64[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET65[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x16U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET66[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x17U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET67[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x18U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET68[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x19U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET69[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET70[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET71[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET72[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET73[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET74[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET75[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET76[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET77[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET78[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET79[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET80[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET81[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET82[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET83[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET84[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0xD0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET85[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET86[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x68U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET87[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x69U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET88[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET89[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET90[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET91[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET92[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET93[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET94[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x70U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET95[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x71U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET96[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x72U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET97[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x73U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET98[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x74U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET99[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x75U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET100[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x76U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET101[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x77U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET102[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x78U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET103[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x79U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET104[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET105[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET106[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET107[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET108[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET109[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET110[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET111[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x33U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET112[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET113[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x78U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET114[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA6U,    /* Write Address */
    (U1)0x7FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET115[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA7U,    /* Write Address */
    (U1)0x87U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET116[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xB0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET117[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0xD0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET118[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET119[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET120[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET121[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xC8U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET122[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET123[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET124[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET125[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET126[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET127[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET128[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0xD0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET129[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET130[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET131[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x33U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET132[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET133[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET134[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET135[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET136[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET137[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET138[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET139[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET140[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET141[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET142[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET143[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET3[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET4[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC7U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET5[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC8U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET6[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC9U,    /* Write Address */
    (U1)0x4DU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET7[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCAU,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET8[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCBU,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET9[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCCU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET10[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF0U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET11[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF1U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET12[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF2U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET13[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF3U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET14[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF4U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET15[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET16[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET17[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET18[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET19[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x20U,    /* Write Address */
    (U1)0x2EU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET20[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x21U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET21[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x22U,    /* Write Address */
    (U1)0x9FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET22[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET23[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x81U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET24[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x25U,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET25[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x37U,    /* Write Address */
    (U1)0xB3U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET26[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x38U,    /* Write Address */
    (U1)0x7CU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET27[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x39U,    /* Write Address */
    (U1)0xB3U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET28[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3AU,    /* Write Address */
    (U1)0x7CU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET29[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3BU,    /* Write Address */
    (U1)0x66U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET30[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3CU,    /* Write Address */
    (U1)0x09U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET31[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3DU,    /* Write Address */
    (U1)0x67U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET32[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3EU,    /* Write Address */
    (U1)0x09U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET33[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x58U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET34[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD0U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET35[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD1U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET36[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD2U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET37[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD3U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET38[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD4U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET39[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD5U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET40[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET41[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD7U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET42[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x60U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET43[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x6FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET44[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET45[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET46[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET47[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET48[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET49[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET50[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET51[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x08U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET52[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET53[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET54[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET55[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET56[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET57[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET58[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET59[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x10U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET60[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x11U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET61[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET62[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x13U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET63[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x14U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET64[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET65[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x16U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET66[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x17U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET67[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x18U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET68[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x19U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET69[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET70[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET71[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET72[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET73[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET74[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET75[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET76[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET77[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET78[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET79[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET80[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET81[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET82[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET83[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET84[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0x4EU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET85[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET86[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x68U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET87[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x69U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET88[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET89[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET90[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET91[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET92[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET93[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET94[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x70U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET95[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x71U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET96[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x72U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET97[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x73U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET98[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x74U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET99[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x75U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET100[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x76U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET101[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x77U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET102[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x78U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET103[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x79U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET104[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET105[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET106[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET107[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET108[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET109[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET110[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET111[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x33U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET112[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET113[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x78U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET114[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA6U,    /* Write Address */
    (U1)0x7FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET115[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA7U,    /* Write Address */
    (U1)0x87U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET116[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xB0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET117[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x4EU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET118[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET119[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET120[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET121[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xC8U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET122[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET123[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET124[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET125[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET126[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET127[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET128[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0x4EU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET129[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET130[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET131[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x33U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET132[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET133[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET134[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET135[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET136[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET137[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET138[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET139[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET140[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET141[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET142[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET143[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET3[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET4[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC7U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET5[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC8U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET6[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC9U,    /* Write Address */
    (U1)0xCFU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET7[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCAU,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET8[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCBU,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET9[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCCU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET10[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF0U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET11[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF1U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET12[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF2U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET13[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF3U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET14[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF4U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET15[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET16[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET17[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET18[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET19[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x20U,    /* Write Address */
    (U1)0x6FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET20[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x21U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET21[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x22U,    /* Write Address */
    (U1)0x9FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET22[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET23[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET24[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x25U,    /* Write Address */
    (U1)0x09U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET25[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x37U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET26[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x38U,    /* Write Address */
    (U1)0x7CU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET27[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x39U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET28[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3AU,    /* Write Address */
    (U1)0x7CU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET29[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET30[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3CU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET31[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET32[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3EU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET33[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x58U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET34[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD0U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET35[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD1U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET36[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD2U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET37[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD3U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET38[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD4U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET39[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD5U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET40[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET41[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD7U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET42[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x60U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET43[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x6FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET44[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET45[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET46[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET47[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET48[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET49[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET50[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET51[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x08U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET52[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET53[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET54[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET55[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET56[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET57[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET58[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET59[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x10U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET60[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x11U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET61[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET62[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x13U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET63[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x14U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET64[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET65[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x16U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET66[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x17U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET67[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x18U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET68[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x19U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET69[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET70[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET71[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET72[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET73[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET74[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET75[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET76[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET77[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET78[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET79[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET80[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET81[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET82[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET83[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET84[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0xD0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET85[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET86[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x68U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET87[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x69U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET88[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET89[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET90[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET91[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET92[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET93[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET94[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x70U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET95[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x71U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET96[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x72U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET97[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x73U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET98[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x74U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET99[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x75U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET100[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x76U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET101[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x77U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET102[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x78U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET103[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x79U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET104[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET105[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET106[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET107[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET108[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET109[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET110[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET111[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x33U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET112[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET113[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x78U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET114[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA6U,    /* Write Address */
    (U1)0x7FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET115[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA7U,    /* Write Address */
    (U1)0x87U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET116[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xB0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET117[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0xD0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET118[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET119[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET120[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET121[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xC8U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET122[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET123[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET124[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET125[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET126[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET127[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET128[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0xD0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET129[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET130[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET131[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x33U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET132[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET133[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET134[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET135[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET136[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET137[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET138[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET139[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET140[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET141[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET142[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET143[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET3[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET4[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC7U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET5[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC8U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET6[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC9U,    /* Write Address */
    (U1)0x6CU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET7[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCAU,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET8[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCBU,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET9[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCCU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET10[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF0U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET11[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF1U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET12[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF2U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET13[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF3U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET14[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF4U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET15[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET16[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET17[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET18[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET19[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x20U,    /* Write Address */
    (U1)0x6FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET20[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x21U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET21[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x22U,    /* Write Address */
    (U1)0xD9U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET22[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET23[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET24[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x25U,    /* Write Address */
    (U1)0x09U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET25[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x37U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET26[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x38U,    /* Write Address */
    (U1)0x7CU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET27[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x39U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET28[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3AU,    /* Write Address */
    (U1)0x7CU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET29[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET30[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3CU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET31[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET32[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3EU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET33[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x58U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET34[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD0U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET35[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD1U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET36[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD2U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET37[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD3U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET38[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD4U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET39[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD5U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET40[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET41[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD7U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET42[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x60U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET43[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x6FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET44[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET45[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET46[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET47[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET48[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET49[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET50[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET51[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x08U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET52[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET53[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET54[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET55[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET56[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET57[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET58[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET59[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x10U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET60[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x11U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET61[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET62[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x13U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET63[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x14U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET64[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET65[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x16U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET66[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x17U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET67[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x18U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET68[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x19U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET69[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET70[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET71[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET72[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET73[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET74[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET75[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET76[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET77[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET78[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET79[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET80[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET81[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET82[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET83[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET84[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0x6DU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET85[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET86[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x68U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET87[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x69U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET88[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET89[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET90[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET91[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET92[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET93[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET94[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x70U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET95[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x71U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET96[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x72U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET97[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x73U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET98[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x74U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET99[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x75U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET100[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x76U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET101[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x77U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET102[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x78U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET103[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x79U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET104[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET105[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET106[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET107[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET108[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET109[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET110[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET111[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x33U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET112[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET113[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x78U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET114[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA6U,    /* Write Address */
    (U1)0x7FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET115[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA7U,    /* Write Address */
    (U1)0x87U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET116[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xB0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET117[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x6DU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET118[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET119[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET120[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET121[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xC8U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET122[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET123[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET124[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET125[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET126[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET127[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET128[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0x6DU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET129[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET130[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET131[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x33U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET132[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET133[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET134[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET135[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET136[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET137[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET138[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET139[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET140[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET141[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET142[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET143[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET3[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET4[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC7U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET5[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC8U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET6[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC9U,    /* Write Address */
    (U1)0xB9U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET7[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCAU,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET8[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCBU,    /* Write Address */
    (U1)0x9FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET9[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCCU,    /* Write Address */
    (U1)0x06U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET10[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF0U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET11[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF1U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET12[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF2U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET13[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF3U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET14[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF4U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET15[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET16[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET17[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET18[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET19[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x20U,    /* Write Address */
    (U1)0x6FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET20[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x21U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET21[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x22U,    /* Write Address */
    (U1)0x9FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET22[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET23[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET24[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x25U,    /* Write Address */
    (U1)0x09U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET25[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x37U,    /* Write Address */
    (U1)0x4CU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET26[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x38U,    /* Write Address */
    (U1)0x7DU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET27[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x39U,    /* Write Address */
    (U1)0x4CU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET28[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3AU,    /* Write Address */
    (U1)0x7DU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET29[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3BU,    /* Write Address */
    (U1)0x99U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET30[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3CU,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET31[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3DU,    /* Write Address */
    (U1)0x99U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET32[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3EU,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET33[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x58U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET34[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD0U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET35[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD1U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET36[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD2U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET37[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD3U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET38[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD4U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET39[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD5U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET40[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET41[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD7U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET42[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x60U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET43[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x6FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET44[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET45[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET46[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET47[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET48[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET49[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET50[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET51[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x08U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET52[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET53[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET54[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET55[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET56[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET57[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET58[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET59[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x10U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET60[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x11U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET61[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET62[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x13U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET63[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x14U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET64[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET65[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x16U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET66[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x17U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET67[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x18U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET68[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x19U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET69[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET70[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET71[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET72[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET73[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET74[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET75[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET76[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET77[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET78[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET79[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET80[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET81[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET82[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET83[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x06U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET84[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0xBAU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET85[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET86[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x68U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET87[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x69U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET88[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET89[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET90[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET91[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET92[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET93[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET94[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x70U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET95[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x71U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET96[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x72U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET97[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x73U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET98[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x74U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET99[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x75U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET100[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x76U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET101[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x77U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET102[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x78U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET103[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x79U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET104[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET105[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET106[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET107[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET108[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET109[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET110[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET111[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x33U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET112[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET113[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x78U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET114[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA6U,    /* Write Address */
    (U1)0x7FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET115[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA7U,    /* Write Address */
    (U1)0x87U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET116[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xB0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET117[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0xBAU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET118[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET119[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET120[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x06U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET121[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xC8U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET122[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET123[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET124[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET125[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET126[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET127[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x06U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET128[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0xBAU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET129[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET130[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET131[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x33U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET132[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET133[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET134[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET135[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET136[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET137[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET138[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET139[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET140[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET141[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET142[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET143[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET3[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET4[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC7U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET5[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC8U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET6[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC9U,    /* Write Address */
    (U1)0x6CU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET7[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCAU,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET8[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCBU,    /* Write Address */
    (U1)0x4FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET9[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCCU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET10[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF0U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET11[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF1U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET12[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF2U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET13[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF3U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET14[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF4U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET15[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET16[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET17[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET18[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET19[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x20U,    /* Write Address */
    (U1)0x6FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET20[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x21U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET21[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x22U,    /* Write Address */
    (U1)0x9FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET22[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET23[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET24[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x25U,    /* Write Address */
    (U1)0x09U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET25[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x37U,    /* Write Address */
    (U1)0x73U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET26[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x38U,    /* Write Address */
    (U1)0x7BU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET27[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x39U,    /* Write Address */
    (U1)0x73U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET28[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3AU,    /* Write Address */
    (U1)0x7BU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET29[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3BU,    /* Write Address */
    (U1)0xE6U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET30[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3CU,    /* Write Address */
    (U1)0x06U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET31[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3DU,    /* Write Address */
    (U1)0xE6U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET32[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3EU,    /* Write Address */
    (U1)0x06U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET33[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x58U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET34[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD0U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET35[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD1U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET36[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD2U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET37[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD3U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET38[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD4U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET39[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD5U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET40[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET41[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD7U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET42[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x60U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET43[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x6FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET44[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET45[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x21U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET46[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET47[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET48[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET49[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET50[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET51[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x08U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET52[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET53[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET54[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET55[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET56[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET57[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET58[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET59[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x10U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET60[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x11U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET61[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET62[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x13U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET63[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x14U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET64[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET65[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x16U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET66[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x17U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET67[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x18U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET68[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x19U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET69[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET70[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET71[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET72[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET73[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET74[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET75[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET76[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET77[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET78[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET79[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET80[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET81[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET82[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x50U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET83[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET84[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0x6DU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET85[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET86[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x68U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET87[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x69U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET88[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET89[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET90[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET91[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET92[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET93[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET94[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x70U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET95[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x71U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET96[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x72U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET97[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x73U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET98[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x74U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET99[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x75U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET100[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x76U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET101[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x77U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET102[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x78U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET103[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x79U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET104[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET105[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET106[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET107[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET108[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET109[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET110[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET111[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x33U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET112[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET113[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x78U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET114[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA6U,    /* Write Address */
    (U1)0x7FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET115[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA7U,    /* Write Address */
    (U1)0x87U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET116[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xB0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET117[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x6DU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET118[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET119[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x50U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET120[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET121[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xC8U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET122[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET123[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET124[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET125[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET126[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x50U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET127[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET128[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0x6DU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET129[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET130[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET131[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x33U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET132[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET133[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET134[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET135[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET136[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET137[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET138[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET139[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET140[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x05U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET141[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET142[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x1FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET143[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x13U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET3[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET4[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC7U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET5[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC8U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET6[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xC9U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET7[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCAU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET8[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCBU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET9[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCCU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET10[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF0U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET11[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF1U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET12[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF2U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET13[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF3U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET14[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF4U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET15[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xF5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET16[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET17[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET18[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET19[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x20U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET20[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x21U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET21[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x22U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET22[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET23[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET24[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x25U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET25[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x37U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET26[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x38U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET27[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x39U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET28[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET29[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET30[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET31[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET32[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET33[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x58U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET34[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD0U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET35[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD1U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET36[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD2U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET37[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD3U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET38[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD4U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET39[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD5U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET40[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET41[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xD7U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET42[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x60U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET43[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET44[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET45[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET46[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET47[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET48[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET49[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET50[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET51[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x08U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET52[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET53[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET54[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET55[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET56[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET57[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET58[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET59[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x10U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET60[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x11U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET61[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET62[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x13U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET63[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x14U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET64[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET65[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x16U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET66[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x17U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET67[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x18U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET68[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x19U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET69[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET70[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET71[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET72[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET73[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET74[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET75[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET76[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET77[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET78[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET79[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET80[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET81[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET82[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET83[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET84[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET85[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET86[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x68U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET87[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x69U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET88[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET89[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET90[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET91[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET92[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET93[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x6FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET94[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x70U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET95[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x71U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET96[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x72U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET97[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x73U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET98[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x74U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET99[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x75U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET100[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x76U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET101[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x77U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET102[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x78U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET103[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x79U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET104[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET105[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET106[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET107[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7DU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET108[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET109[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x7FU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET110[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET111[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET112[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET113[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x78U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET114[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA6U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET115[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA7U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET116[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xB0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET117[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x09U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET118[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET119[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0BU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET120[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x0CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET121[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xC8U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET122[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET123[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET124[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x02U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET125[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x03U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET126[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x04U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET127[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x05U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET128[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET129[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x07U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET130[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x23U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET131[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET132[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x26U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET133[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET134[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x61U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET135[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x62U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET136[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x63U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET137[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x64U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET138[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x65U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET139[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x66U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET140[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x67U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET141[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x83U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET142[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x84U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET143[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x86U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlMIPIREG_ON_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlMIPIREG_ON_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA7U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_ML86294_MlMIPIREG_OFF_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlMIPIREG_OFF_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA7U,    /* Write Address */
    (U1)0x90U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_ON_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_ON_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5AU,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_ON_SET3[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3CU,    /* Write Address */
    (U1)0x0EU     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_ON_SET4[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_ON_SET5[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x10U,    /* Write Address */
    (U1)0x82U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_ON_SET6[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x11U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_ON_SET7[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xC8U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_ON_SET8[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x85U,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_ON_SET9[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x60U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_ON_SET10[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x29U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_ON_SET11[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x89U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_ON_SET12[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xC8U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_ON_SET13[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x29U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_ON_SET14[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x89U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_OFF_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_OFF_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3CU,    /* Write Address */
    (U1)0x0FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_OFF_SET3[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_OFF_SET4[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x10U,    /* Write Address */
    (U1)0x86U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_OFF_SET5[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x11U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_OFF_SET6[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xC8U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_OFF_SET7[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x85U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_OFF_SET8[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x60U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_OFF_SET9[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x29U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_OFF_SET10[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x89U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_OFF_SET11[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0xC8U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_OFF_SET12[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x29U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_OFF_SET13[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x89U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_BYPASS_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_BYPASS_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x58U,    /* Write Address */
    (U1)0xDBU     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_BYPASS_SET3[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_BYPASS_SET4[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCCU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_BYPASS_SET5[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCCU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_BYPASS_SET6[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xBEU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlFRZCHGREG_BYPASS_SET7[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCCU,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_ML86294_MlCAMPATHREG_NORMAL_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlCAMPATHREG_NORMAL_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x58U,    /* Write Address */
    (U1)0x99U     /* Write Data */
};

const U1 u1_sp_ML86294_MlCAMPATHREG_NORMAL_SET3[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_ML86294_MlCAMPATHREG_NORMAL_SET4[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCCU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MlCAMPATHREG_NORMAL_SET5[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCCU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlCAMPATHREG_NORMAL_SET6[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xBEU,    /* Write Address */
    (U1)0x3FU     /* Write Data */
};

const U1 u1_sp_ML86294_MlCAMPATHREG_NORMAL_SET7[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xCCU,    /* Write Address */
    (U1)0x03U     /* Write Data */
};

const U1 u1_sp_ML86294_SET_BANK0[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MIPISYNCSTATUS_RD_PDU1[ML86294_I2C_RWC_BYTE2] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5FU     /* Write Address */
};

U1 u1_sp_ML86294_MIPISYNCSTATUS_RD_PDU2[ML86294_I2C_RWC_BYTE2];

const U1 u1_sp_ML86294_MlRCVVICSTATUS_RD_PDU1[ML86294_I2C_RWC_BYTE2] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5AU     /* Write Address */
};

U1 u1_sp_ML86294_MlRCVVICSTATUS_RD_PDU2[ML86294_I2C_RWC_BYTE2];

const U1 u1_sp_ML86294_MlRCVVICSTATUS_CLEAR_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5AU,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_ML86294_MlI2CMUTEREG_ON_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_ML86294_MlI2CMUTEREG_ON_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x18U     /* Write Data */
};

const U1 u1_sp_ML86294_MlI2CMUTEREG_OFF_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_ML86294_MlI2CMUTEREG_OFF_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_ML86294_MlNOAISMUTEREG_ON_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x58U     /* Write Data */
};

const U1 u1_sp_ML86294_MlNOAISMUTEREG_ON_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xDEU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_ML86294_MlNOAISMUTEREG_OFF_SET1[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x58U     /* Write Data */
};

const U1 u1_sp_ML86294_MlNOAISMUTEREG_OFF_SET2[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xDEU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_ML86294_MLFAILCYCCHK_RD_PDU1[ML86294_I2C_RWC_BYTE2] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x3CU     /* Write Address */
};

U1 u1_sp_ML86294_MLFAILCYCCHK_RD_PDU2[ML86294_I2C_RWC_BYTE2];

const U1 u1_sp_ML86294_MLSYNCCYCCHK_RD_PDU1[ML86294_I2C_RWC_BYTE2] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0x5FU     /* Write Address */
};

U1 u1_sp_ML86294_MLSYNCCYCCHK_RD_PDU2[ML86294_I2C_RWC_BYTE2];

const U1 u1_sp_ML86294_SET_BANK15[ML86294_I2C_RWC_BYTE3] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x78U     /* Write Data */
};

const U1 u1_sp_ML86294_MLMIPIRCVCYCCHK_RD_PDU1[ML86294_I2C_RWC_BYTE2] = {
    (U1)ML86294_I2C_SLAVEADR_WR,    /* Slave Address */
    (U1)0xA2U     /* Write Address */
};

U1 u1_sp_ML86294_MLMIPIRCVCYCCHK_RD_PDU2[ML86294_I2C_RWC_BYTE2];

const ST_GP_I2C_MA_REQ st_sp_ML86294_SET_BANK12_TBL[1] = {
    {
        (U1 *)&u1_sp_ML86294_SET_BANK12[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MLFRZDATCYCFRZBIT_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_ML86294_MLFRZDATCYCFRZBIT_RD_PDU1[0],
        (U4)0x10000002U
    },
    {
        (U1 *)&u1_sp_ML86294_MLFRZDATCYCFRZBIT_RD_PDU2[0],
        (U4)0x10000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_SET_BANK2_TBL[1] = {
    {
        (U1 *)&u1_sp_ML86294_SET_BANK2[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MLFRZDATCYCROUTEBIT_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_ML86294_MLFRZDATCYCROUTEBIT_RD_PDU1[0],
        (U4)0x10000002U
    },
    {
        (U1 *)&u1_sp_ML86294_MLFRZDATCYCROUTEBIT_RD_PDU2[0],
        (U4)0x10000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_SET_BANK8_TBL[1] = {
    {
        (U1 *)&u1_sp_ML86294_SET_BANK8[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MLIRQHPD_ASSERT_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_ML86294_MLIRQHPD_ASSERT_RD_PDU1[0],
        (U4)0x10000002U
    },
    {
        (U1 *)&u1_sp_ML86294_MLIRQHPD_ASSERT_RD_PDU2[0],
        (U4)0x10000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MLIRQHPD_DPCD_SET1_TBL[3] = {
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET1_DCPC202_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET1_DCPC202_SET2[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET1_DCPC202_SET3[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MLIRQHPD_DPCD_READSET_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_READSET_RD_PDU1[0],
        (U4)0x10000002U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_READSET_RD_PDU2[0],
        (U4)0x10000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MLIRQHPD_DPCD_READSET_SET_TBL[1] = {
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_READSET_SET_PDU[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MLIRQHPD_DPCD_REGNUM_SET_TBL[1] = {
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_REGNUM_SET[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MLIRQHPD_DPCD_AUXSND_READSET_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_AUXSND_READSET_RD_PDU1[0],
        (U4)0x10000002U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_AUXSND_READSET_RD_PDU2[0],
        (U4)0x10000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MLIRQHPD_DPCD_AUXSND_READSET_SET_TBL[1] = {
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_AUXSND_READSET_SET_PDU[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MLIRQHPD_DPCD_AUXCOM_RD1_TBL[2] = {
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_AUXCOM_RD1_PDU1[0],
        (U4)0x10000002U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_AUXCOM_RD1_PDU2[0],
        (U4)0x10000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MLIRQHPD_DPCD_AUXCOM_RD2_TBL[2] = {
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_AUXCOM_RD2_PDU1[0],
        (U4)0x10000002U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_AUXCOM_RD2_PDU2[0],
        (U4)0x10000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MLIRQHPD_DPCD_SET2_TBL[3] = {
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET2_CLEAR_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET2_CLEAR_SET2[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET2_CLEAR_SET3[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MLIRQHPD_DPCD_SET3_TBL[42] = {
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_ALTMOFF_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_ALTMOFF_SET2[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET2[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET3[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET4[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET5[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET6[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET7[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET8[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET9[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET10[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET11[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET12[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET13[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET14[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET15[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET16[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET17[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET18[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET19[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET20[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET21[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET22[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET23[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET24[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET25[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET26[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET27[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET28[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET29[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET30[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET31[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_EDPTX_SET32[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_CLEAR_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_CLEAR_SET2[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_CLEAR_SET3[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_CLEAR_SET4[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_ALTMON_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_ALTMON_SET2[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_VTSTART_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MLIRQHPD_DPCD_SET3_VTSTART_SET2[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_TBL[143] = {
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET2[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET3[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET4[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET5[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET6[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET7[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET8[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET9[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET10[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET11[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET12[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET13[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET14[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET15[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET16[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET17[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET18[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET19[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET20[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET21[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET22[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET23[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET24[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET25[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET26[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET27[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET28[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET29[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET30[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET31[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET32[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET33[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET34[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET35[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET36[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET37[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET38[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET39[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET40[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET41[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET42[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET43[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET44[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET45[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET46[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET47[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET48[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET49[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET50[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET51[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET52[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET53[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET54[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET55[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET56[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET57[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET58[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET59[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET60[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET61[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET62[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET63[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET64[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET65[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET66[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET67[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET68[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET69[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET70[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET71[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET72[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET73[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET74[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET75[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET76[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET77[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET78[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET79[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET80[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET81[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET82[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET83[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET84[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET85[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET86[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET87[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET88[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET89[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET90[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET91[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET92[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET93[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET94[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET95[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET96[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET97[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET98[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET99[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET100[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET101[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET102[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET103[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET104[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET105[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET106[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET107[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET108[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET109[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET110[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET111[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET112[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET113[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET114[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET115[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET116[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET117[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET118[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET119[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET120[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET121[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET122[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET123[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET124[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET125[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET126[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET127[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET128[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET129[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET130[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET131[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET132[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET133[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET134[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET135[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET136[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET137[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET138[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET139[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET140[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET141[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET142[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_SET143[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_TBL[143] = {
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET2[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET3[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET4[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET5[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET6[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET7[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET8[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET9[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET10[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET11[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET12[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET13[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET14[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET15[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET16[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET17[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET18[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET19[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET20[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET21[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET22[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET23[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET24[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET25[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET26[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET27[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET28[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET29[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET30[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET31[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET32[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET33[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET34[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET35[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET36[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET37[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET38[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET39[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET40[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET41[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET42[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET43[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET44[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET45[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET46[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET47[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET48[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET49[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET50[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET51[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET52[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET53[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET54[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET55[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET56[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET57[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET58[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET59[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET60[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET61[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET62[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET63[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET64[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET65[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET66[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET67[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET68[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET69[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET70[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET71[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET72[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET73[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET74[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET75[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET76[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET77[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET78[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET79[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET80[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET81[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET82[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET83[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET84[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET85[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET86[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET87[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET88[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET89[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET90[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET91[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET92[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET93[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET94[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET95[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET96[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET97[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET98[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET99[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET100[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET101[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET102[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET103[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET104[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET105[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET106[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET107[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET108[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET109[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET110[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET111[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET112[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET113[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET114[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET115[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET116[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET117[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET118[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET119[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET120[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET121[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET122[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET123[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET124[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET125[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET126[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET127[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET128[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET129[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET130[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET131[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET132[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET133[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET134[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET135[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET136[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET137[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET138[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET139[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET140[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET141[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET142[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_SET143[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_TBL[143] = {
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET2[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET3[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET4[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET5[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET6[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET7[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET8[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET9[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET10[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET11[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET12[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET13[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET14[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET15[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET16[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET17[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET18[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET19[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET20[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET21[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET22[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET23[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET24[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET25[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET26[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET27[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET28[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET29[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET30[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET31[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET32[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET33[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET34[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET35[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET36[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET37[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET38[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET39[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET40[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET41[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET42[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET43[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET44[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET45[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET46[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET47[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET48[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET49[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET50[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET51[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET52[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET53[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET54[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET55[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET56[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET57[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET58[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET59[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET60[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET61[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET62[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET63[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET64[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET65[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET66[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET67[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET68[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET69[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET70[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET71[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET72[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET73[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET74[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET75[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET76[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET77[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET78[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET79[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET80[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET81[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET82[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET83[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET84[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET85[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET86[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET87[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET88[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET89[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET90[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET91[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET92[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET93[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET94[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET95[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET96[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET97[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET98[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET99[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET100[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET101[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET102[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET103[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET104[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET105[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET106[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET107[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET108[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET109[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET110[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET111[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET112[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET113[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET114[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET115[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET116[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET117[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET118[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET119[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET120[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET121[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET122[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET123[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET124[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET125[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET126[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET127[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET128[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET129[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET130[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET131[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET132[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET133[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET134[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET135[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET136[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET137[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET138[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET139[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET140[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET141[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET142[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_SET143[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_TBL[143] = {
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET2[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET3[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET4[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET5[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET6[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET7[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET8[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET9[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET10[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET11[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET12[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET13[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET14[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET15[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET16[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET17[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET18[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET19[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET20[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET21[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET22[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET23[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET24[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET25[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET26[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET27[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET28[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET29[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET30[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET31[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET32[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET33[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET34[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET35[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET36[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET37[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET38[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET39[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET40[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET41[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET42[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET43[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET44[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET45[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET46[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET47[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET48[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET49[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET50[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET51[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET52[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET53[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET54[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET55[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET56[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET57[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET58[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET59[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET60[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET61[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET62[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET63[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET64[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET65[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET66[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET67[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET68[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET69[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET70[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET71[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET72[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET73[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET74[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET75[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET76[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET77[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET78[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET79[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET80[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET81[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET82[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET83[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET84[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET85[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET86[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET87[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET88[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET89[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET90[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET91[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET92[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET93[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET94[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET95[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET96[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET97[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET98[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET99[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET100[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET101[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET102[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET103[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET104[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET105[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET106[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET107[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET108[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET109[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET110[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET111[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET112[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET113[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET114[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET115[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET116[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET117[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET118[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET119[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET120[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET121[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET122[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET123[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET124[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET125[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET126[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET127[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET128[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET129[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET130[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET131[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET132[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET133[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET134[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET135[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET136[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET137[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET138[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET139[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET140[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET141[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET142[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_SET143[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_TBL[143] = {
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET2[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET3[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET4[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET5[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET6[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET7[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET8[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET9[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET10[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET11[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET12[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET13[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET14[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET15[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET16[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET17[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET18[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET19[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET20[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET21[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET22[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET23[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET24[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET25[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET26[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET27[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET28[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET29[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET30[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET31[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET32[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET33[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET34[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET35[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET36[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET37[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET38[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET39[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET40[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET41[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET42[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET43[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET44[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET45[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET46[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET47[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET48[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET49[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET50[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET51[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET52[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET53[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET54[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET55[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET56[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET57[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET58[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET59[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET60[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET61[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET62[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET63[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET64[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET65[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET66[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET67[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET68[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET69[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET70[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET71[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET72[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET73[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET74[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET75[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET76[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET77[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET78[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET79[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET80[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET81[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET82[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET83[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET84[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET85[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET86[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET87[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET88[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET89[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET90[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET91[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET92[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET93[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET94[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET95[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET96[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET97[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET98[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET99[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET100[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET101[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET102[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET103[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET104[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET105[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET106[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET107[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET108[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET109[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET110[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET111[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET112[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET113[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET114[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET115[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET116[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET117[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET118[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET119[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET120[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET121[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET122[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET123[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET124[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET125[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET126[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET127[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET128[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET129[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET130[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET131[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET132[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET133[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET134[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET135[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET136[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET137[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET138[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET139[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET140[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET141[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET142[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_SET143[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_TBL[143] = {
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET2[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET3[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET4[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET5[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET6[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET7[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET8[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET9[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET10[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET11[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET12[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET13[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET14[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET15[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET16[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET17[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET18[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET19[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET20[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET21[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET22[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET23[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET24[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET25[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET26[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET27[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET28[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET29[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET30[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET31[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET32[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET33[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET34[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET35[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET36[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET37[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET38[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET39[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET40[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET41[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET42[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET43[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET44[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET45[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET46[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET47[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET48[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET49[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET50[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET51[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET52[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET53[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET54[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET55[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET56[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET57[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET58[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET59[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET60[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET61[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET62[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET63[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET64[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET65[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET66[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET67[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET68[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET69[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET70[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET71[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET72[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET73[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET74[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET75[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET76[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET77[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET78[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET79[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET80[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET81[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET82[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET83[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET84[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET85[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET86[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET87[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET88[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET89[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET90[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET91[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET92[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET93[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET94[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET95[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET96[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET97[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET98[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET99[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET100[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET101[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET102[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET103[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET104[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET105[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET106[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET107[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET108[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET109[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET110[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET111[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET112[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET113[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET114[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET115[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET116[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET117[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET118[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET119[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET120[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET121[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET122[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET123[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET124[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET125[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET126[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET127[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET128[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET129[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET130[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET131[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET132[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET133[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET134[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET135[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET136[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET137[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET138[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET139[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET140[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET141[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET142[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_SET143[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_TBL[143] = {
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET2[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET3[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET4[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET5[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET6[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET7[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET8[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET9[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET10[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET11[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET12[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET13[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET14[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET15[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET16[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET17[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET18[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET19[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET20[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET21[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET22[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET23[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET24[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET25[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET26[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET27[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET28[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET29[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET30[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET31[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET32[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET33[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET34[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET35[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET36[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET37[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET38[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET39[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET40[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET41[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET42[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET43[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET44[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET45[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET46[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET47[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET48[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET49[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET50[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET51[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET52[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET53[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET54[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET55[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET56[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET57[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET58[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET59[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET60[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET61[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET62[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET63[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET64[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET65[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET66[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET67[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET68[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET69[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET70[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET71[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET72[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET73[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET74[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET75[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET76[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET77[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET78[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET79[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET80[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET81[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET82[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET83[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET84[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET85[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET86[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET87[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET88[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET89[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET90[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET91[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET92[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET93[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET94[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET95[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET96[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET97[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET98[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET99[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET100[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET101[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET102[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET103[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET104[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET105[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET106[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET107[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET108[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET109[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET110[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET111[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET112[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET113[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET114[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET115[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET116[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET117[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET118[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET119[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET120[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET121[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET122[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET123[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET124[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET125[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET126[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET127[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET128[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET129[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET130[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET131[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET132[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET133[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET134[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET135[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET136[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET137[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET138[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET139[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET140[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET141[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET142[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_SET143[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_TBL[143] = {
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET2[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET3[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET4[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET5[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET6[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET7[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET8[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET9[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET10[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET11[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET12[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET13[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET14[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET15[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET16[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET17[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET18[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET19[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET20[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET21[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET22[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET23[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET24[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET25[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET26[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET27[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET28[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET29[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET30[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET31[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET32[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET33[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET34[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET35[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET36[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET37[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET38[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET39[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET40[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET41[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET42[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET43[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET44[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET45[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET46[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET47[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET48[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET49[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET50[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET51[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET52[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET53[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET54[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET55[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET56[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET57[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET58[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET59[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET60[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET61[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET62[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET63[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET64[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET65[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET66[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET67[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET68[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET69[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET70[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET71[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET72[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET73[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET74[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET75[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET76[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET77[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET78[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET79[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET80[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET81[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET82[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET83[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET84[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET85[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET86[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET87[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET88[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET89[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET90[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET91[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET92[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET93[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET94[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET95[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET96[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET97[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET98[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET99[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET100[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET101[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET102[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET103[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET104[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET105[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET106[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET107[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET108[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET109[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET110[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET111[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET112[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET113[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET114[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET115[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET116[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET117[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET118[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET119[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET120[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET121[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET122[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET123[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET124[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET125[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET126[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET127[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET128[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET129[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET130[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET131[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET132[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET133[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET134[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET135[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET136[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET137[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET138[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET139[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET140[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET141[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET142[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_SET143[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_TBL[143] = {
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET2[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET3[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET4[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET5[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET6[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET7[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET8[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET9[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET10[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET11[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET12[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET13[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET14[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET15[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET16[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET17[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET18[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET19[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET20[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET21[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET22[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET23[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET24[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET25[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET26[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET27[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET28[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET29[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET30[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET31[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET32[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET33[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET34[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET35[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET36[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET37[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET38[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET39[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET40[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET41[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET42[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET43[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET44[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET45[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET46[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET47[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET48[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET49[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET50[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET51[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET52[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET53[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET54[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET55[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET56[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET57[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET58[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET59[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET60[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET61[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET62[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET63[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET64[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET65[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET66[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET67[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET68[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET69[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET70[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET71[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET72[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET73[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET74[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET75[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET76[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET77[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET78[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET79[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET80[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET81[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET82[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET83[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET84[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET85[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET86[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET87[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET88[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET89[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET90[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET91[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET92[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET93[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET94[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET95[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET96[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET97[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET98[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET99[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET100[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET101[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET102[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET103[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET104[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET105[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET106[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET107[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET108[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET109[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET110[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET111[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET112[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET113[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET114[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET115[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET116[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET117[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET118[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET119[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET120[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET121[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET122[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET123[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET124[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET125[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET126[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET127[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET128[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET129[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET130[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET131[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET132[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET133[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET134[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET135[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET136[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET137[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET138[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET139[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET140[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET141[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET142[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_SET143[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE[143] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET2[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET3[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET4[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET5[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET6[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET7[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET8[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET9[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET10[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET11[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET12[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET13[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET14[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET15[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET16[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET17[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET18[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET19[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET20[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET21[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET22[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET23[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET24[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET25[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET26[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET27[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET28[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET29[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET30[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET31[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET32[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET33[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET34[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET35[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET36[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET37[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET38[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET39[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET40[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET41[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET42[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET43[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET44[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET45[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET46[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET47[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET48[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET49[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET50[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET51[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET52[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET53[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET54[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET55[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET56[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET57[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET58[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET59[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET60[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET61[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET62[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET63[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET64[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET65[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET66[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET67[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET68[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET69[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET70[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET71[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET72[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET73[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET74[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET75[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET76[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET77[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET78[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET79[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET80[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET81[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET82[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET83[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET84[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET85[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET86[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET87[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET88[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET89[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET90[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET91[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET92[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET93[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET94[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET95[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET96[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET97[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET98[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET99[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET100[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET101[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET102[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET103[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET104[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET105[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET106[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET107[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET108[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET109[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET110[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET111[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET112[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET113[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET114[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET115[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET116[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET117[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET118[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET119[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET120[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET121[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET122[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET123[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET124[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET125[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET126[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET127[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET128[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET129[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET130[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET131[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET132[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET133[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET134[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET135[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET136[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET137[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET138[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET139[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET140[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET141[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET142[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE_SET143[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MlMIPIREG_ON_TBL[2] = {
    {
        (U1 *)&u1_sp_ML86294_MlMIPIREG_ON_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlMIPIREG_ON_SET2[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MlMIPIREG_OFF_TBL[2] = {
    {
        (U1 *)&u1_sp_ML86294_MlMIPIREG_OFF_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlMIPIREG_OFF_SET2[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MlFRZCHGREG_ON_TBL[14] = {
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_ON_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_ON_SET2[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_ON_SET3[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_ON_SET4[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_ON_SET5[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_ON_SET6[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_ON_SET7[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_ON_SET8[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_ON_SET9[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_ON_SET10[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_ON_SET11[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_ON_SET12[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_ON_SET13[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_ON_SET14[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MlFRZCHGREG_OFF_TBL[13] = {
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_OFF_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_OFF_SET2[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_OFF_SET3[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_OFF_SET4[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_OFF_SET5[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_OFF_SET6[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_OFF_SET7[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_OFF_SET8[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_OFF_SET9[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_OFF_SET10[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_OFF_SET11[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_OFF_SET12[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_OFF_SET13[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MlFRZCHGREG_BYPASS_TBL[7] = {
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_BYPASS_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_BYPASS_SET2[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_BYPASS_SET3[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_BYPASS_SET4[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_BYPASS_SET5[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_BYPASS_SET6[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlFRZCHGREG_BYPASS_SET7[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MlCAMPATHREG_NORMAL_TBL[7] = {
    {
        (U1 *)&u1_sp_ML86294_MlCAMPATHREG_NORMAL_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlCAMPATHREG_NORMAL_SET2[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlCAMPATHREG_NORMAL_SET3[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlCAMPATHREG_NORMAL_SET4[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlCAMPATHREG_NORMAL_SET5[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlCAMPATHREG_NORMAL_SET6[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlCAMPATHREG_NORMAL_SET7[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_SET_BANK0_TBL[1] = {
    {
        (U1 *)&u1_sp_ML86294_SET_BANK0[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MIPISYNCSTATUS_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_ML86294_MIPISYNCSTATUS_RD_PDU1[0],
        (U4)0x10000002U
    },
    {
        (U1 *)&u1_sp_ML86294_MIPISYNCSTATUS_RD_PDU2[0],
        (U4)0x10000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MlRCVVICSTATUS_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_ML86294_MlRCVVICSTATUS_RD_PDU1[0],
        (U4)0x10000002U
    },
    {
        (U1 *)&u1_sp_ML86294_MlRCVVICSTATUS_RD_PDU2[0],
        (U4)0x10000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MlRCVVICSTATUS_CLEAR_TBL[1] = {
    {
        (U1 *)&u1_sp_ML86294_MlRCVVICSTATUS_CLEAR_SET1[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MlI2CMUTEREG_ON_TBL[2] = {
    {
        (U1 *)&u1_sp_ML86294_MlI2CMUTEREG_ON_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlI2CMUTEREG_ON_SET2[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MlI2CMUTEREG_OFF_TBL[2] = {
    {
        (U1 *)&u1_sp_ML86294_MlI2CMUTEREG_OFF_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlI2CMUTEREG_OFF_SET2[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MlNOAISMUTEREG_ON_TBL[2] = {
    {
        (U1 *)&u1_sp_ML86294_MlNOAISMUTEREG_ON_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlNOAISMUTEREG_ON_SET2[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MlNOAISMUTEREG_OFF_TBL[2] = {
    {
        (U1 *)&u1_sp_ML86294_MlNOAISMUTEREG_OFF_SET1[0],
        (U4)0x10000003U
    },
    {
        (U1 *)&u1_sp_ML86294_MlNOAISMUTEREG_OFF_SET2[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MLFAILCYCCHK_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_ML86294_MLFAILCYCCHK_RD_PDU1[0],
        (U4)0x10000002U
    },
    {
        (U1 *)&u1_sp_ML86294_MLFAILCYCCHK_RD_PDU2[0],
        (U4)0x10000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MLSYNCCYCCHK_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_ML86294_MLSYNCCYCCHK_RD_PDU1[0],
        (U4)0x10000002U
    },
    {
        (U1 *)&u1_sp_ML86294_MLSYNCCYCCHK_RD_PDU2[0],
        (U4)0x10000002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_SET_BANK15_TBL[1] = {
    {
        (U1 *)&u1_sp_ML86294_SET_BANK15[0],
        (U4)0x10000003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_ML86294_MLMIPIRCVCYCCHK_RD_TBL[2] = {
    {
        (U1 *)&u1_sp_ML86294_MLMIPIRCVCYCCHK_RD_PDU1[0],
        (U4)0x10000002U
    },
    {
        (U1 *)&u1_sp_ML86294_MLMIPIRCVCYCCHK_RD_PDU2[0],
        (U4)0x10000002U
    }
};

/*===================================================================================================================================*/
/*  void    vd_g_Pict_Ml86294_Init(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Pict_Ml86294_Init(void)
{
    u1_s_pict_ml_state = (U1)ML86294_SEQ_IDLE;

    u2_s_pict_ml_regstep = (U2)0U;
    u4_s_pict_ml_i2c_ack_wait_time = (U4)0U;
    u2_s_pict_ml_reg_btwn_time = (U2)0xFFFFU;

    u1_s_pict_dev_sts = (U1)0U;
    u1_s_pict_pre_dev_sts = (U1)0U;

    u1_s_pict_ml_frzint_chk_flg = (U1)FALSE;
    u1_s_pict_ml_pre_v_ic_sts1_sts = (U1)PICT_ML_IO_STS_LOW;

    u1_s_pict_mlcycchk_sts = (U1)ML86294_CYCCHK_STEP0;
    u2_s_pict_ml_cycchk_timer = (U2)0U;
    u1_s_pict_mlcyc_dev_reset_cnt = (U1)0U;
    u1_s_pict_mlcyc_dev_rst_timer = (U1)0U;

    u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP0;
    u2_s_pict_ml_frzdat_cycchk_timer = (U2)0U;
    u1_s_pict_mlfrzdatcyc_n1_cnt = (U1)0U;
    u1_s_pict_mlfrzdatcyc_n2_cnt = (U1)0U;
    u1_s_pict_mlfrzdatcyc_frz_drec_cnt = (U1)0U;
    u1_s_pict_mlfrzdatcyc_route_drec_cnt = (U1)0U;
    u1_s_pict_mlfrzdatcyc_gpio0_sts = (U1)PICT_ML_IO_STS_LOW;

    u1_s_pict_mlirqhpdcycchk_sts = (U1)ML86294_IRQHPD_CYCCHK_STEP0;
    u2_s_pict_ml_irqhpd_cycchk_timer = (U2)0U;
    u1_s_pict_mlirqhpdcyc_assert_drec_cnt = (U1)0U;

    u1_s_pict_mlcamarea_set_sts = (U1)ML86294_CAMAREA_SET_STEP0;

    u1_s_pict_mlrcvvicstatus_sts = (U1)ML86294_RCVVICSTATUS_STEP0;

    u1_s_pict_mlfrz_drec_cnt = (U1)0U;
    u1_s_pict_mlfail_drec_cnt = (U1)0U;
    u1_s_pict_mlsync_pre_sip_sync_err = (U1)0x00U;
    u1_s_pict_mlsync_sip_drec_cnt = (U1)0U;
    u1_s_pict_mlsync_pre_cam_sync_err = (U1)0x00U;
    u1_s_pict_mlsync_cam_drec_cnt = (U1)0U;
    u1_s_pict_mlroute_pre_v_ic_sts2_sts = (U1)PICT_ML_IO_STS_LOW;
    u1_s_pict_mlroute_drec_cnt = (U1)0U;
    u1_s_pict_mlmipircv_drec_cnt = (U1)0U;
    u1_s_pict_mldevrst_sts = (U1)ML86294_DEV_RST_STEP0;
    U1 u2_s_pict_mlregget_timer = (U2)0U;
    U1 u1_s_pict_mlregget_flag = (U1)ML86294_REGGET_FLAG_STOP;
    u1_s_pict_mlregget_sts = (U1)ML86294_REGGET_STEP0;
    u1_s_pict_mlregget_result = (U1)PICT_ML_MIPI_SYNC_OFF;
    u1_s_pict_mldevrst_notif = (U1)PICT_ML_DEVRST_NON;

    /*  データリード用テーブル初期化 */
    u1_sp_ML86294_MLFRZDATCYCFRZBIT_RD_PDU2[0] = (U1)ML86294_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_ML86294_MLFRZDATCYCFRZBIT_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_ML86294_MLFRZDATCYCROUTEBIT_RD_PDU2[0] = (U1)ML86294_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_ML86294_MLFRZDATCYCROUTEBIT_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_ML86294_MLIRQHPD_ASSERT_RD_PDU2[0] = (U1)ML86294_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_ML86294_MLIRQHPD_ASSERT_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_MLIRQHPD_DPCD_READSET_RD_PDU2[0] = (U1)ML86294_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MLIRQHPD_DPCD_READSET_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /* DPCDリード設定 レジスタ設定 書込み用テーブル(Data可変)初期化 */
    u1_sp_MLIRQHPD_DPCD_READSET_SET_PDU[0] = (U1)ML86294_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_MLIRQHPD_DPCD_READSET_SET_PDU[1] = (U1)0x27U;    /* Write Address */
    u1_sp_MLIRQHPD_DPCD_READSET_SET_PDU[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  データリード用テーブル初期化 */
    u1_sp_MLIRQHPD_DPCD_AUXSND_READSET_RD_PDU2[0] = (U1)ML86294_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MLIRQHPD_DPCD_AUXSND_READSET_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /* AUX送信バイト数の設定 レジスタ設定 書込み用テーブル(Data可変)初期化 */
    u1_sp_MLIRQHPD_DPCD_AUXSND_READSET_SET_PDU[0] = (U1)ML86294_I2C_SLAVEADR_WR;    /* Slave Address */
    u1_sp_MLIRQHPD_DPCD_AUXSND_READSET_SET_PDU[1] = (U1)0x38U;    /* Write Address */
    u1_sp_MLIRQHPD_DPCD_AUXSND_READSET_SET_PDU[2] = (U1)0U;    /* Write Data初期値(定期処理内で更新) */

    /*  データリード用テーブル初期化 */
    u1_sp_MLIRQHPD_DPCD_AUXCOM_RD1_PDU2[0] = (U1)ML86294_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MLIRQHPD_DPCD_AUXCOM_RD1_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_MLIRQHPD_DPCD_AUXCOM_RD2_PDU2[0] = (U1)ML86294_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MLIRQHPD_DPCD_AUXCOM_RD2_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_ML86294_MIPISYNCSTATUS_RD_PDU2[0] = (U1)ML86294_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_ML86294_MIPISYNCSTATUS_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_ML86294_MlRCVVICSTATUS_RD_PDU2[0] = (U1)ML86294_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_ML86294_MlRCVVICSTATUS_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_ML86294_MLFAILCYCCHK_RD_PDU2[0] = (U1)ML86294_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_ML86294_MLFAILCYCCHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_ML86294_MLSYNCCYCCHK_RD_PDU2[0] = (U1)ML86294_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_ML86294_MLSYNCCYCCHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_ML86294_MLMIPIRCVCYCCHK_RD_PDU2[0] = (U1)ML86294_I2C_SLAVEADR_RD;    /* Slave Address */
    u1_sp_ML86294_MLMIPIRCVCYCCHK_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */
}

/*===================================================================================================================================*/
/*  void    vd_g_Pict_Ml86294_Routine(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
void    vd_g_Pict_Ml86294_Routine(void)
{
    U1      u1_t_ml_pwron_sts;
    U1      u1_t_dio_read_result;                                   /* I/O Port Read Result */
    U1      u1_t_cycchk_func_sts;

    switch (u1_s_pict_ml_state){
        case ML86294_SEQ_IDLE:                                             /* IDLE */
            /* Timer Clear */
            u2_s_pict_ml_cycchk_timer = (U2)0U;
            u2_s_pict_ml_frzdat_cycchk_timer = (U2)0U;
            u2_s_pict_ml_irqhpd_cycchk_timer = (U2)0U;

            /* Power ON Check */
            if(Mcu_OnStep_EIZOIC_OVRALL == (U1)PICT_ML_PWRON_COMP){
                /* State Update */
                u1_s_pict_ml_state = (U1)ML86294_SEQ_CYC;

                /* Poling Timer Start */
                u2_s_pict_ml_cycchk_timer++;
                u2_s_pict_ml_frzdat_cycchk_timer++;
                u2_s_pict_ml_irqhpd_cycchk_timer++;

                /* Device Reset Counter Clear */
                u1_s_pict_mlcyc_dev_reset_cnt = (U1)0U;
                
                /* Freeze Cycle Check Counter Clear */
                u1_s_pict_mlfrzdatcyc_n1_cnt = (U1)0U;
                u1_s_pict_mlfrzdatcyc_n2_cnt = (U1)0U;

                /* Drec Counter Clear */
                u1_s_pict_mlfrzdatcyc_frz_drec_cnt = (U1)0U;
                u1_s_pict_mlfrzdatcyc_route_drec_cnt = (U1)0U;
                u1_s_pict_mlirqhpdcyc_assert_drec_cnt = (U1)0U;
                u1_s_pict_mlfail_drec_cnt = (U1)0U;
                u1_s_pict_mlsync_sip_drec_cnt = (U1)0U;
                u1_s_pict_mlsync_cam_drec_cnt = (U1)0U;
                u1_s_pict_mlroute_drec_cnt = (U1)0U;
                u1_s_pict_mlmipircv_drec_cnt = (U1)0U;
            }
            break;
        case ML86294_SEQ_CYC:                                              /* CYCLIC */
            /* Ack Wait Timer Countr Increment */
            if(u4_s_pict_ml_i2c_ack_wait_time < (U4)U4_MAX){        /* 暫定 I2Cアクセス時にカウンタクリアされるため定期では常にカウントアップする */
                u4_s_pict_ml_i2c_ack_wait_time++;
            }

            /* Cyc Check Start */
            u1_t_cycchk_func_sts = (U1)TRUE;

            /* Freeze Detection Intruput Check */
            if(u1_s_pict_ml_frzint_chk_flg == (U1)TRUE){
                u1_t_dio_read_result = (U1)u1_PICT_ML_GET_V_IC_STATUS1();
                if((u1_t_dio_read_result == (U1)PICT_ML_IO_STS_HIGH)
                && (u1_s_pict_ml_pre_v_ic_sts1_sts == (U1)PICT_ML_IO_STS_LOW)){     /* V-IC-STATUS1 = L -> H */
                    /* Freeze Detection Intruput */
                    u1_s_pict_ml_state = (U1)ML86294_SEQ_FRZ_INT;
                    /* Cyc Check Stop */
                    u1_t_cycchk_func_sts = (U1)FALSE;
                }
                /* Previous State Update */
                u1_s_pict_ml_pre_v_ic_sts1_sts = u1_t_dio_read_result;
            }

            /* ML86294 Cyc Check */
            if(u1_t_cycchk_func_sts == (U1)TRUE){
                u1_t_cycchk_func_sts = (U1)u1_s_Pict_MLCycChk();
            }

            /* Freeze Cycle Cyc Check */
            if(u1_t_cycchk_func_sts == (U1)TRUE){
                u1_t_cycchk_func_sts = (U1)u1_s_Pict_MLFrzDatCycChk();
            }

            /* IRQ_HPD Cycle Cyc Check */
            if(u1_t_cycchk_func_sts == (U1)TRUE){
                u1_t_cycchk_func_sts = (U1)u1_s_Pict_MLIrqHpdCycChk();
            }

            /* 暫定 カメラ同期検知 */
            if((u1_s_pict_mlregget_flag == (U1)ML86294_REGGET_FLAG_START)
            && (u1_t_cycchk_func_sts == (U1)TRUE)){
                u1_t_cycchk_func_sts = u1_s_Pict_MLMIPISyncCheck();
            }
            break;
        case ML86294_SEQ_DEV_RST:                                       /* DEV_RST */
            vd_s_Pict_MLDevRst();
            break;
        case ML86294_SEQ_FRZ_INT:                                       /* FRZ_INT */
            u1_t_cycchk_func_sts = (U1)u1_s_Pict_MlRcvVIcStatusNty();
            if(u1_t_cycchk_func_sts == (U1)TRUE){
                /* Cyc Check */
                u1_s_pict_ml_state = (U1)ML86294_SEQ_CYC;
            }
            break;
        default:                                                        /* FAIL */
            /* State Reset */
            u1_s_pict_ml_state = (U1)ML86294_SEQ_IDLE;
            break;
    }
}

/*===================================================================================================================================*/
/*  U1    u1_s_Pict_Ml86294_TimChk(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u2_a_tim_cnt  :  Timer Count /  u2_a_wait_tim  :  Wait Time                                                      */
/*  Return:         TRUE (Wait Time Elapsed) / FALSE (Wait Time Not Elapsed)                                                         */
/*===================================================================================================================================*/
static U1 u1_s_Pict_Ml86294_TimChk(const U2 u2_a_tim_cnt, const U2 u2_a_wait_tim)
{
    U1  u1_t_ret;

    u1_t_ret = (U1)FALSE;
    if(u2_a_tim_cnt >= u2_a_wait_tim){
        u1_t_ret = (U1)TRUE;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1    u1_s_Pict_MLCycChk(void)                                                                                                   */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Pict_MLCycChk(void)   /* 暫定 100ms定期 */
{   /* 暫定　I/Fメモ 6.10.1 定期処理 */
    static const U2 ML86294_CYCCHK_POLING = (U2)(500U / ML86294_TASK_TIME);   /* t20 min:100ms */

    U1      u1_t_ret;                                               /* Function Completion Status  */
    U1      u1_t_time_chk_flg;
    U1      u1_t_reg_req_sts;
    U1      u1_t_reg_read_result;                                   /* Register Read Result */
    U1      u1_t_dio_read_result;                                   /* I/O Port Read Result */
    U1      u1_t_sip_sync_err;                                      /* Sip Error Result */
    U1      u1_t_cam_sync_err;                                      /* Camera Error Result */
    U1      u1_t_rcv_err;                                           /* Receiver Error Result */

    u1_t_ret = (U1)FALSE;

    switch (u1_s_pict_mlcycchk_sts){
        case ML86294_CYCCHK_STEP0:                                       /* STEP0 */
            /* Poling Check */
            u1_t_time_chk_flg = u1_s_Pict_Ml86294_TimChk((U2)u2_s_pict_ml_cycchk_timer, ML86294_CYCCHK_POLING);

            if(u1_t_time_chk_flg == (U1)TRUE){
                /* Poling Timer Clear */
                u2_s_pict_ml_cycchk_timer = (U2)0;

                /* Next Process */
                u1_s_pict_mlcycchk_sts = (U1)ML86294_CYCCHK_STEP1;
            }
            else{
                /* Function Completion */
                u1_t_ret = (U1)TRUE;

                u2_s_pict_ml_cycchk_timer++;
            }
            break;
        case ML86294_CYCCHK_STEP1:                                       /* STEP1 */
        /* ----------6.10.1 定期処理 デバイス異常検知開始---------- */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_BANKSET_WRINUM,
                                                          ML86294_BANKSET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_ML86294_SET_BANK0_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlcycchk_sts = (U1)ML86294_CYCCHK_STEP2;
            }
            break;
        case ML86294_CYCCHK_STEP2:                                       /* STEP2 */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGREAD(&u2_s_pict_ml_regstep, &u4_s_pict_ml_i2c_ack_wait_time,
                                                           st_sp_ML86294_MLFAILCYCCHK_RD_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlcycchk_sts = (U1)ML86294_CYCCHK_STEP3;
            }
            break;
        case ML86294_CYCCHK_STEP3:                                       /* STEP3 */
            u1_t_reg_read_result = st_sp_ML86294_MLFAILCYCCHK_RD_TBL[1].u1p_pdu[1];
            if(u1_t_reg_read_result == (U1)PICT_ML_MLFAILCYCCHK_DEV_ERR){               /* Device Error */
                if(u1_s_pict_mlfail_drec_cnt < (U1)PICT_ML_MLFAILCYCCHK_DREC_CNT_MAX){  /* Drec Counter < 1 */
                    /* ダイレコ保存 *//* 暫定 シス検ではダイレコ保存未対応 */
                    u1_s_pict_mlfail_drec_cnt++;
                }
                if(u1_s_pict_mlcyc_dev_reset_cnt < (U1)U1_MAX){
                    u1_s_pict_mlcyc_dev_reset_cnt++;
                }
#if 0           /* 暫定 符号なし変数と0を比較する処理となり、ビルドエラーとなるためコメントアウト */
                if(u1_s_pict_mlcyc_dev_reset_cnt < (U1)PICT_ML_MLFAILCYCCHK_DEV_RESET_CNT_MAX){ /* Device Reset Counter < 0 */
                    vd_PICT_MLFAILCYCCHK_V_IC_RST_L();                                  /* V-IC-RST = L *//* 暫定 ポート設定I/F展開後に見直し */
                }
                else {
#endif
                    vd_s_Pict_MLDevRst();                                               /* Device Reset Request */

                    /* Next Process */
                    u1_s_pict_mlcycchk_sts = (U1)ML86294_CYCCHK_STEP10;
#if 0           /* 暫定 符号なし変数と0を比較する処理となり、ビルドエラーとなるためコメントアウト */
                }
#endif
            }
        /* ----------6.10.1 定期処理 デバイス異常検知終了---------- */
            /* Next Process */
            u1_s_pict_mlcycchk_sts = (U1)ML86294_CYCCHK_STEP4;
            break;
        case ML86294_CYCCHK_STEP4:                                       /* STEP4 */
        /* ----------6.10.1 定期処理 SiP映像入力の同期監視/カメラ映像入力の同期監視開始---------- */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGREAD(&u2_s_pict_ml_regstep, &u4_s_pict_ml_i2c_ack_wait_time,
                                                           st_sp_ML86294_MLSYNCCYCCHK_RD_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlcycchk_sts = (U1)ML86294_CYCCHK_STEP4;
            }
            break;
        case ML86294_CYCCHK_STEP5:                                       /* STEP5 */
            u1_t_reg_read_result = st_sp_ML86294_MLSYNCCYCCHK_RD_TBL[1].u1p_pdu[1];
            u1_t_sip_sync_err = u1_t_reg_read_result & (U1)PICT_REG_MASK_BIT_2;     /* Get Sip Error Result */
            if((u1_t_sip_sync_err == (U1)PICT_ML_MLSYNCCYCCHK_SIP_ERR)              /* Sip Error */
            && (u1_s_pict_mlsync_pre_sip_sync_err == (U1)PICT_REG_MASK_BIT_2)){     /* Previous State OK */
                if(u1_s_pict_mlsync_sip_drec_cnt < (U1)PICT_ML_MLSYNCCYCCHK_SIP_DREC_CNT_MAX){ /* Drec Counter < 3 */
                    /* ダイレコ保存 *//* 暫定 シス検ではダイレコ保存未対応 */
                    u1_s_pict_mlsync_sip_drec_cnt++;
                }
            }

            u1_t_cam_sync_err = u1_t_reg_read_result & (U1)PICT_REG_MASK_BIT_3;     /* Get Camera Error Result */
            if((u1_t_cam_sync_err == (U1)PICT_ML_MLSYNCCYCCHK_CAM_ERR)              /* Camera Error */
            && (u1_s_pict_mlsync_pre_cam_sync_err == (U1)PICT_REG_MASK_BIT_3)){     /* Previous State OK */
                if(u1_s_pict_mlsync_cam_drec_cnt < (U1)PICT_ML_MLSYNCCYCCHK_SIP_DREC_CNT_MAX){ /* Drec Counter < 3 */
                    /* ダイレコ保存 *//* 暫定 シス検ではダイレコ保存未対応 */
                    u1_s_pict_mlsync_cam_drec_cnt++;
                }
            }
            /* Previous State Update */
            u1_s_pict_mlsync_pre_sip_sync_err = u1_t_sip_sync_err;
            u1_s_pict_mlsync_pre_cam_sync_err = u1_t_cam_sync_err;
        /* ----------6.10.1 定期処理 SiP映像入力の同期監視/カメラ映像入力の同期監視終了---------- */
            /* Next Process */
            u1_s_pict_mlcycchk_sts = (U1)ML86294_CYCCHK_STEP6;
            break;
        case ML86294_CYCCHK_STEP6:                                       /* STEP6 */
        /* ----------6.10.1 定期処理 映像ICの内部経路監視開始---------- */
            /* Read I/O */
            u1_t_dio_read_result = u1_PICT_MLROUTECYCCHK_GET_V_IC_STATUS2();        /* Get V-IC-STATUS2 Status */

            if((u1_t_dio_read_result == (U1)PICT_ML_IO_STS_HIGH)                    /* V-IC-STATUS2 = H */
            && (u1_s_pict_mlroute_pre_v_ic_sts2_sts == (U1)PICT_ML_IO_STS_LOW)){    /* Previous State L */
                if(u1_s_pict_mlroute_drec_cnt < (U1)PICT_ML_MLROUTECYCCHK_DREC_CNT_MAX){ /* Drec Counter < 3 */
                    /* ダイレコ保存 *//* 暫定 シス検ではダイレコ保存未対応 */
                    u1_s_pict_mlroute_drec_cnt++;
                }
            }

            /* Previous State Update */
            u1_s_pict_mlroute_pre_v_ic_sts2_sts = u1_t_dio_read_result;
        /* ----------6.10.1 定期処理 映像ICの内部経路監視終了---------- */
            /* Next Process */
            u1_s_pict_mlcycchk_sts = (U1)ML86294_CYCCHK_STEP7;
            break;
        case ML86294_CYCCHK_STEP7:                                       /* STEP7 */
        /* ----------6.10.1 定期処理 MIPI映像受信部のエラー検知開始---------- */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_BANKSET_WRINUM,
                                                          ML86294_BANKSET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_ML86294_SET_BANK15_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlcycchk_sts = (U1)ML86294_CYCCHK_STEP8;
            }
            break;
        case ML86294_CYCCHK_STEP8:                                       /* STEP8 */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGREAD(&u2_s_pict_ml_regstep, &u4_s_pict_ml_i2c_ack_wait_time,
                                                           st_sp_ML86294_MLMIPIRCVCYCCHK_RD_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlcycchk_sts = (U1)ML86294_CYCCHK_STEP9;
            }
            break;
        case ML86294_CYCCHK_STEP9:                                       /* STEP9 */
            u1_t_reg_read_result = st_sp_ML86294_MLMIPIRCVCYCCHK_RD_TBL[1].u1p_pdu[1];
            u1_t_rcv_err = u1_t_reg_read_result & (U1)PICT_ML_MIPIRCVCYCCHK_RCV_DAT_MASK;   /* Get Receiver Error Result */
            if(u1_t_rcv_err != (U1)PICT_ML_MIPIRCVCYCCHK_RCV_OK ){                  /* Receiver Error */
                if(u1_s_pict_mlmipircv_drec_cnt < (U1)PICT_ML_MLMIPIRCVCYCCHK_DREC_CNT_MAX){ /* Drec Counter < 3 */
                    /* ダイレコ保存 *//* 暫定 シス検ではダイレコ保存未対応 */
                    u1_s_pict_mlmipircv_drec_cnt++;
                }
            }
        /* ----------6.10.1 定期処理 MIPI映像受信部のエラー検知終了---------- */
            /* Function Completion */
            u1_t_ret = (U1)TRUE;
            /* Process Reset */
            u1_s_pict_mlcycchk_sts = (U1)ML86294_CYCCHK_STEP0;
            break;
        case ML86294_CYCCHK_STEP10:                                     /* STEP10 */
        /* Device Restart or Reset */
            /* Process Reset */
            u1_s_pict_mlcycchk_sts = (U1)ML86294_CYCCHK_STEP0;
            break;
        default:                                                                /* FAIL */
            /* Process Reset */
            u1_s_pict_mlcycchk_sts = (U1)ML86294_CYCCHK_STEP0;
            break;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1    u1_s_Pict_MLFrzDatCycChk(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Pict_MLFrzDatCycChk(void)   /* 暫定 20ms定期 */
{   /* 暫定　I/Fメモ 6.10.2 固着検知ビット監視 */
    static const U2 ML86294_FRZDAT_CYCCHK_POLING = (U2)(20U / ML86294_TASK_TIME);   /* t21 min:20ms */

    U1      u1_t_ret;                                               /* Function Completion Status  */
    U1      u1_t_time_chk_flg;
    U1      u1_t_reg_req_sts;
    U1      u1_t_reg_read_result;                                   /* Register Read Result */
    U1      u1_t_dio_read_result;                                   /* I/O Port Read Result */
    U1      u1_t_func_result;                                       /* Function Completion Result */

    U1      u1_t_cam_sts;                                           /* Camera Mode Status */
    U1      u1_t_cam_diag_sts;                                      /* Camera Diag Mode Status */
    U1      u1_t_cam_sync_sts;                                      /* Camera SYNC Status */
    U1      u1_t_qual_mode_rev_sts;                                 /* Quality Mode Receive Status */
    U1      u1_t_qual_mode_rev_data;                                /* Quality Mode Data */
    U1      u1_t_frz_dat_sts;                                       /* Freeze Data Status */

    u1_t_ret = (U1)FALSE;

    switch (u1_s_pict_mlfrzdatcycchk_sts){
        case ML86294_FRZDAT_CYCCHK_STEP0:                                       /* STEP0 */
            /* Poling Check */
            u1_t_time_chk_flg = u1_s_Pict_Ml86294_TimChk((U2)u2_s_pict_ml_frzdat_cycchk_timer, ML86294_FRZDAT_CYCCHK_POLING);

            if(u1_t_time_chk_flg == (U1)TRUE){
                /* Poling Timer Clear */
                u2_s_pict_ml_frzdat_cycchk_timer = (U2)0;

                /* Next Process */
                u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP1;
            }
            else{
                /* Function Completion */
                u1_t_ret = (U1)TRUE;

                u2_s_pict_ml_frzdat_cycchk_timer++;
            }
            break;
        case ML86294_FRZDAT_CYCCHK_STEP1:                                       /* STEP1 */
            u1_s_pict_mlfrzdatcyc_gpio0_sts = u1_PICT_MLFLZDATCYCCHK_GET_DISP_REQ_GPIO0(); /* Get DISP-REQ-GPIO0 Status */
            u1_t_cam_sts = u1_PICT_MLFLZDATCYCCHK_GET_CAM_STS();                        /* Get Camera Mode Status */
            u1_t_cam_diag_sts = u1_PICT_MLFLZDATCYCCHK_GET_CAM_DIAG_STS();              /* Get Camera Diag Mode Status */
            u1_t_cam_sync_sts = u1_PICT_MLFLZDATCYCCHK_GET_CAM_SYNC_STS();              /* Get Camera SYNC Mode Status */

            if((u1_s_pict_mlfrzdatcyc_gpio0_sts == (U1)PICT_ML_IO_STS_HIGH)             /* DISP-REQ-GPIO0 = H */
            && (u1_t_cam_sts == (U1)PICT_ML_CAM_MODE_ON)                                /* Camera Mode:ON */
            && (u1_t_cam_diag_sts == (U1)PICT_ML_CAM_DIAG_MODE_OFF)                     /* Camera Diag Mode:OFF */
            && (u1_t_cam_sync_sts == (U1)PICT_ML_CAM_SYNC_MODE_OK)){                    /* Camera SYNC Status:OK */
                /* N2=0 */
                u1_s_pict_mlfrzdatcyc_n2_cnt = (U1)0U;

                /* Next Process */
                u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP2;
            }
            else {
                /* N1=0 */
                u1_s_pict_mlfrzdatcyc_n1_cnt = (U1)0U;

                /* Next Process */
                u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP8;
            }
            break;
        case ML86294_FRZDAT_CYCCHK_STEP2:                                       /* STEP2 */
        /* ----------6.10.2 固着検知ビット監視 カメラモード開始---------- */
            /* N1++ */
            if(u1_s_pict_mlfrzdatcyc_n1_cnt < (U1)U1_MAX){
                u1_s_pict_mlfrzdatcyc_n1_cnt++;
            }

            if(u1_s_pict_mlfrzdatcyc_n1_cnt >= PICT_ML_MLFLZDATCYCCHK_L1){          /* N1 >= L1 */
                /* Next Process */
                u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP3;
            }
            else {
                /* Function Completion */
                u1_t_ret = (U1)TRUE;
                /* Process Reset */
                u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP0;
            }
            break;
        case ML86294_FRZDAT_CYCCHK_STEP3:                                       /* STEP3 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_BANKSET_WRINUM,
                                                          ML86294_BANKSET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_ML86294_SET_BANK12_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP4;
            }
            break;
        case ML86294_FRZDAT_CYCCHK_STEP4:                                       /* STEP4 */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGREAD(&u2_s_pict_ml_regstep, &u4_s_pict_ml_i2c_ack_wait_time,
                                                           st_sp_ML86294_MLFRZDATCYCFRZBIT_RD_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP5;
            }
            break;
        case ML86294_FRZDAT_CYCCHK_STEP5:                                       /* STEP5 */
            u1_t_reg_read_result = st_sp_ML86294_MLFRZDATCYCFRZBIT_RD_TBL[1].u1p_pdu[1];
            u1_t_frz_dat_sts = u1_t_reg_read_result & (U1)PICT_REG_MASK_BIT_0;  /* Get Freeze Data Result */
            if(u1_t_frz_dat_sts != (U1)PICT_REG_MASK_BIT_0){                /* bit[0] = 0 */
                if(u1_s_pict_mlfrzdatcyc_frz_drec_cnt < (U1)PICT_ML_MLFLZDATCYCCHK_FRZ_DREC_CNT_MAX){ /* Drec Counter < 3 */
                    /* ダイレコ保存 *//* 暫定 シス検ではダイレコ保存未対応 */
                    u1_s_pict_mlfrzdatcyc_frz_drec_cnt++;
                }
                /* Next Process */
                u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP6;
            }
            else {
                /* Next Process */
                u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP7;
            }
            break;
        case ML86294_FRZDAT_CYCCHK_STEP6:                                       /* STEP6 */
            /* Freeze Check ON */
            u1_t_func_result = u1_g_Pict_MlFrzChgSet((U1)PICT_ML_FRZ_ON);
            if(u1_t_func_result == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP7;
            }
            break;
        case ML86294_FRZDAT_CYCCHK_STEP7:                                       /* STEP7 */
            /* N1=0 */
            u1_s_pict_mlfrzdatcyc_n1_cnt = (U1)0U;
        /* ----------6.10.2 固着検知ビット監視 カメラモード終了---------- */

            /* Function Completion */
            u1_t_ret = (U1)TRUE;
            /* Process Reset */
            u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP0;
            break;
        case ML86294_FRZDAT_CYCCHK_STEP8:                                       /* STEP8 */
        /* ----------6.10.2 固着検知ビット監視 カメラモード以外開始---------- */
            /* N2++ */
            if(u1_s_pict_mlfrzdatcyc_n2_cnt < (U1)U1_MAX){
                u1_s_pict_mlfrzdatcyc_n2_cnt++;
            }

            if(u1_s_pict_mlfrzdatcyc_n2_cnt >= PICT_ML_MLFLZDATCYCCHK_L2){          /* N2 >= L2 */
                u1_t_qual_mode_rev_sts = u1_PICT_MLFLZDATCYCCHK_GET_QUALMODE_REV_STS(); /* Get Quality Mode Receive Status */
                u1_t_qual_mode_rev_data = u1_PICT_MLFLZDATCYCCHK_GET_QUALMODE_DATA();   /* Get Quality Mode Data */

                if((u1_t_qual_mode_rev_sts == (U1)PICT_ML_CAM_QUAL_MODE_RECEIVED)       /* Quality Mode Received */
                && (u1_t_qual_mode_rev_data != (U1)PICT_ML_CAM_QUAL_MODE_CAM)){         /* Quality Mode Not Camera */
                    /* Next Process */
                    u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP9;
                }
                else {                                                                  /* Quality Mode Not Receive or Quality Mode Camera */
                    /* Next Process */
                    u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP18;
                }
            }
            else {
                /* Function Completion */
                u1_t_ret = (U1)TRUE;
                /* Process Reset */
                u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP0;
            }
            break;
        case ML86294_FRZDAT_CYCCHK_STEP9:                                       /* STEP9 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_BANKSET_WRINUM,
                                                          ML86294_BANKSET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_ML86294_SET_BANK12_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP10;
            }
            break;
        case ML86294_FRZDAT_CYCCHK_STEP10:                                      /* STEP10 */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGREAD(&u2_s_pict_ml_regstep, &u4_s_pict_ml_i2c_ack_wait_time,
                                                           st_sp_ML86294_MLFRZDATCYCFRZBIT_RD_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP11;
            }
            break;
        case ML86294_FRZDAT_CYCCHK_STEP11:                                      /* STEP11 */
            u1_t_reg_read_result = st_sp_ML86294_MLFRZDATCYCFRZBIT_RD_TBL[1].u1p_pdu[1];
            u1_t_frz_dat_sts = u1_t_reg_read_result & (U1)PICT_REG_MASK_BIT_0;  /* Get Freeze Data Result */
            if(u1_t_frz_dat_sts == (U1)PICT_REG_MASK_BIT_0){                /* bit[0] = 1 */
                if(u1_s_pict_mlfrzdatcyc_frz_drec_cnt < (U1)PICT_ML_MLFLZDATCYCCHK_FRZ_DREC_CNT_MAX){ /* Drec Counter < 3 */
                    /* ダイレコ保存 *//* 暫定 シス検ではダイレコ保存未対応 */
                    u1_s_pict_mlfrzdatcyc_frz_drec_cnt++;
                }
                /* Next Process */
                u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP12;
            }
            else {
                /* Next Process */
                u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP13;
            }
        case ML86294_FRZDAT_CYCCHK_STEP12:                                      /* STEP12 */
            /* Freeze Check ON */
            u1_t_func_result = u1_g_Pict_MlFrzChgSet((U1)PICT_ML_FRZ_OFF);
            if(u1_t_func_result == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP13;
            }
            break;
        case ML86294_FRZDAT_CYCCHK_STEP13:                                      /* STEP13 */
            if(u1_s_pict_mlfrzdatcyc_gpio0_sts == (U1)PICT_ML_IO_STS_LOW){      /* DISP-REQ-GPIO0 = L */
                /* Next Process */
                u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP14;
            }
            else {
                /* Next Process */
                u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP18;
            }
        case ML86294_FRZDAT_CYCCHK_STEP14:                                      /* STEP14 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_BANKSET_WRINUM,
                                                          ML86294_BANKSET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_ML86294_SET_BANK2_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP10;
            }
            break;
        case ML86294_FRZDAT_CYCCHK_STEP15:                                      /* STEP15 */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGREAD(&u2_s_pict_ml_regstep, &u4_s_pict_ml_i2c_ack_wait_time,
                                                           st_sp_ML86294_MLFRZDATCYCROUTEBIT_RD_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP16;
            }
            break;
        case ML86294_FRZDAT_CYCCHK_STEP16:                                      /* STEP16 */
            u1_t_reg_read_result = st_sp_ML86294_MLFRZDATCYCFRZBIT_RD_TBL[1].u1p_pdu[1];
            if(u1_t_reg_read_result == (U1)PICT_ML_MLFLZDATCYCCHK_ROUTE_BYPASS){                /* Route Bypass */
                if(u1_s_pict_mlfrzdatcyc_route_drec_cnt < (U1)PICT_ML_MLFLZDATCYCCHK_ROUTE_DREC_CNT_MAX){ /* Drec Counter < 3 */
                    /* ダイレコ保存 *//* 暫定 シス検ではダイレコ保存未対応 */
                    u1_s_pict_mlfrzdatcyc_route_drec_cnt++;
                }
                /* Next Process */
                u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP17;
            }
            else {
                /* Next Process */
                u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP18;
            }
            break;
        case ML86294_FRZDAT_CYCCHK_STEP17:                                      /* STEP17 */
            /* Route Change SiP */
            u1_t_func_result = u1_g_Pict_MlCamPathSet((U1)PICT_ML_CAMPATH_NORMAL);
            if(u1_t_func_result == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP18;
            }
            break;
        case ML86294_FRZDAT_CYCCHK_STEP18:                                      /* STEP18 */
            /* N2=0 */
            u1_s_pict_mlfrzdatcyc_n2_cnt = (U1)0U;
        /* ----------6.10.2 固着検知ビット監視 カメラモード以外終了---------- */

            /* Function Completion */
            u1_t_ret = (U1)TRUE;
            /* Process Reset */
            u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP0;
            break;
        default:                                                                /* FAIL */
            /* Process Reset */
            u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP0;
            break;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1    u1_s_Pict_MLIrqHpdCycChk(void)                                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Pict_MLIrqHpdCycChk(void)   /* 暫定 20ms定期 */
{   /* 暫定　I/Fメモ 6.10.3 IRQ_HPDの監視 */
    static const U2 ML86294_IRQHPC_CYCCHK_POLING = (U2)(50U / ML86294_TASK_TIME);   /* t22 min:20ms */

    static const ST_REG_WRI_REQ ML86294_IRQHPD_DPCD_SET1[ML86294_IRQHPD_DPCD_SET1_WRINUM] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         3,         0}
    };

    static const ST_REG_WRI_REQ ML86294_IRQHPD_DPCD_READSET_SET[ML86294_IRQHPD_DPCD_READSET_SET_WRINUM] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };

    static const ST_REG_WRI_REQ ML86294_IRQHPD_DPCD_REGNUM_SET[ML86294_IRQHPD_DPCD_REGNUM_SET_WRINUM] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };

    static const ST_REG_WRI_REQ ML86294_IRQHPD_DPCD_AUXSND_READSET_SET[ML86294_IRQHPD_DPCD_AUXSND_READSET_SET_WRINUM] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };

    static const ST_REG_WRI_REQ ML86294_IRQHPD_DPCD_SET2[ML86294_IRQHPD_DPCD_SET2_WRINUM] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         3,         0}
    };

    static const ST_REG_WRI_REQ ML86294_IRQHPD_DPCD_SET3[ML86294_IRQHPD_DPCD_SET3_WRINUM] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},  /* Bank9 */
        {        1,         1,         0},
        {        2,         1,         0},  /* Bank8 */
        {        3,         4,         0},
        {        7,         1,         0},  /* Bank9 */
        {        8,         5,         0},
        {       13,         1,         0},  /* Bank10 */
        {       14,        10,         0},
        {       24,        10,         0},
        {       34,         1,         0},  /* Bank8 */
        {       35,         3,         0},
        {       38,         1,         0},  /* Bank9 */
        {       39,         1,         0},
        {       40,         1,         0},  /* Bank8 */
        {       41,         1,         0}
    };

    U1      u1_t_ret;                                               /* Function Completion Status  */
    U1      u1_t_time_chk_flg;
    U1      u1_t_reg_req_sts;
    U1      u1_t_reg_read_result;                                   /* Register Read Result */
    U1      u1_t_dio_read_result;                                   /* I/O Port Read Result */
    U1      u1_t_func_result;                                       /* Function Completion Result */
    U1      u1_t_irqhpd_assert;                                     /* IRQ_HPD Assert */
    U1      u1_t_irqhpd_dpcd_read_set;                              /* DPCD Register Read Set Data  */
    U1      u1_t_irqhpd_dpcd_auxsnd_set;                            /* DPCD Register AUX Send Byte Data */
    U1      u1_t_irqhpd_auxcom_read_sts1;                           /* Register Read Status1 */
    U1      u1_t_irqhpd_auxcom_read_sts2;                           /* Register Read Status2 */

    u1_t_ret = (U1)FALSE;

    switch (u1_s_pict_mlirqhpdcycchk_sts){
        case ML86294_IRQHPD_CYCCHK_STEP0:                                       /* STEP0 */
            /* Poling Check */
            u1_t_time_chk_flg = u1_s_Pict_Ml86294_TimChk((U2)u2_s_pict_ml_irqhpd_cycchk_timer, ML86294_IRQHPC_CYCCHK_POLING);

            if(u1_t_time_chk_flg == (U1)TRUE){
                /* Poling Timer Clear */
                u2_s_pict_ml_irqhpd_cycchk_timer = (U2)0;

                /* Next Process */
                u1_s_pict_mlirqhpdcycchk_sts = (U1)ML86294_IRQHPD_CYCCHK_STEP1;
            }
            else{
                /* Function Completion */
                u1_t_ret = (U1)TRUE;

                u2_s_pict_ml_irqhpd_cycchk_timer++;
            }
            break;
        case ML86294_IRQHPD_CYCCHK_STEP1:                                       /* STEP1 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_BANKSET_WRINUM,
                                                          ML86294_BANKSET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_ML86294_SET_BANK8_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlirqhpdcycchk_sts = (U1)ML86294_IRQHPD_CYCCHK_STEP2;
            }
            break;
        case ML86294_IRQHPD_CYCCHK_STEP2:                                       /* STEP2 */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGREAD(&u2_s_pict_ml_regstep, &u4_s_pict_ml_i2c_ack_wait_time,
                                                           st_sp_ML86294_MLIRQHPD_ASSERT_RD_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlirqhpdcycchk_sts = (U1)ML86294_IRQHPD_CYCCHK_STEP3;
            }
            break;
        case ML86294_IRQHPD_CYCCHK_STEP3:                                       /* STEP3 */
            u1_t_reg_read_result = st_sp_ML86294_MLIRQHPD_ASSERT_RD_TBL[1].u1p_pdu[1];
            u1_t_irqhpd_assert = u1_t_reg_read_result & (U1)PICT_REG_MASK_BIT_1;      /* Get IRQ_HPD Assert */
            if(u1_t_irqhpd_assert == (U1)PICT_REG_MASK_BIT_1){
                if(u1_s_pict_mlirqhpdcyc_assert_drec_cnt < (U1)PICT_ML_MLIRQHPD_ASSERT_DREC_CNT_MAX){ /* Drec Counter < 3 */
                    /* ダイレコ保存 *//* 暫定 シス検ではダイレコ保存未対応 */
                    u1_s_pict_mlirqhpdcyc_assert_drec_cnt++;
                }
                /* Next Process */
                u1_s_pict_mlirqhpdcycchk_sts = (U1)ML86294_IRQHPD_CYCCHK_STEP4;
            }
            else{
                /* Function Completion */
                u1_t_ret = (U1)TRUE;
                /* Process Reset */
                u1_s_pict_mlirqhpdcycchk_sts = (U1)ML86294_IRQHPD_CYCCHK_STEP0;
            }
            break;
        case ML86294_IRQHPD_CYCCHK_STEP4:                                       /* STEP4 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_IRQHPD_DPCD_SET1_WRINUM,
                                                          ML86294_IRQHPD_DPCD_SET1, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_MLIRQHPD_DPCD_SET1_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlirqhpdcycchk_sts = (U1)ML86294_IRQHPD_CYCCHK_STEP5;
            }
            break;
        case ML86294_IRQHPD_CYCCHK_STEP5:                                       /* STEP5 */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGREAD(&u2_s_pict_ml_regstep, &u4_s_pict_ml_i2c_ack_wait_time,
                                                           st_sp_MLIRQHPD_DPCD_READSET_RD_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_reg_read_result = st_sp_MLIRQHPD_DPCD_READSET_RD_TBL[1].u1p_pdu[1];
                u1_t_irqhpd_dpcd_read_set = u1_t_reg_read_result & (U1)PICT_ML_MLIRQHPD_DPCD_READ_REGDATA1; /* bit[7:4] = 0x0 */
                u1_t_irqhpd_dpcd_read_set = u1_t_reg_read_result | (U1)PICT_ML_MLIRQHPD_DPCD_READ_REGDATA2; /* bit[7] = 1, bit[4] = 1 */
                st_sp_MLIRQHPD_DPCD_READSET_SET_TBL[0].u1p_pdu[2] = u1_t_irqhpd_dpcd_read_set;              /* Register Write Data Set */
                /* Next Process */
                u1_s_pict_mlirqhpdcycchk_sts = (U1)ML86294_IRQHPD_CYCCHK_STEP6;
            }
            break;
        case ML86294_IRQHPD_CYCCHK_STEP6:                                       /* STEP6 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_IRQHPD_DPCD_READSET_SET_WRINUM,
                                                          ML86294_IRQHPD_DPCD_READSET_SET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_MLIRQHPD_DPCD_READSET_SET_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlirqhpdcycchk_sts = (U1)ML86294_IRQHPD_CYCCHK_STEP7;
            }
            break;
        case ML86294_IRQHPD_CYCCHK_STEP7:                                       /* STEP7 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_IRQHPD_DPCD_REGNUM_SET_WRINUM,
                                                          ML86294_IRQHPD_DPCD_REGNUM_SET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_MLIRQHPD_DPCD_REGNUM_SET_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlirqhpdcycchk_sts = (U1)ML86294_IRQHPD_CYCCHK_STEP8;
            }
            break;
        case ML86294_IRQHPD_CYCCHK_STEP8:                                       /* STEP8 */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGREAD(&u2_s_pict_ml_regstep, &u4_s_pict_ml_i2c_ack_wait_time,
                                                           st_sp_MLIRQHPD_DPCD_AUXSND_READSET_RD_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_reg_read_result = st_sp_MLIRQHPD_DPCD_AUXSND_READSET_RD_TBL[1].u1p_pdu[1];
                u1_t_irqhpd_dpcd_auxsnd_set = u1_t_reg_read_result & (U1)PICT_ML_MLIRQHPD_DPCD_AUXSND_REGDATA1; /* bit[4:0] = 0x00 */
                u1_t_irqhpd_dpcd_auxsnd_set = u1_t_reg_read_result | (U1)PICT_ML_MLIRQHPD_DPCD_AUXSND_REGDATA2; /* bit[4:0] = 0x03 */
                st_sp_MLIRQHPD_DPCD_AUXSND_READSET_SET_TBL[0].u1p_pdu[2] = u1_t_irqhpd_dpcd_auxsnd_set;         /* Register Write Data Set */
                /* Next Process */
                u1_s_pict_mlirqhpdcycchk_sts = (U1)ML86294_IRQHPD_CYCCHK_STEP9;
            }
            break;
        case ML86294_IRQHPD_CYCCHK_STEP9:                                       /* STEP9 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_IRQHPD_DPCD_AUXSND_READSET_SET_WRINUM,
                                                          ML86294_IRQHPD_DPCD_AUXSND_READSET_SET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_MLIRQHPD_DPCD_AUXSND_READSET_SET_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlirqhpdcycchk_sts = (U1)ML86294_IRQHPD_CYCCHK_STEP10;
            }
            break;
        case ML86294_IRQHPD_CYCCHK_STEP10:                                      /* STEP10 */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGREAD(&u2_s_pict_ml_regstep, &u4_s_pict_ml_i2c_ack_wait_time,
                                                           st_sp_MLIRQHPD_DPCD_AUXCOM_RD1_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlirqhpdcycchk_sts = (U1)ML86294_IRQHPD_CYCCHK_STEP11;
            }
            break;
        case ML86294_IRQHPD_CYCCHK_STEP11:                                      /* STEP11 */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGREAD(&u2_s_pict_ml_regstep, &u4_s_pict_ml_i2c_ack_wait_time,
                                                           st_sp_MLIRQHPD_DPCD_AUXCOM_RD2_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlirqhpdcycchk_sts = (U1)ML86294_IRQHPD_CYCCHK_STEP12;
            }
            break;
        case ML86294_IRQHPD_CYCCHK_STEP12:                                      /* STEP12 */
            u1_t_irqhpd_auxcom_read_sts1 = st_sp_MLIRQHPD_DPCD_AUXCOM_RD1_TBL[1].u1p_pdu[1];
            u1_t_irqhpd_auxcom_read_sts2 = st_sp_MLIRQHPD_DPCD_AUXCOM_RD2_TBL[1].u1p_pdu[1];
            if((u1_t_irqhpd_auxcom_read_sts1 == (U1)PICT_ML_MLIRQHPD_DPCD_AUXCOM_OK)
            && (u1_t_irqhpd_auxcom_read_sts2 == (U1)PICT_ML_MLIRQHPD_DPCD_AUXCOM_OK)){
                /* Next Process */
                u1_s_pict_mlirqhpdcycchk_sts = (U1)ML86294_IRQHPD_CYCCHK_STEP13;
            }
            else{
                /* Process Reset */
                u1_s_pict_mlirqhpdcycchk_sts = (U1)ML86294_IRQHPD_CYCCHK_STEP14;
            }
            break;
        case ML86294_IRQHPD_CYCCHK_STEP13:                                      /* STEP13 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_IRQHPD_DPCD_SET2_WRINUM,
                                                          ML86294_IRQHPD_DPCD_SET2, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_MLIRQHPD_DPCD_SET2_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Function Completion */
                u1_t_ret = (U1)TRUE;
                /* Process Reset */
                u1_s_pict_mlirqhpdcycchk_sts = (U1)ML86294_IRQHPD_CYCCHK_STEP0;
            }
            break;
        case ML86294_IRQHPD_CYCCHK_STEP14:                                      /* STEP14 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_IRQHPD_DPCD_SET3_WRINUM,
                                                          ML86294_IRQHPD_DPCD_SET3, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_MLIRQHPD_DPCD_SET3_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Function Completion */
                u1_t_ret = (U1)TRUE;
                /* Process Reset */
                u1_s_pict_mlirqhpdcycchk_sts = (U1)ML86294_IRQHPD_CYCCHK_STEP0;
            }
            break;
        default:                                                                /* FAIL */
            /* Process Reset */
            u1_s_pict_mlfrzdatcycchk_sts = (U1)ML86294_FRZDAT_CYCCHK_STEP0;
            break;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1    u1_g_Pict_MlCamAreaSet(void)                                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
U1    u1_g_Pict_MlCamAreaSet(void)
{   /* 暫定　I/Fメモ 6.5.1.2 起動後のカメラ映像表示に関する設定フロー */
    static const ST_REG_WRI_REQ ML86294_CAMAREA_SET[ML86294_CAMAREA_SET_WRINUM] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},  /* Bank0 */
        {        1,         7,         0},
        {        8,         7,         0},
        {       15,         1,         0},  /* Bank1 */
        {       16,         8,         0},
        {       24,         8,         0},
        {       32,         1,         0},  /* Bank11 */
        {       33,         8,         0},
        {       41,         1,         0},  /* Bank12 */
        {       42,        10,         0},
        {       52,        10,         0},
        {       62,        10,         0},
        {       72,        10,         0},
        {       82,        10,         0},
        {       92,        10,         0},
        {      102,        10,         0},
        {      112,         1,         0},  /* Bank15 */
        {      113,         2,         0},
        {      115,         1,         0},  /* Bank22 */
        {      116,         4,         0},
        {      120,         1,         0},  /* Bank25 */
        {      121,         8,         0},
        {      129,         7,         0},
        {      136,         7,         0}
    };

    static const U1  u1_sp_ML86294_CAMAREA_SIZE_FUNC_STEP[PICT_ML_CAN_CAM_SIZE_MAX] = { /* 暫定 カメラサイズI/F展開後に見直す */
        ML86294_CAMAREA_SET_STEP1,          /* 1920x1080 */
        ML86294_CAMAREA_SET_STEP2,          /* 1920x954 */
        ML86294_CAMAREA_SET_STEP3,          /* 1920x900 */
        ML86294_CAMAREA_SET_STEP4,          /* 1920x720 */
        ML86294_CAMAREA_SET_STEP5,          /* 1280x846 */
        ML86294_CAMAREA_SET_STEP6,          /* 1280x720 */
        ML86294_CAMAREA_SET_STEP7,          /* 1280x621 */
        ML86294_CAMAREA_SET_STEP8,          /* 1696x954 */
        ML86294_CAMAREA_SET_STEP9           /* 1104x621 */
    };

    U1      u1_t_ret;                                               /* Function Completion Status  */
    U1      u1_t_reg_req_sts;
    U1      u1_t_camarea_camkind;                                   /* Camera Kind */
    U1      u1_t_camarea_camsize;                                   /* Camera Size */

    u1_t_ret = (U1)FALSE;

    switch (u1_s_pict_mlcamarea_set_sts){
        case ML86294_CAMAREA_SET_STEP0:                                       /* STEP0 */
            /* Init Camera Kind */
            u1_t_camarea_camkind = (U1)PICT_ML_GVIFIF_NONE;                         /* 暫定 提供元I/Fで不定値提供されないなら不要 */
            u1_t_camarea_camkind = vd_PICT_MLCAMAREASET_GET_CAMAREA_KIND();         /* 暫定 提供元I/F作成後に置き換え */

            if(u1_t_camarea_camkind == (U1)PICT_ML_GVIFIF_ADC_ECU){                  /* Camera Kind:ADC_ECU */
                /* Init Camera Size */
                u1_t_camarea_camsize = (U1)PICT_ML_CAN_CAM_SIZE_NONE;           /* 暫定 提供元I/Fで不定値提供されないなら不要 */
                u1_t_camarea_camsize = vd_PICT_MLCAMAREASET_GET_CAMAREA_SIZE(); /* 暫定 提供元I/F作成後に置き換え */
                if(u1_t_camarea_camsize <= (U1)PICT_ML_CAN_CAM_SIZE_MAX){       /* 暫定 定義はカメラ制御仕様対応後に確定 */
                    /* Next Process */
                    u1_s_pict_mlcamarea_set_sts = (U1)u1_sp_ML86294_CAMAREA_SIZE_FUNC_STEP[u1_t_camarea_camsize];
                }
                else {
                    /* Function Completion */
                    u1_t_ret = (U1)TRUE;
                    /* Process Reset */
                    u1_s_pict_mlcamarea_set_sts = (U1)ML86294_CAMAREA_SET_STEP0;
                }
            }
            else if(u1_t_camarea_camkind == (U1)PICT_ML_GVIFIF_NONE){                /* Camera Kind:NONE */
                    /* Next Process */
                    u1_s_pict_mlcamarea_set_sts = ML86294_CAMAREA_SET_STEP10;
            }
            else{                                                                   /* Camera Kind:Other */
                /* Function Completion */
                u1_t_ret = (U1)TRUE;
                /* Process Reset */
                u1_s_pict_mlcamarea_set_sts = (U1)ML86294_CAMAREA_SET_STEP0;
            }
            break;
        case ML86294_CAMAREA_SET_STEP1:                                       /* STEP1 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_CAMAREA_SET_WRINUM,
                                                          ML86294_CAMAREA_SET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X1080_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Function Completion */
                u1_t_ret = (U1)TRUE;
                /* Process Reset */
                u1_s_pict_mlcamarea_set_sts = (U1)ML86294_CAMAREA_SET_STEP0;
            }
            break;
        case ML86294_CAMAREA_SET_STEP2:                                       /* STEP2 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_CAMAREA_SET_WRINUM,
                                                          ML86294_CAMAREA_SET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X954_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Function Completion */
                u1_t_ret = (U1)TRUE;
                /* Process Reset */
                u1_s_pict_mlcamarea_set_sts = (U1)ML86294_CAMAREA_SET_STEP0;
            }
            break;
        case ML86294_CAMAREA_SET_STEP3:                                       /* STEP3 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_CAMAREA_SET_WRINUM,
                                                          ML86294_CAMAREA_SET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X900_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Function Completion */
                u1_t_ret = (U1)TRUE;
                /* Process Reset */
                u1_s_pict_mlcamarea_set_sts = (U1)ML86294_CAMAREA_SET_STEP0;
            }
            break;
        case ML86294_CAMAREA_SET_STEP4:                                       /* STEP4 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_CAMAREA_SET_WRINUM,
                                                          ML86294_CAMAREA_SET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_ML86294_MlSETREG_CAMAREA_ADC_1920X720_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Function Completion */
                u1_t_ret = (U1)TRUE;
                /* Process Reset */
                u1_s_pict_mlcamarea_set_sts = (U1)ML86294_CAMAREA_SET_STEP0;
            }
            break;
        case ML86294_CAMAREA_SET_STEP5:                                       /* STEP5 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_CAMAREA_SET_WRINUM,
                                                          ML86294_CAMAREA_SET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X846_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Function Completion */
                u1_t_ret = (U1)TRUE;
                /* Process Reset */
                u1_s_pict_mlcamarea_set_sts = (U1)ML86294_CAMAREA_SET_STEP0;
            }
            break;
        case ML86294_CAMAREA_SET_STEP6:                                       /* STEP6 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_CAMAREA_SET_WRINUM,
                                                          ML86294_CAMAREA_SET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X720_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Function Completion */
                u1_t_ret = (U1)TRUE;
                /* Process Reset */
                u1_s_pict_mlcamarea_set_sts = (U1)ML86294_CAMAREA_SET_STEP0;
            }
            break;
        case ML86294_CAMAREA_SET_STEP7:                                       /* STEP7 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_CAMAREA_SET_WRINUM,
                                                          ML86294_CAMAREA_SET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_ML86294_MlSETREG_CAMAREA_ADC_1280X621_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Function Completion */
                u1_t_ret = (U1)TRUE;
                /* Process Reset */
                u1_s_pict_mlcamarea_set_sts = (U1)ML86294_CAMAREA_SET_STEP0;
            }
            break;
        case ML86294_CAMAREA_SET_STEP8:                                       /* STEP8 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_CAMAREA_SET_WRINUM,
                                                          ML86294_CAMAREA_SET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_ML86294_MlSETREG_CAMAREA_ADC_1696X954_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Function Completion */
                u1_t_ret = (U1)TRUE;
                /* Process Reset */
                u1_s_pict_mlcamarea_set_sts = (U1)ML86294_CAMAREA_SET_STEP0;
            }
            break;
        case ML86294_CAMAREA_SET_STEP9:                                       /* STEP9 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_CAMAREA_SET_WRINUM,
                                                          ML86294_CAMAREA_SET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_ML86294_MlSETREG_CAMAREA_ADC_1104X621_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Function Completion */
                u1_t_ret = (U1)TRUE;
                /* Process Reset */
                u1_s_pict_mlcamarea_set_sts = (U1)ML86294_CAMAREA_SET_STEP0;
            }
            break;
        case ML86294_CAMAREA_SET_STEP10:                                      /* STEP10 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_CAMAREA_SET_WRINUM,
                                                          ML86294_CAMAREA_SET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_MCU_SYS_PWR_EIZOIC_MlSETREG_CAMAREA_NONE, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Function Completion */
                u1_t_ret = (U1)TRUE;
                /* Process Reset */
                u1_s_pict_mlcamarea_set_sts = (U1)ML86294_CAMAREA_SET_STEP0;
            }
            break;
        default:                                                                /* FAIL */
            /* Process Reset */
            u1_s_pict_mlcamarea_set_sts = (U1)ML86294_CAMAREA_SET_STEP0;
            break;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1    u1_g_Pict_MlMipiSet(const U1 u1_a_req_sts)                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_req_sts  :  Request Status(ON/OFF)                                                                          */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
U1    u1_g_Pict_MlMipiSet(const U1 u1_a_req_sts)
{   /* 暫定　I/Fメモ 6.6.1/6.6.2 Sipへのカメラ映像出力ON/OFF */
    static const ST_REG_WRI_REQ ML86294_MIPI_SET[ML86294_MIPI_SET_WRINUM] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},  /* Bank0 */
        {        0,         1,         0}
    };

    U1      u1_t_ret;                                               /* Function Completion Status  */
    U1      u1_t_reg_req_sts;

    u1_t_ret = (U1)FALSE;

    if(u1_a_req_sts == (U1)PICT_ML_MIPI_ON){                                    /* ON Request */
        /* Set Register */
        u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_MIPI_SET_WRINUM,
                                                      ML86294_MIPI_SET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                      st_sp_ML86294_MlMIPIREG_ON_TBL, &u2_s_pict_ml_reg_btwn_time);
        if(u1_t_reg_req_sts == (U1)TRUE){
            /* Function Completion */
            u1_t_ret = (U1)TRUE;
        }
    }
    else {                                                                      /* OFF Request */
        /* Set Register */
        u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_MIPI_SET_WRINUM,
                                                      ML86294_MIPI_SET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                      st_sp_ML86294_MlMIPIREG_OFF_TBL, &u2_s_pict_ml_reg_btwn_time);
        if(u1_t_reg_req_sts == (U1)TRUE){
            /* Function Completion */
            u1_t_ret = (U1)TRUE;
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1    u1_g_Pict_MlFrzChgSet(const U1 u1_a_req_sts)                                                                               */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_req_sts  :  Request Status(ON/OFF)                                                                          */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
U1    u1_g_Pict_MlFrzChgSet(const U1 u1_a_req_sts)
{   /* 暫定　I/Fメモ 6.7.1.1/6.7.2.1 固着検知の有効化/無効化設定 */
    static const ST_REG_WRI_REQ ML86294_FRZCHG_ON_SET[ML86294_FRZCHG_ON_SET_WRINUM] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},  /* Bank0 */
        {        1,         2,         0},
        {        3,         1,         0},  /* Bank1 */
        {        4,         2,         0},
        {        6,         1,         0},  /* Bank25 */
        {        7,         1,         0},
        {        8,         1,         0},  /* Bank12 */
        {        9,         2,         0},
        {       11,         1,         0},  /* Bank25 */
        {       12,         2,         0}
    };

    static const ST_REG_WRI_REQ ML86294_FRZCHG_OFF_SET[ML86294_FRZCHG_OFF_SET_WRINUM] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},  /* Bank0 */
        {        1,         1,         0},
        {        2,         1,         0},  /* Bank1 */
        {        3,         2,         0},
        {        5,         1,         0},  /* Bank25 */
        {        6,         1,         0},
        {        7,         1,         0},  /* Bank12 */
        {        8,         2,         0},
        {       10,         1,         0},  /* Bank25 */
        {       11,         2,         0}
    };

    U1      u1_t_ret;                                               /* Function Completion Status  */
    U1      u1_t_reg_req_sts;

    u1_t_ret = (U1)FALSE;

    if(u1_a_req_sts == (U1)PICT_ML_FRZ_ON){                                     /* ON Request */
        /* Set Register */
        u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_FRZCHG_ON_SET_WRINUM,
                                                        ML86294_FRZCHG_ON_SET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                        st_sp_ML86294_MlFRZCHGREG_ON_TBL, &u2_s_pict_ml_reg_btwn_time);
        if(u1_t_reg_req_sts == (U1)TRUE){
            /* V-IC-STATUS Interrupt Enable */
            u1_s_pict_ml_frzint_chk_flg = (U1)TRUE;

            /* Drec Count Clear */
            u1_s_pict_mlfrz_drec_cnt = (U1)0;

            /* Function Completion */
            u1_t_ret = (U1)TRUE;
        }
    }
    else {                                                                      /* OFF Request */
        /* Set Register */
        u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_FRZCHG_OFF_SET_WRINUM,
                                                        ML86294_FRZCHG_OFF_SET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                        st_sp_ML86294_MlFRZCHGREG_OFF_TBL, &u2_s_pict_ml_reg_btwn_time);
        if(u1_t_reg_req_sts == (U1)TRUE){
            /* V-IC-STATUS Interrupt Disable */
            u1_s_pict_ml_frzint_chk_flg = (U1)FALSE;

            /* Function Completion */
            u1_t_ret = (U1)TRUE;
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1    u1_g_Pict_MlCamPathSet(const U1 u1_a_req_path)                                                                             */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_req_path  :  Request Camera Path(Normal/Bypass)                                                             */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
U1    u1_g_Pict_MlCamPathSet(const U1 u1_a_req_path)
{   /* 暫定　I/Fメモ 6.7.1.2/6.7.2.2 カメラバイパス/Sip映像経路切替 */
    static const ST_REG_WRI_REQ ML86294_CAMPATH_SET[ML86294_CAMPATH_SET_WRINUM] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},  /* Bank0 */
        {        1,         1,         0},
        {        2,         1,         0},  /* Bank2 */
        {        3,         4,         0}
    };

    U1      u1_t_ret;                                               /* Function Completion Status  */
    U1      u1_t_reg_req_sts;

    u1_t_ret = (U1)FALSE;

    if(u1_a_req_path == (U1)PICT_ML_CAMPATH_NORMAL){                            /* Normal Request */
        /* Set Register */
        u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_CAMPATH_SET_WRINUM,
                                                        ML86294_CAMPATH_SET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                        st_sp_ML86294_MlCAMPATHREG_NORMAL_TBL, &u2_s_pict_ml_reg_btwn_time);
        if(u1_t_reg_req_sts == (U1)TRUE){
            /* Function Completion */
            u1_t_ret = (U1)TRUE;
        }
    }
    else {                                                                      /* Bypass Request */
        /* Set Register */
        u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_CAMPATH_SET_WRINUM,
                                                        ML86294_CAMPATH_SET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                        st_sp_ML86294_MlFRZCHGREG_BYPASS_TBL, &u2_s_pict_ml_reg_btwn_time);
        if(u1_t_reg_req_sts == (U1)TRUE){
            /* Function Completion */
            u1_t_ret = (U1)TRUE;
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1    u1_s_Pict_MlRcvVIcStatusNty(void)                                                                                          */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
static U1    u1_s_Pict_MlRcvVIcStatusNty(void)
{   /* 暫定　I/Fメモ 6.7.4 固着検知割り込み */
    static const ST_REG_WRI_REQ ML86294_RCVVICSTATUS_CLEAR_SET[ML86294_RCVVICSTATUS_CLEAR_SET_WRINUM] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0}
    };

    U1      u1_t_ret;                                               /* Function Completion Status  */
    U1      u1_t_reg_req_sts;
    U1      u1_t_reg_read_result;                                   /* Register Read Result */

    u1_t_ret = (U1)FALSE;

    switch (u1_s_pict_mlrcvvicstatus_sts){
        case ML86294_RCVVICSTATUS_STEP0:                          /* STEP0 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_BANKSET_WRINUM,
                                                          ML86294_BANKSET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_ML86294_SET_BANK0_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlrcvvicstatus_sts = (U1)ML86294_RCVVICSTATUS_STEP1;
            }
            break;
        case ML86294_RCVVICSTATUS_STEP1:                          /* STEP1 */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGREAD(&u2_s_pict_ml_regstep, &u4_s_pict_ml_i2c_ack_wait_time,
                                                           st_sp_ML86294_MlRCVVICSTATUS_RD_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_reg_read_result = st_sp_ML86294_MlRCVVICSTATUS_RD_TBL[1].u1p_pdu[1];
                if(u1_s_pict_mlfrz_drec_cnt < (U1)PICT_ML_MlRCVVICSTATUS_DREC_CNT_MAX){   /* Drec Counter < 4 */
                    /* ダイレコ保存 *//* 暫定 シス検ではダイレコ保存未対応 */
                    u1_s_pict_mlfrz_drec_cnt++;
                }

                /* Next Process */
                u1_s_pict_mlirqhpdcycchk_sts = (U1)ML86294_RCVVICSTATUS_STEP2;
            }
            break;
        case ML86294_RCVVICSTATUS_STEP2:                          /* STEP2 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_RCVVICSTATUS_CLEAR_SET_WRINUM,
                                                          ML86294_RCVVICSTATUS_CLEAR_SET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_ML86294_MlRCVVICSTATUS_CLEAR_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Function Completion */
                u1_t_ret = (U1)TRUE;
            }
        default:                                                                /* FAIL */
            /* Process Reset */
            u1_s_pict_mlirqhpdcycchk_sts = (U1)ML86294_RCVVICSTATUS_STEP0;
            break;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1    u1_g_Pict_MlI2cMuteSet(const U1 u1_a_req_sts)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_req_sts  :  Request Status(ON/OFF)                                                                          */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
U1    u1_g_Pict_MlI2cMuteSet(const U1 u1_a_req_sts)
{   /* 暫定　I/Fメモ 6.9.1 I2C全画面MUTE */
    static const ST_REG_WRI_REQ ML86294_I2CMUTE_SET[ML86294_I2CMUTE_SET_WRINUM] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},  /* Bank2 */
        {        1,         1,         0}
    };

    U1      u1_t_ret;                                               /* Function Completion Status  */
    U1      u1_t_reg_req_sts;

    u1_t_ret = (U1)FALSE;

    if(u1_a_req_sts == (U1)PICT_ML_I2C_MUTE_ON){                                 /* ON Request */
        /* Set Register */
        u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_I2CMUTE_SET_WRINUM,
                                                      ML86294_I2CMUTE_SET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                      st_sp_ML86294_MlI2CMUTEREG_ON_TBL, &u2_s_pict_ml_reg_btwn_time);
        if(u1_t_reg_req_sts == (U1)TRUE){
            /* Function Completion */
            u1_t_ret = (U1)TRUE;
        }
    }
    else {                                                                       /* OFF Request */
        /* Set Register */
        u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_I2CMUTE_SET_WRINUM,
                                                      ML86294_I2CMUTE_SET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                      st_sp_ML86294_MlI2CMUTEREG_OFF_TBL, &u2_s_pict_ml_reg_btwn_time);
        if(u1_t_reg_req_sts == (U1)TRUE){
            /* Function Completion */
            u1_t_ret = (U1)TRUE;
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1    u1_g_Pict_MlNoAisMuteSet(const U1 u1_a_req_sts)                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_req_sts  :  Request Status(ON/OFF)                                                                          */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
U1    u1_g_Pict_MlNoAisMuteSet(const U1 u1_a_req_sts)
{   /* 暫定　I/Fメモ 6.9.2 I2Cヒーコン部以外MUTE */
    static const ST_REG_WRI_REQ ML86294_NOAISMUTE_SET[ML86294_NOAISMUTE_SET_WRINUM] = {
        /*  開始位置,   書込み個数, レジスタアクセス間Wait時間 */
        {        0,         1,         0},  /* Bank11 */
        {        1,         1,         0}
    };

    U1      u1_t_ret;                                               /* Function Completion Status  */
    U1      u1_t_reg_req_sts;

    u1_t_ret = (U1)FALSE;

    if(u1_a_req_sts == (U1)PICT_ML_NOAIS_MUTE_ON){                                /* ON Request */
        /* Set Register */
        u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_NOAISMUTE_SET_WRINUM,
                                                      ML86294_NOAISMUTE_SET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                      st_sp_ML86294_MlNOAISMUTEREG_ON_TBL, &u2_s_pict_ml_reg_btwn_time);
        if(u1_t_reg_req_sts == (U1)TRUE){
            /* Function Completion */
            u1_t_ret = (U1)TRUE;
        }
    }
    else {                                                                       /* OFF Request */
        /* Set Register */
        u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_NOAISMUTE_SET_WRINUM,
                                                      ML86294_NOAISMUTE_SET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                      st_sp_ML86294_MlNOAISMUTEREG_OFF_TBL, &u2_s_pict_ml_reg_btwn_time);
        if(u1_t_reg_req_sts == (U1)TRUE){
            /* Function Completion */
            u1_t_ret = (U1)TRUE;
        }
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1    u1_s_Pict_MLMIPISyncCheck(void)                                                                                            */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
U1    u1_s_Pict_MLMIPISyncCheck(void)
{   /* 暫定　I/Fメモ 6.7.3 カメラ映像入力の同期検出 */
    /* 暫定 カメラ同期検知でのレジスタ連続アクセス防止のためのポーリングタイマ20ms */
    static const U2 ML86294_MIPISYNCCHK_WAIT_POLING = (U2)(20U / ML86294_TASK_TIME);

    U1      u1_t_ret;                                               /* Function Completion Status  */
    U1      u1_t_time_chk_flg;
    U1      u1_t_reg_req_sts;
    U1      u1_t_reg_read_result;                                   /* Register Read Result */
    U1      u1_t_mipi_sync_sts;                                     /* MIPI Synchronize Status */

    u1_t_ret = (U1)FALSE;

    switch (u1_s_pict_mlregget_sts){
        case ML86294_REGGET_STEP0:                          /* STEP0 */
            u1_t_time_chk_flg = u1_s_Pict_Ml86294_TimChk((U2)u2_s_pict_mlregget_timer, ML86294_MIPISYNCCHK_WAIT_POLING);
            if(u1_t_time_chk_flg == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlregget_sts = (U1)ML86294_REGGET_STEP1;
                /* Poling Timer Clear */
                u2_s_pict_mlregget_timer = (U2)0;
            }
            else{
                /* Function Completion */
                u1_t_ret = (U1)TRUE;

                u2_s_pict_mlregget_timer++;
            }
            break;
        case ML86294_REGGET_STEP1:                          /* STEP1 */
            /* Set Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGSET(&u2_s_pict_ml_regstep, (U2)ML86294_BANKSET_WRINUM,
                                                          ML86294_BANKSET, &u4_s_pict_ml_i2c_ack_wait_time,
                                                          st_sp_ML86294_SET_BANK0_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                /* Next Process */
                u1_s_pict_mlregget_sts = (U1)ML86294_REGGET_STEP2;
            }
            break;
        case ML86294_REGGET_STEP2:                          /* STEP2 */
            /* Read Register */
            u1_t_reg_req_sts = u1_PICT_ML_I2C_CTRL_REGREAD(&u2_s_pict_ml_regstep, &u4_s_pict_ml_i2c_ack_wait_time,
                                                            st_sp_ML86294_MIPISYNCSTATUS_RD_TBL, &u2_s_pict_ml_reg_btwn_time);
            if(u1_t_reg_req_sts == (U1)TRUE){
                u1_t_reg_read_result = st_sp_ML86294_MIPISYNCSTATUS_RD_TBL[1].u1p_pdu[1];
                u1_t_mipi_sync_sts = u1_t_reg_read_result & (U1)PICT_REG_MASK_BIT_3;
                if(u1_t_mipi_sync_sts == (U1)PICT_REG_MASK_BIT_3){          /* bit[3] = 1 */
                    u1_s_pict_mlregget_result = (U1)PICT_ML_MIPI_SYNC_ON;
                }
                else{                                                       /* bit[3] = 0 */
                    u1_s_pict_mlregget_result = (U1)PICT_ML_MIPI_SYNC_OFF;
                }
                U1 u1_s_pict_mlregget_flag = (U1)ML86294_REGGET_FLAG_COMP;
                /* Function Completion */
                u1_t_ret = (U1)TRUE;
            }
            break;
        default:                                                                /* FAIL */
            /* Process Reset */
            u1_s_pict_mlregget_sts = (U1)ML86294_REGGET_STEP0;
            break;
    }

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  U1    u1_g_Pict_MlRegGet(U1 * u1_a_reg_read_result)                                                                              */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_reg_read_result  :  Register Read Result                                                                    */
/*  Return:         TRUE (Function Completion) / FALSE (Function Incompletion)                                                       */
/*===================================================================================================================================*/
U1    u1_g_Pict_MlRegGet(U1 * u1_a_reg_read_result)
{   /* 暫定 外部提供I/Fでのレジスタアクセス手法については要検討 */
    U1      u1_t_ret;                                               /* Function Completion Status  */

    if(u1_s_pict_mlregget_flag == (U1)ML86294_REGGET_FLAG_COMP){        /* Register Read Complete */
        u1_t_ret = (U1)TRUE;
        (*u1_a_reg_read_result) = u1_s_pict_mlregget_result;
        u1_s_pict_mlregget_flag = (U1)ML86294_REGGET_FLAG_STOP;         /* Register Read Stop */
    }
    else{
        u1_t_ret = (U1)FALSE;
    }

    u1_s_pict_mlregget_flag = (U1)ML86294_REGGET_FLAG_START;            /* Register Read Start */

    return(u1_t_ret);
}

/*===================================================================================================================================*/
/*  void    vd_s_Pict_MLDevRst(void)                                                                                                 */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      -                                                                                                                */
/*  Return:         -                                                                                                                */
/*===================================================================================================================================*/
static void    vd_s_Pict_MLDevRst(void)
{   /* 暫定　I/Fメモ 6.11 デバイス再起動 */
    static const U2 ML86294_DEVRST_WAIT_POLING = (U2)(10U / ML86294_TASK_TIME);   /* t23 min:10ms */

    U1      u1_t_time_chk_flg;

    switch (u1_s_pict_mldevrst_sts){
        case ML86294_DEV_RST_STEP0:                                        /* STEP0 */
            /* DEV_RST State */
            u1_s_pict_ml_state = (U1)ML86294_SEQ_DEV_RST;
        
            /* Notification the SiP side of the video IC malfunction */
            u1_s_pict_mldevrst_notif = (U1)PICT_ML_DEVRST_ACT;

            /* Stop of GVIF3-TX fail-safe process */
            /* T.B.D */

            /* V-IC-RST = L */
            vd_PICT_MLFAILCYCCHK_V_IC_RST_L();

            /* Next Process */
            u1_s_pict_mldevrst_sts = (U1)ML86294_DEV_RST_STEP1;

            break;
        case ML86294_DEV_RST_STEP1:                                        /* STEP1 */
            /* Poling Check */
            u1_t_time_chk_flg = u1_s_Pict_Ml86294_TimChk((U2)u1_s_pict_mlcyc_dev_rst_timer, ML86294_DEVRST_WAIT_POLING);

            if(u1_t_time_chk_flg == (U1)TRUE){
                /* V-IC-RST = H *//* 暫定 ポート設定I/F展開後に見直し */
                vd_PICT_MLFAILCYCCHK_V_IC_RST_H();

                /* ML86294 Init */
                vd_g_Pict_Ml86294_Init();
                /* State = IDLE */
                /* Process = STEP0 */
                /* Timer = 0 */
            }
            else{
                u1_s_pict_mlcyc_dev_rst_timer++;
            }
            break;
        default:                                                                /* FAIL */
            /* Process Reset */
            u1_s_pict_mldevrst_sts = (U1)ML86294_DEV_RST_STEP0;
            break;
    }
}

/*===================================================================================================================================*/
/*  U1    u1_g_Pict_MlDevRstGet(void)                                                                                                */
/* --------------------------------------------------------------------------------------------------------------------------------- */
/*  Arguments:      u1_a_reg_read_result  :  Register Read Result                                                                    */
/*  Return:         PICT_ML_DEVRST_NON(0) / ML86294_SEQ_DEV_RST(1)                                                                   */
/*===================================================================================================================================*/
U1    u1_g_Pict_MlDevRstGet(void)
{
    return(u1_s_pict_mldevrst_notif);
}
