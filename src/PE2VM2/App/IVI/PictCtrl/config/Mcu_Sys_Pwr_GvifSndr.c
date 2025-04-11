/*===================================================================================================================================*/
/*  Copyright DENSO Corporation                                                                                                      */
/*===================================================================================================================================*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Include Files                                                                                                                    */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
#include "aip_common.h"
#include "Mcu_Sys_Pwr_GvifSndr.h"
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Literal Definitions                                                                                                              */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Macro Definitions                                                                                                                */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Type Definitions                                                                                                                 */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Variable Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Static Function Prototypes                                                                                                       */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Constant Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x76U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU3[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x75U,    /* Write Address */
    (U1)0x40U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU4[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x78U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU5[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x80U,    /* Write Address */
    (U1)0x0AU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU6[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x8EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU7[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x97U,    /* Write Address */
    (U1)0x80U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU8[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x98U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU9[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xB8U,    /* Write Address */
    (U1)0xA1U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU10[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xB9U,    /* Write Address */
    (U1)0xA0U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU11[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xECU,    /* Write Address */
    (U1)0x30U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU12[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xEEU,    /* Write Address */
    (U1)0x39U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU13[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU14[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x12U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU15[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU16[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1AU,    /* Write Address */
    (U1)0x41U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU17[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1BU,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU18[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x1CU,    /* Write Address */
    (U1)0xFFU     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU19[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x24U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU20[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2FU,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU21[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU22[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFBU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_PDU3[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x49U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x00U,    /* Write Data 0x42 */
    (U1)0xFFU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU6[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU7[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x01U,    /* Write Data 0x42 */
    (U1)0x55U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU12[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU13[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x02U,    /* Write Data 0x42 */
    (U1)0xAEU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU18[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU19[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x04U,    /* Write Data 0x42 */
    (U1)0xFFU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU24[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU25[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x05U,    /* Write Data 0x42 */
    (U1)0xFFU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU30[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU31[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x06U,    /* Write Data 0x42 */
    (U1)0xFFU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU36[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU37[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x20U,    /* Write Data 0x42 */
    (U1)0x09U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU42[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU43[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x21U,    /* Write Data 0x42 */
    (U1)0x11U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU48[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU49[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x28U,    /* Write Data 0x42 */
    (U1)0x03U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU54[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU55[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x2AU,    /* Write Data 0x42 */
    (U1)0x0DU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU60[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU61[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x2BU,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU66[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU67[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x60U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU72[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU73[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0xA0U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU78[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU79[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0xA1U,    /* Write Data 0x42 */
    (U1)0x30U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU84[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU85[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0xA2U,    /* Write Data 0x42 */
    (U1)0x03U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU90[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU91[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0xA3U,    /* Write Data 0x42 */
    (U1)0x87U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU96[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU97[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x00U,    /* Write Data 0x42 */
    (U1)0x83U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU102[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU103[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x01U,    /* Write Data 0x42 */
    (U1)0x03U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU108[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU109[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x02U,    /* Write Data 0x42 */
    (U1)0x50U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU114[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU115[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x03U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU120[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU121[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x04U,    /* Write Data 0x42 */
    (U1)0x11U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU126[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU127[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x05U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU132[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU133[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x06U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU138[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU139[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x07U,    /* Write Data 0x42 */
    (U1)0x11U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU144[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU145[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x08U,    /* Write Data 0x42 */
    (U1)0x22U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU150[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU151[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x09U,    /* Write Data 0x42 */
    (U1)0x33U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU156[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU157[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x0AU,    /* Write Data 0x42 */
    (U1)0x44U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU162[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU163[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x0BU,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU168[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU169[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x0CU,    /* Write Data 0x42 */
    (U1)0x11U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU174[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU175[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x0DU,    /* Write Data 0x42 */
    (U1)0x22U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU180[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU181[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x0EU,    /* Write Data 0x42 */
    (U1)0x33U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU186[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU187[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x01U,    /* Write Data 0x41 */
    (U1)0x0FU,    /* Write Data 0x42 */
    (U1)0x44U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU192[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU193[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x00U,    /* Write Data 0x42 */
    (U1)0x05U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU198[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU199[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x01U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU204[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU205[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x02U,    /* Write Data 0x42 */
    (U1)0x04U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU210[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU211[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x04U,    /* Write Data 0x42 */
    (U1)0x03U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU216[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU217[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x05U,    /* Write Data 0x42 */
    (U1)0x03U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU222[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU223[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x06U,    /* Write Data 0x42 */
    (U1)0x03U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU228[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU229[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x07U,    /* Write Data 0x42 */
    (U1)0x03U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU234[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU235[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x10U,    /* Write Data 0x42 */
    (U1)0xD7U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU240[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU241[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x11U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU246[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU247[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x12U,    /* Write Data 0x42 */
    (U1)0xF2U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU252[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU253[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x13U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU258[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU259[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x14U,    /* Write Data 0x42 */
    (U1)0x0DU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU264[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU265[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x15U,    /* Write Data 0x42 */
    (U1)0x01U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU270[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU271[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x16U,    /* Write Data 0x42 */
    (U1)0x43U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU276[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU277[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x17U,    /* Write Data 0x42 */
    (U1)0x01U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU282[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU283[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x18U,    /* Write Data 0x42 */
    (U1)0xAFU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU288[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU289[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x19U,    /* Write Data 0x42 */
    (U1)0x01U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU294[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU295[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x1AU,    /* Write Data 0x42 */
    (U1)0x1BU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU300[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU301[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x1BU,    /* Write Data 0x42 */
    (U1)0x02U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU306[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU307[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x1CU,    /* Write Data 0x42 */
    (U1)0x29U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU312[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU313[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x1DU,    /* Write Data 0x42 */
    (U1)0x03U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU318[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU319[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x1EU,    /* Write Data 0x42 */
    (U1)0x01U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU324[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU325[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x20U,    /* Write Data 0x42 */
    (U1)0x42U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU330[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU331[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x21U,    /* Write Data 0x42 */
    (U1)0xE0U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU336[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU337[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x22U,    /* Write Data 0x42 */
    (U1)0x53U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU342[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU343[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x23U,    /* Write Data 0x42 */
    (U1)0xE1U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU348[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU349[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x24U,    /* Write Data 0x42 */
    (U1)0x53U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU354[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU355[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x25U,    /* Write Data 0x42 */
    (U1)0xE2U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU360[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU361[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x26U,    /* Write Data 0x42 */
    (U1)0x53U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU366[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU367[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x27U,    /* Write Data 0x42 */
    (U1)0xE3U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU372[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU373[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x28U,    /* Write Data 0x42 */
    (U1)0x33U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU378[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU379[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x29U,    /* Write Data 0x42 */
    (U1)0xE4U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU384[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU385[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x2AU,    /* Write Data 0x42 */
    (U1)0x33U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU390[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU391[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x2BU,    /* Write Data 0x42 */
    (U1)0xE5U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU396[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU397[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x2CU,    /* Write Data 0x42 */
    (U1)0x30U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU402[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU403[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x2DU,    /* Write Data 0x42 */
    (U1)0xE8U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU408[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU409[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x34U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU414[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU415[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x35U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU420[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU421[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x40U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU426[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU427[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x41U,    /* Write Data 0x42 */
    (U1)0x0AU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU432[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU433[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x42U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU438[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU439[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x43U,    /* Write Data 0x42 */
    (U1)0x0AU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU444[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU445[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x44U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU450[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU451[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x45U,    /* Write Data 0x42 */
    (U1)0x0AU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU456[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU457[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x46U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU462[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU463[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x47U,    /* Write Data 0x42 */
    (U1)0x0AU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU468[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU469[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x48U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU474[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU475[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x49U,    /* Write Data 0x42 */
    (U1)0x0AU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU480[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU481[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x60U,    /* Write Data 0x42 */
    (U1)0x32U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU486[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU487[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x61U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU492[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU493[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x62U,    /* Write Data 0x42 */
    (U1)0x78U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU498[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU499[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x63U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU504[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU505[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x64U,    /* Write Data 0x42 */
    (U1)0xF0U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU510[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU511[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x65U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU516[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU517[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x66U,    /* Write Data 0x42 */
    (U1)0xE0U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU522[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU523[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x67U,    /* Write Data 0x42 */
    (U1)0x01U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU528[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU529[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x68U,    /* Write Data 0x42 */
    (U1)0xDAU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU534[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU535[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x69U,    /* Write Data 0x42 */
    (U1)0x02U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU540[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU541[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x6AU,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU546[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU547[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x6BU,    /* Write Data 0x42 */
    (U1)0x03U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU552[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU553[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x6CU,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU558[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU559[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x6DU,    /* Write Data 0x42 */
    (U1)0x03U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU564[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU565[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x70U,    /* Write Data 0x42 */
    (U1)0xA3U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU570[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU571[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x71U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU576[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU577[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x72U,    /* Write Data 0x42 */
    (U1)0x62U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU582[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU583[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x73U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU588[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU589[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x74U,    /* Write Data 0x42 */
    (U1)0x21U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU594[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU595[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x75U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU600[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU601[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x76U,    /* Write Data 0x42 */
    (U1)0x20U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU606[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU607[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x77U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU612[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU613[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x78U,    /* Write Data 0x42 */
    (U1)0x24U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU618[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU619[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x79U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU624[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU625[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0xB0U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU630[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU631[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0xC0U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU636[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU637[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0xC1U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU642[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU643[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0xC2U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU648[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU649[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0xC3U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU654[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU655[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0xC8U,    /* Write Data 0x42 */
    (U1)0x04U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU660[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU661[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0xC9U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x03U,    /* Write Data 0x43 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU666[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU667[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0xCAU,    /* Write Data 0x42 */
    (U1)0x02U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU672[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU673[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0xCBU,    /* Write Data 0x42 */
    (U1)0x04U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU678[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU679[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0xD0U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU684[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU685[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x00U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0xF0U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU690[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x00U,    /* Write Data 0x42 */
    (U1)0x14U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU6[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU7[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x01U,    /* Write Data 0x42 */
    (U1)0x14U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU12[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU13[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x02U,    /* Write Data 0x42 */
    (U1)0xC4U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU18[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU19[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x03U,    /* Write Data 0x42 */
    (U1)0x81U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU24[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU25[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x08U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU30[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU31[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x0AU,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU36[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU37[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x0CU,    /* Write Data 0x42 */
    (U1)0x10U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU42[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU43[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x0DU,    /* Write Data 0x42 */
    (U1)0x01U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU48[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU49[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x0EU,    /* Write Data 0x42 */
    (U1)0x01U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU54[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU55[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x10U,    /* Write Data 0x42 */
    (U1)0xA4U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU60[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU61[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x11U,    /* Write Data 0x42 */
    (U1)0x1FU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU66[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU67[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x12U,    /* Write Data 0x42 */
    (U1)0x30U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU72[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU73[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x13U,    /* Write Data 0x42 */
    (U1)0x2AU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU78[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU79[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x14U,    /* Write Data 0x42 */
    (U1)0x76U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU84[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU85[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x15U,    /* Write Data 0x42 */
    (U1)0x2FU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU90[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU91[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x16U,    /* Write Data 0x42 */
    (U1)0xBCU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU96[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU97[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x17U,    /* Write Data 0x42 */
    (U1)0x34U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU102[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU103[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x18U,    /* Write Data 0x42 */
    (U1)0x48U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU108[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU109[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x19U,    /* Write Data 0x42 */
    (U1)0x3FU,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU114[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU115[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x1AU,    /* Write Data 0x42 */
    (U1)0x60U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU120[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU121[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x1BU,    /* Write Data 0x42 */
    (U1)0x54U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU126[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU127[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x1CU,    /* Write Data 0x42 */
    (U1)0x78U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU132[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU133[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x1DU,    /* Write Data 0x42 */
    (U1)0x69U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU138[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU139[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x00U,    /* Write Data 0x41 */
    (U1)0x21U,    /* Write Data 0x42 */
    (U1)0x00U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU144[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU145[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x02U,    /* Write Data 0x41 */
    (U1)0x00U,    /* Write Data 0x42 */
    (U1)0x01U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU150[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU151[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE8] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,
    (U1)0x40U,    /* Write Address   */
    (U1)0x10U,    /* Write Data 0x40 */
    (U1)0x07U,    /* Write Data 0x41 */
    (U1)0x00U,    /* Write Data 0x42 */
    (U1)0x05U,    /* Write Data 0x43 */
    (U1)0x00U,    /* Write Data 0x44 */
    (U1)0x01U     /* Write Data 0x45 */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU156[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET2_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x47U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET3_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET3_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xB6U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET3_PDU3[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_HPD_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_HPD_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_HPD_PDU3[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_HPD_PDU4[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x51U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_HPD_PDU5[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_HPD_PDU6[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET3_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET1_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x60U,    /* Write Address */
    (U1)0x77U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE2] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U     /* Write Address */
};

U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE2];

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET2_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x07U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET2_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFBU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET2_PDU3[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET2_PDU4[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2EU,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET2_PDU5[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2EU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2AU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1_PDU3[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x2CU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1_PDU4[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1_PDU5[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x08U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1_PDU6[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1_PDU7[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x06U,    /* Write Address */
    (U1)0x30U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1_PDU8[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1_PDU9[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x01U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP2_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_STATUS_RD_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE2] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x10U     /* Write Address */
};

U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_STATUS_RD_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE2];

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_EVENT_RD_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE2] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x13U     /* Write Address */
};

U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_EVENT_RD_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE2];

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP3_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U,    /* Write Address */
    (U1)0x83U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE2] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x20U     /* Write Address */
};

U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3];

U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEV_ID_RD_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE2];

U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEV_ID_RD_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE6];

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP4_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x10U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP4_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP4_PDU3[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xB6U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP4_PDU4[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP_HPD_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x40U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP_HPD_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x41U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP_HPD_PDU3[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x42U,    /* Write Address */
    (U1)0x02U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP_HPD_PDU4[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x43U,    /* Write Address */
    (U1)0x51U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP_HPD_PDU5[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP_HPD_PDU6[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x45U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_ENC_RD_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE2] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x30U     /* Write Address */
};

U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_ENC_RD_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE2];

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP5_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPSTOP_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPSTOP_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x15U,    /* Write Address */
    (U1)0x83U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPSTOP_PDU3[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x11U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPSTOP_PDU4[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x12U,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP6_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_GVIF3TX0_ACT_RD_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE2] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0x00U     /* Write Address */
};

U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_GVIF3TX0_ACT_RD_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE2];

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP7_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x00U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP7_PDU2[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xB6U,    /* Write Address */
    (U1)0x01U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP7_PDU3[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x04U     /* Write Data */
};

const U1 u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP8_PDU1[MCU_SYS_PWR_GVIFSNDR_RWC_BYTE3] = {
    (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR,    /* Slave Address */
    (U1)0xFFU,    /* Write Address */
    (U1)0x08U     /* Write Data */
};


const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT[MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU1[0],
        (U4)0x30040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU2[0],
        (U4)0x30080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU3[0],
        (U4)0x300C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU4[0],
        (U4)0x30100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU5[0],
        (U4)0x30140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU6[0],
        (U4)0x30180003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU7[0],
        (U4)0x301C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU8[0],
        (U4)0x30200003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU9[0],
        (U4)0x30240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU10[0],
        (U4)0x30280003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU11[0],
        (U4)0x302C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU12[0],
        (U4)0x30300003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU13[0],
        (U4)0x30340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU14[0],
        (U4)0x30380003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU15[0],
        (U4)0x303C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU16[0],
        (U4)0x30400003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU17[0],
        (U4)0x30440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU18[0],
        (U4)0x30480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU19[0],
        (U4)0x304C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU20[0],
        (U4)0x30500003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU21[0],
        (U4)0x30540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_SETREG_INIT_PDU22[0],
        (U4)0x30580003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET1[MCU_SYS_PWR_GVIFSNDR_EDPSET1_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_PDU1[0],
        (U4)0x305C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_PDU2[0],
        (U4)0x30600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_PDU3[0],
        (U4)0x30640003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC[MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU1[0],
        (U4)0x30680008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU6[0],
        (U4)0x306C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU7[0],
        (U4)0x30700008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU12[0],
        (U4)0x30740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU13[0],
        (U4)0x30780008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU18[0],
        (U4)0x307C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU19[0],
        (U4)0x30800008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU24[0],
        (U4)0x30840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU25[0],
        (U4)0x30880008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU30[0],
        (U4)0x308C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU31[0],
        (U4)0x30900008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU36[0],
        (U4)0x30940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU37[0],
        (U4)0x30980008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU42[0],
        (U4)0x309C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU43[0],
        (U4)0x30A00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU48[0],
        (U4)0x30A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU49[0],
        (U4)0x30A80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU54[0],
        (U4)0x30AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU55[0],
        (U4)0x30B00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU60[0],
        (U4)0x30B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU61[0],
        (U4)0x30B80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU66[0],
        (U4)0x30BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU67[0],
        (U4)0x30C00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU72[0],
        (U4)0x30C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU73[0],
        (U4)0x30C80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU78[0],
        (U4)0x30CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU79[0],
        (U4)0x30D00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU84[0],
        (U4)0x30D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU85[0],
        (U4)0x30D80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU90[0],
        (U4)0x30DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU91[0],
        (U4)0x30E00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU96[0],
        (U4)0x30E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU97[0],
        (U4)0x30E80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU102[0],
        (U4)0x30EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU103[0],
        (U4)0x30F00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU108[0],
        (U4)0x30F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU109[0],
        (U4)0x30F80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU114[0],
        (U4)0x30FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU115[0],
        (U4)0x31000008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU120[0],
        (U4)0x31040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU121[0],
        (U4)0x31080008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU126[0],
        (U4)0x310C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU127[0],
        (U4)0x31100008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU132[0],
        (U4)0x31140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU133[0],
        (U4)0x31180008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU138[0],
        (U4)0x311C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU139[0],
        (U4)0x31200008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU144[0],
        (U4)0x31240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU145[0],
        (U4)0x31280008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU150[0],
        (U4)0x312C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU151[0],
        (U4)0x31300008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU156[0],
        (U4)0x31340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU157[0],
        (U4)0x31380008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU162[0],
        (U4)0x313C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU163[0],
        (U4)0x31400008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU168[0],
        (U4)0x31440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU169[0],
        (U4)0x31480008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU174[0],
        (U4)0x314C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU175[0],
        (U4)0x31500008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU180[0],
        (U4)0x31540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU181[0],
        (U4)0x31580008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU186[0],
        (U4)0x315C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU187[0],
        (U4)0x31600008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU192[0],
        (U4)0x31640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU193[0],
        (U4)0x31680008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU198[0],
        (U4)0x316C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU199[0],
        (U4)0x31700008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU204[0],
        (U4)0x31740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU205[0],
        (U4)0x31780008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU210[0],
        (U4)0x317C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU211[0],
        (U4)0x31800008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU216[0],
        (U4)0x31840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU217[0],
        (U4)0x31880008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU222[0],
        (U4)0x318C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU223[0],
        (U4)0x31900008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU228[0],
        (U4)0x31940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU229[0],
        (U4)0x31980008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU234[0],
        (U4)0x319C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU235[0],
        (U4)0x31A00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU240[0],
        (U4)0x31A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU241[0],
        (U4)0x31A80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU246[0],
        (U4)0x31AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU247[0],
        (U4)0x31B00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU252[0],
        (U4)0x31B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU253[0],
        (U4)0x31B80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU258[0],
        (U4)0x31BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU259[0],
        (U4)0x31C00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU264[0],
        (U4)0x31C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU265[0],
        (U4)0x31C80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU270[0],
        (U4)0x31CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU271[0],
        (U4)0x31D00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU276[0],
        (U4)0x31D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU277[0],
        (U4)0x31D80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU282[0],
        (U4)0x31DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU283[0],
        (U4)0x31E00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU288[0],
        (U4)0x31E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU289[0],
        (U4)0x31E80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU294[0],
        (U4)0x31EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU295[0],
        (U4)0x31F00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU300[0],
        (U4)0x31F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU301[0],
        (U4)0x31F80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU306[0],
        (U4)0x31FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU307[0],
        (U4)0x32000008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU312[0],
        (U4)0x32040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU313[0],
        (U4)0x32080008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU318[0],
        (U4)0x320C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU319[0],
        (U4)0x32100008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU324[0],
        (U4)0x32140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU325[0],
        (U4)0x32180008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU330[0],
        (U4)0x321C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU331[0],
        (U4)0x32200008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU336[0],
        (U4)0x32240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU337[0],
        (U4)0x32280008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU342[0],
        (U4)0x322C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU343[0],
        (U4)0x32300008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU348[0],
        (U4)0x32340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU349[0],
        (U4)0x32380008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU354[0],
        (U4)0x323C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU355[0],
        (U4)0x32400008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU360[0],
        (U4)0x32440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU361[0],
        (U4)0x32480008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU366[0],
        (U4)0x324C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU367[0],
        (U4)0x32500008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU372[0],
        (U4)0x32540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU373[0],
        (U4)0x32580008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU378[0],
        (U4)0x325C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU379[0],
        (U4)0x32600008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU384[0],
        (U4)0x32640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU385[0],
        (U4)0x32680008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU390[0],
        (U4)0x326C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU391[0],
        (U4)0x32700008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU396[0],
        (U4)0x32740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU397[0],
        (U4)0x32780008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU402[0],
        (U4)0x327C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU403[0],
        (U4)0x32800008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU408[0],
        (U4)0x32840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU409[0],
        (U4)0x32880008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU414[0],
        (U4)0x328C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU415[0],
        (U4)0x32900008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU420[0],
        (U4)0x32940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU421[0],
        (U4)0x32980008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU426[0],
        (U4)0x329C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU427[0],
        (U4)0x32A00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU432[0],
        (U4)0x32A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU433[0],
        (U4)0x32A80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU438[0],
        (U4)0x32AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU439[0],
        (U4)0x32B00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU444[0],
        (U4)0x32B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU445[0],
        (U4)0x32B80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU450[0],
        (U4)0x32BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU451[0],
        (U4)0x32C00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU456[0],
        (U4)0x32C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU457[0],
        (U4)0x32C80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU462[0],
        (U4)0x32CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU463[0],
        (U4)0x32D00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU468[0],
        (U4)0x32D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU469[0],
        (U4)0x32D80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU474[0],
        (U4)0x32DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU475[0],
        (U4)0x32E00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU480[0],
        (U4)0x32E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU481[0],
        (U4)0x32E80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU486[0],
        (U4)0x32EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU487[0],
        (U4)0x32F00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU492[0],
        (U4)0x32F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU493[0],
        (U4)0x32F80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU498[0],
        (U4)0x32FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU499[0],
        (U4)0x33000008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU504[0],
        (U4)0x33040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU505[0],
        (U4)0x33080008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU510[0],
        (U4)0x330C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU511[0],
        (U4)0x33100008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU516[0],
        (U4)0x33140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU517[0],
        (U4)0x33180008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU522[0],
        (U4)0x331C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU523[0],
        (U4)0x33200008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU528[0],
        (U4)0x33240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU529[0],
        (U4)0x33280008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU534[0],
        (U4)0x332C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU535[0],
        (U4)0x33300008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU540[0],
        (U4)0x33340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU541[0],
        (U4)0x33380008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU546[0],
        (U4)0x333C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU547[0],
        (U4)0x33400008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU552[0],
        (U4)0x33440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU553[0],
        (U4)0x33480008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU558[0],
        (U4)0x334C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU559[0],
        (U4)0x33500008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU564[0],
        (U4)0x33540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU565[0],
        (U4)0x33580008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU570[0],
        (U4)0x335C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU571[0],
        (U4)0x33600008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU576[0],
        (U4)0x33640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU577[0],
        (U4)0x33680008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU582[0],
        (U4)0x336C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU583[0],
        (U4)0x33700008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU588[0],
        (U4)0x33740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU589[0],
        (U4)0x33780008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU594[0],
        (U4)0x337C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU595[0],
        (U4)0x33800008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU600[0],
        (U4)0x33840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU601[0],
        (U4)0x33880008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU606[0],
        (U4)0x338C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU607[0],
        (U4)0x33900008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU612[0],
        (U4)0x33940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU613[0],
        (U4)0x33980008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU618[0],
        (U4)0x339C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU619[0],
        (U4)0x33A00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU624[0],
        (U4)0x33A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU625[0],
        (U4)0x33A80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU630[0],
        (U4)0x33AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU631[0],
        (U4)0x33B00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU636[0],
        (U4)0x33B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU637[0],
        (U4)0x33B80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU642[0],
        (U4)0x33BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU643[0],
        (U4)0x33C00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU648[0],
        (U4)0x33C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU649[0],
        (U4)0x33C80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU654[0],
        (U4)0x33CC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU655[0],
        (U4)0x33D00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU660[0],
        (U4)0x33D40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU661[0],
        (U4)0x33D80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU666[0],
        (U4)0x33DC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU667[0],
        (U4)0x33E00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU672[0],
        (U4)0x33E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU673[0],
        (U4)0x33E80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU678[0],
        (U4)0x33EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU679[0],
        (U4)0x33F00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU684[0],
        (U4)0x33F40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU685[0],
        (U4)0x33F80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_REC_PDU690[0],
        (U4)0x33FC0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD[MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU1[0],
        (U4)0x34000008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU6[0],
        (U4)0x34040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU7[0],
        (U4)0x34080008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU12[0],
        (U4)0x340C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU13[0],
        (U4)0x34100008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU18[0],
        (U4)0x34140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU19[0],
        (U4)0x34180008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU24[0],
        (U4)0x341C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU25[0],
        (U4)0x34200008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU30[0],
        (U4)0x34240003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU31[0],
        (U4)0x34280008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU36[0],
        (U4)0x342C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU37[0],
        (U4)0x34300008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU42[0],
        (U4)0x34340003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU43[0],
        (U4)0x34380008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU48[0],
        (U4)0x343C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU49[0],
        (U4)0x34400008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU54[0],
        (U4)0x34440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU55[0],
        (U4)0x34480008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU60[0],
        (U4)0x344C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU61[0],
        (U4)0x34500008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU66[0],
        (U4)0x34540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU67[0],
        (U4)0x34580008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU72[0],
        (U4)0x345C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU73[0],
        (U4)0x34600008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU78[0],
        (U4)0x34640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU79[0],
        (U4)0x34680008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU84[0],
        (U4)0x346C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU85[0],
        (U4)0x34700008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU90[0],
        (U4)0x34740003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU91[0],
        (U4)0x34780008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU96[0],
        (U4)0x347C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU97[0],
        (U4)0x34800008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU102[0],
        (U4)0x34840003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU103[0],
        (U4)0x34880008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU108[0],
        (U4)0x348C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU109[0],
        (U4)0x34900008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU114[0],
        (U4)0x34940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU115[0],
        (U4)0x34980008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU120[0],
        (U4)0x349C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU121[0],
        (U4)0x34A00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU126[0],
        (U4)0x34A40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU127[0],
        (U4)0x34A80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU132[0],
        (U4)0x34AC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU133[0],
        (U4)0x34B00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU138[0],
        (U4)0x34B40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU139[0],
        (U4)0x34B80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU144[0],
        (U4)0x34BC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU145[0],
        (U4)0x34C00008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU150[0],
        (U4)0x34C40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU151[0],
        (U4)0x34C80008U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_DPCD_PDU156[0],
        (U4)0x34CC0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET2[MCU_SYS_PWR_GVIFSNDR_EDPSET2_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET2_PDU1[0],
        (U4)0x34D00003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET3[MCU_SYS_PWR_GVIFSNDR_EDPSET3_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET3_PDU1[0],
        (U4)0x3DA40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET3_PDU2[0],
        (U4)0x3DA80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET3_PDU3[0],
        (U4)0x3DAC0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_HPD[MCU_SYS_PWR_GVIFSNDR_EDPSET_HPD_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_HPD_PDU1[0],
        (U4)0x3DB00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_HPD_PDU2[0],
        (U4)0x3DB40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_HPD_PDU3[0],
        (U4)0x3DB80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_HPD_PDU4[0],
        (U4)0x3DBC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_HPD_PDU5[0],
        (U4)0x3DC00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_EDPSET_HPD_PDU6[0],
        (U4)0x3DC40003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET3[MCU_SYS_PWR_GVIFSNDR_OUTSET3_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET3_PDU1[0],
        (U4)0x34D40003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET1[MCU_SYS_PWR_GVIFSNDR_OUTSET1_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET1_PDU1[0],
        (U4)0x34D80003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD[MCU_SYS_PWR_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD_PDU1[0],
        (U4)0x34DC0002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD_PDU2[0],
        (U4)0x34E00002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET2[MCU_SYS_PWR_GVIFSNDR_OUTSET2_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET2_PDU1[0],
        (U4)0x34E40003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET2_PDU2[0],
        (U4)0x34E80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET2_PDU3[0],
        (U4)0x34EC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET2_PDU4[0],
        (U4)0x34F00003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET2_PDU5[0],
        (U4)0x34F40003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1[MCU_SYS_PWR_GVIFSNDR_HDCP1_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1_PDU1[0],
        (U4)0x34F80003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1_PDU2[0],
        (U4)0x34FC0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1_PDU3[0],
        (U4)0x35000003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1_PDU4[0],
        (U4)0x35040003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1_PDU5[0],
        (U4)0x35080003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1_PDU6[0],
        (U4)0x350C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1_PDU7[0],
        (U4)0x35100003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1_PDU8[0],
        (U4)0x35140003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP1_PDU9[0],
        (U4)0x35180003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP2[MCU_SYS_PWR_GVIFSNDR_HDCP2_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP2_PDU1[0],
        (U4)0x351C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_STATUS_RD[MCU_SYS_PWR_GVIFSNDR_HDCPTX_STATUS_RD_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_STATUS_RD_PDU1[0],
        (U4)0x35200002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_STATUS_RD_PDU2[0],
        (U4)0x35240002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_EVENT_RD[MCU_SYS_PWR_GVIFSNDR_HDCPTX_EVENT_RD_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_EVENT_RD_PDU1[0],
        (U4)0x35280002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_EVENT_RD_PDU2[0],
        (U4)0x352C0002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP3[MCU_SYS_PWR_GVIFSNDR_HDCP3_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP3_PDU1[0],
        (U4)0x35300003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD[MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD_PDU1[0],
        (U4)0x35340002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD_PDU2[0],
        (U4)0x35380003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEV_ID_RD[MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEV_ID_RD_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEV_ID_RD_PDU1[0],
        (U4)0x353C0002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEV_ID_RD_PDU2[0],
        (U4)0x35400006U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP4[MCU_SYS_PWR_GVIFSNDR_HDCP4_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP4_PDU1[0],
        (U4)0x35440003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP4_PDU2[0],
        (U4)0x35480003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP4_PDU3[0],
        (U4)0x354C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP4_PDU4[0],
        (U4)0x35500003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP_HPD[MCU_SYS_PWR_GVIFSNDR_EDPSET_HPD_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP_HPD_PDU1[0],
        (U4)0x35540003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP_HPD_PDU2[0],
        (U4)0x35580003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP_HPD_PDU3[0],
        (U4)0x355C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP_HPD_PDU4[0],
        (U4)0x35600003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP_HPD_PDU5[0],
        (U4)0x35640003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP_HPD_PDU6[0],
        (U4)0x35680003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_ENC_RD[MCU_SYS_PWR_GVIFSNDR_HDCPTX_ENC_RD_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_ENC_RD_PDU1[0],
        (U4)0x356C0002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_ENC_RD_PDU2[0],
        (U4)0x35700002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP5[MCU_SYS_PWR_GVIFSNDR_HDCP5_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP5_PDU1[0],
        (U4)0x35740003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCPSTOP[MCU_SYS_PWR_GVIFSNDR_HDCPSTOP_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPSTOP_PDU1[0],
        (U4)0x35780003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPSTOP_PDU2[0],
        (U4)0x357C0003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPSTOP_PDU3[0],
        (U4)0x35800003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPSTOP_PDU4[0],
        (U4)0x35840003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP6[MCU_SYS_PWR_GVIFSNDR_HDCP6_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP6_PDU1[0],
        (U4)0x35880003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_GVIF3TX0_ACT_RD[MCU_SYS_PWR_GVIFSNDR_GVIF3TX0_ACT_RD_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_GVIF3TX0_ACT_RD_PDU1[0],
        (U4)0x358C0002U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_GVIF3TX0_ACT_RD_PDU2[0],
        (U4)0x35900002U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP7[MCU_SYS_PWR_GVIFSNDR_HDCP7_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP7_PDU1[0],
        (U4)0x35940003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP7_PDU2[0],
        (U4)0x35980003U
    },
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP7_PDU3[0],
        (U4)0x359C0003U
    }
};

const ST_GP_I2C_MA_REQ st_sp_MCU_SYS_PWR_GVIFSNDR_HDCP8[MCU_SYS_PWR_GVIFSNDR_HDCP8_NUM] = {
    {
        (U1 *)&u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCP8_PDU1[0],
        (U4)0x35A00003U
    }
};

/*****************************************************************************
  Function      : Mcu_Sys_Pwr_GvifSndr_Init
  Description   : 初期化関数
  param[in/out] : none
  return        : none
  Note          : 読出し用バッファの初期化,固定値ではない書込み用バッファの初期化
*****************************************************************************/
void Mcu_Sys_Pwr_GvifSndr_Init( void )
{
    uint32 mcu_cnt;

    /*  データリード用テーブル初期化 */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD_PDU2[0] = (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_OUTSET_GVIF3TX0_ACTIVATED_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_STATUS_RD_PDU2[0] = (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_STATUS_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_EVENT_RD_PDU2[0] = (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_EVENT_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD_PDU2[0] = (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_RD;    /* Slave Address */
    for(mcu_cnt = (U4)1U; mcu_cnt < (U4)3U; mcu_cnt++) {
        u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEVS_CASCADE_RD_PDU2[mcu_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /* Receiver ID取得 5Byte Read 書込み用テーブル(Write Address可変)初期化 */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEV_ID_RD_PDU1[0] = (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_WR;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEV_ID_RD_PDU1[1] = (U1)0x50U;    /* Write Address初期値(定期処理内で更新) */

    /*  データリード用テーブル(BurstRead)初期化 */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEV_ID_RD_PDU2[0] = (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_RD;    /* Slave Address */
    for(mcu_cnt = (U4)1U; mcu_cnt < (U4)6U; mcu_cnt++) {
        u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_DEV_ID_RD_PDU2[mcu_cnt] = (U1)0U;    /* 読出しデータ初期値 */
    }

    /*  データリード用テーブル初期化 */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_ENC_RD_PDU2[0] = (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_HDCPTX_ENC_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */

    /*  データリード用テーブル初期化 */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_GVIF3TX0_ACT_RD_PDU2[0] = (U1)MCU_SYS_PWR_GVIFSNDR_SLAVEADR_RD;    /* Slave Address */
    u1_sp_MCU_SYS_PWR_GVIFSNDR_GVIF3TX0_ACT_RD_PDU2[1] = (U1)0U;    /* 読出しデータ初期値 */
}

/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*  Function Definitions                                                                                                             */
/*-----------------------------------------------------------------------------------------------------------------------------------*/
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Change History                                                                                                                   */
/*                                                                                                                                   */
/*===================================================================================================================================*/
/*                                                                                                                                   */
/*  Version  Date        Author   Change Description                                                                                 */
/* --------- ----------  -------  -------------------------------------------------------------------------------------------------- */
/*  0.0.0    12/06/2024  TN       New.                                                                                               */
/*                                                                                                                                   */
/*  * TN   = Tatsuya Niimi, KSE                                                                                                      */
/*                                                                                                                                   */
/*===================================================================================================================================*/
