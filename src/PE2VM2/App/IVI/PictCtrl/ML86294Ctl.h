/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
#ifndef ML86294CTL_H
#define ML86294CTL_H
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"

#include "Dio.h"
#include "gpi2c_ma.h"
#include "Mcu_I2c_Ctrl_private.h"
#include "pictic.h"
#include "PictCtl.h"
#include "SysEcDrc.h"

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/* Register Access Data */
#define ML86294_I2C_SLAVEADR_WR                 (0x72U)
#define ML86294_I2C_SLAVEADR_RD                 (0x73U)
#define ML86294_I2C_RWC_BYTE1                   (1U)
#define ML86294_I2C_RWC_BYTE2                   (2U)
#define ML86294_I2C_RWC_BYTE3                   (3U)

/* Register Bit Mask */
#define PICT_REG_MASK_BIT_0	                    (0x01U)
#define PICT_REG_MASK_BIT_1	                    (0x02U)
#define PICT_REG_MASK_BIT_2	                    (0x04U)
#define PICT_REG_MASK_BIT_3	                    (0x08U)
#define PICT_REG_MASK_BIT_4	                    (0x10U)
#define PICT_REG_MASK_BIT_5	                    (0x20U)
#define PICT_REG_MASK_BIT_6	                    (0x40U)
#define PICT_REG_MASK_BIT_7	                    (0x80U)

/* Register Read Result */
#define PICT_ML_REG_READ_NG                     (0U)
#define PICT_ML_REG_READ_OK                     (1U)

#define PICT_ML_MLFLZDATCYCCHK_L1               (18U)
#define PICT_ML_MLFLZDATCYCCHK_L2               (6U)
#define PICT_ML_MLFLZDATCYCCHK_FRZ_DREC_OFF_CNT_MAX (3U)
#define PICT_ML_MLFLZDATCYCCHK_FRZ_DREC_ON_CNT_MAX (3U)
#define PICT_ML_MLFLZDATCYCCHK_ROUTE_DREC_CNT_MAX (3U)
#define PICT_ML_MLFLZDATCYCCHK_ROUTE_BYPASS     (0x00U)

#define PICT_ML_MLIRQHPD_ASSERT_DREC_CNT_MAX    (3U)
#define PICT_ML_MLIRQHPD_DPCD_READ_REGDATA1     (0x0FU)
#define PICT_ML_MLIRQHPD_DPCD_READ_REGDATA2     (0x90U)
#define PICT_ML_MLIRQHPD_DPCD_AUXSND_REGDATA1   (0xE0U)
#define PICT_ML_MLIRQHPD_DPCD_AUXSND_REGDATA2   (0x03U)
#define PICT_ML_MLIRQHPD_DPCD_AUXCOM_OK         (0x77U)

#define PICT_ML_CAMAREASET_READY                (0U)
#define PICT_ML_CAMAREASET_PROCESSING           (1U)
#define PICT_ML_CAMAREASET_COMPLETED            (2U)

#define PICT_ML_MIPI_SYNC_OFF                   (0U)
#define PICT_ML_MIPI_SYNC_ON                    (1U)

#define PICT_ML_MlRCVVICSTATUS_DREC_CNT_MAX     (4U)

#define PICT_ML_MLFAILCYCCHK_DEV_ERR            (0x00U)
#define PICT_ML_MLFAILCYCCHK_DREC_CNT_MAX       (3U)
#define PICT_ML_MLFAILCYCCHK_DEV_RESET_CNT_MAX  (0U)

#define PICT_ML_MLSYNCCYCCHK_SIP_ERR            (0U)
#define PICT_ML_MLSYNCCYCCHK_SIP_DREC_CNT_MAX   (3U)
#define PICT_ML_MLSYNCCYCCHK_CAM_ERR            (0U)
#define PICT_ML_MLSYNCCYCCHK_CAM_DREC_CNT_MAX   (3U)

#define PICT_ML_MLROUTECYCCHK_DREC_CNT_MAX      (3U)

#define PICT_ML_MIPIRCVCYCCHK_RCV_DAT_MASK      (0xFEU)
#define PICT_ML_MIPIRCVCYCCHK_RCV_OK            (0x00U)
#define PICT_ML_MLMIPIRCVCYCCHK_DREC_CNT_MAX    (3U)

#define PICT_ML_DEVRST_NON                      (0U)
#define PICT_ML_DEVRST_ACT                      (1U)

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#define PICT_ML_PWRON_COMP                      (MCU_STEP_EIZOIC_OVERALL_FIN) 

#define PICT_ML_IO_STS_LOW                      (0U)
#define PICT_ML_IO_STS_HIGH                     (1U)

#define PICT_ML_CAM_MODE_ON                     (TRUE)
#define PICT_ML_CAM_DIAG_MODE_OFF               (FALSE)
#define PICT_ML_CAM_SYNC_MODE_OK                (PICT_CAM_SYNC_CHK_OK)
#define PICT_ML_CAM_QUAL_MODE_RECEIVED          (TRUE)
#define PICT_ML_CAM_QUAL_MODE_CAM               (PICT_VIS_KIND_CAM)

#define PICT_ML_GVIFIF_NONE                     (PICT_GVIFIF_NONE)
#define PICT_ML_GVIFIF_ADC_ECU                  (PICT_GVIFIF_ADAS)

#define PICT_ML_CAN_CAM_SIZE_NONE               (PICT_CAN_CAM_SIZE_NONE)
#define PICT_ML_CAN_CAM_SIZE_MAX                (PICT_CAN_CAM_SIZE_1104X621 + 1)
#define PICT_ML_CID_TYPE_MAX                    (2U)    /* 暫定 車パラI/F展開後に見直し */
#define PICT_ML_CID_TYPE_NML                    (0U)    /* 暫定 車パラI/F展開後に見直し */
#define PICT_ML_CID_TYPE_INTEG                  (1U)    /* 暫定 車パラI/F展開後に見直し */

#define u1_PICT_ML_I2C_CTRL_REGSET(u, v, w, x, y, z)    (Mcu_Dev_I2c_Ctrl_RegSet((U1)MCU_I2C_ACK_VIDEO_IC, (u), (v), (U1)GP_I2C_MA_SLA_1_VIDEO_IC, (w), (x), (y), (z)))
#define u1_PICT_ML_I2C_CTRL_REGREAD(w, x, y, z)         (Mcu_Dev_I2c_Ctrl_RegRead((U1)MCU_I2C_ACK_VIDEO_IC, (w), (U1)GP_I2C_MA_SLA_1_VIDEO_IC, (x), (y), (z), (U1)MCU_I2C_WAIT_NON))

#define vd_PICT_ML_DREC_REQ(x, y, z)                    (vd_g_SysEcDrc_Drec((U1)SYSECDRC_DREC_CAT_EIZOIC, (x), (y), (z)))

#define u1_PICT_ML_GET_V_IC_STATUS1()                   (Dio_ReadChannel(DIO_ID_PORT3_CH0))

#define u1_PICT_MLFLZDATCYCCHK_GET_DISP_REQ_GPIO0()     (Dio_ReadChannel(DIO_ID_PORT2_CH2))
#define u1_PICT_MLFLZDATCYCCHK_GET_CAM_STS()            (u1_g_PictCtl_CamStsGet())
#define u1_PICT_MLFLZDATCYCCHK_GET_CAM_DIAG_STS()       (u1_g_PictCtl_GetCamDiagMode())
#define u1_PICT_MLFLZDATCYCCHK_GET_CAM_SYNC_STS()       (u1_g_PictCtl_CamSyncSts())
#define u1_PICT_MLFLZDATCYCCHK_GET_QUALMODE_REV_STS()   (u1_g_PictCtl_RcvQualModeRevFlgSts())
#define u1_PICT_MLFLZDATCYCCHK_GET_QUALMODE_DATA()      (u1_g_PictCtl_RcvQualModeRevDate())

#define u1_PICT_MLROUTECYCCHK_GET_V_IC_STATUS2()        (Dio_ReadChannel(DIO_ID_PORT3_CH2))

#define vd_PICT_MLCAMAREASET_GET_CAMAREA_KIND()         (u1_g_PictCtl_CamKindSts())
#define vd_PICT_MLCAMAREASET_GET_CAMAREA_SIZE()         (u1_g_PictCtl_CamSizeSts())
//#define vd_PICT_MLCAMAREASET_GET_CID_TYPE()             (u1_g_PictCtl_CidType())    /* 暫定 車パラI/F展開後に見直し */

#define vd_PICT_MLFAILCYCCHK_V_IC_RST_L()               (Dio_WriteChannel(DIO_ID_PORT3_CH3, (Dio_LevelType)PICT_ML_IO_STS_LOW))
#define vd_PICT_MLFAILCYCCHK_V_IC_RST_H()               (Dio_WriteChannel(DIO_ID_PORT3_CH3, (Dio_LevelType)PICT_ML_IO_STS_HIGH))


/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Prototypes                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
void  vd_g_Pict_Ml86294_Init(void);
void  vd_g_Pict_Ml86294_Routine(void);
U1    u1_g_Pict_MlCamAreaSet(void);
U1    u1_g_Pict_MlMipiSetOn(void);
U1    u1_g_Pict_MlMipiSetOff(void);
U1    u1_g_Pict_MlFrzChgSetOn(void);
U1    u1_g_Pict_MlFrzChgSetOff(void);
U1    u1_g_Pict_MlCamPathSetNml(void);
U1    u1_g_Pict_MlCamPathSetByp(void);
U1    u1_g_Pict_MlRegGet(U1 * u1_a_reg_read_result);
U1    u1_g_Pict_MlI2cMuteSetOn(void);
U1    u1_g_Pict_MlI2cMuteSetOff(void);
U1    u1_g_Pict_MlNoAisMuteSetOn(void);
U1    u1_g_Pict_MlNoAisMuteSetOff(void);
U1    u1_g_Pict_MlDevRstGet(void);

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Externs                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/

#endif      /* ML86294CTL_H */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History  :  ML86294Ctl.c                                                                                                  */
/*                                                                                                                                   */
/*===================================================================================================================================*/